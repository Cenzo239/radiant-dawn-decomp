#ifndef RC2_BASE_H
#define RC2_BASE_H
/* Plain integer types only, for files whose local structs would clash with the shared region declarations. */
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
typedef unsigned long long u64;
typedef signed long long s64;
typedef float f32;
typedef double f64;
#endif
