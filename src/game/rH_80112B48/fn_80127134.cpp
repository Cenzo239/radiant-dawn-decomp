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

#pragma push
#pragma use_lmw_stmw on
void fn_80127134(UC* d, UC* s) {
    if (s != 0 && s != d) {
    d->e4 = 0;
    d->e8 = 0;
    d->ec = s->ec;
    d->f0 = s->f0;
    d->f4 = s->f4;
    d->f8 = s->f8;
    d->fc[0] = s->fc[0];
    d->fc[1] = s->fc[1];
    d->fc[2] = s->fc[2];
    d->fc[3] = s->fc[3];
    d->fc[4] = s->fc[4];
    d->fc[5] = s->fc[5];
    d->fc[6] = s->fc[6];
    d->fc[7] = s->fc[7];
    *(u64*)&d->w108 = *(u64*)&s->w108;
    d->h110 = s->h110;
    d->h112 = s->h112;
    d->b114[0] = s->b114[0];
    d->b114[1] = s->b114[1];
    d->b114[2] = s->b114[2];
    d->b114[3] = s->b114[3];
    d->b114[4] = s->b114[4];
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
        for (i = 0; i < 7; i++) {
            fn_80111C78(&d->inv[i], &s->inv[i]);
        }
    }
    {
        int i;
        for (i = 0; i < 6; i++) {
CP(&d->h2d4[i * 2], &s->h2d4[i * 2]);
        }
        for (i = 0; i < 4; i++) {
            d->w2f0[i] = s->w2f0[i];
        }
    }
    {
        int i, j;
        for (i = 0; i < 9; i++) {
            UC* a = (UC*)((u8*)s + i * 8);
            UC* b = (UC*)((u8*)d + i * 8);
            for (j = 0; j < 8; j++) {
                b->sup[0][j] = a->sup[0][j];
            }
        }
    }
    d->w34c[0] = s->w34c[0];
    d->w34c[1] = s->w34c[1];
    d->w34c[2] = s->w34c[2];
    d->w35c[0] = s->w35c[0];
    d->w35c[1] = s->w35c[1];
    d->w35c[2] = s->w35c[2];
    d->w36c[0] = s->w36c[0];
    d->w36c[1] = s->w36c[1];
    d->w36c[2] = s->w36c[2];
    d->b378 = s->b378;
    d->b379 = s->b379;
    d->h37a = s->h37a;
    d->h37c = s->h37c;
    d->h37e = s->h37e;
    d->h382[0] = s->h382[0];
    d->h382[1] = s->h382[1];
    d->h382[2] = s->h382[2];
    d->h382[3] = s->h382[3];
    d->h382[4] = s->h382[4];
    d->h382[5] = s->h382[5];
    d->b38e = s->b38e;
    d->b38f = s->b38f;
    d->b390 = s->b390;
    }
}
#pragma pop

static inline int StatJ(Unit* u, int i) {
    return u->stat[i] + u->job->base[i];
}

static inline s16 StatBaseF(Unit* u, int i) {
    int a = StatJ(u, i);
    int v = u->person->base[i] + a;
    if (v > u->job->max[i]) {
        v = u->job->max[i];
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

#define CLAMP_STAT(i)                                                   \
    m = u->job->max[i];                                                 \
    if (u->job->promoted && fn_8011B77C(u->skills, lbl_804CA4EC)) {     \
        m = ((Job*)u->job->promoted)->max[i];                           \
    }                                                                   \
    {                                                                   \
        s16 c = m - (u->person->base[i] + u->job->base[i]);             \
        if (u->stat[i] > c) {                                           \
            u->stat[i] = c;                                             \
        }                                                               \
    }

void fn_80127DEC(Unit* u) {
    int m;
    CLAMP_STAT(0)
    CLAMP_STAT(1)
    CLAMP_STAT(2)
    CLAMP_STAT(3)
    CLAMP_STAT(4)
    CLAMP_STAT(5)
    CLAMP_STAT(6)
    CLAMP_STAT(7)
    m = 0x63;
    if (u->job->promoted && fn_8011B77C(u->skills, lbl_804CA4EC)) {
        m = 0x63;
    }
    {
        s8 c = m - (u->person->level1F + u->job->levelF0);
        if ((s8)u->exp115 > c) {
            u->exp115 = c;
        }
    }
    m = 0x14;
    if (u->job->promoted && fn_8011B77C(u->skills, lbl_804CA4EC)) {
        m = 0x14;
    }
    {
        s8 c = m - u->job->f5;
        if (u->u116 > c) {
            u->u116 = c;
        }
    }
    {
        s16 v = StatBaseF(u, 0);
        {
            s16 c = v + fn_801243F4(u);
            if (u->hp > c) {
                u->hp = c;
            }
        }
    }
    if (u->hp < 0) {
        u->hp = 0;
    }
}

}
