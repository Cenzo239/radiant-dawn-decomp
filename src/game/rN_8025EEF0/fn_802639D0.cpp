/* Dictionary menu: tables, loaders */
#include "game/rN_8025EEF0/dict.h"

extern "C" {

void* fn_80075D78(const char* path);
void fn_800761F0(void* p);
extern int* lbl_804CC00C;
extern int* lbl_804CC010;

void fn_802639D0(void) {
    if (lbl_804CC00C == 0) {
        int* raw = (int*)fn_80075D78(lbl_80372C90 + 0x1D8);
        lbl_804CC00C = raw;
        lbl_804306E8.raw = raw;
        DictF8* t0;
        Dict14* t1;
        int* c1;
        Dict18* t2;
        int* c2;
        Dict10* t3;
        int* c3;
        int* c4;
        t0 = (DictF8*)(raw + 1);
        lbl_804306E8.t0 = t0;
        c1 = (int*)(t0 + *raw);
        t1 = (Dict14*)(c1 + 1);
        lbl_804306E8.cnt1 = c1;
        lbl_804306E8.t1 = t1;
        c2 = (int*)(t1 + *c1);
        t2 = (Dict18*)(c2 + 1);
        lbl_804306E8.cnt2 = c2;
        lbl_804306E8.t2 = t2;
        c3 = (int*)(t2 + *c2);
        t3 = (Dict10*)(c3 + 1);
        lbl_804306E8.cnt3 = c3;
        lbl_804306E8.t3 = t3;
        c4 = (int*)(t3 + *c3);
        lbl_804306E8.cnt4 = c4;
        lbl_804306E8.t4 = (Dict10*)(c4 + 1);
    }
}

void fn_80263A80(void) {
    if (lbl_804CC00C != 0) {
        fn_800761F0(lbl_804CC00C);
        lbl_804CC00C = 0;
    }
}

void fn_80263AB4(void) {
    if (lbl_804CC010 == 0) {
        int* raw = (int*)fn_80075D78(lbl_80372C90 + 0x1E7);
        lbl_804CC010 = raw;
        lbl_80430710.cnt1 = raw;
        DictF8* t0;
        DictF8* t1;
        int* c1;
        DictF8* t2;
        int* c2;
        int* c3;
        t0 = (DictF8*)(raw + 1);
        lbl_80430710.tbl1 = t0;
        c1 = (int*)(t0 + *raw);
        t1 = (DictF8*)(c1 + 1);
        lbl_80430710.cnt2 = c1;
        lbl_80430710.tbl2 = t1;
        c2 = (int*)(t1 + *c1);
        t2 = (DictF8*)(c2 + 1);
        lbl_80430710.cnt3 = c2;
        lbl_80430710.tbl3 = t2;
        c3 = (int*)(t2 + *c2);
        lbl_80430710.cnt4 = c3;
        lbl_80430710.tbl4 = (DictF8*)(c3 + 1);
    }
}

}
