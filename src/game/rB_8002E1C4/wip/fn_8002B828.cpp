/* NEAR MISS: fn_8002B828 13 words. The original keeps `li r0,1` for the side store and `li r3,1` in the over() inline; ours CSEs the constant 1 into r30 across the call at two sites. No spelling of the store, the inline or its return type changed this. */
#include "game/rB_8002E1C4/battle.h"

struct Roll { u8 pad[0xa2]; u8 xa2; };
extern Roll lbl_803C8DA0;
struct GS2 { u8 pad[0x10]; u8 x10; u8 pad11[0xc0 - 0x11]; s16 xc0[4]; int xc8[4]; };
extern GS2 lbl_803CAB38;
extern void* lbl_804CA698;
extern "C" {
int fn_8011B77C(void* list, void* key);
void fn_8002600C(void* log, int code, int v);
void fn_80027D9C(Battle* b, BU* a, BU* d, int k, int n);

static inline int over(Battle* b) {
    if (b->a.u.s114 == 0) return 1;
    return b->b.u.s114 == 0;
}
static inline void strikeA(Battle* b, int n) {
    b->f15e4 = 0;
    fn_80027D9C(b, &b->a, &b->b, 0x25, n);
}
static inline void strikeB(Battle* b, int n) {
    b->f15e4 = 1;
    fn_80027D9C(b, &b->b, &b->a, 0x26, n);
}
#define KILL(u, army) { \
    (*(u16*)((u8*)(u) + 0x386))++; \
    (*(u16*)((u8*)(u) + 0x384))++; \
    *((u8*)(u) + 0x38e) = lbl_803CAB38.x10; \
    switch ((army)[8]) { \
    case 0: lbl_803CAB38.xc8[0]++; lbl_803CAB38.xc0[0]++; break; \
    case 1: lbl_803CAB38.xc8[1]++; lbl_803CAB38.xc0[1]++; break; \
    case 2: lbl_803CAB38.xc8[2]++; lbl_803CAB38.xc0[2]++; break; \
    case 3: lbl_803CAB38.xc8[3]++; lbl_803CAB38.xc0[3]++; break; \
    } \
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
        strikeB(b, 0);
        if (over(b)) goto end;
        if (b->b.x482 == 0) {
            strikeA(b, 0);
            if (over(b)) goto end;
        }
    } else {
        strikeA(b, 0);
        if (over(b)) goto end;
        if (b->a.x482 == 0) {
            strikeB(b, 0);
            if (over(b)) goto end;
        }
    }
    if (b->a.x44c >= b->b.x44c + 4 && !(b->f15ec & 0x200) && !(b->f15ec & 0x8000) && !lbl_803C8DA0.xa2 && !b->b.x482) {
        strikeA(b, 1);
        if (over(b)) goto end;
    }
    if (b->b.x44c >= b->a.x44c + 4 && !lbl_803C8DA0.xa2 && !b->a.x482) {
        strikeB(b, 1);
        if (over(b)) goto end;
    }
end:
    if (b->a.u.s114 == 0) {
        fn_8002600C(b->log, 0xb, 0);
        KILL(b->b.u.u3f0, b->a.u.f4)
    } else if (b->b.u.s114 == 0) {
        fn_8002600C(b->log, 0x16, 0);
        KILL(b->a.u.u3f0, b->b.u.f4)
    }
}
}
