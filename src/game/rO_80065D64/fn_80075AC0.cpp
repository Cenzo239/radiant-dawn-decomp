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

#if TARGET_PC
extern FE10_PROTO ptr32<Hdr> fn_8023F8EC(void*);
#else
extern Hdr* fn_8023F8EC(void*);
#endif
extern Hdr* fn_8023F1A4(void*, int);
extern void fn_8023F7EC(void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
extern void fn_8023F1A8(Hdr*);
#endif
extern void fn_80076D48(const char*, void*);

#pragma push
#pragma use_lmw_stmw on
void fn_80075874(Hdr* h) {
#if TARGET_PC
    /* convert the container header/tables to host order once (data stays big-endian) */
    if (!TagOk(h, lbl_804CA3A8)) {
        fe10_isbin_meta_to_native(h);
    }
#endif
    u8* base = (u8*)h + 0x20;
    u32* keys = (u32*)(base + (h->size & ~3));
    char* strs;
    Sym* s = (Sym*)(keys + h->nKey);
    strs = (char*)(s + h->nSym) + h->nC * 8;
    if (!TagOk(h, lbl_804CA3A8)) {
        u32* k = keys;
        u32 i;
        h->tag[0] = lbl_804CA3A8[0];
        h->tag[1] = lbl_804CA3A8[1];
        h->tag[2] = lbl_804CA3A8[2];
        h->tag[3] = lbl_804CA3A8[3];
        h->tag[4] = lbl_804CA3A8[4];
        h->tag[5] = lbl_804CA3A8[5];
        h->tag[6] = lbl_804CA3A8[6];
        i = 0;
        while (i < h->nKey) {
            u32 v = *k;
            k++;
            i++;
            u32 off = v & ~3;
#if TARGET_PC
            /* big-endian pointer field; the 32-bit value is the window offset */
            fe10_st32(base + off, fe10_ld32(base + off) + fe10_c32(base));
#else
            *(u32*)(base + off) += (u32)base;
#endif
        }
    }
    if (!h->reg) {
        h->reg = 1;
        u32 i = 0;
        if (h->nSym != 0) {
            for (; i < h->nSym; i++) {
                u32 key = s->key;
                const char* name = strs + s->off;
                void* data = base + (key & ~3);
                SymFind(h, keys, key);
                fn_80076D48(name, data);
                s++;
            }
        }
    }
}
#pragma pop

#pragma push
#pragma use_lmw_stmw on
void fn_80075AC0(Hdr* h);
#pragma pop

Hdr* fn_80075B90(Hdr* h) {
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

void* fn_80075D78(void* a) {
    Hdr* h = fn_8023F1A4(a, 1);
    fn_80075874(h);
    fn_8023F7EC(a, 0x400000);
    return (u8*)GetHdr(h) + 0x20;
}

void* fn_80075FB4(void* a, int f) {
    Hdr* h = fn_8023F1A4(a, f | 1);
    fn_80075874(h);
    fn_8023F7EC(a, 0x400000);
    return (u8*)GetHdr(h) + 0x20;
}

void fn_800761F0(Hdr* h) {
    fn_8023F1A8(GetHdr(h));
}

void fn_800763E0(void* a) {
    fn_8023F1A8(GetHdr((Hdr*)((u8*)GetHdr(fn_8023F8EC(a)) + 0x20)));
}

u32 fn_800767DC(Hdr* h) {
    return GetHdr(h)->nSym;
}

const char* fn_800769D0(Hdr* h, int idx);

void fn_80076C28(void) {
    lbl_803CB870.n = 0;
    int i;
    for (i = 0; i < 0x7EB; i++) {
        lbl_803CB870.b[i] = 0;
    }
#if TARGET_PC
    /* the unit size is sizeof(Node): 0x10 on the Wii, 0x20 with 64-bit pointers */
    u32 sz = fn_8030EC9C(sizeof(Node), 0x4000, 4);
    void* m = fn_80079940(sz, 0x40);
    fn_8017F44C(m, 0, sz);
    lbl_803CB870.mem = (u8*)m + (sz - 0x40000);
    lbl_803CB870.heap = fn_8030EA0C(m, sz, sizeof(Node), 4, 4);
#else
    u32 sz = fn_8030EC9C(0x10, 0x4000, 4);
    void* m = fn_80079940(sz, 0x40);
    fn_8017F44C(m, 0, sz);
    lbl_803CB870.mem = (u8*)m + (sz - 0x40000);
    lbl_803CB870.heap = fn_8030EA0C(m, sz, 0x10, 4, 4);
#endif
}

u32 fn_80076D18(const char* s) {
    u32 h = 0;
    while (*s) {
        h = *s++ + h * 37;
    }
    return h;
}

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

void* fn_80076F54(const char* s) {
    u32 g;
    void* r;
    Lock* l;
    u32 h;
    if (s == 0) {
        return 0;
    }
    h = 0;
    g = 0;
    while (*s) {
        h = *s + h * 37;
        g = *s + g * 31;
        s++;
    }
    r = 0;
    l = LOCK;
    l->lock();
    Node* n;
    for (n = lbl_803CB870.b[h % 0x7EB]; n != 0; n = n->next) {
        if (g == n->hash) {
            r = n->data;
        }
    }
    l->unlock();
    return r;
}

void* fn_80077064(const char* s) {
    u32 g;
    u32 h;
    Lock* l;
    void* r;
    if (s == 0) {
        r = 0;
    } else {
        h = 0;
        g = 0;
        while (*s) {
            h = *s + h * 37;
            g = *s + g * 31;
        s++;
        }
        r = 0;
        l = LOCK;
        l->lock();
        Node* n;
        for (n = lbl_803CB870.b[h % 0x7EB]; n != 0; n = n->next) {
            if (g == n->hash) {
                r = n->data;
            }
        }
        l->unlock();
    }
    return r;
}

#pragma push
#pragma use_lmw_stmw on
int fn_80077174(const char* s) {
    u32 g;
    int r;
    Lock* l;
    u32 h;
    Node* n;
    h = 0;
    g = 0;
    while (*s) {
        h = *s + h * 37;
        g = *s + g * 31;
        s++;
    }
    r = 0;
    l = LOCK;
    l->lock();
    Node** b = &lbl_803CB870.b[h % 0x7EB];
    Node* first = *b;
    for (n = first; n != 0; n = n->next) {
        if (g == n->hash) {
            if (first == n) {
                *b = n->next;
                r = 1;
            } else {
                Node* q = first;
                while (q->next != n) {
                    q = q->next;
                }
                q->next = n->next;
                r = 1;
            }
            n->name = 0;
            LOCK->lock();
            fn_8030EC2C(lbl_803CB870.heap, n);
            lbl_803CB870.n--;
            LOCK->unlock();
            break;
        }
    }
    l->unlock();
    return r;
}
#pragma pop
}
