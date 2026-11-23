/* Conversation room: list input */
#include "game/rN_8025EEF0/calls.h"

extern "C" {

extern char lbl_8037359C[];
extern u8* lbl_804CC06C;
extern u8* lbl_804CC068;
u8* fn_80272A14(void);
u8* fn_80272A8C(void);
u8* fn_80272B08(void);
void fn_8027B144(void);
void fn_8027B568(void);
void fn_80274A14(void);
f32 fn_80272D58(void);
int fn_80272B84(void);
void fn_802732FC(int a, int b, int c);
void fn_80253EE4(const char* s, f32 v);
int fn_8027D6F8(void* p);
int fn_80272E3C(int id);
void fn_80272C68(int v);
f64 fn_8027D748(int v);
void fn_80274790(int a, f32 b);
int fn_80274E00(void);

static inline void go(f32 v) { fn_802732FC(fn_80272B84(), (int)v, 4); }
static inline void goK(const f32& v) { fn_802732FC(fn_80272B84(), (int)v, 4); }
static inline void scrollUp(int n, int pr, int held) {
    if (fn_80272B84() == 0) {
        if (pr & 0x800008) {
            f32 v;
            fn_80272C68(n - 1);
            v = n - 7;
            fn_80274790((s16)(int)fn_8027D748(n * 4), v);
            go(v);
        }
    } else if (held & 0x800008) {
        f32 v;
        fn_80272C68(fn_80272B84() - 1);
        if (fn_80272B84() - (int)fn_80272D58() <= 1 && fn_80272D58() > 0.0f) {
            v = (int)(fn_80272D58() - 1.0f);
            fn_80274790(4, v);
        } else {
            v = (int)fn_80272D58();
        }
        go(v);
    }
}
static inline void scrollDown(int n, int pr, int held) {
    if (n - 1 == fn_80272B84()) {
        if (pr & 0x400004) {
            fn_80272C68(0);
            {
                f32 v = 0.0f;
                s16 s = (int)fn_8027D748(n * 4);
                fn_80274790(s, 0.0f);
                go(v);
            }
        }
    } else if (held & 0x400004) {
        f32 v;
        fn_80272C68(fn_80272B84() + 1);
        if (fn_80272B84() - (int)fn_80272D58() >= 5 && fn_80272D58() < (f32)(n - 7)) {
            v = (int)(1.0f + fn_80272D58());
            fn_80274790(4, v);
        } else {
            v = (int)fn_80272D58();
        }
        go(v);
    }
}

void fn_8027BC1C(void) {
/*P*/
    int old;
    int held;
    int pr;
    int n;
/*E*/
    pr = lbl_804CB5B8->v48();
    held = lbl_804CB5B8->v3C();
    *(s16*)fn_80272A14() = 0;
    fn_8027B144();
    fn_8027B568();
    if (*(s16*)(fn_80272B08() + 0x1C) > 0) return;
    if (*(s16*)(fn_80272A8C() + 0x12) > 0) return;
    if (pr & 0x800) {
        fn_80253EE4(lbl_8037359C + 0xA2, 0.0f);
        fn_80083DC4(lbl_804CC068, 3);
    } else if (*(s16*)(fn_80272A8C() + 0xC) == 0) {
        if ((held & 0x800008) && fn_80272B84() != 0) {
            old = fn_80272B84();
            fn_80272C68(fn_80272B84() - 1);
            fn_802732FC(fn_80272B84(), 0, 4);
            if (old != fn_80272B84()) fn_80253EE4(lbl_8037359C + 0xB2, 0.0f);
        } else if ((held & 0x400004) && fn_80272B84() != 1) {
            old = fn_80272B84();
            fn_80272C68(fn_80272B84() + 1);
            fn_802732FC(fn_80272B84(), 0, 4);
            if (old != fn_80272B84()) fn_80253EE4(lbl_8037359C + 0xB2, 0.0f);
        } else if (held & 0x200002) {
            switch (fn_80272B84()) {
            case 0:
                *(s16*)(fn_80272A8C() + 0xC) = 1;
                { int vv = (int)fn_80272D58(); fn_802732FC(fn_80272B84(), vv, 4); }
                break;
            case 1:
                *(s16*)(fn_80272A8C() + 0xC) = 2;
                { int vv = (int)fn_80272D58(); fn_802732FC(fn_80272B84(), vv, 4); }
                break;
            }
            fn_80253EE4(lbl_8037359C + 0xB2, 0.0f);
        }
    } else {
        old = fn_80272B84();
        if (pr & 0x400) {
            if (fn_80274E00()) {
                fn_802732FC(0, 0, 4);
                fn_80253EE4(lbl_8037359C + 0xCE, 0.0f);
                fn_80083DC4(lbl_804CC068, 1);
            }
        } else {
            switch (*(s16*)(fn_80272A8C() + 0xC)) {
            case 1: n = *(int*)(lbl_804CC06C + 0x14); break;
            case 2: n = *(int*)(lbl_804CC06C + 0x1C); break;
            }
            scrollUp(n, pr, held);
            scrollDown(n, pr, held);
            if (old != fn_80272B84()) fn_80253EE4(lbl_8037359C + 0xB2, 0.0f);
            if (held & 0x100001) {
                *(s16*)(fn_80272A8C() + 0xC) = 0;
                fn_802732FC(fn_80272B84(), 0, 4);
                fn_80253EE4(lbl_8037359C + 0xB2, 0.0f);
            }
        }
    }
}

}
