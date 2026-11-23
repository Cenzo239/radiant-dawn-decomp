/* NEAR MISS: 9 lines: entry pointer e should be r27, name s r28; declaration order has no effect. */
/* Result report: list body */
#include "game/rN_8025EEF0/prim2d.h"

struct GXC { u8 r, g, b, a; };
struct Ent { u8 id; u8 p1; s16 m2; int v; };
struct Rep {
    void* tex;
    void* bar;
    s16 n;
    u8 padA[2];
    Ent e[0x40];
    f32 pad;
};
struct Rect16 { s16 x, y, w, h; };

extern "C" {

extern Rep* lbl_804CC0D4;
extern s8 lbl_804CC0D8;
extern Rect16 lbl_804CC0E0;
extern char lbl_80373CF0[];
void fn_80287834(void* p, void* arg);
void fn_8007E74C(void* f, void* a);
void fn_8007E7B4(void);
void fn_8017980C(void* p, int a, int b, int c);
void fn_80179888(void* p, int a);
void fn_8017985C(void* p, int a);
void fn_80179864(void* p, int a);
void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC* c, int d, int e);
void* fn_8010B094(int a);
void fn_8028784C(f32 x, f32 y);
const char* fn_800928B0(void* p);
const char* fn_80092904(void* p);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_801C6DA0(f32 x, f32 y, int a, const char* s);
void* fn_8010B1B4(int a);
const char* fn_80118C44(void* p);
void fn_800804D4(int r, int g, int b, int a);
void fn_80080330(f32 x, f32 y);
void fn_80080B00(f32 s, int a, u8* c);
void fn_80080C24(const char* s);

static inline f32 frac(f32 v) { return v - (f32)(int)v; }
static inline f32 row(int i, f32 v) { return (f32)i - (v - (f32)(int)v); }
void fn_80287B54(f32 x, f32 y) {
    char buf[0x10];
/*P*/
    int i;
    const char* s;
    const char* s2;
    Ent* e;
    void* v;
    void* b;
    int k;
    f32 yy;
/*E*/
    b = lbl_804CC0D4->bar;
    fn_8017980C(b, (int)(505.0f + x), (int)(86.0f + y), 0x10C);
    { f32 mm = *(f32*)((u8*)lbl_804CC0D4 + 0x210); fn_80179888(b, mm * 28.0f); }
    if (lbl_804CC0D4->n > 0) {
        fn_8017985C(b, lbl_804CC0D4->n * 0x1C);
        fn_80179864(b, 0xFC);
    } else {
        fn_8017985C(b, 0x1C);
        fn_80179864(b, 0x1C);
    }
    fn_801BCA5C(-1.0f);
    {
        u16* d = *fn_80006A0C(lbl_804CC0D4->tex, 1);
        f32 h;
        f32 w;
        w = d[1];
        h = d[0];
        {
            GXC t; GXC a;
            const u8* p = fn_800CD204(1);
            t.r = p[0]; t.g = p[1]; t.b = p[2]; t.a = 0xFF;
            d = *fn_80006A0C(lbl_804CC0D4->tex, 1);
            {
                f32 tw = d[1];
                f32 th = d[0];
                *(u32*)&a = *(u32*)&t;
                fn_801BC88C(x, y, x + w, y + h, 0.0f, 0.0f, tw, th, lbl_804CC0D4->tex, 1, &a, 0x11, 0);
            }
        }
    }
    fn_801BCA5C(-1.0f);
    if (lbl_804CC0D8 == 0) {
        lbl_804CC0E0.x = 0;
        lbl_804CC0E0.y = (int)(95.0f + y);
        lbl_804CC0E0.w = 0x280;
        lbl_804CC0E0.h = 0xFE;
        lbl_804CC0D8 = 1;
    }
    fn_8007E154();
    fn_8007E74C(fn_80287834, &lbl_804CC0E0);
    fn_8007E164();
    for (i = 0; i < 10; i++) {
        k = i + (int)*(f32*)((u8*)lbl_804CC0D4 + 0x210);
        if (k >= lbl_804CC0D4->n) break;
        e = &lbl_804CC0D4->e[k];
        v = fn_8010B094(e->id);
        yy = 28.0f * ((f32)i - frac(*(f32*)((u8*)lbl_804CC0D4 + 0x210))) + (96.0f + y);
        if (i == 0) fn_8028784C(54.0f + x, yy);
        fn_801BCA94();
        s = fn_800928B0(v);
        fn_801C6DA0((98.0f + x) - (f32)(fn_800CA3DC(s, -1, 1.0f) / 2), 2.0f + yy, 8, s);
        s2 = fn_80092904(v);
        fn_801C6DA0((160.0f + x) - (f32)(fn_800CA3DC(fn_80092904(v), -1, 1.0f) / 2), 2.0f + yy, 8, s2);
        fn_801C6DA0(220.0f + x, 2.0f + yy, 8, fn_8010B1B4(e->m2) != 0 ? fn_80118C44(fn_8010B1B4(e->m2)) : fn_800D0864(lbl_80373CF0));
        fn_80290DDC(buf, lbl_80373CF0 + 0x12, e->v);
        fn_801BCA94();
        fn_800800D4(5);
        fn_80080330((int)(386.0f + x), (int)(2.0f + yy));
        fn_800804D4(0, 0x61, 0, 0xFF);
        fn_80080B00(2.0f, 1, fn_800CD204(0x2A));
        fn_80080C24(buf);
        fn_80080308();
        fn_8028784C(54.0f + x, 28.0f + yy);
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_801BCA5C(2.0f);
}

}
