#include "game/rS_8023FD30/types.h"
/* Talk list window: rebuild from the talk table. */
struct Empty { Empty() {} char c; };
struct MslString {
    union {
        struct { u32 isLong : 1; u32 pad : 31; u32 size; char* data; } l;
        struct { u8 isLong : 1; u8 size : 7; char data[11]; } s;
    };
};
class Deletable { public: virtual void destroy(int); };
struct LNode { LNode* prev; LNode* next; Deletable* val; };
struct LW {
    u8 pad00[0x56];
    s16 cursor;
    u8 pad58[0x6C - 0x58];
    s32 count;
    LNode* prev;
    LNode* next;
};
struct TItem { void* vt; int kind; int idx; void* cfg; };
extern "C" {
extern char lbl_80372780[];
extern char lbl_80390F30[];
extern char lbl_803CAB38[];
extern char lbl_80389464[];
extern char __files[];
int fn_80290B48(void*, const char*, ...);
void fn_80291BD0(void);
void fn_80079210(void*);
void* fn_80079150(int);
int fn_800A06F8(void);
int fn_800A07B8(int);
int fn_800A08F0(int);
const char** fn_8006074C(void*);
const char* fn_800A074C(int);
u32 strlen(const char*);
void fn_80024EFC(MslString*, u32);
void fn_800250B0(MslString*, u32, u32, const char*, const char*, Empty);
void* fn_80076F54(const char*);
void fn_8024076C(LW*, int);
}
static inline u32 strSize(MslString* s) {
    return s->l.isLong == 0 ? s->s.size : s->l.size;
}
static inline const char* strData(MslString* s) {
    return s->l.isLong == 0 ? s->s.data : s->l.data;
}
static inline void strInit(MslString* s, const char* const& p, u32& n) {
    n = strlen(p);
    fn_80024EFC(s, n);
    fn_800250B0(s, 0, 0, p, p + n, Empty());
}
static inline void strApp(MslString* s, const char* const& p, u32& n) {
    n = strSize(s);
    fn_800250B0(s, n, 0, p, p + strlen(p), Empty());
}
class Gd {
public:
    LNode** list;
    LNode* node;
    ~Gd() { if (node != NULL) fn_80079210(node); }
};
static inline Deletable* newItem(int i, void* c) {
    TItem* it = (TItem*)fn_80079150(0x10);
    if (it) {
        it->kind = 1;
        it->vt = lbl_80390F30;
        it->idx = i;
        it->cfg = c;
    }
    return (Deletable*)it;
}
static inline void pushFront(LW* w, Deletable* const& v) {
    LNode** e = &w->prev;
    LNode* node = (LNode*)fn_80079150(0xC);
    if (node == NULL) {
        fn_80290B48(__files + 0xa0, lbl_80389464);
        fn_80291BD0();
    }
    {
        Gd g;
        g.list = &w->prev;
        g.node = node;
        {
            Deletable** p = &g.node->val;
            if (p != NULL) *p = v;
        }
        g.node = NULL;
        (*e)->next = node;
        node->prev = *e;
        *e = node;
        node->next = (LNode*)e;
        w->count++;
    }
}
extern "C" {
#pragma use_lmw_stmw on
void fn_8024044C(LW* w) {
    /*P*/
    int cnt;
    const char* nm2;
    const char* lit2;
    const char** nm;
    s16 cur;
    int i;
    const char* q;
    const char* lit;
    u32 n;
    u32 n2;
    u32 n3;
    u32 n4;
    /*E*/
    cur = w->cursor;
    while (w->count != 0) {
        Deletable* d = w->prev->val;
        if (d) {
            d->destroy(1);
        }
        LNode* n = w->prev;
        n->prev->next = n->next;
        n->next->prev = n->prev;
        fn_80079210(n);
        w->count--;
    }
    cnt = fn_800A06F8();
    for (i = 0; i < cnt; i++) {
        if (fn_800A07B8(i) != 0 || fn_800A08F0(i) != 0) {
            nm = fn_8006074C(lbl_803CAB38);
            q = fn_800A074C(i);
            MslString s;
            lit = lbl_80372780 + 0x2d;
            *(u32*)&s = 0;
            s.l.size = 0; s.l.data = 0;
                        strInit(&s, lit, n);
            nm2 = *nm;
            strApp(&s, nm2, n2);
            lit2 = lbl_80372780 + 0x3d;
            strApp(&s, lit2, n3);
            strApp(&s, q, n4);
            pushFront(w, newItem(i, fn_80076F54(strData(&s))));
            if (s.l.isLong) {
                fn_80079210(s.l.data);
            }
        }
    }
    fn_8024076C(w, cur);
}
}
