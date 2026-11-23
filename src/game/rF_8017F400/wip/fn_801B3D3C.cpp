/* near misses: std::list merge (fn_801B3D3C, fn_801B4480: 9 words with named end pointers e1, e2: e2 wants r11 and j r8; written here with End() it is worse; fn_801B40B0 needs the same). Declarations in ../fn_801B3B3C.cpp */
void fn_801B3D3C(LList* a, LList* b, Cmp c) {
/*P*/
    LNode* t;
    LNode* f2;
    LNode* j;
    int k;
    LNode* l2;
    LNode* h;
    LNode* f1;
/*E*/
    if (a == b) return;
    f1 = a->first;
    f2 = b->first;
    for (; f1 != End(a) && f2 != End(b); f1 = f1->next) {
        if (LT1(f2->val, f1->val)) {
            j = f2->next;
            k = 1;
            for (; j != End(b); j = j->next) {
                if (!(LT1(j->val, f1->val))) break;
                k++;
            }
            {
            l2 = j->prev;
            f2->prev->next = l2->next;
            l2->next->prev = f2->prev;
            f1->prev->next = f2;
            f2->prev = f1->prev;
            f2 = j;
            f1->prev = l2;
            l2->next = f1;
            }
            b->n -= k;
            a->n += k;
        }
    }
    if (f2 != End(b) && b->n != 0) {
        h = b->first;
        t = b->last;
        b->first = End(b);
        b->last = End(b);
        f1->prev->next = h;
        h->prev = f1->prev;
        f1->prev = t;
        t->next = f1;
        a->n += b->n;
        b->n = 0;
    }
}
void fn_801B4480(LList* a, LList* b, Cmp c) {
/*P*/
    LNode* t;
    LNode* f2;
    LNode* j;
    int k;
    LNode* l2;
    LNode* h;
    LNode* f1;
/*E*/
    if (a == b) return;
    f1 = a->first;
    f2 = b->first;
    for (; f1 != End(a) && f2 != End(b); f1 = f1->next) {
        if (LT3(f2->val, f1->val)) {
            j = f2->next;
            k = 1;
            for (; j != End(b); j = j->next) {
                if (!(LT3(j->val, f1->val))) break;
                k++;
            }
            {
            l2 = j->prev;
            f2->prev->next = l2->next;
            l2->next->prev = f2->prev;
            f1->prev->next = f2;
            f2->prev = f1->prev;
            f2 = j;
            f1->prev = l2;
            l2->next = f1;
            }
            b->n -= k;
            a->n += k;
        }
    }
    if (f2 != End(b) && b->n != 0) {
        h = b->first;
        t = b->last;
        b->first = End(b);
        b->last = End(b);
        f1->prev->next = h;
        h->prev = f1->prev;
        f1->prev = t;
        t->next = f1;
        a->n += b->n;
        b->n = 0;
    }
}
void fn_801B40B0(LList* a, LList* b, Cmp c) {
/*P*/
    LNode* t;
    LNode* f2;
    LNode* j;
    int k;
    LNode* l2;
    LNode* h;
    LNode* f1;
/*E*/
    if (a == b) return;
    f1 = a->first;
    f2 = b->first;
    for (; f1 != End(a) && f2 != End(b); f1 = f1->next) {
        if (LT2((s8*)f2->val, (s8*)f1->val)) {
            j = f2->next;
            k = 1;
            for (; j != End(b); j = j->next) {
                if (!(LT2((s8*)j->val, (s8*)f1->val))) break;
                k++;
            }
            {
            l2 = j->prev;
            f2->prev->next = l2->next;
            l2->next->prev = f2->prev;
            f1->prev->next = f2;
            f2->prev = f1->prev;
            f2 = j;
            f1->prev = l2;
            l2->next = f1;
            }
            b->n -= k;
            a->n += k;
        }
    }
    if (f2 != End(b) && b->n != 0) {
        h = b->first;
        t = b->last;
        b->first = End(b);
        b->last = End(b);
        f1->prev->next = h;
        h->prev = f1->prev;
        f1->prev = t;
        t->next = f1;
        a->n += b->n;
        b->n = 0;
    }
}
