#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

/* "Support conversation"-like fullscreen overlay state, 0x35C bytes */
typedef struct RData {
    u8 done;      /* 0x000 */
    u8 pad1[3];
    u32 flags;    /* 0x004 */
    s8 state;     /* 0x008 */
    u8 pad9;
    s16 timer;    /* 0x00A */
    void* res;    /* 0x00C */
    u8 pad10[0x320 - 0x10];
    u32 x320;     /* 0x320 */
    u32 x324;     /* 0x324 */
    u8 pad328[0x334 - 0x328];
    void* x334;   /* 0x334 */
    u8 x338;      /* 0x338 */
    u8 x339;      /* 0x339 */
    u8 pad33A[0x340 - 0x33A];
    s16 x340;     /* 0x340 */
    u8 pad342[0x358 - 0x342];
    u16 x358;     /* 0x358 */
    u8 pad35A[2];
} RData;

typedef struct RProc {
    u8 pad[0x30];
    RData* d; /* 0x30 */
} RProc;

extern RData* lbl_804CB964;
extern RProc* lbl_804CB960;
extern u32 lbl_804CB700;
extern char lbl_8036D22C[];
extern u8 lbl_80388DF8[];
extern u8 lbl_80388E94[];
extern u8 lbl_80388ED0[];
extern void* fn_8013B9A8(void);
extern void fn_80138D6C(void* p);
extern void fn_80006EE0(void* p);
extern void fn_80006A2C(void* p);
extern void fn_80250D64(int a, f32 x, f32 y);
extern void fn_800E4548(void);
extern void fn_80078E24(void* p);
extern int fn_801D09F0(void);
extern void fn_801A6BFC(void);
extern void fn_801C6EAC(const char* a, const char* b, char* out);
extern void fn_800068EC(void* res, const char* path, int flags);
extern f32 fn_8017F68C(int a, f32 x, f32 y, f32 t, f32 d);
extern void fn_80083B78(void* p);
extern void* fn_8009E898(void);
extern void fn_801389C0(void* p, u16 a, int b, void* c);
extern int fn_800C7F90(void);
extern void* fn_80081194(void* cls, void* parent);
extern void* fn_80081050(void* cls, void* parent);
extern void* fn_80078CCC(u32 size, const char* tag, int arg);
extern void memset(void* p, int v, u32 n);
extern void fn_80185720(void);
extern void* fn_80085708(const char* name);
extern void fn_803080DC(int a, int b, int c, int d);

void fn_801A77A0(RProc* p) {
    if (lbl_804CB964->done == 0) {
        fn_80138D6C(fn_8013B9A8());
        if (lbl_804CB964->x334 != NULL) {
            fn_80006EE0(lbl_804CB964->x334);
        }
        if (lbl_804CB964->res != NULL) {
            fn_80006A2C(&lbl_804CB964->res);
        }
        fn_80250D64(6, 1.0f, 250.0f);
        fn_800E4548();
        lbl_804CB964->done = 1;
        fn_80078E24(p->d);
        p->d = NULL;
        lbl_804CB964 = NULL;
        lbl_804CB960 = NULL;
    }
}

void fn_801A7840(void) {
    char path[0x80];
    lbl_804CB964->flags = 0;
    lbl_804CB964->state = 0;
    lbl_804CB964->timer = 0;
    lbl_804CB964->res = NULL;
    lbl_804CB964->x320 = 0;
    lbl_804CB964->x324 = 0;
    lbl_804CB964->x338 = 0;
    lbl_804CB964->x339 = 0;
    lbl_804CB964->x340 = 0;
    if (fn_801D09F0() == 0) {
        lbl_804CB964->x358 = 0x138;
    } else {
        lbl_804CB964->x358 = 0xEE;
    }
    fn_801A6BFC();
    lbl_804CB964->res = NULL;
    fn_801C6EAC(lbl_8036D22C + 0x8C, lbl_8036D22C + 0xA1, path);
    fn_800068EC(&lbl_804CB964->res, path, 0x2080);
}

void fn_801A790C(void) {
    RData* d = lbl_804CB964;
    switch (d->state) {
    case 0:
        if (lbl_804CB700 & 0x8001) {
            d->state = 5;
            lbl_804CB964->timer = 0;
        } else {
            d->timer++;
            lbl_804CB964->x338 = fn_8017F68C(0, 0.0f, 255.0f, lbl_804CB964->timer, 30.0f);
            if (lbl_804CB964->timer >= 30) {
                lbl_804CB964->state = 5;
                lbl_804CB964->timer = 0;
            }
        }
        break;
    case 5:
        break;
    case 10:
        if (lbl_804CB700 & 0x8001) {
            fn_80083B78(d);
        } else {
            d->timer++;
            lbl_804CB964->x338 = fn_8017F68C(0, 255.0f, 0.0f, lbl_804CB964->timer, 30.0f);
            if (lbl_804CB964->timer >= 30) {
                fn_80083B78(lbl_804CB964);
            }
        }
        break;
    }
}

void fn_801A7A80(RProc* p) {
    if (lbl_804CB964->res != NULL) {
        fn_80006A2C(&lbl_804CB964->res);
    }
    fn_800E4548();
    fn_80078E24(p->d);
    p->d = NULL;
    lbl_804CB964 = NULL;
    lbl_804CB960 = NULL;
}

void fn_801A7ADC(void) {
    void* a = fn_8009E898();
    fn_801389C0(fn_8013B9A8(), lbl_804CB964->x358, 0x106, a);
}

void fn_801A7B20(void* parent) {
    if (fn_800C7F90() == 0 && fn_8013B9A8() != NULL) {
        lbl_804CB960 = (RProc*)fn_80081194(lbl_80388DF8, parent);
        lbl_804CB960->d = (RData*)fn_80078CCC(0x35C, lbl_8036D22C + 0x109, 0);
        lbl_804CB964 = lbl_804CB960->d;
        memset(lbl_804CB964, 0, 0x35C);
        fn_80185720();
    }
}

void fn_801A7BB0(void) {
    fn_80081194(lbl_80388ED0, fn_8009E898());
}

void fn_801A7BE0(void* parent) {
    lbl_804CB960 = (RProc*)fn_80081050(lbl_80388E94, parent);
    lbl_804CB960->d = (RData*)fn_80078CCC(0x35C, lbl_8036D22C + 0x109, 0);
    lbl_804CB964 = lbl_804CB960->d;
    memset(lbl_804CB964, 0, 0x35C);
}

void fn_801A7C48(void) {
    RProc* p = (RProc*)fn_80085708(lbl_8036D22C + 0x10A);
    if (p != NULL) {
        p->d->state = 10;
    }
}

void fn_801A7C88(void) {
    RProc* p = (RProc*)fn_80085708(lbl_8036D22C + 0x10A);
    if (p != NULL) {
        p->d->flags |= 1;
    }
}

void fn_801A7CCC(void) {
    RProc* p = (RProc*)fn_80085708(lbl_8036D22C + 0x10A);
    if (p != NULL) {
        p->d->flags |= 4;
    }
}

void fn_801A7D10(void) {
    fn_80138D6C(fn_8013B9A8());
}

void fn_801A7D34(void* unused, s16* r) {
    fn_803080DC(r[0], r[1], r[2], r[3]);
}

}
