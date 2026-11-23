#include "game/rI_801DD7D4/types.h"
extern "C" {
extern char lbl_8036F03C[];
extern u8 lbl_8038DBB8[], lbl_8038DB60[];
extern u8 lbl_8038D200[], lbl_8038C8A8[], lbl_8038DAB0[];
extern s8 lbl_804CBE48, lbl_804CBE58;
extern void* lbl_804CBE50, *lbl_804CBE60;
struct W;
W* fn_801E5640(void*, int, int);
void* fn_80079150(u32);
void* fn_800D5448(void*, void*, int);
}
struct W { u8 p[0x64]; const char* x64; };
struct Sc { u8 p[0x5c]; void* x5c; };
struct Eff { void* vt; void* vt2; s16 x8, xa, xc, xe, x10, x12, x14, x16; f32 x18; s16 x1c, x1e; };
#define LZ(g, o, v) if (!g) { g = 1; o = v; }
static inline void help(void* o, const char* const& s) {
    W* h = fn_801E5640(o, -0x1000, 0);
    if (h) h->x64 = s;
}
static inline Eff* mk() {
    Eff* e = (Eff*)fn_80079150(0x20);
    if (e) {
        e->vt = lbl_8038D200;
        e->vt2 = lbl_8038C8A8;
        e->x8 = 0x31;
        e->xa = 0x13;
        e->xc = 0xf4;
        e->xe = 0x20;
        e->x10 = 0;
        e->x12 = 4;
        e->x14 = 0;
        e->x16 = 0;
        e->x18 = 10.0f;
        e->x1c = 0x20;
        e->x1e = 4;
        e->vt2 = lbl_8038DAB0;
    }
    return e;
}
extern "C" void fn_801F977C(Sc* o) {
    Eff* e;
    LZ(lbl_804CBE48, lbl_804CBE50, lbl_8038DBB8);
    LZ(lbl_804CBE58, lbl_804CBE60, lbl_8038DB60);
    e = mk();
    e->x1e = 0;
    o->x5c = fn_800D5448(e, o, 0);
    help(o, lbl_8036F03C + 0x1bb);
}
