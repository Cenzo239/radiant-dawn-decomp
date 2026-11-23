/* fn_80075AC0: exact (round m10). Registers the symbols of a named data file once.
 * Lever: the end of the header block is integer arithmetic in a named local,
 * `u32 q = (u32)h + (h->size & ~3); u32* keys = (u32*)(q + 0x20);`, which keeps q in r5 apart from keys (r30);
 * the pointer form through Keys() folds both into r30. Kept apart from fn_80075AC0.cpp, which holds the
 * following functions. */
/* Named data files: tag check, symbol table, global name hash, 80075AC0..800772EC. */
#include "game/rO_80065D64/types.h"
#pragma auto_inline off

struct Hdr {
    u32 f0;
    u32 size;   /* 4 */
    u32 nKey;   /* 8 */
    u32 nSym;   /* C */
    u32 nC;     /* 10 */
    u8 pad14[4];
    s8 tag[7];  /* 18 */
    s8 reg;     /* 1F */
};

struct Sym { u32 key; u32 off; };

struct Node {
    Node* next;
    u32 hash;
    const char* name;
    void* data;
};

struct NameTab {
    int n;
    void* heap;   /* 4 */
    void* mem;    /* 8 */
    Node* b[0x7EB]; /* C */
};

class Lock {
public:
    virtual void lock();
    virtual void v0C();
    virtual void unlock();
};

extern "C" {
extern s8* lbl_804CA3A8;
extern NameTab lbl_803CB870;
extern u8 lbl_803CD828[];
#define LOCK ((Lock*)lbl_803CD828)
extern u32 fn_8030EC9C(int, int, int);
extern void* fn_80079940(u32, int);
extern void fn_8017F44C(void*, int, u32);
extern void* fn_8030EA0C(void*, u32, int, int, int);
extern Node* fn_8030EB98(void*);
extern void fn_8030EC2C(void*, Node*);
extern int fn_80077174(const char*);

static inline BOOL TagOk(Hdr* h, const s8* m) {
    int i;
    for (i = 0; i < 7; i++) {
        if (h->tag[i] != m[i]) {
            return 0;
        }
    }
    return 1;
}

static inline u32* Keys(Hdr* h) {
    Hdr* q = (Hdr*)((u8*)h + (h->size & ~3));
    return (u32*)(q + 1);
}

static inline Hdr* GetHdr(Hdr* h) {
    const s8* m = lbl_804CA3A8;
    if (TagOk(h, m)) {
        return h;
    }
    h = (Hdr*)((u8*)h - 0x20);
    if (TagOk(h, m)) {
        return h;
    }
    return 0;
}

static inline void SymFind(Hdr* h, u32* k, u32 key) {
    u32 j;
    for (j = 0; j < h->nKey; j++) {
        if (key == *k) {
            break;
        }
        k++;
    }
}

extern Hdr* fn_8023F8EC(void*);
extern Hdr* fn_8023F1A4(void*, int);
extern void fn_8023F7EC(void*, int);
extern void fn_8023F1A8(Hdr*);
extern void fn_80076D48(const char*, void*);

#pragma push
#pragma use_lmw_stmw on
void fn_80075874(Hdr* h);
#pragma pop

#pragma push
#pragma use_lmw_stmw on
void fn_80075AC0(Hdr* h);
#pragma pop

Hdr* fn_80075B90(Hdr* h);

void* fn_80075D78(void* a);

void* fn_80075FB4(void* a, int f);

void fn_800761F0(Hdr* h);

void fn_800763E0(void* a);

u32 fn_800767DC(Hdr* h);

const char* fn_800769D0(Hdr* h, int idx);

void fn_80076C28(void);

u32 fn_80076D18(const char* s);

#pragma push
#pragma use_lmw_stmw on
static inline u32 Hash31(const char* s0) {
    const char* s = s0;
    u32 k;
    k = 0;
    while (*s) {
        k = *s++ + k * 31;
    }
    return k;
}

static inline Node* NewNode(const char* name, void* data) {
    LOCK->lock();
    Node* n = fn_8030EB98(lbl_803CB870.heap);
    lbl_803CB870.n++;
    LOCK->unlock();
    n->next = 0;
    n->hash = Hash31(name);
    n->name = name;
    n->data = data;
    return n;
}

struct HK { u32 h; u32 g; };

void fn_80076D48(const char* name, void* data);
#pragma pop

void* fn_80076F54(const char* s);

void* fn_80077064(const char* s);

#pragma push
#pragma use_lmw_stmw on
int fn_80077174(const char* s);
#pragma pop
}

#pragma use_lmw_stmw on
extern "C" {
void fn_80075AC0(Hdr* h) {
    u32 q = (u32)h + (h->size & ~3);
    u32* keys = (u32*)(q + 0x20);
    char* strs;
    Sym* s = (Sym*)(keys + h->nKey);
    strs = (char*)(s + h->nSym) + h->nC * 8;
    if (h->reg) {
        u32 i = 0;
        if (h->nSym != 0 && h->nSym != 0)
        for (; i < h->nSym; i++) {
            u32* k = keys;
            const char* name = strs + s->off;
            u32 j;
            for (j = 0; j < h->nKey; j++) {
                if (s->key == *k) {
                    break;
                }
                k++;
            }
            fn_80077174(name);
            s++;
        }
        h->reg = 0;
    }
}


}
