/* Tile and skill healing at the start of a unit's turn. */
#include "game/rC2_8005259C/base.h"
struct TileD { u8 pad[6]; u8 heal; u8 flags; };
struct Tile { u8 pad[8]; TileD* d; };
struct MU { u8 pad[0xfc]; u8 bfc; u8 p[5]; u8 x; u8 y; u8 p104[0x10]; s8 hp; u8 p115[0x17]; u8 a12c[1]; };
struct Item { u32 f0; };
struct Ent { s8 x, y; u8 c; int a4; int a8; };
extern "C" {
extern u8 lbl_803EC898[];
extern u8 lbl_803E7320[];
extern void* lbl_804CA6C0;
extern void* lbl_804CA6C4;
extern void* lbl_804CA63C;
s16 fn_801237EC(MU*);
s16 fn_80122880(MU*);
s16 fn_80123D1C(MU*);
int fn_8011799C(void*, int, int);
Tile* fn_801181E8(void*, int, int);
int fn_8011B77C(void*, void*);
Item* fn_8012759C(MU*);
Item* fn_801116B8(Item*);
int fn_801C875C(u32);
Ent* fn_800CFBFC(void*);
}
static inline int dirBit(int i) {
    switch (i) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 8;
    default: return 0x40;
    }
}
static inline int dirX(int d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    default: return 0;
    }
}
static inline int dirY(int d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    default: return 0;
    }
}

#pragma use_lmw_stmw on
extern "C" void fn_8005449C(MU* u) {
    int sum;
    int x;
    int y;
    int ny;
    int nx;
    Tile* t;
    int i;
    int hp;
    int d;
    sum = 0;
    hp = (s8)u->hp;
    if (hp != fn_801237EC(u)) {
        y = *(s8*)&u->y;
        x = *(s8*)&u->x;
        for (i = 0; i < 4; i++) {
            switch (i) {
            case 0: d = 1; break;
            case 1: d = 2; break;
            case 2: d = 4; break;
            case 3: d = 8; break;
            default: d = 0x40; break;
            }
            nx = x + dirX(d);
            ny = y + dirY(d);
            if (fn_8011799C(lbl_803EC898, (s8)nx, (s8)ny)) {
                t = fn_801181E8(lbl_803EC898, (s8)nx, (s8)ny);
                switch (t->d->flags & 0x40) {
                case 0:
                    break;
                default:
                    goto found;
                }
            }
        next:;
        }
        t = 0;
    found:
        if (!t) {
            t = fn_801181E8(lbl_803EC898, (s8)u->x, (s8)u->y);
        }
        if (t) {
            u8 k = t->d->heal;
            if (k) {
                int h = fn_801237EC(u);
                sum = h * k / 100;
            }
        }
        if (fn_8011B77C(u->a12c, lbl_804CA6C0)) {
            sum += fn_801237EC(u) / 10;
        }
        if (fn_8011B77C(u->a12c, lbl_804CA6C4)) {
            sum += fn_80122880(u);
        }
        if (fn_8011B77C(u->a12c, lbl_804CA63C)) {
            sum += fn_80123D1C(u);
        }
        if (fn_8012759C(u) && (fn_801116B8(fn_8012759C(u))->f0 & 0x40000)) {
            sum += fn_801C875C(fn_8012759C(u)->f0);
        }
        if (sum) {
            Ent* e = fn_800CFBFC(lbl_803E7320);
            u8 c = u->bfc; u8 y = u->y; u8 xx = u->x; e->x = xx; e->y = y; e->c = c; e->a4 = 0; e->a8 = sum;
        }
    }
}
