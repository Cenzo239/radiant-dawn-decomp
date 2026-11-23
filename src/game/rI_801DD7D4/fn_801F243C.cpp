#include "game/rI_801DD7D4/types.h"
extern "C" {
extern char lbl_8036F03C[];
extern u8 lbl_8038D9B0[], lbl_8038D958[], lbl_8038D900[], lbl_8038D8A8[], lbl_8038D850[], lbl_8038D7F8[], lbl_8038D7A0[], lbl_8038D748[];
extern u8 lbl_8038D20C[], lbl_8038D230[], lbl_8038C8A8[], lbl_8038DA08[];
extern s8 lbl_804CBE68, lbl_804CBE70, lbl_804CBE78, lbl_804CBE80, lbl_804CBE90, lbl_804CBE98, lbl_804CBEA0, lbl_804CBEA8;
extern s8 lbl_804CBEB0, lbl_804CBEB8, lbl_804CBEC0, lbl_804CBEC8, lbl_804CBED8, lbl_804CBEE0, lbl_804CBEE8, lbl_804CBEF0;
extern void* lbl_804CBE6C, *lbl_804CBE74, *lbl_804CBE7C, *lbl_804CBE88, *lbl_804CBE94, *lbl_804CBE9C, *lbl_804CBEA4, *lbl_804CBEAC;
extern void* lbl_804CBEB4, *lbl_804CBEBC, *lbl_804CBEC4, *lbl_804CBED0, *lbl_804CBEDC, *lbl_804CBEE4, *lbl_804CBEEC, *lbl_804CBEF4;
struct W;
W* fn_801E5640(void*, int, int);
void fn_801E518C(void*, W*, int, f32);
f32 fn_801E3468(W*);
void* fn_80079150(u32);
int fn_80058718(void);
int fn_8002460C(void);
void* fn_800D5448(void*, void*, int);
}
struct W { u8 p[0x34]; f32 x34; u8 p38[4]; W* x3c; u8 p40[0xe]; u8 x4e; u8 p4f[0x15]; const char* x64; u8 x68; };
struct Sc { u8 p[0x40]; W* x40; u8 p44[8]; W* x4c; u8 p50[0xc]; void* x5c; };
struct Eff { void* vt; void* vt2; s16 x8, xa, xc, xe, x10, x12, x14, x16; f32 x18; s16 x1c, x1e, x20; };
#define LZ(g, o, v) if (!g) { g = 1; o = v; }
#define CHAIN(res, W0, FN, F) {     W* w1 = (W0);     v1 = w1->F;     if (w1->x3c) {         W* w2 = w1->x3c;         v2 = w2->F;         if (w2->x3c) {             W* w3 = w2->x3c;             v3 = w3->F;             if (w3->x3c) {                 W* w4 = w3->x3c;                 v4 = w4->F;                 if (w4->x3c) v4 *= FN(w4->x3c);                 v3 *= v4;             }             v2 *= v3;         }         v1 *= v2;     }     res = v1; }
static inline void help(void* o, const char* const& s) {
    W* h = fn_801E5640(o, -0x1000, 0);
    if (h) h->x64 = s;
}
static inline Eff* mk(u8* vt) {
    Eff* e = (Eff*)fn_80079150(0x24);
    if (e) {
        e->vt = vt;
        e->vt2 = lbl_8038C8A8;
        e->x8 = 0;
        e->xa = 0;
        e->xc = 0x80;
        e->xe = 0;
        e->x10 = 2;
        e->x12 = 0xc;
        e->x14 = 0x10;
        e->x16 = 0;
        e->x18 = 0.0f;
        e->x1c = 0x20;
        e->x1e = 4;
        e->x20 = 2;
        e->vt2 = lbl_8038DA08;
    }
    return e;
}
extern "C" void fn_801F243C(Sc* o) {
/*P*/
    f32 k;
    f32 v4;
    f32 v3;
    f32 v2;
    f32 v1;
    Eff* e;
/*E*/
    CHAIN(k, o->x40, fn_801E3468, x34);
    {
    f32 one = 0.5f;
    if (one != k) fn_801E518C(o, o->x40, 0, one);
    }
    {
    int t = 1;
    o->x4c->x68 = t;
    o->x4c->x4e = 0;
    }
    if (fn_80058718() || fn_8002460C()) {
        LZ(lbl_804CBE68, lbl_804CBE6C, lbl_8038D9B0);
        LZ(lbl_804CBE70, lbl_804CBE74, lbl_8038D958);
        LZ(lbl_804CBE78, lbl_804CBE7C, lbl_8038D900);
        LZ(lbl_804CBE80, lbl_804CBE88, lbl_8038D8A8);
        LZ(lbl_804CBE90, lbl_804CBE94, lbl_8038D850);
        LZ(lbl_804CBE98, lbl_804CBE9C, lbl_8038D7F8);
        LZ(lbl_804CBEA0, lbl_804CBEA4, lbl_8038D7A0);
        LZ(lbl_804CBEA8, lbl_804CBEAC, lbl_8038D748);
        e = mk(lbl_8038D20C);
    } else {
        LZ(lbl_804CBEB0, lbl_804CBEB4, lbl_8038D9B0);
        LZ(lbl_804CBEB8, lbl_804CBEBC, lbl_8038D958);
        LZ(lbl_804CBEC0, lbl_804CBEC4, lbl_8038D900);
        LZ(lbl_804CBEC8, lbl_804CBED0, lbl_8038D8A8);
        LZ(lbl_804CBED8, lbl_804CBEDC, lbl_8038D850);
        LZ(lbl_804CBEE0, lbl_804CBEE4, lbl_8038D7F8);
        LZ(lbl_804CBEE8, lbl_804CBEEC, lbl_8038D7A0);
        LZ(lbl_804CBEF0, lbl_804CBEF4, lbl_8038D748);
        e = mk(lbl_8038D230);
    }
    e->x8 = 0x148;
    e->xa = 0xd8;
    e->xc = 0xc8;
    e->x14 = 0;
    e->x18 = 200.0f;
    e->x1e = 4;
    o->x5c = fn_800D5448(e, o, 0);
    help(o, lbl_8036F03C + 0x4b);
}
