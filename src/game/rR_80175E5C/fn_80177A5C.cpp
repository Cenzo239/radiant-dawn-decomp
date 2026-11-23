/* fn_80177A5C (0x570): exact (round m23). From equiv/fn_80177A5C.cpp. The nine preset colours are read as the
 * .sdata2 words lbl_804CE470+4..+0x24 (declared here as extern C4 objects at those addresses, like fn_8017794C.cpp
 * reads entry 0 as lbl_804CE470); `static const` copies get their loads hoisted to the function top, an extern
 * array gets its base hoisted. Register lever: `void* anim; int end;` declared before `int f = (int)h->frame;`
 * (f r25, h/anim r26 like the original). */
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
extern "C" {
extern C4 lbl_804CE474;
extern C4 lbl_804CE478;
extern C4 lbl_804CE47C;
extern C4 lbl_804CE480;
extern C4 lbl_804CE484;
extern C4 lbl_804CE488;
extern C4 lbl_804CE48C;
extern C4 lbl_804CE490;
extern C4 lbl_804CE494;
}
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
    void* anim;
    int end;
    int f = (int)h->frame;
    end = fn_80008E88(h, f, 0x51);
    anim = fn_80007F10(h);
    for (; f < end; f++) {
        EvList* l = fn_80009CD0(anim, f);
        if (l) {
            int i;
            for (i = 0; i < l->n; i++) {
                switch (l->e[i].id) {
                case 0xC8: t->x54 = 0; break;
                case 0xC9: t->x54 = 0x80; break;
                case 0xCA: t->x54 = 0xFF; break;
                case 0xCB: SetCol(t, lbl_804CE474); break;
                case 0xCC: SetCol(t, lbl_804CE478); break;
                case 0xCD: SetCol(t, lbl_804CE47C); break;
                case 0xCE: SetCol(t, lbl_804CE480); break;
                case 0xCF: SetCol(t, lbl_804CE484); break;
                case 0xD0: SetCol(t, lbl_804CE488); break;
                case 0xD1: SetCol(t, lbl_804CE48C); break;
                case 0xD2: SetCol(t, lbl_804CE490); break;
                case 0xD3: SetCol(t, lbl_804CE494); break;
                }
            }
        }
    }
}
