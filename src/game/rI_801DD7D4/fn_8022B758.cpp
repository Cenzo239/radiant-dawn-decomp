#include "game/rI_801DD7D4/types.h"
extern "C" {
#pragma pool_strings on
void* memset(void*, int, u32);
#if TARGET_PC
FE10_PROTO int fn_8022B620(ptr32<const void>);
#else
int fn_8022B620(void*);
#endif
#if TARGET_PC
FE10_PROTO int fn_8022B6A0(ptr32<const void>);
#else
int fn_8022B6A0(void*);
#endif
int fn_800CAB40(const char*);
int fn_800CAF38(int, f32);
int fn_800CABA0(const char*, int, f32);
u32 strlen(const char*);
int fn_80290DDC(char*, const char*, ...);
char* fn_80291110(char*, const char*);
void fn_80253EE4(const char*, f32);
u32* fn_801E2204(void*, s16*, s16*);
extern s16 lbl_804CAA78[4], lbl_804CAA80, lbl_804CAA82;

struct VT { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual int v30_(); virtual int v30(); virtual int v34(); virtual int v38(); };
struct TW { u8 p[0xa]; s16 x0a, x0c, x0e, x10, x12, x14, x16, x18, x1a, x1c, x1e, x20; u8 p2[0x1e]; void* x40; s16 x44, x46, x48; };
static inline const s16& mn(const s16& a, const s16& b) { return b < a ? b : a; }
struct W4 { int v; };
typedef struct C4 { u8 r, g, b, a; } C4;
#if TARGET_PC
FE10_PROTO void fn_801D6F1C(s16, s16, s16, s16, ptr32<const void>, const C4*);
#else
void fn_801D6F1C(s16, s16, s16, s16, void*, const C4*);
#endif
int fn_8028DB44(int);
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_801D9788(int, int, ptr32<const void>);
#else
void fn_801D9788(int, int, void*);
#endif
int fn_800CB0FC(int, f32);
void fn_800800D4(int);
void fn_80080330(f32, f32);
const C4* fn_800CD204(int);
void fn_80080508(C4*);
void fn_80080ABC(int, f32);
void fn_80080C24(const char*);
void fn_80080308(void);
int fn_8017F990(int, int);
double fn_80295940(double);
void fn_80083B78(void*);
struct D44 { u8 p[0x44]; };
struct FontV : D44 { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(int, int, void*); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual int v4c(); virtual int v50(); };
extern u8 lbl_803E7290[];
#define FONT ((FontV*)lbl_803E7290)
struct VI { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual u32 v3c(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern VI* lbl_804CB5B8;
struct VD0 { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); };
struct VD { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14_(); virtual void v18(void*); };
typedef struct Ch { char c[4]; } Ch;
typedef struct TE { u8 p[0x40]; Ch ch[13]; s16 cur, x76, x78; } TE;
static inline int isSJ(const char* const& s) {
    const u8* p = (const u8*)s;
    if ((*p >= 0x81 && *p <= 0x9f) || (*p >= 0xe0 && *p <= 0xfc)) {
        u8 d = p[1];
        if ((d >= 0x40 && d <= 0x7e) || (d >= 0x80 && d <= 0xfc)) return 1;
    }
    return 0;
}
void fn_8022B758(TE* o, const char* s) {
    const char* p = s;
    Ch* q = o->ch;
    u32 i;
    memset(q, 0, 0x34);
    for (i = 0; *p != 0 && i < 0xc; i++) {

        p += fn_800CAB40(p);
        if (!*(char*)p) break;

        if (isSJ(p)) {
            q->c[0] = p[0]; q->c[1] = p[1];
            p += 2;
            q++;
        } else {
            q->c[0] = *p;
            p++;
            q++;
        }
    }
    o->cur = 0;
    o->x76 = -0x8000;
    o->x78 = -0x8000;
}
void fn_8022B880(TE* o, char* buf) {
    Ch* q = o->ch;
    s16 n = 0;
    s16 w = fn_800CAF38(-1, 1.0f) * 7;
    for (; *(int*)q != 0; q++) {
        n += fn_800CABA0(q->c, -1, 1.0f);
    }
    buf[0] = 0;
    if (w < n) {
        fn_80290DDC(buf, "#X%02X", (u8)((f32)w / (f32)n * 64.0f));
    }
    for (q = o->ch; *(int*)q != 0; q++) {
        strlen(q->c);
        fn_80291110(buf, q->c);
    }
    if (w < n) {
        fn_80291110(buf, "#x");
    }
}
static inline s16 teLen(TE* o) {
    Ch* q = o->ch;
    int n = 0;
    while (*(int*)q != 0) { n++; q++; }
    return n;
}

int fn_8022B9B8(TE* o, int wrap) {
    s16 n = teLen(o);
    const s16& m = mn(n, lbl_804CAA80);
    s16 mx; int prev = o->cur;
    mx = m;
    o->cur = prev - 1;
    if ((s16)(prev - 1) < 0) {
        o->cur = wrap != 0 ? mx : 0;
    }
    if (prev != o->cur) {
        fn_80253EE4("SFX_SYS_NAME_WINDOW_MOVE2", 0.0f);
    }
    return o->cur;
}
int fn_8022BA6C(TE* o, int wrap) {
    s16 n = teLen(o);
    const s16& m = mn(n, lbl_804CAA82);
    s16 mx; int prev = o->cur;
    mx = m;
    o->cur = prev + 1;
    if ((u32)(s16)(prev + 1) > (u32)mx) {
        o->cur = wrap != 0 ? 0 : mx;
    }
    if (prev != o->cur) {
        fn_80253EE4("SFX_SYS_NAME_WINDOW_MOVE2", 0.0f);
    }
    return o->cur;
}
Ch* fn_8022BB24(TE* o) {
    u32 n = teLen(o);
    if (n == o->cur) return &o->ch[o->cur];
    W4* q = (W4*)&o->ch[o->cur];
    for (int i = o->cur; i < n; i++, q++) { *q = q[1]; }
    return &o->ch[o->cur];
}
Ch* fn_8022BC00(TE* o, const char* s) {
    Ch* q = &o->ch[o->cur];
    *(int*)q = 0;
    if (isSJ(s)) {
        q->c[0] = s[0];
        q->c[1] = s[1];
    } else {
        q->c[0] = s[0];
    }
    return &o->ch[o->cur];
}
u32 fn_8022C9DC(const TW* o) {
    s16 k = *(s16*)((u8*)o + 0x54);
    s16 q[2]; s16 p[2];
    int i = ((VT*)o)->v34();
    s16 x = o->x1e - 0x5f;
    s16 y = o->x20 + 3;
    switch ((s16)i) {
    case 0: y += i * k; break;
    case 1: y = 0x78; break;
    case 2: y = 0x99; break;
    case 3: y = 0xba; break;
    }
    p[0] = x; p[1] = y;
    return *fn_801E2204((void*)o, q, p);
}

}
