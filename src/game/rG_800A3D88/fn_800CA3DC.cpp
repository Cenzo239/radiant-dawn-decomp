#include "game/rG_800A3D88/types.h"

// Text width: walks a string with #-escapes (colour, scale, font, ruby) and sums the advances.
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
int fn_800CA3DC(char* s, int idx, f32 f) {
    if (idx == -1) idx = 0;
    int prev = SwapMode(idx);
    f32 w = 0.0f;
    f32 m = 1.0f;
    Res* save = lbl_804CB6F0;
    while (*s) {
        int ruby = 0;
        f32 adv;
        if (*s == '#') {
            char* p = s;
            s = p + 2;
            switch (p[1]) {
            case 'A': case 'B': case 'C': case 'G': case 'I': case 'R': case 'Y': case 'y':
                s += 2;
                continue;
            case 'S': case 'X':
                m = (u32)fn_800CA1B4(&s, 2) / 64.0f;
                continue;
            case 'D': case 's': case 'x':
                m = 1.0f;
                continue;
            case '#':
                s--;
                break;
            case 'P':
                s += 3;
                ruby = 1;
                break;
            case 'K':
                save = lbl_804CB6F0;
                lbl_804CB6F0 = RB ? RB : RA;
                continue;
            case 'k':
                lbl_804CB6F0 = save ? save : RA;
                continue;
            case 'F':
                {
                    int n = fn_800CA1B4(&s, 2);
                    if (n == -1) n = 0;
                    SwapMode(n);
                }
                continue;
            case 'E': case 'O': case 'c': case 'e': case 'i': case 'o':
                continue;
            }
        }
        if (ruby == 0) {
            int a;
            s = fn_800776F8(s, &a);
            adv = f * ((f32)a * m);
        } else {
            adv = (f32)lbl_804CB6F0->v15();
        }
        w += adv;
    }
    if (prev == -1) prev = 0;
    SwapMode(prev);
    f32 d = fn_80295AA4(lbl_804CD620, lbl_804CD628);
    return (int)((f32)(int)(d * (w + lbl_804CD630 / d)) / d);
}
}
