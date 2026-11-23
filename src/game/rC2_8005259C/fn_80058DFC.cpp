#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on
extern s8 lbl_804CB4D8; extern void* lbl_804CB4DC; extern u8 lbl_8037F080[];
extern s8 lbl_804CB4E0; extern void* lbl_804CB4E4; extern u8 lbl_8037F028[];
extern s8 lbl_804CB4E8; extern void* lbl_804CB4EC; extern u8 lbl_8037EFD0[];
extern s8 lbl_804CB4F0; extern void* lbl_804CB4F4; extern u8 lbl_8037EF78[];
extern s8 lbl_804CB4F8; extern void* lbl_804CB500; extern u8 lbl_8037EF20[];
extern s8 lbl_804CB508; extern void* lbl_804CB50C; extern u8 lbl_8037EEC8[];
extern s8 lbl_804CB510; extern void* lbl_804CB514; extern u8 lbl_8037E948[];
extern s8 lbl_804CB518; extern void* lbl_804CB51C; extern u8 lbl_8037E8F0[];
extern s8 lbl_804CB520; extern void* lbl_804CB524; extern u8 lbl_8037E898[];
extern s8 lbl_804CB528; extern void* lbl_804CB52C; extern u8 lbl_8037E840[];
extern s8 lbl_804CB530; extern void* lbl_804CB534; extern u8 lbl_8037E7E8[];
extern s8 lbl_804CB538; extern void* lbl_804CB53C; extern u8 lbl_8037E790[];
extern s8 lbl_804CB540; extern Lazy2 lbl_804CB548; extern u8 lbl_8037E1B4[]; extern u8 lbl_8037F328[];
struct Sally { u8 pad[0x954]; s8 n; s8 pairs[1]; };
extern "C" {
void* fn_800CFD18(Word*, int);
int fn_80057B7C(void*, int*);
int fn_80057A3C(void*, int*);
int fn_800578FC(void*, int*);
int fn_800577BC(void*, int*);
}

extern "C" void fn_80058DFC(void* p) {
    int a, b, c, d;
    Sally* g;
    s8* q;
    int i2;
    int i;
    void* tt;
    int n;
    if (!lbl_804CB818) fn_8012FCB0();
    fn_801856F4();
    {
        g = (Sally*)&lbl_803CAB38;
        n = g->n;
        fn_800CFB34(&lbl_803E7320);
        q = g->pairs;
        for (i = 0; i < n; i++) {
            fn_800CFC50(&lbl_803E7320, q[0], q[1], 0, 0);
            q += 2;
        }
    }
    if (lbl_803E7320.i0 >= 2) {
        for (i2 = 0; i2 < lbl_803E7320.i0; i2++) {
            tt = fn_800CFD18(&lbl_803E7320, i2);
            fn_80057B7C(tt, &a);
            fn_80057A3C(tt, &b);
            fn_800578FC(tt, &c);
            fn_800577BC(tt, &d);
        }
    }
    LAZY1(lbl_804CB4D8, lbl_804CB4DC, lbl_8037F080);
    LAZY1(lbl_804CB4E0, lbl_804CB4E4, lbl_8037F028);
    LAZY1(lbl_804CB4E8, lbl_804CB4EC, lbl_8037EFD0);
    LAZY1(lbl_804CB4F0, lbl_804CB4F4, lbl_8037EF78);
    LAZY1(lbl_804CB4F8, lbl_804CB500, lbl_8037EF20);
    LAZY1(lbl_804CB508, lbl_804CB50C, lbl_8037EEC8);
    LAZY1(lbl_804CB510, lbl_804CB514, lbl_8037E948);
    LAZY1(lbl_804CB518, lbl_804CB51C, lbl_8037E8F0);
    LAZY1(lbl_804CB520, lbl_804CB524, lbl_8037E898);
    LAZY1(lbl_804CB528, lbl_804CB52C, lbl_8037E840);
    LAZY1(lbl_804CB530, lbl_804CB534, lbl_8037E7E8);
    LAZY1(lbl_804CB538, lbl_804CB53C, lbl_8037E790);
    LAZY2(lbl_804CB540, lbl_804CB548, lbl_8037E1B4, lbl_8037F328);
    fn_800453B4(&lbl_803CA870, 0);
    fn_800D5448(&lbl_804CB548, p, 0);
    SALLY_TAIL(p);
}
