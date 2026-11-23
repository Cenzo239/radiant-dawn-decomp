#ifndef RD_8008E3B4_SCRIPT_H
#define RD_8008E3B4_SCRIPT_H

/* Shared declarations for the script command files (0x80092D04..). */

#include "game/rD_8008E3B4/types.h"

extern "C" {

/* Pointer sanity check used by every command that takes a string or object. */
#define IsValidPtr(p) \
    (((u32)(p) >= 0x80000000 && (u32)(p) < 0x81800000) || ((u32)(p) >= 0x90000000 && (u32)(p) < 0x98000000))

extern u32 lbl_804CB700;     /* script run flags: 0x8001 = skipping, 1 = mute */
extern u8* lbl_804CB810;     /* unit array */
extern u8* lbl_804CB814;     /* army list heads */
extern u8 lbl_803E5064[0x24];
extern u8 lbl_803EC898[];    /* map */
extern char lbl_80363B74[];  /* string pool */

void* fn_8009E898(void);
void* fn_80081050(void* cls, void* parent);
void* fn_80081194(void* cls, void* parent);
void fn_80083B78(void* proc);
u8* fn_800C3558(void);
#if TARGET_PC
FE10_PROTO struct Proc * fn_80085708(const char* name);
#else
int fn_80085708(const char* name);
#endif
void* fn_8010B228(void* x);

static inline u8* GetUnit(u8 id)
{
    if (id != 0) {
        return lbl_804CB810 + (id - 1) * 0x3f0;
    }
    return NULL;
}

/* An inline setter keeps the constant 1 out of a callee-saved register. */
static inline void setFlag1C(u8* p)
{
    p[0x1c] = 1;
}

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
} Vec;

}

#endif
