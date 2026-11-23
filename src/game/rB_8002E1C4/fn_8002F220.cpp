#include "game/rT_80026898/types.h"

/* Battle unit stat calculation: attack, defence, speed, hit, avoid, crit, dodge. */
struct ItemF { u32 hi, lo; u8 pad8[0x12 - 8]; u8 x12; u8 x13; };
struct Rec7 { s8 a, b, c, d, e, f, g; };
struct WU {
    u8 pad0[0xec];
    u8* ec;
    u8 padf0[0x108 - 0xf0];
    u32 f108;
    u32 f10c;
    u16 x110;
    u16 x112;
    u8 pad114[0x12c - 0x114];
    u8 x12c[0x3f0 - 0x12c];
    WU* u3f0;
    Slot item;   /* 0x3f4 */
    Slot base;   /* 0x41c */
    u8 x444, x445, x446, x447;
    s16 x448, x44a, x44c, x44e, x450, x452, x454, x456, x458, x45a, x45c;
    u16 x45e;
    u32 x460;
    s8 x464, x465, x466;
    u8 pad467[0x474 - 0x467];
    s16 x474, x476, x478;
    u8 pad47a[2];
    s8 x47c;
    u8 x47d;
    s8 x47e;
    u8 pad47f[0x48a - 0x47f];
    u8 x48a;
    u8 pad48b[0x4a0 - 0x48b];
    u8* f4() { return *(u8**)((u8*)this + 0xf4); }
};
extern Slot lbl_803EC368;
extern void* lbl_804CA57C;
extern void* lbl_804CA584;
extern void* lbl_804CA5D8;
extern void* lbl_804CA5D4;
extern void* lbl_804CA5D0;
extern void* lbl_804CA5CC;
extern void* lbl_804CA5C8;
extern void* lbl_804CA638;
extern void* lbl_804CA634;
extern "C" {
int fn_8012BF70(WU* o, u16* p);
int fn_80110758(int k);
u8 fn_80110DA8(Slot* w);
u8 fn_80110E00(Slot* w);
u8 fn_80110E58(Slot* w);
u8 fn_80110EB0(Slot* w);
ItemF* fn_801116B8(Slot* w);
s16 fn_80123998(WU* u);
s16 fn_8012386C(WU* u);
int fn_8011B77C(void* l, void* k);
s16 fn_80123DC4(WU* u);
s16 fn_80123EF0(WU* u);
s16 fn_80123BF0(WU* u);
f32 fn_80127868(WU* u);
Rec7 fn_801278B8(WU* u, f32 bio);
s16 fn_80123AC4(WU* u);
int fn_80123D1C(WU* u);
s8 fn_80112CD4(WU* u, int k);
int fn_8010EF98(int k);
#if TARGET_PC
FE10_PROTO int fn_80124BC0(WU* u, p32arg);
#else
int fn_80124BC0(WU* u, int k);
#endif
WU* fn_80127B68(WU* u);

static inline Slot* weapon(WU* u) {
    if (u->x47c <= 0) return &lbl_803EC368;
    if (u->x47d != 0) return &lbl_803EC368;
    return &u->item;
}
static inline u8 k12(Slot* s) {
    if (s->data) return ((ItemF*)s->data)->x12;
    return 0x13;
}
static inline int k13(Slot* s) {
    if (s->data) return ((ItemF*)s->data)->x13;
    return 0x13;
}

void fn_8002F220(WU* u, WU* o) {
    int mag = 0;
    if (o && o->ec && fn_8012BF70(o, &u->x45e)) u->x446 = 1;
    if (o && o->ec && fn_80110758(k13(weapon(o)))) mag = 1;
    if (weapon(u)->data) {
        Slot* w0 = weapon(u);
        s16 t = u->x474;
        { int v = fn_80110DA8(w0); u->x448 = v + t; }
        if (u->x446) u->x448 = u->x448 * 4 - u->x448;
        if (u->x47e > 0) u->x448 += 2;
        if (!(fn_801116B8(weapon(u))->lo & 0x4000) && k12(weapon(u)) != 0xd) {
            if (fn_80110758(k13(weapon(u)))) u->x448 += fn_80123998(u);
            else u->x448 += fn_8012386C(u);
        }
        if (o && fn_8011B77C(o->x12c, lbl_804CA57C) && !(fn_801116B8(weapon(u))->hi & 0x2000)) {
            u->x448 = 0;
            u->x48a = 1;
        } else {
            u->x48a = 0;
        }
    } else {
        u->x448 = 0;
    }
    if (u->x448 < 0) u->x448 = 0;
    if (mag == 0) {
        u->x44a = u->x464 + fn_80123DC4(u);
        if (u->x110 & 1) u->x44a += 10;
    } else {
        u->x44a = u->x465 + fn_80123EF0(u);
    }
    if (u->x44a < 0) u->x44a = 0;
    {
        int over;
        mag = fn_80110EB0(&u->base);
        over = mag - fn_8012386C(u);
        if (over < 0) over = 0;
        u->x44c = fn_80123BF0(u) - over;
        if (u->x44c < 0) u->x44c = 0;
    }
    f32 bioA = fn_80127868(u);
    {
    Rec7 r = fn_801278B8(u, bioA);
    {
        Slot* w = weapon(u);
        u->x44e = fn_80110E00(w) + fn_80123AC4(u) * 2;
        s16 t476 = u->x476;
        s16 t478 = u->x478;
        u->x44e += fn_80123D1C(u) + (t478 + t476);
        u->x44e += r.c;
    }
    if (u->x112 >> 10 & 3) u->x44e /= 2;
    if (u->x47e > 0) u->x44e += 0x32;
    else if (u->x47e < 0) u->x44e -= 0x32;
    {
        s16 t = u->x44c;
        u->x450 = u->x466 + (int)((char*)fn_80123D1C(u) + t * 2); /* the cast only fixes the add operand order */
        u->x450 += r.d;
    }
    if (u->x110 >> 7 & 7) u->x450 = 0;
    {
        mag = fn_80110E58(weapon(u));
        { int h = fn_80123AC4(u) / 2; s16 w = h + mag; u->x454 = w + r.e; }
    }
    }
    if (!(u->f108 & 0x800)) {
        u->x454 += fn_80112CD4(u->u3f0, 0);
        if (o && o->u3f0) u->x454 -= fn_80112CD4(o->u3f0, 0);
    }
    {
        int k = fn_8011B77C(u->x12c, lbl_804CA584);
        if (k) u->x454 += fn_8010EF98(k);
    }
    if (fn_8011B77C(u->x12c, lbl_804CA5D8)) u->x454 += 0x19;
    if (fn_8011B77C(u->x12c, lbl_804CA5D4)) u->x454 += 0x14;
    if (fn_8011B77C(u->x12c, lbl_804CA5D0)) u->x454 += 0xf;
    if (fn_8011B77C(u->x12c, lbl_804CA5CC)) u->x454 += 0xa;
    if (fn_8011B77C(u->x12c, lbl_804CA5C8)) u->x454 += 5;
    if (*(u64*)fn_801116B8(weapon(u)) & 0x8000ULL) u->x454 = 0;
    u->x456 = fn_80123D1C(u);
    if (!(u->f108 & 0x800)) {
        if (fn_8011B77C(u->x12c, lbl_804CA638)) {
            u->x450 += 0x14;
            u->x456 += 0x14;
        }
        if (fn_8011B77C(u->x12c, lbl_804CA634)) u->x44e += 0x14;
        {
            int a = 0;
            int b = 0;
            int c = 0;
            int k = fn_80124BC0(u, 0);
            if (k > 0) {
                a = -(k * 5);
                c = a;
            }
            switch (u->f4()[8]) {
            case 5:
            case 6:
                break;
            default: {
                WU* m = fn_80127B68(u);
                if (m) {
                    b = (s8)m->ec[0x21] * 5;
                    a += b;
                }
                break;
            }
            }
            u->x44e += a;
            u->x450 += b;
            u->x454 += c;
            if (u->x44e < 0) u->x44e = 0;
            if (u->x450 < 0) u->x450 = 0;
            if (u->x454 < 0) u->x454 = 0;
        }
    }
}
}
