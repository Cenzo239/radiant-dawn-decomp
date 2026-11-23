#ifndef RI_801DD7D4_TYPES_H
#define RI_801DD7D4_TYPES_H

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

/* Input-blocked test used widely in this region. The original reads the global
   twice with no CSE before branching, which volatile plus two locals reproduces.
   The global is probably not really volatile. */
#ifdef __cplusplus
extern "C" {
#endif
extern volatile u32 lbl_804CB700;
#ifdef __cplusplus
}
#endif
static inline BOOL inputBlocked(void) {
    u32 f1 = lbl_804CB700;
    u32 f2 = lbl_804CB700;
    BOOL b = FALSE;
    if ((f1 & 0x10) && !(f2 & 0x20)) {
        b = TRUE;
    }
    return b;
}

#endif
