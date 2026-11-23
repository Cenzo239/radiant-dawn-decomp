/* Scrolling list: screen draw and auto scroll */
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void* f, void* a);
#endif
void fn_8007E7B4(void);
void fn_80080508(C4* c);
void fn_8027E834(void*);
void fn_8027E85C(void*);
void fn_8027E870(void*);

struct Rows {
    u8 pad[0x34];
    void* tex;
    u8 pad38[4];
    u16 x;
    s16 y;
    s16 wait;
    u8 div;
    s8 step;
    u8 pad44[2];
    u8 cnt;
};

void fn_8027ECA4(Rows* p);

static const C4 k0 = {0, 0, 0, 0xFF};
static const C4 k1 = {0, 0, 0, 0xFF};

static inline void cb(void (*f)(void*)) { if (f != 0) { fn_8007E74C((void*)f, 0); } }

static inline void tex1(void* tex, int i, int fl, void (*f)(void*)) {
    fn_8007E154();
    fn_8007E374(tex, i, fl);
    fn_8007E7DC(0xFF);
    cb(f);
    fn_8007E164();
}
static inline void tex2(void* tex, int i) {
    fn_8007E154();
    fn_8007E374(tex, i, 0x11);
    fn_8007E7DC(0xFF);
    fn_8007E164();
}
static inline void pos(f32 z) {
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, z, 1.0f);
    fn_8007E164();
}
static inline void col(C4 c) { fn_80080508(&c); }

static inline void col0(C4 c) { col(c); }

void fn_8027EFAC(Rows* p) {
    pos(500.0f);
    tex1(p->tex, 0, 1, fn_8027E834);
    fn_800800D4(1);
    fn_80080430(0.0f, 24.0f, 0.0f, 0.0f, 608.0f, 400.0f);
    fn_80080578(0);
    fn_80080308();
    fn_8027ECA4(p);
    pos(300.0f);
    tex1(p->tex, 0, 1, fn_8027E85C);
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 608.0f, 24.0f);
    col0(k0);
    fn_80080578(0);
    fn_80080308();
    tex2(p->tex, 1);
    fn_800800D4(1);
    fn_80080430(0.0f, 24.0f, 0.0f, 0.0f, 608.0f, 80.0f);
    fn_80080578(0);
    fn_80080308();
    tex1(p->tex, 0, 1, fn_8027E870);
    fn_800800D4(1);
    fn_80080430(0.0f, 424.0f, 0.0f, 0.0f, 608.0f, 24.0f);
    col(k1);
    fn_80080578(0);
    fn_80080308();
    tex2(p->tex, 2);
    fn_800800D4(1);
    fn_80080430(0.0f, 400.0f, 0.0f, 0.0f, 608.0f, 24.0f);
    fn_80080578(0);
    fn_80080308();
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    if (p->wait > 0) {
        p->wait--;
    } else if (p->div > p->cnt) {
        p->cnt++;
    } else {
        p->cnt = 0;
        p->y -= p->step;
    }
}

}
