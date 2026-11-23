#include "game/rI_801DD7D4/types.h"
extern "C" {
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, int);
#endif
u32* fn_801116B8(void*);
int fn_8012BCB0(void*);
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E8;
#else
extern int lbl_804CA4E8;
#endif
}
struct It { int x0; u8 x4, x5; u8 p6[0x22]; };
struct U { u8 p[0x12c]; u8 x12c[0x90]; It it[7]; };
static inline BOOL fA(It* it) { return *fn_801116B8(it) & 0x1000000; }
static inline BOOL fB(It* it) { return (it->x5 >> 2) & 1; }
static inline BOOL isOk(It* it) { BOOL ok; ok = fA(it) || fB(it); return ok; }
extern "C" BOOL fn_801F15A4(U* u) {
/*P*/
    It* it;
    BOOL r;
    int i;
/*E*/
    r = 1;
    if (fn_8011B77C(u->x12c, lbl_804CA4E8)) {
        it = u->it;
        for (i = 0; i < 7; i++, it++) {
            if (it != 0 && it->x0 != 0) {
                if (!(fn_801116B8(it)[1] & 4)) {
                    if (!isOk(it)) { r = 0; break; }
                }
            }
        }
    } else {
        r = fn_8012BCB0(u);
    }
    return r;
}
