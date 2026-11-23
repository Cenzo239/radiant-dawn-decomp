/* Easing: from, to, elapsed t, duration d. */
#include "game/rF_8017F400/types.h"
extern "C" {
extern double fn_80295534(double);
extern double fn_80295940(double);
extern const f32 lbl_804CE538;
extern const f32 lbl_804CE54C;
f32 fn_8017F68C(int mode, f32 from, f32 to, f32 t, f32 d) {
    if (lbl_804CE538 == d) return to;
    switch (mode) {
    case 0:
        return from + t * (to - from) / d;
    case 1:
        return from + t * t * (to - from) / (d * d);
    case 2:
        return from + t * t * t * (to - from) / (d * d * d);
    case 3:
        return from + t * t * t * t * (to - from) / (d * d * d * d);
    case 7: { return to - (d - t) * ((d - t) * ((to - from) * (f32)fn_80295534(4.0f * (3.1415927f * (t / d))))) / (d * d); }
    case 8: { return to - (d - t) * ((d - t) * ((to - from) * (f32)fn_80295534(4.0f * (3.1415927f * (t * t / d)) / 15.0f))) / (d * d); }
    case 4: { f32 r = d - t; return from + (to - from) - r*r * (to - from) / (d*d); }
    case 5: { f32 r = d - t; return from + (to - from) - r*r*r * (to - from) / (d*d*d); }
    case 6: { f32 r = d - t; return from + (to - from) - r*r*r*r * (to - from) / (d*d*d*d); }
    case 9: { f32 s = fn_80295534(4.0f * (3.1415927f * (t * t / d)) / 40.0f); f32 q = d - t; f32 r = q * (q * s) / (d * d); if (r < 0.0f) r = -r; return to - r * (to - from); }
    case 10: { f32 s = fn_80295534(3.1415927f * t / d); return (to - from) * (lbl_804CE54C - s) / 2.0f + from; }
    case 11: { return (to - from) * (f32)fn_80295940(1.5707964f * t / d) + from; }
    case 12: { f32 s = fn_80295534(1.5707964f * t / d); return (to - from) * (lbl_804CE54C - s) + from; }
    }
    return 0.0f;
}
}
