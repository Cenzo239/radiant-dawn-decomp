#ifndef RP_SLOT_H
#define RP_SLOT_H
#include "game/rP_80105B04/rp.h"
/* Item data block pointed to by a slot. +0x38 holds a u64 of item flags. */
struct ItemD {
    u8 pad0[0x16];
    u16 icon;  /* 0x16 */
    u8 pad18[3];
    u8 maxUses; /* 0x1B */
    u8 pad1C[0x38 - 0x1C];
    u64 flags; /* 0x38 */
};
/* Inventory slot: the same layout as Inv (0x28 bytes) at Unit +0x1BC. */
struct Slot {
    ItemD* item; /* 0 */
    u8 uses;     /* 4 */
    u8 f80 : 1;  /* 5 */
    u8 f40 : 1;
    u8 f20 : 1;
    u8 f10 : 1;
    u8 f08 : 1;
    u8 f04 : 1;
    u8 f02 : 1;
    u8 f01 : 1;
};
struct IconBase { u8 d[0x44]; };
/* The icon font object (lbl_803E7290): data base, vptr at +0x44. */
class IconFont : public IconBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(int x, int y, int id);
    virtual void v5(int x, int y, int id, int a, int b, int c);
};
extern "C" {
extern u8 lbl_803E7290[];
extern u8 lbl_803E72D8[];
u64* fn_801116B8(Slot* s);
char* fn_80110F08(Slot* s);
u32 fn_80111074(Slot* s);
}
#define ICONS ((IconFont*)lbl_803E7290)
#define ICONS2 ((IconFont*)lbl_803E72D8)
#endif
