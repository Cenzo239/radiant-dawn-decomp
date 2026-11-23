#ifndef NW4R_SND_SOUND_ACTOR_H
#define NW4R_SND_SOUND_ACTOR_H
#include <nw4r/types_nw4r.h>

#include <nw4r/snd/snd_BasicSound.h>
#include <nw4r/snd/snd_ExternalSoundPlayer.h>
#include <nw4r/snd/snd_SoundStartable.h>

#include <climits>

namespace nw4r {
namespace snd {

// Forward declarations
class SoundArchivePlayer;
class SoundHandle;

namespace detail {

struct SoundActorParam {
    f32 volume; // at 0x0
    f32 pitch;  // at 0x4
    f32 pan;    // at 0x8

    SoundActorParam() : volume(1.0f), pitch(1.0f), pan(0.0f) {}
};

} // namespace detail

// FE10: the newer NW4R SoundActor (reference zeldaret/ss), 0x54 bytes
class SoundActor : public SoundStartable {
public:
    explicit SoundActor(SoundArchivePlayer& rPlayer);
    virtual ~SoundActor(); // at 0x8

    virtual StartResult detail_SetupSound(SoundHandle* pHandle, u32 id,
                                          bool hold,
                                          const StartInfo* pStartInfo); // at 0xC

    virtual u32 detail_ConvertLabelStringToSoundId(const char* pLabel); // at 0x10

    virtual StartResult SetupSound(SoundHandle* pHandle, u32 id,
                                   const StartInfo* pStartInfo,
                                   void* pArg); // at 0x14

    virtual StartResult
    detail_SetupSoundWithAmbientInfo(SoundHandle* pHandle, u32 id,
                                     const StartInfo* pStartInfo,
                                     detail::BasicSound::AmbientArgInfo* pInfo,
                                     void* pArg); // at 0x18

    detail::ExternalSoundPlayer* detail_GetActorPlayer(int idx) {
        if (idx < 0 || idx >= ACTOR_PLAYER_COUNT) {
            return NULL;
        }

        return &mActorPlayer[idx];
    }

    // Older name used by the ogws sources
    detail::ExternalSoundPlayer* detail_GetActorSoundPlayer(int idx) {
        return detail_GetActorPlayer(idx);
    }

    const detail::SoundActorParam& detail_GetActorParam() const {
        return mActorParam;
    }

    template <typename TForEachFunc>
    TForEachFunc ForEachSound(TForEachFunc pFunc, bool reverse) {
        for (int i = 0; i < ACTOR_PLAYER_COUNT; i++) {
            mActorPlayer[i].ForEachSound(pFunc, reverse);
        }

        return pFunc;
    }

    int GetPlayingSoundCount(int idx) const;

    void SetVolume(f32 volume) {
        mActorParam.volume = volume;
    }
    f32 GetVolume() const {
        return mActorParam.volume;
    }

public:
    static const int ACTOR_PLAYER_COUNT = 4;

private:
    SoundArchivePlayer& mSoundArchivePlayer;                      // at 0x4
    detail::ExternalSoundPlayer mActorPlayer[ACTOR_PLAYER_COUNT]; // at 0x8
    detail::SoundActorParam mActorParam;                          // at 0x48
};

} // namespace snd
} // namespace nw4r

#endif
