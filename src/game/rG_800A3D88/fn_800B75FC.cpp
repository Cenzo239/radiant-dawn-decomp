#include "game/rG_800A3D88/types.h"

// Picks the attack animation for a character from the scene state.
extern "C" {
struct Ch { u8 p[0x56]; s8 m56; u8 p57[0x78 - 0x57]; void* data; };
struct Sc;
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_800BEEC8(Sc*);
int fn_800BEED0(Sc*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A7460(void*, const char*);
#else
void* fn_800A7460(void*, const char*);
#endif
int fn_800BEEB0(Ch*, int);
int fn_800B727C(Ch*, const char*);
int fn_800B591C(Ch*);
int fn_800BEED8(void*, int);
u32 fn_80089ED0();
void fn_800BEEBC(Ch*);
static inline int Random(Ch* c, int n) {
    int k;
    if (fn_800BEED8(c->data, fn_800B591C(c))) {
        k = fn_80089ED0() % n;
        for (int j = 0; j < 3; j++) {
            if (j == 2) {
                fn_800BEEBC(c);
                break;
            }
            if (!(c->m56 & (1 << k))) break;
            k = (k + 1) % n;
        }
        c->m56 |= 1 << k;
    } else {
        k = c->m56 % n;
        c->m56 = (k + 1) % n;
    }
    return k;
}
int fn_800B75FC(Ch* c, Sc* s) {
    int t[4];
    int r;
    int k;
    int n;
    if (s == NULL) return -1;
    if (c->data == NULL) return -1;
    r = -1;
    if (fn_800BEEC8(s) == 0x6F) {
        if (fn_800A7460(c->data, STR(0x1ED)) && fn_800BEEB0(c, 0x10000)) {
            if (fn_800BEED0(s)) r = fn_800B727C(c, STR(0x1F2));
            if (r < 0) r = fn_800B727C(c, STR(0x1FF));
        }
        if (r < 0) {
            if (fn_800BEED0(s)) r = fn_800B727C(c, STR(0x208));
            if (r < 0) r = fn_800B727C(c, STR(0xEE));
        }
    }
    if (fn_800BEEC8(s) == 0x70 && fn_800A7460(c->data, STR(0x218))) {
        r = fn_800B727C(c, STR(0x211));
    }
    if (r < 0) {
        n = 0;
        if (fn_800A7460(c->data, STR(0x1ED))) {
            if (fn_800BEEB0(c, 0x10000)) {
                k = fn_800B727C(c, STR(0x221));
                if (k >= 0) { t[0] = k; n = 1; }
                k = fn_800B727C(c, STR(0x228));
                if (k >= 0) { t[n] = k; n++; }
            } else {
                k = fn_800B727C(c, STR(0x211));
                if (k >= 0) { t[0] = k; n = 1; }
                k = fn_800B727C(c, STR(0x22F));
                if (k >= 0) { t[n] = k; n++; }
            }
        } else {
            k = fn_800B727C(c, STR(0x211));
            if (k >= 0) { t[0] = k; n = 1; }
            k = fn_800B727C(c, STR(0x22F));
            if (k >= 0) { t[n] = k; n++; }
            k = fn_800B727C(c, STR(0x221));
            if (k >= 0) { t[n] = k; n++; }
        }
        if (n == 0) return -1;
        r = t[Random(c, n)];
    }
    return r;
}
}
