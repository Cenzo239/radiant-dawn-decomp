/* fn_8001AB10: exact (round m4, m4-c). The clear colour is a GXC passed by value, as in fn_8001AC30.cpp. */
#include "game/rA_800068A0/types.h"
extern "C" {
typedef struct GXC { u8 r, g, b, a; } GXC;
extern u8* fn_80020E74(void);
extern int fn_80020EFC(void);
extern int fn_8030585C(int, int, int, int, int);
extern GXC fn_8002177C(void);
extern void fn_80304C74(GXC c, u32 z);
extern void fn_8001F4D8(int x, int y, int w, int h, int dw, int dh, void* t, int fmt, u8 clr);

int fn_8001AB10(void) {
    u8* buf = fn_80020E74();
    u8* p = buf + fn_8030585C(0x130, 0xE0, 6, 0, 0);
    if (buf == 0) {
        return 0;
    }
    {
        int sz = fn_8030585C(0x130, 0xE0, 6, 0, 0);
        sz += fn_8030585C(0x260, 0x1C0, 6, 0, 0);
        if (sz > fn_80020EFC()) {
            return 0;
        }
    }
    {
        GXC z = {0};
        fn_80304C74(z, 0xFFFFFF);
    }
    fn_8001F4D8(0, 0, 0x260, 0x1C0, -1, -1, p, 6, 1);
    fn_80304C74(fn_8002177C(), 0xFFFFFF);
    return 1;
}
}
