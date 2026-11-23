/* fn_8017EA78: near miss, one extra instruction: the original drops the dead initial store of the second colour's blue byte (0xE) and schedules the first colour's final blue store late. Slots and registers match. */
/* Material colour fade process: start or retarget a fade to scaled colours (names guessed). */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
#pragma use_lmw_stmw on
struct C4 { u8 r, g, b, a; };
struct C4P { C4 a, b; };
struct Fade {
    u8 pad[0x30];
    s16 id;
    s16 dur;
    s16 mode;
    s16 t;
    C4 c38, c3C, c40, c44, c48, c4C, c50, c54;
};
extern "C" {
extern u8 lbl_80387C10[];
void fn_8017EA60(void* p, void* arg);
void* fn_800893E4(void*, void*, void*);
void* fn_80081050(void*, void*);
void* fn_80010BB0(void*);
void* fn_80010DA4(void*, int);
void fn_80083DC4(void*, int);

static inline int Clamp(int v) { return v > 0xFF ? 0xFF : v; }
static inline C4 Scale(C4 c, int pct) {
    c.r = Clamp(c.r * pct / 100);
    c.g = Clamp(c.g * pct / 100);
    c.b = Clamp(c.b * pct / 100);
    return c;
}
static inline void Apply(Fade* o, C4P v, int dur, int mode) {
    o->c40 = o->c38;
    o->c50 = o->c48;
    o->c3C = v.a;
    o->c4C = v.b;
    o->t = 0;
    o->dur = dur;
    o->mode = mode;
}

Fade* fn_8017EA78(int id, int pa, int pb, int dur, int mode, void* parent) {
    struct { int k; int z; } kk;
    C4P v;
    C4P t;
    kk.k = id;
    Fade* o = (Fade*)fn_800893E4(lbl_80387C10, (void*)fn_8017EA60, &kk);
    if (!o) {
        if (pa == 100 && pb == 100) return 0;
        o = (Fade*)fn_80081050(lbl_80387C10, parent);
        o->id = id;
        u8* a = (u8*)fn_80010BB0((void*)id);
        o->c38.r = a[2];
        o->c38.g = a[3];
        o->c38.b = a[4];
        o->c38.a = a[5];
        o->c40.r = a[2];
        o->c40.g = a[3];
        o->c40.b = a[4];
        o->c40.a = a[5];
        o->c3C.r = a[2];
        o->c3C.g = a[3];
        o->c3C.b = a[4];
        o->c3C.a = a[5];
        o->c44.r = a[2];
        o->c44.g = a[3];
        o->c44.b = a[4];
        o->c44.a = a[5];
        a = (u8*)fn_80010DA4(a, 1);
        if (a) {
            o->c48.r = a[4];
            o->c48.g = a[5];
            o->c48.b = a[6];
            o->c48.a = a[7];
            o->c50.r = a[4];
            o->c50.g = a[5];
            o->c50.b = a[6];
            o->c50.a = a[7];
            o->c4C.r = a[4];
            o->c4C.g = a[5];
            o->c4C.b = a[6];
            o->c4C.a = a[7];
            o->c54.r = a[4];
            o->c54.g = a[5];
            o->c54.b = a[6];
            o->c54.a = a[7];
        }
    }
    t.a = o->c44;
    {
        int r = t.a.r * pa / 100;
        int g = t.a.g * pa / 100;
        int bb = t.a.b * pa / 100;
        t.a.r = Clamp(r);
        t.a.g = Clamp(g);
        t.a.b = Clamp(bb);
    }
    t.b = o->c54;
    {
        int r = t.b.r * pb / 100;
        int g = t.b.g * pb / 100;
        int bb = t.b.b * pb / 100;
        t.b.r = Clamp(r);
        t.b.g = Clamp(g);
        t.b.b = Clamp(bb);
    }
    v = t;
    if (dur <= 0) dur = 1;
    o->c40 = o->c38;
    o->c50 = o->c48;
    o->c3C = v.a;
    o->c4C = v.b;
    o->t = 0;
    o->dur = dur;
    o->mode = mode;
    fn_80083DC4(o, 0);
    return o;
}
}
