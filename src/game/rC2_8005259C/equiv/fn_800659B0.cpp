/*
 * fn_800659B0 (round 22, `regs`: 21 words, all register choice; symcheck --anon --xargs: 58 blocks,
 * 0 differ). Start of the trade screen's alternative entry: same body as fn_800656BC
 * (auto/80060000/wip/fn_800656BC.cpp) with the cursor position passed in.
 *   parent: parent proc; x45: stored at proc+0x45; side/index: initial cursor (side < 0: none, then the
 *   cursor goes to the first usable slot and the proc starts at label 0 instead of jumping to label 1).
 * Fills the two 7-slot columns lbl_803CB4D0[2][7] (0x30 bytes each: position, copied item slot from
 * unit+0x1BC+i*0x28, enabled flag) for the two units in lbl_803CA870, creates the help panel, and,
 * when a side is given, refreshes the flags again and jumps to label 1.
 * What differs: the slot counter and the "enabled" temporary of the first RefreshSlots copy swap
 * r24/r31, and the second copy uses another register assignment (r27/r24/r31/r25/r26 in the original).
 * Local declaration orders were searched (main function and inline), best is this one.
 */
#include "game/rC2_8005259C/base.h"
#pragma use_lmw_stmw on

struct Unit;
struct ItemE;
struct FSlot { ItemE* item; u8 rest[0x24]; };
struct Flags2 { u32 h, l; };
struct Proc;
struct Panel;

/* one cell of the two 7-slot item columns of the trade screen */
struct TradeSlot {
    s16 x, y;      /* 0x00: screen position */
    FSlot item;    /* 0x04 */
    u8 enabled;    /* 0x2C */
    u8 pad[3];
};

struct TradeProc {
    u8 pad0[0x30];
    Unit* a;       /* 0x30: left unit */
    Unit* b;       /* 0x34: right unit */
    s16 x38, x3a;  /* 0x38 */
    u8 side;       /* 0x3C */
    s8 index;      /* 0x3D */
    u8 oldSide;    /* 0x3E */
    u8 oldIndex;   /* 0x3F */
    u8 flag;       /* 0x40 */
    u8 phase;      /* 0x41 */
    u8 x42;        /* 0x42 */
    u8 mode;       /* 0x43 */
    u8 filter;     /* 0x44 */
    u8 x45;        /* 0x45 */
    u8 p46[2];
    Panel* child;  /* 0x48 */
};

struct Context { Unit* a; Unit* b; u8 pad8[0x128]; };

extern "C" {
extern TradeSlot lbl_803CB4D0[2][7];
extern Context lbl_803CA870;
extern u8 lbl_803CAB38[];
extern u8 lbl_8037F870[];
extern char lbl_8037F8E4[];
extern char lbl_804CA380[8];
Proc* fn_80081194(void* script, Proc* parent);
FSlot* fn_80111C78(FSlot* d, FSlot* s);
void fn_8012CAD8(Unit* u);
Flags2* fn_801116B8(FSlot* s);
void fn_80193054(void);
void* fn_80078CCC(int size, const char* file, int line);
Panel* fn_8017AA08(Panel* p);
void fn_8017A9F8(Panel* p, f32 a, f32 b, f32 c);
void fn_8017A968(Panel* p, const char* name);
void fn_80083DC4(Proc* p, int label);
}

static inline void RefreshSlots(TradeProc* o)
{
    u8 e;
    TradeSlot* p;
    int j;
    TradeSlot* row;
    int i;
    row = lbl_803CB4D0[0];
    for (i = 0; i < 2; i++, row += 7) {
        p = row;
        for (j = 0; j < 7; j++, p++) {
            if (o->filter) {
                e = 0;
                if (p->item.item && (fn_801116B8(&p->item)->l & 0x60)) {
                    e = 1;
                }
                p->enabled = e;
            } else {
                p->enabled = p->item.item != 0;
            }
        }
    }
}

static inline int FirstEnabled(int side)
{
    TradeSlot* p = lbl_803CB4D0[0];
    int i = 0;
    for (;; p++, i++) {
        if (i >= 7) {
            i = -1;
            break;
        }
        if (p[side * 7].enabled) {
            break;
        }
    }
    return i;
}

extern "C" void fn_800659B0(Proc* parent, u8 x45, s8 side, s8 index)
{
    TradeSlot* p;
    int i;
    int j;
    int x;
    TradeSlot* row2;
    TradeSlot* p2;
    TradeSlot* row;
    TradeProc* o;
    int y;
    int off;
    Panel* m;
    o = (TradeProc*)fn_80081194(lbl_8037F870, parent);
    Unit* ua = lbl_803CA870.a;
    Unit* ub = lbl_803CA870.b;
    o->a = ua;
    o->b = ub;
    o->x3a = -1;
    o->x38 = -1;
    o->mode = 0;
    o->flag = 0;
    row = lbl_803CB4D0[0];
    x = 0x26;
    for (i = 0; i < 2; i++, row += 7) {
        p = row;
        j = 0;
        y = 0x77;
        off = 0;
        for (; j < 7; j++, p++, y += 0x1c, off += 0x28) {
            p->x = x;
            p->y = y;
            if (i) {
                p->x += 0x12a;
            }
            if (i) {
                fn_80111C78(&p->item, (FSlot*)((u8*)o->b + off + 0x1bc));
            } else {
                fn_80111C78(&p->item, (FSlot*)((u8*)o->a + off + 0x1bc));
            }
        }
    }
    o->filter = 0;
    fn_8012CAD8(o->a);
    fn_8012CAD8(o->b);
    RefreshSlots(o);
    o->side = 0;
    o->index = FirstEnabled(0);
    if (o->index < 0) {
        o->side = 1;
        o->index = FirstEnabled(1);
    }
    o->oldSide = 0;
    o->oldIndex = 0;
    fn_80193054();
    lbl_803CAB38[0x92c] = 15;
    m = (Panel*)fn_80078CCC(0x30, lbl_804CA380, 0);
    if (m) {
        m = fn_8017AA08(m);
    }
    o->child = m;
    fn_8017A9F8(m, 0.0f, 400.0f, 100.0f);
    fn_8017A968(o->child, lbl_8037F8E4);
    o->phase = 1;
    o->x45 = x45;
    o->x42 = 1;
    if (side >= 0) {
        o->phase = 0;
        o->flag = 0;
        RefreshSlots(o);
        o->side = side;
        o->index = index;
        fn_80083DC4((Proc*)o, 1);
    }
}
