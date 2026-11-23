#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct BtlProc {
    u8 pad[0x34];
    Handle* h1;   /* 0x34 */
    u8 pad38[0xF];
    s8 b47;       /* 0x47 */
} BtlProc;

extern "C" {
extern u8 lbl_803672A0[];
#if TARGET_PC
extern FE10_PROTO char ** fn_801CE474(Handle*);
#else
extern BOOL fn_801CE474(Handle*);
#endif
extern GXColor fn_801125B4(void);
extern void fn_80103374(void*, GXColor, void*);
#if TARGET_PC
extern FE10_PROTO void fn_80102928(void*, s32, s32, s32, p32arg);
extern FE10_PROTO void fn_80102D70(void*, char*, p32arg, p32arg);
#else
extern void fn_80102928(void*, s32, s32, s32, s32);
extern void fn_80102D70(void*, char*, s32, s32);
#endif

void fn_800ECCCC(BtlProc* p) {
    void* a = HandleActor(p->h1);
    if (fn_801CE474(p->h1)) {
        fn_80103374(a, fn_801125B4(), p);
    }
    fn_80102928(a, p->b47, 8, 0, 0);
    fn_80102D70(a, (char*)lbl_803672A0 + 0xCA, 4, 0);
}
}
