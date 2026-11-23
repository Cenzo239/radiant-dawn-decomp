#include "game/rI_801DD7D4/types.h"
extern "C" {
struct UB { u32 x0, x4; };
UB* fn_801116B8(void*);
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, int);
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E8;
#else
extern int lbl_804CA4E8;
#endif
struct IS { int x0; u8 x4; u8 x5a : 3; u8 x5b : 1; u8 x5c : 4; u8 p[0x22]; };
static inline BOOL isOk(IS* it) {
    return 0;
}
BOOL fn_801F1688(u8* u) {
        int o2;
    IS* i2;
    IS* it;
    int ok;
    int r;
    int i;
    r = 1;
    if (fn_8011B77C(u + 0x12c, lbl_804CA4E8)) {
        it = (IS*)(u + 0x1bc);
        for (i = 0; i < 7; i++, it++) {
            if (it && it->x0) {
                ok = 1;
                if ((fn_801116B8(it)->x0 & 0x20000) == 0) { if (!it->x5b) ok = 0; }
                if (!ok && !(fn_801116B8(it)->x4 & 4)) {
                    r = 0;
                    break;
                }
            }
        }
    } else {
        i2 = (IS*)(u + 0x1bc);
        for (int j = 0; j < 7; j++, i2++) {
            if (i2 && i2->x0) {
                o2 = 1;
                if ((fn_801116B8(i2)->x0 & 0x20000) == 0) { if (!i2->x5b) o2 = 0; }
                if (!o2) {
                    r = 0;
                    break;
                }
            }
        }
    }
    return r;
}
}
