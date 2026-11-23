#include <nw4r/snd.h>

#include <climits>
#include <cstring>

namespace nw4r {
namespace snd {
namespace detail {

NW4R_UT_RTTI_DEF_BASE(BasicSound);

BasicSound::BasicSound(int priority, int ambientPriority)
    : mHeap(NULL),
      mGeneralHandle(NULL),
      mTempGeneralHandle(NULL),
      mSoundPlayer(NULL),
      mSoundActor(NULL),
      mExtSoundPlayer(NULL),
      mId(INVALID_ID) {
    mAmbientInfo.paramUpdateCallback = NULL;
    mAmbientInfo.argUpdateCallback = NULL;
    mAmbientInfo.argAllocaterCallback = NULL;
    mAmbientInfo.arg = NULL;
    mAmbientInfo.argSize = 0;

    mVoiceOutCount = 1;
    mPriority = priority;
    mAmbientParam.priority = ambientPriority;
}

void BasicSound::InitParam() {
    mPauseFlag = false;
    mPauseFadeFlag = false;
    mStartFlag = false;
    mStartedFlag = false;
    mAutoStopFlag = false;
    mFadeOutFlag = false;

    mAutoStopCounter = 0;
    mUpdateCounter = 0;

    mFadeVolume.InitValue(0.0f);
    mPauseFadeVolume.InitValue(1.0f);
    mFadeVolume.SetTarget(1.0f, 1);

    mInitVolume = 1.0f;
    mExtPitch = 1.0f;
    mExtPan = 0.0f;
    mExtSurroundPan = 0.0f;
    mExtMoveVolume.InitValue(1.0f);

    mLpfFreq = 0.0f;
    mOutputLineFlag = OUTPUT_LINE_MAIN;
    mOutputLineFlagEnable = false;

    mMainOutVolume = 1.0f;
    for (int i = 0; i < AUX_BUS_NUM; i++) {
        mFxSend[i] = 0.0f;
    }
    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        mRemoteOutVolume[i] = 1.0f;
    }

    mAmbientParam.volume = 1.0f;
    mAmbientParam.pitch = 1.0f;
    mAmbientParam.pan = 0.0f;
    mAmbientParam.surroundPan = 0.0f;
    mAmbientParam.fxSend = 0.0f;
    mAmbientParam.lpf = 0.0f;
    mAmbientParam.priority = 0;
}

void BasicSound::StartPrepared() {
    if (!mStartedFlag) {
        mStartFlag = true;
    }
}

void BasicSound::Stop(int frames) {
    BasicPlayer& rPlayer = GetBasicPlayer();

    if (frames == 0 || !rPlayer.IsActive() || !rPlayer.IsStarted() ||
        rPlayer.IsPause()) {
        Shutdown();
        return;
    }

    int t = frames * mFadeVolume.GetValue();
    mFadeVolume.SetTarget(0.0f, t);

    SetPlayerPriority(0);
    mAutoStopFlag = false;
    mPauseFlag = false;
    mPauseFadeFlag = false;
    mFadeOutFlag = true;
}

void BasicSound::Pause(bool flag, int frames) {
    BasicPlayer& rPlayer = GetBasicPlayer();

    if (flag) {
        int t = frames * mPauseFadeVolume.GetValue();
        mPauseFadeFlag = true;

        if (t <= 0) {
            t = 1;
        }

        mPauseFadeVolume.SetTarget(0.0f, t);
    } else {
        if (mPauseFlag != flag) {
            rPlayer.Pause(false);
        }

        int t = frames * (1.0f - mPauseFadeVolume.GetValue());
        mPauseFadeFlag = true;

        if (t <= 0) {
            t = 1;
        }

        mPauseFadeVolume.SetTarget(1.0f, t);
    }

    mPauseFlag = flag;
}


void BasicSound::FadeIn(int frames) {
    if (mFadeOutFlag) {
        return;
    }

    int t = frames * (1.0f - mFadeVolume.GetValue());
    mFadeVolume.SetTarget(1.0f, t);
}

bool BasicSound::IsPause() const {
    return mPauseFlag;
}

void BasicSound::Update() {
    BasicPlayer& rPlayer = GetBasicPlayer();

    if (mAutoStopFlag && rPlayer.IsActive()) {
        if (mAutoStopCounter == 0) {
            Stop(0);
            return;
        }

        mAutoStopCounter--;
    }

    bool startPlayer = false;
    if (!mStartedFlag) {
        if (!mStartFlag) {
            return;
        }

        if (!IsPrepared()) {
            return;
        }

        startPlayer = true;
    }

    if (rPlayer.IsStarted() && mUpdateCounter < ULONG_MAX) {
        mUpdateCounter++;
    }

    if (!rPlayer.IsActive()) {
        Shutdown();
        return;
    }

    if (rPlayer.IsPause()) {
        return;
    }

    if (mPauseFadeFlag) {
        mPauseFadeVolume.Update();
    } else {
        UpdateMoveValue();
    }

    if (mAmbientInfo.argUpdateCallback != NULL) {
        mAmbientInfo.argUpdateCallback->detail_Update(mAmbientInfo.arg, this);
    }

    if (mAmbientInfo.paramUpdateCallback != NULL) {
        SoundAmbientParam param;

        mAmbientInfo.paramUpdateCallback->detail_Update(mAmbientInfo.arg, mId,
                                                   mVoiceOutCount, &param);

        mAmbientParam.volume = param.volume;
        mAmbientParam.pitch = param.pitch;
        mAmbientParam.pan = param.pan;
        mAmbientParam.surroundPan = param.surroundPan;
        mAmbientParam.fxSend = param.fxSend;
        mAmbientParam.lpf = param.lpf;
        mAmbientParam.priority = param.priority;

        for (int i = 0; i < mVoiceOutCount; i++) {
            rPlayer.SetVoiceOutParam(i, param.voiceOutParam[i]);
        }
    }

    if (mSoundActor != NULL) {
        // TODO(FE10): SoundActor::detail_GetActorParam (actor param at 0x48)
        mActorParam = *static_cast<const ActorParam*>(
            ut::AddOffsetToPtr(mSoundActor, 0x48));
    }

    UpdateParam();

    if (mFadeOutFlag && mFadeVolume.IsFinished()) {
        mFadeOutFlag = false;
        Shutdown();
        return;
    }

    if (mPauseFadeFlag && mPauseFadeVolume.IsFinished()) {
        mPauseFadeFlag = false;

        if (mPauseFlag) {
            rPlayer.Pause(true);
        }
    }

    if (startPlayer) {
        if (rPlayer.Start()) {
            mStartedFlag = true;
            mStartFlag = false;
        } else {
            Shutdown();
        }
    }
}

void BasicSound::UpdateMoveValue() {
    mFadeVolume.Update();
    mExtMoveVolume.Update();
}

void BasicSound::UpdateParam() {
    f32 volume;
    f32 pan;
    f32 surroundPan;
    f32 pitch;
    f32 mainOutVol;
    f32 lpf;

    volume = 1.0f;
    volume *= mInitVolume;
    volume *= mSoundPlayer->GetVolume();
    volume *= mExtMoveVolume.GetValue();
    volume *= mFadeVolume.GetValue();
    volume *= mPauseFadeVolume.GetValue();
    volume *= mAmbientParam.volume;
    volume *= mActorParam.volume;

    pan = 0.0f;
    pan += mExtPan;
    pan += mAmbientParam.pan;
    pan += mActorParam.pan;

    surroundPan = 0.0f;
    surroundPan += mExtSurroundPan;
    surroundPan += mAmbientParam.surroundPan;

    pitch = 1.0f;
    pitch *= mExtPitch;
    pitch *= mAmbientParam.pitch;
    pitch *= mActorParam.pitch;

    lpf = mLpfFreq;
    lpf += mAmbientParam.lpf;

    mainOutVol = 1.0f;
    mainOutVol *= mSoundPlayer->detail_GetMainOutVolume();
    mainOutVol *= mMainOutVolume;

    int outputLine = OUTPUT_LINE_MAIN;
    if (mOutputLineFlagEnable) {
        outputLine = mOutputLineFlag;
    } else if (mSoundPlayer->detail_IsEnabledOutputLine()) {
        outputLine = mSoundPlayer->detail_GetOutputLine();
    }

    f32 fxSend[AUX_BUS_NUM];
    for (int i = 0; i < AUX_BUS_NUM; i++) {
        fxSend[i] = mFxSend[i];
    }

    fxSend[AUX_A] += mAmbientParam.fxSend;

    f32 remoteOutVol[WPAD_MAX_CONTROLLERS];
    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        remoteOutVol[i] = 1.0f;
        remoteOutVol[i] *= mSoundPlayer->detail_GetRemoteOutVolume(i);
        remoteOutVol[i] *= mRemoteOutVolume[i];
    }

    BasicPlayer& rPlayer = GetBasicPlayer();
    rPlayer.SetVolume(volume);
    rPlayer.SetPan(pan);
    rPlayer.SetSurroundPan(surroundPan);
    rPlayer.SetPitch(pitch);
    rPlayer.SetLpfFreq(lpf);
    rPlayer.SetOutputLine(outputLine);
    rPlayer.SetMainOutVolume(mainOutVol);

    for (int i = 0; i < AUX_BUS_NUM; i++) {
        rPlayer.SetFxSend(static_cast<AuxBus>(i), fxSend[i]);
    }

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        rPlayer.SetRemoteOutVolume(i, remoteOutVol[i]);
    }
}

void BasicSound::Shutdown() {
    BasicPlayer& rPlayer = GetBasicPlayer();

    if (rPlayer.IsActive()) {
        if (mFadeOutFlag) {
            rPlayer.SetVolume(0.0f);
        }

        rPlayer.Stop();
    }

    SetId(INVALID_ID);

    if (IsAttachedGeneralHandle()) {
        DetachGeneralHandle();
    }

    if (IsAttachedTempGeneralHandle()) {
        DetachTempGeneralHandle();
    }

    if (IsAttachedTempSpecialHandle()) {
        DetachTempSpecialHandle();
    }

    if (mHeap != NULL) {
        mSoundPlayer->detail_FreePlayerHeap(this);
    }

    if (mSoundPlayer != NULL) {
        mSoundPlayer->detail_RemoveSoundList(this);
    }

    if (mExtSoundPlayer != NULL) {
        mExtSoundPlayer->RemoveSoundList(this);
    }

    if (mAmbientInfo.argAllocaterCallback != NULL) {
        mAmbientInfo.argAllocaterCallback->detail_FreeAmbientArg(mAmbientInfo.arg, this);
        mAmbientInfo.arg = NULL;
    }

    mStartedFlag = false;
    mFadeOutFlag = false;
}

void BasicSound::AttachPlayerHeap(PlayerHeap* pHeap) {
    mHeap = pHeap;
}

void BasicSound::DetachPlayerHeap(PlayerHeap* pHeap) {
#pragma unused(pHeap)
    mHeap = NULL;
}

void BasicSound::AttachSoundPlayer(SoundPlayer* pPlayer) {
    mSoundPlayer = pPlayer;
}

void BasicSound::DetachSoundPlayer(SoundPlayer* pPlayer) {
#pragma unused(pPlayer)
    mSoundPlayer = NULL;
}

void BasicSound::AttachSoundActor(nw4r::snd::SoundActor* pActor) {
    mSoundActor = pActor;
}

void BasicSound::DetachSoundActor(nw4r::snd::SoundActor* pActor) {
#pragma unused(pActor)
    mSoundActor = NULL;
}

void BasicSound::AttachExternalSoundPlayer(ExternalSoundPlayer* pExtPlayer) {
    mExtSoundPlayer = pExtPlayer;
}

void BasicSound::DetachExternalSoundPlayer(ExternalSoundPlayer* pExtPlayer) {
#pragma unused(pExtPlayer)
    mExtSoundPlayer = NULL;
}

int BasicSound::GetVoiceOutCount() const {
    return mVoiceOutCount;
}

void BasicSound::SetPlayerPriority(int priority) {
    mPriority = priority;

    if (mSoundPlayer != NULL) {
        mSoundPlayer->detail_ChangePriority(this);
    }

    OnUpdatePlayerPriority();
}

void BasicSound::SetInitialVolume(f32 vol) {
    mInitVolume = ut::Clamp(vol, 0.0f, 1.0f);
}

void BasicSound::SetVolume(f32 vol, int frames) {
    f32 target = ut::Clamp(vol, 0.0f, 1.0f);
    mExtMoveVolume.SetTarget(target, frames);
}

void BasicSound::SetPitch(f32 pitch) {
    mExtPitch = pitch;
}

void BasicSound::SetPan(f32 pan) {
    mExtPan = pan;
}

void BasicSound::SetSurroundPan(f32 pan) {
    mExtSurroundPan = pan;
}

void BasicSound::SetLpfFreq(f32 freq) {
    mLpfFreq = freq;
}






void BasicSound::SetMainSend(f32 send) {
    GetBasicPlayer().SetMainSend(send);
}

void BasicSound::SetFxSend(AuxBus bus, f32 send) {
    mFxSend[bus] = send;
}

void BasicSound::SetRemoteFilter(int filter) {
    GetBasicPlayer().SetRemoteFilter(filter);
}

void BasicSound::SetPanMode(PanMode mode) {
    GetBasicPlayer().SetPanMode(mode);
}

void BasicSound::SetPanCurve(PanCurve curve) {
    GetBasicPlayer().SetPanCurve(curve);
}

void BasicSound::SetAmbientInfo(const AmbientArgInfo& rInfo) {
    void* pArg =
        rInfo.argAllocaterCallback->detail_AllocAmbientArg(rInfo.argSize);

    if (pArg == NULL) {
        return;
    }

    std::memcpy(pArg, rInfo.arg, rInfo.argSize);
    mAmbientInfo = rInfo;
    mAmbientInfo.arg = pArg;

    if (rInfo.paramUpdateCallback != NULL) {
        int voiceOutCount =
            mAmbientInfo.paramUpdateCallback->detail_GetRequiredVoiceOutCount(
                mAmbientInfo.arg, mId);

        if (voiceOutCount > 4) {
            voiceOutCount = 4;
        }

        mVoiceOutCount = voiceOutCount;
    }
}

int BasicSound::GetAmbientPriority(const AmbientArgInfo& rInfo, u32 id) {
    if (rInfo.paramUpdateCallback == NULL) {
        return 0;
    }

    int priority =
        rInfo.paramUpdateCallback->detail_GetAmbientPriority(rInfo.arg, id);

    return priority;
}








bool BasicSound::IsAttachedGeneralHandle() {
    return mGeneralHandle != NULL;
}

bool BasicSound::IsAttachedTempGeneralHandle() {
    return mTempGeneralHandle != NULL;
}

void BasicSound::DetachGeneralHandle() {
    mGeneralHandle->DetachSound();
}

void BasicSound::DetachTempGeneralHandle() {
    mTempGeneralHandle->DetachSound();
}

void BasicSound::SetId(u32 id) {
    mId = id;
    GetBasicPlayer().SetId(id);
}

} // namespace detail
} // namespace snd
} // namespace nw4r
