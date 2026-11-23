/* fn_8004288C: static initialiser of the unit at 0x80042914. Level: sched
   (needs fn_8004288C.symbols.json: "...bss.0" = lbl_803CA720). Hand-written
   stand-in for the compiler's __sinit of roughly

       static NameObj a(...);       // lbl_804CB188, vtable lbl_80379E44 at +4
       static NameObj b(...);       // lbl_804CB190, vtable lbl_80379E10 at +4
       static ObjA sObjA;           // lbl_803CA720+0xa0, vtable lbl_80379888 at +4
       static ObjB sObjB;           // +0xb8, vtable lbl_80379DD8 at +4
       static Item sItem;           // +0xe0, ctor fn_80111B34, dtor fn_80111C24

   One block before the first call: the four vtable stores are in the
   original's order; the lis/addi/li lines that form the addresses are
   interleaved differently and use other volatile registers. symcheck --anon:
   3 blocks, 0 differ.
   Port caveats: sHead stands for the 0xa0 bytes of statics of this unit that
   the initialiser does not touch; sChain is the compiler's destructor-chain
   record. Use real static objects. */
#include "game/rB_8002E1C4/types.h"

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

static u8 sHead[0xa0];      /* +0x00: statics of the unit not touched here */
static Obj18 sObjA;         /* +0xa0 */
static Obj18 sObjB;         /* +0xb8 */
static u32 sChain[4];       /* +0xd0 */
static SItem sItem;          /* +0xe0 */

void fn_8004288C(void) {
    lbl_804CB190.vt = lbl_80379E10;
    lbl_804CB188.vt = lbl_80379E44;
    sObjA.vt = lbl_80379888;
    sObjB.vt = lbl_80379DD8;
    fn_80111B34(&sItem);
    __register_global_object(&sItem, fn_80111C24, sChain);
}
}
