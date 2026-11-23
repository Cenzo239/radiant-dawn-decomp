#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
typedef struct BU {
    Unit u;
    u8 pad3f4[0x448 - 0x3f4];
    s16 f448;
    s16 f44a;
    u8 pad44c[0x492 - 0x44c];
    u8 f492;
    u8 pad493[0x4a0 - 0x493];
} BU;
typedef struct Battle {
    BU a;     /* 0x000 */
    BU b;     /* 0x4A0 */
    BU c;     /* 0x940 */
    u8 log[0x15e4 - 0xde0]; /* 0xDE0 */
    u8 f15e4;
    u8 pad15e5[3];
    int f15e8;
    u32 f15ec;
    u32 f15f0;
    u32 f15f4;
    u32 f15f8;
    s8 f15fc;
    u8 pad15fd[0x1604 - 0x15fd];
    u8 f1604;
} Battle;
struct Spec {
    Unit* u;
    s8 x, y;
    s8 f6, f7;
    void* item;
    u8 fc;
    u8 fd, fe, ff;
};
extern "C" {
extern u8 lbl_803EC898[];
extern u8 lbl_803CB770[];
extern void* lbl_804CA698;
u8 fn_80089D68(int);
void fn_8002600C(void*, int, int);
void fn_80026324(void*, int, int, int);
void fn_800282A0(Battle*, BU*, BU*, int);
void fn_800275C4(Battle*, int, int);
f32 fn_80127868(BU*);
void fn_801278B8(BU*, f32);
int fn_8011B77C(void*, void*);
void fn_8011B430(void*, void*);
void fn_8011A36C(void*);
Slot* fn_80030CBC(BU*);
s16 fn_80123AC4(BU*);
void fn_80126D9C(void*, int);
s16 fn_801237EC(void*);
void fn_8002E7E0(BU*);
void fn_8006CC40(BU*);
void fn_8006DE7C(BU*);
u8* fn_80066130(void*, int, int, int);
void fn_8006625C(void*, int, int, int);
s16 fn_80067858(int, int, int);
void fn_8002CD5C(Battle*);
void fn_80126EB0(void*, int, int);
void fn_8002EF48(Battle*, int);
void fn_8002FFDC(Battle*, Slot*);
#if TARGET_PC
FE10_PROTO void fn_8003098C(Battle*, p32arg, int);
#else
void fn_8003098C(Battle*, int, int);
#endif
void fn_80030988(Battle*);
void fn_80030E54(Battle*, int);
void fn_80110D38(Slot*);
void fn_8002EA20(BU*, Battle*);
#if TARGET_PC
FE10_PROTO int fn_8002C774(Battle*, BU*, BU*);
#else
void fn_8002C774(Battle*, BU*, BU*);
#endif
int fn_8011F680(Unit*);
int fn_801220A0(BU*);

void fn_8002A780(Battle* bt, BU* a, BU* d, int dmg, int code, int heal) {
    int n;
    s8 c;
    s16 h;
    if (dmg == -0x8000) {
        dmg = (s16)(a->f448 - d->f44a);
        if (dmg < 0) dmg = 0;
    }
    if (dmg != 0) a->f492 = 1;
    n = d->u.s114 - dmg;
    if (n < 0) n = 0;
    dmg = (s16)(d->u.s114 - n);
    fn_80126D9C(d, n);
    heal += a->u.s114;
    if (heal > fn_801237EC(a)) heal = fn_801237EC(a);
    c = a->u.s114;
    heal = (s16)(heal - c);
    if (heal > dmg) heal = dmg;
    h = heal;
    heal = h + c;
    if (h != 0) fn_8002600C(bt->log, 0x8f, h);
    fn_80126D9C(a, heal);
    fn_8002600C(bt->log, 0x96, (s16)-dmg);
    fn_8002600C(bt->log, code, 0);
}

void fn_8002BCC4(Battle* b) {
    fn_8002E7E0(&b->a);
    if (!(b->f15ec & 1)) fn_8002E7E0(&b->b);
    fn_8006CC40(&b->a);
    if (!(b->f15ec & 1)) fn_8006CC40(&b->b);
    fn_8006DE7C(&b->a);
    if (!(b->f15ec & 1)) fn_8006DE7C(&b->b);
    if (b->f15ec & 0x100) {
        u8* t = fn_80066130(lbl_803CB770, b->b.u.x102, (s8)*(u8*)&b->b.u.y103, 4);
        t[4] = b->b.u.s114;
        if (b->b.u.s114 == 0) {
            fn_8006625C(lbl_803CB770, b->b.u.x102, (s8)*(u8*)&b->b.u.y103, 4);
        }
    }
}

void fn_8002BDA0(Battle* b, int a) {
    int c = b->b.u.s114;
    a = fn_80067858(c, fn_801237EC(&b->b), a);
    fn_80126D9C(&b->b, a + b->b.u.s114);
    fn_8002600C(b->log, 0x24, 0);
    fn_8002600C(b->log, 0x25, 0);
    fn_8002600C(b->log, 0x14, a);
    fn_8002600C(b->log, 0x6e, 0);
    fn_8002600C(b->log, 0x2a, 0);
}

void fn_8002BE64(Battle* b, int a) {
    int c = b->a.u.s114;
    a = fn_80067858(c, fn_801237EC(&b->a), a);
    fn_80126D9C(&b->a, a + b->a.u.s114);
    fn_8002600C(b->log, 0x24, 0);
    fn_8002600C(b->log, 0x25, 0);
    fn_8002600C(b->log, 9, a);
    fn_8002600C(b->log, 0x6e, 0);
    fn_8002600C(b->log, 0x2a, 0);
    if (b->a.u.s114 <= 0) fn_8002600C(b->log, 0xb, 0);
}

void fn_8002BF40(Battle* b, int a) {
    int c = b->b.u.s114;
    a = fn_80067858(c, fn_801237EC(&b->b), a);
    fn_80126D9C(&b->a, b->a.u.s114 - a);
    fn_80126D9C(&b->b, a + b->b.u.s114);
    fn_8002600C(b->log, 0x24, 0);
    fn_8002600C(b->log, 0x25, 0);
    fn_8002600C(b->log, 0x14, a);
    fn_8002600C(b->log, 9, (s16)-a);
    fn_8002600C(b->log, 0x6e, 0);
    fn_8002600C(b->log, 0x2a, 0);
    if (b->a.u.s114 <= 0) fn_8002600C(b->log, 0xb, 0);
    if (b->b.u.s114 <= 0) fn_8002600C(b->log, 0x16, 0);
    fn_8002CD5C(b);
}

void fn_8002C0EC(Battle* b, s8 a) {
    b->f15ec |= 4;
    fn_8002EF48(b, a);
    fn_800282A0(b, &b->a, &b->b, 0);
    fn_8002600C(b->log, 0x72, 0);
    fn_8002FFDC(b, fn_80030CBC(&b->a));
    fn_8003098C(b, 0, 1);
}

void fn_8002C170(Battle* b) {
    b->f15ec |= 4;
    fn_800282A0(b, &b->a, &b->b, 0);
    fn_8002600C(b->log, 0x72, 0);
}

void fn_8002C270(Battle* b, s8 a, int v) {
    int c;
    b->f15ec |= 8;
    fn_8002EF48(b, a);
    fn_800282A0(b, &b->a, &b->b, 0);
    fn_8002600C(b->log, 0x72, 0);
    fn_80030988(b);
    c = b->a.u.s114;
    v = (s8)fn_80067858(c, fn_801237EC(&b->a), (s8)v);
    fn_80126D9C(&b->a, v + b->a.u.s114);
    fn_8002600C(b->log, 0x24, 0);
    fn_8002600C(b->log, 0x25, 0);
    fn_8002600C(b->log, 9, v);
    fn_8002600C(b->log, 0x6e, 0);
    fn_8002600C(b->log, 0x2a, 0);
    fn_8002600C(b->log, 0x2b, 0);
    fn_8003098C(b, 0, 1);
}

void fn_8002C394(Battle* b, s8 a, s8 v) {
    b->f15ec |= 8;
    fn_8002EF48(b, a);
    fn_800282A0(b, &b->a, &b->b, 0);
    fn_8002600C(b->log, 0x72, 0);
    fn_80030988(b);
    fn_80030E54(b, v);
    fn_8002600C(b->log, 0x24, 0);
    fn_8002600C(b->log, 0x25, 0);
    fn_8002600C(b->log, 0x6e, 0);
    fn_8002600C(b->log, 0x2a, 0);
    fn_8002600C(b->log, 0x2b, 0);
    fn_8003098C(b, 0, 1);
}

void fn_8002C474(Battle* b, s8 a) {
    b->f15ec |= 8;
    fn_8002EF48(b, a);
    fn_800282A0(b, &b->a, &b->b, 0);
    fn_8002600C(b->log, 0x72, 0);
    fn_80030988(b);
    fn_8002600C(b->log, 0x24, 0);
    fn_8002600C(b->log, 0x25, 0);
    fn_8002600C(b->log, 0x6e, 0);
    fn_8002600C(b->log, 0x2a, 0);
    fn_8002600C(b->log, 0x2b, 0);
    fn_8003098C(b, 0, 1);
}

void fn_8002C53C(Battle* b, s8 a) {
    b->f15ec |= 0x8000;
    fn_8002EF48(b, a);
    fn_80110D38(fn_80030CBC(&b->b));
    fn_8002EA20(&b->b, b);
}

#if TARGET_PC
int fn_8002C84C(Battle* b, int f) {
    if (f == 0) {
        return fn_8002C774(b, &b->a, &b->b);
    } else {
        return fn_8002C774(b, &b->b, &b->a);
    }
}
#else
void fn_8002C84C(Battle* b, int f) {
    if (f == 0) {
        fn_8002C774(b, &b->a, &b->b);
    } else {
        fn_8002C774(b, &b->b, &b->a);
    }
}
#endif

int fn_8002DD1C(Battle* b) {
    BU* s;
    if (b->a.u.u3f0 && fn_8011F680(b->a.u.u3f0)) return 2;
    s = 0;
    if (b->a.u.u3f0 && b->a.u.f4[8] == 0) s = &b->a;
    if (b->b.u.u3f0 && b->b.u.f4[8] == 0) s = &b->b;
    if (s) return fn_801220A0(s);
    if (b->a.u.u3f0) return fn_801220A0(&b->a);
    return 2;
}

extern u8 lbl_803C8DA0[0xe0];

u8 fn_80026950(int n) {
    Battle* b = (Battle*)lbl_803C8E80;
    if (b->f15ec & 0x4000) {
        u8* p = lbl_803C8DA0;
        return p[0xa3];
    }
    return fn_80089D68(n);
}

static inline int rollP(int n) {
    if (lbl_803C8E80[0x15ec] & 0x40) {
        return lbl_803C8E80[0xc3] ? 1 : 0;
    }
    return fn_80089D68(n);
}


void fn_800269E4(Battle*, const Spec*, const Spec*);


void fn_8002E3D4(BU*);
void fn_80025FE0(void*);
void fn_8002E6FC(Battle*, Unit*);
void fn_8002E738(BU*);
void fn_80114888(void*, int);
#if TARGET_PC
FE10_PROTO void fn_80116098(void*, int, int, p32arg, p32arg);
#else
void fn_80116098(void*, int, int, int, int);
#endif
void fn_8002ED4C(Battle*, int, int);
void fn_8002F14C(Battle*);
u8 fn_80118130(void*, int, int);

struct Pos {
    s8 x, y;
    u8 pad[2];
    u8 f4;
    u8 f5;
};



}
