#include <nw4r/snd.h>
#include <nw4r/ut.h>

#include <climits>
#include <cstring>

namespace nw4r {
namespace snd {
namespace detail {

u8 StrmPlayer::sLoadBuffer[LOAD_BUFFER_SIZE] ALIGN(32);
OSMutex StrmPlayer::sLoadBufferMutex;

bool StrmPlayer::sStaticInitFlag = false;

namespace {

// FE10's ut::DynamicCast also accepts NULL
template <typename TDerived, typename TBase>
inline TDerived DynamicCastNullable(TBase* pPtr) {
    const ut::detail::RuntimeTypeInfo* pDerivedTypeInfo =
        ut::detail::GetTypeInfoFromPtr_(static_cast<TDerived>(NULL));

    if (pPtr != NULL &&
        pPtr->GetRuntimeTypeInfo()->IsDerivedFrom(pDerivedTypeInfo)) {
        return static_cast<TDerived>(pPtr);
    }

    return NULL;
}

} // namespace

StrmPlayer::StrmPlayer()
    : mSetupFlag(false), mActiveFlag(false), mFileStream(NULL) {

    if (!sStaticInitFlag) {
        OSInitMutex(&sLoadBufferMutex);
        sStaticInitFlag = true;
    }

    mStrmDataLoadTaskPool.Create(
        mStrmDataLoadTaskArea, DATA_BLOCK_COUNT_MAX * sizeof(StrmDataLoadTask));
}

StrmPlayer::~StrmPlayer() {
    Shutdown();
}

StrmPlayer::SetupResult StrmPlayer::Setup(StrmBufferPool* pBufferPool,
                                          int allocChannelCount,
                                          u16 allocTrackFlag,
                                          int voiceOutCount) {
    SoundThread::AutoLock lock;

    if (mSetupFlag) {
        Shutdown();
    }

    InitParam();
    mChannelCount = ut::Min(allocChannelCount, STRM_CHANNEL_NUM);

    u32 bitMask = allocTrackFlag;

    int trackIndex;
    for (trackIndex = 0; bitMask; bitMask >>= 1, trackIndex++) {
        if (!(bitMask & 1)) {
            continue;
        }

        if (trackIndex >= STRM_TRACK_NUM) {
            break;
        }

        mTracks[trackIndex].mActiveFlag = true;
    }

    mTrackCount = ut::Min(trackIndex, STRM_TRACK_NUM);
    if (mTrackCount == 0) {
        return SETUP_ERR_UNKNOWN;
    }

    mVoiceOutCount = voiceOutCount;
    mBufferPool = pBufferPool;

    {
        ut::AutoInterruptLock lockIntr;

        if (mChannelCount > 0) {
            if (!AllocStrmBuffers()) {
                return SETUP_ERR_CANNOT_ALLOCATE_BUFFER;
            }

            mAllocStrmBufferFlag = true;
        }
    }

    mSetupFlag = true;
    return SETUP_SUCCESS;
}

void StrmPlayer::Shutdown() {
    Stop();

    SoundThread::AutoLock lock;

    if (!mSetupFlag) {
        return;
    }

    mBufferPool = NULL;
    mStrmDataLoadTaskPool.Destroy(
        mStrmDataLoadTaskArea, DATA_BLOCK_COUNT_MAX * sizeof(StrmDataLoadTask));

    mSetupFlag = false;
}

bool StrmPlayer::Prepare(ut::FileStream* pFileStream,
                         StartOffsetType offsetType, int offset) {
    SoundThread::AutoLock lock;

    mFileStream = pFileStream;
    mStartOffsetType = offsetType;
    mStartOffset = offset;

    mTaskErrorFlag = false;
    mTaskCancelFlag = false;
    mLoadingDelayFlag = false;
    mActiveFlag = true;
    SoundThread::GetInstance().RegisterPlayerCallback(this);

    StrmHeaderLoadTask* pTask = &mStrmHeaderLoadTask;
    pTask->strmPlayer = this;
    pTask->fileStream = mFileStream;
    pTask->startOffsetType = mStartOffsetType;
    pTask->startOffset = mStartOffset;
    TaskManager::GetInstance().AppendTask(pTask);

    return true;
}

bool StrmPlayer::Start() {
    SoundThread::AutoLock lock;

    if (!mPreparedFlag) {
        return false;
    }

    if (!mStartedFlag) {
        if (!AllocVoices(mVoiceOutCount)) {
            FreeStrmBuffers();
            return false;
        }

        s32 blockIndex = 0;
        u32 blockOffset = 0;
        s32 loopCount = 0;

        if (!CalcStartOffset(&blockIndex, &blockOffset, &loopCount)) {
            return false;
        }

        mLoopCounter += loopCount;

        for (int trackIndex = 0; trackIndex < mTrackCount; trackIndex++) {
            StrmTrack& rTrack = mTracks[trackIndex];
            if (!rTrack.mActiveFlag) {
                continue;
            }

            WaveData waveData;
            waveData.sampleFormat = mStrmInfo.format;
            waveData.loopFlag = true;
            waveData.numChannels = rTrack.mTrackInfo.channelCount;
            waveData.sampleRate = mStrmInfo.sampleRate;
            waveData.loopStart = 0;

            AxVoice::Format format =
                WaveFileReader::GetAxVoiceFormatFromWaveFileFormat(
                    mStrmInfo.format);

            waveData.loopEnd = AxVoice::GetSampleByByte(
                mDataBlockSize * mPlayingBufferBlockCount, format);

            for (int i = 0; i < rTrack.mTrackInfo.channelCount; i++) {
                StrmChannel* pChannel = GetTrackChannel(rTrack, i);
                ChannelParam& rParam = waveData.channelParam[i];

                rParam.dataAddr = pChannel->bufferAddress;
                rParam.adpcmInfo = pChannel->adpcmInfo;
                rParam.adpcmInfo.param.pred_scale =
                    *static_cast<u8*>(pChannel->bufferAddress);
            }

            ut::AutoInterruptLock lock;

            if (rTrack.mVoice != NULL) {
                rTrack.mVoice->Setup(waveData, blockOffset);
                rTrack.mVoice->SetVoiceType(AxVoice::VOICE_TYPE_STREAM);
                rTrack.mVoice->Start();
            }
        }

        if (blockIndex == mStrmInfo.numBlocks - 2) {
            UpdateDataLoopAddress(1);
        } else if (blockIndex == mStrmInfo.numBlocks - 1) {
            UpdateDataLoopAddress(0);
        }

        UpdatePauseStatus();
        mStartedFlag = true;
    }

    return true;
}

void StrmPlayer::Stop() {
    {
        SoundThread::AutoLock lock;

        for (int i = 0; i < STRM_TRACK_NUM; i++) {
            if (mTracks[i].mActiveFlag) {
                Voice* pVoice = mTracks[i].mVoice;
                if (pVoice != NULL) {
                    pVoice->Stop();
                }
            }
        }

        if (mActiveFlag) {
            SoundThread::GetInstance().UnregisterPlayerCallback(this);
        }
    }

    TaskManager::GetInstance().CancelTask(&mStrmHeaderLoadTask);

    {
        ut::AutoInterruptLock lock;

        while (!mStrmDataLoadTaskList.IsEmpty()) {
            TaskManager::GetInstance().CancelTask(
                &mStrmDataLoadTaskList.GetBack());
        }
    }

    FreeStrmBuffers();
    FreeVoices();

    {
        SoundThread::AutoLock lock;

        if (mFileStream != NULL) {
            mFileStream->Close();
            mFileStream = NULL;
        }
    }

    mStartedFlag = false;
    mPreparedFlag = false;
    mActiveFlag = false;
}

void StrmPlayer::Pause(bool flag) {
    SoundThread::AutoLock lock;

    mPauseFlag = flag;

    if (flag) {
        mLoadWaitFlag = true;
    }

    UpdatePauseStatus();
}

void StrmPlayer::InitParam() {
    BasicPlayer::InitParam();

    mStartedFlag = false;
    mPreparedFlag = false;
    mLoadFinishFlag = false;
    mPauseFlag = false;
    mPauseStatus = false;
    mLoadWaitFlag = false;
    mNoRealtimeLoadFlag = false;
    mPlayFinishFlag = false;
    mSkipUpdateAdpcmLoop = false;
    mValidAdpcmLoop = false;
    mAllocStrmBufferFlag = false;
    mLoopCounter = 0;
    mVoiceOutCount = 1;

    for (int i = 0; i < STRM_TRACK_NUM; i++) {
        StrmTrack& rTrack = mTracks[i];

        rTrack.mActiveFlag = false;
        rTrack.mVolume = 1.0f;
        rTrack.mPan = 0.0f;
        rTrack.mVoice = NULL;
    }

    for (int i = 0; i < STRM_CHANNEL_NUM; i++) {
        mChannels[i].bufferAddress = NULL;
    }
}

bool StrmPlayer::LoadHeader(ut::FileStream* pFileStream,
                            StartOffsetType offsetType, int offset) {
    ut::detail::AutoLock<OSMutex> lock(sLoadBufferMutex);

    StrmFileLoader loader(*pFileStream);
    if (!loader.LoadFileHeader(sLoadBuffer, LOAD_BUFFER_SIZE)) {
        return false;
    }

    loader.ReadStrmInfo(&mStrmInfo);

    if (mChannelCount == 0) {
        mChannelCount = ut::Min(loader.GetChannelCount(), STRM_CHANNEL_NUM);
    }

    for (int i = 0; i < mTrackCount; i++) {
        loader.ReadStrmTrackInfo(&mTracks[i].mTrackInfo, i);
    }

    if (mStrmInfo.format == WaveFile::FORMAT_ADPCM) {
        for (int i = 0; i < mChannelCount; i++) {
            loader.ReadAdpcmInfo(&mChannels[i].adpcmInfo, i);
        }

        if (offset != 0) {
            int startSample;
            if (offsetType == START_OFFSET_TYPE_SAMPLE) {
                startSample = offset;
            } else if (offsetType == START_OFFSET_TYPE_MILLISEC) {
                startSample = offset * mStrmInfo.sampleRate / 1000;
            }

            s32 block = startSample / static_cast<s32>(mStrmInfo.blockSamples);

            u16 yn1[STRM_CHANNEL_NUM];
            u16 yn2[STRM_CHANNEL_NUM];
            loader.ReadAdpcBlockData(yn1, yn2, block, mStrmInfo.numChannels);

            for (int i = 0; i < mStrmInfo.numChannels; i++) {
                mChannels[i].adpcmInfo.param.yn1 = yn1[i];
                mChannels[i].adpcmInfo.param.yn2 = yn2[i];
            }
        }
    }

    if (!SetupPlayer()) {
        return false;
    }

    mPrepareCounter = 0;
    for (int i = 0; i < mBufferBlockCountBase; i++) {
        UpdateLoadingBlockIndex();
        mPrepareCounter++;

        if (mLoadFinishFlag) {
            break;
        }
    }

    if (mStrmInfo.numBlocks <= 2 && !mStrmInfo.loopFlag) {
        SetLoopEndToZeroBuffer(mStrmInfo.numBlocks - 1);
    }

    return true;
}

bool StrmPlayer::LoadStreamData(ut::FileStream* pFileStream, int offset,
                                u32 /* size */, u32 blockSize, int blockIndex,
                                bool needUpdateAdpcmLoop) {
    ut::DvdFileStream* pDvdStream =
        DynamicCastNullable<ut::DvdFileStream*>(pFileStream);

    if (pDvdStream != NULL) {
        pDvdStream->SetPriority(DVD_PRIO_HIGH);
    }

    ut::detail::AutoLock<OSMutex> lock(sLoadBufferMutex);
    DCInvalidateRange(sLoadBuffer, LOAD_BUFFER_SIZE);

    int loadOffset = offset + mStrmInfo.blockHeaderOffset;
    u16 adpcmPredScale[STRM_CHANNEL_NUM];

    int currentChannel = 0;
    while (currentChannel < mChannelCount) {
        int loadChannelCount = CHANNEL_MAX;
        if (currentChannel + loadChannelCount > mChannelCount) {
            loadChannelCount = mChannelCount - currentChannel;
        }

        u32 loadSize = blockSize * loadChannelCount;

        pFileStream->Seek(loadOffset, ut::FileStream::SEEK_ORIGIN_BEG);
        s32 bytesRead = pFileStream->Read(sLoadBuffer, loadSize);

        if (bytesRead != loadSize) {
            return false;
        }

        for (int i = 0; i < loadChannelCount; i++) {
            if (needUpdateAdpcmLoop) {
                adpcmPredScale[currentChannel] = sLoadBuffer[blockSize * i];
            }

            u32 len = blockSize;
            const void* pSrc = ut::AddOffsetToPtr(sLoadBuffer, blockSize * i);
            void* pDst =
                ut::AddOffsetToPtr(mChannels[currentChannel].bufferAddress,
                                   mDataBlockSize * blockIndex);

            std::memcpy(pDst, pSrc, len);
            DCFlushRange(pDst, len);

            currentChannel++;
        }

        loadOffset += loadSize;
    }

    if (needUpdateAdpcmLoop) {
        SetAdpcmLoopContext(mChannelCount, adpcmPredScale);
    }

    if (!mPreparedFlag && --mPrepareCounter == 0) {
        mPreparedFlag = true;
    }

    return true;
}

bool StrmPlayer::SetupPlayer() {
    u32 poolBlockSize = mBufferPool->GetBlockSize();

    s32 blockIndex = 0;
    u32 blockOffset = 0;
    s32 loopCount = 0;
    if (!CalcStartOffset(&blockIndex, &blockOffset, &loopCount)) {
        return false;
    }

    mLoopStartBlockIndex = mStrmInfo.loopStart / mStrmInfo.blockSamples;
    mLastBlockIndex = mStrmInfo.numBlocks - 1;

    mDataBlockSize = mStrmInfo.blockSize;
    if (mDataBlockSize > DATA_BLOCK_SIZE_MAX) {
        return false;
    }

    mBufferBlockCount = poolBlockSize / mDataBlockSize;
    if (mBufferBlockCount < DATA_BLOCK_COUNT_MIN) {
        return false;
    }

    if (mBufferBlockCount > DATA_BLOCK_COUNT_MAX) {
        mBufferBlockCount = DATA_BLOCK_COUNT_MAX;
    }

    mBufferBlockCountBase = mBufferBlockCount - 1;
    mChangeNumBlocks = mBufferBlockCountBase;

    mPlayingDataBlockIndex = blockIndex;
    mLoadingDataBlockIndex = blockIndex;

    mLoadingBufferBlockIndex = 0;
    mPlayingBufferBlockIndex = 0;

    if (mNoRealtimeLoadFlag) {
        mLoadingBufferBlockCount = mStrmInfo.numBlocks;
    } else {
        mLoadingBufferBlockCount = CalcLoadingBufferBlockCount();
    }

    mPlayingBufferBlockCount = mLoadingBufferBlockCount;

    ut::AutoInterruptLock lock;

    if (!mAllocStrmBufferFlag) {
        if (!AllocStrmBuffers()) {
            return false;
        }

        mAllocStrmBufferFlag = true;
    }

    return true;
}

bool StrmPlayer::AllocStrmBuffers() {
    for (int i = 0; i < mChannelCount; i++) {
        void* pBuffer = mBufferPool->Alloc();

        if (pBuffer == NULL) {
            for (int j = 0; j < i; j++) {
                mBufferPool->Free(mChannels[j].bufferAddress);
                mChannels[j].bufferAddress = NULL;
            }

            return false;
        }

        mChannels[i].bufferAddress = pBuffer;
    }

    return true;
}

void StrmPlayer::FreeStrmBuffers() {
    for (int i = 0; i < mChannelCount; i++) {
        if (mChannels[i].bufferAddress == NULL) {
            continue;
        }

        mBufferPool->Free(mChannels[i].bufferAddress);
        mChannels[i].bufferAddress = NULL;
    }
}

bool StrmPlayer::AllocVoices(int voiceOutCount) {
    ut::AutoInterruptLock lock;

    for (int trackIndex = 0; trackIndex < mTrackCount; trackIndex++) {
        StrmTrack& rTrack = mTracks[trackIndex];
        if (!rTrack.mActiveFlag) {
            continue;
        }

        Voice* pVoice = VoiceManager::GetInstance().AllocVoice(
            rTrack.mTrackInfo.channelCount, voiceOutCount, Voice::PRIORITY_MAX,
            VoiceCallbackFunc, &mTracks[trackIndex]);

        if (pVoice == NULL) {
            for (int i = 0; i < trackIndex; i++) {
                StrmTrack& rOther = mTracks[i];

                if (rOther.mVoice != NULL) {
                    rOther.mVoice->Free();
                    rOther.mVoice = NULL;
                }
            }

            return false;
        }

        rTrack.mVoice = pVoice;
        pVoice->SetVoiceOutParamPitchDisableFlag(true);
    }

    return true;
}

void StrmPlayer::FreeVoices() {
    ut::AutoInterruptLock lock;

    for (int trackIndex = 0; trackIndex < mTrackCount; trackIndex++) {
        StrmTrack& rTrack = mTracks[trackIndex];
        if (!rTrack.mActiveFlag) {
            continue;
        }

        if (rTrack.mVoice != NULL) {
            rTrack.mVoice->Free();
            rTrack.mVoice = NULL;
        }
    }
}

void StrmPlayer::Update() {
    if (!mActiveFlag) {
        return;
    }

    if (mTaskErrorFlag && !mTaskCancelFlag) {
        Stop();
        return;
    }

    if (mStartedFlag) {
        for (int trackIndex = 0; trackIndex < mTrackCount; trackIndex++) {
            StrmTrack& rTrack = mTracks[trackIndex];

            if (rTrack.mActiveFlag && rTrack.mVoice == NULL) {
                Stop();
                return;
            }
        }
    }

    if (mLoadWaitFlag && mStrmDataLoadTaskList.IsEmpty()) {
        mLoadWaitFlag = false;
        UpdatePauseStatus();
    }

    if (mLoadingDelayFlag) {
        mLoadingDelayFlag = false;
    }

    for (int trackIndex = 0; trackIndex < mTrackCount; trackIndex++) {
        UpdateVoiceParams(&mTracks[trackIndex]);
    }
}

void StrmPlayer::UpdateVoiceParams(StrmTrack* pTrack) {
    if (!pTrack->mActiveFlag) {
        return;
    }

    f32 volume = 1.0f;
    volume *= GetVolume();
    volume *= pTrack->mTrackInfo.volume / 127.0f;
    volume *= pTrack->mVolume;

    f32 pitchRatio = 1.0f;
    pitchRatio *= GetPitch();

    f32 pan = 0.0f;
    pan += GetPan();
    if (pTrack->mTrackInfo.pan <= 1) {
        pan += (pTrack->mTrackInfo.pan - 63) / 63.0f;
    } else {
        pan += (pTrack->mTrackInfo.pan - 64) / 63.0f;
    }
    pan += pTrack->mPan;

    f32 surroundPan = 0.0f;
    surroundPan += GetSurroundPan();

    f32 lpfFreq = 1.0f;
    lpfFreq += GetLpfFreq();

    int remoteFilter = 0;
    remoteFilter += GetRemoteFilter();

    f32 mainSend = 0.0f;
    mainSend += GetMainSend();

    f32 fxSend[AUX_BUS_NUM];
    for (int i = 0; i < AUX_BUS_NUM; i++) {
        fxSend[i] = 0.0f;
        fxSend[i] += GetFxSend(static_cast<AuxBus>(i));
    }

    f32 remoteOutVolume[WPAD_MAX_CONTROLLERS];
    f32 remoteSend[WPAD_MAX_CONTROLLERS];
    f32 remoteFxSend[WPAD_MAX_CONTROLLERS];
    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        remoteOutVolume[i] = GetRemoteOutVolume(i);

        remoteSend[i] = 0.0f;
        remoteSend[i] += GetRemoteSend(i);

        remoteFxSend[i] = 0.0f;
        remoteFxSend[i] += GetRemoteFxSend(i);
    }

    ut::AutoInterruptLock lock;

    Voice* pVoice = pTrack->mVoice;
    if (pVoice != NULL) {
        pVoice->SetVolume(volume);
        pVoice->SetPitch(pitchRatio);
        pVoice->SetPan(pan);
        pVoice->SetSurroundPan(surroundPan);
        pVoice->SetLpfFreq(lpfFreq);
        pVoice->SetRemoteFilter(remoteFilter);
        pVoice->SetOutputLine(GetOutputLine());
        pVoice->SetMainOutVolume(GetMainOutVolume());
        pVoice->SetMainSend(mainSend);

        for (int i = 0; i < AUX_BUS_NUM; i++) {
            pVoice->SetFxSend(static_cast<AuxBus>(i), fxSend[i]);
        }

        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
            pVoice->SetRemoteOutVolume(i, remoteOutVolume[i]);
            pVoice->SetRemoteSend(i, remoteSend[i]);
            pVoice->SetRemoteFxSend(i, remoteFxSend[i]);
        }

        for (int i = 0; i < mVoiceOutCount; i++) {
            pVoice->SetVoiceOutParam(i, GetVoiceOutParam(i));
        }
    }
}

void StrmPlayer::UpdateBuffer() {
    if (!mStartedFlag) {
        return;
    }

    if (!mTracks[0].mActiveFlag) {
        return;
    }

    Voice* pVoice = mTracks[0].mVoice;
    if (pVoice == NULL) {
        return;
    }

    if (AxManager::GetInstance().IsDiskError()) {
        mLoadWaitFlag = true;
        UpdatePauseStatus();
    }

    if (!mPlayFinishFlag && !mNoRealtimeLoadFlag && !mLoadWaitFlag) {
        u32 sample = pVoice->GetCurrentPlayingSample();
        int block = sample / mStrmInfo.blockSamples;

        while (mPlayingBufferBlockIndex != block) {
            if (!mLoadWaitFlag && mStrmDataLoadTaskList.GetSize() >=
                                      mBufferBlockCountBase - 2) {

                mLoadingDelayFlag = true;
                mLoadWaitFlag = true;
                UpdatePauseStatus();
                break;
            }

            UpdatePlayingBlockIndex();
            UpdateLoadingBlockIndex();
        }
    }
}

void StrmPlayer::UpdateLoopAddress(u32 startSample, u32 endSample) {
    ut::AutoInterruptLock lock;

    for (int trackIndex = 0; trackIndex < mTrackCount; trackIndex++) {
        StrmTrack& rTrack = mTracks[trackIndex];
        if (!rTrack.mActiveFlag) {
            continue;
        }

        Voice* pVoice = rTrack.mVoice;
        if (pVoice == NULL) {
            continue;
        }

        for (int i = 0; i < rTrack.mTrackInfo.channelCount; i++) {
            StrmChannel* pChannel = GetTrackChannel(mTracks[trackIndex], i);

            pVoice->SetLoopStart(i, pChannel->bufferAddress, startSample);
            pVoice->SetLoopEnd(i, pChannel->bufferAddress, endSample);
        }

        pVoice->SetLoopFlag(true);
    }
}

void StrmPlayer::UpdatePlayingBlockIndex() {
    mPlayingDataBlockIndex++;

    if (mPlayingDataBlockIndex > mLastBlockIndex && mStrmInfo.loopFlag) {
        mPlayingDataBlockIndex = mLoopStartBlockIndex;

        if (mLoopCounter < INT_MAX) {
            mLoopCounter++;
        }

        UpdateLoopAddress(0, mPlayingBufferBlockCount * mStrmInfo.blockSamples);
    }

    mPlayingBufferBlockIndex++;

    if (mPlayingBufferBlockIndex >= mPlayingBufferBlockCount) {
        mPlayingBufferBlockIndex = 0;
        mPlayingBufferBlockCount = mLoadingBufferBlockCount;

        UpdateLoopAddress(0, mPlayingBufferBlockCount * mStrmInfo.blockSamples);
    }

    if (mPlayingBufferBlockIndex == mPlayingBufferBlockCount - 1) {
        if (!mSkipUpdateAdpcmLoop && mValidAdpcmLoop) {
            for (int trackIndex = 0; trackIndex < mTrackCount; trackIndex++) {
                StrmTrack& rTrack = mTracks[trackIndex];
                if (!rTrack.mActiveFlag) {
                    continue;
                }

                Voice* pVoice = rTrack.mVoice;
                if (pVoice == NULL) {
                    continue;
                }

                if (pVoice->GetFormat() == AxVoice::FORMAT_ADPCM) {
                    ut::AutoInterruptLock lock;

                    for (int i = 0; i < rTrack.mTrackInfo.channelCount; i++) {
                        StrmChannel* pChannel = GetTrackChannel(rTrack, i);

                        AdpcmLoopParam loopParam;
                        loopParam.loop_pred_scale = pChannel->adpcmPredScale;
                        loopParam.loop_yn1 = 0;
                        loopParam.loop_yn2 = 0;

                        pVoice->SetAdpcmLoop(i, &loopParam);
                    }

                    pVoice->SetVoiceType(AxVoice::VOICE_TYPE_STREAM);
                }
            }
        }

        mValidAdpcmLoop = false;
        mSkipUpdateAdpcmLoop = false;
    }

    if (mPlayingDataBlockIndex == mLastBlockIndex - 1) {
        UpdateDataLoopAddress(mPlayingBufferBlockIndex + 1);
    }
}

void StrmPlayer::UpdateDataLoopAddress(s32 endBlock) {
    if (mStrmInfo.loopFlag) {
        s32 startBlock = endBlock + 1;
        if (startBlock >= mPlayingBufferBlockCount) {
            startBlock -= mPlayingBufferBlockCount;
        }

        ut::AutoInterruptLock lock;

        UpdateLoopAddress(startBlock * mStrmInfo.blockSamples,
                          mStrmInfo.lastBlockSamples +
                              (endBlock * mStrmInfo.blockSamples));

        if (mStrmInfo.format == WaveFile::FORMAT_ADPCM) {
            for (int trackIndex = 0; trackIndex < mTrackCount; trackIndex++) {
                StrmTrack& rTrack = mTracks[trackIndex];
                if (!rTrack.mActiveFlag) {
                    continue;
                }

                Voice* pVoice = rTrack.mVoice;
                if (pVoice == NULL) {
                    continue;
                }

                if (pVoice->GetFormat() == AxVoice::FORMAT_ADPCM) {
                    pVoice->SetVoiceType(AxVoice::VOICE_TYPE_NORMAL);

                    for (int i = 0; i < rTrack.mTrackInfo.channelCount; i++) {
                        StrmChannel* pChannel = GetTrackChannel(rTrack, i);
                        pVoice->SetAdpcmLoop(i,
                                             &pChannel->adpcmInfo.loopParam);
                    }
                }
            }

            if (endBlock == mPlayingBufferBlockCount - 1) {
                mSkipUpdateAdpcmLoop = true;
            }
        }
    } else {
        SetLoopEndToZeroBuffer(endBlock);
    }
}

void StrmPlayer::SetLoopEndToZeroBuffer(int endBlock) {
    {
        ut::AutoInterruptLock lock;

        for (int trackIndex = 0; trackIndex < mTrackCount; trackIndex++) {
            StrmTrack& rTrack = mTracks[trackIndex];
            if (!rTrack.mActiveFlag) {
                continue;
            }

            Voice* pVoice = rTrack.mVoice;
            if (pVoice == NULL) {
                continue;
            }

            for (int i = 0; i < rTrack.mTrackInfo.channelCount; i++) {
                StrmChannel* pChannel = GetTrackChannel(rTrack, i);

                pVoice->StopAtPoint(i, pChannel->bufferAddress,
                                    mStrmInfo.lastBlockSamples +
                                        endBlock * mStrmInfo.blockSamples);
            }
        }
    }

    mPlayFinishFlag = true;
}

void StrmPlayer::UpdateLoadingBlockIndex() {
    if (mLoadFinishFlag) {
        return;
    }

    u32 blockSize =
        mLoadingDataBlockIndex < static_cast<s32>(mStrmInfo.numBlocks - 1)
            ? mStrmInfo.blockSize
            : mStrmInfo.lastBlockPaddedSize;

    u32 loadSize = mStrmInfo.blockHeaderOffset + blockSize * mChannelCount;

    s32 loadOffset =
        mStrmInfo.dataOffset +
        mLoadingDataBlockIndex * (mStrmInfo.blockHeaderOffset +
                                  mStrmInfo.blockSize * mStrmInfo.numChannels);

    bool needUpdateAdpcmLoop = mLoadingBufferBlockIndex == 0 &&
                               mStrmInfo.format == WaveFile::FORMAT_ADPCM;

    StrmDataLoadTask* pTask = mStrmDataLoadTaskPool.Alloc();
    pTask->strmPlayer = this;
    pTask->fileStream = mFileStream;
    pTask->size = loadSize;
    pTask->offset = loadOffset;
    pTask->blockSize = blockSize;
    pTask->bufferBlockIndex = mLoadingBufferBlockIndex;
    pTask->needUpdateAdpcmLoop = needUpdateAdpcmLoop;

    ut::AutoInterruptLock lock;
    mStrmDataLoadTaskList.PushBack(pTask);

    TaskManager::GetInstance().AppendTask(
        pTask, mStartedFlag ? TaskManager::PRIORITY_HIGH
                            : TaskManager::PRIORITY_MIDDLE);

    mLoadingDataBlockIndex++;

    if (mLoadingDataBlockIndex > mLastBlockIndex) {
        if (mStrmInfo.loopFlag) {
            mLoadingDataBlockIndex = mLoopStartBlockIndex;
        } else {
            mLoadFinishFlag = true;
            return;
        }
    }

    mLoadingBufferBlockIndex++;

    if (mLoadingBufferBlockIndex >= mLoadingBufferBlockCount) {
        mLoadingBufferBlockIndex = 0;
        mLoadingBufferBlockCount = CalcLoadingBufferBlockCount();
    }
}

void StrmPlayer::UpdatePauseStatus() {
    ut::AutoInterruptLock lock;

    bool paused = false;

    if (mPauseFlag) {
        paused = true;
    }

    if (mLoadWaitFlag) {
        paused = true;
    }

    if (paused != mPauseStatus) {
        for (int trackIndex = 0; trackIndex < mTrackCount; trackIndex++) {
            if (!mTracks[trackIndex].mActiveFlag) {
                continue;
            }

            Voice* pVoice = mTracks[trackIndex].mVoice;
            if (pVoice != NULL) {
                pVoice->Pause(paused);
            }
        }

        mPauseStatus = paused;
    }
}

int StrmPlayer::CalcLoadingBufferBlockCount() const {
    int restBlocks = (mLastBlockIndex - mLoadingDataBlockIndex) + 1;
    int loopBlocks = (mLastBlockIndex - mLoopStartBlockIndex) + 1;

    if ((mBufferBlockCountBase + 1 - restBlocks) % loopBlocks == 0) {
        return mBufferBlockCountBase + 1;
    }

    return mBufferBlockCountBase;
}

bool StrmPlayer::CalcStartOffset(s32* pBlockIndex, u32* pBlockOffset,
                                 s32* pLoopCount) {
    if (mStrmInfo.blockSamples == 0) {
        return false;
    }

    int startSample;
    if (mStartOffsetType == START_OFFSET_TYPE_SAMPLE) {
        startSample = mStartOffset;
    } else if (mStartOffsetType == START_OFFSET_TYPE_MILLISEC) {
        startSample =
            (mStartOffset * static_cast<s64>(mStrmInfo.sampleRate)) / 1000;
    }

    *pLoopCount = 0;

    if (startSample >= mStrmInfo.loopEnd) {
        if (mStrmInfo.loopFlag) {
            s32 loopStart = mStrmInfo.loopStart;
            s32 loopEnd = mStrmInfo.loopEnd;
            s32 loopLength = loopEnd - loopStart;

            s32 startOffset2 = startSample - loopEnd;
            *pLoopCount = startOffset2 / loopLength + 1;

            s32 startLoop = startOffset2 / loopLength;
            startSample = loopStart + (startOffset2 - (startLoop * loopLength));
        } else {
            return false;
        }
    }

    *pBlockIndex = startSample / static_cast<s32>(mStrmInfo.blockSamples);

    if (mStrmInfo.format == WaveFile::FORMAT_ADPCM) {
        s32 startBlock = startSample / mStrmInfo.blockSamples;
        *pBlockOffset = startSample - (startBlock * mStrmInfo.blockSamples);
    }

    return true;
}

void StrmPlayer::VoiceCallbackFunc(Voice* pDropVoice,
                                   Voice::VoiceCallbackStatus status,
                                   void* pCallbackArg) {
    StrmTrack* pTrack = static_cast<StrmTrack*>(pCallbackArg);
    ut::AutoInterruptLock lock;

    switch (status) {
    case Voice::CALLBACK_STATUS_FINISH_WAVE:
    case Voice::CALLBACK_STATUS_CANCEL: {
        pDropVoice->Free();
        pTrack->mVoice = NULL;
        break;
    }

    case Voice::CALLBACK_STATUS_DROP_VOICE:
    case Voice::CALLBACK_STATUS_DROP_DSP: {
        pTrack->mVoice = NULL;
        break;
    }

    default: {
        return;
    }
    }
}

void StrmPlayer::SetAdpcmLoopContext(int channels, u16* pPredScale) {
    if (mStrmInfo.format != WaveFile::FORMAT_ADPCM) {
        return;
    }

    for (int i = 0; i < channels && i < STRM_CHANNEL_NUM; i++) {
        mChannels[i].adpcmPredScale = pPredScale[i];
    }

    mValidAdpcmLoop = true;
}

void StrmPlayer::SetTrackVolume(u32 trackBitFlag, f32 volume) {
    ut::AutoInterruptLock lock;

    for (int trackNo = 0; trackNo < mTrackCount && trackBitFlag;
         trackNo++, trackBitFlag >>= 1) {
        if (trackBitFlag & 1) {
            mTracks[trackNo].mVolume = volume;
        }
    }
}

StrmPlayer::StrmTrack* StrmPlayer::GetPlayerTrack(int trackNo) {
    if (trackNo > STRM_TRACK_NUM - 1) {
        return NULL;
    }

    return &mTracks[trackNo];
}

StrmPlayer::StrmHeaderLoadTask::StrmHeaderLoadTask()
    : strmPlayer(NULL), fileStream(NULL), startOffset(0) {}

void StrmPlayer::StrmHeaderLoadTask::Execute() {
    if (!strmPlayer->LoadHeader(fileStream, startOffsetType, startOffset)) {
        strmPlayer->SetTaskErrorFlag();
    }
}

void StrmPlayer::StrmHeaderLoadTask::Cancel() {}

void StrmPlayer::StrmHeaderLoadTask::OnCancel() {
    strmPlayer->SetTaskCancelFlag();

    if (fileStream != NULL && fileStream->CanCancel()) {
        if (fileStream->CanAsync()) {
            fileStream->CancelAsync(NULL, NULL);
        } else {
            fileStream->Cancel();
        }
    }
}

StrmPlayer::StrmDataLoadTask::StrmDataLoadTask()
    : strmPlayer(NULL),
      fileStream(NULL),
      size(0),
      offset(0),
      blockSize(0),
      bufferBlockIndex(-1),
      needUpdateAdpcmLoop(false) {}

void StrmPlayer::StrmDataLoadTask::Execute() {
    if (!strmPlayer->LoadStreamData(fileStream, offset, size, blockSize,
                                    bufferBlockIndex, needUpdateAdpcmLoop)) {
        strmPlayer->SetTaskErrorFlag();
    }

    ut::AutoInterruptLock lock;
    strmPlayer->mStrmDataLoadTaskList.Erase(this);
    strmPlayer->mStrmDataLoadTaskPool.Free(this);
}

void StrmPlayer::StrmDataLoadTask::Cancel() {
    ut::AutoInterruptLock lock;
    strmPlayer->mStrmDataLoadTaskList.Erase(this);
    strmPlayer->mStrmDataLoadTaskPool.Free(this);
}

void StrmPlayer::StrmDataLoadTask::OnCancel() {
    strmPlayer->SetTaskCancelFlag();

    if (fileStream != NULL && fileStream->CanCancel()) {
        if (fileStream->CanAsync()) {
            fileStream->CancelAsync(NULL, NULL);
        } else {
            fileStream->Cancel();
        }
    }
}

} // namespace detail
} // namespace snd
} // namespace nw4r
