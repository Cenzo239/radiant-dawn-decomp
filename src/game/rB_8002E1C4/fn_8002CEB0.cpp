#include "game/rB_8002E1C4/battle.h"

struct MapS {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
    u8 pad100d[0xd18e - 0x100d];
    u16 xd18e[64 * 64];
};
struct Roll {
    u8 pad[0xa2];
    u8 xa2, xa3, xa4;
};
struct Terr { u8 pad[8]; u8* x8; };
struct GS2 { u8 pad[0x10]; u8 x10; u8 pad11[0xc0 - 0x11]; s16 xc0[4]; int xc8[4]; };
extern MapS lbl_803EC898;
#define M ((MapS*)&lbl_803EC898)
extern Roll lbl_803C8DA0;
extern u8 lbl_803CAB38[];
extern const char lbl_80361338[];
extern u8 lbl_804CB834;
extern void* lbl_804CA500;
extern void* lbl_804CA698;
extern "C" {
char* strcpy(char* d, const char* s);
int fn_8013B9CC(void);
void* fn_8013B9A8(void);
u8 fn_8013B664(void* p);
int fn_801148D8(MapS* m, int n);
void* fn_80078D9C(int n, const char* s, int k);
void fn_80078E24(void* p);
void fn_80114944(MapS* m, int n, void* p);
void fn_80114A44(MapS* m, int n, void* p);
void fn_80114B44(MapS* m, int a, int b);
Slot* fn_80030CBC(BU* p);
int fn_801107C0(void* d, BU* u);
int fn_801107A0(void* d, BU* u);
void fn_80115DEC(MapS* m, s8 x, s8 y, u8 a, u8 b);
u8* fn_80116A30(MapS* m, s8 x, s8 y);
Terr* fn_801181E8(MapS* m, s8 x, s8 y);
int fn_8011B77C(void* list, void* key);
const char* fn_80025FA4(void* p);
s8 fn_80025FC8(void* p);
#if TARGET_PC
FE10_PROTO const char* fn_8011D3A4(p32arg, char* s);
#else
const char* fn_8011D3A4(u32 k, char* s);
#endif
u32 fn_800689D4(BU* a, BU* d);
void fn_8002600C(void* log, int code, int v);
void fn_80027D9C(Battle* b, BU* a, BU* d, int k, int n);

static inline u8 rmax(Slot* w, BU* a) {
    if (w->data) return fn_801107C0(w->data, a);
    return 0;
}
static inline u8 rmin(Slot* w, BU* a) {
    if (w->data) return fn_801107A0(w->data, a);
    return 0;
}

#pragma use_lmw_stmw on
void fn_8002CEB0(Battle* b) {
    strcpy(b->s1604, (char*)lbl_803CAB38 + 0x914);
    b->f15fc = lbl_804CB834;
    if (fn_8013B9CC()) b->f15fd = fn_8013B664(fn_8013B9A8());
    else b->f15fd = 0;
    if (b->f15ec & 1) b->f15f8 = *(u32*)((u8*)&b->a + 0x460);
    else b->f15f8 = *(u32*)((u8*)&b->b + 0x460);
    {
    u32 f = b->f15ec;
    b->f15ec = f & ~0x4000000;
    if (!(f & 1) && b->f15e8 > 1) {
        int x = b->a.u.x102;
        int y = b->a.u.y103;
        int tx = b->b.u.x102;
        int ty = b->b.u.y103;
        void* buf = fn_80078D9C(-fn_801148D8(M, 9), lbl_80361338, 0);
        Slot* w;
        fn_80114944(M, 9, buf);
        w = fn_80030CBC(&b->a);
        fn_80114B44(M, 9, 0);
        {
        u8 mx = rmax(w, &b->a);
        fn_80115DEC(M, x, y, rmin(w, &b->a), mx);
        }
        if (lbl_803EC898.xd18e[tx + ty * 64]) {
            u8* r = fn_80116A30(M, tx, ty);
            while (*r != 0x40) {
                switch (*r) {
                case 1: x--; break;
                case 2: x++; break;
                case 4: y++; break;
                case 8: y--; break;
                }
                {
                Terr* t = fn_801181E8(M, x, y);
                if (t->x8[7] & 0x20) {
                    b->f15f8 = (u32)t;
                    b->f15ec |= 0x4000000;
                    break;
                }
                }
                r++;
            }
        }
        fn_80114A44(M, 9, buf);
        fn_80078E24(buf);
    }
    }
    {
    u32 f = b->f15ec;
    b->f15ec = f & ~0x2000000;
    if (!(f & 1) && fn_8011B77C(b->a.u.x12c, lbl_804CA500) && fn_8011B77C(b->b.u.x12c, lbl_804CA500)) {
        b->f15ec |= 0x2000000;
    }
    }
    b->s1624[0] = 0;
    if (b->f15ec & 0x4000) {
        if (fn_80025FA4(&lbl_803C8DA0)) strcpy(b->s1624, fn_80025FA4(&lbl_803C8DA0));
        if (fn_80025FC8(&lbl_803C8DA0) >= 0) b->f15fc = fn_80025FC8(&lbl_803C8DA0);
    }
    if (b->s1624[0] == 0 && b->f15f8) {
        const char* s = fn_8011D3A4(b->f15f8, b->s1604);
        if (s) strcpy(b->s1624, s);
    }
    b->f1600 = fn_800689D4(&b->a, &b->b);
    if ((b->f15ec & 0x4000) && lbl_803C8DA0.xa4) b->f1600 = 0;
}
#pragma use_lmw_stmw reset
}
