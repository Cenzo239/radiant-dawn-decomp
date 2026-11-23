#include "game/rF_8017F400/drawinl.h"
#pragma auto_inline off
extern "C" {
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_8007E7F4(void);
extern void fn_80080430(f32, f32, f32, f32, f32, f32);
extern void fn_801BCA94(void);
void fn_801AC7AC(void* tex, int n, int a, f32 x, f32 y) {
    fn_8007E154();
    fn_8007E4E4(x, y, 105.0f, 1.0f);
    fn_8007E374(tex, 1, 0x11);
    fn_8007E7DC((u8)a);
    fn_8007E164();
    {
    s16 t = 0x80 - n * 8;
    if (t > 0xE0) t = 0xE0;
    if (t < 0) t = 0;
    fn_800800D4(1);
    fn_80080430(-t, 0.0f, 0.0f, 0.0f, 224.0f, 32.0f);
    }
    fn_80080578(0);
    fn_80080308();
    fn_8007E7F4();
}

void fn_801AC8BC(void* tex, int a, const char* s, int f, f32 x, f32 y) {
    fn_8007E154();
    fn_8007E4E4(x, y - 7.0f, 104.0f, 1.0f);
    fn_8007E7DC((u8)a);
    fn_8007E164();
    if (f == 0) {
        fn_8007E154();
        fn_8007E374(tex, 10, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(8.0f, -2.0f, 39.0f, 26.0f, 50.0f, 15.0f);
        fn_80080578(0);
        fn_80080308();
    }
    fn_801BCA94();
    fn_800CB3A8(1.0f, 0.0f, 0xC, 0xC, 1, 0, 1, s);
    fn_8007E7F4();
}

void fn_801AC9D8(void* tex, int n, int a, f32 x, f32 y) {
    int d[4];
    int* p;
    int i;
    if (n > 0x3E7) n = 0x3E7;
    fn_8007E154();
    fn_8007E4E4(x, 5.0f + y, 104.0f, 1.0f);
    fn_8007E7DC((u8)a);
    fn_8007E164();
    fn_8007E154();
    fn_8007E374(tex, 10, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 10.0f, 1.0f, 27.0f, 37.0f, 13.0f);
    fn_80080578(0);
    fn_80080308();
    {
    p = d;
    i = 0;
    while (n != 0) {
        i++;
        *p = n % 10;
        n /= 10;
        p++;
    }
    }
    {
    int* p;
    int k;
    int px;
    k = i - 1;
    p = &d[k];
    px = 0x26;
    for (; k >= 0; p--, k--) {
        fn_800800D4(1);
        fn_80080430(px, -1.0f, *p * 0x17 + 1, 1.0f, 22.0f, 25.0f);
        fn_80080308();
        px += 0x16;
    }
    }
    fn_8007E7F4();
}
}
