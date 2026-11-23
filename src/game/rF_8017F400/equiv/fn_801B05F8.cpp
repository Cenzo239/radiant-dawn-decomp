/* r19: copied from wip/fn_801B05F8.cpp; `sched` level (same instructions per basic block, order differs). */
/* near miss: fn_801B05F8, 3 words: scheduling of the list store vs lis/addi of __files before the loop. fn_801B0850 in this file is matched in ../fn_801B0850.cpp. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* picture list setup and teardown */
struct LNode { LNode* prev; LNode* next; void* val; };
struct PList { int size; LNode* last; LNode* first; };
struct E { E() {} char c; };
struct VPad { u8 pad[0x28]; };
class VWin : public VPad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void destroy(int);
};
typedef struct LData {
    void* res; void* x4; void* x8; void* xC; void* x10; VWin* x14; PList* list; int x1C; int x20; int x24;
} LData;
extern void fn_80079210(void*);
template <class L, class N> class Gd {
public:
    L* list;
    N* node;
    ~Gd() { if (node != NULL) fn_80079210(node); }
};
extern LData* lbl_804CB9BC;
extern void* lbl_804CB9B8;
extern char lbl_8036DCE0[];
extern char lbl_80389464[];
extern char lbl_804CA798[8];
extern char __files[];
extern void* fn_80077064(const char*);
extern void* fn_80079150(int);
extern void fn_80079210(void*);
extern int fn_80290B48(void*, const char*, ...);
extern void fn_80291BD0(void);
extern void fn_801B3B3C(void* p, E e);
extern void fn_801B3E68(void* p, E e);
extern void fn_801B4280(void* p, E e);
extern void* fn_80078CCC(u32, const char*, int);
extern void* fn_80179660(void*);
extern void fn_8017980C(VWin*, int, int, int);
extern void fn_801798A8(VWin*, int);
extern void fn_8017985C(VWin*, int);
extern void fn_80179864(VWin*, int);
extern void fn_80179854(VWin*, f32);
extern void fn_80177284(void*, void*);
extern void fn_801B378C(void);
extern void fn_800761F0(void*);
extern void fn_80006A2C(void*);

static inline LNode* NewNode(void) {
    LNode* n = (LNode*)fn_80079150(0xC);
    if (n == NULL) {
        fn_80290B48(__files + 0xA0, lbl_80389464);
        fn_80291BD0();
    }
    return n;
}
static inline void Push(PList* l, LNode* const& e, void* const& v, LNode*& n) {
    n = (LNode*)fn_80079150(0xC);
    if (n == NULL) {
        fn_80290B48(__files + 0xA0, lbl_80389464);
        fn_80291BD0();
    }
    Gd<PList, LNode> g;
    g.list = (PList*)&l->last;
    g.node = n;
    {
        void** p = &g.node->val;
        if (p != NULL) *p = v;
    }
    g.node = NULL;
    e->prev->next = n;
    n->prev = e->prev;
    e->prev = n;
    n->next = e;
    l->size++;
}

static inline void S0(PList* l) { E t; fn_801B3B3C(l, t); }
static inline void S1(PList* l) { E t; fn_801B3E68(l, t); }
static inline void S2(PList* l) { E t; fn_801B4280(l, t); }
static inline void D1(PList* l) { S1(l); }
static inline void D0(PList* l) { S0(l); }
static inline void D00(PList* l) { D0(l); }
static inline void Sort(void) {
    switch (lbl_804CB9BC->x24) {
    case 0: D00(lbl_804CB9BC->list); break;
    case 1: D1(lbl_804CB9BC->list); break;
    case 2: S2(lbl_804CB9BC->list); break;
    }
}
void fn_801B05F8(void) {
/*P*/
    PList* l;
    LNode* nd;
    LNode* e;
    u32 i;
    u32 n;
    u8* q;
/*E*/
    lbl_804CB9BC->x8 = fn_80077064(lbl_8036DCE0);
    lbl_804CB9BC->xC = fn_80077064(lbl_8036DCE0 + 0xC);
    lbl_804CB9BC->x10 = fn_80077064(lbl_8036DCE0 + 0x19);
    {
        u32* t = (u32*)fn_80077064(lbl_8036DCE0 + 0x25);
        n = *t;
        q = (u8*)(t + 1);
    }
    {
        PList* nl = (PList*)fn_80079150(0xC);
        if (nl != NULL) {
            nl->size = 0;
            { LNode* z = (LNode*)&nl->last; nl->first = z; nl->last = z; }
        }
        lbl_804CB9BC->list = nl;
    }
    for (i = 0; i < n; i++) {
        l = lbl_804CB9BC->list;
        e = (LNode*)&l->last;
        void* v = q;
        Push(l, e, v, nd);
        q += 0x18;
    }
    Sort();
    {
        void* m = fn_80078CCC(0x2C, lbl_804CA798, 0);
        if (m) m = fn_80179660(m);
        lbl_804CB9BC->x14 = (VWin*)m;
    }
    fn_8017980C(lbl_804CB9BC->x14, lbl_804CB9BC->x1C + 0x21E, lbl_804CB9BC->x20 + 0x10, 0x11C);
    fn_801798A8(lbl_804CB9BC->x14, 1);
    fn_8017985C(lbl_804CB9BC->x14, lbl_804CB9BC->list->size << 5);
    fn_80179864(lbl_804CB9BC->x14, 0x100);
    fn_80179854(lbl_804CB9BC->x14, 145.0f);
    fn_80177284((void*)fn_801B378C, lbl_804CB9B8);
}

}
