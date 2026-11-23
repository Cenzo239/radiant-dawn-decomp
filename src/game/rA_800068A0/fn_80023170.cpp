#include "game/rA_800068A0/types.h"
extern "C" {
extern u8 lbl_803C0210[];
extern u8* fn_8031F69C(void);
extern int fn_8031F6BC(u8*);
extern void fn_8031FF98(u8*);
void fn_80023170(void) {
    u8* cur = fn_8031F69C();
    u8* t = lbl_803C0210;
    if (cur == t) return;
    if (fn_8031F6BC(t) != 0) return;
    fn_8031FF98(t);
}
extern void* fn_801D5DC4(void);
extern int fn_8023F880(void*);
extern int fn_801D5F7C(void);
extern void fn_801D5DFC(void);
extern void* fn_80075FB4(void*, int);
extern void fn_80083B78(void*);
struct P { u8 x0[0x4C]; void* x4c; };
void fn_800232FC(P* p) {
    if (fn_8023F880(fn_801D5DC4()) == 0 || fn_801D5F7C() == 0) return;
    fn_801D5DFC();
    p->x4c = fn_80075FB4(fn_801D5DC4(), 0x80);
    fn_80083B78(p);
}
}
