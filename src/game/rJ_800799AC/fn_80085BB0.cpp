/* Proc_WalkTree: the walker fn_800858B0 is inlined here to its own fixed depth, so
 * the layers are written out and end in a call to the real function. */
#include "game/rJ_800799AC/proc.h"

extern "C" {

void fn_800858B0(Proc* p, ProcFunc f);

#define WALK_LAYER(name, callee)                                               \
    static inline void name(Proc* p, ProcFunc f) {                             \
        if (p->prev != 0) {                                                    \
            callee(p->prev, f);                                                \
        }                                                                      \
        f(p);                                                                  \
        if (p->child != 0) {                                                   \
            callee(p->child, f);                                               \
        }                                                                      \
    }
WALK_LAYER(walk0, fn_800858B0)
WALK_LAYER(walk1, walk0)
WALK_LAYER(walk2, walk1)
WALK_LAYER(walk3, walk2)

#pragma use_lmw_stmw on
void fn_80085BB0(Proc* p, ProcFunc f) {
    f(p);
    if (p->child != 0) {
        walk3(p->child, f);
    }
}
#pragma use_lmw_stmw off

}
