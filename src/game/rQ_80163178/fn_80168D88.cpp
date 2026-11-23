/* AI: move the unit along its route toward a named destination (names guessed). */
#include "game/rQ_80163178/common.h"
struct P34 { u8 pad[0x34]; u8 b34; };
extern "C" {
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA500;
FE10_PROTO extern void *lbl_804CA520;
#else
extern u32 lbl_804CA500;
extern u32 lbl_804CA520;
#endif
extern u8 lbl_803CAB38[];
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, u32);
#endif
#if TARGET_PC
FE10_PROTO void fn_80103CE4(Unit*, int, p32arg, p32arg, void*);
#else
void fn_80103CE4(Unit*, int, int, int, void*);
#endif
void fn_80165F94(Unit*, int, int);
void fn_80116658(Map*, int, int);
u8 fn_80116A68(Map*, s8*, s8*, int, u8*);
void fn_800620A8(void*, f32, f32);
void fn_800453B4(AiAct*, int);
void fn_801034B4(Unit*, void*);
void fn_80103410(Unit*, u8*, int, void*);

static inline void Step(AiAct* a, s8& x, s8& y, int k) {
    fn_800620A8(lbl_803CAB38, x, y);
    fn_800453B4(a, k);
    a->y = y;
    a->x = x;
}

void fn_80168D88(P34* p) {
    AiAct* a = &lbl_803CA870;
    Unit* u = a->unit;
    int k = fn_8011B77C(u->skills, lbl_804CA500);
    s8 x = u->x;
    s8 y = u->y;
    if (u->m3D0[0] == 0x40) {
        if (fn_8011B77C(u->skills, lbl_804CA520)) {
            if (p->b34 && (a->x0 != a->x || a->y0 != a->y)) {
                fn_80103CE4(u, 0x10, a->x, a->y, p);
            }
            return;
        }
        fn_80165F94(u, 6, -1);
        fn_80116658(&lbl_803EC898, a->x, (s8)*(u8*)&a->y);
        switch (fn_80116A68(&lbl_803EC898, &x, &y, k, 0)) {
        case 1:
            Step(a, x, y, 0x25);
            break;
        case 2:
            Step(a, x, y, 0x2E);
            break;
        }
        if (p->b34 && (a->x0 != a->x || a->y0 != a->y)) {
            fn_801034B4(u, p);
        }
    } else {
        switch (fn_80116A68(&lbl_803EC898, &x, &y, k, u->m3D0)) {
        case 1:
            Step(a, x, y, 0x25);
            break;
        case 2:
            Step(a, x, y, 0x2E);
            break;
        }
        if (p->b34 && (a->x0 != a->x || a->y0 != a->y)) {
            fn_80103410(u, u->m3D0, 0x40, p);
        }
    }
}
}
