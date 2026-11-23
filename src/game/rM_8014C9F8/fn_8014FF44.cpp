/* Message log draw, fn_8014FF44. */
/* Message log: load a script into the text ring, fn_8014F288. */
#include "game/rM_8014C9F8/types.h"
struct Color { u8 r,g,b,a; };
struct Msg {
    char names[0x10][0x20]; /* 0x0000 */
    char lines[0x100][0x40]; /* 0x0200 */
    int who;        /* 0x4200 */
    int last;       /* 0x4204 */
    char cur[0x18]; /* 0x4208 */
    u8 pad4220[0xC];
    int cnt;        /* 0x422C */
    int line;       /* 0x4230 */
    int col;        /* 0x4234 */
    u8 fresh;       /* 0x4238 */
    u8 pad4239;
    s16 h423A;      /* 0x423A */
    s16 scroll;     /* 0x423C */
    s8 dir;         /* 0x423E */
    s8 speed;       /* 0x423F */
    s16 alpha;      /* 0x4240 */
    s16 dalpha;     /* 0x4242 */
    void* obj;      /* 0x4244 */
    u8 b4248;       /* 0x4248 */
};
struct CE { const char* key; int col; };
struct CT { CE e[0x2F]; };
extern "C" {
extern char lbl_80369FE8[];
extern CT lbl_80369E70;
extern Color lbl_80386D90[];
extern void fn_8014FC58(void);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_80080308(void);
extern void fn_8007E7DC(u8);
extern void fn_8007E174(void*, int);
extern void fn_800803F0(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void (*)(void), void*);
#endif
extern void fn_80080330(f32, f32);
extern Color* fn_800CD204(int);
extern void fn_80080508(Color);
extern char* fn_80291314(const char*, int);
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_80080C24(const char*);
extern void fn_8007E7B4(void);
extern void fn_80179A7C(void*, int);
extern void fn_80179888(void*, int);
extern void fn_80179A84(void*);
extern int fn_80291188(const char*, const char*);
extern char* fn_800C4058(const char*);
#if TARGET_PC
extern FE10_PROTO void fn_8007E41C(p32arg, p32arg, int, int);
#else
extern void fn_8007E41C(int, int, int, int);
#endif
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_80080A94(f32);
#define LINE(m, n) ((m)->lines[((n) + 0x100) & 0xFF])

static inline int FindCol(CT& t, const char* s) {
    if (s == 0) {
        return -1;
    }
    CE* e;
    for (e = t.e; e->key; e++) {
        if (fn_80291188(s, e->key) == 0) {
            return e - t.e;
        }
    }
    return -1;
}

void fn_8014FF44(Msg* m) {
    
    int i;
    char* s;
    int y;
    int k;
    int d;
    f32 w;
    
    m->alpha += m->dalpha;
    if (m->alpha > 0xFF) {
        m->alpha = 0xFF;
    }
    if (m->alpha < 0) {
        m->alpha = 0;
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 17.0f, 1.0f);
    fn_8007E174(NULL, 0x10);
    fn_8007E7DC(m->alpha);
    fn_8007E164();
    fn_800800D4(1);
    fn_800803F0(16.0f, 43.0f, 592.0f, 434.0f);
    fn_800804D4(0, 0, 0, 0xE0);
    fn_80080308();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 16.0f, 1.0f);
    fn_8007E174(NULL, 0x13);
    fn_8007E74C(fn_8014FC58, NULL);
    fn_8007E164();
    for (i = 0; i < 0x13; i++) {
        int n = m->line - i - m->scroll / 25;
        if (n < 0) {
            break;
        }
        s = LINE(m, n);
        y = m->scroll % 25 + (0x191 - i * 25);
        if (s[0] == '-') {
            if (s[1] == 'F') {
                CT t = lbl_80369E70;
                char buf[0x1C];
                k = FindCol(t, s + 3);
                if (k >= 0) {
                    fn_8007E154();
                    fn_8007E41C(*(int*)(m->pad4220 + 8), k, 0, 0x10);
                    fn_8007E164();
                    fn_800800D4(1);
                    fn_80080388(48.0f, y + 0x16, 64.0f, 64.0f);
                    fn_80080308();
                    fn_8007E154();
                    fn_8007E174(NULL, 0x13);
                    fn_8007E164();
                }
                fn_80290DDC(buf, lbl_80369FE8 + 0x11, fn_80291314(s, '*') + 1);
                w = 0.4f * (f32)fn_800CA3DC(fn_800C4058(buf), -1, 1.0f);
                fn_800800D4(5);
                fn_80080330(80.0f - w, y + 0x56);
                fn_80080508(*fn_800CD204(0xD));
                fn_80080A94(0.8f);
                fn_80080C24(fn_800C4058(buf));
                fn_80080308();
            }
        } else {
            d = 0;
            if (*(u32*)(s + 1) == 0x23463031) {
                d = -4;
            }
            fn_800800D4(6);
            fn_80080508(lbl_80386D90[(s8)s[0] - 0x30]);
            fn_80080330(128.0f, y + d);
            fn_80080C24(s + 1);
            fn_80080308();
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    if (m->obj != NULL) {
        fn_80179A7C(m->obj, (u8)m->alpha);
        fn_80179888(m->obj, m->h423A - m->scroll);
        fn_80179A84(m->obj);
    }
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}
}
