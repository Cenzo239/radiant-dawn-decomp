#include "game/rA_800068A0/types.h"
/* Merges two 4-entry key lists into one, padding the rest with 0xFFFF. */
extern "C" {
typedef struct GKey { u16 id; s16 val; } GKey;
extern char lbl_80360B08[];
extern void fn_8001E008(const char* file, int line, const char* msg);
int fn_8000A460(GKey* a, GKey* b, GKey* out) {
    GKey t[4];
    int n = 0;
    int i, j;
    for (j = 0; j < 4; a++, b++, j++) {
        if (((const GKey*)a)->id != 0xFFFF) {
            t[n].id = a->id;
            t[n].val = a->val;
            n++;
        }
        if (((const GKey*)b)->id != 0xFFFF) {
            t[n].id = b->id;
            t[n].val = b->val;
            n++;
        }
    }
    if (n > 4) {
        fn_8001E008(lbl_80360B08, 0x10A, lbl_80360B08 + 0x35);
    }
    for (i = 0; i < n; i++) {
        out[i].id = t[i].id;
        out[i].val = t[i].val;
    }
    for (i = n; i < 4; i++) {
        out[i].id = 0xFFFF;
    }
    return n;
}
}
