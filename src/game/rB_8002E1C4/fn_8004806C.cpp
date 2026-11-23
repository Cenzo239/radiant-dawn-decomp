/* Support conversation start: builds the line name from the pair table and the support level suffix (names guessed). */
#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
extern "C" {
int fn_8012E9B4(Unit*, Unit*);
int fn_8012E8BC(Unit*, int);
char* strcpy(char*, const char*);
void fn_80291110(char*, const char*);
void* fn_80118C44(void*);
void fn_800D0B38(int, const void*);
void fn_8014BED4(char*, void*);
void fn_8014C2AC(char*);
extern char lbl_804CCE88[];
extern char lbl_804CCE8C[];
extern char lbl_804CCE90[];
extern char lbl_804CCE94[];
struct Seq { char* s0; char* s4; char* s8; };
struct SeqTbl {
    u8 pad[0x38];
    u8* base;
    int n;
};
/* Entry (row, col) of the support conversation table; the word at +0x10 / +0x14. */
static inline u8* cellAt(SeqTbl* p, s8 row, s8 col) {
    int rr = row * 0xc;
    u8* r = p->base + rr * (p->n + 1);
    r += col * 0xc;
    return r;
}
static inline char* textA(SeqTbl* p, Unit* a, Unit* b) {
    s8 x = fn_8012E9B4(a, b);
    s8 y = fn_8012E9B4(b, a);
    return *(char**)(cellAt(p, y, x) + 0x10);
}
static inline char* textB(SeqTbl* p, Unit* a, Unit* b, int& x) {
    x = (s8)fn_8012E9B4(a, b);
    s8 y = fn_8012E9B4(b, a);
    return *(char**)(cellAt(p, x, y) + 0x14);
}

void fn_8004806C(SeqTbl* p) {
    const char* t[4] = {lbl_804CCE88, lbl_804CCE8C, lbl_804CCE90, lbl_804CCE94};
    char buf[0x40];
    int k = fn_8012E8BC(lbl_803CA870.unit, (s8)fn_8012E9B4(lbl_803CA870.unit, lbl_803CA870.unit2)) & 0xFF;
    strcpy(buf, textA(p, lbl_803CA870.unit, lbl_803CA870.unit2));
    fn_80291110(buf, t[k]);
    fn_800D0B38(0, fn_80118C44(lbl_803CA870.unit2->ec));
    fn_8014BED4(buf, p);
}

void fn_80048168(SeqTbl* p) {
    const char* t[4] = {lbl_804CCE88, lbl_804CCE8C, lbl_804CCE90, lbl_804CCE94};
    char buf[0x40];
    int k = fn_8012E8BC(lbl_803CA870.unit2, (s8)fn_8012E9B4(lbl_803CA870.unit2, lbl_803CA870.unit)) & 0xFF;
    int x;
    strcpy(buf, textB(p, lbl_803CA870.unit, lbl_803CA870.unit2, x));
    fn_80291110(buf, t[k]);
    fn_800D0B38(0, fn_80118C44(lbl_803CA870.unit->ec));
    fn_8014C2AC(buf);
}
}
