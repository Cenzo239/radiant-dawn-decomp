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
FE10_PROTO p32ret fn_80110F08(Slot*);
FE10_PROTO p32ret fn_801110C4(Slot*, int);
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
void fn_8011EB4C(Unit*, s8*, s8*);
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


static inline bool mode1(u8 m) { return m == 1; }
static inline bool mode2(u8 m) { return m == 2; }
static inline bool modeIs(u8 m) { return mode1(m) || mode2(m); }
static inline Slot* cmdItem() { return &lbl_803CA870.unit2->items[(s8)lbl_803CA870.item]; }


struct Seq { u8 pad[0xc]; };
struct SeqTbl {
    u8 pad[0x38];
    u8* base;
    int n;
};




int fn_800478B4(void* a) {
    Unit* u = fn_8002C590(lbl_803C8E80);
    Unit* v;
    s8 b, c;
    if (u == 0) return 0;
    if (!(u->f10c & 2)) return 0;
    v = u->u3f0;
    fn_8011EB4C(v, &b, &c);
    fn_801037D4(v->f8, v->f8->x102, v->f8->y103, b, c, a);
    fn_8011E300(v, b, (s8)*(u8*)&c, 1);
    return 1;
}
static inline bool ModeOk() { bool r = 1; u8 m = lbl_804CB830; if (m != 1 && m != 2) r = 0; return r; }
int fn_800474C8(void* proc) {
    char buf[0x80];
    Unit* s0;
    Unit* s1;
    int v;
    Slot* it;
    u8* d;
    u16 m;
    Unit* s;
    int w;
    s0 = (Unit*)lbl_803C8E80;
    s1 = (Unit*)(lbl_803C8E80 + 0x4a0);
    s = 0;
    if (s0->f4[8] == 0) s = s0;
    if ((*(u32*)(lbl_803C8E80 + 0x15ec) & 5) == 0 && s1->f4[8] == 0) s = s1;
    if (s == 0 || s->s114 == 0 || ((u8*)s)[0x47b] == 0) return 0;
    it = fn_80030CF4(s);
    if (it == 0 || (d = it->data) == 0) return 0;
    if ((u8)(d ? d[0x12] : 0x13) == 0x10) return 0;
    if (d) m = *(u16*)(d + 0x16); else m = 0;
    v = fn_80110F08(it);
    w = fn_801110C4(it, 1);
    fn_80290D04(buf, 0x80, lbl_803619D0 + 0x6f, w, v, (u8)m + 0x80);
    fn_800D0B38(0, buf);
    fn_801ABBA8(fn_800D08B4(lbl_803619D0 + 0x7a, fn_8011B77C(s->x12c, lbl_804CA4DC)), lbl_803619D0 + 0x85, proc, 1);
    return 1;
}
}
