#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
typedef struct RangeState { void* x0; } RangeState;
extern u8 lbl_803CA870[];
extern char lbl_804CA990[8];
extern char lbl_8036F03C[];
void fn_80102C6C(void*, const char*, int, int, int);
void fn_801EA538(void*, void*);
void fn_801E5734(void*, void*);
void* fn_801E5640(void*, int, int);
int fn_801E999C(void*, int);
void fn_801E5448(void*, void*);
void fn_801E5558(void*, void*, int);
void fn_801E459C(void*, void*, void*, int);
void fn_801E495C(void*, void*, void*, int);
void fn_801E77E8(void*, int);
void fn_800893AC(void*);
void fn_800D56E8(void*);
void fn_80083174(void*);
void* fn_801116B8(void*);
typedef struct Sub { u8 pad[0x40]; void* x40; } Sub;
typedef struct LM {
    u8 pad[0xa]; s16 xa, xc; u8 p2[0x3e]; u8 x4c; u8 p3[3]; s16 x50; u8 x52; u8 p4[0x11]; const char* x64; u8 p5[0xc]; void* x74; u32 x78; u32 x7c;
} LM;
typedef struct Mp { u8 p[0xa6]; s8 xa6; } Mp;
static inline void setA6(Mp* m, s8 v) { m->xa6 = v; }
typedef struct Proc { u8 pad[0x40]; void* x40; Sub* x44; u8 pad48[4]; LM* x4c; u8 pad50[0xc]; Mp* x5c; } Proc;
typedef struct Mp9 { u8 p[0x2c]; u8 x2c; } Mp9;
typedef struct P9 { u8 p[0x5c]; Mp* x5c; } P9;
void* fn_801FB050(void*);
static inline void help(void* o, const char* s0) {
    const char* s = s0;
    LM* p = (LM*)fn_801E5640(o, -0x1000, 0);
    if (p != NULL) p->x64 = s;
}
static inline void lmOff(LM* m) {
    m->x4c = 0;
    m->x74 = 0;
    m->x78 = 0;
    m->x50 = fn_801E999C(m, 0);
}
void fn_801F76C4(Proc* o) {
    Mp* m = o->x5c;
    const char* s;
    LM* p;
    fn_800893AC(m);
    {
        int v = m->xa6;
        fn_800D56E8(m);
        setA6(m, v);
    }
    fn_80083174(o->x5c);
    { LM* l = o->x4c; lmOff(l); }
    fn_801E5734(o, o->x40);
    if (*(void**)lbl_803CA870) {
        fn_80102C6C(*(void**)lbl_803CA870, lbl_804CA990, 4, 0, 0);
    }
    if (o->x44 && o->x44->x40) fn_801EA538(o->x44, o->x44->x40);
    s = lbl_8036F03C + 0x4b;
    p = (LM*)fn_801E5640(o, -0x1000, 0);
    if (p != NULL) p->x64 = s;
}
void fn_801F7BD0(Proc* o) {
    Mp* m = o->x5c;
    const char* s;
    LM* p;
    fn_800893AC(m);
    {
        int v = m->xa6;
        fn_800D56E8(m);
        setA6(m, v);
    }
    fn_80083174(o->x5c);
    {
        void* t;
        LM* l = o->x4c;
        t = o->x40;
        lmOff(l);
        fn_801E5734(o, t);
    }
    if (*(void**)lbl_803CA870) {
        fn_80102C6C(*(void**)lbl_803CA870, lbl_804CA990, 4, 0, 0);
    }
    if (o->x44 && o->x44->x40) fn_801EA538(o->x44, o->x44->x40);
    s = lbl_8036F03C + 0x4b;
    p = (LM*)fn_801E5640(o, -0x1000, 0);
    if (p != NULL) p->x64 = s;
}
typedef struct W7 { void* vt; int rc; u8 p[2]; s16 xa, xc; u8 p2[0x42]; u8 x50, x51; u8 p3[2]; s16 x54; u8 p4[0x26]; int x7c, x80; } W7;
typedef struct P7 { u8 p[0x40]; W7* x40; u8 p2[0xc]; RObj* x50; W7* x54; W7* x58; } P7;
#define REL(fld) { RObj* r = (RObj*)o->fld; if (r) { if (--r->rc == 0 && r) r->destroy(1); o->fld = 0; } }
void fn_801F7110(P7* o) {
    W7* l = o->x40;
    fn_801E5448(o, l);
    {
        s16 q[2];
        q[0] = l->xa;
        q[1] = 0x1c;
        fn_801E459C(o, l, q, 0);
    }
    fn_801E77E8(l, l->x54);
    l->x51 = 0;
    l->x7c = 0;
    l->x80 = 0;
    {
        s16 q[2];
        s16 y = o->x54->xc;
        q[0] = 0x189;
        q[1] = y;
        fn_801E495C(o, o->x54, q, 1);
    }
    REL(x54);
    {
        s16 q[2];
        s16 y = o->x58->xc;
        q[0] = 0x197;
        q[1] = y;
        fn_801E495C(o, o->x58, q, 0);
    }
    REL(x58);
    fn_801E5558(o, o->x50, 0);
    REL(x50);
}
void fn_801F98A0(P9* o) {
    Mp* m = o->x5c;
    const char* s;
    LM* p;
    {
        int v = m->xa6;
        fn_800D56E8(m);
        setA6(m, v);
    }
    {
        Mp9* n = (Mp9*)o->x5c;
        if (!(n->x2c & 4)) fn_80083174(n);
        fn_800893AC(n);
    }
    s = lbl_8036F03C + 0x1bb;
    p = (LM*)fn_801E5640(o, -0x1000, 0);
    if (p != NULL) p->x64 = s;
}
static inline void lmFilter(LM* m, void* f, u32 v) {
    m->x74 = f;
    m->x78 = v;
}
void fn_801FB0FC(Proc* o) {
    LM* m = o->x4c;
    const char* s;
    LM* p;
    m->x4c = 1;
    lmFilter(m, fn_801FB050, *(u32*)lbl_803CA870);
    m->x50 = fn_801E999C(m, 0);
    fn_801E5734(o, m);
    s = lbl_8036F03C + 0x252;
    p = (LM*)fn_801E5640(o, -0x1000, 0);
    if (p != NULL) p->x64 = s;
}
}
