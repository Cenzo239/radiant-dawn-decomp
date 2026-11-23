/* Give rank 1 in weapons the unit has a skill for, 8012C448. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern void* lbl_804CA52C; extern void* lbl_804CA530; extern void* lbl_804CA534; extern void* lbl_804CA538;
extern void* lbl_804CA548; extern void* lbl_804CA54C; extern void* lbl_804CA544; extern void* lbl_804CA540; extern void* lbl_804CA550;
#define R(i,s) if (u->s2D4[i] == 0 && fn_8011B77C(u->skills, s)) { u->s2D4[i] = 1; }
void fn_8012C448(Unit* u) {
    R(0,lbl_804CA52C) R(1,lbl_804CA530) R(2,lbl_804CA534) R(3,lbl_804CA538) R(9,lbl_804CA548) R(10,lbl_804CA54C) R(5,lbl_804CA544) R(4,lbl_804CA540) R(11,lbl_804CA550)
}
}
