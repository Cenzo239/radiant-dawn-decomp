#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef struct Probe { u8 pad[0x30]; void* a; } Probe;
typedef struct R21D8 { u8 pad[0x30]; MapUnit* u; u8 b34; u8 b35; u8 b36; } R21D8;

/* Jump process (guessed), 8010403C..801045F4. */
typedef struct Jump {
    u8 pad[0x30];
    MapUnit* u; /* 0x30 */
    s16 dir;    /* 0x34 */
    u8 pad36[4];
    s16 x;      /* 0x3A */
    s16 y;      /* 0x3C */
    u8 pad3E[6];
    f32 f44;    /* 0x44 */
    f32 f48, f4C, f50; /* 0x48 */
    f32 f54, f58, f5C; /* 0x54 */
    f32 f60;    /* 0x60 */
    s16 t;      /* 0x64 */
    s16 dur;    /* 0x66 */
    s16 speed;  /* 0x68 */
    u8 b6A;
    u8 b6B;     /* 0x6B */
} Jump;

extern "C" {
extern u8 lbl_80385090[];
extern void fn_80104A70(void* a, void* b);
extern void* fn_800893E4(void*, void*, Probe*);
extern R21D8* fn_80081050(void*, void*);
extern int fn_801220A0(MapUnit*);
extern int fn_800F4700(MapUnit*, const char*);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_800F0994(const char*);
#else
extern void* fn_800F0994(const char*);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80102928(MapUnit*, i32arg, int, int, p32arg);
#else
extern void fn_80102928(MapUnit*, void*, int, int, int);
#endif
extern void fn_80083DC4(void*, int);

#pragma pool_strings on
void pool_7d50() {
    const char* volatile s;
    s = "\x95""\xe0""\x82""\xab"""; /* 0x0 */
    s = "\x88""\xda""\x93""\xae"""; /* 0x5 */
    s = ""; /* 0xa */
    s = "\x93""o\x82""\xe8"""; /* 0xb */
    s = "\x8d""~\x82""\xe8"""; /* 0x10 */
    s = "\x83""_\x83""\x81""\x81""[\x83""W"; /* 0x15 */
    s = "EID_SMITE"; /* 0x1e */
    s = "EID_TACKLE"; /* 0x28 */
    s = "\x91""\xcc""\x93""\x96""\x82""\xbd""\x82""\xe8"""; /* 0x33 */
    s = "SFX_BMP_DAMAGE_TACKLE1"; /* 0x3c */
    s = "EID_QUICK_REWARP_F1"; /* 0x53 */
    s = "EID_QUICK_REWARP_T1"; /* 0x67 */
    s = "EID_QUICK_REWARP_W1"; /* 0x7b */
    s = "EID_QUICK_REWARP1"; /* 0x8f */
    s = "EID_RESCUE1"; /* 0xa1 */
    s = "EID_QUICK_REWARP_F2"; /* 0xad */
    s = "EID_QUICK_REWARP_T2"; /* 0xc1 */
    s = "EID_QUICK_REWARP_W2"; /* 0xd5 */
    s = "EID_QUICK_REWARP2"; /* 0xe9 */
    s = "EID_RESCUE2"; /* 0xfb */
    s = "\x95""\xcf""\x90""g"; /* 0x107 */
    s = "EID_INCARNATION"; /* 0x10c */
    s = "\x8e""\x80""\x96""S"; /* 0x11c */
    s = "SFX_BMP_FADE_DIE_AWAY1"; /* 0x121 */
    s = "\x91""\xd2""\x8b""@"; /* 0x138 */
}

static inline int DirX(u8 d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    }
    return 0;
}
static inline int DirY(u8 d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    }
    return 0;
}
static inline int Scale(int t, f32 k) { return (f32)t * k; }
static inline void PA(MapUnit* u, const char* name, int a, int b, int c) {
    fn_80102928(u, fn_800F0994(name), a, b, c);
}
static inline int State(R21D8* p) {
    if (p->b34 == 0) return 2;
    if (p->b36) {
        if (fn_801220A0(p->u) == 2) return 1;
    }
    return 0;
}
static inline void Fx(MapUnit* u, void* parent) {
    Probe s;
    R21D8* q;
    s.a = u;
    fn_800893E4(lbl_80385090, fn_80104A70, &s);
    if (parent == 0) parent = (void*)3;
    q = fn_80081050(lbl_80385090, parent);
    q->u = u;
}
void fn_80102300(R21D8* p) {
    char* s;
    switch (State(p)) {
    case 0: {
        if (fn_800F4700(p->u, "\x95""\xcf""\x90""g")) {
            PA(p->u, "\x95""\xcf""\x90""g", 0x10, 0, 0);
            Fx(p->u, p);
            break;
        }
    }
    case 1:
        fn_80083DC4(p, 0);
        break;
    case 2:
        fn_80083DC4(p, 1);
        break;
    }
}

}
