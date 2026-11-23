/* fn_80235098 (round 22, agent r22b): exact.
 * Revolution DEMO library, __DEMOInitRenderMode(mode): copy the caller's GXRenderModeObj
 * into the static lbl_8041F030 (`rmodeobj = *mode`; the implicit C++ copy gives the bytewise
 * sample_pattern pairs), else pick the default mode for VIGetTvFormat() (NTSC, PAL, EURGB60,
 * MPAL), trim 16 lines with GXAdjustForOverscan (fn_80304638) and use the static copy.
 * lbl_804CBF28 = rmode. The round-7 fragment copied field by field; the plain struct
 * assignment is the original.
 */
#include "game/rI_801DD7D4/types.h"
extern "C" {
/* GXRenderModeObj */
typedef struct RM {
    u32 viTVmode;
    u16 fbWidth, efbHeight, xfbHeight, viXOrigin, viYOrigin, viWidth, viHeight;
    u32 xFBmode;
    u8 field_rendering, aa;
    u8 sample_pattern[12][2];
    u8 vfilter[7];
} RM;
extern RM lbl_8041F030;
extern RM lbl_803A03F8, lbl_803A0470, lbl_803A04AC, lbl_803A0434;
extern RM* lbl_804CBF28;
extern char lbl_803726A8[];
int VIGetTvFormat(void);
void OSPanic(const char*, int, const char*, ...);
void fn_80304638(const RM*, RM*, u16, u16);
void fn_80235098(const RM* m) {
    if (m != NULL) {
        lbl_8041F030 = *m;
        lbl_804CBF28 = &lbl_8041F030;
    } else {
        switch (VIGetTvFormat()) {
        case 0: lbl_804CBF28 = &lbl_803A03F8; break;
        case 1: lbl_804CBF28 = &lbl_803A0470; break;
        case 5: lbl_804CBF28 = &lbl_803A04AC; break;
        case 2: lbl_804CBF28 = &lbl_803A0434; break;
        default:
            OSPanic(lbl_803726A8, 0xbf, lbl_803726A8 + 0xb);
        }
        fn_80304638(lbl_804CBF28, &lbl_8041F030, 0, 0x10);
        lbl_804CBF28 = &lbl_8041F030;
    }
}
}
