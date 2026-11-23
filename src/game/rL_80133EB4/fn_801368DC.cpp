#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw on
extern "C" {
struct Clr { u8 r, g, b, a; };
struct Fog { u8 mode, r, g, b; f32 start, end; };
extern u8 lbl_804CB830, lbl_804CB834, lbl_804CB839;
extern s8 lbl_804CB83A, lbl_804CB83B;
extern u8 lbl_804CB83C, lbl_804CB83D, lbl_804CB83E, lbl_804CB83F;
#if TARGET_PC
extern FE10_PROTO void fn_80010968(p32arg);
#else
extern void fn_80010968(int);
#endif
extern Fog* fn_80010960(void);
extern void fn_80010AB8(void);
extern void fn_80010AE4(void);
extern void fn_801476E8(void);
extern void fn_80147AF8(void);
extern void fn_80250D64(f32, f32, int);
extern void fn_80250E38(f32, f32, int);
extern void fn_801364AC(MapModel*);
extern void fn_8013B2B8(MapModel*);
extern void fn_80146BAC(void*, int);
extern void fn_80146B40(void*);
static inline void FogSet(Fog* f, u8 mode, f32 s, f32 e, u8 r, u8 g, u8 b, u8 a) {
    f->mode = mode;
    f->start = s;
    f->end = e;
    f->r = r;
    f->g = g;
    f->b = b;
}
#pragma auto_inline on
static inline void Upd(MapModel* mm) {
    Fog* f;
    Clr c;
    fn_80010968(0);
    f = fn_80010960();
    fn_80010AB8();
    {
        u8 r = lbl_804CB83C;
        u8 g = lbl_804CB83D;
        u8 b = lbl_804CB83E;
        u8 a = lbl_804CB83F;
        f->mode = lbl_804CB839;
        *(u8*)&c.r = r;
        *(u8*)&c.g = g;
        *(u8*)&c.b = b;
        *(u8*)&c.a = a;
        f32 s;
        f32 k = 5.0f;
        s = k * mm->scale;
        f->start = (f32)lbl_804CB83A * s;
        k = k * mm->scale;
        f->end = (f32)lbl_804CB83B * k;
        f->r = r;
        f->g = g;
        f->b = b;
    }
    fn_80010AE4();
}
#pragma auto_inline off
void fn_801368DC(MapModel* mm) { Upd(mm); }

static inline BOOL IsShadow(void) { return lbl_804CB830 == 1 || lbl_804CB830 == 2; }
struct H18 { u8 pad[0x18]; u8* w; };
void fn_8013A638(MapModel* mm) {
    switch (mm->xb1) {
    case 4:
        break;
    case 0:
        fn_801476E8();
        fn_80147AF8();
        if (IsShadow()) {
            fn_80250D64(0.55f, 250.0f, 7);
            fn_80250E38(1.35f, 250.0f, 7);
        } else {
            fn_80250D64(1.0f, 250.0f, 7);
            fn_80250E38(1.0f, 250.0f, 7);
        }
        fn_801364AC(mm);
        Upd(mm);
        break;
    case 1:
    case 2:
    case 3:
        fn_801364AC(mm);
        Upd(mm);
        break;
    }
    fn_8013B2B8(mm);
    {
        u8* w = ((H18*)mm)->w;
        if (w) {
            int k = lbl_804CB834; if (k != (int)w[0x31]) fn_80146BAC(w, k);
            fn_80146B40(w);
        }
    }
}

#pragma auto_inline off
extern u8 lbl_803EC898[];
extern u8 lbl_803CB770[];
extern u8 lbl_803CAB38[];
extern MapModel* lbl_804CB860;
extern char lbl_803694D4[];
extern void fn_80010788(int, int, void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_801384E4(void *);
#else
extern void fn_801384E4(void);
#endif
extern void fn_80138628(void);
extern void fn_801CC2BC(Mesh*, int, int);
static inline void Cull(MapModel* mm) {
    int i;
    Mesh* m;
    for (i = 0; i < mm->nMesh; i++) {
        m = MeshAt(mm, i);
        if ((m->group->flags & 0x20000000) && (lbl_803EC898 + 0x200D)[m->ty * 0x40 + m->tx] == 0) m->flags |= 0x20;
    }
}
void fn_80138800(void) {
    MapModel* mm = lbl_804CB860;
    fn_80010788(1, 0x41, (void*)fn_801384E4, mm);
    if (mm->x04) {
        Mesh* m = mm->mesh;
        int i;
        for (i = 0; i < mm->nMesh; i++, m++) m->flags &= ~0x20;
    }
    if (IsShadow()) Cull(mm);
    {
        Mesh* m = mm->mesh;
        int i;
        for (i = 0; i < mm->nMesh; i++, m++) fn_801CC2BC(m, 0, 0);
    }
    fn_80010788(3, 0x9D, (void*)fn_80138628, mm);
}
extern void fn_80290DDC(char*, const char*, ...);
extern void* fn_8017F37C(const char*, const char*, const char*);
extern int fn_8023F9F4(void*);
#if TARGET_PC
extern FE10_PROTO void fn_8023F1A0(void*, ptr32<const void>);
#else
extern void fn_8023F1A0(void*, void*);
#endif
int fn_80139964(const char* name, int kind, void* out) {
    char path[0x48];
    void* f;
    const char* dir = 0;
    const char* ext = 0;
    switch (kind) {
    case 4:
        break;
    case 0:
        dir = lbl_803694D4 + 0x155;
        ext = lbl_803694D4 + 0x15B;
        break;
    case 1:
    case 2:
    case 3:
        dir = lbl_803694D4 + 0x15F;
        ext = lbl_803694D4 + 0x164;
        break;
    }
    if (dir == 0) return 0;
    {
        fn_80290DDC(path, lbl_803694D4 + 0x167, dir, name);
        f = fn_8017F37C(path, ext, lbl_803694D4 + 0x16D);
        if (fn_8023F9F4(f) == 0x40000) f = fn_8017F37C(path, ext, lbl_803694D4 + 0x172);
        if (fn_8023F9F4(f) == 0x40000) return 0;
        fn_8023F1A0(f, out);
        return 1;
    }
}
extern Mesh* fn_80135934(MapModel*, int, u32, u32);
int fn_8013B664(MapModel* mm) {
    int r = 0;
    int n = 0;
    int i;
    for (i = 0; i < mm->nMesh; i++) {
        u32 f = mm->mesh[i].group->flags;
        if ((f & 0x10) == 0 && (f & 0x10000000) == 0x10000000) n++;
    }
    if (n > 0) {
        int c = 0;
        int j;
        for (j = 0; j < n; j++) {
            Mesh* m = fn_80135934(mm, j, 0x10000000, 0x10);
            if (m && ((u8*)m)[0xCD]) c++;
        }
        r = c * 100 / n;
    }
    return r;
}
extern void fn_8001A218(int, void*);
extern void fn_80137BC8(MapModel*);
extern int fn_801CA1E8(Mesh*);
extern int fn_801CA260(Mesh*);
extern void fn_80138000(MapModel*, int, int, int, int, int);
extern int fn_800670BC(void*, int);
extern int fn_800660E8(void*);
extern void fn_8010B240(u8);
extern void fn_80113428(void*);
extern void fn_80136C34(MapModel*);
extern void fn_8011398C(void*);
extern void fn_801136C0(void*);
extern void fn_801135C0(void*);
extern void fn_8012DCA8(void);
struct Ev { s8 x, y; u8 t, pad, v; };
void fn_801379F8(MapModel* mm, int b) {
    fn_80137BC8(mm);
    if (mm->flags & 0x10000000) {
        Mesh* m = mm->mesh;
        int i;
        for (i = 0; i < mm->nMesh; i++, m++) {
            if (fn_801CA1E8(m) && fn_801CA260(m)) {
                int x0 = m->x0;
                int y0 = m->y0;
                int x1 = m->x1;
                int y1 = m->y1;
                if (x0 < 0) x0 = 0;
                if (y0 < 0) y0 = 0;
                if (x1 >= mm->x4c - 1) x1 = mm->x4c - 1;
                if (y1 >= mm->x4d - 1) y1 = mm->x4d - 1;
                if (m->group->flags & 2) {
                    fn_80138000(mm, x0, y0, x1, y1, 1);
                } else {
                    fn_80138000(mm, x0, y0, x1, y1, 0);
                }
            }
        }
    }
    if (fn_800670BC(lbl_803CB770, 0x11)) {
        int i;
        for (i = 0; i < fn_800660E8(lbl_803CB770); i++) {
            Ev* e = (Ev*)(*(u8**)lbl_803CB770 + i * 8);
            if (e && e->t == 0x11) {
                int x = e->x;
                int y = e->y;
                u8 v = e->v;
                fn_8010B240(v);
                (lbl_803EC898 + 0x100D)[y * 0x40 + x] = v;
            }
        }
    }
    fn_80113428(lbl_803EC898);
    fn_80136C34(mm);
    fn_8011398C(lbl_803EC898);
    fn_801136C0(lbl_803EC898);
    fn_801135C0(lbl_803EC898);
    if (b) {
        fn_8012DCA8();
        mm->flags |= 1;
    }
}

extern void fn_80136E74(MapModel*);
extern u8* fn_80060728(void*);
extern void fn_80012268(void);
extern int fn_80011E28(void);
extern void fn_803128AC(void*, f32, f32, f32);
extern void* fn_8000FB88(void);
extern void fn_80312378(void*, void*, void*);
extern void fn_80307E48(void*, int);
extern void fn_80021784(int);
extern void fn_8031258C(void*, void*);
extern void fn_80307E98(void*, int);
extern void fn_80304538(int, int);
extern void fn_80021B2C(int);
extern void fn_80021958(int, Clr);
extern void fn_800218A8(int, Clr);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_800217CC(int);
extern void fn_80021808(int, int, int, int, int);
extern void fn_80021860(int, int, int);
extern void fn_80147D78(void);
extern int fn_80011EAC(void);
extern void fn_80021BF4(u8);
extern int fn_80011FBC(void);
extern void fn_80021C34(u8);
extern void fn_80307B58(void*, int);
extern void fn_80011838(int);
extern u8 lbl_804CB838;
struct MS { u8 pad[0xB8]; Clr c; void* xbc; int xc0; };
static inline BOOL Dirty(MapModel* m) { return (*(volatile u32*)&m->flags & 1) != 0; }
void fn_80137724(MapModel* mm) {
    u8 m[0x30];
    Clr c;
    if (Dirty(mm)) {
        mm->flags &= ~1;
        fn_80136E74(mm);
    }
    if (lbl_804CB838 & 0x10) return;
    c = ((MS*)mm)->c;
    c.a = fn_80060728(lbl_803CAB38)[9] * 0xFF / 100;
    if (c.a) {
        int v;
        fn_80012268();
        v = fn_80011E28();
        fn_803128AC(m, 0.0f, 0.0f, -0.02f);
        fn_80312378(fn_8000FB88(), m, m);
        fn_80307E48(m, 0);
        fn_80021784(0);
        fn_8031258C(m, m);
        fn_80307E98(m, 0);
        fn_80304538(6, 0);
        fn_80021B2C(1);
        fn_80021958(4, c);
        {
            Clr w = {0xFF, 0xFF, 0xFF, 0xFF};
            fn_800218A8(4, w);
        }
        fn_80021A08(4, 0, 0, 0, 0, 0, 2);
        fn_80021CB4(v, 0xFF, 0xFF, 4);
        fn_80021EF8(v, 4);
        fn_803031CC();
        fn_80302B80(9, 1);
        fn_80303200(0, 9, 1, 4, 0);
        fn_80021BA4(1, 4, 5, 0);
        fn_800217CC(1);
        fn_80021808(0, 0, 1, 7, 0);
        fn_80021860(1, 3, 0);
        if (IsShadow()) fn_80147D78();
        fn_80021BF4(fn_80011EAC());
        fn_80021C34(fn_80011FBC());
        fn_80307B58(((MS*)mm)->xbc, ((MS*)mm)->xc0);
        fn_80011838(-1);
    }
}

}
