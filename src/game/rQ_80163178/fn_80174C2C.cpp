/* AI: target searches on the map, whole-army AI runners. */
#include "game/rQ_80163178/common.h"
struct Fk { void* vt; Unit* u; u8 k; };
static inline BOOL SameT(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}
extern "C" {
extern ListHdr lbl_803E7320[];
extern u8 lbl_803CAB38[];
extern u8 lbl_80387248[];
extern u8 lbl_80387308[];
extern u8 lbl_80387338[];
extern u8 lbl_80387790[];
extern u8 lbl_80387800[];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA5C0;
#else
extern u32 lbl_804CA5C0;
#endif
void* memset(void*, int, u32);
void fn_80163010(AiCfg*, Unit*);
void fn_80045120(AiAct*, Unit*);
void fn_80045548(AiAct*);
void fn_80166720(Unit*);
#if TARGET_PC
FE10_PROTO int fn_80169718(Unit*, ptr32<const void>, ptr32<const void>);
#else
int fn_80169718(Unit*, void*, void*);
#endif
#if TARGET_PC
FE10_PROTO int fn_80169558(Unit*, ptr32<const void>, ptr32<const void>);
#else
int fn_80169558(Unit*, void*, void*);
#endif
#if TARGET_PC
FE10_PROTO int fn_80169870(Unit*, ptr32<const void>, ptr32<const void>);
#else
int fn_80169870(Unit*, void*, void*);
#endif
int fn_80152C20(void*, void*, int);
#if TARGET_PC
FE10_PROTO int fn_801699C8(Unit*, ptr32<const void>, ptr32<const void>);
#else
int fn_801699C8(Unit*, void*, void*);
#endif
void fn_8010E41C(u8*, int);
#if TARGET_PC
FE10_PROTO Unit* fn_8012CE54(p32arg);
#else
Unit* fn_8012CE54(int);
#endif
int fn_801658E4(Unit*, s8, s8);
void fn_80165E18(Unit*, int, int);
void fn_801659F4(int, int, int, int, int);
int fn_8011EFC8(Unit*, Unit*);
int fn_8016CB60(Unit*, Inv*);
int fn_80162B54(void*, Unit*);
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, u32);
#endif
void fn_800CFB34(ListHdr*);
void fn_800398E0(void*, int);
void* fn_800CFD18(ListHdr*, int);
Unit* fn_800CFB0C(void* e);
s8 fn_8016CC18(Unit*, Unit*, int*);
void fn_800392FC(void*, int, int);
int fn_8016D11C(Unit*);
void fn_80169B20(Unit*, u16, int, int, void*, s16*, s16*);
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
u32 fn_80045274(AiAct*);
int fn_8010E2F4(Side*);
extern Side* lbl_804CB814;
extern u8 lbl_803872F8[];
u8* fn_801116B8(Inv*);
void fn_80165F94(Unit*, int, int);
int fn_80171378(int, int, Filt*);
void fn_8016F94C(Unit*, int, int, int, u16, int, int, int);

u32 fn_80174C2C(void) {
    AiAct* a = &lbl_803CA870;
    Unit* u = a->unit;
    if (lbl_804183F0.flags & 2 || u->w3B4 & 0x7000000) {
        return 0;
    }
    if (u->hp == 0 || (u->flags10C & 0x18)) {
        return 0;
    }
    if (lbl_803CAB38[0x11] != u->team[8]) {
        return 0;
    }
    return fn_80045274(a);
}

int fn_8016E2AC(Unit* u, s16* ox, s16* oy, u32* res) {
    u32 v, w;
    int r = 1;
    if (!u || !u->person) {
        if (res) {
            *res = 9;
        }
        return 0;
    }
    w = u->flags10C;
    v = u->flags108;
    if (w & 0x18) {
        if (res) *res = 1;
        r = 0;
    } else if (w & 4) {
        if (res) *res = 4;
        r = 1;
    } else if (v & 4) {
        if (res) *res = 5;
        r = 1;
    } else if (w & 0x40) {
        if (res) *res = 6;
        r = 1;
    } else if (w & 0x80) {
        if (res) *res = 7;
        r = 0;
    } else {
        if (res) *res = 0;
    }
    if (r) {
        *ox = u->x;
        *oy = u->y;
    }
    return r;
}

int fn_8016E3BC(int id, s16* ox, s16* oy, u32* res) {
    Unit* u = fn_8012CE54(id);
    u32 v, w;
    int r = 1;
    if (!u || !u->person) {
        if (res) {
            *res = 9;
        }
        return 0;
    }
    w = u->flags10C;
    v = u->flags108;
    if (w & 0x18) {
        if (res) *res = 1;
        r = 0;
    } else if (w & 4) {
        if (res) *res = 4;
        r = 1;
    } else if (v & 4) {
        if (res) *res = 5;
        r = 1;
    } else if (w & 0x40) {
        if (res) *res = 6;
        r = 1;
    } else if (w & 0x80) {
        if (res) *res = 7;
        r = 0;
    } else {
        if (res) *res = 0;
    }
    if (r) {
        *ox = u->x;
        *oy = u->y;
    }
    return r;
}

BOOL fn_8016E50C(Filter* f, Unit* u, s16* ox, s16* oy) {
    s16 best = 0x7FFF;
    s16 bx, by;
    int y;
    fn_80165E18(u, 6, lbl_803EC898.w * lbl_803EC898.h);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        int x;
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40] && f->check(UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40])) && lbl_803EC898.costS[(s8)x + (s8)y * 0x40] < best) {
                {
                    bx = x;
                    by = y;
                    best = lbl_803EC898.costS[(s8)x + (s8)y * 0x40];
                }
            }
        }
    }
    if (best != 0x7FFF) {
        *ox = bx;
        *oy = by;
        return 1;
    }
    return 0;
}

BOOL fn_8016E67C(Filter* f, Unit* u, s16* ox, s16* oy) {
    s16 best = 0x7FFF;
    s16 bx, by;
    int y;
    fn_801659F4(u->x, u->y, 0, 6, lbl_803EC898.w * lbl_803EC898.h);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        int x;
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40] && f->check(UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40])) && lbl_803EC898.costS[(s8)x + (s8)y * 0x40] < best) {
                {
                    bx = x;
                    by = y;
                    best = lbl_803EC898.costS[(s8)x + (s8)y * 0x40];
                }
            }
        }
    }
    if (best != 0x7FFF) {
        *ox = bx;
        *oy = by;
        return 1;
    }
    return 0;
}

static inline void AiPrep(Unit* v) {
    v->m3D0[0] = 0x40;
    v->b3BC = 0;
    fn_80163010(&lbl_804183F0, v);
    lbl_804183F0.done = 0;
    memset(&lbl_804183F0.res, 0, 0x14);
    fn_80045120(&lbl_803CA870, v);
    fn_80166720(v);
}

u8 fn_80173188(void) {
    AiAct* act = &lbl_803CA870;
    u8 tbl[0xB];
    int m = 0x80000000;
    Unit* best = 0;
    int id;
    Unit* v;
    fn_8010E41C(tbl, 0);
    for (id = 1; id <= 0xFE; id++) {
        v = UnitGet(id);
        if (v->person) {
            if (tbl[v->team[8]] && !(v->flags10C & 0x9D)) {
                Filt a;
                Filt b;
                v->m3D0[0] = 0x40;
                v->b3BC = 0;
                fn_80163010(&lbl_804183F0, v);
                lbl_804183F0.done = 0;
                memset(lbl_804183F0.res, 0, 0x14);
                fn_80045120(act, v);
                fn_80166720(v);
                b.vt = lbl_80387338;
                b.u = v;
                a.u = v;
                a.vt = lbl_80387308;
                if (fn_80169718(v, &a, &b) && v->h3BE > m) {
                    m = v->h3BE;
                    best = v;
                }
                lbl_804183F0.done = 0;
                fn_80045548(act);
            }
        }
    }
    if (best) {
        Filt a;
        Filt b;
        best->m3D0[0] = 0x40;
        best->b3BC = 0;
        fn_80163010(&lbl_804183F0, best);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, best);
        fn_80166720(best);
        b.vt = lbl_80387338;
        b.u = best;
        a.u = best;
        a.vt = lbl_80387308;
        fn_80169718(best, &a, &b);
    }
    return lbl_804183F0.done;
}

u8 fn_80173628(void) {
    AiAct* act = &lbl_803CA870;
    u8 tbl[0xB];
    int m = 0x80000000;
    Unit* best = 0;
    int id;
    Unit* v;
    fn_8010E41C(tbl, 0);
    for (id = 1; id <= 0xFE; id++) {
        v = UnitGet(id);
        if (v->person) {
            if (tbl[v->team[8]] && !(v->flags10C & 0x9D)) {
                Filt a;
                Filt b;
                v->m3D0[0] = 0x40;
                v->b3BC = 0;
                fn_80163010(&lbl_804183F0, v);
                lbl_804183F0.done = 0;
                memset(lbl_804183F0.res, 0, 0x14);
                fn_80045120(act, v);
                fn_80166720(v);
                b.vt = lbl_80387338;
                b.u = v;
                a.u = v;
                a.vt = lbl_80387308;
                if (fn_80152C20(&a, &b, 0xF) && v->h3BE > m) {
                    m = v->h3BE;
                    best = v;
                }
                lbl_804183F0.done = 0;
                fn_80045548(act);
            }
        }
    }
    if (best) {
        Filt a;
        Filt b;
        best->m3D0[0] = 0x40;
        best->b3BC = 0;
        fn_80163010(&lbl_804183F0, best);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, best);
        fn_80166720(best);
        b.vt = lbl_80387338;
        b.u = best;
        a.u = best;
        a.vt = lbl_80387308;
        fn_80152C20(&a, &b, 0xF);
    }
    return lbl_804183F0.done;
}

u8 fn_801737FC(void) {
    AiAct* act = &lbl_803CA870;
    u8 tbl[0xB];
    int m = 0x80000000;
    Unit* best = 0;
    int id;
    Unit* v;
    fn_8010E41C(tbl, 0);
    for (id = 1; id <= 0xFE; id++) {
        v = UnitGet(id);
        if (v->person) {
            if (tbl[v->team[8]] && !(v->flags10C & 0x9D)) {
                Filt a;
                Filt b;
                v->m3D0[0] = 0x40;
                v->b3BC = 0;
                fn_80163010(&lbl_804183F0, v);
                lbl_804183F0.done = 0;
                memset(lbl_804183F0.res, 0, 0x14);
                fn_80045120(act, v);
                fn_80166720(v);
                b.vt = lbl_80387338;
                b.u = v;
                a.u = v;
                a.vt = lbl_80387308;
                if (fn_80169870(v, &a, &b) && v->h3BE > m) {
                    m = v->h3BE;
                    best = v;
                }
                lbl_804183F0.done = 0;
                fn_80045548(act);
            }
        }
    }
    if (best) {
        Filt a;
        Filt b;
        best->m3D0[0] = 0x40;
        best->b3BC = 0;
        fn_80163010(&lbl_804183F0, best);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, best);
        fn_80166720(best);
        b.vt = lbl_80387338;
        b.u = best;
        a.u = best;
        a.vt = lbl_80387308;
        fn_80169870(best, &a, &b);
    }
    return lbl_804183F0.done;
}

Unit* fn_80173C04(ListHdr* l) {
    AiAct* act = &lbl_803CA870;
    int m = 0x80000000;
    Unit* best = 0;
    int n;
    Unit* v;
    for (n = 0; n < l->n; n++) {
        Filt a;
        Filt b;
        v = fn_800CFB0C(fn_800CFD18(l, n));
        v->m3D0[0] = 0x40;
        v->b3BC = 0;
        fn_80163010(&lbl_804183F0, v);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, v);
        fn_80166720(v);
        b.vt = lbl_80387338;
        b.u = v;
        a.u = v;
        a.vt = lbl_80387308;
        if (fn_80169718(v, &a, &b) && v->h3BE > m) {
            m = v->h3BE;
            best = v;
        }
        lbl_804183F0.done = 0;
        fn_80045548(act);
    }
    return best;
}

Unit* fn_80173F08(ListHdr* l) {
    AiAct* act = &lbl_803CA870;
    int m = 0x80000000;
    Unit* best = 0;
    int n;
    Unit* v;
    for (n = 0; n < l->n; n++) {
        Filt a;
        Filt b;
        v = fn_800CFB0C(fn_800CFD18(l, n));
        v->m3D0[0] = 0x40;
        v->b3BC = 0;
        fn_80163010(&lbl_804183F0, v);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, v);
        fn_80166720(v);
        b.vt = lbl_80387338;
        b.u = v;
        a.u = v;
        a.vt = lbl_80387308;
        if (fn_80152C20(&a, &b, 0xF) && v->h3BE > m) {
            m = v->h3BE;
            best = v;
        }
        lbl_804183F0.done = 0;
        fn_80045548(act);
    }
    return best;
}

u8 fn_8016CDEC(Unit* u, void* f);
void fn_8016CF78(FF* f, s8 x, s8 y);
void fn_8017293C(FF* f, s8 x, s8 y);

u8 fn_80164330(Unit* u, u16 item);

static inline BOOL SideOn(int i, int k) {
    BOOL r = 0;
    if (fn_8010E2F4(&lbl_804CB814[i]) > 0 && lbl_803CAB38[k] == 1) {
        r = 1;
    }
    return r;
}
static inline BOOL IsNz(int v) {
    return v != 0;
}
Unit* fn_801739D0(ListHdr* l) {
    AiAct* act = &lbl_803CA870;
    bool y;
    bool x = IsNz(SideOn(0, 0x14));
    int m;
    Unit* best;
    int n;
    Unit* v;
    x = x | SideOn(3, 0x17);
    x = x | SideOn(1, 0x15);
    x = x | SideOn(2, 0x16);
    y = !x;
    m = 0x80000000;
    best = 0;
    for (n = 0; n < l->n; n++) {
        Filt a;
        Filt c;
        Filt b;
        v = fn_800CFB0C(fn_800CFD18(l, n));
        v->m3D0[0] = 0x40;
        v->b3BC = 0;
        fn_80163010(&lbl_804183F0, v);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, v);
        fn_80166720(v);
        {
            Filt* s;
            a.u = v;
            a.vt = lbl_80387308;
            c.u = v;
            c.vt = lbl_803872F8;
            s = &c;
            if (y) {
                s = &a;
            }
            b.vt = lbl_80387338;
            b.u = v;
            if (fn_80152C20(s, &b, 0xF) && (v->b3BC & 2) && v->h3BE > m) {
                m = v->h3BE;
                best = v;
            }
        }
        lbl_804183F0.done = 0;
        fn_80045548(act);
    }
    return best;
}

u8 fn_80172E70(void);

static inline BOOL HasW(Unit* u, Unit* v) {
    int i;
    BOOL any = 0;
    Inv* p = v->inv;
    for (i = 0; i < 7; i++, p++) {
        if (!p || !p->item) break;
        if (fn_8016CB60(u, p)) {
            any = 1;
            break;
        }
    }
    return any;
}
BOOL fn_8016E7FC(Filter* f, Unit* u, s16* ox, s16* oy) {
    s16 best = 0x7FFF;
    s16 bx, by;
    int y;
    fn_80165E18(u, 6, lbl_803EC898.w * lbl_803EC898.h);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        int x;
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]) {
                Unit* v = UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]);
                if (f->check(v)) {
                    Fk g;
                    g.u = u;
                    g.vt = lbl_80387248;
                    g.k = 1;
                    if (((Filter*)&g)->check(v) && lbl_803EC898.costS[(s8)x + (s8)y * 0x40] < best) {
                        bx = x;
                        by = y;
                        best = lbl_803EC898.costS[(s8)x + (s8)y * 0x40];
                    }
                }
            }
        }
    }
    if (best != 0x7FFF) {
        *ox = bx;
        *oy = by;
        return 1;
    }
    return 0;
}
BOOL fn_8016EDE8(Filter* f, Unit* u, s16* ox, s16* oy);
}
