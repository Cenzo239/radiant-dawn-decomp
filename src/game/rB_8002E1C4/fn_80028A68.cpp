#include "game/rE_800E5DE4/types.h"
struct Rec7 { u8 a, b, c, d, e; s8 f; u8 g; };
struct Roll {
    u8 x0[0x20];
    u16 x20[0x20];
    s16 x60[0x20];
    u8 xa0, xa1, xa2, xa3, xa4;
};
struct ItemD { u32 x0; u32 flags; u8 pad8[0x13 - 8]; u8 x13; };
struct Slot { ItemD* data; u8 x4; u8 x5; };
struct BU {
    u8 pad0[0x110];
    u8 x110[4];
    u8 x114;
    u8 pad115[0x12c - 0x115];
    u8 x12c[0x445 - 0x12c];
    u8 x445;
    u8 pad446[2];
    s16 x448;
    s16 x44a;
    u8 pad44c[0x45a - 0x44c];
    s16 x45a;
    s16 x45c;
    u8 pad45e[0x47d - 0x45e];
    u8 x47d;
    u8 pad47e[4];
    u8 x482;
    u8 pad483[3];
    s16 x486;
    s16 x488;
    u8 x48a;
    u8 pad48b[0x4a0 - 0x48b];
};
struct Battle {
    BU a, b, c;
    u8 log[0x15e4 - 0xde0];
    u8 f15e4;
    u8 pad15e5[3];
    int f15e8;
    u32 f15ec;
};
extern Roll lbl_803C8DA0;
extern u8 lbl_803C8E80[];
#define BT ((Battle*)lbl_803C8E80)
extern void* lbl_804CA63C;
extern void* lbl_804CA6E0;
extern void* lbl_804CA6A0;
extern void* lbl_804CA680;
extern void* lbl_804CA5EC;
extern void* lbl_804CA5F0;
extern void* lbl_804CA5F4;
extern void* lbl_804CA5F8;
extern void* lbl_804CA5FC;
extern void* lbl_804CA600;
extern void* lbl_804CA604;
extern void* lbl_804CA608;
extern void* lbl_804CA60C;
extern void* lbl_804CA610;
extern void* lbl_804CA614;
extern void* lbl_804CA618;
extern void* lbl_804CA4EC;
extern void* lbl_804CA61C;
extern void* lbl_804CA620;
extern void* lbl_804CA624;
extern void* lbl_804CA628;
extern void* lbl_804CA670;
extern void* lbl_804CA4E8;
extern void* lbl_804CA674;
extern void* lbl_804CA68C;
extern void* lbl_804CA694;
extern void* lbl_804CA5DC;
extern void* lbl_804CA640;
extern void* lbl_804CA644;
extern void* lbl_804CA648;
extern void* lbl_804CA64C;
extern "C" {
f32 fn_80127868(BU* p);
Rec7 fn_801278B8(BU* p, f32 bio);
s16 fn_80123AC4(BU* p);
s16 fn_80123D1C(BU* p);
s16 fn_8012386C(BU* p);
s16 fn_80123BF0(BU* p);
void fn_8002600C(void* log, int code, int v);
int fn_8011B77C(void* list, void* key);
int fn_80089D68(int n);
Slot* fn_80030CBC(BU* p);
Slot* fn_80030CF4(BU* p);
ItemD* fn_801116B8(Slot* s);
u8 fn_80120AC0(BU* a, BU* d);
u8 fn_80120BB0(BU* a, BU* d);
int fn_80110758(int t);
void fn_801088DC(void* s, BU* d, int n);
void fn_80108BA8(void* s, BU* d, int n);
void fn_80108A20(void* s, BU* d, int n);
void fn_801089B4(void* s, BU* d, int n);
void fn_80108AD0(void* s, BU* d, int n);
void fn_80108B3C(void* s, BU* d, int n);
void fn_80108830(void* s, BU* d, int n);
int fn_80126BA4(BU* a);
void fn_80030B58(BU* d, void* log, u8 k, int z);
void fn_80030C78(BU* d, void* log, int z);
int fn_8011F2F0(BU* a, BU* d);
int fn_80121DEC(BU* d);
static inline int rollP(int n) {
    if (BT->f15ec & 0x4000) {
        if (lbl_803C8DA0.xa3) return 1;
        return 0;
    }
    return fn_80089D68(n);
}
#define R(m) (lbl_803C8DA0.x20[lbl_803C8DA0.xa0] & (m))
#define HAS(u, k) fn_8011B77C((u)->x12c, lbl_804CA##k)
#define LOG(c) fn_8002600C(b->log, c, 0)
#define G (!(b->f15ec & 0x100) && !a->x48a)
#define CRIT3 if (a->x445 == 0x6f) { a->x445 = 0x6e; a->x45a = a->x45a / 3; }
#define RA(fn) rollP(ax + fn(a) / 2)
static inline int wtype(Slot* s) { return s->data ? s->data->x13 : 0x13; }
#define NZ(v) if (a->x45a < 0) a->x45a = 0
#pragma use_lmw_stmw on
void fn_80028A68(Battle* b, BU* a, BU* d, int f) {
    /*P*/
    int fail;
    int a2;
    s8 ax;
    int cap;
    int flag;
    int a1;
    int a3;
    int u1;
    int u2;
    int v1;
    int w1;
    int v2;
    int w2;
    int v3;
    int w3;
    int v4;
    int w4;
    s8 dx;
    int heal;
/*E*/
    Rec7 sa;
    Rec7 sd;
    f32 bioA = fn_80127868(a);
    sa = fn_801278B8(a, bioA);
    ax = sa.f;
    f32 bioB = fn_80127868(d);
    sd = fn_801278B8(d, bioB);
    dx = sd.f;
    if (f == 0 && R(8)) LOG(0x45);
    if (R(0x4000)) LOG(0x44);
    if (R(1)) LOG(0x42);
    if (a->x445 == 0x70) return;
    fail = 0;
    if (HAS(d, 63C)) {
        if (!fn_80030CBC(a)->data || !((fn_80030CBC(a)->x5 >> 4) & 1)) {
            LOG(0x6a);
            LOG(0x6d);
            a->x445 = 0x6e;
            fail = 1;
            a->x45a = 0;
        }
    }
    if (R(0x100) || (HAS(d, 6E0) && rollP(dx + fn_80123AC4(d)))) {
        LOG(0x5e);
        LOG(0x6d);
        a->x445 = 0x6e;
        fail = 1;
        a->x45a = 0;
    }
    if (fail) return;
    cap = 0;
    if (R(0x400)) {
        if ((int)d->x114 == 1) {
            a->x445 = 0x70;
            a->x45a = 0;
            return;
        }
        cap = 0x61;
    }
    if (HAS(a, 6A0) && !(fn_801116B8(fn_80030CBC(a))->flags & 0x4000)) {
        if ((int)d->x114 == 1) {
            LOG(0x60);
            a->x445 = 0x70;
            a->x45a = 0;
            return;
        }
        cap = 0x60;
    }
    if (R(0x200) || (HAS(d, 680) && rollP(dx + fn_80123D1C(d)))) {
        if ((int)d->x114 == 1) {
            LOG(0x5f);
            a->x445 = 0x70;
            a->x45a = 0;
            return;
        }
        cap = 0x5f;
    }
    flag = 0;
    if (HAS(a, 5EC) && G && RA(fn_80123AC4)) {
        CRIT3;
        LOG(0x4a);
        a->x45a = a->x45a * 4;
    }
    if (R(0x20) || (HAS(a, 5F0) && G && RA(fn_80123AC4))) {
        CRIT3;
        a1 = d->x44a;
        heal = (s16)(fn_8012386C(a) - a1);
        if (heal < 0) heal = 0;
        a2 = a->x448;
        a3 = d->x44a;
        a->x45a = heal + (a2 + fn_8012386C(a) * 2 - a3);
        NZ();
        fn_8002600C(b->log, 0x51, heal);
    }
    if (HAS(a, 5F4) && G && RA(fn_80123AC4)) {
        CRIT3;
        LOG(0x48);
        a->x45a = a->x45a * 3;
        LOG(0x7f);
        fn_801088DC(d->x110, d, 5);
    }
    if (R(4) || (HAS(a, 5F8) && G && RA(fn_80123AC4))) {
        CRIT3;
        if (R(0x4000)) {
            a->x45a = a->x448;
            NZ();
        } else {
            u1 = a->x448;
            a->x45a = u1 + fn_8012386C(a) * 2;
            NZ();
            LOG(0x4b);
        }
    }
    if (HAS(a, 5FC) && G && RA(fn_80123AC4)) {
        CRIT3;
        LOG(0x4c);
        u2 = a->x448;
        a->x45a = u2 + fn_8012386C(a) * 4;
        NZ();
    }
    if (HAS(a, 600) && G && a->x45a < (s8)d->x114 && rollP(fn_80120AC0(a, d))) {
        CRIT3;
        LOG(0x4f);
        a->x45a = (s8)d->x114 - 1;
    }
    if (R(0x10) || (HAS(a, 604) && G && rollP(fn_80120BB0(a, d)))) {
        CRIT3;
        LOG(0x50);
        a->x45a = (s8)d->x114;
    }
    if (HAS(a, 608) && G && RA(fn_80123AC4) && fn_80110758(wtype(fn_80030CBC(a)))) {
        CRIT3;
        LOG(0x4d);
        a->x45a = a->x448;
        NZ();
        flag = 1;
    }
    if (HAS(a, 60C) && G && RA(fn_80123AC4) && fn_80110758(wtype(fn_80030CBC(a)))) {
        CRIT3;
        LOG(0x4e);
        a->x45a = a->x448;
        NZ();
        LOG(0x86);
        fn_80108BA8(d->x110, d, 1);
    }
    if (R(2) || (HAS(a, 610) && G && RA(fn_80123AC4))) {
        CRIT3;
        if (!R(0x4000)) {
            a->x45a = a->x45a * 3;
            LOG(0x43);
        }
        flag = 1;
    }
    if (R(0x800) || (HAS(a, 614) && G && RA(fn_80123AC4))) {
        CRIT3;
        LOG(0x63);
        a->x45a = a->x45a * 3;
        LOG(0x82);
        fn_80108A20(d->x110, d, 1);
    }
#define AETHER(k, rf, lg, mul, lg2, fx, t23, t31) \
    if (HAS(a, k) && HAS(a, 4EC) && G && RA(rf)) { \
        CRIT3; \
        LOG(lg); \
        t23 = a->x448; \
        t31 = d->x44a; \
        a->x45a = t23 + fn_8012386C(a) * mul - t31; \
        NZ(); \
        LOG(lg2); \
        fx(d->x110, d, 1); \
    }
    AETHER(618, fn_8012386C, 0x52, 2, 0x81, fn_801089B4, v1, w1)
    AETHER(61C, fn_80123BF0, 0x53, 4, 0x81, fn_801089B4, v2, w2)
    AETHER(620, fn_80123AC4, 0x54, 2, 0x84, fn_80108AD0, v3, w3)
    AETHER(624, fn_80123BF0, 0x55, 2, 0x85, fn_80108B3C, v4, w4)
    if (HAS(a, 628) && HAS(a, 4EC) && G && RA(fn_80123AC4)) {
        CRIT3;
        LOG(0x56);
        a->x45a = a->x45a * 3;
    }
    if (R(0x2000) || (HAS(a, 670) && !(b->f15ec & 0x100) && !HAS(d, 4E8) && fn_80030CF4(d)->data && !d->x47d && RA(fn_80123AC4))) {
        LOG(0x5b);
        fn_80030B58(d, b->log, fn_80126BA4(a), 0);
    }
    if (HAS(a, 674) && !(b->f15ec & 0x100) && !HAS(d, 4E8) && fn_80030CF4(d)->data && !d->x47d && RA(fn_80123AC4)) {
        LOG(0x5c);
        fn_80030C78(d, b->log, 0);
    }
    if (R(0x80) || (HAS(a, 68C) && a == &b->a && rollP(ax + fn_80123AC4(a)))) {
        LOG(0x5d);
        a->x482 = 1;
    }
    if (R(0x1000) || (HAS(d, 694) && fn_8011F2F0(a, d) && !a->x48a && rollP(dx + fn_80123AC4(d)))) {
        a->x486 = 0x64;
    }
    if (HAS(d, 5DC) && fn_8011F2F0(a, d) && !a->x48a && rollP(0x64)) {
        a->x486 = 0x69;
    }
#define PAVISE(k, rf, v) \
    if (HAS(d, k) && !(b->f15ec & 0x100) && fn_8011F2F0(a, d) && !a->x48a && b->f15e8 == 2 && rollP(dx + rf(d))) { \
        a->x486 = v; \
    }
    PAVISE(640, fn_8012386C, 0x57)
    PAVISE(644, fn_80123BF0, 0x58)
    PAVISE(648, fn_80123D1C, 0x59)
    PAVISE(64C, fn_80123AC4, 0x5a)
    if ((fn_801116B8(fn_80030CBC(a))->flags & 0x2000) && !a->x48a && !fn_80121DEC(d)) {
        LOG(0x7e);
        fn_80108830(d->x110, d, 5);
    }
    if (fn_801116B8(fn_80030CBC(a))->x0 & 0x1000) {
        LOG(0x67);
        flag = 1;
    }
    if (a->x45a == 0) LOG(0x6d);
    if (flag && a->x45a > 0) a->x45c = a->x45a;
    if ((s8)d->x114 <= a->x45a) {
        switch (cap) {
        case 0x61:
            a->x45a = (s8)d->x114 - 1;
            break;
        case 0x60:
            a->x45a = (s8)d->x114 - 1;
            LOG(0x60);
            break;
        case 0x5f:
            a->x45a = (s8)d->x114 / 2;
            LOG(0x5f);
            break;
        }
    }
    a->x488 = a->x488 + a->x45a;
}
}
