#include "game/rP_80105B04/rp.h"
struct Color { u8 r, g, b, a; };
struct CS { u8* item; u8 uses; u8 f80 : 1; u8 f40 : 1; u8 f20 : 1; u8 f10 : 1; u8 f08 : 1; u8 f04 : 1; u8 f02 : 1; u8 f01 : 1; char name[0x18]; s8 mt, hit, crt, wt; Color col; };
extern "C" {
extern Color lbl_804CDC08;
const Color* fn_80108678(CS* s);
const Color* fn_80108774(CS* s);
BOOL fn_80108660(CS* s);
#pragma auto_inline off
static inline const Color* T1() { Color t = lbl_804CDC08; return &t; }
static inline const Color* T2() { return T1(); }
static inline const Color* A0(CS* s) { if (s->f20) { return fn_80108774(s); } { Color t = lbl_804CDC08; return &t; } }
static inline const Color* A1(CS* s) { if (s->f20) { if (s->f20) return &s->col; return A0(s); } { Color t = lbl_804CDC08; return &t; } }
static inline const Color* A2(CS* s) { if (s->f20) { if (s->f20) return &s->col; return A1(s); } return T1(); }
const Color* fn_80108678(CS* s) {
 if (s->f20) { if (s->f20) return &s->col; return A2(s); }
 { Color t = lbl_804CDC08; return &t; }
}
static inline const Color* B0(CS* s) { if (s->f20) { if (fn_80108660(s)) return &s->col; return fn_80108678(s); } { Color t = lbl_804CDC08; return &t; } }
static inline const Color* B1(CS* s) { if (s->f20) { if (s->f20) return &s->col; return B0(s); } { Color t = lbl_804CDC08; return &t; } }
const Color* fn_80108774(CS* s) {
 if (s->f20) return &s->col;
 return B1(s);
}
}
