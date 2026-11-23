/* fn_80263B64: 7 words. Second loop: ofs should be r29 and e r26. */
/* Dictionary menu: release the portrait resources */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/calls.h"

#pragma use_lmw_stmw on

extern "C" {

void* fn_800D4228(const char* s);
void fn_80039030(void);

void fn_80263B64(void) {
    char buf[0x40];
    Dict10* e;
    int ofs;
    const char* name;
    int i2;
    int i;
    int ofs2;

    if (lbl_804CC004->m7C != 0) {
        fn_80081A90(lbl_804CC004->m7C);
    }
    lbl_804CC004->m7C = 0;
    i = 0;
    ofs = 0;
    for (; i < *lbl_804306E8.cnt2; ofs += 0x18, i++) {
        const char* s = *(const char**)((u8*)lbl_804306E8.t2 + ofs);
        if (s != 0) {
            fn_80290DDC(buf, lbl_80372C90 + 0x11C, s);
            void* p = fn_800D4228(buf);
            if (p != 0) {
                fn_80081A90(p);
            }
        }
    }
    i2 = 0;
    ofs2 = 0;
    for (; i2 < *lbl_804306E8.cnt3; ofs2 += 0x10, i2++) {
        e = (Dict10*)((u8*)lbl_804306E8.t3 + ofs2);
        if (*(int*)((u8*)lbl_804306E8.t3 + ofs2) != 0) {
            if (*(u32*)(fn_8024BC94() + 0x18C0) & 0x80000000) {
                name = e->name;
                if (fn_80291188(name, lbl_80372C90 + 0x1F7) == 0 || fn_80291188(name, lbl_80372C90 + 0x200) == 0) {
                    fn_80290DDC(buf, lbl_80372C90 + 0x20B, name);
                } else {
                    fn_80290DDC(buf, lbl_80372C90 + 0x11C, name);
                }
            } else {
                fn_80290DDC(buf, lbl_80372C90 + 0x11C, e->name);
            }
            void* p = fn_800D4228(buf);
            if (p != 0) {
                fn_80081A90(p);
            }
            fn_80290DDC(buf, lbl_80372C90 + 0x11C, e->b);
            p = fn_800D4228(buf);
            if (p != 0) {
                fn_80081A90(p);
            }
        }
    }
    fn_80039030();
}

}
