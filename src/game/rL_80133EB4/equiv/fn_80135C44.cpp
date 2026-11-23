/* fn_80135C44 (0x344): functionally equal at `sched` level (tools/check_regs.py, round 20). Flood-collects a
 * mesh and the meshes of the same group that touch its four edge midpoints into `list` (recursive; returns the new
 * count; names guessed). From wip/near3.cpp. The old draft wrapped the body in an inline (`Body`), which lost the
 * copy of `n` into a saved register at entry (one instruction short); the plain function has it.
 * Moved instructions (tools/equiv/dd.py): in each of the four lookup set-ups, `lha 0x52(mm)` / `subi rI,r3,1`
 * (the mesh count for the inlined Find loop), one `lbz` of the mesh bounds with its `extsb`, and the
 * `oris need,flags,0x20` are scheduled a slot or two away. All are loads of unrelated fields or pure arithmetic.
 */
#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw on
extern "C" {
extern int fn_801CA274(Mesh*, int, int);
int fn_80135C44(MapModel* mm, Mesh* m, Mesh** list, int n);
static inline Mesh* Find(MapModel* mm, u32 need, int a, int b) {
    int i;
    Mesh* e;
    for (i = mm->nMesh - 1; i >= 0; i--) {
        e = &mm->mesh[i];
        u32 g = e->group->flags;
        if (!(g & 0x10) && (need == 0 || need == (need & g)) && fn_801CA274(e, a, b)) return e;
    }
    return 0;
}
#pragma push
#pragma auto_inline off
int fn_80135C44(MapModel* mm, Mesh* m, Mesh** list, int n) {
    u32 need;
    if (m == 0) return n;
    {
        Mesh** q = list;
        int k;
        for (k = 0; k < n; k++, q++) {
            if (*q == m) return n;
        }
    }
    list[n++] = m;
    need = m->group->flags | 0x200000;
    n = fn_80135C44(mm, Find(mm, need, m->x0 - 1, (m->y0 + m->y1) / 2), list, n);
    n = fn_80135C44(mm, Find(mm, need, m->x1 + 1, (m->y0 + m->y1) / 2), list, n);
    n = fn_80135C44(mm, Find(mm, need, (m->x0 + m->x1) / 2, m->y0 - 1), list, n);
    n = fn_80135C44(mm, Find(mm, need, (m->x0 + m->x1) / 2, m->y1 + 1), list, n);
    return n;
}
#pragma pop
}
