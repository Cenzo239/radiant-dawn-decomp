#include "game/rA_800068A0/types.h"
/* GMaterial.c: whole-material setup. Reset and the tev allocator are inlined copies from fn_80011E28.cpp. */
extern "C" {
extern char lbl_80360D24[];
extern void fn_8001E008(const char* file, int line, const char* msg);
static u32 sTev[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
static u32 sTexMap[8] = {0,1,2,3,4,5,6,7};
static u32 sTexCoord[8] = {0,1,2,3,4,5,6,7};
static u32 sTexMtx[10] = {0x1E,0x21,0x24,0x27,0x2A,0x2D,0x30,0x33,0x36,0x39};
static u32 sInd[4] = {0,1,2,3};
static u32 sD[4] = {1,2,3,0};
static u32 sE[4] = {3,2,1,0};
extern u8 lbl_804CB098;
extern u8 lbl_804CB099;
extern u8 lbl_804CB09A;
extern u8 lbl_804CB09B;
extern u8 lbl_804CB09C;
extern u8 lbl_804CB09D;
extern u8 lbl_804CB09E;
typedef struct GMatLayer {
    u16 flags;
    u8 stage;
    u8 type;
    u8 x4[0x1C - 4];
} GMatLayer;
typedef struct GMaterial {
    u32 x0;
    u16 x4;
    u8 nLayers;
    u8 flags;
    u8 r, g, b;
    u8 xB;
    u8 xC, xD, xE;
    u8 xF[0x13 - 0xF];
    u8 x13;
    GMatLayer* layers;
} GMaterial;
typedef f32 Mtx[3][4];
extern void fn_80019D9C(void* p);
extern void fn_80021CB4(u32 s, u32 a, u32 b, u32 c);
extern void fn_80021D18(u32 s, u32 a, u32 b, u32 c, u32 d, u32 e);
extern void fn_80021E20(u32 s, u32 a, u32 b, u32 c, u32 d);
extern void fn_80021D9C(u32 s, u32 a, u32 b, u32 c, u32 d, u32 e);
extern void fn_80021E8C(u32 s, u32 a, u32 b, u32 c, u32 d);
extern void* fn_8000FB88(void);
extern void fn_80312378(const void* a, const void* b, void* c);
extern void fn_8031258C(const void* a, void* b);
extern void fn_803128AC(void* m, f32 x, f32 y, f32 z);
extern void fn_8031292C(void* m, f32 x, f32 y, f32 z);
extern void fn_80307F10(const void* m, u32 id, u32 type);
extern void fn_80303634(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);

static inline u32 AllocTev(void) {
    if (lbl_804CB098 >= 0x10) {
        fn_8001E008(lbl_80360D24, 0x31, lbl_80360D24 + 0xC);
    }
    return sTev[lbl_804CB098++];
}
static inline u32 LastTev(void) {
    if (lbl_804CB098 == 0) {
        return 0x10;
    }
    return sTev[lbl_804CB098 - 1];
}
static inline u32 LastTexMap(void) {
    if (lbl_804CB099 == 0) {
        return 0xFF;
    }
    return sTexMap[lbl_804CB099 - 1];
}
static inline u32 LastTexCoord(void) {
    if (lbl_804CB09A == 0) {
        return 0xFF;
    }
    return sTexCoord[lbl_804CB09A - 1];
}
static inline u32 AllocTexMtx(void) {
    if (lbl_804CB09B >= 0x3C) {
        fn_8001E008(lbl_80360D24, 0x9C, lbl_80360D24 + 0x5A);
    }
    return sTexMtx[lbl_804CB09B++];
}

typedef struct GXC { u8 r, g, b, a; } GXC;
typedef struct GLightS { u8 x0, x1; GXC amb; u8 pad[0x128-6]; } GLightS;
typedef struct GLightL { u8 x0[4]; GXC col; } GLightL;
typedef struct GObj { u32 flags; u8 pad[0x81-4]; s8 x81; } GObj;
extern GLightS* fn_80010BB0(int i);
extern void fn_80011280(GLightS* s);
extern GLightL* fn_80010DA4(GLightS* s, int t);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_800218A8(int ch, GXC c);
extern void fn_80021958(int ch, GXC c);
static const GXC k0 = {0,0,0,0xFF};
static const GXC k1 = {0,0,0,0xFF};
static const GXC k2 = {0xFF,0xFF,0xFF,0xFF};

typedef struct GObj2 { u32 flags; u8 x4[4]; u8 r, g, b, a; u8 pad[0x58-0xC]; f32 frame; u8 x5c[0x80-0x5C]; u8 x80; } GObj2;
typedef struct GNode2 { u8 x0[0xA]; s16 id; u8 xC[4]; u32 flags; } GNode2;
typedef struct GX2 { u32 x0; } GX2;
extern void fn_8000AB6C(GX2* b, int id, u8* out, f32 frame);
extern void fn_8000A838(GX2* b, int id, int t, GXC* out, f32 frame);
extern void fn_80306DDC(u32 reg, GXC c);
#define ALLOC_TEV(x) \
    if (lbl_804CB098 >= 0x10) { \
        fn_8001E008(lbl_80360D24, 0x31, lbl_80360D24 + 0xC); \
    } \
    x = sTev[lbl_804CB098++];
#define ALLOC_K(x) \
    if (lbl_804CB09D >= 3) { \
        fn_8001E008(lbl_80360D24, 0xDD, lbl_80360D24 + 0x88); \
    } \
    x = sD[lbl_804CB09D++];
static inline u32 AllocK(void) {
    if (lbl_804CB09D >= 3) {
        fn_8001E008(lbl_80360D24, 0xDD, lbl_80360D24 + 0x88);
    }
    return sD[lbl_804CB09D++];
}
static inline u32 kA(u32 i) {
    switch (i) {
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 6;
    default:
        return 0;
    }
}
static inline u32 kB(u32 i) {
    switch (i) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    default:
        return 0;
    }
}
static inline void setE(u32 reg, const GXC& c) {
    fn_80306DDC(reg, c);
}
static inline void setC(u32 reg, const GXC& c) {
    fn_80021958(reg, c);
}
static inline void set4(u32 reg, const GXC& c) {
    GXC t = {c.r, c.g, c.b, c.a};
    fn_80306DDC(reg, t);
}
static inline void set3(u32 reg, int r, int g, int b) {
    GXC t = {r, g, b};
    fn_80306DDC(reg, t);
}
static inline void setF(u32 reg, int r, int g, int b) {
    GXC t = {r, g, b, 0xFF};
    fn_80306DDC(reg, t);
}
#define KA(k, reg) switch (reg) { case 1: k = 2; break; case 2: k = 4; break; case 3: k = 6; break; default: k = 0; break; }

typedef struct GXTexObj { u32 data[8]; } GXTexObj;
typedef struct GXTlutObj { u32 data[3]; } GXTlutObj;
typedef struct GTexPair { void* tex; void* tlut; } GTexPair;
typedef struct GTexRes { u32 x0; u32 x4; GTexPair* table; } GTexRes;
typedef struct GTexDesc { u16 flags; u8 stage; u8 type; u16 index; u16 x6; f32 x8, xC, x10, x14, x18; } GTexDesc;
typedef struct GTexCache { GTexRes* res; GTexDesc* desc; GXTexObj obj; } GTexCache;
extern GTexCache lbl_803B7850;
extern void fn_80006A64(GTexRes* res, GXTexObj* obj, u16 index);
extern void fn_80006B84(GTexRes* res, GXTexObj* obj, GXTlutObj* tlut, u32 name, u32 index);
extern u8 fn_80305E40(GXTexObj* obj);
extern u32 fn_80305E20(GXTexObj* obj);
extern u16 fn_80305E0C(GXTexObj* obj);
extern u16 fn_80305DF8(GXTexObj* obj);
extern void* fn_80305DEC(GXTexObj* obj);
extern void fn_80306054(GXTlutObj* tlut, u32 name);
extern void fn_80305A40(void* obj, void* image, u16 w, u16 h, u32 fmt, u32 wrapS, u32 wrapT, u8 mip);
extern int fn_8000AE38(GX2* b, int id, f32* out, f32 frame);
extern int fn_8000B100(GX2* b, int id, f32* out, f32 frame);
extern int fn_8000B3C8(GX2* b, int id, f32* out, f32 frame);
extern int fn_8000B690(GX2* b, int id, f32* out, f32 frame);
extern int fn_8000B958(GX2* b, int id, f32* out, f32 frame);
extern void fn_80312318(void* m);
extern void fn_80312654(void* m, int axis, f32 a);
extern void fn_80021F7C(u32, int, int, u32);
extern void fn_80022254(void* obj, u32 n);
extern void fn_80021EF8(u32, int);
#define ALLOC_TEX(x) \
    if (lbl_804CB09A >= 8) { \
        fn_8001E008(lbl_80360D24, 0x76, lbl_80360D24 + 0x40); \
    } \
    x = sTexCoord[lbl_804CB09A++];
#define ALLOC_MAP(x) \
    if (lbl_804CB099 >= 8) { \
        fn_8001E008(lbl_80360D24, 0x55, lbl_80360D24 + 0x28); \
    } \
    x = sTexMap[lbl_804CB099++];
#define ALLOC_MTX(x) \
    if (lbl_804CB09B >= 0x3C) { \
        fn_8001E008(lbl_80360D24, 0x9C, lbl_80360D24 + 0x5A); \
    } \
    x = sTexMtx[lbl_804CB09B++];
static inline u32 LastK(void) {
    if (lbl_804CB09D == 0) {
        return 1;
    }
    return sD[lbl_804CB09D - 1];
}
BOOL fn_800125A8(GObj2* a, GX2* b, GNode2* c, GMaterial* m) {
    u32 st1;
    u32 reg1;
    u32 st2;
    int k2;
    u32 st3;
    u32 reg3;
    u32 st4;
    u32 reg4;
    u32 reg2;
    int k3;
    int k4;
    int r2;
    int g2;
    int b2;
    int r3;
    int g3;
    int b3;
    GXC col = {m->r, m->g, m->b, m->xB};
    GXC amb = {m->xC, m->xD, m->xE};
    GXC emi = {0};
    fn_8000AB6C(b, c->id, &col.a, a->frame);
    col.a = col.a * a->a / 255;
    if (m->x4 & 0x4000) {
        col.r = col.g = col.b = col.a;
    }
    if (col.a == 0) {
        return FALSE;
    }
    if (b != 0 && b->x0 != 0) {
        fn_8000A838(b, c->id, 7, &col, a->frame);
        fn_8000A838(b, c->id, 0xE, &amb, a->frame);
        fn_8000A838(b, c->id, 0xF, &emi, a->frame);
    }
    if (a->r < 0x80) {
        col.r = (a->r * col.r) >> 7;
    }
    if (a->g < 0x80) {
        col.g = (a->g * col.g) >> 7;
    }
    if (a->b < 0x80) {
        col.b = (a->b * col.b) >> 7;
    }
    if (!(a->flags & 0x400)) {
        u32 f = c->flags;
        if (((f & 0x1000) && col.r + col.g + col.b != 0x2FD) || ((f & 0x400000) && col.a != 0xFF)) {
            ALLOC_TEV(st1);
            ALLOC_K(reg1);
            set4(reg1, col);
            fn_80021CB4(st1, 0xFF, 0xFF, 0xFF);
            if (c->flags & 0x1000) {
                fn_80021E20(st1, 0xF, 0, kA(reg1), 0xF);
                fn_80021D18(st1, 0, 0, 0, 1, 0);
            } else {
                fn_80021E20(st1, 0xF, 0xF, 0xF, 0);
                fn_80021D18(st1, 0, 0, 0, 1, 0);
            }
            if (c->flags & 0x400000) {
                fn_80021E8C(st1, 7, 0, kB(reg1), 7);
                fn_80021D9C(st1, 0, 0, 0, 1, 0);
            } else {
                fn_80021E8C(st1, 7, 7, 7, 0);
                fn_80021D9C(st1, 0, 0, 0, 1, 0);
            }
        }
    }
    if (a->r > 0x80 || a->g > 0x80 || a->b > 0x80) {
        r2 = ((a->r - 0x80) * 0xFF) >> 7;
        g2 = ((a->g - 0x80) * 0xFF) >> 7;
        b2 = ((a->b - 0x80) * 0xFF) >> 7;
        if (r2 < 0) r2 = 0;
        if (g2 < 0) g2 = 0;
        if (b2 < 0) b2 = 0;
        ALLOC_TEV(st2);
        ALLOC_K(reg2);
        KA(k2, reg2);
        set3(reg2, r2, g2, b2);
        fn_80021CB4(st2, 0xFF, 0xFF, 0xFF);
        fn_80021E20(st2, 0xF, 0xC, k2, 0);
        fn_80021D18(st2, 0, 0, 0, 1, 0);
        fn_80021E8C(st2, 7, 7, 7, 0);
        fn_80021D9C(st2, 0, 0, 0, 1, 0);
    }
    if (amb.r + amb.g + amb.b != 0) {
        r3 = amb.r * 0x7F / 0xFF + 0x80;
        g3 = amb.g * 0x7F / 0xFF + 0x80;
        b3 = amb.b * 0x7F / 0xFF + 0x80;
        ALLOC_TEV(st3);
        ALLOC_K(reg3);
        KA(k3, reg3);
        setF(reg3, r3, g3, b3);
        fn_80021CB4(st3, 0xFF, 0xFF, 0xFF);
        fn_80021E20(st3, 0xF, 0, k3, 0xF);
        fn_80021D18(st3, 0, 0, 1, 1, 0);
        fn_80021E8C(st3, 7, 7, 7, 0);
        fn_80021D9C(st3, 0, 0, 0, 1, 0);
    }
    if (emi.r + emi.g + emi.b != 0) {
        ALLOC_TEV(st4);
        ALLOC_K(reg4);
        KA(k4, reg4);
        setE(reg4, emi);
        fn_80021CB4(st4, 0xFF, 0xFF, 0xFF);
        fn_80021E20(st4, 0xF, 0xC, k4, 0);
        fn_80021D18(st4, 0, 0, 0, 1, 0);
        fn_80021E8C(st4, 7, 7, 7, 0);
        fn_80021D9C(st4, 0, 0, 0, 1, 0);
    }
    if ((a->flags & 0x2000) && col.a == 0xFF && a->a == 0xFF) {
        col.a = a->x80;
    }
    setC(4, col);
    return TRUE;
}
BOOL fn_80012F00(GObj2* a, GX2* b, GNode2* c, GTexDesc* l, GTexRes* e) {
    u32 st;
    u32 tc;
    u32 tmap;
    GXTexObj* obj;
    u32 tm;
    u32 tc2;
    u32 st2;
    int stage;
    Mtx sm;
    Mtx rm;
    Mtx tr;
    Mtx mt;
    GXTlutObj tlut;
    f32 rot, tx, ty, sx, sy;
    ALLOC_TEV(st);
    ALLOC_TEX(tc);
    ALLOC_MAP(tmap);
    tm = 0x3C;
    stage = l->stage;
    if (lbl_803B7850.res == e && lbl_803B7850.desc == l) {
        obj = &lbl_803B7850.obj;
    } else {
        lbl_803B7850.res = e;
        obj = &lbl_803B7850.obj;
        lbl_803B7850.desc = l;
        if (e != NULL) {
            fn_80006A64(e, obj, l->index);
            if (l->flags & 0x20) {
fn_80305A40(obj, fn_80305DEC(obj), fn_80305DF8(obj), fn_80305E0C(obj), fn_80305E20(obj), 1, 1, fn_80305E40(obj));
            }
            if (e->table[l->index].tlut != NULL) {
                fn_80006B84(e, obj, &tlut, 0, l->index);
                fn_80306054(&tlut, 0);
            }
        }
    }
    if (!(c->flags & (0x4000 << (stage - 4)))) {
        stage = 4;
    }
    if ((b == 0 || b->x0 == 0) && (l->flags & 1)) {
        fn_80021F7C(tc, 1, stage, 0x3C);
    } else {
        rot = l->x18;
        tx = l->x8;
        ty = l->xC;
        sx = l->x10;
        sy = l->x14;
        if (b != 0 && b->x0 != 0) {
            fn_8000B3C8(b, c->id, &rot, a->frame);
            fn_8000AE38(b, c->id, &tx, a->frame);
            fn_8000B100(b, c->id, &ty, a->frame);
            fn_8000B690(b, c->id, &sx, a->frame);
            fn_8000B958(b, c->id, &sy, a->frame);
        }
        fn_80312318(mt);
        if (0.0f != rot) {
            fn_803128AC(tr, -0.5f, -0.5f, 0.0f);
            fn_80312654(rm, 0x7A, 0.017453292f * -rot);
            fn_80312378(rm, tr, rm);
            fn_803128AC(tr, 0.5f, 0.5f, 0.0f);
            fn_80312378(tr, rm, mt);
        }
        if (1.0f != sx || 1.0f != sy) {
            fn_803128AC(tr, 0.0f, -1.0f, 0.0f);
            fn_8031292C(sm, sx, sy, 1.0f);
            fn_80312378(sm, tr, sm);
            fn_803128AC(tr, 0.0f, 1.0f, 0.0f);
            fn_80312378(tr, sm, sm);
            fn_80312378(sm, mt, mt);
        }
        if (0.0f != tx || 0.0f != ty) {
            fn_803128AC(tr, tx, -ty, 0.0f);
            fn_80312378(tr, mt, mt);
        }
        ALLOC_MTX(tm);
        fn_80307F10(mt, tm, 1);
        fn_80021F7C(tc, 1, stage, tm);
    }
    fn_80022254(obj, tmap);
    fn_80021CB4(st, tc, tmap, 4);
    switch (l->type) {
    case 0:
        fn_80021EF8(st, 0);
        return FALSE;
    case 1:
        if (st == 0) {
            fn_80021EF8(st, 0);
        } else {
            fn_80021D18(st, 0, 0, 0, 1, 0);
            fn_80021E20(st, 0, 8, 9, 0xF);
            fn_80021D9C(st, 0, 0, 0, 1, 0);
            fn_80021E8C(st, 7, 7, 7, 0);
        }
        break;
    case 2:
        fn_80021D18(st, 0, 0, 0, 1, 0);
        fn_80021E20(st, 0xF, 8, 0, 0xF);
        fn_80021D9C(st, 0, 0, 0, 1, 0);
        fn_80021E8C(st, 7, 7, 7, 0);
        break;
    case 3:
        fn_80021D18(st, 0, 0, 0, 1, 0);
        fn_80021E20(st, 0xF, 0, 8, 0xF);
        fn_80021D9C(st, 0, 0, 0, 1, 0);
        fn_80021E8C(st, 7, 7, 7, 0);
        break;
    case 4:
        fn_80021D18(st, 1, 0, 0, 1, 0);
        fn_80021E20(st, 0xF, 0xC, 8, 0);
        fn_80021D9C(st, 0, 0, 0, 1, 0);
        fn_80021E8C(st, 7, 7, 7, 0);
        break;
    case 5:
        fn_80021D18(st, 0, 0, 0, 1, lbl_804CB09D == 0 ? AllocK() : LastK());
        fn_80021E20(st, 0xF, 0xF, 0xF, 8);
        fn_80021D9C(st, 0, 0, 0, 1, 0);
        fn_80021E8C(st, 7, 7, 7, 0);
        break;
    case 6:
        fn_80021E20(st, 0xF, 8, 0xC, 0);
        fn_80021D18(st, 0, 0, 0, 0, 0);
        fn_80021E8C(st, 7, 7, 7, 0);
        fn_80021D9C(st, 0, 0, 0, 0, 0);
        ALLOC_TEX(tc2);
        ALLOC_TEV(st2);
        fn_80021F7C(tc2, 2, tc2 + 0xB, tm);
        fn_80021CB4(st2, tc2, tmap, 0xFF);
        fn_80021E20(st2, 0xF, 8, 0xC, 0);
        fn_80021D18(st2, 1, 0, 0, 1, 0);
        fn_80021E8C(st2, 7, 7, 7, 0);
        fn_80021D9C(st2, 0, 0, 0, 0, 0);
        break;
    case 7:
        if (st == 0) {
            fn_80021E20(st, 0xF, 0xF, 0xF, 0xA);
            fn_80021D18(st, 0, 0, 0, 1, 0);
            fn_80021E8C(st, 7, 4, 5, 7);
            fn_80021D9C(st, 0, 0, 0, 0, 0);
        } else {
            fn_80021E20(st, 0xF, 0xF, 0xF, 0);
            fn_80021D18(st, 0, 0, 0, 1, 0);
            fn_80021E8C(st, 7, 4, 0, 7);
            fn_80021D9C(st, 0, 0, 0, 0, 0);
        }
        break;
    }
    return TRUE;
}
void fn_8001393C(u32* a, void* b, void* c, GMaterial* m, void* e) {
    u32 s;
    u32 t;
    GMatLayer* l;
    int i;
    u32 tm;
    u32 tc;
    if (m->flags & 0x80) {
        i = 0;
        for (l = m->layers; i < m->nLayers; i++, l++) {
            if (l->type == 6) {
                if (!fn_80012F00((GObj2*)a, (GX2*)b, (GNode2*)c, (GTexDesc*)l, (GTexRes*)e)) {
                    return;
                }
            }
        }
    }
    if (m->flags & 0x20) {
        if (lbl_804CB098 >= 0x10) {
        fn_8001E008(lbl_80360D24, 0x31, lbl_80360D24 + 0xC);
    }
    s = sTev[lbl_804CB098++];
        fn_80021CB4(s, 0xFF, 0xFF, 4);
        fn_80021D18(s, 0, 0, 0, 1, 0);
        fn_80021E20(s, 0xF, 0xA, 0, 0xF);
        fn_80021D9C(s, 0, 0, 0, 1, 0);
        fn_80021E8C(s, 7, 5, 0, 7);
    }
    if (m->x4 & 0x80) {
        Mtx m3, m2, m1, m0;
        if (lbl_804CB09A == 0) {
        tc = 0xFF;
    } else {
    tc = sTexCoord[lbl_804CB09A - 1];
    }
    if (lbl_804CB09B >= 0x3C) {
        fn_8001E008(lbl_80360D24, 0x9C, lbl_80360D24 + 0x5A);
    }
    tm= sTexMtx[lbl_804CB09B++];
        fn_80019D9C(m3);
        fn_80312378(fn_8000FB88(), m3, m3);
        fn_8031258C(m3, m3);
        fn_803128AC(m1, 0.5f, 0.5f, 1.0f);
        fn_8031292C(m2, 0.5f, -0.5f, 0.0f);
        fn_80312378(m1, m2, m0);
        fn_80307F10(m3, tm, 0);
        fn_80307F10(m0, 0x40, 0);
        fn_80303634(tc, 0, 1, tm, 1, 0x40);
    }
    if (*a & 0x400) {
        if (lbl_804CB098 == 0) {
            t = 0x10;
        } else {
            t = sTev[lbl_804CB098 - 1];
        }
        fn_80021CB4(t, LastTexCoord(), LastTexMap(), 4);
        fn_80021D18(t, 0, 0, 0, 1, 0);
        fn_80021E20(t, 0xF, 0xF, 0xF, 0xA);
    }
}
#pragma use_lmw_stmw on
void fn_80013CF0(GObj* a, u8* b, GMaterial* m) {
    BOOL t0, t1, lit, y;
    u32 v;
    if ((*(u16*)(b + 8) & 8) & ~m->flags) {
        return;
    }
    t0 = 0;
    t1 = 0;
    lit = 1;
    y = 0;
    switch (m->x4 & 0x1800) {
    case 0x800:
        lit = 1;
        break;
    case 0x1000:
        lit = 0;
        break;
    case 0x1800:
        y = 1;
        break;
    default:
        if (a->flags & 0x10000) {
            lit = 0;
        }
        break;
    }
    v = *(u32*)(b + 0x10);
    if (v & 0x1000) {
        if (!(a->flags & 0x400)) {
            t0 = 1;
        }
        if (v & 0x400000) {
            t1 = 1;
        }
    }
    if (lit) {
        GLightS* s = fn_80010BB0(a->x81);
        u8 x;
        GXC c;
        fn_80011280(s);
        c = s->amb;
        x = s->x0;
        if (y) {
            GLightL* l;
            x = 0;
            l = fn_80010DA4(s, 1);
            if (l != 0) {
                c.r = (c.r + l->col.r) >> 1;
                c.g = (c.g + l->col.g) >> 1;
                c.b = (c.b + l->col.b) >> 1;
            }
        }
        fn_80021B2C(1);
        fn_80021A08(0, 1, 0, t0, x, 2, 1);
        fn_80021A08(2, 0, 0, t1, 0, 0, 2);
        fn_800218A8(4, c);
        if ((m->x4 & 1) && !(a->flags & 0x400)) {
            u32 st;
            x = s->x1;
            fn_80021B2C(2);
            fn_80021A08(1, 1, 0, 0, x, 0, 0);
            fn_80021A08(3, 0, 0, 0, 0, 0, 2);
            fn_800218A8(5, k0);
            fn_80021958(5, k1);
            st = AllocTev();
            fn_80021CB4(st, 0xFF, 0xFF, 5);
            fn_80021E20(st, 0xF, 0xA, 0xC, 0);
            fn_80021D18(st, 0, 0, 0, 1, 0);
            fn_80021E8C(st, 7, 7, 7, 0);
            fn_80021D9C(st, 0, 0, 0, 1, 0);
        }
    } else {
        fn_80021B2C(1);
        fn_80021A08(0, 0, 0, t0, 0, 2, 2);
        fn_80021A08(2, 0, 0, t1, 0, 0, 2);
        fn_800218A8(4, k2);
    }
}
#pragma use_lmw_stmw off

extern void* fn_80020E74(void);
extern void fn_8001F4D8(int x, int y, int w, int h, int dw, int dh, void* t, int fmt, u8 clr);
extern void fn_8001E51C(f32* a);
extern void fn_803067E0(int, f32*, int);
extern void fn_80306934(u32, int, int);
extern void fn_80306A38(u32, u32, u32);
extern void fn_80306B6C(u32, u32, int, int, int);
extern void fn_80305A40(void* obj, void* image, u16 w, u16 h, u32 fmt, u32 wrapS, u32 wrapT, u8 mip);
extern void fn_80305C94(void* obj, int, int, f32, f32, f32, int, int, int);
extern void fn_8000FEA0(void* c, void* m);
extern void fn_80021F7C(u32, int, int, u32);
extern void fn_80306B24(u32 stage);
extern void fn_80021C74(u32 n);
extern void fn_80021BF4(u32 n);
extern void fn_80021C34(u32 n);
extern BOOL fn_800146A8(u32* a, void* b, GMaterial* m, void* d);
extern BOOL fn_80014760(u32* a, void* b, GMaterial* m, void* d);
extern void fn_80014158(GMaterial* m, void* p);
extern void fn_80013CF0(GObj* a, u8* b, GMaterial* m);
extern void fn_800140A0(u32* a, void* b);

static inline u32 AllocTexMap(void) {
    if (lbl_804CB099 >= 8) {
        fn_8001E008(lbl_80360D24, 0x55, lbl_80360D24 + 0x28);
    }
    return sTexMap[lbl_804CB099++];
}
static inline u32 AllocTexCoord(void) {
    if (lbl_804CB09A >= 8) {
        fn_8001E008(lbl_80360D24, 0x76, lbl_80360D24 + 0x40);
    }
    return sTexCoord[lbl_804CB09A++];
}
static inline u32 AllocInd(void) {
    if (lbl_804CB09C >= 4) {
        fn_8001E008(lbl_80360D24, 0xBB, lbl_80360D24 + 0x73);
    }
    return sInd[lbl_804CB09C++];
}
void fn_80014158(GMaterial* m, void* buf) {
    void* img = fn_80020E74();
    u32 st;
    u32 tc;
    u32 tmap;
    u32 x;
    u32 st2;
    u32 x2;
    u32 tmap2;
    u32 tm2;
    Mtx mt;
    u32 obj[8];
    f32 ind[6];
    fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x260, 0x1C0, img, 4, 0);
    if (m->nLayers != 0) {
        st = LastTev();
        tc = LastTexCoord();
        tmap = LastTexMap();
        x = AllocInd();
        fn_8001E51C(ind);
        fn_803067E0(1, ind, -4);
        fn_80306934(x, 0, 0);
        fn_80306A38(x, tc, tmap);
        fn_80306B6C(st, x, 1, 0, 1);
    }
    st2 = LastTev();
    if (lbl_804CB09A >= 8) {
        fn_8001E008(lbl_80360D24, 0x76, lbl_80360D24 + 0x40);
    }
    x2 = sTexCoord[lbl_804CB09A++];
    if (lbl_804CB09B >= 0x3C) {
        fn_8001E008(lbl_80360D24, 0x9C, lbl_80360D24 + 0x5A);
    }
    tm2 = sTexMtx[lbl_804CB09B++];
    if (lbl_804CB099 >= 8) {
        fn_8001E008(lbl_80360D24, 0x55, lbl_80360D24 + 0x28);
    }
    tmap2 = sTexMap[lbl_804CB099++];
    fn_80305A40(obj, img, 0x260, 0x1C0, 4, 0, 0, 0);
    fn_80305C94(obj, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    fn_80022254(obj, tmap2);
    fn_8000FEA0(0, mt);
    fn_80312378(mt, buf, mt);
    fn_80307F10(mt, tm2, 0);
    fn_80021F7C(x2, 0, 0, tm2);
    fn_80021CB4(st2, x2, tmap2, 4);
    fn_80021EF8(st2, 0);
}

#pragma use_lmw_stmw on
BOOL fn_8001444C(u32* a, void* b, void* c, GMaterial* m, void* e) {
    u32 s;
    int j;
    u32* p;
    GMatLayer* l;
    int i;
    u8 buf[0x38];
    lbl_804CB098 = 0;
    lbl_804CB099 = 0;
    lbl_804CB09A = 0;
    lbl_804CB09B = 0;
    lbl_804CB09D = 0;
    lbl_804CB09E = 0;
    if (lbl_804CB09C != 0) {
        p = sTev;
        for (j = 0; j < 8; j++) {
            fn_80306B24(*p);
            p++;
        }
        fn_80021C74(0);
        lbl_804CB09C = 0;
    }
    if (fn_800146A8(a, c, m, e)) {
        fn_80014760(a, c, m, e);
        fn_80021BF4(lbl_804CB098);
        fn_80021C34(lbl_804CB09A);
        fn_80021C74(lbl_804CB09C);
        return TRUE;
    }
    if ((*a & 0x800) || m->nLayers == 0) {
        if (lbl_804CB098 >= 0x10) {
        fn_8001E008(lbl_80360D24, 0x31, lbl_80360D24 + 0xC);
    }
    s = sTev[lbl_804CB098++];
        fn_80021CB4(s, 0xFF, 0xFF, 4);
        fn_80021EF8(s, 4);
    } else {
        i = 0;
        for (l = m->layers; i < m->nLayers; i++, l++) {
            if (l->type != 6) {
                if (!fn_80012F00((GObj2*)a, (GX2*)b, (GNode2*)c, (GTexDesc*)l, (GTexRes*)e)) {
                    break;
                }
            }
        }
    }
    if (m->x4 & 0x40) {
        fn_80019D9C(buf);
        fn_80014158(m, buf);
    }
    if (!fn_800125A8((GObj2*)a, (GX2*)b, (GNode2*)c, m)) {
        return FALSE;
    }
    fn_80013CF0((GObj*)a, (u8*)c, m);
    fn_800140A0(a, c);
    fn_80014760(a, c, m, e);
    if (!(*a & 0x800)) {
        fn_8001393C(a, b, c, m, e);
    }
    fn_80021BF4(lbl_804CB098);
    fn_80021C34(lbl_804CB09A);
    fn_80021C74(lbl_804CB09C);
    return TRUE;
}
#pragma use_lmw_stmw off
}
