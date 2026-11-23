/* fn_8014CFEC: stop the banner process, keeping the talk-state word and flags (names guessed). */
/* Title-card banner process, event message display flags, 8014C9F8..8014D370. */
#include "game/rM_8014C9F8/types.h"
#pragma auto_inline off

struct Banner : Proc {
    char str[0x20];  /* 0x30 */
    u32 id;          /* 0x50 */
    s16 x;           /* 0x54 */
    s16 y;           /* 0x56 */
    u8 fadeFrom;     /* 0x58 */
    u8 fadeTo;       /* 0x59 */
    u8 fadeCur;      /* 0x5A */
    u8 fadeLen;      /* 0x5B */
    u8 alpha;        /* 0x5C */
    u8 width;        /* 0x5D */
};

struct Fade : Proc {
    u8* target;      /* 0x30 */
    u8 from;         /* 0x34 */
    u8 to;           /* 0x35 */
    u8 cur;          /* 0x36 */
    u8 len;          /* 0x37 */
};

struct Saved {
    u32 w;
    u16 h;
};

extern "C" {

extern u32 lbl_804CB700;
extern Saved lbl_804CB878;
extern u8 lbl_80386C80[];
extern u8 lbl_80386CBC[];
extern char lbl_80369C20[];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB888;
#else
extern u8 lbl_804CB888[];
#endif
extern char lbl_80369C30[];
class Pad5B8 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
    virtual u32 v48();
};
extern Pad5B8* lbl_804CB5B8;

extern void fn_80079210(void*);
extern void fn_80079474(void*);
extern void fn_800068A0(void*, char*);
extern void fn_80006A2C(void*);
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO char* fn_800C4058(p32arg);
#else
extern char* fn_800C4058(u32);
#endif
extern int fn_800CA3DC(char*, int, f32);
extern char* strcpy(char*, const char*);
#if TARGET_PC
extern FE10_PROTO int fn_80291188(p32arg, p32arg);
#else
extern int fn_80291188(u32, u32);
#endif

struct Blk {
    u32 a;
    u32 owned : 1;
    u32 b : 31;
    u32 c;
    void* d;
};

















#pragma use_lmw_stmw off
static inline u16 gh() { return lbl_804CB878.h; }
void fn_8014CFEC(void) {
    u32 w = lbl_804CB878.w;
    u16 h = gh();
    Proc* p;
    lbl_804CB700 |= 2;
    if (!(lbl_804CB878.w & 0x40)) {
        p = fn_80083B84(lbl_80386C80);
        if (p != NULL) {
            if (lbl_804CB700 & 3) {
                fn_80081A90(p);
            } else {
                fn_80083B78(p);
            }
        }
    }
    lbl_804CB878.w = w;
    lbl_804CB878.h = h;
}

}
