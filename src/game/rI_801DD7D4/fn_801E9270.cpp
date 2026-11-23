#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {

extern char lbl_8038C294[];
extern char lbl_8038CEA8[];
extern char lbl_8036EF28[];
extern char lbl_8038D100[];
extern void* lbl_804CBE38;
extern char fn_80006EE0[];
void fn_80011CBC(void*, void*);
void* fn_801E2E00(void*, int);
void fn_8012A850(void*);
#if TARGET_PC
FE10_PROTO int fn_8012B120(void*, p32arg);
FE10_PROTO void fn_80107C80(p32arg, int, int, int);
#else
int fn_8012B120(void*, int);
void fn_80107C80(int, int, int, int);
#endif
void fn_80072ACC(int, int, int, int, int, int, int);
u32* fn_801E2204(void*, s16*, s16*);
void* fn_80006E1C(void);
void fn_80006F20(void*);
#if TARGET_PC
FE10_PROTO void * fn_800F4544(void*, const char*);
#else
int fn_800F4544(void*, const char*);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_8000BD3C(p32arg);
#else
int fn_8000BD3C(int);
#endif
void fn_801D74B4(int, int, int, int, int, int);
void fn_801DB770(int, int, int, int, int);
void fn_800720F4(void*, int, int);
void fn_801D870C(int, int, int, int);
void fn_801D88F4(int, int, int, int);
void fn_801D8ADC(int, int, int, int);
void fn_80107DC4(void*, void*, int, int, f32);
#if TARGET_PC
FE10_PROTO void fn_80107F24(void*, ptr32<const void>, int, int);
#else
void fn_80107F24(void*, void*, int, int);
#endif
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void* fn_80081194(void*, void*);
void fn_801E4094(void*);
void fn_801E5448(void*, void*);

typedef struct HNode { struct HNode* prev; struct HNode* next; void* val; void* handle; } HNode;
typedef struct HList { int size; HNode* prev; HNode* next; } HList;

class MBase {
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
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual f32 v68();
    u8 pad4[6];
    s16 xa, xc, xe, x10;
    s16 x12, x14, x16, x18;
    u8 pad1a[4];
    s16 x1e, x20;
    u8 pad22[0x38 - 0x22];
    u32 x38;
    u8* x3c_;
    u8* x40;
    u8 x44;
    u8 pad45[3];
    void* x48;
    void* x4c;
    s16 x50;
    u8 pad52[2];
};

typedef struct HMenu {
    u8 pad0[0x70];
    HList list;
} HMenu;

static inline void hFree(HMenu* o) {
    if (&o->list != NULL) {
        if (&o->list != NULL) {
            if (&o->list != NULL) {
                HNode* p = o->list.next;
                HNode* e = (HNode*)&o->list.prev;
                if (p != e) {
                    HNode* last = e->prev;
                    p->prev->next = last->next;
                    last->next->prev = p->prev;
                    while (p != e) {
                        void** h = (void**)&p->val;
                        HNode* t;
                        if (h != NULL) {
                            if (h[1] != NULL) {
                                fn_80011CBC(fn_80006EE0, h[1]);
                            }
                        }
                        t = p;
                        p = p->next;
                        fn_80079210(t);
                        o->list.size--;
                    }
                }
            }
        }
    }
}

#pragma use_lmw_stmw on
void* fn_801E9270(HMenu* o, int del) {
    if (o != NULL) {
        if (o != NULL) {
            hFree(o);
            fn_801E2E00(o, 0);
        }
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}

void* fn_801E9348(HMenu* o, int del) {
    if (o != NULL) {
        hFree(o);
        fn_801E2E00(o, 0);
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}
#pragma use_lmw_stmw off

void* fn_801E97E4(void* p, int del) {
    if (p != NULL) {
        if (p != NULL) {
            *(void**)p = lbl_8038C294;
            ((VO0*)p)->v10();
        }
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

int fn_801E9850(void) { return 8; }
int fn_801E9858(void) { return 0x10; }
f32 fn_801E9860(void) { return 0.025f; }

void* fn_801E9868(void* p, int del) {
    if (p != NULL) {
        fn_801E2E00(p, 0);
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

typedef struct Slot { u32 id; u8 pad[0x24]; } Slot;
typedef struct UnitS { u8 pad[0x1bc]; Slot items[7]; } UnitS;
typedef struct Rect8 { s16 x12, x14, x16, x18; u8 pad[4]; s16 x1e, x20; } Rect8;
typedef struct LMenu {
    u8 pad0[0xa];
    s16 xa, xc, xe, x10;
    s16 x12, x14, x16, x18;
    u8 pad1a[4];
    s16 x1e, x20;
    u8 pad22[0x50 - 0x22];
    s16 x50;
    u8 pad52[0x58 - 0x52];
    s16 x58;
    u8 pad5a[2];
    UnitS* x5c;
    int x60;
    u8 pad64[0x74 - 0x64];
    u8 (*x74)(void*, void*);
    void* x78;
} LMenu;

static inline s16 lmW(LMenu* o) { return o->xe - o->xa; }
static inline s16 lmH(LMenu* o) { return o->x10 - o->xc; }
static inline void lmSet(LMenu* o, s16 a, s16 b, s16 c, s16 d, s16 e, s16 f) {
    o->x12 = a;
    o->x14 = b;
    o->x16 = c;
    o->x18 = d;
    o->x1e = e;
    o->x20 = f;
}

void fn_801E98C0(LMenu* o) {
    lmSet(o, 2, 5, lmW(o) - 2, lmH(o) - 5, 0x15, 7);
}

static inline BOOL slotOk(LMenu* o, int i) {
    BOOL r;
    Slot* s;
    s = o->x5c->items;
    r = 0;
    if (s[i].id == 0) {
        if (o->x60 == 1) {
            int k = (s16)i;
            if (k == 0 || *(u32*)((u8*)s + (k - 1) * 0x28) != 0) {
                r = 1;
            }
        }
    } else {
        r = 1;
    }
    return r;
}

u32 fn_801E9AC4(const LMenu* o) {
    s16 q[2];
    s16 p[2];
    int s = o->x50;
    int y;
    if (s < 0) {
        y = 0;
        s = 0;
    } else {
        int t = s * o->x58;
        y = (s16)(t + o->x20);
        s = o->x1e;
    }
    p[0] = s;
    p[1] = y;
    return *fn_801E2204((void*)o, q, p);
}

Slot* fn_801E9B28(LMenu* o) {
    int s = o->x50;
    if (s < 0 || s > 6) {
        return NULL;
    }
    return &o->x5c->items[s];
}

void fn_801E9BE0(LMenu* o) {
    if (o->x5c != NULL) {
        fn_8012A850(o->x5c);
    }
}

Slot* fn_801E9BF4(LMenu* o, int i) {
    return &o->x5c->items[i];
}

int fn_801E9C08(LMenu* o, int* a) {
    if (o->x74 != NULL) {
        return o->x74(a, o->x78) != 0;
    }
    return fn_8012B120(o->x5c, *a);
}

void fn_801E9C64(void* o, int a, int b, int c, int d, int e) {
    fn_80107C80(d, e, a, b);
}

void fn_801E9C7C(void* o, int x, int y, int w, int h, int k) {
    fn_80072ACC(x + (w >> 1), y + (h >> 1), w, 0x18, 0x19, 0x4c, k);
}

void fn_801EA48C(VO0* o) { o->v24(); }

void* fn_801EA49C(MBase* o, int del) {
    if (o != NULL) {
        *(void**)o = lbl_8038CEA8;
        if (o->x4c != NULL) {
            fn_80011CBC(fn_80006EE0, o->x4c);
            o->x4c = NULL;
        }
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}

void fn_801EA518(MBase* o) {
    o->x12 = 0;
    o->x14 = 0;
    o->x16 = 0x128;
    o->x18 = 0x70;
}

typedef struct TexH { u32 flags; u8* x4; u8 pad8[0x44 - 8]; int x44; } TexH;

void fn_801EA538(MBase* o, u8* a) {
    o->x40 = a;
    if (o->x4c != NULL) {
        fn_80011CBC(fn_80006EE0, o->x4c);
        o->x4c = NULL;
    }
    if (a != NULL) {
        o->x4c = fn_80006E1C();
        ((TexH*)o->x4c)->x4 = a + 0x28;
        ((TexH*)o->x4c)->flags |= 0xE021A000;
        ((TexH*)o->x4c)->x44 = fn_8000BD3C(fn_800F4544(a, lbl_8036EF28));
        fn_80006F20(o->x4c);
    }
}

void fn_801EAC6C(MBase* o) {
    u8* u = o->x40;
    o->v14();
    fn_801D74B4(0, 0, (s16)(o->xe - o->xa), (s16)(o->x10 - o->xc), (*(u8**)(u + 0xf4))[8], o->x38);
}

void fn_801EB3DC(MBase* o) {
    u8* u = o->x40;
    o->v14();
    fn_801D74B4(0, 0, (s16)(o->xe - o->xa), (s16)(o->x10 - o->xc), (*(u8**)(u + 0xf4))[8], o->x38);
    fn_801DB770(0x8f, 0xb, 0x78, 0x58, o->x38);
    switch (o->x44) {
    case 1:
        fn_800720F4(u, -6, -0x68);
        break;
    }
}

int fn_801EB904(void) { return 0x1c; }
int fn_801EB90C(void) { return 0x1c; }

void fn_801EB914(LMenu* o) {
    lmSet(o, 5, 2, lmW(o) - 5, lmH(o) - 2, 8, 0xe);
}

void* fn_801EB968(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void fn_801EB9A8(LMenu* o) {
    lmSet(o, 5, 2, lmW(o) - 5, lmH(o) - 2, 0x17, 0xa);
}

void* fn_801EB9FC(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void fn_801EBA3C(MBase* o) {
    o->v14();
    fn_801D870C(0, 0, (s16)(o->xe - o->xa), 0x10);
}

void fn_801EBA94(MBase* o, int x, int y, int d, void** p, void* k) {
    void* v = *p;
    int w;
    fn_80107DC4(v, k, x, y, o->v68());
    fn_8007E154();
    fn_8007E720(1.8f);
    fn_8007E164();
    w = o->x1e;
    w = (s16)(o->v3C() - w * 2);
    fn_801D8ADC(x, (s16)(y + o->v40() - 10), w, 0x10);
    fn_8007E154();
    fn_8007E720(-1.8f);
    fn_8007E164();
}

void fn_801EBB6C(MBase* o) {
    o->v14();
    fn_801D870C(0, 0, (s16)(o->xe - o->xa), 0x10);
}

void fn_801EBBC4(MBase* o, int x, int y, int d, void** p, void* k) {
    void* v = *p;
    int w;
    fn_80107DC4(v, k, x, y, o->v68());
    fn_8007E154();
    fn_8007E720(1.8f);
    fn_8007E164();
    w = o->x1e;
    w = (s16)(o->v3C() - w * 2);
    fn_801D8ADC(x, (s16)(y + o->v40() - 10), w, 0x10);
    fn_8007E154();
    fn_8007E720(-1.8f);
    fn_8007E164();
}

void fn_801EBC9C(MBase* o) {
    o->v14();
    fn_801D88F4(0, 0, (s16)(o->xe - o->xa), 0x10);
}

void fn_801EBCF4(MBase* o, int x, int y, int d, void** p, void* k) {
    int w;
    fn_80107F24(*p, k, x, y);
    fn_8007E154();
    fn_8007E720(1.8f);
    fn_8007E164();
    w = o->x1e;
    w = (s16)(o->v3C() - w * 2);
    fn_801D8ADC(x, (s16)(y + o->v40() - 10), w, 0x10);
    fn_8007E154();
    fn_8007E720(-1.8f);
    fn_8007E164();
}

f32 fn_801EBDC4(u8* o) { return *(f32*)(o + 0xd8); }
int fn_801EBDCC(void) { return 0x1c; }
s16 fn_801EBDD4(MBase* o) { return o->x16 - o->x12; }
f32 fn_801EBDE8(u8* o) { return *(f32*)(o + 0xa8); }
int fn_801EBDF0(void) { return 0x1c; }
s16 fn_801EBDF8(MBase* o) { return o->x16 - o->x12; }
int fn_801EBE0C(void) { return 0x1c; }
s16 fn_801EBE14(MBase* o) { return o->x16 - o->x12; }

typedef struct PTw { u8 pad[0x42]; s16 x42; int x44; int x48; } PTw;

void fn_801EBE28(MBase* o, void* a, int b, int c) {
    if (b != o->v34()) {
        PTw* p = (PTw*)fn_80081194(lbl_8038D100, a);
        if (p != NULL) {
            fn_801E4094(p);
        }
        fn_801E5448(p, o);
        *((u8*)o + 0x50) = 1;
        p->x42 = 4;
        p->x44 = b;
        p->x48 = c;
    }
}

void* fn_801EBED0(u8* o) { return *(void**)(*(u8**)(o + 0xf8) + 0x40); }

void fn_801EBEDC(MBase* o) { o->v30(lbl_804CBE38); }

void fn_801EBEF0(u8* o, void* v) {
    *(void**)(*(u8**)(o + 0xf8) + 0x40) = v;
    lbl_804CBE38 = v;
}

}
