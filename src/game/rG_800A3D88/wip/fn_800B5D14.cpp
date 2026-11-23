// Near misses, see NOTES.md. Needs declarations from ../fn_800B5D14.cpp.
void fn_800C4104(F43* f, s8 k, s8 m, int w) {
    if (k >= 0 && k <= 9) {
        f->m43 = k;
        int x = lbl_803E50F0[k].x;
        if (w != 0) {
            if (x >= 1000) x = fn_8007E9BC(x - 1000) + 1000;
            else x = fn_8007E9BC(x);
        }
        f->m38 = x;
        f->m3c = lbl_803E50F0[k].y;
        f->m48 &= ~1;
        if (m == 0) { f->m48 |= lbl_803E50F0[k].fl; }
        else if (m >= 0 && m < 2) { f->m48 |= 1; }
    }
}
void fn_800A40B4(WC* w) {
    T18* t = (T18*)w->m18;
    f32 len = fn_80295CF0(w->m40 * w->m40 + w->m44 * w->m44);
    f32 nx = w->m40 / len;
    f32 ny = w->m44 / len;
    int v = fn_8017F990(0, w->m38);
    f32 s = fn_80295940(lbl_804CD270 * ((f32)v / (f32)w->m38));
    f32 a = w->m3c * s - lbl_804CD280 * w->m3c;
    t->x = a * nx + w->m30;
    t->y = a * ny + w->m34;
}
void fn_800C9918(VO* o) {
    u8 m[0x30];
    f32 y = lbl_804CD610 / (f32)o->v12();
    fn_8031292C(m, lbl_804CD610 / (f32)o->v11(), y);
    fn_80307F10(m, 0x21, 1);
}
