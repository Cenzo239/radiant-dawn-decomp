#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

extern u32 lbl_803CA870[];
extern char lbl_803CAB38[];
extern char lbl_8038D254[];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E8;
#else
extern u32 lbl_804CA4E8;
#endif
extern char lbl_8038DF78[];
extern char lbl_8038DF54[];
extern char lbl_8038DF38[];
extern char lbl_8038DF1C[];
extern char lbl_8038DEFC[];
extern char lbl_8038DEE8[];
extern char lbl_8038DED4[];
extern char lbl_8038DEA0[];
extern char lbl_8038DE84[];
extern char lbl_8038DE5C[];

typedef struct Ent { u8 pad[0x30]; s16 x, y; u8 pad34[5]; u8 x39; } Ent;
typedef struct Pr { u8 pad[0x5c]; void* x5c; } Pr;
void fn_801E6B64(const char*, void*, f32, f32);
void* fn_80083B84(void*);
void fn_800453B4(void*, int);
void fn_80083DC4(void*, int);
void fn_8008319C(void*);
#if TARGET_PC
FE10_PROTO int fn_801F1688(p32arg);
FE10_PROTO int fn_8012C8BC(void*, p32arg);
FE10_PROTO int fn_8012C998(void*, p32arg);
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_801F1688(u32);
int fn_8012C8BC(void*, u32);
int fn_8012C998(void*, u32);
int fn_8011B77C(void*, u32);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_80127648(...);
#else
int fn_80127648(void*);
#endif
#if TARGET_PC
FE10_PROTO struct Inv * fn_8012759C(void*);
#else
int fn_8012759C(void*);
#endif
u32* fn_801116B8(void*);
int fn_80060754(void*);
#if TARGET_PC
FE10_PROTO int fn_801F15A4(p32arg);
#else
int fn_801F15A4(u32);
#endif
int* fn_801059B0(void);
int fn_80105158(void*);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E7DC(int);
void fn_8007E7E8(int);
Ent* fn_80085EF8(int);

#define DRAW2(fn, msg, id, st) \
int fn(void* o, void* a0, Ent* b) { \
    Ent* a = (Ent*)a0; \
    if (b->x39 == 2) { \
        fn_801E6B64(msg, a, (f32)(a->x + b->x), (f32)(a->y + b->y)); \
        return 0; \
    } else { \
        Pr* p = (Pr*)fn_80083B84(lbl_8038D254); \
        fn_800453B4(lbl_803CA870, id); \
        fn_80083DC4(p, st); \
        fn_8008319C(p->x5c); \
        return 4; \
    } \
}
#define DRAW1(fn, msg, id) \
int fn(void* o, void* a0, Ent* b) { \
    Ent* a = (Ent*)a0; \
    if (b->x39 == 2) { \
        fn_801E6B64(msg, a, (f32)(a->x + b->x), (f32)(a->y + b->y)); \
        return 0; \
    } else { \
        fn_800453B4(lbl_803CA870, id); \
        return 6; \
    } \
}

DRAW2(fn_801FC014, lbl_8038DF78, 0x87, 0x2a)

static inline BOOL eq0(int x) { return x == 0; }
int fn_801FC0D8(void) {
    BOOL b = fn_801F1688(lbl_803CA870[0]) == 0;
    int r = 2;
    if (b) {
        r = 0;
    }
    return r;
}

DRAW1(fn_801FC12C, lbl_8038DF54, 0x86)

typedef struct It { u32 a; u8 pad[0x24]; } It;
int fn_801FC1C4(void) {
    It* it;
    u8* u;
    int found = 0;
    int i;
    u = (u8*)lbl_803CA870[0];
    for (i = 0, it = (It*)(u + 0x1bc); i < 7; i++, it++) {
        if (it == NULL || it->a == 0) {
            break;
        }
        if (fn_8012C8BC(u, it->a)) {
            found = 1;
            break;
        }
    }
    {
        int rr = 2;
        if (found) {
            rr = 0;
        }
        return rr;
    }
}

DRAW2(fn_801FC274, lbl_8038DF38, 0x85, 0x16)

int fn_801FC338(void) {
    int r;
    void* st = (void*)lbl_803CA870[0];
    if (fn_8011B77C((u8*)st + 0x12c, lbl_804CA4E8)) {
        r = fn_80127648(st) != 0;
    } else {
        r = 0;
        if (fn_8012759C(st) || fn_80127648(st)) {
            r = 1;
        }
    }
    {
        int rr = 2;
        if (r) {
            rr = 0;
        }
        return rr;
    }
}

DRAW2(fn_801FC3E4, lbl_8038DF1C, 0x84, 0x13)

int fn_801FC4A8(void) {
    It* it;
    u8* u;
    int found = 0;
    int i;
    u = (u8*)lbl_803CA870[0];
    for (i = 0, it = (It*)(u + 0x1bc); i < 7; i++, it++) {
        if (it != NULL && it->a != 0 && !(fn_801116B8(it)[1] & 4)) {
            if (fn_8012C998(u, it->a)) {
                found = 1;
                break;
            }
        }
    }
    {
        int rr = 2;
        if (found) {
            rr = 0;
        }
        return rr;
    }
}

typedef struct OS4 { u32 x0; s8 x4; } OS4;
int fn_801FC570(OS4* o, void* a0, Ent* b) {
    Ent* a = (Ent*)a0;
    if (b->x39 == 2) {
        f32 fx = a->x + b->x;
        f32 fy = a->y + b->y;
        switch (o->x4) {
        case 0:
            fn_801E6B64(lbl_8038DEFC, a, fx, fy);
            break;
        case 1:
            fn_801E6B64(lbl_8038DEE8, a, fx, fy);
            break;
        case 2:
            fn_801E6B64(lbl_8038DED4, a, fx, fy);
            break;
        }
        return 0;
    } else {
        Pr* p = (Pr*)fn_80083B84(lbl_8038D254);
        fn_800453B4(lbl_803CA870, 0x83);
        fn_80083DC4(p, 0x28);
        fn_8008319C(p->x5c);
        return 4;
    }
}

int fn_801FC680(OS4* o) {
    int a;
    if (fn_80060754(lbl_803CAB38) == 0) {
        o->x4 = 0;
        return 2;
    }
    if (fn_801F15A4(lbl_803CA870[0]) != 0) {
        o->x4 = 1;
        return 2;
    }
    a = *fn_801059B0();
    if (a - fn_80105158(fn_801059B0()) <= 0) {
        o->x4 = 2;
        return 2;
    }
    return 0;
}

DRAW1(fn_801FC73C, lbl_8038DEA0, 0x82)
DRAW1(fn_801FC824, lbl_8038DE84, 0x81)
DRAW1(fn_801FC94C, lbl_8038DE5C, 0x80)

s16 fn_801FCEFC(VO4* o) {
    int w = o->v50();
    s16 t = w - (s16)o->v48() * 2;
    return t / 3;
}


typedef struct W3C { u8 pad[0x30]; f32 x30; u8 pad34[8]; struct W3C* x3c; } W3C;
f32 fn_801E33B4(W3C*);
extern char lbl_8038DFF4[];
extern char lbl_8038DFE0[];
extern char lbl_8038DFB4[];
extern char lbl_8038DFA0[];
extern char lbl_8038E038[];
extern char lbl_8038E028[];
extern char lbl_8038E05C[];
extern char lbl_8038E050[];
extern char lbl_804CA9A4[8];
extern char lbl_804CA99C[8];
extern char lbl_804CA998[4];
extern char lbl_804CA9AC[8];
void fn_8008939C(void*);
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
int fn_800CB0FC(int, f32);
int fn_800CA3DC(const char*, f32, int);
int fn_800CA7A4(const char*, f32, int);
const char* fn_800D0864(const char*);
void fn_801E6DA0(int, int, int, const char*, ...);
void fn_800CB278(int, int, int, const char*, ...);
#if TARGET_PC
FE10_PROTO const char* fn_80118C44(p32arg);
#else
const char* fn_80118C44(u32);
#endif
void* fn_801246A4(void*);
void* fn_800C6210(void*, int);
void fn_800C48A8(int, int, int, void*, int);
void fn_800C429C(void*);
void fn_80079210(void*);

typedef struct CF { u8 pad[0x2d]; u8 x2d; u8 x2e; } CF;
static inline BOOL cfT(CF* c) { return c->x2d != 0 || c->x2e != 0; }
void fn_801FCFC0(VO4* o, CF* c) {
    fn_8007E154();
    {
        f32 y;
        f32 w;
        w = o->v70();
        y = (s16)o->v64();
        fn_8007E4E4((s16)o->v60(), y, w, 1.0f);
    }
    fn_8007E7DC(0xff);
    {
        BOOL b = cfT(c);
        int a = 0x40;
        if (!b) {
            a = 0x80;
        }
        fn_8007E7E8(a);
    }
    fn_8007E164();
}

class LLV : public VO4 {};
typedef struct LL {
    u8 pad[0x3c];
    VO4* x3c;
    u8 ids[0x64];
    s8 xa4;
    u8 pada5;
    s8 xa6;
} LL;
#pragma use_lmw_stmw on
void fn_801FD0EC(void* o, LL* l) {
    s8 c;
    int i;
    for (i = 0; i < l->xa4; i++) {
        Ent* e = fn_80085EF8(l->ids[i]);
        c = l->xa4;
        s16 step = (s16)l->x3c->v50() / (c + 1);
        e->x = (i + 1) * step + l->x3c->v48();
        e->y = 4;
    }
}
#pragma use_lmw_stmw off

void fn_801FD198(void* o, LL* l) {
    fn_800453B4(lbl_803CA870, 0);
    while (l->xa6 < l->xa4) {
        if (fn_80085EF8(l->ids[l->xa6])->x39 != 2) {
            break;
        }
        l->xa6++;
    }
    if (l->xa6 >= l->xa4) {
        l->xa6 = 0;
    }
}


#define DRAW3(fn, m0, m1, id) int fn(OS4* o, void* a0, Ent* b) {     Ent* a = (Ent*)a0;     if (b->x39 == 2) {         f32 fx = a->x + b->x;         f32 fy = a->y + b->y;         switch (o->x4) {         case 0:             fn_801E6B64(m0, a, fx, fy);             break;         case 1:             fn_801E6B64(m1, a, fx, fy);             break;         }         return 0;     } else {         fn_800453B4(lbl_803CA870, id);         fn_8008319C(a);         fn_8008939C(a);         return 4;     } }
DRAW3(fn_801FD434, lbl_8038DFF4, lbl_8038DFE0, 0x80)
DRAW3(fn_801FD5AC, lbl_8038DFB4, lbl_8038DFA0, 0x81)

class FB {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C();
    u8 pad4[0x2c];
    f32 x30;
    u32 x34;
    u32 x38;
    W3C* x3c;
    void* x40;
    u32 x44;
};
void fn_801FD718(FB* o, void* a) {
    o->v2C();
    o->v18(a);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->x38 | 3));
    fn_8007E164();
    {
        s16 y = ((0x20 - fn_800CB0FC(-1, 1.0f)) >> 1) + 4;
        fn_801E6DA0(0x108, y, 0x1f, fn_800D0864(lbl_8038E038));
        fn_801E6DA0(0x148, y, 0x1f, lbl_804CA9A4, fn_80105158(fn_801059B0()));
        {
            s16 w = fn_800CA3DC(lbl_804CA99C, 1.0f, -1);
            fn_801E6DA0((s16)(w + 0x148), y, 0xc, lbl_804CA998, *fn_801059B0());
        }
        fn_801E6DA0(0x1ba, y, 0x1f, fn_800D0864(lbl_8038E028));
    }
}

void fn_801FD894(FB* o, void* a) {
    const char* s;
    o->v2C();
    o->v18(a);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->x38 | 3));
    fn_8007E164();
    fn_800CB278(0x33, 0xf, 0x1e, fn_800D0864(lbl_8038E05C));
    if (o->x44 == 0) {
        s = lbl_804CA9AC;
    } else if (o->x40 != NULL) {
        s = fn_80118C44(*(u32*)((u8*)o->x40 + 0xec));
    } else {
        s = fn_800D0864(lbl_8038E050);
    }
    fn_800CA3DC(s, 1.0f, -1);
    {
        int w = fn_800CA3DC(s, 1.0f, -1);
        fn_801E6DA0((s16)(0x4e - (w >> 1)), 0x2c, 0x1f, s);
    }
    if (o->x44 != 0 && o->x40 != NULL) {
        void* m = fn_800C6210(fn_801246A4(o->x40), 0);
        W3C* p0 = o->x3c;
        f32 f0 = o->x30;
        if (p0 != NULL) {
            W3C* p1 = p0->x3c;
            f32 f1 = p0->x30;
            if (p1 != NULL) {
                W3C* p2 = p1->x3c;
                f32 f2 = p1->x30;
                if (p2 != NULL) {
                    W3C* p3 = p2->x3c;
                    f32 f3 = p2->x30;
                    if (p3 != NULL) {
                        f3 = f3 * fn_801E33B4(p3);
                    }
                    f2 = f2 * f3;
                }
                f1 = f1 * f2;
            }
            f0 = f0 * f1;
        }
        fn_800C48A8(0xa3, 0xd, (u8)(int)(255.99f * f0), m, 0);
        fn_800C429C(m);
    }
}

}
