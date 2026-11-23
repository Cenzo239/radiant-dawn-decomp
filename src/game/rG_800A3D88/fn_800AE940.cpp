#include "game/rG_800A3D88/types.h"

// Background model: load the files of one scene entry.
extern "C" {
struct BgM { u32 flags; u8 p4[0x5C - 4]; f32 m5c; };
struct Bg { u8 p[0x34]; f32 m34; void* m38; BgM* m3c; void* m40; };
struct BgE { u8 p[4]; const char* m4; };
extern char lbl_803656F8[];
#define S(a) (lbl_803656F8 + ((a) - 0x803656F8))
long long OSGetTime();
void fn_80011CBC(void*, void*);
void fn_80006EE0(void*);
#if TARGET_PC
FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
void fn_8023F1A8(void*);
#endif
void fn_80081A90(void*);
BgE* fn_800A7CE8(int);
int fn_80290DDC(char*, const char*, ...);
#if TARGET_PC
FE10_PROTO const char* fn_8017F37C(const char*, const char*, p32arg);
#else
const char* fn_8017F37C(const char*, const char*, int);
#endif
int fn_8023F9F4(const char*);
void* fn_8023F1A4(const char*, int);
BgM* fn_80006E1C();
void fn_80009214(BgM*, const char*, int);
void fn_80009274(BgM*, const char*, int);
void fn_800092D4(BgM*, const char*, int);
void fn_80009150(BgM*, const char*, int);
void* fn_80007F10(BgM*);
int fn_8000A168(void*, int, u16*);
void fn_80006F20(BgM*);
void fn_80008F54(BgM*, int);
void fn_80008F5C(BgM*, int);
void* fn_80008110(BgM*, const char*);
void* fn_800A91B0(Bg*);
void fn_800A8B80(void*, BgM*);
f32 fn_800A84A4(const char*);
int fn_800AE940(Bg* b, int k) {
    struct { u16 c; u8 p[2]; char buf[0x40]; } f;
    OSGetTime();
    if (k < 0) return 0;
    if (b->m3c != NULL) {
        fn_80011CBC(fn_80006EE0, b->m3c);
        if (b->m38 != NULL) fn_80011CBC(fn_8023F1A8, b->m38);
        b->m3c = NULL;
        b->m38 = NULL;
        if (b->m40 != NULL) {
            fn_80081A90(b->m40);
            b->m40 = NULL;
        }
    }
    const char* n = fn_800A7CE8(k)->m4;
    if (n == NULL) return 0;
    fn_80290DDC(f.buf, lbl_803656F8, n, n);
    if (fn_8023F9F4(fn_8017F37C(f.buf, S(0x80365702), 0)) == 0x40000) return 0;
    b->m38 = fn_8023F1A4(fn_8017F37C(f.buf, S(0x80365702), 0), 0x2040);
    b->m3c = fn_80006E1C();
    fn_80009214(b->m3c, fn_8017F37C(f.buf, S(0x80365707), 0), 0x2040);
    fn_80009274(b->m3c, fn_8017F37C(f.buf, S(0x8036570B), 0), 0x2040);
    fn_800092D4(b->m3c, fn_8017F37C(f.buf, S(0x8036570E), 0), 0x2040);
    if (fn_8023F9F4(fn_8017F37C(f.buf, S(0x80365713), 0)) != 0x40000) {
        fn_80009150(b->m3c, fn_8017F37C(f.buf, S(0x80365713), 0), 0x2040);
        if (fn_8000A168(fn_80007F10(b->m3c), 0x19, &f.c)) {
            b->m3c->m5c = (f32)f.c / 100.0f;
        }
    }
    fn_80006F20(b->m3c);
    b->m3c->flags |= 0x20000;
    fn_80008F54(b->m3c, 0x8C);
    fn_80008F5C(b->m3c, 3);
    if (fn_80008110(b->m3c, S(0x80365717))) {
        b->m40 = fn_800A91B0(b);
        fn_800A8B80(b->m40, b->m3c);
    } else {
        b->m40 = NULL;
    }
    b->m34 = fn_800A84A4(S(0x8036571E));
    OSGetTime();
    return 1;
}
}
