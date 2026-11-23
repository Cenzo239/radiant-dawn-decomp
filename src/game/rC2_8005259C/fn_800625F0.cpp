#include "game/rC2_8005259C/base.h"
/* Play timer split into hours, minutes and seconds; returns the half-second blink. */
struct Timer { u8 pad[0xA0]; u64 ticks; };
extern "C" {
u64 fn_8028C418(u64, u64);
#pragma use_lmw_stmw on
int fn_800625F0(Timer* g, u32* h, u32* m, u32* s) {
    u64 t = g->ticks;
    u32 sec = fn_8028C418(t, *(u32*)0x800000F8 / 4);
    *s = sec % 60;
    *m = (sec / 60) % 60;
    *h = sec / 3600;
    u32 ms = fn_8028C418(t, *(u32*)0x800000F8 / 4 / 1000);
    return ms % 1000 < 500;
}
}
