#include "game/rA_800068A0/types.h"
extern "C" {
typedef struct GXC { u8 r, g, b, a; } GXC;
extern u8* fn_80020E74(void);
extern int fn_8030585C(int, int, int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_8000FF74(p32arg);
#else
extern void fn_8000FF74(int);
#endif
extern GXC fn_8002177C(void);
extern void fn_80304C74(GXC c, u32 z);
extern void fn_8001F4D8(int x, int y, int w, int h, int dw, int dh, void* t, int fmt, u8 clr);
extern void fn_803080DC(int, int, int, int);
extern void fn_8001F5B8(int x, int y, int w, int h, int dw, int dh, void* img, int fmt, const GXC* cols, void* tex2, u16 fl);
extern void fn_80011838(int);
#if TARGET_PC
extern FE10_PROTO void fn_800104DC(p32arg);
#else
extern void fn_800104DC(int);
#endif
void fn_8001AC30(void) {
    u8* img = fn_80020E74();
    u8* img2 = img + fn_8030585C(0x130, 0xE0, 6, 0, 0);
    if (img != 0) {
        f32 d;
        f32 w;
        f32 h;
        int i;
        fn_8000FF74(0);
        GXC old = fn_8002177C();
        GXC z = {0};
        fn_80304C74(z, 0xFFFFFF);
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x130, 0xE0, img, 6, 1);
        w = 304.0f;
        h = 224.0f;
        d = 1.0f;
        fn_803080DC(0, 0, 0x130, 0xE0);
        for (i = 0; i < 4; i++) {
            fn_8001F5B8((int)-d, (int)-d, (int)(2.0f * d + 304.0f), (int)(2.0f * d + 224.0f), (int)w, (int)h, img, 6, 0, 0, 0);
            w = 152.0f;
            h = 112.0f;
            fn_8001F4D8(0, 0, 0x130, 0xE0, (int)w, (int)h, img, 6, 0);
        }
        fn_803080DC(0, 0, 0x260, 0x1C0);
        fn_8001F5B8(0, 0, 0x260, 0x1C0, -1, -1, img2, 6, 0, 0, 0);
        fn_8001F5B8(0, 0, 0x260, 0x1C0, (int)w, (int)h, img, 6, 0, 0, 0x2000);
        fn_80011838(-1);
        fn_800104DC(0);
        fn_80304C74(old, 0xFFFFFF);
    }
}
}
