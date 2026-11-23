/* EQUIVALENT (regs, round 19b): fn_800650DC: swaps the two chosen items of the item exchange screen, closes the gaps in both columns, recomputes which slots can be picked and moves the cursor to the nearest usable slot. */
#pragma use_lmw_stmw on
extern "C" {
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned int u32;
typedef int BOOL;
struct F { u32 f0; u32 flags; };
struct Item { void* p; u8 b4; u8 mark : 1; u8 b5 : 7; u8 rest[0x22]; };
struct Slot { s16 x, y; Item item; u8 enabled, pad[3]; };
struct O {
    u8 pad[0x28]; s16 state; u8 p2a[6]; void* a; void* b; s16 x38, x3a;
    s8 side, index, oldSide, oldIndex; u8 flag, phase, x42, mode, filter, x45, p46[2]; void* child;
};
extern Slot lbl_803CB4D0[2][7];
void fn_80111B34(Item*);
void fn_80111C24(Item*, int);
void fn_80111C78(Item*, Item*);
void fn_80110D38(Item*);
F* fn_801116B8(Item*);

/* Item with its constructor and destructor (fn_80111B34 / fn_80111C24) as a local object. */
struct ItemL : Item {
    ItemL() { fn_80111B34(this); }
    ~ItemL() { fn_80111C24(this, -1); }
};

static inline void compact(int row) {
    ItemL t[7];
    Item* q;
    Slot* p;
    int i, n, k;
    for (i = 0, q = t; i < 7; i++, q++) {
        fn_80110D38(q);
    }
    n = 0;
    for (i = 0; i < 7; i++) {
        if (lbl_803CB4D0[row][i].item.p) {
            fn_80111C78(&t[n++], &lbl_803CB4D0[row][i].item);
        }
        fn_80110D38(&lbl_803CB4D0[row][i].item);
    }
    for (k = 0, q = t, p = lbl_803CB4D0[row]; k < n; q++, p++, k++) {
        fn_80111C78(&p->item, q);
    }
}

void fn_800650DC(O* o) {
    Slot* row;
    Slot* p;
    int i, j, v;
    o->mode = 1;
    lbl_803CB4D0[o->side][o->index].item.mark = 0;
    lbl_803CB4D0[o->oldSide][o->oldIndex].item.mark = 0;
    ItemL tmp;
    fn_80111C78(&tmp, &lbl_803CB4D0[o->side][o->index].item);
    fn_80111C78(&lbl_803CB4D0[o->side][o->index].item, &lbl_803CB4D0[o->oldSide][o->oldIndex].item);
    fn_80111C78(&lbl_803CB4D0[o->oldSide][o->oldIndex].item, &tmp);
    compact(0);
    compact(1);
    for (i = 0, row = lbl_803CB4D0[0]; i < 2; i++, row += 7) {
        for (j = 0, p = row; j < 7; j++, p++) {
            if (o->filter) {
                v = 0;
                if (p->item.p) {
                    if (fn_801116B8(&p->item)->flags & 0x60) v = 1;
                }
                p->enabled = v;
            } else {
                p->enabled = p->item.p != 0;
            }
        }
    }
    {
        s8 side = o->oldSide;
        int k = o->oldIndex;
        Slot* s = &lbl_803CB4D0[side][k];
        for (;; s--, k--) {
            if (k < 0) break;
            if (s->enabled) break;
        }
        if (k >= 0) {
            o->side = side;
            o->index = k;
        }
    }
}
}
