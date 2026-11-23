/* Game commands and option setters: 0x800A2ACC..0x800A3D14. */
#include "game/rD_8008E3B4/types.h"

class Item3 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5C();
    virtual void v60(int k);
    virtual void v64(); virtual void v68();
    virtual void v6C(int k);
};

struct DataBase3 { int d0; };

class List3 : public DataBase3 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40();
    virtual Item3* at(int i);   /* 0x44 */
    u16 s8_;   /* 0x08 */
    u16 sA;    /* 0x0A */
    u16 sC;    /* 0x0C */
    u16 sE;    /* 0x0E */
    u8 pad10[8];
    f32 f18;   /* 0x18 */
    u16 s1C;   /* 0x1C */
    u8 pad1E[6];
    u8 b24;    /* 0x24 */
};

extern "C" {

typedef struct FlagBits0 {
    u32 f0 : 2;
    u32 f2 : 1;
    u32 f3 : 2;
    u32 f5 : 1;
    u32 f6 : 1;
    u32 f7 : 1;
    u32 f8 : 2;
    u32 f10 : 2;
    u32 f12 : 2;
    u32 f14 : 1;
    u32 f15 : 1;
    u32 f16 : 2;
    u32 f18 : 1;
    u32 f19 : 1;
    u32 pad20 : 3;
    u32 f23 : 1;
    u32 f24 : 1;
    u32 f25 : 1;
    u32 pad26 : 6;
    /* word 1 */
    u32 g0 : 6;
    u32 g6 : 2;
    u32 g8 : 24;
    u8 b8;
    u8 b9;
    u8 pad_a[7];
    u8 b11;
    u8 pad12[0xe];
    u8 b20;
    u8 b21;
    u8 b22;
    u8 pad23;
    u32 w24;
    u32 w28;
} FlagBits0;

extern u8 lbl_803CAB38[];
extern u8 lbl_80381BF0[];
extern u8 lbl_80381E24[];
extern u8 lbl_80382128[];
extern u8 lbl_803CA870[];
extern char lbl_80364C1C[];
extern char* lbl_8037AB10[];
extern char lbl_804CA0C0[8];
extern void* lbl_804CB62C;

FlagBits0* fn_80060728(void* p);
u8* fn_800C3558(void);
void fn_80062380(void* t, void* x);
void fn_80062598(void* t, void* x);
void* fn_80083B84(void* cls);
void fn_80083B78(void* p);
void* fn_8023F1A4(void* name, int k);
#if TARGET_PC
FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
void fn_8023F1A8(void* p);
#endif
void fn_8023F4EC(char* name);
u8* fn_8024BC94(void);
int fn_80290D04(char* buf, int n, const char* fmt, ...);
void fn_800C3840(void* name, int k);
void fn_80075FB4(char* name, int k);
List3* fn_801E041C(const char* a, const char* b);
u8* fn_800D5448(void* o, void* parent, int k);
void fn_8014C2AC(const char* name);
void fn_8014C59C(void);
void* fn_8009E898(void);
void* fn_80081194(void* cls, void* parent);
void fn_80253EE4(void* name, f32 v);

static inline void setFlag1C(u8* p)
{
    p[0x1c] = 1;
}

int fn_800A2ACC(void* x)
{
    fn_80062380(lbl_803CAB38, x);
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_800A2B08(void)
{
    fn_80062598(lbl_803CAB38, fn_80083B84(lbl_80381BF0));
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_800A2B98(void* res, const char* name)
{
    char buf[0x40];
    s8 lang;
    lbl_804CB62C = fn_8023F1A4(res, 0x20a0);
    lang = *(s8*)(fn_8024BC94() + 0x1bc8);
    fn_80290D04(buf, 0x3f, lbl_80364C1C + 0xd9, lang >= 0 ? lbl_8037AB10[lang] : lbl_804CA0C0, name);
    buf[0x3f] = 0;
    fn_800C3840(res, 0x20a0);
    fn_80075FB4(buf, 0x20a0);
    return 1;
}

int fn_800A2C44(const char* name)
{
    char buf[0x40];
    s8 lang = *(s8*)(fn_8024BC94() + 0x1bc8);
    int z;
    fn_80290D04(buf, 0x3f, lbl_80364C1C + 0xd9, lang >= 0 ? lbl_8037AB10[lang] : lbl_804CA0C0, name);
    z = 0;
    buf[0x3f] = z;
    if (lbl_804CB62C != NULL) {
        fn_8023F1A8(lbl_804CB62C);
        lbl_804CB62C = (void*)z;
    }
    fn_8023F4EC(buf);
    return 1;
}

#define BITSET_BODY(n)                               \
    u32* p = (u32*)(lbl_803CAB38 + 0xdc);            \
    u32 q = n;                                       \
    while (q >= 32) {                                \
        q -= 32;                                     \
        p++;                                         \
    }

int fn_800A2D6C(u32 n)
{
    BITSET_BODY(n)
    *p |= 1 << q;
    return 1;
}

int fn_800A2E04(u32 n)
{
    BITSET_BODY(n)
    *p &= ~(1 << q);
    return 1;
}

#define BITSET_BODY2(n)                              \
    u32* p = (u32*)(lbl_803CAB38 + 0xf0);            \
    u32 q = n;                                       \
    while (q >= 32) {                                \
        q -= 32;                                     \
        p++;                                         \
    }

int fn_800A2E9C(u32 n)
{
    BITSET_BODY2(n)
    *p |= 1 << q;
    return 1;
}

int fn_800A2F34(u32 n)
{
    BITSET_BODY2(n)
    *p &= ~(1 << q);
    return 1;
}

void* fn_800A30AC(void* parent)
{
    List3* o = fn_801E041C(lbl_80364C1C + 0xfe, lbl_80364C1C + 0x106);
    int i;
    Item3* it;
    u8* q;
    o->sC = 0x160;
    o->sE = 0x20;
    o->s1C = 0x20;
    o->s8_ = 0x80;
    o->sA = 0xf0;
    o->f18 = 10.0f;
    o->b24 = 1;
    for (i = 0; o->at(i) != NULL; i++) {
        it = o->at(i);
        it->v60(2);
        it->v6C(0xff);
    }
    q = fn_800D5448(o, parent, 0);
    q[0xa6] = 1;
    q[0xa7] = 1;
    return q;
}

void fn_800A31C8(void* proc)
{
    switch (lbl_803CA870[0xc]) {
    case 0x81: {
        fn_80060728(lbl_803CAB38)->f14 = 0;
        fn_8014C2AC(lbl_80364C1C + 0x10f);
        break;
    }
    case 0x80: {
        fn_80060728(lbl_803CAB38)->f14 = 1;
        fn_8014C59C();
        break;
    }
    }
    fn_80083B78(proc);
}

int fn_800A3274(void)
{
    fn_80081194(lbl_80381E24, fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}

void fn_800A32B4(void)
{
    FlagBits0* b = fn_80060728(lbl_803CAB38);
    b->f0 = 1;
    b->f3 = 1;
    b->g6 = 0;
    b->f5 = 0;
    b->f7 = 1;
    b->f8 = 0;
    b->f12 = 2;
    b->f14 = 0;
    b->f15 = 0;
    b->f16 = 0;
    b->f18 = 1;
    b->f19 = 1;
    b->f23 = 0;
    b->f6 = 0;
    b->b9 = 0x14;
    b->b20 = 0;
    b->w24 = 0;
    b->b21 = 0;
    b->b22 = 0;
    b->w28 = 0;
    b->b11 = 1;
}

void fn_800A3344(int v)
{
    FlagBits0* b = fn_80060728(lbl_803CAB38);
    if (v == 1) {
        b->f12 = 2;
    } else {
        b->f12 = 0;
    }
}

void fn_800A33A0(int v)
{
    FlagBits0* b = fn_80060728(lbl_803CAB38);
    if (v == 1) {
        b->b8 = 0;
    } else {
        b->b8 = 1;
    }
}

void fn_800A33F0(int v)
{
    FlagBits0* b = fn_80060728(lbl_803CAB38);
    if (v == 1) {
        b->f5 = 1;
    } else {
        b->f5 = 0;
    }
}

void fn_800A3448(int v)
{
    FlagBits0* b = fn_80060728(lbl_803CAB38);
    if (v == 1) {
        b->f25 = 1;
    } else {
        b->f25 = 0;
    }
}

void fn_800A34A0(u8 v)
{
    fn_80060728(lbl_803CAB38)->b20 = v;
}

int fn_800A3584(int v)
{
    FlagBits0* b = fn_80060728(lbl_803CAB38);
    if (v == 1) {
        b->f14 = 0;
    } else {
        b->f14 = 1;
    }
    return 0;
}

int fn_800A3CE4(void)
{
    fn_80253EE4(lbl_80382128, 0.0f);
    return 9;
}

class Vt3 : public DataBase3 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C();
    virtual void v20();
};

void fn_800A3D14(Vt3* o)
{
    o->v20();
}

}
