/* AI: top-level action selection, 80152274..80152C20. */
#include "game/rM_8014C9F8/ai.h"

extern "C" {

extern int fn_80152C20(void*, void*, u8);
extern int fn_8015279C(Unit*, s8, s8);
#if TARGET_PC
extern FE10_PROTO int fn_80169718(Unit*, ptr32<const void>, ptr32<const void>);
#else
extern int fn_80169718(Unit*, void*, void*);
#endif
extern int fn_8016335C(Unit*);
extern int fn_80163178(Unit*);
extern int fn_801635B8(Unit*, u16);
extern int fn_80163808(Unit*, u16);
extern int fn_80163C8C(Unit*, u16);
extern int fn_80164064(Unit*, u16);
extern int fn_80164330(Unit*, u16);
extern void fn_80164BA8(Unit*);

static inline void AiFinish(Unit* u) {
    if (lbl_803CA870.action == 1) {
        s8 c = fn_80172748(u);
        if (c >= 0) {
            if (lbl_804183F0.done) {
                fn_800453B4(&lbl_803CA870, 0x3D);
            } else {
                int x = u->x;
                int y = u->y;
                fn_80160610(0x3D, x, y, u, x, y, 0, c, 0);
            }
        }
    }
}

#pragma use_lmw_stmw off
int fn_80152940(Unit* u) {
    Unit* t = (Unit*)fn_80106F54(u->ai);
    if (t->flags10C & 0x98) {
        lbl_804183F0.res[0] = 1;
        return 0;
    }
    if (t->flags10C & 4) {
        lbl_804183F0.res[0] = 4;
    } else {
        lbl_804183F0.res[0] = 0;
    }
    return fn_8015279C(u, t->x, t->y);
}

#pragma use_lmw_stmw off
void fn_801529DC(Unit* u) {
    s8 y = fn_80106F10(u->ai);
    fn_8015279C(u, fn_80106ECC(u->ai), y);
}

#pragma use_lmw_stmw off
int fn_80152A34(Unit* u) {
    s16 x;
    s16 y;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        return 0;
    }
    if (fn_8016DC30(u, 0, &x, &y) == 1) {
        fn_80160610(1, (s8)x, (s8)y, NULL, (s8)x, (s8)y, -1, 0, 0);
    }
    return 1;
}

#pragma use_lmw_stmw off
int fn_80152C18(void) { return 1; }

/* from fn_80152274.cpp */
static inline void AiFinish2(Unit* u) {
    if (lbl_803CA870.action == 1) {
        s8 c = fn_80172748(u);
        if (c >= 0) {
            if (lbl_804183F0.done) {
                fn_800453B4(&lbl_803CA870, 0x3D);
            } else {
                int x = (s8)*(u8*)&u->x;
                int y = u->y;
                fn_80160610(0x3D, x, y, u, x, y, 0, c, 0);
            }
        }
    }
}
#pragma use_lmw_stmw off
int fn_8015246C(Unit* u) {
    s16 x;
    s16 y;
    Fn3 f6;
    Fn3 f5;
    Fn2 f4;
    Fn2 f3;
    Fn2 f2;
    Fn2 f1;
    f3.u = u;
    f3.vt = lbl_80387338;
    f4.u = u;
    f4.vt = lbl_80387308;
    if (fn_801699C8(u, &f4, &f3) == 0) {
        f2.u = u;
        f2.vt = lbl_80387308;
        if (fn_8016CD04(u, &f2) == 0) {
            f1.vt = lbl_80387338;
            f1.u = u;
            f6.u = u;
            f6.vt = lbl_80387248;
            f6.b = 1;
            if (fn_80152C20(&f6, &f1, 0xF) == 0) {
                f5.u = u;
                f5.vt = lbl_80387248;
                f5.b = 1;
                if (fn_8016E50C(&f5, u, &x, &y)) {
                    fn_8016F94C(u, x, y, 1, 0xFFFF, 1, 0, -1);
                }
            }
        }
    }
    AiFinish2(u);
    return 1;
}

/* from fn_80152274.cpp */
#pragma use_lmw_stmw off
int fn_8015279C(Unit* u, s8 x, s8 y) {
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        return 0;
    }
    fn_8016F94C(u, x, y, 1, 0xFFFF, 1, 0, -1);
    if (lbl_804183F0.done == 0 ||
        (x != u->x && u->x == lbl_803CA870.x && y != u->y && u->y == lbl_803CA870.y)) {
        fn_8016F9C0(u, x, y, 1, 0xFFFF, 1, 0, -1);
    }
    if (lbl_804183F0.done != 0) {
        s8 ax = lbl_803CA870.x;
        int ar = fn_80106ECC(u->ai);
        if (ar == ax) {
            s8 ay = lbl_803CA870.y;
            int br = fn_80106F10(u->ai);
            if (br == ay && fn_800A05B0(0xE, lbl_803CA870.x, (s8)*(u8*)&lbl_803CA870.y)) {
                fn_800453B4(&lbl_803CA870, 0xE);
            }
        }
    }
    return 1;
}

/* from fn_80152274.cpp */
#pragma use_lmw_stmw off
int fn_80152AC8(Unit* u) {
    Fn2 f1;
    Fn2 f2;
    if (lbl_804183F0.flags & 4) {
        return 1;
    }
    f2.u = u;
    f2.vt = lbl_80387338;
    f1.u = u;
    f1.vt = lbl_80387308;
    if (fn_80169718(u, &f1, &f2) == 0 && fn_8016335C(u) != 0 && fn_80163178(u) != 0) {
        int k = 0x10000;
        if (fn_801635B8(u, k - 1)) {
            return 1;
        }
        if (fn_80163808(u, k - 1)) {
            return 1;
        }
        if (fn_80163C8C(u, k - 1)) {
            fn_80164BA8(u);
        } else if (fn_80164064(u, k - 1)) {
            fn_80164BA8(u);
        } else if (fn_80164330(u, k - 1)) {
            fn_80164BA8(u);
        }
    }
    return 1;
}

#pragma use_lmw_stmw off
int fn_80152604(Unit* u) {
    s16 x;
    s16 y;
    Fn3 f4;
    Fn3 f2;
    Fn3 f6;
    Fn3 f5;
    Fn2 f3;
    Fn2 f1;
    f3.vt = lbl_80387338;
    f3.u = u;
    f4.u = u;
    f4.vt = lbl_80387228;
    f4.b = 1;
    if (fn_801699C8(u, &f4, &f3) == 0) {
        f2.u = u;
        f2.vt = lbl_80387228;
        f2.b = 1;
        if (fn_8016CD04(u, &f2) == 0) {
            f1.vt = lbl_80387338;
            f1.u = u;
            f6.u = u;
            f6.vt = lbl_80387228;
            f6.b = 1;
            if (fn_80152C20(&f6, &f1, 0xF) == 0) {
                f5.u = u;
                f5.vt = lbl_80387228;
                f5.b = 1;
                if (fn_8016E50C(&f5, u, &x, &y)) {
                    fn_8016F94C(u, x, y, 1, 0xFFFF, 1, 0, -1);
                }
            }
        }
    }
    AiFinish2(u);
    return 1;
}

#pragma use_lmw_stmw off
int fn_80152274(Unit* u) {
    s16 x;
    s16 y;
    Unit* a = (Unit*)fn_80106F54(u->ai);
    if (a->flags10C & 0x98) {
        lbl_804183F0.res[0] = 1;
        return 0;
    }
    if (a->flags10C & 4) {
        lbl_804183F0.res[0] = 4;
        return 0;
    }
    {
    Fn3 f4;
    Fn3 f2;
    Fn3 f6;
    Fn3 f5;
    Fn2 f3;
    Fn2 f1;
    f3.vt = lbl_80387338;
    f3.u = u;
    f4.u = u;
    f4.vt = lbl_80387238;
    f4.b = 1;
    if (fn_801699C8(u, &f4, &f3) == 0) {
        f2.u = u;
        f2.vt = lbl_80387238;
        f2.b = 1;
        if (fn_8016CD04(u, &f2) == 0) {
            f1.vt = lbl_80387338;
            f1.u = u;
            f6.u = u;
            f6.vt = lbl_80387238;
            f6.b = 1;
            if (fn_80152C20(&f6, &f1, 0xF) == 0) {
                f5.u = u;
                f5.vt = lbl_80387238;
                f5.b = 1;
                if (fn_8016E50C(&f5, u, &x, &y)) {
                    fn_8016F94C(u, x, y, 1, 0xFFFF, 1, 0, -1);
                }
            }
        }
    }
    }
    AiFinish2(u);
    lbl_804183F0.res[0] = 0;
    return 1;
}
}
