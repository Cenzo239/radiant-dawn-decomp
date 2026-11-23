/* fn_8008A22C: read a big-endian 64-bit value from a memory stream. Standalone copy of the declarations of rD_8008E3B4/fn_80089AA8.cpp (function bodies stripped) plus this function. */
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

void fn_80089AA8(u32 x);

int fn_80089C1C(void);

int fn_80089C88(int n);

int fn_80089CF4(int a, int b);

BOOL fn_80089D68(int v);

BOOL fn_80089DE8(int v);

u32 fn_80089ED0(void);

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
FE10_PROTO void * fn_8031F69C(void);
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

void fn_80089EF0(void);


typedef struct MemStream {
    u8* base;     /* 0x00 */
    u8* cur;      /* 0x04 */
    u32 size;     /* 0x08 */
    u8 owned;     /* 0x0C */
    void* vtbl;   /* 0x10 */
} MemStream;

static inline u8 sGet(MemStream* s)
{
    return *s->cur++;
}

int fn_8008A1B4(MemStream* s);

int fn_8008A1DC(MemStream* s);


f32 fn_8008A31C(MemStream* s);

u32 strlen(const char* s);


extern u8 lbl_803810B0[];
#if TARGET_PC
FE10_PROTO void* fn_80077064(p32arg);
#else
void* fn_80077064(u32 size);
#endif

MemStream* fn_8008A4B0(MemStream* s, u32 size);

static inline BOOL sEq(MemStream* s, char* m)
{
    s8 c = sGet(s);
    return c == *m;
}

BOOL fn_8008A518(MemStream* s, char* m);

static inline void sPut(MemStream* s, u8 v)
{
    *s->cur++ = v;
}

void fn_8008A5E4(MemStream* s, u32 v);

void fn_8008A628(MemStream* s, int pad, u64 v);

void fn_8008A820(MemStream* s, u8* m);


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

void fn_8008AEA8(void);

void* fn_8008AECC(int i);

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

int fn_8008B08C(const char* s);

}


extern "C" {
u64 fn_8008A22C(MemStream* s) {
    u64 a;
    a = (u64)sGet(s) << 56;
    a += (u64)sGet(s) << 48;
    a += (u64)sGet(s) << 40;
    a += (u64)sGet(s) << 32;
    a += (u64)sGet(s) << 24;
    a += (u64)sGet(s) << 16;
    a += (u64)sGet(s) << 8;
    a += sGet(s);
    return a;
}
}
