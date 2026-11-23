/* EQUIVALENT (sched, round 19b): fn_80058944: start of the sortie ("Sally") menu: clears unit flags, rebuilds the deploy tile list and its neighbour links, creates the menu procs and the token sprite, then picks the proc script by mode.
 * Moved instructions (checked with dd.py): the same three constant loads in the inlined sprite constructor as the fn_8005B508 family.
 * Caveats: the options block is written through a local view `SOpt` (decls.h has it as bitfield struct Opt44) and a named zero `z`; the sprite constructor is a copy of the one in equiv/fn_8005B508.cpp. */
#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw off
struct Sally { u8 pad[0x954]; s8 n; s8 pairs[1]; };
struct SUnit { u8 pad[0xe4]; SUnit* next; u8 pad2[0x24]; u32 flags10C; };
struct SProc { u8 pad[0x40]; int mode; u8 pad2[8]; void* child; };
struct SChild { u8 pad[0x2c]; u8 f2c; u8 pad2[3]; void* f30; };
struct SOpt { u8 pad[0x21]; u8 b21; u8 b22; u8 pad2[5]; int w28; };
extern "C" {
void* fn_800CFD18(Word*, int);
int fn_80057B7C(void*, int*);
int fn_80057A3C(void*, int*);
int fn_800578FC(void*, int*);
int fn_800577BC(void*, int*);
void fn_8011FDD8(SUnit*, int);
SChild* fn_80081050(void*, void*);
void fn_80084F0C(const char*);
void fn_8012FC90(void);
extern u8 lbl_804CB838;
extern u8 lbl_8037E11C[];
extern u8 lbl_8037E108[];
extern u8 lbl_8037E1E8[];
extern u8 lbl_8037E218[];
}
static inline void sprBaseInit(Spr* p) {
        p->f4 = 0;
        p->vt = lbl_8038CB1C;
        p->f8 = -1;
        p->fa = 0;
        p->fc = 0x190;
        p->fe = 0x260;
        p->f10 = 0x1c0;
        p->f12 = 0;
        p->f14 = 0;
        p->f16 = 0x260;
        p->f18 = 0x30;
        p->f1a = 0;
        p->f1c = 0;
        p->f1e = 0;
        p->f20 = 0;
        p->f22 = 0xff;
        p->f23 = 0xff;
        p->f24 = 0xff;
        p->f25 = 0xff;
        p->f26 = 0x316;
        p->f28 = 0;
        p->f2c = 1.0f;
        p->f30 = 1.0f;
        p->f34 = 1.0f;
        p->f38 = 0x10;
        p->f3c = 0;
        p->f40 = 0;
        p->f44 = 0;
        p->f48 = 0;
        p->f4c = 0;
        p->f50 = 1;
        p->f5a = 0;
        p->f5e = 0;
}
static inline void sprInit(Spr* p) {
        sprBaseInit(p);
        p->vt = lbl_8038C1C0;
        p->f60 = 0;
        p->f64 = 0;
        p->f58 = 0x30;
        p->f5c = 0x30;
        p->f54 = 0.75f;
}
static inline Spr* newSpr(void) {
    Spr* p = (Spr*)fn_80079150(0x68);
    if (p) {
        sprInit(p);
    }
    return p;
}


extern "C" void fn_80058944(SProc* p) {
    int a, b, c, d;
    Sally* g;
    s8* q;
    int i2;
    int i;
    void* tt;
    int n;
    SUnit* u;
    SUnit* next;
    SChild* ch;
    Spr* s;
    Spr* s2;
    int t;
    switch (p->mode) {
    case 5:
        lbl_804CB838 |= 0x10;
        break;
    }
    lbl_804CB550 = 0;
    lbl_804CB700 &= ~1;
    for (u = *(SUnit**)(lbl_804CB814 + 4); u != 0; u = next) {
        next = u->next;
        if (u->flags10C & 0x10000dc) {
            fn_8011FDD8(u, 5);
        }
    }
    {
        g = (Sally*)&lbl_803CAB38;
        n = g->n;
        fn_800CFB34(&lbl_803E7320);
        q = g->pairs;
        for (i = 0; i < n; i++) {
            fn_800CFC50(&lbl_803E7320, q[0], q[1], 0, 0);
            q += 2;
        }
    }
    if (lbl_803E7320.i0 >= 2) {
        for (i2 = 0; i2 < lbl_803E7320.i0; i2++) {
            tt = fn_800CFD18(&lbl_803E7320, i2);
            fn_80057B7C(tt, &a);
            fn_80057A3C(tt, &b);
            fn_800578FC(tt, &c);
            fn_800577BC(tt, &d);
        }
    }
    ch = fn_80081050(lbl_8037E11C, p);
    if (ch) {
        ch->f30 = fn_800CFD3C(&lbl_803E7320);
    }
    fn_80081050(lbl_8037E108, ch);
    p->child = ch;
    ch->f2c |= 8;
    fn_80084F0C(lbl_80361F9C + 0x62);
    s = newSpr();
    s->f8 = -0x1000;
    s->f4c = 1;
    s->f64 = lbl_80361F9C + 0x6f;
    s->f38 |= 0x10;
    s->f60 = 0;
    s->f28 = 8;
    fn_801E5448(p, s);
    s2 = fn_801E5640(p, -0x1000, 0);
    if (s2) {
        s2->f60 = 1;
    }
    {
        SOpt* op = (SOpt*)fn_80060728(&lbl_803CAB38);
        int z = 0;
        op->b21 = z;
        ((SOpt*)fn_80060728(&lbl_803CAB38))->b22 = z;
        ((SOpt*)fn_80060728(&lbl_803CAB38))->w28 = z;
    }
    if (!(lbl_804CB700 & 0x10)) {
        t = fn_800685B0(fn_8006074C(&lbl_803CAB38));
        if (fn_8024F7EC(t)) {
            fn_80251838(0, t, 0.0f);
        }
    }
    lbl_804CB700 |= 0x10000;
    switch (p->mode) {
    case 1:
    case 2:
    case 3:
    case 6:
        lbl_804CB554 = lbl_8037E1E8;
        break;
    case 4:
    case 5:
        lbl_804CB554 = lbl_8037E218;
        break;
    }
    fn_8012FC90();
}
