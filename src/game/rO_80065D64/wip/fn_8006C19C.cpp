/* fn_8006C19C: static initialiser of the choice/text box unit
   (fn_8006AA70.cpp). Hand-written stand-in, level `other`: 76 instructions
   against 77. Every store, the store order and the __construct_array call are
   the original's; the one missing instruction is `addi r27,r29,0`: the
   original addresses the pointer list at lbl_8037FA70 as "pool base + 0"
   because the unit's .data pool holds more objects (the vtables at +0x118,
   +0x1ac, +0x2dc, +0x370, +0x404), and it saves r20..r31 where this saves
   r21..r31.

   What the original source must look like (for the port):

       static Item itemA("....");            // lbl_804CB570, name lbl_804CA398, vtable lbl_8037FAD8
       static Item itemB("....");            // lbl_804CB578, name lbl_804CA390, vtable lbl_8037FA80
       static Item* const sList[] = { &itemA, &itemB, 0, 0 };     // lbl_8037FA70
       static MenuA m00(sList);              // lbl_803CB7B8+0x00, vtable lbl_8037FF60
       static MenuB m10(sList);              // +0x10, vtable lbl_8037FA70+0x404
       static MenuC m24(sList);              // +0x24, vtable +0x370
       static MenuD m38(sList);              // +0x38, vtable +0x2dc
       static MsgEnt sEnt[4];                // +0x50, constructor fn_8006C2D0
       static MsgEnt* sTab[6];               // +0x70
       static BoxA b88(sTab, 0, 0x46);       // +0x88, vtable +0x1ac
       static BoxB b98(sTab, 0, 0x46);       // +0x98, vtable +0x118

   All of the m.. and b.. classes derive from the base with vtable
   lbl_80383F28 (pointer at 0, vtable at 4); the items from the base with
   vtable lbl_8037FF08 (vtable at 0, pointer at 4).

   Port caveats: `VT(off)` stands for the five pooled vtables, and the o..
   statics are the objects above with their fields reduced to what the
   initialiser writes. Needs fn_8006C19C.symbols.json for the two pools. */
#include "game/rO_80065D64/types.h"
#pragma use_lmw_stmw on

struct PV { void* p; void* vt; };          /* pointer, then vtable */
struct VP { void* vt; void* p; };          /* vtable, then pointer */
struct PVH { void* p; void* vt; u8 pad[4]; s16 xc; s16 xe; };

extern "C" {
void fn_8028BFD8(void*, void*, void*, u32, u32);   /* __construct_array */
void fn_8006C2D0(void*);
extern u8 lbl_80383F28[];
extern u8 lbl_8037FA80[];
extern u8 lbl_8037FAD8[];
extern u8 lbl_8037FF08[];
extern u8 lbl_8037FF60[];
extern char lbl_804CA390[8];
extern char lbl_804CA398[8];
extern VP lbl_804CB570;
extern VP lbl_804CB578;


static VP* sList[4] = { &lbl_804CB570, &lbl_804CB578, 0, 0 };   /* lbl_8037FA70 */
#define VT(off) ((u8*)sList + (off))

struct Ent { void* vt; u32 x4; };
struct O10 { void* p; void* vt; u32 x8[2]; };
struct O14 { void* p; void* vt; u32 x8[3]; };
struct O18 { void* p; void* vt; u32 x8[4]; };
static O10 o00;         /* +0x00 */
static O14 o10;         /* +0x10 */
static O14 o24;         /* +0x24 */
static O18 o38;         /* +0x38 */
static Ent sEnt[4];     /* +0x50 */
static Ent* sTab[6];    /* +0x70 */
static PVH o88;         /* +0x88 */
static PVH o98;         /* +0x98 */

void fn_8006C19C(void) {
    lbl_804CB570.vt = lbl_8037FF08;
    lbl_804CB578.vt = lbl_8037FF08;
    o00.vt = lbl_80383F28;
    o10.vt = lbl_80383F28;
    o24.vt = lbl_80383F28;
    o38.vt = lbl_80383F28;
    lbl_804CB570.p = lbl_804CA398;
    lbl_804CB570.vt = lbl_8037FAD8;
    lbl_804CB578.p = lbl_804CA390;
    lbl_804CB578.vt = lbl_8037FA80;
    o00.p = sList;
    o00.vt = lbl_8037FF60;
    o10.p = sList;
    o10.vt = VT(0x404);
    o24.p = sList;
    o24.vt = VT(0x370);
    o38.p = sList;
    o38.vt = VT(0x2dc);
    fn_8028BFD8(sEnt, fn_8006C2D0, 0, 8, 4);
    o88.vt = lbl_80383F28;
    o98.vt = lbl_80383F28;
    o88.p = sTab;
    o88.vt = VT(0x1ac);
    o88.xc = 0;
    o88.xe = 0x46;
    o98.p = sTab;
    o98.xc = 0;
    o98.xe = 0x46;
    o98.vt = VT(0x118);
}
}
