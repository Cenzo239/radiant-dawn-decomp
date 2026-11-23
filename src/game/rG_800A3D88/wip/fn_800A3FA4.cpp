// 9/41: float registers (numerator f3, const f2 in the original).
void fn_800A3FA4(WobbleProc* p) {
    Target* t = p->target;
    f32 s = fn_80295940(lbl_804CD270 * ((f32)fn_8017F990(0, p->period) / (f32)p->period));
    f32 a = p->amp * s;
    t->x = p->x;
    t->y = p->y + a;
}

