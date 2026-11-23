#include "game/rG_800A3D88/chr.h"

// Battle camera: per-frame matrix update with shake and mirror.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct ModF { u8 p[0x10]; Mtx34 m10; };
struct Tgt { u8 p[0x80]; Tgt* m80; };
struct Body {
    u8 p[0x30];
    Vec m30;
    Vec m3c;
    Vec m48;
    u8 p54[0x60 - 0x54];
    f32 m60;
    u8 p64[4];
    f32 m68;
    u8 p6c[3];
    u8 m6f;
    u8 p70[2];
    u16 m72;
    u8 p74[0x78 - 0x74];
    ModF* m78;
    u8 p7c[0x88 - 0x7C];
    s16 m88, m8a, m8c, m8e;
    f32 m90;
    Tgt* m94;
    Tgt* m98;
};
extern Vec lbl_80365040;
extern Vec lbl_8036504C;
u16* fn_8000F470();
int fn_801D09F0();
void fn_800A47AC(Body*, int);
int fn_80008C98(ModF*, int);
s16 fn_80008CF0(ModF*, int);
void fn_8031292C(Mtx34*, f32, f32, f32);
void fn_8001D748(Mtx34*, f32, f32, f32, int);
void fn_803128AC(Mtx34*, f32, f32, f32);
void fn_80312378(Mtx34*, Mtx34*, Mtx34*);
f32 fn_8001EF30(f32, f32, f32, f32);
double fn_80295940(double);
void fn_803134A8(Vec*, Vec*, f32);
void fn_80312654(Mtx34*, int, f32);
void fn_80312DB4(Mtx34*, Vec*, Vec*);
void* fn_8000FB88();
void fn_80312444(void*, Mtx34*);
u32 fn_80089ED0();
f32 fn_80313508(Vec*);
static inline Tgt* Target(Body* b) {
    Tgt* t = b->m98;
    if (t == NULL) return NULL;
    switch (b->m72 & 0xE000) {
    case 0:
    case 0x4000:
    case 0x8000:
    case 0xA000:
        return t;
    case 0x2000:
        return t->m80;
    case 0x6000:
        return b->m94;
    }
    return NULL;
}
static inline void SetCamMode(Body* b, int m) {
    b->m72 = (b->m72 & 0x1FFF) | m;
}
static inline void Scale(Mtx34* m, f32 k) {
    fn_8031292C(m, k, k, k);
}
void fn_800A53DC(Body* b) {
    Mtx34 scale;
    Mtx34 t;
    Mtx34 rot;
    Mtx34 ab;
    Mtx34 sc;
    u16* fl = fn_8000F470();
    if (fn_801D09F0()) *fl |= 4;
    else *fl &= ~4;
    if (!(b->m72 & 0x10)) fn_800A47AC(b, 1);
    if (fn_80008C98(b->m78, 0x1A)) {
        Tgt* old = Target(b);
        switch (fn_80008CF0(b->m78, 0x1A)) {
        case 0: SetCamMode(b, 0); break;
        case 1: SetCamMode(b, 0x2000); break;
        case 2: SetCamMode(b, 0x4000); break;
        case 3: SetCamMode(b, 0x6000); break;
        case 4: SetCamMode(b, 0x8000); break;
        case 5: SetCamMode(b, 0xA000); break;
        }
        if (old != Target(b)) fn_800A47AC(b, 0);
    }
    f32 z = b->m68;
    f32 y = b->m60;
    Scale(&scale, y * z);
    fn_8001D748(&rot, b->m48.x, b->m48.y, b->m48.z, 1);
    fn_803128AC(&t, b->m30.x, b->m30.y, b->m30.z);
    fn_80312378(&rot, &scale, &ab);
    fn_80312378(&t, &ab, &b->m78->m10);
    if (b->m6f != 0) {
        fn_8031292C(&scale, -1.0f, 1.0f, 1.0f);
        fn_80312378(&b->m78->m10, &scale, &b->m78->m10);
    }
    if (b->m72 & 8) {
        fn_8031292C(&scale, -1.0f, 1.0f, 1.0f);
        fn_80312378(&b->m78->m10, &scale, &b->m78->m10);
    }
    if (b->m88 != 0) {
        Vec v = lbl_80365040;
        b->m8c++;
        f32 a = fn_80295940(fn_8001EF30(0.0f, 6.2831855f, b->m8a, b->m8c));
        a = fn_8001EF30(a, 0.0f, b->m8a, b->m8c);
        fn_803134A8(&v, &v, a * b->m90);
        fn_80312654(&rot, 0x7A, 0.017453292f * (f32)b->m8e);
        fn_80312DB4(&rot, &v, &v);
        fn_80312444(fn_8000FB88(), &ab);
        fn_80312DB4(&ab, &v, &v);
        fn_803128AC(&t, v.x, v.y, v.z);
        fn_80312378(&t, &b->m78->m10, &b->m78->m10);
        if (b->m8c >= b->m8a) {
            b->m8c = 0;
            if (b->m88 > 0) b->m88--;
            if (b->m88 == 0) {
                b->m88 = 0;
                b->m8a = 0;
                b->m8c = 0;
                b->m90 = 0.0f;
                b->m8e = 0;
            } else {
                b->m8e = fn_80089ED0() % 360;
            }
        }
    }
    if (fn_80313508(&b->m3c) > 0.0f) {
        fn_803128AC(&t, b->m3c.x, b->m3c.y, b->m3c.z);
        fn_80312378(&t, &b->m78->m10, &b->m78->m10);
        b->m3c.x = 0.0f;
        b->m3c.y = 0.0f;
        b->m3c.z = 0.0f;
    }
    if ((b->m72 & 2) || (b->m72 & 4)) {
        Vec s = lbl_8036504C;
        if (b->m72 & 2) s.x = -1.0f;
        if (b->m72 & 4) s.z = -1.0f;
        fn_8031292C(&sc, s.x, s.y, s.z);
        fn_80312378(&b->m78->m10, &sc, &b->m78->m10);
    }
}
}
