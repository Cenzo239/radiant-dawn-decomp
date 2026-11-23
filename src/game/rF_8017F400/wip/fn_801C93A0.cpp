/* near miss: fn_801C93A0, 25 lines: saved registers rotated (the parameter wants r31 above the hoisted global addresses, o wants r27). Spellings of every global access, named pointers and a wrapper changed nothing. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct Act { u8* unit; void* x4; u8 pad[6]; s8 xE; } Act;
extern Act lbl_803CA870;
extern u8 lbl_803EC898[];
extern u8 lbl_803C8E80[];
extern void fn_8012152C(void*, s8*, s8*);
extern void fn_80126EB0(void*, int, int);
extern void fn_80114D00(void*);
extern void fn_80026C44(void*, u8*, void*);
extern void fn_8002C0EC(void*, int);
extern void fn_8006C794(void*);
extern void fn_800E8C54(int, int, void*);
#pragma use_lmw_stmw on
int fn_801C93A0(void* p0) {
/*P*/
    void* p;
    Act* a;
    void* o;
/*E*/
    s8 x;
    s8 y;
    p = p0;
    a = &lbl_803CA870;
    o = a->x4;
    x = lbl_803CA870.unit[0x102];
    y = lbl_803CA870.unit[0x103];
    lbl_803EC898[x + y * 0x40 + 0xD] = 0xFF;
    fn_8012152C(o, &x, &y);
    fn_80126EB0(o, x, (s8)*(u8*)&y);
    fn_80114D00(lbl_803EC898);
    fn_80026C44(lbl_803C8E80, lbl_803CA870.unit, a->x4);
    fn_8002C0EC(lbl_803C8E80, (s8)*(u8*)&a->xE);
    fn_8006C794(lbl_803C8E80);
    fn_800E8C54(x, y, p);
    return 1;
}
#pragma use_lmw_stmw off
}
