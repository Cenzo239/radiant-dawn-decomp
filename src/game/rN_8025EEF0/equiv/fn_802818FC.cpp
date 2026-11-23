/* r19: `sched` level. The eight gradient colours stand for lbl_804D0830 (sdata2, 8 x 4 bytes); their values were
   all 0xFFFFFFFF in the wip and are now the original bytes (k00 = +0xC ... k03 = +0x0, k10 = +0x1C ... k13 = +0x10).
   The checker cannot verify those references (file statics). */
/* NEAR MISS: all structure right; o should be r23 and end r17 (end ranks above the parameter). */
/* Save record list screen */
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

extern u8 lbl_804D0813;
static const C4 k00 = {0xFF, 0xFF, 0xFF, 0x00};
static const C4 k01 = {0xFF, 0xFF, 0xFF, 0x00};
static const C4 k02 = {0xFF, 0xFF, 0xFF, 0xFF};
static const C4 k03 = {0xFF, 0xFF, 0xFF, 0xFF};
static const C4 k10 = {0xFF, 0xFF, 0xFF, 0xFF};
static const C4 k11 = {0xFF, 0xFF, 0xFF, 0xFF};
static const C4 k12 = {0xFF, 0xFF, 0xFF, 0x00};
static const C4 k13 = {0xFF, 0xFF, 0xFF, 0x00};
extern char lbl_80392BD8[], lbl_80392BBC[], lbl_80392BAC[], lbl_80392BC8[], lbl_80392B98[], lbl_80392B80[], lbl_80392B8C[];
extern char lbl_804CAB48[4], lbl_804CAB40[8], lbl_804CAB38[8], lbl_804CAB30[4], lbl_804CAB2C[4], lbl_804CAB34[4], lbl_804CAB28[4], lbl_804CAB20[4], lbl_804CAB24[4];
void fn_8028270C(void*);
void fn_80080330(f32 x, f32 y);
void fn_80080508(C4* c);
void fn_80080A94(f32 s);
void fn_80080ABC(f32 s, int a);
void fn_80080C24(const char* s);
void fn_8007E74C(void* f, void* a);
void fn_8007E7B4(void);
void fn_80080940(C4* a, C4* b, C4* c, C4* d);
C4* fn_800CD204(int i);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_80070C64(f32 a, f32 b, f32 c, f32 d);
void* fn_8010B1B4(int a);
void fn_800D0AE4(int a, int b);
const char* fn_80118C44(void* p);
void fn_80179888(void* a, u8 b);
void fn_80179A84(void* a);
void fn_801C6D9C(const char* s, int a, int b, int c);

struct Rec {
    u8 pad0[8];
    u8 kind;
    u8 lv;
    s16 id;
    u32 pts;
    u32 pad10;
    u32 time;
};
struct RecScr {
    u8 pad[0x30];
    void* tex;
    u8 pad34[8];
    f32 m3C;
    u8 pad40[0xC];
    u8 m4C;
    u8 m4D;
    u8 pad4E[2];
    void* m50;
    Rec* list;
    int count;
};

static inline void pos(f32 z) {
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, z, 1.0f);
    fn_8007E164();
}
static inline void tex(void* t, int i) {
    fn_8007E154();
    fn_8007E374(t, i, 0x11);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800800D4(1);
}
static inline void pos2(u16 y, f32 z) { fn_8007E4E4(56.0f, y, z, 1.0f); }
static inline void colr(C4 c) { fn_80080508(&c); }
static inline void cola(u8 r, u8 g, u8 b) {
    C4 a;
    C4 c = {r, g, b, 0xFF};
    *(u32*)&a = *(u32*)&c;
    fn_80080508(&a);
}
static inline void grad(C4 d, C4 c, C4 b, C4 a) { fn_80080940(&d, &c, &b, &a); }
static inline void tbegin(f32 x, f32 y) {
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_800800D4(5);
    fn_80080330(x, y);
}
static inline void tend(const C4* p, f32 s, const char* b) {
    C4 c = *p;
    fn_80080508(&c);
    fn_80080A94(s);
    fn_80080ABC(2.0f, 1);
    fn_80080C24(b);
    fn_80080308();
}

void fn_802818FC(RecScr* o) {
    char buf[0x50];
/*P*/
    s8 kind;
    u32 pts;
    int off;
    Rec* e;
    int y;
    int mode;
    u8 lv2;
    void* v;
    int bx;
    u32 tm;
    Rec* end;
    u8 lv;
    void* t;
    u16 w;
/*E*/
    pos(500.0f);
    t = o->tex;
    tex(t, 0);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 608.0f, 448.0f);
    cola(0xFF, 0xFF, 0xFF);
    fn_80080578(0);
    fn_80080308();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 250.0f, 1.0f);
    fn_8007E374(o->tex, 0, 0x11);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800800D4(3);
    fn_80080430(0.0f, 106.0f, 0.0f, 106.0f, 608.0f, 4.0f);
    fn_80080578(0);
    grad(k03, k02, k01, k00);
    fn_80080308();
    fn_800800D4(3);
    fn_80080430(0.0f, 386.0f, 0.0f, 386.0f, 608.0f, 4.0f);
    fn_80080578(0);
    grad(k13, k12, k11, k10);
    fn_80080308();
    pos(475.0f);
    t = o->tex;
    tex(t, 1);
    fn_80080430(17.0f, 14.0f, 0.0f, 0.0f, 310.0f, 42.0f);
    cola(0xFF, 0xFF, 0xFF);
    fn_80080578(0);
    fn_80080308();
    t = o->tex;
    tex(t, 9);
    fn_80080430(0.0f, 62.0f, 0.0f, 0.0f, 608.0f, 608.0f);
    cola(0xFF, 0xFF, 0xFF);
    fn_80080578(0);
    fn_80080308();
    pos(450.0f);
    fn_80290DDC(buf, fn_800D0864(lbl_80392BD8));
    w = fn_800CA3DC(buf, -1, 0.8f);
    tbegin((s16)(0x130 - ((u32)w >> 1)), 67.0f);
    tend(fn_800CD204(0x3E), 0.8f, buf);
    fn_8007E154();
    fn_8007E74C(fn_8028270C, 0);
    fn_8007E164();
    off = 0;
    e = o->list;
    end = e + o->count;
    for (; e != end; e++, off += 0x46) {
        y = (int)(109.0f + o->m3C + (f32)off);
        if ((u16)y + 0x46 >= 0x6D && (u16)y <= 0x182) {
            kind = (s8)e->kind;
            lv = e->lv;
            v = fn_8010B1B4(e->id);
            {
                u32 p0 = e->pts;
                u32 t0 = e->time;
                lv2 = lv > 99 ? 99 : lv;
                pts = 999999; if (p0 <= 999999) pts = p0;
                tm = t0 > 3599999 ? 3599999 : t0;
            }
            fn_8007E154();
            pos2((u16)y, 300.0f);
            fn_8007E164();
            fn_80070C64(0.0f, 0.0f, 496.0f, 67.0f);
            if (kind != -1) {
                bx = (s8)fn_8024BC94()[0x1BC8] == 0 ? 0x1E : 0x1A;
                t = o->tex;
                tex(t, 7);
                fn_80080430(bx, 38.0f, 0.0f, 0.0f, 40.0f, 16.0f);
                cola(0xFF, 0xFF, 0xFF);
                fn_80080578(2);
                fn_80080308();
                t = o->tex;
                tex(t, 8);
                fn_80080430(304.0f, 38.0f, 0.0f, 0.0f, 48.0f, 16.0f);
                cola(0xFF, 0xFF, 0xFF);
                fn_80080578(1);
                fn_80080308();
                fn_8007E154();
                pos2((u16)y, 300.0f);
                fn_8007E164();
                fn_800D0AE4(0, lv2);
                fn_80290DDC(buf, lbl_804CAB48, fn_800D0864(lbl_804CAB40));
                tbegin(bx, 5.0f);
                tend(fn_800CD204(1), 0.8f, buf);
                fn_80290DDC(buf, lbl_804CAB38, fn_80118C44(v));
                tbegin(145.0f, 5.0f);
                tend(fn_800CD204(0x3E), 0.8f, buf);
                switch (kind) {
                case 2:
                    fn_80290DDC(buf, lbl_804CAB34, fn_800D0864(lbl_80392BC8));
                    mode = 0xE;
                    break;
                case 1:
                    fn_80290DDC(buf, lbl_804CAB30, fn_800D0864(lbl_80392BBC));
                    mode = 0xD;
                    break;
                case 0:
                    fn_80290DDC(buf, lbl_804CAB2C, fn_800D0864(lbl_80392BAC));
                    mode = 0xC;
                    break;
                }
                tbegin(372.0f, 5.0f);
                tend(fn_800CD204(1), 0.8f, buf);
                fn_80290DDC(buf, lbl_80392B98, tm / 3600, (tm % 3600) / 60, tm % 60);
                tbegin(104.0f, 32.0f);
                tend(fn_800CD204(1), 1.0f, buf);
                fn_80290DDC(buf, lbl_804CAB28, pts);
                if (pts > 9999) {
                    tbegin(381.0f, 32.0f);
                    tend(fn_800CD204(1), 1.0f, buf);
                } else {
                    u16 pw = fn_800CA3DC(buf, -1, 1.0f);
                    tbegin((s16)(0x1AD - pw), 32.0f);
                    tend(fn_800CD204(1), 1.0f, buf);
                }
                fn_8007E154();
                pos2((u16)y, 400.0f);
                fn_8007E164();
                t = o->tex;
                tex(t, 10);
                fn_80080430(0.0f, 6.0f, 0.0f, 0.0f, 496.0f, 18.0f);
                cola(0xAC, 0xAC, 0xAC);
                fn_80080578(0);
                fn_80080308();
                t = o->tex;
                tex(t, mode);
                fn_80080430(0.0f, 21.0f, 0.0f, 0.0f, 495.0f, 45.0f);
                cola(0xAC, 0xAC, 0xAC);
                fn_80080578(0);
                fn_80080308();
            } else {
                t = o->tex;
                tex(t, 0xB);
                fn_80080430(0.0f, 6.0f, 0.0f, 0.0f, 496.0f, 18.0f);
                cola(0x80, 0x80, 0x80);
                fn_80080578(0);
                fn_80080308();
                t = o->tex;
                tex(t, 0xF);
                fn_80080430(0.0f, 21.0f, 0.0f, 0.0f, 495.0f, 45.0f);
                cola(0x80, 0x80, 0x80);
                fn_80080578(0);
                fn_80080308();
            }
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_80179888(o->m50, o->m4C);
    fn_80179A84(o->m50);
    pos(400.0f);
    if (o->m4D > 4) {
        fn_80290DDC(buf, lbl_804CAB24, fn_800D0864(lbl_80392B8C));
    } else {
        fn_80290DDC(buf, lbl_804CAB20, fn_800D0864(lbl_80392B80));
    }
    fn_801C6D9C(buf, 0xFF, 0xFF, 0);
}

}
