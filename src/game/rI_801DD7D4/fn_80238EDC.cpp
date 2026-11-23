/* Archive/file entry manager: reference counts run up the parent chain. */
#include "game/rI_801DD7D4/fn_thp.h"

struct FE {
    u8 p0[0x50];
    u32 flags;
    u16 rc;
    u8 p56[6];
    FE* parent;
};
extern "C" {
inline int fn_80238EDC(FE* e, int m) { return e->flags & m; }
inline FE* fn_80238FB0(FE* e) { return e->parent; }
#pragma push
#pragma use_lmw_stmw on
#pragma inline_depth(4)
int fn_80238EE8(FE* e) {
    if (fn_80238EDC(e, 0x10000000) != 0) {
        fn_80238EE8(fn_80238FB0(e));
    }
    return --e->rc;
}
int fn_8023AB4C(FE* e) {
    if (fn_80238EDC(e, 0x10000000) != 0) {
        fn_8023AB4C(fn_80238FB0(e));
    }
    return ++e->rc;
}
#pragma pop
}
