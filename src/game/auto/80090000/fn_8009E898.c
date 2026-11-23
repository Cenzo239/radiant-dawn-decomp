#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
#else
s32 fn_80083B84();
#endif
#if TARGET_PC
FE10_PROTO void * fn_800A2918(void);
#else
M2C_UNK fn_800A2918();
#endif
extern u8 lbl_80381B80[0x54];

void
#if TARGET_PC
*
#endif
fn_8009E898(void) {
#if TARGET_PC
    void *p = fn_80083B84(lbl_80381B80);
    if (p == 0) {
        p = fn_800A2918();
    }
    return p;
#else
    if (fn_80083B84(lbl_80381B80) == 0) {
        fn_800A2918();
    }
#endif
}
