/* fn_801E2F40 (round 22, agent r22b): class `slots`, 9 words differ.
 * Proposed name: Group::AddChild(child). If the child is not yet in the group's list
 * (+0x40, size + sentinel), sets child->parent, appends it (12-byte node from
 * fn_80079150, guarded), takes a reference (rc++), and converts the child's offset (+0x1A)
 * so its absolute position stays put: child->ofs = parent->pos + parent->ofs - child->pos.
 *
 * check_regs: `slots`. The two compiler temporaries of the position arithmetic (the copy
 * inside ptSub and its return value) sit in swapped stack slots 0x8/0x10; same registers,
 * same instructions. symcheck --anon --xargs: 19 blocks, 1 flagged (block 17: stack bytes
 * 0x8..0xB / 0x10..0x13 differ), which is exactly that swap: both are dead temporaries
 * read back right after being written, and the stores to the child are identical.
 *
 * Port caveat: ptAdd is an inline copy of the real function fn_801E32C8 (Pu + Pt); the
 * original inlines it. ptSub is its subtracting twin (no out-of-line copy found).
 */
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
template <class L, class N> struct Gd { L* list; N* node; ~Gd() { if (node != NULL) fn_80079210(node); } };
static inline void rPush(RList* l, LNode* const& e, RObj* c) {
    LNode* n = nodeAlloc();
    Gd<RList, LNode> g;
    g.list = (RList*)&l->prev;
    g.node = n;
    {
        RObj** p = &g.node->val;
        if (p != NULL) {
            *p = c;
        }
    }
    g.node = NULL;
    e->prev->next = n;
    n->prev = e->prev;
    e->prev = n;
    n->next = e;
    l->size++;
}
struct Pt { s16 x, y; };
struct Pu { u16 x, y; };
/* inline copy of fn_801E32C8 (Pu + Pt) */
static inline Pu ptAdd(const Pu& a, const Pt& b) { Pu r = a; r.x = (s16)r.x + b.x; r.y = (s16)r.y + b.y; return r; }
static inline Pu ptSub(const Pu& a, const Pt& b) { Pu r = a; r.x = (s16)r.x - b.x; r.y = (s16)r.y - b.y; return r; }
typedef struct WC { void* vt; int rc; u8 p8[2]; Pu pos; u8 pe[0x1a - 0xe]; Pt ofs; u8 p1e[0x3c - 0x1e]; struct WC* parent; RList l40; } WC;
extern "C" {

void fn_801E2F40(WC* o, WC* c) {
    if (c != NULL) {
        if (listFind(&o->l40, (RObj*)c) == (LNode*)&o->l40.prev) {
            c->parent = o;
            rPush(&o->l40, (LNode*)&o->l40.prev, (RObj*)c);
            if (c != NULL) {
                c->rc++;
            }
            WC* p = c->parent;
            if (p != NULL) {
                Pu t = ptSub(ptAdd(p->pos, p->ofs), *(Pt*)&c->pos);
                c->ofs.x = (s16)t.x; c->ofs.y = (s16)t.y;
            }
        }
    }
}

}
