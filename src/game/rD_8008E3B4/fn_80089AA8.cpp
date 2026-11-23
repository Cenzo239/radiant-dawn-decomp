/* Game RNG, fatal handler, MemStream methods, system font metrics: 0x80089AA8..0x8008B19C. */
#include "game/rD_8008E3B4/types.h"

#define VSLOT(n) virtual void v##n();
class PadObj4 {
public:
    VSLOT(08) VSLOT(0C) VSLOT(10) VSLOT(14) VSLOT(18)
    virtual int v1C();                 /* 0x1C */
    VSLOT(20)
    virtual int v24();                 /* 0x24 */
};

extern "C" {

typedef struct Rng {
    u16 a;
    u16 b;
    u16 c;
} Rng;
extern Rng lbl_804CB5D0;
extern u32 lbl_804CB5D8;
extern u32 lbl_804CB700;
extern volatile u32 lbl_804CB5F4;
extern s16 lbl_804CA3C8;
extern u32 lbl_804CB5E0;
extern PadObj4* lbl_804CB5B8;
typedef struct U16x8 { u16 v[8]; } U16x8;
extern U16x8 lbl_803625B0;

static inline u16 rnd(void)
{
    u16 t = (lbl_804CB5D0.b << 11) + (lbl_804CB5D0.a >> 5);
    lbl_804CB5D0.c = lbl_804CB5D0.c << 1;
    if (lbl_804CB5D0.b & 0x8000) {
        lbl_804CB5D0.c++;
    }
    t ^= lbl_804CB5D0.c;
    lbl_804CB5D0.c = lbl_804CB5D0.b;
    lbl_804CB5D0.b = lbl_804CB5D0.a;
    lbl_804CB5D0.a = t;
    return t;
}

void fn_80089AA8(u32 x)
{
    U16x8 t = lbl_803625B0;
    u32 m = x % 7;
    int n;
    lbl_804CB5D0.a = t.v[m & 7];
    lbl_804CB5D0.b = t.v[(m + 1) & 7];
    lbl_804CB5D0.c = t.v[(m + 2) & 7];
    for (n = x % 23; n > 0; n--) {
        rnd();
    }
}

int fn_80089C1C(void)
{
    return rnd() * 100 / 0x10000;
}

int fn_80089C88(int n)
{
    return rnd() * n / 0x10000;
}

int fn_80089CF4(int a, int b)
{
    return a + rnd() * (b - a) / 0x10000;
}

BOOL fn_80089D68(int v)
{
    return (int)(rnd() * 100 / 0x10000) < v;
}

BOOL fn_80089DE8(int v)
{
    int a = rnd() * 100 / 0x10000;
    a += rnd() * 100 / 0x10000;
    return (a >> 1) < v;
}

u32 fn_80089ED0(void)
{
    u32 x = lbl_804CB5D8 * 4 + 2;
    x *= x + 1;
    x >>= 2;
    lbl_804CB5D8 = x;
    return x;
}

void fn_8033111C(int a);
void fn_80330F9C(void);
void fn_80330018(void);
void fn_80303CB4(void);
void fn_80236D3C(void);
void fn_8023662C(void);
void fn_80236334(void);
void fn_800226C0(void);
void fn_803208BC(int a, int b, int c, int d);
u8* fn_8024BC94(void);
void fn_8024F2F4(void);
void fn_8024F364(void);
void fn_8002277C(void);
void fn_8024D810(void);
void fn_802FAFA8(void);
void fn_80023170(void);
void fn_8007A734(void);
u32 fn_800226A0(void);
#if TARGET_PC
FE10_PROTO p32ret fn_8031F69C(void);
FE10_PROTO void fn_80320548(p32arg);
#else
u32 fn_8031F69C(void);
void fn_80320548(u32 x);
#endif
void fn_8031E34C(void);
void fn_80322F58(u32 x);
void fn_8031E5B8(u32 x);
void fn_8031E644(void);
void fn_8031E3F4(void);

void fn_80089EF0(void)
{
    u32 f;
    u32 c;
    u32 d;
    lbl_804CB700 |= 0x100;
    fn_8033111C(1);
    fn_80330F9C();
    fn_80330018();
    fn_80330018();
    fn_80303CB4();
    fn_80330018();
    fn_80330018();
    fn_80330018();
    fn_80236D3C();
    fn_8023662C();
    fn_80236334();
    fn_800226C0();
    fn_803208BC(0, 0, 0, 0);
    f = 0;
    if (lbl_804CB5F4 & 0x90000) {
        if (lbl_804CB5F4 & 0x40) {
            f |= 1;
        }
    } else if (lbl_804CB5F4 & 0x60000) {
        if (lbl_804CB5F4 & 0x40) {
            f |= 1;
        } else if (lbl_804CB5F4 & 0x100) {
            f |= 0x10;
        }
    }
    if (!(lbl_804CB700 & 0x10000000)) {
        f |= 0x10000;
    }
    f |= *(s8*)(fn_8024BC94() + 0x1bc8) << 20;
    fn_8024F2F4();
    fn_8024F364();
    fn_8002277C();
    fn_8024D810();
    fn_802FAFA8();
    fn_80023170();
    fn_8007A734();
    c = fn_800226A0();
    d = fn_8031F69C();
    if (d != c) {
        fn_80320548(fn_800226A0());
    }
    switch (lbl_804CA3C8) {
    case 1:
        fn_8031E34C();
        break;
    case 0:
        fn_80322F58(0xf0000000);
        fn_8031E5B8(f);
        break;
    case 0xfe:
        fn_8031E644();
        break;
    case 0xff:
        fn_8031E3F4();
        break;
    }
    for (;;) {
    }
}


#if TARGET_PC
/* Host: same layout as the buffer class Block in rJ fn_800799AC.cpp (whose methods are
   this object's vtable slots) with 8-byte pointers: base 0, cur 8, size 16, owned 24,
   vtbl 32. MWCC puts the vptr after the base-class data (here at +0x10); clang would
   put it first, so the vtable stays a plain data member. */
typedef struct MemStream {
    u8* base;     /* 0x00 */
    u8* cur;      /* 0x08 */
    u32 size;     /* 0x10 */
    u32 sizeHi;   /* 0x14: Block reads size as a pointer-sized field */
    u8 owned;     /* 0x18 */
    void* vtbl;   /* 0x20 */
} MemStream;
#else
typedef struct MemStream {
    u8* base;     /* 0x00 */
    u8* cur;      /* 0x04 */
    u32 size;     /* 0x08 */
    u8 owned;     /* 0x0C */
    void* vtbl;   /* 0x10 */
} MemStream;
#endif

static inline u8 sGet(MemStream* s)
{
    return *s->cur++;
}

int fn_8008A1B4(MemStream* s)
{
    u32 a = sGet(s);
    a = (a << 8) & 0xff00;
    return a + sGet(s);
}

int fn_8008A1DC(MemStream* s)
{
    u32 a = sGet(s) << 24;
    a += sGet(s) << 16;
    a += sGet(s) << 8;
    return a + sGet(s);
}


f32 fn_8008A31C(MemStream* s)
{
    u32 a = sGet(s) << 24;
    a += sGet(s) << 16;
    a += sGet(s) << 8;
    a += sGet(s);
    return *(f32*)&a;
}

u32 strlen(const char* s);


extern u8 lbl_803810B0[];
#if TARGET_PC
FE10_PROTO void* fn_80077064(p32arg);
#else
void* fn_80077064(u32 size);
#endif

MemStream* fn_8008A4B0(MemStream* s, u32 size)
{
    u8* p;
    s->cur = NULL;
    s->base = NULL;
    s->size = 0;
    s->owned = 0;
    s->vtbl = lbl_803810B0;
    p = (u8*)fn_80077064(size);
    s->cur = p;
    s->base = p;
    s->owned = 0;
    return s;
}

static inline BOOL sEq(MemStream* s, char* m)
{
    s8 c = sGet(s);
    return c == *m;
}

BOOL fn_8008A518(MemStream* s, char* m)
{
    if (sEq(s, m) && sEq(s, m + 1) && sEq(s, m + 2) && sEq(s, m + 3)) {
        return 1;
    }
    return 0;
}

static inline void sPut(MemStream* s, u8 v)
{
    *s->cur++ = v;
}

void fn_8008A5E4(MemStream* s, u32 v)
{
    sPut(s, v >> 24);
    sPut(s, v >> 16);
    sPut(s, v >> 8);
    sPut(s, v);
}

void fn_8008A628(
#if TARGET_PC
MemStream* s, u64 v
#else
MemStream* s, int pad, u64 v
#endif
)
{
    sPut(s, v >> 56);
    sPut(s, v >> 48);
    sPut(s, v >> 40);
    sPut(s, v >> 32);
    sPut(s, v >> 24);
    sPut(s, v >> 16);
    sPut(s, v >> 8);
    sPut(s, v);
}

void fn_8008A820(MemStream* s, u8* m)
{
    *s->cur++ = m[0];
    *s->cur++ = m[1];
    *s->cur++ = m[2];
    *s->cur++ = m[3];
}


void fn_8008A868(void);
typedef struct Glyph {
    u8 pad0[0x120];
    u16 code;   /* 0x120 */
    u16 width;  /* 0x122 */
    u8 pad124[0x1c];
} Glyph;
typedef struct SysFont {
    Glyph* glyphs;
    int count;
} SysFont;
extern SysFont lbl_804CB5E8;
extern u8* lbl_80381190[0x10];
u32 fn_8031C044(void);

void fn_8008AEA8(void)
{
    SysFont* f = &lbl_804CB5E8;
    if (lbl_804CB5E8.glyphs == NULL) {
        f->glyphs = NULL;
        f->count = 0;
        fn_8008A868();
    }
}

void* fn_8008AECC(int i)
{
    return ((void**)lbl_80381190[1])[i];
}

static inline BOOL isDbcs(const u8* p)
{
    u8 c = p[0];
    if ((c >= 0x81 && c <= 0x9f) || (c >= 0xe0 && c <= 0xfc)) {
        c = p[1];
        if ((c >= 0x40 && c <= 0x7e) || (c >= 0x80 && c <= 0xfc)) {
            return 1;
        }
    }
    return 0;
}

#pragma push
#pragma use_lmw_stmw on
#pragma pop

int fn_8008B08C(const char* s)
{
    /*P*/
    int d;
    int h;
    const char* p;
/*E*/
    if (*s == 0) {
        return 0;
    }
    p = s;
    h = 0x18;
    while (*p != 0) {
        if (*p == 10) {
            h += 0x18;
            p++;
        } else if ((u16)fn_8031C044() != 1) {
            p++;
        } else {
            d = 0;
            if ((u16)fn_8031C044() == 1) {
                d = isDbcs((u8*)p);
            }
            if (d != 0) {
                p += 2;
            } else {
                p++;
            }
        }
    }
    return h;
}

}
