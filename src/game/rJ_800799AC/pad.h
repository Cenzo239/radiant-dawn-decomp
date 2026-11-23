#ifndef RJ_800799AC_PAD_H
#define RJ_800799AC_PAD_H

#include "game/rJ_800799AC/types.h"

/* Controller base class. Subclass vtables: lbl_80380978, lbl_80380A64,
 * lbl_80380B50, lbl_80380C3C, lbl_80380D28. Each virtual is named after its
 * vtable offset; the real names are not known yet. */
class Pad {
public:
    virtual int v08(int);
    virtual int v0C(int);
    virtual int v10();
    virtual int v14();
    virtual int v18();
    virtual int v1C();
    virtual int v20();
    virtual int v24();
    virtual int v28();
    virtual int v2C();
    virtual int v30();
    virtual int v34();
    virtual int v38();
    virtual int v3C();
    virtual int v40();
    virtual int v44();
    virtual int v48();
    virtual int v4C();
    virtual int v50();
    virtual int v54();
    virtual int v58();
    virtual int v5C();
    virtual int v60();
    virtual int v64();
    virtual int v68();
    virtual int v6C();
    virtual int v70();
    virtual int v74();
    virtual int v78();
    virtual int v7C();
    virtual int v80();
    virtual int v84();
    virtual int v88();
    virtual int v8C();
    virtual int v90();
    virtual int v94(u32);
    virtual int v98();
    virtual int v9C();
    virtual int vA0();
    virtual int vA4();
    virtual int vA8();
    virtual int vAC();
    virtual void vB0(int);
    virtual int vB4();
    virtual int vB8();
    virtual int vBC();
    virtual int vC0();
    virtual void vC4(void*, void*);
    virtual int vC8();
    virtual int vCC();
    virtual void vD0(int);
    virtual void vD4(int);
    virtual int vD8();
    virtual int vDC();
    virtual int vE0();
    virtual int vE4(void*);
    virtual int vE8();
    virtual int vEC();
    virtual int vF0();
    virtual int vF4();
    virtual int vF8();
    virtual int vFC();
    int f4;      /* 0x04 */
    int f8;      /* 0x08 */
    int chan;    /* 0x0C */
    u32 flags;   /* 0x10 */
    int repDelay; /* 0x14 */
    int repRate;  /* 0x18 */
    int rumble;  /* 0x1C */
    u32 held;    /* 0x20 */
    u32 prev;    /* 0x24 */
    u32 press;   /* 0x28 */
    u32 repeat;  /* 0x2C */
    u32 raw;     /* 0x30 */
    u32 rawPrev; /* 0x34 */
    int f38;     /* 0x38 */
    int f3C;     /* 0x3C */
    int f40;     /* 0x40 */
    s16 axis[8]; /* 0x44: 0..3 at 44..4A, then 4C, 4E, 50, 52 */
    u32 flags2;  /* 0x54 */
    int f58;     /* 0x58 */
};


/* The PADStatus of the Revolution SDK */
struct PadStatus {
    u16 button;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerL;
    u8 triggerR;
    u8 analogA;
    u8 analogB;
    s8 err;
    u8 pad;
};

#endif
