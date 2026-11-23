#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
void fn_80079210(void*);
void* fn_801E5640(void*, int, int);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_801E5734(void*, void*);
void fn_8014C2AC(void*);
void fn_80253EE4(const char*, f32);
void fn_801E495C(void*, void*, void*, int);
void fn_801E518C(void*, void*, int, f32);
void fn_801E4F50(void*, void*, int);
extern VO0N* lbl_804CB5B8;
extern u8 lbl_803CA870[0x130];
extern u8 lbl_803CAB38[0x988];
extern char lbl_80372600[];
struct XY { s16 x, y; };
struct Wi { u8 p[0x40]; const char* a40; u8 p44[0x20]; const char* a64; };
struct WY { u8 p[0xa]; s16 x, y; };
struct Sm { u8 p[0x88]; u8* a88; };
static inline void mvx(void* s, WY* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }
static inline void setHelpV(void* s, const char* str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
#define FINI1(name, off) \
void name(Sm* s) { \
    fn_801E5734(s, fn_801E5640(s, -0x1000, 0)); \
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) { \
        fn_801E5734(s, fn_801E5640(s, 0, 0)); \
        fn_8014C2AC(*(void**)(s->a88 + off)); \
        fn_80253EE4(lbl_80372600 + 0x52, 0.0f); \
        fn_80083B78(s); \
    } \
}
void fn_801E59A8(void*, void*, void*, int);
extern char lbl_80390B28[];
struct RW { u8 p[0xa]; s16 x0, y0, x1, y1; u8 p12[0x16]; s16 a28; };
struct Roll { u8 p[0x28]; s16 a28; u8 p2a[6]; u8 a30; s8 a31; s8 a32; u8 p33[5]; u8* a38; };
struct Sm70 { u8 p[0x70]; void* a70; };
int fn_80060754(void*);
int* fn_801059B0(void);
void fn_802319E8(void);
#if TARGET_PC
FE10_PROTO int * fn_8010F5E0(void* p);
#else
int fn_8010F5E0(void* p);
#endif
void* fn_80110F08(void*);
#if TARGET_PC
FE10_PROTO void fn_8022DE0C(void*, p32arg, int, void*);
#else
void fn_8022DE0C(void*, int, int, void*);
#endif
struct It { u8 p[0x16]; u16 a16; };
void fn_801E59A8(void*, void*, void*, int);
extern char lbl_80390B28[];
extern char lbl_80390B14[];
extern char lbl_80390B00[];
void fn_80231090(Roll* o) {
    u8* t = o->a38;
    int x;
    int i;
    i = 0;
    x = 0;
    do {
        RW* w = *(RW**)(t + 0x4c);
        if (i != o->a32) {
            XY p;
            w->a28 = 0x1e;
            p.x = x;
            p.y = 0;
            fn_801E59A8(o, w, &p, 0);
        }
        t += 4;
        i++;
        x += 0x78;
    } while (i < 5);
    fn_80253EE4(lbl_80390B28, 0.0f);
    o->a28 = 0x1e;
}
void fn_801051D8(int*, void*);
void fn_80233AF4(void* s) {
    void* p;
    void* w = fn_801E5640(s, 8, 0);
    switch (lbl_803CA870[0xc]) {
    case 0x81:
        fn_801E5640(s, 6, 0);
        {
            p = (u8*)s + 0x40;
            if (fn_80060754(lbl_803CAB38) != 0) {
                fn_801051D8(fn_801059B0(), p);
            }
        }
        if (w != NULL) fn_801E5734(s, w);
        break;
    case 0x80:
        fn_80083DC4(s, 0x22);
        break;
    }
}
void fn_802319E8(void);
struct LV { VO0N* v; };
void fn_80231AF8(Sm* s) {
    u8* w = (u8*)fn_801E5640(s, 0xc, 0);
    u8* t = *(u8**)(w + *(s16*)(w + 0x6a) * 4 + 0x4c);
    switch (lbl_803CA870[0xc]) {
    case 0x81:
        w[0x68] = 0;
        t[0x40] = w[0x61];
        fn_802319E8();
        ((VO0N*)w)->v38();
        setHelpV(s, *(const char**)(s->a88 + 0xa4));
        break;
    case 0x80:
        fn_8014C2AC(*(void**)(s->a88 + 0x2c));
        fn_801E5734(s, w);
        fn_80083DC4(s, 0x16);
        break;
    }
}
}
