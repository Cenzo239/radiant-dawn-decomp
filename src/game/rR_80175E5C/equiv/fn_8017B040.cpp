/* fn_8017B040: functionally equal (regs, 12 of 72 words differ in registers only). Helpers from fn_8017B160.cpp (exported bodies removed), body from wip/fn_8017B040.cpp. */
/* Screen filter process: blur, cross-fade, glow, zoom, depth of field, wave. */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
#include "game/rR_80175E5C/strpool.h"
#define FIFOF (*(volatile f32*)0xCC008000)
#define F(p, t, o) (*(t*)((u8*)(p) + (o)))

struct C4 { u8 r, g, b, a; };

struct Filter {
    u8* base;
    int a;
    int b;
    int c;
    int d;
    u8 pad14[0x24 - 0x14];
    u8 mode;
    u8 a1;
    u8 a2;
    u8 n;
    s16 x28;
    u8 x2a;
    C4 col;
};

extern "C" {
extern char lbl_804CB8CA;
extern void* lbl_804CB8CC;
extern u8 lbl_80387B88[], lbl_80387BB0[], lbl_80387C38[];
void fn_803031CC();
void fn_80302B80(int, int);
void fn_80303200(int, int, int, int, int);
void fn_80021C34(u8);
void fn_80021B2C(int);
void fn_80021A08(int, int, int, int, int, int, int);
void fn_80021BF4(u8);
void fn_80021CB4(int, int, int, int);
void fn_80021860(int, int, int);
void fn_80021B68(int);
void fn_80021BA4(int, int, int, int);
void fn_80304314(int, int, int);
void fn_80011838(int);
void fn_80305A40(void*, void*, u16, u16, int, int, int, int);
void fn_80305C94(void*, int, int, f32, f32, f32, int, int, int);
void fn_80022254(void*, int);
void fn_80021E20(int, int, int, int, int);
void fn_80021D18(int, int, int, int, int, int);
void fn_80021E8C(int, int, int, int, int);
void fn_80021D9C(int, int, int, int, int, int);
void fn_80307F10(void*, int, int);
void fn_80021F7C(int, int, int, int);
void fn_80012268();
int fn_80011EB4();
int fn_80011F38();
int fn_80011E28();
int fn_80011EAC();
int fn_80011FBC();
int fn_80011FC4();
int fn_80012048();
void fn_80306EA0(int, C4);
void fn_80021FF0(int, int);
void fn_8000FF74(int);
void fn_800104DC(int);
void fn_8001F4D8(int, int, int, int, int, int, void*, int, int);
void fn_8001F5B8(int, int, int, int, int, int, void*, int, C4*, void*, u16);
int fn_80007630(void*, const char*);
int fn_8030585C(int, int, int, int, int);
void fn_80020E7C(int);
void* fn_80020E74();
void* fn_80078D9C(int, const char*, int);
void DCFlushRange(void*, int);
void fn_8017F464(void*, u32, int);
void fn_80021958(int, C4);
void fn_800218A8(int, C4);
void fn_80021C74(int);
void fn_80306B6C(int, int, int, int, int);
void fn_8001E51C(void*);
void fn_803067E0(int, void*, s8);
void fn_80306A38(int, int, int);
void fn_80306934(int, int, int);
void fn_80306B24(int);
void fn_8031292C(void*, f32, f32, f32);
u32 fn_80089ED0();
void* fn_80007F3C(void*);
void fn_80014E24(void*, const char*, void*, int);
void* fn_800893E4(void*, void*, void*);
void fn_8017D838(void* p, void* arg);
void fn_8017D84C(void*);
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
char* strcpy(char*, const char*);
void fn_800CB278(int, int, int, const char*, ...);
void fn_8007E4E4(f32, f32, f32, f32);
void* fn_80010BB0(void*);
void* fn_80010DA4(void*, int);
void* fn_80010E38(void*, int);
void fn_80081A90(void*);
void fn_8007E154();
void fn_8007E164();
void fn_8007E174(void* tex, u16 flags);
void fn_800800D4(int mode);
void fn_80080308();
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080578(int);
void fn_80080940(C4 a, C4 b, C4 c, C4 d);

static inline void Pos(f32 x, f32 y, f32 z) {
    FIFOF = x;
    FIFOF = y;
    FIFOF = z;
}
static inline void Tc(f32 s, f32 t) {
    FIFOF = s;
    FIFOF = t;
}

static inline void Konst(u8 a) {
    C4 c;
    c.r = a;
    c.g = a;
    c.b = a;
    c.a = a;
    fn_80306EA0(0, c);
}
void fn_8017B160(int x, int y, int w, int h, int tw, int th, void* tex, int fmt, u8 a, u8 add);

void fn_8017C2F4(void* a);


static inline const C4& White() {
    C4 c = {0xFF, 0xFF, 0xFF, 0xFF};
    return c;
}
void fn_8017CD80(void* a);

void fn_8017D1DC(u8* o);

void fn_8017D84C(void* a);

void fn_8017DAD4(const char* name, int a, void* parent, int b);

void fn_8017DC24(f32 r, f32 g, f32 t, int lo, int hi);

void fn_8017E25C(u8* o);

void fn_8017E9E0(u8* o);

}

/* ---- from rR_80175E5C/wip/fn_8017B040.cpp ---- */
extern "C" {
/* fn_8017B040: 12 of 72 words differ, all volatile register numbers around the wait countdown and the fn_8001EBC8 arguments. Uses the declarations of fn_8017B160.cpp. */
struct FadeIn {
    u8 pad0[0x30];
    Filter* f;
    u8 pad34[0x34 - 0x34];
    u16 t;
    u16 dur;
    u16 from;
    u16 to;
    u8 pad3C[2];
    s16 wait;
};

void fn_8017B638(Filter* o);
void fn_80010788(int, int, void*, void*);
f32 fn_8001EBC8(f32, f32, f32, f32, int);
void fn_80083B78(void*);
void fn_8017B040(FadeIn* o) {
    fn_80010788(3, 0x9C, fn_8017B638, o->f);
    if (o->wait > 0) {
        s16 w = o->wait - 1;
        o->wait = w;
        if (w == 0) {
            o->t = 0;
            o->dur = o->dur * 2;
            o->from = 0xFF;
            o->to = 0;
        }
    }
    if (o->t < o->dur) {
        u16 nt = o->t + 1;
        o->t = nt;
        o->f->a2 = fn_8001EBC8(o->from, o->to, o->dur, nt, 2);
    } else {
        o->f->a2 = o->to;
        if (o->to == 0) fn_80083B78(o);
    }
}
}
