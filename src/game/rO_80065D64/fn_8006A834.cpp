/* fn_8006A834 (0x11C): exact (round m12). Lays the menu's items out in one row: finds the widest label, then
   spaces the items evenly. From equiv/fn_8006A834.cpp. Levers:
   - no named locals for the item or its id byte: the label call is written as nested calls,
     `Item(i)->obj->v18(Item(i))`, so the first lookup result is an argument temporary (r30) and the
     `w + i` address is a compiler temporary (r31 / r29);
   - all remaining locals declared at the top in the order n, h, i, sp, tw, px, k (hill climb);
   - the row y goes through the setY(Widget*, int) inline (no extsh). */
#include "game/rO_80065D64/menu.h"
#pragma auto_inline off
extern "C" {
extern u8* fn_80085EF8(int);
extern int fn_800CA3DC(char*, int, f32);
static inline void setY(Widget* w, int y) { w->y = y; }
void fn_8006A834(MenuBase* m, Widget* w) {
    int n;
    int h;
    int i;
    s16 sp;
    s16 tw;
    s16 px;
    int k;
    m->cols = 0;
    for (i = 0; n = (s8)*(u8*)&w->n, i < n; i++) {
        tw = fn_800CA3DC(((Widget*)fn_80085EF8(w->ids[i]))->obj->v18((Widget*)fn_80085EF8(w->ids[i])), -1, 1.0f);
        if (tw >= m->cols) {
            m->cols = tw;
        }
    }
    sp = (s16)m->v50() / (n + 1);
    px = sp;
    h = m->v4C();
    for (k = 0; k < n; k++) {
        ((Widget*)fn_80085EF8(w->ids[k]))->x = px;
        setY((Widget*)fn_80085EF8(w->ids[k]), h);
        px += sp;
    }
}
}
