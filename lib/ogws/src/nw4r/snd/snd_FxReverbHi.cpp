#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {

// FE10 version: AXFXReverbHiExp, mIsActive outside of AxfxImpl

FxReverbHi::FxReverbHi() : mIsActive(false) {
    ReverbHiParam param;
    SetParam(param);
}

u32 FxReverbHi::GetRequiredMemSize() {
    u32 memSize = AXFXReverbHiExpGetMemSize(&mAxfxParam);
    return ut::RoundUp(memSize + detail::AxfxImpl::HEAP_SIZE_MIN, 32);
}

bool FxReverbHi::AssignWorkBuffer(void* pBuffer, u32 size) {
    return mImpl.CreateHeap(pBuffer, size);
}

void FxReverbHi::ReleaseWorkBuffer() {
    mImpl.DestroyHeap();
}

bool FxReverbHi::StartUp() {
    u32 memSize = GetRequiredMemSize();
    if (memSize > mImpl.GetHeapTotalSize()) {
        return false;
    }

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    BOOL success = AXFXReverbHiExpInit(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);

    (void)AXFXReverbHiExpGetMemSize(&mAxfxParam); // debug leftover
    mIsActive = true;

    return success;
}

void FxReverbHi::Shutdown() {
    if (!mIsActive) {
        return;
    }

    mIsActive = false;

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    AXFXReverbHiExpShutdown(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);
}

// FE10: in SetParam the register that holds the zero for busIn/busOut is also the heap size
// (no `li` on the mHeap == NULL path), so the size variable is live before those stores.
// Form found by search; AxfxImpl::GetHeapTotalSize() with a caller-provided default.
static inline u32 HeapTotalSize(MEMiHeapHead* pHeap, u32 size) {
    if (pHeap == NULL) {
        return size;
    }

    return MEMGetHeapTotalSize(pHeap);
}

bool FxReverbHi::SetParam(const ReverbHiParam& rParam) {
    mParam = rParam;

    f32 preDelayTimeMax = ut::Max(rParam.preDelayTimeMax, 0.0f);
    bool needReinit = preDelayTimeMax != mAxfxParam.preDelayTimeMax;

    mAxfxParam.preDelayTimeMax = preDelayTimeMax;
    mAxfxParam.earlyMode = rParam.earlyMode;
    mAxfxParam.preDelayTime =
        ut::Clamp(rParam.preDelayTime, 0.0f, rParam.preDelayTimeMax);
    mAxfxParam.fusedMode = rParam.fusedMode;
    mAxfxParam.fusedTime = ut::Max(rParam.fusedTime, 0.0f);
    mAxfxParam.coloration = ut::Clamp(rParam.coloration, 0.0f, 1.0f);
    mAxfxParam.damping = ut::Clamp(rParam.damping, 0.0f, 1.0f);
    mAxfxParam.crosstalk = ut::Clamp(rParam.crossTalk, 0.0f, 1.0f);
    mAxfxParam.earlyGain = ut::Clamp(rParam.earlyGain, 0.0f, 1.0f);
    mAxfxParam.fusedGain = ut::Clamp(rParam.fusedGain, 0.0f, 1.0f);
    mAxfxParam.outGain = ut::Clamp(rParam.outGain, 0.0f, 1.0f);
    u32 heapSize = 0; // see HeapTotalSize
    mAxfxParam.busIn = NULL;
    mAxfxParam.busOut = NULL;
    mAxfxParam.sendGain = 0.0f;

    if (!mIsActive) {
        return true;
    }

    u32 memSize = GetRequiredMemSize();
    if (memSize > HeapTotalSize(mImpl.mHeap, heapSize)) {
        return false;
    }

    BOOL success;
    if (needReinit) {
        AXFXAllocHook allocHook;
        AXFXFreeHook freeHook;
        mImpl.HookAlloc(&allocHook, &freeHook);

        success = AXFXReverbHiExpSettings(&mAxfxParam);

        mImpl.RestoreAlloc(allocHook, freeHook);
    } else {
        success = AXFXReverbHiExpSettingsUpdate(&mAxfxParam);
    }

    return success;
}

void FxReverbHi::UpdateBuffer(int channels, void** ppBuffer, u32 size,
                              SampleFormat format, f32 sampleRate,
                              OutputMode mode) {
#pragma unused(channels)
#pragma unused(size)
#pragma unused(format)
#pragma unused(sampleRate)

    if (!mIsActive) {
        return;
    }

    if (mode == OUTPUT_MODE_DPL2) {
        return;
    }

    AXFX_BUFFERUPDATE update;
    update.left = static_cast<s32*>(ppBuffer[0]);
    update.right = static_cast<s32*>(ppBuffer[1]);
    update.surround = static_cast<s32*>(ppBuffer[2]);

    AXFXReverbHiExpCallback(&update, &mAxfxParam);
}

} // namespace snd
} // namespace nw4r
