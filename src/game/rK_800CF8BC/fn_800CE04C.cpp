/* Sprite sheet objects: a file with a texture and optional palette, the blink
 * draw, and three draw variants that pick a cell from a frame number. */
#include "game/rK_800CF8BC/types.h"

struct Colr {
    u8 r, g, b, a;
};
struct SprB {
    void* h;     /* 0x00 file handle */
    u8 o4[0x20]; /* 0x04 texture */
    u8 o24[0xC]; /* 0x24 source palette */
    u8 o30[0xC]; /* 0x30 tinted palette */
    u16* tint;   /* 0x3C */
    u8 hasTlut;  /* 0x40 */
};
class Spr : public SprB {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18(int, int, int);
    virtual void v1C();
    virtual void v20(int, int, int, Colr);
    virtual void v24();
    virtual void v28();
    virtual const char* v2C();
    virtual const char* v30();
    virtual void v34();
    virtual void v38();
    virtual int cols();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual int w();
    virtual int h2();

    void load();
    void blink(int x, int y, int k, int on, u32 a, int period);
    void draw(int x, int y, int frame, const Colr* c);
    void draw2(f32 x, f32 y, int c, int frame);
    void draw3(f32 x, f32 y, f32 z, int a, int t, int frame);
};

extern "C" {
void fn_800068A0(void*, const char*);
struct TexInfo { u8 pad[4]; void* p4; };
#if TARGET_PC
FE10_PROTO TexInfo* fn_80006A0C(void*, ptr32<const void>);
#else
TexInfo* fn_80006A0C(void*, const char*);
#endif
#if TARGET_PC
FE10_PROTO void fn_80006B84(void*, void*, void*, int, ptr32<const void>);
#else
void fn_80006B84(void*, void*, void*, int, const char*);
#endif
#if TARGET_PC
FE10_PROTO void fn_80006A64(void*, void*, ptr32<const void>);
#else
void fn_80006A64(void*, void*, const char*);
#endif
u16 fn_8030604C(void*);
void* fn_80079940(int, int);
void fn_80306018(void*, void*, int, u16);
u32 fn_80306040(void*);
f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_8007E154();
void fn_8007E164();
void fn_8007E174(void*, int);
void fn_8007E244(void*, void*, int, int);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_800800D4(int);
void fn_80080308();
void fn_80080430(f32, f32, f32, f32, f32, f32);
void fn_800804F4(int);
void fn_800804D4(int, int, int, int);
void DCFlushRange(void*, u32);
s64 OSGetTime();
}

#pragma use_lmw_stmw off

extern "C" void fn_800CE04C(Spr* p) {
    if (p->h == 0) {
        fn_800068A0(p, p->v2C());
        if (fn_80006A0C(p->h, p->v30())->p4) {
            u16 n;
            void* m;
            p->hasTlut = 1;
            fn_80006B84(p->h, p->o4, p->o24, 0, p->v30());
            n = fn_8030604C(p->o24);
            m = fn_80079940(n * 2, 0x40);
            p->tint = (u16*)m;
            fn_80306018(p->o30, m, 2, n);
        } else {
            u16* z = 0;
            p->hasTlut = (int)z;
            fn_80006A64(p->h, p->o4, p->v30());
            p->tint = z;
        }
    }
}

extern "C" void fn_800CE208(Spr* p, int x, int y, int k) {
    Colr c;
    *(u32*)&c = 0;
    p->v20(x, y, k, c);
}

static inline void blinkDraw(Spr* p, int x, int y, int k, int v) {
    Colr c = {v, v, v, 255};
    p->v20(x, y, k, c);
}

extern "C" void fn_800CE240(Spr* p, int x, int y, int k, int on, u32 a, int period) {
    if (on == 0) {
        p->v18(x, y, k);
    } else {
        int half = period >> 1;
        u32 t = (OSGetTime() / (*(u32*)0x800000F8 / 4 / 1000)) % period;
        int v;
        if (t < half) {
            v = fn_8017F68C(0, 0.0f, a, t, half);
        } else {
            v = fn_8017F68C(0, a, 0.0f, t - half, half);
        }
        blinkDraw(p, x, y, k, v);
    }
}

extern "C" void fn_800CE3C4(Spr* p, int x, int y, int frame, const Colr* c) {
    if (frame != 0) {
        fn_8007E154();
        if (p->hasTlut) {
            if (c->r == 0 && c->g == 0 && c->b == 0) {
                fn_8007E244(p->o4, p->o24, 0, 0x11);
            } else {
                u16* src = (u16*)(fn_80306040(p->o24) + 0x80000000);
                u16 n = fn_8030604C(p->o24);
                u16 i;
                for (i = 0; i < n; i++) {
                    u16 s = src[i];
                    if (!(s & 0x8000)) {
                        p->tint[i] = s;
                    } else {
                        u16 r = (s & 0x7C00) >> 10;
                        u16 g = (s & 0x3E0) >> 5;
                        u16 b = s & 0x1F;
                        r += c->r >> 3;
                        if (r > 0x1F) r = 0x1F;
                        g += c->g >> 3;
                        if (g > 0x1F) g = 0x1F;
                        b += c->b >> 3;
                        if (b > 0x1F) b = 0x1F;
                        p->tint[i] = (g << 5) | (r << 10) | b | 0x8000;
                    }
                }
                DCFlushRange(p->tint, n * 2);
                fn_8007E244(p->o4, p->o30, 0, 0x11);
            }
        } else {
            fn_8007E174(p->o4, 0x11);
        }
        fn_8007E164();
        {
            f32 h, u, v;
            int cw = p->w();
            int m = (frame - 1) % p->cols();
            u = m * cw;
            int ch = p->h2();
            int n2 = (frame - 1) / p->cols();
            v = n2 * ch;
            fn_800800D4(1);
            h = p->h2();
            fn_80080430(x, y, u, v, p->w(), h);
        }
        fn_80080308();
    }
}

extern "C" void fn_800CE6C8(Spr* p, f32 x, f32 y, int col, int frame) {
    if (frame != 0) {
        fn_8007E154();
        if (p->hasTlut) {
            fn_8007E244(p->o4, p->o24, 0, 0x11);
        } else {
            fn_8007E174(p->o4, 0x11);
        }
        fn_8007E164();
        {
            f32 h, u, v;
            int cw = p->w();
            int m = (frame - 1) % p->cols();
            u = m * cw;
            int ch = p->h2();
            int n2 = (frame - 1) / p->cols();
            v = n2 * ch;
            fn_800800D4(1);
            h = p->h2();
            fn_80080430(x, y, u, v, p->w(), h);
        }
        fn_800804F4(col);
        fn_80080308();
    }
}

extern "C" void fn_800CE8D0(Spr* p, f32 x, f32 y, f32 z, int a, int t, int frame) {
    if (frame != 0) {
        fn_8007E154();
        fn_8007E4E4(x, y, z, 1.0f);
        fn_8007E174(p->o4, t);
        fn_8007E164();
        {
            f32 h, u, v;
            int cw = p->w();
            int m = (frame - 1) % p->cols();
            u = m * cw;
            int ch = p->h2();
            int n2 = (frame - 1) / p->cols();
            v = n2 * ch;
            fn_800800D4(1);
            h = p->h2();
            fn_80080430(0.0f, 0.0f, u, v, p->w(), h);
        }
        fn_800804D4(0xFF, 0xFF, 0xFF, a);
        fn_80080308();
    }
}

extern "C" int fn_800CEABC(u32 k) {
    switch (k) {
    case 0: return 9;
    case 4: return 0xD;
    case 1: return 0xA;
    case 2: return 0xB;
    case 3: return 0xC;
    case 6: return 0x10;
    case 7: return 0x12;
    case 8: return 0x11;
    case 9: return 0x13;
    case 10: return 0x14;
    case 11: return 0xF;
    case 5: return 0xE;
    case 13: return 0xC;
    default: return 0;
    }
}
