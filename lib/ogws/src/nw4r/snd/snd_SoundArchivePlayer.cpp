#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {

SoundArchivePlayer::SoundArchivePlayer()
    : mSoundArchive(NULL),
      mGroupTable(NULL),
      mFileManager(NULL),
      mSeqCallback(*this),
      mWsdCallback(*this),
      mSoundPlayerCount(0),
      mSoundPlayers(NULL),
      mMmlSeqTrackAllocator(&mMmlParser),
      mSetupBufferAddress(NULL),
      mSetupBufferSize(0) {

    detail::DisposeCallbackManager::GetInstance().RegisterDisposeCallback(this);
}

SoundArchivePlayer::~SoundArchivePlayer() {
    detail::DisposeCallbackManager::GetInstance().UnregisterDisposeCallback(
        this);
}

bool SoundArchivePlayer::IsAvailable() const {
    if (mSoundArchive == NULL) {
        return false;
    }

    return mSoundArchive->IsAvailable();
}

u32 SoundArchivePlayer::GetRequiredStrmBufferSize(
    const SoundArchive* pArchive) {
    int strmChannels = 0;

    SoundArchive::SoundArchivePlayerInfo info;
    if (pArchive->ReadSoundArchivePlayerInfo(&info)) {
        strmChannels = info.strmChannelCount;
    }

    // TODO(kiwi) How is this calculated?
    return strmChannels * 0xA000;
}

bool SoundArchivePlayer::SetupStrmBuffer(const SoundArchive* pArchive,
                                         void* pBuffer, u32 bufferSize) {
    if (bufferSize < GetRequiredStrmBufferSize(pArchive)) {
        return false;
    }

    int strmChannels = 0;

    SoundArchive::SoundArchivePlayerInfo info;
    if (pArchive->ReadSoundArchivePlayerInfo(&info)) {
        strmChannels = info.strmChannelCount;
    }

    mStrmBufferPool.Setup(pBuffer, bufferSize, strmChannels);
    return true;
}

bool SoundArchivePlayer::Setup(const SoundArchive* pArchive, void* pMramBuffer,
                               u32 mramBufferSize, void* pStrmBuffer,
                               u32 strmBufferSize) {
    if (!SoundSystem::IsInitializedSoundSystem()) {
        return false;
    }

    if (!SetupMram(pArchive, pMramBuffer, mramBufferSize)) {
        return false;
    }

    if (!SetupStrmBuffer(pArchive, pStrmBuffer, strmBufferSize)) {
        return false;
    }

    mSeqTrackAllocator = &mMmlSeqTrackAllocator;
    return true;
}

void SoundArchivePlayer::Shutdown() {
    mSoundArchive = NULL;
    mGroupTable = NULL;
    mFileManager = NULL;
    mSeqTrackAllocator = NULL;

    for (int i = 0; i < mSoundPlayerCount; i++) {
        mSoundPlayers[i].~SoundPlayer();
    }

    mSoundPlayerCount = 0;
    mSoundPlayers = NULL;

    mSeqSoundInstanceManager.Destroy(mSetupBufferAddress, mSetupBufferSize);
    mStrmSoundInstanceManager.Destroy(mSetupBufferAddress, mSetupBufferSize);
    mWaveSoundInstanceManager.Destroy(mSetupBufferAddress, mSetupBufferSize);
    mMmlSeqTrackAllocator.Destroy(mSetupBufferAddress, mSetupBufferSize);

    mStrmBufferPool.Shutdown();
    mSetupBufferAddress = NULL;
    mSetupBufferSize = 0;
}

u32 SoundArchivePlayer::GetRequiredMemSize(const SoundArchive* pArchive) {
    u32 size = 0;

    u32 playerCount = pArchive->GetPlayerCount();
    size += ut::RoundUp(playerCount * sizeof(SoundPlayer), 4);

    for (u32 i = 0; i < playerCount; i++) {
        SoundArchive::PlayerInfo info;
        if (!pArchive->ReadPlayerInfo(i, &info)) {
            continue;
        }

        for (int j = 0; j < info.playableSoundCount; j++) {
            if (info.heapSize == 0) {
                continue;
            }

            size += ut::RoundUp(info.heapSize + sizeof(detail::PlayerHeap), 4);
        }
    }

    // clang-format off
    size += ut::RoundUp(
        pArchive->GetGroupCount() * sizeof(Group) + (sizeof(GroupTable) - sizeof(Group)), 4);
    // clang-format on

    SoundArchive::SoundArchivePlayerInfo info;
    if (pArchive->ReadSoundArchivePlayerInfo(&info)) {
        // clang-format off
        size += ut::RoundUp(info.seqSoundCount  * sizeof(detail::SeqSound),    4);
        size += ut::RoundUp(info.strmSoundCount * sizeof(detail::StrmSound),   4);
        size += ut::RoundUp(info.waveSoundCount * sizeof(detail::WaveSound),   4);
        size += ut::RoundUp(info.seqTrackCount  * sizeof(detail::MmlSeqTrack), 4);
        // clang-format on
    }

    return size;
}

bool SoundArchivePlayer::SetupMram(const SoundArchive* pArchive, void* pBuffer,
                                   u32 bufferSize) {
    void* pEndPtr = static_cast<u8*>(pBuffer) + bufferSize;
    void* pPtr = pBuffer;

    if (!SetupSoundPlayer(pArchive, &pPtr, pEndPtr)) {
        return false;
    }

    if (!CreateGroupAddressTable(pArchive, &pPtr, pEndPtr)) {
        return false;
    }

    SoundArchive::SoundArchivePlayerInfo info;
    if (pArchive->ReadSoundArchivePlayerInfo(&info)) {
        if (!SetupSeqSound(pArchive, info.seqSoundCount, &pPtr, pEndPtr)) {
            return false;
        }

        if (!SetupStrmSound(pArchive, info.strmSoundCount, &pPtr, pEndPtr)) {
            return false;
        }

        if (!SetupWaveSound(pArchive, info.waveSoundCount, &pPtr, pEndPtr)) {
            return false;
        }

        if (!SetupSeqTrack(pArchive, info.seqTrackCount, &pPtr, pEndPtr)) {
            return false;
        }
    }

    mSoundArchive = pArchive;
    mSetupBufferAddress = pBuffer;
    mSetupBufferSize = bufferSize;

    return true;
}

detail::PlayerHeap* SoundArchivePlayer::CreatePlayerHeap(void* pBuffer,
                                                         u32 bufferSize) {
    detail::PlayerHeap* pHeap = new (pBuffer) detail::PlayerHeap();

    pBuffer = ut::AddOffsetToPtr(pBuffer, sizeof(detail::PlayerHeap));

    if (!pHeap->Create(pBuffer, bufferSize)) {
        return NULL;
    }

    return pHeap;
}

bool SoundArchivePlayer::SetupSoundPlayer(const SoundArchive* pArchive,
                                          void** ppBuffer, void* pEnd) {
    u32 playerCount = pArchive->GetPlayerCount();
    u32 requireSize = playerCount * sizeof(SoundPlayer);

    void* pPlayerEnd =
        ut::RoundUp(ut::AddOffsetToPtr(*ppBuffer, requireSize), 4);

    if (ut::ComparePtr(pPlayerEnd, pEnd) > 0) {
        return false;
    }

    void* pPlayerBuffer = *ppBuffer;
    *ppBuffer = pPlayerEnd;

    mSoundPlayers = static_cast<SoundPlayer*>(pPlayerBuffer);
    mSoundPlayerCount = playerCount;

    u8* pPtr = static_cast<u8*>(pPlayerBuffer);

    for (u32 i = 0; i < playerCount; i++, pPtr += sizeof(SoundPlayer)) {
        SoundPlayer* pPlayer = new (pPtr) SoundPlayer();

        SoundArchive::PlayerInfo info;
        if (!pArchive->ReadPlayerInfo(i, &info)) {
            continue;
        }

        pPlayer->SetPlayableSoundCount(info.playableSoundCount);

        if (info.heapSize == 0) {
            continue;
        }

        for (int j = 0; j < info.playableSoundCount; j++) {
            u32 requireSize = sizeof(detail::PlayerHeap) + info.heapSize;

            void* pHeapEnd =
                ut::RoundUp(ut::AddOffsetToPtr(*ppBuffer, requireSize), 4);

            if (ut::ComparePtr(pHeapEnd, pEnd) > 0) {
                return false;
            }

            void* pHeapBuffer = *ppBuffer;
            *ppBuffer = pHeapEnd;

            detail::PlayerHeap* pHeap =
                CreatePlayerHeap(pHeapBuffer, info.heapSize);

            if (pHeap == NULL) {
                return false;
            }

            pPlayer->detail_AppendPlayerHeap(pHeap);
        }

        pPlayer->detail_SetPlayableSoundLimit(info.playableSoundCount);
    }

    return true;
}

bool SoundArchivePlayer::CreateGroupAddressTable(const SoundArchive* pArchive,
                                                 void** ppBuffer, void* pEnd) {
    // clang-format off
    u32 requireSize = 
        pArchive->GetGroupCount() * sizeof(Group) + (sizeof(GroupTable) - sizeof(Group));
    // clang-format on

    void* pTableEnd =
        ut::RoundUp(ut::AddOffsetToPtr(*ppBuffer, requireSize), 4);

    if (ut::ComparePtr(pTableEnd, pEnd) > 0) {
        return false;
    }

    mGroupTable = static_cast<GroupTable*>(*ppBuffer);
    *ppBuffer = pTableEnd;

    mGroupTable->count = pArchive->GetGroupCount();

    for (int i = 0; i < mGroupTable->count; i++) {
        mGroupTable->items[i].address = NULL;
        mGroupTable->items[i].waveDataAddress = NULL;
    }

    return true;
}

bool SoundArchivePlayer::SetupSeqSound(const SoundArchive* pArchive, int sounds,
                                       void** ppBuffer, void* pEnd) {
#pragma unused(pArchive)

    u32 requireSize = sounds * sizeof(detail::SeqSound);

    void* pSoundEnd =
        ut::RoundUp(ut::AddOffsetToPtr(*ppBuffer, requireSize), 4);

    if (ut::ComparePtr(pSoundEnd, pEnd) > 0) {
        return false;
    }

    mSeqSoundInstanceManager.Create(*ppBuffer, requireSize);
    *ppBuffer = pSoundEnd;

    return true;
}

bool SoundArchivePlayer::SetupWaveSound(const SoundArchive* pArchive,
                                        int sounds, void** ppBuffer,
                                        void* pEnd) {
#pragma unused(pArchive)

    u32 requireSize = sounds * sizeof(detail::WaveSound);

    void* pSoundEnd =
        ut::RoundUp(ut::AddOffsetToPtr(*ppBuffer, requireSize), 4);

    if (ut::ComparePtr(pSoundEnd, pEnd) > 0) {
        return false;
    }

    mWaveSoundInstanceManager.Create(*ppBuffer, requireSize);
    *ppBuffer = pSoundEnd;

    return true;
}

bool SoundArchivePlayer::SetupStrmSound(const SoundArchive* pArchive,
                                        int sounds, void** ppBuffer,
                                        void* pEnd) {
#pragma unused(pArchive)

    u32 requireSize = sounds * sizeof(detail::StrmSound);

    void* pSoundEnd =
        ut::RoundUp(ut::AddOffsetToPtr(*ppBuffer, requireSize), 4);

    if (ut::ComparePtr(pSoundEnd, pEnd) > 0) {
        return false;
    }

    mStrmSoundInstanceManager.Create(*ppBuffer, requireSize);
    *ppBuffer = pSoundEnd;

    return true;
}

bool SoundArchivePlayer::SetupSeqTrack(const SoundArchive* pArchive, int tracks,
                                       void** ppBuffer, void* pEnd) {
#pragma unused(pArchive)

    u32 requireSize = tracks * sizeof(detail::MmlSeqTrack);

    void* pTrackEnd =
        ut::RoundUp(ut::AddOffsetToPtr(*ppBuffer, requireSize), 4);

    if (ut::ComparePtr(pTrackEnd, pEnd) > 0) {
        return false;
    }

    mMmlSeqTrackAllocator.Create(*ppBuffer, requireSize);
    *ppBuffer = pTrackEnd;

    return true;
}

void SoundArchivePlayer::Update() {
    for (u32 i = 0; i < mSoundPlayerCount; i++) {
        GetSoundPlayer(i).Update();
    }

    mSeqSoundInstanceManager.SortPriorityList();
    mStrmSoundInstanceManager.SortPriorityList();
    mWaveSoundInstanceManager.SortPriorityList();
}

const SoundArchive& SoundArchivePlayer::GetSoundArchive() const {
    return *mSoundArchive;
}

SoundPlayer& SoundArchivePlayer::GetSoundPlayer(u32 idx) {
    return mSoundPlayers[idx];
}

const void* SoundArchivePlayer::detail_GetFileAddress(u32 id) const {
    // FE10: the file manager is asked first
    if (mFileManager != NULL) {
        const void* pAddr = mFileManager->GetFileAddress(id);
        if (pAddr != NULL) {
            return pAddr;
        }
    }

    const void* pAddr = mSoundArchive->detail_GetFileAddress(id);
    if (pAddr != NULL) {
        return pAddr;
    }

    SoundArchive::FileInfo file;
    if (!mSoundArchive->detail_ReadFileInfo(id, &file)) {
        return NULL;
    }

    for (unsigned int i = 0; i < file.filePosCount; i++) {
        SoundArchive::FilePos pos;
        if (!mSoundArchive->detail_ReadFilePos(id, i, &pos)) {
            continue;
        }

        const void* pGroup = GetGroupAddress(pos.groupId);
        if (pGroup == NULL) {
            continue;
        }

        SoundArchive::GroupItemInfo item;
        if (mSoundArchive->detail_ReadGroupItemInfo(pos.groupId, pos.index,
                                                    &item)) {
            return static_cast<const u8*>(pGroup) + item.offset;
        }
    }

    return NULL;
}

const void* SoundArchivePlayer::detail_GetFileWaveDataAddress(u32 id) const {
    const void* pAddr = mSoundArchive->detail_GetWaveDataFileAddress(id);
    if (pAddr != NULL) {
        return pAddr;
    }

    if (mFileManager != NULL) {
        const void* pAddr = mFileManager->GetFileWaveDataAddress(id);
        if (pAddr != NULL) {
            return pAddr;
        }
    }

    SoundArchive::FileInfo file;
    if (!mSoundArchive->detail_ReadFileInfo(id, &file)) {
        return NULL;
    }

    for (unsigned int i = 0; i < file.filePosCount; i++) {
        SoundArchive::FilePos pos;
        if (!mSoundArchive->detail_ReadFilePos(id, i, &pos)) {
            continue;
        }

        const void* pGroup = GetGroupWaveDataAddress(pos.groupId);
        if (pGroup == NULL) {
            continue;
        }

        SoundArchive::GroupItemInfo item;
        if (mSoundArchive->detail_ReadGroupItemInfo(pos.groupId, pos.index,
                                                    &item)) {
            return static_cast<const u8*>(pGroup) + item.waveDataOffset;
        }
    }

    return NULL;
}

const void* SoundArchivePlayer::GetGroupAddress(u32 id) const {
    if (mGroupTable == NULL) {
        return NULL;
    }

    if (id >= mGroupTable->count) {
        return NULL;
    }

    return mGroupTable->items[id].address;
}

void SoundArchivePlayer::SetGroupAddress(u32 id, const void* pAddr) {
    if (mGroupTable == NULL) {
        return;
    }

    // @bug Index not validated
    mGroupTable->items[id].address = pAddr;
}

const void* SoundArchivePlayer::GetGroupWaveDataAddress(u32 id) const {
    if (mGroupTable == NULL) {
        return NULL;
    }

    if (id >= mGroupTable->count) {
        return NULL;
    }

    return mGroupTable->items[id].waveDataAddress;
}

void SoundArchivePlayer::SetGroupWaveDataAddress(u32 id, const void* pAddr) {
    if (mGroupTable == NULL) {
        return;
    }

    // @bug Index not validated
    mGroupTable->items[id].waveDataAddress = pAddr;
}

SoundStartable::StartResult
SoundArchivePlayer::detail_SetupSound(SoundHandle* pHandle, u32 id, bool hold,
                                      const StartInfo* pStartInfo) {
    return detail_SetupSoundImpl(pHandle, id, NULL, NULL, hold, pStartInfo);
}

SoundStartable::StartResult SoundArchivePlayer::detail_SetupSoundImpl(
    SoundHandle* pHandle, u32 id, detail::BasicSound::AmbientArgInfo* pArgInfo,
    SoundActor* pActor, bool hold, const StartInfo* pStartInfo) {

    if (!IsAvailable()) {
        return START_ERR_NOT_AVAILABLE;
    }

    if (pHandle->IsAttachedSound()) {
        pHandle->DetachSound();
    }

    SoundArchive::SoundInfo sndInfo;
    if (!mSoundArchive->ReadSoundInfo(id, &sndInfo)) {
        return START_ERR_INVALID_SOUNDID;
    }

    StartInfo::StartOffsetType startType = StartInfo::START_OFFSET_TYPE_MILLISEC;
    int startOffset = 0;
    int playerPriority = sndInfo.playerPriority;
    int actorPlayerId = sndInfo.actorPlayerId;

    if (pStartInfo != NULL) {
        if (pStartInfo->enableFlag & StartInfo::ENABLE_START_OFFSET) {
            startType = pStartInfo->startOffsetType;
            startOffset = pStartInfo->startOffset;
        }

        if (pStartInfo->enableFlag & StartInfo::ENABLE_PLAYER_PRIORITY) {
            playerPriority = pStartInfo->playerPriority;
        }

        if (pStartInfo->enableFlag & StartInfo::ENABLE_ACTOR_PLAYER_ID) {
            actorPlayerId = pStartInfo->actorPlayerId;
        }
    }

    int priority = playerPriority;
    if (hold) {
        priority--;
    }

    int ambientPriority = 0;
    if (pArgInfo != NULL) {
        ambientPriority =
            detail::BasicSound::GetAmbientPriority(*pArgInfo, id);
    }

    int allocPriority = ut::Clamp(priority + ambientPriority, 0,
                                  detail::BasicSound::PRIORITY_MAX);

    detail::ExternalSoundPlayer* pExtPlayer = NULL;
    if (pActor != NULL) {
        pExtPlayer = pActor->detail_GetActorPlayer(actorPlayerId);
        if (pExtPlayer == NULL) {
            return START_ERR_INVALID_PARAMETER;
        }
    }

    detail::SoundThread::AutoLock lock;

    SoundPlayer& rPlayer = GetSoundPlayer(sndInfo.playerId);
    if (!rPlayer.detail_CanPlaySound(allocPriority)) {
        return START_ERR_LOW_PRIORITY;
    }

    if (pExtPlayer != NULL) {
        if (!pExtPlayer->detail_CanPlaySound(allocPriority)) {
            return START_ERR_LOW_PRIORITY;
        }
    }

    detail::BasicSound* pSound = NULL;
    detail::SeqSound* pSeqSound = NULL;
    detail::StrmSound* pStrmSound = NULL;
    detail::WaveSound* pWaveSound = NULL;

    switch (mSoundArchive->GetSoundType(id)) {
    case SOUND_TYPE_SEQ: {
        pSeqSound = AllocSound(&mSeqSoundInstanceManager, id, priority,
                               ambientPriority, pArgInfo);
        if (pSeqSound == NULL) {
            return START_ERR_LOW_PRIORITY;
        }

        pSound = pSeqSound;
        break;
    }

    case SOUND_TYPE_STRM: {
        pStrmSound = AllocSound(&mStrmSoundInstanceManager, id, priority,
                                ambientPriority, pArgInfo);
        if (pStrmSound == NULL) {
            return START_ERR_LOW_PRIORITY;
        }

        pSound = pStrmSound;
        break;
    }

    case SOUND_TYPE_WAVE: {
        pWaveSound = AllocSound(&mWaveSoundInstanceManager, id, priority,
                                ambientPriority, pArgInfo);
        if (pWaveSound == NULL) {
            return START_ERR_LOW_PRIORITY;
        }

        pSound = pWaveSound;
        break;
    }

    default: {
        return START_ERR_INVALID_SOUNDID;
    }
    }

    if (!rPlayer.detail_AppendSound(pSound)) {
        pSound->Shutdown();
        return START_ERR_UNKNOWN;
    }

    switch (mSoundArchive->GetSoundType(id)) {
    case SOUND_TYPE_SEQ: {
        rPlayer.detail_AllocPlayerHeap(pSeqSound);

        SoundArchive::SeqSoundInfo info;
        if (!mSoundArchive->detail_ReadSeqSoundInfo(id, &info)) {
            pSeqSound->Shutdown();
            return START_ERR_INVALID_SOUNDID;
        }

        StartResult result =
            PrepareSeqImpl(pSeqSound, &sndInfo, &info, startType, startOffset);

        if (result == START_SUCCESS) {
            break;
        }

        pSeqSound->Shutdown();
        return result;
    }

    case SOUND_TYPE_STRM: {
        SoundArchive::StrmSoundInfo info;
        if (!mSoundArchive->detail_ReadStrmSoundInfo(id, &info)) {
            pStrmSound->Shutdown();
            return START_ERR_INVALID_SOUNDID;
        }

        StartResult result = PrepareStrmImpl(pStrmSound, &sndInfo, &info,
                                             startType, startOffset);

        if (result == START_SUCCESS) {
            break;
        }

        pStrmSound->Shutdown();
        return result;
    }

    case SOUND_TYPE_WAVE: {
        SoundArchive::WaveSoundInfo info;
        if (!mSoundArchive->detail_ReadWaveSoundInfo(id, &info)) {
            pWaveSound->Shutdown();
            return START_ERR_INVALID_SOUNDID;
        }

        StartResult result = PrepareWaveSoundImpl(pWaveSound, &sndInfo, &info,
                                                  startType, startOffset);

        if (result == START_SUCCESS) {
            break;
        }

        pWaveSound->Shutdown();
        return result;
    }

    default: {
        pSound->Shutdown();
        return START_ERR_INVALID_SOUNDID;
    }
    }

    if (pExtPlayer != NULL) {
        if (!pExtPlayer->AppendSound(pSound)) {
            pSound->Shutdown();
            return START_ERR_UNKNOWN;
        }
    }

    if (pActor != NULL) {
        pSound->AttachSoundActor(pActor);
    }

    if (hold) {
        pSound->SetPlayerPriority(playerPriority);
    }

    pHandle->detail_AttachSound(pSound);
    return START_SUCCESS;
}

SoundStartable::StartResult SoundArchivePlayer::PrepareSeqImpl(
    detail::SeqSound* pSound, const SoundArchive::SoundInfo* pSndInfo,
    const SoundArchive::SeqSoundInfo* pSeqInfo,
    SoundStartable::StartInfo::StartOffsetType startType, int startOffset) {

    const void* pSeqBin = detail_GetFileAddress(pSndInfo->fileId);
    ut::FileStream* pFileStream = NULL;

    if (pSeqBin == NULL) {
        detail::PlayerHeap* pHeap = pSound->GetPlayerHeap();
        if (pHeap == NULL) {
            return START_ERR_NOT_DATA_LOADED;
        }

        void* pStreamBuffer = pSound->GetFileStreamBuffer();
        s32 streamBufferSize = pSound->GetFileStreamBufferSize();

        pFileStream = mSoundArchive->detail_OpenFileStream(
            pSndInfo->fileId, pStreamBuffer, streamBufferSize);

        if (pFileStream == NULL) {
            return START_ERR_CANNOT_OPEN_FILE;
        }

        if (pHeap->GetFreeSize() < pFileStream->GetSize()) {
            pFileStream->Close();
            return START_ERR_NOT_ENOUGH_PLAYER_HEAP;
        }
    }

    detail::SeqPlayer::SetupResult result =
        pSound->Setup(mSeqTrackAllocator, pSeqInfo->allocTrack, &mSeqCallback);

    while (result != detail::SeqPlayer::SETUP_SUCCESS) {
        if (result == detail::SeqPlayer::SETUP_ERR_CANNOT_ALLOCATE_TRACK) {
            if (mSeqSoundInstanceManager.GetActiveCount() == 1) {
                if (pFileStream != NULL) {
                    pFileStream->Close();
                }

                return START_ERR_NOT_ENOUGH_INSTANCE;
            }

            detail::SeqSound* pDropSound =
                mSeqSoundInstanceManager.GetLowestPrioritySound();

            if (pSound == pDropSound) {
                if (pFileStream != NULL) {
                    pFileStream->Close();
                }

                return START_ERR_LOW_PRIORITY;
            }

            pDropSound->Stop(0);
            result = pSound->Setup(mSeqTrackAllocator, pSeqInfo->allocTrack,
                                   &mSeqCallback);
        } else {
            return START_ERR_UNKNOWN;
        }
    }

    pSound->SetInitialVolume(pSndInfo->volume / 127.0f);
    pSound->SetRemoteFilter(pSndInfo->remoteFilter);
    pSound->SetPanMode(pSndInfo->panMode);
    pSound->SetPanCurve(pSndInfo->panCurve);
    pSound->SetChannelPriority(pSeqInfo->channelPriority);
    pSound->SetReleasePriorityFix(pSeqInfo->releasePriorityFixFlag);

    detail::SeqPlayer::OffsetType seqOffsetType;

    switch (startType) {
    case StartInfo::START_OFFSET_TYPE_MILLISEC: {
        seqOffsetType = detail::SeqPlayer::OFFSET_TYPE_MILLISEC;
        break;
    }

    case StartInfo::START_OFFSET_TYPE_TICK: {
        seqOffsetType = detail::SeqPlayer::OFFSET_TYPE_TICK;
        break;
    }

    case StartInfo::START_OFFSET_TYPE_SAMPLE: {
        seqOffsetType = detail::SeqPlayer::OFFSET_TYPE_TICK;
        startOffset = 0;
        break;
    }

    default: {
        seqOffsetType = detail::SeqPlayer::OFFSET_TYPE_TICK;
        startOffset = 0;
        break;
    }
    }

    if (pSeqBin != NULL) {
        detail::SeqFileReader reader(pSeqBin);
        pSound->Prepare(reader.GetBaseAddress(), pSeqInfo->dataOffset,
                        seqOffsetType, startOffset);
    } else {
        pSound->Prepare(pFileStream, pSeqInfo->dataOffset, seqOffsetType,
                        startOffset);
    }

    return START_SUCCESS;
}

SoundStartable::StartResult SoundArchivePlayer::PrepareStrmImpl(
    detail::StrmSound* pSound, const SoundArchive::SoundInfo* pSndInfo,
    const SoundArchive::StrmSoundInfo* pStrmInfo,
    SoundStartable::StartInfo::StartOffsetType startType, int startOffset) {

    detail::StrmPlayer::SetupResult result =
        pSound->Setup(&mStrmBufferPool, pStrmInfo->allocChannelCount,
                      pStrmInfo->allocTrackFlag);

    while (result != detail::StrmPlayer::SETUP_SUCCESS) {
        if (result == detail::StrmPlayer::SETUP_ERR_CANNOT_ALLOCATE_BUFFER) {
            if (mStrmSoundInstanceManager.GetActiveCount() == 1) {
                return START_ERR_NOT_ENOUGH_INSTANCE;
            }

            detail::StrmSound* pDropSound =
                mStrmSoundInstanceManager.GetLowestPrioritySound();

            if (pSound == pDropSound) {
                return START_ERR_LOW_PRIORITY;
            }

            pDropSound->Stop(0);
            result = pSound->Setup(&mStrmBufferPool,
                                   pStrmInfo->allocChannelCount,
                                   pStrmInfo->allocTrackFlag);
        } else {
            return START_ERR_UNKNOWN;
        }
    }

    detail::StrmPlayer::StartOffsetType strmOffsetType;

    switch (startType) {
    case StartInfo::START_OFFSET_TYPE_MILLISEC: {
        strmOffsetType = detail::StrmPlayer::START_OFFSET_TYPE_MILLISEC;
        break;
    }

    case StartInfo::START_OFFSET_TYPE_TICK: {
        strmOffsetType = detail::StrmPlayer::START_OFFSET_TYPE_SAMPLE;
        startOffset = 0;
        break;
    }

    case StartInfo::START_OFFSET_TYPE_SAMPLE: {
        strmOffsetType = detail::StrmPlayer::START_OFFSET_TYPE_SAMPLE;
        break;
    }

    default: {
        strmOffsetType = detail::StrmPlayer::START_OFFSET_TYPE_SAMPLE;
        startOffset = 0;
        break;
    }
    }

    void* pStreamBuffer = pSound->GetFileStreamBuffer();
    s32 streamBufferSize = pSound->GetFileStreamBufferSize();

    ut::FileStream* pFileStream = mSoundArchive->detail_OpenFileStream(
        pSndInfo->fileId, pStreamBuffer, streamBufferSize);

    if (pFileStream == NULL) {
        return START_ERR_CANNOT_OPEN_FILE;
    }

    if (!pSound->Prepare(strmOffsetType, startOffset, pFileStream)) {
        return START_ERR_UNKNOWN;
    }

    pSound->SetInitialVolume(pSndInfo->volume / 127.0f);
    pSound->SetRemoteFilter(pSndInfo->remoteFilter);
    pSound->SetPanMode(pSndInfo->panMode);
    pSound->SetPanCurve(pSndInfo->panCurve);

    return START_SUCCESS;
}

SoundStartable::StartResult SoundArchivePlayer::PrepareWaveSoundImpl(
    detail::WaveSound* pSound, const SoundArchive::SoundInfo* pSndInfo,
    const SoundArchive::WaveSoundInfo* pWsdInfo,
    SoundStartable::StartInfo::StartOffsetType startType, int startOffset) {

    const void* pWsdBin = detail_GetFileAddress(pSndInfo->fileId);
    if (pWsdBin == NULL) {
        return START_ERR_NOT_DATA_LOADED;
    }

    detail::WsdPlayer::StartOffsetType wsdOffsetType;

    switch (startType) {
    case StartInfo::START_OFFSET_TYPE_MILLISEC: {
        wsdOffsetType = detail::WsdPlayer::START_OFFSET_TYPE_MILLISEC;
        break;
    }

    case StartInfo::START_OFFSET_TYPE_TICK: {
        wsdOffsetType = detail::WsdPlayer::START_OFFSET_TYPE_SAMPLE;
        startOffset = 0;
        break;
    }

    case StartInfo::START_OFFSET_TYPE_SAMPLE: {
        wsdOffsetType = detail::WsdPlayer::START_OFFSET_TYPE_SAMPLE;
        break;
    }

    default: {
        wsdOffsetType = detail::WsdPlayer::START_OFFSET_TYPE_SAMPLE;
        startOffset = 0;
        break;
    }
    }

    if (!pSound->Prepare(pWsdBin, pWsdInfo->subNo, wsdOffsetType, startOffset,
                         &mWsdCallback, pSndInfo->fileId)) {
        return START_ERR_UNKNOWN;
    }

    pSound->SetInitialVolume(pSndInfo->volume / 127.0f);
    pSound->SetRemoteFilter(pSndInfo->remoteFilter);
    pSound->SetPanMode(pSndInfo->panMode);
    pSound->SetPanCurve(pSndInfo->panCurve);
    pSound->SetChannelPriority(pWsdInfo->channelPriority);
    pSound->SetReleasePriorityFix(pWsdInfo->releasePriorityFixFlag);

    return START_SUCCESS;
}

bool SoundArchivePlayer::LoadGroup(u32 id, SoundMemoryAllocatable* pAllocatable,
                                   u32 blockSize) {
    if (!IsAvailable()) {
        return false;
    }

    if (id >= mSoundArchive->GetGroupCount()) {
        return false;
    }

    if (GetGroupAddress(id) != NULL) {
        return true;
    }

    if (pAllocatable == NULL) {
        return false;
    }

    detail::SoundArchiveLoader loader(*mSoundArchive);

    void* pWaveBuffer;
    const void* pGroup =
        loader.LoadGroup(id, pAllocatable, &pWaveBuffer, blockSize);

    if (pGroup == NULL) {
        return NULL;
    }

    SetGroupAddress(id, pGroup);
    SetGroupWaveDataAddress(id, pWaveBuffer);

    return true;
}

bool SoundArchivePlayer::LoadGroup(const char* pLabel,
                                   SoundMemoryAllocatable* pAllocatable,
                                   u32 blockSize) {
    u32 id = mSoundArchive->ConvertLabelStringToGroupId(pLabel);
    if (id == SoundArchive::INVALID_ID) {
        return false;
    }

    return LoadGroup(id, pAllocatable, blockSize);
}

void SoundArchivePlayer::InvalidateData(const void* pStart, const void* pEnd) {
    if (mGroupTable == NULL) {
        return;
    }

    for (int i = 0; i < mGroupTable->count; i++) {
        const void* pAddr = mGroupTable->items[i].address;

        if (pStart <= pAddr && pAddr <= pEnd) {
            mGroupTable->items[i].address = NULL;
        }
    }
}

void SoundArchivePlayer::InvalidateWaveData(const void* pStart,
                                            const void* pEnd) {
    if (mGroupTable == NULL) {
        return;
    }

    for (int i = 0; i < mGroupTable->count; i++) {
        const void* pAddr = mGroupTable->items[i].waveDataAddress;

        if (pStart <= pAddr && pAddr <= pEnd) {
            mGroupTable->items[i].waveDataAddress = NULL;
        }
    }
}

detail::Channel*
SoundArchivePlayer::SeqNoteOnCallback::NoteOn(detail::SeqPlayer* pSeqPlayer,
                                              int bankNo,
                                              const detail::NoteOnInfo& rInfo) {
#pragma unused(bankNo)

    if (!mSoundArchivePlayer.IsAvailable()) {
        return NULL;
    }

    const SoundArchive& rArchive = mSoundArchivePlayer.GetSoundArchive();
    u32 soundId = pSeqPlayer->GetId();

    SoundArchive::SeqSoundInfo seqInfo;
    if (!rArchive.detail_ReadSeqSoundInfo(soundId, &seqInfo)) {
        return NULL;
    }

    SoundArchive::BankInfo bankInfo;
    if (!rArchive.detail_ReadBankInfo(seqInfo.bankId, &bankInfo)) {
        return NULL;
    }

    const void* pBankBin =
        mSoundArchivePlayer.detail_GetFileAddress(bankInfo.fileId);

    if (pBankBin == NULL) {
        return NULL;
    }

    detail::Bank bank(pBankBin);

    const void* pWaveData =
        mSoundArchivePlayer.detail_GetFileWaveDataAddress(bankInfo.fileId);

    if (pWaveData == NULL) {
        return NULL;
    }

    bank.SetWaveDataAddress(pWaveData);
    return bank.NoteOn(rInfo);
}

bool SoundArchivePlayer::WsdCallback::GetWaveSoundData(
    detail::WaveSoundInfo* pSoundInfo, detail::WaveSoundNoteInfo* pNoteInfo,
    detail::WaveData* pWaveData, const void* pWsdData, int index, int noteIndex,
    u32 callbackArg) const {

    u32 fileId = callbackArg;

    if (!mSoundArchivePlayer.IsAvailable()) {
        return false;
    }

    const void* pWaveAddr =
        mSoundArchivePlayer.detail_GetFileWaveDataAddress(fileId);

    if (pWaveAddr == NULL) {
        return false;
    }

    detail::WsdFileReader reader(pWsdData);

    if (!reader.ReadWaveSoundInfo(pSoundInfo, index)) {
        return false;
    }

    if (!reader.ReadWaveSoundNoteInfo(pNoteInfo, index, noteIndex)) {
        return false;
    }

    if (!reader.ReadWaveParam(pNoteInfo->waveIndex, pWaveData, pWaveAddr)) {
        return false;
    }

    return true;
}

} // namespace snd
} // namespace nw4r
