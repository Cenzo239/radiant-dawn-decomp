/* AI: closest tile searches on the map. */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
struct Ar { void* vt; u32 k; };
extern "C" {
extern ListHdr lbl_803E7320[];
extern s16 lbl_8036B278[];
extern s16 lbl_8036B060[][2];
extern u8 lbl_80387308[];
extern u8 lbl_80387800[];
void fn_80165E18(Unit*, int, int);
void fn_80165F94(Unit*, int, int);
int fn_801658E4(Unit*, s8, s8);
void fn_800CFB34(ListHdr*);
void fn_80039708(void*, int, int);
int fn_800A05B0(int, int, int);
u16 fn_801676D8(int, int);
void* fn_801181E8(Map*, int, int);
int fn_80171378(int, int, Filt*);
void fn_8016F94C(Unit*, int, int, int, u16, int, int, int);
void fn_80114B44(Map*, int, int);
void fn_80114888(Map*, int);
s8 fn_8012408C(Unit*);
int fn_8011799C(Map*, int, int);
u8 fn_80118098(Map*, int, int);
u8* fn_8010B240(u8);
u8 fn_80110880(u8*, Unit*);
u8 fn_801107B8(u8*, Unit*);
void fn_801663E0(int, int, u8, u8, int);
int fn_8016D11C(Unit*);
int fn_8015814C(Unit*, int, int, int);
int fn_80158208(Unit*, int, int, int);
void fn_80116BD0(Map*, int, int, int, int);
static inline BOOL SameT(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}

BOOL fn_8016D27C(Unit* u, u32 fl, u32 k, s16* ox, s16* oy);

u8 fn_80164064(Unit* u, u32 lim);


BOOL fn_8016A280(Unit* u, Unit* t, Inv* p, Filter* f, s16* ox, s16* oy);

int fn_8016A9BC(Unit* u, int x, int y, int a, int r) {
    int n = 0;
    int x0, y0, x1, y1, yy;
    fn_80114888(&lbl_803EC898, 7);
    fn_80114B44(&lbl_803EC898, 0xC, -1);
    fn_80116BD0(&lbl_803EC898, (s8)x, (s8)y, (s8)r, 1);
    fn_80116BD0(&lbl_803EC898, (s8)x, (s8)y, (s8)(a - 1), -1);
    fn_80114888(&lbl_803EC898, 6);
    x0 = x - r;
    if (x0 < lbl_803EC898.x0) {
        x0 = lbl_803EC898.x0;
    }
    y0 = y - r;
    if (y0 < lbl_803EC898.y0) {
        y0 = lbl_803EC898.y0;
    }
    x1 = x + r;
    if (x1 > lbl_803EC898.x1 - 1) {
        x1 = lbl_803EC898.x1 - 1;
    }
    y1 = y + r;
    if (y1 > lbl_803EC898.y1 - 1) {
        y1 = lbl_803EC898.y1 - 1;
    }
    for (yy = y0; yy <= y1; yy++) {
        int xx;
        for (xx = x0; xx <= x1; xx++) {
            if (r >= ABS(x - xx) + ABS(y - yy) && lbl_803EC898.cost2S[(s8)xx + (s8)yy * 0x40] >= 0 && lbl_803EC898.b5S[(s8)xx + (s8)yy * 0x40] == 0 && !fn_801658E4(0, (s8)xx, (s8)yy) && lbl_803EC898.ter[0][(s8)xx + (s8)yy * 0x40]) {
                Unit* v = UnitGet(lbl_803EC898.ter[0][(s8)xx + (s8)yy * 0x40]);
                if (!SameT(u, v, 1) && (v->w3B4 & 1)) {
                    n++;
                }
            }
        }
    }
    return n;
}
}
