#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct EvX {
    EvProc b;
    f32 f84;   /* 0x84 */
    s16 h88;   /* 0x88 */
    s16 h8A;   /* 0x8A */
} EvX;

typedef struct Seq2 {
    u8 pad[0xB];
    u8 bB;     /* 0x0B */
    u8 bC;     /* 0x0C */
    u8 padD;
    u16 ids[1]; /* 0x0E */
} Seq2;

typedef struct BP2 {
    u8 pad[0x30];
    Seq2* seq; /* 0x30 */
    u8 pad34[0x10];
    u8 b44;    /* 0x44 */
} BP2;

typedef struct Gauge {
    u8 pad[0x3C];
    void* tex; /* 0x3C */
    u8 pad40[7];
    u8 b47;    /* 0x47 */
} Gauge;

extern u8 lbl_8036707C[];
extern u8 lbl_803672A0[];
extern s32 lbl_803E7320[];
extern const f32 lbl_804CD9B8;
extern const f32 lbl_804CD9C0;
extern f32 fn_80176A4C(f32, f32, f32, f32);
extern void fn_801CAD54(void*, void*, int, f32);
#if TARGET_PC
extern FE10_PROTO void fn_801030B8(void*, int, int, int, int, void *);
#else
extern void fn_801030B8(void*, int, int, int, int, int);
#endif
extern void* fn_800E3A10(char*, void*);
extern void* fn_800E3810(char*, void*);
extern void fn_800E48AC(void*, f32, f32, f32);
extern void* fn_800CFD18(void*, int);
extern void* fn_800CFB0C(void*);
#if TARGET_PC
extern FE10_PROTO void fn_80102C6C(void*, char*, int, int, int);
extern FE10_PROTO void fn_80102CD8(void*, void *, void *, void *);
extern FE10_PROTO void fn_80103234(void*, int, int, void *);
#else
extern void fn_80102C6C(void*, char*, int, int, void*);
extern void fn_80102CD8(void*, int, int, int);
extern void fn_80103234(void*, int, int, int);
#endif
extern void fn_800E5878(void*, void*);
extern void fn_80083B78(void*);
extern Handle* fn_801D0784(void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_8010301C(void*, void*, int, int, void *);
#else
extern void fn_8010301C(void*, void*, int, int, void*);
#endif
extern int fn_801CFE78(Seq2*, int);
extern void fn_800EB4AC(BP2*, int);
extern int fn_801D0214(Seq2*, int);
extern int fn_801CFDEC(Seq2*, int);
extern int fn_801D012C(Seq2*, int);
extern void* fn_801D009C(Seq2*, int);
extern int fn_8013B9B0(void);
extern void fn_801CE2F4(void*, int, int);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, void *, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_8007E7DC(u8);
extern void fn_8007E7F4(void);
extern void fn_800800D4(int);
extern void fn_80080430(f32, f32, f32, f32, f32, f32);
extern void fn_80080578(int);
extern void fn_80080308(void);




#pragma use_lmw_stmw on
#pragma use_lmw_stmw off



static inline void Rect(f32 a, f32 b, f32 c, f32 d, int w, int h) {
    fn_80080430(a, b, c, d, (f32)w, (f32)h);
}
static inline void Tex(void* t, int n, int f) { fn_8007E374(t, n, f); }

typedef struct EvY {
    EvProc b;
    f32 f84;
} EvY;
typedef struct EvZ {
    u8 pad[0x6C];
    s8 x6C, y6C;
    u8 pad6E[0xA];
    u8* o;     /* 0x78 */
    s8 x0, y0, x1, y1; /* 0x7C */
    f32 z0;    /* 0x80 */
    f32 z1;    /* 0x84 */
} EvZ;
extern u8 lbl_803CA870[];
extern u8 lbl_803EC898[];
extern const f32 lbl_804CD928;
extern const f32 lbl_804CD92C;
extern void* fn_8013B9A8(void);
extern u8* fn_80135A54(void*, int, int, int, int);
extern void fn_80083DC4(void*, int);
extern f32 fn_801142F0(void*, f32, f32);
extern void fn_800E24F8(char*);
extern void fn_800F6604(void*, char*);
extern f32 fn_80313508(Vec*);
extern void fn_800E4AD4(EvCmd*, f32);
extern void fn_800E49AC(EvCmd*, f32);
void fn_800E9DA4(EvCmd*);
void fn_800E9DF0(EvCmd*);



#pragma pool_strings on
void pool_72a0() {
    const char* volatile s;
    s = "SFX_BMP_DAMAGE_DOOR_FINISH1"; /* 0x0 */
    s = "SFX_BMP_DAMAGE_DOOR1"; /* 0x1c */
    s = "SFX_BMP_DAMAGE_FINISH1"; /* 0x31 */
    s = "SFX_BMP_DAMAGE_THRUST1"; /* 0x48 */
    s = "SFX_BMP_DAMAGE_UP1"; /* 0x5f */
    s = "SFX_BMP_DAMAGE_DOWN1"; /* 0x72 */
    s = "SFX_BMP_DAMAGE_SPECIAL2"; /* 0x87 */
    s = "SFX_BMP_DAMAGE_SPECIAL1"; /* 0x9f */
    s = "SFX_BMP_NO_DAMAGE1"; /* 0xb7 */
    s = "\x8d""\\\x82""\xa6"""; /* 0xca */
    s = "SFX_BMP_MISS1"; /* 0xcf */
    s = "\x89""\x9c""\x8b""`\x82""P"; /* 0xdd */
    s = "\x89""\x9c""\x8b""`\x82""Q"; /* 0xe4 */
    s = "\x89""\x9c""\x8b""`\x82""R"; /* 0xeb */
    s = "\x89""\x9c""\x8b""`\x82""S"; /* 0xf2 */
    s = "\x89""\x9c""\x8b""`\x82""T"; /* 0xf9 */
    s = "\x8f""\xe3""\x8d""U\x8c""\x82""\x82""P"; /* 0x100 */
    s = "\x89""\xba""\x8d""U\x8c""\x82""\x82""P"; /* 0x109 */
    s = "\x8d""U\x8c""\x82""\x82""P"; /* 0x112 */
    s = "\x8f""\xe3""\x96""\x82""\x96""@\x82""P"; /* 0x119 */
    s = "\x89""\xba""\x96""\x82""\x96""@\x82""P"; /* 0x122 */
    s = "\x96""\x82""\x96""@\x82""P"; /* 0x12b */
    s = "\x83""K\x81""[\x83""h"; /* 0x132 */
    s = "\x92""e\x82""\xa9""\x82""\xea""\x82""P"; /* 0x139 */
    s = "\x92""e\x82""\xa9""\x82""\xea""\x82""Q"; /* 0x142 */
    s = "\x83""_\x83""\x81""\x81""[\x83""W"; /* 0x14b */
    s = "\x89""\xf1""\x94""\xf0"""; /* 0x154 */
    s = "magic"; /* 0x159 */
    s = ""; /* 0x15f */
}

#pragma use_lmw_stmw on
void fn_800EC0C8(BP2* p) {
    void* a = HandleActor(fn_801D0784(p->seq, 0));
    void* b = HandleActor(fn_801D0784(p->seq, 1));
    void* c = HandleActor(fn_801D0784(p->seq, 2));
    fn_80102C6C(a, "\x8d""\\\x82""\xa6""", 0x10, 0, p);
    if (b) {
        fn_8010301C(a, b, 0x18, 0, p);
        fn_8010301C(b, a, 0x18, 0, p);
        fn_80102C6C(b, "\x8d""\\\x82""\xa6""", 0x10, 0, p);
        if (c) {
            fn_8010301C(c, b, 0x18, 0, p);
            fn_80102C6C(c, "\x8d""\\\x82""\xa6""", 0x10, 0, p);
        }
    }
}

