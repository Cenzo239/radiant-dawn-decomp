/* fn_8019F5E8: file menu sound fade; fn_8019FD1C: buffer holder destructor; fn_8019FF0C: help window scissor callback. */
#include "game/rF_8017F400/types.h"
extern "C" {
class Snd { public: virtual void v08(); virtual void v0C(); virtual int v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(int); virtual void v28(int); };
typedef struct Fm { u8 pad[0x14]; u8 x14; } Fm;
typedef struct Buf { void* p; u8 pad4[0xc-4]; u8 own; u8 padd[3]; void* vt; } Buf;
typedef struct HW { u8 pad[0xf4]; f32 xf4, xf8; u8 padfc[0x10c-0xfc]; f32 x10c, x110; } HW;
extern Fm* lbl_804CB934;
extern int fn_800CD4DC(void);
extern Snd* fn_8024F3FC(int);
extern void fn_80250D64(int, f32, f32);
extern char lbl_80380940[];
extern void fn_80078E24(void*);
extern void fn_80079210(void*);
extern HW lbl_8041EB20;
extern void fn_803080DC(u32, u32, u32, u32);
void fn_8019F5E8(void) {
    f32 v = 500.0f;
    switch (lbl_804CB934->x14) {
    case 5:
    case 0:
        if (fn_800CD4DC() != 0x1e) {
            Snd* s = fn_8024F3FC(3);
            if (s && s->v10()) {
                int k = fn_800CD4DC();
                switch (k) {
                case 0x1f: case 0x20: case 0x21:
                    v = 1500.0f;
                    s->v24(0x5dc);
                    break;
                default:
                    s->v28(0xfa);
                    break;
                }
            }
        }
        break;
    }
    fn_80250D64(6, 1.0f, v);
}
Buf* fn_8019FD1C(Buf* b, int del) {
    if (b) {
        if (b) {
            if (b) {
                b->vt = lbl_80380940;
                if (b->own) {
                    fn_80078E24(b->p);
                    b->p = 0;
                    b->own = 0;
                }
            }
        }
        if (del > 0) fn_80079210(b);
    }
    return b;
}
void fn_8019FF0C(void) {
    HW* w = &lbl_8041EB20;
    f32 c, b, a;
    c = w->x10c;
    b = w->xf8;
    a = w->xf4;
    fn_803080DC(8.0f + a, 8.0f + b, c - 16.0f, w->x110 - 8.0f);
}
}
