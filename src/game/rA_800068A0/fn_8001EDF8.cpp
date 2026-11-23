/* Easing curve with an integer power (name guessed: a two-sided ease of degree n). */
extern "C" {
typedef float f32;

/* Raises both running products by one power per step from 1 to n. */
static inline void pw(f32& pe, f32& pc, f32 e, f32 c, int n)
{
    int i;
    for (i = 1; i < n; i++) {
        pe *= e;
        pc *= c;
    }
}

f32 fn_8001EDF8(f32 a, f32 b, f32 c, f32 d, int n)
{
    f32 r;
    f32 pc;
    f32 pe;
    f32 e;
    f32 m;
    r = b - a;
    e = c - d;
    pc = c;
    pe = e;
    m = a + d * r / c;
    pw(pe, pc, e, c, n);
    return m + d * ((a + (r - r * pe / pc)) - m) / c;
}
}
