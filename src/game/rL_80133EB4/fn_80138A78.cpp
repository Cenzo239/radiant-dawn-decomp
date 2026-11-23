/* Minimap start: allocates the render target and queues the capture of the map. */
#include "game/rL_80133EB4/map3d.h"
struct Mini {
    f32 x, y, sx, sy;
    f32 w, h;
    u8 pad18[4];
    void* tex;
};
extern "C" {
extern Mini* lbl_804CB85C;
extern u8 lbl_804CB830;
extern char lbl_803694D4[];
extern u8 lbl_803EC898[];
extern u8 lbl_80386090[];
extern Mini* fn_80079150(int);
extern int fn_8030585C(u16, u16, int, int, int);
extern void* fn_80078D9C(int, char*, int);
extern void DCInvalidateRange(void*, u32);
extern void fn_801384E4(MapModel*);
extern void fn_80138628(MapModel*);
extern void fn_80010788(int, int, void (*)(MapModel*), MapModel*);
extern void fn_801CC2BC(Mesh*, int, int);
extern void fn_80081194(void*, void*);

static inline BOOL IsShadow() {
    BOOL r = 1;
    if (lbl_804CB830 != 1 && lbl_804CB830 != 2) r = 0;
    return r;
}

static inline Mesh* MeshI(MapModel* mm, int i) { return &mm->mesh[i]; }
static inline void Cull(MapModel* mm) {
    int i;
    Mesh* m;
    for (i = 0; i < mm->nMesh; i++) {
        m = MeshI(mm, i);
        if ((m->group->flags & 0x20000000) && (lbl_803EC898 + 0x200D)[m->ty * 0x40 + m->tx] == 0) m->flags |= 0x20;
    }
}
static inline void Start(MapModel* mm) {
    fn_80010788(1, 0x41, fn_801384E4, mm);
    if (mm->x04) {
        int i; Mesh* m = mm->mesh;
        for (i = 0; i < mm->nMesh; i++, m++) m->flags &= ~0x20;
    }
    if (IsShadow()) Cull(mm);
    {
        int i; Mesh* m = mm->mesh;
        for (i = 0; i < mm->nMesh; i++, m++) fn_801CC2BC(m, 0, 0);
    }
    fn_80010788(3, 0x9D, fn_80138628, mm);
}
void fn_80138A78(MapModel* mm, void* proc, f32 x, f32 y, f32 s, f32 mn, f32 w, f32 h) {
    lbl_804CB85C = fn_80079150(0x20);
    lbl_804CB85C->x = x;
    lbl_804CB85C->y = y;
    lbl_804CB85C->w = w;
    lbl_804CB85C->h = h;
    if (s * h / w < mn) s = mn;
    if (s > 64.0f) s = 64.0f;
    lbl_804CB85C->sx = s;
    lbl_804CB85C->sy = s;
    if (w > h) {
        lbl_804CB85C->sx *= w / h;
    } else {
        lbl_804CB85C->sy *= h / w;
    }
    int sz = fn_8030585C((u16)w, (u16)h, 4, 0, 0);
    lbl_804CB85C->tex = fn_80078D9C(-sz, lbl_803694D4 + 0x103, 0);
    DCInvalidateRange(lbl_804CB85C->tex, sz);
    if (proc == 0) {
        Start(mm);
    } else {
        fn_80081194(lbl_80386090, proc);
    }
}
}
