#include "game/rD_8008E3B4/types.h"

#pragma use_lmw_stmw on

/* Own file because fn_8012E8A0 takes a second argument here: `extsb. r4, r31` leaves ia in r4
 * for the call. fn_8008E3B4.c declares it with one argument. */
void* fn_8012CE54(void* pid);
s8 fn_8012E9B4(void* a, void* b);
void fn_8012E8A0(void* a, s8 i);
int fn_8012E8BC(void* a, s8 i);
#if TARGET_PC
FE10_PROTO void * fn_8012E390(void* a);
#else
int fn_8012E390(void* a);
#endif
void fn_8012EDA0(void* a, int v);
void fn_8012E398(void* a, void* b);
void fn_8012E88C(void* a, s8 i, u8 v);
extern u8* lbl_804CB808;

int fn_80091BAC(void* pidA, void* pidB)
{
    u8* a = fn_8012CE54(pidA);
    u8* b = fn_8012CE54(pidB);
    s8 ia;
    s8 ib;
    if (a == NULL || b == NULL) {
        return -1;
    }
    ia = fn_8012E9B4(a, b);
    ib = fn_8012E9B4(b, a);
    if (ia < 0 || ib < 0) {
        return -1;
    }
    fn_8012E8A0(a, ia);
    return (u8)fn_8012E8BC(a, ia);
}

/* PersonSetYellLevel */
int fn_80091C5C(void* pidA, void* pidB, int level)
{
    u8* a = fn_8012CE54(pidA);
    u8* b = fn_8012CE54(pidB);
    int ia;
    int ib;
    u8 v;
    u8* t;
    if (a == NULL || b == NULL) {
        return -1;
    }
    if (fn_8012E390(a) != 0) {
        fn_8012EDA0(a, fn_8012E390(a));
    }
    if (fn_8012E390(b) != 0) {
        fn_8012EDA0(b, fn_8012E390(b));
    }
    ia = fn_8012E9B4(a, b);
    ib = fn_8012E9B4(b, a);
    if (ia < 0 || ib < 0) {
        return -1;
    }
    t = lbl_804CB808;
    v = 0;
    switch (level) {
    case 0:
        v = t[0];
        break;
    case 1:
        v = t[1];
        break;
    case 2:
        v = t[2];
        break;
    case 3:
        v = t[3];
        break;
    }
    if (level != 0) {
        fn_8012E398(a, b);
        fn_8012E398(b, a);
    }
    fn_8012E88C(a, ia, v);
    fn_8012E88C(b, ib, v);
    return v;
}
