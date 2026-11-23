/* AI: move bonus commands and the per-unit driver procs, 8015F2DC..80160508. */
#include "game/rM_8014C9F8/ai.h"
#pragma auto_inline off

struct AiCmd {
    int op;
    int a;
    int b;
    int c;
    int d;
    u32 fl;
    u32 x;
    u32 y;
    u32 z;
    u32 w;
};

extern "C" {

extern AiCmd* lbl_804CB8B8;
#if TARGET_PC
FE10_PROTO extern p32ret lbl_804CB8B4;
#else
extern int lbl_804CB8B4;
#endif
extern u8 lbl_804CB8B0;
extern void fn_80129550(Unit*, int);
extern void fn_8015960C(Unit*);
extern u8 fn_801725A0(Unit*);
extern u8 lbl_80386F88[];
extern u8 lbl_80387020[];
extern u8 lbl_80387038[];
extern u8 lbl_80387060[];
extern void fn_80083DC4(void*, int);
extern void fn_80168BC0(void*);
extern void fn_800A20F4(void);
extern void fn_8004559C(AiAct*, int);
extern void fn_80166720(Unit*);
extern u32 fn_80159008(Unit*);
extern u8 fn_80158CA0(Unit*);
extern u32 fn_80159124(Unit*);
extern u8 fn_80158DB8(Unit*);
extern u32 fn_80159244(Unit*);
extern u8 fn_80158EE0(Unit*);
extern void fn_80164D18(Unit*);
extern void fn_80127A8C(Unit*);
extern int fn_80163178(Unit*);
extern int fn_80106E30(void*);
extern int fn_80152C18(Unit*);
extern int fn_80152274(Unit*);
extern int fn_8015246C(Unit*);
extern int fn_80152604(Unit*);
extern void fn_801529DC(Unit*);
extern int fn_80152A34(Unit*);
extern int fn_80152AC8(Unit*);
extern int fn_80152940(Unit*);
extern int fn_8016D0B0(Unit*);
extern void fn_800453CC(AiAct*);
extern void fn_800453FC(AiAct*);

#pragma use_lmw_stmw off
void fn_8015F5E8(Unit* u) {
    lbl_804CB8B0 = 1;
    u->w3B4 |= 0x8000;
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015F604(Unit* u) {
    fn_8015960C(u);
    lbl_804CB8B0 = 1;
}

#pragma use_lmw_stmw off
void fn_8015F62C(Unit* u) {
    fn_8015960C(u);
    lbl_804CB8B0 = 1;
}

#pragma use_lmw_stmw off
void fn_8015F654(Unit* u) { fn_80129550(u, lbl_804CB8B4); }
#pragma use_lmw_stmw off
void fn_8015F65C(void* p) { fn_80081194(lbl_80386F88, p); }

#pragma use_lmw_stmw off
void fn_8015F7F8(void) { fn_80081050(lbl_80387020, (void*)9); }
#pragma use_lmw_stmw off
BOOL fn_8015F808(void) { return fn_80083B84(lbl_80387020) != NULL; }
#pragma use_lmw_stmw off
void fn_8015F83C(void) { fn_80081050(lbl_80387038, (void*)9); }
#pragma use_lmw_stmw off
BOOL fn_8015F84C(void) { return fn_80083B84(lbl_80387038) != NULL; }
#pragma use_lmw_stmw off
void fn_8015F880(void) { fn_80081050(lbl_80387060, (void*)9); }
#pragma use_lmw_stmw off
BOOL fn_8015F890(void) { return fn_80083B84(lbl_80387060) != NULL; }

struct DrvProc : Proc {
    u8 pad[4];
    int next;  /* 0x34 */
};

#pragma use_lmw_stmw off
void fn_8015F8C4(DrvProc* p) { fn_80083DC4(p, (u8)p->next); }

#pragma use_lmw_stmw off
void fn_8015F8D0(void* p) {
    if (lbl_804183F0.done != 0) {
        fn_80168BC0(p);
    }
}

#pragma use_lmw_stmw off
void fn_8015F8EC(void* p) {
    if (lbl_804183F0.done != 0) {
        fn_80168BC0(p);
    } else {
        fn_8004559C(&lbl_803CA870, 0);
    }
}

#pragma use_lmw_stmw off
void fn_8015FB10(void) { fn_80166720(lbl_803CA870.unit); }
#pragma use_lmw_stmw off
void fn_8015FB1C(void) { fn_800A20F4(); }

#pragma use_lmw_stmw off
u8 fn_801602E8(Unit* u) {
    int i;
    if (lbl_804183F0.flags & 4) {
        return 0;
    }
    i = 0;
    for (;;) {
        if (fn_80159008(u) == 1) {
            break;
        }
        if (i > 0xFF) {
            fn_80158CA0(u);
            break;
        }
        i++;
    }
    return lbl_804183F0.done;
}

#pragma use_lmw_stmw off
u8 fn_80160370(Unit* u) {
    int i;
    if (lbl_804183F0.flags & 4) {
        return 0;
    }
    i = 0;
    for (;;) {
        if (fn_80159124(u) == 1) {
            break;
        }
        if (i > 0xFF) {
            fn_80158DB8(u);
            break;
        }
        i++;
    }
    return lbl_804183F0.done;
}

#pragma use_lmw_stmw off
u8 fn_801603F8(Unit* u) {
    if (lbl_804183F0.flags & 4) {
        return 0;
    }
    fn_80164D18(u);
    return lbl_804183F0.done;
}

#pragma use_lmw_stmw off
u8 fn_80160440(Unit* u) {
    fn_80127A8C(u);
    fn_80163178(u);
    switch ((u8)fn_80106E30(u->ai)) {
    case 1:
        fn_80152274(u);
        break;
    case 2:
        fn_8015246C(u);
        break;
    case 3:
        fn_80152604(u);
        break;
    case 4:
        fn_801529DC(u);
        break;
    case 5:
        fn_80152A34(u);
        break;
    case 6:
        fn_80152AC8(u);
        break;
    case 7:
        fn_80152940(u);
        break;
    case 0:
        fn_80152C18(u);
        break;
    }
    return lbl_804183F0.done;
}

extern void fn_80163014(AiCfg*, Unit*);
extern void fn_80163080(AiCfg*, Unit*);

#pragma use_lmw_stmw off
void fn_8015F66C(void) { *(int*)((u8*)&lbl_804183F0 + 0x228) = 0; }

extern void fn_80164BA8(Unit*);
extern int fn_8016335C(Unit*);
extern int fn_801635B8(Unit*, int);
extern int fn_80163808(Unit*, u16);
extern int fn_80163C8C(Unit*, u16);
extern int fn_80164064(Unit*, u16);
extern int fn_80164330(Unit*, u16);
extern int fn_80163AF0(Unit*, u16);
extern void fn_80164A78(Unit*);

#pragma use_lmw_stmw off
u8 fn_8016012C(Unit* u) {
    if (lbl_804183F0.flags & 4) {
        return 0;
    }
    if (fn_8016335C(u) && fn_80163178(u)) {
        if (fn_801635B8(u, 0)) {
            return lbl_804183F0.done;
        }
        if (fn_80163808(u, 0xFFFF)) {
            return lbl_804183F0.done;
        }
        if (u->w3B4 & 8) {
            if (fn_80163AF0(u, 0xFFFF)) {
                if (lbl_803CA870.action == 1) {
                    fn_80164A78(u);
                }
                return lbl_804183F0.done;
            }
        } else if (fn_80163C8C(u, 0xFFFF)) {
            fn_80164BA8(u);
        } else if (fn_80164064(u, 0xFFFF)) {
            fn_80164BA8(u);
        } else if (fn_80164330(u, 0xFFFF)) {
            fn_80164BA8(u);
        }
    } else if ((u->w3B4 & 8) && fn_80163AF0(u, 0xFFFF) && lbl_803CA870.action == 1) {
        fn_80164A78(u);
    }
    return lbl_804183F0.done;
}

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off
void fn_8015F524(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s8 v;
    lbl_804183F0.res[c->a] = 0;
    v = (s8)*((u8*)u + 0x3BA);
    if (v != 0) {
        if (fn_8012408C(u) - v < 0) {
            v = fn_8012408C(u);
        }
        s8 m = ((s8*)u)[0x116];
        ((s8*)u)[0x3BA] = 0;
        ((s8*)u)[0x116] = m - v;
    }
    lbl_804183F0.res[c->a] = fn_8012408C(u);
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off

extern void fn_80045120(AiAct*, Unit*);
extern void fn_80163010(AiCfg*, Unit*);
extern void fn_80158C8C(void);
extern Unit* fn_80127CA0(Unit*);
extern void fn_80129160(void*);
extern u8 lbl_803CAB38[];
extern int (**lbl_80386F7C[])(Unit*);
extern int fn_8016335C(Unit*);
extern u32 fn_80045274(AiAct*);
extern void fn_80045548(AiAct*);
#define CFGLIST (*(Unit***)&lbl_804183F0.res[0x85])
#define CFGPASS (lbl_804183F0.res[0x86])

static inline Unit* PickUnit(void) {
    Unit* u;
    AiAct* act = &lbl_803CA870;
    u8 side = lbl_803CAB38[0x11];
    while ((u = *(*(Unit***)&lbl_804183F0.res[0x85])++) != NULL) {
        if (u->team[8] != side) continue;
        if (u->flags10C & 0x9D) continue;
        if (lbl_804183F0.res[0x86] > 0 && !(u->w3B4 & 0x10000)) continue;
        fn_80045120(act, u);
        fn_80163010(&lbl_804183F0, u);
        u->w3B4 &= ~0x18000;
        ((u8*)u)[0x3D0] = 0x40;
        u->b3BC = 0;
        lbl_804183F0.b1 = 0;
        memset(&lbl_804183F0.res[0], 0, 0x14);
        fn_80158C8C();
        lbl_804183F0.done = 0;
        *(Unit**)((u8*)u + 0x3C0) = fn_80127CA0(u);
        if (lbl_804183F0.res[0x86] == 0) {
            fn_80129160((u8*)u + 0x3C4);
        }
        break;
    }
    return u;
}

#pragma use_lmw_stmw off
u32 fn_8015F9E8(void) {
    AiAct* act = &lbl_803CA870;
    Unit* u = act->unit;
    if (u->hp == 0 || (u->flags10C & 0x18)) {
        return 0;
    }
    fn_80163178(u);
    if ((u->w3B4 & 1) && fn_8016335C(u) != 0 && lbl_80386F7C[lbl_804183F0.b0][lbl_804183F0.b1] == (int(*)(Unit*))fn_8016012C) {
        return 0;
    }
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        return 0;
    }
    if (lbl_803CAB38[0x11] != u->team[8]) {
        return 0;
    }
    return fn_80045274(act);
}

#pragma use_lmw_stmw on
void fn_8015FB20(void) {
    AiAct* act = &lbl_803CA870;
    Unit* u = act->unit;
    if (fn_8016D0B0(u) != 0) {
        lbl_804183F0.b0 = 1;
    } else {
        lbl_804183F0.b0 = 0;
    }
    while (lbl_80386F7C[lbl_804183F0.b0][lbl_804183F0.b1] != NULL) {
        lbl_804183F0.op = 0xFFFF;
        u->b3BC = 0;
        if (lbl_80386F7C[lbl_804183F0.b0][lbl_804183F0.b1](u) != 0) {
            break;
        }
        lbl_804183F0.b1++;
    }
    if (lbl_804183F0.done == 0 || (u->w3B4 & 0x400000) ||
        (act->action == 1 && act->x == u->x && act->y == u->y)) {
        if (!(u->w3B4 & 0x8000)) {
            u->w3B4 |= 0x10000;
        }
        u->w3B4 &= ~0x400000;
        fn_80045548(act);
        ((DrvProc*)fn_80083B84(lbl_80386F88))->next = 1;
    } else {
        ((DrvProc*)fn_80083B84(lbl_80386F88))->next = 2;
    }
}
}
