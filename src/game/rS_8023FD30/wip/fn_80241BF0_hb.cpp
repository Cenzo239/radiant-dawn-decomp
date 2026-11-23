/* 18 of 184 words off: constructors match, function-wide r30/r31 swap remains (self wants r31). Maybe a member function with self = this. */
/* fn_80241BF0: talk list ("ask whom") window: adds its title strip (0x50 widget, id 0x80) and the help bar
   (0x68 widget, id -0x1000), enables the help bar's second line in the two special modes and sets its
   message (names guessed). Like the original, the code writes to both new objects even if the allocation
   returned NULL. The three strings are literals pooled as in the original (lbl_803728A8 +0, +0x13, +0x14).
   Exact (check_func.py --symbol-map fn_80241BF0.symbols.json --strict-references). */
#include "game/rS_8023FD30/types.h"
#include "game/helpbar.h"
#pragma pool_strings on

/* Title strip: HbWidget plus a string pointer; both its constructors call slot 9 (vtable +0x2C). */
class HbTitleBase : public HbWidget {
public:
    const char* a40; s16 a44; u8 a46; u8 a47; int a48, a4c;
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9();
    HbTitleBase(s16 x0_, s16 y0_, s16 x1_, s16 y1_, s16 ix1_, s16 iy1_, s16 a26_, int fl)
        : HbWidget(x0_, y0_, x1_, y1_, ix1_, iy1_, a26_, fl) {
        a40 = 0;
        a44 = 0x20;
        a46 = 0;
        v9();
    }
};
class HbTitle : public HbTitleBase {
public:
    virtual void v9();
    HbTitle() : HbTitleBase(0x10, 0x13, 0x250, 0x3b, 0x240, 0x28, 0x1fe, 0x10) { v9(); }
};

extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E5448(void*, void*);
int fn_80058718(void);
int fn_8002460C(void);
}

static inline void setHelp(void* self, const char* msg) {
    HbHelpBar* p = (HbHelpBar*)fn_801E5640(self, -0x1000, 0);
    if (p != 0) {
        p->a64 = msg;
    }
}

extern "C" void fn_80241BF0(void* self) {
    HbTitle* t = new HbTitle;
    t->a28 = 8;
    t->id = 0x80;
    t->a40 = "MESS_INFO_ASK_WHOM";
    fn_801E5448(self, t);
    HbHelpBar* b = new HbHelpBar;
    int one = 1;
    b->id = -0x1000;
    b->s.w[3] = one;
    b->a64 = "";
    b->flags |= 0x10;
    b->a60 = 0;
    b->a28 = 8;
    fn_801E5448(self, b);
    if (fn_80058718() && fn_8002460C()) {
        HbHelpBar* p = (HbHelpBar*)fn_801E5640(self, -0x1000, 0);
        if (p != 0) {
            p->a60 = one;
        }
    }
    setHelp(self, "MESS_INFO_HELP01");
}
