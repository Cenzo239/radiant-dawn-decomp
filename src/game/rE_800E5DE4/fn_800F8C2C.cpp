#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
typedef struct GF { u32 pad : 7; u32 b : 1; } GF;
extern "C" {
extern u8 lbl_804CB73E;
extern u8 lbl_804CB741;
extern u8 lbl_803CAB38[];
extern GF* fn_80060728(void*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E7DC(u8);
extern void fn_8007E7F4(void);
extern s16 fn_801237EC(MapUnit*);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_80080578(int);
extern void fn_80080940(GXColor, GXColor, GXColor, GXColor);
extern void fn_80080308(void);
extern void fn_800804D4(int, int, int, int);
void fn_800F8C2C(MapUnit* m) {
    if (lbl_804CB73E && !fn_80060728(lbl_803CAB38)->b && (m->flags & 0x100)) {
        u8 a = m->unk33 * lbl_804CB741 / 255;
        if (a) {
            GXColor t[16] = {{0x40,0x40,0x80,0xC0}, {0x80,0x80,0xFF,0xC0}, {0x40,0x40,0x80,0xC0}, {0x80,0x80,0xFF,0xC0}, {0x80,0x20,0x20,0xC0}, {0xFF,0x40,0x40,0xC0}, {0x80,0x20,0x20,0xC0}, {0xFF,0x40,0x40,0xC0}, {0x20,0x80,0x20,0xC0}, {0x40,0xFF,0x40,0xC0}, {0x20,0x80,0x20,0xC0}, {0x40,0xFF,0x40,0xC0}, {0x80,0x80,0x00,0xC0}, {0xFF,0xFF,0x00,0xC0}, {0x80,0x80,0x00,0xC0}, {0xFF,0xFF,0x00,0xC0}};
            GXColor* c;
            Vec p = *(Vec*)&m->f1C;
            switch (m->unkF4->unk8) {
            case 0: c = &t[0]; break;
            case 1: c = &t[4]; break;
            case 2: c = &t[8]; break;
            case 3: c = &t[12]; break;
            }
            fn_8007E154();
            fn_8007E4E4(p.x - 16.0f, 16.0f + p.y, 990.0f, 1.0f);
            fn_8007E174(0, 0x12);
            fn_8007E7DC(a);
            fn_8007E164();
            {
                int v = m->unk114;
                int w = (v << 5) / fn_801237EC(m);
                if (w > 0) {
                    fn_800800D4(3);
                    fn_80080388(0.0f, 0.0f, w, 3.0f);
                    fn_80080578(0);
                    fn_80080940(c[0], c[1], c[2], c[3]);
                    fn_80080308();
                }
            }
            fn_800800D4(1);
            fn_80080388(-1.0f, -1.0f, 34.0f, 5.0f);
            fn_800804D4(0, 0, 0, 0xC0);
            fn_80080308();
            fn_8007E7F4();
        }
    }
}
}
