/* fn_80069220 (0x208): exact (round m8). Lays the menu items out in one row or two.
 * The item position is written as `x0 + r * dx` / `y0 + c * dy` with the (s16) casts inside the loops: the compiler
 * strength-reduces both products and hoists the three sign extensions in the original's order (dy, x0, dx). */
#include "game/rO_80065D64/menu.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
extern u8* fn_80085EF8(int);
void fn_80069220(MenuBase* m, Widget* w);

static inline void ClampY(Widget* w) {
    s16 h = w->h;
    if (w->y + (h >> 1) > 0xE0) {
        w->y = (0x1C0 - h) >> 1;
    }
}

void fn_80069220(MenuBase* m, Widget* w) {
    int n = w->n;
    if (n <= 10) {
        w->x = 400;
        w->w = 0x78;
        m->cols = n;
        m->rows = 1;
        ClampY(w);
    } else {
        int dx, dy, x0, y0;
        int r, k, c;
        m->cols = (n + 1) >> 1;
        m->rows = 2;
        int t = 400 - m->v58();
        w->x = t + 0x20;
        w->w = m->v58() + 0x78;
        w->h = m->v4C() + m->cols * m->v5C();
        dx = m->v58();
        dy = m->v5C();
        x0 = m->v48();
        y0 = m->v4C();
        ClampY(w);
        r = 0;
        k = 0;
        for (; r < m->rows && k < n; r++) {
            c = 0;
            for (; c < m->cols && k < n; c++) {
                Widget* it = (Widget*)fn_80085EF8(w->ids[k]);
                it->x = (s16)x0 + r * (s16)dx;
                it->y = y0 + c * (s16)dy;
                k++;
            }
        }
    }
}
}
