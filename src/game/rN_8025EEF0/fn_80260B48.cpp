/* Dictionary: per-frame update */
#include "game/rN_8025EEF0/calls.h"

struct DPage { f32 y, from, to; int t, tMax; };
struct DPos { s16 x, y; s16 sx, sy; s16 ex, ey; s16 t; };
struct DS {
    u8 pad[4];
    int mode;
    u8 pad8[0x12];
    s16 x, y, sx, sy, ex, ey, t;
    u8 pad28[0x48];
    s8 m70;
};

extern "C" {

extern u8* lbl_804CC004;
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
void fn_80260E58(void);
void fn_80261728(void);

void fn_80260B48(void) {
/*P*/
    u8* p;
    u8* q;
    int off;
    int i;
    int o2;
    int j;
/*E*/
    lbl_804CB5B8->v48();
    lbl_804CB5B8->v3C();
    switch (*(int*)(lbl_804CC004 + 4)) {
    case 0: fn_80260E58(); break;
    case 1: fn_80261728(); break;
    }
    i = 0;
    off = 0;
    for (; i < 2; i++, off += 0x24) {
        q = lbl_804CC004 + off;
        if (*(int*)(q + 0x44) > 0) {
            int t = --*(int*)(q + 0x44);
            *(f32*)(q + 0x38) = fn_8017F68C(*(f32*)(q + 0x3C), *(f32*)(q + 0x40), *(int*)(q + 0x48) - t, *(int*)(q + 0x48), 0);
        }
    }
    p = lbl_804CC004;
    {
        *(s16*)(p + 0x1A) = fn_8017F68C(*(s16*)(p + 0x1E), *(s16*)(p + 0x22), 4 - *(s16*)(p + 0x26), 4.0f, 0);
        *(s16*)(p + 0x1C) = fn_8017F68C(*(s16*)(p + 0x20), *(s16*)(p + 0x24), 4 - *(s16*)(p + 0x26), 4.0f, 0);
        if (--*(s16*)(p + 0x26) < 0) *(s16*)(p + 0x26) = 0;
    }
    j = 0;
    o2 = 0;
    for (; j < 2; j++, o2 += 0x24) {
        p = lbl_804CC004 + o2;
        *(s16*)(p + 0x2A) = fn_8017F68C(*(s16*)(p + 0x2E), *(s16*)(p + 0x32), 4 - *(s16*)(p + 0x36), 4.0f, 0);
        *(s16*)(p + 0x2C) = fn_8017F68C(*(s16*)(p + 0x30), *(s16*)(p + 0x34), 4 - *(s16*)(p + 0x36), 4.0f, 0);
        if (--*(s16*)(p + 0x36) < 0) *(s16*)(p + 0x36) = 0;
    }
    if (*(s8*)(lbl_804CC004 + 0x70) > 0) (*(s8*)(lbl_804CC004 + 0x70))--;
}

}
