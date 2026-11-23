#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct EvX {
    EvProc b;
    f32 f84;   /* 0x84 */
    s16 h88;   /* 0x88 */
    s16 h8A;   /* 0x8A */
} EvX;

typedef struct Seq2 {
    u8 pad[0xB];
    u8 bB;     /* 0x0B */
    u8 bC;     /* 0x0C */
    u8 padD;
    u16 ids[1]; /* 0x0E */
} Seq2;

typedef struct BP2 {
    u8 pad[0x30];
    Seq2* seq; /* 0x30 */
    u8 pad34[0x10];
    u8 b44;    /* 0x44 */
} BP2;

typedef struct Gauge {
    u8 pad[0x3C];
    void* tex; /* 0x3C */
    u8 pad40[7];
    u8 b47;    /* 0x47 */
} Gauge;

extern u8 lbl_8036707C[];
extern u8 lbl_803672A0[];
extern s32 lbl_803E7320[];
extern const f32 lbl_804CD9B8;
extern const f32 lbl_804CD9C0;
extern f32 fn_80176A4C(f32, f32, f32, f32);
extern void fn_801CAD54(void*, void*, int, f32);
#if TARGET_PC
extern FE10_PROTO void fn_801030B8(void*, int, int, int, int, void *);
#else
extern void fn_801030B8(void*, int, int, int, int, int);
#endif
extern void* fn_800E3A10(char*, void*);
extern void* fn_800E3810(char*, void*);
extern void fn_800E48AC(void*, f32, f32, f32);
extern void* fn_800CFD18(void*, int);
extern void* fn_800CFB0C(void*);
#if TARGET_PC
extern FE10_PROTO void fn_80102C6C(void*, char*, int, int, int);
extern FE10_PROTO void fn_80102CD8(void*, void *, void *, void *);
extern FE10_PROTO void fn_80103234(void*, int, int, void *);
#else
extern void fn_80102C6C(void*, char*, int, int, void*);
extern void fn_80102CD8(void*, int, int, int);
extern void fn_80103234(void*, int, int, int);
#endif
extern void fn_800E5878(void*, void*);
extern void fn_80083B78(void*);
extern Handle* fn_801D0784(void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_8010301C(void*, void*, int, int, void *);
#else
extern void fn_8010301C(void*, void*, int, int, void*);
#endif
extern int fn_801CFE78(Seq2*, int);
extern void fn_800EB4AC(BP2*, int);
extern int fn_801D0214(Seq2*, int);
extern int fn_801CFDEC(Seq2*, int);
extern int fn_801D012C(Seq2*, int);
extern void* fn_801D009C(Seq2*, int);
extern int fn_8013B9B0(void);
extern void fn_801CE2F4(void*, int, int);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, void *, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_8007E7DC(u8);
extern void fn_8007E7F4(void);
extern void fn_800800D4(int);
extern void fn_80080430(f32, f32, f32, f32, f32, f32);
extern void fn_80080578(int);
extern void fn_80080308(void);

void fn_800EAEA4(EvProc* p) {
    p->unk70 = fn_80176A4C((f32)p->unk7C, (f32)p->unk7D, (f32)p->unk7E, (f32)p->unk7F);
    fn_801CAD54(p->u78.p, p, 0x14, (f32)p->unk70);
    fn_801030B8(p->actor1, p->unk7C, p->unk7D, 0x18, 0, 0);
}


#pragma use_lmw_stmw on
#pragma use_lmw_stmw off

int fn_800EC46C(BP2* p) {
    int i;
    Seq2* q = p->seq;
    int k;
    i = p->b44;
    if (i >= q->bC) return 0;
    k = q->ids[(u8)i];
    p->b44 = i + 1;
    if (k == 0x3C) return 1;
    if (fn_801CFE78(q, k) == 0) {
        Handle* h;
        fn_800EB4AC(p, k);
        h = fn_801D0784(p->seq, fn_801D0214(p->seq, k));
        if (fn_801CFDEC(p->seq, k) == 0 || (int)p->seq->bB == 1) {
            if (h && fn_801D012C(p->seq, k)) {
                UnitObj* o;
                void* r = fn_801D009C(p->seq, k);
                int t;
                o = h->obj;
                t = fn_8013B9B0();
                if (((u8*)o)[0x48B]) {
                    fn_801CE2F4(r, 9, t);
                } else {
                    fn_801CE2F4(r, 10, t);
                }
            }
        }
    }
    return 1;
}

static inline void Rect(f32 a, f32 b, f32 c, f32 d, int w, int h) {
    fn_80080430(a, b, c, d, (f32)w, (f32)h);
}
static inline void Tex(void* t, int n, int f) { fn_8007E374(t, n, f); }

typedef struct EvY {
    EvProc b;
    f32 f84;
} EvY;
typedef struct EvZ {
    u8 pad[0x6C];
    s8 x6C, y6C;
    u8 pad6E[0xA];
    u8* o;     /* 0x78 */
    s8 x0, y0, x1, y1; /* 0x7C */
    f32 z0;    /* 0x80 */
    f32 z1;    /* 0x84 */
} EvZ;
extern u8 lbl_803CA870[];
extern u8 lbl_803EC898[];
extern const f32 lbl_804CD928;
extern const f32 lbl_804CD92C;
extern void* fn_8013B9A8(void);
extern u8* fn_80135A54(void*, int, int, int, int);
extern void fn_80083DC4(void*, int);
extern f32 fn_801142F0(void*, f32, f32);
extern void fn_800E24F8(char*);
extern void fn_800F6604(void*, char*);
extern f32 fn_80313508(Vec*);
extern void fn_800E4AD4(EvCmd*, f32);
extern void fn_800E49AC(EvCmd*, f32);
void fn_800E9DA4(EvCmd*);
void fn_800E9DF0(EvCmd*);

void fn_800EA224(EvY* p) {
    Vec v = {0.0f, 0.0f, 0.0f};
    f32 d;
    f32 a;
    EvCmd* c;
    v.x = (f32)(p->b.unk7E - p->b.unk7C);
    v.y = (f32)(p->b.unk7F - p->b.unk7D);
    d = fn_80313508(&v);
    p->f84 = d;
    p->b.unk82 = lbl_804CD928 * p->f84;
    if (p->b.unk82 <= 0) p->b.unk82 = 1;
    p->b.unk80 = 0;
    a = fn_80176A4C((f32)p->b.unk7C, (f32)p->b.unk7D, (f32)p->b.unk7E, (f32)p->b.unk7F);
    c = fn_800E3810((char*)lbl_8036707C + 0x196, p);
    if (c) {
        c->ctl->onUpdate = fn_800E9DA4;
        c->ctl->onEvent = fn_800E9DF0;
        c->ctl->flags |= 0x801;
        fn_800E4AD4(c, lbl_804CD92C);
        fn_800E49AC(c, a);
    }
}
