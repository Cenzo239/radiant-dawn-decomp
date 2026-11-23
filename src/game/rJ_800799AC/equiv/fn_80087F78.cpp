/* fn_80087F78: functionally equal (regs level per tools/check_regs.py; registers differ from the original). Script command: end all of a class. From wip/fn_80085FC4_pm.cpp. */
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
struct PM : Proc {
void unlink() {
        if (next != 0) next->prev = prev;
        if (prev != 0) prev->next = next;
        if ((u32)parent > 10) { if (parent->child == this) parent->child = prev; }
        else { if (lbl_803E4E60[(u32)parent] == this) lbl_803E4E60[(u32)parent] = prev; }
        next = 0; prev = 0;
    }
void cl0_m();
void cl1_mm();
void fr0_m();
void fr1_mm();
void fr2_mmm();
};
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
inline void PM::cl0_m() { if (this->prev != 0) { fn_80081948(this->prev); } if (this->child != 0) { fn_80081948(this->child); } if (this->onEnd != 0) this->onEnd(this); this->script = 0; this->loop = 0; if (this->flags & PROC_BLOCKING) this->parent->lockCnt--; }
inline void PM::cl1_mm() { if (this->prev != 0) { ((PM*)(this->prev))->cl0_m(); } if (this->child != 0) { ((PM*)(this->child))->cl0_m(); } if (this->onEnd != 0) this->onEnd(this); this->script = 0; this->loop = 0; if (this->flags & PROC_BLOCKING) this->parent->lockCnt--; }
inline void PM::fr0_m() { int l_fr0_m = OSDisableInterrupts(); if (this->prev != 0) { fn_800815A8(this->prev); } if (this->child != 0) { fn_800815A8(this->child); } FREE_TAIL(this, l_fr0_m) }
inline void PM::fr1_mm() { int l_fr1_mm = OSDisableInterrupts(); if (this->prev != 0) { ((PM*)(this->prev))->fr0_m(); } if (this->child != 0) { ((PM*)(this->child))->fr0_m(); } FREE_TAIL(this, l_fr1_mm) }
inline void PM::fr2_mmm() { int l_fr2_mmm = OSDisableInterrupts(); if (this->prev != 0) { ((PM*)(this->prev))->fr1_mm(); } if (this->child != 0) { ((PM*)(this->child))->fr1_mm(); } FREE_TAIL(this, l_fr2_mmm) }

static inline void endS(Proc* p) { if (p == 0 || p->script == 0 || (p->flags & PROC_ENDED)) return; ((PM*)p)->unlink();mk3_ssss(p);((PM*)(p))->cl1_mm();((PM*)(p))->fr2_mmm(); }
static inline void endR(Proc*& p) { if (p == 0 || p->script == 0 || (p->flags & PROC_ENDED)) return; ((PM*)p)->unlink();mk3_ssss(p);((PM*)(p))->cl1_mm();((PM*)(p))->fr2_mmm(); }
struct PE : PM { void end() { if (this == 0 || script == 0 || (flags & PROC_ENDED)) return; ((PM*)this)->unlink();mk3_ssss(this);((PM*)(this))->cl1_mm();((PM*)(this))->fr2_mmm(); } void body() { ((PM*)this)->unlink();mk3_ssss(this);((PM*)(this))->cl1_mm();((PM*)(this))->fr2_mmm(); } };
static inline Proc* findName(const char* name) { Proc* q = lbl_803D9A58; int i;
  for (i = 0; i < 0x100; i++, q++) { if (q->script != 0) { const char* s1 = q->name; const char* s2 = name; int r;
    while (*s1 | *s2) { if (*s1 != *s2) { r = *s1 - *s2; goto done; } s1++; s2++; } r = 0; done: if (r == 0) return q; } } return 0; }
extern "C" {
#pragma use_lmw_stmw on
static inline void ec(void* script) { Proc* q = lbl_803D9A58; int i; for (i = 0; i < 0x100; i++, q++) { if (q->script == script) { if (q != 0 && q->script != 0 && !(q->flags & PROC_ENDED)) { ((PM*)q)->unlink();mk3_ssss(q);((PM*)(q))->cl1_mm();((PM*)(q))->fr2_mmm(); } } } }
int fn_80087F78(Proc* p) { ec((void*)p->cur[1]); p->cur += 2; return 1; }
}
