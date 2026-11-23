/* fn_801A7FDC: class change / level up screen: per-frame state machine (fade in, stat growth one stat at a time with the
 * "up" markers, wait for input, fade out), then the backdrop and the two draw passes. */
#include "game/rF_8017F400/types.h"
#pragma use_lmw_stmw off
extern "C" {
class Pad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
    virtual u32 held(); /* +0x48 */
};
typedef struct UEnt { int st; u8 pad4[0xC]; void* m; } UEnt;
typedef struct UData {
    int x0, x4, x8, xC; /* 0x00 */
    int mode;      /* 0x10 */
    u8* unit;      /* 0x14 */
    void* res;     /* 0x18 */
    u8 stat[11];   /* 0x1C */
    s8 diff[10];   /* 0x27 */
    u8 pad31[3];
    f32 scale[10]; /* 0x34 */
    u32 x5C, x60, x64;
    u8 x68;
    u8 pad69[3];
    u32 x6C;       /* 0x6C */
    UEnt ent[10];  /* 0x70 */
    f32 x138;      /* 0x138 */
    u32 x13C;      /* 0x13C */
} UData;
typedef struct UProc { u8 pad[0x30]; UData* d; } UProc;
typedef struct GNode { u8 pad[8]; s16 x8; u8 padA[0x64 - 0xA]; u8 r, g, b, a; } GNode;
typedef struct GMdl { u8 pad[0x30]; GNode* n; } GMdl;
typedef struct LC4 { u8 r, g, b, a; } LC4;
static s16 sX[10] = { 0x2A, 0x2A, 0x2A, 0x2A, 0xAB, 0xAB, 0xAB, 0xAB, 0x2A, 0xAB };
static s16 sY[10] = { 0x20, 0x42, 0x63, 0x84, 0x20, 0x42, 0x63, 0x84, 0xA5, 0xA5 };
static u8 sOrd[12] = { 0, 1, 2, 3, 8, 4, 5, 6, 7, 9, 0, 0 };
extern Pad* lbl_804CB5B8;
extern char lbl_8036D360[];
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
extern void fn_80253EE4(const char*, f32);
extern GMdl* fn_800E3C04(const char*, void*);
extern void fn_800E48AC(GMdl*, f32, f32, f32);
extern void fn_800E4AD4(GMdl*, f32);
extern void* fn_80193198(void);
extern void fn_8004B120(void*, void*);
extern void fn_800C835C(int, int);
extern void fn_80083B78(void*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_800800D4(int);
extern void fn_80080348(f32, f32, f32, f32);
extern void fn_80080368(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080578(int);
extern void fn_80080308(void);
extern void fn_801A88A4(UData*, f32, f32);
extern void fn_801A8E20(UData*, f32, f32, f32, f32);
static inline void SetC(GNode* n, LC4 c) { n->r = c.r; n->g = c.g; n->b = c.b; n->a = c.a; }
void fn_801A7FDC(UProc* p) {
    /*P*/
    f32 bx;
    f32 by;
    f32 cx;
    f32 cy;
    f32 ay;
    int k;
    UData* d;
    u32 held;
    f32 ax;
    GMdl* m;
    GMdl* m6;
    int o;
    int lim;
/*E*/
    d = p->d;
    held = lbl_804CB5B8->held();
    if (d->mode == 0) { ax = 445.0f; ay = 363.0f; bx = 27.0f; by = 105.0f; cx = 26.0f; cy = 159.0f; }
    if (d->mode == 1) { ax = 445.0f; ay = 361.0f; bx = 20.0f; by = 80.0f; cx = 22.0f; cy = 129.0f; }
    if (d->mode == 2) { ax = 445.0f; ay = 359.0f; bx = 22.0f; by = 76.0f; cx = 23.0f; cy = 126.0f; }
    if (d->x4 >= 9 && (held & 0xFFF0)) d->x0 |= 1;
    switch (d->x4) {
    case 0:
        d->x4 = 1;
        d->xC = 0;
        break;
    case 1:
        if (++d->xC >= 20) { d->x4 = 2; d->xC = 0; }
        break;
    case 2:
        ax = fn_8017F68C(4, ax, ax, ++d->xC, 10.0f);
        d->x68 = fn_8017F68C(0, 0.0f, 255.0f, d->xC, 15.0f);
        if (d->xC >= 15) { d->x4 = 5; d->xC = 0; }
        break;
    case 5:
        if (++d->xC >= 30) {
            if (d->mode == 0) { d->x4 = 6; d->xC = 0; }
            else { d->x4 = 7; d->xC = 0; fn_80253EE4(lbl_8036D360 + 0x18, 0.0f); }
        }
        break;
    case 6: {
        fn_80253EE4(lbl_8036D360 + 0x2E, 0.0f);
        m6 = fn_800E3C04(lbl_8036D360 + 0x3D, p);
        fn_800E48AC(m6, 255.0f + bx, 23.0f + by, 0.0f);
        m6->n->x8 = 0;
        d->x5C = 0x3C;
        d->x60 = 0x41;
        d->x64 = 0x46;
        d->x4 = 9;
        d->xC = 0x23;
        d->stat[0]++;
        break;
    }
    case 7:
        d->x138 = fn_8017F68C(0, 1.0f, 0.0f, ++d->xC, 10.0f);
        if (d->xC >= 10) {
            d->x4 = 8;
            d->xC = 0;
            d->stat[0] = 1;
            d->x13C = *(u32*)(d->x13C + 0x14);
        }
        break;
    case 8:
        d->x138 = fn_8017F68C(0, 0.0f, 1.0f, ++d->xC, 10.0f);
        if (d->xC >= 10) { d->x4 = 9; d->xC = 0x19; }
        break;
    case 9:
        if (--d->xC <= 0) { d->x4 = 10; d->xC = 0; }
        break;
    case 10:
    next:
        for (;;) {
            if (d->x8 >= 10) { d->x4 = 0x13; goto end; }
            o = sOrd[d->x8];
            lim = d->mode == 0 ? 8 : 10;
            if (o < lim && d->diff[o] != 0) {
                d->x4 = 0xF;
                d->xC = 0;
                if (!(d->x0 & 1)) goto end;
                break;
            }
            d->x8++;
        }
    case 15:
    c15: {
        k = sOrd[d->x8];
        if (!(d->x0 & 2)) fn_80253EE4(lbl_8036D360 + 0x48, 0.0f);
        if (d->x0 & 1) d->x0 |= 2;
        m = fn_800E3C04(lbl_8036D360 + 0x3D, p);
        fn_800E48AC(m, 52.0f + (cx + sX[k]), 12.0f + (cy + sY[k]), 0.0f);
        m->n->x8 = 0;
        d->ent[k].st = 5;
        m = fn_800E3C04(lbl_8036D360 + 0x5E, p);
        d->ent[k].m = m;
        fn_800E48AC(m, 105.0f + (cx + sX[k]), 7.0f + (cy + sY[k]), 0.0f);
        m->n->x8 = 0;
        fn_800E4AD4(m, 0.05f);
        {
            LC4 c;
            c.r = m->n->r; c.g = m->n->g; c.b = m->n->b; c.a = 0xFF;
            SetC(m->n, c);
        }
        d->x4 = 0x10;
        d->xC = 0;
        d->scale[k] = 2.0f;
        if (d->x0 & 1) {
            d->x4 = 10;
            d->x8++;
            d->xC = 0;
            goto next;
        }
        break;
    }
    case 16:
        if (++d->xC >= 20 || (d->x0 & 1)) {
            d->x4 = 10;
            d->x8++;
            d->xC = 0;
        }
        break;
    case 19:
        d->xC++;
        switch (d->mode) {
        case 1:
        case 2:
            if (d->xC >= 1200 || (d->xC >= 20 && (held & 0xFFF0))) { d->xC = 0; d->x4 = 0x14; }
            break;
        case 0:
            if (d->xC >= 180 || (d->xC >= 20 && (held & 0xFFF0))) { d->xC = 0; d->x4 = 0x14; }
            break;
        }
        break;
    case 20:
        fn_8004B120(fn_80193198(), p);
        d->x4 = 0x15;
        break;
    case 21:
        ax = fn_8017F68C(4, ax, ax, ++d->xC, 10.0f);
        if (d->xC >= 10) {
            d->x4 = 0x19;
            d->xC = 0;
            if (d->mode) fn_800C835C(3, 500);
        }
        break;
    case 25:
        d->xC++;
        if (d->mode == 0) d->x68 = fn_8017F68C(0, 255.0f, 0.0f, d->xC > 15 ? 15 : d->xC, 15.0f);
        else d->x68 = 0xFF;
        if (d->xC >= 30) fn_80083B78(p);
        break;
    }
end:
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 8.0f, 1.0f);
    fn_8007E7DC(d->x68);
    fn_8007E164();
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080348(0.0f, 0.0f, 0.0f, 0.0f);
    fn_80080368(608.0f, 448.0f, 0.0f, 0.0f);
    fn_800804D4(0, 0, 0, 0x40);
    fn_80080578(0);
    fn_80080308();
    fn_801A88A4(d, ax, ay);
    fn_801A8E20(d, bx, by, cx, cy);
}
}
