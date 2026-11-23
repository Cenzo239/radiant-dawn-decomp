/* EXACT (round 23a): fn_80263D18 and fn_80263DE0, from equiv/fn_80263D18.cpp (fn_80263D18.cpp is an unrelated earlier file of this TU); declaration order ofs, c, n, col, l in both, found by a grid over declaration x initialisation orders. */
/* symcheck: r21 review. Fixed in both functions: the parameter is `char* s`, not `const char* s`. With const the compiler
   read `*s` for the end test BEFORE the `l[col] = 0` store, the original reads it AFTER (same block, so `sched` accepted
   it); the two differ if the text being split lies in the line buffer being written. Now both are class `regs` (same
   instruction order as the original; 16 and 14 words) and symcheck is clean. Declare them `char*` in callers. */
/* r19: self-contained (helpers of fn_80263418.cpp + wip fragment); `sched` level. */
/* Dictionary menu: relation chart draw and teardown */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

#pragma use_lmw_stmw on

extern "C" {

void fn_8007E5C0(f32 x, f32 y, f32 z, f32 a, f32 b, f32 sx, f32 sy, f32 c);
void fn_80266024(void);
void fn_802652DC(void* e, int a);
void fn_80265574(void* e);
void fn_80265840(void* a, void* b, int c);
void fn_8026654C(void);
void fn_8026697C(void);
void fn_802662EC(void);
void fn_800712E8(int x, int y, int a);
void fn_800C4AA8(void* p);
void fn_800C4240(void* p);
void fn_80263B64(void);
void fn_800763E0(const char* s);
void fn_801C6EAC(const char* a, const char* b, char* out);
void fn_80068C08(void);
extern int* lbl_804CC00C;


class DtorObj28 {
public:
    u8 pad[0x28];
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void dtor(int del);
};
void fn_802636F0(void);


}

/* ---- from rN_8025EEF0/wip/fn_80263D18.cpp ---- */
extern "C" {
/* fn_80263D18 (12 words) and fn_80263DE0 (10 words): loop-register colours and load of *s after the store. */
/* copies text into lines, skipping the 02 'm' 'c' and 02 'm' 'd' control sequences */
void fn_80263D18(char* s) {
/*P*/
    int ofs;
    int c;
    int n;
    int col;
    char* l;
/*E*/
    col = 0;
    n = 0;
    ofs = 0;
    for (;;) {
        c = *(u8*)s;
        if ((c == 2 && s[1] == 'm' && s[2] == 'c') || ((s8)c == 2 && s[1] == 'm' && s[2] == 'd')) {
            s += 3;
        } else if ((s8)c == 0 || (s8)c == '\n') {
            n++;
            l = *(char**)((u8*)lbl_804CC004->lines + ofs);
            ofs += 4;
            l[col] = 0;
            if (*s == 0) {
                break;
            }
            col = 0;
            s++;
        } else {
            s++;
            (*(char**)((u8*)lbl_804CC004->lines + ofs))[col] = c;
            col++;
        }
    }
    lbl_804CC004->nlines = n;
}

void fn_80263DE0(char* s) {
/*P*/
    int ofs;
    int c;
    int n;
    int col;
    char* l;
/*E*/
    col = 0;
    n = 0;
    ofs = 0;
    for (;;) {
        c = *(u8*)s;
        if ((s8)c == 0 || (s8)c == '\n') {
            n++;
            l = *(char**)((u8*)lbl_804CC008->lines + ofs);
            ofs += 4;
            l[col] = 0;
            if (*s == 0) {
                break;
            }
            col = 0;
            s++;
        } else {
            s++;
            (*(char**)((u8*)lbl_804CC008->lines + ofs))[col] = c;
            col++;
        }
    }
    lbl_804CC008->nlines = n;
}
}
