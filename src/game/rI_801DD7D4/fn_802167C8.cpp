#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/fn_wf.h"
extern "C" {
extern u8 lbl_8038FAA0[], lbl_803CAB38[], lbl_803715F0[];
extern char lbl_80371974[];
const char** fn_8006074C(void*);
void fn_80290D04(char*, int, const char*, ...);
void* fn_80076F54(const char*);
struct W68 { WF w; int a40; LN l44; u8 x4c; s16 x4e, x50, x52, x54, x56; u8 p[8]; void* x60; int x64, x68; void* x6c; };
W68* fn_802167C8(W68* o, int x, int y, int w, int h, int z, int fl) {
    char buf[0x20];
    gInit((G40*)o, x, y, (s16)x + (s16)w, (s16)y + (s16)h, w, h, z, 0x10);
    o->w.vt = lbl_8038FAA0;
    o->x4c = 1;
    o->x4e = 0;
    o->x50 = -0x8000;
    o->x52 = -0x8000;
    o->x54 = 0x20;
    o->x56 = 1;
    o->x60 = fl ? fn_80079150(0xc) : 0;
    o->x64 = 0;
    o->x68 = 0;
    o->x6c = 0;
    ((Lst*)o)->v2C();
    fn_80290D04(buf, 0x20, lbl_80371974, *fn_8006074C(lbl_803CAB38));
    o->x6c = fn_80076F54(buf);
    if (!o->x6c) o->x6c = lbl_803715F0;
    return o;
}
}
