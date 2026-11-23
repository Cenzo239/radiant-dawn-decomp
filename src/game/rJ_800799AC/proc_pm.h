#ifndef RJ_800799AC_PROC_PM_H
#define RJ_800799AC_PROC_PM_H

/* Proc_End's teardown walkers as member functions of the process. This is a second spelling of
 * proc_inl.h: the callers in fn_80082230.cpp only match when unlink, the onEnd walker and the
 * free walker are members (an inlined member call ranks `this` differently from an inlined
 * static function's pointer parameter), while the mark walker stays a static inline. The
 * recursion is written out level by level, ending in calls to the real walkers. */

#include "game/rJ_800799AC/proc_inl.h"

struct ProcM : Proc {
    ProcM* Prev() { return (ProcM*)prev; }
    ProcM* Child() { return (ProcM*)child; }

    void unlink() {
        if (next != 0) next->prev = prev;
        if (prev != 0) prev->next = next;
        if ((u32)parent > 10) {
            if (parent->child == this) parent->child = prev;
        } else {
            if (lbl_803E4E60[(u32)parent] == this) lbl_803E4E60[(u32)parent] = prev;
        }
        next = 0;
        prev = 0;
    }

    /* run onEnd over the subtree */
    void clear0() {
        if (prev != 0) fn_80081948(prev);
        if (child != 0) fn_80081948(child);
        if (onEnd != 0) onEnd(this);
        script = 0;
        loop = 0;
        if (flags & PROC_BLOCKING) parent->lockCnt--;
    }
    void clear1() {
        if (prev != 0) Prev()->clear0();
        if (child != 0) Child()->clear0();
        if (onEnd != 0) onEnd(this);
        script = 0;
        loop = 0;
        if (flags & PROC_BLOCKING) parent->lockCnt--;
    }

    /* return the subtree to the free stack */
    void free0() {
        int l = OSDisableInterrupts();
        if (prev != 0) fn_800815A8(prev);
        if (child != 0) fn_800815A8(child);
        FREE_TAIL(this, l)
    }
    void free1() {
        int l = OSDisableInterrupts();
        if (prev != 0) Prev()->free0();
        if (child != 0) Child()->free0();
        FREE_TAIL(this, l)
    }
    void free2() {
        int l = OSDisableInterrupts();
        if (prev != 0) Prev()->free1();
        if (child != 0) Child()->free1();
        FREE_TAIL(this, l)
    }

    /* Proc_End after the validity checks */
    void endBody() {
        unlink();
        mark3(this);
        clear1();
        free2();
    }
};

#endif
