/* fn_80069F14 and fn_8006A434 (0x214 each, identical bodies): exact (round m8). Place the items of a menu window by
 * row and draw the frame.
 * The item's y is one expression, `y + (f32)v4C() + (f32)(r * v5C())`. The row term is evaluated first (it holds the
 * call-crossing value) and its compiler temporary takes f31, above the hoisted int-to-float bias constant (f30). With the
 * row term in a named local (`f = r * v5C(); g = y + v4C(); it->y = g + f;`) the two float registers are exchanged. */
#include "game/rO_80065D64/menu.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern u8* fn_80085EF8(int);
extern void fn_800718D0(int, int, int, int, int, int);
void fn_80069F14(MenuBase* m, Widget* w, int c, f32 x, f32 y);
void fn_8006A434(MenuBase* m, Widget* w, int c, f32 x, f32 y);

void fn_80069F14(MenuBase* m, Widget* w, int c, f32 x, f32 y) {
    int i;
    int mx = 0;
    for (i = 0; i < w->n; i++) {
        Widget* it = (Widget*)fn_80085EF8(w->ids[i]);
        int r = it->b3B;
        if (r + 1 > mx) {
            mx = r + 1;
        }
        it->x = x + (f32)(s16)m->v48();
        it->y = y + (f32)(s16)m->v4C() + (f32)(r * (s16)m->v5C());
    }
    u16 a = m->v50();
    u16 b = mx * m->v5C() + 0x18;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, m->v70(), 1.0f);
    fn_8007E164();
    fn_800718D0((int)x, (int)y, a, b, (u8)c, 0x9A);
}

void fn_8006A434(MenuBase* m, Widget* w, int c, f32 x, f32 y) {
    int i;
    int mx = 0;
    for (i = 0; i < w->n; i++) {
        Widget* it = (Widget*)fn_80085EF8(w->ids[i]);
        int r = it->b3B;
        if (r + 1 > mx) {
            mx = r + 1;
        }
        it->x = x + (f32)(s16)m->v48();
        it->y = y + (f32)(s16)m->v4C() + (f32)(r * (s16)m->v5C());
    }
    u16 a = m->v50();
    u16 b = mx * m->v5C() + 0x18;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, m->v70(), 1.0f);
    fn_8007E164();
    fn_800718D0((int)x, (int)y, a, b, (u8)c, 0x9A);
}
}
