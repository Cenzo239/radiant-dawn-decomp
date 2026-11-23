/* AI: best tile for an attack, scored with the battle preview; fn_80155D2C, fn_8015639C, fn_80156A18. */
#include "game/rM_8014C9F8/ai.h"
struct BA { Unit* u; s8 x; s8 y; u8 p; u8 e; int a; int b; };
struct Cf { u8 pad[0x14]; u8 a[1]; };
class TF {
public:
    virtual int check(Unit*);
    virtual int at(Unit*, s16, s16);
};
extern "C" {
extern u8 lbl_803C8E80[];
extern BA lbl_80386F40, lbl_80386F50;
extern void fn_80111B34(void*);
extern void fn_80111C24(void*, int);
extern void fn_80110BB4(void*, void*);
extern void* fn_8010B204(int);
extern BA lbl_80386EE0, lbl_80386EF0, lbl_80386F00, lbl_80386F10;
extern u8 lbl_803CAB38[];
extern void* lbl_804CA66C;
extern void fn_800269E4(u8*, const BA&, const BA&);
extern void fn_8002742C(u8*, int);
extern u8 fn_80127520(Unit*);
extern int fn_801658E4(Unit*, int, int);
extern u16 fn_801676D8(int, int);
extern int fn_8016D11C(Unit*);
#if TARGET_PC
extern FE10_PROTO void fn_801586C8(u8*, u8*, int*, int*, p32arg);
#else
extern void fn_801586C8(u8*, u8*, int*, int*, int);
#endif
extern void fn_801539CC(Unit*, Unit*, void*);
#if TARGET_PC
extern FE10_PROTO u8* fn_80076F54(p32arg);
#else
extern u8* fn_80076F54(u32);
#endif
extern int fn_80158820(u8*, AiBest*);
extern int fn_8015897C(u8*, AiBest*);
extern int fn_80158B1C(u8*, AiBest*);
extern u32* fn_80060728(void*);
extern s16 fn_801237EC(u8*);
extern s8 fn_80126AA4(u8*);
extern int fn_80121DEC(u8*);
extern int fn_8011B77C(void*, void*);

static inline int Score(Unit* u, AiBest* c, int& ha) {
    
    int z3;
    int hp2;
    int z1;
    int hb;
    int k;
    int z2;
    int v;
    int s;
    int hp;
    int z4;
    int v2;
    u8* b;
    u8* w2;
    u8* p;

    p = fn_80076F54(*(u32*)((u8*)u + 0x3A4));
    s = fn_80158820(p, c);
    w2 = lbl_803C8E80 + 0x4A0;
    hp = *(s8*)(lbl_803C8E80 + 0x114);
    {
        f32 mx = fn_801237EC(lbl_803C8E80);
        z1 = (int)(10.0f * (fn_801237EC(lbl_803C8E80) - hp) / mx);
        ha = 0.03125f*((f32)z1 * (f32)(s8)p[0xD]);
    }
    hp2 = *(s8*)(w2 + 0x114);
    {
        f32 mx = fn_801237EC(w2);
        z2 = (int)(10.0f * (fn_801237EC(w2) - hp2) / mx);
        hb = 0.03125f*((f32)z2 * (f32)(s8)p[6]);
    }
    s += hb - ha;
    s += fn_8015897C(p, c);
    s += fn_80158B1C(p, c);
    k = 0;
    switch (*fn_80060728(lbl_803CAB38) & 3) {
    case 2:
        switch ((lbl_803CAB38 + (*(Unit**)(lbl_803C8E80 + 0x890))->team[8])[0x14]) {
        case 0:
        case 1:
            k = 10;
            break;
        }
        break;
    }
    s += k;
    z3 = fn_801676D8((s8)*(u8*)(lbl_803C8E80 + 0x102), (s8)*(u8*)(lbl_803C8E80 + 0x103)) >> 4;
    v = 0.03125f * ((f32)z3 * (f32)(s8)p[0xC]);
    s += v;
    b = lbl_803C8E80 + 0x4A0;
    z4 = fn_80126AA4(b);
    v2 = 0.03125f * ((f32)z4 * (f32)(s8)p[0xA]);
    if (fn_80121DEC(lbl_803C8E80) == 0 && fn_8011B77C(b + 0x12C, lbl_804CA66C)) {
        v2 -= 1000;
    }
    switch (*fn_80060728(lbl_803CAB38) & 3) {
    case 2:
        if (*(u32*)(b + 0x10C) & 1) {
            v2 += 5;
        }
        break;
    }
    s += v2;
    return s;
}
int fn_80155D2C(Unit* u, AiBest* c, TF* f) {
    
    int cost;
    Map* m;
    Inv* inv;
    int y;
    int x;
    int s;
    int d;
    int best;
    u32 t;
    int r;

    inv = &u->inv[c->item];
    m = &lbl_803EC898;
    best = 0x80000000;
    for (y = m->y0; y <= m->y1 - 1; y++) {
        for (x = m->x0; x <= m->x1 - 1; x++) {
            if (m->costS[(s8)x + (s8)y * 0x40] < 0) continue;
            if (lbl_803EC898.b5S[(s8)x + (s8)y * 0x40]) continue;
            if (fn_801658E4(u, (s8)x, (s8)y)) continue;
            if (lbl_803EC898.g4[(s8)x + (s8)y * 0x40] == 0) continue;
            t = m->ter[0][(s8)x + (s8)y * 0x40];
            if (t && t != u->padFC[0]) continue;
            cost = fn_801676D8((s8)x, (s8)y);
            if (fn_8016D11C(u) < cost) continue;
            if (f->at(c->t, x, y) == 0) continue;
            {
                BA b2 = lbl_80386EF0;
                b2.u = c->t;
                b2.x = c->t->x;
                b2.y = c->t->y;
                b2.p = fn_80127520(c->t);
                {
                    BA b1 = lbl_80386EE0;
                    b1.u = u;
                    b1.x = x;
                    b1.y = y;
                    b1.p = c->item;
                    fn_800269E4(lbl_803C8E80, b1, b2);
                }
            }
            fn_8002742C(lbl_803C8E80, lbl_803CA870.action);
            {
                int ac, a8;
                fn_801586C8(lbl_803C8E80, lbl_803C8E80 + 0x4A0, &a8, &ac, 0);
                d = a8 - ac;
                d -= fn_801676D8((s8)x, (s8)y) >> 4;
                fn_801539CC(u, c->t, inv);
                if (d > best) {
                    c->x = x;
                    best = d;
                    c->y = y;
                }
            }
        }
    }
    r = 0;
    if (best != 0x80000000) {
        {
            BA b2 = lbl_80386F10;
            b2.u = c->t;
            b2.x = c->t->x;
            b2.y = c->t->y;
            b2.p = fn_80127520(c->t);
            {
                BA b1 = lbl_80386F00;
                b1.u = u;
                b1.x = c->x;
                b1.y = c->y;
                b1.p = c->item;
                fn_800269E4(lbl_803C8E80, b1, b2);
            }
        }
        fn_8002742C(lbl_803C8E80, lbl_803CA870.action);
        c->score = Score(u, c, d);
        r = 1;
        c->score += best;
    }
    return r;
}
int fn_8015639C(Unit* u, AiBest* c, TF* f) {
    
    int cost;
    Map* m;
    Inv* inv;
    int y;
    int x;
    int s;
    int d;
    int best;
    u32 t;
    int r;

    inv = &u->inv[c->item];
    m = &lbl_803EC898;
    best = 0x80000000;
    for (y = m->y0; y <= m->y1 - 1; y++) {
        for (x = m->x0; x <= m->x1 - 1; x++) {
            if (m->costS[(s8)x + (s8)y * 0x40] < 0) continue;
            if (lbl_803EC898.b5S[(s8)x + (s8)y * 0x40]) continue;
            if (fn_801658E4(u, (s8)x, (s8)y)) continue;
            if (lbl_803EC898.g4[(s8)x + (s8)y * 0x40] == 0) continue;
            if ((s16)lbl_803EC898.cost2[(s8)x + (s8)y * 0x40] > 1) continue;
            t = m->ter[0][(s8)x + (s8)y * 0x40];
            if (t && t != u->padFC[0]) continue;
            cost = fn_801676D8((s8)x, (s8)y);
            if (fn_8016D11C(u) < cost) continue;
            if (f->at(c->t, x, y) == 0) continue;
            {
                BA b2 = lbl_80386EF0;
                b2.u = c->t;
                b2.x = c->t->x;
                b2.y = c->t->y;
                b2.p = fn_80127520(c->t);
                {
                    BA b1 = lbl_80386EE0;
                    b1.u = u;
                    b1.x = x;
                    b1.y = y;
                    b1.p = c->item;
                    fn_800269E4(lbl_803C8E80, b1, b2);
                }
            }
            fn_8002742C(lbl_803C8E80, lbl_803CA870.action);
            {
                int ac, a8;
                fn_801586C8(lbl_803C8E80, lbl_803C8E80 + 0x4A0, &a8, &ac, 0);
                d = a8 - ac;
                d -= fn_801676D8((s8)x, (s8)y) >> 4;
                fn_801539CC(u, c->t, inv);
                if (d > best) {
                    c->x = x;
                    best = d;
                    c->y = y;
                }
            }
        }
    }
    r = 0;
    if (best != 0x80000000) {
        {
            BA b2 = lbl_80386F10;
            b2.u = c->t;
            b2.x = c->t->x;
            b2.y = c->t->y;
            b2.p = fn_80127520(c->t);
            {
                BA b1 = lbl_80386F00;
                b1.u = u;
                b1.x = c->x;
                b1.y = c->y;
                b1.p = c->item;
                fn_800269E4(lbl_803C8E80, b1, b2);
            }
        }
        fn_8002742C(lbl_803C8E80, lbl_803CA870.action);
        c->score = Score(u, c, d);
        r = 1;
        c->score += best;
    }
    return r;
}
int fn_80156A18(Unit* u, AiBest* c, TF* f) {
    
    int cost;
    Map* m;
    Inv* inv;
    int y;
    int x;
    int s;
    int d;
    int best;
    u32 t;
    int r;

    inv = &u->inv[c->item];
    m = &lbl_803EC898;
    best = 0x80000000;
    for (y = m->y0; y <= m->y1 - 1; y++) {
        for (x = m->x0; x <= m->x1 - 1; x++) {
            if (m->costS[(s8)x + (s8)y * 0x40] < 0) continue;
            if (lbl_803EC898.b5S[(s8)x + (s8)y * 0x40]) continue;
            if (fn_801658E4(u, (s8)x, (s8)y)) continue;
            if (lbl_803EC898.g4[(s8)x + (s8)y * 0x40] == 0) continue;
            if ((s16)lbl_803EC898.cost2[(s8)x + (s8)y * 0x40] <= 1) continue;
            t = m->ter[0][(s8)x + (s8)y * 0x40];
            if (t && t != u->padFC[0]) continue;
            cost = fn_801676D8((s8)x, (s8)y);
            if (fn_8016D11C(u) < cost) continue;
            if (f->at(c->t, x, y) == 0) continue;
            {
                BA b2 = lbl_80386EF0;
                b2.u = c->t;
                b2.x = c->t->x;
                b2.y = c->t->y;
                b2.p = fn_80127520(c->t);
                {
                    BA b1 = lbl_80386EE0;
                    b1.u = u;
                    b1.x = x;
                    b1.y = y;
                    b1.p = c->item;
                    fn_800269E4(lbl_803C8E80, b1, b2);
                }
            }
            fn_8002742C(lbl_803C8E80, lbl_803CA870.action);
            {
                int ac, a8;
                fn_801586C8(lbl_803C8E80, lbl_803C8E80 + 0x4A0, &a8, &ac, 0);
                d = a8 - ac;
                d -= fn_801676D8((s8)x, (s8)y) >> 4;
                fn_801539CC(u, c->t, inv);
                if (d > best) {
                    c->x = x;
                    best = d;
                    c->y = y;
                }
            }
        }
    }
    r = 0;
    if (best != 0x80000000) {
        {
            BA b2 = lbl_80386F10;
            b2.u = c->t;
            b2.x = c->t->x;
            b2.y = c->t->y;
            b2.p = fn_80127520(c->t);
            {
                BA b1 = lbl_80386F00;
                b1.u = u;
                b1.x = c->x;
                b1.y = c->y;
                b1.p = c->item;
                fn_800269E4(lbl_803C8E80, b1, b2);
            }
        }
        fn_8002742C(lbl_803C8E80, lbl_803CA870.action);
        c->score = Score(u, c, d);
        r = 1;
        c->score += best;
    }
    return r;
}
}
