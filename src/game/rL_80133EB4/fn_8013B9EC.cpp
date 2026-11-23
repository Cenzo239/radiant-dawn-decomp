/* Map model: per-frame update and mesh picking. */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

extern u8 lbl_804CB830;
extern u8 lbl_803EC898[];
extern int fn_801CA274(Mesh*, int, int);
#if TARGET_PC
extern FE10_PROTO int fn_801CA138(MapGroup*, p32arg, p32arg, p32arg);
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
    u8 mtxC[0x30];
    u8 mtxB[0x30];
    u8 mtxA[0x30];
    f32 s;
    int i;
    MapEntry18* e;
    s = 5.0f * mm->scale;
    fn_80312318(mtxA, 5.0f);
    fn_80312654(mtxB, 0x58, -4.712389f);
    fn_8031292C(mtxC, s, s, s);
    fn_80312344(mm->xe4, mtxA);
    fn_80312378(mtxA, mtxC, mtxA);
    fn_80312378(mtxA, mtxB, mtxA);
    e = mm->lights;
    for (i = 0; i < 16; i++, e++) fn_802727A0(e, mtxA);
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


extern MapModel* lbl_804CB860; extern u32 lbl_804CB5F4;
void fn_8013B9EC(void) {
    MapModel* mm;
    int k;
    Mesh* m2;
    int i2;
    MapEntry18* e;
    mm = lbl_804CB860;
    if (mm && !(lbl_804CB5F4 & 2)) {

    if ((mm->flags & 0x40000000) && !(mm->flags & 0x80000000)) {
        if (mm->x04) fn_8013450C(mm->quad, 0);
        if (IsShadowMode()) CullShadow(mm);
        fn_80134F90(mm);
        {
            m2 = mm->mesh;
            for (i2 = 0; i2 < mm->nMesh; i2++, m2++) {
                fn_801CC2BC(m2, 0, 0);
            }
        }
        if (mm->x04 && !(mm->flags & 0x80000000) && mm->xb1 == 0) {
            fn_80010788(3, 0x90, fn_80137724, mm);
        }
        fn_8013531C(mm);
        {
            u8* cam = fn_8000F470();
            if (cam) {
                Vec a;
                Vec b;
                Vec c;
                c = *(Vec*)(cam + 0xEC);
                b = *(Vec*)(cam + 0xE0);
                a = *(Vec*)(cam + 0xD4);
                fn_80257948(&a, &b, &c);
            }
        }
        {
            u8 mtxA[0x30];
            u8 mtxB[0x30];
            u8 mtxC[0x30];
            f32 s = 5.0f * mm->scale;
            fn_80312318(mtxA, 5.0f);
            fn_80312654(mtxB, 0x58, -4.712389f);
            fn_8031292C(mtxC, s, s, s);
            fn_80312344(mm->xe4, mtxA);
            fn_80312378(mtxA, mtxC, mtxA);
            fn_80312378(mtxA, mtxB, mtxA);
            e = mm->lights;
            for (k = 0; k < 16; k++, e++) fn_802727A0(e, mtxA);
        }
    }

    }
}
void fn_80135554(MapModel* mm) {
    int i2;
    Mesh* m2;
    int k;
    MapEntry18* e;

    if ((mm->flags & 0x40000000) && !(mm->flags & 0x80000000)) {
        if (mm->x04) fn_8013450C(mm->quad, 0);
        if (IsShadowMode()) CullShadow(mm);
        fn_80134F90(mm);
        {
            m2 = mm->mesh;
            for (i2 = 0; i2 < mm->nMesh; i2++, m2++) {
                fn_801CC2BC(m2, 0, 0);
            }
        }
        if (mm->x04 && !(mm->flags & 0x80000000) && mm->xb1 == 0) {
            fn_80010788(3, 0x90, fn_80137724, mm);
        }
        fn_8013531C(mm);
        {
            u8* cam = fn_8000F470();
            if (cam) {
                Vec c;
                Vec b;
                Vec a;
                c = *(Vec*)(cam + 0xEC);
                b = *(Vec*)(cam + 0xE0);
                a = *(Vec*)(cam + 0xD4);
                fn_80257948(&a, &b, &c);
            }
        }
        {
            u8 mtxC[0x30];
            u8 mtxB[0x30];
            u8 mtxA[0x30];
            f32 s = 5.0f * mm->scale;
            fn_80312318(mtxA, 5.0f);
            fn_80312654(mtxB, 0x58, -4.712389f);
            fn_8031292C(mtxC, s, s, s);
            fn_80312344(mm->xe4, mtxA);
            fn_80312378(mtxA, mtxC, mtxA);
            fn_80312378(mtxA, mtxB, mtxA);
            e = mm->lights;
            for (k = 0; k < 16; k++, e++) fn_802727A0(e, mtxA);
        }
    }

}
}
