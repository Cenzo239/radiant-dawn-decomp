#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {

extern VO0N* lbl_804CB5B8;
extern char lbl_803711E8[];
void* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
void fn_8014C2AC(void*);
void fn_80253EE4(const char*, f32);
void fn_80083B78(void*);

typedef struct P64 {
    u8 pad[0x3c];
    void* x3c;
    u8 pad40[4];
    void* x44;
    u8 pad48[8];
    void* x50;
    u8 pad54[8];
    void* x5c;
    u8 pad60[0x78 - 0x60];
    const char* x78;
} P64;
typedef struct Proc { u8 pad[0x5e]; u8 x5e; u8 pad5f[5]; P64* x64; } Proc;
typedef struct LM { u8 pad[0x64]; const char* x64; } LM;
extern char lbl_803CAB38[];
u8* fn_80060728(void*);
#if TARGET_PC
FE10_PROTO void fn_801E7938(void*, p32arg);
#else
void fn_801E7938(void*, int);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_801E7A28(void*);
#else
int fn_801E7A28(void*);
#endif
void fn_80083DC4(void*, int);
void fn_801E58A0(void*);
void* fn_801E9270(void*, int);

void fn_802102C8(Proc* o) {
    fn_801E5734(o, fn_801E5640(o, -0x1000, 0));
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) {
        fn_801E5734(o, fn_801E5640(o, 3, 0));
        fn_8014C2AC(o->x64->x44);
        fn_80253EE4(lbl_803711E8 + 0xb5, 0.0f);
        fn_80083B78(o);
    }
}

void fn_80210390(Proc* o) {
    fn_801E5734(o, fn_801E5640(o, -0x1000, 0));
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) {
        fn_801E5734(o, fn_801E5640(o, 3, 0));
        fn_80253EE4(lbl_803711E8 + 0xb5, 0.0f);
        fn_80083B78(o);
    }
}

void fn_8021044C(Proc* o) {
    fn_801E5734(o, fn_801E5640(o, -0x1000, 0));
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) {
        fn_801E5734(o, fn_801E5640(o, 3, 0));
        fn_8014C2AC(o->x64->x50);
        fn_80253EE4(lbl_803711E8 + 0xb5, 0.0f);
        fn_80083B78(o);
    }
}

void fn_80210514(Proc* o) {
    fn_801E5734(o, fn_801E5640(o, -0x1000, 0));
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) {
        fn_8014C2AC(o->x64->x5c);
        fn_80253EE4(lbl_803711E8 + 0xb5, 0.0f);
        {
            const char* s = o->x64->x78;
            LM* p = (LM*)fn_801E5640(o, -0x1000, 0);
            if (p != NULL) {
                p->x64 = s;
            }
        }
        fn_80083B78(o);
    }
}

void fn_802105EC(Proc* o) { fn_80083DC4(o, o->x5e); }

class Lst {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34(int);
};

void fn_802105F4(Proc* o) {
    void* a = fn_801E5640(o, 3, 0);
    Lst* b = (Lst*)fn_801E5640(o, 4, 0);
    fn_801E7938(a, *(int*)(fn_80060728(lbl_803CAB38) + 0x24));
    b->v34(fn_801E7A28(a));
}

void fn_80210684(Proc* o) {
    void* a = fn_801E5640(o, 3, 0);
    Lst* b = (Lst*)fn_801E5640(o, 4, 0);
    fn_801E7938(a, *(int*)(fn_80060728(lbl_803CAB38) + 0x28));
    b->v34(fn_801E7A28(a));
    fn_80083DC4(o, o->x5e);
}

void fn_80210728(Proc* o) {
    fn_8014C2AC(o->x64->x3c);
    {
        const char* s = o->x64->x78;
        LM* p = (LM*)fn_801E5640(o, -0x1000, 0);
        if (p != NULL) {
            p->x64 = s;
        }
    }
}

void fn_80210780(void* o) {
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) {
        fn_80253EE4(lbl_803711E8 + 0xb5, 0.0f);
        fn_80083B78(o);
    }
}

void fn_802109BC(void* o) { fn_801E58A0(o); }

void fn_802109C0(RList* l) {
    LNode* e = (LNode*)&l->prev;
    l->size = 0;
    l->next = e;
    l->prev = e;
}

void fn_802109D8(RList* l) {
    LNode* e = (LNode*)&l->prev;
    l->size = 0;
    l->next = e;
    l->prev = e;
}

static inline void listClr(RList* l) {
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

void fn_802109F0(RList* l) { listClr(l); }
void fn_80210A78(RList* l) { listClr(l); }

}
