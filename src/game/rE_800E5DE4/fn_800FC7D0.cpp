#include "game/rE_800E5DE4/types.h"
struct W3 { u32 a, b, c; };
struct Ctl2 { u8 pad[0x10]; u8 x10; };
struct Eff { u8 pad[0x10]; Ctl2* c; };
struct MU {
    u8 pad0[4];
    f32 x4, x8;
    u8 padc[0x28 - 0xc];
    u8 x28[0xc4 - 0x28];
    s16 xc4;
    u8 padc6[0xd4 - 0xc6];
    s8 xd4[4];
};
struct UP { u8 pad[0x30]; MU* m; };
struct Cls { u8 pad[8]; const char* x8; };
struct Eg { u8 pad[8]; Cls* x8; };
struct Cam { u8 pad[0x78]; f32 x78; };
struct Cmd;
extern u8 lbl_803EC898[];
extern "C" {
Eff* fn_800F47F4(MU*);
int fn_80008C98(void*, int);
int fn_80118098(void*, s8, s8);
int fn_8011D260(int);
Eg* fn_8010B240(int);
void fn_800076E8(Vec*, void*, int);
void fn_800FB904(s16, f32, f32);
int fn_800E4588(void);
f32 fn_80113F00(void*, f32, f32);
Cam* fn_8013B9A8(void);
void* fn_80068DE4(void);
Cmd* fn_800E3810(const char*, void*);
void fn_800E48AC(Cmd*, f32, f32, f32);
void fn_800E49AC(Cmd*, f32);
static inline void Pl3(Cmd* c, f32 x, f32 y, f32 z) { fn_800E48AC(c, x, y, z); }
#pragma inline_max_size(4000)
static inline void body(UP* p0) {
    /*P*/
    int y;
    Cmd* c;
    f32 z;
    MU* m;
    Eff* e;
    int k;
    int x;
    int ii;
    int kind;
    Eg* eg;
    const char* nm;
    void* mdl;
    UP* pp;
/*E*/
    Vec v;
    W3 q;
    pp = p0;
    m = pp->m;
    mdl = m->x28;
    e = fn_800F47F4(m);
    if (!e) return;
    if (e->c->x10 & 8) return;
    if (!fn_80008C98(mdl, 0x32)) return;
    {
        f32 my;
        f32 mx;
        mx = pp->m->x4;
        my = pp->m->x8;
        x = (int)mx;
        y = (int)my;
    }
    k = (u8)fn_80118098(lbl_803EC898, (s8)x, (s8)y);
    kind = fn_8011D260(k);
    eg = fn_8010B240(k);
    switch (kind) {
    case 0x39:
    case 0x10:
        for (ii = 0; ii < 4; ii++) {
            int j = pp->m->xd4[ii];
            if (j >= 0) {
                fn_800076E8(&v, mdl, j);
                *(W3*)&q = *(W3*)&v;
                f32 an = 0.015625f * (f32)pp->m->xc4;
                fn_800FB904(360.0f - an, ((Vec*)&q)->x, ((Vec*)&q)->y);
            }
        }
        break;
    }
    if (!eg->x8->x8) return;
    if (fn_800E4588() >= 0x20) return;
    z = fn_80113F00(lbl_803EC898, (f32)x, (f32)y);
    if (kind == 0x60) {
        if (z > fn_8013B9A8()->x78) z = fn_8013B9A8()->x78;
    }
    nm = eg->x8->x8;
    c = fn_800E3810(nm, fn_80068DE4());
    Pl3(c, pp->m->x4, pp->m->x8, z);
    fn_800E49AC(c, 0.015625f * (f32)pp->m->xc4);
}
void fn_800FC7D0(UP* p0) { body(p0); }
}
