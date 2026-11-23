/* Clear wall bits between tiles whose corner heights differ too much, 80113C74. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern Map lbl_803EC898;
struct Hg { s16 c[4]; };
static inline f32 Sq3(f32 s, int a, int b) { f32 t = s * (f32)(a - b); return t * t; }
#define D2(a, b) Sq3(m->scale, a, b)
void fn_80113C74(Map* m) {
    /*P*/
    u16 v;
    int y;
    Hg* h;
    Hg* up;
    Hg* dn;
    Hg* lf;
    Hg* rt;
    int x;
/*E*/
    for (y = 0; y < lbl_803EC898.h; y++) {
        h = (Hg*)&m->hgt[y * 0x100];
        up = h - 64;
        dn = h + 64;
        lf = h - 1;
        rt = h + 1;
        for (x = 0; x < lbl_803EC898.w; x++, h++, up++, dn++, lf++, rt++) {
            v = lbl_803EC898.flags[(s8)x + ((s8)y << 6)];
            if (v & 8) {
                if (!(D2(h->c[0], up->c[2]) < 0.04000000283f && D2(h->c[1], up->c[3]) < 0.04000000283f)) {
                    v &= ~8;
                }
            }
            if (v & 4) {
                if (!(D2(h->c[2], dn->c[0]) < 0.04000000283f && D2(h->c[3], dn->c[1]) < 0.04000000283f)) {
                    v &= ~4;
                }
            }
            if (v & 1) {
                if (!(D2(h->c[0], lf->c[1]) < 0.04000000283f && D2(h->c[2], lf->c[3]) < 0.04000000283f)) {
                    v &= ~1;
                }
            }
            if (v & 2) {
                if (!(D2(h->c[1], rt->c[0]) < 0.04000000283f && D2(h->c[3], rt->c[2]) < 0.04000000283f)) {
                    v &= ~2;
                }
            }
            lbl_803EC898.flags[(s8)x + ((s8)y << 6)] = v;
        }
    }
}
}
