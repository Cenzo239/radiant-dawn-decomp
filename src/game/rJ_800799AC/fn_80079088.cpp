/* Game heaps: size of the largest free block of heap h (the current heap when h < 0),
 * minus the block header. Types as in fn_80077F98.cpp. */
#include "game/rJ_800799AC/types.h"

struct Heap;
struct Block {
    u32 v0;
    u32 v4;
    Block* prev;  /* 0x08 */
    Block* next;  /* 0x0C */
    u32 size;     /* 0x10 */
    Heap* heap;   /* 0x14 */
    u8 p18[8];
};
struct Heap {
    u32 magic;
    char name[12];
    Heap* below;  /* 0x10 */
    Block* used;  /* 0x14 */
    Block* free;  /* 0x18 */
    u32 size;     /* 0x1C */
};

extern "C" {
extern Heap* lbl_803CD868[16];
extern u8 lbl_803CD8A8[0x38];
extern Heap* lbl_804CB5B0;
void fn_8031DD44(void* m);
void fn_8031DE20(void* m);

static inline u32 largest(Heap* h) {
    Block* b;
    u32 best = 0;
    for (b = h->free; b != 0; b = b->next) {
        if (b->size >= best) {
            best = b->size;
        }
    }
    return best - 0x20;
}

u32 fn_80079088(int h) {
    u32 r;
    fn_8031DD44(lbl_803CD8A8 + 4);
    if (h < 0) {
        r = largest(lbl_804CB5B0);
    } else {
        r = largest(lbl_803CD868[h]);
    }
    fn_8031DE20(lbl_803CD8A8 + 4);
    return r;
}
}
