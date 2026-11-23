/* std::list<T*>::merge, one copy per comparison (key byte in the pointed-to struct); the
   sorts that call them are in fn_801B3B3C.cpp. Same spelling as the exact merge in
   rI_801DD7D4/fn_8021CA54.cpp (fn_80224AAC). Round m15. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {

typedef struct LNode { struct LNode* prev; struct LNode* next; s8* val; } LNode;
typedef struct LList { u32 n; LNode* last; LNode* first; } LList;
struct Cmp { Cmp() {} Cmp(const Cmp& o) : c(o.c) {} char c; };

static inline BOOL LT2(s8* a, s8* b) { if (a[1] == b[1]) return a[3] < b[3]; return a[1] < b[1]; }

void fn_801B3D3C(LList* a, LList* b, Cmp c) {
    LNode* last;
    LNode* j;
    LNode* ae;
    LNode* bi;
    s8 k;
    LNode* be;
    LNode* ai;
    int n;
    if (a == b) return;
    ai = a->first;
    ae = (LNode*)&a->last;
    bi = b->first;
    be = (LNode*)&b->last;
    while (ai != ae && bi != be) {
        k = ai->val[0];
        if (bi->val[0] < k) {
            j = bi->next;
            n = 1;
            while (j != be) {
                if (j->val[0] >= k) break;
                j = j->next;
                n++;
            }
            last = j->prev;
            bi->prev->next = last->next;
            last->next->prev = bi->prev;
            ai->prev->next = bi;
            bi->prev = ai->prev;
            LNode* nb = j;
            ai->prev = last;
            last->next = ai;
            bi = nb;
            b->n -= n;
            a->n += n;
        }
        ai = ai->next;
    }
    if (bi != be && b->n != 0) {
        LNode* lst;
        LNode* first = b->first;
        LNode* e2 = (LNode*)((u8*)b + 4);
        lst = b->last;
        b->first = e2;
        b->last = e2;
        ai->prev->next = first;
        first->prev = ai->prev;
        ai->prev = lst;
        lst->next = ai;
        a->n += b->n;
        b->n = 0;
    }
}

void fn_801B40B0(LList* a, LList* b, Cmp c) {
    LNode* j;
    LNode* ae;
    s8* v;
    LNode* ai;
    LNode* bi;
    LNode* be;
    LNode* last;
    int n;
    if (a == b) return;
    ai = a->first;
    ae = (LNode*)&a->last;
    bi = b->first;
    be = (LNode*)&b->last;
    while (ai != ae && bi != be) {
        v = ai->val;
        if (LT2(bi->val, v)) {
            j = bi->next;
            n = 1;
            while (j != be) {
                if (!LT2(j->val, v)) break;
                j = j->next;
                n++;
            }
            last = j->prev;
            bi->prev->next = last->next;
            last->next->prev = bi->prev;
            ai->prev->next = bi;
            bi->prev = ai->prev;
            LNode* nb = j;
            ai->prev = last;
            last->next = ai;
            bi = nb;
            b->n -= n;
            a->n += n;
        }
        ai = ai->next;
    }
    if (bi != be && b->n != 0) {
        LNode* lst;
        LNode* first = b->first;
        LNode* e2 = (LNode*)((u8*)b + 4);
        lst = b->last;
        b->first = e2;
        b->last = e2;
        ai->prev->next = first;
        first->prev = ai->prev;
        ai->prev = lst;
        lst->next = ai;
        a->n += b->n;
        b->n = 0;
    }
}

void fn_801B4480(LList* a, LList* b, Cmp c) {
    LNode* last;
    LNode* j;
    LNode* ae;
    LNode* bi;
    s8 k;
    LNode* be;
    LNode* ai;
    int n;
    if (a == b) return;
    ai = a->first;
    ae = (LNode*)&a->last;
    bi = b->first;
    be = (LNode*)&b->last;
    while (ai != ae && bi != be) {
        k = ai->val[3];
        if (bi->val[3] < k) {
            j = bi->next;
            n = 1;
            while (j != be) {
                if (j->val[3] >= k) break;
                j = j->next;
                n++;
            }
            last = j->prev;
            bi->prev->next = last->next;
            last->next->prev = bi->prev;
            ai->prev->next = bi;
            bi->prev = ai->prev;
            LNode* nb = j;
            ai->prev = last;
            last->next = ai;
            bi = nb;
            b->n -= n;
            a->n += n;
        }
        ai = ai->next;
    }
    if (bi != be && b->n != 0) {
        LNode* lst;
        LNode* first = b->first;
        LNode* e2 = (LNode*)((u8*)b + 4);
        lst = b->last;
        b->first = e2;
        b->last = e2;
        ai->prev->next = first;
        first->prev = ai->prev;
        ai->prev = lst;
        lst->next = ai;
        a->n += b->n;
        b->n = 0;
    }
}

}
