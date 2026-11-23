#ifndef RN_ROOMDRAW_H
#define RN_ROOMDRAW_H
/* Shared by the conversation-room draw functions. */
#include "game/rN_8025EEF0/room.h"
#include "game/rN_8025EEF0/prim2d.h"

struct GXC { u8 r, g, b, a; };
struct RC { s16 x, y, w, h; };

extern "C" {
void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC* c, int d, int e);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_800CB3A8(s16 x, s16 y, int a, int b, int c, f32 s, f32 t, const char* f, ...);
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_800804D4(int r, int g, int b, int a);
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void (*f)(void*, void*), void* p);
#endif
void fn_8007E7B4(void);
void fn_80272F94(void* p, void* arg);
void fn_80074EB4(int x, int y, int w, int h);
void* fn_8010B100(const char* s);
void* fn_8010B1D8(const char* s);
const char* fn_8009285C(void* e);
const char* fn_800929AC(void* e);
const char* fn_80118C44(void* u);
void fn_80072ACC(int x, int y, int a, int b, int c, int d, int e);
void fn_800712E8(int x, int y, int a);
void fn_8017980C(void* p, int x, int y, int h);
void fn_80179888(void* p, int v);
void fn_8017985C(void* p, int v);
void fn_80179864(void* p, int v);
void fn_80179A7C(void* p, int v);
void fn_80179854(void* p, f32 v);
void fn_80179A84(void* p);
void fn_80070688(f32 x, f32 y, f32 w, f32 h);
#if TARGET_PC
FE10_PROTO int fn_80245368(void* p, p32arg);
#else
int fn_80245368(void* p, int k);
#endif

}
static inline GXC mk(const u8* p) { GXC c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF; return c; }

static inline void texSize(int i, f32& w, f32& h) {
    u16* p = *fn_80006A0C(roomTex(), i);
    w = p[1];
    h = p[0];
}
/* The stack slots are spelled out: the original passes GXC by value, and the slot order depends on inlining this file does not reproduce. */
static inline void dS(int x, int y, f32 w, f32 h, int i, GXC& c, GXC& t) {
    f32 h2;
    f32 w2;
    { const u8* p = fn_800CD204(1); c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF; }
    texSize(i, w2, h2);
    { void* tx = roomTex();
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(x, y, x + w, y + h, 0.0f, 0.0f, w2, h2, tx, i, &t, 0x11, 0); }
}
static inline void drawAt(int x, int y, int i, GXC& c, GXC& t) {
    f32 ww;
    f32 hh;
    texSize(i, ww, hh);
    dS(x, y, ww, hh, i, c, t);
}
#define drawSized dS
#endif
