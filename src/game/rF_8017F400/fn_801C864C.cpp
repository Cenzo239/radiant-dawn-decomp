#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* item effect registrars; lbl_8038AA20: pooled file statics, the classes themselves are not reproduced here */
extern void fn_80076D48(const char* name, void* cls);
extern char lbl_8036E538[];
extern void fn_801C7AF0(void);
extern void fn_801C7898(void);
static u8 p0[0x38], T0[0x14], T1[0x14], T2[0x14], T3[0x14], T4[0x14], T5[0x14], T6[0x14], T7[0x14], T8[0x14], T9[0x14], T10[0x14], T11[0x14], T12[0x14], T13[0x14];
void fn_801C864C(void) {
    const char* s = lbl_8036E538;
    fn_80076D48(s + 0x50, T0);
    fn_80076D48(s + 0x5D, T1);
    fn_80076D48(s + 0x6F, T2);
    fn_80076D48(s + 0x82, T3);
    fn_80076D48(s + 0x91, T4);
    fn_80076D48(s + 0x9F, T5);
    fn_80076D48(s + 0xB1, T6);
    fn_80076D48(s + 0xBF, T7);
    fn_80076D48(s + 0xD1, T8);
    fn_80076D48(s + 0xE3, T9);
    fn_80076D48(s + 0xF7, T9);
    fn_80076D48(s + 0x10C, T10);
    fn_80076D48(s + 0x11E, T11);
    fn_80076D48(s + 0x132, T11);
    fn_80076D48(s + 0x144, T11);
    fn_80076D48(s + 0x15A, T12);
    fn_80076D48(s + 0x16F, T13);
    fn_801C7AF0();
    fn_801C7898();
}
}
