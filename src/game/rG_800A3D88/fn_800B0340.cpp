#include "game/rG_800A3D88/types.h"

// Model draw callback: picks a bob offset from a timer table and sets the fog/blend state.
extern "C" {
typedef f32 Mt[3][4];
struct Cam { u8 p[0x5F]; u8 m5f; u8 m60; };
struct Mo { u8 p[0x88]; Cam* m88; };
int fn_80011F90();
int fn_8001201C();
int fn_80011F38();
int fn_80011FC4();
u32 fn_8017FA1C();
f32 fn_8001E010(int);
f32 fn_8001EF30(f32, f32, f32, f32);
u32 fn_8028C1A0(f32);
void fn_803128AC(Mt, f32, f32, f32);
void fn_80307F10(Mt, int, int);
void fn_80021F7C(int, int, int, int);
static inline f32 Bob(int k, u32 t, f32 sc) {
    u32 tb[5] = {0, 3, 7, 10, 0x5A};
    f32 ft[4] = {0.25f, 0.5f, 0.25f, 0.0f};
    f32 y = 0.0f;
    switch (k) {
    case 0:
        break;
    case 1:
        tb[4] <<= 1;
        break;
    case 2:
        tb[4] >>= 1;
        break;
    case 3:
        return y;
    case 4:
        return 0.5f;
    }
    tb[4] = fn_8028C1A0(fn_8001EF30(tb[3], tb[4], 1.0f, sc));
    u32 r = t % tb[4];
    int i;
    u32* q;
    for (q = tb, i = 0; i < 4; q++, i++) {
        if (r < q[1]) return ft[i];
    }
    return y;
}
void fn_800B0340(Mo* m) {
    Mt mt;
    Cam* d = m->m88;
    int a = fn_80011F90();
    int b = fn_8001201C();
    if (a == 0xFF) a = fn_80011F38();
    if (b == 0x3C) b = fn_80011FC4();
    u32 t = fn_8017FA1C();
    int k = d->m5f;
    f32 sc = fn_8001E010((s8)d->m60);
    f32 y = Bob(k, t, sc);
    fn_803128AC(mt, 0.0f, y, 0.0f);
    fn_80307F10(mt, b, 1);
    fn_80021F7C(a, 1, 4, b);
}
}
