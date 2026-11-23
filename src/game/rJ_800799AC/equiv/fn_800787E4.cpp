/* fn_800787E4: functionally equal (regs level per tools/check_regs.py; registers differ from the original). Heap table dump/sort. From wip/fn_800785FC.cpp. */
/* Game heaps: a table of 16 named heaps, each a sorted free list of 32-byte-aligned blocks. */
#include "game/rJ_800799AC/types.h"

struct Heap;

struct Block {
    u32 v0;
    u32 v4;
    Block* prev;  /* 0x08 */
    Block* next;  /* 0x0C */
    int size;     /* 0x10 negative before alloc means from the top */
    Heap* heap;   /* 0x14 */
    u8 p18[8];
};

struct Heap {
    u32 magic;    /* 0x00 "HEAP" */
    char name[12]; /* 0x04 */
    Heap* below;  /* 0x10 */
    Block* used;  /* 0x14 */
    Block* free;  /* 0x18 */
    u32 size;     /* 0x1C */
    u8 p20[0x2C - 0x20];
    u32 v2C;      /* 0x2C */
};

extern "C" {

extern Heap* lbl_803CD868[16];
extern u8 lbl_803CD8A8[0x38];
extern u8* lbl_804CB5A0;
extern u8* lbl_804CB5A4;
extern Heap* lbl_804CB5A8;
extern Heap* lbl_804CB5AC;
extern Heap* lbl_804CB5B0;
extern u32 lbl_804CBF40;
void fn_8031DD44(void* m);
void fn_8031DE20(void* m);
void* OSGetArenaLo(void);
void* OSGetArenaHi(void);
void fn_8023FC18(int i);
void fn_8023F19C(void);
void fn_8023FBEC(int i);
void fn_8023F7B0(int i);
int fn_8023FBF4(void);
void fn_800C7B14(void* p, u32 n);
void fn_80078484(Heap* h);
char* fn_802910CC(char* d, const char* s, int n);
int fn_80291188(const char* a, const char* b);
void fn_8030E344(u32 h, u32 size, int align);
void fn_8030E3F4(u32 h, void* p);
Block* fn_80078218(Heap* h, int size);

static inline int heapIndex(Heap* h) {
    Heap** p = lbl_803CD868;
    int r = -1;
    int i;
    for (i = 0; i < 16; i++) {
        if (*p == h) {
            r = i;
            break;
        }
        p++;
    }
    return r;
}

#define BESTFIT(H, SIZE, R) \
    best = 0x7FFFFFFF; \
    R = 0; \
    for (w = H->free; w != 0; w = w->next) { \
        sz = w->size; if (sz <= best && sz >= SIZE) { \
            best = sz; \
            R = w; \
        } \
    }

static inline Block* unlink(Block* head, Block* b) {
    if (b->next != 0) {
        b->next->prev = b->prev;
    }
    if (b->prev != 0) {
        b->prev->next = b->next;
    } else {
        head = b->next;
    }
    return head;
}

#define UNLINK(list, b) list = unlink(list, b);

/* Allocate from the bottom */
Block* fn_80077F98(Heap* h, int n);

/* Allocate from the top */
Block* fn_80078218(Heap* h, int n);

void fn_800784E0(void);

u32 fn_8007857C(void);

void fn_80078C2C(const char* name);

#define h ((Heap*)p)
void fn_80078E24(void* p);
#undef h

void* fn_80079150(u32 n);

void* fn_800791B0(u32 n);

void fn_80079210(void* p);

void fn_80079474(void* p);

#define h ((Heap*)p)
void fn_800796D8(void* p);
#undef h

void fn_80079958(u32 size, u32 align);

void fn_80079978(void* p);

}


/* ---- fn_800787E4 ---- */
extern "C" {
void fn_800787E4(void) {
    int i;
    int j;
    BOOL cur;
    Heap* h;
    Heap* n;
    fn_8031DD44(lbl_803CD8A8 + 4);
    i = heapIndex(lbl_804CB5A8);
    j = heapIndex(lbl_804CB5B0);
    lbl_804CB5A8 = lbl_804CB5A8->below;
    h = lbl_803CD868[i];
    cur = i == j;
    fn_800C7B14(h, h->size);
    fn_8023F7B0(heapIndex(h));
    n = lbl_804CB5A8;
    lbl_803CD868[i] = 0;
    if (n != 0) {
        j = heapIndex(n);
        if (cur) {
            lbl_804CB5B0 = lbl_803CD868[j];
            fn_8023FBEC(j);
        }
    }
    fn_8031DE20(lbl_803CD8A8 + 4);
}
}
