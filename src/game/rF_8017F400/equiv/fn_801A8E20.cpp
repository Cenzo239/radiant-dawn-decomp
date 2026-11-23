/* symcheck: r21 review, flag was an artefact. fn_801A8E20: (a) stale r5 before fn_800800D4(int). See
   docs/SCHED_REVIEW.md. */
/* r19: copied from wip/fn_801A8E20.cpp; `sched` level (same instructions per basic block, order differs). */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
struct TexH { u16 x0, x2; };
struct Fx { int on; u8 p[0x10]; };
struct Win {
    u8 pad[0x10]; int x10; void* x14; void* arch; s8 x1C; s8 x1D[10]; s8 x27[10];
    u8 p31[3];
    f32 x34[10];
    int x5C[3]; /* in fact overlaps */
    u8 p68[8];
    Fx fx[1];
    u8 p84[0xB4];
    f32 x138; void* x13C;
};
extern s8 lbl_804CB978;
extern s16 lbl_804CB980[4];
extern char lbl_8036D360[];
extern s16 lbl_80388F00[];
extern s16 lbl_80388F14[];
extern void fn_801A7D34(void* p, void* arg);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void* fn_80006A0C(void*, int);
extern const u8* fn_800CD204(int);
extern void fn_801BC88C(void* a, int b, C4* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern int fn_800CA3DC(const char*, int, f32);
extern int fn_800CA7A4(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(int, int);
extern void fn_8007E7B4(void);
extern void fn_8007E74C(void (*)(void*, void*), s16*);
extern const char* fn_80118F00(void*);
extern char* strcpy(char*, const char*);
extern int fn_80290DDC(char*, const char*, ...);
extern f32 fn_8017F68C(int a, f32 x, f32 y, f32 t, f32 d);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080508(const C4*);
extern void fn_800804F4(int);
extern void fn_80080A94(f32);
extern void fn_80080B00(int, const u8*, f32);
extern void fn_80080C24(const char*);
extern void fn_80080308(void);
extern void fn_801C6DA0(f32, f32, int, const char*);
extern void fn_801C6D98(f32, f32, int, int);

static inline void Dr1(Win* p, int tile, f32 x, f32 y, f32 ax, f32 ay, f32 sx, f32 sy) {
    C4 c;
    C4 t;
    const u8* cp = fn_800CD204(1);
    c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = 0xFF;
    TexH* q = *(TexH**)fn_80006A0C(p->arch, tile);
    f32 w = q->x2;
    f32 h = q->x0;
    *(u32*)&t = *(u32*)&c;
    f32 x1 = ax * (0.5f * w) + x;
    f32 y1 = ay * (0.5f * h) + y;
    fn_801BC88C(p->arch, tile, &t, 0x11, 0, x1, y1, w * sx + x1, h * sy + y1, 0.0f, 0.0f, w, h);
}
static inline void Dr2(Win* p, int tile, f32 x, f32 y, f32 ax, f32 ay, f32 sx, f32 sy) {
    C4 t;
    C4 c;
    const u8* cp = fn_800CD204(1);
    c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = 0xFF;
    TexH* q = *(TexH**)fn_80006A0C(p->arch, tile);
    f32 w = q->x2;
    f32 h = q->x0;
    *(u32*)&t = *(u32*)&c;
    f32 x1 = ax * (0.5f * w) + x;
    f32 y1 = ay * (0.5f * h) + y;
    fn_801BC88C(p->arch, tile, &t, 0x11, 0, x1, y1, w * sx + x1, h * sy + y1, 0.0f, 0.0f, w, h);
}

static inline void SetC6(void) {
    C4 k2;
    const u8* cp = fn_800CD204(6);
    k2.r = cp[0]; k2.g = cp[1]; k2.b = cp[2]; k2.a = cp[3];
    fn_80080508(&k2);
}

#pragma inline_max_size(8000)
static inline f32 Sc(int v, int a30) { if (v >= 30) return fn_8017F68C(4, 5.0f, 1.0f, 60 - v, a30); return 1.0f; }
static inline void SetR(s16* r, int d, int c, int b, int a) { r[0] = a; r[1] = b; r[2] = c; r[3] = d; }
static inline void Mid(Win* me, f32 x, f32 y, char* buf, C4& k, f32& sca, int& alpha, s16& th1, int& i, s16& w0, s16& tw1, int& tw) {
    int a30;
    s16 h0;
    if (me->x138 >= 0.15f) {
        f32 s2 = me->x138;
        s16* R = lbl_804CB980;
        R[3] = (int)(25.0f * s2); R[1] = (int)(14.0f * (1.0f - s2) + (12.0f + y)); R[0] = (int)x; R[2] = 0x120;
        if (me->x10 != 0) {
            fn_8007E154();
            fn_8007E74C(fn_801A7D34, lbl_804CB980);
            fn_8007E164();
        }
        fn_801BCA94();
        strcpy(buf, fn_80118F00(me->x13C));
        if (me->x10 == 0) fn_800CB3A8(1.0f, 0.0f, (100.0f + x) - 0.5f * fn_800CA3DC(buf, -1, 1.0f), 11.0f + y, 0x38, 1, 0, buf);
        if (me->x10 == 1) fn_800CB3A8(1.0f, 0.0f, (100.0f + x) - 0.5f * fn_800CA3DC(buf, -1, 1.0f), 9.0f + y, 0x38, 1, 0, buf);
        if (me->x10 == 2) fn_800CB3A8(1.0f, 0.0f, (100.0f + x) - 0.5f * fn_800CA3DC(buf, -1, 1.0f), 13.0f + y, 0x38, 1, 0, buf);
        fn_80290DDC(buf, lbl_8036D360 + 0x69, me->x1C);
        {
        w0 = fn_800CA3DC(buf, -1, 1.0f);
        h0 = fn_800CA7A4(buf, -1, 1.0f);
        int m = me->x10;
        if (m == 0) tw = (int)((23.0f + y) - (f32)(h0 / 2));
        if (m == 1) tw = (int)((21.0f + y) - (f32)(h0 / 2));
        if (m == 2) tw = (int)((25.0f + y) - (f32)(h0 / 2));
        fn_800CB3A8(1.0f, 0.0f, (255.0f + x) - (f32)(w0 / 2), tw, 1, 1, 0, buf);
        }
        fn_801BCA5C(-10.0f);
        {
        a30 = 0x1E;
        for (i = 0; i < 3; i++) {
            if (me->x5C[i] > 0) {
                if (me->x5C[i] <= 60) {
                    int v = me->x5C[i] - 1;
                    me->x5C[i] = v;
                    sca = Sc(v, a30);
                    if (me->x5C[i] >= 30) alpha = (int)fn_8017F68C(0, 0.0f, 128.0f, 60 - me->x5C[i], a30);
                    else alpha = (int)fn_8017F68C(0, 128.0f, 0.0f, 30 - me->x5C[i], 30.0f);
                    {
                    tw1 = fn_800CA3DC(buf, -1, sca);
                    th1 = fn_800CA7A4(buf, -1, sca);
                    fn_8007E154();
                    fn_8007E174(0, 0x23);
                    fn_8007E164();
                    fn_800800D4(5);
                    fn_80080330((255.0f + x) - (f32)(tw1 / 2), (23.0f + y) - (f32)(th1 / 2));
                    {
                    const u8* cp = fn_800CD204(1);
                    k.r = cp[0]; k.g = cp[1]; k.b = cp[2]; k.a = cp[3];
                    fn_80080508(&k);
                    }
                    fn_800804F4((u8)alpha);
                    fn_80080A94(sca);
                    fn_80080C24(buf);
                    fn_80080308();
                    }
                } else {
                    me->x5C[i] = me->x5C[i] - 1;
                }
            }
        }
        }
        fn_801BCA5C(10.0f);
        fn_801BCA94();
        if (me->x10 != 0) {
            fn_8007E154();
            fn_8007E7B4();
            fn_8007E164();
        }
    }
}
void fn_801A8E20(Win* p0, f32 x, f32 y, f32 ox, f32 oy) {
    char buf[0x20];
    C4 k;
/*P*/
    s16 tw1;
    s16 th1;
    int alpha2;
    s16 tw2;
    f32 s;
    s16 tw3;
    int i;
    s16 w0;
    int i2;
    f32 sc3;
    f32 sca;
    f32 fx;
    f32 fy;
    int r21;
    int tw2_;
    s16 th3;
    int tw;
    s16 th0;
    int alpha;
    Win* me;
    int cnt;
/*E*/
    me = p0;
    if (!lbl_804CB978) lbl_804CB978 = 1;
    cnt = me->x10 == 0 ? 8 : 10;
    fn_801BCA5C(-3.0f);
    if (me->x10 == 0) {
        s = me->x138;
        Dr1(me, 2, x - 1.0f, y, 0.0f, 1.0f - s, 1.0f, s);
        Dr2(me, 5, ox, oy, 0.0f, 0.0f, 1.0f, 1.0f);
    }
    if (me->x10 == 1) {
        s = me->x138;
        Dr1(me, 3, x, y, 0.0f, 1.0f - s, 1.0f, s);
        Dr2(me, 6, ox, oy, 0.0f, 0.0f, 1.0f, 1.0f);
    }
    if (me->x10 == 2) {
        s = me->x138;
        Dr1(me, 4, x, y, 0.0f, 1.0f - s, 1.0f, s);
        Dr2(me, 7, ox, oy, 0.0f, 0.0f, 1.0f, 1.0f);
    }
    fn_801BCA5C(-1.0f);
    fn_801BCA5C(-1.0f);
    Mid(me, x, y, buf, k, sca, alpha2, th1, i2, w0, tw1, tw2_);
    r21 = me->x10 == 2 ? 4 : 0;
    for (i = 0; i < cnt; i++) {
        Fx* f = &me->fx[i];
        fn_801BCA94();
        if (f->on != 0) { fn_80290DDC(buf, lbl_8036D360 + 0x69, me->x1D[i] + me->x27[i]); }
        else { fn_80290DDC(buf, lbl_8036D360 + 0x69, me->x1D[i]); }
        {
        tw2 = fn_800CA3DC(buf, -1, 1.0f);
        th0 = fn_800CA7A4(buf, -1, 1.0f);
        if (me->x10 == 0) fn_801C6DA0((52.0f + (ox + (f32)lbl_80388F00[i])) - (f32)(tw2 / 2), (f32)r21 + (12.0f + (oy + (f32)lbl_80388F14[i])) - (f32)(th0 / 2), 0x39, buf);
        else fn_800CB3A8(1.0f, 0.0f, (52.0f + (ox + (f32)lbl_80388F00[i])) - (f32)(tw2 / 2), (f32)r21 + (12.0f + (oy + (f32)lbl_80388F14[i])) - (f32)(th0 / 2), 1, 1, 0, buf);
        }
        if (f->on != 0) {
            fn_801BCA5C(-10.0f);
            fn_8007E154();
            fn_8007E174(0, 0x23);
            fn_8007E164();
            {
            tw3 = fn_800CA3DC(buf, -1, me->x34[i]);
            th3 = fn_800CA7A4(buf, -1, me->x34[i]);
            sc3 = me->x34[i];
            alpha = (int)(255.0f * (sc3 - 1.0f));
            fy = (f32)r21 + (12.0f + (oy + (f32)lbl_80388F14[i])) - (f32)(th3 / 2);
            fx = (52.0f + (ox + (f32)lbl_80388F00[i])) - (f32)(tw3 / 2);
            fn_800800D4(5);
            fn_80080330(fx, fy);
            SetC6();
            fn_800804F4((u8)alpha);
            fn_80080B00(1, fn_800CD204(0x2B), 1.0f);
            fn_80080A94(sc3);
            fn_80080C24(buf);
            fn_80080308();
            if (me->x34[i] > 1.0f) {
                me->x34[i] = me->x34[i] - 0.05f;
                if (me->x34[i] < 1.0f) me->x34[i] = 1.0f;
            }
            fn_801BCA5C(10.0f);
            { f32 yb = (f32)r21 + (oy + (f32)lbl_80388F14[i]); f32 xc = 66.0f + (ox + (f32)lbl_80388F00[i]); fn_801C6D98(xc, yb, me->x27[i], 1); }
            }
        }
    }
    fn_801BCA5C(5.0f);
}
}
