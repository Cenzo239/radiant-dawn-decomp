/* fn_8002B828 (r16): draft, same size structure but 80 lines off by the scorer. The original keeps every short temporary in r3 and never holds the constant 1 in a saved register across fn_80027D9C; ours CSEs the f15e4 = 1 store with over()'s 1 into r30. #pragma opt_propagation off removes the CSE (61) but temporaries then use r0, and global_optimizer off gives 60, so a different construct for over() / the strike sequence is still missing. */
/* One battle exchange: attacker and defender strikes, then the death bookkeeping (names guessed). */
#define lbl_803C8E80 lbl_unused
#include "game/rB_8002E1C4/battle.h"
#undef lbl_803C8E80

struct Roll { u8 pad[0xa2]; u8 xa2; u8 xa3; };
struct Stats {
    u8 pad0[0x10];
    u8 x10;
    u8 pad11[0xc0 - 0x11];
    s16 kills[4];   /* 0xC0 */
    u32 deaths[4];  /* 0xC8 */
};
struct Rec {
    u8 pad0[0x384];
    u16 x384;
    u16 x386;
    u8 pad388[0x38e - 0x388];
    u8 x38e;
};
extern Roll lbl_803C8DA0;
extern Stats lbl_803CAB38;
extern void* lbl_804CA698;
extern "C" {
void fn_8002600C(void* log, int code, int v);
int fn_8011B77C(void* list, void* key);
void fn_80027D9C(Battle* b, BU* a, BU* d, int k, int n);

static inline void side(Battle* b, int s) { b->f15e4 = s; }
static inline int over(Battle* b);
static inline int strike(Battle* b, BU* x, BU* y, int k, int n, int s);
static inline int over(Battle* b) {
    if (b->a.u.s114 == 0) return 1;
    return b->b.u.s114 == 0;
}

static inline void tally(Unit* w, Unit* l) {
    Stats* g = &lbl_803CAB38;
    ((Rec*)w)->x386++;
    ((Rec*)w)->x384++;
    ((Rec*)w)->x38e = g->x10;
    switch (l->f4[8]) {
    case 0:
        g->deaths[0]++;
        g->kills[0]++;
        break;
    case 1:
        g->deaths[1]++;
        g->kills[1]++;
        break;
    case 2:
        g->deaths[2]++;
        g->kills[2]++;
        break;
    case 3:
        g->deaths[3]++;
        g->kills[3]++;
        break;
    }
}

static inline int strike(Battle* b, BU* x, BU* y, int k, int n, int s) {
    side(b, s);
    fn_80027D9C(b, x, y, k, n);
    return over(b);
}

void fn_8002B828(Battle* b) {
    if (b->b.u.s114 == 0) {
        fn_8002600C(b->log, 0x24, 0);
        fn_8002600C(b->log, 0x71, 0);
        fn_8002600C(b->log, 0x2a, 0);
        fn_8002600C(b->log, 0x16, 0);
        return;
    }
    if (fn_8011B77C(b->b.u.x12c, lbl_804CA698)) {
        if (strike(b, &b->b, &b->a, 0x26, 0, 1)) goto done;
        if (b->b.x482 == 0) {
            if (strike(b, &b->a, &b->b, 0x25, 0, 0)) goto done;
        }
    } else {
        if (strike(b, &b->a, &b->b, 0x25, 0, 0)) goto done;
        if (b->a.x482 == 0) {
            if (strike(b, &b->b, &b->a, 0x26, 0, 1)) goto done;
        }
    }
    if (b->a.x44c >= b->b.x44c + 4 && !(b->f15ec & 0x200) && !(b->f15ec & 0x8000) && !lbl_803C8DA0.xa2 && !b->b.x482) {
        if (strike(b, &b->a, &b->b, 0x25, 1, 0)) goto done;
    }
    if (b->b.x44c >= b->a.x44c + 4 && !lbl_803C8DA0.xa2 && !b->a.x482) {
        side(b, 1);
        fn_80027D9C(b, &b->b, &b->a, 0x26, 1);
    }
done:
    if (b->a.u.s114 == 0) {
        fn_8002600C(b->log, 0xb, 0);
        tally(b->b.u.u3f0, &b->a.u);
    } else if (b->b.u.s114 == 0) {
        fn_8002600C(b->log, 0x16, 0);
        tally(b->a.u.u3f0, &b->b.u);
    }
}
}
