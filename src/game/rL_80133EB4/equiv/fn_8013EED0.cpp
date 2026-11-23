/* fn_8013EED0: functionally equal (regs level per tools/check_regs.py; registers differ from the original). Coloured range tiles. From wip/near4.cpp with the step order fixed. */
/* ===== fn_8013EED0 (0x268): masked diff 4 lines, 66 lines of ranks. Parameter must be r23 but takes r31; lis base r31, g r30, p8 r28, p16 r29, offsets r27 and r22. ===== */
/* Draws the movement and attack range tiles over the map. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct EP { u8 pad[0x34]; f32 x34; };
struct C4 { u8 r, g, b, a; };
struct Map {
    int w;
    int h;
    u8 pad8[0x200D - 8];
    u8 mark[0x40][0x40];
    u8 pad300d[0x710E - 0x300D];
    s16 rng[0x40][0x40];
    u8 pad910e[0xD18E - 0x910E];
    u16 atk[0x40][0x40];
    u8 padf18e[0xF18E - 0xF18E];
    s8 sel[0x40][0x40];
};
struct Tab { C4 c[4]; };
extern "C" {
extern Map lbl_803EC898;
extern Tab lbl_803863A8[];
extern int fn_80068D74(void);
extern void fn_8013E7FC(void);
extern void fn_8013EA08(s8, s8, C4*, f32);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80011838(int);

#define G lbl_803EC898
#define CELL(CK, BODY) \
        for (y = (s8)(G2->h - 1); (s8)y >= 0; y--) { \
            x = (s8)(G.w - 1); \
            p8 = x + ((u8*)G2 + y * 0x40); \
            p16 = x * 2 + ((u8*)G2 + y * 0x80); \
            for (; (s8)x >= 0; p8--, p16 -= 2, x--) { BODY } \
        }
#define SHOW \
    if (*(s8*)(p8 + 0xF18E)) { \
        if (*(s16*)(p16 + 0x710E) >= 0) fn_8013EA08((s8)x, (s8)y, tab[3].c, p->x34); \
    } else if (*(s16*)(p16 + 0x710E) >= 0) { \
        fn_8013EA08((s8)x, (s8)y, tab[1].c, p->x34); \
    } else if (*(u16*)(p16 + 0xD18E)) { \
        fn_8013EA08((s8)x, (s8)y, tab[2].c, p->x34); \
    }
void fn_8013EED0(EP* p) {
    /*P*/
    Map* G2;
    u8* p16;
    int x;
    int y;
    BOOL any;
    u8* p8;
    Tab* tab;
/*E*/
    if (fn_80068D74()) {
        any = 0;
        fn_8013E7FC();
        G2 = &lbl_803EC898;
        tab = lbl_803863A8;
        CELL(0, if (p8[0x200D] == 0) { any = 1; } else SHOW)
        if (any) {
            fn_80021BA4(1, 4, 5, 0);
            G2 = &lbl_803EC898;
            tab = lbl_803863A8;
            CELL(0, if (p8[0x200D] == 0) SHOW)
        }
        fn_80011838(-1);
    }
}
}

