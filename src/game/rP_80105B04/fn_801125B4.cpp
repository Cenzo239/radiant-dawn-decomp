#include "game/rP_80105B04/rp.h"
struct Color { u8 r, g, b, a; };
struct IT { u8 pad[0x2C]; u8 kind; };
struct CS { IT* item; u8 uses; u8 f80 : 1; u8 f40 : 1; u8 f20 : 1; u8 f10 : 1; u8 f08 : 1; u8 f04 : 1; u8 f02 : 1; u8 f01 : 1; char name[0x18]; s8 mt, hit, crt, wt; Color col; };
extern "C" {
extern Color lbl_804CDC40;
static Color k0 = {0x80,0x80,0x80,0xff};
static Color k1 = {0,0,0,0x80};
static Color k2 = {0xff,0x20,0x20,0xff};
static Color k3 = {0x20,0xff,0x20,0xff};
static Color k4 = {0x20,0x20,0xff,0xff};
static Color k5 = {0x80,0x80,0x20,0xff};
static Color k6 = {0x80,0x20,0x80,0xff};
static Color k7 = {0x80,0x40,0x20,0xff};
static Color k8 = {0x20,0x80,0x80,0xff};
static Color k9 = {0x80,0x80,0x80,0xff};
const Color* fn_80108774(CS* s);
static inline const Color* T1() { Color t = lbl_804CDC40; return &t; }
static inline const Color* T2() { return T1(); }
#pragma auto_inline off
static inline const Color* A0(CS* s) { if (s->f20) { return fn_80108774(s); } { Color t = lbl_804CDC40; return &t; } }
static inline const Color* A1(CS* s) { if (s->f20) { if (s->f20) return &s->col; return A0(s); } return T1(); }
static inline const Color* A2(CS* s) { if (s->f20) { if (s->f20) return &s->col; return A1(s); } return T2(); }
static inline const Color* A3(CS* s) { if (s->f20) { if (s->f20) return &s->col; return A2(s); } { Color t = lbl_804CDC40; return &t; } }
static inline const Color* A4(CS* s) { if (s->f20) { if (s->f20) return &s->col; return A3(s); } { Color t = lbl_804CDC40; return &t; } }
static inline const Color* A5(CS* s) { if (s->f20) { if (s->f20) return &s->col; return A4(s); } { Color t = lbl_804CDC40; return &t; } }
static inline const Color* Ax(CS* s) { if (s->f20) return &s->col; return A5(s); }
Color fn_801125B4(CS* s) {
    Color c = k9;
    if (s->f20) { c = *Ax(s); } else {
        switch (s->item ? s->item->kind : 0) {
        case 0: { Color t = k0; c = t; break; }
        case 1: { Color t = k1; c = t; break; }
        case 2: { Color t = k2; c = t; break; }
        case 3: { Color t = k3; c = t; break; }
        case 4: { Color t = k4; c = t; break; }
        case 5: { Color t = k5; c = t; break; }
        case 6: { Color t = k6; c = t; break; }
        case 7: { Color t = k7; c = t; break; }
        case 8: { Color t = k8; c = t; break; }
        }
    }
    return c;
}
}
