#ifndef NW4R_SND_BASIC_SOUND_H
#define NW4R_SND_BASIC_SOUND_H
#include <nw4r/types_nw4r.h>

#include <nw4r/snd/snd_BasicPlayer.h>
#include <nw4r/snd/snd_MoveValue.h>
#include <nw4r/snd/snd_Types.h>

#include <nw4r/ut.h>

#include <revolution/WPAD.h>

namespace nw4r {
namespace snd {

// Forward declarations
class SoundHandle;
class SoundActor;
class SoundPlayer;

// FE10: parameters exchanged with the ambient parameter callback
struct SoundAmbientParam {
    SoundAmbientParam()
        : volume(1.0f),
          pitch(1.0f),
          pan(0.0f),
          surroundPan(0.0f),
          fxSend(0.0f),
          lpf(0.0f),
          priority(0) {}

    f32 volume;                                     // at 0x0
    f32 pitch;                                      // at 0x4
    f32 pan;                                        // at 0x8
    f32 surroundPan;                                // at 0xC
    f32 fxSend;                                     // at 0x10
    f32 lpf;                                        // at 0x14
    int priority;                                   // at 0x18
    detail::BasicPlayer::OutParam voiceOutParam[4]; // at 0x1C
};

namespace detail {
class ExternalSoundPlayer;
class PlayerHeap;
} // namespace detail

namespace detail {

class BasicSound {
    friend class nw4r::snd::SoundHandle;

public:
    NW4R_UT_RTTI_DECL(BasicSound);

    struct AmbientParamUpdateCallback {
        enum ParamUpdateFlags {
            PARAM_UPDATE_VOLUME = (1 << 0),
            PARAM_UPDATE_PAN = (1 << 1),
            PARAM_UPDATE_SURROUND_PAN = (1 << 2),
            PARAM_UPDATE_PRIORITY = (1 << 3),
        };

        virtual ~AmbientParamUpdateCallback() {} // at 0x8

        // FE10: (arg, id, voice out count, param)
        virtual void detail_Update(const void* pArg, u32 id,
                                   int voiceOutCount,
                                   SoundAmbientParam* pParam) = 0; // at 0xC

        virtual int detail_GetAmbientPriority(const void*, u32) {
            return 0;
        } // at 0x10

        virtual int detail_GetRequiredVoiceOutCount(const void*, u32) {
            return 1;
        } // at 0x14
    };

    struct AmbientArgUpdateCallback {
        virtual ~AmbientArgUpdateCallback() {} // at 0x8

        virtual void detail_Update(void* pArg,
                                   const BasicSound* pSound) = 0; // at 0xC
    };

    struct AmbientArgAllocaterCallback {
        virtual ~AmbientArgAllocaterCallback() {} // at 0x8

        virtual void* detail_AllocAmbientArg(u32 size) = 0; // at 0xC

        virtual void
        detail_FreeAmbientArg(void* pArg,
                              const BasicSound* pSound) = 0; // at 0x10
    };

    struct AmbientArgInfo {
        AmbientParamUpdateCallback* paramUpdateCallback;   // at 0x0
        AmbientArgUpdateCallback* argUpdateCallback;       // at 0x4
        AmbientArgAllocaterCallback* argAllocaterCallback; // at 0x8
        void* arg;                                         // at 0xC
        u32 argSize;                                       // at 0x10
    };

    static const u32 INVALID_ID = 0xFFFFFFFF;
    static const int PRIORITY_MAX = 127;

public:
    BasicSound(int priority, int ambientPriority);
    virtual ~BasicSound() {} // at 0xC

    virtual void Shutdown();                        // at 0x10
    virtual bool IsPrepared() const = 0;            // at 0x14
    virtual bool IsAttachedTempSpecialHandle() = 0; // at 0x18
    virtual void DetachTempSpecialHandle() = 0;     // at 0x1C

    virtual void InitParam();                              // at 0x20
    virtual BasicPlayer& GetBasicPlayer() = 0;             // at 0x24
    virtual const BasicPlayer& GetBasicPlayer() const = 0; // at 0x28

    virtual void OnUpdatePlayerPriority() {} // at 0x2C
    virtual void UpdateMoveValue();          // at 0x30
    virtual void UpdateParam();              // at 0x34

    void Update();
    void StartPrepared();
    void Stop(int frames);
    void Pause(bool flag, int frames);
    void SetAutoStopCounter(int count) {
        mAutoStopCounter = count;
        mAutoStopFlag = count > 0;
    }
    void FadeIn(int frames);
    bool IsPause() const;

    bool IsStartedSound() const {
        return mStartedFlag;
    }

    void SetInitialVolume(f32 vol);
    void SetVolume(f32 vol, int frames);
    void SetPitch(f32 pitch);
    void SetPan(f32 pan);
    void SetSurroundPan(f32 pan);
    void SetLpfFreq(f32 freq);
    void SetPlayerPriority(int priority);
    void SetRemoteFilter(int filter);
    void SetPanMode(PanMode mode);
    void SetPanCurve(PanCurve curve);

    int GetVoiceOutCount() const;

    void AttachPlayerHeap(PlayerHeap* pHeap);
    void DetachPlayerHeap(PlayerHeap* pHeap);
    void AttachSoundPlayer(SoundPlayer* pPlayer);
    void DetachSoundPlayer(SoundPlayer* pPlayer);
    void SetAmbientInfo(const AmbientArgInfo& rInfo);
    static int GetAmbientPriority(const AmbientArgInfo& rInfo, u32 id);

    void AttachSoundActor(nw4r::snd::SoundActor* pActor);
    void DetachSoundActor(nw4r::snd::SoundActor* pActor);
    void AttachExternalSoundPlayer(ExternalSoundPlayer* pExtPlayer);
    void DetachExternalSoundPlayer(ExternalSoundPlayer* pExtPlayer);

    PlayerHeap* GetPlayerHeap() {
        return mHeap;
    }
    void SetPlayerHeap(PlayerHeap* pHeap) {
        mHeap = pHeap;
    }

    bool IsAttachedGeneralHandle();
    void DetachGeneralHandle();

    bool IsAttachedTempGeneralHandle();
    void DetachTempGeneralHandle();

    SoundPlayer* GetSoundPlayer() {
        return mSoundPlayer;
    }
    void SetSoundPlayer(SoundPlayer* pPlayer) {
        mSoundPlayer = pPlayer;
    }

    ExternalSoundPlayer* GetExternalSoundPlayer() {
        return mExtSoundPlayer;
    }
    void SetExternalSoundPlayer(ExternalSoundPlayer* pExtPlayer) {
        mExtSoundPlayer = pExtPlayer;
    }

    AmbientParamUpdateCallback* GetAmbientParamUpdateCallback() {
        return mAmbientInfo.paramUpdateCallback;
    }

    AmbientArgUpdateCallback* GetAmbientArgUpdateCallback() {
        return mAmbientInfo.argUpdateCallback;
    }
    void ClearAmbientArgUpdateCallback() {
        mAmbientInfo.argUpdateCallback = NULL;
    }

    AmbientArgAllocaterCallback* GetAmbientArgAllocaterCallback() {
        return mAmbientInfo.argAllocaterCallback;
    }

    void* GetAmbientArg() {
        return mAmbientInfo.arg;
    }

    SoundParam& GetAmbientParam() {
        return mAmbientParam;
    }

    void SetAmbientParamCallback(
        AmbientParamUpdateCallback* pParamUpdate,
        AmbientArgUpdateCallback* pArgUpdate,
        AmbientArgAllocaterCallback* pArgAlloc, void* pArg) {

        mAmbientInfo.paramUpdateCallback = pParamUpdate;
        mAmbientInfo.argUpdateCallback = pArgUpdate;
        mAmbientInfo.argAllocaterCallback = pArgAlloc;
        mAmbientInfo.arg = pArg;
    }

    void SetPriority(int priority) {
        mPriority = priority;
    }

    u32 GetId() const {
        return mId;
    }
    void SetId(u32 id);

    f32 GetMoveVolume() {
        return mExtMoveVolume.GetValue();
    }

    f32 GetInitialVolume() const {
        return mInitVolume;
    }
    f32 GetPan() const {
        return mExtPan;
    }
    f32 GetSurroundPan() const {
        return mExtSurroundPan;
    }
    f32 GetPitch() const {
        return mExtPitch;
    }

    void SetOutputLine(int flag) {
        mOutputLineFlag = flag;
        mOutputLineFlagEnable = true;
    }
    bool IsEnabledOutputLine() const {
        return mOutputLineFlagEnable;
    }
    int GetOutputLine() const {
        return mOutputLineFlag;
    }

    f32 GetMainOutVolume() const {
        return mMainOutVolume;
    }
    void SetMainOutVolume(f32 vol) {
        mMainOutVolume = ut::Clamp(vol, 0.0f, 1.0f);
    }

    f32 GetRemoteOutVolume(int remote) const {
        return mRemoteOutVolume[remote];
    }
    void SetRemoteOutVolume(int remote, f32 vol) {
        mRemoteOutVolume[remote] = ut::Clamp(vol, 0.0f, 1.0f);
    }

    void SetMainSend(f32 send);
    void SetFxSend(AuxBus bus, f32 send);

    int CalcCurrentPlayerPriority() const {
        return ut::Clamp(mPriority + mAmbientParam.priority, 0, PRIORITY_MAX);
    }

private:
    struct AmbientSoundParam : public SoundParam {
        AmbientSoundParam() {
            volume = 1.0f;
            pitch = 1.0f;
            pan = 0.0f;
            surroundPan = 0.0f;
            fxSend = 0.0f;
            lpf = 0.0f;
        }
    };

    struct ActorParam {
        ActorParam() : volume(1.0f), pitch(1.0f), pan(0.0f) {}

        f32 volume; // at 0x0
        f32 pitch;  // at 0x4
        f32 pan;    // at 0x8
    };

    PlayerHeap* mHeap;                    // at 0x4
    SoundHandle* mGeneralHandle;          // at 0x8
    SoundHandle* mTempGeneralHandle;      // at 0xC
    SoundPlayer* mSoundPlayer;            // at 0x10
    nw4r::snd::SoundActor* mSoundActor;            // at 0x14
    ExternalSoundPlayer* mExtSoundPlayer; // at 0x18

    AmbientArgInfo mAmbientInfo;                               // at 0x1C
    AmbientSoundParam mAmbientParam;                           // at 0x30
    ActorParam mActorParam;                                    // at 0x4C

    MoveValue<f32, int> mFadeVolume;      // at 0x58
    MoveValue<f32, int> mPauseFadeVolume; // at 0x68
    bool mStartFlag;                      // at 0x78
    bool mStartedFlag;                    // at 0x79
    bool mAutoStopFlag;                   // at 0x7A
    bool mPauseFlag;                      // at 0x7B
    bool mPauseFadeFlag;                  // at 0x7C
    bool mFadeOutFlag;                    // at 0x7D
    int mAutoStopCounter;                 // at 0x80
    u32 mUpdateCounter;                   // at 0x84

    u8 mPriority;      // at 0x88
    u8 mVoiceOutCount; // at 0x89
    u32 mId;           // at 0x8C

    MoveValue<f32, int> mExtMoveVolume; // at 0x90
    f32 mInitVolume;                    // at 0xA0
    f32 mExtPan;                        // at 0xA4
    f32 mExtSurroundPan;                // at 0xA8
    f32 mExtPitch;                      // at 0xAC
    f32 mLpfFreq;                       // at 0xB0

    bool mOutputLineFlagEnable;                 // at 0xB4
    int mOutputLineFlag;                        // at 0xB8
    f32 mMainOutVolume;                         // at 0xBC
    f32 mFxSend[AUX_BUS_NUM];                   // at 0xC0
    f32 mRemoteOutVolume[WPAD_MAX_CONTROLLERS]; // at 0xCC

public:
    NW4R_UT_LINKLIST_NODE_DECL_EX(Prio);       // at 0xDC
    NW4R_UT_LINKLIST_NODE_DECL_EX(PlayerPlay); // at 0xE4
    NW4R_UT_LINKLIST_NODE_DECL_EX(PlayerPrio); // at 0xEC
    NW4R_UT_LINKLIST_NODE_DECL_EX(ExtPlay);    // at 0xF4
};

NW4R_UT_LINKLIST_TYPEDEF_DECL_EX(BasicSound, Prio);
NW4R_UT_LINKLIST_TYPEDEF_DECL_EX(BasicSound, PlayerPlay);
NW4R_UT_LINKLIST_TYPEDEF_DECL_EX(BasicSound, PlayerPrio);
NW4R_UT_LINKLIST_TYPEDEF_DECL_EX(BasicSound, ExtPlay);

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
