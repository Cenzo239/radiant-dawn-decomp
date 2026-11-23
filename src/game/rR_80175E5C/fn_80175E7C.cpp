/* Fades, wallpaper and text panel helpers (0x80175E7C..0x8017F3F0). */
#include "game/rR_80175E5C/types.h"
#define F(p, t, o) (*(t*)((u8*)(p) + (o)))

class Pad {
public:
    virtual int v08(int);
    virtual int v0C(int);
    virtual int v10();
    virtual int v14();
    virtual int v18();
    virtual int v1C();
    virtual int v20();
    virtual int v24();
    virtual int v28();
    virtual int v2C();
    virtual int v30();
    virtual int v34();
    virtual int v38();
    virtual int v3C();
    virtual int v40();
    virtual int v44();
    virtual int v48();
};

extern "C" {
extern Pad* lbl_804CB5B8;
extern u8 lbl_803879F8[], lbl_80387A10[], lbl_80387A40[], lbl_80387AC8[], lbl_80387C60[];
extern char lbl_8036B4C8[];
void* fn_80081050(void*, void*);
void* fn_80081194(void*, void*);
void fn_80083B78(void*);
void fn_80083DC4(void*, int);
#if TARGET_PC
FE10_PROTO void fn_800893E4(void*, void*, p32arg);
#else
void fn_800893E4(void*, void*, int);
#endif
f32 fn_8007E048();
int fn_800CA3DC(const char*, int, f32);
void fn_80080330(f32, f32);
void fn_80080C24(const char*);
f64 fn_80295CF0(f64);
#if TARGET_PC
FE10_PROTO void fn_8017735C(void* p, ptr32<const void>);
#else
void fn_8017735C(void* p, void* arg);
#endif
void* fn_80078CCC(int, const char*, int);
void fn_8001AAB4(void*, int);
#if TARGET_PC
FE10_PROTO void fn_80020E7C(ptr32<const void>);
#else
void fn_80020E7C(void*, int);
#endif
f32 fn_8001EBC8(int, f32, f32, f32, f32);
void fn_80290DDC(char*, const char*, ...);
int fn_80007630(void*, const char*);
void fn_8017794C(void*, void*, const char*, const char*);
void* fn_8001D3EC(const char*, int);
void fn_8001D424(void*);
void fn_80081A90(void*);
void fn_80078E24(void*);
extern u8 lbl_804CA7C0, lbl_804CA7C1, lbl_804CA7C2, lbl_804CA7C3;



void fn_80176EA8(int x, int y, int align, const char* s) {
    int w = fn_800CA3DC(s, -1, fn_8007E048());
    switch (align) {
    case 0:
        x -= w;
        break;
    case 2:
        x -= w / 2;
        break;
    case 1:
        break;
    }
    fn_80080330(x, y);
    fn_80080C24(s);
}

void
#if TARGET_PC
*
#endif
fn_80177284(int v, void* parent) {
#if TARGET_PC
    void* p = fn_80081050(lbl_803879F8, parent);
    F(p, int, 0x30) = v;
    return p;
#else
    F(fn_80081050(lbl_803879F8, parent), int, 0x30) = v;
#endif
}

void
#if TARGET_PC
*
#endif
fn_801772EC(int a, int b, int c, void* parent) {
    u8* p = (u8*)fn_80081194(lbl_80387A10, parent);
    F(p, int, 0x30) = a;
    F(p, int, 0x34) = b;
    F(p, int, 0x38) = c;
#if TARGET_PC
    return p;
#endif
}

void fn_80177390(int a) {
    fn_800893E4(lbl_80387A40, fn_8017735C, a);
}



void fn_80177468(u8* p) {
    if (lbl_804CB5B8->v48() & 0xFFF0) {
        fn_80083B78(p);
        return;
    }
    F(p, s16, 0x30) += 1;
    if (F(p, s16, 0x30) == F(p, s16, 0x32)) fn_80083B78(p);
}

void fn_80177FCC(
#if TARGET_PC
u8* p, Color c
#else
u8* p, const Color& c
#endif
) {
    u8 r = c.r;
    u8 g = c.g;
    u8 b = c.b;
    u8 a = c.a;
    p[0x38] = r;
    p[0x39] = g;
    p[0x3A] = b;
    p[0x3B] = a;
    p[0x3C] = r;
    p[0x3D] = g;
    p[0x3E] = b;
    p[0x3F] = a;
    const volatile u8* q = &c.r;
    if (q[0] < 0x80 && q[1] < 0x80 && q[2] < 0x80) {
        p[0x50] = (p[0x50] & 0xFE) | 2;
    } else {
        p[0x50] = (p[0x50] & ~2) | 1;
    }
}


#pragma use_lmw_stmw on
void* fn_80179040(void* a, int b, int c, void* parent) {
    char buf0[0x10];
    char buf1[0x10];
    fn_80290DDC(buf0, lbl_8036B4C8 + 0x2A, b, c);
    fn_80290DDC(buf1, lbl_8036B4C8 + 0x2A, b, c + 1);
    if (fn_80007630(a, buf0) >= 0) fn_80007630(a, buf1);
    void* p = fn_80081050(lbl_80387AC8, parent);
    fn_8017794C(p, a, buf0, buf1);
    return p;
}
#pragma use_lmw_stmw off

static inline void SetCol(u8* p, const Color& c) {
    p[0x1B] = c.r;
    p[0x1C] = c.g;
    p[0x1D] = c.b;
    p[0x1E] = c.a;
}


static inline void FreeTex(u8* t) {
    if (t != NULL) {
        if (F(t, int, 0x34) != 0) fn_8001D424(F(t, void*, 0x34));
        if (F(t, int, 0x30) != 0) {
            fn_80081A90(F(t, void*, 0x30));
            F(t, int, 0x30) = 0;
        }
        fn_80078E24(t);
    }
}

u8* fn_80179710(u8* p, int del) {
    if (p != NULL) {
        F(p, void*, 0x28) = lbl_80387C60;
        fn_8001D424(F(p, void*, 0));
        if (F(p, u8*, 0x20) != NULL) {
            FreeTex(F(p, u8*, 0x20));
            F(p, void*, 0x20) = NULL;
        }
        if (F(p, u8*, 0x24) != NULL) {
            FreeTex(F(p, u8*, 0x24));
            F(p, void*, 0x24) = NULL;
        }
        if (del > 0) fn_80078E24(p);
    }
    return p;
}

void fn_80179864(u8* p, s16 v) {
    if (v < 0) v = F(p, s16, 0x12);
    if (v > F(p, s16, 0x12)) v = F(p, s16, 0x12);
    F(p, s16, 0x14) = v;
}

void fn_80179888(u8* p, int v) {
    int m = F(p, s16, 0x12) - F(p, s16, 0x14);
    if (v > m) v = m;
    F(p, s16, 0x16) = v;
}

void fn_80179A58(u8* p, const u8* c) {
    p[0x1B] = c[0];
    p[0x1C] = c[1];
    p[0x1D] = c[2];
    p[0x1E] = c[3];
}

void fn_800E4AD4(void*, f32);
void fn_800E48AC(void*, f32, f32, f32, f32);
void fn_800E4A40(void*, f32);
void fn_800E515C(void*);
void fn_800E56B8(void*);
#if TARGET_PC
FE10_PROTO void* fn_800E4060(const char*, p32arg);
#else
void* fn_800E4060(const char*, int);
#endif
extern u8 lbl_804CE4B8[4];
extern u8 lbl_804CE4C0[8];
extern char lbl_804CA440[8];



extern u8 lbl_803879E8[], lbl_80387B68[], lbl_80387BE8[];
extern u8 lbl_804CB8CA;
extern void* lbl_804CB8CC;
void* fn_8008580C(void*, void*);
void fn_80020EEC();
void fn_80079978(void*);
void* fn_80010960();
void* fn_80010B8C(void*, const Color&);
void fn_80010AE4(void*);
void* fn_80010BB0(int);
void* fn_80010DA4(void*, int);
#if TARGET_PC
FE10_PROTO struct GLight * fn_80010E38(void*, int);
#else
int fn_80010E38(void*, int);
#endif
void fn_80010F94(void* p, void* arg);
int strlen(const char*);
struct Elem { u8 b; };
void fn_800250B0(void*, int, int, const char*, const char*, Elem);

void fn_801772BC(u8* p) {
    int v = F(p, int, 0x38)--;
    if (v - 1 > 0) return;
    fn_80083DC4(p, 0x63);
}

void fn_801773A8(u8* p) {
    if (F(p, int, 0x30) != 0) return;
    fn_80083B78(p);
}

void* fn_80177260(void* parent) { return fn_80081050(lbl_803879E8, parent); }
void* fn_8017C288(void* parent) { return fn_8008580C(lbl_80387B68, parent); }
void* fn_8017E460(void* parent) { return fn_8008580C(lbl_80387BE8, parent); }

void fn_8017AFF4(void** p) {
    if (p != NULL && p != NULL) {
        if (*p != NULL) fn_80079978(*p);
        fn_80078E24(p);
    }
}

void fn_8017C3B0(void* a) {
    if (fn_80007630(a, lbl_8036B4C8 + 0xC3) >= 0) {
        if ((s8)--lbl_804CB8CA == 0) {
            fn_80020EEC();
            fn_80078E24(lbl_804CB8CC);
            lbl_804CB8CC = 0;
        }
    }
}

void fn_8017F13C(u8* p) {
    Color c;
    void* o = fn_80010960();
    c.r = p[0x42];
    c.g = p[0x43];
    c.b = p[0x44];
    c.a = p[0x45];
    fn_80010AE4(fn_80010B8C(o, c));
}


}
