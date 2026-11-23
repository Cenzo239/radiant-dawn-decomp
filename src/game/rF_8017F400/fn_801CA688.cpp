/* fn_801CA688: map object animation state set (0 closed, 1 open, 5 play to the last key and re-anchor). */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct Mdl { u32 flags; u8 pad[0x58]; f32 x5C; u8 pad60[0x18]; f32 x78; } Mdl;
typedef struct MInn { u8 pad[0xA]; s16 xA; u8 padC[0xAC]; u32 xB8; u8 padBC[0]; } MInn;
typedef struct MObj {
    u8 x0;
    u8 pad1[3];
    s8 x4, x5, x6, x7;
    u8 pad8[4];
    f32 xC;
    MInn* x10;
    Mdl x14;
} MObj;
typedef struct MCol { u8 pad[0x1C]; u8 r, g, b, a; } MCol;
extern void fn_8000866C(void*, f32);
extern void fn_80007C58(void*);
extern void* fn_8013B9A8(void);
#if TARGET_PC
extern FE10_PROTO void fn_801379F8(void*, int);
#else
extern void* fn_801379F8(void*, int);
#endif
extern void fn_8012D908(void*);
extern void fn_800081D4(void*);
extern void fn_800F15AC(void*, f32, f32, f32);
extern void fn_80083DC4(void*, int);
extern void fn_80083B78(void*);
extern BOOL fn_80008C98(void*, int);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void* fn_800893E4(void*, void*, void*);
extern void* fn_800811E4(void*, void*);
extern void fn_80081A90(void*);
extern void fn_801CA674(void* p, void* arg);
extern u8 lbl_8038ACF8[];
extern u8 lbl_8038AD38[];
extern f32 fn_8001EBC8(int, f32, f32, f32, f32);
extern void fn_801CC5CC(void*, f32, f32, f32, f32);
extern void fn_80008F10(void*, u8, u8, u8);
extern void fn_80008F20(void*, u8);

typedef struct PX {
    u8 pad[0x30];
    MObj* m;
    Mdl* x34;
    f32 x38, x3C, x40;
    int x44;
} PX;
extern void* fn_80007F10(void*);
extern int fn_80009D60(void*, int, u16**);
extern int fn_80007630(void*, const char*);
extern void fn_80007860(void*, int, void*);
extern void fn_80312494(void*, void*);
extern void fn_80312378(void*, void*, void*);
extern char lbl_8036E9AC[];
typedef struct Mtx34 { f32 m[3][4]; } Mtx34;
typedef struct MdlM { u32 flags; u8 pad[0xc]; Mtx34 mtx; } MdlM;
void fn_801CA688(PX* p) {
    /*P*/
    MInn* in;
    Mdl* a;
    MObj* m;
/*E*/
    m = p->m;
    in = m->x10;
    a = &m->x14;
    switch (p->x44) {
    case 0:
        fn_8000866C(a, 0.0f);
        fn_80007C58(a);
        a->x5C = 1.0f;
        break;
    case 1:
        fn_8000866C(a, -1.0f);
        fn_80007C58(a);
        a->x5C = -1.0f;
        break;
    case 5: {
        Mtx34 m1;
        Mtx34 m2;
        u16* list[64];
        int n, v, j;
        a->x5C = 1.0f;
        n = fn_80009D60(fn_80007F10(a), 0x37, list);
        v = n > 0 ? *list[n - 1] : -1;
        if (v > 0) {
            fn_8000866C(a, v);
            fn_80007C58(a);
        }
        if (in->xB8 & 0x01000000) a->flags |= 0x20;
        else a->flags |= 0x10;
        j = fn_80007630(a, lbl_8036E9AC + 0x18);
        if (j >= 0) {
            fn_80007C58(a);
            fn_80007860(a, j, &m1);
            fn_80007C58(a);
            fn_80007860(a, j, &m2);
            fn_80312494(&m2, &m2);
            fn_80312378(&m2, &((MdlM*)a)->mtx, &m2);
            fn_80312378(&m1, &m2, (u8*)a + 0x10);
        }
        break;
    }
    case 2:
        break;
    }
    m->x0 |= 0x10;
}
}
