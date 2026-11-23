/*
 * fn_80095514: 3 of 74 words differ: the int-to-float conversion registers (want f2 const, f1
 * value; ours f1 const, f0 value). Needs GXColor, Color2 and callColor below, plus IsValidPtr,
 * fn_80184648 and lbl_803E5028 from ../fn_80092D04.cpp. fn_80183944 takes GXColor by value.
 */
struct GXColor {
    u8 r, g, b, a;
};

struct Color2 {
    GXColor c;
    Color2(u32 color)
    {
        GXColor t = { (u8)(color >> 16), (u8)(color >> 8), (u8)color, 0xff };
        c = t;
    }
};

static inline void callColor(void* q, int a, int b, int c, GXColor col, f32 v)
{
    fn_80183944(q, a, b, c, col, v);
}

int fn_80095514(int a, int b, int c, int d, u32 color)
{
    void* q;
    if (!IsValidPtr(lbl_803E5028)) {
        return 0;
    }
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    q = fn_80184648(lbl_803E5028);
    if (q == NULL) {
        return 0;
    }
    {
        Color2 col(color);
        callColor(q, a, b, c, col.c, 0.01f * d);
    }
    return 1;
}

