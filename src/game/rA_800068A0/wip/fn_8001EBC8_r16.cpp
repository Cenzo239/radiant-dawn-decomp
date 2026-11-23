/* r16: fn_8001EBC8 and fn_8001ECE4 at 2 words each when compiled together in this order (the earlier wip single-function files are stale): the only difference is li r8,1 scheduled one slot early. 600 declaration/statement orders and loop/inline forms did not move it. fn_8001EDF8 matches (see ../fn_8001EDF8.cpp). */
/* Easing curves with an integer power (names guessed). */
extern "C" {
typedef float f32;

static inline void pwB(f32& pe, f32& pc, f32 e, f32 c, int n, int& i) { for (i = 1; i < n; i++) { pe *= e; pc *= c; } }
static inline void pwI(f32& pe, f32& pc, f32 e, f32 c, int n, int i) { for (; i < n; i++) { pe *= e; pc *= c; } }
static inline void pwV(f32* pe, f32* pc, f32 e, f32 c, int n) { int i; for (i = 1; i < n; i++) { *pe *= e; *pc *= c; } }
static inline void pwQ(f32& q, f32& p, f32 y, f32 x, int n, int& i) { q = y; p = x; for (i = 1; i < n; i++) { q *= y; p *= x; } }
static inline void pwR(f32& q, f32& p, f32 y, f32 x, int n, int& i) { q = y; i = 1; p = x; for (; i < n; i++) { q *= y; p *= x; } }
static inline void pwS(f32& q, f32& p, f32 y, f32 x, int n, int& i) { i = 1; q = y; p = x; for (; i < n; i++) { q *= y; p *= x; } }
static inline void pwT(f32& q, f32& p, f32 y, f32 x, int n) { int i; q = y; p = x; for (i = 1; i < n; i++) { q *= y; p *= x; } }
static inline void pw(f32& pe, f32& pc, f32 e, f32 c, int n)
{
    int i;
    for (i = 1; i < n; i++) {
        pe *= e;
        pc *= c;
    }
}

f32 fn_8001EBC8(f32 a, f32 b, f32 x, f32 y, int n) {
    /*P*/
    f32 d;
    f32 q;
    f32 p;
    int i;
/*E*/
    d = x - y;
    b = b - a;
    p = x;
    q = d;
    for (i = 1; i < n; i++) {
        q *= d;
        p *= x;
    }
    return a + (b - b * q / p);
}

f32 fn_8001ECE4(f32 a, f32 b, f32 x, f32 y, int n) {
    /*P*/
    f32 d;
    f32 q;
    f32 p;
    int i;
/*E*/
    d = b - a;
    q = y;
    p = x;
    for (i = 1; i < n; i++) {
        q *= y;
        p *= x;
    }
    return a + d * q / p;
}

f32 fn_8001EDF8(f32 a, f32 b, f32 c, f32 d, int n) {
    /*P*/
    f32 r;
    f32 pc;
    f32 pe;
    f32 e;
    f32 m;
    /*E*/
    r = b - a;
    e = c - d;
    pc = c;
    pe = e;
    m = a + d * r / c;
    pw(pe, pc, e, c, n);
    return m + d * ((a + (r - r * pe / pc)) - m) / c;
}
}
