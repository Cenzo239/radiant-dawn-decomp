/* Trail setup: archive, joint names, defaults and the trail colour (fn_8017794C). */
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
extern "C" {
char* strcpy(char*, const char*);
}
extern "C" C4 lbl_804CE470;
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
extern "C" void fn_8017794C(Trail* t, void* arch, const char* n0, const char* n1) {
    t->arch = arch;
    strcpy(t->name0, n0);
    strcpy(t->name1, n1);
    t->cap = 0xC;
    t->sub = 0x10;
    t->x4A = 0;
    t->count = 0;
    t->head = 0;
    t->speed = 0;
    t->x53 = 0;
    t->x54 = 0xFF;
    t->fade = 0;
    t->flags = 0;
    t->flags |= 1;
    t->segs = 0;
    t->verts = 0;
    t->tex = 0;
    SetCol(t, lbl_804CE470);
}
