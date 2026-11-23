/* NEAR MISS: 16-32 lines: float literal load order and in-place extsh conflict through the s16/int prototype choice. */
/* Countdown numbers with pulsing rings */
#include "game/rN_8025EEF0/calls.h"

struct Cd { s16 m0, m2; u8 pad4[0xC]; void* m10; s16 m14, m16, m18; };

extern "C" {

extern s16* lbl_804CC0A8;
extern char lbl_803738BC[];
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E7DC(int a);
void fn_800068A0(void* a, const char* b);
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
void fn_80253EE4(const char* s, f32 v);
void fn_8027F9B0(f32 a, f32 b, int n, int c, int d, int e, int f);
void fn_8027FD08(f32 a, f32 b, int n, int c, int d, int e, int f);

#define OBJ lbl_804CC0A8
static inline void D2(int n, s16 x, s16 y, int a, f32 z, f32 s) { fn_8027FD08(z, s, n, x, y, a, 0x20); }
#define D1(n, x, y, a) D2(n, x, y, a, -1.0f, 1.0f)

void fn_80280060(void) {
/*P*/
    f32 s;
    s16 d;
    s16 a;
    s16 k;
/*E*/
    if (fn_8023F880(lbl_803738BC) == 0) return;
    if (*(void**)(OBJ + 0x10) == 0) fn_800068A0(OBJ + 0x10, lbl_803738BC);
    if (OBJ[0xC] == 0) return;
    fn_8007E154();
    fn_8007E7DC((u8)OBJ[0xC]);
    fn_8007E164();
    s = fn_8017F68C(1.0f, 0.5f, OBJ[1], 80.0f, 0);
    if (OBJ[1] > 0x50) s = 0.5f;
    if (OBJ[0xB] > 0) OBJ[0xB]--;
    OBJ[0xD] = fn_8017F68C(0.0f, 255.0f, OBJ[0xB], 32.0f, 0);
    OBJ[0xE] = fn_8017F68C(255.0f, 0.0f, OBJ[0xB], 32.0f, 0);
    OBJ[10]++;
    if ((f32)OBJ[10] > 160.0f * s) OBJ[10] = 0;
    if (OBJ[10] == (s16)(int)(50.0f * s)) {
        s16 c = OBJ[1];
        if (c >= 0 && c <= 9) {
            fn_80253EE4(lbl_803738BC + 0x15, 0.0f);
        } else if (c >= 10 && c <= 0x13) {
            fn_80253EE4(lbl_803738BC + 0x2D, 0.0f);
        } else if (c >= 0x14 && c <= 0x1D) {
            fn_80253EE4(lbl_803738BC + 0x45, 0.0f);
        } else if (c >= 0x1E) {
            fn_80253EE4(lbl_803738BC + 0x5D, 0.0f);
        }
    }
    fn_8027F9B0(0.0f, 1.0f, OBJ[0], 0, 0, 0xFF, 0x10);
    d = 50.0 * s;
    fn_8027FD08(0.0f, 1.0f, OBJ[1], 0, 0, 0xFF, 0x10);
    k = -(50.0 * s - (f32)OBJ[10]);
    if (k >= 0 && k <= d) {
        f32 u = fn_8017F68C(1.3f / s, 1.0f, k, d, 4);
        s16 al = fn_8017F68C(0.0f, 255.0f, k, d / 2 + 1, 4);
        fn_8027FD08(-1.0f, u, OBJ[1], 0, 0, al, 0x20);
    }
    k = -(70.0f * s - (f32)OBJ[10]);
    if (k >= 0 && k <= d) {
        f32 u = fn_8017F68C(1.3f / s, 1.0f, k, d, 4);
        s16 al = fn_8017F68C(0.0f, 255.0f, k, d / 2 + 1, 4);
        fn_8027FD08(-1.0f, u, OBJ[1], 0, 0, al, 0x20);
    }
    k = -(90.0f * s - (f32)OBJ[10]);
    if (k >= 0 && k <= d) {
        f32 u = fn_8017F68C(1.3f / s, 1.0f, k, d, 4);
        s16 al = fn_8017F68C(0.0f, 255.0f, k, d / 2 + 1, 4);
        fn_8027FD08(-1.0f, u, OBJ[1], 0, 0, al, 0x20);
    }
    a = 0;
    {
        s16 d2 = 30.0f * s;
        int j = (s16)(int)-(60.0f * s - (f32)OBJ[10]);
        if (j >= 0 && j <= d2) a = fn_8017F68C(0.0f, 255.0f, j, d2, 0);
        j = (s16)(int)-(90.0f * s - (f32)OBJ[10]);
        if (j >= 0 && j <= d2) a = fn_8017F68C(255.0f, 0.0f, j, d2, 0);
    }
    D1(OBJ[1], 1.5f / s, 0.0f / s, a);
    D1(OBJ[1], -1.5f / s, 0.0f / s, a);
    D1(OBJ[1], 0.0f / s, 1.5f / s, a);
    D1(OBJ[1], 0.0f / s, -1.5f / s, a);
    D1(OBJ[1], 1.0f / s, 1.0f / s, a);
    D1(OBJ[1], -1.0f / s, -1.0f / s, a);
    D1(OBJ[1], -1.0f / s, 1.0f / s, a);
    D1(OBJ[1], 1.0f / s, -1.0f / s, a);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

}
