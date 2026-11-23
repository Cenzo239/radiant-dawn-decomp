/* Sort camera script keys and index them by kind, 801301DC. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
struct W2 { u32 a, b; };
struct Ev {
    u8 kind;
    s16 key;
    W2 p;
    u32 c, d;
    
    
};
struct Evs {
    u8 pad[0x34];
    u32 v34;
    int maxk;
    u8 pad3c[4];
    Ev* ev;
    u8 n;
    u8 pad45;
    u8 cnt[5];
    u8 pad4b;
    Ev* first[5];
};
void fn_801301DC(Evs* s) {
    int i;
    s->cnt[0] = 0; s->first[0] = 0;
    s->cnt[1] = 0; s->first[1] = 0;
    s->cnt[2] = 0; s->first[2] = 0;
    s->cnt[3] = 0; s->first[3] = 0;
    s->cnt[4] = 0; s->first[4] = 0;
    s->v34 = 0;
    s->maxk = 0;
    for (i = 0; i < s->n; i++) {
        int j;
        for (j = 0; j < s->n - 1 - i; j++) {
            if (s->ev[j].key > s->ev[j + 1].key) {
                Ev t = s->ev[j];
                s->ev[j] = s->ev[j + 1];
                s->ev[j + 1] = t;
            }
        }
    }
    for (i = 0; i < s->n; i++) {
        int j;
        for (j = 0; j < s->n - 1 - i; j++) {
            if (s->ev[j].kind > s->ev[j + 1].kind) {
                Ev t = s->ev[j];
                s->ev[j] = s->ev[j + 1];
                s->ev[j + 1] = t;
            }
        }
    }
    for (i = 0; i < s->n; i++) {
        u8 k = s->ev[i].kind; if (s->first[k] == 0) s->first[k] = &s->ev[i]; s->cnt[k]++;
        if (s->ev[i].key > s->maxk) s->maxk = s->ev[i].key;
    }
}
}
