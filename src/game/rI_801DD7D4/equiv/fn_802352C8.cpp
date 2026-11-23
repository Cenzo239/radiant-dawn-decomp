/* fn_802352C8 (round 22, agent r22b): class `regs`, 10 words differ.
 * Revolution DEMO library, __DEMOInitMem(): carve the GX FIFO (0x80000, lbl_804CBF20) and
 * two external frame buffers (lbl_804CBF30, lbl_804CBF34; size lbl_804CBF2C =
 * VIPadFrameBufferWidth(fbWidth) * xfbHeight * 2) from the MEM1 arena, then either make
 * expanded heaps over the rest of MEM1 and MEM2 with allocators lbl_8041F070/lbl_8041F080
 * (lbl_804CBF3C set), or set up the game's own memory (fn_800784E0, fn_800785FC) and a
 * MEM2 heap with a 0x780000 sub-heap lbl_804CBF40.
 * fn_8030E294 = MEMCreateExpHeapEx, fn_8030ECF8 = MEMInitAllocatorForExpHeap,
 * fn_8030ECD8 = MEMAllocFromAllocator.
 *
 * Remaining difference: in the lbl_804CBF3C branch the arena low/high and the heap handle
 * take r30/r29/r31 in the original and r30/r31/r30 here (callee-saved `mr` only, both
 * halves); declaration order, function-level reuse of lo/hi, and scoping were tried.
 * symcheck --anon --xargs: 35 blocks, 0 differ.
 */
#include "game/rI_801DD7D4/types.h"
extern "C" {
/* GXRenderModeObj */
typedef struct RM {
    u32 viTVmode;
    u16 fbWidth, efbHeight, xfbHeight, viXOrigin, viYOrigin, viWidth, viHeight;
    u32 xFBmode;
    u8 field_rendering, aa;
    u8 sample_pattern[12][2];
    u8 vfilter[7];
} RM;
extern RM lbl_8041F030;
extern RM lbl_803A03F8, lbl_803A0470, lbl_803A04AC, lbl_803A0434;
extern RM* lbl_804CBF28;
extern char lbl_803726A8[];
int VIGetTvFormat(void);
void OSPanic(const char*, int, const char*, ...);
void fn_80304638(const RM*, RM*, u16, u16);
u32 OSGetMEM1ArenaLo(void);
u32 OSGetMEM1ArenaHi(void);
u32 OSGetMEM2ArenaLo(void);
u32 OSGetMEM2ArenaHi(void);
void OSSetMEM1ArenaLo(u32);
void OSSetMEM2ArenaLo(u32);
void* fn_8030E294(u32, u32, int);
void fn_8030ECF8(void*, void*, int);
void fn_800784E0(void);
void fn_800785FC(const char*, u32);
u32 fn_8030ECD8(void*, u32);
extern u32 lbl_804CBF20, lbl_804CBF30, lbl_804CBF2C, lbl_804CBF34, lbl_804CBF3C;
extern void* lbl_804CBF40;
extern u8 lbl_8041F070[0x10], lbl_8041F080[0x10];
#define RUP32(x) (((u32)(x) + 0x1f) & ~0x1f)
void fn_802352C8(void) {
    u32 lo;
    u32 hi;
    u32 sz;
    lo = OSGetMEM1ArenaLo();
    hi = OSGetMEM1ArenaHi();
    sz = ((lbl_804CBF28->fbWidth + 0xf) & 0xfff0) * lbl_804CBF28->xfbHeight * 2;
    lbl_804CBF20 = RUP32(lo);
    lbl_804CBF30 = RUP32(lbl_804CBF20 + 0x80000);
    lbl_804CBF2C = sz;
    lbl_804CBF34 = RUP32(lbl_804CBF30 + sz);
    OSSetMEM1ArenaLo(RUP32(lbl_804CBF34 + sz));
    if (lbl_804CBF3C != 0) {
        void* h;
        u32 a, b;
        a = OSGetMEM1ArenaLo();
        b = OSGetMEM1ArenaHi();
        h = fn_8030E294(a, b - a, 0);
        if (h == NULL) OSPanic(lbl_803726A8, 0x101, lbl_803726A8 + 0x28);
        OSSetMEM1ArenaLo(b);
        fn_8030ECF8(lbl_8041F070, h, 0x20);
        a = OSGetMEM2ArenaLo();
        b = OSGetMEM2ArenaHi();
        h = fn_8030E294(a, b - a, 0);
        if (h == NULL) OSPanic(lbl_803726A8, 0x10c, lbl_803726A8 + 0x45);
        OSSetMEM2ArenaLo(b);
        fn_8030ECF8(lbl_8041F080, h, 0x20);
    } else {
        u32 a, b;
        void* h;
        u32 k;
        fn_800784E0();
        fn_800785FC(lbl_803726A8 + 0x62, 0x500000);
        a = OSGetMEM2ArenaLo();
        b = OSGetMEM2ArenaHi();
        h = fn_8030E294(a, b - a, 4);
        if (h == NULL) OSPanic(lbl_803726A8, 0x13c, lbl_803726A8 + 0x45);
        OSSetMEM2ArenaLo(b);
        fn_8030ECF8(lbl_8041F080, h, 0x20);
        k = fn_8030ECD8(lbl_8041F080, 0x780000);
        if (k == 0) OSPanic(lbl_803726A8, 0x147, lbl_803726A8 + 0x67);
        lbl_804CBF40 = fn_8030E294(k, 0x780000, 4);
        if (lbl_804CBF40 == NULL) OSPanic(lbl_803726A8, 0x14d, lbl_803726A8 + 0x85);
    }
}
}
