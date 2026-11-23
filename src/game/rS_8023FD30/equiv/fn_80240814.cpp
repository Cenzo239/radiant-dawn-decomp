/* symcheck: r21 review, flag was an artefact. fn_80240814: (a) stale temporaries before fn_801E2204 (reads r3-r5);
   the stack pair passed is equal. See docs/SCHED_REVIEW.md. */
/* EQUIVALENT (sched, round 19b): fn_80240814. Moved instructions (checked with dd.py): LR save, two stack addresses and four independent lha loads are interleaved differently; same subf/extsh/mulli/add chain. From wip/fn_80240814_a.cpp. */
#include "game/rS_8023FD30/types.h"
/* List window: cursor item, list walk, row draw. */
struct Pt16 { s16 x, y; };
struct LNode { LNode* prev; LNode* next; void* val; };
struct ListWin {
    u8 pad00[0xA];
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 v12;
    s16 v14;
    s16 v16;
    s16 v18;
    u8 pad1A[4];
    s16 v1E;
    s16 v20;
    u8 pad22[0x38 - 0x22];
    u32 flags;
    u8 pad3C[0x56 - 0x3C];
    s16 cursor;
    u8 pad58[4];
    s16 top;
    u8 pad5E[0x6C - 0x5E];
    u32 count;
    LNode* last;
    LNode* first;
};
extern "C" {
u32* fn_801E2204(ListWin*, void*, Pt16*);

static inline LNode* adv(LNode* it, s16 n) {
    if (n >= 0) {
        for (; n > 0; n--) {
            it = it->next;
        }
    } else {
        for (; n < 0; n++) {
            it = it->prev;
        }
    }
    return it;
}
struct R4 { s16 a, b, c, d; };
static inline void setR(ListWin* w, s16 a, s16 b, s16 c, s16 d) { w->v12 = a; w->v14 = b; w->v16 = c; w->v18 = d; }
static inline s16 cur(ListWin* w) { return w->cursor - w->top; }
static inline s16 rowH(ListWin* w) { return 0x1E; }
struct Pt { s16 x, y; Pt() {} Pt(s16 a, s16 b) { x = a; y = b; } };
static inline u32* get(ListWin* w, void* t, Pt p);
u32 fn_80240814(ListWin* w) {
    u32 tmp; Pt16 p; s16 c = cur(w); p.x = w->v1E; p.y = c * 0x1E + w->v20; return *fn_801E2204(w, &tmp, &p);
}
void* fn_80240868(ListWin* w);

void fn_802419AC(ListWin* w);

}