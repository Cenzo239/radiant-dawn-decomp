#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void* fn_801E5640(void*, int, int);
#if TARGET_PC
FE10_PROTO void* fn_8010B22C(ptr32<const void>);
#else
void* fn_8010B22C(void*);
#endif
void fn_80222AD0(void*, void*, void*);
void** fn_8011A158(void*);
int fn_80129A8C(void*);
void fn_8012A440(void*, void*);
int fn_80060754(void*);
void* fn_801059B0(void);
int fn_80105194(void*);
void fn_80105260(void*, void*);
extern u8 lbl_803CA870[];
extern u8 lbl_803CAB38[];
struct B4 { u8 p[0x4c]; u8 a4c; };
struct S { u8 p[0x4c]; B4* a4c; };
void fn_80228900(S* s) {
/*P*/
    void** x;
    void* g;
    void* it;
    B4* b;
/*E*/
    fn_801E5640(s, 0x86, 0);
    it = fn_8010B22C(*(void**)(lbl_803CA870 + 0x18));
    x = NULL;
    { b = s->a4c; b->a4c = 0; fn_80222AD0(b, it, s); }
    g = *(void**)lbl_803CA870;
    if (it != NULL) x = fn_8011A158(it); else x = NULL;
    if (x == NULL) return;
    if (fn_80129A8C(g) >= 0) {
        fn_8012A440(g, *x);
        return;
    }
    if (fn_80060754(lbl_803CAB38) != 0 && fn_80105194(fn_801059B0()) >= 0) {
        fn_80105260(fn_801059B0(), *x);
    }
}
}
