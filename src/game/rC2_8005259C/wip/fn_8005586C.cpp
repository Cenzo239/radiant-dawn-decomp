/* NEAR MISS: 10 of 88 words. Hoisted registers differ (want &lbl_803CA870 in r31, the 0x100 constant
 * in r30, buf in r29). fn_80055DE8, the same loop without the range test, matches. */
#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on
extern "C" {
int fn_8010931C(void* p);
void* fn_8010B228(const char* s);
void fn_8003A3BC(void* u, void* it);
void fn_8003A664(void* u, void* it);
}
extern u8 lbl_8037DF20[];
extern char lbl_80361CF0[48];
extern void* lbl_804CA654;
extern void* lbl_804CA658;
typedef struct UFull3 { u8 pad[0xec]; void* ec; u8 padf0[4]; UnitSub* f4; u8 padf8[4]; u8 fc; u8 padfd[5]; s8 x; s8 y; u8 pad104[8]; u32 flags; u8 sk[0x12c-0x110]; u8 x12c[4]; } UFull3;
static inline int iabs(int v) { return v < 0 ? -v : v; }
typedef struct Sort1 { u8 b; } Sort1;
extern "C" void fn_80056338(void* a, void* b, Sort1 c);
typedef struct UP { u8 s[0x24]; } UP;
#define LAYER (lbl_803E7320.i0)
#define TILES ((UP*)((u8*)&lbl_803E7320 + 8))
typedef struct Ly { int n; int p4; UP a[1]; } Ly;
#define LY ((Ly*)&lbl_803E7320)
typedef struct CS { u8 pad[0x11]; s8 x; s8 y; u8 p13[0x24-0x13]; int r; } CS;
extern "C" void fn_8005586C(void* parent) {
    u8 buf[24];
        int dy;
    int i;
    UFull3* u;
    int dx;

        Sort1 s1;
    fn_800CFB34(&lbl_803E7320);
    fn_8010E41C(buf, 1);
    for (i = 1; i <= 0xfe; i++) {
        u = (UFull3*)GetU(i);
        if (u->ec == 0) continue;
        if (!buf[u->f4->b8]) continue;
        if (u->flags & 0x10000dc) continue;
        {
        s8 uy = u->y;
        s8 ux = u->x;
        dy = lbl_803CA870.y12 - uy;
        dx = lbl_803CA870.x11 - ux;
        if (((CS*)&lbl_803CA870)->r >= iabs(dx) + iabs(dy)) {
            fn_800CFC50(&lbl_803E7320, ux, uy, u->fc, iabs(dx) + iabs(dy));
        }
        }
    }
    fn_80056338((UP*)(lbl_803E7320.pad+4), (UP*)(lbl_803E7320.pad+4)+lbl_803E7320.i0, s1);
    fn_800E8844(parent, 0);
}
typedef struct P62 { u8 pad[0x30]; void* v[12]; u8 b[12]; s16 n; s16 m; } P62;
