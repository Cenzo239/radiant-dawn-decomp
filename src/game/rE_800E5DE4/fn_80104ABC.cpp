#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

/* The map-unit process classes live in one data block at lbl_80385050. The
 * original addresses all of them off one base register (addi rN, rBase, 0x0),
 * which only file statics reproduce. Offsets match the lbl_ symbols, the block
 * base is lbl_80385050 in all three functions (read from the asm). */
typedef struct Probe { u8 pad[0x30]; void* a; } Probe;

static u8 c000[0x20];
static u8 c020[0x20];
static u8 c040[0x20];
static u8 c060[0x18];
static u8 c078[0x30];
static u8 c0A8[0x28];
static u8 c0D0[0x28];
static u8 c0F8[0x28];
static u8 c120[0x28];
static u8 c148[0x30];
static u8 c178[0xC8];
static u8 c240[0x158];
static u8 c398[0x34];
static u8 c3CC[0x34];
static u8 c400[0xC8];
static u8 c4C8[0xB4];
static u8 c57C[0xAC];
static u8 c628[0x50];

extern "C" {
extern void* fn_800893E4(void*, void*, Probe*);
extern void fn_80104A70(void* a, void* b);
extern void* fn_80083B84(void*);
extern void fn_800846BC(void*);

static inline void Stop(u8* cls, void* u) {
    Probe s;
    s.a = u;
    fn_800893E4(cls, fn_80104A70, &s);
}
void fn_80104ABC(void* u) {
    Stop(c000, u);
    Stop(c020, u);
    Stop(c078, u);
    Stop(c0A8, u);
    Stop(c0D0, u);
    Stop(c120, u);
    Stop(c0F8, u);
    Stop(c040, u);
    Stop(c060, u);
    Stop(c178, u);
    Stop(c4C8, u);
    Stop(c148, u);
    Stop(c57C, u);
    Stop(c628, u);
    Stop(c240, u);
}
int fn_80104F18(void) {
    if (fn_80083B84(c000)) return 1;
    if (fn_80083B84(c020)) return 1;
    if (fn_80083B84(c078)) return 1;
    if (fn_80083B84(c0A8)) return 1;
    if (fn_80083B84(c0D0)) return 1;
    if (fn_80083B84(c120)) return 1;
    if (fn_80083B84(c0F8)) return 1;
    if (fn_80083B84(c4C8)) return 1;
    if (fn_80083B84(c57C)) return 1;
    if (fn_80083B84(c628)) return 1;
    if (fn_80083B84(c148)) return 1;
    if (fn_80083B84(c240)) return 1;
    if (fn_80083B84(c398)) return 1;
    if (fn_80083B84(c3CC)) return 1;
    return fn_80083B84(c400) != 0;
}
void fn_801050A8(void) {
    fn_800846BC(c000);
    fn_800846BC(c020);
    fn_800846BC(c078);
    fn_800846BC(c0A8);
    fn_800846BC(c0D0);
    fn_800846BC(c120);
    fn_800846BC(c0F8);
    fn_800846BC(c4C8);
    fn_800846BC(c57C);
    fn_800846BC(c628);
    fn_800846BC(c148);
    fn_800846BC(c178);
    fn_800846BC(c240);
    fn_800846BC(c398);
    fn_800846BC(c3CC);
    fn_800846BC(c400);
}
}
