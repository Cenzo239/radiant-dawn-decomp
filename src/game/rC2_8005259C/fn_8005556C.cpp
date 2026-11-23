#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on
extern "C" {
void* fn_8012759C(void* u);
int fn_80108F68(void* p);
void fn_80109094(void* p, int a, int b);
void fn_8010904C(void* p);
}
extern u8 lbl_8037DF4C[];
typedef struct SkB { u16 pad0 : 6; u16 b7 : 3; u16 b4 : 3; u16 pad1 : 4; } SkB;
typedef struct U6 { u8 pad[0xec]; void* ec; u8 padf0[4]; UnitSub* f4; u8 padf8[4]; u8 fc; u8 padfd[5]; s8 x; s8 y; u8 pad104[8]; u32 flags; SkB sk; } U6;
extern "C" void fn_8005556C(void) {
    U6* u = (U6*)fn_800CFB0C(fn_800CFD3C(&lbl_803E7320));
    if (fn_8012759C(u) && (fn_801116B8((ItemSlot*)fn_8012759C(u))->flags4 & 0x10)) {
    } else { return; }
    {
            ItemSlot* it = (ItemSlot*)fn_8012759C(u);
            SkB* s = &u->sk;
            if (fn_801116B8(it)->flags0 & 0x80000) {
                fn_8010904C(s);
            } else {
                if (fn_801116B8(it)->flags0 & 0x100000) fn_80109094(s, 3, 0);
                if (fn_801116B8(it)->flags0 & 0x200000) fn_80109094(s, 2, 0);
            }
    }
}
extern "C" int fn_800556C0(void* parent) {
    u8 buf[24];
        U6* u;
    SkB* s;
    ItemSlot* it;
    int i;

    fn_800CFB34(&lbl_803E7320);
    fn_8010E41C(buf, 0);
    for (i = 1; i <= 0xfe; i++) {
        u = (U6*)GetU(i);
        if (u->ec == 0) continue;
        if (!buf[u->f4->b8]) continue;
        if (!fn_8012759C(u)) continue;
        if (!(fn_801116B8((ItemSlot*)fn_8012759C(u))->flags4 & 0x10)) continue;
        {
            it = (ItemSlot*)fn_8012759C(u);
            s = &u->sk;
            if (!fn_80108F68(s)) continue;
            if ((fn_801116B8(it)->flags0 & 0x80000) || ((fn_801116B8(it)->flags0 & 0x100000) && s->b4) || ((fn_801116B8(it)->flags0 & 0x200000) && s->b7)) {
                fn_800CFC50(&lbl_803E7320, u->x, u->y, u->fc, 0);
            }
        }
    }
    if (lbl_803E7320.i0 == 0) {
        return 0;
    }
    fn_80081194(lbl_8037DF4C, parent);
    return 1;
}
