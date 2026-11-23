#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
extern char lbl_803699B0[];
extern u8 lbl_804CB84C;
extern MapModel* fn_8013B9A8(void);
#if TARGET_PC
extern FE10_PROTO MapGroup* fn_80135F90(MapModel*, const char*, void*, u32, u32, p32arg);
extern FE10_PROTO int fn_801CA138(MapGroup*, const char*, void*, p32arg);
#else
extern MapGroup* fn_80135F90(MapModel*, const char*, void*, u32, u32, int);
extern int fn_801CA138(MapGroup*, const char*, void*, int);
#endif
extern int fn_801357C8(MapModel*, u32);
extern u32 fn_8030585C(int, int, int, int, int);
extern void* fn_80078D9C(u32, const char*, int);
extern void DCFlushRange(void*, u32);
extern void fn_80141650(void*, void*, void*, void*);
extern void fn_80143374(void*, void*, void*);
extern void fn_80141DCC(void*, void*, void*, void*);
extern void fn_80142C44(void);
extern void fn_801420B0(void*, void*, void*, void*);
extern void fn_80143180(void*);
extern void fn_80142D90(void*, void*, void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_80143054(void*, void*, ptr32<const void>, ptr32<const void>);
#else
extern void fn_80143054(void*, void*, void*, void*);
#endif
extern void fn_80143390(void);
extern void fn_80143464(void);
extern void fn_801435A4(void);
extern void fn_8014348C(void);
struct FxP { u8 pad[0x30]; void* x30; f32 x34; void* x38; void* x3c; void* x40; void* x44; void* x48; void* x4c; void* x50; void* x54; void* x58; void* x5c; };
extern void fn_801436EC(FxP*);
#define MB(mm, o) (((u8*)(mm))[o])
static inline void Capture(FxP* p) {
    u32 sz = fn_8030585C(0x130, 0x1C0, 4, 0, 0);
    p->x38 = fn_80078D9C(sz, lbl_803699B0, 0);
    DCFlushRange(p->x38, sz);
    {
        void* q = p->x38;
        p->x40 = 0;
        p->x3c = q;
    }
}
void fn_80143D88(FxP* p) {
    MapModel* mm;
    MapGroup* g2;
    int off;
    const char* s;
    int i;
    p->x30 = 0;
    p->x34 = 0.0f;
    p->x38 = 0;
    p->x3c = 0;
    p->x40 = 0;
    p->x44 = 0;
    p->x48 = 0;
    p->x4c = 0;
    p->x50 = 0;
    p->x54 = 0;
    p->x58 = 0;
    p->x5c = 0;
    mm = fn_8013B9A8();
    if (mm == 0) return;
    switch (mm->xb1) {
    case 0:
        fn_80135F90(mm, lbl_803699B0 + 1, (void*)fn_80141650, 0, 0, 1);
        fn_80135F90(mm, lbl_803699B0 + 0xA, (void*)fn_80141650, 0, 0, 1);
        if (lbl_804CB84C) fn_80135F90(mm, lbl_803699B0 + 0x13, (void*)fn_80143374, 0, 0, 2);
        if (mm->flags & 4) fn_80135F90(mm, 0, (void*)fn_80141DCC, 0x110, 0, 2);
        if (mm->flags & 0x10) {
            for (i = 0, off = 0; i < mm->nGroup; off += 0xC0, i++) {
                g2 = (MapGroup*)((u8*)mm->group + off);
                if ((g2->flags & 0x2000) && fn_801CA138(g2, lbl_803699B0 + 0x1C, (void*)fn_80142C44, 2) == 0) {
                    fn_801CA138(g2, 0, (void*)fn_80142C44, 2);
                }
            }
        }
        if ((mm->flags & 0x20) && fn_80135F90(mm, lbl_803699B0 + 0x26, (void*)fn_801420B0, 0, 0, 1)) {
            if (MB(mm, 0x56) && fn_801357C8(mm, 0x8000000)) {
                fn_80135F90(mm, lbl_803699B0 + 0x26, (void*)fn_80143180, 0, 0, 1);
                Capture(p);
            }
            if (MB(mm, 0x60)) fn_801436EC(p);
        }
        break;
    case 1:
    case 2:
    case 3:
    {
        MapGroup* g;
        fn_80135F90(mm, lbl_803699B0 + 1, (void*)fn_80141650, 0, 0, 1);
        fn_80135F90(mm, lbl_803699B0 + 0xA, (void*)fn_80141650, 0, 0, 1);
        if ((mm->flags & 4) && fn_80135F90(mm, lbl_803699B0 + 0x30, (void*)fn_80142D90, 0x110, 0, 2) == 0) {
            fn_80135F90(mm, 0, (void*)fn_80142D90, 0x110, 0, 2);
        }
        s = lbl_803699B0 + 0x39;
        g = fn_80135F90(mm, s, (void*)fn_80143054, 0, 0, 1);
        if (g == 0) {
            s = lbl_803699B0 + 0x26;
            g = fn_80135F90(mm, s, (void*)fn_801420B0, 0, 0, 1);
        }
        if (g) {
            if (MB(mm, 0x56) && fn_801357C8(mm, 0x8000000)) {
                fn_80135F90(mm, s, (void*)fn_80143180, 0, 0, 1);
                Capture(p);
            }
            if (MB(mm, 0x60)) fn_801436EC(p);
        } else if (MB(mm, 0x56) && fn_801357C8(mm, 0x8000000) && fn_80135F90(mm, lbl_803699B0 + 0x41, (void*)fn_80143180, 0, 0, 2)) {
            Capture(p);
        }
        break;
    }
    }
    fn_80135F90(mm, lbl_803699B0 + 0x47, (void*)fn_80143390, 0, 0, 2);
    fn_80135F90(mm, lbl_803699B0 + 0x47, (void*)fn_80143464, 0, 0, 4);
    if (MB(mm, 0x60) && fn_80135F90(mm, lbl_803699B0 + 0x51, (void*)fn_801435A4, 0, 0, 2)) fn_801436EC(p);
    switch (MB(mm, 0x64)) {
    case 2:
        fn_80135F90(mm, 0, (void*)fn_8014348C, 0, 0x80000, 2);
        break;
    default:
        break;
    }
}
}
