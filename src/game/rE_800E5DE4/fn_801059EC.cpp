/* fn_801059EC: static initialiser of the item/save unit that starts at
   fn_80105B04 (rP_80105B04). Round 21, exact (needs fn_801059EC.symbols.json:
   "...bss.0" = lbl_803E8FF0). Hand-written; the original is the compiler's
   __sinit for roughly

       static FixedArray<Item, 16> sObj;        // lbl_803E8FF0+0x10, destructor fn_80105B04
       static Something sObj2;                  // +0x298 (12 bytes, zeroed), destructor fn_80105B6C
       static Item sPool[300];                  // +0x2b0, Item ctor fn_80111B34, dtor fn_80111C24
       Span all   = { 300, sPool };             // lbl_804CB750
       Span a     = { 100, sPool };             // lbl_804CB758
       Span b     = { 100, sPool + 100 };       // lbl_804CB760
       Span c     = { 100, sPool + 200 };       // lbl_804CB768
       Span bc    = { 200, sPool + 100 };       // lbl_804CB770

   Port caveats: sChainA/sChainB are the compiler's destructor-chain records
   (use real static objects instead); the local `ca` only fixes the order of
   the pooled statics; __register_global_object is called with object 0 for
   the second record exactly as the original does. */
#include "game/rE_800E5DE4/types.h"

struct Item { u8 b[0x28]; };
struct Arr16 { int n; Item* p; Item a[16]; };
struct Span { int n; Item* p; };

extern "C" {
void fn_8028BFD8(void*, void*, void*, u32, u32);   /* __construct_array */
void __register_global_object(void* o, void* dtor, void* chain);
void* memset(void*, int, u32);
void fn_80111B34(void*);
void fn_80111C24(void*, int);
void fn_80105B04(void*, int);
void fn_80105B6C(void*, int);
extern Span lbl_804CB750;
extern Span lbl_804CB758;
extern Span lbl_804CB760;
extern Span lbl_804CB768;
extern Span lbl_804CB770;

static u32 sChainA[4];      /* +0x000 */
static Arr16 sObj;          /* +0x010 */
static u32 sObj2[3];        /* +0x298 */
static u32 sChainB[3];      /* +0x2a4 */
static Item sPool[300];     /* +0x2b0 */

void fn_801059EC(void) {
    void* ca = sChainA;
    sObj.n = 0x10;
    sObj.p = sObj.a;
    fn_8028BFD8(sObj.a, fn_80111B34, fn_80111C24, 0x28, 0x10);
    __register_global_object(&sObj, fn_80105B04, ca);
    memset(sObj2, 0, 0xc);
    fn_8028BFD8(sPool, fn_80111B34, fn_80111C24, 0x28, 300);
    __register_global_object(0, fn_80105B6C, sChainB);
    lbl_804CB750.n = 300;
    lbl_804CB750.p = sPool;
    lbl_804CB758.n = 100;
    lbl_804CB758.p = sPool;
    lbl_804CB760.n = 100;
    lbl_804CB760.p = sPool + 100;
    lbl_804CB768.n = 100;
    lbl_804CB768.p = sPool + 200;
    lbl_804CB770.n = 200;
    lbl_804CB770.p = sPool + 100;
}
}
