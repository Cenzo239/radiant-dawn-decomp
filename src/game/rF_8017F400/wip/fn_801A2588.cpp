#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "MIR_NAVI_SELECT"; p[1] = "\x81H\x81H\x81H\x81H\x81H\x81H";
}
struct C4 { u8 r, g, b, a; };
struct TexH { u16 x0, x2; };
typedef struct IEnt { void* a; const char* b; } IEnt;
typedef struct IG {
    void* res0; void* res4; void* res8; int xC;
    s16 x10, x12, x14, x16, x18, x1A, x1C, x1E;
    u8 x20; u8 pad21; s16 x22; f32 x24; s16 x28, x2A, x2C, x2E;
    IEnt* x30; char x34[0x60]; void* x94;
} IG;
extern IG* lbl_804CB94C;
extern s8 lbl_804CB950;
extern s16 lbl_804CB958[4];
extern void fn_801A2570(void* p, void* arg);
extern f32 fn_8017F68C(int a, f32 x, f32 y, f32 t, f32 d);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void* fn_80006A0C(void*, int);
extern const u8* fn_800CD204(int);
extern void fn_801BC88C(void* a, int b, C4* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(int, int);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_8007E7B4(void);
extern void fn_8007E74C(void (*)(void*, void*), s16*);
extern const char* fn_800D0864(const char*);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080308(void);
extern void fn_80070688(f32, f32, f32, f32);
extern void fn_80074EB4(int, int, int, int);
extern u32 fn_8025F6A0(void*);
extern void** fn_802600A4(void*);
extern void* fn_80076F54(void*);
extern const char* fn_80118C44(void*);
extern int fn_801D09F0(void);
extern void fn_800712E8(int, int, int);
extern void fn_80072ACC(int, int, int, int, int, int, int);
extern void fn_801C6D9C(char*, int, int, int);
extern void fn_8017980C(void*, int, int, int);
extern void fn_80179888(void*, int);
extern void fn_8017985C(void*, int);
extern void fn_80179864(void*, int);
extern void fn_80179854(void*, f32);
extern void fn_80179A84(void*);

static inline void Spr(int tile, f32 x, f32 y) {
    C4 c;
    C4 t;
    const u8* cp = fn_800CD204(1);
    c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = 0xFF;
    TexH* q = *(TexH**)fn_80006A0C(lbl_804CB94C->res0, tile);
    f32 tw = q->x2;
    f32 th = q->x0;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(lbl_804CB94C->res0, tile, &t, 0x11, 0, x, y, x + tw, y + th, 0.0f, 0.0f, tw, th);
}
static inline int Rows(IG* g) {
    int r = g->x20 / 3;
    if (g->x20 % 3 > 0) r++;
    return r;
}

void fn_801A2588(void) {
    IG* g = lbl_804CB94C;
/*P*/
    int y;
    int t;
    const char* s;
    int i;
    int h;
    int x;
    int idx;
    u16 w;
    u16 hh;
    int off;
    IEnt* ents;
    int o;
/*E*/
    if (g->x16 > 0) {
        int k = 4;
        g->x16--;
        t = k - lbl_804CB94C->x16;
        lbl_804CB94C->x12 = (int)fn_8017F68C(k, lbl_804CB94C->x18, lbl_804CB94C->x1C, t, k);
        lbl_804CB94C->x14 = (int)fn_8017F68C(k, lbl_804CB94C->x1A, lbl_804CB94C->x1E, t, k);
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    Spr(0, 0.0f, 0.0f);
    fn_801BCA5C(-1.0f);
    if (lbl_804CB94C->xC & 2) {
        if (!lbl_804CB950) lbl_804CB950 = 1;
        h = g->x22;
        lbl_804CB958[0] = 0;
        lbl_804CB958[1] = 0x98;
        lbl_804CB958[2] = 0x260;
        lbl_804CB958[3] = h - 0x2E;
        if (g->x2C > 0) {
            g->x2C--;
            g->x24 = fn_8017F68C(0, g->x28, g->x2A, g->x2E - g->x2C, g->x2E);
        }
        Spr(2, 0.0f, 62.0f);
        fn_801BCA5C(-1.0f);
        s = fn_800D0864("MIR_NAVI_SELECT");
        fn_801BCA94();
        fn_800CB3A8(0.8f, 0.0f, 0x130 - fn_800CA3DC(s, -1, 0.8f) / 2, 0x43, 0x3E, 0, 0, s);
        Spr(1, 17.0f, 14.0f);
        fn_801BCA5C(-1.0f);
        fn_8007E154();
        fn_8007E174(0, 0x12);
        fn_8007E164();
        fn_800800D4(1);
        {
        int a = 0x3F, b = 0x82, c = 0x1E2;
        fn_80080388(a, b, c, h - 4);
        }
        fn_800804D4(0, 0, 0, 0x99);
        fn_80080308();
        fn_801BCA5C(-1.0f);
        {
        int a = 0x3B, b = 0x80, c = 0x1EA;
        fn_80070688(a, b, c, h);
        }
        {
        int k3 = 3;
        int y0 = 0x98;
        for (i = 0; i < 0x1B; i++) {
            idx = (int)((f32)k3 * (g->x24 - 1.0f) + (f32)i);
            if (idx < 0 || idx >= g->x20) continue;
            ents = g->x30;
            o = idx * 8;
            if (*(void**)((u8*)ents + o) == 0) break;
            x = (s16)((idx % 3) * 0x92 + 0x4D);
            y = (int)(28.0f * ((f32)(idx / 3) - g->x24) + (f32)y0);
            fn_8007E154();
            fn_8007E74C(fn_801A2570, lbl_804CB958);
            fn_8007E164();
            fn_80074EB4(x + 6, (s16)y + 0x14, 0x7E, 0x80);
            fn_801BCA5C(-5.0f);
            fn_801BCA94();
            if (fn_8025F6A0(*(void**)((u8*)ents + o)) == 1) {
                fn_800CB3A8(1.0f, 0.0f, x + 0xC, y, 1, 1, 0, fn_80118C44(fn_80076F54(*fn_802600A4(*(void**)((u8*)ents + o)))));
            } else {
                fn_800CB3A8(1.0f, 0.0f, x + 0xC, y, 0, 1, 0, "\x81H\x81H\x81H\x81H\x81H\x81H");
            }
            fn_801BCA5C(5.0f);
            fn_8007E154();
            fn_8007E7B4();
            fn_8007E164();
        }
        }
        fn_801BCA5C(3.0f);
    }
    if (lbl_804CB94C->xC & 4) {
        C4 c;
        TexH* q = *(TexH**)fn_80006A0C(lbl_804CB94C->res4, 0);
        w = q->x2;
        hh = q->x0;
        off = fn_801D09F0() ? 0x66 : 0x28;
        {
        const u8* cp = fn_800CD204(1);
        c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = cp[3];
        fn_801BC88C(lbl_804CB94C->res4, 0, &c, 0x11, 0, off, 24.0f, off + w, hh + 0x18, 0.0f, 0.0f, w, hh);
        }
    }
    if (lbl_804CB94C->xC & 1) {
        fn_801BCA5C(-10.0f);
        fn_800712E8(lbl_804CB94C->x12, lbl_804CB94C->x14, 1);
        fn_801BCA5C(5.0f);
        fn_80072ACC(lbl_804CB94C->x12 + 0x45, lbl_804CB94C->x14 + 0xE, 0x88, 0x17, 0x19, 0x4B, 1);
        fn_801BCA5C(-5.0f);
        fn_801BCA5C(10.0f);
    }
    if (lbl_804CB94C->x34[0]) fn_801C6D9C(lbl_804CB94C->x34, 0xFF, 0xFF, 0);
    fn_801BCA5C(1.0f);
    {
    IG* d = lbl_804CB94C;
    if (d->xC & 2) {
        if (Rows(g) > 7) {
            fn_8017980C(d->x94, 0x20F, 0x88, 0xE0);
            fn_80179888(lbl_804CB94C->x94, (int)g->x24);
            fn_8017985C(lbl_804CB94C->x94, Rows(g));
            fn_80179864(lbl_804CB94C->x94, 7);
            fn_80179854(lbl_804CB94C->x94, 95.0f);
            fn_80179A84(lbl_804CB94C->x94);
        }
    }
    }
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}
}
