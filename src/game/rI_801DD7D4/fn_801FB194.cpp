#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

extern u32 lbl_803CA870[];
extern char lbl_803CAB38[];
extern char lbl_8036F03C[];
extern char lbl_8038D254[];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4EC;
#else
extern u32 lbl_804CA4EC;
#endif
extern char lbl_804CA990[8];

typedef struct Cls { u32 x0; u32 x4; } Cls;
Cls* fn_801116B8(void*);
int fn_801E999C(void*, int);
void fn_801E5734(void*, void*);
void* fn_801E5640(void*, int, int);
void fn_800893AC(void*);
void fn_800D56E8(void*);
void fn_80083174(void*);
void* fn_80060728(void*);
#if TARGET_PC
FE10_PROTO void fn_801E7938(void*, p32arg);
#else
void fn_801E7938(void*, int);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_801E7A28(void*);
#else
int fn_801E7A28(void*);
#endif
void fn_801EA538(void*, void*);
void fn_80083DC4(void*, int);
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, u32);
#endif
int fn_8012CA88(void*);
void fn_80128460(void*);
void fn_801038D0(void*, void*);
#if TARGET_PC
FE10_PROTO void fn_80102C6C(p32arg, char*, int, int, int);
#else
void fn_80102C6C(u32, char*, int, int, int);
#endif
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void* fn_80083B84(void*);
void fn_801E4094(void*);

typedef struct UnitH { u32 x0; u8 x4; u8 h:1; u8 p:2; u8 b:1; u8 q:4; } UnitH;
class LM4 {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(int);
};
typedef struct LM {
    u8 pad[0x4c];
    u8 x4c;
    u8 pad4d[3];
    s16 x50;
    u8 pad52[0x64 - 0x52];
    const char* x64;
    u8 pad68[0x74-0x68];
    void* x74;
    u32 x78;
} LM;
typedef struct P5C { u8 pad[0xa6]; s8 xa6; } P5C;
typedef struct Sub { u8 pad[0x40]; void* x40; } Sub;
typedef struct Proc {
    u8 pad[0x18];
    struct Proc* x18;
    u8 pad1c[0x40-0x1c];
    void* x40;
    Sub* x44;
    u8 pad48[4];
    LM* x4c;
    LM4* x50;
    u32 x54;
    u32 x58;
    P5C* x5c;
    u32 x60;
    s8 x64;
    u8 pad65[3];
    void* x68;
    u8 x6c;
} Proc;


static inline void setF(LM* m, void* f, u32 a) {
    m->x74 = f;
    m->x78 = a;
}

void fn_801FB758(Proc* o) {
    P5C* u = o->x5c;
    int t;
    fn_800893AC(u);
    t = u->xa6;
    fn_800D56E8(u);
    u->xa6 = t;
    fn_80083174(o->x5c);
    {
        LM* m = o->x4c;
        m->x4c = 0;
        m->x74 = NULL;
        m->x78 = 0;
        m->x50 = fn_801E999C(m, 0);
        fn_801E5734(o, m);
    }
}

static inline void applySel(Proc* o, void* w) {
    switch (o->x6c) {
    case 0xb:
        o->x50->v34(fn_801E7A28(w));
        break;
    default:
        ((LM4*)o->x4c)->v34(fn_801E7A28(w));
        fn_801EA538(o->x44, (void*)fn_801E7A28(w));
        break;
    }
}

void fn_801FB7F0(Proc* o) {
    void* w = o->x40;
    fn_801E7938(w, *(int*)((u8*)fn_80060728(lbl_803CAB38) + 0x24));
    applySel(o, w);
}

void fn_801FB8A8(Proc* o) {
    void* w = o->x40;
    fn_801E7938(w, *(int*)((u8*)fn_80060728(lbl_803CAB38) + 0x28));
    applySel(o, w);
    fn_80083DC4(o, o->x6c);
}

void fn_801FB96C(void* o) {
    void* st;
    u8 f = 0;
    st = (void*)lbl_803CA870[0];
    if (fn_8011B77C((u8*)st + 0x12c, lbl_804CA4EC)) {
        f |= 1;
    }
    if (fn_8012CA88(st)) {
        f |= 2;
    }
    switch (f) {
    case 3:
        fn_80128460(st);
        fn_80083DC4(o, 0x31);
        break;
    case 0: case 1: case 2:
    default:
        fn_801038D0(st, o);
        break;
    }
}

void fn_801FBA24(Proc* o) {
    Proc* q = o->x18;
    if (lbl_803CA870[0] != 0) {
        fn_80102C6C(lbl_803CA870[0], lbl_804CA990, 4, 0, 0);
    }
    if (q->x44 != NULL && q->x44->x40 != NULL) {
        fn_801EA538(q->x44, q->x44->x40);
    }
}
void fn_801FBBC8(Proc* o) {
    Proc* q = o->x18;
    if (lbl_803CA870[0] != 0) {
        fn_80102C6C(lbl_803CA870[0], lbl_804CA990, 4, 0, 0);
    }
    if (q->x44 != NULL && q->x44->x40 != NULL) {
        fn_801EA538(q->x44, q->x44->x40);
    }
}

static inline Proc* mkP(void* parent) {
    Proc* p;
    if (parent != NULL) {
        p = (Proc*)fn_80081194(lbl_8038D254, parent);
    } else {
        p = (Proc*)fn_80081050(lbl_8038D254, parent);
    }
    if (p != NULL) {
        fn_801E4094(p);
        p->x40 = NULL;
        p->x44 = NULL;
        *(u32*)&p->pad48 = 0;
        p->x4c = NULL;
        p->x50 = NULL;
        p->x54 = 0;
        p->x58 = 0;
        p->x5c = NULL;
        p->x60 = 0;
        p->x64 = -1;
        p->x68 = NULL;
    }
    return p;
}

Proc* fn_801FBE14(void* parent) {
    return mkP(parent);
}

void fn_801FBF08(void) {
    Proc* p = (Proc*)fn_80083B84(lbl_8038D254);
    if (p != NULL) {
        Sub* s = p->x44;
        void* a = p->x68;
        if (s != NULL) {
            fn_801EA538(s, a);
        }
        p->x68 = NULL;
    }
}

Proc* fn_801FBF64(void* parent) {
    Proc* p = mkP(parent);
    p->x64 = 6;
    fn_80083DC4(p, 0x1d);
    return p;
}


extern void* lbl_804CB5B8;
extern char lbl_8041EB20[];
void* fn_801E9B28(void*);
void fn_801E5954(void*);
int fn_801A2224(void*);
void fn_801A1F64(void*, void*, f32, f32);
void fn_801A1CFC(void*);
void fn_801A1BE0(void*, void*, void*, f32, f32);
void* fn_801E0274(const char*);
void fn_800D5448(void*, void*, int);
void fn_80083B78(void*);
void fn_80253EE4(const char*, f32);
#if TARGET_PC
FE10_PROTO s8 fn_80127520(p32arg);
FE10_PROTO void fn_80129CB8(p32arg, int);
#else
s8 fn_80127520(u32);
void fn_80129CB8(u32, int);
#endif
void fn_800453B4(void*, int);
void fn_8008939C(void*);
void fn_80110D38(void*);
void fn_801E9BE0(void*);
int fn_801E9914(void*, int);
extern char lbl_8038D668[];
void fn_801E40B0(void*, int);

typedef struct RS { u32 x0; u32 x4; u32 x8; u8 xc; u8 xd; u8 xe; } RS;

#pragma use_lmw_stmw on
void fn_801FB560(Proc* o) {
    #define s ((RS*)lbl_803CA870)
    switch (s->xc) {
    case 0x81: {
        UnitH* u;
        LM* m = o->x4c;
        u = (UnitH*)fn_801E9B28(m);
        if (u != NULL) {
            s->x4 = lbl_803CA870[0];
            fn_800453B4(s, 5);
            s->xe = m->x50;
            if (u->h && (fn_801116B8(u)->x0 & 0x100) && (*(u32*)((u8*)lbl_803CA870[0] + 0x10c) & 0x800000)) {
                u->h = 0;
                fn_80081194(lbl_8038D668, o);
            }
            fn_80110D38(u);
        }
        break;
    }
    case 0x80:
        fn_80083DC4(o, 0x2b);
        break;
    }
    {
        const char* s2 = lbl_8036F03C + 0x252;
        LM* p = (LM*)fn_801E5640(o, -0x1000, 0);
        if (p != NULL) {
            p->x64 = s2;
        }
    }
}

#pragma use_lmw_stmw off
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
    fn_80083DC4(o, 0x2c);
}

void fn_801FB668(Proc* o) {
    s16 cur;
    LM* m;
    int r;
    m = o->x4c;
    cur = m->x50;
    fn_801E9BE0(m);
    r = fn_801E9914(m, cur);
    if ((s16)r < 0) {
        r = fn_801E999C(m, cur);
    }
    if ((s16)r >= 0) {
        m->x50 = r;
        fn_80083DC4(o, 0x2b);
    } else {
        closeList(o);
    }
}

class RO {
public:
    virtual void destroy(int);
    int rc;
};
static inline void rel(RO* p) {
    if (--p->rc == 0) {
        if (p != NULL) {
            p->destroy(1);
        }
    }
}
#define REL(f) if (o->f != NULL) { rel(o->f); o->f = NULL; }
typedef struct PR { u8 pad[0x40]; RO* x40; RO* x44; RO* x48; RO* x4c; RO* x50; RO* x54; RO* x58; } PR;
void fn_801FBC34(PR* o) {
    if (o != NULL) {
        REL(x40)
        REL(x44)
        REL(x48)
        REL(x4c)
        REL(x50)
        REL(x54)
        REL(x58)
        fn_801E40B0(o, 0);
    }
}


#undef s
typedef struct Pt { s16 x, y; } Pt;
class WV {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual u32 v30();
};
static inline Pt wpos(WV* a) { u32 r = a->v30(); Pt p0; p0.x = r >> 16; p0.y = r; return p0; }
void fn_801E6B64(const char*, void*, f32, f32);
typedef struct K24 { u8 pad[0x24]; u8 x24; } K24;
static inline void setHelp(void* o, const char* const& s) {
    LM* p = (LM*)fn_801E5640(o, -0x1000, 0);
    if (p != NULL) {
        p->x64 = s;
    }
}
void fn_801FB194(Proc* o) {
    LM* m = o->x4c;
    UnitH* cur = (UnitH*)fn_801E9B28(m);
    u32 k;
    fn_801E5954(o);
    if (cur != fn_801E9B28(m)) {
        cur = (UnitH*)fn_801E9B28(m);
        if (fn_801A2224(lbl_8041EB20)) {
            if (cur != NULL) {
                Pt p = wpos((WV*)m);
                fn_801A1F64(lbl_8041EB20, cur, p.x, p.y);
            } else {
                fn_801A1CFC(lbl_8041EB20);
            }
        }
    }
    if (inputBlocked()) {
        return;
    }
    k = ((VO0N*)lbl_804CB5B8)->v48();
    if ((k & 0x400) && cur != NULL && !fn_801A2224(lbl_8041EB20)) {
        int t = 1;
        if ((fn_801116B8(cur)->x0 & 0x20000) == 0 && cur->b == 0) {
            t = 0;
        }
        if (t != 0 || (fn_801116B8(cur)->x4 & 4)) {
            Pt p = wpos((WV*)m);
            fn_801E6B64(lbl_8036F03C + 0x26b, o, p.x, p.y);
        } else {
            K24* w = (K24*)fn_801E0274(lbl_8036F03C + 0x278);
            w->x24 = 1;
            fn_800D5448(w, o, 0);
            setHelp(o, lbl_8036F03C + 0x1a8);
            fn_80083B78(o);
            fn_80253EE4(lbl_8036F03C + 0x2b, 0.0f);
        }
    } else if ((k & 0x2000) && !fn_801A2224(lbl_8041EB20) && cur != NULL) {
        Pt p = wpos((WV*)m);
        fn_801A1BE0(lbl_8041EB20, o, cur, p.x, p.y);
        *(u32*)lbl_8041EB20 |= 2;
    } else if ((k & 0x2800) && fn_801A2224(lbl_8041EB20)) {
        fn_801A1CFC(lbl_8041EB20);
    } else if ((k & 0x800) && !fn_801A2224(lbl_8041EB20)) {
        closeList(o);
        fn_80253EE4(lbl_8036F03C + 0x3b, 0.0f);
    }
}

}
