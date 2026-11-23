/* fn_800105AC (GCamera_SortDisps): 14 of 64 words differ, all from r4/r5
 * being swapped between the list-head pointer and the l->prio temporary.
 * Goes in fn_8000F48C.cpp after fn_800104DC. Every declaration order of the
 * locals was tried (tools/perm), and a static inline per-list helper is worse
 * (36+ words). The `ins = cond ? ins : first` spelling is what gives the
 * original "blt; b; mr; b" block layout. */
/* GCamera_SortDisps: stable insertion sort of every list by prio. */
void fn_800105AC(GCamera* c) {
    GDisp** head;
    int i;
    GDisp* p;
    GDisp* first;
    GDisp* last;
    GDisp* next;
    GDisp* ins;
    GDisp* l;
    if (c == NULL) {
        c = lbl_804CB080;
    }
    if (c == NULL) {
        return;
    }
    head = c->lists;
    for (i = 0; i < 6; i++) {
        l = *head;
        first = NULL;
        last = NULL;
        ins = NULL;
        if (l != NULL) {
            while (l != NULL) {
                next = l->next;
                if (last != NULL) {
                    if (l->prio >= last->prio) {
                        last->next = l;
                        last = l;
                        l->next = NULL;
                    } else if (l->prio < first->prio) {
                        l->next = first;
                        first = l;
                    } else {
                        ins = (l->prio >= ins->prio) ? ins : first;
                        while ((p = ins->next) != NULL) {
                            if (l->prio < p->prio) {
                                break;
                            }
                            ins = p;
                        }
                        l->next = p;
                        ins->next = l;
                        if (l->next == NULL) {
                            last = l;
                        }
                    }
                } else {
                    l->next = NULL;
                    first = l;
                    last = l;
                    ins = l;
                }
                l = next;
            }
        }
        *head = first;
        head++;
    }
}
