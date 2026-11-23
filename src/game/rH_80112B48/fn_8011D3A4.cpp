/* Battle terrain name lookup, 8011D3A4. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern u32 lbl_80413098[];
extern char lbl_80368FB8[];
extern u8* fn_80077064(char*);
extern u16 fn_80109A2C(u8**);
#if TARGET_PC
extern FE10_PROTO ptr32<char> fn_80109A88(u8**);
#else
extern char* fn_80109A88(u8**);
#endif
extern int fn_80291188(const char*, const char*);
static inline u32 SH(const u8* s0) { const u8* p=s0; u32 h = 0; while ((s8)*p != 0) { h += *p; p++; h <<= 4; } return h; }
static inline u8 TerrainId(u32 h) {
    u32* d = lbl_80413098;
    int i;
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
#pragma use_lmw_stmw on
char* fn_8011D3A4(char** t, const char* s) {
    int off;
    u8* p;
    int stride;
    int id;
    int ofs2;
    int cols;
    int rows;
    int row;
    int i;
    int k;
    u8* q1;
    u8* q2;
    id = TerrainId(SH((const u8*)*t));
    p = fn_80077064(lbl_80368FB8);
    cols = fn_80109A2C(&p);
    rows = fn_80109A2C(&p);
    cols += cols % 2;
    row = -1;
    if (s == 0 || *s == 0) {
        row = 0;
    } else {
        i = 0;
        stride = cols * 2 + 4;
        off = 0;
        for (; i < rows; i++) {
            q1 = p + off;
            if (fn_80291188(fn_80109A88(&q1), s) == 0) {
                row = i;
                break;
            }
            off += stride;
        }
        if (row < 0) {
            return lbl_80368FB8 + 0x10;
        }
    }
    ofs2 = row * (cols * 2 + 4);
    {u16* b = (u16*)(p + ofs2 + 4); q2 = (u8*)&b[id];}
    k = (s16)fn_80109A2C(&q2);
    if (k < 0) {
        q2 = p + ofs2 + 4;
        k = (s16)fn_80109A2C(&q2);
    }
    p = fn_80077064(lbl_80368FB8 + 0x17);
    p += k * 4;
    return fn_80109A88(&p);
}
}
