#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {
extern u32 lbl_803CA870[];
extern char lbl_8036F03C[];
extern char lbl_804CA990[8];
extern char lbl_8041EB20[];
extern char lbl_8038E008[];
extern char lbl_8038D690[];
extern VO0N* lbl_804CB5B8;
#if TARGET_PC
FE10_PROTO s8 fn_80127520(p32arg);
FE10_PROTO void fn_80129CB8(p32arg, int);
#else
s8 fn_80127520(u32);
void fn_80129CB8(u32, int);
#endif
#if TARGET_PC
FE10_PROTO void fn_80102C6C(p32arg, char*, int, int, int);
#else
void fn_80102C6C(u32, char*, int, int, int);
#endif
void fn_801EA538(void*, void*);
int fn_801E999C(void*, int);
void fn_801E5448(void*, void*);
void fn_801E459C(void*, void*, void*, int);
void fn_801E495C(void*, void*, void*, int);
void* fn_801E5640(void*, int, int);
void fn_801E5558(void*, void*, int);
void fn_801E5734(void*, void*);
void fn_801E9BE0(void*);
u32* fn_801116B8(void*);
void* fn_801059B0(void);
s16 fn_80105194(void*);
int fn_801051D8(void*, void*);
void fn_80110D38(void*);
void fn_80081194(void*, void*);
void fn_800893AC(void*);
void fn_800D56E8(void*);
void fn_80083174(void*);
int fn_801A2224(void*);
void fn_801A1DCC(void*, void*, f32, f32);
void fn_80253EE4(const char*, f32);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7E8(int);
void fn_800712E8(int, int, int);
void fn_80072ACC(int, int, int, int, int, int, int);
int fn_800CB0FC(int, f32);
int fn_800CA3DC(const char*, f32, int);
int fn_800CA7A4(const char*, f32, int);

typedef struct Pt { s16 x, y; } Pt;
class RO {
public:
    virtual void destroy(int);
    int rc;
};
typedef struct LMH { u8 pad[0x4c]; u8 x4c; u8 p4d; u8 x4e; u8 p4f; s16 x50; u8 p52[0x64 - 0x52]; const char* x64; u8 x68; } LMH;
typedef struct S54 { u8 pad[0x51]; u8 x51; } S54;
typedef struct Q58 { u8 pad[0x40]; int x40, x44; } Q58;
typedef struct Sub { u8 pad[0x40]; void* x40; } Sub;
typedef struct W { u8 pad[0xa]; s16 xa, xc; } W;
typedef struct Proc {
    u8 pad[0x40];
    W* x40;
    Sub* x44;
    u8 p48[4];
    LMH* x4c;
    u8 p50[4];
    S54* x54;
    Q58* x58;
    void* x5c;
} Proc;
typedef struct Proc2 {
    u8 pad[0x40];
    W* x40;
    Sub* x44;
    u8 p48[4];
    LMH* x4c;
    u8 p50[4];
    RO* x54;
    RO* x58;
} Proc2;

static inline void closeList(Proc* o) {
    if (fn_80127520(lbl_803CA870[0]) < 0) {
        fn_80129CB8(lbl_803CA870[0], -1);
    }
    if (lbl_803CA870[0] != 0) {
        fn_80102C6C(lbl_803CA870[0], lbl_804CA990, 4, 0, 0);
    }
    if (o->x44 != NULL && o->x44->x40 != NULL) {
        fn_801EA538(o->x44, o->x44->x40);
    }
}
static inline void resetQ(Q58* q, int z) {
    q->x40 = z;
    q->x44 = z;
    if (z == 0) {
        q->x40 = z;
    }
}



#define RELM(f) if (o->f != NULL) { RO* r = o->f; if (--r->rc == 0) { if (r != NULL) { r->destroy(1); } } o->f = NULL; }
static inline void mvB(Proc2* o, W* const& w, s16 x, s16 y, int f) {
    Pt p;
    p.x = x;
    p.y = y;
    fn_801E495C(o, w, &p, f);
}
void fn_801FAD10(Proc2* o) {
    LMH* m = o->x4c;
    W* w;
    m->x68 = 1;
    m->x4e = 0;
    w = o->x40;
    fn_801E5448(o, w);
    {
        Pt p;
        p.x = w->xa;
        p.y = 0x1c;
        fn_801E459C(o, w, &p, 0);
    }
    {
        s16 y = ((W*)o->x54)->xc;
        Pt p;
        p.x = 0x189;
        p.y = y;
        fn_801E495C(o, o->x54, &p, 1);
    }
    RELM(x54)
    fn_801E5558(o, fn_801E5640(o, 0x10a, 0), 0);
    {
        s16 y = ((W*)o->x58)->xc;
        Pt p;
        p.x = 0x197;
        p.y = y;
        fn_801E495C(o, o->x58, &p, 0);
    }
    RELM(x58)
}

typedef struct It { u32 a; u8 x4; u8 p:5; u8 b:1; u8 q:2; u8 p6[0x22]; } It;
#pragma use_lmw_stmw on
void fn_801FAE74(Proc* o) {
    int t;
    It* it;
    LMH* m;
    int i = 0;
    u8* st = (u8*)lbl_803CA870[0];
    m = o->x4c;
    it = (It*)(st + 0x1bc);
    do {
        if (it->a != 0 && !(fn_801116B8(it)[1] & 4)) {
            t = 1;
            if ((fn_801116B8(it)[0] & 0x1000000) == 0 && it->b == 0) {
                t = 0;
            }
            if (t == 0) {
                if (fn_80105194(fn_801059B0()) < 0) {
                    break;
                }
                if (fn_801051D8(fn_801059B0(), it)) {
                    fn_80110D38(it);
                }
            }
        }
        i++;
        it++;
    } while (i < 7);
    fn_801E9BE0(m);
    m->x50 = fn_801E999C(m, 0);
    lbl_803CA870[1] = 0;
    fn_80081194(lbl_8038D690, o);
}
#pragma use_lmw_stmw off

typedef struct P5C { u8 pad[0xa6]; s8 xa6; } P5C;

class VE {
public:
    virtual int v08(); virtual const char* v0C(); virtual void* v10();
    virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C();
    virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40();
    virtual void v44(void*, void*);
    virtual void v48(void*, void*);
};
typedef struct Ent { u8 pad[0x30]; s16 x, y; VE* x34; } Ent;
Ent* fn_80085EF8(int);
typedef struct LL {
    u8 pad[0x2d];
    u8 x2d;
    u8 x2e;
    u8 p2f;
    s16 x30, x32;
    u8 p34[4];
    s16 x38, x3a;
    VO4* x3c;
    u8 ids[0x64];
    s8 xa4;
    u8 pada5;
    s8 xa6;
    s8 xa7;
} LL;
void fn_801FCAA0(void* o, LL* l) {
    int k;
    if (inputBlocked()) {
        return;
    }
    k = lbl_804CB5B8->v48();
    l->xa7 = l->xa6;
    if (l->xa6 != 0 && (k & 0x100001)) {
        l->xa6--;
    }
    if (l->xa6 != l->xa4 - 1 && (k & 0x200002)) {
        l->xa6++;
    }
    if (l->xa6 != l->xa7 && fn_801A2224(lbl_8041EB20)) {
        Ent* e1 = fn_80085EF8(l->ids[l->xa6]);
        f32 x = l->x30 + e1->x;
        Ent* e2 = fn_80085EF8(l->ids[l->xa6]);
        f32 y = l->x32 + e2->y;
        void* s = fn_80085EF8(l->ids[l->xa6])->x34->v10();
        if (s != NULL) {
            fn_801A1DCC(lbl_8041EB20, s, x, y);
        }
    }
    if (l->xa6 != l->xa7) {
        Ent* e = fn_80085EF8(l->ids[l->xa7]);
        e->x34->v48(l, e);
        e = fn_80085EF8(l->ids[l->xa6]);
        e->x34->v44(l, e);
        fn_80253EE4(lbl_8038E008, 0.0f);
    }
}

static inline BOOL cfT(LL* c) { return c->x2d != 0 || c->x2e != 0; }
static inline int cfA(LL* c) { return c->x2d == 0 && c->x2e == 0; }
void fn_801FCCEC(VO4* o, LL* l) {
    Ent* e = fn_80085EF8(l->ids[l->xa6]);
    s16 x = e->x;
    s16 y = e->y;
    int hw;
    int w2;
    s16 h;
    hw = (s16)fn_800CA3DC(e->x34->v0C(), 1.0f, -1) >> 1;
    x -= hw;
    y += (0x20 - fn_800CA7A4(e->x34->v0C(), 1.0f, -1)) >> 1;
    if (l->x38 < 0 || l->x3a < 0) {
        l->x38 = x;
        l->x3a = y;
    } else {
        l->x38 = (l->x38 + x) / 2;
        l->x3a = (l->x3a + y) / 2;
    }
    fn_8007E154();
    fn_8007E720(-1.0f);
    {
        BOOL b = cfT(l);
        int a = 0x40;
        if (!b) {
            a = 0x80;
        }
        fn_8007E7E8(a);
    }
    fn_8007E164();
    fn_800712E8(l->x38, l->x3a, cfA(l));
    w2 = o->v58();
    h = fn_800CB0FC(-1, 1.0f);
    fn_8007E154();
    fn_8007E720(1.5f);
    fn_8007E164();
    fn_80072ACC(l->x38 + hw, l->x3a + (h >> 1), (s16)w2, 0x17, 0x19, 0x4c, cfA(l));
    fn_8007E154();
    fn_8007E720(-1.5f);
    fn_8007E164();
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
}

}
