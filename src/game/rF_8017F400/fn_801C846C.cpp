#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct Vec3 { f32 x, y, z; };
struct V3 : Vec3 { V3(const Vec3& o) { x = o.x; y = o.y; z = o.z; } };
struct UQ { u32 x0; u8 p4[0xA]; s8 xE; u8 pF[4]; s8 x13; s8 x14; };
extern u8 lbl_803C8E80[];
extern UQ lbl_803CA870;
extern u8 lbl_803CB770[];
extern u8 lbl_803CAB38[];
extern u8 lbl_803EC898[];
extern char lbl_8036E538[];
#if TARGET_PC
extern FE10_PROTO void fn_80026CD8(u8*, p32arg, int);
#else
extern void fn_80026CD8(u8*, u32, int);
#endif
extern void fn_8002C474(u8*, int);
extern void fn_8006625C(u8*, int, int, int);
extern void* fn_80044FD0(UQ*);
extern int fn_80110DA8(void*);
extern u8* fn_800661A0(u8*, int, int, int, u8);
extern void fn_80065E4C(u8*, int);
extern Vec3 fn_80118B94(u8*, int, int);
extern void fn_802549C4(const char*, f32, const Vec3&);
int fn_801C846C(void) {
    fn_80026CD8(lbl_803C8E80, lbl_803CA870.x0, -1);
    fn_8002C474(lbl_803C8E80, (s8)*(u8*)&lbl_803CA870.xE);
    {
    s8 x = lbl_803CA870.x13;
    s8 y = lbl_803CA870.x14;
    fn_8006625C(lbl_803CB770, x, y, 0xC);
    {
    int k = fn_80110DA8(fn_80044FD0(&lbl_803CA870));
    u8* r = fn_800661A0(lbl_803CB770, x, y, 0xC, (u8)k);
    r[4] = lbl_803CAB38[0x11];
    fn_80065E4C(r, 0x1E);
    }
    {
    Vec3 t = fn_80118B94(lbl_803EC898, x, y);
    fn_802549C4(lbl_8036E538 + 0x3B, 0.0f, V3(t));
    }
    }
    return 1;
}
}
