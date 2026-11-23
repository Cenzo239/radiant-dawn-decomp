/* Unit slot menu: unit info window */
#pragma inline_max_size(4000)
#include "game/rN_8025EEF0/calls.h"
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int b);
#else
void fn_8007E174(int a, int b);
#endif
void fn_8007E4E4(f32 x, f32 y, f32 z, f32 s);
void fn_8007E7DC(u8 alpha);
}

struct GXC { u8 r, g, b, a; };

extern "C" {

extern s8 lbl_804CC031;
extern char lbl_804CAB00[8], lbl_804CAAFC[4], lbl_804CAAF4[8], lbl_804CAAF0[4], lbl_804CAAE8[8];
extern u8 lbl_803E7290[];
struct InfoB { u8 pad[0x44]; };
class Info : public InfoB {
public:
    virtual void v8(); virtual void vC(); virtual void v10(); virtual void v14();
    virtual void v18(int x, int y, const char* s);
};
struct InfoWin {
    u8 pad[0x34];
    void* tex;
    void* m38;
    u8* unit;
    f32 m40, m44, m48, m4C, m50;
};
void fn_8007E7E8(int a);
void fn_8007E720(f32 v);
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC* c, int d, int e);
void fn_800C4AAC(void* a, void* b, int x, int y, int al, int f);
void* fn_801246A4(void* u);
void fn_80074EB4(int x, int y, int a, int b);
void fn_801BCA94(void);
void fn_800CB278(s16 x, s16 y, int c, const char* s, ...);
const char* fn_80118C44(void* u);
const char* fn_80118F00(void* u);
#if TARGET_PC
FE10_PROTO ptr32<const char> fn_801196F0(u8 k);
#else
const char* fn_801196F0(u8 k);
#endif
int fn_801237EC(void* u);

static inline void mkc(GXC& t, const u8* p, u8 al) { t.r = p[0]; t.g = p[1]; t.b = p[2]; t.a = al; }
static inline void spr(void* tex, int i, f32 x, f32 y, f32 w, f32 h, f32 s, GXC& t, GXC& a, int rot) {
    u16* d = *fn_80006A0C(tex, i);
    f32 tw = d[1];
    f32 th = d[0];
    *(u32*)&a = *(u32*)&t;
    fn_801BC88C(x, y, w * s + x, h * s + y, 0.0f, 0.0f, tw, th, tex, i, &a, 0x11, rot);
}

static inline void frame(InfoWin* o, f32 x, f32 y, f32 w, f32 h) {
    void* t;
    GXC a1; GXC t1;
    GXC a2; GXC t2;
    GXC a3; GXC t3;
    GXC a4; GXC t4;
    GXC a5; GXC t5;
    GXC a6; GXC t6;
    GXC a7; GXC t7;
    GXC a8; GXC t8;
    GXC a9; GXC t9;
    t = o->tex;
    mkc(t1, fn_800CD204(1), 0xC4);
    spr(t, 6, x, y, w, h, 1.0f, t1, a1, 0);
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E164();
    t = o->tex;
    mkc(t2, fn_800CD204(1), 0xFF);
    spr(t, 3, x, y, 8.0f, 16.0f, 1.0f, t2, a2, 5);
    t = o->tex;
    mkc(t3, fn_800CD204(1), 0xFF);
    spr(t, 4, 8.0f + x, y, w - 16.0f, 8.0f, 1.0f, t3, a3, 0);
    t = o->tex;
    mkc(t4, fn_800CD204(1), 0xFF);
    spr(t, 3, (x + w) - 8.0f, y, 8.0f, 16.0f, 1.0f, t4, a4, 8);
    t = o->tex;
    mkc(t5, fn_800CD204(1), 0xFF);
    spr(t, 5, x, 16.0f + y, 8.0f, h - 32.0f, 1.0f, t5, a5, 4);
    t = o->tex;
    mkc(t6, fn_800CD204(1), 0xFF);
    spr(t, 5, (x + w) - 8.0f, 16.0f + y, 8.0f, h - 32.0f, 1.0f, t6, a6, 8);
    t = o->tex;
    mkc(t7, fn_800CD204(1), 0xFF);
    spr(t, 3, x, (y + h) - 16.0f, 8.0f, 16.0f, 1.0f, t7, a7, 4);
    t = o->tex;
    mkc(t8, fn_800CD204(1), 0xFF);
    spr(t, 4, 8.0f + x, (y + h) - 8.0f, w - 16.0f, 8.0f, 1.0f, t8, a8, 2);
    t = o->tex;
    mkc(t9, fn_800CD204(1), 0xFF);
    spr(t, 3, (x + w) - 8.0f, (y + h) - 16.0f, 8.0f, 16.0f, 1.0f, t9, a9, 9);
}

static inline u8 cls(u8* u) {
    if (*(s8*)(u + 0x118) == -1) return (*(u8**)(u + 0xEC))[0xE1];
    return u[0x118];
}

static inline void body(InfoWin* o) {
/*P*/
    f32 x;
    f32 y;
    f32 w;
    f32 h;
    u8* u;
    int i;
    int k;
/*E*/
    if (lbl_804CC031 > 0) return;
    fn_8007E154();
    fn_8007E4E4(o->m40 + o->m48, o->m44, o->m50, 1.0f);
    fn_8007E174(0, 0x12);
    fn_8007E7DC(255.9f * o->m4C);
    fn_8007E7E8(0x80);
    fn_8007E164();
    if (o->unit == 0) return;
    x = 0.0f;
    y = x;
    w = 286.0f;
    h = 88.0f;
    frame(o, x, y, w, h);
    for (i = 0, k = 0; i < 3; i++, k += 0x1A) {
        fn_80074EB4((int)(24.0f + (64.0f + x)), (int)((18.0f + (5.0f + y)) + (f32)k), 0xB8, 0xA0);
    }
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E164();
    u = o->unit;
    fn_800C4AAC(o->m38, fn_801246A4(u), (int)(12.0f + x), (int)(12.0f + y), (int)(255.9f * o->m4C), 0);
    x += 88.0f;
    y += 5.0f;
    fn_801BCA94();
    fn_800CB278(24.0f + x, y, 1, fn_80118C44(*(void**)(u + 0xEC)));
    {
        const char* s = fn_801196F0(cls(u));
        ((Info*)lbl_803E7290)->v18((int)x, (int)y, s);
    }
    y += 26.0f;
    fn_801BCA94();
    fn_800CB278(x, y, 1, fn_80118F00(*(void**)(u + 0xF0)));
    y += 26.0f;
    fn_800CB278(x, y, 9, fn_800D0864(lbl_804CAB00));
    fn_800CB278(28.0f + x, y, 1, lbl_804CAAFC, *(s8*)(u + 0xFE));
    fn_800CB278(62.0f + x, y, 9, fn_800D0864(lbl_804CAAF4));
    fn_800CB278(94.0f + x, y, 1, lbl_804CAAF0, *(s8*)(u + 0x114));
    fn_800CB278(136.0f + x, y, 0xC, lbl_804CAAE8, (s16)fn_801237EC(u));
}

void fn_8026972C(InfoWin* o) { body(o); }

}
