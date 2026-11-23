/* video.cpp: apply the screen offset and build the vertical copy filter from the width setting.
 * Names guessed. */
#include "game/rJ_800799AC/types.h"

struct RenderMode {
    u8 pad0[0xA];
    s16 viXOrigin;          /* 0x0A */
    s16 viYOrigin;          /* 0x0C */
    u8 pad[0x19 - 0xE];
    u8 aa;                  /* 0x19 */
    u8 sample_pattern[12][2]; /* 0x1A */
    u8 vfilter[7];          /* 0x32 */
};

extern "C" {
extern s16 lbl_804CA3D0;
extern s16 lbl_804CA3D2;
extern s8 lbl_804CA3D4;
extern s8 lbl_804CB600;
extern s8 lbl_804CB601;
extern volatile u32 lbl_804CB5F4;
RenderMode* fn_802356AC(void);
void fn_803304B4(RenderMode*);
void fn_80304CEC(u8 aa, u8 pattern[12][2], u8 vf, u8* vfilter); /* GXSetCopyFilter */
void* memcpy(void*, const void*, u32);

void fn_8008CA90(void) {
    u8 b[3];
    u8 a[4];
    f32 k;
    u16 c;
    u16 s;
    int i;
    RenderMode* rm = fn_802356AC();
    rm->viXOrigin = lbl_804CA3D0 + lbl_804CB600;
    rm->viYOrigin = lbl_804CA3D2 + lbl_804CB601;
    fn_803304B4(rm);
    if (lbl_804CB5F4 & 0x40) {
        k = 1.0f;
    } else {
        k = 0.5f;
    }
    c = (f32)lbl_804CA3D4 * k;
    s = lbl_804CA3D4 - c;
    for (i = 0; i < 4; i++) {
        if (i < s % 4) {
            a[i] = (f32)s / 4.0f + 1.0f;
        } else {
            a[i] = (f32)s / 4.0f;
        }
    }
    for (i = 0; i < 3; i++) {
        if (i < c % 3) {
            b[i] = 1.0f + (f32)c / 3.0f;
        } else {
            b[i] = (f32)c / 3.0f;
        }
    }
    {
        u8 vf[7] = {a[2], a[0], b[1], b[0], b[2], a[1], a[3]};
        fn_80304CEC(rm->aa, rm->sample_pattern, 1, vf);
        memcpy(rm->vfilter, vf, 7);
    }
}
}
