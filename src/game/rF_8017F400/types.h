#ifndef RF_8017F400_TYPES_H
#define RF_8017F400_TYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;
typedef float f32;
typedef double f64;
typedef int BOOL;
#define TRUE 1
#define FALSE 0

#ifndef NULL
#define NULL 0
#endif

#endif

#ifndef RF_8017F400_STRUCTS
#define RF_8017F400_STRUCTS
#ifdef __cplusplus
extern "C" {
#endif

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct Vec {
    f32 x, y, z;
} Vec;

/* 0x3250-byte keyframe track; ctor fn_8017FDC8; 8 of them are new[]'d by fn_80180CBC */
typedef struct Track {
    GXColor color; /* 0x00 */
    u8 unk4;       /* 0x04 */
    s16 unk6;      /* 0x06 */
    u8 count;      /* 0x08 */
    s16 unkA;      /* 0x0A */
    f32 unkC;      /* 0x0C */
    f32 unk10;     /* 0x10 */
    f32 unk14;     /* 0x14 */
    f32 unk18;     /* 0x18 */
    f32 unk1C;     /* 0x1C */
    s32 keys[32];  /* 0x20 */
    Vec vals[32];  /* 0xA0 */
    u8 pad[0x3250 - 0x220];
} Track;

#ifdef __cplusplus
}
#endif
#endif
