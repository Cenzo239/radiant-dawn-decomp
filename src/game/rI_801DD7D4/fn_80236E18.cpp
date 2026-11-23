#include "game/rI_801DD7D4/fn_thp.h"
#pragma auto_inline off
extern "C" {
extern void (*lbl_804CBF58)(void);
u32 fn_8033119C(void);
int fn_802370F4(void);
#if TARGET_PC
FE10_PROTO ptr32<int> fn_80238184(int);
#else
int* fn_80238184(int);
#endif
extern u8 lbl_80420680[];
#define T lbl_80420420
static inline BOOL startOk(void) {
    if (T.a88 & 1) {
        if (fn_8033119C() == 0) return 1;
    } else if (T.a88 & 2) {
        if (fn_8033119C() == 1) return 1;
    } else {
        return 1;
    }
    return 0;
}
void fn_80236E18(void) {
    int* ts;
    if (lbl_804CBF58 != NULL) lbl_804CBF58();
    ts = (int*)-1;
    if (T.a0 != 0 && T.a4 == 2) {
        if (T.a8 != 0 || T.ac != 0) {
            T.a5 = 5;
            T.a4 = 5;
            return;
        }
        T.c8++;
        if (T.c8 == 0) {
            if (startOk()) {
                if (T.a7 != 0) {
                    if (T.f0 - T.f4 <= 1) {
                        ts = fn_80238184(0);
                        T.f0++;
                    } else {
                        T.a5 = 2;
                    }
                } else {
                    ts = fn_80238184(0);
                }
            } else {
                T.c8 = -1;
            }
        } else {
            if (T.c8 == 1) T.a5 = 2;
            if (fn_802370F4()) {
                if (T.a7 != 0) {
                    if (T.f0 - T.f4 <= 1) {
                        ts = fn_80238184(0);
                        T.f0++;
                    }
                } else {
                    ts = fn_80238184(0);
                }
            }
        }
        if (ts != NULL && ts != (int*)-1) {
            if (T.fc != NULL) fn_8031D284(lbl_80420680, T.fc, 0);
            T.fc = ts;
        }
        if (!(T.a6 & 1)) {
            if (T.a7 != 0) {
                u32 k = T.f4 + T.c0;
                if (k == T.a50 && T.buf == NULL) {
                    T.a5 = 3;
                    T.a4 = 3;
                }
            } else {
                int f;
                if (T.fc != NULL) f = T.fc[3] + T.c0;
                else f = T.c0 - 1;
                if (f == T.a50 - 1 && ts == NULL) {
                    T.a5 = 3;
                    T.a4 = 3;
                }
            }
        }
    }
}
}
