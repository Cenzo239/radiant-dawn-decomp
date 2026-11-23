/* WIP (round 18): class `other`, 81 of 82 instructions: the original has one more `extsh r3,r28`
   (the old cursor, already loaded with lha) before the final compare. int/s16 locals, an int accessor
   and compare inlines were tried. */
/* fn_80223580: up/down selection in a short list whose length comes from fn_8011AB30 (wraps on a fresh press). */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_80253EE4(const char*, f32);
int fn_8011AB30(void*);
extern char lbl_80371DCC[];
}
class Pad { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual int v3C(); virtual void v40(); virtual void v44(); virtual int v48(); };
extern "C" Pad* lbl_804CB5B8;
struct Lst { u8 p[0x50]; s16 cur; u8 p52[0xa]; u8* x5c; };
static inline int gcur(Lst* o) { return o->cur; }
extern "C" void fn_80223580(Lst* o) {
    if (!inputBlocked()) {
        int held = lbl_804CB5B8->v3C();
        int trig = lbl_804CB5B8->v48();
        int cur = gcur(o);
        int nw = cur;
        u8 n = fn_8011AB30(o->x5c + 0x12c);
        s16 m = n;
        if (cur < 0 || m == 0) return;
        if (held & 0x800008) {
            nw = cur - 1;
            if ((s16)nw < 0) {
                if (trig & 0x800008) nw = (s16)(n - 1); else nw = cur;
            }
        } else if (held & 0x400004) {
            nw = cur + 1;
            if ((s16)nw > m - 1) {
                nw = (trig & 0x400004) ? 0 : cur;
            }
        }
        if ((s16)cur != (s16)nw) {
            o->cur = nw;
            fn_80253EE4(lbl_80371DCC, 0.0f);
        }
    }
}
