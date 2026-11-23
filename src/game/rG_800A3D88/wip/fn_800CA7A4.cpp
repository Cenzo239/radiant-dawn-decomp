// WIP, does not match: 17/231 lines, right size. Only float ranks: the u32 conversion double takes f31 (f26 wanted), rotating m, f, 0.5, s32 double and 1/64 by one. Declaration order has no effect.
#include "game/rG_800A3D88/types.h"

// Text height: tallest scaled line in a string with #-escapes.
extern "C" {
extern void* lbl_803E7260[6];
void* fn_80077DB0(void*);
extern const f32 lbl_804CD630;
extern const f64 lbl_804CD620, lbl_804CD628;
f64 fn_80295AA4(f64, f64);
int fn_800CA1B4(char**, u32);
char* fn_800776F8(char*, int*);
struct Res {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual int v15();
};
extern u8 lbl_804CB6E0[8];
extern u8 lbl_804CB6E8[8];
extern Res* lbl_804CB6F0;
#define RA ((Res*)lbl_804CB6E0)
#define RB ((Res*)lbl_804CB6E8)
static inline int SwapMode(int idx) {
    void* old = fn_80077DB0(lbl_803E7260[idx]);
    int i;
    for (i = 0; i < 6; i++) {
        if (lbl_803E7260[i] == old) return i;
    }
    return -1;
}
int fn_80077BF0();
int fn_800CA7A4(char* s, int idx, f32 f) {
    if (idx == -1) idx = 0;
    int prev = SwapMode(idx);
    int best = 0;
    f32 m = 1.0f;
    Res* save = lbl_804CB6F0;
    while (*s) {
        if (*s++ == '#') {
            switch (*s++) {
            case 'A': case 'B': case 'C': case 'G': case 'I': case 'R': case 'X': case 'x':
                s += 2;
                break;
            case 'P':
                s += 3;
                break;
            case 'K':
                save = lbl_804CB6F0;
                lbl_804CB6F0 = RB ? RB : RA;
                break;
            case 'k':
                lbl_804CB6F0 = save ? save : RA;
                break;
            case 'F':
                {
                    int n = fn_800CA1B4(&s, 2);
                    if (n == -1) n = 0;
                    SwapMode(n);
                }
                break;
            case 'S': case 'Y':
                {
                    f32 v = (u32)fn_800CA1B4(&s, 2) / 64.0f;
                    if (v > m) m = v;
                }
                break;
            case '#': case 'y':
                break;
            }
        } else {
            f32 v = f * (m * (f32)fn_80077BF0());
            f32 d = fn_80295AA4(lbl_804CD620, lbl_804CD628);
            int h = (int)((f32)(int)(d * (v + lbl_804CD630 / d)) / d);
            if (best < h) best = h;
        }
    }
    if (prev == -1) prev = 0;
    SwapMode(prev);
    return best;
}
}
