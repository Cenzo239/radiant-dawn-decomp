/* Create the proc named by lbl_80392A68 unless the boot string matches; the empty early return keeps the dead compare */
#include "game/rN_8025EEF0/types.h"
extern "C" {
extern u8 lbl_803CAB38[];
extern char lbl_803738BC[];
extern char lbl_80392A68[];
void* fn_8006074C(void* p);
int fn_80291188(const char* a, const char* b);
void* fn_80081050(void* a, void* b);
void fn_80280DF8(void* parent) {
    if (fn_80291188(*(const char**)fn_8006074C(lbl_803CAB38), lbl_803738BC + 0x73) == 0) {
        void* p = fn_80081050(lbl_80392A68, parent);
        if (p == 0) return;
    }
}
}
