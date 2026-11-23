#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {
extern char lbl_8036FBC0[];
extern char lbl_803CAB38[];
extern u32 lbl_803CA870[];
extern VO0N* lbl_804CB5B8;
extern char lbl_8041EB20[];
extern char lbl_8038FA38[];
extern char lbl_8038E1D0[];
extern char lbl_8038C294[];
extern u32 lbl_804CB878;
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4EC;
#else
extern u32 lbl_804CA4EC;
#endif
int fn_800CB0FC(int, f32);
int fn_800CA3DC(const char*, f32, int);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_801E6DA0(int, int, int, const char*, ...);
void* fn_80079150(int);
void fn_802167C8(void*, int, int, int, int, int, int);
void fn_801E5448(void*, void*);
void* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
void fn_801E459C(void*, void*, void*, int);
void fn_801E495C(void*, void*, void*, int);
int fn_801A2224(void*);
void fn_8020291C(void*);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_80253EE4(const char*, f32);
#if TARGET_PC
FE10_PROTO void fn_8014C2AC(p32arg);
#else
void fn_8014C2AC(int);
#endif
void fn_801E40B0(void*, int);
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, u32);
#endif
int fn_8012CA88(void*);
void fn_80128460(void*);
void fn_801038D0(void*, void*);
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void fn_801E4094(void*);
u8 fn_801E7164(void);
#if TARGET_PC
FE10_PROTO void fn_801E7218(ptr32<const void>);
#else
void fn_801E7218(void* p);
#endif
int fn_80060754(void*);
int* fn_801059B0(void);
int fn_80105158(void*);
int fn_8012BDFC(void*);
typedef struct K { u8 pad[8]; s16 x8, xa; u8 pad_c[0x24 - 0xc]; u8 x24; } K;
K* fn_801E041C(const char*, const char*);
void fn_800D5448(void*, void*, int);
typedef struct Pt { s16 x, y; } Pt;
typedef struct LMH { u8 pad[0x64]; const char* x64; } LMH;
#define setHelp(o, e) { \
    const char* s = e; \
    LMH* p = (LMH*)fn_801E5640(o, -0x1000, 0); \
    if (p != NULL) { \
        p->x64 = s; \
    } \
}
typedef struct Msg { u8 pad[0x18]; int x18; u8 pad1c[0x2c - 0x1c]; const char* x2c; u8 pad30[0x3c - 0x30]; const char* x3c; } Msg;
typedef struct Sc { u8 pad[0x40]; void* x40; u8 pad44[4]; Msg* x48; } Sc;

typedef struct WL { u8 pad[0x1e]; s16 x1e, x20; u8 pad22[0x38 - 0x22]; u32 x38; u8 pad3c[4]; const char* x40; const char* x44; } WL;
void fn_80201B64(WL* o) {
    const char* s;
    int x;
    int y;
    ((VO0N*)o)->v18();
    {
        int h = fn_800CB0FC(-1, 1.0f);
        h = 0x1c - h;
        y = ((h + 0x12) >> 1) + o->x20;
        x = o->x1e + 0x67;
    }
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->x38 | 3));
    fn_8007E164();
    s = o->x40;
    if (s != NULL) {
        fn_801E6DA0((s16)(x - ((s16)fn_800CA3DC(s, 1.0f, -1) >> 1)), (s16)y, 0x1f, s);
    }
    s = o->x44;
    if (s != NULL) {
        fn_801E6DA0((s16)(x - ((s16)fn_800CA3DC(s, 1.0f, -1) >> 1)), (s16)(y + 0x1c), 0x1f, s);
    }
}

/* list dtor helpers */
static inline void listFree2(RList* l) {
    if (l != NULL) {
        if (l != NULL) {
            LNode* p = l->next;
            LNode* e = (LNode*)&l->prev;
            if (p != e) {
                LNode* last = e->prev;
                p->prev->next = last->next;
                last->next->prev = p->prev;
                while (p != e) {
                    LNode* t = p;
                    p = p->next;
                    fn_80079210(t);
                    l->size--;
                }
            }
        }
    }
}
void* fn_801FDAF8(RList* l, int del) {
    if (l != NULL) {
        listFree2(l);
        if (del > 0) {
            fn_80079210(l);
        }
    }
    return l;
}
void fn_801FDBB0(RList* l) {
    LNode* e = (LNode*)&l->prev;
    LNode* p = l->next;
    if (p != e) {
        LNode* last = e->prev;
        p->prev->next = last->next;
        last->next->prev = p->prev;
        while (p != e) {
            LNode* t = p;
            p = p->next;
            fn_80079210(t);
            l->size--;
        }
    }
}
void fn_8020446C(RList* l) {
    LNode* e = (LNode*)&l->prev;
    LNode* p = l->next;
    if (p != e) {
        LNode* last = e->prev;
        p->prev->next = last->next;
        last->next->prev = p->prev;
        while (p != e) {
            LNode* t = p;
            p = p->next;
            fn_80079210(t);
            l->size--;
        }
    }
}

typedef struct WH { u8 pad[0xa]; s16 xa, xc, xe, x10, x12, x14, x16, x18; u8 pad1a[4]; s16 x1e, x20; u8 pad22[0x54 - 0x22]; s16 x54, x56; } WH;
static inline s16 wW(WH* w) { return w->xe - w->xa; }
static inline s16 wH(WH* w) { return w->x10 - w->xc; }
static inline void setI(WH* w, s16 a, s16 b, s16 c, s16 d) { w->x12 = a; w->x14 = b; w->x16 = c; w->x18 = d; }
static inline void setI3(WH* w, int a, int b, int c, s16 d) { w->x12 = a; w->x14 = b; w->x16 = c; w->x18 = d; }
void fn_80201F38(WH* o) {
    setI3(o, 0, 4, wW(o), wH(o) - 4);
    o->x1e = 0;
    o->x20 = 0;
}

void fn_802049A0(WH* o) {
    setI(o, 4, 4, wW(o) - 4, wH(o) - 4);
    o->x1e = 0x12;
    o->x20 = 9;
    o->x54 = 0x20;
    o->x56 = 6;
}

static inline void setI2(WH* w, int a, int b, int c, int d) { w->x12 = a; w->x14 = b; w->x16 = c; w->x18 = d; }
void fn_80201CE0(WH* o) {
    setI2(o, 0, 0, wW(o), wH(o));
    o->x1e = 0;
    o->x20 = 0;
}
#define RINIT(fn) void fn(WH* o) { setI2(o, 0, 0, wW(o), wH(o)); o->x1e = 0; o->x20 = 0; }
RINIT(fn_80201D58)
RINIT(fn_80201FBC)
RINIT(fn_80202034)
void fn_801E1BB0(WH* o) {
    setI2(o, 0x20, 0, wW(o), wH(o));
    o->x1e = 0;
    o->x20 = 0;
}
void fn_801E1BEC(WH* o) {
    setI2(o, 0, 0, wW(o), wH(o));
    o->x1e = 0x18;
    o->x20 = 4;
}
typedef struct WH2 { WH w; u8 p58[0x50 - 0x58 + 8]; } WH2;
typedef struct WD { u8 pad[0xa]; s16 xa, xc, xe, x10, x12, x14, x16, x18; u8 pad1a[4]; s16 x1e, x20; u8 pad22[0x50 - 0x22]; VO0N* x50vt; u8 p54[0x5e - 0x54]; s16 x5e, x60, x62; u8 p64[0x86 - 0x64]; s16 x86, x88, x8a; } WD;
void fn_80201DD0(WD* o) {
    s16 w;
    int z = 0;
    setI((WH*)o, z, 4, wW((WH*)o), wH((WH*)o) - 4);
    w = o->x16 - 0x21;
    o->x1e = z;
    o->x20 = z;
    {
        int t = ((VO0N*)&o->x50vt)->v24();
        o->x5e = w;
        o->x60 = -t;
        o->x62 = z;
        o->x86 = w;
        o->x88 = t + (s16)(o->x18 - o->x14);
        o->x8a = z;
    }
}

void fn_80203838(Sc* o) {
    const char* base = lbl_8036FBC0;
    K* w = fn_801E041C(base + 0x44, base + 0x4d);
    w->x8 = 0x180;
    w->xa = 0x1b;
    w->x24 = 1;
    fn_800D5448(w, o, 0);
    setHelp(o, o->x48->x2c);
}

typedef struct LW { void* vt; int rc; s16 x8; s16 xa, xc; u8 pad[0x28 - 0xe]; s16 x28; u8 pad2a[0x70 - 0x2a]; int x70; } LW;
class VW {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(int);
};
void fn_80203DD8(Sc* o) {
    LW* w = (LW*)fn_80079150(0x74);
    if (w != NULL) {
        fn_802167C8(w, 0x12c, 0x66, 0x158, 0xda, 0x1c2, 0);
        w->vt = lbl_8038FA38;
        w->x70 = 0;
        ((VO0N*)w)->v2C();
    }
    w->x8 = 1;
    w->x28 = 8;
    ((VW*)w)->v38(0);
    w->x70 = 1;
    fn_801E5448(o, w);
    setHelp(o, o->x48->x3c);
}

void fn_80203EC4(Sc* o) {
    LW* w = (LW*)fn_801E5640(o, 1, 0);
    ((VW*)w)->v38(0);
    w->x70 = 1;
    if (w->xa != 0xd8) {
        s16 y = w->xc;
        Pt p;
        p.x = 0xd8;
        p.y = y;
        fn_801E459C(o, w, &p, 1);
    }
    fn_801E5734(o, w);
    setHelp(o, o->x48->x3c);
}

void fn_80203F80(Sc* o) {
    LW* w = (LW*)fn_801E5640(o, 1, 0);
    if (inputBlocked()) {
        return;
    }
    if ((lbl_804CB5B8->v48() & 0x1c00) && !fn_801A2224(lbl_8041EB20)) {
        s16 y = w->xc;
        Pt p;
        p.x = 0x12c;
        p.y = y;
        fn_801E495C(o, w, &p, 0);
        fn_8020291C(o);
        fn_80083DC4(o, 5);
        fn_80253EE4(lbl_8036FBC0 + 0x34, 0.0f);
    }
}

void fn_80204064(Sc* o) {
    fn_801E5734(o, fn_801E5640(o, -0x1000, 0));
    if (inputBlocked()) {
        return;
    }
    if (lbl_804CB5B8->v48() & 0xc00) {
        fn_801E5734(o, o->x40);
        fn_8014C2AC(o->x48->x18);
        fn_80253EE4(lbl_8036FBC0 + 0x58, 0.0f);
        fn_80083B78(o);
    }
}

class RO {
public:
    virtual void destroy(int);
    int rc;
};
typedef struct PR { u8 pad[0x40]; RO* x40; } PR;
void fn_802041FC(PR* o) {
    lbl_804CB878 &= ~0x10;
    if (o != NULL) {
        if (o->x40 != NULL) {
            RO* p = o->x40;
            if (--p->rc == 0) {
                if (p != NULL) {
                    p->destroy(1);
                }
            }
            o->x40 = NULL;
        }
        fn_801E40B0(o, 0);
    }
}

void fn_80204284(void* o) {
    void* st;
    u8 f = 0;
    st = (void*)lbl_803CA870[1];
    if (fn_8011B77C((u8*)st + 0x12c, lbl_804CA4EC)) {
        f |= 1;
    }
    if (fn_8012CA88(st)) {
        f |= 2;
    }
    switch (f) {
    case 3:
        fn_80128460(st);
        fn_80083DC4(o, 0xb);
        break;
    case 0: case 1: case 2:
    default:
        fn_801038D0(st, o);
        break;
    }
}

void fn_80204454(RList* l) {
    LNode* e = (LNode*)&l->prev;
    l->size = 0;
    l->next = e;
    l->prev = e;
}

class V18 {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(void*);
};
int fn_802053FC(V18* o, void* a) { return o->v18(a); }
int fn_80205584(V18* o, void* a) { return o->v24(a); }

u8 fn_802056E4(void* u, int n) {
    if (fn_80060754(lbl_803CAB38)) {
        int* g = fn_801059B0();
        n -= *g - fn_80105158(g);
        if (n < 0) {
            n = 0;
        }
    }
    {
        u8 k = 7 - fn_8012BDFC(u);
        u8 r = 0;
        if (k != 0 && n <= k) {
            r = 1;
        }
        return r;
    }
}

class V10 {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14();
};
typedef struct M50 { void* vt; u8 pad[0x28 - 4]; } M50;
typedef struct W50 { u8 pad[0x50]; M50 x50; M50 x78; } W50;
void* fn_80201E94(W50* o, int del) {
    if (o != NULL) {
        {
            M50* m = &o->x78;
            if (m != NULL) {
                if (m != NULL) {
                    o->x78.vt = lbl_8038C294;
                    ((VO0N*)m)->v10();
                }
            }
        }
        {
            M50* m = &o->x50;
            if (m != NULL) {
                if (m != NULL) {
                    o->x50.vt = lbl_8038C294;
                    ((VO0N*)m)->v10();
                }
            }
        }
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}


extern char lbl_803E7290[];
extern char lbl_8036F328[];
#if TARGET_PC
FE10_PROTO char * fn_80110F08(void*);
#else
int fn_80110F08(void*);
#endif
u64* fn_801116B8(void*);
void fn_8007E7B4(void);
void fn_8007E7E8(int);
struct DB { u8 pad[0x44]; };
class DV : public DB {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14();
    virtual int v18(int, int, int);
    virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48();
    virtual int v4C(); virtual int v50();
};
typedef struct UI { u8 pad[0x16]; u16 x16; u8 p18[3]; u8 x1b; } UI;
typedef struct UU { UI* x0; u8 x4; u8 p:2; u8 c:1; u8 b:1; u8 q:4; } UU;
typedef struct WU { u8 pad[0x1e]; s16 x1e, x20; u8 p22[0x38 - 0x22]; u32 x38; u8 p3c[4]; UU* x40; } WU;
static inline void dr2(WU* o, int x, int y2) {
    const char* base = lbl_8036F328;
    fn_801E6DA0((s16)(x + 0xa8), (s16)y2, 0x31, base + 0x66, o->x40->x4);
    fn_801E6DA0((s16)(x + 0xcb), (s16)y2, 0x28, base + 0x6b, o->x40->x0 ? o->x40->x0->x1b : 0);
}
void fn_80200E50(WU* o) {
    ((VO0N*)o)->v18();
    if (o->x40 != NULL) {
        s16 x = o->x1e;
        s16 y = o->x20;
        int dy;
        int col;
        int y2;
        s16 w;
        fn_8007E154();
        fn_8007E720(-1.0f);
        fn_8007E174(0, (u16)(o->x38 | 3));
        fn_8007E164();
        col = 0x31;
        if (o->x40->c) {
            col = 0x32;
        }
        w = ((DV*)lbl_803E7290)->v4C();
        dy = (0x20 - fn_800CB0FC(-1, 1.0f)) >> 1;
        fn_801E6DA0((s16)(x + w), (s16)(y + dy), col, (const char*)fn_80110F08(o->x40));
        if ((*fn_801116B8(o->x40) & 0x1000000000040ULL) == 0 && o->x40->b == 0) {
            y2 = y + ((0x20 - fn_800CB0FC(-1, 1.0f)) >> 1);
            dr2(o, x, y2);
        }
        {
            int d = (0x20 - ((DV*)lbl_803E7290)->v50()) >> 1;
            ((DV*)lbl_803E7290)->v18(x, y + d, (u8)(o->x40->x0 ? o->x40->x0->x16 : 0) + 0x81);
        }
    }
}

class MV {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(int);
    virtual int v30(); virtual int v34(int, int, int, int, int);
};
typedef struct KB2 { u8 pad[0x2d]; u8 x2d; u8 x2e; u8 pad2f[5]; RList l; } KB2;
static inline BOOL kbTest(KB2* a) { return a->x2d != 0 || a->x2e != 0; }
class WS : public MV {
public:
    u8 p4[0x3c];
    int x40;
    int x44;
    s16 x48, x4a;
    u8 x4c;
    u8 p4d[3];
    MV m50;
    u8 p54[8];
    u8 x5c;
    u8 x5d;
    u8 p5e[6];
    s16 x64;
    u8 p66[0x12];
    MV m78;
    u8 p7c[8];
    u8 x84;
    u8 x85;
    u8 p86[6];
    s16 x8c;
};
void fn_80201388(WS* o, KB2* a) {
    ((VO0N*)o)->v18();
    if (o->x40 == 1 && o->x4c != 0 && o->x44 != 0) {
        int sel = 0;
        if (!kbTest(a)) {
            if ((a->l.size != 0 ? a->l.prev->val : NULL) == (RObj*)o) {
                sel = 1;
            }
        }
        if (sel != 0) {
            fn_8007E154();
            fn_8007E720(1.0f);
            fn_8007E164();
            o->v34(0xbc, 0, 0xc, 0x20, sel);
            o->x5c = o->x48 < o->x4a;
            o->x84 = o->x48 > 1;
            o->m50.v2C(0x10);
            o->m78.v2C(0x10);
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E7E8(0x80);
    fn_8007E164();
}

void fn_80201508(WS* o) {
    int k, k2;
    s16 old;
    if (inputBlocked()) {
        return;
    }
    k = lbl_804CB5B8->v3C();
    k2 = lbl_804CB5B8->v48();
    old = o->x48;
    if (k & 0x800008) {
        if (old == o->x4a) {
            if (k == k2) {
                o->x48 = 1;
            }
        } else {
            o->x48 = old + 1;
        }
        if (old != o->x48) {
            o->x5d = 1;
            o->x64 = 0x1e;
        }
    } else if (k & 0x400004) {
        if (old == 1) {
            if (k == k2) {
                o->x48 = o->x4a;
            }
        } else {
            o->x48 = old - 1;
        }
        if (old != o->x48) {
            o->x85 = 1;
            o->x8c = 0x1e;
        }
    }
    if (old != o->x48) {
        fn_80253EE4(lbl_8036F328 + 0x6f, 0.0f);
    }
}

}
