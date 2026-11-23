/* fn_8015F680 (0x178): exact (round m23). AI driver proc step: pick the next unit of the active side from the
 * config's unit list (PickUnit), or on an empty list restart the list for the second pass / finish the proc.
 * From equiv/fn_8015F680.cpp. Lever: the list walker as a named local declared first in PickUnit
 * (`Unit*** list = (Unit***)&lbl_804183F0.res[0x85];` before `Unit* u;`, walk `*(*list)++`); this gives the
 * hoisted config base r5 and the side byte r4 like the original. The pass counter in the switch is still read
 * through a volatile cast (original reload). */
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
extern int lbl_804CB8B4;
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
void fn_8015F5E8(Unit* u);

#pragma use_lmw_stmw off
void fn_8015F604(Unit* u);

#pragma use_lmw_stmw off
void fn_8015F62C(Unit* u);

#pragma use_lmw_stmw off
void fn_8015F654(Unit* u);
#pragma use_lmw_stmw off
void fn_8015F65C(void* p);

#pragma use_lmw_stmw off
void fn_8015F7F8(void);
#pragma use_lmw_stmw off
BOOL fn_8015F808(void);
#pragma use_lmw_stmw off
void fn_8015F83C(void);
#pragma use_lmw_stmw off
BOOL fn_8015F84C(void);
#pragma use_lmw_stmw off
void fn_8015F880(void);
#pragma use_lmw_stmw off
BOOL fn_8015F890(void);

struct DrvProc : Proc {
    u8 pad[4];
    int next;  /* 0x34 */
};

#pragma use_lmw_stmw off
void fn_8015F8C4(DrvProc* p);

#pragma use_lmw_stmw off
void fn_8015F8D0(void* p);

#pragma use_lmw_stmw off
void fn_8015F8EC(void* p);

#pragma use_lmw_stmw off
void fn_8015FB10(void);
#pragma use_lmw_stmw off
void fn_8015FB1C(void);

#pragma use_lmw_stmw off
u8 fn_801602E8(Unit* u);

#pragma use_lmw_stmw off
u8 fn_80160370(Unit* u);

#pragma use_lmw_stmw off
u8 fn_801603F8(Unit* u);

#pragma use_lmw_stmw off
u8 fn_80160440(Unit* u);

extern void fn_80163014(AiCfg*, Unit*);
extern void fn_80163080(AiCfg*, Unit*);

#pragma use_lmw_stmw off
void fn_8015F66C(void);

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
u8 fn_8016012C(Unit* u);

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off

/* from fn_8015F2DC.cpp */
#pragma use_lmw_stmw off
void fn_8015F524(Unit* u);

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
    Unit*** list = (Unit***)&lbl_804183F0.res[0x85];
    Unit* u;
    AiAct* act = &lbl_803CA870;
    u8 side = lbl_803CAB38[0x11];
    while ((u = *(*list)++) != NULL) {
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
u32 fn_8015F9E8(void);

#pragma use_lmw_stmw on
void fn_8015FB20(void);
}

#pragma use_lmw_stmw off
extern "C" {
/* from fn_8015F2DC.cpp */
void fn_8015F680(void* p) {
    if (PickUnit() == NULL) {
        switch (*(volatile int*)&lbl_804183F0.res[0x86]) {
        case 0:
            lbl_804183F0.res[0x85] = (int)&lbl_804183F0.res[5];
            lbl_804183F0.res[0x86]++;
            fn_80083DC4(p, 0);
            break;
        default:
            fn_80083DC4(p, 4);
            break;
        }
    }
}


}
