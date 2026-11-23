/* Light fade process step: interpolate, then copy position, range and scaled colours to the two lights (fn_8017DECC). */
#include "game/rR_80175E5C/types.h"
struct C4 { u8 r, g, b, a; };
struct Vec { f32 x, y, z; };
struct Lt {
    u8 pad0[2];
    C4 col;
};
struct Lt2 {
    u8 pad0[4];
    C4 col;
    Vec pos;
    u8 pad14[0x20 - 0x14];
    f32 range;
};
struct LF {
    u8 pad0[0x30];
    Vec pos;
    f32 range;
    f32 t;
    int state;
    int dur;
    int cnt;
    u8 pad50[4];
    u8 on;
    C4 c0;
    C4 c1;
    u8 pad5D[0x64 - 0x5D];
    Lt* amb;
    Lt2* lt;
};
extern "C" {
f32 fn_8001EF44(int, int, f32, f32);
f32 fn_8001EF30(f32, f32, f32, f32);
void fn_80083B78(void*);
}
static inline C4 Scale(C4 c, int pct) {
    int r = c.r * pct / 100;
    int g = c.g * pct / 100;
    int b = c.b * pct / 100;
    c.r = r > 0xFF ? 0xFF : r;
    c.g = g > 0xFF ? 0xFF : g;
    c.b = b > 0xFF ? 0xFF : b;
    return c;
}
extern "C" void fn_8017DECC(LF* o) {
    switch (o->state) {
    case 0:
        o->cnt++;
        o->t = fn_8001EF44(o->dur, o->cnt, 0.0f, 1.0f);
        if (o->cnt >= o->dur) {
            fn_80083B78(o);
        }
        break;
    case 1:
        o->cnt++;
        o->t = fn_8001EF30(0.0f, 1.0f, o->dur, o->cnt);
        if (o->cnt >= o->dur) {
            o->state = 3;
        }
        break;
    case 2:
        o->cnt++;
        o->t = fn_8001EF30(1.0f, 0.0f, o->dur, o->cnt);
        if (o->cnt >= o->dur) {
            fn_80083B78(o);
        }
        break;
    case 3:
        break;
    }
    o->lt->pos = o->pos;
    o->lt->range = o->range;
    o->lt->col = Scale(o->c0, (int)(100.0f * o->t));
    if (o->on) {
        o->amb->col = Scale(o->c1, (int)(100.0f * (1.0f - o->t)));
    }
}
