/* fn_80177A5C: functionally equal (renamed, 10 of 348 words differ in registers only). Written in round 18. Caveat: the nine preset colours are non-const file statics kCol1..kCol9 (values checked against the DOL); the original reads lbl_804CE470+4..+0x27 in .sdata2, which is one const table shared with fn_8017794C (entry 0). A port should use one const C4 table of ten entries. */
/* Trail events: scans the animation events between the current frame and the frame fn_80008E88 returns,
   and applies the trail commands 0xC8..0xD3 (alpha 0 / 0x80 / 0xFF, then nine preset colours from lbl_804CE470). */
#include "game/rR_80175E5C/types.h"
struct C4 { u8 r, g, b, a; };
struct Trail {
    u8 pad0[0x30];
    void* arch;
    void* tex;
    C4 c0;
    C4 c1;
    void* segs;
    void* verts;
    u16 head;
    u16 x4A;
    u16 count;
    u16 cap;
    u8 flags;
    u8 pad51;
    u8 sub;
    u8 x53;
    u8 x54;
    u8 fade;
    s16 speed;
    char name0[8];
    char name1[8];
};
struct TrHost {
    u8 pad[0x58];
    f32 frame;
};
struct EvEnt { u16 id; u16 arg; };
struct EvList {
    u8 pad[3];
    u8 n;
    EvEnt e[1];
};
extern "C" {
int fn_80008E88(TrHost*, int, int);
void* fn_80007F10(TrHost*);
EvList* fn_80009CD0(void*, int);
}
/* Preset trail colours: lbl_804CE470+4 .. +0x24 in .sdata2 (entry 0, the default, is read by fn_8017794C). */
static C4 kCol1 = {0xFF, 0xFF, 0xFF, 0xFF};
static C4 kCol2 = {0x00, 0x00, 0x00, 0xFF};
static C4 kCol3 = {0x80, 0x80, 0x80, 0xFF};
static C4 kCol4 = {0xFF, 0x00, 0x00, 0xFF};
static C4 kCol5 = {0x00, 0xFF, 0x00, 0xFF};
static C4 kCol6 = {0x00, 0x00, 0xFF, 0xFF};
static C4 kCol7 = {0xFF, 0xFF, 0x00, 0xFF};
static C4 kCol8 = {0xFF, 0x00, 0xFF, 0xFF};
static C4 kCol9 = {0x00, 0xFF, 0xFF, 0xFF};
static inline void SetCol(Trail* t, C4 c) {
    t->c0 = c;
    t->c1 = c;
    if (c.r < 0x80 && c.g < 0x80 && c.b < 0x80) {
        t->flags &= ~1;
        t->flags |= 2;
    } else {
        t->flags &= ~2;
        t->flags |= 1;
    }
}
extern "C" void fn_80177A5C(Trail* t, TrHost* h) {
    int f = (int)h->frame;
    int end = fn_80008E88(h, f, 0x51);
    void* anim = fn_80007F10(h);
    for (; f < end; f++) {
        EvList* l = fn_80009CD0(anim, f);
        if (l) {
            int i;
            for (i = 0; i < l->n; i++) {
                switch (l->e[i].id) {
                case 0xC8: t->x54 = 0; break;
                case 0xC9: t->x54 = 0x80; break;
                case 0xCA: t->x54 = 0xFF; break;
                case 0xCB: SetCol(t, kCol1); break;
                case 0xCC: SetCol(t, kCol2); break;
                case 0xCD: SetCol(t, kCol3); break;
                case 0xCE: SetCol(t, kCol4); break;
                case 0xCF: SetCol(t, kCol5); break;
                case 0xD0: SetCol(t, kCol6); break;
                case 0xD1: SetCol(t, kCol7); break;
                case 0xD2: SetCol(t, kCol8); break;
                case 0xD3: SetCol(t, kCol9); break;
                }
            }
        }
    }
}
