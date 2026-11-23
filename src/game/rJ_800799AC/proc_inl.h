#ifndef RJ_800799AC_PROC_INL_H
#define RJ_800799AC_PROC_INL_H

#include "game/rJ_800799AC/proc.h"

/* Teardown walkers spelled out layer by layer: in the original each recursive
 * walker was auto-inlined to a fixed depth, and that expansion was then inlined
 * into every caller. The real functions live in fn_80081050.cpp so that these
 * layers end in a call. */

extern "C" {
extern u8 lbl_803E4E88[0x20];
extern Proc* lbl_803E4E60[10];
extern Proc** lbl_804CB5C8;
void fn_8008130C(Proc* p);
void fn_800815A8(Proc* p);
void fn_80081948(Proc* p);
}

#define MARK_LAYER(name, callee)                                               \
    static inline void name(Proc* p) {                                         \
        if (p->prev != 0) {                                                    \
            callee(p->prev);                                                   \
        }                                                                      \
        if (p->child != 0) {                                                   \
            callee(p->child);                                                  \
        }                                                                      \
        p->flags |= PROC_ENDED;                                                \
    }
MARK_LAYER(mark0, fn_8008130C)
MARK_LAYER(mark1, mark0)
MARK_LAYER(mark2, mark1)
MARK_LAYER(mark3, mark2)

#define FREE_TAIL(q, l)                                                        \
    if (!(q->flags & PROC_FREED)) {                                            \
        q->flags |= PROC_FREED;                                                \
        ((ProcLock*)lbl_803E4E88)->lock();                                     \
        *--lbl_804CB5C8 = q;                                                   \
        ((ProcLock*)lbl_803E4E88)->unlock();                                   \
        OSRestoreInterrupts(l);                                                \
    }

static inline void free0(Proc* p) {
    int lvl = OSDisableInterrupts();
    if (p->prev != 0) {
        fn_800815A8(p->prev);
    }
    if (p->child != 0) {
        fn_800815A8(p->child);
    }
    FREE_TAIL(p, lvl)
}

#define FREE_MID(x)                                                            \
    {                                                                          \
        Proc* q1 = (x);                                                        \
        int l1 = OSDisableInterrupts();                                        \
        if (q1->prev != 0) {                                                   \
            free0(q1->prev);                                                   \
        }                                                                      \
        if (q1->child != 0) {                                                  \
            free0(q1->child);                                                  \
        }                                                                      \
        FREE_TAIL(q1, l1)                                                      \
    }

/* Variant whose middle layer is a macro: it changes which saved register holds
 * the interrupt levels, and each caller matches only one of the two. */
static inline void free2m(Proc* p) {
    int lvl = OSDisableInterrupts();
    if (p->prev != 0) {
        FREE_MID(p->prev)
    }
    if (p->child != 0) {
        FREE_MID(p->child)
    }
    FREE_TAIL(p, lvl)
}

static inline void free1(Proc* p) {
    int lvl = OSDisableInterrupts();
    if (p->prev != 0) {
        free0(p->prev);
    }
    if (p->child != 0) {
        free0(p->child);
    }
    FREE_TAIL(p, lvl)
}

static inline void free2(Proc* p) {
    int lvl = OSDisableInterrupts();
    if (p->prev != 0) {
        free1(p->prev);
    }
    if (p->child != 0) {
        free1(p->child);
    }
    FREE_TAIL(p, lvl)
}

#define CLEAR_LAYER(name, callee)                                              \
    static inline void name(Proc* p) {                                         \
        if (p->prev != 0) {                                                    \
            callee(p->prev);                                                   \
        }                                                                      \
        if (p->child != 0) {                                                   \
            callee(p->child);                                                  \
        }                                                                      \
        if (p->onEnd != 0) {                                                   \
            p->onEnd(p);                                                       \
        }                                                                      \
        p->script = 0;                                                         \
        p->loop = 0;                                                           \
        if (p->flags & PROC_BLOCKING) {                                        \
            p->parent->lockCnt--;                                              \
        }                                                                      \
    }
CLEAR_LAYER(clear0, fn_80081948)
CLEAR_LAYER(clear1, clear0)

static inline void Proc_Unlink(Proc* p) {
    if (p->next != 0) {
        p->next->prev = p->prev;
    }
    if (p->prev != 0) {
        p->prev->next = p->next;
    }
    if ((u32)p->parent > 10) {
        if (p->parent->child == p) {
            p->parent->child = p->prev;
        }
    } else {
        if (lbl_803E4E60[(u32)p->parent] == p) {
            lbl_803E4E60[(u32)p->parent] = p->prev;
        }
    }
    p->next = 0;
    p->prev = 0;
}

/* The whole of Proc_End after the validity checks. It has to be a macro: an
 * inline wrapper stops its own callees from being expanded. */
/* The whole of Proc_End. Expanding it needs a raised inline size limit. */
#pragma inline_max_size(5000)
static inline void procEnd(Proc* p) {
    if (p == 0 || p->script == 0 || (p->flags & PROC_ENDED)) {
        return;
    }
    Proc_Unlink(p);
    mark3(p);
    clear1(p);
    free2(p);
}

/* Same, but script is read again here. The original reloads it after an inlined
 * loop where the compiler here would reuse the earlier load, so the read is
 * volatile. The original source probably has no volatile. */
static inline void procEndV(Proc* p) {
    if (p == 0 || *(void* volatile*)&p->script == 0 || (p->flags & PROC_ENDED)) {
        return;
    }
    Proc_Unlink(p);
    mark3(p);
    clear1(p);
    free2(p);
}

static inline void procEndM(Proc* p) {
    if (p == 0 || p->script == 0 || (p->flags & PROC_ENDED)) {
        return;
    }
    Proc_Unlink(p);
    mark3(p);
    clear1(p);
    free2m(p);
}

#define PROC_END_BODY(p)                                                       \
    Proc_Unlink(p);                                                            \
    mark3(p);                                                                  \
    clear1(p);                                                                 \
    free2(p);

#define PROC_END_BODY_M(p)                                                     \
    Proc_Unlink(p);                                                            \
    mark3(p);                                                                  \
    clear1(p);                                                                 \
    free2m(p);

#endif
