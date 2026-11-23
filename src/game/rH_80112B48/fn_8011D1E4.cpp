/* Terrain id from its name hash, 8011D1E4. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern u32 lbl_80413098[];
static inline u32 SH(const char* s) { u32 h = 0; const u8* p=(const u8*)s; while ((s8)*p != 0) { h += *p; p++; h <<= 4; } return h; }
u8 fn_8011D1E4(const char* s) {
    u32 h = SH(s);
    u32* d;
    int i;
    d = lbl_80413098;
    for (i = 0; i < 0xc7; i++) {
        if (h == *d) {
            switch (i) {
            case 0xb0:
            case 0xb6:
                return 0xb6;
            }
            return i;
        }
        d++;
    }
    return 0;
}
}
