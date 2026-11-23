// FE10: the Sound3DEngine generation of Sound3DManager (reference zeldaret/ss).
#include <nw4r/snd.h>
#include <nw4r/snd/snd_Sound3DEngine.h>
#include <nw4r/snd/snd_Sound3DManager.h>

namespace nw4r {
namespace snd {

Sound3DManager::Sound3DManager()
    : mpEngine(NULL),
      mMaxPriorityReduction(32),
      mPanRange(0.9f),
      mSonicVelocity(0.0f) {}

u32 Sound3DManager::GetRequiredMemSize(const SoundArchive* pArchive) {
    u32 numParam = 0;

    SoundArchive::SoundArchivePlayerInfo playerInfo;
    if (pArchive->ReadSoundArchivePlayerInfo(&playerInfo)) {
        numParam += playerInfo.seqSoundCount;
        numParam += playerInfo.strmSoundCount;
        numParam += playerInfo.waveSoundCount;
    }

    return numParam * sizeof(Sound3DParam);
}

bool Sound3DManager::Setup(const SoundArchive* pArchive, void* pBuffer,
                           u32 size) {
#pragma unused(pArchive)

    mParamPool.Create(pBuffer, size);

    static Sound3DEngine sEngine;
    SetEngine(&sEngine);
    return true;
}

void Sound3DManager::detail_Update(const void* pArg, u32 id,
                                   int voiceOutCount,
                                   SoundAmbientParam* pParam) {
    const Sound3DParam* p = static_cast<const Sound3DParam*>(pArg);
    if (mpEngine != NULL) {
        mpEngine->UpdateAmbientParam(this, p, id, voiceOutCount, pParam);
    }
}

int Sound3DManager::detail_GetAmbientPriority(const void* pArg, u32 id) {
    int result = 0;
    if (mpEngine != NULL) {
        const Sound3DParam* p = static_cast<const Sound3DParam*>(pArg);
        result = mpEngine->GetAmbientPriority(this, p, id);
    }
    return result;
}

int Sound3DManager::detail_GetRequiredVoiceOutCount(const void* pArg,
                                                    u32 id) {
    int result = 1;
    if (mpEngine != NULL) {
        const Sound3DParam* p = static_cast<const Sound3DParam*>(pArg);
        result = mpEngine->GetRequiredVoiceOutCount(this, p, id);
    }
    return result;
}

void* Sound3DManager::detail_AllocAmbientArg(u32 size) {
    if (size != sizeof(Sound3DParam)) {
        return NULL;
    }

    return mParamPool.Alloc();
}

void Sound3DManager::detail_FreeAmbientArg(void* pArg,
                                           const detail::BasicSound* pSound) {
#pragma unused(pSound)

    mParamPool.Free(static_cast<Sound3DParam*>(pArg));
}

Sound3DParam::Sound3DParam() {
    flags = 0;
    decayCurve = Sound3DManager::DECAY_CURVE_LOGARITHMIC;
    decayRatio = 128;
    field_0x1E = 0;
    userParam = 0;
    soundUserParam = 0;
}

} // namespace snd
} // namespace nw4r
