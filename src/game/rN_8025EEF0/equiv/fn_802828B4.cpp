/* r19: copied from wip/fn_802828B4_r17.cpp; `sched` level (same instructions per basic block, order differs). */
/* NEAR MISS: fn_802828B4, 2 words short, 18 masked lines. The 0x1A flag term wants extrwi/neg/or/srawi (bitfield-like test); registers after that. */
/* Confirm dialog: layout from two messages and the YES/NO labels */
#include "game/rN_8025EEF0/calls.h"

extern "C" {
void* memset(void* p, int v, u32 n);
void* memcpy(void* d, const void* s, u32 n);
int fn_800CA3DC(const char* s, int a, f32 v);
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
extern char lbl_80373AA0[];

struct Dlg {
    s16 x0; s16 x2; s16 x4; s16 x6; s16 x8; s16 xA; s16 xC; s16 xE; s16 x10;
    s16 x12; s16 x14; s16 x16; s16 x18; s16 x1A; s16 x1C; s16 x1E;
    s16 x20; s16 x22; s16 x24; s16 x26; u8 pad28[2];
    char line[2][7][0x41];
    s8 cnt[2];
};

void fn_802828B4(Dlg* d, const char** msg, int flag, s16 type) {
/*P*/
    int i;
    const char* st;
    int n;
    int k;
    const char* s;
    int w1;
    int w2;
/*E*/
    memset(d, 0, 0x3BA);
    d->x0 = 1;
    d->xC = -1000;
    d->x8 = -1000;
    d->x4 = -1000;
    d->xA = -1000;
    d->x6 = -1000;
    d->x2 = -1000;
    d->xE = 0;
    d->x10 = 0;
    d->x14 = 100;
    d->x16 = type;
    d->x1C = 200;
    if (flag) d->x12 |= 4;
    switch (d->x16) {
    case 0:
        break;
    case 1:
        d->x12 |= 2;
        break;
    }
    for (i = 0; i < 2; i++) {
        s = fn_800D0864(msg[i]);
        msg[i] = s;
        n = 0;
        st = s;
        k = 0;
        if (s == 0) continue;
        for (;;) {
            if (*s == 0 || *s == '\n') {
                if (n > 0) memcpy(d->line[i][k], st, n);
                d->line[i][k][n] = 0;
                {
                    f32 w = fn_800CA3DC(d->line[i][k], -1, 1.0f);
                    if (w > d->x1C) d->x1C = w;
                }
                k++;
                if (*s == 0) break;
                s++;
                n = 0;
                st = s;
            } else {
                s++;
                n++;
            }
        }
        d->cnt[i] = k;
    }
    {
d->x1C = d->x1C + 0x18;
int a = (d->x12 & 4) ? 0x28 : 0;
int b = ((u16)((d->x12 >> 1) & 1) != 0) ? 0x1A : 0;
d->x1E = d->cnt[0] * 0x14 + (d->cnt[1] ? d->cnt[1] * 0x14 + 8 : 0) + b + (a + 0x20);
    }
    w1 = (s16)fn_800CA3DC(fn_800D0864(lbl_80373AA0), -1, 1.0f);
    w2 = (s16)fn_800CA3DC(fn_800D0864(lbl_80373AA0 + 7), -1, 1.0f);
    {
        int a = (d->x12 & 4) ? 0x28 : 0;
        switch (d->x16) {
        case 0:
        case 1: {
            s16 x = (0x260 - d->x1C) / 2;
            s16 g;
            d->x18 = x;
            d->x1A = (0x1E0 - d->x1E) / 2;
            g = (d->x1C - w1 - w2) / 3;
            d->x20 = x + g;
            d->x24 = g * 2 + (x + w1);
            d->x22 = d->x1A + a + d->cnt[0] * 0x14 + 0x12;
            d->x26 = d->x22;
            break;
        }
        }
    }
    if ((d->x0 & 1) && d->xE > 0) {
        d->xE = d->xE - 1;
        d->x2 = fn_8017F68C(d->x6, d->xA, d->x10 - d->xE, d->x10, 4);
        d->x4 = fn_8017F68C(d->x8, d->xC, d->x10 - d->xE, d->x10, 4);
    }
}
}
