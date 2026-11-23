/* fn_80176B0C: 5 of 18 words differ: the result goes through f0 with frsp f0,f1 and fmr f1,f0 instead of directly to f1. About 20 return spellings tried. Uses the declarations of fn_80175E7C.cpp. */
static inline f32 Sq(f32 d) { if (0.0f == d) return 0.0f; return (f32)fn_80295CF0(d); }
static inline f32 Sq2(f32 d) { f32 z = 0.0f; if (z == d) return z; return (f32)fn_80295CF0(d); }
f32 fn_80176B0C(f32 x0, f32 y0, f32 x1, f32 y1) {
    f32 dy = y1 - y0;
    f32 dx = x1 - x0;
    f32 d = dx * dx + dy * dy;
    if (0.0f == d) return 0.0f;
    return (f32)fn_80295CF0(d);
}

f32 fn_80176B0C(f32 x0, f32 y0, f32 x1, f32 y1) {
    f32 dy = y1 - y0;
    f32 dx = x1 - x0;
    f32 d = dx * dx + dy * dy;
    return Sq(d);
}
