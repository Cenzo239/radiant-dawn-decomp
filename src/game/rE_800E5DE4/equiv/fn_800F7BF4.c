/* fn_800F7BF4: functionally equal (regs, 5 of 68 words differ in registers only). Helpers from fn_800F3360.c (exported bodies removed), body from wip/fn_800F7BF4.c. fn_800F7724_i is a local inline copy of fn_800F7724, which the original inlines here. */
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
extern void fn_80080910(void*, int);
extern void fn_80080308(void);
extern void fn_8007E7F4(void);
extern void fn_8000F9C8(int, u16, u16, u16, u16);
extern void fn_8000FF74(void*);
extern void fn_800104DC(int);
extern void fn_80010788(void*, int, void*, int);
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
extern int fn_80008C98(void*, int ev);
extern void* fn_800620A8(void*, f32, f32);
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
extern void fn_80102928(MapUnit*, s32, s32, u16, u32);
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
extern int fn_80007630(void*, int);
extern Vec fn_800076E8(void*, int);

extern int fn_80009BC8(void*, int);
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
extern void fn_80014E24(void*, char*, void*, int);
extern void fn_80014F64(void*, char*, void*);
extern int fn_80008110(void*, char*);
extern void fn_800FB9D0(void* m, void* b, void* a, void* t);
extern void fn_800FBC90(void* m, void* b, void* c, void* d);
extern void* fn_8023F8EC(void*);
extern void fn_8023F1A0(void*, int);
extern BOOL fn_8023F880(void*);
extern char* fn_800F0B08(void*, int);
extern void fn_80104ABC(MapUnit*);
extern void fn_80006EE0(void*);
extern void fn_8023F1A8(void*);
extern void* fn_80007F68(void*);
extern void fn_800F6AEC(MapUnit*, int);
extern s16 fn_801237EC(MapUnit*);
extern int fn_801092C4(void*);
extern int fn_800F14A8(void*, int);
void fn_800F3360(GXColor c, f32 x, f32 y, int z);

void fn_800F3874(void);


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
void fn_800F3900(void);

void fn_800F3984(void);

void fn_800F39DC(MapUnit* m);

void fn_800F3B50(MapUnit* m, f32 x, f32 y);

void fn_800F3EB0(MapUnit* m, GXColor* c);

void fn_800F3F08(MapUnit* m, int a);

void fn_800F3F14(MapUnit* m, f32 v);

void fn_800F3F1C(MapUnit* m, int a);

void fn_800F3F28(MapUnit* m, s16 v);

void fn_800F3F30(MapUnit* m, s8 v);

void fn_800F3F38(MapUnit* m, int dir);

u8 fn_800F3FE4(MapUnit* m);

u8 fn_800F40F4(MapUnit* m);


static inline BOOL InMidRange(int v) {
    return v >= 15 && v < 30;
}
char* fn_800F416C(MapUnit* m);

int fn_800F4284(MapUnit* m, int k);


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
BOOL fn_800F42A0(MapUnit* m, int k, Vec* out);

BOOL fn_800F432C(MapUnit* m, int j, Vec* out);

int fn_800F4394(MapUnit* m, int k);

int fn_800F43B0(MapUnit* m);

void* fn_800F43F0(MapUnit* m);

void fn_800F446C(MapUnit* m, int k);

void fn_800F4544(MapUnit* m, char* name);

int fn_800F4628(MapUnit* m, int k);

int fn_800F4700(MapUnit* m, char* name);

struct UnitRef* fn_800F47F4(MapUnit* m);

char* fn_800F47FC(MapUnit* m, int k);

void fn_800F5088(MapUnit* m, u8 v);

void fn_800F629C(MapUnit* m, void* mdl);

void fn_800F64D4(MapUnit* m);

void fn_800F651C(MapUnit* m, int k);

void fn_800F6604(MapUnit* m, char* name);

BOOL fn_800F66F8(MapUnit* m, int k);

BOOL fn_800F67E4(MapUnit* m, char* name);

void fn_800F68DC(MapUnit* m, int k);

BOOL fn_800F69E4(MapUnit* m);


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
void fn_800F7410(MapUnit* m, int reinit);

void fn_800F74D0(MapUnit* m, int k);

int fn_800F760C(MapUnit* m);

/* Local inline copy of fn_800F7724_i (matched elsewhere): the original inlines it here. */
static inline BOOL fn_800F7724_i(MapUnit* m){
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

Vec fn_800F7790(MapUnit* m);

void fn_800F7D04(MapUnit* m);

void fn_800F7D30(void);

void fn_800F7D5C(void);

void fn_800F7E40(int h);

void fn_800F7F04(void);

void fn_800F8030(void* a);

void fn_800F87CC(void);

void fn_800F8810(void* a);


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
void fn_800F91B8(MapUnit* m);

void fn_800F9890(void);

void fn_800F98CC(void);

void fn_800FAD48(void);

BOOL fn_800FADA0(MapUnit* m);

BOOL fn_800FADB8(MapUnit* m);


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

BOOL fn_800FAE98(MapUnit* m);

#pragma pop

void fn_800FAF78(MapUnit* m);

int fn_800FAFD4(MapUnit* m, int ev);


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
f32 fn_800FB08C(MapUnit* m, MapUnit* o);

f32 fn_800FB100(MapUnit* m, f32 x, f32 y);

Vec fn_800FB178(MapUnit* m, f32 s);

void fn_800FB228(MapUnit* m, BOOL on);

void fn_800FB258(MapUnit* m, BOOL on);

void fn_800FB288(MapUnit* m, BOOL on);

void fn_800FB2B8(MapUnit* m, void* w);

void fn_800FB304(MapUnit* m, void* r);


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
void fn_800FB824(void);


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
void fn_800FB904(s16 id, f32 x, f32 y);

void fn_800FC550(MUProc* q);

void fn_800FC56C(MUProc* q);


/* ---- from rE_800E5DE4/wip/fn_800F7BF4.c ---- */
/* fn_800F7BF4: 5 of 68 words differ (register swap only: the original keeps
 * `mdl` (m+0x28) in r5 and the low flags2 word of the inlined fn_800F7724_i in
 * r7; MWCC gives the opposite). Tried: local declared/assigned separately,
 * static inline copy of fn_800F7724_i, Model* type, `!= 0`. Uses the MapUnit
 * struct from ../fn_800F3360.c, where fn_800F7724_i precedes it. */
void fn_800F7BF4(MapUnit* m) {
    Model* mdl = (Model*)m->model;
    if (m->flags & 8) {
        return;
    }
    if (fn_800F7724_i(m)) {
        fn_80007C58(mdl);
    }
    if (m->flags2 & 1) {
        return;
    }
    if (m->unkF4->unk8 == lbl_803CAB38[0x11] || m->unk2 != 0) {
        m->unk2 = (m->unk2 + 4) % 360;
    }
}