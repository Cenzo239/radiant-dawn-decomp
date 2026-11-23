/* fn_80185D0C: class change event setup, with the battle unit constructor inlined three times. StringPool is scaffolding. */
#include "game/rF_8017F400/types.h"
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "BGM_EVT_CLASS_CHANGE1";
    p[1] = "\x8d\\\x82\xa6";
    p[2] = "\x83N\x83\x89\x83X\x8f\xe3\x8b\x89";
    p[3] = "EID_CLASSCHANGE1";
    p[4] = "EID_CLASSCHANGE1_ROOT";
}
struct Slot {
    u8* item;
    u8 uses;
    u8 flags;
    void init() {
        item = 0;
        uses = 2;
        flags = 0;
        if (item) {
            flags |= item[0x20] == 0 ? 1 : 0;
        }
    }
};

typedef struct BU {
    u16 x0; u8 pad2[0x108 - 2]; int x108, x10c; u8 pad110[0x119 - 0x110]; u8 a[8]; u8 b[8]; u8 pad129[3];
    Slot skills[18]; u8 inv[0x118]; u8 pad2d4[0x2ec - 0x2d4]; void* v2ec; u8 pad2f0[0x348 - 0x2f0]; void* v348; u8 pad34c[0x358 - 0x34c]; void* v358; u8 pad35c[0x368 - 0x35c]; void* v368; u8 pad36c[0x382 - 0x36c];
    u16 x382, x384, x386, x388, x38a, x38c; u8 x38e, x38f; u8 pad390[0x3c4 - 0x390]; u8 s3c4[0x3f4 - 0x3c4]; u8 w1[0x28]; u8 w2[0x28]; u8 pad444[0x45e - 0x444]; u16 x45e; u8 pad460[0x493 - 0x460]; u8 c[8]; u8 pad49b[0x4a0 - 0x49b];
} BU;
typedef struct BMem { BU u[3]; u8 pad[0x15ec - 0xde0]; int x15ec; u8 pad2[0x1648 - 0x15f0]; } BMem;
typedef struct BGlob { u8 pad[0x15fc]; s8 x15fc; u8 x15fd; u8 pad15fe[0x1624 - 0x15fe]; char x1624[1]; } BGlob;
typedef struct PS { u8 pad[0x30]; u8 x30; } PS;
typedef struct EvE { u8 pad[0x98]; void* x98; void* x9c; } EvE;
typedef struct MdlD { u8 pad[8]; u8 x8; } MdlD;
typedef struct Mdl { u8 pad[0x54]; MdlD* x54; } Mdl;
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct W3 { u32 a, b, c; } W3;
typedef struct Act { u8 pad[0x44]; W3 pos; int x50; s8 x54; u8 pad55[2]; u8 x57; s16 x58; u8 pad5a[0x78 - 0x5a]; void* x78; u8 pad7c[4]; int x80; } Act;
typedef struct Cam { u8 pad[0x48]; Vec3 rot; u8 pad54[0x75 - 0x54]; u8 x75, x76; } Cam;
typedef struct GfxQ { u8 pad[4]; s16 x4; u8 pad6[0x18 - 6]; u32 x18; } GfxQ;
typedef struct SprQ { u8 pad[0x30]; GfxQ* g; } SprQ;
typedef struct Ev { u8 pad[0x30]; Mdl* x30; void* x34; u8 pad38[4]; Act* act[2]; Cam* x44; u8 x48[4]; u8 x4c; u8 pad4d[0x54 - 0x4d]; void* x54; BMem* x58; } Ev;
extern u8 lbl_803C8E80[];
extern u8 lbl_803CAB38[];
extern char lbl_80379438[];
extern char lbl_80388140[];
extern void* fn_80079150(u32);
extern void fn_8028BFD8(void*, void*, void*, u32, u32);
extern void fn_80111B34(void*);
extern void fn_80111C24(void*, int);
extern void fn_80129150(void*);
extern void* fn_8002E3D4(void*);
extern void fn_80026898(void*, void*);
extern void fn_8006CE30(void*, void*);
extern void fn_8011FFD0(void*);
extern void fn_800A947C(Ev*);
extern void* fn_800A75E8(void*, int);
extern void fn_80083DC4(void*, int);
extern PS* fn_80083B84(void*);
extern EvE* fn_8006074C(void*);
extern int fn_801347B0(void*);
extern void* fn_80030CF4(void*);
extern void fn_800AAB14(void*, int);
extern int fn_800AA548(void*, const char*, int);
extern void fn_800AAB1C(void*, int);
extern void fn_800AE940(void*, int);
extern void fn_800AAB38(void*, int);
extern void fn_800B1120(void*);
extern void fn_800B1628(void*, void*);
extern void fn_800B540C(void*, void*);
extern void fn_800B4574(void*, void*, int);
extern void fn_800B54DC(void*, int);
extern void fn_800B26B0(void*, const char*, int, u16);
extern void fn_800B2958(void*, f32);
extern void fn_800B29D0(void*);
extern void fn_800A4B00(void*, void*);
extern void* fn_800A8324(const char*);
extern void fn_800A4420(void*, void*, int);
extern void fn_800A5D34(void*, int);
extern SprQ* fn_800E3810(const char*, void*);
extern void fn_800E48C8(void*, void*);
extern f32 fn_8001E064(int);
extern void fn_800E49AC(void*, f32);
extern void fn_800B377C(W3*, void*, int);
extern void fn_800A9E64(void*, int, int);
static inline void* Ctor(BU* const& u) {
    u32 z = 0;
    u->x0 = z;
    u->x10c = z;
    u->x108 = z;
    u->a[7] = z; u->a[6] = z; u->a[5] = z; u->a[4] = z; u->a[3] = z; u->a[2] = z; u->a[1] = z; u->a[0] = z;
    u->b[7] = z; u->b[6] = z; u->b[5] = z; u->b[4] = z; u->b[3] = z; u->b[2] = z; u->b[1] = z; u->b[0] = z;
    {
        Slot* s = u->skills;
        do {
            s->init();
            s++;
        } while (s < (Slot*)u->inv);
    }
    fn_8028BFD8(u->inv, (void*)fn_80111B34, (void*)fn_80111C24, 0x28, 7);
    u->v2ec = lbl_80379438;
    u->v348 = lbl_80379438;
    u->v358 = lbl_80379438;
    u->v368 = lbl_80379438;
    u->x382 = 0; u->x384 = 0; u->x386 = 0; u->x388 = 0; u->x38a = 0; u->x38c = 0; u->x38e = 0; u->x38f = 0;
    fn_80129150(u->s3c4);
    fn_80111B34(u->w1);
    fn_80111B34(u->w2);
    u->x45e = 0;
    u->c[7] = 0; u->c[6] = 0; u->c[5] = 0; u->c[4] = 0; u->c[3] = 0; u->c[2] = 0; u->c[1] = 0; u->c[0] = 0;
    return fn_8002E3D4(u);
}
static inline BOOL Active(void) {
    PS* s = fn_80083B84(lbl_80388140);
    if (s) {
        switch (s->x30) {
        case 1: case 2: case 3: case 4:
            return TRUE;
        }
    }
    return FALSE;
}
static inline Act* At(Ev* p, int i) {
    if (i < 0) return 0;
    return p->act[i];
}
void fn_80185D0C(Ev* p) {
    /*P*/
    Cam* c;
    int k2;
    BU* u2;
    BU* u3;
    SprQ* q2;
    BMem* m;
    void* a;
    void* b;
    const char* name;
    int k;
    int j;
    void* d;
    int i;
    SprQ* q;
/*E*/
    m = (BMem*)fn_80079150(0x1648);
    if (m) {
        Ctor((BU*)m);
        {
        u2 = (BU*)((u8*)m + 0x4a0);
        Ctor(u2);
        }
        {
        u3 = (BU*)((u8*)m + 0x940);
        m->x15ec = (int)Ctor(u3) * 0;
        }
    }
    p->x58 = m;
    fn_80026898(m, lbl_803C8E80);
    fn_8006CE30(lbl_803C8E80, p->x54);
    fn_8011FFD0(p->x54);
    fn_800A947C(p);
    a = fn_800A75E8(lbl_803C8E80, 0);
    b = fn_800A75E8(lbl_803C8E80 + 0x4a0, 0);
    if (a == 0 || b == 0) {
        fn_80083DC4(p, 2);
        return;
    }
    {
    BGlob* g = (BGlob*)lbl_803C8E80;
    k = g->x15fc;
    j = g->x15fd;
    name = g->x1624;
    }
    if (Active()) {
        EvE* e = fn_8006074C(lbl_803CAB38);
        name = (const char*)e->x98;
        k = fn_801347B0(e->x9c);
        j = 0;
    }
    d = fn_80030CF4(lbl_803C8E80);
    p->x4c = 0;
    fn_800AAB14(p->x30, 2);
    if (fn_800AA548(p->x30, name, 0)) {
        if (!(p->x30->x54->x8 & 2)) {
            fn_800AAB1C(p->x30, k);
            fn_800AE940(p->x34, k);
        }
        fn_800AAB38(p->x30, j);
    }
    p->act[0]->x78 = a;
    p->act[1]->x78 = b;
    {
    k2 = 0x10000;
    for (i = 0; i < 2; i++) {
        At(p, i)->x50 |= 0x04000000;
        fn_800B1120(At(p, i));
        fn_800B1628(At(p, i), lbl_803C8E80);
        fn_800B540C(At(p, i), lbl_803C8E80);
        At(p, i)->x57 = 0;
        fn_800B4574(At(p, i), d, 0);
        fn_800B54DC(At(p, i), -1);
        fn_800B26B0(At(p, i), "\x8d\\\x82\xa6", -1, k2 - 1);
        At(p, i)->x54 = -1;
        At(p, i)->x80 = 0;
        fn_800B2958(At(p, i), 0.0f);
        fn_800B29D0(At(p, i));
    }
    }
    p->x44->x76 = 0;
    p->x44->x75 = 0;
    fn_800A4B00(p->x44, p->act[0]);
    {
    Vec3 r = { 0.0f, -90.0f, 0.0f };
    c = p->x44; c->rot = r;
    }
    fn_800A4420(p->x44, fn_800A8324("\x83N\x83\x89\x83X\x8f\xe3\x8b\x89"), -1);
    fn_800A5D34(p->x44, 1);
    {
    q = fn_800E3810("EID_CLASSCHANGE1", p);
    if (q) {
        W3 w = p->act[0]->pos;
        fn_800E48C8(q, &w);
        fn_800E49AC(q, fn_8001E064(p->act[0]->x58));
        q->g->x18 &= ~0x8000;
        q->g->x4 = 6;
    }
    }
    {
    q2 = fn_800E3810("EID_CLASSCHANGE1_ROOT", p);
    if (q2) {
        W3 w;
        W3 t;
        fn_800B377C(&t, p->act[0], -1);
        w = t;
        fn_800E48C8(q2, &w);
        fn_800E49AC(q2, fn_8001E064(p->act[0]->x58));
        q2->g->x18 &= ~0x8000;
    }
    }
    fn_800A9E64(p, -1, 0x78);
}
}
