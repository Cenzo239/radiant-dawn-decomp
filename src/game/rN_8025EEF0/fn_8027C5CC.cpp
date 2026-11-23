/* fn_8027C5CC: exact (round m7). The count-1 value at the end reuses the variable `n` (or `i`: both match) and
 * `#pragma opt_lifetimes off` keeps it in that variable's register (r27). */
/* Conversation room (FE8): support list input */
#include "game/rN_8025EEF0/calls.h"

#pragma opt_lifetimes off
extern "C" {

extern char lbl_8037359C[];
extern u8* lbl_804CC074;
extern u8* lbl_804CC070;
u8* fn_80272A14(void);
u8* fn_80272A8C(void);
u8* fn_80272B08(void);
void fn_8027B144(void);
void fn_8027B568(void);
f32 fn_80272D58(void);
int fn_80272B84(void);
void fn_802732FC(int a, int b, int c);
void fn_80253EE4(const char* s, f32 v);
int fn_80272E3C(void* p);
void fn_80272C68(int v);
f64 fn_8027D748(int v);
void fn_80274790(int a, f32 b);
int fn_802401F4(void* p);
void fn_80272F8C(void* p);
void* fn_8027D710(void* p);
void* fn_8027D718(void* p);
void* fn_8027D720(void* p);
void* fn_8027D730(void* p);
void* fn_8027D738(void* p);
void* fn_8027D740(void* p);
void* fn_8027D700(void* p);
void* fn_8027D708(void* p);
void* fn_8027D728(void* p);

static inline void clampC(u8* q) {
    int c = fn_802401F4(*(u8**)(lbl_804CC074 + 8) + *(s16*)(q + 8) * 0x2C);
    if (fn_80272B84() > c - 1) fn_80272C68(c - 1);
}
static inline void go(f32 v) { fn_802732FC(fn_80272B84(), (int)v, 4); }

static inline int cntm1(void) { return fn_802401F4(*(u8**)(lbl_804CC074 + 8) + *(s16*)(fn_80272A8C() + 8) * 0x2C) - 1; }
static inline void go2(void) { fn_802732FC(fn_80272B84(), (int)fn_80272D58(), 4); }

void fn_8027C5CC(void) {
    void* b[6];
    void* a[6];
    int d2;
    void** pb;
    int held;
    u8* q;
    int i;
    int k;
    int pr;
    void* e;
    s16 old;
    int n;
    pr = lbl_804CB5B8->v48();
    held = lbl_804CB5B8->v3C();
    *(s16*)fn_80272A14() = 2;
    fn_8027B144();
    fn_8027B568();
    if (*(s16*)(fn_80272B08() + 0x1C) > 0) return;
    if (*(s16*)(fn_80272A8C() + 0x12) > 0) return;
    if (pr & 0x800) {
        fn_80253EE4(lbl_8037359C + 0xA2, 0.0f);
        fn_80083DC4(lbl_804CC070, 5);
        return;
    }
    n = *(int*)(lbl_804CC074 + 4);
    if (*(s16*)(fn_80272A8C() + 0xC) != 5) return;
    q = fn_80272A8C();
    if (pr & 0x400) {
        e = *(u8**)(lbl_804CC074 + 8) + *(s16*)(fn_80272A8C() + 8) * 0x2C;
        b[0] = fn_8027D710(e);
        b[1] = fn_8027D718(e);
        b[2] = fn_8027D720(e);
        b[3] = fn_8027D730(e);
        b[4] = fn_8027D738(e);
        b[5] = fn_8027D740(e);
        a[0] = fn_8027D700(e);
        a[1] = fn_8027D700(e);
        a[2] = fn_8027D728(e);
        a[3] = fn_8027D728(e);
        a[4] = fn_8027D708(e);
        a[5] = fn_8027D708(e);
        pb = b;
        k = 0;
        for (i = 0; i < 6; i++, pb++) {
            if (*pb != 0) {
                if (k == fn_80272B84()) {
                    if (fn_80272E3C(a[i])) {
                        fn_80253EE4(lbl_8037359C + 0xCE, 0.0f);
                        fn_80272F8C(b[i]);
                    } else {
                        fn_80253EE4(lbl_8037359C + 0xDE, 0.0f);
                    }
                    break;
                }
                k++;
            }
        }
        return;
    }
    old = *(s16*)(q + 8);
    if (old == 0) {
        if (pr & 0x800008) {
            f32 v;
            *(s16*)(q + 8) = n - 1;
            v = n - 7;
            if (v < 0.0f) v = 0.0f;
            fn_80274790((s16)(int)fn_8027D748(n * 4), v);
            clampC(q);
            go(v);
        }
    } else if (held & 0x800008) {
        f32 v;
        *(s16*)(q + 8) = old - 1;
        if (*(s16*)(q + 8) - (int)fn_80272D58() <= 1 && fn_80272D58() > 0.0f) {
            v = (int)(fn_80272D58() - 1.0f);
            fn_80274790(4, v);
        } else {
            v = (int)fn_80272D58();
        }
        clampC(q);
        go(v);
    }
    if (*(s16*)(q + 8) == n - 1) {
        if (pr & 0x400004) {
            f32 v = 0.0f;
            s16 s;
            *(s16*)(q + 8) = 0;
            s = (int)fn_8027D748(n * 4);
            fn_80274790(s, 0.0f);
            clampC(q);
            go(v);
        }
    } else if (held & 0x400004) {
        f32 v;
        *(s16*)(q + 8) = *(s16*)(q + 8) + 1;
        if (*(s16*)(q + 8) - (int)fn_80272D58() >= 5 && fn_80272D58() < (f32)(n - 7)) {
            v = (int)(1.0f + fn_80272D58());
            fn_80274790(4, v);
        } else {
            v = (int)fn_80272D58();
        }
        clampC(q);
        go(v);
    }
    if (old != *(s16*)(q + 8)) fn_80253EE4(lbl_8037359C + 0xB2, 0.0f);
    if (held & 0x100001) {
        n = fn_802401F4(*(u8**)(lbl_804CC074 + 8) + *(s16*)(fn_80272A8C() + 8) * 0x2C) - 1;
        d2 = fn_80272B84();
        if (d2 != n) {
            fn_80272C68(fn_80272B84() + 1);
            go2();
            fn_80253EE4(lbl_8037359C + 0xB2, 0.0f);
        }
    } else if ((held & 0x200002) && fn_80272B84() > 0) {
        fn_80272C68(fn_80272B84() - 1);
        go2();
        fn_80253EE4(lbl_8037359C + 0xB2, 0.0f);
    }
}

}
