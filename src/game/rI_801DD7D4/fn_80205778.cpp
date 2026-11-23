#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
extern char lbl_8038EEB0[];
extern char lbl_8038F110[], lbl_8038F194[], lbl_8038F218[], lbl_8038F29C[], lbl_8038F320[], lbl_8038F3A4[];
extern char lbl_8038F478[];
extern char lbl_803711D0[], lbl_80371188[], lbl_8036FD70[], lbl_8036FD08[];
extern char lbl_8038E938[], lbl_8038EB98[], lbl_8038EC1C[], lbl_8038ECA0[], lbl_8038ED24[], lbl_8038EDA8[], lbl_8038EE2C[];
int fn_801E70C4(void);
int fn_801E7114(void);
extern char lbl_803CAB38[];
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void fn_801E4094(void*);
int fn_801E70C4(void);
void* fn_80076F54(void*);
typedef struct It { u8 pad[0x26]; u8 x26; u8 p27[0x28 - 0x27]; } It;
void fn_80111B34(It*);
void fn_80110BFC(It*, const char*);
void fn_80111B64(void*, const It*);
void fn_80111C24(void*, int);
typedef struct ILN { struct ILN* prev; struct ILN* next; It v; } ILN;
typedef struct IL { int size; ILN* prev; ILN* next; } IL;
typedef struct Ent { const char* name; u8 x4; u8 x5; } Ent;
typedef struct Pr {
    u8 pad[0x40];
    IL l;
    int x4c, x50, x54, x58;
    u8 x5c, x5d, x5e;
    f32 x60;
    void* x64;
    int x68;
} Pr;
class Gd {
public:
    IL* list;
    ILN* node;
    ~Gd() { if (node != NULL) fn_80079210(node); }
};
static inline void listAdd(IL* l, const It& v, ILN*& e, ILN*& n) {
    e = (ILN*)&l->prev;
    n = (ILN*)fn_80079150(0x30);
    if (n == NULL) {
        fn_80290B48(__files + 0xa0, lbl_8038F478);
        fn_80291BD0();
    }
    {
        Gd g;
        g.list = (IL*)&l->prev;
        g.node = n;
        {
            It* p = &g.node->v;
            if (p != NULL) fn_80111B64(p, &v);
        }
        n = g.node;
        g.node = NULL;
        e->prev->next = n;
        n->prev = e->prev;
        e->prev = n;
        n->next = e;
        l->size++;
    }
}
static inline BOOL bitTest(u32* p, u32 v) {
    for (; v >= 0x20; v -= 0x20, p++) {}
    return (*p & (1 << v)) != 0;
}
static inline void ilClear(IL* l, ILN*& z) { ILN* n;
    n = l->next;
    z = (ILN*)&l->prev;
    if (n != z) {
        ILN* b = z->prev;
        n->prev->next = b->next;
        b->next->prev = n->prev;
        while (n != z) {
            ILN* d;
            fn_80111C24(&n->v, -1);
            d = n;
            n = n->next;
            fn_80079210(d);
            l->size--;
        }
    }
}
static inline void ilInit(IL* l) {
    int z = 0; ILN* e = (ILN*)&l->prev;
    l->size = z;
    l->next = e;
    l->prev = e;
}
#define MK(FN, CLS, KIND, GET, A1, A2, A3, A4, A5, A6, D1, D0) \
Pr* FN(void* parent, void* data) { \
    ILN* ln; \
    ILN* z; \
    ILN* le; \
    Pr* p; \
    Ent* e; \
    if (parent != NULL) { \
        p = (Pr*)fn_80081194(CLS, parent); \
    } else { \
        p = (Pr*)fn_80081050(CLS, parent); \
    } \
    if (p != NULL) { \
        fn_801E4094(p); \
        ilInit(&p->l); \
        p->x4c = 0; \
        p->x50 = 0; \
        p->x54 = 0; \
        p->x58 = 0; \
        p->x5c = 0; \
        p->x5d = 0; \
        p->x5e = 0; \
        p->x60 = 1.0f; \
        p->x64 = 0; \
        p->x68 = 0; \
    } \
    p->x5c = KIND; \
    p->x5d = GET(); \
    switch (p->x5d) { \
    case 1: p->x64 = A1; break; \
    case 2: p->x64 = A2; break; \
    case 3: p->x64 = A3; break; \
    case 4: p->x64 = A4; break; \
    case 5: p->x64 = A5; break; \
    case 6: p->x64 = A6; break; \
    } \
    e = (Ent*)fn_80076F54(data); \
    if (data == NULL || e == NULL || e->name == NULL) { \
        e = (Ent*)D1; \
        if (p->x5c == 0) e = (Ent*)D0; \
    } \
    ilClear(&p->l, z); \
    { \
        It t; \
        fn_80111B34(&t); \
        for (; e->name != NULL; e++) { \
            fn_80110BFC(&t, e->name); \
            if (e->x4 != 0) { \
                if (bitTest((u32*)(lbl_803CAB38 + 0x104), e->x5)) continue; \
                t.x26 = e->x5; \
            } \
            listAdd(&p->l, t, le, ln); \
        } \
        fn_80111C24(&t, -1); \
    } \
    return p; \
}
MK(fn_80205778, lbl_8038EEB0, 0, fn_801E70C4, lbl_8038F110, lbl_8038F194, lbl_8038F218, lbl_8038F29C, lbl_8038F320, lbl_8038F3A4, lbl_803711D0, lbl_80371188)
MK(fn_80205AE4, lbl_8038E938, 1, fn_801E7114, lbl_8038EB98, lbl_8038EC1C, lbl_8038ECA0, lbl_8038ED24, lbl_8038EDA8, lbl_8038EE2C, lbl_8036FD70, lbl_8036FD08)
}
