/* fn_80168BF0 (0x198): functionally equal at `sched` level (tools/check_regs.py, round 20). Copy of
 * wip/r18/fn_80168BF0.cpp. One moved instruction (dd.py): the constant `li r0,1` comes after `addi r9` (map base)
 * here and before it in the original.
 */
/* fn_80168BF0 (round 18): other by one instruction: li r0,1 (b = 1) should come before addi r9 (the map base). Everything else matches. */
/* AI: unit flag setup, range marks. */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
extern "C" {
extern u8 lbl_80387438[];
extern u8 lbl_803CAB38[];
extern u8 lbl_804CB830;
extern SkillAct lbl_80387690[];
extern u32 lbl_804CA5C4;
void fn_80163178(Unit*);
int fn_8012BB48(Unit*, u8*);
int fn_8012BA20(Unit*, u8*);
int fn_8011B77C(void*, u32);
u8* fn_801116B8(Inv*);
void fn_80170D64(Unit*);
void fn_80170E60(Unit*);
int fn_80109348(void*);
void fn_8010E41C(u8*, int);
int fn_80165818(void);
void fn_801148CC(Map*, int);
void fn_80114B44(Map*, int, int);
void fn_80114888(Map*, int);
void fn_80115DEC(Map*, int, int, u8, u8);
void fn_80116098(Map*, int, int, u8, u8);
s8 fn_8012408C(Unit*);
int fn_801658E4(Unit*, s8, s8);
void fn_800620A8(u8*, f32, f32);
void fn_800454A8(AiAct*, int, int);
u8* fn_80081194_(void);
void fn_80129CB8(Unit*, int);
u8 fn_801107A0(u8*, Unit*);
u8 fn_801107C0(u8*, Unit*);
u8 fn_80110DA8(Inv*);
void fn_801030B8(Unit*, int, int, int, int, void*);

void fn_801689C8(f32* p);

void fn_80168BF0(u8* p);

void fn_80170F50(void);

void fn_80171188(Unit* u);

void fn_80170738(Unit* u, u8 a, u8 b);
void fn_80170998(Unit* u, u8 a, u8 b);
void fn_8016935C(void);
}


static inline BOOL IsM() { BOOL b = 1; u8 m = lbl_804CB830; if (m != 1 && m != 2) b = 0; return b; }
static inline BOOL IsM2(u8 m) { BOOL b = 1; if (m != 1 && m != 2) b = 0; return b; }
/* ---- fn_80168BF0 ---- */
extern "C" {
void fn_80168BF0(u8* p) {
    AiAct* a = &lbl_803CA870;
    Map* m = &lbl_803EC898;
    p[0x34] = 1;
    {
        BOOL b = IsM();
        if (b && lbl_803CAB38[0x11] == 1) {
            if (m->ter[2][a->x0 + a->y0 * 0x40] != 0 || m->ter[2][a->x + a->y * 0x40] != 0) {
                fn_800620A8(lbl_803CAB38, a->x0, a->y0);
            } else {
                p[0x34] = 0;
                if (a->action == 0x26) {
                    fn_800620A8(lbl_803CAB38, a->x0, a->y0);
                }
            }
        } else {
            fn_800620A8(lbl_803CAB38, a->x0, a->y0);
        }
    }
}
}
