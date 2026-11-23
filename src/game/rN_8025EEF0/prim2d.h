#ifndef RN_8025EEF0_PRIM2D_H
#define RN_8025EEF0_PRIM2D_H
#include "game/rN_8025EEF0/calls.h"
/* Prim2D API of rJ_800799AC/fn_8007DEE4.cpp */
extern "C" {
void fn_8007E154(void);                        /* begin state */
void fn_8007E164(void);                        /* end state */
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int b);
FE10_PROTO void fn_8007E374(void* tex, p32arg, int f);
#else
void fn_8007E174(int a, int b);
void fn_8007E374(void* tex, int a, int f);
#endif
void fn_8007E4E4(f32 x, f32 y, f32 z, f32 s);  /* transform */
void fn_8007E7DC(int alpha);
void fn_800800D4(int type);
void fn_80080430(f32 x, f32 y, f32 u, f32 v, f32 w, f32 h);
void fn_80080578(int mode);
void fn_80080308(void);
}
#endif
