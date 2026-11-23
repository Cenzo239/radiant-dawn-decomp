#include "game/rD_8008E3B4/types.h"

#pragma use_lmw_stmw on

void fn_800C3C3C(const char* name, void* func, int nargs);
extern char lbl_80364968[];
#if TARGET_PC
FE10_PROTO int fn_8009C5C4(void);
FE10_PROTO int fn_8009C5F8(void);
FE10_PROTO int fn_8009C62C(void);
FE10_PROTO int fn_8009C674(void);
FE10_PROTO int fn_8009C6A8(void);
#else
void fn_8009C5C4();
void fn_8009C5F8();
void fn_8009C62C();
void fn_8009C674();
void fn_8009C6A8();
#endif

void fn_8009C6DC(void)
{
    fn_800C3C3C(lbl_80364968 + 0x14, fn_8009C5C4, 0);
    fn_800C3C3C(lbl_80364968 + 0x1d, fn_8009C5F8, 0);
    fn_800C3C3C(lbl_80364968 + 0x27, fn_8009C62C, 0);
    fn_800C3C3C(lbl_80364968 + 0x31, fn_8009C674, 0);
    fn_800C3C3C(lbl_80364968 + 0x3b, fn_8009C6A8, 0);
}
