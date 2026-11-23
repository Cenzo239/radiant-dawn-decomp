#ifndef RJ_800799AC_TYPES_H
#define RJ_800799AC_TYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
#if TARGET_PC
/* long is 64-bit on LP64 hosts */
typedef unsigned int u32;
typedef signed int s32;
#else
typedef unsigned long u32;
typedef signed long s32;
#endif
typedef float f32;
typedef double f64;
typedef unsigned long long u64;
typedef signed long long s64;
typedef int BOOL;

#ifndef NULL
#define NULL 0
#endif

#endif
