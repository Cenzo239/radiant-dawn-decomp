#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* title bars and caption */
typedef struct PData { u8 pad[0x10]; void* x10; } PData;
extern char lbl_8036D68C[];
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_800800D4(int);
extern void fn_80080348(f32, f32, f32, f32);
extern void fn_80080368(f32, f32, f32, f32);
extern void fn_80080578(int);
extern void fn_80080308(void);
extern const char* fn_800D0864(const char*);
extern int fn_800CA3DC(const char* s, int n, f32 scale);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, int c, int d, int e, const char* fmt, ...);
void fn_801AF104(PData* d) {
    int b = 0x4A;
    int a = 0x12;
    fn_801BCA5C(-1.0f);
    fn_8007E154();
    fn_8007E374(d->x10, 1, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080348(304.0f, a, 0.0f, 0.0f);
    fn_80080368(608.0f, b, 304.0f, 56.0f);
    fn_80080578(0);
    fn_80080308();
    fn_800800D4(1);
    fn_80080348(0.0f, a, 304.0f, 0.0f);
    fn_80080368(304.0f, b, 0.0f, 56.0f);
    fn_80080578(0);
    fn_80080308();
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    {
        const char* t = fn_800D0864(lbl_8036D68C + 0x1BD);
        f32 w = fn_800CA3DC(t, -1, 1.2f);
        fn_800CB3A8(1.2f, 0.0f, 304.0f - 0.5f * w, 0x1E, 2, 0, 0, t);
    }
    fn_801BCA5C(2.0f);
}
}
