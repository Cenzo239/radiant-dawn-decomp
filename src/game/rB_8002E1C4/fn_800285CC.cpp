#include "game/rE_800E5DE4/types.h"
typedef unsigned long long u64;
struct Rec7 { u8 a, b, c, d, e; s8 f; u8 g; };
struct Roll {
    u8 x0[0x20];
    u16 x20[0x20];
    s16 x60[0x20];
    u8 xa0, xa1, xa2, xa3, xa4;
};
struct ItemD { u64 flags; };
struct Slot { ItemD* data; u8 x4; u8 x5; };
struct BU {
    u8 pad0[0x108];
    u64 x108;
    u8 pad110[0x114 - 0x110];
    s8 x114;
    u8 pad115[0x119 - 0x115];
    u8 s[8];
    u8 pad121[0x12c - 0x121];
    u8 x12c[0x445 - 0x12c];
    u8 x445;
    u8 pad446[2];
    s16 x448;
    s16 x44a;
    u8 pad44c[0x458 - 0x44c];
    s16 x458;
    u8 pad45a[0];
    s16 x45a;
    s16 x45c;
    u8 pad45e[0x4a0 - 0x45e];
};
struct Battle {
    BU a, b, c;
    u8 log[0x15e4 - 0xde0];
};
extern Roll lbl_803C8DA0;
extern void* lbl_804CA684;
extern void* lbl_804CA688;
extern void* lbl_804CA6AC;
extern "C" {
f32 fn_80127868(BU* p);
Rec7 fn_801278B8(BU* p, f32 bio);
s16 fn_801237EC(BU* p);
void fn_8002600C(void* log, int code, int v);
void fn_80026208(void* log, int code);
void fn_80026288(void* log);
int fn_8011B77C(void* list, void* key);
Slot* fn_80030CBC(BU* p);
ItemD* fn_801116B8(Slot* s);
void fn_800282A0(Battle* b, BU* a, BU* d, int k);
int fn_8002FF14(BU* a);
void fn_80028A68(Battle* b, BU* a, BU* d, int f);
void fn_8002A780(Battle* b, BU* a, BU* d, int v, u8 k, int w);
void fn_8003098C(BU* a, void* log, int n);
void fn_80025FD0(Roll* r);
#define R(m) (lbl_803C8DA0.x20[lbl_803C8DA0.xa0] & (m))
#define LOW(u, k) ((f32)(s8)(u)->x114 / (f32)fn_801237EC(u) <= k)
void fn_800285CC(Battle* b, BU* a, BU* d, int f) {
    /*P*/
    u8 a1, a2, a3, a4, a5, a6, a7, a8;
    u8 d1, d2, d3, d4, d5, d6, d7, d8;
    int fa, fd, fb;
    int hp;
    /*E*/
    f32 bioA = fn_80127868(a);
    fn_801278B8(a, bioA);
    f32 bioB = fn_80127868(d);
    fn_801278B8(d, bioB);
    a1 = a->s[0];
    a2 = a->s[1];
    a3 = a->s[2];
    a4 = a->s[3];
    a5 = a->s[4];
    a6 = a->s[5];
    a7 = a->s[6];
    a8 = a->s[7];
    d1 = d->s[0];
    d2 = d->s[1];
    d3 = d->s[2];
    d4 = d->s[3];
    d5 = d->s[4];
    d6 = d->s[5];
    d7 = d->s[6];
    d8 = d->s[7];
    fa = 0;
    fd = 0;
    fb = 0;
    if (fn_8011B77C(a->x12c, lbl_804CA684)) {
        hp = a->x114;
        if ((f32)hp / (f32)fn_801237EC(a) <= 0.5f) {
            fa = 1;
            a->x108 |= 0x8000000000ULL;
        }
    }
    if (fn_8011B77C(d->x12c, lbl_804CA684)) {
        hp = d->x114;
        if ((f32)hp / (f32)fn_801237EC(d) <= 0.5f) {
            fd = 1;
            d->x108 |= 0x8000000000ULL;
        }
    }
    fn_800282A0(b, a, d, 0);
    if (fn_8011B77C(a->x12c, lbl_804CA688)) {
        hp = a->x114;
        if ((f32)hp / (f32)fn_801237EC(a) <= 0.3f) {
            if (!fn_8011B77C(d->x12c, lbl_804CA6AC) && fn_80030CBC(a)->data && !(fn_801116B8(fn_80030CBC(a))->flags & 0x8000ULL)) {
                a->x458 = a->x458 + 0x32;
                if (a->x458 > 0x64) a->x458 = 0x64;
            }
            fb = 1;
        }
    }
    a->x45a = a->x448 - d->x44a;
    if (a->x45a < 0) a->x45a = 0;
    a->x45c = 0;
    a->x445 = fn_8002FF14(a);
    if ((u8)a->x445 == 0x6f && R(1)) a->x445 = 0x6e;
    switch (a->x445) {
    case 0x70:
        a->x45a = 0;
        break;
    case 0x6f:
        a->x45a = a->x45a * 3;
        break;
    }
    if (lbl_803C8DA0.x60[lbl_803C8DA0.xa0] != 0x3039) a->x45a = lbl_803C8DA0.x60[lbl_803C8DA0.xa0];
    fn_80026208(b->log, 0x74);
    fn_80028A68(b, a, d, f);
    if (fa) fn_8002600C(b->log, 0x46, 0);
    if (fd) fn_8002600C(b->log, 0x47, 0);
    if (fb) fn_8002600C(b->log, 0x49, 0);
    fn_80026288(b->log);
    fn_80026208(b->log, 0x75);
    fn_8002A780(b, a, d, a->x45a, a->x445, a->x45c);
    fn_8003098C(a, b->log, 1);
    fn_80026288(b->log);
    a->x108 &= ~0x8000000000ULL;
    d->x108 &= ~0x8000000000ULL;
    a->s[0] = a1;
    a->s[1] = a2;
    a->s[2] = a3;
    a->s[3] = a4;
    a->s[4] = a5;
    a->s[5] = a6;
    a->s[6] = a7;
    a->s[7] = a8;
    d->s[0] = d1;
    d->s[1] = d2;
    d->s[2] = d3;
    d->s[3] = d4;
    d->s[4] = d5;
    d->s[5] = d6;
    d->s[6] = d7;
    d->s[7] = d8;
    fn_80025FD0(&lbl_803C8DA0);
}
}
