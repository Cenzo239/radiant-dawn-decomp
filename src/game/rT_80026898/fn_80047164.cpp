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
void* fn_80108A20(void*, Unit*, int);
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


void fn_80047348(void* a) {
    Unit* u = lbl_803CA870.unit2;
    fn_8013CB90(u->x102, u->y103, a);
    fn_80108A20(lbl_803CA870.unit2->x110, lbl_803CA870.unit2, 1);
}

int fn_800473A0(void* a) {
    Unit* s;
    Slot* it;
    int i;
    if (*(u32*)(lbl_803C8E80 + 0x15ec) & 0x100) return 0;
    s = fn_8002C648(lbl_803C8E80);
    if (s == 0) return 0;
    if (s->f4[8] == 1) return 0;
    it = fn_8002C590(lbl_803C8E80)->items;
    for (i = 0; i < 7; i++, it++) {
        if (it && it->data && it->f40) {
            if (s->f4[8] == 0) {
                Item t;
                fn_80111B64(&t, it);
                fn_8004AD18(s->u3f0, &t, a);
                fn_80111C24(&t, -1);
            } else {
                Item t;
                fn_80111B64(&t, it);
                fn_8004AED0(&t, a);
                fn_80111C24(&t, -1);
            }
            return 1;
        }
    }
    return 0;
}



static inline bool mode1(u8 m) { return m == 1; }
static inline bool mode2(u8 m) { return m == 2; }
static inline bool modeIs(u8 m) { return mode1(m) || mode2(m); }
static inline Slot* cmdItem() { return &lbl_803CA870.unit2->items[(s8)lbl_803CA870.item]; }


void fn_800479FC(void) {
    Slot* s = &lbl_803CA870.unit2->items[(s8)lbl_803CA870.item];
    s8 n;
    fn_8012A0F4(lbl_803CA870.unit, s);
    n = fn_8012BD30(lbl_803CA870.unit, s->data);
    fn_8012A80C(lbl_803CA870.unit2, (s8)lbl_803CA870.item);
    lbl_803CA870.item = n;
}

void fn_80047AA8(u8* p) {
    void* d = lbl_803CA870.unit->items[(s8)lbl_803CA870.item].data;
    *(void**)(p + 0x54) = d;
    fn_80111A0C(lbl_803CA870.unit, d, p);
}

void fn_80047AD8(u8* p) {
    fn_80111A98(lbl_803CA870.unit, *(void**)(p + 0x54), p);
    fn_800F491C(lbl_803CA870.unit);
}

struct Seq { u8 pad[0xc]; };
struct SeqTbl {
    u8 pad[0x38];
    u8* base;
    int n;
};


}
