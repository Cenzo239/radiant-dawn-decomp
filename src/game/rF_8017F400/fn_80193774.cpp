/* fn_80193774: gauge bar draw (background, numbers, fill, frame). */
#include "game/rF_8017F400/types.h"
extern "C" {
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void* tex, p32arg, int b);
#else
extern void fn_8007E374(void* tex, int a, int b);
#endif
extern void fn_800800D4(int);
extern void fn_80080308(void);
extern void fn_80080430(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
extern void fn_80080578(int);
extern u8* fn_800CD204(int);
extern void fn_80176B54(int a, int b, int c, void* d, int e, int f, int g, int h, int i, int j);
void fn_80193774(void* tex, int x, int y, int c, f32 den, f32 num) {
    int w;
    if (c >= 0) {
        fn_8007E154();
        fn_8007E4E4(x, y, 100.0f, 1.0f);
        fn_8007E374(tex, c, 0x11);
        fn_8007E164();
        fn_800800D4(2);
        fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 48.0f, 56.0f);
        fn_80080578(0);
        fn_80080308();
    }
    fn_8007E154();
    fn_8007E4E4(x, y, 100.0f, 1.0f);
    fn_8007E374(tex, 5, 0x11);
    fn_8007E164();
    fn_80176B54(0xe9, 0x14, 2, fn_800CD204(1), 0, 0, 0xe, 0x13, 0xc, num);
    w = 127.0f * num / den;
    if (w > 0) {
        if (w < 2) w = 2;
        fn_8007E154();
        fn_8007E4E4(x, y, 100.0f, 1.0f);
        fn_8007E374(tex, 4, 0x11);
        fn_8007E164();
        fn_800800D4(2);
        fn_80080430(68.0f, 23.0f, 0.0f, 0.0f, w, 16.0f);
        fn_80080578(0);
        fn_80080308();
    }
    fn_8007E154();
    fn_8007E4E4(x, y, 100.0f, 1.0f);
    fn_8007E374(tex, 3, 0x11);
    fn_8007E164();
    fn_800800D4(2);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 264.0f, 56.0f);
    fn_80080578(0);
    fn_80080308();
}
}
