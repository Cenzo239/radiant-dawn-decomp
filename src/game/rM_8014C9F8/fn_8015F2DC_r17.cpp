/* fn_8015F2DC: AI command, add a clamped move bonus (fields at +0x116 and +0x3BA; names guessed). Named _r17 because fn_8015F2DC.cpp already holds its neighbours. */
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

#pragma use_lmw_stmw off

#pragma use_lmw_stmw off

#pragma use_lmw_stmw off
#pragma use_lmw_stmw off

#pragma use_lmw_stmw off
#pragma use_lmw_stmw off
#pragma use_lmw_stmw off
#pragma use_lmw_stmw off
#pragma use_lmw_stmw off
#pragma use_lmw_stmw off

struct DrvProc : Proc {
    u8 pad[4];
    int next;  /* 0x34 */
};

#pragma use_lmw_stmw off

#pragma use_lmw_stmw off

#pragma use_lmw_stmw off

#pragma use_lmw_stmw off
#pragma use_lmw_stmw off

#pragma use_lmw_stmw off

#pragma use_lmw_stmw off

#pragma use_lmw_stmw off

#pragma use_lmw_stmw off

extern void fn_80163014(AiCfg*, Unit*);
extern void fn_80163080(AiCfg*, Unit*);

#pragma use_lmw_stmw off

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

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off

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

#pragma use_lmw_stmw on
#pragma use_lmw_stmw off
void fn_8015F2DC(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    int v;
    int t;
    lbl_804183F0.res[c->a] = 0;
    v = c->c;
    if (c->fl & 8) {
        if (fn_8012408C(u) < v) {
            v = fn_8012408C(u);
        } else if (v < 0) {
            v = 0;
        }
        v -= fn_8012408C(u);
    }
    if (v + fn_8012408C(u) < 0) {
        v = -fn_8012408C(u);
    }
    ((u8*)u)[0x116] = v + ((u8*)u)[0x116];
    t = v + (s8)*((u8*)u + 0x3BA);
    if (t > 0x7F) {
        t = 0x7F;
    }
    if (t < -0x80) {
        t = -0x80;
    }
    ((s8*)u)[0x3BA] = t;
    lbl_804183F0.res[c->a] = fn_8012408C(u);
    fn_80129550(u, lbl_804CB8B4);
}

}
