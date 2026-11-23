/* fn_8017B638: 9 of 710 words differ. In the three blur loops mr r9 comes after li r5 and li r6 in the fn_8001F4D8 call, and only the scheduler order differs. Case order is from the jump table. Compiles on its own. */
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

void fn_8017B160(int x, int y, int w, int h, int tw, int th, void* tex, int fmt, u8 a, u8 add);
void fn_8017B638(Filter* o) {
    /*P*/
    u8* tex3;
    int tw1;
    int tw3;
    int i1;
    int th1;
    int th3;
    u8* tex1;
    int i3;
    int v;
    u8* tex7;
    int tw7;
    int th7;
    int i7;
    int i3b;
/*E*/
    u8 obj[0x20];
    C4 col[4];
    C4 t;
    v = o->a1 * o->a2 / 0xFF;
    if (v == 0) return;
    t.r = o->col.r;
    t.g = o->col.g;
    t.b = o->col.b;
    t.a = o->col.a;
    u32 w = *(u32*)&t;
    *(u32*)&col[0] = w;
    *(u32*)&col[1] = w;
    *(u32*)&col[2] = w;
    *(u32*)&col[3] = w;
    col[3].a = v;
    col[2].a = v;
    col[1].a = v;
    col[0].a = v;
    fn_8000FF74(0);
    fn_80021860(0, 3, 0);
    switch (o->mode) {
    case 0:
        if (!o->x2a) {
            fn_8001F5B8(0, 0, 0x260, 0x1C0, 0x260, 0x1C0, o->base + o->a, 6, col, 0, 0);
        }
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x260, 0x1C0, o->base + o->a, 6, 0);
        break;
    case 5:
        if (!o->x2a) {
            int k = o->x28;
            fn_8001F5B8(k, k, 0x260 - k * 2, 0x1C0 - k * 2, 0x260, 0x1C0, o->base + o->a, 6, col, 0, 0);
        }
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x260, 0x1C0, o->base + o->a, 6, 0);
        break;
    case 6:
        if (!o->x2a) {
            int d = o->x28 * 2;
            int k = -o->x28;
            fn_8001F5B8(k, k, d + 0x260, d + 0x1C0, 0x260, 0x1C0, o->base + o->a, 6, col, 0, 0);
        }
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x260, 0x1C0, o->base + o->a, 6, 0);
        break;
    case 10:
        col[0].r = col[0].g = col[0].b = v;
        col[1].r = col[1].g = col[1].b = v;
        col[2].r = col[2].g = col[2].b = v;
        col[3].r = col[3].g = col[3].b = v;
        { int kk = 0x10000; fn_8001F5B8(0, 0, 0x260, 0x1C0, 0, 0, 0, 6, col, 0, kk - 0x6000); }
        break;
    case 1:
        fn_8001F4D8(0, 0, 0x130, 0xE0, 0x130, 0xE0, o->base + o->a, 6, 0);
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x130, 0xE0, o->base + o->b, 6, 0);
        tw1 = 0x130;
        th1 = 0xE0;
        tex1 = o->base + o->b;
        for (i1 = 0; i1 < o->n; i1++) {
            fn_8001F5B8(0, 0, 0x130, 0xE0, tw1, th1, tex1, 6, 0, 0, 0);
            tw1 = 0x98;
            th1 = 0x70;
            tex1 = o->base + o->c;
            fn_8001F4D8(0, 0, 0x130, 0xE0, 0x98, 0x70, tex1, 6, 0);
        }
        fn_8001F5B8(0, 0, 0x130, 0xE0, 0x130, 0xE0, o->base + o->a, 6, 0, 0, 0);
        fn_8001F5B8(0, 0, 0x260, 0x1C0, tw1, th1, tex1, 6, col, 0, 0);
        break;
    case 3:
        fn_8001F4D8(0, 0, 0x130, 0xE0, 0x130, 0xE0, o->base + o->a, 6, 0);
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x130, 0xE0, o->base + o->b, 6, 0);
        tw3 = 0x130;
        th3 = 0xE0;
        tex3 = o->base + o->b;
        for (i3 = 0; i3 < o->n; i3++) {
            fn_8001F5B8(0, 0, 0x130, 0xE0, tw3, th3, tex3, 6, 0, 0, 0);
            tw3 = 0x98;
            th3 = 0x70;
            tex3 = o->base + o->c;
            fn_8001F4D8(0, 0, 0x130, 0xE0, 0x98, 0x70, tex3, 6, 0);
        }
        fn_8001F5B8(0, 0, 0x130, 0xE0, 0x130, 0xE0, o->base + o->a, 6, 0, 0, 0);
        fn_8001F5B8(0, 0, 0x260, 0x1C0, tw3, th3, tex3, 6, col, 0, 0x2000);
        for (i3b = 1; i3b < o->x28; i3b++) {
            fn_8001F5B8(0, 0, 0x260, 0x1C0, tw3, th3, tex3, 6, col, 0, 0x2000);
        }
        break;
    case 7:
    case 8:
        fn_8001F4D8(0, 0, 0x130, 0xE0, 0x130, 0xE0, o->base + o->a, 6, 0);
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x130, 0xE0, o->base + o->b, 6, 0);
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x130, 0xE0, o->base + o->d, 0x13, 0);
        tw7 = 0x130;
        th7 = 0xE0;
        tex7 = o->base + o->b;
        for (i7 = 0; i7 < o->n; i7++) {
            fn_8001F5B8(0, 0, 0x130, 0xE0, tw7, th7, tex7, 6, 0, 0, 0);
            tw7 = 0x98;
            th7 = 0x70;
            tex7 = o->base + o->c;
            fn_8001F4D8(0, 0, 0x130, 0xE0, 0x98, 0x70, tex7, 6, 0);
        }
        if ((s8)o->mode == 7) {
            fn_8017B160(0, 0, 0x98, 0x70, 0x130, 0xE0, o->base + o->d, 0x13, o->x28, 0);
        }
        if ((s8)o->mode == 8) {
            fn_8017B160(0, 0, 0x98, 0x70, 0x130, 0xE0, o->base + o->d, 0x13, o->x28, 1);
        }
        fn_8001F4D8(0, 0, 0x98, 0x70, 0x98, 0x70, o->base + o->d, 1, 0);
        fn_8001F5B8(0, 0, 0x130, 0xE0, 0x130, 0xE0, o->base + o->a, 6, 0, 0, 0);
        fn_80305A40(obj, o->base + o->d, 0x98, 0x70, 1, 0, 0, 0);
        fn_80305C94(obj, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
        fn_8001F5B8(0, 0, 0x260, 0x1C0, tw7, th7, tex7, 6, col, obj, 0);
        break;
    case 2:
        if (o->x2a) {
            fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x130, 0xE0, o->base + o->a, 6, 0);
        } else {
            fn_8001F5B8(0, 0, 0x260, 0x1C0, 0x130, 0xE0, o->base + o->a, 6, col, 0, 0);
        }
        break;
    case 4:
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x260, 0x1C0, o->base + o->a, 0x28, 0);
        fn_8001F5B8(0, 0, 0x260, 0x1C0, 0x260, 0x1C0, o->base + o->a, 0x28, col, 0, 0);
        break;
    case 0xC:
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x260, 0x1C0, o->base + o->a, 0x28, 0);
        fn_8001F5B8(0, 0, 0x260, 0x1C0, 0x260, 0x1C0, o->base + o->a, 0x28, col, 0, 0);
        break;
    case 9:
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x130, 0xE0, o->base + o->a, 0x13, 0);
        fn_80305A40(obj, o->base + o->a, 0x130, 0xE0, 0x13, 0, 0, 0);
        fn_80305C94(obj, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
        fn_8001F5B8(0, 0, 0x260, 0x1C0, 0x130, 0xE0, 0, 0x13, col, obj, 0);
        break;
    case 11:
        break;
    }
    fn_800104DC(0);
    o->x2a = 0;
}

}
