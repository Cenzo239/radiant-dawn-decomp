#ifndef RG_TYPES_H
#define RG_TYPES_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
typedef double f64;
typedef int BOOL;
#ifndef NULL
#define NULL 0
#endif
/* Dummy vtable slots: a class needs real virtuals for the r12 call sequence. */
#define VP1(a) virtual void a();
#define VP2(a) VP1(a##0) VP1(a##1)
#define VP4(a) VP2(a##0) VP2(a##1)
#define VP8(a) VP4(a##0) VP4(a##1)
#define VP16(a) VP8(a##0) VP8(a##1)
#endif
