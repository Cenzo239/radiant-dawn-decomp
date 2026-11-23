/* fn_8022C080: left/right selection in a short option row (wraps on a fresh press). */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_80253EE4(const char*, f32);
extern char lbl_80371FA0[];
extern const s16 lbl_804CAA80;
extern const s16 lbl_804CAA82;
}
class Pad { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual int v3C(); virtual void v40(); virtual void v44(); virtual int v48(); };
extern "C" Pad* lbl_804CB5B8;
struct Row { u8 p[0x40]; int item[13]; s16 cur; };
static inline const s16& Min(const s16& a, const s16& b) { return b < a ? b : a; }
static inline s16 count(Row* o) { s16 n = 0; int* p = o->item; while (*p != 0) { n++; p++; } return n; }
extern "C" void fn_8022C080(Row* o) {
    if (!inputBlocked()) {
        int held = lbl_804CB5B8->v3C();
        int trig = lbl_804CB5B8->v48();
        if (held & 0x1100041) {
            s16 lim = Min(count(o), lbl_804CAA80);
            s16 old = o->cur;
            o->cur--;
            if (o->cur < 0) o->cur = held == trig ? lim : 0;
            if (old != o->cur) fn_80253EE4(lbl_80371FA0 + 0xa, 0.0f);
        } else if (held & 0x2200102) {
            s16 lim = Min(count(o), lbl_804CAA82);
            s16 old = o->cur;
            o->cur++;
            if ((u32)o->cur > (u32)lim) o->cur = held == trig ? 0 : lim;
            if (old != o->cur) fn_80253EE4(lbl_80371FA0 + 0xa, 0.0f);
        }
    }
}
