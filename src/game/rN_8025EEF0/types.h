#ifndef RN_8025EEF0_TYPES_H
#define RN_8025EEF0_TYPES_H

typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef int BOOL;


/* Controller singleton, lbl_804CB5B8. Virtual slots named by vtable offset. */
class Pad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual u32 v18(); virtual void v1C(); virtual u32 v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual u32 v34();
    virtual void v38();
    virtual u32 v3C();   /* held/repeat */
    virtual void v40(); virtual void v44();
    virtual u32 v48();   /* pressed */
};
extern "C" Pad* lbl_804CB5B8;
/* Files that define RN_FLAGS_PLAIN see the flag word as a normal global. */
#ifdef RN_FLAGS_PLAIN
extern "C" u32 lbl_804CB700;
#else
extern "C" volatile u32 lbl_804CB700;
#endif
extern "C" u32 lbl_804CB878;

#ifndef RN_FLAGS_PLAIN
/* Input-blocked test, as in rI_801DD7D4/types.h */
static inline BOOL inputBlocked(void) {
    u32 f1 = lbl_804CB700;
    u32 f2 = lbl_804CB700;
    BOOL b = 0;
    if ((f1 & 0x10) && !(f2 & 0x20)) {
        b = 1;
    }
    return b;
}
#endif

#endif
