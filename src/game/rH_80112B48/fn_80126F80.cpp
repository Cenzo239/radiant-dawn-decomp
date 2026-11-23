/* Copy class, stats, skills and items between units, 80126F80. */
/* Unit copy and stat clamp, 80127134, 80127DEC. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern void fn_80111C78(Inv*, Inv*);
extern s8 fn_801243F4(Unit*);
extern void* lbl_804CA4EC;

struct Sk { u32 a, b; };
struct UC {
    u8 pad0[0xE4];
    u32 e4, e8, ec, f0, f4, f8;
    u8 fc[8];
    u8 pad104[4];
    u32 w108, w10C;
    u16 h110, h112;
    u8 b114[0x15];
    u8 pad129[3];
    Sk sk[18];
    Inv inv[7];
    u16 h2d4[12];
    u8 pad2EC[4];
    u32 w2f0[4];
    u8 sup[9][8];
    u8 pad348[4];
    u32 w34c[3];
    u8 pad358[4];
    u32 w35c[3];
    u8 pad368[4];
    u32 w36c[3];
    u8 b378, b379;
    s16 h37a;
    u16 h37c, h37e;
    u8 pad380[2];
    u16 h382[6];
    u8 b38e, b38f, b390;
};
static inline void CP(u16* w,const u16* q){ u16 x=*q++; u16 y=*q; *w++=x; *w=y; }


void fn_80126F80(UC* d, UC* s) {
    if (s != 0 && s != d) {
    d->f0 = s->f0;
    ((u8*)&d->fc)[2] = ((u8*)&s->fc)[2];
    ((u8*)&d->fc)[3] = ((u8*)&s->fc)[3];
    d->b114[0] = s->b114[0];
    d->b114[2] = s->b114[2];
    d->b114[5] = s->b114[5];
    d->b114[6] = s->b114[6];
    d->b114[7] = s->b114[7];
    d->b114[8] = s->b114[8];
    d->b114[9] = s->b114[9];
    d->b114[10] = s->b114[10];
    d->b114[11] = s->b114[11];
    d->b114[12] = s->b114[12];
    d->b114[13] = s->b114[13];
    d->b114[14] = s->b114[14];
    d->b114[15] = s->b114[15];
    d->b114[16] = s->b114[16];
    d->b114[17] = s->b114[17];
    d->b114[18] = s->b114[18];
    d->b114[19] = s->b114[19];
    d->b114[20] = s->b114[20];
    {
        struct Skk { Sk sk[18]; };
        *(Skk*)d->sk = *(Skk*)s->sk;
    }
    {
        int i;
        for (i = 0; i < 6; i++) {
CP(&d->h2d4[i * 2], &s->h2d4[i * 2]);
        }
    }
    {
        int i;
        for (i = 0; i < 7; i++) {
            fn_80111C78(&d->inv[i], &s->inv[i]);
        }
    }
    d->w10C |= 0x20000000;
    }
}
}
