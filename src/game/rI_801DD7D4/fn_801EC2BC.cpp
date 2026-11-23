#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {

extern char lbl_8038D138[];
extern char lbl_8038D170[];
extern char lbl_8038D1E0[];
extern char lbl_8038D1C4[];
extern char lbl_8038D1A8[];
extern void* lbl_804CBE3C;
extern void* lbl_804CBE40;
void fn_8028C0D0(void*, void*, int, int);
void* fn_801E2E00(void*, int);
void* fn_80081194(void*, void*);
void fn_801E4094(void*);
void fn_801E5448(void*, void*);
void fn_80072ACC(int, int, int, int, int, int, int);
void fn_801D870C(int, int, int, int);
void fn_801D8ADC(int, int, int, int);
#if TARGET_PC
FE10_PROTO void fn_80107C80(void*, ptr32<const void>, int, int);
#else
void fn_80107C80(void*, void*, int, int);
#endif
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
u32* fn_801E2204(void*, s16*, s16*);
void* fn_801ECD88(RList*, int);
void* fn_801EDEE4(RList*, int);
void* fn_801EEEEC(RList*, int);

void* fn_801EC2BC(u8* o, int del) {
    if (o != NULL) {
        if (o != NULL) {
            fn_8028C0D0(o + 0x88, fn_801ECD88, 0xc, 8);
            fn_801E2E00(o, 0);
        }
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}

class Win {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30(void*);
    virtual int v34();
    virtual void v38();
    virtual int v3C();
    virtual int v40();
    virtual int v44();
    u8 pad4[6];
    s16 xa, xc, xe, x10;
    s16 x12, x14, x16, x18;
    u8 pad1a[4];
    s16 x1e, x20;
    u8 pad22[0x50 - 0x22];
    u8 x50;
};

typedef struct PTw { u8 pad[0x42]; s16 x42; int x44; int x48; } PTw;

void fn_801EC334(Win* o, void* a, int b, int c) {
    if (b != o->v34()) {
        PTw* p = (PTw*)fn_80081194(lbl_8038D138, a);
        if (p != NULL) {
            fn_801E4094(p);
        }
        fn_801E5448(p, o);
        o->x50 = 1;
        p->x42 = 4;
        p->x44 = b;
        p->x48 = c;
    }
}

void* fn_801EC3DC(u8* o) { return *(void**)(*(u8**)(o + 0xac) + 0x40); }
void fn_801EC3E8(Win* o) { o->v30(lbl_804CBE3C); }
void fn_801EC3FC(u8* o, void* v) {
    *(void**)(*(u8**)(o + 0xac) + 0x40) = v;
    lbl_804CBE3C = v;
}
void fn_801EC40C(u8* o, f32 v) { *(f32*)(o + 0xa8) = v; }

void* fn_801EC7D0(u8* o, int del) {
    if (o != NULL) {
        if (o != NULL) {
            fn_8028C0D0(o + 0x74, fn_801EDEE4, 0xc, 3);
            fn_801E2E00(o, 0);
        }
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}

void fn_801EC848(Win* o, void* a, int b, int c) {
    if (b != o->v34()) {
        PTw* p = (PTw*)fn_80081194(lbl_8038D170, a);
        if (p != NULL) {
            fn_801E4094(p);
        }
        fn_801E5448(p, o);
        o->x50 = 1;
        p->x42 = 4;
        p->x44 = b;
        p->x48 = c;
    }
}

void* fn_801EC8F0(u8* o) { return *(void**)(*(u8**)(o + 0xdc) + 0x40); }
void fn_801EC8FC(Win* o) { o->v30(lbl_804CBE40); }
void fn_801EC910(u8* o, void* v) {
    *(void**)(*(u8**)(o + 0xdc) + 0x40) = v;
    lbl_804CBE40 = v;
}
void fn_801EC920(u8* o, f32 v) { *(f32*)(o + 0xd8) = v; }

void* fn_801ECD10(u8* o, int del) {
    if (o != NULL) {
        if (o != NULL) {
            fn_8028C0D0(o + 0x80, fn_801EEEEC, 0xc, 6);
            fn_801E2E00(o, 0);
        }
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}

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

#define LIST_DTOR(name) \
void* name(RList* l, int del) { \
    if (l != NULL) { \
        listFree2(l); \
        if (del > 0) { \
            fn_80079210(l); \
        } \
    } \
    return l; \
}

LIST_DTOR(fn_801ECD88)

typedef struct IType { u8 pad[0x12]; u8 x12; } IType;
typedef struct IEnt { IType* x0; u8 pad[0x26 - 4]; u8 x26; } IEnt;

static inline u8 entType(IEnt* e) {
    return e->x0 ? e->x0->x12 : 0x13;
}

int fn_801ECE40(void* o, IEnt* e) {
    switch (entType(e)) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
    case 0xd:
        return 3;
    case 4:
        return 4;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        return 5;
    case 0xb:
        return 6;
    case 0xe:
    case 0xf:
    case 0x10:
        return 7;
    }
    return 9;
}

int fn_801ECEC0(void* o, IEnt* e) {
    if (e->x26 != 0xff) {
        return 2;
    }
    switch (entType(e)) {
    case 0xb:
        return 0;
    case 0xe:
    case 0xf:
    case 0x10:
        return 1;
    }
    return 4;
}

int fn_801ECF24(void* o, IEnt* e) {
    switch (entType(e)) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
    case 0xd:
        return 3;
    case 4:
        return 4;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        return 5;
    }
    return 7;
}

#define MENU_POS(name, off) \
u32 name(Win* o) { \
    s16 q[2]; \
    s16 p[2]; \
    int t = o->v34(); \
    p[0] = o->x1e; \
    p[1] = (s16)(((s16*)((u8*)o + off))[t] - ((s16*)((u8*)o + 0x58))[t]) * 0x1c + o->x20; \
    return *fn_801E2204(o, q, p); \
}


#define MENU_CB(name, f, a) \
BOOL name(u8* o, void* x) { \
    u8 (*fp)(void*, void*) = *(u8 (**)(void*, void*))(o + f); \
    if (fp != NULL) { \
        return fp(x, *(void**)(o + a)) != 0; \
    } \
    return 1; \
}

MENU_CB(fn_801ED0E8, 0xf0, 0xf4)

#define MENU_DRAW(name) \
void name(Win* o, int x, int y, int d, void** p, void* k) { \
    int w; \
    fn_80107C80(*p, k, x, y); \
    fn_8007E154(); \
    fn_8007E720(1.8f); \
    fn_8007E164(); \
    w = o->x1e; \
    w = (s16)(o->v3C() - w * 2); \
    fn_801D8ADC(x, (s16)(y + o->v40() - 10), w, 0x10); \
    fn_8007E154(); \
    fn_8007E720(-1.8f); \
    fn_8007E164(); \
}

MENU_DRAW(fn_801ED13C)

void fn_801ED20C(void* o, int x, int y, int w, int h, int k) {
    fn_80072ACC(x + (w >> 1), y + (h >> 1), w, 0x17, 0x19, 0x4c, k);
}

void fn_801ED238(Win* o) {
    o->v14();
    fn_801D870C(0, 0, (s16)(o->xe - o->xa), 0x10);
}

typedef struct FnT { void (RObj::*f)(int); int arg; } FnT;

static inline void forEach(LNode* n, LNode* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
}

#define MENU_FOREACH(name, tbl) \
void name(Win* o, int arg) { \
    LNode* e; \
    FnT g; \
    o->v24(); \
    e = (LNode*)((u8*)o + 0x44); \
    g.f = tbl; \
    g.arg = arg; \
    forEach(*(LNode**)((u8*)o + 0x48), e, g); \
}

extern void (RObj::*lbl_8038D070)(int);
extern void (RObj::*lbl_8038D094)(int);
extern void (RObj::*lbl_8038D0F0)(int);


LIST_DTOR(fn_801EDEE4)


MENU_CB(fn_801EE0F0, 0xa0, 0xa4)

MENU_DRAW(fn_801EE144)

void fn_801EE214(void* o, int x, int y, int w, int h, int k) {
    fn_80072ACC(x + (w >> 1), y + (h >> 1), w, 0x17, 0x19, 0x4c, k);
}

void fn_801EE240(Win* o) {
    o->v14();
    fn_801D870C(0, 0, (s16)(o->xe - o->xa), 0x10);
}


LIST_DTOR(fn_801EEEEC)


MENU_CB(fn_801EF0F8, 0xd0, 0xd4)

MENU_DRAW(fn_801EF14C)

void fn_801EF21C(void* o, int x, int y, int w, int h, int k) {
    fn_80072ACC(x + (w >> 1), y + (h >> 1), w, 0x17, 0x19, 0x4c, k);
}

void fn_801EF248(Win* o) {
    o->v14();
    fn_801D870C(0, 0, (s16)(o->xe - o->xa), 0x10);
}


typedef struct Tgt { u8 pad[0x50]; u8 x50; u8 pad51[0x84 - 0x51]; s16 x84, x86; } Tgt;
typedef struct Seq { u8 pad[0x34]; RList list; } Seq;

void* fn_801E40B0(void*, int);

void fn_801EFEF4(Seq* o) {
    Tgt* t = o->list.size != 0 ? (Tgt*)o->list.prev->val : NULL;
    t->x50 = 0;
    t->x84 = 0;
    t->x86 = 0;
    if (o != NULL) {
        fn_801E40B0(o, 0);
    }
}

void fn_801EFF34(u8* o) { *(s16*)(o + 0x40) = 0; }

}
