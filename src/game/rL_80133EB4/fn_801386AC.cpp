/* Map model: minimap render target, global object, sound and misc. queries. */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

struct MiniMap {
    f32 x, y, w, h;  /* 0x00 */
    f32 tw, th;      /* 0x10 */
    u8 pad18[4];
    void* tex;       /* 0x1C */
};

extern MiniMap* lbl_804CB85C;
extern MapModel* lbl_804CB860;
extern volatile u32 lbl_804CB5F4;
extern u8 lbl_804CB830;
extern char lbl_803694D4[];
extern u8 lbl_803EC898[];
extern u8 lbl_80386090[];

extern void fn_8001F4D8(int, int, int, int, int, int, void*, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_800104DC(p32arg);
#else
extern void fn_800104DC(int);
#endif
extern void fn_80011274(void);
extern void* fn_8000F470(void);
extern void fn_8000F468(void*);
extern void fn_8000F48C(void*);
extern void* fn_80078D9C(int, const char*, int);
extern void* fn_80078CCC(int, const char*, int);
extern void fn_80011B58(void*);
extern void fn_80078E24(void*);
extern void fn_80079210(void*);
extern void fn_800846BC(void*);
extern void fn_80010788(int, int, void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_801384E4(void *);
#else
extern void fn_801384E4(void);
#endif
extern void fn_80138628(void);
extern void fn_801CC2BC(Mesh*, int, int);
extern void fn_80305A40(void*, void*, u16, u16, int, int, int, int);
extern void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
extern void fn_80138A78(MapModel*, void*, f32, f32, f32, f32, f32, f32);
extern void fn_80134814(void);
extern void fn_80138E6C(MapModel*);
extern void fn_802729A8(MapEntry18*);
#if TARGET_PC
extern FE10_PROTO void fn_802726C8(MapEntry18*, ptr32<const void>);
#else
extern void fn_802726C8(MapEntry18*, void*);
#endif
extern void* fn_802729F8(MapEntry18*);
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(const char*);
#else
extern int fn_80076F54(const char*);
#endif
extern int* fn_80077064(const char*);
extern int fn_80291188(const char*, const char*);
extern void fn_80290DDC(char*, const char*, ...);
extern void* fn_8017F37C(char*, const char*, const char*);
extern int fn_8023F9F4(void*);
#if TARGET_PC
extern FE10_PROTO void fn_8023F1A0(void*, ptr32<const void>);
#else
extern void fn_8023F1A0(void*, void*);
#endif
extern Mesh* fn_80135934(MapModel*, int, u32, u32);
extern void fn_801CA33C(Mesh*, int, int);
extern void fn_80272624(void*, f32);

void fn_80138628(void) {
    int w = (int)lbl_804CB85C->tw;
    int h = (int)lbl_804CB85C->th;
    fn_8001F4D8(0, 0, w, h, w, h, lbl_804CB85C->tex, 4, 1);
    fn_800104DC(0);
    fn_80011274();
}

void fn_80138764(u8* p) {
    u8* v;
    *(void**)(p + 0x54) = fn_8000F470();
    v = (u8*)fn_80078D9C(-0x150, lbl_803694D4 + 0x103, 0);
    fn_8000F468(v);
    fn_8000F48C(v);
    *(void**)(v + 0x120) = fn_80078D9C(-0x4000, lbl_803694D4 + 0x103, 0);
    *(u16*)(v + 0x126) = 0x400;
    fn_80011B58(v);
    *(u8**)(p + 0x58) = v;
    lbl_804CB5F4 |= 8;
}

void fn_80138968(u8* p) {
    u8* v;
    fn_8000F468(*(void**)(p + 0x54));
    v = *(u8**)(p + 0x58);
    fn_80078E24(*(void**)(v + 0x120));
    *(void**)(v + 0x120) = 0;
    fn_80078E24(v);
    lbl_804CB5F4 &= ~8;
}

void fn_801389C0(MapModel* mm, int a, int b, void* c) {
    fn_80138A78(mm, c, (s32)mm->x4c / 2.0f, (s32)mm->x4d / 2.0f, (s32)(mm->x4c - mm->xb0 * 2), (s32)(mm->x4d - mm->xb0 * 2), a, b);
}

void fn_80138D6C(void) {
    if (lbl_804CB85C) {
        fn_800846BC(lbl_80386090);
        fn_80078E24(lbl_804CB85C->tex);
        lbl_804CB85C->tex = 0;
        if (lbl_804CB85C) {
            fn_80079210(lbl_804CB85C);
            lbl_804CB85C = 0;
        }
    }
}

void fn_80138DD4(void* a, void* b) {
    fn_80305A40(b, lbl_804CB85C->tex, (u16)lbl_804CB85C->tw, (u16)lbl_804CB85C->th, 4, 0, 0, 0);
    fn_80305C94(b, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
}

void fn_8013AAB4(MapModel* mm, void* m) {
    int i;
    for (i = 0; i < 16; i++) fn_802726C8(&mm->lights[i], m);
}

class SndObj {
public:
    virtual void v08();
    virtual void v0C();
    virtual int v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28(void*);
    virtual void v2C(void*);
};

void fn_8013AB10(MapModel* mm, void* a) {
    int i;
    for (i = 0; i < 16; i++) {
        SndObj* o = (SndObj*)fn_802729F8(&mm->lights[i]);
        if (o && o->v10()) o->v28(a);
    }
}

void fn_8013ABAC(MapModel* mm, void* a) {
    int i;
    for (i = 0; i < 16; i++) {
        SndObj* o = (SndObj*)fn_802729F8(&mm->lights[i]);
        if (o && o->v10()) o->v2C(a);
    }
}

void fn_8013B5E4(MapModel* mm) {
    int i;
    *(f32*)((u8*)mm + 0x78) = 0.0f;
    if (mm->flags & 0x20) {
        for (i = 0; i < mm->nMesh; i++) {
            Mesh* m = MeshAt(mm, i);
            if (m->group->flags & 0x80) {
                f32 v = 0.0f;
                switch (mm->xb1) {
                case 0:
                    v = m->minz;
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                    v = m->maxy;
                    break;
                }
                *(f32*)((u8*)mm + 0x78) = v;
                return;
            }
        }
    }
}

static inline int CountBlocks(MapModel* mm) {
    int n = 0;
    int i;
    for (i = 0; i < mm->nMesh; i++) {
        u32 f = mm->mesh[i].group->flags;
        if ((f & 0x10) == 0 && (f & 0x10000000) == 0x10000000) n++;
    }
    return n;
}

MapModel* fn_8013B920(u8 a) {
    lbl_804CB860 = (MapModel*)fn_80078CCC(0x294, lbl_803694D4 + 0x103, 0);
    fn_80138E6C(lbl_804CB860);
    lbl_804CB860->xb1 = a;
    return lbl_804CB860;
}

} /* extern "C" */
