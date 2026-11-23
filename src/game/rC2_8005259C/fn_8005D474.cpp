/* fn_8005D474: sortie-menu command: when the shared command byte (lbl_803CA870+0xC) is 0x81, jump to proc label
   0x27; otherwise add the help bar (id -0x1000, second line on) like the fn_8005B508 family, call fn_80058094 and
   end the proc.
   Exact (check_func.py --symbol-map fn_8005D474.symbols.json --strict-references); help bar class in hb316.h. */
#include "game/helpbar.h"
#pragma auto_inline off
typedef unsigned char u8;
extern "C" {
extern char lbl_80361F9C[];
extern int lbl_803CA870[];
void* fn_801E5640(void*, int, int);
void fn_801E5448(void*, void*);
void fn_80083B78(void*);
void fn_80083DC4(void*, int);
void fn_80058094(void);
}

extern "C" void fn_8005D474(void* proc) {
    switch (((u8*)lbl_803CA870)[0xc]) {
    case 0x81:
        fn_80083DC4(proc, 0x27);
        break;
    default: {
        HbHelpBar* b = new HbHelpBar(0x316);
        int one = 1;
        b->id = -0x1000;
        b->s.w[3] = one;
        b->a64 = lbl_80361F9C + 0x6f;
        b->flags |= 0x10;
        b->a60 = 0;
        b->a28 = 8;
        fn_801E5448(proc, b);
        HbHelpBar* h = (HbHelpBar*)fn_801E5640(proc, -0x1000, 0);
        if (h != 0) h->a60 = one;
        fn_80058094();
        fn_80083B78(proc);
        break;
    }
    }
}
