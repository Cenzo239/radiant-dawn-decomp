/* Game heaps: a table of 16 named heaps, each a sorted free list of 32-byte-aligned blocks. */
#include "game/rJ_800799AC/types.h"

struct Heap;

#if TARGET_PC
/* Host: the heap keeps the Wii layout (32-byte block header, fn_80078484 walks it by
   raw offset), so the links are 32-bit window offsets. */
struct Block {
    u32 v0;
    u32 v4;
    FE10_P32(Block) prev;  /* 0x08 */
    FE10_P32(Block) next;  /* 0x0C */
    int size;     /* 0x10 negative before alloc means from the top */
    FE10_P32(Heap) heap;   /* 0x14 */
    u8 p18[8];
};

struct Heap {
    u32 magic;    /* 0x00 "HEAP" */
    char name[12]; /* 0x04 */
    FE10_P32(Heap) below;  /* 0x10 */
    FE10_P32(Block) used;  /* 0x14 */
    FE10_P32(Block) free;  /* 0x18 */
    u32 size;     /* 0x1C */
    u8 p20[0x2C - 0x20];
    u32 v2C;      /* 0x2C */
};
static_assert(sizeof(Block) == 0x20, "Block");
static_assert(sizeof(Heap) == 0x30, "Heap");

#else
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
#endif

extern "C" {

extern Heap* lbl_803CD868[16];
extern u8 lbl_803CD8A8[0x38];
extern u8* lbl_804CB5A0;
extern u8* lbl_804CB5A4;
extern Heap* lbl_804CB5A8;
extern Heap* lbl_804CB5AC;
extern Heap* lbl_804CB5B0;
#if TARGET_PC
FE10_PROTO extern unsigned int lbl_804CBF40;
#else
extern u32 lbl_804CBF40;
#endif
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
#if TARGET_PC
FE10_PROTO void* fn_8030E344(u32 h, u32 size, int align);
#else
void fn_8030E344(u32 h, u32 size, int align);
#endif
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
Block* fn_80077F98(Heap* h, int n) {
    u32 best;
    Block* b;
    u32 sz;
    Block* w;
    u32 rest;
    u32 size;
    Block* s;
    if (n < 0) {
        return fn_80078218(h, -n);
    }
    size = (n + 0x3F) & ~0x1F;
    BESTFIT(h, size, b)
    if (b == 0) {
        fn_8023FC18(heapIndex(h));
        BESTFIT(h, size, b)
        if (b == 0) {
            fn_8023F19C();
        }
    }
    rest = b->size - size;
    if (rest < 0x40) {
        UNLINK(h->free, b)
        b->heap = h;
    } else {
        b->size = size;
        s = (Block*)((u8*)b + size);
        b->heap = h;
        s->size = rest;
        s->prev = b->prev;
        s->next = b->next;
        if (s->next != 0) {
            s->next->prev = s;
        }
        if (s->prev != 0) {
            s->prev->next = s;
        } else {
            h->free = s;
        }
    }
    b->next = h->used;
    b->prev = 0;
    if (b->next != 0) {
        b->next->prev = b;
    }
    h->used = b;
    return b;
}

/* Allocate from the top */
Block* fn_80078218(Heap* h, int n) {
    Block* q;
    u32 best;
    u32 sz;
    Block* w;
    Block* b;
    u32 rest;
    u32 size;
    Block* t;
    Block* x;
    size = (n + 0x3F) & ~0x1F;
    BESTFIT(h, size, b)
    if (b == 0) {
        fn_8023FC18(heapIndex(h));
        BESTFIT(h, size, b)
        if (b == 0) {
            fn_8023F19C();
        }
    }
    rest = b->size - size;
    if (rest < 0x40) {
        UNLINK(h->free, b)
        b->heap = h;
    } else {
        b->size = rest;
        b = (Block*)((u8*)b + rest);
        b->size = -size;
        b->heap = h;
    }
    q = h->used;
    if (q != 0) {
        t = q;
    } else {
        t = b;
    }
    if (q != 0) {
        while ((x = q->next) != 0) {
            q = x;
        }
    }
    b->next = 0;
    b->prev = q;
    if (q != 0) {
        q->next = b;
    }
    h->used = t;
    return b;
}

void fn_800784E0(void) {
    fn_8031DD44(lbl_803CD8A8 + 4);
    lbl_804CB5A0 = (u8*)OSGetArenaLo();
    lbl_804CB5A4 = (u8*)OSGetArenaHi();
    lbl_804CB5A8 = 0;
    lbl_804CB5AC = 0;
    for (int i = 0; i < 16; i++) {
        lbl_803CD868[i] = 0;
    }
    fn_8031DE20(lbl_803CD8A8 + 4);
}

u32 fn_8007857C(void) {
    u8* lo;
    u8* hi;
    fn_8031DD44(lbl_803CD8A8 + 4);
    lo = lbl_804CB5A8 ? (u8*)lbl_804CB5A8 + lbl_804CB5A8->size : lbl_804CB5A0;
    hi = lbl_804CB5AC ? (u8*)lbl_804CB5AC : lbl_804CB5A4;
    fn_8031DE20(lbl_803CD8A8 + 4);
    return hi - lo;
}

void fn_80078C2C(const char* name) {
    int i;
    Heap** p;
    fn_8031DD44(lbl_803CD8A8 + 4);
    p = lbl_803CD868;
    for (i = 0; i < 16; i++) {
        Heap* h = *p;
        if (h != 0 && fn_80291188(name, h->name) == 0) {
            lbl_804CB5B0 = h;
        }
        p++;
    }
    fn_8031DE20(lbl_803CD8A8 + 4);
}

#define h ((Heap*)p)
void fn_80078E24(void* p) {
    Block* b;
    Block* t;
    Block* q;
    Block* head;
    Block* q2;
    Block* t2;
    Block* head2;
    if (p != 0) {
        fn_8031DD44(lbl_803CD8A8 + 4);
        b = (Block*)p - 1;
        p = ((Block*)p - 1)->heap;
        fn_80078484(h);
        if (b->size < 0) {
            b->size = -b->size;
            UNLINK(h->used, b)
            head = h->free;
            t = head;
            q = 0;
            while (t != 0) {
                q = t;
                t = t->next;
            }
            for (; q != 0; q = q->prev) {
                if (q <= b) {
                    break;
                }
                t = q;
            }
            b->next = t;
            b->prev = q;
            if (t != 0) {
                t->prev = b;
                if ((u8*)b + b->size == (u8*)t) {
                    b->size += t->size;
                    t = t->next;
                    b->next = t;
                    if (t != 0) {
                        t->prev = b;
                    }
                }
            }
            if (q != 0) {
                q->next = b;
                if ((u8*)q + q->size == (u8*)b) {
                    q->size += b->size;
                    q->next = t;
                    if (t != 0) {
                        t->prev = q;
                    }
                }
            } else {
                head = b;
            }
            h->free = head;
        } else {
            UNLINK(h->used, b)
            head2 = h->free;
            q2 = 0;
            for (t2 = head2; t2 != 0; t2 = t2->next) {
                if (b <= t2) {
                    break;
                }
                q2 = t2;
            }
            b->next = t2;
            b->prev = q2;
            if (t2 != 0) {
                t2->prev = b;
                if ((u8*)b + b->size == (u8*)t2) {
                    b->size += t2->size;
                    t2 = t2->next;
                    b->next = t2;
                    if (t2 != 0) {
                        t2->prev = b;
                    }
                }
            }
            if (q2 != 0) {
                q2->next = b;
                if ((u8*)q2 + q2->size == (u8*)b) {
                    q2->size += b->size;
                    q2->next = t2;
                    if (t2 != 0) {
                        t2->prev = q2;
                    }
                }
            } else {
                head2 = b;
            }
            h->free = head2;
        }
        fn_8031DE20(lbl_803CD8A8 + 4);
    }
}
#undef h

void* fn_80079150(u32 n) {
    Block* b;
    fn_8031DD44(lbl_803CD8A8 + 4);
    b = fn_80077F98(lbl_803CD868[0], n);
    fn_8031DE20(lbl_803CD8A8 + 4);
    return b + 1;
}

void* fn_800791B0(u32 n) {
    Block* b;
    fn_8031DD44(lbl_803CD8A8 + 4);
    b = fn_80077F98(lbl_803CD868[0], n);
    fn_8031DE20(lbl_803CD8A8 + 4);
    return b + 1;
}

void fn_80079210(void* p) {
    Block* t2;
    Heap* h;
    Block* q;
    Block* t;
    Block* q2;
    Block* head2;
    Block* b;
    Block* head;
    if (p != 0) {
        fn_8031DD44(lbl_803CD8A8 + 4);
        b = (Block*)p - 1;
        h = b->heap;
        fn_80078484(h);
        if (b->size < 0) {
            b->size = -b->size;
            UNLINK(h->used, b)
            head = h->free;
            t = head;
            q = 0;
            while (t != 0) {
                q = t;
                t = t->next;
            }
            for (; q != 0; q = q->prev) {
                if (q <= b) {
                    break;
                }
                t = q;
            }
            b->next = t;
            b->prev = q;
            if (t != 0) {
                t->prev = b;
                if ((u8*)b + b->size == (u8*)t) {
                    b->size += t->size;
                    t = t->next;
                    b->next = t;
                    if (t != 0) {
                        t->prev = b;
                    }
                }
            }
            if (q != 0) {
                q->next = b;
                if ((u8*)q + q->size == (u8*)b) {
                    q->size += b->size;
                    q->next = t;
                    if (t != 0) {
                        t->prev = q;
                    }
                }
            } else {
                head = b;
            }
            h->free = head;
        } else {
            UNLINK(h->used, b)
            head2 = h->free;
            q2 = 0;
            for (t2 = head2; t2 != 0; t2 = t2->next) {
                if (b <= t2) {
                    break;
                }
                q2 = t2;
            }
            b->next = t2;
            b->prev = q2;
            if (t2 != 0) {
                t2->prev = b;
                if ((u8*)b + b->size == (u8*)t2) {
                    b->size += t2->size;
                    t2 = t2->next;
                    b->next = t2;
                    if (t2 != 0) {
                        t2->prev = b;
                    }
                }
            }
            if (q2 != 0) {
                q2->next = b;
                if ((u8*)q2 + q2->size == (u8*)b) {
                    q2->size += b->size;
                    q2->next = t2;
                    if (t2 != 0) {
                        t2->prev = q2;
                    }
                }
            } else {
                head2 = b;
            }
            h->free = head2;
        }
        fn_8031DE20(lbl_803CD8A8 + 4);
    }
}

void fn_80079474(void* p) {
    Block* t2;
    Heap* h;
    Block* q;
    Block* t;
    Block* q2;
    Block* head2;
    Block* b;
    Block* head;
    if (p != 0) {
        fn_8031DD44(lbl_803CD8A8 + 4);
        b = (Block*)p - 1;
        h = b->heap;
        fn_80078484(h);
        if (b->size < 0) {
            b->size = -b->size;
            UNLINK(h->used, b)
            head = h->free;
            t = head;
            q = 0;
            while (t != 0) {
                q = t;
                t = t->next;
            }
            for (; q != 0; q = q->prev) {
                if (q <= b) {
                    break;
                }
                t = q;
            }
            b->next = t;
            b->prev = q;
            if (t != 0) {
                t->prev = b;
                if ((u8*)b + b->size == (u8*)t) {
                    b->size += t->size;
                    t = t->next;
                    b->next = t;
                    if (t != 0) {
                        t->prev = b;
                    }
                }
            }
            if (q != 0) {
                q->next = b;
                if ((u8*)q + q->size == (u8*)b) {
                    q->size += b->size;
                    q->next = t;
                    if (t != 0) {
                        t->prev = q;
                    }
                }
            } else {
                head = b;
            }
            h->free = head;
        } else {
            UNLINK(h->used, b)
            head2 = h->free;
            q2 = 0;
            for (t2 = head2; t2 != 0; t2 = t2->next) {
                if (b <= t2) {
                    break;
                }
                q2 = t2;
            }
            b->next = t2;
            b->prev = q2;
            if (t2 != 0) {
                t2->prev = b;
                if ((u8*)b + b->size == (u8*)t2) {
                    b->size += t2->size;
                    t2 = t2->next;
                    b->next = t2;
                    if (t2 != 0) {
                        t2->prev = b;
                    }
                }
            }
            if (q2 != 0) {
                q2->next = b;
                if ((u8*)q2 + q2->size == (u8*)b) {
                    q2->size += b->size;
                    q2->next = t2;
                    if (t2 != 0) {
                        t2->prev = q2;
                    }
                }
            } else {
                head2 = b;
            }
            h->free = head2;
        }
        fn_8031DE20(lbl_803CD8A8 + 4);
    }
}

#define h ((Heap*)p)
void fn_800796D8(void* p) {
    Block* b;
    Block* t;
    Block* q;
    Block* head;
    Block* q2;
    Block* t2;
    Block* head2;
    if (p != 0) {
        if (p != 0) {
        fn_8031DD44(lbl_803CD8A8 + 4);
        b = (Block*)p - 1;
        p = ((Block*)p - 1)->heap;
        fn_80078484(h);
        if (b->size < 0) {
            b->size = -b->size;
            UNLINK(h->used, b)
            head = h->free;
            t = head;
            q = 0;
            while (t != 0) {
                q = t;
                t = t->next;
            }
            for (; q != 0; q = q->prev) {
                if (q <= b) {
                    break;
                }
                t = q;
            }
            b->next = t;
            b->prev = q;
            if (t != 0) {
                t->prev = b;
                if ((u8*)b + b->size == (u8*)t) {
                    b->size += t->size;
                    t = t->next;
                    b->next = t;
                    if (t != 0) {
                        t->prev = b;
                    }
                }
            }
            if (q != 0) {
                q->next = b;
                if ((u8*)q + q->size == (u8*)b) {
                    q->size += b->size;
                    q->next = t;
                    if (t != 0) {
                        t->prev = q;
                    }
                }
            } else {
                head = b;
            }
            h->free = head;
        } else {
            UNLINK(h->used, b)
            head2 = h->free;
            q2 = 0;
            for (t2 = head2; t2 != 0; t2 = t2->next) {
                if (b <= t2) {
                    break;
                }
                q2 = t2;
            }
            b->next = t2;
            b->prev = q2;
            if (t2 != 0) {
                t2->prev = b;
                if ((u8*)b + b->size == (u8*)t2) {
                    b->size += t2->size;
                    t2 = t2->next;
                    b->next = t2;
                    if (t2 != 0) {
                        t2->prev = b;
                    }
                }
            }
            if (q2 != 0) {
                q2->next = b;
                if ((u8*)q2 + q2->size == (u8*)b) {
                    q2->size += b->size;
                    q2->next = t2;
                    if (t2 != 0) {
                        t2->prev = q2;
                    }
                }
            } else {
                head2 = b;
            }
            h->free = head2;
        }
        fn_8031DE20(lbl_803CD8A8 + 4);
        }
    }
}
#undef h

void
#if TARGET_PC
*
#endif
fn_80079958(u32 size, u32 align) {
    size = (size + 0x1F) & ~0x1F;
    align = (align + 0x1F) & ~0x1F;
#if TARGET_PC
    return fn_8030E344(lbl_804CBF40, size, -align);
#else
    fn_8030E344(lbl_804CBF40, size, -align);
#endif
}

void fn_80079978(void* p) {
    if (p != 0) {
        fn_8030E3F4(lbl_804CBF40, p);
    }
}

}
