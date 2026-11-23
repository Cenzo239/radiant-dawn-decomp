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
#if TARGET_PC
FE10_PROTO void fn_8000FF74(p32arg);
FE10_PROTO void fn_800104DC(p32arg);
#else
void fn_8000FF74(int);
void fn_800104DC(int);
#endif
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
#if TARGET_PC
FE10_PROTO void fn_80014E24(void*, const char*, void*, p32arg);
#else
void fn_80014E24(void*, const char*, void*, int);
#endif
void* fn_800893E4(void*, void*, void*);
void fn_8017D838(void* p, void* arg);
void fn_8017D84C(void*);
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
char* strcpy(char*, const char*);
void fn_800CB278(int, int, int, const char*, ...);
void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
FE10_PROTO void* fn_80010BB0(ptr32<const void>);
#else
void* fn_80010BB0(void*);
#endif
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

void fn_8017B160(int x, int y, int w, int h, int tw, int th, void* tex, int fmt, u8 a, u8 add) {
    /*P*/
    int st;
    int coord;
    int map;
/*E*/
    u8 t[0x20];
    fn_80012268();
    fn_80021B2C(1);
    fn_80021C34(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    map = fn_80011EB4();
    fn_80305A40(t, tex, tw, th, fmt, 0, 0, 0);
    fn_80305C94(t, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    fn_80022254(t, map);
    coord = fn_80011F38();
    fn_80021F7C(coord, 1, 4, 0x3C);
    st = fn_80011E28();
    Konst(a);
    fn_80021FF0(st, 0xC);
    fn_80021CB4(st, coord, map, 4);
    fn_80021E20(st, 0xF, 0xC, 0xE, 8);
    fn_80021D18(st, 1, 0, 0, 1, 0);
    fn_80021E8C(st, 7, 7, 7, 6);
    fn_80021D9C(st, 0, 0, 0, 1, 0);
    st = fn_80011E28();
    fn_80021CB4(st, 0xFF, 0xFF, 4);
    fn_80021E20(st, 0xF, 0xF, 0xF, 0);
    fn_80021D18(st, 0, 0, 2, 1, 0);
    fn_80021E8C(st, 7, 7, 7, 6);
    fn_80021D9C(st, 0, 0, 0, 1, 0);
    st = fn_80011E28();
    fn_80021CB4(st, 0xFF, 0xFF, 4);
    fn_80021E20(st, 0xF, 0xF, 0xF, 0);
    fn_80021D18(st, 0, 0, 2, 1, 0);
    fn_80021E8C(st, 7, 7, 7, 6);
    fn_80021D9C(st, 0, 0, 0, 1, 0);
    if (add) {
        st = fn_80011E28();
        fn_80021CB4(st, 0xFF, 0xFF, 4);
        fn_80021E20(st, 0xF, 0xC, 0, 0xC);
        fn_80021D18(st, 1, 0, 0, 1, 0);
        fn_80021E8C(st, 7, 7, 7, 6);
        fn_80021D9C(st, 0, 0, 0, 1, 0);
    }
    fn_80021BF4(fn_80011EAC());
    fn_80021C34(fn_80011FBC());
    fn_80021BA4(1, 4, 5, 7);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xD, 1, 4, 0);
    fn_80021B68(0);
    fn_80304314(0x80, 0, 4);
    Pos(x, y, 0.0f);
    Tc(0.0f, 0.0f);
    Pos(x + w, y, 0.0f);
    Tc(1.0f, 0.0f);
    Pos(x + w, y + h, 0.0f);
    Tc(1.0f, 1.0f);
    Pos(x, y + h, 0.0f);
    Tc(0.0f, 1.0f);
}

void fn_8017C2F4(void* a) {
    if (fn_80007630(a, "wave") >= 0) {
        if (lbl_804CB8CA++ == 0) {
            fn_80020E7C(fn_8030585C(0x260, 0x1C0, 4, 0, 0));
            int size = fn_8030585C(0x20, 0x20, 3, 0, 0);
            lbl_804CB8CC = fn_80078D9C(size, "", 0);
            DCFlushRange(lbl_804CB8CC, size);
            fn_8017F464(lbl_804CB8CC, 0x80808080, size);
        }
    }
}

static inline const C4& White() {
    C4 c = {0xFF, 0xFF, 0xFF, 0xFF};
    return c;
}
void fn_8017CD80(void* a) {
    u8 t2[0x20];
    u8 t1[0x20];
    u8 m[0x18];
    if (fn_80007630(a, "wave") >= 0 && lbl_804CB8CA) {
        const C4& c = White();
        fn_8000FF74(0);
        void* tex = fn_80020E74();
        fn_8001F4D8(0, 0, 0x260, 0x1C0, 0x260, 0x1C0, tex, 4, 0);
        fn_80305A40(t2, tex, 0x260, 0x1C0, 4, 0, 0, 0);
        fn_80305C94(t2, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
        fn_80022254(t2, 0);
        fn_803031CC();
        fn_80302B80(9, 1);
        fn_80302B80(0xD, 1);
        fn_80303200(0, 9, 1, 4, 0);
        fn_80303200(0, 0xD, 1, 4, 0);
        fn_80021B2C(1);
        fn_80021A08(4, 0, 0, 0, 0, 0, 2);
        fn_80021958(4, c);
        fn_800218A8(4, c);
        fn_80021BF4(1);
        fn_80021C34(2);
        fn_80021F7C(0, 1, 4, 0x3C);
        fn_80021CB4(0, 0, 0, 4);
        fn_80021E20(0, 0xF, 0xF, 0xF, 8);
        fn_80021D18(0, 0, 0, 0, 1, 0);
        fn_80021E8C(0, 7, 7, 7, 5);
        fn_80021D9C(0, 0, 0, 0, 1, 0);
        fn_80305A40(t1, lbl_804CB8CC, 0x20, 0x20, 3, 1, 1, 0);
        fn_80305C94(t1, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
        fn_80022254(t1, 1);
        fn_80021C74(1);
        fn_80306B6C(0, 0, 1, 0, 1);
        fn_80021F7C(1, 1, 4, 0x3C);
        fn_8001E51C(m);
        fn_803067E0(1, m, -4);
        fn_80306A38(0, 1, 1);
        fn_80306934(0, 0, 0);
        fn_80021BA4(1, 4, 5, 7);
        fn_80021860(0, 3, 0);
        fn_80021B68(0);
        fn_80304314(0x98, 0, 4);
        Pos(0.0f, 0.0f, 0.0f);
        Tc(0.0f, 0.0f);
        Pos(608.0f, 0.0f, 0.0f);
        Tc(1.0f, 0.0f);
        Pos(0.0f, 448.0f, 0.0f);
        Tc(0.0f, 1.0f);
        Pos(608.0f, 448.0f, 0.0f);
        Tc(1.0f, 1.0f);
        fn_80306B24(0);
        fn_80021C74(0);
        fn_80011838(-1);
        fn_800104DC(0);
    }
}

void fn_8017D1DC(u8* o) {
    /*P*/
    int row;
    int k;
    int j;
    int i;
/*E*/
    F(o, int, 0x34) = -2;
    F(o, f32, 0x38) = 32.0f;
    F(o, f32, 0x3C) = 0.1f;
    int size = fn_8030585C(0x20, 0x20, 3, 0, 0);
    int total = size * 2;
    int n = total + 0x4000;
    void* buf = fn_80078D9C(n, "", 0);
    F(o, void*, 0x60) = buf;
    DCFlushRange(buf, n);
    u8* p = F(o, u8*, 0x60);
    F(o, u8*, 0x50) = p;
    F(o, u8*, 0x58) = p;
    F(o, u8*, 0x54) = p + size;
    F(o, u8*, 0x5C) = p + size;
    fn_8017F464(p, 0x80808080, total);
    u8* q = F(o, u8*, 0x60) + total;
    F(o, u8*, 0x40) = q;
    F(o, u8*, 0x44) = q + 0x1000;
    F(o, u8*, 0x48) = q + 0x2000;
    F(o, u8*, 0x4C) = q + 0x3000;
    fn_8017F464(q, 0, 0x4000);
    for (j = 0, row = 0; j < 0x20; j++, row += 0x20) {
        for (i = 0; i < 0x20; i++) {
            k = (i + row) * 4;
            *(f32*)(F(o, u8*, 0x40) + k) = ((f32)(fn_80089ED0() % 100) - 50.0f) / 200.0f;
            *(f32*)(F(o, u8*, 0x44) + k) = ((f32)(fn_80089ED0() % 100) - 50.0f) / 200.0f;
            *(f32*)(F(o, u8*, 0x48) + k) = ((f32)(fn_80089ED0() % 100) - 50.0f) / 200.0f;
            *(f32*)(F(o, u8*, 0x4C) + k) = ((f32)(fn_80089ED0() % 100) - 50.0f) / 200.0f;
        }
    }
    fn_80014E24(fn_80007F3C(F(o, void*, 0x30)), "waveB", fn_8017D84C, 2);
}

void fn_8017D84C(void* a) {
    f32 s[3][4];
    u8 m[0x18];
    u8 t[0x20];
    u8* o = (u8*)fn_800893E4(lbl_80387B88, fn_8017D838, a);
    if (o != 0) {
        f32 scale = F(o, f32, 0x38);
        int e = F(o, int, 0x34);
        void* tex = F(o, void*, 0x58);
        int coord = fn_80011F38();
        int map = fn_80011EB4();
        int mtx = fn_80011FC4();
        int ind = fn_80012048();
        fn_80305A40(t, tex, 0x20, 0x20, 3, 1, 1, 0);
        fn_80305C94(t, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
        fn_8001E51C(m);
        fn_803067E0(2, m, e);
        fn_8031292C(s, scale, scale, scale);
        fn_80307F10(s, mtx, 1);
        fn_80021F7C(coord, 1, 4, mtx);
        fn_80022254(t, map);
        fn_80306A38(ind, coord, map);
        fn_80306934(ind, 0, 0);
        fn_80306B6C(0, ind, 1, 0, 2);
    }
}

void fn_8017DAD4(const char* name, int a, void* parent, int b) {
    u8* p = (u8*)fn_80081194(lbl_80387BB0, parent);
    F(p, int, 0x78) = a;
    F(p, int, 0x74) = b;
    strcpy((char*)(p + 0x30), name);
}

void fn_8017DC24(f32 r, f32 g, f32 t, int lo, int hi) {
    fn_8007E154();
    fn_8007E4E4(r, g, 0.0f, 1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_800CB278(0x1E0, 0, 1, "%3d/%3d", (int)t, hi);
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    C4 c1 = {0x80, 0x80, 0x20, 0xFF};
    int x = 475.0f * (t - lo) / (hi - lo);
    fn_800800D4(3);
    fn_80080388(x, 10.0f, 5.0f, 10.0f);
    fn_80080578(0);
    fn_80080940(c1, c1, c1, c1);
    fn_80080308();
    C4 c2 = {0x20, 0x20, 0xFF, 0x80};
    fn_800800D4(3);
    fn_80080388(0.0f, 13.0f, 480.0f, 4.0f);
    fn_80080578(0);
    fn_80080940(c2, c2, c2, c2);
    fn_80080308();
}

void fn_8017E25C(u8* o) {
    u8* a = (u8*)fn_80010BB0(F(o, void*, 0x50));
    F(o, u8*, 0x64) = a;
    if (a != 0) {
        o[0x59] = a[2];
        o[0x5A] = a[3];
        o[0x5B] = a[4];
        o[0x5C] = a[5];
        a = (u8*)fn_80010DA4(a, 1);
        F(o, u8*, 0x6C) = a;
        if (a != 0) {
            o[0x5D] = a[4];
            o[0x5E] = a[5];
            o[0x5F] = a[6];
            o[0x60] = a[7];
        }
        a = (u8*)fn_80010E38(F(o, void*, 0x64), 5);
        F(o, u8*, 0x68) = a;
        if (a != 0) return;
    }
    fn_80081A90(o);
}

void fn_8017E9E0(u8* o) {
    u8* a = (u8*)fn_80010BB0((void*)F(o, s16, 0x30));
    a[2] = o[0x44];
    a[3] = o[0x45];
    a[4] = o[0x46];
    a[5] = o[0x47];
    a = (u8*)fn_80010DA4(a, 1);
    if (a != 0) {
        a[4] = o[0x54];
        a[5] = o[0x55];
        a[6] = o[0x56];
        a[7] = o[0x57];
    }
}
}
