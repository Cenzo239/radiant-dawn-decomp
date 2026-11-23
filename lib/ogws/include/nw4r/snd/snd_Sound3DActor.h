#ifndef NW4R_SND_SOUND_3D_ACTOR_H
#define NW4R_SND_SOUND_3D_ACTOR_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>
#include <nw4r/snd/snd_BasicSound.h>
#include <nw4r/snd/snd_SoundActor.h>

namespace nw4r {
namespace snd {

// Forward declarations
class Sound3DManager;
class SoundArchivePlayer;
class SoundHandle;

// FE10: the newer NW4R Sound3DActor (reference zeldaret/ss), 0x80 bytes
class Sound3DActor : public SoundActor,
                     public detail::BasicSound::AmbientArgUpdateCallback {
public:
    Sound3DActor(SoundArchivePlayer& rPlayer, Sound3DManager& rManager);
    virtual ~Sound3DActor(); // at 0x8

    virtual StartResult SetupSound(SoundHandle* pHandle, u32 id,
                                   const StartInfo* pStartInfo,
                                   void* pArg); // at 0x14

    virtual void detail_Update(void* pArg,
                               const detail::BasicSound* pSound); // at 0xC

    const math::VEC3& GetPosition() const {
        return mPosition;
    }
    const math::VEC3& GetVelocity() const {
        return mVelocity;
    }

    void SetPosition(const math::VEC3& rPosition);

    void SetUserParam(u32 param) {
        mUserParam = param;
    }

private:
    static void ClearUpdateCallback(SoundHandle& rHandle);

private:
    Sound3DManager& m3DManager;              // at 0x58
    SoundArchivePlayer* mSoundArchivePlayer; // at 0x5C
    u32 mUserParam;                          // at 0x60
    math::VEC3 mPosition;                    // at 0x64
    math::VEC3 mVelocity;                    // at 0x70
    bool mSkipVelocityUpdate;                // at 0x7C
};

} // namespace snd
} // namespace nw4r

#endif
