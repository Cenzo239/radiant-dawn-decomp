/* fn_8004564C (round 17): case locals hoisted to a /*P*/ block and one sw.py pass: 313 of 1050 by position (was 325).
 * The rotation is unchanged: the case-34 loop counter (and Rec's v) outrank o; declaration order, loop forms, a
 * member-function body, a wrapper and a loop inline did not move it. */
/* fn_8004564C: near miss. Structure matches (1050 of 1050 instructions); registers rotated: o and p should be r31/r29 but take r30/r28 because the first case-local in each case outranks them; plus one load order in Fire87/88. Compiles on its own. */
/* Command action start: per-kind setup dispatch (names guessed). */
#include "game/rT_80026898/types.h"
struct W3 { u32 a, b, c; };
struct SpecA { Unit* u; u8 x, y, r, k; void* it; u8 m, m1, m2, m3; };
struct SpecB { Unit* u; u8 x, y, r, k; Item* it; u8 m, m1, m2, m3; };
struct TB { u32 w0, w4, w8, wC; };
struct Cel { u8 b0, b1, b2, b3; void* w4; };
struct Mark { Unit* u; u8 b4; u8 b5; u8 b6; u8 b7; };
struct Map2 { u8 pad[0xD]; u8 occ[0x3000]; u8 flags[0x10000]; };
extern "C" {
extern Map2 lbl_803EC898;
extern u8 lbl_803CAB38[];
extern u8 lbl_803CB770[];
extern const TB lbl_8037B188, lbl_8037B1F0;
extern const SpecA lbl_8037B198, lbl_8037B200;
extern u8 lbl_8037AE48[], lbl_8037AE70[], lbl_8037AE90[], lbl_8037AED0[], lbl_8037AF08[], lbl_8037AF80[], lbl_8037B058[], lbl_8037B118[], lbl_8037B140[], lbl_8037B168[];
void* fn_800E3A10(const char*, void*);
void fn_80253EE4(const char*, f32);
void fn_800E48AC(void*, f32, f32, f32);
u8* fn_80066130(void*, int, int, int);
void fn_8013CB90(int, int, void*);
void fn_80108A20(void*, Unit*, int);
void fn_80046FE4(CmdState*, void*, int);
int fn_8012084C(Unit*, Unit*);
int fn_80026950(u8);
int fn_80121DEC(Unit*);
void fn_80103638(Unit*, Unit*, void*);
W3 fn_800F7790(Unit*);
void fn_800EE270(W3, void*);
void fn_80103684(Unit*, Unit*, void*);
void* fn_80081194(void*, void*);
void fn_8011E300(Unit*, int, int, int);
void fn_801036D0(Unit*, Unit*, int, int, void*);
void fn_80026C44(void*, Unit*, Unit*);
void fn_8002B2AC(void*, int, int);
void fn_8002DBA0(void*, int);
void fn_8006C440(void*);
void fn_8006DE18(void*);
void fn_800262D8(void*);
void fn_80026EE8(void*, Unit*, void*);
void fn_8002B668(void*);
void fn_8004985C(CmdState*, void*);
void fn_80111A0C(Unit*, void*, void*);
void fn_80103778(Unit*, Unit*, Unit*, void*);
void fn_8010316C(Unit*, u8, int, int, void*);
void fn_8009FEB0(void*);
void* fn_80067E20(int);
void fn_8010D8B4(void*, int, void*);
void* fn_8010B228(const char*);
void fn_8003A664(Unit*, void*);
void fn_8003A3BC(Unit*, void*);
void fn_80026CD8(void*, Unit*, int);
void fn_8002C170(void*);
void fn_800E8188(void*, void*);
void fn_800E81EC(void*, void*);
void fn_800E86D4(void*, void*);
void fn_800484AC(int a);
void fn_800485B8(int a);
void fn_8004869C();
Cel* fn_800CFD18(void*, int);
s16 fn_80123998(Unit*);
void fn_8002C06C(void*, int);
void fn_800487DC(CmdState*, void*);
void fn_80048A98(CmdState*, void*);
void fn_80048D54(CmdState*, void*);
void fn_80048FF8(CmdState*, void*);
void fn_800492B8(CmdState*, void*);
void fn_80111B34(Item*);
void fn_80110BFC(Item*, const char*);
void fn_80026E64(void*, Item*);
void fn_80111C24(Item*, int);
void fn_800A04C8(void*, int, int, int);
int fn_800626E0(void*);
void fn_800615DC(void*, int);
int fn_800A05B0(int, int, int);
void* fn_80065E10(void* t);
void fn_80117F74(void*, void*);
void fn_8003B5C8(int, int, void*);
void fn_8013DA20(int, int, void*, int, void*);
Mark* fn_80062A9C(void*, int);
u8* fn_80066E24(void*, int, int, int);
void fn_80126EB0(Unit*, int, int);
void fn_801046B0(Unit*, u8, int, int);
void fn_80049F8C(CmdState*, void*);
void fn_8004A110(CmdState*, void*);
void fn_8004A2C4(CmdState*, void*);
int fn_80161CD0(Unit*);
int fn_80161D98(Unit*);
s8 fn_80127520(Unit*);
void fn_800269E4(void*, void*, void*);
void fn_8002BDA0(void*, int);
void fn_800E7670(void*, int);
void fn_800E76B8(void*, int);
int fn_801237EC(Unit*);

static inline void Enc(void* p) {
    void* e = fn_800E3A10(lbl_803619D0, p);
    if (e) {
        Unit* u = lbl_803CA870.unit;
        fn_80253EE4(lbl_803619D0 + 0xC, 0.0f);
        f32 z = *(f32*)((u8*)u + 0xC);
        f32 y = *(f32*)((u8*)u + 8);
        f32 x = *(f32*)((u8*)u + 4);
        fn_800E48AC(e, x, y, z);
    }
}
static inline void SetAct(u8 k) {
    CmdState* c = &lbl_803CA870;
    c->action = k;
    if ((s8)c->f16 == 0) c->fd = k;
}
static inline u8 Dir(s8 x1, s8 y1, s8 x2, s8 y2) {
    if (x1 < x2) return 2;
    if (x1 > x2) return 1;
    if (y1 < y2) return 4;
    if (y1 > y2) return 8;
    return 0x40;
}
static inline u8 Opp(u8 d) {
    switch (d) {
    case 1: return 2;
    case 2: return 1;
    case 4: return 8;
    case 8: return 4;
    }
    return 0x40;
}
static inline void Occupy(void* r, int k, void* p) {
    CmdState* c = &lbl_803CA870;
    Map2* m = &lbl_803EC898;
    m->occ[(s8)c->cx + (s8)c->cy * 0x40] = c->unit->fc;
    fn_8010D8B4(r, k, p);
}
static inline void Hop(CmdState* o, void* p, int k) {
    Unit* u = lbl_803CA870.unit;
    int x = u->x102;
    int y = u->y103;
    u8* q = fn_80066E24(lbl_803CB770, x, y, k);
    int tx = x + ((s8)q[0] - x) * 2;
    int ty = y + ((s8)q[1] - y) * 2;
    u8 d = Dir(x, y, (s8)tx, (s8)ty);
    fn_80126EB0(u, (s8)tx, (s8)ty);
    fn_801046B0(u, d, p != 0, 0);
    o->cx = tx;
    o->cy = ty;
}
static inline void Rec(CmdState* o, int k) {
    u8 y = o->y;
    u8 x = o->x;
    u8 v = (u8)o->f18;
    Unit* u = o->unit;
    Mark* r = fn_80062A9C(lbl_803CAB38, k);
    r->u = u;
    r->b4 = v;
    if ((s8)x >= 0) r->b6 = x;
    if ((s8)y >= 0) r->b7 = y;
}
static inline W3 Get(Unit* u) { W3 v = fn_800F7790(u); return v; }
#define B lbl_803C8E80
#define COUNT (*(int*)lbl_803E7320)
static inline void Fire87(void* p, Item* it) {
    CmdState* c = &lbl_803CA870;
    Unit* u1 = c->unit;
    Unit* u2 = c->unit2;
    fn_80111B34(it);
    fn_80110BFC(it, lbl_803619D0 + 0x50);
    SpecB b;
    SpecA a = lbl_8037B198;
    a.u = u2;
    a.x = u2->x102;
    a.y = u2->y103;
    a.r = fn_80127520(u2);
    *(u32*)&b.x = lbl_8037B188.w4;
    *(u32*)&b.m = lbl_8037B188.wC;
    b.u = u1;
    b.x = c->cx;
    b.y = c->cy;
    b.it = it;
    fn_800269E4(B, &b, &a);
    fn_8002C170(B);
    fn_8002BDA0(B, fn_80123998(lbl_803CA870.unit) / 2);
    fn_8002C06C(B, 1);
    fn_800E7670(p, 0);
    fn_80111C24(it, -1);
}
static inline void Fire88(void* p, Item* it) {
    CmdState* c = &lbl_803CA870;
    Unit* u1 = c->unit;
    Unit* u2 = c->unit2;
    fn_80111B34(it);
    fn_80110BFC(it, lbl_803619D0 + 0x5E);
    SpecB b;
    SpecA a = lbl_8037B200;
    a.u = u2;
    a.x = u2->x102;
    a.y = u2->y103;
    a.r = fn_80127520(u2);
    *(u32*)&b.x = lbl_8037B1F0.w4;
    *(u32*)&b.m = lbl_8037B1F0.wC;
    b.u = u1;
    b.x = c->cx;
    b.y = c->cy;
    b.it = it;
    fn_800269E4(B, &b, &a);
    fn_8002C170(B);
    int h = c->unit2->s114;
    fn_8002BDA0(B, (s16)(fn_801237EC(c->unit2) - h));
    fn_8002C06C(B, 1);
    fn_800E76B8(p, 0);
    fn_80111C24(it, -1);
}

int fn_8004564C(CmdState* o, void* p) {
    u8 buf[0x108];
    Item it30;
    Item it87;
    Item it88;
/*P*/
    int i34;
    Unit* f27;
    Unit* f28;
    Unit* f29;
    u8 d7;
    void* s17;
    u8 k33;
    void* r33;
    Unit* u35;
    Unit* u34;
    int ny47;
    Cel* c34;
    void* a34;
    CmdState* c27;
    s16 v34;
    u8 y47;
    u8* t47;
    int dx47;
    int dy47;
    int nx47;
    u8 b34;
    Unit* u10;
    u8 x47;
    void* r86;
    void* r90;
/*E*/
    switch (o->action) {
    case 37:
        Enc(p);
        break;
    case 46:
        fn_80066130(lbl_803CB770, (s8)o->cx, (s8)o->cy, 9);
        fn_8013CB90((s8)o->cx, (s8)o->cy, p);
        fn_80108A20((u8*)lbl_803CA870.unit + 0x110, lbl_803CA870.unit, 1);
        break;
    case 19:
        fn_80046FE4(o, p, 1);
        break;
    case 20:
        fn_80046FE4(o, p, 2);
        break;
    case 25:
        if (fn_80026950((u8)fn_8012084C(o->unit, o->unit2)) && !fn_80121DEC(o->unit2)) {
            fn_80103638(o->unit, o->unit2, p);
            *(int*)o->pad1c = 1;
        } else {
            fn_800EE270(Get(o->unit2), p);
            *(int*)o->pad1c = 0;
        }
        break;
    case 26:
        fn_80103684(o->unit, o->unit2, p);
        break;
    case 27: {
        c27 = &lbl_803CA870;
        switch (lbl_803EC898.flags[(s8)c27->x + (s8)c27->y * 0x40]) {
        case 1:
            o->action = 0x25;
            if ((s8)o->f16 == 0) o->fd = 0x25;
            Enc(p);
            break;
        case 2:
            fn_80081194(lbl_8037AE48, p);
            break;
        default: {
            f27 = o->unit->f8;
            fn_8011E300(o->unit, (s8)o->x, (s8)o->y, 1);
            fn_801036D0(o->unit, f27, (s8)o->x, (s8)o->y, p);
            break;
        }
        }
        break;
    }
    case 15:
    case 21:
    case 22:
    case 65:
        fn_80026C44(B, o->unit, o->unit2);
        fn_8002B2AC(B, o->action, 0);
        fn_8002DBA0(B, o->action);
        fn_8006C440(B);
        fn_8006DE18(B);
        fn_800262D8(B + 0xDE0);
        fn_80081194(lbl_8037AF80, p);
        break;
    case 40:
        fn_80026EE8(B, o->unit, fn_80066130(lbl_803CB770, (s8)o->x, (s8)o->y, 4));
        fn_8002B668(B);
        fn_800262D8(B + 0xDE0);
        fn_80081194(lbl_8037B058, p);
        break;
    case 43:
    case 50:
        fn_8004985C(o, p);
        break;
    case 16:
        fn_80081194(lbl_8037AE90, p);
        break;
    case 53:
        fn_80081194(lbl_8037AE70, p);
        SetAct(4);
        break;
    case 4:
        fn_80111A0C(o->unit, o->unit->items[(s8)o->item].data, p);
        break;
    case 28: {
        f28 = o->unit->f8;
        fn_8011E300(o->unit, (s8)o->cx, (s8)o->cy, 1);
        fn_80103778(o->unit, o->unit2, f28, p);
        *(Unit**)o->pad8 = f28;
        break;
    }
    case 29: {
        f29 = o->unit2->f8;
        fn_8011E300(o->unit2, (s8)o->x, (s8)o->y, 1);
        fn_80103778(o->unit2, o->unit, f29, p);
        *(Unit**)o->pad8 = f29;
        break;
    }
    case 7: {
        d7 = Dir(o->unit->x102, o->unit->y103, o->unit2->x102, o->unit2->y103);
        fn_8010316C(o->unit, d7, 8, 0, p);
        fn_8010316C(o->unit2, Opp(d7), 8, 0, p);
        lbl_803EC898.flags[o->unit->x102 + o->unit->y103 * 0x40] |= 2;
        fn_8009FEB0(p);
        break;
    }
    case 78:
        fn_80081194(lbl_8037AED0, p);
        break;
    case 17: {
        s17 = &lbl_803CA870.unit2->items[(s8)lbl_803CA870.item];
        *(void**)((u8*)fn_80081194(lbl_8037AF08, p) + 0x54) = s17;
        break;
    }
    case 33: {
        k33 = lbl_803CAB38[0x90];
        lbl_803CAB38[0x90] = k33 + 1;
        r33 = fn_80067E20(k33);
        if (!r33) r33 = fn_80067E20(k33 - 1);
        if (r33) Occupy(r33, 0, p);
        break;
    }
    case 35: {
        u35 = o->unit;
        fn_8003A664(u35, fn_8010B228(lbl_803619D0 + 0x22));
        if (COUNT) {
            fn_80026CD8(B, lbl_803CA870.unit, -1);
            fn_8002C170(B);
            fn_800E8188(p, (void*)fn_800484AC);
        }
        break;
    }
    case 34: {
        u34 = o->unit;
        fn_8003A3BC(u34, fn_8010B228(lbl_803619D0 + 0x2B));
        if (COUNT) {
            for (i34 = 0; i34 < COUNT; i34++) {
                c34 = fn_800CFD18(lbl_803E7320, i34);
                a34 = c34->w4;
                b34 = c34->b2;
                v34 = fn_80123998(o->unit);
                c34->b0 = 3;
                c34->b1 = v34;
                c34->b2 = b34;
                c34->w4 = a34;
            }
            fn_80026CD8(B, lbl_803CA870.unit, -1);
            fn_8002C170(B);
            fn_800E81EC(p, (void*)fn_800485B8);
        }
        break;
    }
    case 31:
        fn_80026C44(B, o->unit, o->unit2);
        fn_8002C170(B);
        fn_8002C06C(B, 1);
        fn_800E86D4(p, (void*)fn_8004869C);
        break;
    case 18:
    case 44:
    case 64:
        fn_800487DC(o, p);
        break;
    case 66:
    case 67:
    case 68:
        fn_80048A98(o, p);
        break;
    case 69:
    case 70:
    case 71:
        fn_80048D54(o, p);
        break;
    case 72:
    case 73:
    case 74:
        fn_80048FF8(o, p);
        break;
    case 75:
    case 76:
    case 77:
        fn_800492B8(o, p);
        break;
    case 30:
        o->unit->f10c |= 0x2000;
        fn_80111B34(&it30);
        fn_80110BFC(&it30, lbl_803619D0 + 0x34);
        fn_80026C44(B, o->unit, o->unit2);
        fn_80026E64(B, &it30);
        fn_8002B2AC(B, 0xF, 0);
        fn_8006C440(B);
        fn_8006DE18(B);
        fn_800262D8(B + 0xDE0);
        fn_80081194(lbl_8037AF80, p);
        fn_80111C24(&it30, -1);
        break;
    case 9:
    case 13:
    case 14:
    case 38:
    case 42:
    case 45:
        fn_800A04C8(p, o->action, (s8)o->cx, (s8)o->cy);
        break;
    case 55:
    case 59:
        fn_800A04C8(p, o->action, (s8)o->x, (s8)o->y);
        break;
    case 10:
    case 11:
    case 12:
        if (lbl_803CA870.pad17 & 0x10) {
            u8* g = lbl_803CAB38;
            if (g[0x11] == 0) {
                fn_800615DC(g, fn_800626E0(g) - 0x32);
            }
        }
        if (fn_800A05B0(0xB, (s8)o->x, (s8)o->y)) {
            SetAct(0xB);
        } else if (fn_800A05B0(0xC, (s8)o->x, (s8)o->y)) {
            SetAct(0xC);
        }
        if ((s8)lbl_803CA870.item < 0) {
            u10 = o->unit;
            fn_80111A0C(u10, fn_8010B228(lbl_803619D0 + 0x40), p);
        } else {
            fn_80111A0C(o->unit, o->unit->items[(s8)o->item].data, p);
        }
        break;
    case 47: {
        y47 = lbl_803CA870.cy;
        x47 = lbl_803CA870.cx;
        t47 = fn_80066130(lbl_803CB770, (s8)x47, (s8)y47, 10);
        switch (t47[3]) {
        case 1: dx47 = -1; break;
        case 2: dx47 = 1; break;
        default: dx47 = 0; break;
        }
        nx47 = (s8)(x47 + dx47);
        switch (t47[3]) {
        case 4: dy47 = 1; break;
        case 8: dy47 = -1; break;
        default: dy47 = 0; break;
        }
        ny47 = (s8)(y47 + dy47);
        fn_80117F74(fn_80065E10(t), buf);
        fn_8003B5C8(nx47, ny47, buf);
        fn_8013DA20(nx47, ny47, buf, 0, p);
        break;
    }
    case 51:
    case 52:
        if (o->action == 0x33) {
            Rec(o, 0);
        } else {
            Rec(o, 3);
        }
        break;
    case 56:
        Hop(o, p, 1);
        break;
    case 57:
        Hop(o, p, 0);
        break;
    case 58:
        fn_80026EE8(B, o->unit, fn_80066130(lbl_803CB770, (s8)o->x, (s8)o->y, 4));
        fn_8002B668(B);
        fn_800262D8(B + 0xDE0);
        fn_80081194(lbl_8037B058, p);
        break;
    case 60:
        fn_80081194(lbl_8037B118, p);
        break;
    case 32:
        fn_80081194(lbl_8037B140, p);
        break;
    case 61:
        lbl_803CA870.f18 = 0;
        fn_80081194(lbl_8037B168, p);
        break;
    case 62:
        lbl_803CA870.f18 = 1;
        fn_80081194(lbl_8037B168, p);
        break;
    case 63:
        lbl_803CA870.f18 = 2;
        fn_80081194(lbl_8037B168, p);
        break;
    case 80:
    case 81:
    case 82:
    case 94:
    case 95:
        fn_80049F8C(o, p);
        break;
    case 83:
    case 84:
    case 85:
    case 96:
        fn_8004A110(o, p);
        break;
    case 86: {
        r86 = (void*)fn_80161CD0(o->unit);
        if (r86) Occupy(r86, 3, p);
        break;
    }
    case 87:
        Fire87(p, &it87);
        break;
    case 88:
        Fire88(p, &it88);
        break;
    case 90: {
        r90 = (void*)fn_80161D98(o->unit);
        if (r90) Occupy(r90, 3, p);
        break;
    }
    case 91:
    case 92:
    case 93:
        fn_8004A2C4(o, p);
        break;
    case 79:
    case 89:
        break;
    default:
        return 1;
    }
    return 0;
}
}
