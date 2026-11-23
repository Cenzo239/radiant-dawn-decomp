#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef struct Probe { u8 pad[0x30]; void* a; } Probe;
typedef struct R4248 {
    u8 pad[0x30];
    MapUnit* u;
    s32 a;      /* 0x34 */
    s32 n;      /* 0x38 */
    f32 f;      /* 0x3C */
    u16 fl;     /* 0x40 */
    u8 pad42[0x29];
    u8 b6B;     /* 0x6B */
    u8 b6C;     /* 0x6C */
} R4248;

typedef struct SlotEnt {
    void* key;
    u8 b4;
    u8 f5 : 1;
    u8 r5 : 7;
    u8 pad6[0x22];
} SlotEnt;
typedef struct SlotTbl {
    s32 count;
    SlotEnt* ents;
} SlotTbl;

extern u8 lbl_80367D50[];
extern u8 lbl_80385090[];
extern u8 lbl_80385678[];
extern void fn_80104A70(void* a, void* b);
extern void* fn_800893E4(void*, void*, Probe*);
extern void* fn_80081050(void*, void*);
extern void* fn_800811E4(void*, void*);
#if TARGET_PC
extern FE10_PROTO int fn_800F0994(char*);
#else
extern void* fn_800F0994(char*);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80102928(MapUnit*, int, int, u16, void*);
#else
extern void fn_80102928(MapUnit*, void*, int, u16, void*);
#endif
extern void fn_80083B78(void*);
extern int* fn_800F0AA8(s32);
#if TARGET_PC
extern FE10_PROTO void fn_800F4E08(MapUnit*, char *);
#else
extern void fn_800F4E08(MapUnit*, int);
#endif
extern void fn_800FAF78(MapUnit*);
extern void fn_800FB258(MapUnit*, int);
extern void fn_800FB228(MapUnit*, int);
extern void fn_800FB288(MapUnit*, int);
extern void fn_800F3F14(MapUnit*, f32);
#if TARGET_PC
extern FE10_PROTO void fn_800F6604(MapUnit*, char *);
extern FE10_PROTO int fn_800F67E4(MapUnit*, char *);
#else
extern void fn_800F6604(MapUnit*, int);
extern int fn_800F67E4(MapUnit*, int);
#endif
extern void fn_80111C78(SlotEnt*, SlotEnt*);
extern void fn_80111B34(SlotEnt*);
extern void fn_80110BFC(SlotEnt*, void*);
extern void fn_80111C24(SlotEnt*, int);
extern void* fn_8010B228(void*);

static inline void PA4(MapUnit* u, char* name, int n, void* p) {
    int fl = 0xE003;
    fn_80102928(u, fn_800F0994(name), n, (u16)fl, p);
}
void fn_80104248(R4248* p) {
    MapUnit* u = p->u;
    if (*(u32*)((u8*)u + 0x28) & 2) {
        int n = 4;
        if (p->b6C) n = 2;
        if (p->b6B) {
            PA4(u, (char*)lbl_80367D50 + 0x138, n, p);
        } else {
            PA4(u, (char*)lbl_80367D50 + 5, n, p);
        }
        fn_80083B78(p);
    }
}

static inline void Restore(MapUnit* u, s32 a, u16 fl) {
    if (u) {
        u->flags &= 0x7FFF;
        if (a >= 0) {
            fn_800F4E08(u, *fn_800F0AA8(a));
            fn_800FAF78(u);
            if (fl & 1) {
                fn_800FB258(u, 1);
                fn_800FB228(u, 1);
            }
            if (fl & 4) {
                fn_800FB288(u, 1);
            }
        }
        fn_800F3F14(u, 1.0f);
    }
}
void fn_80104744(R4248* p) {
    Restore(p->u, p->a, p->fl);
}

static inline void Fx(MapUnit* u, void* parent) {
    Probe s;
    R4248* q;
    s.a = u;
    fn_800893E4(lbl_80385090, fn_80104A70, &s);
    if (parent == 0) parent = (void*)3;
    q = fn_80081050(lbl_80385090, parent);
    q->u = u;
}
int fn_801047F4(R4248* p) {
    int a = *fn_800F0AA8(p->a);
    fn_800F6604(p->u, a);
    if (fn_800F67E4(p->u, a)) {
        u16 fl = p->fl;
        u16 x = 0;
        if (fl & 1) x |= 8;
        if (fl & 2) x |= 4;
        if (fl & 4) x |= 0x10;
        fn_80102928(p->u, (void*)p->a, p->n, x, p);
        fn_800F3F14(p->u, p->f);
        Fx(p->u, p);
        p->a = -1;
        return 0;
    }
    return 1;
}

void* fn_80104948(MapUnit* u, s32 a, s32 n, int fl, void* parent, f32 f) {
    Probe s;
    R4248* q;
    s.a = u;
    fn_800893E4(lbl_80385678, fn_80104A70, &s);
    if (n == 0) {
        Restore(u, a, fl);
        return 0;
    }
    q = fn_800811E4(lbl_80385678, parent);
    q->u = u;
    q->a = a;
    q->f = f;
    q->n = n;
    q->fl = fl;
    u->flags |= 0x8000;
    return q;
}

static inline int FindFree(SlotTbl* t) {
    int i;
    for (i = 0; i < t->count; i++) {
        if (t->ents[i].key == 0) {
            return i;
        }
    }
    return -1;
}
int fn_801051D8(SlotTbl* t, SlotEnt* e) {
    int i;
    e->f5 = 0;
    i = FindFree(t);
    if (i < 0) return 0;
    fn_80111C78(&t->ents[i], e);
    return 1;
}
static inline int Add(SlotTbl* t, SlotEnt* e) {
    int i;
    e->f5 = 0;
    i = FindFree(t);
    if (i < 0) return 0;
    fn_80111C78(&t->ents[i], e);
    return 1;
}
int fn_80105260(SlotTbl* t, void* key) {
    SlotEnt o;
    int r;
    fn_80111B34(&o);
    fn_80110BFC(&o, key);
    r = Add(t, &o);
    fn_80111C24(&o, -1);
    return r;
}
static inline int FindKey(SlotTbl* t, void* key) {
    int i;
    for (i = 0; i < t->count; i++) {
        if (t->ents[i].key == key) {
            return i;
        }
    }
    return -1;
}
int fn_8010536C(SlotTbl* t, void* x) {
    return FindKey(t, fn_8010B228(x));
}
