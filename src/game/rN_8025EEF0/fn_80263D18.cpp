/* Dictionary menu: list building and paging */
#include "game/rN_8025EEF0/dict.h"

#pragma use_lmw_stmw on

extern "C" {

int fn_80291188(const char* a, const char* b);
BOOL fn_8025F6B8(const char* s, int mode);
void fn_80078E24(void* p);
const char* fn_800D0864(const char* s);
void* fn_80078CCC(int size, const char* name, int a);
void fn_800C4240(void* p);
void fn_800C3FD0(void* p);
void* fn_800C6118(void* a, int b, int c, int d, void* e);
void* fn_80076F54(const char* s);

void fn_80263E5C(void) {
    Dict14* t1;
    DictF8* f1;
    Dict10* t4;
    DictF8* f4;
    int n;
    int i;
    int* c;
    DictState* st = lbl_804CC004;
    switch (st->page) {
    case 0:
        c = lbl_804306E8.cnt1;
        t1 = lbl_804306E8.t1;
        f1 = lbl_80430710.tbl1;
        n = *c;
        break;
    case 1:
        c = lbl_804306E8.cnt4;
        t4 = lbl_804306E8.t4;
        f4 = lbl_80430710.tbl4;
        n = *c;
        break;
    }
    if (st->list != 0) {
        fn_80078E24(st->list);
        lbl_804CC004->list = 0;
        lbl_804CC004->list = 0;
    }
    lbl_804CC004->list = (void**)fn_80078CCC(0x1E0, lbl_80372C90 + 0x26, 0);
    lbl_804CC004->listCount = 0;
    for (i = 0; i < n; i++) {
        switch (st->page) {
        case 0:
            if (fn_8025F6B8(f1->name, 0)) {
                if (lbl_804CC004->listCount != 0) {
                    void** p = lbl_804CC004->list + lbl_804CC004->listCount;
                    if (fn_80291188(t1->name, *(const char**)p[-1]) == 0) {
                        p[-1] = t1;
                    } else {
                        p[0] = t1;
                        lbl_804CC004->listCount++;
                    }
                } else {
                    lbl_804CC004->list[lbl_804CC004->listCount] = t1;
                    lbl_804CC004->listCount++;
                }
            }
            t1++;
            f1++;
            break;
        case 1:
            if (fn_8025F6B8(f4->name, 0)) {
                lbl_804CC004->list[lbl_804CC004->listCount] = t4;
                lbl_804CC004->listCount++;
            }
            t4++;
            f4++;
            break;
        }
    }
}



}
