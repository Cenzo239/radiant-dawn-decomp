/* fn_801386AC (round 22, agent r22b): class `sched`, 4 masked words differ.
 * Proposed name: MiniMap::CellToTexel(x, y, out). Map cell (x, y) to minimap texture
 * coordinates: s = tw / w; out = s * (cell centre - (origin - half extent)), out->z = 0;
 * returns 0 when the point falls outside [0, tw] on either axis.
 * Built with tools/equiv/mkself.py from ../fn_801386AC.cpp and the wip/near.cpp section.
 * Differences: the two int-to-float conversions and the origin loads are scheduled a few
 * slots apart (same instructions per block). symcheck --anon --xargs: 7 blocks, 0 differ.
 */
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
extern void fn_800104DC(int);
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
extern void fn_801384E4(void);
extern void fn_80138628(void);
extern void fn_801CC2BC(Mesh*, int, int);
extern void fn_80305A40(void*, void*, u16, u16, int, int, int, int);
extern void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
extern void fn_80138A78(MapModel*, void*, f32, f32, f32, f32, f32, f32);
extern void fn_80134814(void);
extern void fn_80138E6C(MapModel*);
extern void fn_802729A8(MapEntry18*);
extern void fn_802726C8(MapEntry18*, void*);
extern void* fn_802729F8(MapEntry18*);
extern int fn_80076F54(const char*);
extern int* fn_80077064(const char*);
extern int fn_80291188(const char*, const char*);
extern void fn_80290DDC(char*, const char*, ...);
extern void* fn_8017F37C(char*, const char*, const char*);
extern int fn_8023F9F4(void*);
extern void fn_8023F1A0(void*, void*);
extern Mesh* fn_80135934(MapModel*, int, u32, u32);
extern void fn_801CA33C(Mesh*, int, int);
extern void fn_80272624(void*, f32);
void fn_80138628(void);

void fn_80138764(u8* p);

void fn_80138968(u8* p);

void fn_801389C0(MapModel* mm, int a, int b, void* c);

void fn_80138D6C(void);

void fn_80138DD4(void* a, void* b);

void fn_8013AAB4(MapModel* mm, void* m);


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
void fn_8013AB10(MapModel* mm, void* a);

void fn_8013ABAC(MapModel* mm, void* a);

void fn_8013B5E4(MapModel* mm);


static inline int CountBlocks(MapModel* mm) {
    int n = 0;
    int i;
    for (i = 0; i < mm->nMesh; i++) {
        u32 f = mm->mesh[i].group->flags;
        if ((f & 0x10) == 0 && (f & 0x10000000) == 0x10000000) n++;
    }
    return n;
}
MapModel* fn_8013B920(u8 a);


} /* extern "C" */


/* ---- from build/tmp/r22b/fr_386b.cpp ---- */
extern "C" {
extern "C" {
BOOL fn_801386AC(void* a, int x, int y, Vec* out) {
    f32 zero = 0.0f;
    MiniMap* m = lbl_804CB85C;
    f32 tw = m->tw;
    f32 s = tw / m->w;
    f32 fx = s * ((0.5f + x) - -(m->w * 0.5f - m->x));
    f32 fy = s * ((0.5f + y) - -(m->h * 0.5f - m->y));
    out->z = zero;
    out->x = fx;
    out->y = fy;
    if (fx < zero || fy < zero || fx > tw || fy > tw) return 0;
    return 1;
}
}
}
