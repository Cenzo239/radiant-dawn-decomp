#include "game/rG_800A3D88/types.h"
extern "C" {
extern void* lbl_803E7260[6];
void* fn_80077DB0(void*);
extern const f32 lbl_804CD630;
extern const f64 lbl_804CD620, lbl_804CD628;
int fn_80077A58(void*);
int fn_80077BF0();
f64 fn_80295AA4(f64, f64);
static inline int SwapMode(int idx) {
    void* old = fn_80077DB0(lbl_803E7260[idx]);
    int i;
    for (i = 0; i < 6; i++) {
        if (lbl_803E7260[i] == old) return i;
    }
    return -1;
}
int fn_800CABA0(f32 f, void* p, int idx) {
    if (idx == -1) idx = 0;
    int prev = SwapMode(idx);
    f32 v = f * (f32)fn_80077A58(p);
    f32 d = fn_80295AA4(lbl_804CD620, lbl_804CD628);
    int r = (int)((f32)(int)(d * (v + lbl_804CD630 / d)) / d);
    if (prev == -1) prev = 0;
    SwapMode(prev);
    return r;
}
int fn_800CB0FC(f32 f, int idx) {
    if (idx == -1) idx = 0;
    int prev = SwapMode(idx);
    int r = f * (f32)fn_80077BF0();
    if (prev == -1) prev = 0;
    SwapMode(prev);
    return r;
}
int fn_800778A8(void*);
int fn_80077BE0();
int fn_800CAD6C(f32 f, void* p, int idx) {
    if (idx == -1) idx = 0;
    int prev = SwapMode(idx);
    f32 v = f * (f32)fn_800778A8(p);
    f32 d = fn_80295AA4(lbl_804CD620, lbl_804CD628);
    int r = (int)((f32)(int)(d * (v + lbl_804CD630 / d)) / d);
    if (prev == -1) prev = 0;
    SwapMode(prev);
    return r;
}
int fn_800CAF38(f32 f, int idx) {
    if (idx == -1) idx = 0;
    int prev = SwapMode(idx);
    f32 v = f * (f32)fn_80077BE0();
    f32 d = fn_80295AA4(lbl_804CD620, lbl_804CD628);
    int r = (int)((f32)(int)(d * (v + lbl_804CD630 / d)) / d);
    if (prev == -1) prev = 0;
    SwapMode(prev);
    return r;
}
typedef struct va_list_ { char gpr; char fpr; char reserved[2]; char* input; char* reg; } va_list_;
struct GXC { u8 r, g, b, a; };
void fn_80290C84(char*, const char*, va_list_*);
void fn_800800D4(int);
void fn_80080330(f32, f32);
GXC* fn_800CD204(int);
void fn_80080508(GXC*);
void fn_80080C24(char*);
void fn_80080308();
void fn_80080A94(f32);
void fn_80080AA8(f32);
void fn_80080ABC(int, f32);
void fn_80080B70(int, f32);
extern const f32 lbl_804CD648, lbl_804CD610;
void fn_800CB278(int x, int y, int col, const char* fmt, ...) {
#if TARGET_PC
    /* Host: a host va_list; fn_80290C84 (vsprintf) gets its address, as on the Wii */
    __builtin_va_list ap;
    char buf[0x100];
    __builtin_va_start(ap, fmt);
    fn_80290C84(buf, fmt, (va_list_*)&ap);
    __builtin_va_end(ap);
#else
    va_list_ ap;
    char buf[0x100];
    __builtin_va_info(&ap);
    fn_80290C84(buf, fmt, &ap);
#endif
    fn_800800D4(5);
    fn_80080330(x, y);
    {
        GXC c = *fn_800CD204(col);
        fn_80080508(&c);
    }
    fn_80080C24(buf);
    fn_80080308();
}
void fn_800CB3A8(f32 a, f32 b, int x, int y, int col, int k1, int k2, const char* fmt, ...) {
#if TARGET_PC
    /* Host: a host va_list; fn_80290C84 (vsprintf) gets its address, as on the Wii */
    __builtin_va_list ap;
    char buf[0x100];
    __builtin_va_start(ap, fmt);
    fn_80290C84(buf, fmt, (va_list_*)&ap);
    __builtin_va_end(ap);
#else
    va_list_ ap;
    char buf[0x100];
    __builtin_va_info(&ap);
    fn_80290C84(buf, fmt, &ap);
#endif
    fn_800800D4(5);
    fn_80080330(x, y);
    {
        GXC c = *fn_800CD204(col);
        fn_80080508(&c);
    }
    fn_80080A94(a);
    fn_80080AA8(b);
    fn_80080ABC(k1, lbl_804CD648);
    fn_80080B70(k2, lbl_804CD610);
    fn_80080C24(buf);
    fn_80080308();
}
void fn_800CB520(f32 a, f32 b, int mode, int x, int y, int col, int k1, int k2, const char* fmt, ...) {
#if TARGET_PC
    /* Host: a host va_list; fn_80290C84 (vsprintf) gets its address, as on the Wii */
    __builtin_va_list ap;
    char buf[0x100];
    __builtin_va_start(ap, fmt);
    fn_80290C84(buf, fmt, (va_list_*)&ap);
    __builtin_va_end(ap);
#else
    va_list_ ap;
    char buf[0x100];
    __builtin_va_info(&ap);
    fn_80290C84(buf, fmt, &ap);
#endif
    fn_800800D4(mode);
    fn_80080330(x, y);
    {
        GXC c = *fn_800CD204(col);
        fn_80080508(&c);
    }
    fn_80080A94(a);
    fn_80080AA8(b);
    fn_80080ABC(k1, lbl_804CD648);
    fn_80080B70(k2, lbl_804CD610);
    fn_80080C24(buf);
    fn_80080308();
}
}
