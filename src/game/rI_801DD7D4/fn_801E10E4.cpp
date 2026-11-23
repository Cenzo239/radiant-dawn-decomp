/* fn_801E10E4: draw of a multi-line text label: clips to the inner rectangle, then for every row that
   fits copies one line of the (localised) text into a std::string, character by character
   (multi-byte aware through fn_80077D44), and draws it; '\n' advances y by the row height. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
struct Str {
    union {
        u32 w;
        struct { u8 l; char d[11]; } s;
        struct { u32 cap; u32 len; char* ptr; } h;
    };
};
struct Tag { Tag() {} char c; };
extern "C" {
void fn_800250B0(Str*, u32, u32, const char*, const char*, Tag);
void fn_80079210(void*);
const char* fn_80077D44(const char*);
const char* fn_800D0864(const char*);
int fn_800CB0FC(f32, int);
void fn_800CB278(int, int, int, const char*, ...);
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u32);
#else
void fn_8007E174(int, u32);
#endif
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void*, void*);
#endif
void fn_8007E7B4(void);
u32* fn_801E2204(void*, s16*, s16*);
void fn_801E2104(void* p, void* arg);
extern char lbl_8036ED78[];
}
class TL { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; void* parent; const char* text; s16 lineH; u8 p46[2]; s16 r0, r1, r2, r3;
};
static inline void setR(TL* o, s16 a, s16 b, s16 c, s16 d) { o->r0 = a; o->r1 = b; o->r2 = c; o->r3 = d; }
static inline bool Small(const Str* s) { return !(s->w >> 31); }
static inline u32 Size(const Str* s) { if (Small(s)) return s->s.l & 0x7F; return s->h.len; }
static inline const char* CStr(const Str* s) { if (Small(s)) return s->s.d; return s->h.ptr; }
static inline void PushBack(Str* s, char c) { Tag t; fn_800250B0(s, Size(s), 0, &c, &c + 1, t); }
struct String : Str {
    String() { h.cap = 0; h.len = 0; h.ptr = 0; }
    ~String() { if (w >> 31) fn_80079210(h.ptr); }
    const char* c_str() const { return !(w >> 31) ? s.d : h.ptr; }
};
static inline const char* textOf(TL* o) { if (o->text != NULL) return fn_800D0864(o->text); return lbl_8036ED78; }
extern "C" void fn_801E10E4(TL* o) {
    s16 x;
    s16 y;
    s16 lineH;
    const char* p;
    s16 row;
    s16 ty;
    o->v18();
    x = o->tx;
    lineH = o->lineH;
    ty = o->ty;
    y = ty + ((lineH - fn_800CB0FC(1.0f, -1)) >> 1);
    p = textOf(o);
    if (p != NULL) {
        setR(o, 0, 0, o->ix1 - o->ix0, o->iy1 - o->iy0);
        fn_801E2204(o, &o->r0, &o->r0);
        fn_801E2204(o, &o->r2, &o->r2);
        fn_8007E154();
        fn_8007E74C(fn_801E2104, &o->r0);
        fn_8007E720(-1.0f);
        fn_8007E174(0, (u16)(o->flags | 3));
        fn_8007E164();
        for (row = 0; row < (s16)(((s16)(o->iy1 - o->iy0) - o->ty * 2) / o->lineH); row++, p++) {
            String line;
            BOOL done = FALSE;
            while (!done) {
                switch (*p) {
                case '\0':
                case '\n':
                    PushBack(&line, '\0');
                    done = TRUE;
                    break;
                default: {
                    const char* e = fn_80077D44(p);
                    for (; p != e; p++) PushBack(&line, *p);
                    break;
                }
                }
            }
            fn_800CB278(x, y, 1, line.c_str());
            if (*p == '\n') {
                y += o->lineH;
                continue;
            }
            if (*p == '\0') break;
        }
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E164();
    }
}
