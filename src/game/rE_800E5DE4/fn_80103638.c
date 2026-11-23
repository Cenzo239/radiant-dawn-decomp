#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef struct SlotEnt {
    void* key;
    u8 pad4[0x24];
} SlotEnt;

typedef struct SlotTbl {
    s32 count;
    SlotEnt* ents;
} SlotTbl;

extern void fn_80110D38(SlotEnt*);
extern void fn_80111D68(SlotEnt*, void*);
extern void fn_80111E48(SlotEnt*, void*);
extern SlotTbl lbl_804CB750;
extern void* fn_800811E4(void*, void*);
extern u8 lbl_803853E8[];
extern u8 lbl_80385518[];
extern void fn_80083DC4(void*, int);
extern void fn_80083B78(void*);
extern void fn_800F4B94(void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_80102928(void*, int, int, int, void *);
#else
extern void fn_80102928(void*, int, int, int, int);
#endif

typedef struct P3034 { u8 pad[0x30]; void* a; void* b; } P3034;

void fn_80105704(SlotTbl* t) {
    int i;
    for (i = 0; i < t->count; i++) {
        fn_80110D38(&t->ents[i]);
    }
}
void fn_80105768(SlotTbl* t, void* a) {
    int i;
    for (i = 0; i < t->count; i++) {
        fn_80111D68(&t->ents[i], a);
    }
}
void fn_801057DC(SlotTbl* t, void* a) {
    int i;
    for (i = 0; i < t->count; i++) {
        fn_80111E48(&t->ents[i], a);
    }
}
void fn_80105850(void) {
    int i, off;
    for (i = 0, off = 0; i < lbl_804CB750.count; off += 0x28, i++) {
        fn_80110D38((SlotEnt*)((u8*)lbl_804CB750.ents + off));
    }
}
void fn_801058B4(void* a) {
    int i, off;
    for (i = 0, off = 0; i < lbl_804CB750.count; off += 0x28, i++) {
        fn_80111D68((SlotEnt*)((u8*)lbl_804CB750.ents + off), a);
    }
}
void fn_80105928(void* a) {
    int i, off;
    for (i = 0, off = 0; i < lbl_804CB750.count; off += 0x28, i++) {
        fn_80111E48((SlotEnt*)((u8*)lbl_804CB750.ents + off), a);
    }
}
void fn_80103638(void* a, void* b, void* c) {
    P3034* p = fn_800811E4(lbl_803853E8, c);
    p->a = a;
    p->b = b;
}
void
#if TARGET_PC
*
#endif
fn_80103684(void* a, void* b, void* c) {
    P3034* p = fn_800811E4(lbl_803853E8, c);
    p->a = a;
    p->b = b;
#if TARGET_PC
    return p;
#endif
}
void fn_801039E8(void* a, void* c) {
    P3034* p = fn_800811E4(lbl_80385518, c);
    p->a = a;
}
void fn_80103D50(void* a, int n) {
    if (n < 0) n = 8;
    if (n == 0) {
        fn_800F4B94(a, -1);
    } else {
        fn_80102928(a, -1, n, 0x20, 0);
    }
}

typedef struct Probe { u8 pad[0x30]; void* a; } Probe;
extern void* fn_800893E4(void*, void*, Probe*);
#if TARGET_PC
extern FE10_PROTO void* fn_80081050(void*, void *);
#else
extern void* fn_80081050(void*, int);
#endif
extern void* fn_80081194(void*, void*);
extern u8 lbl_80385090[];
extern u8 lbl_803851C8[];
extern u8 lbl_80385290[];
extern u8 lbl_803853A0[];
extern u8 lbl_8038541C[];
extern u8 lbl_80385450[];
extern u8 lbl_80385198[];
extern u8 lbl_803854D0[];
extern u8 lbl_80385484[];
extern u8 lbl_803855CC[];
extern u8 lbl_803EC898[];
extern void fn_80104A70(void* a, void* b);
extern void fn_80104AA4(void* a, void* b);
extern void fn_800F39DC(void*, void*, int);
extern void fn_800FF998(void*, void*, int);
extern void fn_800FFFDC(void*, void*);
extern void fn_80100384(void*);
extern void* fn_80116A4C(void*);
extern f32 fn_80113F00(void*, f32, f32);
extern int fn_800F7724(void*);
extern int fn_80068D74(void);
extern void fn_800F3B50(MapUnit*, f32, f32);
extern void fn_800F3F14(MapUnit*, f32);

typedef struct PC { u8 pad[0x30]; void* a; GXColor c; } PC;

void* fn_80103304(
#if TARGET_PC
void* a, void* n
#else
void* a, int n
#endif
) {
    Probe s;
    s.a = a;
    fn_800893E4(lbl_80385090, fn_80104A70, &s);
#if TARGET_PC
    if (n == 0) n = (void*)3;
#else
    if (n == 0) n = 3;
#endif
    {
    P3034* p = fn_80081050(lbl_80385090, n);
    p->a = a;
    return p;
    }
}
void fn_80103374(
#if TARGET_PC
void* a, GXColor c, void* n
#else
void* a, GXColor c, int n
#endif
) {
    Probe s;
    PC* p;
    s.a = a;
    fn_800893E4(lbl_803851C8, fn_80104A70, &s);
#if TARGET_PC
    if (n == 0) n = (void*)3;
#else
    if (n == 0) n = 3;
#endif
    p = fn_80081050(lbl_803851C8, n);
    p->a = a;
    p->c = c;
}
#pragma use_lmw_stmw on
static inline void* GetOrMake(void* a, int fl, void* parent) {
    Probe s;
    void* p;
    s.a = a;
    p = fn_800893E4(lbl_80385290, fn_80104AA4, &s);
    if (p == 0) {
        p = fn_80081194(lbl_80385290, parent);
        fn_800FF998(p, a, fl);
    }
    return p;
}
void* fn_801034B4(void* a, void* parent) {
    void* b = fn_80116A4C(lbl_803EC898);
    Probe s;
    void* p;
    s.a = a;
    p = fn_800893E4(lbl_80385290, fn_80104AA4, &s);
    if (p == 0) {
        p = fn_80081194(lbl_80385290, parent);
        fn_800FF998(p, a, 0x240);
    }
    fn_800FFFDC(p, b);
    fn_80100384(p);
    return p;
}
#pragma use_lmw_stmw off
typedef struct P354C { u8 pad[0x30]; void* a; void* b; u8 pad38[8]; s32 c; s32 d; u8 pad48[4]; s32 e; s32 f; u8 g; u8 h; } P354C;
void* fn_8010354C(void* a, void* b, s32 c, s32 d, void* parent) {
    P354C* p = fn_800811E4(lbl_803853A0, parent);
    p->a = a;
    p->b = b;
    p->c = c;
    p->d = d;
    p->e = 0;
    p->f = 0;
    p->g = 0;
    p->h = 0;
    return p;
}
#pragma use_lmw_stmw on
void* fn_801035CC(void* a, s32 e, s32 f, s32 c, s32 d, void* parent) {
    P354C* p = fn_800811E4(lbl_803853A0, parent);
    p->a = a;
    p->b = 0;
    p->c = c;
    p->d = d;
    p->e = e;
    p->f = f;
    p->g = 0;
    p->h = 0;
    return p;
}
#pragma use_lmw_stmw off
typedef struct P36D0 { u8 pad[0x30]; void* a; void* b; u8 pad38[0xC]; f32 x; f32 y; } P36D0;
void* fn_801036D0(void* a, void* b, int x, int y, void* parent) {
    P36D0* p = fn_800811E4(lbl_8038541C, parent);
    p->a = a;
    p->b = b;
    p->x = 0.5f + (f32)x;
    p->y = 0.5f + (f32)y;
    return p;
}
typedef struct P3778 { u8 pad[0x30]; void* a; void* c; void* b; } P3778;
void* fn_80103778(void* a, void* b, void* c, void* parent) {
    P3778* p = fn_800811E4(lbl_80385450, parent);
    p->a = a;
    p->c = c;
    p->b = b;
    return p;
}
typedef struct P37D4 { u8 pad[0x30]; void* a; f32 x; f32 y; f32 v; f32 x2; f32 y2; f32 v2; } P37D4;
void* fn_801037D4(void* a, int x, int y, int x2, int y2, void* parent) {
    P37D4* p = fn_800811E4(lbl_80385198, parent);
    p->a = a;
    p->x = 0.5f + (f32)x;
    p->y = 0.5f + (f32)y;
    p->v = fn_80113F00(lbl_803EC898, p->x, p->y);
    p->x2 = 0.5f + (f32)x2;
    p->y2 = 0.5f + (f32)y2;
    p->v2 = fn_80113F00(lbl_803EC898, p->x2, p->y2);
    return p;
}
typedef struct P38D0 { u8 pad[0x30]; void* a; u8 b34; u8 b35; u8 b36; } P38D0;
void* fn_801038D0(void* a, void* parent) {
    P38D0* p = fn_800811E4(lbl_803854D0, parent);
    p->a = a;
    p->b35 = 0;
    p->b34 = 1;
    p->b36 = 1;
    if (fn_800F7724(a) == 0) p->b34 = 0;
    if (fn_80068D74() == 0) p->b34 = 0;
    return p;
}
void* fn_8010395C(void* a, void* parent) {
    P38D0* p = fn_800811E4(lbl_803854D0, parent);
    p->a = a;
    p->b35 = 0;
    p->b34 = 1;
    p->b36 = 0;
    if (fn_800F7724(a) == 0) p->b34 = 0;
    if (fn_80068D74() == 0) p->b34 = 0;
    return p;
}
typedef struct P3CE4 { u8 pad[0x30]; void* a; u16 b; void* c; void* d; } P3CE4;
void* fn_80103CE4(void* a, int b, void* c, void* d, void* parent) {
    P3CE4* p = fn_800811E4(lbl_80385484, parent);
    p->b = b;
    p->a = a;
    p->c = c;
    p->d = d;
    return p;
}
typedef struct P431C { u8 pad[0x30]; MapUnit* u; u8 pad34[0x10]; f32 v44; u8 pad48[0x23]; u8 b6B; } P431C;
static inline void ZeroOff(MapUnit* u) {
    u->offX = 0.0f;
    u->offY = 0.0f;
    u->offZ = 0.0f;
}
static inline void SetPos(MapUnit* u, f32 dx, f32 dy, f32 z) {
    u->x = u->x + dx;
    u->y = u->y + dy;
    u->z = z;
}
void fn_8010431C(P431C* p) {
    if (p->b6B == 0) {
        f32 ox, x, oy, y, z;
        MapUnit* u = p->u;
        z = p->v44;
        ox = u->offX;
        x = u->x;
        oy = u->offY;
        y = u->y;
        x = x + ox;
        y = y + oy;
        u->x = x;
        u->y = y;
        u->z = z;
        ZeroOff(p->u);
    }
}
typedef struct P45F4 { u8 pad[0x30]; MapUnit* u; u8 pad34[6]; s16 x; s16 y; } P45F4;
void fn_801045F4(P45F4* p) {
    fn_800F3B50(p->u, 0.5f + (f32)p->x, 0.5f + (f32)p->y);
    ZeroOff(p->u);
    fn_80102928(p->u, -1, 8, 0, 0);
    fn_800F3F14(p->u, 1.0f);
    p->u->flags |= 0x3C0;
}
typedef struct CharFlags { u8 pad0[0x14]; u8 b14; } CharFlags;
typedef struct CharDesc { u8 pad0[0x10]; CharFlags* sub; } CharDesc;
extern CharDesc* fn_800F43F0(MapUnit*);
typedef struct P46B0 { u8 pad[0x30]; MapUnit* u; u16 b; u8 pad36[0x32]; s16 h; u8 pad6A[2]; u8 c; } P46B0;
void* fn_801046B0(MapUnit* u, int b, int c, void* parent) {
    P46B0* p = fn_800811E4(lbl_803855CC, parent);
    CharDesc* d = fn_800F43F0(u);
    p->u = u;
    p->b = b;
    p->c = c;
    p->h = d->sub->b14 * 10;
    if (c != 0) p->h = 0x42;
    return p;
}
