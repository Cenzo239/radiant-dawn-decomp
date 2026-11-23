#ifndef RI_RLIST_H
#define RI_RLIST_H
/* Reference counted UI node and the std::list-style container that holds them.
   The list keeps a size word followed by a sentinel (prev, next). */
#ifdef __cplusplus
extern "C" {
#endif
void fn_80079210(void*);
void* fn_80079150(int);
extern char lbl_80389464[];
extern char __files[];
int fn_80290B48(void*, const char*, ...);
void fn_80291BD0(void);
#ifdef __cplusplus
}
#endif

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
typedef struct RList {
    int size;
    LNode* prev;
    LNode* next;
} RList;
typedef struct NodeHolder {
    RList* list;
    LNode* node;
} NodeHolder;

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

static inline LNode* listFind(RList* l, RObj* c) {
    LNode* n = l->next;
    LNode* e = (LNode*)&l->prev;
    while (n != e && n->val != c) {
        n = n->next;
    }
    return n;
}

class NodeGuard {
public:
    RList* list;
    LNode* node;
    NodeGuard(RList* l, LNode* n) {
        list = l;
        node = n;
    }
    ~NodeGuard() {
        if (node != NULL) {
            fn_80079210(node);
        }
    }
};

static inline LNode* nodeAlloc(void) {
    LNode* n = (LNode*)fn_80079150(0xc);
    if (n == NULL) {
        fn_80290B48(__files + 0xa0, lbl_80389464);
        fn_80291BD0();
    }
    return n;
}

static inline void listInsertN(RList* l, LNode* e, LNode* n, RObj* c) {
    NodeGuard h((RList*)&l->prev, n);
    RObj** vp = &n->val;
    if (vp != NULL) {
        *vp = c;
    }
    h.node = NULL;
    e->prev->next = n;
    n->prev = e->prev;
    e->prev = n;
    n->next = e;
    l->size++;
}

static inline void listInsert(RList* l, LNode* e, RObj* c) {
    LNode* n = nodeAlloc();
    listInsertN(l, e, n, c);
}
static inline void listPushBack(RList* l, RObj* c) {
    listInsert(l, (LNode*)&l->prev, c);
}
#endif
