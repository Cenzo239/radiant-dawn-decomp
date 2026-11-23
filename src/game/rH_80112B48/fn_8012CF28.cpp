/* Unit table loops: apply something to every unit of a side, 8012CC80..8012E3A4. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern void fn_8010E41C(void*, int);
extern void fn_8010E27C(void*, Unit*);
extern void fn_8010E168(void*, Unit*);
extern void fn_8010DF10(void*, int);
extern void fn_8010DF24(void*);
extern void fn_8011FDD8(Unit*, int);
extern void fn_80126EB0(Unit*, int, int);
extern void* fn_80076F54(void*);
extern Unit* fn_80127B68(Unit*);
extern void fn_80121700(Unit*, void*);
extern int fn_80121A28(Unit*, void*);
extern void fn_801221E8(Unit*, int);
extern u8* fn_8024BCA0(void);
extern void fn_800F68DC(Unit*, int);
extern void fn_800F6AEC(Unit*, int);
extern void fn_800F7410(Unit*, int);
extern void fn_800F39DC(Unit*);
extern void fn_800F7A98(Unit*);
extern void fn_800F7D04(Unit*);
extern void fn_800F7BF4(Unit*);
extern void fn_800F91B8(Unit*);
extern void fn_800F93E4(Unit*);
extern void fn_800F9890(void);
extern void fn_800F98CC(void);
extern void fn_800FAD48(void);
extern void fn_800FB824(void);
#if TARGET_PC
extern FE10_PROTO void fn_800F8030(p32arg);
#else
extern void fn_800F8030(int);
#endif
extern int fn_800F69E4(Unit*);
extern int fn_800F760C(Unit*);
extern void* fn_801246A4(Unit*);
extern void fn_800C7B18(void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_80102928(Unit*, int, int, int, p32arg);
#else
extern void fn_80102928(Unit*, int, int, int, int);
#endif
extern void fn_80083B78(void*);
extern void* fn_80081194(void*, void*);
extern u64 fn_8017DA30(u64);
extern u32 lbl_804CB5F4;
extern u32 lbl_804CA710;
extern void* memset(void*, int, u32);
extern void* lbl_804CA4D8;
extern char lbl_80369258[];
extern u8 lbl_80385E20[];
extern u8 lbl_80385E44[];

struct Team {
    Unit* head;
    Unit* tail;
    int n;
};

extern Team* lbl_804CB814;

static inline void SideSet(u8* tbl, const u8* a) {
    for (; *a != 0xff; a++) {
        tbl[*a] = 1;
    }
}

Unit* fn_8012CF28(int x, int y) {
    u8 tbl[0xb];
    int i;
    fn_8010E41C(tbl, 3);
    for (i = 1; i <= 0xfe; i++) {
        Unit* v = UnitGet(i);
        if (v->person && tbl[v->team[8]] && !(v->flags & 0x80000001C) && x == v->x && y == v->y) {
            return v;
        }
    }
    return 0;
}

int fn_8012D07C(u32 t) {
    u8 tbl[0xb];
    int n = 0;
    int i;
    fn_8010E41C(tbl, (u8)t);
    for (i = 1; i <= 0xfe; i++) {
        Unit* v = UnitGet(i);
        if (v->person && tbl[v->team[8]]) {
            n++;
        }
    }
    return n;
}

Unit* fn_8012D280(int i) {
    return lbl_804CB814[i].head;
}

Unit* fn_8012D290(int i) {
    Unit* u = lbl_804CB814[i].head;
    if (u) {
        return fn_80127B68(u);
    }
    return 0;
}

static inline Unit* FindUnit(Person* p) {
    if (p == 0) {
        return 0;
    }
    {
        Team* t = lbl_804CB814;
        int i;
        for (i = 0; i < 0xb; i++) {
            Unit* u;
            for (u = t->head; u; u = u->next) {
                if (u->person && u->person == p) {
                    return u;
                }
            }
            t++;
        }
    }
    return 0;
}

Unit* fn_8012D2B0(int k) {
    Unit* h = FindUnit((Person*)fn_80076F54(lbl_80369258));
    Unit* u;
    Unit* r = 0;
    for (u = lbl_804CB814[k].head; u; u = u->next) {
        if (fn_8011B77C(u->skills, lbl_804CA4D8)) {
            r = u;
            if (u == h) {
                break;
            }
        }
    }
    return r;
}

void fn_8012D38C(void* w) {
    int off = 0;
    int i;
    for (i = 0; i < 0xfe; i++) {
        fn_80121700((Unit*)((u8*)lbl_804CB810 + off), w);
        off += 0x3f0;
    }
}

#define FOR_SIDE(n, body)                                  \
    {                                                      \
        u8 tbl[0xb];                                      \
        int i;                                             \
        fn_8010E41C(tbl, n);                               \
        for (i = 1; i <= 0xfe; i++) {                      \
            Unit* v = UnitGet(i);                          \
            if (v->person && tbl[v->team[8]]) {            \
                body;                                      \
            }                                              \
        }                                                  \
    }

void fn_8012D58C(void) {
    FOR_SIDE(3, fn_800F68DC(v, 0));
}

void fn_8012D620(void) {
    FOR_SIDE(3, fn_800F6AEC(v, 0));
}

void fn_8012D78C(void) {
    FOR_SIDE(5, fn_800F7410(v, 0));
}

void fn_8012D820(void) {
    u8 a[] = {7, 8, 9, 10, 0xff};
    u8 tbl[0xb];
    int i;
    memset(tbl, (u8)lbl_804CA710, 0xb);
    SideSet(tbl, a);
    for (i = 1; i <= 0xfe; i++) {
        Unit* v = UnitGet(i);
        if (v->person && tbl[v->team[8]]) {
            fn_800F7410(v, 0);
        }
    }
}

void fn_8012D908(void) {
    FOR_SIDE(3, fn_800F39DC(v));
}

void fn_8012D998(void) {
    if (fn_8017DA30(0x200)) {
        return;
    }
    FOR_SIDE(3, fn_800F7A98(v));
}

void fn_8012D6B4(void) {
    Unit* u = lbl_804CB814[5].head;
    while (u) {
        Unit* n = u->next;
        fn_800F6AEC(u, 0);
        u = n;
    }
}

void fn_8012D6FC(void) {
    Unit* u = lbl_804CB814[5].head;
    while (u) {
        Unit* n = u->next;
        fn_800F7410(u, 0);
        u = n;
    }
}

void fn_8012D744(void) {
    Unit* u = lbl_804CB814[6].head;
    while (u) {
        Unit* n = u->next;
        fn_800F7410(u, 0);
        u = n;
    }
}

void fn_8012DA3C(void) {
    if (fn_8017DA30(0x200)) {
        return;
    }
    if (lbl_804CB5F4 & 2) {
        FOR_SIDE(3, fn_800F7D04(v));
        return;
    }
    {
        u8 tbl[0xb];
        int i;
        fn_8010E41C(tbl, 3);
        for (i = 1; i <= 0xfe; i++) {
            Unit* v = UnitGet(i);
            if (v->person && tbl[v->team[8]]) {
                fn_800F7D04(v);
                fn_800F7BF4(v);
            }
        }
    }
}

void fn_8012DB68(void) {
    if (fn_8017DA30(0x200)) {
        return;
    }
    if (lbl_804CB5F4 & 2) {
        return;
    }
    fn_800F9890();
    fn_800F98CC();
    fn_800FAD48();
    FOR_SIDE(3, fn_800F91B8(v));
    if (fn_8017DA30(0x800000)) {
        FOR_SIDE(3, fn_800F93E4(v));
    }
    fn_800FB824();
    fn_800F8030(2);
}

extern void fn_800F3B50(Unit*, f32, f32);

void fn_8012DCA8(void) {
    u8 tbl[0xb];
    int i;
    fn_8010E41C(tbl, 3);
    for (i = 1; i <= 0xfe; i++) {
        Unit* v = UnitGet(i);
        if (v->person && tbl[v->team[8]]) {
            f32 y = *(f32*)((u8*)v + 8);
            f32 x = *(f32*)((u8*)v + 4);
            fn_800F3B50(v, 0.5f + (f32)(int)x, 0.5f + (f32)(int)y);
        }
    }
}

void fn_8012DDBC(void) {
    FOR_SIDE(4, fn_800C7B18(fn_801246A4(v), 0x400));
}

void fn_8012DE54(void) {
    u8 tbl[0xb];
    int i;
    fn_8010E41C(tbl, 3);
    for (i = 1; i <= 0xfe; i++) {
        Unit* v = UnitGet(i);
        if (v->person && tbl[v->team[8]]) {
            int s = fn_800F760C(v); if (s != v->sC7) {
                fn_80102928(v, -1, 8, 0, 0);
            }
        }
    }
}

struct Proc {
    u8 pad0[0x60];
    int t;
};

void fn_8012DF18(Proc* p) {
    p->t = 0;
    FOR_SIDE(3, fn_800F68DC(v, 0));
}

static inline BOOL AllDone(void) {
    u8 tbl[0xb];
    int i;
    fn_8010E41C(tbl, 3);
    for (i = 1; i <= 0xfe; i++) {
        Unit* v = UnitGet(i);
        if (v->person && tbl[v->team[8]]) {
            if (!fn_800F69E4(v)) {
                return 0;
            }
        }
    }
    return 1;
}

void fn_8012DFB4(Proc* p) {
    p->t++;
    if (AllDone() || p->t > 0x4650) {
        fn_80083B78(p);
    }
}

void fn_8012E08C(void) {
    FOR_SIDE(3, fn_800F6AEC(v, 0));
}

void fn_8012E120(void* p) {
    fn_80081194(lbl_80385E20, p);
}

void fn_8012E130(Proc* p) {
    Unit* u;
    p->t = 0;
    u = lbl_804CB814[5].head;
    while (u) {
        Unit* n = u->next;
        fn_800F68DC(u, 0);
        u = n;
    }
}

static inline BOOL ListDone(void) {
    Unit* u = lbl_804CB814[5].head;
    while (u) {
        Unit* n = u->next;
        if (!fn_800F69E4(u)) {
            return 0;
        }
        u = n;
    }
    return 1;
}

void fn_8012E180(Proc* p) {
    p->t++;
    if (ListDone() || p->t > 0x4650) {
        fn_80083B78(p);
    }
}

void fn_8012E20C(void) {
    Unit* u = lbl_804CB814[5].head;
    while (u) {
        Unit* n = u->next;
        fn_800F6AEC(u, 0);
        u = n;
    }
}

void fn_8012E254(void* p) {
    fn_80081194(lbl_80385E44, p);
}

struct UnitExt {
    u8 pad0[0x2FC];
    void* p2FC;
};

void fn_8012E388(UnitExt* u, void* p) {
    u->p2FC = p;
}

void* fn_8012E390(UnitExt* u) {
    return u->p2FC;
}

void fn_8012E398(UnitExt* u, Unit* v) {
    u->p2FC = v->person;
}

extern Unit* fn_8012CECC(void*);

Unit* fn_8012E3A4(UnitExt* u) {
    return fn_8012CECC(u->p2FC);
}

}
