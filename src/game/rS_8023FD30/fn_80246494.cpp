#include "game/rS_8023FD30/types.h"
/* Waits for the save worker thread to finish, sleeping 5 ms at a time. */
extern "C" {
extern u8 lbl_8042A470[];
BOOL fn_8031F6BC(void*);
void fn_80320978(s64);
}
static inline bool done() { return fn_8031F6BC(lbl_8042A470) != 0; }
extern "C" {
#pragma use_lmw_stmw on
void fn_80246494(void) {
    while (!done()) {
        s64 t = (s64)5 * ((*(u32*)0x800000F8 / 4) / 1000);
        fn_80320978(t);
    }
}
}
