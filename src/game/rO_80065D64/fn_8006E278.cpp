/* Window and menu sprite drawing built on fn_8006E098: frames, bars, unit panels, range stats. */
#include "game/rO_80065D64/types.h"
#pragma auto_inline off
struct Tex {
    u32 d[8];
    u16 w;
    u16 h;
};
extern "C" {
extern void* lbl_804CB58C;
extern void fn_80006A64(void*, Tex*, u16);
extern u16 fn_80305DF8(Tex*);
extern u16 fn_80305E0C(Tex*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(Tex*, int);
extern void fn_8007E720(f32);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_80080410(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_80080C24(p32arg);
#else
extern void fn_80080C24(int);
#endif
extern void fn_80080308(void);
extern Tex fn_8006E098(int x, int y, int w, int h, int u0, int v0, int u1, int v1, int color, u8 alpha, u16 id, int flags);

static inline void TexLoad(Tex* t, u16 id) {
    fn_80006A64(lbl_804CB58C, t, id);
    t->w = fn_80305DF8(t);
    t->h = fn_80305E0C(t);
}

static inline Tex Spr(int x, int y, int w, int h, int color, u8 alpha, u16 id, int flags) {
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    return fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, color, alpha, id, flags);
}

static inline Tex Spr3(int x, int y, int color, u8 alpha, u16 id, int flags) {
    Tex t0;
    TexLoad(&t0, id);
    int w = t0.w;
    int h = t0.h;
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    return fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, color, alpha, id, flags);
}
void fn_80072488(
#if TARGET_PC
int x, int y, int a, int b, int f, char* s
#else
int x, int y, int a, int b, int f, int s
#endif
) {
    Tex t0;
    TexLoad(&t0, 3);
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 500 - b, 1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E7DC(a);
    fn_8007E164();
    int flip = 0;
    int dx = 0x50;
    if (f) {
        flip = 1;
        dx = 0x50;
    }
    fn_800800D4(5);
    fn_80080330(x + dx, y + 6);
    fn_800804D4(0, 0, 0, 0xFF);
    fn_80080C24(s);
    fn_80080308();
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
    Spr(x, y, -1, -1, 1, 0xFF, 3, flip);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
}

void fn_80072EE0(int x, int y, int w) {
    Tex t;
    TexLoad(&t, 0x28);
    int mid = w - t.w;
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(x, y, 56.0f, 48.0f);
    fn_80080410(0.0f, 0.0f, 56.0f, 48.0f);
    fn_80080308();
    fn_800800D4(1);
    fn_80080388(x + 0x38, y, mid, 48.0f);
    fn_80080410(56.0f, 0.0f, 56.0f, 48.0f);
    fn_80080308();
    fn_800800D4(1);
    fn_80080388(x + mid + 0x38, y, t.w - 0x38, 48.0f);
    fn_80080410(56.0f, 0.0f, t.w, 48.0f);
    fn_80080308();
}

#if TARGET_PC
extern FE10_PROTO u8 fn_801076D0(p32arg);
#else
extern u8 fn_801076D0(int);
#endif
#pragma use_lmw_stmw on
#pragma use_lmw_stmw off

extern void fn_80071C30(int, int);
#if TARGET_PC
extern FE10_PROTO char * fn_801246A4(void*);
extern FE10_PROTO void* fn_800C6210(p32arg, int);
#else
extern int fn_801246A4(void*);
extern void* fn_800C6210(int, int);
#endif
#if TARGET_PC
extern FE10_PROTO void* fn_8007E4C4(p32arg);
#else
extern void* fn_8007E4C4(int);
#endif
extern int fn_8028C1A0(f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, int);
#else
extern void fn_8007E74C(void (*)(int, int), int);
#endif
extern void fn_800C4DDC(int, int, int, void*);
extern void fn_8007E7B4(void);
#if TARGET_PC
extern FE10_PROTO char* fn_80118C44(p32arg);
extern FE10_PROTO char* fn_80118F00(p32arg);
#else
extern char* fn_80118C44(int);
extern char* fn_80118F00(int);
#endif
extern u8 fn_80126B0C(u8*);
extern char* strcpy(char*, const char*);
extern void fn_800C429C(void*);
void fn_80071C44(u8*, int, int, int);
extern int fn_80127A90(u8*);
extern int fn_8011B8A4(u8*);
extern int fn_80290DDC(char*, const char*, ...);
extern int fn_800CA3DC(f32, const char*, int);
extern void fn_801C6DA0(f32, f32, int, const char*);
extern char lbl_803622BC[];
void fn_800722B8(u8* u, int x, int y) {
    char s[24];
    fn_80071C44(u, x, y, 0x2F);
    int col;
    int cur = fn_80127A90(u);
    int max = fn_8011B8A4(u + 300);
    col = 8;
    if (cur < max) {
        col = 0x23;
    }
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_8007E154();
    fn_8007E720(-3.0f);
    fn_8007E164();
    const char* fmt = lbl_803622BC;
    fn_80290DDC(s, fmt + 0x4D, max);
        f32 w = fn_800CA3DC(1.0f, s, -1);
    fn_801C6DA0((x + 0x46) - (w * 0.5f), y + 0x48, col, s);
    fn_801C6DA0(x + 0x60, y + 0x48, 8, fmt + 0x55);
    fn_80290DDC(s, fmt + 0x4D, cur);
        f32 w2 = fn_800CA3DC(1.0f, s, -1);
    fn_801C6DA0((x + 0x7E) - (w2 * 0.5f), y + 0x48, 0xC, s);
    fn_8007E154();
    fn_8007E720(3.0f);
    fn_8007E164();
}

void fn_8006E278(int x, int y, int h) {
    Tex t;
    TexLoad(&t, 6);
    int tw = t.w;
    Spr(x + 3, y + 0x14, -1, h - 0x28, 1, 0xD2, 6, 0);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    t = Spr(x, y, -1, -1, 1, 0xFF, 4, 0);
    Spr(x, y + h - t.h, -1, -1, 1, 0xFF, 4, 2);
    Spr(x, y + 0x18, -1, h - 0x30, 1, 0xFF, 5, 0);
    Spr(x + tw - 5, y + 0x18, -1, h - 0x30, 1, 0xFF, 5, 1);
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
}

#pragma use_lmw_stmw on
void fn_80074EB4(int x, int y, int w, u8 a) {
    if (w <= 0x10) {
        w = 0x10;
    }
    int m = w - 5;
    Spr3(x, y, 1, a, 0x29, 0);
    Spr(x + 3, y, m, 8, 1, a, 0x2A, 0);
    Spr3(x + m + 3, y, 1, a, 0x2B, 0);
}
#pragma use_lmw_stmw off

extern void fn_801BCA94(int);
#if TARGET_PC
extern FE10_PROTO int* fn_80030CBC(p32arg);
extern FE10_PROTO int fn_8012BA20(p32arg, p32arg);
#else
extern int* fn_80030CBC(int);
extern int fn_8012BA20(int, int);
#endif
extern int fn_80291188(const char*, const char*);
extern void fn_800CB3A8(f32, f32, s16, s16, int, int, int, const char*, ...);
void fn_80073374(int u, const char* name, int cur, int max, u32 f, u32 g, f32 x, f32 y) {
    fn_801BCA94(u);
    if (g == 1) {
        if (f != 1) {
            int ok = 0;
            if (*fn_80030CBC(u) != 0 && fn_8012BA20(u, *fn_80030CBC(u)) != 0) {
                ok = 1;
            }
            if (ok) {
                goto L;
            }
        }
        fn_800CB3A8(1.0f, 0.0f, 36.0f + x, y, 2, 0, 0, lbl_803622BC + 0x50);
        return;
    }
L:
    if (fn_80291188(name, lbl_803622BC + 0x7C) == 0) {
        if (cur == max) {
            fn_800CB3A8(1.0f, 0.0f, 40.0f + x, y, 2, 0, 0, lbl_803622BC + 0x83, cur);
        } else {
            fn_800CB3A8(1.0f, 0.0f, 28.0f + x, y, 2, 0, 0, lbl_803622BC + 0x83, cur);
            fn_800CB3A8(1.0f, 0.0f, 52.0f + x, y, 2, 0, 0, lbl_803622BC + 0x87);
            if (max >= 10) {
                fn_800CB3A8(1.0f, 0.0f, 59.0f + x, y, 2, 0, 0, lbl_803622BC + 0x83, max);
            } else {
                fn_800CB3A8(1.0f, 0.0f, 52.0f + x, y, 2, 0, 0, lbl_803622BC + 0x83, max);
            }
        }
    } else {
        fn_800CB3A8(1.0f, 0.0f, 35.0f + x, y, 2, 0, 0, lbl_803622BC + 0x89, cur);
    }
}

#if TARGET_PC
extern FE10_PROTO char* fn_800D0864(p32arg);
#else
extern char* fn_800D0864(int);
#endif
extern void fn_801BCA5C(f32);
#pragma use_lmw_stmw off
void fn_80074718(int x, int y, int mid) {
    char* s = fn_800D0864(mid);
    u16 w = fn_800CA3DC(1.0f, s, -1);
    u16 hw = (u16)(w + 0xB0) >> 1;
    if (x + hw > 0x260) {
        x = x - (x + hw - 0x260);
    } else if (x - hw < 0) {
        x = hw;
    }
    int left = x - hw;
    Spr3(left, y, 1, 0xFF, 0x20, 0);
    left += 0x58;
    Spr(left, y, w, 0x30, 1, 0xFF, 0x21, 0);
    left += w;
    Spr3(left, y, 1, 0xFF, 0x22, 0);
    fn_801BCA5C(-1.0f);
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_800800D4(5);
    fn_80080330(x - (w >> 1), y + 10);
    fn_800804D4(0xFE, 0xF2, 0xA1, 0xFF);
    fn_80080C24(mid);
    fn_80080308();
    fn_801BCA5C(1.0f);
}

#pragma use_lmw_stmw on
void fn_80074A64(int x, int y, u8 a, int k) {
    switch (k) {
    case 0:
        Spr3(x, y, 1, a, 0x26, 1);
        Spr3(x + 0x130, y, 1, a, 0x26, 0);
        break;
    case 1:
        Spr3(x, y, 1, a, 0x27, 1);
        Spr3(x + 0x130, y, 1, a, 0x27, 0);
        break;
    case 2:
        Spr3(x, y, 1, a, 0x1A, 0);
        break;
    }
}
#pragma use_lmw_stmw off

void fn_800718F0(u8* u, int x, int y, int f) {
    /*P*/
    char* s;
    int w;
    int h;
    int id;
/*E*/
    id = 1;
    Spr3(x, y, 1, 0xFF, 1, 0);
    Tex t;
    TexLoad(&t, 1);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    s = fn_80118C44(*(int*)(u + 0xEC));
    w = fn_800CA3DC(1.0f, s, -1);
    h = 0;
    fn_801C6DA0((t.w - w) / 2, y + 4, 8, s);
    if (f) {
        int k = fn_801076D0((int)u);
        if (k == 2) {
            goto end;
        }
        switch (k) {
        case 0:
            id = 0x30;
            h = 0x18;
            w = 0x18;
            break;
        case 1:
            id = 0x31;
            h = 0x10;
            w = 0x10;
            break;
        case 3:
            id = 0x32;
            h = 0x10;
            w = 0x10;
            break;
        case 4:
            id = 0x33;
            h = 0x18;
            w = 0x18;
            break;
        case 2:
        default:
            break;
        }
        Spr3(x + t.w - w - 0xC, y + ((0x22 - h) >> 1), 1, 0xFF, id, 0);
    }
end:
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
}

class DB { u8 pad[0x44]; };
class Drawer : public DB {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18(int, int, int);
};
extern u8 lbl_803E7290[];
static inline int Icon(u16* p, u32 m, f32 x, f32 y, int id) {
    if (*p & m) {
        ((Drawer*)lbl_803E7290)->v18(x, y, id);
        return 1;
    }
    return 0;
}
void fn_80073688(u16* p, f32 x, f32 y) {
    f32 xx = 45.0f + x;
    if (Icon(p, 0x20, xx, y, 0x34)) xx += 28.0f;
    f32 d = xx;
    if (Icon(p, 0x10, xx, y, 0x35)) d += 28.0f;
    if (Icon(p, 4, xx, y, 0x36)) xx += 28.0f;
    if (Icon(p, 8, xx, y, 0x37)) xx += 28.0f;
    if (Icon(p, 0x40, xx, y, 0x39)) xx += 28.0f;
    if (Icon(p, 0x100, xx, y, 0x3A)) xx += 28.0f;
    if (Icon(p, 2, xx, y, 0x38)) xx += 28.0f;
    if (Icon(p, 0x80, xx, y, 0x3B)) xx = xx;
}

void fn_80071C44(u8* u, int x, int y, int id) {
    char s[24];
    int a;
    int b;
    void* o = fn_800C6210(fn_801246A4(u), 0);
    a = *(int*)(u + 0xF0);
    b = *(int*)(u + 0xEC);
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(x, y - 10, t.w, t.h);
    fn_80080308();
    void* m = fn_8007E4C4(0);
    int c = fn_8028C1A0(188.0f + (*(f32*)((u8*)m + 0xC) + x));
    fn_8007E154();
    fn_8007E74C(fn_80071C30, c);
    fn_8007E164();
    fn_8007E154();
    fn_8007E720(-2.0f);
    fn_8007E164();
    if (o) {
        fn_800C4DDC(x + 0xE4, y + 0x60, 0xFF, o);
    }
    fn_8007E154();
    fn_8007E720(2.0f);
    fn_8007E164();
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    Spr3(x - 5, y - 0xF, 1, 0xFF, 2, 0);
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_8007E154();
    fn_8007E720(-2.0f);
    fn_8007E164();
    f32 w0 = fn_800CA3DC(1.0f, fn_80118C44(b), -1);
    fn_801C6DA0((90.0f + x) - (w0 * 0.5f), y - 0xB, 8, fn_80118C44(b));
    f32 w1 = fn_800CA3DC(1.0f, fn_80118F00(a), -1);
    fn_801C6DA0((92.0f + x) - (w1 * 0.5f), y + 0xF, 8, fn_80118F00(a));
    fn_80290DDC(s, lbl_803622BC + 0x4D, *(s8*)(u + 0xFE));
    f32 w = fn_800CA3DC(1.0f, s, -1);
    fn_801C6DA0((x + 0x46) - (w * 0.5f), y + 0x2C, 8, s);
    if (fn_80126B0C(u) == 0xFF) {
        strcpy(s, lbl_803622BC + 0x50);
    } else {
        fn_80290DDC(s, lbl_803622BC + 0x4D, fn_80126B0C(u));
    }
    f32 w3 = fn_800CA3DC(1.0f, s, -1);
    fn_801C6DA0(x + 0x88, y + 0x2C, 8, s);
    fn_8007E154();
    fn_8007E720(3.0f);
    fn_8007E164();
    if (o) {
        fn_800C429C(o);
    }
}

#pragma use_lmw_stmw on
void fn_80075124(int x, int y, int w, int h) {
    if (w <= 0x10) {
        w = 0x10;
    }
    if (h <= 0x10) {
        h = 0x10;
    }
    int mw = w - 0x10;
    int mh = h - 0x10;
    Spr3(x, y, 1, 0xFF, 0x2C, 0);
    Spr(x + 8, y, mw, 8, 1, 0xFF, 0x2D, 0);
    Spr3(x + mw + 8, y, 1, 0xFF, 0x2C, 1);
    Spr(x, y + 8, 8, mh, 1, 0xFF, 0x2E, 0);
    Spr(x + mw + 8, y + 8, 8, mh, 1, 0xFF, 0x2E, 1);
    Spr3(x, y + mh + 8, 1, 0xFF, 0x2C, 2);
    Spr(x + 8, y + mh + 8, mw, 8, 1, 0xFF, 0x2D, 2);
    Spr3(x + mw + 8, y + mh + 8, 1, 0xFF, 0x2C, 3);
}
#pragma use_lmw_stmw off

void fn_80070C64(f32 x, f32 y, f32 w, f32 h) {
    /*P*/
    int ix3;
    int ix;
    int iy;
    int ix2;
    int iy2;
    int iy3;
    int mh;
    int mw;
    int mw2;
/*E*/
    ix = x;
    iy = y;
    mw = (w - 16.0f) - 16.0f;
    if (mw < 0) {
        mw = 0;
    }
    Spr3(ix, iy, 1, 0xFF, 0x14, 0);
    ix += 0x10;
    Spr(ix, iy, mw, 8, 1, 0xFF, 0x17, 0);
    ix += mw;
    Spr3(ix, iy, 1, 0xFF, 0x14, 1);
    ix2 = x;
    iy2 = 8.0f + y;
    mh = (h - 8.0f) - 8.0f;
    if (mh < 0) {
        mh = 0;
    }
    Spr(ix2, iy2, 8, mh, 1, 0xFF, 0x16, 4);
    Spr(((f32)ix2 + w) - 8.0f, iy2, 8, mh, 1, 0xFF, 0x16, 8);
    ix3 = x;
    iy3 = (8.0f + y) + mh;
    mw2 = (w - 8.0f) - 8.0f;
    Spr(ix3, iy3, 8, 8, 1, 0xFF, 0x3B, 6);
    ix3 += 8;
    Spr(ix3, iy3, mw2, 8, 1, 0xFF, 0x16, 2);
    ix3 += mw2;
    Spr(ix3, iy3, 8, 8, 1, 0xFF, 0x3B, 4);
}

extern s16 fn_801237EC(u8*);
void fn_800720F4(u8* u, int x, int y) {
    char s[24];
    fn_80071C44(u, x, y, 0);
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_8007E154();
    fn_8007E720(-3.0f);
    fn_8007E164();
    const char* fmt = lbl_803622BC;
    fn_80290DDC(s, fmt + 0x4D, *(s8*)(u + 0x114));
    f32 w = fn_800CA3DC(1.0f, s, -1);
    fn_801C6DA0((x + 0x46) - (w * 0.5f), y + 0x48, 8, s);
    fn_801C6DA0(x + 0x60, y + 0x48, 8, fmt + 0x55);
    fn_80290DDC(s, fmt + 0x4D, fn_801237EC(u));
    f32 w2 = fn_800CA3DC(1.0f, s, -1);
    fn_801C6DA0((x + 0x7E) - (w2 * 0.5f), y + 0x48, 0xC, s);
    fn_8007E154();
    fn_8007E720(3.0f);
    fn_8007E164();
}

extern s64 OSGetTime(void);
extern s64 fn_8028C418(s64, s64);
extern s64 fn_8028C634(s64, s64);
extern f32 fn_8028C764(s64);
extern double fn_80295940(double);
extern double fn_80295534(double);
extern int fn_8017F990(int, int);
void fn_8006F1B4(int x, int y, int f) {
    Spr3(x, y, 1, 0xFF, 7, 0);
    if (f) {
        Tex t;
        TexLoad(&t, 8);
        int tw = t.w;
        f32 ms = fn_8028C764(fn_8028C634(fn_8028C418(OSGetTime(), (*(u32*)0x800000F8 >> 2) / 1000), 2000));
        f32 c = fn_80295940(6.2831855f * (ms / 2000.0f));
        int a = 0.5f * (255.9f * (1.0f + c));
        Spr3(x, y, 1, a, 8, 0);
        fn_8007E154();
        fn_8007E720(-0.5f);
        fn_8007E164();
        f32 s = fn_80295534(6.2831855f * ((f32)fn_8017F990(0, 500) / 500.0f));
        f32 d = 4.0f * (1.0f + s);
        Spr3((x - 0xE) - d, y, 1, 0xFF, 0xB, 0);
        Spr3(d + (x + tw - 0x12), y + 1, 1, 0xFF, 0xC, 0);
        f32 dead = x;
        fn_8007E154();
        fn_8007E720(-0.5f);
        fn_8007E164();
    }
}
void fn_8006F6A4(int x, int y, int f) {
    Spr3(x, y, 1, 0xFF, 9, 0);
    if (f) {
        Tex t;
        TexLoad(&t, 0xA);
        int tw = t.w;
        f32 ms = fn_8028C764(fn_8028C634(fn_8028C418(OSGetTime(), (*(u32*)0x800000F8 >> 2) / 1000), 2000));
        f32 c = fn_80295940(6.2831855f * (ms / 2000.0f));
        int a = 0.5f * (255.9f * (1.0f + c));
        Spr3(x, y, 1, a, 0xA, 0);
        fn_8007E154();
        fn_8007E720(-0.5f);
        fn_8007E164();
        f32 s = fn_80295534(6.2831855f * ((f32)fn_8017F990(0, 500) / 500.0f));
        f32 d = 4.0f * (1.0f + s);
        Spr3((x - 0xE) - d, y, 1, 0xFF, 0xB, 0);
        Spr3(d + (x + tw - 0x12), y + 1, 1, 0xFF, 0xC, 0);
        f32 dead = x;
        fn_8007E154();
        fn_8007E720(-0.5f);
        fn_8007E164();
    }
}

extern int fn_801D09F0(void);
extern void* lbl_804CB580;
extern u8 lbl_803C8E80[];
extern int* fn_80030CF4(u8*);
extern u32* fn_801116B8(int*);
#if TARGET_PC
extern FE10_PROTO u8 fn_801107C0(p32arg, u8*);
#else
extern u8 fn_801107C0(int, u8*);
#endif
#if TARGET_PC
extern FE10_PROTO u8 fn_801107A0(p32arg, ...);
#else
extern u8 fn_801107A0(int, u8*);
#endif
static inline void Spr3Z(int x, int y, int color, u8 alpha, u16 id, int& w, int& z) {
    Tex t0;
    TexLoad(&t0, id);
    w = t0.w;
    int h = t0.h;
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, color, alpha, id, z = 0);
}
void fn_80073374(int u, const char* name, int cur, int max, u32 f, u32 g, f32 x, f32 y);
void fn_80073688(u16* p, f32 x, f32 y);
void fn_8007309C(int k, f32 x, f32 y) {
    /*P*/
    int rng;
    int sw_;
    u8* b;
    int* w;
    const char* str;
/*E*/
    b = lbl_803C8E80;
    if (b) {
        w = fn_80030CF4(b);
        if (w && (fn_801116B8(w)[1] & 1)) {
            Spr3Z(x, y, 1, 0xFF, 0x1B, sw_, rng);
            fn_801BCA5C(-1.0f);
            str = lbl_803622BC;
            fn_80073374((int)b, str + 0x57, *(s16*)(b + 0x448), 0, k, 1, 19.0f + x, 19.0f + y);
            fn_80073374((int)b, str + 0x5E, *(s16*)(b + 0x44E), 0, k, 1, 99.0f + x, 19.0f + y);
            fn_80073374((int)b, str + 0x65, *(s16*)(b + 0x450), 0, k, 0, 178.0f + x, 19.0f + y);
            fn_80073374((int)b, str + 0x6C, *(s16*)(b + 0x454), 0, k, 1, 19.0f + x, 50.0f + y);
            fn_80073374((int)b, str + 0x74, *(s16*)(b + 0x456), 0, k, 0, 99.0f + x, 50.0f + y);
            if (*w) {
                rng = fn_801107C0(*w, b);
            }
            fn_80073374((int)b, lbl_803622BC + 0x7C, *w ? fn_801107A0(*w, b) : 0, rng, k, 1, 178.0f + x, 50.0f + y);
            fn_80073688((u16*)(b + 0x45E), 28.0f + x, 82.0f + y);
            fn_801BCA5C(1.0f);
        }
    }
}

void fn_8006FED4(f32 x, f32 y, f32 w, f32 h) {
    /*P*/
    int ix3;
    int iy;
    int ix;
    int ix2;
    int iy2;
    int iy3;
    int mh;
    int mw;
/*E*/
    ix = x;
    iy = y;
    mw = (w - 16.0f) - 16.0f;
    if (mw < 0) {
        mw = 0;
    }
    Spr3(ix, iy, 1, 0xFF, 0x14, 0);
    ix += 0x10;
    Spr(ix, iy, mw, 8, 1, 0xFF, 0x17, 0);
    ix += mw;
    Spr3(ix, iy, 1, 0xFF, 0x14, 1);
    ix2 = x;
    iy2 = 8.0f + y;
    mh = (h - 8.0f) - 8.0f;
    if (mh < 0) {
        mh = 0;
    }
    Spr(ix2, iy2, 8, mh, 1, 0xFF, 0x16, 4);
    Spr(((f32)ix2 + w) - 8.0f, iy2, 8, mh, 1, 0xFF, 0x16, 8);
    ix3 = x;
    iy3 = (8.0f + y) + mh;
    Spr3(ix3, iy3, 1, 0xFF, 0x14, 2);
    ix3 += 0x10;
    Spr(ix3, iy3, mw, 8, 1, 0xFF, 0x17, 2);
    ix3 += mw;
    Spr3(ix3, iy3, 1, 0xFF, 0x14, 3);
}

void fn_80070688(f32 x, f32 y, f32 w, f32 h) {
    /*P*/
    int ix3;
    int iy;
    int ix2;
    int iy2;
    int mw;
    int mh;
    int iy3;
    int ix;
/*E*/
    ix = x;
    iy = y;
    mw = (w - 8.0f) - 8.0f;
    if (mw < 0) {
        mw = 0;
    }
    Spr(ix, iy, 8, 0x10, 1, 0xFF, 0x14, 5);
    ix += 8;
    Spr(ix, iy, mw, 8, 1, 0xFF, 0x16, 0);
    ix += mw;
    Spr(ix, iy, 8, 0x10, 1, 0xFF, 0x14, 8);
    ix2 = x;
    iy2 = 16.0f + y;
    mh = (h - 16.0f) - 16.0f;
    if (mh < 0) {
        mh = 0;
    }
    Spr(ix2, iy2, 8, mh, 1, 0xFF, 0x17, 4);
    Spr(((f32)ix2 + w) - 8.0f, iy2, 8, mh, 1, 0xFF, 0x17, 8);
    ix3 = x;
    iy3 = (16.0f + y) + mh;
    Spr(ix3, iy3, 8, 0x10, 1, 0xFF, 0x14, 4);
    ix3 += 8;
    Spr(ix3, iy3 + 8, mw, 8, 1, 0xFF, 0x16, 2);
    ix3 += mw;
    Spr(ix3, iy3, 8, 0x10, 1, 0xFF, 0x14, 6);
}
}
