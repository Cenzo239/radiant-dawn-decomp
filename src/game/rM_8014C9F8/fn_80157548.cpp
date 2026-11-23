/* AI: score of attacking from a trap tile, fn_80157548. */
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
extern BA lbl_80386F20;
extern BA lbl_80386F30;
extern u8 lbl_803CB770[];
extern u8* fn_80066130(void*, int, int, int);
extern void* fn_80066D18(u8*);
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

static inline int Score(Unit* u, AiBest* c) {
    
    int z4;
    int z1;
    u8* p;
    int z3;
    int hb;
    int v2;
    int z2;
    int ha;
    int hp2;
    int s;
    int hp;
    u8* w2;
    int k;
    u8* b;
    int v;

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

int fn_80157548(Unit* u, AiBest* c) {
    u8* t = fn_80066130(lbl_803CB770, (s8)c->x, (s8)c->y, 7);
    {
        BA b2 = lbl_80386F30;
        b2.u = c->t;
        b2.x = c->t->x;
        b2.y = c->t->y;
        BA b1 = lbl_80386F20;
        b1.u = u;
        b1.x = c->x;
        b1.y = c->y;
        b1.a = (int)fn_80066D18(t);
        fn_800269E4(lbl_803C8E80, b1, b2);
    }
    fn_8002742C(lbl_803C8E80, lbl_803CA870.action == 0x15 ? 0x15 : 0xF);
    c->score = Score(u, c);
    return 1;
}
}
