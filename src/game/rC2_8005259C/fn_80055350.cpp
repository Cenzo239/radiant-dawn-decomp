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
typedef struct P62 { u8 pad[0x30]; void* v[12]; u8 b[12]; s16 n; s16 m; } P62;
extern "C" int fn_80055350(void* parent) {
    u8 buf[24];
        UFull3* u;
    P62* p;
    int i;
    int k;

    p = (P62*)fn_80081194(lbl_8037DF20, parent);
    p->n = 0;
    p->m = 0;
    for (k = 0; k < 12; k++) { p->v[k] = 0; p->b[k] = 0; }
    fn_8010E41C(buf, 0);
    for (i = 1; i <= 0xfe; i++) {
        u = (UFull3*)GetU(i);
        if (u->ec == 0) continue;
        if (!buf[u->f4->b8]) continue;
        if (u->flags & 4) continue;
        if (fn_8010931C(u->sk)) continue;
        if (fn_8011B77C(u->x12c, lbl_804CA654)) {
            fn_8003A3BC(u, fn_8010B228(lbl_80361CF0 + 0x18));
            if (lbl_803E7320.i0 != 0 && p->n != 0xb) {
                p->v[p->n] = u;
                p->b[p->n] = 1;
                p->n++;
            }
        }
        if (fn_8011B77C(u->x12c, lbl_804CA658)) {
            fn_8003A664(u, fn_8010B228(lbl_80361CF0 + 0x21));
            if (lbl_803E7320.i0 != 0 && p->n != 0xb) {
                p->v[p->n] = u;
                p->b[p->n] = 2;
                p->n++;
            }
        }
    }
    if (p->n == 0) {
        fn_80081A90(p);
        return 0;
    }
    return 1;
}
