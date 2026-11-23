#include "game/auto/m2c_prelude.h"
#if TARGET_PC
/* Host: lbl_804CB7B0 is a pointer (TerrainData records), not s32 */
extern u8* lbl_804CB7B0;

u8* fn_8010B240(s32 arg0) {
    return lbl_804CB7B0 + ((arg0 * 0x10) & 0xFF0);
}
#else
extern s32 lbl_804CB7B0;

s32 fn_8010B240(s32 arg0) {
    return lbl_804CB7B0 + ((arg0 * 0x10) & 0xFF0);
}
#endif
