#include "game/rL_80133EB4/types.h"
struct Color { u8 r, g, b, a; };
struct WP {
    u8 pad[0x30];
    u8 x30; u8 x31; u8 x32; u8 x33; u8 x34; u8 pad35; s16 x36;
    f32 x38, x3c, x40;
    u8 pad44[0x54 - 0x44];
    Vec x54, x60;
    u8 pad6c[0x78 - 0x6C];
    Color x78;
    void* x7c;
};
struct MM { u8 pad[0xB1]; u8 xb1; };
extern "C" {
extern u8 lbl_80386540[];
extern Color lbl_804CA720;
extern WP* fn_80081050(void*, void*);
extern MM* fn_8013B9A8(void);
static inline void SetC(WP* w, Color c) { w->x78 = c; }
static inline void Set2(WP* w) {
    Vec a = {0.0f, 0.0f, 0.0f};
    w->x54 = a;
    Vec b = {0.0f, 0.0f, 0.0f};
    w->x60 = b;
}
WP* fn_80146A4C(void* parent) {
    WP* w = fn_80081050(lbl_80386540, parent);
    w->x30 = 1;
    w->x7c = 0;
    w->x33 = 0;
    w->x34 = 0;
    w->x31 = 0;
    w->x38 = 0.0f;
    w->x3c = 0.0f;
    w->x40 = 0.0f;
    w->x36 = 300;
    Set2(w);
    SetC(w, lbl_804CA720);
    w->x32 = fn_8013B9A8()->xb1;
    return w;
}
}
