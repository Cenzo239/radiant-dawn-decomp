#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void* fn_801E5640(void*, int, int);
#if TARGET_PC
FE10_PROTO void* fn_8010B22C(ptr32<const void>);
#else
void* fn_8010B22C(void*);
#endif
#if TARGET_PC
FE10_PROTO void fn_80222A58(void*, ptr32<const void>, ptr32<const void>);
#else
void fn_80222A58(void*, void*, void*);
#endif
void* fn_8011A158(void*);
s8 fn_8012C9BC(void*, void*);
s8 fn_8012BD30(void*, void*);
void fn_8012A80C(void*, int);
int fn_80060754(void*);
void* fn_801059B0(void);
int fn_80105328(void*, void*);
void fn_801053DC(void*, int);
void* memset(void*, int, u32);
extern u8 lbl_803CA870[];
extern u8 lbl_803CAB38[];
extern int lbl_804CAA70;
extern u8* lbl_804CB810;
struct S { u8 p[0x4c]; void* a4c; };
struct J { u8 p[8]; u8 cls; };
struct Un { u8 p[0xec]; void* aec; u8 pf0[4]; J* af4; };
struct Rv { u8 c[3]; };
static inline Un* unitAt(u8 id) { if (id != 0) return (Un*)(lbl_804CB810 + (id - 1) * 0x3f0); return NULL; }
static inline void mk(u8* buf, u8* t) { for (u8* q = t; *q != 0xff; q++) buf[*q] = 1; }
static inline void useK(int k) { fn_801053DC(fn_801059B0(), k); }
void fn_801053DC2(int);
void fn_8022776C(S* s) {
/*P*/
    void* it;
    void* g;
    void* x;
    Un* u;
    int i;
    u8* q;
    int n;
/*E*/
    u8 buf[0xb];
    fn_801E5640(s, 0x86, 0);
    it = fn_8010B22C(*(void**)(lbl_803CA870 + 0x18));
    fn_80222A58(s->a4c, it, s);
    g = *(void**)lbl_803CA870;
    if (it != NULL) x = fn_8011A158(it); else x = NULL;
    if (x == NULL) return;
    if (fn_8012C9BC(g, x) >= 0) {
        fn_8012A80C(g, fn_8012BD30(g, x));
        return;
    }
    if (fn_80060754(lbl_803CAB38) != 0 && fn_80105328(fn_801059B0(), x) >= 0) {
        useK(fn_80105328(fn_801059B0(), x));
        return;
    }
    {
        u8 t[3] = {0, 5, 0xff};
        memset(buf, (u8)lbl_804CAA70, 0xb);
        u8 kk; q = t; while ((kk = *q) != 0xff) { buf[kk] = 1; q++; }
    }
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->aec != NULL && buf[u->af4->cls] != 0 && fn_8012C9BC(u, x) >= 0) {
            fn_8012A80C(u, fn_8012BD30(u, x));
            return;
        }
    }
}
}
