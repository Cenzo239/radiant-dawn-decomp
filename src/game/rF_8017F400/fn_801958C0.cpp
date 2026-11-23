#include "game/rF_8017F400/types.h"

extern "C" {

/* file menu globals (see fn_801945C0.cpp) */

/* 2D mover: current position tweened from -> to over dur frames */
typedef struct Mover {
    s16 flags; /* 0x0 */
    u8 pad2[4];
    s16 x;     /* 0x6 */
    s16 y;     /* 0x8 */
    s16 fromX; /* 0xa */
    s16 fromY; /* 0xc */
    s16 toX;   /* 0xe */
    s16 toY;   /* 0x10 */
    s16 t;     /* 0x12 */
    s16 dur;   /* 0x14 */
} Mover;

/* window rect with mover (x/y at +8/+a) */
typedef struct Mover2 {
    s16 flags; /* 0x0 */
    u8 pad2[6];
    s16 x;     /* 0x8 */
    s16 y;     /* 0xa */
    s16 fromX; /* 0xc */
    s16 fromY; /* 0xe */
    s16 toX;   /* 0x10 */
    s16 toY;   /* 0x12 */
    s16 mode;  /* 0x14 */
    s16 t;     /* 0x16 */
    s16 dur;   /* 0x18 */
    s16 a0;    /* 0x1a */
    s16 a1;    /* 0x1c */
    s16 a2;    /* 0x1e */
    s16 at;    /* 0x20 */
    s16 adur;  /* 0x22 */
    u8 pad24[4];
} Mover2;

/* window anim (0x28 bytes, g->win[]) */
typedef struct WinAnim {
    s16 flags; /* 0x0 */
    u8 pad2[4];
    s16 x;     /* 0x6 */
    s16 y;     /* 0x8 */
    s16 fromX; /* 0xa */
    s16 toX;   /* 0xc */
    s16 fromY; /* 0xe */
    s16 toY;   /* 0x10 */
    s16 mode;  /* 0x12 */
    s16 t;     /* 0x14 */
    s16 dur;   /* 0x16 */
    s16 a0;    /* 0x18 */
    s16 a1;    /* 0x1a */
    s16 a2;    /* 0x1c */
    s16 at;    /* 0x1e */
    s16 adur;  /* 0x20 */
} WinAnim;

/* 0..1 fade pair */
typedef struct Fade2 {
    s16 a;     /* 0x0 */
    s16 b;     /* 0x2 */
    s16 fromA; /* 0x4 */
    s16 toA;   /* 0x6 */
    s16 fromB; /* 0x8 */
    s16 toB;   /* 0xa */
    s16 t;     /* 0xc */
    s16 dur;   /* 0xe */
    s16 x10;   /* 0x10 */
} Fade2;

typedef struct ModelNode {
    u8 pad[8];
    s16 x8;    /* 0x8 */
    u8 padA[0x18 - 0xA];
    u32 flags; /* 0x18 */
} ModelNode;

typedef struct Model {
    u8 pad[0x30];
    ModelNode* node; /* 0x30 */
} Model;

/* 0x7c-byte entry */
typedef struct FMEntry {
    s16 flags;
    u8 pad[0x7C - 2];
} FMEntry;

/* 0x1c-byte rank-marker entry */
typedef struct FMMarker {
    s16 flags;
    s16 hidden; /* 0x2 */
    s16 idx;    /* 0x4 */
    s16 x6;
    s16 x8;
    s16 xa;
    s16 xc;
    s16 xe;
    s16 x10;
    s16 x12;
    s16 x14;
    u8 pad16[2];
    Model* model; /* 0x18 */
} FMMarker;

typedef struct FMGlobal {
    u32 flags; /* 0x0 */
    int x4;
    int x8;
    u8 padc[0x15 - 0xC];
    u8 x15;
    u8 pad16[2];
    u8 x18;
    u8 pad19[3];
    int mode;  /* 0x1c */
    char text[0x80 - 0x20]; /* 0x20 */
    char* msg; /* 0x80 */
    u8 pad84[0x8C - 0x84];
    u8 x8c;
    u8 x8d;
    u8 x8e;
    u8 pad8f;
    s16 x90;
    u8 pad92[2];
    int x94;
    int x98;
    Fade2 fade;      /* 0x9c */
    u8 padae[2];
    Mover2 win[6];   /* 0xb0 */
    FMEntry ent[6];  /* 0x1a0 */
    u8 cur[0x28];    /* 0x488 */
    FMMarker mark[2]; /* 0x4b0 */
} FMGlobal;

extern FMGlobal* lbl_804CB934;
extern char lbl_80388864[0xF]; /* "EID_DRAGONBALL" */
extern Model* fn_800E3C04(const char* name, void* archive);
extern void fn_800E4AD4(Model* m, f32 v);
extern void* memset(void* p, int c, u32 n);

/* u8 tween (alpha) */
typedef struct Tween8 {
    u8 cur;  /* 0x0 */
    u8 from; /* 0x1 */
    u8 to;   /* 0x2 */
    u8 pad3;
    s16 z;   /* 0x4 */
    u8 pad6[2];
    int t;   /* 0x8 */
    int dur; /* 0xc */
} Tween8;

extern f32 fn_8017F68C(int mode, f32 from, f32 to, f32 t, f32 d); /* interpolate */
extern void* fn_801947D4(void);
extern void* fn_801947E0(void);
extern void* fn_801947EC(int i);
extern void* fn_80194800(int i);
extern void* fn_80194814(void);
extern void* fn_80194820(int i);
extern void fn_80194644(void);
extern void fn_80194840(void);
extern void fn_8019467C(int a, int b, int c, f32 x, f32 y);
extern void fn_8019555C(void* c);

void fn_80197DF0(Tween8* p);
void fn_80197EA0(Fade2* f);
void fn_80197FC8(WinAnim* m);
void fn_80198180(Mover2* m);
void fn_80198338(Mover* m);



extern void fn_8019846C(void* p);
void fn_801985DC(Tween8* p);
extern void fn_801986C4(void* p);
extern void fn_80198CC0(void* p);
extern void fn_8019A82C(void* p);
void fn_8019AD58(FMMarker* m);
extern void fn_801BCA5C(f32 z);
extern void fn_801BCA94(void);
extern void fn_800800D4(int x);
extern void fn_80080330(f32 x, f32 y);
extern void fn_800804D4(int r, int g, int b, int a);
extern void fn_80080A94(f32 s);
extern char* fn_800D0864(const char* id);
extern void fn_80080C24(char* s);
extern void fn_80080308(void);
extern void fn_801C6D9C(char* s, int a, int b, int c);
typedef s64 OSTime;
extern OSTime OSGetTime(void);
#define OS_BUS_CLOCK (*(u32*)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
extern double fn_80295940(double x); /* sin */
extern void fn_800E57B4(Model* m, int x, int y);
extern void fn_800712E8(int x, int y, int a);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int b);
#else
extern void fn_8007E174(int a, int b);
#endif
extern void fn_80080388(f32 x0, f32 y0, f32 x1, f32 y1);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32 x, f32 y, f32 z, f32 w);
extern s16 lbl_804CB93C;
extern s16 lbl_804CB93E;
extern int lbl_804CB940;
extern u8 lbl_803886EC[0x34];
extern u8 lbl_80388798[0x34];
extern void* fn_80081194(void* cls, void* parent);
#if TARGET_PC
extern FE10_PROTO int fn_802F4318(int a, int b, p32arg);
#else
extern int fn_802F4318(int a, int b, int c);
#endif
extern void fn_80283AC0(void);

void* fn_801958C0(void* parent)
{
    return fn_80081194(lbl_803886EC, parent);
}

static inline void FM_CardChanged(void)
{
    lbl_804CB93C = 100;
    lbl_804CB934->flags &= ~8;
    fn_80283AC0();
}

void fn_801958D0(void)
{
    if (lbl_804CB934->flags & 4) {
        int r = fn_802F4318(0, 0, 0);
        if (r != -1) {
            if (lbl_804CB940 != 0xFFFF) {
                if (lbl_804CB940 == -3 && (r == -2 || r == 0)) {
                    FM_CardChanged();
                }
                if ((lbl_804CB940 == -2 || lbl_804CB940 == 0) && r == -3) {
                    FM_CardChanged();
                }
            }
            lbl_804CB940 = r;
        }
    }
}

void fn_80196DC8(Mover* m)
{
    m->flags = 0;
}

void fn_80196DD4(Mover* m, s16 x, s16 y, s16 t)
{
    m->fromX = m->x;
    m->fromY = m->y;
    m->toX = x;
    m->toY = y;
    m->dur = t;
    m->t = t;
    if (t == 0) {
        m->x = x;
        m->y = y;
    }
    m->flags |= 1;
}

void fn_801977E0(Mover2* m, s16 x, s16 y, s16 t, s16 mode)
{
    m->fromX = m->x;
    m->fromY = m->y;
    m->toX = x;
    m->toY = y;
    m->dur = t;
    m->t = t;
    if (mode != -1) {
        m->mode = mode;
    }
    if (t == 0) {
        m->x = x;
        m->y = y;
    }
    m->flags |= 1;
}

void fn_8019782C(Mover2* m, int t)
{
    m->a0 = 0;
    m->a1 = 0;
    m->a2 = 0xFF;
    m->adur = t;
    m->at = t;
    if (m->at == 0) {
        m->a0 = 0xFF;
    }
}

void fn_80197858(Mover2* m, BOOL on)
{
    if (on) {
        m->flags |= 2;
    } else {
        m->flags &= ~2;
    }
}

void fn_80197880(Mover* m, Mover2* ref, s16 t)
{
    fn_80196DD4(m, ref->x - 0x10, ref->y + 0x1A, t);
}

s16 fn_801978D8(Mover2* m)
{
    return m->x;
}

s16 fn_801978E0(Mover2* m)
{
    return m->y;
}

void fn_801978E8(void)
{
    lbl_804CB93C = 0;
    lbl_804CB93E = 1;
    lbl_804CB940 = 0xFFFF;
}

void fn_80197908(void)
{
    lbl_804CB934->mode = 2;
}

void* fn_80197918(void* parent)
{
    return fn_80081194(lbl_80388798, parent);
}

static inline void Fade2_Out(Fade2* f, s16 t)
{
    f->fromA = f->a;
    f->fromB = f->b;
    f->toA = 0;
    f->toB = 1;
    f->dur = t;
    f->t = t;
    if (t == 0) {
        f->a = 0;
        f->b = 1;
    }
}

static inline void Fade2_Init(Fade2* f)
{
    memset(f, 0, 0x12);
    f->x10 = 0;
    Fade2_Out(f, 0);
}

static inline void Mover2_Init(Mover2* m)
{
    memset(m, 0, 0x28);
    m->flags = 0;
}

static inline void FMEntry_Init(FMEntry* e)
{
    memset(e, 0, 0x7C);
    e->flags = 0;
}

static inline void FM_InitMarker(FMMarker* e, int idx, s16 hidden)
{
    e->flags = 1;
    e->hidden = hidden;
    e->idx = idx;
    if (!e->hidden && e->model == NULL) {
        e->model = fn_800E3C04(lbl_80388864, NULL);
        e->model->node->x8 = 0x71;
        fn_800E4AD4(e->model, 0.1f);
        e->model->node->flags |= 0x1004;
    }
    e->x8 = e->xc = e->x10 = -1000;
    e->x6 = e->xa = e->xe = -1000;
    e->x12 = 0;
    e->x14 = 0;
}

void fn_80197928(void)
{
    int i;
    lbl_804CB934->x4 = 0;
    lbl_804CB934->x8 = 0;
    lbl_804CB934->x15 = 0;
    lbl_804CB934->x18 = 0;
    lbl_804CB934->mode = 0;
    lbl_804CB934->msg = 0;
    {
        FMGlobal* g = lbl_804CB934;
        g->x8d = g->x8c;
        g->x8e = 0;
        g->x90 = 0;
        g->x98 = 0;
        g->x94 = 0;
    }
    Fade2_Init(&lbl_804CB934->fade);
    for (i = 0; i < 6; i++) {
        Mover2_Init(&lbl_804CB934->win[i]);
    }
    for (i = 0; i < 6; i++) {
        FMEntry_Init(&lbl_804CB934->ent[i]);
    }
    memset(lbl_804CB934->cur, 0, 0x28);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            FM_InitMarker(&lbl_804CB934->mark[i], i, 0);
        } else {
            FM_InitMarker(&lbl_804CB934->mark[i], i, 1);
        }
    }
}

void fn_80197BAC(Fade2* f, s16 v)
{
    f->x10 = v;
}

void fn_80197BB4(Fade2* f, s16 t)
{
    f->fromA = f->a;
    f->fromB = f->b;
    f->toA = 0;
    f->toB = 1;
    f->dur = t;
    f->t = t;
    if (t == 0) {
        f->a = 0;
        f->b = 1;
    }
}

void fn_80197BF0(void)
{
    int i;
    fn_80197DF0((Tween8*)fn_801947D4());
    fn_80197EA0((Fade2*)fn_801947E0());
    for (i = 0; i < 6; i++) {
        fn_80197FC8((WinAnim*)fn_801947EC(i));
    }
    for (i = 0; i < 6; i++) {
        fn_80198180((Mover2*)fn_80194800(i));
    }
    fn_8019555C(fn_80194814());
    for (i = 0; i < 2; i++) {
        fn_80198338((Mover*)fn_80194820(i));
    }
    fn_80194644();
    if (lbl_804CB934->flags & 2) {
        fn_8019467C(1, 0xFF, 1, 0.0f, 0.0f);
        fn_801BCA5C(-1.0f);
    } else {
        fn_8019467C(1, 0xFF, 0, 0.0f, 0.0f);
        fn_801BCA5C(-1.0f);
        fn_8019846C(fn_801947E0());
    }
    fn_801985DC((Tween8*)fn_801947D4());
    for (i = 0; i < 6; i++) {
        fn_801986C4(fn_801947EC(i));
    }
    for (i = 0; i < 6; i++) {
        fn_80198CC0(fn_80194800(i));
    }
    fn_8019A82C(fn_80194814());
    for (i = 0; i < 2; i++) {
        fn_8019AD58((FMMarker*)fn_80194820(i));
    }
    if (lbl_804CB934->msg != NULL) {
        fn_80194644();
        fn_801BCA5C(-4.0f);
        fn_801BCA94();
        fn_800800D4(5);
        fn_80080330(270.0f, 30.0f);
        fn_800804D4(0xD9, 0xC5, 0x93, 0xFF);
        fn_80080A94(0.8f);
        fn_80080C24(fn_800D0864(lbl_804CB934->msg));
        fn_80080308();
        fn_801BCA5C(4.0f);
    }
    fn_80194840();
    if (lbl_804CB934->text[0] != 0) {
        fn_80194644();
        fn_801BCA5C(-10.0f);
        fn_801C6D9C(lbl_804CB934->text, 0xFF, 0xFF, 0);
        fn_801BCA5C(10.0f);
    }
}

void fn_80197DF0(Tween8* p)
{
    if (p->t > 0) {
        p->t--;
        p->cur = fn_8017F68C(0, p->from, p->to, p->dur - p->t, p->dur);
    }
}

void fn_80197EA0(Fade2* f)
{
    if (f->t > 0) {
        f->t--;
        f->a = fn_8017F68C(4, f->fromA, f->toA, f->dur - f->t, f->dur);
        f->b = fn_8017F68C(4, f->fromB, f->toB, f->dur - f->t, f->dur);
    }
}

void fn_80197FC8(WinAnim* m)
{
    if (m->flags & 1) {
        if (m->t > 0) {
            m->t--;
            m->x = fn_8017F68C(m->mode, m->fromX, m->toX, m->dur - m->t, m->dur);
            m->y = fn_8017F68C(m->mode, m->fromY, m->toY, m->dur - m->t, m->dur);
        }
        if (m->at > 0) {
            m->at--;
            m->a0 = fn_8017F68C(0, m->a1, m->a2, m->adur - m->at, m->adur);
        }
    }
}

void fn_80198180(Mover2* m)
{
    if (m->flags & 1) {
        if (m->t > 0) {
            m->t--;
            m->x = fn_8017F68C(m->mode, m->fromX, m->toX, m->dur - m->t, m->dur);
            m->y = fn_8017F68C(m->mode, m->fromY, m->toY, m->dur - m->t, m->dur);
        }
        if (m->at > 0) {
            m->at--;
            m->a0 = fn_8017F68C(0, m->a1, m->a2, m->adur - m->at, m->adur);
        }
    }
}

void fn_80198338(Mover* m)
{
    if (m->flags & 1) {
        if (m->t > 0) {
            m->t--;
            m->x = fn_8017F68C(4, m->fromX, m->toX, m->dur - m->t, m->dur);
            m->y = fn_8017F68C(4, m->fromY, m->toY, m->dur - m->t, m->dur);
        }
    }
}

static inline void FM_Ortho(void)
{
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 120.0f, 1.0f);
    fn_8007E164();
}

void fn_801985DC(Tween8* p)
{
    FM_Ortho();
    if (p->cur != 0) {
        fn_801BCA5C(p->z);
        fn_8007E154();
        fn_8007E174(0, 0x12);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080388(0.0f, 0.0f, 608.0f, 480.0f);
        fn_800804D4(0, 0, 0, p->cur);
        fn_80080308();
        fn_801BCA5C(-p->z);
    }
}

void fn_8019AD58(FMMarker* m)
{
    if (m->model != NULL) {
        fn_800E57B4(m->model, -1000, -1000);
    }
    if (m->flags & 1) {
        FM_Ortho();
        switch (m->hidden) {
        case 0: {
            f32 off = 6.0f * (f32)fn_80295940(3.141592f * (2.0f * ((f32)((OSGetTime() / (OS_TIMER_CLOCK / 1000)) % 2000) / 2000.0f)));
            if (m->model != NULL) {
                fn_800E57B4(m->model, m->x6, m->x8 + off);
            }
            break;
        }
        case 1:
            fn_801BCA5C(-20.0f);
            fn_800712E8(m->x6, m->x8, 1);
            fn_801BCA5C(20.0f);
            break;
        }
    }
}

}
