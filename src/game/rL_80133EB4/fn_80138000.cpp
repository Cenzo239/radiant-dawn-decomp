/* Map model: tile data from roof panels, setup, teardown and per-frame environment. */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

extern u8 lbl_804CB830;
extern u8 lbl_804CB834;
extern u8 lbl_803CB770[];
extern char lbl_803694D4[];

extern int fn_801CA1E8(Mesh*);
extern int fn_801CA228(Mesh*);
extern int fn_801CA260(Mesh*);
extern void fn_80134814(void);
extern void fn_802729A8(MapEntry18*);
extern int fn_800660E8(void*);
extern void fn_80065FB0(void*, int);
extern void fn_80081A90(void*);
extern void fn_801CBA0C(void);
extern void fn_8001D424(void*);
extern void fn_8023F4EC(const char*);
#if TARGET_PC
extern FE10_PROTO void fn_802726C8(MapEntry18*, ptr32<const void>);
#else
extern void fn_802726C8(MapEntry18*, void*);
#endif
extern void fn_80078E24(void*);
extern void fn_8014857C(void);
extern void fn_8010DC58(const char*);
extern void fn_80250D64(f32, f32, int);
extern void fn_80250E38(f32, f32, int);
extern void fn_80006EE0(void*);
extern void fn_80079210(void*);
extern void fn_80079474(void*);
extern void fn_800761F0(void*);
#if TARGET_PC
extern FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
extern void fn_8023F1A8(void*);
#endif
extern void fn_8023FC00(void);
#if TARGET_PC
extern FE10_PROTO void fn_8000FA18(f32, f32, p32arg);
#else
extern void fn_8000FA18(f32, f32, int);
#endif
extern void fn_80010AB8(void);
extern void fn_80021754(void*);
extern void fn_8010E41C(u8*, int);

static inline BOOL InRect(Mesh* m, int x, int y) {
    int x0 = m->x0;
    int y0 = m->y0;
    int x1 = m->x1;
    int y1 = m->y1;
    return x >= x0 && x <= x1 && y >= y0 && y <= y1;
}

BOOL fn_8013818C(MapModel* mm, int x, int y) {
    Mesh* m;
    int i;
    if (!(mm->flags & 0x10000000)) return 0;
    m = mm->mesh;
    for (i = 0; i < mm->nMesh; i++, m++) {
        if (fn_801CA1E8(m) && fn_801CA228(m) == 0 && fn_801CA260(m)) {
            int x0 = m->x0;
            int y0 = m->y0;
            int x1 = m->x1;
            int y1 = m->y1;
            if (x >= x0 && x <= x1 && y >= y0 && y <= y1) return 1;
        }
    }
    return 0;
}


void fn_8013A35C(MapModel* mm) {
    switch (mm->flags & 0xC0000) {
    case 0x80000:
        lbl_804CB830 = 1;
        break;
    case 0xC0000:
        lbl_804CB830 = 2;
        break;
    case 0x40000:
        lbl_804CB830 = 3;
        break;
    default:
        lbl_804CB830 = 0;
        break;
    }
    switch (mm->flags & 0x1F00000) {
    case 0x000000: lbl_804CB834 = 0; break;
    case 0x100000: lbl_804CB834 = 1; break;
    case 0x1100000: lbl_804CB834 = 2; break;
    case 0x1500000: lbl_804CB834 = 3; break;
    case 0x200000: lbl_804CB834 = 4; break;
    case 0x300000: lbl_804CB834 = 5; break;
    case 0x400000: lbl_804CB834 = 6; break;
    case 0x500000: lbl_804CB834 = 7; break;
    case 0x600000: lbl_804CB834 = 8; break;
    case 0x700000: lbl_804CB834 = 9; break;
    case 0x1200000: lbl_804CB834 = 10; break;
    case 0x800000: lbl_804CB834 = 11; break;
    case 0x1300000: lbl_804CB834 = 12; break;
    case 0x900000: lbl_804CB834 = 13; break;
    case 0xA00000: lbl_804CB834 = 14; break;
    case 0xB00000: lbl_804CB834 = 15; break;
    case 0xC00000: lbl_804CB834 = 16; break;
    case 0xD00000: lbl_804CB834 = 17; break;
    case 0x1000000: lbl_804CB834 = 18; break;
    case 0xF00000: lbl_804CB834 = 19; break;
    case 0x1400000: lbl_804CB834 = 20; break;
    case 0xE00000: lbl_804CB834 = 21; break;
    default: lbl_804CB834 = 0; break;
    }
}

extern u8* lbl_804CB810;

static inline u8* UnitGet(int id) {
    u8 n = id;
    return n ? lbl_804CB810 + (n - 1) * 0x3F0 : 0;
}

static inline void Reset16(MapModel* mm) {
    int j;
    for (j = 0; j < 16; j++) fn_802726C8(&mm->lights[j], 0);
}

static inline u32 MapLoaded(MapModel* mm) { return *(volatile u32*)&mm->flags & 0x40000000; }

void fn_8013A054(MapModel* mm) {
    u32* p = (u32*)mm;
    if (MapLoaded(mm)) {
        int i;
        u32 z;
        u8 tbl[0xB];
        mm->flags &= ~0x40000000;
        for (i = 0; i < fn_800660E8(lbl_803CB770); i++) {
            fn_80065FB0(*(u8**)lbl_803CB770 + i * 8, 0);
        }
        fn_80081A90((void*)p[6]);
        fn_80081A90((void*)p[5]);
        fn_80081A90((void*)p[4]);
        p[4] = 0;
        p[5] = 0;
        p[6] = 0;
        fn_801CBA0C();
        fn_8001D424((void*)p[0x1F]);
        fn_8023F4EC(lbl_803694D4 + 0x17F);
        Reset16(mm);
        switch (mm->xb1) {
        case 0:
            if (p[0x2F]) {
                fn_80078E24((void*)p[0x2F]);
                p[0x2F] = 0;
            }
            fn_8014857C();
            fn_8010DC58(mm->name);
            fn_80250D64(1.0f, 250.0f, 7);
            fn_80250E38(1.0f, 250.0f, 7);
        }
        {
            int k;
            for (k = 0; k < mm->nMesh; k++) fn_80006EE0(mm->mesh[k].pos14);
        }
        {
            int k;
            for (k = 0; k < mm->nGroup; k++) fn_80006EE0((u8*)&mm->group[k] + 4);
        }
        if (mm->quad) {
            fn_80079210(mm->quad);
            mm->quad = 0;
        }
        if (mm->group) {
            fn_80079474(mm->group);
            mm->group = 0;
        }
        if (mm->mesh) {
            fn_80079474(mm->mesh);
            mm->mesh = 0;
        }
        if (mm->x04) {
            fn_800761F0(mm->x04);
            mm->x04 = 0;
        }
        if (p[0]) {
            fn_8023F1A8((void*)p[0]);
            p[0] = 0;
        }
        mm->nMesh = 0;
        mm->nGroup = 0;
        fn_80134814();
        fn_8023FC00();
        fn_8000FA18(2.0f, 2000.0f, 0);
        fn_80010AB8();
        z = 0;
        fn_80021754(&z);
        fn_8010E41C(tbl, 5);
        for (i = 1; i < 0xFF; i++) {
            u8* u = UnitGet(i);
            if (*(void**)(u + 0xEC) && tbl[*(*(u8**)(u + 0xF4) + 8)]) *(u16*)(u + 0x37E) = 0;
        }
    }
}

#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_8011D1E4(void*);
#else
extern void* fn_8011D1E4(void*);
#endif
extern void fn_80290DDC(char*, const char*, ...);
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(char*);
#else
extern int fn_80076F54(char*);
#endif
extern u8* fn_80077064(char*);
extern u8 lbl_803EC898[];

struct MapH {
    u8 pad0[0x100D];
    s8 ter[64 * 64];     /* 0x100D */
    u8 pad200D[0x15422 - 0x200D];
    s16 hgt[0x4000];     /* 0x15422 */
    u8 pad1D422[0x1D42C - 0x1D422];
    s16 hgt2[0x4000];    /* 0x1D42C */
};

extern void fn_80133EB4(void*);
extern void fn_80134140(void*);
extern void fn_80134024(void*);
extern void fn_80010BB0_(void);

} /* extern "C" */
