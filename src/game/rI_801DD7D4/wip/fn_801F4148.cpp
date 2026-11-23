/* wip near misses for fn_801F4148.cpp (whole file kept so declarations stay together):
   fn_801F84E4: 2 wrong reference(s); 10 of 55 words differ
   fn_801F86B8: 20 of 56 words differ
*/
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

typedef struct RangeState {
    void* x0;
    void* x4;
    u8 pad8[4];
    u8 xc;
    u8 pad_d;
    u8 xe;
    u8 padf[0x1c - 0xf];
    int x1c;
    u8 pad20[0x130 - 0x20];
} RangeState;
extern RangeState lbl_803CA870;
extern char lbl_804CA990[8];
extern char lbl_804CA988[8];
extern char lbl_8036F03C[];
void fn_80102C6C(void*, const char*, int, int, int);
void fn_801EA538(void*, void*);
void fn_80083DC4(void*, int);
void fn_801E5734(void*, void*);
void* fn_801E5640(void*, int, int);
int fn_801E9A30(void*);
int fn_801E999C(void*, int);
void* fn_801E9B28(void*);
void fn_801E495C(void*, void*, void*, int);
void fn_800453B4(void*, int);
void fn_8004564C(void*, void*);
int fn_8012C998(void*, int);
int fn_8012C8BC(void*, int);
void fn_8008939C(void*);

typedef struct Sub { u8 pad[0x40]; void* x40; } Sub;
typedef struct Proc {
    u8 pad[0x44];
    Sub* x44;
    u8 pad48[4];
    struct LM* x4c;
    u8 pad50[4];
    void* x54;
    u8 pad58[4];
    void* x5c;
} Proc;
typedef struct LM {
    u8 pad[0xa];
    s16 xa, xc;
    u8 pade[0x4c - 0xe];
    u8 x4c;
    u8 pad4d[3];
    s16 x50;
    u8 pad52[2];
    s16 x54, x56;
    u8 pad58[0x60 - 0x58];
    int x60;
    const char* x64;
    u8 pad68[0x74 - 0x68];
    void* x74;
    void* x78;
} LM;

static inline void lmFilter(LM* m, void* f, void* a) {
    m->x74 = f;
    m->x78 = a;
}

void fn_801F4148(Proc* o) {
    if (lbl_803CA870.x0 != NULL) {
        fn_80102C6C(lbl_803CA870.x0, lbl_804CA990, 4, 0, 0);
    }
    if (lbl_803CA870.x4 != NULL) {
        fn_80102C6C(lbl_803CA870.x4, lbl_804CA988, 4, 0, 0);
    }
    if (o->x44 != NULL && o->x44->x40 != NULL) {
        fn_801EA538(o->x44, o->x44->x40);
    }
    fn_80083DC4(o, 0xb);
}

void fn_801F5A40(void) {}

void fn_801F7074(Proc* o) {
    if (lbl_803CA870.x0 != NULL) {
        fn_80102C6C(lbl_803CA870.x0, lbl_804CA990, 4, 0, 0);
    }
    if (lbl_803CA870.x4 != NULL) {
        fn_80102C6C(lbl_803CA870.x4, lbl_804CA988, 4, 0, 0);
    }
    if (o->x44 != NULL && o->x44->x40 != NULL) {
        fn_801EA538(o->x44, o->x44->x40);
    }
    fn_80083DC4(o, 0xf);
}

typedef struct Slot { u32 id; u8 x4; u8 b7 : 1; u8 pad : 7; } Slot;

u8 fn_801F72A0(Slot* s, void* a) {
    if (s == NULL || s->id == 0) {
        return 0;
    }
    return fn_8012C998(a, s->id);
}

void fn_801F72E8(Proc* o) { fn_8008939C(o->x5c); }

void fn_801F72F0(Proc* o) {
    LM* m = o->x4c;
    const char* s;
    LM* p;
    m->x4c = 1;
    lmFilter(m, fn_801F72A0, lbl_803CA870.x0);
    m->x50 = fn_801E999C(m, 0);
    fn_801E5734(o, m);
    s = lbl_8036F03C + 0x101;
    p = (LM*)fn_801E5640(o, -0x1000, 0);
    if (p != NULL) {
        p->x64 = s;
    }
}

BOOL fn_801F77BC(Slot* s) {
    if (s == NULL || s->id == 0) {
        return 0;
    }
    return s->b7 != 0;
}

void fn_801F77F0(Proc* o) { fn_8008939C(o->x5c); }

void fn_801F77F8(Proc* o) {
    LM* m = o->x4c;
    const char* s;
    LM* p;
    m->x4c = 1;
    lmFilter(m, fn_801F77BC, lbl_803CA870.x0);
    m->x50 = fn_801E999C(m, 0);
    fn_801E5734(o, m);
    s = lbl_8036F03C + 0x12d;
    p = (LM*)fn_801E5640(o, -0x1000, 0);
    if (p != NULL) {
        p->x64 = s;
    }
}

u8 fn_801F7F28(Slot* s, void* a) {
    if (s == NULL || s->id == 0) {
        return 0;
    }
    return fn_8012C8BC(a, s->id);
}

void fn_801F84E4(Proc* o) {
    RangeState* r = &lbl_803CA870;
    switch (r->xc) {
    case 0x81: {
        LM* m = o->x4c;
        if (fn_801E9B28(m) != NULL) {
            r->x4 = lbl_803CA870.x0;
            fn_800453B4(r, 4);
            r->xe = m->x50;
            r->x1c = m->x50;
            fn_8004564C(r, o);
        }
        break;
    }
    case 0x80:
        fn_80083DC4(o, 0x1a);
        break;
    }
    {
        const char* s = lbl_8036F03C + 0x15b;
        LM* p = (LM*)fn_801E5640(o, -0x1000, 0);
        if (p != NULL) {
            p->x64 = s;
        }
    }
}

static inline void lmMove(Proc* o, LM* p, s16 x, int f) {
    if (p->xa != x) {
        s16 q[2];
        q[0] = x;
        q[1] = p->xc;
        fn_801E495C(o, p, q, f);
    }
}

void fn_801F86B8(Proc* o) {
    LM* m = o->x4c;
    m->x4c = 0;
    lmFilter(m, NULL, NULL);
    m->x50 = fn_801E999C(m, 0);
    lmMove(o, (LM*)fn_801E5640(o, 0x107, 0), 0x191, 1);
    lmMove(o, (LM*)fn_801E5640(o, 0x108, 0), 0x185, 0);
    fn_801E5734(o, m);
}

}
