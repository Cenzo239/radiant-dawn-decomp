#include "game/rG_800A3D88/types.h"
extern "C" {
struct Snd { u8 p[8]; u8 m8; u8 m9; u8 mA; u8 mB; u8 pc[2]; s16 mE, m10, m12, m14, m16; };
struct Vf { u32 x, y, z; };
struct Vg { f32 x, y, z; };
struct Str { u8 p[0xCC]; u8 mCC; u8 pcd[3]; f32 mD0; f32 mD4, mD8, mDC; f32 mE0; };
struct Bg {
    u8 p[0x31];
    u8 m31; s8 m32; u8 m33, m34;
    u8 p35[3];
    f32 m38, m3c, m40, m44, m48;
    u8 m4c, m4d, m4e;
    u8 p4f;
    Str* m50;
    Snd** m54x;
};
struct Bg2 {
    u8 p[0x31];
    u8 m31; s8 m32; u8 m33, m34;
    u8 p35[3];
    f32 m38, m3c, m40, m44, m48;
    u8 m4c, m4d, m4e;
    u8 p4f;
    Str* m50;
    struct SnE* m54;
    void* m58;
};
struct SnE { void* m0; u8 p4[4]; u8 m8; u8 m9; u8 mA; u8 mB; u8 pc[2]; s16 mE, m10, m12, m14, m16; };
void fn_80011CBC(void (*)(), void*);
void fn_8013B974();
void fn_800A66B0(SnE*);
void* fn_800A7B38(void*);
SnE* fn_800A66C4(void*, int);
void fn_800A6618(SnE*);
Str* fn_8013B920(u8);
int fn_80139A7C(Str*, void*, int);
f32 fn_800A84A4(const char*);
void fn_80021754(int*);
void fn_800A6588(SnE*);
void fn_8013AF10(Str*);
void fn_801364AC(Str*);
extern char lbl_8036544C[];
extern const f32 lbl_804CD330, lbl_804CD334, lbl_804CD338;
int fn_800AA548(Bg2* b, void* name, int k) {
    if (b->m50 != NULL) {
        fn_80011CBC(fn_8013B974, NULL);
        b->m50 = NULL;
    }
    SnE* o = b->m54;
    if (o != NULL) {
        if (b->m4d != 0) fn_800A66B0(o);
        b->m54 = NULL;
    }
    b->m58 = NULL;
    b->m58 = fn_800A7B38(name);
    b->m32 = k;
    if (b->m58 == NULL) return 0;
    b->m54 = fn_800A66C4(b->m58, k);
    if (b->m54 == NULL) return 0;
    if (b->m4d != 0) fn_800A6618(b->m54);
    Str* st = fn_8013B920(b->m31);
    b->m50 = st;
    if (fn_80139A7C(st, b->m54->m0, b->m4e != 0 ? 0x20 : 0x2240) == 0) return 0;
    b->m33 = b->m54->mA;
    if (b->m33 == 0) b->m33 = fn_800A84A4(lbl_8036544C);
    b->m34 = b->m54->mB;
    if (b->m34 == 0) b->m34 = fn_800A84A4(lbl_8036544C + 9);
    if (b->m54->m8 & 2) {
        int z = 0;
        fn_80021754(&z);
    }
    fn_800A6588(b->m54);
    SnE* e = b->m54;
    if (e != NULL) {
        if (e->m8 & 8) b->m4c = 1;
        else b->m4c = 0;
        b->m44 = e->m14;
        b->m38 = e->mE;
        b->m3c = e->m10;
        b->m40 = e->m12;
        b->m48 = lbl_804CD338 * (f32)e->m16;
        if (lbl_804CD330 == b->m48) b->m48 = lbl_804CD334;
    }
    if (b->m50 != NULL) {
        if (b->m4c != 0) b->m50->mCC = 1;
        else b->m50->mCC = 0;
        b->m50->mE0 = b->m44;
        Vf v = *(Vf*)&b->m38;
        *(Vg*)&b->m50->mD4 = *(Vg*)&v;
        b->m50->mD0 = b->m48;
        fn_8013AF10(b->m50);
        fn_801364AC(b->m50);
    }
    return 1;
}
}
