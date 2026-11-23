#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct MEnt { u8 pad[0x18]; u8 b18; } MEnt;
typedef struct MObj { u8 pad[0x10]; u8* tbl; } MObj;
typedef struct Snd { u16 id; u16 k; } Snd;
typedef struct Sm { u8 pad[0x5C]; f32 f5C; u8 pad60[0x2C]; Snd s[4]; } Sm;

extern u8 lbl_803674B4[];
#if TARGET_PC
extern FE10_PROTO unsigned int fn_800F14B4(u32);
#else
extern void* fn_800F14B4(u32);
#endif
extern int fn_80007630(void*, char*);
extern Vec fn_800076E8(void*, int);
extern void fn_802549C4(void*, Vec, f32);
extern void fn_80253EE4(void*, f32);

#pragma auto_inline on
#pragma push
#pragma inline_depth(3)
static inline int fn_800F1490(MObj* o, int i, int j) {
    return (o->tbl + i * 0x30)[j + 0x18];
}
#pragma use_lmw_stmw on
int fn_800F130C(MObj* o, int i, int j) {
    if (j < 0) {
        int k;
        for (k = 0; k < 0x30; k++) {
            if (fn_800F130C(o, i, k)) return 1;
        }
    } else {
        if (fn_800F1490(o, i, j)) return 1;
    }
    return 0;
}
#pragma use_lmw_stmw off
#pragma pop
#pragma auto_inline off

