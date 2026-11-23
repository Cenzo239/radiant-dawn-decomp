/* AI: move range setup, turn order. */
#include "game/rQ_80163178/types.h"
#pragma use_lmw_stmw on
#pragma auto_inline off
#define ABS(a) ((a) < 0 ? -(a) : (a))

class Filter {
public:
    virtual int check(Unit*);
    virtual int at(int, int, int);
};
struct ListHdr { int n; };
struct Side { Unit* head; Unit* tail; int n; };
struct SkillAct { char* name; void* item; int (*func)(Unit*, int, int, int); };

extern "C" Unit* lbl_804CB810;
static inline Unit* UnitGet(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}
extern "C" int fn_8010E398(void*, void*);
static inline BOOL SameT(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}

struct Bf110 { u8 pad[0x110]; u16 a : 9; u16 s : 3; };
class Pad5B8 {
public:
    virtual void v8(); virtual void vc(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual u32 v34();
};
struct Filt {
    void* vt;
    Unit* u;
};
struct Tb { void* n; void (*f)(Unit*, int); };
struct Cmp { int (*f)(u32, u32); };
extern "C" {
extern Side* lbl_804CB814;
extern Pad5B8* lbl_804CB5B8;
extern Tb lbl_80387768[];
extern u8 lbl_80387338[];
void fn_80133034(void);
void fn_8004564C(AiAct*, void*);
int fn_8011B680(void*, u8* skill);
void* fn_8010B23C(void*);
void fn_80152C20(Unit*, void*, int);
int fn_8010931C(void*);
int fn_8016D0B0(Unit*);
u8 fn_80106E30(void*);
void fn_80167704(Side*);
int fn_801681C4(Unit*, Unit*);
void fn_801681E0(Unit**, Unit**, int (*)(Unit*, Unit*));
extern u8 lbl_803CAB38[];
extern u8 lbl_804CB830;
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA5C0;
FE10_PROTO extern void *lbl_804CA5C4;
#else
extern u32 lbl_804CA5C0;
extern u32 lbl_804CA5C4;
#endif
extern int lbl_804CA7B0;
extern SkillAct lbl_80387690[];
extern u8 lbl_80387468[];
extern s16 lbl_8036B218[];
void* fn_8010B228(char*);
u8* fn_8010B240(u8);
void fn_80114888(Map*, int);
void fn_801151BC(Map*, Unit*);
void fn_8011567C(Map*, void*);
void fn_80115658(Map*, int, int);
void fn_80115764(Map*, int, int, u16);
void fn_80114B44(Map*, int, int);
void fn_80115DEC(Map*, int, int, u8, u8);
#if TARGET_PC
FE10_PROTO void fn_80116098(Map*, int, int, p32arg, p32arg);
#else
void fn_80116098(Map*, int, int, u8, u8);
#endif
s8 fn_8012408C(Unit*);
int fn_8012B868(Unit*, u8*);
u8 fn_801107C0(u8*, Unit*);
u16 fn_801676D8(int, int);
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, u32);
#endif
Unit* fn_80127CA0(Unit*);
int fn_8012BB48(Unit*, void*);
void fn_80081194_(void);
void fn_80053A7C(void);
int fn_8015804C(Unit*, int, int);
int fn_801658E4(Unit*, s8, s8);
void fn_80083DC4(void*, int);
void fn_800620A8(u8*, f32, f32);
#if TARGET_PC
FE10_PROTO void fn_801030B8(Unit*, int, int, int, int, p32arg);
#else
void fn_801030B8(Unit*, int, int, int, int, void*);
#endif

}
static inline BOOL MapOutU(Map* m, Unit* v) {
    s8 x = v->x;
    s8 y = v->y;
    BOOL r = 0;
    if (x < m->x0 || m->x1 - 1 < x || y < m->y0 || m->y1 - 1 < y) {
        r = 1;
    }
    return r;
}
extern "C" int fn_801681C4(Unit*, Unit*);
extern "C" void fn_801681E0(Unit**, Unit**, int (*)(Unit*, Unit*));
static inline void Sort(Unit** const& b, int n) {
    fn_801681E0(b, b + n, fn_801681C4);
}
static inline Tb* FindTb(Unit* u, u8* s, int k) {
    if (fn_8011B680(u->skills, s)) {
        Tb* t;
        for (t = lbl_80387768; t->f; t++) {
            if (k == ((u8*)fn_8010B23C(t->n))[0x1C] && t->f) {
                return t;
            }
        }
    }
    return 0;
}
static inline SkillAct* FindAct(Unit* u, u8* it) {
    if (fn_8012BB48(u, it)) {
        SkillAct* e;
        for (e = lbl_80387690; e->name; e++) {
            if (it == e->item && e->func) {
                return e;
            }
        }
    }
    return 0;
}
extern "C" {

void fn_80165B48(s8 x, s8 y, Unit* u, int k, int range) {
    Map* m = &lbl_803EC898;
    int i;
    if (u->w3B4 & 0x7000000) {
        range = 0;
    }
    fn_80114888(m, k);
    fn_801151BC(m, u);
    fn_8011567C(m, 0);
    if (u->w3B4 & 0x20000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 0x10) {
                fn_80115658(m, i, -1);
            }
        }
    }
    if (u->w3B4 & 0x40000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 8) {
                fn_80115658(m, i, -1);
            }
        }
    }
    if (u->w3B4 & 0x80000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 1) {
                fn_80115658(m, i, -1);
            }
        }
    }
    switch (range) {
    case -1:
        range = fn_8012408C(u);
    }
    fn_80115764(m, x, y, range);
}

void fn_80165CB0(s8 x, s8 y, Unit* u, int k, int range) {
    Map* m = &lbl_803EC898;
    int i;
    if (u->w3B4 & 0x7000000) {
        range = 0;
    }
    fn_80114888(m, k);
    fn_801151BC(m, u);
    fn_8011567C(m, u->team);
    if (u->w3B4 & 0x20000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 0x10) {
                fn_80115658(m, i, -1);
            }
        }
    }
    if (u->w3B4 & 0x40000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 8) {
                fn_80115658(m, i, -1);
            }
        }
    }
    if (u->w3B4 & 0x80000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 1) {
                fn_80115658(m, i, -1);
            }
        }
    }
    switch (range) {
    case -1:
        range = fn_8012408C(u);
    }
    fn_80115764(m, x, y, range);
}

void fn_80165E18(Unit* u, int k, int range) {
    Map* m = &lbl_803EC898;
    int i;
    if (u->w3B4 & 0x7000000) {
        range = 0;
    }
    fn_80114888(m, k);
    fn_801151BC(m, u);
    fn_8011567C(m, 0);
    if (u->w3B4 & 0x20000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 0x10) {
                fn_80115658(m, i, -1);
            }
        }
    }
    if (u->w3B4 & 0x40000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 8) {
                fn_80115658(m, i, -1);
            }
        }
    }
    if (u->w3B4 & 0x80000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 1) {
                fn_80115658(m, i, -1);
            }
        }
    }
    switch (range) {
    case -1:
        range = fn_8012408C(u);
    }
    fn_80115764(m, u->x, (s8)*(u8*)&u->y, range);
}

void fn_80165F94(Unit* u, int k, int range) {
    Map* m = &lbl_803EC898;
    int i;
    if (u->w3B4 & 0x7000000) {
        range = 0;
    }
    fn_80114888(m, k);
    fn_801151BC(m, u);
    fn_8011567C(m, u->team);
    if (u->w3B4 & 0x20000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 0x10) {
                fn_80115658(m, i, -1);
            }
        }
    }
    if (u->w3B4 & 0x40000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 8) {
                fn_80115658(m, i, -1);
            }
        }
    }
    if (u->w3B4 & 0x80000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 1) {
                fn_80115658(m, i, -1);
            }
        }
    }
    switch (range) {
    case -1:
        range = fn_8012408C(u);
    }
    fn_80115764(m, u->x, (s8)*(u8*)&u->y, range);
}

void fn_80166110(Unit* u, int k, int range) {
    Map* m = &lbl_803EC898;
    int i;
    if (u->w3B4 & 0x7000000) {
        range = 0;
    }
    fn_80114888(m, k);
    fn_801151BC(m, u);
    fn_80115658(m, 0xb6, 1);
    fn_80115658(m, 0xb0, 1);
    fn_8011567C(m, 0);
    if (u->w3B4 & 0x20000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 0x10) {
                fn_80115658(m, i, -1);
            }
        }
    }
    if (u->w3B4 & 0x40000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 8) {
                fn_80115658(m, i, -1);
            }
        }
    }
    if (u->w3B4 & 0x80000) {
        for (i = 0; i < 199; i++) {
            if ((*(u8**)(fn_8010B240(i) + 8))[7] & 1) {
                fn_80115658(m, i, -1);
            }
        }
    }
    switch (range) {
    case -1:
        range = fn_8012408C(u);
    }
    fn_80115764(m, u->x, (s8)*(u8*)&u->y, range);
}

void fn_801662AC(int x, int y, u8* s, int k, u16 v);

void fn_801663E0(int x, int y, int a, int r, int k) {
    Map* m = &lbl_803EC898;
    int x0, y0, x1, y1;
    int yy;
    fn_80114B44(m, 9, 0);
    fn_80114888(m, k);
    fn_80115DEC(m, (s8)x, (s8)y, (u8)a, (u8)r);
    x0 = x - r;
    if (x0 < m->x0) {
        x0 = m->x0;
    }
    y0 = y - r;
    if (y0 < lbl_803EC898.y0) {
        y0 = lbl_803EC898.y0;
    }
    x1 = x + r;
    if (x1 > lbl_803EC898.x1 - 1) {
        x1 = lbl_803EC898.x1 - 1;
    }
    y1 = y + r;
    if (y1 > lbl_803EC898.y1 - 1) {
        y1 = lbl_803EC898.y1 - 1;
    }
    for (yy = y0; yy <= y1; yy++) {
        int xx;
        for (xx = x0; xx <= x1; xx++) {
            if (r >= ABS(x - xx) + ABS(y - yy)) {
                if (m->curS[(s8)xx + (s8)yy * 0x40] >= 0 && m->g4[(s8)xx + (s8)yy * 0x40] == 0) {
                    m->curS[(s8)xx + (s8)yy * 0x40] = -1;
                }
            }
        }
    }
}

void fn_80166580(int x, int y, int a, int r, int k) {
    Map* m = &lbl_803EC898;
    int x0, y0, x1, y1;
    int yy;
    fn_80114B44(m, 9, 0);
    fn_80114888(m, k);
    fn_80116098(m, (s8)x, (s8)y, (u8)a, (u8)r);
    x0 = x - r;
    if (x0 < m->x0) {
        x0 = m->x0;
    }
    y0 = y - r;
    if (y0 < lbl_803EC898.y0) {
        y0 = lbl_803EC898.y0;
    }
    x1 = x + r;
    if (x1 > lbl_803EC898.x1 - 1) {
        x1 = lbl_803EC898.x1 - 1;
    }
    y1 = y + r;
    if (y1 > lbl_803EC898.y1 - 1) {
        y1 = lbl_803EC898.y1 - 1;
    }
    for (yy = y0; yy <= y1; yy++) {
        int xx;
        for (xx = x0; xx <= x1; xx++) {
            if (r >= ABS(x - xx) + ABS(y - yy)) {
                if (m->curS[(s8)xx + (s8)yy * 0x40] >= 0 && m->g4[(s8)xx + (s8)yy * 0x40] == 0) {
                    m->curS[(s8)xx + (s8)yy * 0x40] = -1;
                }
            }
        }
    }
}

u32 fn_80167E94(Unit* u) {
    Inv* p = u->inv;
    u8* it;
    u32 r = 0x3C;
    int i;
    for (i = 0; i < 7; i++, p++) {
        if (!p || !(it = p->item)) break;
        if (fn_8012B868(u, it)) {
            u32 w = *(u32*)(it + 0x3C);
            if (w & 0x10) {
                if (r > 0x14) r = 0x14;
            } else if (w & 3) {
                if (fn_801107C0(it, u) > 1) {
                    if (r > 0x28) r = 0x28;
                } else {
                    if (r > 0x32) r = 0x32;
                }
            }
        }
    }
    return r;
}

int fn_80167F5C(Unit* u);

void fn_80169510(void) {
    SkillAct* p = lbl_80387690;
    while (p->name) {
        p->item = fn_8010B228(p->name);
        p++;
    }
}

void fn_80168BC0(void* parent) {
    fn_80081194(lbl_80387468, parent);
    fn_80053A7C();
}

void fn_80168A90_unused(void);
void fn_801689C8(f32* p);

void fn_80168A90(f32* p);

int fn_8016A8D0(Unit* u) {
    int n = 0;
    int y;
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        int x;
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]) {
                Unit* v = UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]);
                if (!SameT(u, v, 1) && (v->w3B4 & 1)) {
                    n++;
                }
            }
        }
    }
    return n;
}

BOOL fn_80169B20(Unit* u, u16 lim, s16 x, s16 y, Filter* f, s16* ox, s16* oy);

void fn_80169C70(Unit* u, Filter* f) {
    int ux = u->x;
    int uy = u->y;
    int r = fn_8012408C(u);
    int x0, y0, x1, y1, yy;
    x0 = ux - r;
    if (x0 < lbl_803EC898.x0) {
        x0 = lbl_803EC898.x0;
    }
    y0 = uy - r;
    if (y0 < lbl_803EC898.y0) {
        y0 = lbl_803EC898.y0;
    }
    x1 = ux + r;
    if (x1 > lbl_803EC898.x1 - 1) {
        x1 = lbl_803EC898.x1 - 1;
    }
    y1 = uy + r;
    if (y1 > lbl_803EC898.y1 - 1) {
        y1 = lbl_803EC898.y1 - 1;
    }
    for (yy = y0; yy <= y1; yy++) {
        int xx;
        for (xx = x0; xx <= x1; xx++) {
            if (r >= ABS(ux - xx) + ABS(uy - yy)) {
                if (lbl_803EC898.curS[(s8)xx + (s8)yy * 0x40] >= 0 && lbl_803EC898.b5S[(s8)xx + (s8)yy * 0x40] == 0 &&
                    !fn_801658E4(u, (s8)xx, (s8)yy) && !f->at(0, (s16)xx, (s16)yy)) {
                    lbl_803EC898.curS[(s8)xx + (s8)yy * 0x40] = -1;
                }
            }
        }
    }
}

void fn_80168B54(u8* p) {
    if ((lbl_804CB5B8->v34() & 0x4400) != 0 || *(int*)(p + 100) > 0x2d) {
        fn_80083B78(p);
    } else {
        fn_80133034();
        *(int*)(p + 100) += 1;
    }
}
void fn_80169254(u8* p) {
    AiAct* a = &lbl_803CA870;
    *(u32*)(p + 0x30) = 0;
    switch (a->action) {
    case 0:
    case 1:
    case 0x24:
        break;
    default:
        fn_8004564C(a, p);
    }
}
u8 fn_80169718(Unit* u, int a, int b) {
    if (((Bf110*)u)->s == 0) {
        Inv* p = u->inv;
        u8* it;
        s16 m = 0;
        int i;
        for (i = 0; i < 7; i++, p++) {
            if (!p || !p->item) break;
            if (fn_8012BB48(u, p->item)) {
                it = p->item;
                if ((u8)(it ? it[0x14] : 0x13) == 0x81 && (it ? *(s16*)(it + 0x18) : 0) >= m) {
                    SkillAct* e = FindAct(u, it);
                    if (e && e->func(u, i, a, b)) {
                        m = p->item ? *(s16*)(p->item + 0x18) : 0;
                    }
                }
            }
        }
    }
    return lbl_804183F0.done;
}
u8 fn_80169870(Unit* u, int a, int b) {
    if (((Bf110*)u)->s == 0) {
        Inv* p = u->inv;
        u8* it;
        s16 m = 0;
        int i;
        for (i = 0; i < 7; i++, p++) {
            if (!p || !p->item) break;
            if (fn_8012BB48(u, p->item)) {
                it = p->item;
                if ((u8)(it ? it[0x14] : 0x13) == 0x84 && (it ? *(s16*)(it + 0x18) : 0) >= m) {
                    SkillAct* e = FindAct(u, it);
                    if (e && e->func(u, i, a, b)) {
                        m = p->item ? *(s16*)(p->item + 0x18) : 0;
                    }
                }
            }
        }
    }
    return lbl_804183F0.done;
}
u8 fn_801699C8(Unit* u, int a, int b) {
    if (((Bf110*)u)->s == 0) {
        Inv* p = u->inv;
        u8* it;
        s16 m = 0;
        int i;
        for (i = 0; i < 7; i++, p++) {
            if (!p || !p->item) break;
            if (fn_8012BB48(u, p->item)) {
                it = p->item;
                if ((u8)(it ? it[0x14] : 0x13) != 0x81 && (it ? *(s16*)(it + 0x18) : 0) >= m) {
                    SkillAct* e = FindAct(u, it);
                    if (e && e->func(u, i, a, b)) {
                        m = p->item ? *(s16*)(p->item + 0x18) : 0;
                    }
                }
            }
        }
    }
    return lbl_804183F0.done;
}
#pragma use_lmw_stmw off
int fn_8016C9C8(Unit* u, u8* s, int a) {
    Tb* e;
    int k = s[0x1C];
    e = FindTb(u, s, k);
    if (!e) {
        return 0;
    }
    e->f(u, a);
    return lbl_804183F0.done;
}
#pragma use_lmw_stmw on
#pragma auto_inline off
void fn_8016CA94(Unit* a, Unit* u) {
    Filt f;
    f.vt = lbl_80387338;
    f.u = a;
    fn_80152C20(u, &f, 0x15);
}
void fn_801688D0(u32* a, u32* b, u32* c, Cmp* f) {
    BOOL x = !f->f(*c, *a);
    BOOL y = !f->f(*b, *c);
    if (x && y) {
        return;
    }
    if (!x && !y) {
        u32 t = *a;
        *a = *b;
        *b = t;
        return;
    }
    if (f->f(*b, *a)) {
        u32 t = *a;
        *a = *b;
        *b = t;
    }
    if (x) {
        u32 t = *b;
        *b = *c;
        *c = t;
    } else {
        u32 t = *a;
        *a = *c;
        *c = t;
    }
}
int fn_80168098(void);
void fn_80167E08(void);
}
