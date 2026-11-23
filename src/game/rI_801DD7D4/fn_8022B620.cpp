#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
extern char lbl_8041EB20[];
extern char* lbl_803902B0[];
extern char lbl_80371F98[];
#if TARGET_PC
FE10_PROTO void fn_801A1AC4(void*, void*, f32, f32, p32arg);
#else
void fn_801A1AC4(void*, void*, f32, f32, int);
#endif
f32 fn_8017F68C(int, f32, f32, f32, f32);
double fn_80295A9C(double, double);
struct Snd { u32 flags; u8 p[0xd4]; s16 xd8; };
struct E6 { u8 p[0x30]; f32 x30, x34; u8 p38[0x1c]; int x54; };
void fn_801E6A88(E6* o) {
    fn_801A1AC4(lbl_8041EB20, o, o->x30, o->x34, o->x54);
    ((Snd*)lbl_8041EB20)->flags |= 2;
    ((Snd*)lbl_8041EB20)->xd8 = 1;
}
static inline char** tb(int k) {
    char** p = NULL;
    switch (k) {
    case 0:
        p = lbl_803902B0;
        break;
    }
    return p;
}
/* `t` only keeps the walking pointer below the counter in register order. */
static inline int cols(int k) {
    int i = 0;
    int t = 0;
    char** p;
    p = (char**)t;
    switch (k) {
    case 0:
        p = lbl_803902B0;
        break;
    }
    while (*p[0] != 0xa) {
        p++;
        i++;
    }
    return (s16)(i + 1);
}
int fn_8022B620(int k) {
    int c = 0;
    int n = cols(k);
    char** q = tb(k);
    while (*q != NULL) {
        q += n;
        c++;
    }
    return c;
}
char* fn_8022B6DC(int k, int a, int b) {
    int n = cols(k);
    char* s = tb(k)[a + n * b];
    if (s == NULL) return lbl_80371F98;
    return s;
}
struct K3 { u8 p[0x44]; f32 x44; };
struct K2 { u8 p[0x28]; s16 x28; u8 p2a[6]; s8 x30; u8 p31[3]; int x34; f32 x38, x3c; K3* x40; };
void fn_8021C1EC(K2* p) {
    f32 v = fn_8017F68C(p->x30, p->x38, p->x3c, p->x34 - p->x28, p->x34);
    K3* k = p->x40;
    k->x44 = fn_80295A9C(v, 360.0);
}
}
