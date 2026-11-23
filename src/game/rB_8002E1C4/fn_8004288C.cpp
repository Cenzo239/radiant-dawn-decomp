/* fn_8004288C: static initialiser of the unit at 0x80042914. Round m1, exact
   (check with --symbol-map fn_8004288C.symbols.json: "...bss.0" = lbl_803CA720).
   Hand-written stand-in for the compiler's __sinit of roughly

       static A a;                  // lbl_804CB188, vtable lbl_80379E44 at +4
       static B b;                  // lbl_804CB190, B : A, vtable lbl_80379E10 at +4
       static ObjA sObjA;           // lbl_803CA720+0xa0, vtable lbl_80379888 at +4
       static ObjB sObjB;           // +0xb8, vtable lbl_80379DD8 at +4
       static Item sItem;           // +0xe0, ctor fn_80111B34, dtor fn_80111C24

   What made it exact (from equiv/fn_8004288C.cpp, sched): every constructor
   first runs a base constructor whose vtable store dies, and the class at
   lbl_804CB190 derives from the class at lbl_804CB188 (its constructor runs
   A's constructor, storing lbl_80379E44, before its own store).
   The 0xa0 bytes in front of sObjA are the state objects of fn_8003CD54 ..
   fn_8003DCAC, defined once for the unit in statefn_bss.h. Port caveat: sChain
   is the compiler's destructor-chain record. Use real static objects. */
#include "game/rB_8002E1C4/statefn_bss.h"

struct VP { void* p; void* vt; };
struct Obj18 { void* x0; void* vt; u32 x8[4]; };
struct SItem { u8 b[0x28]; };

extern "C" {
void __register_global_object(void* o, void* dtor, void* chain);
void fn_80111B34(void*);
void fn_80111C24(void*, int);
extern u8 lbl_80379E44[];
extern u8 lbl_80379E10[];
extern u8 lbl_80379888[];
extern u8 lbl_80379DD8[];
extern VP lbl_804CB188;
extern VP lbl_804CB190;

static Obj18 sObjA;         /* +0xa0 (after statefn_bss.h's objects) */
static Obj18 sObjB;         /* +0xb8 */
static u32 sChain[4];       /* +0xd0 */
static SItem sItem;          /* +0xe0 */

/* base constructor: its vtable store dies at once (see fn_8013157C) */
static inline void* Base(void* o){ ((VP*)o)->vt = 0; return o; }
static inline VP* Ctor188(VP* p){ Base(p); p->vt = lbl_80379E44; return p; }
static inline VP* Ctor190(VP* p){ Ctor188(p); p->vt = lbl_80379E10; return p; }
static inline Obj18* CtorObj(Obj18* p, void* v){ Base(p); p->vt = v; return p; }
void fn_8004288C(void) {
    Ctor188(&lbl_804CB188);
    Ctor190(&lbl_804CB190);
    CtorObj(&sObjA, lbl_80379888);
    CtorObj(&sObjB, lbl_80379DD8);
    fn_80111B34(&sItem);
    __register_global_object(&sItem, fn_80111C24, sChain);
}
}
