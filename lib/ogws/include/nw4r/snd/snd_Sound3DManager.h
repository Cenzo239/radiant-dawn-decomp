#ifndef NW4R_SND_SOUND_3D_MANAGER_H
#define NW4R_SND_SOUND_3D_MANAGER_H
#include <nw4r/types_nw4r.h>

#include <nw4r/snd/snd_BasicSound.h>
#include <nw4r/snd/snd_InstancePool.h>
#include <nw4r/snd/snd_Sound3DEngine.h>
#include <nw4r/snd/snd_Sound3DListener.h>
#include <nw4r/snd/snd_SoundArchive.h>

#include <nw4r/math.h>
#include <nw4r/ut/ut_LinkList.h>

namespace nw4r {
namespace snd {

// FE10: ambient argument of Sound3DActor (newer NW4R, see zeldaret/ss)
struct Sound3DParam {
    math::VEC3 position; // at 0x0
    math::VEC3 velocity; // at 0xC
    u32 flags;           // at 0x18
    u8 decayCurve;       // at 0x1C
    u8 decayRatio;       // at 0x1D
    u8 field_0x1E;       // at 0x1E (doppler factor)
    u32 userParam;       // at 0x20
    u32 soundUserParam;  // at 0x24

    Sound3DParam();
};

// FE10: the Sound3DEngine generation (reference zeldaret/ss), 0x28 bytes
class Sound3DManager : public detail::BasicSound::AmbientParamUpdateCallback,
                       public detail::BasicSound::AmbientArgAllocaterCallback {
public:
    typedef ut::LinkList<Sound3DListener, offsetof(Sound3DListener, mNode)>
        ListenerList;

    enum ParamDecayCurve {
        DECAY_CURVE_NONE,
        DECAY_CURVE_LOGARITHMIC,
        DECAY_CURVE_LINEAR,
    };

public:
    Sound3DManager();

    virtual void detail_Update(const void* pArg, u32 id, int voiceOutCount,
                               SoundAmbientParam* pParam); // at 0xC
    virtual int detail_GetAmbientPriority(const void* pArg,
                                          u32 id); // at 0x10
    virtual int detail_GetRequiredVoiceOutCount(const void* pArg,
                                                u32 id); // at 0x14

    virtual void* detail_AllocAmbientArg(u32 size);
    virtual void detail_FreeAmbientArg(void* pArg,
                                       const detail::BasicSound* pSound);

    u32 GetRequiredMemSize(const SoundArchive* pArchive);
    bool Setup(const SoundArchive* pArchive, void* pBuffer, u32 size);

    const ListenerList& GetListenerList() const {
        return mListenerList;
    }
    ListenerList& GetListenerList() {
        return mListenerList;
    }

    int GetMaxPriorityReduction() const {
        return mMaxPriorityReduction;
    }
    void SetMaxPriorityReduction(int max) {
        mMaxPriorityReduction = max;
    }

    f32 GetPanRange() const {
        return mPanRange;
    }
    void SetPanRange(f32 range) {
        mPanRange = range;
    }

    f32 GetSonicVelocity() const {
        return mSonicVelocity;
    }
    void SetSonicVelocity(f32 velocity) {
        mSonicVelocity = velocity;
    }

    void SetEngine(Sound3DEngine* pEngine) {
        mpEngine = pEngine;
    }

private:
    detail::InstancePool<Sound3DParam> mParamPool; // at 0x8
    ListenerList mListenerList;                    // at 0xC
    Sound3DEngine* mpEngine;                       // at 0x18
    s32 mMaxPriorityReduction;                     // at 0x1C
    f32 mPanRange;                                 // at 0x20
    f32 mSonicVelocity;                            // at 0x24
};

} // namespace snd
} // namespace nw4r

#endif
