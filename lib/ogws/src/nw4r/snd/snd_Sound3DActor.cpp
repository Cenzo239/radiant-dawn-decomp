#include <nw4r/snd.h>

// FE10: the newer NW4R Sound3DActor (reference zeldaret/ss).

namespace nw4r {
namespace snd {

Sound3DActor::Sound3DActor(SoundArchivePlayer& rPlayer,
                           Sound3DManager& rManager)
    : SoundActor(rPlayer),
      m3DManager(rManager),
      mSoundArchivePlayer(&rPlayer),
      mUserParam(0),
      mPosition(0.0f, 0.0f, 0.0f),
      mVelocity(0.0f, 0.0f, 0.0f),
      mSkipVelocityUpdate(true) {}

Sound3DActor::~Sound3DActor() {
    ForEachSound(ClearUpdateCallback, false);
}

SoundStartable::StartResult
Sound3DActor::SetupSound(SoundHandle* pHandle, u32 id,
                         const StartInfo* pStartInfo, void* pArg) {
    Sound3DParam param;
    param.position = mPosition;
    param.velocity = mVelocity;
    param.userParam = mUserParam;

    if (mSoundArchivePlayer != NULL) {
        const SoundArchive& rArchive = mSoundArchivePlayer->GetSoundArchive();

        SoundArchive::Sound3DParam arParam;
        if (rArchive.detail_ReadSound3DParam(id, &arParam)) {
            param.flags = arParam.flags;
            param.decayCurve = arParam.decayCurve;
            param.decayRatio = arParam.decayRatio;
            param.field_0x1E = arParam.dopplerFactor;
        }

        param.soundUserParam = rArchive.GetSoundUserParam(id);
    }

    detail::BasicSound::AmbientArgInfo info = {
        &m3DManager,         // paramUpdateCallback
        this,                // argUpdateCallback
        &m3DManager,         // argAllocaterCallback
        &param,              // arg
        sizeof(Sound3DParam) // argSize
    };

    StartResult result = SoundActor::detail_SetupSoundWithAmbientInfo(
        pHandle, id, pStartInfo, &info, pArg);

    if (pHandle->detail_GetAttachedSound() != NULL) {
        pHandle->detail_GetAttachedSound()->SetPanCurve(
            detail::PAN_CURVE_SINCOS);
    }

    return result;
}

void Sound3DActor::SetPosition(const math::VEC3& rPosition) {
    if (!mSkipVelocityUpdate) {
        VEC3Sub(&mVelocity, &rPosition, &mPosition);
    }

    mPosition = rPosition;
    mSkipVelocityUpdate = false;
}

void Sound3DActor::detail_Update(void* pArg, const detail::BasicSound* pSound) {
#pragma unused(pSound)

    Sound3DParam* pParam = static_cast<Sound3DParam*>(pArg);

    pParam->position = mPosition;
    pParam->velocity = mVelocity;
    pParam->userParam = mUserParam;
}

void Sound3DActor::ClearUpdateCallback(SoundHandle& rHandle) {
    if (rHandle.IsAttachedSound()) {
        rHandle.detail_GetAttachedSound()->ClearAmbientArgUpdateCallback();
    }
}

} // namespace snd
} // namespace nw4r
