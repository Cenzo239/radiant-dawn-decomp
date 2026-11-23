#pragma auto_inline off
extern "C" {
#include "game/rI_801DD7D4/fn_shop.h"
#define BODY_fn_80206E14(FN, AT) \
void FN(Sc* o) { \
    VL* w; \
    int** p; \
    int it; \
    int k; \
    int pr; \
    W* h; \
    w = *(VL**)&o->x4c; \
    p = (int**)AT(w, w->v34()); \
    ((W*)w)->x51 = 1; \
    fn_801E5954(o); \
    if (p != (int**)AT(w, w->v34())) { \
        p = (int**)AT(w, w->v34()); \
        if (fn_801A2224(lbl_8041EB20) != 0) { \
            if (p != NULL) { \
                Pt q = mk(((VS*)w)->v48()); \
                fn_801A1F64(lbl_8041EB20, (int)*p, q.x, q.y); \
            } else { \
                fn_801A1CFC(lbl_8041EB20); \
            } \
        } \
    } \
    h = fn_801E5640(o, 1, 0); \
    *(int*)((u8*)h + 0x40) = p != NULL ? (int)*p : 0; \
    if (((W*)w)->x50 == 0 && !inputBlocked()) { \
        k = ((VS*)lbl_804CB5B8)->v48(); \
        if ((k & 0x400) && p != NULL && fn_801A2224(lbl_8041EB20) == 0) { \
            it = (int)*p; \
            pr = PRICE(o, it); \
            if (pr > fn_800626E0(lbl_803CAB38)) { \
                SND(0x74); \
                fn_8014C2AC(o->x64->x34); \
                HELP(o, x74); \
                o->x5e = 4; \
                fn_80083DC4(o, 0x13); \
            } else { \
                SND(0x82); \
                if (((Item*)it)->x26 == 0xff) { \
                    fn_80083DC4(o, 7); \
                } else { \
                    fn_80083DC4(o, 0xa); \
                } \
            } \
        } else if ((k & 0x2000) && fn_801A2224(lbl_8041EB20) == 0 && p != NULL) { \
            Pt q = mk(((VS*)w)->v48()); \
            fn_801A1BE0(lbl_8041EB20, o, (int)*p, q.x, q.y); \
            *(u32*)lbl_8041EB20 |= 2; \
        } else if ((k & 0x2800) && fn_801A2224(lbl_8041EB20) != 0) { \
            fn_801A1CFC(lbl_8041EB20); \
        } else if ((k & 0x800) && fn_801A2224(lbl_8041EB20) == 0) { \
            ((W*)w)->x51 = 0; \
            mvx(o, h, 0x1a2); \
            fn_80083DC4(o, 0x1a); \
            SND(0x92); \
        } \
    } \
}
BODY_fn_80206E14(fn_80206E14, atA)
BODY_fn_80206E14(fn_8020C3CC, atB)
}
