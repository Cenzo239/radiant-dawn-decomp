/* EQUIVALENT (register-only, round 19): fn_801135C0 at regs level (10 words, second loop registers); near.cpp fragment made self-contained. */
/* Map wall flags and terrain heights, 801135C0..80114A44. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off

extern "C" {

extern void fn_8017F464(void*, int, int);
extern void fn_8017F4A0(void*, void*, int);
extern int fn_8010E314(int, int);
extern void* fn_80078D9C(int, char*, int);
extern void fn_80078E24(void*);
extern char lbl_80368760[];
extern char lbl_803CB770[];
extern Map lbl_803EC898;
extern int fn_80066130(void*, int, int, int);
extern void fn_80113794(Map*, s8, s8, u32);
extern void fn_80115DEC(Map*, int, int, void*, void*);
extern void fn_80116294(Map*, u8*, int, int, int);
extern void fn_80116680(Map*, u8*, int, int);
void fn_801136C0(Map* m);


static inline u16* FlagAt(Map* m, s8 x, s8 y) {
    return &m->flags[x + (y << 6)];
}

static inline void FlagOr(Map* m, s8 x, s8 y, u32 f) {
    *FlagAt(m, x, y) |= f;
}

static inline void FlagClr(Map* m, s8 x, s8 y, u32 f) {
    *FlagAt(m, x, y) &= ~f;
}
f32 fn_801141D4(Map* m, s8 x, s8 y, int k);

f32 fn_80114230(Map* m, s8 x, s8 y);

f32 fn_801146A8(Map* m, s8 x, s8 y, int k);

f32 fn_80114728(Map* m, s8 x, s8 y);

int fn_801147E4(Map* m, s8 x, s8 y);

void fn_80114818(Map* m, s8 x, s8 y);

void fn_80114850(Map* m, s8 x, s8 y);

void fn_80114888(Map* m, int k);

void fn_801148CC(Map* m, u16* p);

int fn_801148D8(Map* m, u32 k);

void fn_80114944(Map* m, u32 k, void* d);

void fn_80114A44(Map* m, u32 k, void* d);


static inline void Fill8(void* p, u8 v, int n) {
    fn_8017F464(p, (v + (v << 8)) + ((v << 24) + (v << 16)), n);
}

static inline void Fill16(void* p, u16 v, int n) {
    fn_8017F464(p, v + (v << 16), n);
}
void fn_80114B44(Map* m, u32 k, int v);

void fn_80115658(Map* m, int i, s8 v);


static inline u8 IsAlly(int a, int b) {
    return (u8)fn_8010E314(a, b) == 1;
}
void fn_8011567C(Map* m, u8* u);


#pragma push
#pragma use_lmw_stmw on

void fn_80116098(Map* m, s8 sx, s8 sy, void* a, void* b);

#pragma pop

void fn_80116658(Map* m, s8 x, s8 y);

void fn_80116A30(Map* m, s8 x, s8 y);

u8* fn_80116A4C(Map* m);

u8* fn_80116A58(Map* m);


}

/* ---- from build/tmp/r19hpbs/frag_h35c0.cpp ---- */
extern "C" {
void fn_801135C0(Map* m) {
    int i;
    int j;
    for (i = m->x0; i < m->x1; i++) {
        m->flags[(s8)i + (m->y0 << 6)] = (m->flags[(s8)i + (m->y0 << 6)] & ~0x808) | 0x80;
        m->flags[(s8)i + ((s8)(m->y1 - 1) << 6)] = (m->flags[(s8)i + ((s8)(m->y1 - 1) << 6)] & ~0x404) | 0x40;
    }
    for (j = m->y0; j < m->y1; j++) {
        int t = (s8)j << 6;
        m->flags[m->x0 + t] = (m->flags[m->x0 + t] & ~0x101) | 0x10;
        m->flags[(s8)(m->x1 - 1) + t] = (m->flags[(s8)(m->x1 - 1) + t] & ~0x202) | 0x20;
    }
}
}
