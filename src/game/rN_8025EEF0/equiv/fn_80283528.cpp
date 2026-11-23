/* r19: copied from wip/fn_80283528.cpp; `sched` level (same instructions per basic block, order differs). */
/* fn_80283528 12 words, fn_802836C0 4 words: scheduling only, the loads of the x position and the duration constant come out in the other order. */
/* Confirm dialog (lbl_80430920): open and input */
#include "game/rN_8025EEF0/calls.h"

struct Cursor {
    s16 m0, m2, m4, m6, m8, mA, mC, mE, m10;
    u8 pad12[2];
    s16 m14;
    u8 pad16[0xA];
    s16 m20, m22, m24, m26;
};

extern "C" {

extern Cursor lbl_80430920;
extern u8 lbl_804CC0B0[8];
extern const char* lbl_804CC0B8;
extern const char* lbl_804CC0BC;
extern const char* lbl_804CC0C0;
extern int lbl_804CC0C4;
extern u8 lbl_804CC0C8;
extern s16 lbl_804CC0CA;
extern s16 lbl_804CC0CC;
extern char lbl_80373AA0[];
void fn_802828B4(Cursor* c, void* a, int b, int d);
void fn_80253EE4(const char* s, f32 v);

static inline void setPos(Cursor* c, int y, int d, int x) {
    c->m6 = c->m2;
    c->m8 = c->m4;
    c->mA = x;
    c->mC = y;
    c->m10 = d;
    c->mE = d;
    if (d == 0) {
        c->m2 = x;
        c->m4 = y;
    }
    c->m0 |= 1;
}

void fn_80283528(void) {
    int z = 0;
    lbl_804CC0CC = z;
    switch (lbl_804CC0CA) {
    case 0:
    case 1:
        fn_802828B4(&lbl_80430920, lbl_804CC0B0, lbl_804CC0C8, 0);
        break;
    case 2:
    case 3:
        fn_802828B4(&lbl_80430920, lbl_804CC0B0, lbl_804CC0C8, 1);
        if (lbl_804CC0C4 == 0) {
            setPos(&lbl_80430920, lbl_80430920.m22, z, lbl_80430920.m20);
        } else if (lbl_804CC0C4 == 1) {
            setPos(&lbl_80430920, lbl_80430920.m26, z, lbl_80430920.m24);
        }
        break;
    }
    if (lbl_804CC0C8 != 0) {
        fn_80253EE4(lbl_80373AA0 + 0xD, 0.0f);
    }
}

void fn_802836C0(void* p) {
    u32 k = lbl_804CB5B8->v48();
    switch (lbl_804CC0CA) {
    case 0:
        if (k & 0x400) {
            fn_80253EE4(lbl_80373AA0 + 0x21, 0.0f);
            lbl_804CC0CC = 3;
            lbl_80430920.m14 = 300;
            lbl_80430920.m0 = 0;
            fn_80083B78(p);
        }
        break;
    case 1:
        break;
    case 2:
    case 3:
        if (k & 0x400) {
            if (lbl_804CC0C4 == 0) {
                if (lbl_804CC0B8 != 0) {
                    fn_80253EE4(lbl_804CC0B8, 0.0f);
                }
                lbl_804CC0CC = 1;
            } else if (lbl_804CC0C4 == 1) {
                if (lbl_804CC0BC != 0) {
                    fn_80253EE4(lbl_804CC0BC, 0.0f);
                }
                lbl_804CC0CC = 2;
            }
            lbl_80430920.m14 = 300;
            lbl_80430920.m0 = 0;
            fn_80083B78(p);
        } else if ((k & 0x800) && lbl_804CC0CA == 2) {
            if (lbl_804CC0C0 != 0) {
                fn_80253EE4(lbl_804CC0C0, 0.0f);
            }
            lbl_804CC0CC = 4;
            lbl_80430920.m14 = 300;
            lbl_80430920.m0 = 0;
            fn_80083B78(p);
        } else {
            if (k & 0x100001) {
                if (lbl_804CC0C4 == 1) {
                    fn_80253EE4(lbl_80373AA0 + 0x31, 0.0f);
                }
                lbl_804CC0C4 = 0;
                setPos(&lbl_80430920, lbl_80430920.m22, 4, lbl_80430920.m20);
            }
            if (k & 0x200002) {
                if (lbl_804CC0C4 == 0) {
                    fn_80253EE4(lbl_80373AA0 + 0x31, 0.0f);
                }
                lbl_804CC0C4 = 1;
                setPos(&lbl_80430920, lbl_80430920.m26, 4, lbl_80430920.m24);
            }
        }
        break;
    }
}

}
