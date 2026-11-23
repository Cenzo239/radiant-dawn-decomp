/* Model viewport draw */
#include "game/rN_8025EEF0/calls.h"

struct Vec { f32 x, y, z; };
struct C4 { u8 r, g, b, a; };

extern "C" {

u8* fn_80010BB0(int a);
void fn_80010C38(void* a, void* b);
void fn_80010CA4(void* a);
u8* fn_80010E38(void* a, int b);
void fn_80011274(void);
void fn_80011280(void* a);
void fn_8001B194(void* a);
void fn_8001A4DC(void* a);

static C4 c0 = {0xFF, 0xFF, 0xFF, 0xFF};
static C4 c1 = {0x60, 0x60, 0x60, 0xFF};

struct Mdl { u32 flags; u8 pad4[7]; u8 mB; u8 padC[0x75]; s8 m81; };

static inline void setC(u8* e, C4 c) { e[0] = c.r; e[1] = c.g; e[2] = c.b; e[3] = c.a; }

void fn_8027D7CC(u8* p) {
    Mdl* m = *(Mdl**)(p + 0x30);
    if (m != 0) {
        u8* l;
        fn_803080DC(*(s16*)(p + 0xA4), *(s16*)(p + 0xA6), *(s16*)(p + 0xA8), *(s16*)(p + 0xAA));
        l = fn_80010BB0((s8)m->m81);
        {
            u8 save[0x128];
            fn_80010C38(l, save);
            fn_80010CA4(l);
            {
                u8* e = fn_80010E38(l, 1);
                Vec v = {0.0f, 0.0f, 1000.0f};
                *(Vec*)(e + 8) = v;
                setC(e + 4, c0);
                setC(l + 2, c1);
            }
            fn_80011274();
            fn_80011280(l);
            m->flags |= 0x200000;
            if (m->mB != 0xFF) {
                fn_8001B194(m);
            }
            fn_8001A4DC(m);
            m->flags &= ~0x200000;
            fn_80010C38(save, l);
            fn_80011274();
            fn_80011280(l);
        }
        fn_803080DC(0, 0, 0x260, 0x1C0);
    }
}

}
