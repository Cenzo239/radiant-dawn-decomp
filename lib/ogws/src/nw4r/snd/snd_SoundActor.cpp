#include <nw4r/snd.h>

// FE10: the newer NW4R SoundActor (reference zeldaret/ss).

namespace nw4r {
namespace snd {

SoundActor::SoundActor(SoundArchivePlayer& rPlayer)
    : mSoundArchivePlayer(rPlayer) {

    for (int i = 0; i < ACTOR_PLAYER_COUNT; i++) {
        mActorPlayer[i].SetPlayableSoundCount(i == 0 ? INT_MAX : 1);
    }
}

SoundActor::~SoundActor() {
    for (int i = 0; i < ACTOR_PLAYER_COUNT; i++) {
        mActorPlayer[i].DetachSoundActorAll(this);
    }
}

int SoundActor::GetPlayingSoundCount(int idx) const {
    return mActorPlayer[idx].GetPlayingSoundCount();
}

SoundStartable::StartResult SoundActor::SetupSound(SoundHandle* pHandle,
                                                   u32 id,
                                                   const StartInfo* pStartInfo,
                                                   void* pArg) {
    return mSoundArchivePlayer.detail_SetupSoundImpl(
        pHandle, id, NULL, this, *static_cast<bool*>(pArg), pStartInfo);
}

SoundStartable::StartResult SoundActor::detail_SetupSoundWithAmbientInfo(
    SoundHandle* pHandle, u32 id, const StartInfo* pStartInfo,
    detail::BasicSound::AmbientArgInfo* pInfo, void* pArg) {

    return mSoundArchivePlayer.detail_SetupSoundImpl(
        pHandle, id, pInfo, this, *static_cast<bool*>(pArg), pStartInfo);
}

SoundStartable::StartResult
SoundActor::detail_SetupSound(SoundHandle* pHandle, u32 id, bool hold,
                              const StartInfo* pStartInfo) {
    bool holdFlag = hold;
    return SetupSound(pHandle, id, pStartInfo, &holdFlag);
}

u32 SoundActor::detail_ConvertLabelStringToSoundId(const char* pLabel) {
    return mSoundArchivePlayer.detail_ConvertLabelStringToSoundId(pLabel);
}

} // namespace snd
} // namespace nw4r
