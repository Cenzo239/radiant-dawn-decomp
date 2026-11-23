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
void pool_707c() {
    const char* volatile s;
    s = "\x8f""\xf1"""; /* 0x0 */
    s = "SFX_BMP_MISS1"; /* 0x3 */
    s = "\x83""_\x83""\x81""\x81""[\x83""W"; /* 0x11 */
    s = "EID_HEALINGHAND"; /* 0x1a */
    s = "r_hand"; /* 0x2a */
    s = "EID_HEALINGHAND_HEAL"; /* 0x31 */
    s = "\x89""\x9c""\x8b""`\x82""T"; /* 0x46 */
    s = "EID_CHANT"; /* 0x4d */
    s = "EID_BLISS"; /* 0x57 */
    s = "EID_SORROW"; /* 0x61 */
    s = "EID_BRAVE"; /* 0x6c */
    s = "EID_HEAL"; /* 0x76 */
    s = "EID_BOON"; /* 0x7f */
    s = "EID_BLESSING"; /* 0x88 */
    s = "EID_CHANT_H"; /* 0x95 */
    s = "EID_BLISS_H"; /* 0xa1 */
    s = "EID_SORROW_H"; /* 0xad */
    s = "EID_BRAVE_H"; /* 0xba */
    s = "EID_HEAL_H"; /* 0xc6 */
    s = "EID_BLESSING_HEAL"; /* 0xd1 */
    s = "EID_BOON_CURE"; /* 0xe3 */
    s = "EID_EVILEYE_STONE"; /* 0xf1 */
    s = "EID_EVILEYE"; /* 0x103 */
    s = "SFX_BMP_NO_DAMAGE1"; /* 0x10f */
    s = "SFX_BMP_DAMAGE_FINISH1"; /* 0x122 */
    s = "SFX_BMP_DAMAGE_DOWN1"; /* 0x139 */
    s = "EID_CURE"; /* 0x14e */
    s = "EID_POISON_H"; /* 0x157 */
    s = "EID_ATTK1"; /* 0x164 */
    s = "EID_LAVA01"; /* 0x16e */
    s = "EID_LAVA02"; /* 0x179 */
    s = "EID_STATE_RECOVER"; /* 0x184 */
    s = "EID_SHOOTER"; /* 0x196 */
    s = "\x8d""\\\x82""\xa6"""; /* 0x1a2 */
    s = "\x89""\xf1""\x94""\xf0"""; /* 0x1a7 */
    s = "SFX_BMP_DAMAGE_THRUST1"; /* 0x1ac */
    s = "SFX_BMP_DAMAGE_SPECIAL1"; /* 0x1c3 */
    s = "SFX_BMP_ROCK_BREAK2"; /* 0x1db */
    s = "EID_ONAGER"; /* 0x1ef */
    s = "EID_ONAGERSTONES"; /* 0x1fa */
    s = ""; /* 0x20b */
}

void fn_800EAD10(EvZ* p) {
    char* s;
    int i;
    u8* c = lbl_803CA870;
    u8* o;
    p->x6C = c[0x11];
    p->y6C = c[0x12];
    p->o = o = fn_80135A54(fn_8013B9A8(), p->x6C, p->y6C, 0x8000, 0);
    if (o == 0) {
        fn_80083DC4(p, 0x63);
        return;
    }
    p->x0 = o[1];
    p->y0 = o[2];
    p->x1 = c[0x13];
    p->y1 = c[0x14];
    p->z0 = fn_801142F0(lbl_803EC898, (f32)p->x0, (f32)p->y0);
    p->z1 = fn_801142F0(lbl_803EC898, (f32)p->x1, (f32)p->y1);
    {
        fn_800E24F8("EID_ONAGER");
        fn_800E24F8("EID_ONAGERSTONES");
        fn_800E24F8("EID_ATTK1");
        for (i = 0; i < lbl_803E7320[0]; i++) {
            void* x = fn_800CFB0C(fn_800CFD18(lbl_803E7320, i));
            if (x) {
                fn_800F6604(x, "\x83""_\x83""\x81""\x81""[\x83""W");
            }
        }
    }
}

#pragma use_lmw_stmw off
void fn_800EB274(EvX* p) {
    if (p->h88 >= p->h8A - 4) {
        void* c = fn_800E3A10("EID_ONAGERSTONES", p);
        if (c) {
            fn_800E48AC(c, 0.5f + (f32)p->b.unk7E, 0.5f + (f32)p->b.unk7F, p->f84);
        }
        {
            int i;
            for (i = 0; i < lbl_803E7320[0]; i++) {
                void* x = fn_800CFB0C(fn_800CFD18(lbl_803E7320, i));
                if (x) {
                    fn_80102C6C(x, "\x83""_\x83""\x81""\x81""[\x83""W", 8, 0, 0);
                    fn_80102CD8(x, -1, 0x10, 0);
                    fn_80103234(x, 1, 2, 0);
                    c = fn_800E3810("EID_ATTK1", p);
                    if (c) {
                        fn_800E5878(c, x);
                    }
                }
            }
        }
        fn_80083B78(p);
    }
}

