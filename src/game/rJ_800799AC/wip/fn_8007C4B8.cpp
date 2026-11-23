/* Near miss, 61 of 364 words (compiles alone). Everything but the stick clamp's
 * registers is right: x should stay in r4 and y in r5 through the dead-zone
 * subtraction, with signs in r6/r7 and t in r8. fn_8007CC1C and fn_8007D5B8 end in
 * the same inlines, so solving this unlocks both. The dead-zone form
 * "v <= 15 ? 0 : v - 15" gives the right xoris/subfic/addc/subfe/andc shape.
 */
#include "game/rJ_800799AC/pad.h"
extern "C" {
#define CL(v) (v <= 15 ? 0 : v - 15)
/* Scale a stick into an octagon with a dead zone */
static inline void stickClamp(s16* ax, s16* ay, int a, int b, int lim) {
    int y = *ay;
int t;
int sx;
int x = *ax;
int sy;
int xa;

    if (x >= 0) {
        sx = 1;
    } else {
        sx = -1;
        x = -x;
    }
    if (y >= 0) {
        sy = 1;
    } else {
        sy = -1;
        y = -y;
    }
    x = CL(x);
    y = CL(y);
    if (x == 0 && y == 0) {
        *ay = 0;
        *ax = 0;
    } else {
        xa = x * a;
        t = y * a;
        if (t <= xa) {
            t = xa + y * b;
            if (t > lim) {
                x = (s16)(x * lim / t);
                y = (s16)(y * lim / t);
            }
        } else {
            t += x * b;
            if (t > lim) {
                x = (s16)(x * lim / t);
                y = (s16)(y * lim / t);
            }
        }
        *ax = sx * x;
        *ay = sy * y;
    }
}

static inline void trigClamp(s16* t) {
    if (*t <= 0x1E) {
        *t = 0;
    } else {
        if (*t > 0xB4) {
            *t = 0xB4;
        }
        *t -= 0x1E;
    }
}

/* Read a Classic Controller sample */
void fn_8007C4B8(Pad* p, u8* wii, void* arg) {
    p->vBC();
    if (*(u32*)(wii + 0x60) & 0x2) {
        p->raw |= 0x1;
    }
    if (*(u32*)(wii + 0x60) & 0x8000) {
        p->raw |= 0x2;
    }
    if (*(u32*)(wii + 0x60) & 0x4000) {
        p->raw |= 0x4;
    }
    if (*(u32*)(wii + 0x60) & 0x1) {
        p->raw |= 0x8;
    }
    if ((*(u32*)(wii + 0x60) & 4) || (*(u32*)(wii + 0x60) & 0x80)) {
        p->raw |= 0x10;
    }
    if (*(u32*)(wii + 0x60) & 0x2000) {
        p->raw |= 0x40;
    }
    if (*(u32*)(wii + 0x60) & 0x200) {
        p->raw |= 0x100;
    }
    if (*(u32*)(wii + 0x60) & 0x10) {
        p->raw |= 0x400;
    }
    if (*(u32*)(wii + 0x60) & 0x40) {
        p->raw |= 0x800;
    }
    if (*(u32*)(wii + 0x60) & 0x8) {
        p->raw |= 0x1000;
    }
    if (*(u32*)(wii + 0x60) & 0x20) {
        p->raw |= 0x2000;
    }
    if (*(u32*)(wii + 0x60) & 0x1000) {
        p->raw |= 0x8000;
    }
    if (*(u32*)(wii + 0x60) & 0x400) {
        p->raw |= 0x4000;
    }
    if (*(u32*)(wii + 0x60) & 0x800) {
        p->raw |= 0x30000;
    }
    if (*(u32*)wii & 0x8000) {
        p->raw |= 0x10000;
    }
    p->axis[0] = 127.0f * *(f32*)(wii + 0x6C);
    p->axis[1] = 127.0f * *(f32*)(wii + 0x70);
    p->axis[2] = 127.0f * *(f32*)(wii + 0x74);
    p->axis[3] = 127.0f * *(f32*)(wii + 0x78);
    p->axis[4] = 255.0f * *(f32*)(wii + 0x7C);
    p->axis[5] = 0;
    p->axis[6] = 255.0f * *(f32*)(wii + 0x80);
    p->axis[7] = 0;
    if (p->vE8() != 0) {
        p->vD4(p->v14());
    } else if (p->vE4(arg) != 0) {
        p->vD4(3);
    }
    stickClamp(&p->axis[0], &p->axis[1], 0x2F, 0x19, 0xD38);
    stickClamp(&p->axis[2], &p->axis[3], 0x1F, 0x1C, 0x725);
    trigClamp(&p->axis[4]);
    trigClamp(&p->axis[5]);
    trigClamp(&p->axis[6]);
    trigClamp(&p->axis[7]);
}

}
