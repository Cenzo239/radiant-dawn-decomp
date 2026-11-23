#include "game/rA_800068A0/types.h"

/* GModel resource acquire/release (same pattern as GAnim_Get in
 * fn_8000BD3C.c; fn_8000E9DC relocates the model data). */

typedef struct GModel GModel;

extern GModel* fn_8023F1A4(void* res, u32 x);
#if TARGET_PC
extern FE10_PROTO void fn_8023F1A8(unsigned int);
#else
extern void fn_8023F1A8(void* res);
#endif
extern u32 fn_8023F7B8(void* res);
extern void fn_8023F7EC(void* res, u32 flags);
extern void fn_8000E9DC(GModel* m);

/* GModel_Get */
GModel* fn_8000EB68(void* res) {
    GModel* m = fn_8023F1A4(res, 0);
    if (!(fn_8023F7B8(res) & 0x400000)) {
        fn_8000E9DC(m);
        fn_8023F7EC(res, 0x400000);
    }
    return m;
}

/* GModel_GetEx */
GModel* fn_8000EBCC(void* res, u32 x) {
    GModel* m = fn_8023F1A4(res, x);
    if (!(fn_8023F7B8(res) & 0x400000)) {
        fn_8000E9DC(m);
        fn_8023F7EC(res, 0x400000);
    }
    return m;
}

/* GModel_Release */
void fn_8000EC2C(GModel* m) {
    fn_8023F1A8(m);
}
