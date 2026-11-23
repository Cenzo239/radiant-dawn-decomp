#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace {

// FE10's nw4r::ut::DynamicCast also checks the pointer for NULL
// (see snd_SeqSoundHandle.cpp).
template <typename TDerived, typename TBase>
inline TDerived DynamicCast(TBase* pPtr) {
    const nw4r::ut::detail::RuntimeTypeInfo* pDerivedTypeInfo =
        nw4r::ut::detail::GetTypeInfoFromPtr_(static_cast<TDerived>(NULL));

    if (pPtr != NULL &&
        pPtr->GetRuntimeTypeInfo()->IsDerivedFrom(pDerivedTypeInfo)) {
        return static_cast<TDerived>(pPtr);
    }

    return NULL;
}

} // namespace

namespace nw4r {
namespace snd {

WaveSoundHandle::WaveSoundHandle(SoundHandle* pHandle) : mSound(NULL) {
    if (pHandle == NULL) {
        return;
    }

    if (!pHandle->IsAttachedSound()) {
        return;
    }

    detail::WaveSound* pSound =
        ::DynamicCast<detail::WaveSound*>(pHandle->detail_GetAttachedSound());

    if (pSound != NULL) {
        mSound = pSound;

        if (mSound->IsAttachedTempGeneralHandle()) {
            mSound->DetachTempGeneralHandle();
        }

        if (mSound->IsAttachedTempSpecialHandle()) {
            mSound->DetachTempSpecialHandle();
        }

        mSound->mTempSpecialHandle = this;
    }
}

void WaveSoundHandle::DetachSound() {
    if (IsAttachedSound()) {
        if (mSound->mTempSpecialHandle == this) {
            mSound->mTempSpecialHandle = NULL;
        }
    }

    if (mSound != NULL) {
        mSound = NULL;
    }
}

} // namespace snd
} // namespace nw4r
