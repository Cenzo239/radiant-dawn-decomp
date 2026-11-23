#ifndef RC_8004BE18_HELPBOX_H
#define RC_8004BE18_HELPBOX_H
#include "game/rC_8004BE18/decls.h"

/* Help-box tails shared by many menu effect callbacks (inlines in the original).
 * CW canonicalises "call() + var" to "add rD, rVar, rCall"; the original has the call
 * result as the first operand. Two spellings reproduce it: an int temporary
 * ("int ox = o->v60(); ox + x"), or "o->v60() - -x". */

/* Help box at the entry position (fn_8004DD78 and friends). */
static inline void helpBox(Menu* b, MenuEntry* c, const char* key) {
    MenuOwner* o;
    s16 x;
    int ox;
    s16 y;
    const char* t;
    int oy;
    y = c->y;
    o = b->owner;
    x = c->x;
    t = fn_800D0864(key);
    oy = o->v64();
    ox = o->v60();
    fn_801A23E0(ox + x, oy + y, t, b);
}

/* Help box 0x3C pixels above the entry (fn_8004C6D0). */
static inline void helpBoxY(Menu* b, MenuEntry* c, const char* key) {
    MenuOwner* o;
    s16 x;
    s16 y;
    const char* t;
    y = c->y;
    o = b->owner;
    x = c->x;
    t = fn_800D0864(key);
    fn_801A23E0(o->v60() - -x, o->v64() - -y - 0x3c, t, b);
}
#endif
