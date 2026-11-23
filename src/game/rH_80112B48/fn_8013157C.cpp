/*
 * fn_8013157C (round 22, exact; check with --symbol-map fn_8013157C.symbols.json).
 *
 * This is the compiler-generated static initialiser (__sinit) of the file that defines three static
 * camera objects. In the original source they are something like
 *
 *     struct CamBase { ...0x6C bytes...; virtual ... };      // vptr at +0x6C, own vtable
 *     struct CamA : CamBase { ... };                          // 0x70 bytes, vtable lbl_80385ED8
 *     struct CamB : CamBase { u32 x70; ... };                 // 0x74 bytes, vtable lbl_80385EB8
 *     struct CamC : CamBase { u32 x70; ... };                 // 0x74 bytes, vtable lbl_80385E98
 *     static CamA s0; static CamB s1; static CamC s2;         // lbl_804133B8, +0x70, lbl_8041349C
 *
 * Written with those real classes (see wip/r17_fn_8013157C.cpp) the compiler emits a byte-identical
 * function, but under the name `__sinit_...cpp`, which the checker cannot credit. This file writes the
 * same constructor calls by hand as inlines over three pooled file statics, so the function carries
 * the symbols.txt name.
 *
 * Why it matches: the base constructor's vtable store must be there and then die. Without it (only the
 * final vtable stores, as tried in round 17) the register assignment comes out reversed (13 words).
 * The base class's own vtable no longer exists in the DOL (nothing references it after the dead
 * store is removed), so `Base` stores 0 here; the store is eliminated either way and emits nothing.
 *
 * Port: define the three objects as real globals of real classes and drop this function; the vtable
 * pointers are the only state it sets (all other bytes are .bss zero).
 */
#include "game/rH_80112B48/types.h"

extern "C" {

struct Cam {
    u8 pad[0x6c];
    void* vt; /* 0x6C */
};

struct Cam2 {
    u8 pad[0x6c];
    void* vt;     /* 0x6C */
    u8 pad70[4];  /* 0x70 */
};

extern u8 lbl_80385E98[]; /* vtable of the third camera class */
extern u8 lbl_80385EB8[]; /* vtable of the second camera class */
extern u8 lbl_80385ED8[]; /* vtable of the first camera class */

/* ...bss.0 = lbl_804133B8 (s0 at +0, s1 at +0x70), s2 at +0xE4 = lbl_8041349C */
static Cam s0;
static Cam2 s1;
static Cam2 s2;

/* base constructor: stores the base vtable, overwritten at once by the derived constructor */
static inline Cam* Base(void* o)
{
    ((Cam*)o)->vt = 0;
    return (Cam*)o;
}

static inline Cam* CtorA(Cam* o)
{
    Base(o);
    o->vt = lbl_80385ED8;
    return o;
}

static inline Cam2* CtorB(Cam2* o)
{
    Base(o);
    o->vt = lbl_80385EB8;
    return o;
}

static inline Cam2* CtorC(Cam2* o)
{
    Base(o);
    o->vt = lbl_80385E98;
    return o;
}

void fn_8013157C(void)
{
    CtorA(&s0);
    CtorB(&s1);
    CtorC(&s2);
}

}
