/* Round 19 draft, NOT at regs level (other): fn_80042D38 (phase start: clear acted flags, tile
   refresh, per-turn gain). 194 of 196 instructions: everything fits except one redundant
   `clrlwi r0,r8,24` on the gain byte in each half of the unrolled last loop (the original keeps the
   s8 value unextended in r8 and masks it before the add). Tried: s8/u8/int/u32 locals, a gain()
   inline with every return type, ternaries. Compile with -i src/game/rT_80026898. */
#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
extern "C" {
extern GameState lbl_803CAB38;
extern u8 lbl_803EC898[];
extern Unit** lbl_804CB814;
extern u8* lbl_804CB810;
extern u8 lbl_80379F58[];
void fn_80083DC4(void*, int);
int fn_8011799C(void*, int, int);
Unit* fn_8012D2B0(u8);
Unit* fn_8012D280(u8);
void fn_800620A8(f32, f32, void*);
u32* fn_80060728(void*);
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void fn_800CD4A4(int);
void fn_8010E41C(char*, int);
void fn_80122460(Unit*);
struct Group { Unit* head; u8 pad[8]; };

static inline Unit* unitAt(u8 id) {
    return id ? (Unit*)(lbl_804CB810 + (id - 1) * 0x3f0) : 0;
}
void fn_80042C84(void);

void fn_80043214(void* p);

void fn_8004333C(void);


struct Scripts { u8 a[0x34]; u8 b[0x1c]; u8 c[0x10]; };
}

/* ---- from build/tmp/r19hpbs/frag_2d38.cpp ---- */
extern "C" {
void fn_80102E10(Unit*, int, int, int, f32);
void fn_80114D00(void*);
static inline u32 gsMode(void) { return (fn_80060728(&lbl_803CAB38)[1] >> 28) & 3; }
/* Start of a phase: clear the "acted" flags, refresh units standing on special tiles and add
   each unit's per-turn gain. */
void fn_80042D38(void) {
    u8 m3[0xc];
    u8 m0[0xc];
    int i;
    for (i = 0; i < 4; i++) {
        if (lbl_803CAB38.sideOn[i] && gsMode() == 2) {
            Unit* head = ((Group*)lbl_804CB814)[i].head;
            int n = 0;
            Unit* u;
            for (u = head; u; ) {
                u32 f = u->f10c;
                u = u->next;
                if (!(f & 1)) n++;
            }
            if (n == 0) {
                for (u = head; u; ) {
                    Unit* nx = u->next;
                    FLAGS(u) &= ~1ULL;
                    u = nx;
                }
            }
        }
    }
    fn_8010E41C((char*)m3, 3);
    for (i = 1; i <= 0xfe; i++) {
        Unit* u = unitAt(i);
        if (u->ec && m3[u->f4[8]]) {
            if (gsMode() != 2) {
                FLAGS(u) &= ~1ULL;
            }
            if (!((*fn_80060728(&lbl_803CAB38) >> 12) & 1)) {
                if (fn_8011799C(lbl_803EC898, u->x102, u->y103)) {
                    fn_80102E10(u, 0x10, 0, 0, 1.0f);
                }
            }
            FLAGS(u) &= ~0x800ULL;
        }
    }
    fn_8010E41C((char*)m0, 0);
    for (i = 1; i <= 0xfe; i++) {
        Unit* u = unitAt(i);
        if (u->ec && m0[u->f4[8]]) {
s8 raw = *((s8*)u + 0x379); u16 cur = *(u16*)&u->f37c; u8 g = raw < 0 ? *((s8*)u->ec + 0xe3) : raw; *(u16*)&u->f37c = cur + g;
            {u64 mm = ~0ULL; FLAGS(u) &= mm;}
        }
    }
    fn_80114D00(lbl_803EC898);
}
}
