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
#if TARGET_PC
/* Host: clang requires C++ linkage for templates (the file is inside extern "C") */
extern "C++" {
template <class L, class N> class Gd {
public:
    L* list;
    N* node;
    ~Gd() { if (node != NULL) fn_80079210(node); }
};
}
#else
template <class L, class N> class Gd {
public:
    L* list;
    N* node;
    ~Gd() { if (node != NULL) fn_80079210(node); }
};
#endif
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
#if TARGET_PC
extern FE10_PROTO void fn_80177284(ptr32<const void>, void*);
#else
extern void fn_80177284(void*, void*);
#endif
extern void fn_801B378C(void);
extern void fn_800761F0(void*);
extern void fn_80006A2C(void*);

void fn_801B0850(void) {
/*P*/
    PList* l;
    LNode* b;
    LNode* a;
/*E*/
    fn_800761F0(lbl_804CB9BC->x4);
    fn_80006A2C(lbl_804CB9BC);
    l = lbl_804CB9BC->list;
    if (l) {
        if (l) {
            if (l) {
                a = l->first;
                b = (LNode*)&l->last;
                if (a != b) {
                    { LNode* z = b->prev;
                    a->prev->next = z->next;
                    z->next->prev = a->prev; }
                    while (a != b) {
                        LNode* t = a;
                        a = a->next;
                        fn_80079210(t);
                        l->size--;
                    }
                }
            }
        }
        fn_80079210(l);
    }
    if (lbl_804CB9BC->x14) lbl_804CB9BC->x14->destroy(1);
}
}
