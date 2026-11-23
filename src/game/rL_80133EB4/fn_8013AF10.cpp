/* Sets the map's environment audio parameters. */
#include "game/rL_80133EB4/map3d.h"
struct Env {
    u8 pad[0x6A];
    u8 a, b;
    f32 x, y, z;
    u8 pad78[0xD0 - 0x78];
    f32 scale;
};
extern "C" {
extern void fn_8025095C(f32, f32);
extern void fn_80250A08(f32, f32);
extern void fn_80257AC0(f32, f32);
extern void fn_80257B6C(f32, f32);
extern void fn_80257A14(f32, f32);

void fn_8013AE18(Env* e) {
    f32 sc, xx, yy, b, x, a, y, z;
a = e->a / 127.0f; b = e->b / 127.0f; sc = 5.0f * e->scale; z = e->z; xx = e->x; yy = e->y; x = xx * sc; y = yy * sc;    fn_8025095C(a - 1.0f, 0.0f);
    fn_80250A08(b, 0.0f);
    fn_80257AC0(x, 0.0f);
    fn_80257B6C(y, 0.0f);
    fn_80257A14(z, 0.0f);
}

static inline void EnvSet(Env* e) {
    f32 yy, z, b, x, xx, y, sc, a;
a = e->a / 127.0f; b = e->b / 127.0f; sc = 5.0f * e->scale; z = e->z; xx = e->x; yy = e->y; x = xx * sc; y = yy * sc;    fn_8025095C(a - 1.0f, 0.0f);
    fn_80250A08(b, 0.0f);
    fn_80257AC0(x, 0.0f);
    fn_80257B6C(y, 0.0f);
    fn_80257A14(z, 0.0f);
}
struct MMx {
    u8 pad0[0xC];
    Mesh* mesh;
    u8 pad10[0x52 - 0x10];
    s16 nMesh;
    u8 pad54[0xB1 - 0x54];
    u8 xb1;
    u8 padb2[0xCC - 0xB2];
    u8 xcc;
    u8 padcd[0xD0 - 0xCD];
    f32 scale;
    Vec t;
    f32 rot;
    u8 xe4[0x30];
    MapEntry18 lights[16];
};
extern void fn_80312654(void*, int, f32);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_80312344(void*, void*);
extern void fn_80312318(void*, f32);
extern void fn_801CC5CC(Mesh*, f32, f32, f32, f32);
extern void fn_801CCC44(Mesh*, int);
extern void fn_801CCCA0(Mesh*);
extern void fn_8013826C(void*);
extern void fn_8013B5E4(void*);
extern void fn_802727A0(MapEntry18*, void*);
void fn_8013AF10(MMx* mm) {
    u8 a[0x30];
    u8 s[0x30];
    u8 r[0x30];
    u8 t[0x30];
    u8 base[0x30];
    u8 mG[0x30];
    u8 mF[0x30];
    u8 mE[0x30];
    /*P*/
    int i2;
    Mesh* m;
    MapEntry18* w;
    u8 mirror;
    int i;
/*E*/
    switch (mm->xb1) {
    case 0:
        fn_80312654(a, 0x58, 4.712389f);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        ((void(*)(void*))fn_80312318)(a);
        break;
    }
    {
        Vec v = mm->t;
        fn_803128AC(t, v.x, v.y, v.z);
    }
    { f32 q = mm->rot; fn_80312654(r, 0x79, 0.017453292f * q); }
    mirror = mm->xcc;
    if (mirror) {
        fn_8031292C(s, -1.0f, 1.0f, 1.0f);
    } else {
        ((void(*)(void*))fn_80312318)(s);
    }
    fn_80312378(r, t, base);
    fn_80312378(s, base, base);
    fn_80312378(a, base, base);
    fn_80312344(base, mm->xe4);
    {
        m = mm->mesh;
        for (i = 0; i < mm->nMesh; i++, m++) {
            fn_801CC5CC(m, 0.0f, 0.0f, 0.0f, 0.0f);
            fn_801CCC44(m, mirror);
            fn_801CCCA0(m);
        }
    }
    fn_8013826C(mm);
    fn_8013B5E4(mm);
    EnvSet((Env*)mm);
    {
        f32 sc = 5.0f * mm->scale;
        fn_80312318(mE, 5.0f);
        fn_80312654(mF, 0x58, -4.712389f);
        fn_8031292C(mG, sc, sc, sc);
        fn_80312344(mm->xe4, mE);
        fn_80312378(mE, mG, mE);
        fn_80312378(mE, mF, mE);
        {
            w = mm->lights;
            for (i2 = 0; i2 < 16; i2++, w++) fn_802727A0(w, mE);
        }
    }
}

}
