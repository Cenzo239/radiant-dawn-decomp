#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* item effect registrars */
extern void fn_80076D48(const char* name, void* cls);
extern char lbl_8036E3E0[], lbl_8036E538[], lbl_8036E6D8[];
extern u8 lbl_8038A990[], lbl_8038AA20[], lbl_8038AB70[];
extern void fn_801C7AF0(void);
extern void fn_801C7898(void);
/* lbl_8038A990: pooled file statics, the classes themselves are not reproduced here */
static u8 s0[0x14], s1[0x14], s2[0x14], s3[0x14], s4[0x14], s5[0x14];
void fn_801C7898(void) {
    const char* s;
    fn_80076D48(lbl_8036E3E0, s0);
    s = lbl_8036E3E0;
    fn_80076D48(s + 0x14, s1);
    fn_80076D48(s + 0x28, s1);
    fn_80076D48(s + 0x3A, s2);
    fn_80076D48(s + 0x4C, s2);
    fn_80076D48(s + 0x5F, s2);
    fn_80076D48(s + 0x74, s2);
    fn_80076D48(s + 0x87, s2);
    fn_80076D48(s + 0x99, s2);
    fn_80076D48(s + 0xAD, s2);
    fn_80076D48(s + 0xC2, s2);
    fn_80076D48(s + 0xD3, s3);
    fn_80076D48(s + 0xE1, s3);
    fn_80076D48(s + 0xF5, s4);
    fn_80076D48(s + 0x108, s5);
}



}
