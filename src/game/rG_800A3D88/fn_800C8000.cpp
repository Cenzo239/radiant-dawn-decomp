#include "game/rG_800A3D88/types.h"

// Screen fade: start one of the fade modes.
extern "C" {
struct Fd { u8 p[0x30]; u8 mode; u8 p31; u16 st; u16 t; u16 n; f32 from; f32 to; int col; u8 p44[4]; void* buf; u8 tex[1]; };
struct Ph { u8 p[0x54]; Fd* m54; };
extern u8 lbl_803829A0[];
u32 fn_8030585C(int, int, int, int, int);
void* fn_80079958(u32, int);
void DCInvalidateRange(void*, u32);
void fn_80305A40(void*, void*, int, int, int, int, int, int);
void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
#if TARGET_PC
FE10_PROTO Ph* fn_80081050(void*, p32arg);
#else
Ph* fn_80081050(void*, int);
#endif
static inline void Grab(Fd* f) {
    u32 sz = fn_8030585C(0x260, 0x1C0, 4, 0, 0);
    if (f->buf == NULL) f->buf = fn_80079958(sz, 0x40);
    DCInvalidateRange(f->buf, sz);
    fn_80305A40(f->tex, f->buf, 0x260, 0x1C0, 4, 0, 0, 0);
    fn_80305C94(f->tex, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    Ph* q = fn_80081050(lbl_803829A0, 6);
    q->m54 = f;
}
void fn_800C8000(Fd* f, u32 mode, int time) {
    if (time == 0 || !(f->st & 0xD) || f->mode != mode) {
        f->mode = mode;
        f->st = 1;
        f->t = 0;
        f->n = (f32)time / 16.666666f;
        switch (mode) {
        case 0:
            f->st = 2;
            f->to = 0.0f;
            f->col = 0;
            break;
        case 1:
            f->st = 6;
            f->to = 1.0f;
            f->col = 0xFF;
            break;
        case 2:
            f->from = 1.0f;
            f->to = 0.0f;
            f->col = 0xFF;
            break;
        case 3:
            f->st |= 4;
            f->from = 0.0f;
            f->to = 1.0f;
            f->col = 0xFF;
            break;
        case 4:
            f->st = 10;
            f->to = 1.0f;
            f->col = -1;
            break;
        case 5:
            f->from = 1.0f;
            f->to = 0.0f;
            f->col = -1;
            break;
        case 6:
            f->st |= 8;
            f->from = 0.0f;
            f->to = 1.0f;
            f->col = -1;
            break;
        case 7:
            f->from = 1.0f;
            f->to = 0.0f;
            f->col = -1;
            Grab(f);
            break;
        case 8:
            f->mode = 7;
            f->st = 2;
            f->from = 1.0f;
            f->to = 1.0f;
            f->n = 0xFFFF;
            f->col = -1;
            Grab(f);
            break;
        case 9:
            if (f->buf == NULL) {
                f->st = 2;
                f->to = 0.0f;
                f->col = 0;
            } else {
                f->mode = 7;
                f->from = 1.0f;
                f->to = 0.0f;
                f->col = -1;
            }
            break;
        }
    }
}
}
