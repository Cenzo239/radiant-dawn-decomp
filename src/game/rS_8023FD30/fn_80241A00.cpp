#include "game/rS_8023FD30/types.h"
class Deletable {
public:
    virtual void destroy(int);
};
struct LNode {
    LNode* prev;
    LNode* next;
    Deletable* val;
};
struct ListW {
    void* vt;
    u8 pad04[0x6C - 4];
    s32 count;
    LNode* anchor;
    LNode* first;
};
class TalkItem {
public:
    virtual void v08();
    virtual void v0C();
    virtual int v10();
    int kind;
    struct { u8 pad[4]; void* a; void* b; }* info;
};
extern "C" {
extern char lbl_803728A8[];
extern char lbl_80390EF4[];
void fn_80079210(void*);
void fn_801E2E00(void*, s32);
void* fn_801E5640(void*, s32, s32);
TalkItem* fn_80240868(void*);
BOOL fn_80058718(void);
BOOL fn_8002460C(void);
void fn_801D237C(void*);
void* fn_800D4228(const char*);
void fn_800893C4(void* proc);
void fn_801E5860(void);
void* fn_8010B1D8(void*);
void fn_800A0BE8(void*, void*, s32, void*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_80068CF8(void);
#else
void* fn_80068CF8(void);
#endif
BOOL fn_80068D74(void);
void fn_80068D34(s32);
void fn_80068C58(void);
#if TARGET_PC
FE10_PROTO void fn_800A0998(ptr32<const void>, void*);
#else
void fn_800A0998(void*, void*);
#endif

ListW* fn_80241A00(ListW* w, s32 del) {
    if (w) {
        w->vt = lbl_80390EF4;
        while (w->count != 0) {
            Deletable* d = w->anchor->val;
            if (d) {
                d->destroy(1);
            }
            LNode* n = w->anchor;
            n->prev->next = n->next;
            n->next->prev = n->prev;
            fn_80079210(n);
            w->count--;
        }
        if (&w->count) {
            if (&w->count) {
                if (&w->count) {
                    LNode* e = (LNode*)&w->anchor;
                    LNode* p = w->first;
                    if (p != e) {
                        LNode* l = e->prev;
                        p->prev->next = l->next;
                        l->next->prev = p->prev;
                        while (p != e) {
                            LNode* n = p;
                            p = p->next;
                            fn_80079210(n);
                            w->count--;
                        }
                    }
                }
            }
        }
        fn_801E2E00(w, 0);
        if (del > 0) {
            fn_80079210(w);
        }
    }
    return w;
}
struct Proc18 { u8 pad[0x18]; void* v18; u8 pad1C[0x44 - 0x1C]; void* v44; };
}
static inline void rel(void* a, void* b, void* self) {
    fn_800A0BE8(fn_8010B1D8(a), fn_8010B1D8(b), 3, self);
}
extern "C" {
void fn_8024253C(Proc18* self) {
    TalkItem* t = fn_80240868(fn_801E5640(self, 0x81, 0));
    if (fn_80058718() == 0 && fn_8002460C() == 0) {
        fn_801D237C(self->v18);
    } else {
        void* proc = fn_800D4228(lbl_803728A8 + 0x7A);
        if (proc) {
            fn_800893C4(proc);
        }
    }
    fn_801E5860();
    switch (t->kind) {
    case 0: {
        rel(t->info->a, t->info->b, self);
        break;
    }
    case 1:
        self->v44 = fn_80068CF8();
        if (t->v10() == 0 && fn_80068D74() == 0) {
            fn_80068D34(0);
        } else {
            fn_80068C58();
        }
        fn_800A0998(t->info, self);
        break;
    }
}
}
