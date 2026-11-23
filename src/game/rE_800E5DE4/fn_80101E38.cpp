#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef struct Probe { u8 pad[0x30]; void* a; } Probe;
typedef struct Opt { u8 pad[4]; u32 hi : 6; u32 mode : 2; u32 rest : 24; } Opt;

class Pad {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual u32 Held();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void Rumble(int);
};

typedef struct R1E38 { u8 pad[0x30]; MapUnit* u; u16 h34; u8 pad36[2]; s32 x; s32 y; } R1E38;
typedef struct R2438 { u8 pad[0x30]; MapUnit* u; u8 b34; u8 b35; u8 b36; } R2438;
typedef struct R2CD8 { u8 pad[0x30]; MapUnit* u; void* a; void* b; u8 pad3C[4]; s16 h40; } R2CD8;

extern "C" {
extern u8 lbl_803CAB38[];
extern u8 lbl_80385070[];
extern Pad* lbl_804CB5B8;
extern void fn_80104A70(void* a, void* b);
extern void* fn_800893E4(void*, void*, Probe*);
extern void* fn_80081050(void*, void*);
extern void fn_800F3B50(MapUnit*, f32, f32);
extern void fn_800F3F08(MapUnit*, int);
extern void fn_800F3F14(MapUnit*, f32);
extern void fn_800E4548(void);
extern int fn_800FAE98(MapUnit*);
extern void fn_80083B78(void*);
extern Opt* fn_80060728(void*);
extern void fn_800F74D0(MapUnit*, int);
extern void fn_800F39DC(MapUnit*);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_800F0994(char*);
#else
extern void* fn_800F0994(char*);
#endif
#if TARGET_PC
extern FE10_PROTO p32ret fn_80102E10(MapUnit*, ptr32<const void>, void*, f32, void*);
#else
extern int fn_80102E10(MapUnit*, void*, void*, f32, void*);
#endif

void fn_80101E38(R1E38* p) {
    switch (p->h34 & 3) {
    case 0:
    case 1:
        fn_800F3B50(p->u, 0.5f + (f32)p->x, 0.5f + (f32)p->y);
        fn_800F3F08(p->u, 0xFF);
        break;
    case 2:
        fn_800F3F08(p->u, 0);
        break;
    }
    fn_800E4548();
}

static inline BOOL Boost(R2438* p) {
    if (p->b36) {
        if (lbl_804CB5B8->Held() & 0xFFF0) return 1;
        if (fn_80060728(lbl_803CAB38)->mode == 2) return 1;
    }
    return 0;
}
void fn_80102438(R2438* p) {
    fn_800F3F14(p->u, 1.0f);
    if (fn_800FAE98(p->u)) {
        fn_80083B78(p);
        return;
    }
    if (Boost(p)) {
        fn_800F3F14(p->u, 2.0f);
    }
}

void fn_8010258C(R2438* p) {
    fn_800F3F14(p->u, 1.0f);
    if (p->b35 == 0) {
        p->u->flags |= 4;
        fn_800F74D0(p->u, 0);
        p->u->flags &= ~4;
        fn_800F39DC(p->u);
    }
    if (p->b34) {
        fn_800F3F08(p->u, 0xFF);
    }
}

static inline void* Make2CD8(MapUnit* u, void* a, void* b, void* parent) {
    Probe s;
    R2CD8* q;
    s.a = u;
    fn_800893E4(lbl_80385070, fn_80104A70, &s);
    if (parent == 0) parent = (void*)3;
    q = (R2CD8*)fn_80081050(lbl_80385070, parent);
    q->u = u;
    q->a = a;
    q->b = b;
    q->h40 = 0x20;
    return q;
}
void* fn_80102CD8(MapUnit* u, void* a, void* b, void* parent) {
    Probe s;
    R2CD8* q;
    s.a = u;
    fn_800893E4(lbl_80385070, fn_80104A70, &s);
    if (parent == 0) parent = (void*)3;
    q = (R2CD8*)fn_80081050(lbl_80385070, parent);
    q->u = u;
    q->a = a;
    q->b = b;
    q->h40 = 0x20;
    return q;
}
void* fn_80102D70(MapUnit* u, char* name, void* b, void* parent) {
    return Make2CD8(u, fn_800F0994(name), b, parent);
}

static inline int DirAngle(u8 c) {
    int n;
    switch (c) {
    case 4: n = 0; break;
    case 6: n = 0x2D; break;
    case 2: n = 0x5A; break;
    case 10: n = 0x87; break;
    case 8: n = 0xB4; break;
    case 9: n = 0xE1; break;
    case 1: n = 0x10E; break;
    case 5: n = 0x13B; break;
    default: n = 0; break;
    }
    return n;
}
int fn_8010316C(MapUnit* u, int c, void* a, void* b, void* d) {
    if (c == 0x40 || c == 0) return 0;
    return fn_80102E10(u, a, b, (f32)DirAngle(c), d);
}

extern u8 lbl_80367D50[];
extern u8 lbl_8038536C[];
extern u8 lbl_803EC898[];
extern void* fn_800811E4(void*, void*);
extern int fn_80008C98(void*, int);
extern f32 fn_800FB08C(MapUnit*, MapUnit*);
extern f32 fn_80113F00(void*, f32, f32);
extern f32 fn_80176A4C(f32, f32, f32, f32);
extern int fn_8028DB44(int);
extern void* fn_800E3810(char*, void*);
extern void fn_800E48AC(void*, f32, f32, f32);
extern void fn_800E49AC(void*, f32);
extern void fn_802549C4(char*, Vec, f32);
extern void fn_8013C14C(int, int, void*, f32);

typedef struct R0C70 {
    u8 pad[0x30];
    MapUnit* u;   /* 0x30 */
    MapUnit* q;   /* 0x34 */
    s32 x0, y0;   /* 0x38 */
    s32 x1, y1;   /* 0x40 */
    u8 b48;
    u8 pad49[3];
    void (*cb)(void*); /* 0x4C */
    void* arg;    /* 0x50 */
    u8 pad54;
    u8 b55;
} R0C70;

static inline f32 AngTo(MapUnit* u, f32 x, f32 y) {
    return fn_80176A4C(u->x, u->y, x, y);
}
}
