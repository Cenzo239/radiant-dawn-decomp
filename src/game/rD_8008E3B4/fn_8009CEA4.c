#include "game/rD_8008E3B4/types.h"

#pragma use_lmw_stmw on

void fn_800C3C3C(const char* name, void* func, int nargs);
extern char lbl_803649D4[];
#if TARGET_PC
FE10_PROTO int fn_8009CA68(void);
FE10_PROTO int fn_8009CAF4(char *);
FE10_PROTO int fn_8009CC50(char *);
FE10_PROTO int fn_8009CD1C(char *);
FE10_PROTO int fn_8009CD9C(void);
FE10_PROTO int fn_8009CDF8(void);
FE10_PROTO int fn_8009CE68(int);
#else
void fn_8009CA68();
void fn_8009CAF4();
void fn_8009CC50();
void fn_8009CD1C();
void fn_8009CD9C();
void fn_8009CDF8();
void fn_8009CE68();
#endif

void fn_8009CEA4(void)
{
    fn_800C3C3C(lbl_803649D4 + 0x22, fn_8009CA68, 0);
    fn_800C3C3C(lbl_803649D4 + 0x33, fn_8009CAF4, 1);
    fn_800C3C3C(lbl_803649D4 + 0x48, fn_8009CC50, 1);
    fn_800C3C3C(lbl_803649D4 + 0x58, fn_8009CD1C, 1);
    fn_800C3C3C(lbl_803649D4 + 0x6b, fn_8009CD9C, 0);
    fn_800C3C3C(lbl_803649D4 + 0x7b, fn_8009CDF8, 0);
    fn_800C3C3C(lbl_803649D4 + 0x8a, fn_8009CE68, 1);
}
