/* Letterbox subtitle panel: gradient bars and centred text. */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
#include "game/rR_80175E5C/strpool.h"
#define F(p, t, o) (*(t*)((u8*)(p) + (o)))

struct C4 { u8 r, g, b, a; };

/* Small-string layout: top bit of the first byte means heap. */
struct Str {
    union {
        u32 w;
        struct {
            u8 l;
            char d[11];
        } s;
        struct {
            u32 cap;
            u32 len;
            char* ptr;
        } h;
    };
};

struct Panel {
    u8 kind;
    u8 x1;
    u8 x2;
    u8 x3;
    s16 h;
    u8 pad6[2];
    f32 r, g, b;
    C4 col;
    Str s0;
    Str s1;
};

struct Tag { Tag() {} char c; };
extern "C" {
extern u8 lbl_804CA7C4;
int strlen(const char*);
void fn_800250B0(Str*, int, u32, const char*, const char*, Tag);
extern u8 lbl_80387C38[];
void* fn_80083B84(void*);
void* fn_80081050(void*, void*);
void fn_80010960();
C4 fn_80010B54();
void fn_80083DC4(void*, int);
void fn_8007E7DC(int);
void fn_8007E7F4();
void fn_8007E154();
void fn_8007E164();
void fn_8007E174(void* tex, u16 flags);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_800800D4(int mode);
void fn_80080308();
void fn_80080348(f32, f32, f32, f32);
void fn_80080368(f32, f32, f32, f32);
void fn_80080578(int);
void fn_80080940(C4 a, C4 b, C4 c, C4 d);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
int fn_800CA7A4(f32, const char*, int);
void fn_800CB3A8(f32, f32, int, int, int, int, int, const char*, ...);

void fn_8017A188(Panel* p) {
    fn_8007E154();
    fn_8007E7DC(p->x3);
    fn_8007E4E4(0.0f, p->g, 1.0f + p->b, 1.0f);
    fn_8007E174(0, 0x12);
    fn_8007E164();
    s16 h3 = p->h / 3;
    C4 clr;
    clr.r = p->col.r;
    clr.g = p->col.g;
    clr.b = p->col.b;
    clr.a = 0;
    switch (p->kind) {
    case 0:
        fn_800800D4(3);
        fn_80080348(0.0f, 0.0f, 0.0f, 0.0f);
        fn_80080368(608.0f, h3, 0.0f, 0.0f);
        fn_80080940(clr, clr, p->col, p->col);
        fn_80080578(0);
        fn_80080308();
        fn_800800D4(3);
        fn_80080348(0.0f, h3, 0.0f, 0.0f);
        fn_80080368(608.0f, p->h - h3 * 2, 0.0f, 0.0f);
        fn_80080940(p->col, p->col, p->col, p->col);
        fn_80080578(0);
        fn_80080308();
        fn_800800D4(3);
        fn_80080348(0.0f, p->h - h3, 0.0f, 0.0f);
        fn_80080368(608.0f, p->h, 0.0f, 0.0f);
        fn_80080940(p->col, p->col, clr, clr);
        fn_80080578(0);
        fn_80080308();
        break;
    case 1:
        fn_800800D4(3);
        fn_80080348(0.0f, 0.0f, 0.0f, 0.0f);
        fn_80080368(608.0f, h3, 0.0f, 0.0f);
        fn_80080940(clr, clr, p->col, p->col);
        fn_80080578(0);
        fn_80080308();
        fn_800800D4(3);
        fn_80080348(0.0f, h3, 0.0f, 0.0f);
        fn_80080368(608.0f, p->h, 0.0f, 0.0f);
        fn_80080940(p->col, p->col, p->col, p->col);
        fn_80080578(0);
        fn_80080308();
        break;
    case 2:
        fn_800800D4(3);
        fn_80080348(0.0f, 0.0f, 0.0f, 0.0f);
        fn_80080368(608.0f, p->h - h3, 0.0f, 0.0f);
        fn_80080940(p->col, p->col, p->col, p->col);
        fn_80080578(0);
        fn_80080308();
        fn_800800D4(3);
        fn_80080348(0.0f, p->h - h3, 0.0f, 0.0f);
        fn_80080368(608.0f, p->h, 0.0f, 0.0f);
        fn_80080940(p->col, p->col, clr, clr);
        fn_80080578(0);
        fn_80080308();
        break;
    }
    const char* txt = 0;
    int sm = !(p->s0.w >> 31);
    u32 n = sm ? p->s0.s.l & 0x7F : p->s0.h.len;
    if (n != 0) {
        txt = sm ? p->s0.s.d : p->s0.h.ptr;
    }
    sm = !(p->s1.w >> 31);
    n = sm ? p->s1.s.l & 0x7F : p->s1.h.len;
    if (n != 0) {
        txt = fn_800D0864(sm ? p->s1.s.d : p->s1.h.ptr);
    }
    if (txt != 0) {
        fn_8007E154();
        fn_8007E4E4(p->r, p->g, p->b, 1.0f);
        fn_8007E174(0, 0x13);
        fn_8007E164();
        f32 sc = 0.75f;
        int tw = fn_800CA3DC(sc, txt, -1);
        int th = fn_800CA7A4(sc, txt, -1);
        fn_800CB3A8(sc, 0.0f, (0x260 - tw) / 2, (p->h - th) / 2, 1, 1, 0, txt);
    }
    fn_8007E7F4();
}

static inline bool Small(const Str* s) { return !(s->w >> 31); }
static inline u32 Size(const Str* s) { if (Small(s)) return s->s.l & 0x7F; return s->h.len; }
static inline void Assign(Str* s, const char* p) {
    u32 n = Size(s);
    fn_800250B0(s, 0, n, p, p + strlen(p), Tag());
}

void fn_8017A968(Panel* p, const char* name) {
    if (name != 0) {
        Assign(&p->s1, name);
    }
}

Panel* fn_8017AA08(Panel* p) {
    p->s0.h.cap = 0;
    p->s0.h.len = 0;
    p->s0.h.ptr = 0;
    p->s1.h.cap = 0;
    p->s1.h.len = 0;
    p->s1.h.ptr = 0;
    p->r = 0.0f;
    p->g = 400.0f;
    p->b = 100.0f;
    p->x3 = 0xFF;
    C4 c = *(C4*)&lbl_804CA7C4;
    p->col.r = c.r;
    p->col.g = c.g;
    p->col.b = c.b;
    p->col.a = c.a;
    p->kind = 1;
    p->h = 0x30;
    Assign(&p->s0, "");
    Assign(&p->s1, "");
    return p;
}

struct Fade {
    u8 pad0[0x30];
    s16 dur;
    s16 mode;
    s16 t;
    C4 base;
    C4 to;
    C4 from;
    C4 max;
};

static inline void Start(Fade* o, C4 to, int dur, s16 mode) {
    if (dur <= 0) dur = 1;
    o->from.r = o->base.r;
    o->from.g = o->base.g;
    o->from.b = o->base.b;
    o->from.a = o->base.a;
    o->to.r = to.r;
    o->to.g = to.g;
    o->to.b = to.b;
    o->to.a = to.a;
    o->t = 0;
    o->dur = dur;
    o->mode = mode;
}

static inline void Scale(Fade* o, int pct, int dur, s16 mode) {
    C4 c = o->max;
    int r = o->max.r * pct / 100;
    int g = o->max.g * pct / 100;
    int b = o->max.b * pct / 100;
    c.r = r > 0xFF ? 0xFF : r;
    c.g = g > 0xFF ? 0xFF : g;
    c.b = b > 0xFF ? 0xFF : b;
    Start(o, c, dur, mode);
}

#pragma use_lmw_stmw on
Fade* fn_8017F194(int pct, int dur, s16 mode, void* parent) {
    /*P*/
    Fade* o = (Fade*)fn_80083B84(lbl_80387C38);
    /*E*/
    if (o == 0) {
        if (pct == 100) return 0;
        o = (Fade*)fn_80081050(lbl_80387C38, parent);
        fn_80010960();
        C4 v = fn_80010B54();
        o->base = v;
        o->from = v;
        o->to = v;
        o->max = v;
    }
    Scale(o, pct, dur, mode);
    fn_80083DC4(o, 0);
    return o;
}
#pragma use_lmw_stmw off
}
