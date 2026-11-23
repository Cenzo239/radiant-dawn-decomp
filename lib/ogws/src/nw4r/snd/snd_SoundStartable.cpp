#include <nw4r/snd.h>

namespace nw4r {
namespace snd {

SoundStartable::StartResult
SoundStartable::detail_StartSound(SoundHandle* pHandle, u32 id,
                                  const StartInfo* pStartInfo) {

    StartResult result = detail_SetupSound(pHandle, id, false, pStartInfo);

    if (result != START_SUCCESS) {
        return result;
    }

    pHandle->StartPrepared();
    return START_SUCCESS;
}

SoundStartable::StartResult
SoundStartable::detail_HoldSound(SoundHandle* pHandle, u32 id,
                                 const StartInfo* pStartInfo) {

    if (pHandle->IsAttachedSound() && id == pHandle->GetId()) {
        pHandle->detail_GetAttachedSound()->SetAutoStopCounter(1);
        return START_SUCCESS;
    }

    StartResult result = detail_SetupSound(pHandle, id, true, pStartInfo);

    if (result != START_SUCCESS) {
        return result;
    }

    pHandle->StartPrepared();
    pHandle->detail_GetAttachedSound()->SetAutoStopCounter(1);
    return START_SUCCESS;
}

SoundStartable::StartResult
SoundStartable::detail_PrepareSound(SoundHandle* pHandle, u32 id,
                                    const StartInfo* pStartInfo) {
    return detail_SetupSound(pHandle, id, false, pStartInfo);
}

} // namespace snd
} // namespace nw4r
