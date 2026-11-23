/* Everything that inlines Proc_End. */
#include "game/rJ_800799AC/proc_inl.h"

extern "C" {

extern Proc lbl_803D9A58[0x100];
Proc* fn_800831C4(void);

#pragma use_lmw_stmw on

/* Proc_End */
void fn_80081A90(Proc* p) {
    if (p == 0 || p->script == 0 || (p->flags & PROC_ENDED)) {
        return;
    }
    PROC_END_BODY_M(p)
}

/* Proc_Alloc: pop the free stack, or kill a killable process when it is empty */
Proc* fn_800831C4(void) {
    Proc* p;
    ProcLock* lock = (ProcLock*)lbl_803E4E88;
    lock->lock();
    p = *lbl_804CB5C8;
    if (p != 0) {
        lbl_804CB5C8++;
    } else {
        int i;
        p = lbl_803D9A58;
        for (i = 0; i < 0x100; i++, p++) {
            if (p->script != 0 && (p->flags & PROC_KILLABLE)) {
                if (p != 0 && p->script != 0 && !(p->flags & PROC_ENDED)) {
                    PROC_END_BODY(p)
                }
                p = fn_800831C4();
                break;
            }
        }
    }
    lock->unlock();
    return p;
}

/* Proc_EndLayer */
void fn_80083F0C(int layer) {
    Proc* q = lbl_803D9A58;
    int i;
    for (i = 0; i < 0x100; i++, q++) {
        if (q->script != 0 && q->layer == layer) {
            if (q != 0 && q->script != 0 && !(q->flags & PROC_ENDED)) {
                PROC_END_BODY(q)
            }
        }
    }
}

/* Proc_EndAllOfClass */
void fn_800846BC(void* script) {
    Proc* q = lbl_803D9A58;
    int i;
    for (i = 0; i < 0x100; i++, q++) {
        if (q->script == script) {
            if (q != 0 && q->script != 0 && !(q->flags & PROC_ENDED)) {
                PROC_END_BODY(q)
            }
        }
    }
}

static inline int nameCmp(const char* s1, const char* s2) {
    while (*s1 | *s2) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return 0;
}

/* Proc_EndByName */
void fn_80084F0C(const char* name) {
    Proc* q = lbl_803D9A58;
    int i;
    for (i = 0; i < 0x100; i++, q++) {
        if (q->script != 0 && nameCmp(q->name, name) == 0) {
            procEndV(q);
        }
    }
}

static inline int cnt(void* script) {
    int n;
    int i;
    Proc* q = lbl_803D9A58;
    for (i = 0, n = 0; i < 0x100; i++, q++) {
        if (q->script == script) {
            n++;
        }
    }
    return n;
}

/* Script command: end this process if another instance exists */
int fn_80086818(Proc* p) {
    if (cnt(p->script) > 1) {
        procEndV(p);
        return 0;
    }
    p->cur++;
    return 1;
}

/* Script command: end one other instance of this class */
int fn_8008707C(Proc* p) {
    Proc* q = lbl_803D9A58;
    int i;
    for (i = 0; i < 0x100; i++, q++) {
        if (q != p && q->script == p->script) {
            procEnd(q);
            break;
        }
    }
    p->cur++;
    return 1;
}

/* Script command: end all of a class */
#pragma use_lmw_stmw off

}
