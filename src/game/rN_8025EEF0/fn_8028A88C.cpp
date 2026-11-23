/* Classic controller cursor emulation and capture loop (never returns) */
#define RN_FLAGS_PLAIN
#include "game/rN_8025EEF0/calls.h"

extern "C" {

struct KPad {
    u8 pad0[0x20];
    f32 x20; f32 x24;
    u8 pad28[0x5E - 0x28];
    s8 x5E;
    u8 pad5F;
    u32 x60;
    u8 pad64[0x6C - 0x64];
    f32 x6C; f32 x70;
    u8 pad74[0x84 - 0x74];
};
struct Cur { KPad* p; f32 x; f32 y; int mode; };
extern int lbl_804CC108;
class PadObj {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5C(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74();
    virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9C(); virtual void vA0(); virtual void vA4();
    virtual void vA8(); virtual void vAC();
};
PadObj* fn_8007B594(int i);
void fn_80348D9C(int wide);
void fn_80348B98(void);
void* fn_8031F69C(void);
void fn_80320548(void* thread);
int fn_80022698(void);
void fn_80302B34(void);
int fn_80336D18(int i, u32* type);
int fn_8030CBF8(int i, KPad* k, int n);
int fn_80348BCC(Cur* c);
void fn_8023550C(void);
void fn_8002230C(void);
void fn_8028A540(void* tex);
void fn_80304314(int a, int b, int c);
void fn_80312F48(void* m, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void fn_80307D98(void* m, int a);
void fn_80021B68(int a);
void fn_80348C1C(void);
void fn_802355D4(void);
void fn_80348DB0(void);
void fn_8017FA40(void);
void fn_8008A15C(void);
}

#if TARGET_PC
/* Host: no write-gather pipe at 0xCC008000 yet (GX FIFO, P3/Aurora); writes go to a dummy */
static volatile s16 WGPIPE;
#else
volatile s16 WGPIPE : 0xCC008000;
#endif
static u8 sTex[0x60];
static u32 sType[4];
static u8 sPad0[0x10];
static KPad sKp[4][16];
static u8 sPad[0x70];
static Cur sCur[4];


#if TARGET_PC
/* Host: OSInitFastCast, fe10/gekko.h */
static inline void FastCast(void) { fe10_fastcast_init(); }
#else
static inline void FastCast(void) {
    asm {
        li r3, 4
        oris r3, r3, 4
        mtspr 0x392, r3
        li r3, 5
        oris r3, r3, 5
        mtspr 0x393, r3
        li r3, 6
        oris r3, r3, 6
        mtspr 0x394, r3
        li r3, 7
        oris r3, r3, 7
        mtspr 0x395, r3
    }
}
#endif

static inline void dpad(Cur* c, BOOL& r) {
    f32 o = 1.0f;
    f32 k = 28.444445f;
    f32 e;
    f32 d;
    d = o / k;
    e = 0.7071f * d;
    switch (c->p->x60 & 0xC003) {
    case 1: c->y -= d; break;
    case 2: c->x -= d; break;
    case 0x4000: c->y += d; break;
    case 0x8000: c->x += d; break;
    case 3: c->y -= e; c->x -= e; break;
    case 0x8001: c->y -= e; c->x += e; break;
    case 0x4002: c->y += e; c->x -= e; break;
    case 0xC000: c->y += e; c->x += e; break;
    default: r = 0; return;
    }
    if (c->x > 1.0f) c->x = 1.0f;
    if (c->x < -1.0f) c->x = -1.0f;
    if (c->y > 1.0f) c->y = 1.0f;
    if (c->y < -1.0f) c->y = -1.0f;
    r = 1;
}
static inline void stick(Cur* c, BOOL& r) {
/*P*/
    f32 t1;
    f32 t2;
    f32 b;
    f32 a0;
    f32 b0;
    f32 a;
    KPad* p;
/*E*/
    p = c->p;
    a0 = p->x6C;
    b0 = p->x70;
    t1 = __fabs(a0);
    if (t1 > 0.11111111f) a = a0 / 28.444445f; else a = 0.0f;
    t2 = __fabs(b0);
    if (t2 > 0.11111111f) b = b0 / 28.444445f; else b = 0.0f;
    if (0.0f == a && 0.0f == b) { r = 0; return; }
    c->x += a;
    if (c->x > 1.0f) c->x = 1.0f;
    if (c->x < -1.0f) c->x = -1.0f;
    c->y -= b;
    if (c->y > 1.0f) c->y = 1.0f;
    if (c->y < -1.0f) c->y = -1.0f;
    r = 1;
}
static inline void update(Cur* c) {
    BOOL a;
    BOOL b;
    dpad(c, a);
    stick(c, b);
    if (!(a | b) && c->p->x5E > 0) {
        c->x = c->p->x20;
        c->y = c->p->x24;
    }
}

extern "C" void fn_8028A88C(void) {
    int cnt[4];
    int st[4];
    u8 m[0x40];
/*P*/
    int j;
    u32* ty;
    int* ps;
    KPad* pk;
    int* pc;
    Cur* c;
    int i;
    int hw;
    int nh;
    int t;
    int e0;
    int e1;
/*E*/
    lbl_804CB700 |= 0x100000;
    for (i = 0; i < 4; i++) fn_8007B594(i)->vAC();
    FastCast();
    fn_80348D9C(fn_801D09F0());
    fn_80348B98();
    for (i = 0; i < 4; i++) {
        sCur[i].x = 0.0f;
        sCur[i].y = 0.0f;
        sCur[i].mode = 0xFD;
    }
    hw = (fn_801D09F0() ? 0x31C : 0x260) >> 1;
    nh = -hw;
    for (;;) {
        while (fn_80022698()) {
            fn_80320548(fn_8031F69C());
        }
        fn_80302B34();
        FastCast();
        ty = sType;
        ps = st;
        pk = sKp[0];
        pc = cnt;
        c = sCur;
        for (j = 0; j < 4; j++, ty++, ps++, pk += 16, pc++, c++) {
            *ps = fn_80336D18(j, ty);
            *pc = fn_8030CBF8(j, pk, 0x10);
            if (*ps == 0 && *pc <= 0) *ps = -2;
            switch (*ps) {
            case -7: case -3: case -2: case 0:
                c->p = pk;
                if (*ty == 2) update(c);
                break;
            default:
                c->p = 0;
                break;
            }
            c->mode = lbl_804CC108;
            switch (*ty) {
            case 0: case 1:
                c->mode = 0;
                break;
            case 2:
                c->mode = 2;
                update(c);
                break;
            default:
                c->mode = 0xFD;
                break;
            }
        }
        if (fn_80348BCC(sCur) >= 0) break;
        {
            fn_8023550C();
            fn_8002230C();
            fn_8028A540(sTex);
            fn_80304314(0x98, 7, 4);
            WGPIPE = 0; WGPIPE = 0; WGPIPE = 0; WGPIPE = 0;
            WGPIPE = 0x260; WGPIPE = 0; WGPIPE = 1; WGPIPE = 0;
            WGPIPE = 0; WGPIPE = 0x1C0; WGPIPE = 0; WGPIPE = 1;
            WGPIPE = 0x260; WGPIPE = 0x1C0; WGPIPE = 1; WGPIPE = 1;
            e0 = 0xE0;
            e1 = -0xE0;
            fn_80312F48(m, e0, e1, nh, hw, 0.0f, 0.1f);
            fn_80307D98(m, 1);
            fn_80021B68(0);
            fn_80348C1C();
            fn_8002230C();
            fn_802355D4();
            fn_80348DB0();
            fn_8017FA40();
            fn_8008A15C();
        }
    }
}
