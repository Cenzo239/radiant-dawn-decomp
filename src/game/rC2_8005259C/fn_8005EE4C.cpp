#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on
extern "C" {
void fn_800E24F8(const char* s);
void fn_800C7B18(const char* s, int n);
#if TARGET_PC
FE10_PROTO void fn_8005449C(void* u);
#else
int fn_8005449C(void* u);
#endif
int fn_80089C88(int n);
typedef struct Cell { s8 x; s8 y; u8 fc; u8 p3; int a4; int a8; } Cell;
Cell* fn_800CFBFC(Word* w);
void fn_8005474C(void);
}
extern u8 lbl_8037DD88[];
extern s8 lbl_804CB460; extern void* lbl_804CB464; extern u8 lbl_8037EDC0[];
extern s8 lbl_804CB468; extern void* lbl_804CB46C; extern u8 lbl_8037ED68[];
extern s8 lbl_804CB470; extern void* lbl_804CB474; extern u8 lbl_8037ED10[];
extern s8 lbl_804CB478; extern void* lbl_804CB47C; extern u8 lbl_8037ECB8[];
extern s8 lbl_804CB480; extern Lazy2 lbl_804CB488; extern u8 lbl_8037E184[]; extern u8 lbl_8037F200[];
extern "C" int fn_8005EE4C(void* a, Menu* m, MenuEntry* e) {
    if (!fn_801E7024()) {
        HELP_XY();
        fn_801E6B64(lbl_8037F518, m, x, y);
        return 0;
    }
    {
    MenuProc* p;
    fn_800E24F8(lbl_8037F50C);
    fn_800E24F8(lbl_8037F500);
    fn_800C7B18(lbl_8037F4F0, 0);
    fn_800C7B18(lbl_8037F4E4, 0);
    fn_800C7B18(lbl_8037F4D4, 0);
    fn_800C7B18(lbl_8037F4C8, 0);
    fn_800C7B18(lbl_8037F4B8, 0);
    fn_800C7B18(lbl_8037F4AC, 0);
    fn_800453B4(&lbl_803CA870, 0x87);
    lbl_804CB550 = 0x87;
    p = m->proc;
    LAZY1(lbl_804CB460, lbl_804CB464, lbl_8037EDC0);
    LAZY1(lbl_804CB468, lbl_804CB46C, lbl_8037ED68);
    LAZY1(lbl_804CB470, lbl_804CB474, lbl_8037ED10);
    LAZY1(lbl_804CB478, lbl_804CB47C, lbl_8037ECB8);
    LAZY2(lbl_804CB480, lbl_804CB488, lbl_8037E184, lbl_8037F200);
    fn_800453B4(&lbl_803CA870, 0);
    fn_800D5448(&lbl_804CB488, p, 0);
    return 5;
    }
}
