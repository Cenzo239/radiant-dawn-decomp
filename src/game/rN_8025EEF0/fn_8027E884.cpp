/* War record row text */
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

extern char lbl_8037387C[];
void fn_80080330(f32 x, f32 y);
void fn_80080508(C4* c);
void fn_80080B00(f32 s, int a, C4* c);
void fn_80080C24(const char* s);
void* fn_8010B094(int a);
const char* fn_8009285C(void* p);
const char* fn_80092904(void* p);
const char* fn_80092958(void* p);
C4* fn_800CD204(int i);
int fn_800CA3DC(const char* s, int a, f32 v);

static const C4 k0 = {0, 0, 0, 0xFF};
static const C4 k1 = {0, 0, 0, 0xFF};
static const C4 k2 = {0, 0, 0, 0xFF};
static const C4 k3 = {0, 0, 0, 0xFF};
static const C4 k4 = {0, 0, 0, 0xFF};
static const C4 k5 = {0xD8, 0xB8, 0x80, 0xFF};
static const C4 k6 = {0xA9, 0xEB, 0xDB, 0xFF};

struct WarRow { u8 id; u8 pad; u16 m2; u32 m4; };

static inline void sh(C4 c) { fn_80080B00(1.0f, 1, &c); }
static inline void col0(const C4& p) { C4 c = p; fn_80080508(&c); }
static inline void col(const C4& p) { col0(p); }

static inline s16 xpos(void) {
    if ((s8)fn_8024BC94()[0x1BC8] == 0) {
        return 0xC1;
    } else {
        int r = fn_801D09F0();
        int x = 0xEC;
        if (r != 0) x = 0xD7;
        return x;
    }
}
static inline void colp0(const C4* p) { C4 c = *p; fn_80080508(&c); }
static inline void colp(const C4* p) { colp0(p); }

void fn_8027E884(WarRow* e) {
    char buf[0x40];
/*P*/
    u16 n;
    const char* s;
    const char* s1;
    const char* s3;
    void* v;
    u32 t;
    int x;
/*E*/
    v = fn_8010B094(e->id);
    n = e->m2;
    t = e->m4;
    s1 = fn_8009285C(v);
    fn_800800D4(5);
    fn_80080330(52.0f, 7.0f);
    col(k5);
    sh(k0);
    fn_80080C24(s1);
    fn_80080308();
    s = fn_80092904(v);
    fn_800CA3DC(s, -1, 1.0f);
    fn_800800D4(5);
    if ((s8)fn_8024BC94()[0x1BC8] == 0) {
        x = (s16)(0x84 + (s16)(0x32 - fn_800CA3DC(s, -1, 1.0f)));
    } else {
        x = 0x8C;
    }
    fn_80080330(x, 7.0f);
    colp(fn_800CD204(1));
    sh(k1);
    fn_80080C24(s);
    fn_80080308();
    s3 = fn_80092958(v);
    fn_800800D4(5);
    fn_80080330(xpos(), 7.0f);
    sh(k2);
    fn_80080C24(s3);
    fn_80080308();
    if (n > 9999) {
        fn_80290DDC(buf, lbl_8037387C);
    } else {
        fn_80290DDC(buf, lbl_8037387C + 5, n);
    }
    if (n > 999) {
        x = -4;
    } else {
        x = 0x21 - fn_800CA3DC(buf, -1, 1.0f);
    }
    fn_800800D4(5);
    fn_80080330(x + 0x15A, 31.0f);
    sh(k3);
    fn_80080C24(buf);
    fn_80080308();
    if (t > 360000) {
        fn_80290DDC(buf, lbl_8037387C + 8);
    } else {
        fn_80290DDC(buf, lbl_8037387C + 0x11, t / 3600, t % 3600 / 60, t % 60);
    }
    fn_800800D4(5);
    fn_80080330(458.0f, 31.0f);
    col(k6);
    sh(k4);
    fn_80080C24(buf);
    fn_80080308();
}

}
