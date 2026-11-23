/* fn_80047164 (round 19, exact). Parent declarations from rT_80026898/fn_80047164.cpp. */
#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
extern "C" {
void fn_8011EED4(Unit*, Unit*, int, u8*, u8*);
void fn_80126EB0(Unit*, int, int);
void fn_800F39DC(Unit*);
void fn_80109094(void*, int, int);
int fn_80109174(void*);
void fn_80026CD8(void*, Unit*, int);
#if TARGET_PC
FE10_PROTO void fn_800E995C(void*, p32arg);
#else
void fn_800E995C(void*, int);
#endif
void fn_80119A88(Unit*, Unit*, int);
void fn_8013CB90(int, int, void*);
#if TARGET_PC
FE10_PROTO void fn_80108A20(void*, Unit*, int);
#else
void* fn_80108A20(void*, Unit*, int);
#endif
Unit* fn_8002C648(void*);
Unit* fn_8002C590(void*);
void fn_80111B64(Item*, Slot*);
void fn_80111C24(Item*, int);
void fn_8004AD18(Unit*, Item*, void*);
void fn_8004AED0(Item*, void*);
Slot* fn_80030CF4(Unit*);
#if TARGET_PC
FE10_PROTO char * fn_80110F08(Slot*);
FE10_PROTO char * fn_801110C4(Slot*, int);
#else
int fn_80110F08(Slot*);
int fn_801110C4(Slot*, int);
#endif
int fn_80290D04(char*, int, const char*, ...);
void fn_800D0B38(int, const void*);
int fn_8011B77C(void*, void*);
void* fn_800D08B4(const char*, int);
#if TARGET_PC
FE10_PROTO void fn_801ABBA8(void*, ptr32<const void>, void*, int);
#else
void fn_801ABBA8(void*, const char*, void*, int);
#endif
extern void* lbl_804CA4DC;
void fn_8011EB4C(Unit*, u8*, u8*);
void fn_801037D4(Unit*, int, int, int, int, void*);
void fn_8011E300(Unit*, int, int, int);
extern u8 lbl_804CB830;
extern u8 lbl_803EC898[];
void fn_800319F8(Slot*, void*, void* unit);
void fn_8012A0F4(Unit*, Slot*);
int fn_8012BD30(Unit*, void*);
void fn_8012A80C(Unit*, int);
void fn_80111A0C(Unit*, void*, void*);
void fn_80111A98(Unit*, void*, void*);
void fn_800F491C(Unit*);
int fn_8012E9B4(Unit*, Unit*);
u8 fn_8012E8BC(Unit*, int);
char* strcpy(char*, const char*);
void fn_80291110(char*, const char*);
void* fn_80118C44(void*);
void fn_8014BED4(char*, void*);
void fn_8014C2AC(char*);
extern char lbl_804CCE88[];
extern char lbl_804CCE8C[];
extern char lbl_804CCE90[];
extern char lbl_804CCE94[];

static inline int hpN(Hp* h) { return h->n; }
static inline int unitN(Unit* u) { return hpN(&u->h); }
void fn_80047348(void* a);

int fn_800473A0(void* a);




static inline bool mode1(u8 m) { return m == 1; }
static inline bool mode2(u8 m) { return m == 2; }
static inline bool modeIs(u8 m) { return mode1(m) || mode2(m); }
static inline Slot* cmdItem() { return &lbl_803CA870.unit2->items[(s8)lbl_803CA870.item]; }
void fn_800479FC(void);

void fn_80047AA8(u8* p);

void fn_80047AD8(u8* p);


struct Seq { u8 pad[0xc]; };
struct SeqTbl {
    u8 pad[0x38];
    u8* base;
    int n;
};


}

/* ---- from build/tmp/r19hpbs/frag_7164.cpp ---- */
extern "C" {
/* Finish a rescue/shove-type action: move the target, drain its counter n times, then clean up. */
void fn_80047164(Act* q, void* proc) {
    u8 x, y;
    int n = q->f18;
    int i;
    fn_8011EED4(q->u1, q->u2, n, &x, &y);
    fn_80126EB0(q->u2, (s8)x, (s8)y);
    fn_800F39DC(q->u2);
    if (n > 0 && unitN(q->u2) != 0) {
        for (i = 0; i < n && ((Hp*)((u8*)q->u2 + 0x110))->n != 0; i++) {
fn_80109094(&q->u2->h, 2, unitN(q->u2) - 1);
        }
        if (fn_80109174(&q->u2->h) == 0 && (q->u2->f10c & 0x10000dc) == 0) {
            fn_80026CD8(lbl_803C8E80, q->u2, -1);
            fn_800E995C(proc, 0);
        }
    }
    switch (q->action) {
    case 0x13:
        fn_80119A88(q->u1, q->u2, 4);
        break;
    case 0x14:
        fn_80119A88(q->u1, q->u2, 5);
        break;
    }
}
}
