#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct TEnt { u8* x0; };
struct TIp { u32 x0; u8 x4; u8 p5[0xC3]; void* xC8; int xCC; int xD0; int xD4; u8 pD8[4];
    f32 xDC, xE0, xE4, xE8, xEC, xF0, xF4, xF8, xFC, x100, x104, x108, x10C, x110, x114, x118, x11C, x120; };
extern const char* fn_800D0864(const char*);
extern void fn_801A2268(TIp*, const char*);
extern const char* fn_8010F628(void*);
struct Sys { u8 pad[0x1BC8]; s8 lang; };
extern Sys* fn_8024BC94(void);
struct U4 { u8 p[4]; u32 x4; };
extern U4* fn_801116B8(TEnt*);

void fn_801A1DCC(TIp* p, const char* s, f32 x, f32 y) {
    f32 xx, yy, w, h;
    if (p->x0 & 1) return;
    p->xE4 = p->xDC;
    p->xE8 = p->xE0;
    p->xEC = x;
    p->xF0 = y;
    p->xC8 = 0;
    if (s) fn_801A2268(p, fn_800D0864(s));
    else p->x4 = 0;
    w = (f32)(p->xD4 + 0x1E);
    h = 24.0f * (f32)p->xD0 + 38.0f;
    if (w < 112.0f) w = 112.0f;
    if (h < 57.0f) h = 57.0f;
    xx = (16.0f + x) - 0.5f * w;
    yy = 50.0f + y;
    if (xx < 32.0f) xx = 16.0f;
    if (xx + w > 592.0f) xx = 592.0f - w;
    if (yy + h > 450.0f) yy = yy - 40.0f - h;
    p->xFC = p->xF4;
    p->x100 = p->xF8;
    p->x104 = xx;
    p->x108 = yy;
    p->x114 = p->x10C;
    p->x118 = p->x110;
    p->x11C = w;
    p->x120 = h;
    p->xCC = 8;
}
static inline u8 EType(TEnt* e) { if (e->x0) return e->x0[0x12]; return 0x13; }
void fn_801A1F64(TIp* p, TEnt* e, f32 x, f32 y) {
    f32 lim[2];
    f32 xx, yy, w, h;
    if (p->x0 & 1) return;
    p->xE4 = p->xDC;
    p->xE8 = p->xE0;
    p->xEC = x;
    p->xF0 = y;
    p->xC8 = e;
    fn_801A2268(p, fn_800D0864(fn_8010F628(e->x0)));
    if (fn_8024BC94()->lang == 0) { lim[0] = 270.0f; lim[1] = 500.0f; }
    else { lim[0] = 313.0f; lim[1] = 520.0f; }
    if (EType(e) == 0xB && (fn_801116B8(e)->x4 & 0x10)) {
        if ((f32)p->xD4 < lim[0]) p->xD4 = (int)lim[0];
        p->xD0++;
    } else if (EType(e) != 0xF && EType(e) != 0xE) {
        if ((f32)p->xD4 < lim[1]) p->xD4 = (int)lim[1];
        p->xD0++;
    }
    w = (f32)(p->xD4 + 0x1E);
    if (w < 112.0f) w = 112.0f;
    h = 24.0f * (f32)p->xD0 + 38.0f;
    if (h < 57.0f) h = 57.0f;
    xx = (16.0f + x) - 0.5f * w;
    yy = 50.0f + y;
    if (xx < 32.0f) xx = 32.0f;
    if (xx + w > 592.0f) xx = 592.0f - w;
    if (yy + h > 450.0f) yy = yy - 40.0f - h;
    p->xFC = p->xF4;
    p->x100 = p->xF8;
    p->x104 = xx;
    p->x108 = yy;
    p->x114 = p->x10C;
    p->x118 = p->x110;
    p->x11C = w;
    p->x120 = h;
    p->xCC = 8;
}
}
