#include "game/rE_800E5DE4/mapunit.h"


typedef struct PoolNode {
    struct PoolNode* a; /* 0x00 next */
    struct PoolNode* b; /* 0x04 prev */
    u8 timer;           /* 0x08 */
    u8 pad9;
    s16 id;             /* 0x0A */
    s16 x;              /* 0x0C */
    s16 y;              /* 0x0E */
} PoolNode;

/* Fixed-size node pool: node array, free list, cursor. */
typedef struct ObjPair {
    PoolNode* a;      /* 0x00 nodes */
    PoolNode** b;     /* 0x04 free list */
    PoolNode** cur;   /* 0x08 */
    PoolNode* head;   /* 0x0C */
    PoolNode* tail;   /* 0x10 */
    s32 used;         /* 0x14 */
    s32 count;        /* 0x18 */
} ObjPair;

extern void fn_800F280C(GXColor c, f32 x, f32 y, int z);
extern void fn_8012D78C(void);
extern void fn_80079978(void*);
extern void fn_80078E24(void*);
extern void fn_8001D424(void*);
extern void* lbl_804CB730;
extern void* lbl_804CB734;
extern void* lbl_804CB738;
extern ObjPair* lbl_804CB748;
extern u8 lbl_804CB743;
extern GXColor lbl_804CB744;
extern void fn_801764F8(int, int, int, int, void*);
extern void fn_8017659C(f32, int, int, int, int, u8, void*, void*);
extern u8 lbl_804CB740;
extern f32 lbl_803E8FD8[3];
extern f32 lbl_803E8FE4[3];
extern u8 lbl_803CAB38[];
extern void fn_8001E9E4(void*, Vec*);
extern void fn_80313460(Vec*, Vec*, Vec*);
extern void fn_800081D4(void*);
extern void fn_80007C58(void*);
extern u64 fn_8017DA30(u64);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E174(void*, u16);
extern void fn_8007E7DC(u8);
extern void fn_800800D4(int);
#if TARGET_PC
extern FE10_PROTO void fn_80080910(int, int);
#else
extern void fn_80080910(void*, int);
#endif
extern void fn_80080308(void);
extern void fn_8007E7F4(void);
#if TARGET_PC
extern FE10_PROTO void fn_8000F9C8(void *, u16, u16, u16, u16);
#else
extern void fn_8000F9C8(int, u16, u16, u16, u16);
#endif
extern void fn_8000FF74(void*);
#if TARGET_PC
extern FE10_PROTO void fn_800104DC(void *);
extern FE10_PROTO void fn_80010788(int, int, void*, void *);
#else
extern void fn_800104DC(int);
extern void fn_80010788(void*, int, void*, int);
#endif
typedef struct MapState {
    u8 pad0[0xB4];
    u32 flags; /* 0xB4 */
} MapState;
extern void fn_800F8430(void);
typedef struct AnimState {
    u8 pad0[0x3C];
    void* unk3C; /* 0x3C */
    void* unk40; /* 0x40 */
    void* unk44; /* 0x44 */
} AnimState;
extern void fn_8001B254(void*);
typedef struct GameFlags {
    u32 b31 : 1;
    u32 b30 : 1;
    u32 b29 : 1;
    u32 b28 : 1;
    u32 b27 : 1;
    u32 b26 : 1;
    u32 b6 : 1; /* 0x02000000 */
    u32 rest : 25;
} GameFlags;
typedef struct ModelHdr {
    u32 hi : 26;
    u32 b5 : 1;
    u32 b4 : 1;
    u32 b3 : 1;
    u32 b2 : 1;
    u32 b1 : 1;
    u32 b0 : 1;
} ModelHdr;
typedef struct AnimInfo {
    u8 pad0[0x10];
    s32 unk10; /* 0x10 */
} AnimInfo;
extern void* fn_80060728(void*);
extern u8 lbl_804CB73C;
extern void fn_800FA9C0(void);
extern AnimInfo* fn_80007F10(void*);
extern void fn_8000866C(void*, f32);
extern int fn_80008C98(void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_800620A8(void*, f32, f32);
#else
extern void* fn_800620A8(void*, f32, f32);
#endif
extern void fn_8012FED4(void*);
extern f32 fn_80176A4C(f32, f32, f32, f32);
typedef struct MUProc {
    u8 pad0[0x18];
    u32 unk18;       /* 0x18 */
    u8 pad1C[0x14];
    MapUnit* unit;   /* 0x30 */
    s32 unk34;       /* 0x34 */
    s32 unk38;       /* 0x38 */
    u8 pad3C[4];
    u16 flags40;     /* 0x40 */
} MUProc;
extern void fn_800FB398(void);
extern s16 fn_8001E094(f32);
extern void fn_80008B50(void*);
extern void fn_80083B78(void*);
#if TARGET_PC
extern FE10_PROTO void fn_80102928(MapUnit*, s32, s32, u16, void *);
#else
extern void fn_80102928(MapUnit*, s32, s32, u16, u32);
#endif
extern void fn_8008A5C0(void*, u16);
extern void fn_8008A5AC(void*, int);
extern s16 fn_8008A1B4(void*);
extern void fn_8008A1A0(void*);
extern void fn_800180F0(void*);
extern void fn_80008F64(void*, u8);
extern int fn_80117A0C(void*, int, int);
extern void fn_800F8880(MapUnit*);
extern void fn_800F8C2C(MapUnit*);
typedef union WGPipe {
    u8 u8;
    s8 s8;
    u16 u16;
    s16 s16;
    u32 u32;
    s32 s32;
    f32 f32;
} WGPipe;
#define GXWGFifo (*(volatile WGPipe*)0xCC008000)

static inline void GXPosition3f32(f32 x, f32 y, f32 z) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}

static inline void GXColor4u8(u8 r, u8 g, u8 b, u8 a) {
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;
}

static inline void GXTexCoord2f32(f32 s, f32 t) {
    GXWGFifo.f32 = s;
    GXWGFifo.f32 = t;
}

typedef f32 Mtx[3][4];
extern double fn_801142F0(void*, f32, f32);
extern void fn_803128AC(Mtx, f32, f32, f32);
extern void fn_80312444(void*, Mtx);
extern void fn_80312378(void*, Mtx, Mtx);
extern void* fn_8000FB88(void);
extern void fn_80307E48(Mtx, int);
extern void fn_80021784(int);
extern void fn_80304314(int, int, int);
extern void fn_800FA264(void);
extern void fn_80305A40(void*, void*, int, int, int, int, int, int);
extern void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
extern s8 lbl_804CB742;
extern u8 lbl_804CB741;
extern u8 lbl_803EC898[];
extern f32 fn_80113F00(void*, f32, f32);
extern int fn_8013B9CC(void);
extern void* fn_8013B9A8(void);
extern int fn_8013818C(void*, int, int);
extern int fn_8011F680(MapUnit*);
extern void fn_80008F10(void*, u8, u8, u8);
extern void fn_80008F20(void*, u8);
extern void fn_80008F5C(void*, u8);
extern int fn_8011B77C(void*, void*);
extern void* lbl_804CA4E0;
extern void* lbl_804CA4E4;
extern void* lbl_804CA4E8;
extern void* lbl_804CA4EC;
extern u8 lbl_80367BA4[];
#if TARGET_PC
extern FE10_PROTO int fn_80007630(void*, char *);
#else
extern int fn_80007630(void*, int);
#endif
extern Vec fn_800076E8(void*, int);

#if TARGET_PC
extern FE10_PROTO int fn_80009BC8(void*, char *);
#else
extern int fn_80009BC8(void*, int);
#endif
extern void* fn_8012759C(MapUnit*);
extern int fn_800F002C(void*, int);
extern void* fn_800F0AF4(int);
extern void* fn_800F0B04(void*);
extern int fn_800F0994(char*);
extern int fn_800F130C(void*, int, int);
extern void* fn_800F0CBC(void*, int, int);
extern char* fn_800F0C68(void*, int);
extern u32 fn_8023F9F4(char*);
extern char* lbl_804CA4A8;
extern void fn_800F5090(MapUnit*);
extern void fn_8031292C(f32*, f32, f32, f32);
extern void* fn_800080B8(void*);
extern void* fn_800078E4(void*, int);
extern void fn_8000F1D4(void*, void*);
extern void* fn_80007F3C(void*);
#if TARGET_PC
extern FE10_PROTO void fn_80014E24(void*, char*, void*, void *);
#else
extern void fn_80014E24(void*, char*, void*, int);
#endif
extern void fn_80014F64(void*, char*, void*);
#if TARGET_PC
extern FE10_PROTO void * fn_80008110(void*, char*);
#else
extern int fn_80008110(void*, char*);
#endif
extern void fn_800FB9D0(void* m, void* b, void* a, void* t);
extern void fn_800FBC90(void* m, void* b, void* c, void* d);
#if TARGET_PC
extern FE10_PROTO int fn_8023F8EC(void*);
#else
extern void* fn_8023F8EC(void*);
#endif
extern void fn_8023F1A0(void*, int);
extern BOOL fn_8023F880(void*);
extern char* fn_800F0B08(void*, int);
extern void fn_80104ABC(MapUnit*);
extern void fn_80006EE0(void*);
#if TARGET_PC
extern FE10_PROTO void fn_8023F1A8(unsigned int);
#else
extern void fn_8023F1A8(void*);
#endif
extern void* fn_80007F68(void*);
extern void fn_800F6AEC(MapUnit*, int);
extern s16 fn_801237EC(MapUnit*);
extern int fn_801092C4(void*);
extern int fn_800F14A8(void*, int);

void fn_800F3360(GXColor c, f32 x, f32 y, int z) {
    fn_800F280C(c, x, y, z);
}

void fn_800F3874(void) {
    ObjPair* p;
    fn_8012D78C();
    fn_80079978(lbl_804CB738);
    fn_80079978(lbl_804CB734);
    p = lbl_804CB748;
    if (p) {
        if (p) {
            fn_80078E24(p->a);
            p->a = NULL;
            fn_80078E24(p->b);
            p->b = NULL;
            fn_80078E24(p);
        }
        lbl_804CB748 = NULL;
    }
    fn_8001D424(lbl_804CB730);
    lbl_804CB730 = NULL;
}

static inline void PoolReset(ObjPair* p) {
    int i;
    p->used = 0;
    for (i = 0; i < p->count; i++) {
        PoolNode* n = &p->a[i];
        n->a = NULL;
        n->b = NULL;
        p->b[i] = &p->a[i];
    }
    p->cur = p->b;
    p->b[p->count] = NULL;
    p->head = NULL;
    p->tail = NULL;
}

void fn_800F3900(void) {
    if (lbl_804CB748) {
        PoolReset(lbl_804CB748);
    }
}

void fn_800F3984(void) {
    fn_801764F8(0, 0, 0x260, 0x1C0, lbl_804CB734);
    fn_8017659C(0.0f, 0, 0, 0x260, 0x1C0, lbl_804CB743, &lbl_804CB744, lbl_804CB734);
}

void fn_800F39DC(MapUnit* m) {
    int x;
    int y;
    if (fn_8013B9CC()) {
        x = m->mapX;
        y = m->mapY;
        m->x = 0.5f + (f32)x;
        m->y = 0.5f + (f32)y;
        m->z = fn_80113F00(lbl_803EC898, 0.5f + (f32)x, 0.5f + (f32)y);
        m->flags2 &= ~0x240ULL;
        fn_80008F20(m->model, 0xFF);
        if (fn_8011F680(m)) {
            m->flags2 |= 0x40;
            fn_80008F20(m->model, 0);
        }
        if (fn_8013818C(fn_8013B9A8(), x, y)) {
            m->flags2 |= 0x80;
        } else {
            m->flags2 &= ~0x80ULL;
        }
    } else {
        fn_80008F20(m->model, 0xFF);
    }
}

void fn_800F3B50(MapUnit* m, f32 x, f32 y) {
    m->x = x;
    m->y = y;
    m->z = fn_80113F00(lbl_803EC898, x, y);
}

void fn_800F3EB0(
#if TARGET_PC
MapUnit* m, fe10_rgba cv
#else
MapUnit* m, GXColor* c
#endif
) {
#if TARGET_PC
    GXColor* c = (GXColor*)&cv;
#endif
    void* mdl = m->model;
    if (mdl) {
        fn_80008F10(mdl, c->r, c->g, c->b);
        fn_80008F20(mdl, c->a);
    }
}

void fn_800F3F08(MapUnit* m, int a) {
    fn_80008F20(m->model, a);
}

void fn_800F3F14(MapUnit* m, f32 v) {
    m->unk84 = v;
}

void fn_800F3F1C(MapUnit* m, int a) {
    fn_80008F5C(m->model, a);
}

void fn_800F3F28(MapUnit* m, s16 v) {
    m->unkDA = v;
}

void fn_800F3F30(MapUnit* m, s8 v) {
    m->unkD8 = v;
}

void fn_800F3F38(MapUnit* m, int dir) {
    int a;
    if (dir == 0) {
        return;
    }
    switch (dir) {
    case 4:
        a = 0;
        break;
    case 6:
        a = 45;
        break;
    case 2:
        a = 90;
        break;
    case 10:
        a = 135;
        break;
    case 8:
        a = 180;
        break;
    case 9:
        a = 225;
        break;
    case 1:
        a = 270;
        break;
    case 5:
        a = 315;
        break;
    default:
        a = 0;
        break;
    }
    m->angle = 64.0f * a;
}

u8 fn_800F3FE4(MapUnit* m) {
    f32 a = 0.015625f * m->angle;
    if (a < 0.0f) {
        a += 360.0f;
    }
    a = a - (int)(a / 360.0f) * 360;
    if (a > 315.0f || a <= 45.0f) {
        return 4;
    }
    if (a > 45.0f && a <= 135.0f) {
        return 2;
    }
    if (a > 135.0f && a <= 225.0f) {
        return 8;
    }
    if (a > 225.0f && a <= 315.0f) {
        return 1;
    }
    return 4;
}

u8 fn_800F40F4(MapUnit* m) {
    switch (fn_800F3FE4(m)) {
    case 1:
        return 2;
    case 2:
        return 1;
    case 4:
        return 8;
    case 8:
        return 4;
    }
    return 0x40;
}

static inline BOOL InMidRange(int v) {
    return v >= 15 && v < 30;
}

char* fn_800F416C(MapUnit* m) {
    MUData* d = m->data;
    int i;
    char* s;
    if (m->flags & 4) {
        d = ((MUOwner*)d)->data;
    }
    i = 0;
    if (!fn_8011B77C(d->unk24, lbl_804CA4E8)) {
        if (fn_8011B77C(d->unk24, lbl_804CA4E0)) {
            i = 1;
        }
        if (fn_8011B77C(d->unk24, lbl_804CA4E4)) {
            i = 2;
        }
    } else if (fn_8011B77C(d->unk24, lbl_804CA4EC)) {
        if (m->unkFE >= 30) {
            i = 3;
        } else {
            i = InMidRange(m->unkFE) ? 2 : 1;
        }
    }
    s = m->tbl->names[i];
    if (s == NULL) {
        s = d->name20;
    }
    if (s == NULL) {
        s = (char*)lbl_80367BA4 + 0x10;
    }
    return s;
}

int fn_800F4284(
#if TARGET_PC
MapUnit* m, char* k
#else
MapUnit* m, int k
#endif
) {
    if (m->flags & 2) {
        return fn_80007630(m->model, k);
    }
    return -1;
}

static inline int MU_Joint(MapUnit* m, int k) {
    if (m->flags & 2) {
        return fn_80007630(m->model, k);
    }
    return -1;
}

static inline BOOL MU_JointPos(MapUnit* m, int j, Vec* out) {
    if (j >= 0) {
        Vec v;
        v = fn_800076E8(m->model, j);
        out->x = v.x;
        out->y = v.y;
        out->z = v.z;
        return 1;
    }
    return 0;
}

BOOL fn_800F42A0(MapUnit* m, int k, Vec* out) {
    return MU_JointPos(m, MU_Joint(m, k), out);
}

BOOL fn_800F432C(MapUnit* m, int j, Vec* out) {
    return MU_JointPos(m, j, out);
}

int fn_800F4394(
#if TARGET_PC
MapUnit* m, char* k
#else
MapUnit* m, int k
#endif
) {
    if (m->flags & 2) {
        return fn_80009BC8(m->model, k);
    }
    return -1;
}

int fn_800F43B0(MapUnit* m) {
    int r;
    if (m->unkD8 >= 0) {
        r = m->unkD8;
    } else {
        r = fn_800F002C(fn_8012759C(m), 0);
    }
    return r;
}

void* fn_800F43F0(MapUnit* m) {
    char* s;
    void* r;
    if (m->unkDA >= 0) {
        return fn_800F0AF4(m->unkDA);
    }
    s = fn_800F416C(m);
    if (s == NULL || *s == 0) {
        return fn_800F0B04(lbl_80367BA4 + 0x11);
    }
    r = fn_800F0B04(s);
    if (r == NULL) {
        r = fn_800F0B04(lbl_80367BA4 + 0x11);
    }
    return r;
}

void
#if TARGET_PC
*
#endif
fn_800F446C(MapUnit* m, int k) {
#if TARGET_PC
    return fn_800F0CBC(fn_800F43F0(m), fn_800F43B0(m), k);
#else
    fn_800F0CBC(fn_800F43F0(m), fn_800F43B0(m), k);
#endif
}

void
#if TARGET_PC
*
#endif
fn_800F4544(MapUnit* m, char* name) {
    int k = fn_800F0994(name);
#if TARGET_PC
    return fn_800F0CBC(fn_800F43F0(m), fn_800F43B0(m), k);
#else
    fn_800F0CBC(fn_800F43F0(m), fn_800F43B0(m), k);
#endif
}

int fn_800F4628(MapUnit* m, int k) {
    return fn_800F130C(fn_800F43F0(m), fn_800F43B0(m), k);
}

int fn_800F4700(MapUnit* m, char* name) {
    int k;
    if (name == NULL) {
        return 0;
    }
    k = fn_800F0994(name);
    return fn_800F130C(fn_800F43F0(m), fn_800F43B0(m), k);
}

struct UnitRef* fn_800F47F4(MapUnit* m) {
    return m->unkDC;
}

char* fn_800F47FC(MapUnit* m, int k) {
    void* c = fn_800F43F0(m);
    char* s;
    switch (k) {
    case 0:
        s = fn_800F0C68(c, 0);
        break;
    case 1:
        s = fn_800F0C68(c, 1);
        break;
    case 2:
        s = fn_800F0C68(c, 2);
        break;
    case 3:
        s = fn_800F0C68(c, 3);
        break;
    default:
        s = fn_800F0C68(c, 0);
        break;
    }
    if (s == NULL || fn_8023F9F4(s) == 0x40000) {
        s = lbl_804CA4A8;
    }
    return s;
}

void fn_800F5088(MapUnit* m, u8 v) {
    m->unkC7 = v;
    fn_800F5090(m);
}

void fn_800F629C(MapUnit* m, void* mdl) {
    f32 mtx[12];
    void* r;
    int i;
    if (m->nJoints != 0) {
        if (mdl == NULL) {
            mdl = m->model;
        }
        fn_8031292C(mtx, 0.0f, 0.0f, 0.0f);
        r = fn_800080B8(mdl);
        for (i = 0; i < m->nJoints; i++) {
            fn_8000F1D4(fn_800078E4(mdl, m->joints[i]), r);
        }
    }
}


void fn_800F64D4(MapUnit* m) {
    m->angle = 0;
    m->unkC6 = 100;
    m->unk2 = 0;
    m->unkDA = -1;
    m->unkD9 = -1;
    m->unkD8 = -1;
    m->f1C = 0.0f;
    m->f20 = 0.0f;
    m->f24 = 0.0f;
    m->unkE0 = 0;
    m->flags = 0;
    m->flags |= 0x3C0;
    m->unkDC = NULL;
}

void fn_800F651C(MapUnit* m, int k) {
    void* p = fn_800F0CBC(fn_800F43F0(m), fn_800F43B0(m), k);
    if (p) {
        fn_8023F1A0(p, 0);
    }
}

void fn_800F6604(MapUnit* m, char* name) {
    int k = fn_800F0994(name);
    void* p = fn_800F0CBC(fn_800F43F0(m), fn_800F43B0(m), k);
    if (p) {
        fn_8023F1A0(p, 0);
    }
}

BOOL fn_800F66F8(MapUnit* m, int k) {
    void* p = fn_800F0CBC(fn_800F43F0(m), fn_800F43B0(m), k);
    if (p == NULL) {
        return 1;
    }
    return fn_8023F880(p);
}

BOOL fn_800F67E4(MapUnit* m, char* name) {
    int k = fn_800F0994(name);
    void* p = fn_800F0CBC(fn_800F43F0(m), fn_800F43B0(m), k);
    if (p == NULL) {
        return 1;
    }
    return fn_8023F880(p);
}

void fn_800F68DC(MapUnit* m, int k) {
    void* c = fn_800F43F0(m);
    u8 w;
    k |= 0x40;
    fn_8023F1A0(fn_800F0B08(c, -1), k);
    w = m->unkF4->unk8;
    if (!fn_800F14A8(c, w)) {
        char* s = fn_800F47FC(m, w);
        if (s != lbl_804CA4A8) {
            fn_8023F1A0(s, k);
        }
    }
    m->flags |= 1;
}

BOOL fn_800F69E4(MapUnit* m) {
    void* c = fn_800F43F0(m);
    u8 w;
    if (!fn_8023F880(fn_800F0B08(c, -1))) {
        return 0;
    }
    w = m->unkF4->unk8;
    if (!fn_800F14A8(c, w)) {
        char* s = fn_800F47FC(m, w);
        if (s != lbl_804CA4A8 && !fn_8023F880(s)) {
            return 0;
        }
    }
    return 1;
}

/* The volatile read on the test is a workaround, not recovered source: the
 * original reloads flags for the clear and this is the only form found that
 * does so. A non-volatile test lets MWCC reuse the loaded value. */
static inline void MU_Release(MapUnit* m) {
    if (*(volatile u16*)&m->flags & 2) {
        m->flags &= ~2;
        fn_80104ABC(m);
        fn_80006EE0(m->model);
        if (m->unkE0) {
            fn_8023F1A8(m->unkE0);
            m->unkE0 = NULL;
        }
        m->unkDC = NULL;
    }
}

void fn_800F7410(MapUnit* m, int reinit) {
    if (*(volatile u16*)&m->flags & 2) {
        m->flags &= ~2;
        fn_80104ABC(m);
        fn_80006EE0(m->model);
        if (m->unkE0) {
            fn_8023F1A8(m->unkE0);
            m->unkE0 = NULL;
        }
        m->unkDC = NULL;
        if (reinit) {
            fn_800F64D4(m);
        }
    }
}

void fn_800F74D0(MapUnit* m, int k) {
    if (!(m->flags & 2)) {
        return;
    }
    if (m->unkE0 == fn_8023F8EC(fn_800F0B08(fn_800F43F0(m), -1))) {
        void* r = fn_80007F68(m->model);
        if (r == fn_8023F8EC(fn_800F47FC(m, m->unkF4->unk8))) {
            return;
        }
    }
    MU_Release(m);
    fn_800F6AEC(m, k);
}

int fn_800F760C(MapUnit* m) {
    int v = m->unk114;
    int ok;
    if (v * 100 < fn_801237EC(m) * 20) {
        ok = 1;
    } else {
        ok = fn_801092C4(m->unk110);
    }
    if (ok && fn_800F130C(fn_800F43F0(m), fn_800F43B0(m), 2)) {
        return 2;
    }
    return 0;
}

BOOL fn_800F7724(MapUnit* m) {
    if (m->flags2 & 0x40100009CULL) {
        return 0;
    }
    if ((m->flags2 & 0x240) == 0x40) {
        return 0;
    }
    if ((m->flags & 0x22U) != 2) {
        return 0;
    }
    return m->unk33 != 0;
}

Vec fn_800F7790(MapUnit* m) {
    Vec v;
    Vec o;
    Vec t;
    Vec p;
    if (m->flags & 2) {
        void* mdl = m->model;
        if (m->unkC8 < 0) {
            fn_8001E9E4((u8*)mdl + 0x10, &v);
            v.z -= 0.5f;
        } else {
            t = fn_800076E8(mdl, m->unkC8);
            v.x = t.x;
            v.y = t.y;
            v.z = t.z;
        }
    } else {
        p = *(Vec*)&m->x;
        v.x = p.x;
        v.y = p.y;
        v.z = p.z - 0.5f;
        o = *(Vec*)&m->offX;
        fn_80313460(&v, &o, &v);
    }
    return v;
}

void fn_800F7D04(MapUnit* m) {
    if (!(m->flags & 2)) {
        return;
    }
    if (m->flags & 8) {
        return;
    }
    if (m->unk110h & 1) {
        return;
    }
    fn_800081D4(m->model);
}

void fn_800F7D30(void) {
    lbl_803E8FD8[0] = 10000.0f;
    lbl_803E8FD8[1] = 10000.0f;
    lbl_803E8FE4[0] = -10000.0f;
    lbl_803E8FE4[1] = -10000.0f;
}

void fn_800F7D5C(void) {
    if (lbl_804CB740) {
        lbl_803E8FD8[0] = 0.0f;
        lbl_803E8FD8[1] = 0.0f;
        lbl_803E8FE4[0] = 608.0f;
        lbl_803E8FE4[1] = 448.0f;
        return;
    }
    lbl_803E8FD8[0] -= 64.0f;
    lbl_803E8FD8[1] -= 64.0f;
    lbl_803E8FE4[0] += 64.0f;
    lbl_803E8FE4[1] += 64.0f;
    if (lbl_803E8FD8[0] < 0.0f) {
        lbl_803E8FD8[0] = 0.0f;
    }
    if (lbl_803E8FD8[1] < 0.0f) {
        lbl_803E8FD8[1] = 0.0f;
    }
    if (lbl_803E8FE4[0] > 608.0f) {
        lbl_803E8FE4[0] = 608.0f;
    }
    if (lbl_803E8FE4[1] < 448.0f) {
        lbl_803E8FE4[1] = 448.0f;
    }
}

void fn_800F7E40(int h) {
    if (fn_8017DA30(0x80)) {
        return;
    }
    lbl_804CB744.r = 0x60;
    lbl_804CB744.g = 0x60;
    lbl_804CB744.b = 0x60;
    lbl_804CB744.a = 0x60;
    lbl_804CB743 = 1;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, h, 1.0f);
    fn_8007E174(0, 0x410);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800800D4(0xB);
    fn_80080910(fn_800F3984, 0);
    fn_80080308();
    fn_8007E7F4();
}

void fn_800F7F04(void) {
    if (fn_8017DA30(0x80)) {
        return;
    }
    lbl_804CB744.r = 0x30;
    lbl_804CB744.g = 0x30;
    lbl_804CB744.b = 0x60;
    lbl_804CB744.a = 0x60;
    lbl_804CB743 = 1;
    if (lbl_803E8FD8[0] >= lbl_803E8FE4[0] || lbl_803E8FD8[1] >= lbl_803E8FE4[1]) {
        return;
    }
    fn_8000F9C8(0, lbl_803E8FD8[0], lbl_803E8FD8[1], lbl_803E8FE4[0] - lbl_803E8FD8[0], lbl_803E8FE4[1] - lbl_803E8FD8[1]);
    fn_8000FF74(0);
    fn_800F3984();
    fn_800104DC(0);
}

void fn_800F8030(void* a) {
    fn_80010788(a, 0x8F, fn_800F7F04, 0);
}

void fn_800F87CC(void) {
    if (((MapState*)fn_8013B9A8())->flags & 0x10) {
        fn_80010788(NULL, 0x43, fn_800F8430, 0);
    }
}

void fn_800F8810(void* a) {
    fn_80305A40(a, lbl_804CB738, 0x98, 0x70, 0, 0, 0, 0);
    fn_80305C94(a, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
}

static inline u8 TileShade(MapUnit* m) {
    int tx = m->x;
    int ty = m->y;
    return (tx + ty * 5) % 25 * 4 + 0x9B;
}

static inline int MapCheck2(MapUnit* m) {
    s8 x = m->x;
    s8 y = m->y;
    return fn_80117A0C(lbl_803EC898, x, y);
}

void fn_800F91B8(MapUnit* m) {
    if (fn_800F7724(m)) {
        Model* mdl = (Model*)m->model;
        AnimState* a = fn_80007F3C(mdl);
        u8 save = mdl->unk82;
        void* s3c = a->unk3C;
        void* s40 = a->unk40;
        void* s44 = a->unk44;
        fn_8001B254(mdl);
        a->unk3C = s3c;
        a->unk40 = s40;
        a->unk44 = NULL;
        mdl->unk82 = 0x8E;
        fn_800180F0(mdl);
        if (s44) {
            a->unk3C = NULL;
            a->unk40 = NULL;
            a->unk44 = s44;
            mdl->unk82 = 0x95;
            fn_800180F0(mdl);
        }
        a->unk3C = s3c;
        a->unk40 = s40;
        a->unk44 = s44;
        mdl->unk82 = save;
        fn_800F629C(m, NULL);
        { int tx = m->x; int ty = m->y; fn_80008F64(mdl, (tx + ty * 5) % 25 * 4 + 0x9B); }
        {
            f32 x = m->x;
            f32 y = m->y;
            if (!fn_80117A0C(lbl_803EC898, (s8)x, (s8)y)) {
                fn_800F8880(m);
                fn_800F8C2C(m);
            }
        }
    }
}

void fn_800F9890(void) {
    int v;
    if (lbl_804CB742 == 0) {
        return;
    }
    v = lbl_804CB741 + lbl_804CB742;
    if (v <= 0) {
        lbl_804CB742 = v = 0;
    }
    if (v > 0xFF) {
        lbl_804CB742 = 0;
        v = 0xFF;
    }
    lbl_804CB741 = v;
}

void fn_800F98CC(void) {
    fn_80010788((void*)3, 0x84, fn_800FA264, 0);
}

void fn_800FAD48(void) {
    if (!((GameFlags*)fn_80060728(lbl_803CAB38))->b6 && lbl_804CB73C) {
        fn_80010788((void*)3, 0x85, fn_800FA9C0, 0);
    }
}

BOOL fn_800FADA0(MapUnit* m) {
    return (u16)(m->flags & 2) != 0;
}

BOOL fn_800FADB8(MapUnit* m) {
    f32 x = m->x;
    f32 y = m->y;
    s8 tx = x;
    s8 ty = y;
    return fn_80117A0C(lbl_803EC898, tx, ty);
}

static inline ModelHdr* MU_Hdr(MapUnit* m) {
    return (ModelHdr*)m->model;
}

static inline u32 ModelBit4(ModelHdr* h) {
    return h ? h->b4 : 0;
}

static inline u32 ModelBit5(ModelHdr* h) {
    return h ? h->b5 : 0;
}

#pragma push
#pragma auto_inline off
BOOL fn_800FAE98(MapUnit* m) {
    ModelHdr* h;
    AnimInfo* a;
    if (!(m->flags & 2)) {
        return 1;
    }
    if (m->flags2 & 0x10000DC) {
        return 1;
    }
    h = (ModelHdr*)m->model;
    a = fn_80007F10(h);
    if (ModelBit4(MU_Hdr(m))) {
        return 1;
    }
    if (a == NULL) {
        return 1;
    }
    if (!ModelBit5(MU_Hdr(m)) && a->unk10 != 0) {
        return 1;
    }
    return h->b1;
}
#pragma pop

void fn_800FAF78(MapUnit* m) {
    if (m->flags & 2) {
        void* mdl = m->model;
        AnimInfo* a = fn_80007F10(mdl);
        if (a && a->unk10 == 0) {
            fn_8000866C(mdl, -1.0f);
        }
    }
}

int fn_800FAFD4(MapUnit* m, int ev) {
    if (m->flags & 2) {
        return fn_80008C98(m->model, ev);
    }
    return 0;
}

static inline f32 MU_AngleTo(MapUnit* m, f32 x, f32 y) {
    if (x == m->x && y == m->y) {
        return 0.015625f * m->angle;
    }
    {
        f32 my = m->y;
        f32 mx = m->x;
        return fn_80176A4C(mx, my, x, y);
    }
}

f32 fn_800FB08C(MapUnit* m, MapUnit* o) {
    return MU_AngleTo(m, o->x, o->y);
}

f32 fn_800FB100(MapUnit* m, f32 x, f32 y) {
    return MU_AngleTo(m, x, y);
}

Vec fn_800FB178(MapUnit* m, f32 s) {
    Vec v = {0};
    UnitRef* r = m->unkDC;
    if (r) {
        v.x = r->info->unk12;
        v.y = r->info->unk13;
    }
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return v;
}

void fn_800FB228(MapUnit* m, BOOL on) {
    ModelHdr* h = MU_Hdr(m);
    if (h) {
        if (on) {
            h->b3 = 1;
        } else {
            h->b3 = 0;
        }
    }
}

void fn_800FB258(MapUnit* m, BOOL on) {
    ModelHdr* h = MU_Hdr(m);
    if (h) {
        if (on) {
            h->b4 = 1;
        } else {
            h->b4 = 0;
        }
    }
}

void fn_800FB288(MapUnit* m, BOOL on) {
    ModelHdr* h = MU_Hdr(m);
    if (h) {
        if (on) {
            h->b5 = 1;
        } else {
            h->b5 = 0;
        }
    }
}

void fn_800FB2B8(MapUnit* m, void* w) {
    fn_8008A5C0(w, m->angle);
    fn_8008A5AC(w, 0);
    fn_8008A5AC(w, 0);
}

void fn_800FB304(MapUnit* m, void* r) {
    fn_800F64D4(m);
    m->angle = fn_8008A1B4(r);
    fn_8008A1A0(r);
    fn_8008A1A0(r);
}

static inline PoolNode* Pool_Next(ObjPair* p, PoolNode* n) {
    if (n == NULL) {
        return p->head;
    }
    return n->a;
}

static inline void Pool_Free(ObjPair* p, PoolNode* n) {
    if (n) {
        if (n->a) {
            n->a->b = n->b;
        }
        if (n->b) {
            n->b->a = n->a;
        }
        if (n == p->head) {
            p->head = n->a;
        }
        if (n == p->tail) {
            p->tail = n->b;
        }
        *--p->cur = n;
        p->used--;
    }
}

void fn_800FB824(void) {
    PoolNode* n;
    if (lbl_804CB748 == NULL) {
        return;
    }
    n = NULL;
    while ((n = Pool_Next(lbl_804CB748, n)) != NULL) {
        if (++n->timer == 180) {
            Pool_Free(lbl_804CB748, n);
        }
    }
    fn_80010788((void*)3, 0x83, fn_800FB398, 0);
}

static inline PoolNode* Pool_Alloc(ObjPair* p) {
    PoolNode* n = *p->cur;
    if (n == NULL) {
        return NULL;
    }
    n->b = p->tail;
    n->a = NULL;
    if (p->tail) {
        p->tail->a = n;
    }
    if (p->head == NULL) {
        p->head = n;
    }
    p->tail = n;
    p->cur++;
    p->used++;
    return n;
}

void fn_800FB904(s16 id, f32 x, f32 y) {
    PoolNode* n = Pool_Alloc(lbl_804CB748);
    if (n) {
        n->x = fn_8001E094(x);
        n->y = fn_8001E094(y);
        n->id = id;
        n->timer = 0;
    }
}

void fn_800FC550(MUProc* q) {
    if (!(q->flags40 & 0x100)) {
        fn_80008B50(q->unit->model);
    }
}

void fn_800FC56C(MUProc* q) {
    if (fn_800FAE98(q->unit)) {
        fn_80083B78(q);
    }
}
