/* AI: pick the best attack over items and targets; 80152C20, 80153070, 801534C0. */
#include "game/rM_8014C9F8/ai.h"

extern "C" {

extern int fn_8010E398(void*, void*);
extern int fn_80155D2C(Unit*, AiBest*, void*);

#pragma use_lmw_stmw on
u8 fn_80152C20(Filter* f, void* arg, int act) {
    Inv* p;
    Unit* u = lbl_803CA870.unit;
    AiBest best;
    AiBest cur;
    int k;
    u8 tbl[0xC];
    int r;
    int d;
    Map* m = &lbl_803EC898;
    fn_800453B4(&lbl_803CA870, act);
    memset(&best, 0, 0x10);
    best.score = 0x80000000;
    best.t = NULL;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + (u->y << 6)] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    memset(&cur, 0, 0x10);
    p = u->inv;
    for (k = 0; k < 7; k++, p++) {
        if (p == NULL || p->item == NULL) {
            break;
        }
        if (fn_8012BA20(u, p->item)) {
            int i;
            cur.item = k;
            fn_8010E41C(tbl, 1);
            for (i = 1; i <= 0xFE; i++) {
                Unit* v = UnitGet(i);
                if (v->person && tbl[v->team[8]] && f->check(v)) {
                    d = fn_8028DB44(u->x - v->x) + fn_8028DB44(u->y - v->y);
                    if (p->item != NULL) {
                        r = (u8)fn_801107C0(p->item, u);
                    } else {
                        r = 0;
                    }
                    int rg = (s8)fn_8012408C(u);
                    if (d <= rg + r && !(v->flags10C & 0x10000DC) && !MapOutU(&lbl_803EC898, v) && fn_8011F1A8(u, v)) {
                        int b;
                        if (p->item != NULL) {
                            r = (u8)fn_801107C0(p->item, u);
                        } else {
                            r = 0;
                        }
                        if (p->item != NULL) {
                            b = (u8)fn_801107A0(p->item, u);
                        } else {
                            b = 0;
                        }
                        fn_801663E0(v->x, v->y, b, r, 7);
                        cur.t = v;
                        if (fn_80155D2C(u, &cur, arg)) {
                            if (fn_8016D070()) {
                                if (*(u32*)(fn_80158C98() + 0x14) & 0x100) {
                                    if (!(cur.fl & 8)) goto P;
                                    continue;
                                }
                            } else if (fn_8016D090() && (cur.fl & 8)) {
                                continue;
                            }
                            P:
                            if (cur.score > best.score) {
                                best = cur;
                            }
                        }
                    }
                }
            }
        }
    }
    if (best.t != NULL) {
        if (best.item < 7) {
            fn_8012A088(u, best.item);
            best.item = 0;
        }
        fn_80160610(lbl_803CA870.action, (s8)best.x, (s8)best.y, best.t, (s8)*(u8*)&best.t->x, best.t->y, (s8)best.item, 0, 0);
        u->b3BC |= best.fl;
        u->h3BE = best.score;
    }
    return lbl_804183F0.done;
}
extern int fn_8015639C(Unit*, AiBest*, void*);

#pragma use_lmw_stmw on
u8 fn_80153070(Filter* f, void* arg, int act) {
    Inv* p;
    Unit* u = lbl_803CA870.unit;
    AiBest best;
    AiBest cur;
    int k;
    u8 tbl[0xC];
    int r;
    int d;
    Map* m = &lbl_803EC898;
    fn_800453B4(&lbl_803CA870, act);
    memset(&best, 0, 0x10);
    best.score = 0x80000000;
    best.t = NULL;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + (u->y << 6)] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    memset(&cur, 0, 0x10);
    p = u->inv;
    for (k = 0; k < 7; k++, p++) {
        if (p == NULL || p->item == NULL) {
            break;
        }
        if (fn_8012BA20(u, p->item)) {
            int i;
            cur.item = k;
            fn_8010E41C(tbl, 1);
            for (i = 1; i <= 0xFE; i++) {
                Unit* v = UnitGet(i);
                if (v->person && tbl[v->team[8]] && f->check(v)) {
                    d = fn_8028DB44(u->x - v->x) + fn_8028DB44(u->y - v->y);
                    if (p->item != NULL) {
                        r = (u8)fn_801107C0(p->item, u);
                    } else {
                        r = 0;
                    }
                    int rg = (s8)fn_8012408C(u);
                    if (d <= rg + r && !(v->flags10C & 0x10000DC) && !MapOutU(&lbl_803EC898, v) && fn_8011F1A8(u, v)) {
                        int b;
                        if (p->item != NULL) {
                            r = (u8)fn_801107C0(p->item, u);
                        } else {
                            r = 0;
                        }
                        if (p->item != NULL) {
                            b = (u8)fn_801107A0(p->item, u);
                        } else {
                            b = 0;
                        }
                        fn_801663E0(v->x, v->y, b, r, 7);
                        cur.t = v;
                        if (fn_8015639C(u, &cur, arg)) {
                            if (fn_8016D070()) {
                                if (*(u32*)(fn_80158C98() + 0x14) & 0x100) {
                                    if (!(cur.fl & 8)) goto P;
                                    continue;
                                }
                            } else if (fn_8016D090() && (cur.fl & 8)) {
                                continue;
                            }
                            P:
                            if (cur.score > best.score) {
                                best = cur;
                            }
                        }
                    }
                }
            }
        }
    }
    if (best.t != NULL) {
        if (best.item < 7) {
            fn_8012A088(u, best.item);
            best.item = 0;
        }
        fn_80160610(lbl_803CA870.action, (s8)best.x, (s8)best.y, best.t, (s8)*(u8*)&best.t->x, best.t->y, (s8)best.item, 0, 0);
        u->b3BC |= best.fl;
        u->h3BE = best.score;
    }
    return lbl_804183F0.done;
}
extern int fn_80156A18(Unit*, AiBest*, void*);

#pragma use_lmw_stmw on
u8 fn_801534C0(Filter* f, void* arg, int act) {
    Inv* p;
    Unit* u = lbl_803CA870.unit;
    AiBest best;
    AiBest cur;
    int k;
    u8 tbl[0xC];
    int r;
    int d;
    Map* m = &lbl_803EC898;
    fn_800453B4(&lbl_803CA870, act);
    memset(&best, 0, 0x10);
    best.score = 0x80000000;
    best.t = NULL;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + (u->y << 6)] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    memset(&cur, 0, 0x10);
    p = u->inv;
    for (k = 0; k < 7; k++, p++) {
        if (p == NULL || p->item != NULL) {
            break;
        }
        if (fn_8012BA20(u, p->item)) {
            int i;
            cur.item = k;
            fn_8010E41C(tbl, 1);
            for (i = 1; i <= 0xFE; i++) {
                Unit* v = UnitGet(i);
                if (v->person && tbl[v->team[8]] && f->check(v)) {
                    d = fn_8028DB44(u->x - v->x) + fn_8028DB44(u->y - v->y);
                    if (p->item != NULL) {
                        r = (u8)fn_801107C0(p->item, u);
                    } else {
                        r = 0;
                    }
                    int rg = (s8)fn_8012408C(u);
                    if (d <= rg + r && !(v->flags10C & 0x10000DC) && !MapOutU(&lbl_803EC898, v) && fn_8011F1A8(u, v)) {
                        int b;
                        if (p->item != NULL) {
                            r = (u8)fn_801107C0(p->item, u);
                        } else {
                            r = 0;
                        }
                        if (p->item != NULL) {
                            b = (u8)fn_801107A0(p->item, u);
                        } else {
                            b = 0;
                        }
                        fn_801663E0(v->x, v->y, b, r, 7);
                        cur.t = v;
                        if (fn_80156A18(u, &cur, arg)) {
                            if (fn_8016D070()) {
                                if (*(u32*)(fn_80158C98() + 0x14) & 0x100) {
                                    if (!(cur.fl & 8)) goto P;
                                    continue;
                                }
                            } else if (fn_8016D090() && (cur.fl & 8)) {
                                continue;
                            }
                            P:
                            if (cur.score > best.score) {
                                best = cur;
                            }
                        }
                    }
                }
            }
        }
    }
    if (best.t != NULL) {
        if (best.item < 7) {
            fn_8012A088(u, best.item);
            best.item = 0;
        }
        fn_80160610(lbl_803CA870.action, (s8)best.x, (s8)best.y, best.t, (s8)*(u8*)&best.t->x, best.t->y, (s8)best.item, 0, 0);
        u->b3BC |= best.fl;
        u->h3BE = best.score;
    }
    return lbl_804183F0.done;
}

static inline void Fn2Init(Fn2* f, Unit* u) {
    f->vt = lbl_80387338;
    f->u = u;
}

static inline BOOL SameSide(Unit* a, Unit* b) {
    return (u8)fn_8010E398(a->team, b->team) == 1;
}

struct Reach {
    u8 pad0[4];
    AiBest* a;   /* 0x4 */
    Unit* u;     /* 0x8 */
    AiBest* b;   /* 0xC */
};

#pragma use_lmw_stmw off
BOOL fn_80153910(Unit* u, Unit* v, u8** item) {
    int d = fn_8028DB44(u->x - v->x) + fn_8028DB44(u->y - v->y);
    int r;
    if (*item != NULL) {
        r = (u8)fn_801107C0(*item, u);
    } else {
        r = 0;
    }
    int rg = (s8)fn_8012408C(u);
    return d <= rg + r;
}

#pragma use_lmw_stmw off
void fn_801539CC(Unit* u, Unit* v, u8** item) {
    int r;
    int b;
    if (*item != NULL) {
        r = (u8)fn_801107C0(*item, u);
    } else {
        r = 0;
    }
    if (*item != NULL) {
        b = (u8)fn_801107A0(*item, u);
    } else {
        b = 0;
    }
    fn_801663E0(v->x, v->y, b, r, 7);
}

extern int fn_80157548(Unit*, AiBest*, void*);
extern u8 lbl_803E7320[];
#if TARGET_PC
extern FE10_PROTO void fn_800CFC50(void*, int, int, u8, p32arg);
#else
extern void fn_800CFC50(void*, int, int, u8, int);
#endif
extern u8* fn_800CFCB4(void*, int, int);
extern void fn_800392FC(void*, int, int);

#pragma use_lmw_stmw off
void fn_80153FBC(Reach* r, Unit* v) {
    BOOL same = SameSide(r->u, v);
    AiBest t;
    Fn2 f;
    memset(&t, 0, 0x10);
    t.x = r->a->x;
    t.y = r->a->y;
    t.t = v;
    t.item = r->b->item;
    Fn2Init(&f, r->u);
    if (fn_80157548(r->u, &t, &f)) {
        if (same) {
            r->b->score += t.score;
        } else {
            r->b->score -= t.score;
        }
    }
}

struct Vis {
    void* vt;
    Filter* f;  /* 0x4 */
    s8 x;       /* 0x8 */
    s8 y;       /* 0x9 */
    virtual int visit(Unit*);
};

#pragma use_lmw_stmw off
void fn_80155A80(Vis* p, Unit* v) {
    if (SameSide(lbl_803CA870.unit, v) && !p->f->check(v)) {
        return;
    }
    fn_800CFC50(lbl_803E7320, v->x, (s8)*(u8*)&v->y, ((u8*)v)[0xFC], 0);
}

#pragma use_lmw_stmw off
void fn_80155BCC(Vis* p, Unit* v) {
    if (fn_8011F1A8(lbl_803CA870.unit, v) && p->f->check(v)) {
        u8* e = fn_800CFCB4(lbl_803E7320, p->x, (s8)*(u8*)&p->y);
        if (e == NULL) {
            fn_800CFC50(lbl_803E7320, p->x, (s8)*(u8*)&p->y, 0, 1);
        } else {
            int n = *(int*)(e + 4) + 1;
            s8 y = p->y;
            s8 x = p->x;
            e[0] = x;
            e[1] = y;
            e[2] = 0;
            *(int*)(e + 4) = n;
        }
    }
}

#pragma use_lmw_stmw off
void fn_80155CA0(Vis* p, Unit* v) {
    if (fn_8011F1A8(lbl_803CA870.unit, v) && p->f->check(v)) {
        fn_800CFC50(lbl_803E7320, v->x, (s8)*(u8*)&v->y, ((u8*)v)[0xFC], 0);
    }
}

extern u8* fn_801181E8(Map*, int, int);
extern int fn_8011B77C(void*, void*);
extern char* lbl_804CA500;
extern int fn_801676D8(int, int);
extern int fn_80158208(Unit*, int, int, int);
extern s8 lbl_8036A090[];
static inline u32 IsFoeT(Unit* a, Unit* b) { return (u8)fn_8010E398(a->team, b->team) == 1; }

static inline int Terrain(Unit* u, u8* t) {
    int a;
    if (fn_8011B77C((u8*)u + 0x12C, lbl_804CA500)) {
        s8* s = *(s8**)(t + 8);
        a = s[3] + s[4];
        a += s[5];
        a += (u8)s[6];
    } else {
        s8* s = *(s8**)(t + 8);
        a = s[0] + s[1];
        a += s[2];
        a += (u8)s[6];
    }
    return a;
}

#pragma use_lmw_stmw off
int fn_8015814C(Unit* u, s8 x, s8 y) {
    u8* t = fn_801181E8(&lbl_803EC898, x, y);
    int h = Terrain(u, t) >> 1;
    return h;
}

/* from fn_80152C20.cpp */
extern s8 lbl_8036A090[];
extern s8 lbl_8036A0DC[];
extern void fn_800392FC(void*, int, int);
#if TARGET_PC
extern FE10_PROTO int fn_80158354(Unit*, Unit*, ptr32<const void>, int);
#else
extern int fn_80158354(Unit*, Unit*, void*, int);
#endif
static inline int TerrainH(Unit* u, u8* t) { return Terrain(u, t) >> 1; }
#pragma use_lmw_stmw on
int fn_80158208(Unit* u, int x, int y, int k) {
    int r = 0;
    s8* p;
    for (p = lbl_8036A090; *p != 0x7F; p += 3) {
        BOOL out;
        s16 tx = x + p[0];
        out = 0;
        s16 ty = y + p[1];
        if (tx < lbl_803EC898.x0 || lbl_803EC898.x1 - 1 < tx || ty < lbl_803EC898.y0 || lbl_803EC898.y1 - 1 < ty) {
            out = 1;
        }
        if (!out && lbl_803EC898.ter[0][(s8)tx + (s8)ty * 0x40] != 0) {
            if (IsFoeT(u, UnitGet(lbl_803EC898.ter[0][(s8)tx + (s8)ty * 0x40])) == 1) {
                r -= p[2];
            } else {
                r += p[2];
            }
        }
    }
    return r;
}
extern u8 lbl_803C8E80[];
extern s8 lbl_8036A0DC[];
extern char* lbl_804CA4D8;
extern void fn_800392FC(void*, int, int);
#if TARGET_PC
extern FE10_PROTO int fn_80158354(Unit*, Unit*, ptr32<const void>, int);
#else
extern int fn_80158354(Unit*, Unit*, void*, int);
#endif
#pragma use_lmw_stmw off
void fn_80155B20(Vis* p, s8 x, s8 y) {
    p->x = x;
    p->y = y;
    if (lbl_803EC898.ter[0][x + y * 0x40] != 0) {
        ((Filter*)p)->check(UnitGet(lbl_803EC898.ter[0][x + y * 0x40]));
    }
    fn_800392FC(p, x, y);
}

#pragma use_lmw_stmw off
int fn_80158B1C(u8* w) {
    u8* b = lbl_803C8E80;
    int r = 0;
    u16 f = *(u16*)(*(u8**)(*(u8**)(b + 0x890) + 0xF0) + 0xEE);
    if (f & 1) {
        r = (s8)w[0xE];
    }
    if (f & 2) {
        r += (s8)w[0xF];
    }
    if (f & 4) {
        r += (s8)w[0x10];
    }
    if (f & 8) {
        r += (s8)w[0x11];
    }
    if (f & 0x10) {
        r += (s8)w[0x12];
    }
    if (f & 0x20) {
        r += (s8)w[0x13];
    }
    if (f & 0x40) {
        r += (s8)w[0x14];
    }
    if (f & 0x80) {
        r += (s8)w[0x15];
    }
    if (f & 0x100) {
        r += (s8)w[0x16];
    }
    if ((f & 0x400) || fn_8011B77C(b + 0x5CC, lbl_804CA4D8)) {
        r += (s8)w[0x17];
    }
    return 0.03125f * ((f32)r * (f32)(s8)w[8]);
}

#pragma use_lmw_stmw on

}
