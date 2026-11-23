/* Cloud layer scroll step, then queues its draw callback. */
#include "game/rL_80133EB4/types.h"
struct WeatherP {
    u8 pad0[0x30];
    u8 x30;
    u8 pad31;
    u8 x32;
    u8 pad33[0x6C - 0x33];
    f32 x6c, x70;
};
struct DP2 {
    u8 pad0[0x34];
    f32 a0, a1;
    f32 b0, b1;
    Vec cam;
    void* tex;
};
extern "C" {
extern u8 lbl_80386540[];
extern WeatherP* fn_80083B84(void*);
extern int fn_80068D74(void);
extern u8* fn_8000F470(void);
#if TARGET_PC
extern FE10_PROTO void fn_80011B90(p32arg, Vec*, Vec*);
#else
extern void fn_80011B90(int, Vec*, Vec*);
#endif
extern void fn_8007E154(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_8007E164(void);
extern void fn_800800D4(int);
extern void fn_801445E8(DP2*);
#if TARGET_PC
extern FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
extern void fn_80080910(void (*)(DP2*), DP2*);
#endif
extern void fn_80080308(void);
void fn_80144938(DP2* p) {
    WeatherP* w = fn_80083B84(lbl_80386540);
    if (w->x30) {
        Vec a = {0.0f, 0.0f, 0.0f};
        Vec b = {0.0f, 0.0f, 0.0f};
        if (w->x32 == 0) {
            u8* cam;
            if (fn_80068D74() == 0) return;
            cam = fn_8000F470();
            fn_80011B90(0, (Vec*)(cam + 0xE0), &a);
            fn_80011B90(0, &p->cam, &b);
            a.x -= b.x;
            a.y -= b.y;
            p->cam = *(Vec*)(cam + 0xE0);
        }
        {
            f32 k;
            k = 1.0f;
            int i;
            for (i = 0; i < 2; i++) {
                (&p->a0)[i] += w->x6c * k - a.x;
                (&p->b0)[i] += w->x70 * k - a.y;
                (&p->a0)[i] -= (int)((&p->a0)[i] / 128.0f) << 7;
                (&p->b0)[i] -= (int)((&p->b0)[i] / 128.0f) << 7;
                k *= 1.5f;
            }
        }
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 800.0f, 1.0f);
        fn_8007E374(p->tex, 5, 0x411);
        fn_8007E164();
        fn_800800D4(0xB);
        fn_80080910(fn_801445E8, p);
        fn_80080308();
    }
}

}
