#include "game/rG_800A3D88/chr.h"

// Node position lookups on the battle character.

extern "C" {
extern char lbl_803657E8[];
extern const f32 lbl_804CD3B8, lbl_804CD400;
int fn_80007630(Mdl*, const char*);
int fn_800B4000(Chr*, int, Vec*, int, int);
f32 fn_8001E064(s16);
f32 fn_800A7370(ChrData*, const char*);
void fn_80312654(f32*, int, f32);
void fn_80312DB4(f32*, Vec*, Vec*);
void fn_80313460(Vec*, Vec*, Vec*);
#define ZERO_VEC(v) (*(u32*)&(v).x = 0, *(u32*)&(v).y = 0, *(u32*)&(v).z = 0)
static inline int NodeIndex(Chr* c, const char* name) {
    int k;
    if (c->mdl == NULL) {
        k = -1;
    } else {
        int t = fn_80007630(c->mdl, name);
        k = t;
    }
    return k;
}

static inline int NodePos(Chr* c, const char* name, Vec* v, int a, int b) {
    return fn_800B4000(c, NodeIndex(c, name), v, a, b);
}

Vec fn_800B377C(Chr* c, int i) {
    Vec v;
    const char* n = lbl_803657E8 + 0x26;
    ZERO_VEC(v);
    NodePos(c, n, &v, i, 0);
    return v;
}

static inline Vec NodeVec(Chr* c, int i) {
    Vec v;
    const char* n = lbl_803657E8 + 0x26;
    ZERO_VEC(v);
    NodePos(c, n, &v, i, 0);
    return v;
}

Vec fn_800B3824(Chr* c, int i) {
    Vec u = NodeVec(c, i);
    u.y = fn_8001E064(c->m5a);
    return u;
}

Vec fn_800B38F0(Chr* c, int i) {
    f32 m[12];
    Vec r = NodeVec(c, i);
    Vec d;
    d.x = lbl_804CD3B8;
    d.y = fn_800A7370(c->data, lbl_803657E8 + 0x16D);
    d.z = fn_800A7370(c->data, lbl_803657E8 + 0x176);
    fn_80312654(m, 'y', lbl_804CD400 * fn_8001E064(c->m58));
    fn_80312DB4(m, &d, &d);
    fn_80313460(&r, &d, &r);
    return r;
}

int fn_800B41C0(Chr* c, const char* name, Vec* v, int a, int b) {
    return NodePos(c, name, v, a, b);
}

BOOL fn_800B65F8(Chr* c) {
    if (c->mdl == NULL) return 0;
    AnimState* s = c->m7c;
    if (s == NULL) return 0;
    u16 f = s->flags;
    if ((f & 1) == 0) return 0;
    return (f & 4) != 0;
}
}
