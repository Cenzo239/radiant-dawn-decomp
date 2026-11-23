#include "game/rA_800068A0/types.h"
extern "C" {
typedef struct GMat { u8 x0[4]; u16 x4; u8 x6; u8 x7; u8 x8[0x18]; } GMat;
typedef struct GPrim {
    u32 x0;
    struct GPrim* next;
    u16 x8;
    s16 mat;
    s16 node;
    s16 xE;
    u32 x10;
    u32 x14;
    u32 x18;
} GPrim;
typedef struct GMdl { u8 x0[0x24]; void* x24; void* x28; void* x2C; void* x30; GMat* mats; u8 x38[4]; GPrim* x3C; GPrim* x40; GPrim* x44; u8* x48; u8 x4c[0x5C-0x4C]; u8 x5C, x5D, x5E; } GMdl;
typedef struct GNd { u8 x0[8]; void* x8; u32 xC; } GNd;
extern char lbl_80360EEC[];
extern GMdl* fn_80007F3C(u32* a);
extern void* fn_80007F10(u32* a);
extern void* fn_80007F94(u32* a);
extern void* fn_800080B8(u32* a);
extern u32* fn_80007EE4(u32* a);
extern void* fn_80007F68(u32* a);
extern void* fn_80007FC0(u32* a);
extern void* fn_80008060(u32* a);
extern void* fn_8000808C(u32* a);
extern void fn_8000F478(void);
extern void fn_803035E4(int, void*, int);
extern void fn_8001E008(const char* file, int line, const char* msg);
extern void fn_8001D44C(u32* m, void* out);
extern void fn_800184BC(u32* a, int k);
extern void fn_80011838(int);
extern GNd* fn_8000F3D4(u32* m, s32 idx);
extern BOOL fn_8001444C(u32* a, void* b, GPrim* c, GMat* m, void* e);
extern void fn_800186C8(GMat* m);
extern void fn_8001B284(u32* a, GNd* n);
extern void fn_80018F74(u32* a, GPrim* p, u32* m, void* s, void* n);
extern void fn_80019504(u32* a, GPrim* p, u32* m, void* s, void* n);
extern void fn_80021784(int);
extern void fn_80019AB0(u32 fl, u8 a, u8 b, u8 c, int d);
#if TARGET_PC
extern FE10_PROTO void fn_80307B58(p32arg, u32);
#else
extern void fn_80307B58(u32, u32);
#endif
extern BOOL fn_80014818(u32* a, GPrim* p, GMat* m, void* d);
extern void fn_80012268(void);
extern u32* lbl_804CB0A0;
extern GPrim* lbl_804CB0A4;
#if TARGET_PC
/* Host: OSInitFastCast, fe10/gekko.h */
static inline void FastCast(void) { fe10_fastcast_init(); }
#else
static inline void FastCast(void) {
    asm {
        li r3, 4
        oris r3, r3, 4
        mtspr 0x392, r3
        li r3, 5
        oris r3, r3, 5
        mtspr 0x393, r3
        li r3, 6
        oris r3, r3, 6
        mtspr 0x394, r3
        li r3, 7
        oris r3, r3, 7
        mtspr 0x395, r3
    }
}
#endif
static inline BOOL endMat(GMat* m) {
    if (m == NULL) {
        return FALSE;
    }
    if (!(m->x4 & 0xE038)) {
        return FALSE;
    }
    fn_80011838(-1);
    return TRUE;
}
#pragma use_lmw_stmw on
void fn_80018888(u32* a, int k) {
    u32 v;
    void* res;
    void* x94;
    void* xb8;
    u32* mdl;
    void* x68;
    GPrim* p;
    GMat* last;
    u32 fmt;
    BOOL ok;
    GMat* m;
    GMdl* md;
    GNd* n;
    void* xx;
    void* yy;
    int z;
    u8 buf[0x30];
    md = fn_80007F3C(a);
    res = fn_80007F10(a);
    x94 = fn_80007F94(a);
    xb8 = fn_800080B8(a);
    mdl = fn_80007EE4(a);
    x68 = fn_80007F68(a);
    fn_8000F478();
    last = 0;
    fmt = -1;
    ok = 1;
    fn_803035E4(0xD, md->x2C, 4);
    fn_803035E4(0xE, md->x2C, 4);
    fn_803035E4(0xF, md->x2C, 4);
    fn_803035E4(0x10, md->x2C, 4);
    fn_803035E4(0xB, md->x30, 4);
    fn_803035E4(0xC, md->x30, 4);
    FastCast();
    switch (k) {
    case 1:
        p = md->x3C;
        break;
    case 2:
        p = md->x40;
        break;
    case 3:
        p = md->x44;
        break;
    default:
        fn_8001E008(lbl_80360EEC, 0x1E5, lbl_80360EEC + 9);
        break;
    }
    {
        GPrim* q;
        for (q = p; q != 0; q = q->next) {
            q->xE = -1;
        }
    }
    fn_8001D44C(a + 3, buf);
    fn_800184BC(a, k);
    for (; p != 0; p = p->next) {
        m = &md->mats[p->mat];
        if ((m->x7 & 0x10) || (p->x8 & 0x30)) {
            if (endMat(last)) {
                fn_800184BC(a, k);
            }
            last = 0;
            continue;
        }
        if (last != 0 && last->x4 != m->x4) {
            if (endMat(last)) {
                fn_800184BC(a, k);
            }
        }
        lbl_804CB0A0 = a;
        lbl_804CB0A4 = p;
        if ((*mdl & 0x20000000)) {
            n = fn_8000F3D4(mdl, p->node);
            if ((n->xC & 0xC00000) && n->x8 != 0) {
                p->x10 |= 0x401000;
                if (fn_8001444C(a, res, p, m, x68)) {
                    fn_800186C8(m);
                    fn_8001B284(a, n);
                    last = m;
                }
                fmt = -1;
                p->x10 &= ~0x401000;
                continue;
            }
        }
        if (p->x8 & 2) {
            fn_80018F74(a, p, mdl, buf, xb8);
        } else {
            if (p->xE < 0) {
                fn_80019504(a, p, mdl, buf, xb8);
            }
            fn_80021784(p->xE);
        }
        v = p->x10 & 0xFFFFFFF;
        if (fmt != v) {
            fmt = v;
            if (p->x8 & 1) {
                fn_80019AB0(v, md->x48[0xC], 0, md->x5E, 1);
                fn_803035E4(9, fn_80007FC0(a), 0x10);
                if (v & 0x800) {
                    fn_803035E4(0x19, (u8*)fn_80007FC0(a) + 0xC, 0x10);
                } else {
                    fn_803035E4(0xA, (u8*)fn_80007FC0(a) + 0xC, 0x10);
                }
            } else {
                fn_80019AB0(v, md->x5C, md->x5D, md->x5E, 0);
                if (x94 == 0) {
                    fn_803035E4(9, md->x24, 6);
                    if (v & 0x800) {
                        fn_803035E4(0x19, md->x28, 3);
                    } else {
                        fn_803035E4(0xA, md->x28, 3);
                    }
                } else {
                    xx = fn_80008060(a);
                    yy = fn_8000808C(a);
                    fn_803035E4(9, xx, 6);
                    if (v & 0x800) {
                        fn_803035E4(0x19, yy, 3);
                    } else {
                        fn_803035E4(0xA, yy, 3);
                    }
                }
            }
        }
        if (last == 0 || !(p->x8 & 4)) {
            if (last == 0) {
                m->x7 |= 8;
            }
            ok = fn_8001444C(a, res, p, m, x68);
            m->x7 &= ~8;
            fn_800186C8(m);
            last = m;
        }
        if (ok) {
            fn_80307B58(p->x14, p->x18);
        }
        if (fn_80014818(a, p, m, x68)) {
            if (endMat(last)) {
                fn_800184BC(a, k);
            }
            last = 0;
        }
    }
    if (last != 0 && (last->x4 & 0xE038)) {
        fn_80011838(-1);
    }
    if (*a & 0xE00273C0) {
        fn_80011838(-1);
    }
    fn_80012268();
}
#pragma use_lmw_stmw off

typedef struct VD { u32 attr; u32 type; } VD;
typedef struct VF { u32 attr; u32 cnt; u32 comp; u8 frac; } VF;
extern void fn_80021B2C(int);
extern void fn_803031CC(void);
extern void fn_80302DE4(VD*);
extern void fn_803033A0(int, VF*);
#pragma use_lmw_stmw on
void fn_80019AB0(u32 fl, u8 a, u8 b, u8 c, int d) {
    u32 tbl[8] = {0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14};
    VD vd[27];
    VF vf[27];
    VD* pd = vd;
    VF* pf = vf;
    int i;
    if (fl & 1) {
        pd->attr = 0;
        pd->type = 1;
        pd++;
    }
    if (fl & 0x200) {
        pd->attr = 9;
        pd->type = 3;
        pf->attr = 9;
        pf->cnt = 1;
        if (d != 0) {
            pf->comp = 4;
            pf->frac = 0;
        } else {
            pf->comp = 3;
            pf->frac = a;
        }
        pf++;
        pd++;
    }
    if (fl & 0x400) {
        pd->attr = 10;
        pf->attr = 10;
        pd->type = 3;
        pf->cnt = 0;
        if (d != 0) {
            pf->comp = 1;
            pf->frac = 6;
        } else {
            pf->comp = 1;
            pf->frac = b;
        }
        pf++;
        pd++;
    }
    if (fl & 0x800) {
        pd->attr = 0x19;
        pd->type = 3;
        pf->attr = 0x19;
        if (d != 0) {
            pf->comp = 1;
            pf->frac = 6;
            pf->cnt = 1;
        } else {
            pf->cnt = 2;
            pf->comp = 1;
            pf->frac = b;
        }
        pf++;
        pd++;
    }
    if (fl & 0x1000) {
        pf->attr = 0xB;
        pf->cnt = 1;
        pd->attr = 0xB;
        pd->type = 3;
        pf->comp = 5;
        pd++;
        pf->frac = 0;
        pf++;
        fn_80021B2C(1);
    }
    for (i = 0; i < 8; i++) {
        if (fl & (0x4000 << i)) {
            u32 k = tbl[i];
pf->attr = k;
pd->attr = k;
pd->type = 3;
pf->cnt = 1;
pf->comp = 3;
            pd++;
            pf->frac = c;
            pf++;
        }
    }
    pd->attr = 0xFF;
    pf->attr = 0xFF;
    fn_803031CC();
    fn_80302DE4(vd);
    fn_803033A0(0, vf);
}
#pragma use_lmw_stmw off
}
