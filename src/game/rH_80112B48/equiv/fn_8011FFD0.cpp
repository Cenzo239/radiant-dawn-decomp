/* fn_8011FFD0 (0x3A8): `sched` (round 21, tools/check_regs.py; 234 of 234 instructions, 14 words differ).
 * Moved lines (dd.py): all inside the one straight-line block of the two stat additions: the original zero-extends
 * the 4th..8th intermediate sums (clrlwi) just before the second addition, ours does the 4th right after its
 * store, and the byte loads of the by-value copy (0x10..0x17(r1)) and the final adds/stb are interleaved in
 * another order. Stores, values and their order per stat are the same.
 * symcheck --anon: 30 blocks, 1 differs: "terminator differs" at `bl fn_8011B77C` because r6..r10 hold
 * different leftover temporaries of the additions. fn_8011B77C takes two arguments (r3, r4, both equal), so the
 * flag is an artefact of dead scratch registers.
 * Port notes: the JobC/UnitC/Slot structs describe the same memory as unit.h's Job/Unit (use one definition);
 * `Sub` copies its first operand bytewise before subtracting (the original keeps four dead byte stores of it);
 * the rank loop reads through `r` and writes through `u->rank` only to reproduce the addressing.
 * Class change (names guessed): drops the unit's class-bound skills (slot kind 1), moves it to job->p14 (the next
 * class), copies that class's skill list, adds the class's promotion gains (job +0x114) to the eight stats,
 * then adds (old class bases - new class bases) so that the visible totals do not drop, makes sure the unit has
 * skill lbl_804CA5BC (adding lbl_804CA6F8 if not), raises the twelve weapon ranks to the new class minimums
 * (job +0xB8), sets the level byte (+0xFE) to 1, and refreshes HP (fn_80126B80, fn_80126D9C(fn_801237EC)).
 */
#include "game/rH_80112B48/types.h"
#pragma use_lmw_stmw on
extern "C" {
struct Stat8 {
    s8 v[8];
};
struct Slot {
    u8* item;
    u8 kind;
    u8 flags;
    u8 pad[2];
};
struct JobC {
    u8 pad0[0x14];
    JobC* next;        /* 0x14 */
    u8 pad18[0x24 - 0x18];
    Slot skills[1];    /* 0x24 */
    u8 pad2C[0xB8 - 0x2C];
    s16 rank[12];      /* 0xB8: weapon rank minimums */
    u8 padD0[0xFC - 0xD0];
    Stat8 base;        /* 0xFC */
    u8 pad104[0x114 - 0x104];
    Stat8 gain;        /* 0x114: promotion gains */
};
struct UnitC {
    u8 pad0[0xF0];
    JobC* job;         /* 0xF0 */
    u8 padF4[0xFE - 0xF4];
    s8 level;          /* 0xFE */
    u8 padFF[0x108 - 0xFF];
    u64 flags;         /* 0x108 */
    u8 pad110[0x119 - 0x110];
    Stat8 stat;        /* 0x119 */
    u8 pad121[0x12C - 0x121];
    Slot skills[18];   /* 0x12C */
    u8 pad1BC[0x2D4 - 0x1BC];
    s16 rank[16];      /* 0x2D4 */
};
extern void* lbl_804CA5BC;
extern void* lbl_804CA6F8;
int fn_8011B77C(Slot*, void*);
void fn_8011B32C(Slot*, u8*);
void fn_8011B958(Slot*, Slot*);
void fn_8011A36C(Slot*);
void fn_8011B430(Slot*, void*);
void fn_80126B80(UnitC*, int);
int fn_801237EC(UnitC*);
void fn_80126D9C(UnitC*, s16);
void fn_8011FFD0(UnitC* u);
}
static inline void Add(Stat8* a, const Stat8& b) {
    a->v[0] += b.v[0];
    a->v[1] += b.v[1];
    a->v[2] += b.v[2];
    a->v[3] += b.v[3];
    a->v[4] += b.v[4];
    a->v[5] += b.v[5];
    a->v[6] += b.v[6];
    a->v[7] += b.v[7];
}
static inline void AddV(Stat8* a, Stat8 b) {
    Add(a, b);
}
static inline Stat8 Sub(const Stat8& a, const Stat8& b) {
    Stat8 t = a;
    t.v[0] -= b.v[0];
    t.v[1] -= b.v[1];
    t.v[2] -= b.v[2];
    t.v[3] -= b.v[3];
    t.v[4] -= b.v[4];
    t.v[5] -= b.v[5];
    t.v[6] -= b.v[6];
    t.v[7] -= b.v[7];
    return t;
}
extern "C" void fn_8011FFD0(UnitC* u) {
    JobC* old = u->job;
    Slot* q;
    int i;
    for (i = 0, q = u->skills; i < 18; i++, q++) {
        if (q && q->item && q->kind == 1) {
            fn_8011B32C(u->skills, q->item);
        }
    }
    u->job = u->job->next;
    fn_8011B958(u->skills, u->job->skills);
    fn_8011A36C(u->skills);
    Add(&u->stat, u->job->gain);
    AddV(&u->stat, Sub(old->base, u->job->base));
    if (!fn_8011B77C(u->skills, lbl_804CA5BC)) {
        fn_8011B430(u->skills, lbl_804CA6F8);
        fn_8011A36C(u->skills);
    }
    {
        u8 k;
        s16* r = u->rank;
        for (k = 0; k < 12; k++) {
            s16 m = u->job->rank[k];
            if (r[k] < m) {
                u->rank[k] = m;
            }
        }
    }
    u->level = 1;
    fn_80126B80(u, 0);
    u->flags &= ~(u64)0x40000;
    fn_80126D9C(u, fn_801237EC(u));
}
