/* Map events: quake, pitfall, doors, breakable walls, treasure, process callbacks. */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

extern u8 lbl_803CB770[];
extern u8 lbl_803CAB38[];
extern u8 lbl_803697B4[];
extern u8 lbl_803EC898[];
extern u8 lbl_80386174[];
extern u8 lbl_803861B8[];
extern u8 lbl_803861FC[];
extern u8 lbl_80386268[];
extern u8 lbl_803862B8[];
extern u8 lbl_803862EC[];
extern u8 lbl_80386320[];
extern u8 lbl_8038634C[];
extern u8 lbl_80386378[];

extern MapModel* fn_8013B9A8(void);
extern u32 fn_8013B9CC(void);
extern void* fn_8012FCD0(void);
extern u32 fn_80089ED0(void);
extern void* fn_80083B84(void*);
#if TARGET_PC
extern FE10_PROTO void* fn_80081050(void*, p32arg);
#else
extern void* fn_80081050(void*, int);
#endif
extern void* fn_800811E4(void*, void*);
extern void fn_800846BC(void*);
extern void fn_80083B78(void*);
extern int fn_8013599C(MapModel*, int, int, u32, u32, Mesh**);
extern Mesh* fn_80135800(MapModel*, int, int, u32, u32);
extern Mesh* fn_80135A54(MapModel*, int, int, u32, u32);
extern int fn_80135F88(MapModel*, Mesh*, Mesh**);
extern void fn_801379F8(MapModel*, int);
extern void fn_801CAA24(Mesh*, void*, int);
#if TARGET_PC
extern FE10_PROTO struct Trap * fn_80066130(void*, int, int, int);
#else
extern int fn_80066130(void*, int, int, int);
#endif
extern void fn_800661A0(void*, int, int, int, int);
extern void fn_8006625C(void*, int, int, int);
extern void fn_800620A8(void*, f32, f32);
extern void fn_800E24F8(void*);
extern void fn_801CA3DC(Mesh*, int);
extern void fn_801CA3E4(Mesh*, int);
extern void fn_801CA300(Mesh*);
extern void fn_801CA33C(Mesh*, int, int);
extern int fn_801CA260(Mesh*);
extern int fn_801CA248(Mesh*);
extern void fn_8012D908(void);
extern void fn_801CA444(Mesh*, int);
extern void fn_801CA49C(Mesh*, int);
extern f32 fn_8001EF30(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8013CCA4(void*, Mesh*, p32arg, p32arg);
#else
extern void fn_8013CCA4(void*, Mesh*, int, int);
#endif

struct QuakeProc {
    u8 pad0[0x30];
    int count;   /* 0x30 */
    u32 angle;   /* 0x34 */
    int period;  /* 0x38 */
    int t;       /* 0x3C */
    f32 amp;     /* 0x40 */
    void* cam;   /* 0x44 */
};

void fn_8013C094(QuakeProc* p) {
    p->t = 0;
    p->cam = fn_8012FCD0();
    p->angle = fn_80089ED0() % 360;
}

void fn_8013C14C(
#if TARGET_PC
f32 amp, int period, int count, void* parent
#else
f32 amp, int period, int count, int parent
#endif
) {
    if (amp != 0.0f && period != 0 && count != 0 && fn_8012FCD0() != 0 &&
        (count <= 0 || fn_80083B84(lbl_80386174) == 0)) {
        QuakeProc* p = (QuakeProc*)fn_80081050(lbl_80386174, parent);
        p->period = period;
        p->amp = amp;
        p->count = count;
    }
}

BOOL fn_8013C234(int x, int y, void* a) {
    Mesh* list[16];
    int n = fn_8013599C(fn_8013B9A8(), x, y, 0x4200, 0x10, list);
    MapGroup* g;
    Mesh** lp = list;
    int i;
    for (i = 0; i < n; i++) {
        Mesh* m = *lp;
        g = m->group;
        if (!(m->flags & 4)) {
            fn_801CAA24(m, a, 5);
            if (g->flags & 0x1000000) {
                if (fn_80066130(lbl_803CB770, (s8)x, (s8)y, 0x12) == 0) {
                    fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x12, 0);
                }
            }
        }
        lp++;
    }
    return n != 0;
}

struct DoorProc {
    u8 pad0[0x18];
    void* x18;
    u8 pad1C[0x30 - 0x1C];
    int x;        /* 0x30 */
    int y;        /* 0x34 */
    Mesh* m38;    /* 0x38 */
    Mesh* m3c;    /* 0x3C */
    Mesh* m40;    /* 0x40 */
    Mesh* m44;    /* 0x44 */
    int t;        /* 0x48 */
    int dur;      /* 0x4C */
};

void fn_8013C310(DoorProc* p) {
    fn_800620A8(lbl_803CAB38, p->x, p->y);
    fn_800E24F8(lbl_803697B4);
}

void fn_8013C784(DoorProc* p) {
    fn_801CA3E4(p->m38, 0);
    if (p->m44) fn_801CA3E4(p->m44, 0);
    if (p->m3c) {
        fn_801CA3DC(p->m3c, 0xFF);
        fn_801CA300(p->m3c);
        fn_801CA3E4(p->m3c, 1);
    }
    if (fn_8013B9CC()) fn_801379F8(fn_8013B9A8(), 1);
}

DoorProc* fn_8013C80C(int x, int y, int dur, void* parent) {
    MapModel* mm = fn_8013B9A8();
    int tx;
    int ty;
    Mesh* door;
    if (mm == 0) return 0;
    door = fn_80135A54(mm, x, y, 0x800, 0);
    if (door == 0) return 0;
    {
        tx = door->tx;
        ty = door->ty;
        Mesh* a = fn_80135800(mm, tx, ty, 0x20000, 0);
        Mesh* b = fn_80135A54(mm, tx, ty, 0x10000000, 0);
        Mesh* c = fn_80135A54(mm, tx, ty, 0x40000000, 0);
        fn_8006625C(lbl_803CB770, tx, ty, 6);
        fn_8006625C(lbl_803CB770, tx, ty, 0x13);
        fn_800661A0(lbl_803CB770, tx, ty, 0x25, 0);
        if (dur == 0) {
            fn_801CA3E4(door, 0);
            if (c) fn_801CA3E4(c, 0);
            if (a) {
                fn_801CA3DC(a, 0xFF);
                fn_801CA300(a);
                fn_801CA3E4(a, 1);
            }
            if (fn_8013B9CC()) fn_801379F8(fn_8013B9A8(), 1);
            return 0;
        } else {
            DoorProc* p;
            if (dur < 0) dur = 0x5A;
            p = (DoorProc*)fn_800811E4(lbl_803861B8, parent);
            p->m38 = door;
            p->m3c = a;
            p->m40 = b;
            p->m44 = c;
            p->dur = dur;
            p->x = tx;
            p->y = ty;
            return p;
        }
    }
}

struct MeshListProc {
    u8 pad0[0x30];
    Mesh* list[16];  /* 0x30 */
    int n;           /* 0x70 */
    int t;           /* 0x74 */
};

void fn_8013CAF4(MeshListProc* p) {
    if (fn_801CA260(p->list[0])) {
        Mesh* m = p->list[0];
        MeshListProc* q = (MeshListProc*)fn_800811E4(lbl_803862B8, p);
        q->n = fn_80135F88(fn_8013B9A8(), m, q->list);
    } else {
        Mesh* m = p->list[0];
        MeshListProc* q = (MeshListProc*)fn_800811E4(lbl_803862EC, p);
        q->n = fn_80135F88(fn_8013B9A8(), m, q->list);
    }
}

void fn_8013CB90(int x, int y, void* parent) {
    Mesh* m;
    fn_8006625C(lbl_803CB770, (s8)x, (s8)y, 9);
    fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x26, 0);
    m = fn_80135800(fn_8013B9A8(), x, y, 0x800, 0x10);
    if (m) {
        MeshListProc* p = (MeshListProc*)fn_800811E4(lbl_803861FC, parent);
        p->list[0] = m;
        fn_800620A8(lbl_803CAB38, x, y);
    }
}

void fn_8013DA20(
#if TARGET_PC
int x, int y, void* a, void* b, void* parent
#else
int x, int y, int a, int b, void* parent
#endif
) {
    Mesh* m;
    fn_8006625C(lbl_803CB770, (s8)(x - 1), (s8)y, 10);
    fn_8006625C(lbl_803CB770, (s8)(x + 1), (s8)y, 10);
    fn_8006625C(lbl_803CB770, (s8)x, (s8)(y - 1), 10);
    fn_8006625C(lbl_803CB770, (s8)x, (s8)(y + 1), 10);
    fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x27, 0);
    m = fn_80135800(fn_8013B9A8(), x, y, 0x10000, 0);
    if (m) fn_8013CCA4(fn_800811E4(lbl_80386268, parent), m, a, b);
}

void fn_8013DB18(MeshListProc* p) {
    int i;
    p->t = 0;
    for (i = 0; i < p->n; i++) p->list[i]->flags |= 8;
    fn_801379F8(fn_8013B9A8(), 1);
    fn_8012D908();
}

void fn_8013DB7C(MeshListProc* p) {
    int i;
    p->t++;
    for (i = 0; i < p->n; i++) {
        Mesh* m = p->list[i];
        int v = fn_8001EF30(255.0f, 0.0f, 60.0f, p->t);
        fn_801CA3DC(m, (u8)v);
        if (m->group->flags & 0x10000000) fn_801CA33C(m, (u8)v, 1);
    }
    if (p->t == 0x3C) fn_80083B78(p);
}

void fn_8013DC68(MeshListProc* p) {
    int i;
    if (fn_8013B9CC()) {
        for (i = 0; i < p->n; i++) {
            Mesh* m = p->list[i];
            if (i == p->n - 1) {
                fn_801CA444(m, 1);
            } else {
                fn_801CA444(m, 0);
            }
        }
    }
}

void fn_8013DCF0(Mesh* m, void* parent) {
    MeshListProc* q = (MeshListProc*)fn_800811E4(lbl_803862B8, parent);
    q->n = fn_80135F88(fn_8013B9A8(), m, q->list);
}

void fn_8013DD80(MeshListProc* p) {
    int i;
    p->t++;
    for (i = 0; i < p->n; i++) {
        Mesh* m = p->list[i];
        int v = fn_8001EF30(0.0f, 255.0f, 60.0f, p->t);
        fn_801CA3DC(m, (u8)v);
        if (m->group->flags & 0x10000000) fn_801CA33C(m, (u8)v, 1);
    }
    if (p->t == 0x3C) fn_80083B78(p);
}

void fn_8013DE6C(MeshListProc* p) {
    int i;
    if (fn_8013B9CC()) {
        for (i = 0; i < p->n; i++) {
            Mesh* m = p->list[i];
            if (i == p->n - 1) {
                fn_801CA49C(m, 1);
            } else {
                fn_801CA49C(m, 0);
            }
        }
    }
}

void fn_8013DEF4(Mesh* m, void* parent) {
    MeshListProc* q = (MeshListProc*)fn_800811E4(lbl_803862EC, parent);
    q->n = fn_80135F88(fn_8013B9A8(), m, q->list);
}

void fn_8013DF48(MeshListProc* p) {
    Mesh* m;
    Mesh* o;
    p->list[0]->flags |= 8;
    fn_801379F8(fn_8013B9A8(), 1);
    fn_8012D908();
    fn_801CAA24(p->list[0], p, 0);
    m = p->list[0];
    o = fn_80135A54(fn_8013B9A8(), m->tx, m->ty, 0x800, 0x10);
    if (o && fn_801CA260(o)) {
        MeshListProc* q = (MeshListProc*)fn_800811E4(lbl_803862B8, p);
        q->n = fn_80135F88(fn_8013B9A8(), o, q->list);
    }
}

void fn_8013E08C(MeshListProc* p) {
    Mesh* m;
    Mesh* o;
    p->list[0]->flags &= ~8;
    fn_801379F8(fn_8013B9A8(), 1);
    fn_8012D908();
    fn_801CAA24(p->list[0], p, 1);
    m = p->list[0];
    o = fn_80135A54(fn_8013B9A8(), m->tx, m->ty, 0x800, 0);
    if (o && fn_801CA248(o)) {
        MeshListProc* q = (MeshListProc*)fn_800811E4(lbl_803862EC, p);
        q->n = fn_80135F88(fn_8013B9A8(), o, q->list);
    }
}

extern u8 lbl_803861A0[];

void fn_8013E710(void) {
    fn_800846BC(lbl_803861A0 + 0x1D8);
    fn_800846BC(lbl_803861A0 + 0x1AC);
    fn_800846BC(lbl_803861A0 + 0x180);
    fn_800846BC(lbl_803861A0 + 0x14C);
    fn_800846BC(lbl_803861A0 + 0x118);
    fn_800846BC(lbl_803861A0 + 0xC8);
    fn_800846BC(lbl_803861A0 + 0x18);
    fn_800846BC(lbl_803861A0 + 0x5C);
}

extern u8 lbl_804CB84C;
extern s8 lbl_804CB84D;
extern s8 lbl_804CB84E;
extern s8 lbl_804CB84F;
extern s8 lbl_804CB850;
extern u8 lbl_804CB852;
struct MapDim { u32 w, h; };

#if TARGET_PC
extern FE10_PROTO void fn_801035CC(void*, ptr32<const void>, ptr32<const void>, int, int, p32arg);
#else
extern void fn_801035CC(void*, void*, void*, int, int, int);
#endif
extern int fn_8013CC7C(void*);
extern void fn_80083DC4(void*, int);
extern void fn_80078E24(void*);
extern void fn_801CB5EC(Mesh*, void*, int, int);
extern int fn_801CA1D8(Mesh*);
extern void* fn_800E3810(void*, void*);
extern void fn_800E48C8(void*, Vec*);
extern void fn_801CA5D4(Vec*, Mesh*);

struct LiftData { Mesh* m; u8 pad4[4]; void* x8; u8 padC[8]; f32 x14; f32 x18; };
struct LiftProc { u8 pad0[0x30]; LiftData* d; };

void fn_8013D944(LiftProc* p) {
    fn_801CA3E4(p->d->m, 0);
    if (fn_8013B9CC()) fn_801379F8(fn_8013B9A8(), 1);
    fn_80078E24(p->d);
    p->d = 0;
}

void fn_8013D9A4(LiftProc* p) {
    LiftData* d = p->d;
    if (d->x8 == 0) {
        fn_80083DC4(p, 1);
    } else {
        fn_801035CC(d->x8, (void*)fn_8013CC7C, p, (int)d->x14, (int)d->x18, 0);
    }
}

extern f32 fn_801142F0(void*, f32, f32);
extern void* fn_800E3A10(const char*, void*);
extern void* fn_800E3810(void*, void*);
extern void fn_800E48AC(void*, f32, f32, f32);
extern void fn_800E49AC(void*, f32);
extern void fn_80118380(void*, s8, s8, const char*);

struct TBoxProc { u8 pad0[0x30]; Mesh* m; };

void fn_8013E1E0(TBoxProc* p) {
    Mesh* m = p->m;
    int x = m->tx;
    int y = m->ty;
    void* e;
    fn_801CAA24(m, p, 0);
    e = fn_800E3A10((const char*)lbl_803697B4 + 0xA4, p);
    if (e) {
        fn_800E48AC(e, 0.5f + x, 0.5f + y, fn_801142F0(lbl_803EC898, 0.5f + x, 0.5f + y));
        fn_800E49AC(e, 0.015625f * *(s16*)((u8*)p->m + 0xA));
    }
}

void fn_8013C9DC(TBoxProc* p) {
    f32 x = 0.5f + p->m->tx;
    f32 y = 0.5f + p->m->ty;
    f32 z = fn_801142F0(lbl_803EC898, x, y);
    void* e = fn_800E3810(lbl_803697B4 + 0x10, 0);
    if (e) fn_800E48AC(e, x, y, z);
    fn_80118380(lbl_803EC898, (s8)x, (s8)y, (const char*)lbl_803697B4 + 0x1D);
}

} /* extern "C" */
