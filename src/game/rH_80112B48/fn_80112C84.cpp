/* Team/ally pair lists, 80112C84..8011337C. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off

extern "C" {

extern u8* fn_8010B1D8(void*);
extern void* fn_8010B1B4(int);
extern void fn_8008A5E4(void*, int);
extern void fn_8008A5C0(void*, int);
extern void fn_8008A5AC(void*, int);
extern int fn_8008A1DC(void*);
extern int fn_8008A1B4(void*);
extern int fn_8008A1A0(void*);
extern void* fn_80244470(void*, int);
extern void* lbl_804CBFC8;
extern void fn_80114D00(Map*);
extern void fn_80114B44(Map*, int, int);
extern u8* fn_8013B9A8(void);
extern int fn_8013554C(u8*);
extern void fn_801379F8(u8*, int);
extern Map lbl_803EC898;

#if TARGET_PC
/* host: KiznaData records used in place in the file: big-endian pointer fields */
struct PairEnt {
    FE10_BP32(void) a;
    FE10_BP32(void) b;
    u8 c;
    u8 d;
};
#else
struct PairEnt {
    void* a;
    void* b;
    u8 c;
    u8 d;
};
#endif

extern PairEnt* lbl_804CB7E4;
extern PairEnt lbl_803EC418[];
extern int lbl_804CB800;

struct UnitH {
    u8 pad0[0xEC];
    void* ec;
};

void fn_80112C84(void) {
    PairEnt* e;
    for (e = lbl_804CB7E4; e->a; e++) {
        e->a = fn_8010B1D8(e->a);
        e->b = fn_8010B1D8(e->b);
    }
}

void fn_801131D8(void* w) {
    PairEnt* e;
    int i;
    fn_8008A5E4(w, lbl_804CB800);
    e = lbl_803EC418;
    for (i = 0; i < lbl_804CB800; i++) {
        fn_8008A5C0(w, *(u16*)((u8*)e->a + 0x1c));
        fn_8008A5C0(w, *(u16*)((u8*)e->b + 0x1c));
        fn_8008A5AC(w, e->c);
        fn_8008A5AC(w, e->d);
        e++;
    }
}

static inline void* PairMap(void* map, int id) {
    return fn_8010B1D8(fn_80244470(map, (u16)id));
}

void fn_80113274(void* r) {
    PairEnt* e;
    void* map = lbl_804CBFC8;
    int i;
    lbl_804CB800 = fn_8008A1DC(r);
    e = lbl_803EC418;
    for (i = 0; i < lbl_804CB800; i++) {
        if (map) {
            e->a = PairMap(map, fn_8008A1B4(r));
            e->b = PairMap(map, fn_8008A1B4(r));
        } else {
            e->a = fn_8010B1B4((u16)fn_8008A1B4(r));
            e->b = fn_8010B1B4((u16)fn_8008A1B4(r));
        }
        e->c = fn_8008A1A0(r);
        e->d = fn_8008A1A0(r);
        e++;
    }
}

void fn_80113370(void) {
    fn_80114D00(&lbl_803EC898);
}

void fn_8011337C(Map* m) {
    u8* g = fn_8013B9A8();
    m->w = g[0x4c];
    m->h = g[0x4d];
    m->x0 = fn_8013554C(g);
    m->x1 = m->w - fn_8013554C(g);
    m->y0 = fn_8013554C(g);
    m->y1 = m->h - fn_8013554C(g);
    m->cur = m->cost;
    fn_80114B44(m, 0, 0);
    fn_801379F8(g, 1);
}

}
