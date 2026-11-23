#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off

extern "C" {

void fn_80079210(void*);
void* fn_80079150(int);
extern char lbl_8038CAF0[];
extern char lbl_80389464[];
extern char __files[];
int fn_80290B48(void*, const char*, ...);
void fn_80291BD0(void);
f32 fn_8017F68C(int, f32, f32, f32, f32);

/* Reference counted UI node with a virtual destructor at +8 */
class RObj {
public:
    virtual void destroy(int);
    virtual int contains(RObj*, int);
    virtual RObj* find(int, int);
    int rc;
};
typedef struct LNode {
    struct LNode* prev;
    struct LNode* next;
    RObj* val;
} LNode;
/* std::list-style container: size + sentinel */
typedef struct RList {
    int size;
    LNode* prev;
    LNode* next;
} RList;

static inline void rRelease(RObj* o) {
    if (o != NULL) {
        if (--o->rc == 0) {
            if (o != NULL) {
                o->destroy(1);
            }
        }
    }
}

static inline void listPopBack(RList* l) {
    LNode* n = l->prev;
    n->prev->next = n->next;
    n->next->prev = n->prev;
    fn_80079210(n);
    l->size--;
}

static inline void listClear(RList* l) {
    while (l->size != 0) {
        rRelease(l->prev->val);
        listPopBack(l);
    }
}

static inline void listFreeAll(RList* l) {
    if (l != NULL) {
        if (l != NULL) {
            if (l != NULL) {
                LNode* p = l->next;
                LNode* e = (LNode*)&l->prev;
                if (p != e) {
                    LNode* last = e->prev;
                    p->prev->next = last->next;
                    last->next->prev = p->prev;
                    while (p != e) {
                        LNode* t = p;
                        p = p->next;
                        fn_80079210(t);
                        l->size--;
                    }
                }
            }
        }
    }
}

typedef struct Group {
    void* vt;
    u8 pad4[0x3c - 4];
    struct Group* parent;
    RList list;
} Group;

void* fn_801E2E00(Group* o, int del) {
    if (o != NULL) {
        o->vt = lbl_8038CAF0;
        listClear(&o->list);
        listFreeAll(&o->list);
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}

#pragma use_lmw_stmw on
int fn_801E30C8(Group* o, RObj* child, int rec) {
    LNode* n;
    LNode* e;
    int found;
    if (child == NULL) {
        return 1;
    }
    n = o->list.next;
    e = (LNode*)&o->list.prev;
    found = 0;
    for (; n != e; n = n->next) {
        RObj* c = n->val;
        if (c == child) {
            ((Group*)child)->parent = NULL;
            n->prev->next = n->next;
            n->next->prev = n->prev;
            fn_80079210(n);
            o->list.size--;
            rRelease(child);
            found = 1;
            break;
        }
        if (rec != 0 && c->contains(child, rec)) {
            found = 1;
            break;
        }
    }
    return found;
}
#pragma use_lmw_stmw off

typedef struct Pt { s16 x, y; } Pt;

typedef struct UPt { u16 x, y; } UPt;
typedef struct Node { u8 pad[0x2c]; f32 x2c, x30, x34; u8 pad38[4]; struct Node* parent; } Node;

#pragma push
#pragma inline_depth(3)
#pragma auto_inline on
f32 fn_801E3300(Node* o) {
    f32 v = o->x2c;
    if (o->parent != NULL) {
        v *= fn_801E3300(o->parent);
    }
    return v;
}
f32 fn_801E33B4(Node* o) {
    f32 v = o->x30;
    if (o->parent != NULL) {
        v *= fn_801E33B4(o->parent);
    }
    return v;
}
f32 fn_801E3468(Node* o) {
    f32 v = o->x34;
    if (o->parent != NULL) {
        v *= fn_801E3468(o->parent);
    }
    return v;
}
#pragma pop

typedef struct Target { u8 pad[0x28]; s16 x28; u8 pad2a[6]; f32 x30; f32 x34; } Target;
typedef struct TNode { struct TNode* prev; struct TNode* next; Target* val; } TNode;
typedef struct Anim {
    u8 pad[0x28];
    s16 x28;
    u8 pad2a[6];
    u8 x30;
    u8 pad31[3];
    RList list;
    union { int mode; f32 from; };
    f32 to;
} Anim;

static inline Target* animBack(Anim* o) {
    return o->list.size != 0 ? (Target*)o->list.prev->val : NULL;
}

void fn_801E3B58(Anim* o) {
    f32 t, m, n;
    n = animBack(o)->x28 + 1;
    m = o->x28 + 1;
    switch (o->mode) {
    case 0:
        t = (1.0f / n) * (n - m);
        break;
    case 1:
        t = (1.0f / n) * m;
        break;
    }
    animBack(o)->x30 = t;
}

static inline f32 animT(Anim* o) {
    f32 n, m;
    n = animBack(o)->x28 + 1;
    m = o->x28 + 1;
    return fn_8017F68C(0, o->from, o->to, (1.0f / n) * (n - m), 1.0f);
}

static inline void animClear(Anim* o) {
    listClear(&o->list);
    listFreeAll(&o->list);
}

void fn_801E4094(Anim* o) {
    LNode* e = (LNode*)&o->list.prev;
    o->x30 = 0;
    o->list.size = 0;
    o->list.next = e;
    o->list.prev = e;
}

void* fn_801E40B0(Anim* o, int del) {
    if (o != NULL) {
        animClear(o);
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}

}
