/* video.cpp: draw the screen position / width adjust menu. Names guessed. */
#include "game/rJ_800799AC/types.h"

struct C4 { u8 r, g, b, a; };
struct Tex { u8 d[0x20]; };
struct TexWH { Tex tex; u16 w, h; };
struct AdjProc {
    u8 pad[0x30];
    void* img;      /* 0x30 */
    u8 dirty;       /* 0x34 */
    void* arrow[3]; /* 0x38 */
};

extern "C" {
extern s8 lbl_804CB600;
extern s8 lbl_804CB601;
extern s8 lbl_804CA3D4;
extern char lbl_803814C0[], lbl_803814B0[], lbl_803814A4[], lbl_80381498[], lbl_80381484[];
extern char lbl_80381438[], lbl_8038144C[], lbl_80381460[], lbl_80381474[];
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(void*, int);
void fn_800800D4(int);
#if TARGET_PC
FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
void fn_80080910(void*, void*);
#endif
void fn_80080308(void);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E7DC(int);
void fn_80006A64(void*, Tex*, int);
u16 fn_80305DF8(Tex*);
u16 fn_80305E0C(Tex*);
void fn_80080388(f32, f32, f32, f32);
void fn_8007E720(f32);
const char* fn_800D0864(const char*);
int fn_80290DDC(char*, const char*, ...);
int fn_800CA3DC(f32, const char*, int);
void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
void fn_80080330(f32, f32);
void fn_80080508(C4);
void fn_80080C24(const char*);
void fn_800CB278(int, int, int, const char*, ...);
void fn_801C6D9C(char*, int, int, int);
void fn_80179214(void*);
void fn_8017918C(void*, int, int);
const char* fn_800CF3A4(void);
const char* fn_800CF470(void);
const char* fn_800CF6E0(void);
const char* fn_800CEC24(void);
const char* fn_800CECFC(void);
const char* fn_800CEB4C(void);
void fn_8008CA90(void);

void fn_8008C594(AdjProc* p) {
    TexWH t;
    char buf[0x80];
    int w;
    int v;
    int y;
    int i;
    if (p->dirty) {
        fn_8007E154();
        fn_8007E174(0, 0x410);
        fn_8007E164();
        fn_800800D4(0xb);
        fn_80080910(fn_8008CA90, 0);
        fn_80080308();
        p->dirty = 0;
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 10.0f, 1.0f);
    fn_8007E7DC(0xff);
    fn_8007E164();
    fn_80006A64(p->img, &t.tex, 0);
    t.w = fn_80305DF8(&t.tex);
    t.h = fn_80305E0C(&t.tex);
    fn_8007E154();
    fn_8007E174(&t.tex, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(0.0f, 0.0f, t.w, t.h);
    fn_80080308();
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_80290DDC(buf, "%s", fn_800D0864(lbl_803814C0));
    w = fn_800CA3DC(0.75f, buf, -1);
    fn_800CB3A8(0.75f, 0.0f, 0x130 - w / 2, 0x44, 1, 0, 0, buf);
    fn_80290DDC(buf, "%s", fn_800D0864(lbl_803814B0));
    fn_800800D4(5);
    w = fn_800CA3DC(1.0f, buf, -1);
    fn_80080330(0x130 - w / 2, 114.0f);
    {
        C4 c = {0xFF, 0xBC, 0x75, 0xFF};
        fn_80080508(c);
    }
    fn_80080C24(buf);
    fn_80080308();
    fn_80290DDC(buf, "%s %s", fn_800CF3A4(), fn_800D0864(lbl_803814A4));
    fn_800CB278(0x6d, 0xa4, 1, buf);
    v = (s8)*(u8*)&lbl_804CB601;
    if (v == 0) {
        fn_80290DDC(buf, " %2d", v);
    } else if (-v < 0) {
        fn_80290DDC(buf, "-%2d", v);
    } else {
        fn_80290DDC(buf, "+%2d", -v);
    }
    fn_800CB278(0x1c8, 0xa4, 1, buf);
    fn_80290DDC(buf, "%s %s", fn_800CF470(), fn_800D0864(lbl_80381498));
    fn_800CB278(0x6d, 0xe4, 1, buf);
    v = (s8)*(u8*)&lbl_804CB600;
    if (v == 0) {
        fn_80290DDC(buf, " %2d", v);
    } else if (v < 0) {
        fn_80290DDC(buf, "-%2d", -v);
    } else {
        fn_80290DDC(buf, "+%2d", v);
    }
    fn_800CB278(0x1c8, 0xe4, 1, buf);
    fn_80290DDC(buf, "%s %s", fn_800CF6E0(), fn_800D0864(lbl_80381484));
    fn_800CB278(0x6d, 0x124, 1, buf);
    v = lbl_804CA3D4 - 0x40;
    if (v == 0) {
        fn_80290DDC(buf, " %2d", v);
    } else if (v < 0) {
        fn_80290DDC(buf, "-%2d", -v);
    } else {
        fn_80290DDC(buf, "+%2d", v);
    }
    fn_800CB278(0x1c8, 0x124, 1, buf);
    fn_80290DDC(buf, lbl_80381474, fn_800CEB4C(), fn_800D0864(lbl_80381460), fn_800CECFC(),
                fn_800D0864(lbl_8038144C), fn_800CEC24(), fn_800D0864(lbl_80381438));
    fn_801C6D9C(buf, 0xff, 0xff, 0);
    for (i = 0, y = 0xb1; i < 3; i++, y += 0x40) {
        fn_80179214(p->arrow[i]);
        fn_8017918C(p->arrow[i], 0x19a, y);
    }
}
}
