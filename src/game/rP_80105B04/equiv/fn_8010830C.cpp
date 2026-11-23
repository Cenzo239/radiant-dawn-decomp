/* fn_8010830C: draws an item model tinted with the colour of its slot (or a
   pulsing red when there is no slot). Names guessed. Level: slots.
   The colour lookup is fn_80108678 inlined six levels deep (each level tests
   the same flag again, as in fn_80108678.cpp); the six default-colour
   temporaries sit in other stack slots than in the original: original level
   0..5 at r1+0x10, 0x18, 0x14, 0x1c, 0x08, 0x0c; here 0x1c, 0x18, 0x14, 0x10,
   0x0c, 0x08. One consistent mapping, same registers. symcheck --anon flags 4
   of 44 blocks (28, 29, 30, 33): each fills one of those temporaries and
   leaves its address in r3, so "stack bytes" and the live-out address differ
   by exactly the slot. Port: C0..C5 are fn_80108678 (call it instead). */
#include "game/rP_80105B04/rp.h"
struct Color { u8 r, g, b, a; };
struct CS { u8* item; u8 uses; u8 f80 : 1; u8 f40 : 1; u8 f20 : 1; u8 f10 : 1; u8 f08 : 1; u8 f04 : 1; u8 f02 : 1; u8 f01 : 1; char name[0x18]; s8 mt, hit, crt, wt; Color col; };
struct GObj { u8 pad[8]; Color col; u8 padc[0x88 - 0xc]; CS* slot; };
struct Mat { u8 pad[6]; u8 x6; };
extern "C" {
extern Color lbl_804CDC08;
const Color* fn_80108678(CS* s);
int fn_80011E28();
void fn_80013C54(GObj*, int, void*, Mat*, void*);
void fn_80021CB4(int, int, int, int);
void fn_80021EF8(int, int);
void fn_800140A0(GObj*, void*);
void fn_80013CF0(GObj*, void*, Mat*);
void fn_800125A8(GObj*, int, void*, Mat*);
f32 fn_8001EF44(int, int, f32, f32);
s64 OSGetTime(void);
extern u32 __OSBusClock : 0x800000F8;
#pragma auto_inline off
#define LVL(name, next) static inline const Color* name(CS* s) { if (s->f20) { if (s->f20) return &s->col; return next(s); } { Color t = lbl_804CDC08; return &t; } }
LVL(C5, fn_80108678)
LVL(C4, C5)
LVL(C3, C4)
LVL(C2, C3)
LVL(C1, C2)
LVL(C0, C1)

void fn_8010830C(GObj* o, void* a, Mat* m, void* d) {
    CS* s = o->slot;
    if (m->x6 != 0) {
        fn_80013C54(o, 0, a, m, d);
    } else {
        int t = fn_80011E28();
        fn_80021CB4(t, 0xff, 0xff, 4);
        fn_80021EF8(t, 4);
    }
    Color c = { 0x80, 0x80, 0x80, 0xff };
    if (s != NULL) {
        c = *C0(s);
    } else {
        c.r = (int)fn_8001EF44(1000, OSGetTime() / ((__OSBusClock / 4) / 1000), 0.0f, 255.0f);
        c.g = 0x80;
        c.b = 0x80;
    }
    Color save = o->col;
    o->col.r = c.r;
    o->col.g = c.g;
    o->col.b = c.b;
    fn_800140A0(o, a);
    fn_80013CF0(o, a, m);
    fn_800125A8(o, 0, a, m);
    o->col = save;
}
}
