/* Round 19, not creditable by the tools: fn_80117F74 compiles to the original words plus one dead `blr`.
   That blr IS in the original: symbols.txt splits it off as the 4-byte "function" fn_80118008 (matched as an
   empty function in fn_empty.cpp). So this source reproduces fn_80117F74+fn_80118008 byte for byte, but check_func.py
   compares by symbol size and reports a size mismatch. fn_80118008 is not a real function. */
/* Tile bounds tests, tile position to world position, 8011799C, 80117A0C, 80118380. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
static inline BOOL In(Map* m, s8 x, s8 y) {
    if (x < m->x0 || x >= m->x1 || y < m->y0 || y >= m->y1) return 0;
    return 1;
}
BOOL fn_8011799C(Map* m, s8 x, s8 y);


static inline BOOL Ins(Map* m, s8 x, s8 y) {
    if (x < m->x0) return 0;
    if (x >= m->x1) return 0;
    if (y < m->y0) return 0;
    return y < m->y1;
}
BOOL fn_80117A0C(Map* m, s8 x, s8 y);

extern f32 fn_801142F0(Map*, f32, f32);
extern void fn_802549C4(void*, Vec*, f32);
void fn_80118380(Map* m, s8 x, s8 y, void* o);

}

/* ---- from build/tmp/r19hpbs/frag_hf74.cpp ---- */
extern "C" {
void fn_80117F74(const char* s, u8* d) {
    while (1) {
        switch (*s) {
        case 0:
            *d = 0x40;
            return;
        case '4':
            *d = 1;
            break;
        case '8':
            *d = 8;
            break;
        case '6':
            *d = 2;
            break;
        case '2':
            *d = 4;
            break;
        }
        s++;
        d++;
    }
}
}
