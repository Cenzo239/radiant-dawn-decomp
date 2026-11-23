/* Intro unit-profile bars */
#include "game/rN_8025EEF0/prim2d.h"

#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

void fn_8026A390(void* tex, int x, int y, int w, int scale, int max, int val) {
    if (val != 0 && max != 0) {
        if (val > max) {
            val = max;
        }
        int len = ((w - 8) * (val * scale)) / (max * 100);
        fn_8007E154();
        fn_8007E4E4(x, y, 104.0f, 1.0f);
        fn_8007E374(tex, 5, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(-4.0f, 0.0f, 0.0f, 0.0f, 8.0f, 8.0f);
        fn_80080578(0);
        fn_80080308();
        fn_8007E154();
        fn_8007E4E4(x, y, 104.0f, 1.0f);
        fn_8007E374(tex, 6, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(4.0f, 0.0f, 0.0f, 0.0f, len, 8.0f);
        fn_80080578(0);
        fn_80080308();
        fn_8007E154();
        fn_8007E4E4(x, y, 104.0f, 1.0f);
        fn_8007E374(tex, 7, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(len + 4, 0.0f, 0.0f, 0.0f, 8.0f, 8.0f);
        fn_80080578(0);
        fn_80080308();
    }
}


void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);
extern char lbl_8037307C[];

#pragma push
#pragma use_lmw_stmw off
void fn_8026A5A0(void* tex, const char* msg, int x, int y, int scale, int max, int val) {
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E4E4(0.0f, 0.0f, 101.0f, 1.0f);
    fn_8007E164();
    fn_800CB3A8((s16)(x + 0x10), (s16)(y - 0xE), 9, 1, 0, 1.0f, 0.0f, fn_800D0864(msg));
    fn_800CB3A8((s16)(x + 0xAA), (s16)(y - 0xE), 1, 1, 0, 1.0f, 0.0f, lbl_8037307C, val);
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 105.0f, 1.0f);
    fn_8007E374(tex, 3, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(x, y, 0.0f, 0.0f, 209.0f, 9.0f);
    fn_80080578(0);
    fn_80080308();
    fn_8026A390(tex, x + 0x46, y + 2, 0x83, scale, max, val);
}
#pragma pop

}
