/* fn_80169558: functionally equal (renamed level per tools/check_regs.py; registers differ from the original).  */
/* fn_80169558: near miss, registers only: u/a/b should be r25..r27 and the Inv walker r23; here the walker outranks the parameters. Sibling of fn_80169718 in fn_80165B48.cpp. */
/* AI: try staff skill actions, healing staves first by power (names guessed). */
#include "game/rQ_80163178/types.h"
#pragma use_lmw_stmw on
struct Bf110 { u8 pad[0x110]; u16 a : 9; u16 s : 3; };
struct SkillAct { char* name; u8* item; int (*func)(Unit*, int, int, int); };
extern "C" {
extern SkillAct lbl_80387690[];
int fn_8012BB48(Unit*, void*);
}
static inline SkillAct* FindAct(Unit* u, u8* it) {
    if (fn_8012BB48(u, it)) {
        SkillAct* e;
        for (e = lbl_80387690; e->name; e++) {
            if (it == e->item && e->func) {
                return e;
            }
        }
    }
    return 0;
}
extern "C" {
u8 fn_80169558(Unit* u, int a, int b) {
    if (((Bf110*)u)->s == 0) {
        /*P*/
        BOOL heal = 0;
        u8* it;
        s16 mh = 0;
        s16 mo = 0;
        int i;
        Inv* p = u->inv;
/*E*/
        for (i = 0; i < 7; i++, p++) {
            if (!p || !p->item) break;
            if (fn_8012BB48(u, p->item)) {
                it = p->item;
                if ((u8)(it ? it[0x14] : 0x13) == 0x81) {
                    if ((it ? *(s16*)(it + 0x18) : 0) >= mh) goto F;
                    continue;
                } else {
                    if (heal) continue;
                    if ((it ? *(s16*)(it + 0x18) : 0) < mo) continue;
                }
                F:
                SkillAct* e = FindAct(u, it);
                if (e && e->func(u, i, a, b)) {
                    it = p->item;
                    if ((u8)(it ? it[0x14] : 0x13) == 0x81) {
                        mh = it ? *(s16*)(it + 0x18) : 0;
                        heal = 1;
                    } else {
                        mo = it ? *(s16*)(it + 0x18) : 0;
                    }
                }
            }
        }
    }
    return lbl_804183F0.done;
}
}
