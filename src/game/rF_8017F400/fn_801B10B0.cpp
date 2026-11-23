#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* picture list input: moves between tabs, thumbnails and columns */
typedef struct LData {
    void* res;
    void* x4;
    u8 pad8[0xC];
    void* x14;
    void* x18;
    int x1C;
    int x20;
    int x24;
    int x28;
    int x2C;
    int x30;
    int x34;
    int x38;
    int x3C;
    int x40;
    int x44;
    int x48;
    int x4C;
    int x50;
    int x54;
    int x58;
    int x5C;
    int x60;
} LData;
class Pad { public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38();
    virtual u32 trig();
    virtual void v40(); virtual void v44();
    virtual u32 held();
};
extern LData* lbl_804CB9BC;
extern void* lbl_804CB9B8;
extern Pad* lbl_804CB5B8;
extern u8 lbl_8041EB20[];
extern char lbl_8036DCE0[];
#if TARGET_PC
extern FE10_PROTO p32ret fn_801B45AC(void*);
#else
extern int fn_801B45AC(void*);
#endif
extern f32 fn_8017F68C(f32, f32, f32, f32, int);
extern void fn_80179888(void*, int);
extern int fn_801B45CC(void);
extern int fn_801A2224(void*);
extern void* fn_801B092C(void);
extern void fn_801A1AC4(void*, void*, void*, f32, f32);
extern void fn_801B45F0(void*);
extern void fn_801A1CFC(void*);
extern void fn_80083DC4(void*, int);
extern void fn_80253EE4(const char*, f32);
extern void fn_801B0E88(int);
extern void fn_801B0418(void);
extern void fn_801B0DD8(void);
extern void fn_801B0E28(void);
extern void fn_801B45B4(void**, void*);
extern void fn_801B46B4(void**, int);
extern void fn_801B4638(void**, int);
extern void** fn_801B45C0(void**, void**);
extern int fn_801B09D0(void**, int);
extern s8 fn_801B0B58(void**, int);
extern int fn_8028DB44(int);
extern f32 fn_801B4600(int);

void fn_801B10B0(void) {
    int last = fn_801B45AC(lbl_804CB9BC->x18) - 1;
    u32 held;
    u32 trig;
    void* a1; void* a2; void* a3; void* a4; void* a5; void* a6;
    void* b1; void* b2; void* b3; void* b4; void* b5; void* b6;
    fn_801B45AC(lbl_804CB9BC->x18);
    if (lbl_804CB9BC->x48 > 0) lbl_804CB9BC->x48--;
    lbl_804CB9BC->x4C = (int)fn_8017F68C(lbl_804CB9BC->x54, lbl_804CB9BC->x5C, 4 - lbl_804CB9BC->x48, 4.0f, 0);
    lbl_804CB9BC->x50 = (int)fn_8017F68C(lbl_804CB9BC->x58, lbl_804CB9BC->x60, 4 - lbl_804CB9BC->x48, 4.0f, 0);
    if (lbl_804CB9BC->x30 > 0) lbl_804CB9BC->x30--;
    lbl_804CB9BC->x3C = (int)fn_8017F68C(lbl_804CB9BC->x40, lbl_804CB9BC->x44, lbl_804CB9BC->x34 - lbl_804CB9BC->x30, lbl_804CB9BC->x34, 0);
    fn_80179888(lbl_804CB9BC->x14, lbl_804CB9BC->x3C);
    if (fn_801B45CC() != 0) return;
    if (lbl_804CB9BC->x30 > 0) return;
    held = lbl_804CB5B8->held();
    trig = lbl_804CB5B8->trig();
    if ((held & 0x2000) && fn_801A2224(lbl_8041EB20) == 0) {
        LData* d = lbl_804CB9BC;
        void* s = fn_801B092C();
        fn_801A1AC4(lbl_8041EB20, lbl_804CB9B8, s, d->x4C, d->x50);
        fn_801B45F0(lbl_8041EB20);
        return;
    }
    if ((held & 0x2800) && fn_801A2224(lbl_8041EB20) != 0) {
        fn_801A1CFC(lbl_8041EB20);
        return;
    }
    if ((held & 0x800) && fn_801A2224(lbl_8041EB20) == 0) {
        fn_80083DC4(lbl_804CB9B8, 5);
        fn_80253EE4(lbl_8036DCE0 + 0x7F, 0.0f);
        return;
    }
    if ((held & 0x400) && lbl_804CB9BC->x28 == 2 && fn_801A2224(lbl_8041EB20) == 0) {
        fn_80083DC4(lbl_804CB9B8, 2);
        return;
    }
    u32 m = held & 0x800008;
    if (m || (trig & 0x800008)) {
        switch (lbl_804CB9BC->x28) {
        case 0: {
            int o = lbl_804CB9BC->x24;
            lbl_804CB9BC->x24 = o - 1;
            if (lbl_804CB9BC->x24 < 0) lbl_804CB9BC->x24 = 0;
            if (o != lbl_804CB9BC->x24) {
                fn_801B0418();
                lbl_804CB9BC->x3C = 0;
                lbl_804CB9BC->x44 = 0;
                lbl_804CB9BC->x40 = 0;
                lbl_804CB9BC->x38 = 0;
                lbl_804CB9BC->x34 = 0;
                lbl_804CB9BC->x30 = 0;
                lbl_804CB9BC->x2C = 0;
                fn_801B0E88(0);
                fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
            }
            break;
        }
        case 1: {
            fn_801B45B4(&a1, lbl_804CB9BC->x18);
            fn_801B46B4(&a1, lbl_804CB9BC->x2C);
            if (fn_801B09D0(fn_801B45C0(&b1, &a1), 0) == 0) {
                if (m) {
                    int k;
                    fn_801B45B4(&a2, lbl_804CB9BC->x18);
                    fn_801B4638(&a2, fn_801B45AC(lbl_804CB9BC->x18) - 1);
                    k = fn_801B09D0(fn_801B45C0(&b2, &a2), 0);
                    lbl_804CB9BC->x40 = lbl_804CB9BC->x38;
                    while (lbl_804CB9BC->x2C != k) fn_801B0E28();
                    fn_801B0E88((int)fn_801B4600(fn_801B45AC(lbl_804CB9BC->x18) << 2));
                    fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
                }
            } else {
                int k;
                lbl_804CB9BC->x40 = lbl_804CB9BC->x38;
                fn_801B0DD8();
                fn_801B45B4(&a3, lbl_804CB9BC->x18);
                fn_801B46B4(&a3, lbl_804CB9BC->x2C);
                k = fn_801B09D0(fn_801B45C0(&b3, &a3), 0);
                while (lbl_804CB9BC->x2C != k) fn_801B0DD8();
                fn_801B0E88((fn_8028DB44(lbl_804CB9BC->x3C - lbl_804CB9BC->x38) * 4 / 32) / 2);
                fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
            }
            break;
        }
        case 2:
            if (lbl_804CB9BC->x2C == 0) {
                if (m) {
                    lbl_804CB9BC->x40 = lbl_804CB9BC->x38;
                    while (lbl_804CB9BC->x2C != last) fn_801B0E28();
                    fn_801B0E88((int)fn_801B4600(fn_801B45AC(lbl_804CB9BC->x18) << 2));
                    fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
                }
            } else {
                lbl_804CB9BC->x40 = lbl_804CB9BC->x38;
                fn_801B0DD8();
                fn_801B0E88(4);
                fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
            }
            break;
        }
        return;
    }
    m = held & 0x400004;
    if (m || (trig & 0x400004)) {
        switch (lbl_804CB9BC->x28) {
        case 0: {
            int o = lbl_804CB9BC->x24;
            lbl_804CB9BC->x24 = o + 1;
            if (lbl_804CB9BC->x24 >= 3) lbl_804CB9BC->x24 = 2;
            if (o != lbl_804CB9BC->x24) {
                fn_801B0418();
                lbl_804CB9BC->x3C = 0;
                lbl_804CB9BC->x44 = 0;
                lbl_804CB9BC->x40 = 0;
                lbl_804CB9BC->x38 = 0;
                lbl_804CB9BC->x34 = 0;
                lbl_804CB9BC->x30 = 0;
                lbl_804CB9BC->x2C = 0;
                fn_801B0E88(0);
                fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
            }
            break;
        }
        case 1: {
            fn_801B45B4(&a4, lbl_804CB9BC->x18);
            fn_801B46B4(&a4, lbl_804CB9BC->x2C);
            s8 v = fn_801B0B58(fn_801B45C0(&b4, &a4), 0);
            if (v == last) {
                if (m) {
                    lbl_804CB9BC->x40 = lbl_804CB9BC->x38;
                    while (lbl_804CB9BC->x2C != 0) fn_801B0DD8();
                    fn_801B0E88((int)fn_801B4600(fn_801B45AC(lbl_804CB9BC->x18) << 2));
                    fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
                }
            } else {
                int k;
                lbl_804CB9BC->x40 = lbl_804CB9BC->x38;
                fn_801B45B4(&a5, lbl_804CB9BC->x18);
                fn_801B46B4(&a5, lbl_804CB9BC->x2C);
                k = fn_801B09D0(fn_801B45C0(&b5, &a5), 1);
                while (k != lbl_804CB9BC->x2C) fn_801B0E28();
                fn_801B0E88((fn_8028DB44(lbl_804CB9BC->x3C - lbl_804CB9BC->x38) * 4 / 32) / 2);
                fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
            }
            break;
        }
        case 2:
            if (lbl_804CB9BC->x2C == last) {
                if (m) {
                    lbl_804CB9BC->x40 = lbl_804CB9BC->x38;
                    while (lbl_804CB9BC->x2C != 0) fn_801B0DD8();
                    fn_801B0E88((int)fn_801B4600(fn_801B45AC(lbl_804CB9BC->x18) << 2));
                    fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
                }
            } else {
                lbl_804CB9BC->x40 = lbl_804CB9BC->x38;
                fn_801B0E28();
                fn_801B0E88(4);
                fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
            }
            break;
        }
        return;
    }
    if (trig & 0x100001) {
        switch (lbl_804CB9BC->x28) {
        case 1:
            lbl_804CB9BC->x28 = 0;
            fn_801B0E88(0);
            fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
            break;
        case 2: {
            int k;
            fn_801B45B4(&a6, lbl_804CB9BC->x18);
            fn_801B46B4(&a6, lbl_804CB9BC->x2C);
            k = fn_801B09D0(fn_801B45C0(&b6, &a6), 0);
            lbl_804CB9BC->x40 = lbl_804CB9BC->x38;
            while (lbl_804CB9BC->x2C != k) fn_801B0DD8();
            lbl_804CB9BC->x28 = 1;
            fn_801B0E88((fn_8028DB44(lbl_804CB9BC->x3C - lbl_804CB9BC->x38) * 4 / 32) / 2);
            fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
            break;
        }
        }
        return;
    }
    if (trig & 0x200002) {
        switch (lbl_804CB9BC->x28) {
        case 0:
            lbl_804CB9BC->x28 = 1;
            fn_801B0E88(0);
            fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
            break;
        case 1:
            lbl_804CB9BC->x28 = 2;
            fn_801B0E88(0);
            fn_80253EE4(lbl_8036DCE0 + 0x8F, 0.0f);
            break;
        }
    }
}
}
