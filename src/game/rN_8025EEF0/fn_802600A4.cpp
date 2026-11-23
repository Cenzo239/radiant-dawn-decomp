/* Dictionary menu: state switches and lookups */
#include "game/rN_8025EEF0/dict.h"

extern "C" {

int fn_80291188(const char* a, const char* b);
void fn_80263B64(void);
void fn_800C4240(void* p);
void fn_80260B48(void);
void fn_80262744(void);
void fn_80263160(void);
void fn_80263418(void);
void fn_8025F6B8(const char* s, int mode);


Dict14* fn_802600A4(const char* s) {
    DictF8* e;
    int n;
    int i;
    i = 0;
    e = lbl_80430710.tbl1;
    n = *lbl_80430710.cnt1;
    for (; i < n; e++, i++) {
        if (fn_80291188(s, e->name) == 0) {
            return lbl_804306E8.t1 + i;
        }
    }
    return 0;
}

void fn_80260AA8(void) {
    fn_80263B64();
    switch (lbl_804CC000->state) {
    case 0:
        lbl_804CC000->state = 1;
        if (lbl_804CC004->m74 != 0) {
            fn_800C4240(lbl_804CC004->m74);
            lbl_804CC004->m74 = 0;
        }
        break;
    case 1:
        lbl_804CC000->state = 0;
        break;
    }
}

void fn_80260B1C(void) {
    switch (lbl_804CC000->state) {
    case 0: fn_80260B48(); break;
    case 1: fn_80262744(); break;
    }
}

void fn_80263134(void) {
    switch (lbl_804CC000->state) {
    case 0: fn_80263160(); break;
    case 1: fn_80263418(); break;
    }
}

}
