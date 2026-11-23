/* fn_80076D48: exact (round m23). Adds a name/data pair to the global name hash (lbl_803CB870).
 * Lever: the hash loop is an inline `Hash37(const char* p)` iterating on its own parameter p; the dead
 * 31-hash the original also computes lives in the second field of a 2-member struct (HK hk; hk.g), which
 * CW keeps in a register. Written in the caller with a `p = name` copy, p and g swap registers. */
/* Named data files: tag check, symbol table, global name hash, 80075AC0..800772EC. */
#include "game/rO_80065D64/types.h"
#pragma auto_inline off

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
extern NameTab lbl_803CB870;
extern u8 lbl_803CD828[];
#define LOCK ((Lock*)lbl_803CD828)
extern Node* fn_8030EB98(void*);

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

static inline u32 Hash37(const char* p) {
    u32 h;
    HK hk;
    h = 0;
    hk.g = 0;
    while (*p) {
        h = *p + h * 37;
        hk.g = *p + hk.g * 31;
        p++;
    }
    return h;
}

void fn_80076D48(const char* name, void* data) {
    u32 h;
    Lock* l;
    Node** b;
    Node* q;
    h = Hash37(name);
    l = LOCK;
    l->lock();
    b = &lbl_803CB870.b[h % 0x7EB];
    q = *b;
    if (q == 0) {
        *b = NewNode(name, data);
    } else {
        Node* t = 0;
        while (q != 0) {
            t = q;
            q = q->next;
        }
        t->next = NewNode(name, data);
    }
    l->unlock();
}
#pragma pop
}
