#ifndef RH_80112B48_TYPES_H
#define RH_80112B48_TYPES_H

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
#ifndef NULL
#define NULL 0
#endif

typedef struct Vec {
    f32 x, y, z;
} Vec;

#endif
