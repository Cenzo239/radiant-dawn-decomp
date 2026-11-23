/* Ending the children of a process; both inline Proc_End. */
#include "game/rJ_800799AC/proc_pm.h"

extern "C" {

#pragma use_lmw_stmw on

/* Proc_EndChildren */
void fn_80082230(Proc* parent) {
    Proc* q;
    if (parent == 0) {
        return;
    }
    q = parent->child;
    while (q != 0) {
        Proc* n = q->prev;
        if (q != 0 && q->script != 0 && !(q->flags & PROC_ENDED)) {
            ((ProcM*)q)->endBody();
        }
        q = n;
    }
}

/* Proc_EndChildrenOfClass */
void fn_800829CC(Proc* parent, void* script) {
    Proc* q;
    if (parent == 0) {
        return;
    }
    q = parent->child;
    while (q != 0) {
        Proc* n = q->prev;
        if (q->script == script) {
            if (q != 0 && q->script != 0 && !(q->flags & PROC_ENDED)) {
                ((ProcM*)q)->endBody();
            }
        }
        q = n;
    }
}

#pragma use_lmw_stmw off

}
