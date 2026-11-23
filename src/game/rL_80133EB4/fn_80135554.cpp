/* Map model: per-frame update and mesh picking. */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

extern u8 lbl_804CB830;
extern u8 lbl_803EC898[];
extern int fn_801CA274(Mesh*, int, int);
#if TARGET_PC
extern FE10_PROTO int fn_801CA138(MapGroup*, const char*, void*, void*);
#else
extern int fn_801CA138(MapGroup*, int, int, int);
#endif
extern void fn_801CA190(MapGroup*, void*, void*);
extern void fn_8013450C(QTNode*, QTNode*);
extern void fn_80134F90(MapModel*);
extern void fn_801CC2BC(Mesh*, int, int);
extern void fn_80010788(int, int, void*, void*);
extern void fn_80137724(void*);
extern void fn_8013531C(MapModel*);
extern u8* fn_8000F470(void);
extern void fn_80257948(Vec*, Vec*, Vec*);
extern void fn_80312318(void*, f32);
extern void fn_80312654(void*, int, f32);
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_80312344(void*, void*);
extern void fn_80312378(void*, void*, void*);
extern void fn_802727A0(void*, void*);

static inline BOOL IsShadowMode(void) { return lbl_804CB830 == 1 || lbl_804CB830 == 2; }

static inline void LightsMul(MapModel* mm, void* mtx) {
    int i;
    MapEntry18* e = mm->lights;
    for (i = 0; i < 16; i++, e++) fn_802727A0(e, mtx);
}

static inline Mesh* FindMesh(MapModel* mm, int x, int y, u32 need, u32 reject) {
    Mesh* m;
    int i;
    for (i = mm->nMesh - 1; i >= 0; i--) {
        m = MeshAt(mm, i);
        u32 f = m->group->flags;
        if ((f & reject) == 0 && (need == 0 || need == (need & f)) && fn_801CA274(m, x, y)) return m;
    }
    return 0;
}

static inline void UpdateEnv(MapModel* mm) {
    u8 mtxA[0x30];
    u8 mtxB[0x30];
    u8 mtxC[0x30];
    f32 s;
    int i;
    s = 5.0f * mm->scale;
    fn_80312318(mtxA, 5.0f);
    fn_80312654(mtxB, 0x58, -4.712389f);
    fn_8031292C(mtxC, s, s, s);
    fn_80312344(mm->xe4, mtxA);
    fn_80312378(mtxA, mtxC, mtxA);
    fn_80312378(mtxA, mtxB, mtxA);
    for (i = 0; i < 16; i++) fn_802727A0(&mm->lights[i], mtxA);
}

static inline void CullShadow(MapModel* mm) {
    int i;
    Mesh* m;
    for (i = 0; i < mm->nMesh; i++) {
        m = MeshAt(mm, i);
        if ((m->group->flags & 0x20000000) && (lbl_803EC898 + 0x200D)[m->ty * 0x40 + m->tx] == 0) {
            m->flags |= 0x20;
        }
    }
}

Mesh* fn_80135800(MapModel* mm, int x, int y, u32 need, u32 reject) {
    Mesh* m;
    int i;
    for (i = mm->nMesh - 1; i >= 0; i--) {
        m = MeshAt(mm, i);
        u32 f = m->group->flags;
        if ((f & reject) == 0 && (need == 0 || need == (need & f)) && fn_801CA274(m, x, y)) return m;
    }
    return 0;
}

static inline Mesh* FindMesh90(MapModel* mm, int x, int y) {
    Mesh* m;
    int i;
    for (i = mm->nMesh - 1; i >= 0; i--) {
        m = MeshAt(mm, i);
        if ((m->group->flags & 0x90) == 0 && fn_801CA274(m, x, y)) return m;
    }
    return 0;
}

Mesh* fn_801358A8(MapModel* mm, int x, int y) {
    Mesh* r = FindMesh90(mm, x, y);
    return r;
}

Mesh* fn_80135934(MapModel* mm, int idx, u32 need, u32 reject) {
    Mesh* m;
    int n = 0;
    int i;
    for (i = 0; i < mm->nMesh; i++) {
        m = MeshAt(mm, i);
        u32 f = m->group->flags;
        if ((f & reject) == 0 && (need == 0 || need == (need & f))) {
            if (n == idx) return m;
            n++;
        }
    }
    return 0;
}

int fn_8013599C(MapModel* mm, int x, int y, u32 need, u32 reject, Mesh** out) {
    Mesh* m;
    int n = 0;
    int i;
    for (i = mm->nMesh - 1; i >= 0; i--) {
        m = MeshAt(mm, i);
        u32 f = m->group->flags;
        if ((f & reject) == 0 && (need == 0 || need == (need & f)) && fn_801CA274(m, x, y)) {
            out[n++] = m;
        }
    }
    return n;
}

static inline int DirBit(int i) {
    switch (i) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 8;
    }
    return 0x40;
}

static inline int DirX(u32 d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    }
    return 0;
}

static inline int DirY(u32 d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    }
    return 0;
}

Mesh* fn_80135A54(MapModel* mm, int x, int y, u32 need, u32 reject) {
    Mesh* m = FindMesh(mm, x, y, need, reject);
    int i;
    if (m) return m;
    for (i = 0; i < 4; i++) {
        u32 d = DirBit(i);
        m = FindMesh(mm, x + DirX(d), y + DirY(d), need, reject);
        if (m) return m;
    }
    return 0;
}

MapGroup* fn_80135F90(
#if TARGET_PC
MapModel* mm, const char* a, void* b, u32 need, u32 reject, void* c
#else
MapModel* mm, int a, int b, u32 need, u32 reject, int c
#endif
) {
    MapGroup* r = 0;
    MapGroup* g = mm->group;
    int i;
    for (i = 0; i < mm->nGroup; i++, g++) {
        if ((g->flags & reject) == 0 && need == (need & g->flags) && fn_801CA138(g, a, b, c)) r = g;
    }
    return r;
}

void fn_8013602C(MapModel* mm, void* a, void* b) {
    MapGroup* g = mm->group;
    int i;
    for (i = 0; i < mm->nGroup; i++, g++) {
        fn_801CA190(g, a, b);
    }
}

} /* extern "C" */
