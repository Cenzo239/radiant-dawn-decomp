/* fn_80241BF0: talk list ("ask whom") window: adds its title strip and its
   help text box (names guessed). Widget constructors as inlines, see
   rI_801DD7D4/fn_wf.h. Level: sched. Moved lines (checked with dd.py): in the
   prologue `mr r31,r3` / `li r3,0x50` / `stw r30` are ordered differently
   (and the window and the title swap r30/r31); in the text box constructor
   block `li 0x190` and `li -1`, and `li 1` and `addi r4,r4,lbl_8038C1C0@l`,
   swap places. All are independent constant loads; the stores keep their
   order. The three strings are literals pooled as in the original
   (lbl_803728A8 +0, +0x13, +0x14). Like the original, the code writes to both
   new objects even if the allocation returned NULL. */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma pool_strings on

extern "C" {
extern u8 lbl_8038CA50[], lbl_8038CA18[], lbl_8038C1C0[];
extern char lbl_803728A8[];   /* "MESS_INFO_ASK_WHOM", "", "MESS_INFO_HELP01", ... */
void* fn_801E5640(void*, int, int);
int fn_80058718(void);
int fn_8002460C(void);
}

struct Title { WF w; const char* a40; s16 a44; u8 a46; };
struct WB { WF w; int a40, a44, a48, a4c; u8 a50; f32 a54; s16 a58, a5a, a5c, a5e; int a60; const char* a64; };

static inline void titleInit(Title* o, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    wfInit(&o->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
    o->w.vt = lbl_8038CA50;
    o->a40 = 0;
    o->a44 = 0x20;
    o->a46 = 0;
    ((Lst*)o)->v2C();
    o->w.vt = lbl_8038CA18;
    ((Lst*)o)->v2C();
}
static inline void wbInit(WB* b, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    wfInit(&b->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
    b->a40 = 0; b->a44 = 0; b->a48 = 0; b->a4c = 0;
    b->a50 = 1;
    b->a5a = 0; b->a5e = 0;
    b->w.vt = lbl_8038C1C0;
    b->a60 = 0; b->a64 = 0;
    b->a58 = iy1; b->a5c = iy1;
    b->a54 = 0.75f;
}

static inline void setHelp(void* self, const char* msg) {
    WB* p = (WB*)fn_801E5640(self, -0x1000, 0);
    if (p != 0) {
        p->a64 = msg;
    }
}

extern "C" void fn_80241BF0(void* self) {
    Title* t = (Title*)fn_80079150(0x50);
    if (t != 0) {
        titleInit(t, 0x10, 0x13, 0x250, 0x3b, 0x240, 0x28, 0x1fe, 0x10);
    }
    t->w.a28 = 8;
    t->w.id = 0x80;
    t->a40 = "MESS_INFO_ASK_WHOM";
    fn_801E5448(self, t);
    WB* b = (WB*)fn_80079150(0x68);
    if (b != 0) {
        wbInit(b, 0, 0x190, 0x260, 0x1c0, 0x260, 0x30, 0x78, 0x10);
    }
    b->w.id = -0x1000;
    b->a4c = 1;
    b->a64 = "";
    b->w.flags |= 0x10;
    b->a60 = 0;
    b->w.a28 = 8;
    fn_801E5448(self, b);
    if (fn_80058718() && fn_8002460C()) {
        WB* p = (WB*)fn_801E5640(self, -0x1000, 0);
        if (p != 0) {
            p->a60 = 1;
        }
    }
    setHelp(self, "MESS_INFO_HELP01");
}
