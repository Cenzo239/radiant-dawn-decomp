/* fn_8005B508 .. fn_8005CF68: fifteen identical sortie-menu commands: add the help bar (id -0x1000, second line
   on) to the proc, then end the proc (fn_80083B78).
   Exact (check_func.py --symbol-map fn_8005B508.symbols.json --strict-references); help bar class in hb316.h. */
#include "game/helpbar.h"
#pragma auto_inline off
extern "C" {
extern char lbl_80361F9C[];
void* fn_801E5640(void*, int, int);
void fn_801E5448(void*, void*);
void fn_80083B78(void*);
}

#define ADD_ITEM_FN(name) \
    extern "C" void name(void* proc) { \
        HbHelpBar* b = new HbHelpBar(0x316); \
        int one = 1; \
        b->id = -0x1000; \
        b->s.w[3] = one; \
        b->a64 = lbl_80361F9C + 0x6f; \
        b->flags |= 0x10; \
        b->a60 = 0; \
        b->a28 = 8; \
        fn_801E5448(proc, b); \
        HbHelpBar* h = (HbHelpBar*)fn_801E5640(proc, -0x1000, 0); \
        if (h != 0) h->a60 = one; \
        fn_80083B78(proc); \
    }

ADD_ITEM_FN(fn_8005B508)
ADD_ITEM_FN(fn_8005B6E4)
ADD_ITEM_FN(fn_8005B8C0)
ADD_ITEM_FN(fn_8005BACC)
ADD_ITEM_FN(fn_8005BCD8)
ADD_ITEM_FN(fn_8005BEB4)
ADD_ITEM_FN(fn_8005C090)
ADD_ITEM_FN(fn_8005C26C)
ADD_ITEM_FN(fn_8005C448)
ADD_ITEM_FN(fn_8005C624)
ADD_ITEM_FN(fn_8005C800)
ADD_ITEM_FN(fn_8005C9DC)
ADD_ITEM_FN(fn_8005CBB0)
ADD_ITEM_FN(fn_8005CD8C)
ADD_ITEM_FN(fn_8005CF68)
