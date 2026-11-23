/* fn_80088948: script command "end by name". Finds the live process whose name matches
 * the script argument and ends it (Proc_End inlined to its fixed depth: unlink, mark,
 * cleanup, free). The name search steps an explicit byte offset beside the counter. */
#include "game/rJ_800799AC/proc.h"
extern "C" {
extern u8 lbl_803E4E88[0x20];
extern Proc* lbl_803E4E60[10];
extern Proc** lbl_804CB5C8;
extern Proc lbl_803D9A58[0x100];
void fn_8008130C(Proc* p);
void fn_800815A8(Proc* p);
void fn_80081948(Proc* p);
}
#pragma inline_max_size(5000)
#define FREE_TAIL(q, l) if (!(q->flags & PROC_FREED)) { q->flags |= PROC_FREED; ((ProcLock*)lbl_803E4E88)->lock(); *--lbl_804CB5C8 = q; ((ProcLock*)lbl_803E4E88)->unlock(); OSRestoreInterrupts(l); }
static inline void sUnlink(Proc* p) {
    if (p->next != 0) p->next->prev = p->prev;
    if (p->prev != 0) p->prev->next = p->next;
    if ((u32)p->parent > 10) { if (p->parent->child == p) p->parent->child = p->prev; }
    else { if (lbl_803E4E60[(u32)p->parent] == p) lbl_803E4E60[(u32)p->parent] = p->prev; }
    p->next = 0; p->prev = 0;
}
static inline void mk0_s(Proc* p) { if (p->prev != 0) { fn_8008130C(p->prev); } if (p->child != 0) { fn_8008130C(p->child); } p->flags |= PROC_ENDED; }
static inline void mk1_ss(Proc* p) { if (p->prev != 0) { mk0_s(p->prev); } if (p->child != 0) { mk0_s(p->child); } p->flags |= PROC_ENDED; }
static inline void mk2_sss(Proc* p) { if (p->prev != 0) { mk1_ss(p->prev); } if (p->child != 0) { mk1_ss(p->child); } p->flags |= PROC_ENDED; }
static inline void mk3_ssss(Proc* p) { if (p->prev != 0) { mk2_sss(p->prev); } if (p->child != 0) { mk2_sss(p->child); } p->flags |= PROC_ENDED; }
static inline void cl0_s(Proc* p) { if (p->prev != 0) { fn_80081948(p->prev); } if (p->child != 0) { fn_80081948(p->child); } if (p->onEnd != 0) p->onEnd(p); p->script = 0; p->loop = 0; if (p->flags & PROC_BLOCKING) p->parent->lockCnt--; }
static inline void cl1_ss(Proc* p) { if (p->prev != 0) { cl0_s(p->prev); } if (p->child != 0) { cl0_s(p->child); } if (p->onEnd != 0) p->onEnd(p); p->script = 0; p->loop = 0; if (p->flags & PROC_BLOCKING) p->parent->lockCnt--; }
static inline void fr0_s(Proc* p) { int l_fr0_s = OSDisableInterrupts(); if (p->prev != 0) { fn_800815A8(p->prev); } if (p->child != 0) { fn_800815A8(p->child); } FREE_TAIL(p, l_fr0_s) }
static inline void fr1_s(Proc* p) { int l_fr1_s = OSDisableInterrupts(); if (p->prev != 0) { fr0_s(p->prev); } if (p->child != 0) { fr0_s(p->child); } FREE_TAIL(p, l_fr1_s) }
static inline void fr2_sxs(Proc* p) { int l_fr2_sxs = OSDisableInterrupts(); if (p->prev != 0) { fr1_s(p->prev); } if (p->child != 0) { fr1_s(p->child); } FREE_TAIL(p, l_fr2_sxs) }

static inline Proc* findName(const char* name) { Proc* q; int i; int off;
  for (i = 0, off = 0; i < 0x100; i++, off += sizeof(Proc)) { q = (Proc*)((u8*)lbl_803D9A58 + off);
    if (q->script != 0) { const char* s1 = q->name; const char* s2 = name; int r;
    while (*s1 | *s2) { if (*s1 != *s2) { r = *s1 - *s2; goto done; } s1++; s2++; } r = 0; done: if (r == 0) return q; } } return 0; }
extern "C" {
#pragma use_lmw_stmw on
int fn_80088948(Proc* p) { Proc* q = findName((const char*)p->cur[1]); if (q != 0) { if (q != 0 && q->script != 0 && !(q->flags & PROC_ENDED)) { sUnlink(q);mk3_ssss(q);cl1_ss(q);fr2_sxs(q); } } p->cur += 2; return 1; }
}
