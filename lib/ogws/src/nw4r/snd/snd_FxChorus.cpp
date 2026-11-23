#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {

// FE10 version: AXFXChorusExp, mIsActive outside of AxfxImpl

FxChorus::FxChorus() : mIsActive(false) {
    ChorusParam param;
    SetParam(param);
}

u32 FxChorus::GetRequiredMemSize() {
    u32 memSize = AXFXChorusExpGetMemSize(&mAxfxParam);
    return ut::RoundUp(memSize + detail::AxfxImpl::HEAP_SIZE_MIN, 32);
}

bool FxChorus::AssignWorkBuffer(void* pBuffer, u32 size) {
    return mImpl.CreateHeap(pBuffer, size);
}

void FxChorus::ReleaseWorkBuffer() {
    mImpl.DestroyHeap();
}

bool FxChorus::StartUp() {
    u32 memSize = GetRequiredMemSize();
    if (memSize > mImpl.GetHeapTotalSize()) {
        return false;
    }

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    BOOL success = AXFXChorusExpInit(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);

    (void)AXFXChorusExpGetMemSize(&mAxfxParam); // debug leftover
    mIsActive = true;

    return success;
}

void FxChorus::Shutdown() {
    if (!mIsActive) {
        return;
    }

    mIsActive = false;

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    AXFXChorusExpShutdown(&mAxfxParam);

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

bool FxChorus::SetParam(const ChorusParam& rParam) {
    mParam = rParam;

    mAxfxParam.delayTime = ut::Clamp(rParam.delayTime, 0.1f, 50.0f);
    mAxfxParam.depth = ut::Clamp(rParam.depth, 0.0f, 1.0f);
    mAxfxParam.rate = ut::Clamp(rParam.rate, 0.1f, 2.0f);
    mAxfxParam.feedback = ut::Clamp(rParam.feedback, 0.0f, 0.99f);
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

    return AXFXChorusExpSettingsUpdate(&mAxfxParam);
}

const FxChorus::ChorusParam& FxChorus::GetParam() const {
    return mParam;
}

void FxChorus::UpdateBuffer(int channels, void** ppBuffer, u32 size,
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

    AXFXChorusExpCallback(&update, &mAxfxParam);
}

} // namespace snd
} // namespace nw4r
