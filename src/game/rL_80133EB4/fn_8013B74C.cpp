#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw on
struct N { s16 v[4]; void* x8; };
struct Mp { u8 p[0x20000]; };
struct Rain { u8 pad[0x44]; u8* x44; u8* x48; u8* x4c; f32* x50; f32* x54; f32* x58; f32* x5c; };
extern "C" {
extern const char lbl_803694D4[];
extern Mp lbl_803EC898;
extern u8 lbl_803699B0[];
extern void fn_80290DDC(char*, const char*, ...);
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(char*);
#else
extern int fn_80076F54(char*);
#endif
extern void* fn_80077064(char*);
extern u8 fn_8011D1E4(void*);
extern Mesh* fn_80135934(MapModel*, int, u32, u32);
extern void fn_801CA33C(Mesh*, int, int);
extern void fn_80272624(void*, f32);
extern int fn_8030585C(int, int, int, int, int);
extern u8* fn_80078D9C(u32, void*, int);
extern void DCFlushRange(void*, u32);
extern void fn_8017F464(void*, int, u32);
extern u32 fn_80089ED0(void);

#define H(q) (*(s16*)((u8*)(q) + 0x15422))
#define L(q) (*(s16*)((u8*)(q) + 0x1D42C))
#pragma use_lmw_stmw off
static inline MapEntry18* FindE(MapModel* mm, Mesh* m) {
    if (m) {
        MapEntry18* e = mm->lights;
        for (int i = 0; i < 16; e++, i++) {
            if (*(Mesh**)((u8*)e + 0x14) == m) return &mm->lights[i];
        }
    }
    return 0;
}
int fn_8013B74C(MapModel* mm, int pct) {
    int n = 0;
    {
        Mesh* m = mm->mesh;
        int cnt = mm->nMesh;
        for (int i = 0; i < cnt; i++) {
            u32 f = MeshAt(mm, i)->group->flags;
            if (!(f & 0x10) && (f & 0x10000000) == 0x10000000) n++;
        }
    }
    if (n > 0) {
    int k = pct * n / 100;
    if (k == 0 && pct > 0) k = 1;
    if (k > n) k = n;
    for (int i = 0; i < n; i++) {
        Mesh* m = fn_80135934(mm, i, 0x10000000, 0x10);
        if (m) {
            MapEntry18* e = FindE(mm, m);
            if (i < k) {
                fn_801CA33C(m, 0xFF, 0);
                if (e) fn_80272624(e, 1.0f);
            } else {
                fn_801CA33C(m, 0, 0);
                if (e) fn_80272624(e, 0.0f);
            }
        }
    }
    return 1;
    }
    return 0;
}
u32 fn_801436EC(Rain* r) {
    if (r->x48) return 0;
    int a = fn_8030585C(0x20, 0x20, 3, 0, 0);
    int b = a * 2;
    u32 sz = b + 0x4000;
    r->x44 = fn_80078D9C(sz, lbl_803699B0, 0);
    DCFlushRange(r->x44, sz);
    r->x48 = r->x44;
    r->x4c = r->x44 + a;
    fn_8017F464(r->x44, 0x80808080, b);
    u8* q = r->x44 + b;
    r->x50 = (f32*)q;
    r->x54 = (f32*)(q + 0x1000);
    r->x58 = (f32*)(q + 0x2000);
    r->x5c = (f32*)(q + 0x3000);
    fn_8017F464(q, 0, 0x4000);
    for (int y = 0; y < 0x20; y++) {
        for (int x = 0; x < 0x20; x++) {
            int i = x + y * 0x20;
            r->x50[i] = ((f32)(fn_80089ED0() % 100) - 50.0f) / 200.0f;
            r->x54[i] = ((f32)(fn_80089ED0() % 100) - 50.0f) / 200.0f;
            r->x58[i] = ((f32)(fn_80089ED0() % 100) - 50.0f) / 200.0f;
            r->x5c[i] = ((f32)(fn_80089ED0() % 100) - 50.0f) / 200.0f;
        }
    }
    return sz;
}
}
