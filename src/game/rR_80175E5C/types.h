#ifndef RR_TYPES_H
#define RR_TYPES_H
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
typedef double f64;
typedef int BOOL;
#ifndef NULL
#define NULL 0
#endif

/* Source rectangle of a window-sheet sprite (guessed). */
struct Rect {
    s16 x0, y0, x1, y1;
};
#define RW(r) ((s16)((r).x1 - (r).x0))
#define RH(r) ((s16)((r).y1 - (r).y0))

struct Color {
    u8 r, g, b, a;
    Color() {}
    Color(const Color& o) : r(o.r), g(o.g), b(o.b), a(o.a) {}
    Color(u8 r_, u8 g_, u8 b_, u8 a_) : r(r_), g(g_), b(b_), a(a_) {}
    Color& operator=(const Color& o) {
        if (this != &o) {
            r = o.r;
            g = o.g;
            b = o.b;
            a = o.a;
        }
        return *this;
    }
};

extern "C" {
/* Prim2D */
void fn_8007E154();
void fn_8007E164();
void fn_8007E174(void* tex, u16 flags);
void fn_8007E244(void* a, void* b, int c, u16 flags);
void fn_800800D4(int mode);
void fn_80080308();
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_800803C8(f32 u, f32 v, f32 w, f32 h);
void fn_800803F0(f32 x, f32 y, f32 w, f32 h);
void fn_80080430(f32 x, f32 y, f32 u, f32 v, f32 w, f32 h);
void fn_80080494();
void fn_800804B4();
void fn_80080508(Color c);
void fn_80080578(int);
void fn_80080690();
void fn_800806E0();
void fn_80080940(Color a, Color b, Color c, Color d);
/* Save/restore of a Prim2D float state. */
void* fn_8007E4C4(f32* out);
void fn_8007E478(void* p, f32 v);
void fn_8007E720(f32 v);

void fn_80006A64(void* tex, void* out, int idx);
}
#endif
