#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
struct Clr { u8 r, g, b, a; };
extern char lbl_803694D4[];
extern u8 lbl_803EC898[];
extern void fn_80290DDC(char*, const char*, ...);
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(const char*);
#else
extern int fn_80076F54(const char*);
#endif
extern u8* fn_80077064(const char*);
extern u8 fn_80109A18(u8**);
extern u16 fn_80109A2C(u8**);
extern void fn_80134814(void);
extern void fn_802729A8(MapEntry18*);
struct IVec { int x, y, z; };
void fn_80138E6C(u32* p) {
    MapModel* mm = (MapModel*)p;
    IVec v;
    IVec dead;
    int i;
    MapEntry18* e;
    *(volatile u32*)&p[0x2F] = 0;
    p[0x2D] = 0;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    mm->x4c = 8;
    mm->x4d = 8;
    mm->nGroup = 0;
    mm->nMesh = 0;
    mm->xab = 0;
    mm->xac = 0;
    mm->xad = 0;
    mm->xae = 0;
    mm->xaf = 0;
    mm->xb0 = 0;
    p[5] = 0;
    p[6] = 0;
    p[4] = 0;
    p[0x2F] = 0;
    *(s8*)&mm->x4e = -1;
    *(f32*)&p[0x31] = 1.0f;
    *(f32*)&p[0x32] = 1000.0f;
    fn_80134814();
    ((u8*)p)[0x6A] = 0;
    ((u8*)p)[0x6B] = 0;
    *(f32*)&p[0x1B] = 8.0f;
    *(f32*)&p[0x1C] = 8.0f;
    *(f32*)&p[0x1D] = 1.0f;
    e = mm->lights;
    for (i = 0; i < 16; i++, e++) fn_802729A8(e);
    p[7] = 0;
    p[8] = 0;
    p[9] = 0;
    p[10] = 0;
    p[0xB] = 0;
    p[0xC] = 0;
    p[0xD] = 0;
    p[0xE] = 0;
    p[0xF] = 0;
    p[0x10] = 0;
    p[0x11] = 0;
    p[0x12] = 0;
    ((u8*)p)[0x54] = 0xF8;
    ((u8*)p)[0x55] = 0;
    *(f32*)&p[0x16] = 1.0f;
    ((u8*)p)[0x56] = 0;
    ((u8*)p)[0x57] = 0;
    *(f32*)&p[0x17] = 0.0f;
    ((u8*)p)[0x64] = 0;
    ((u8*)p)[0x60] = 0;
    *(f32*)&p[0x1E] = 0.0f;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    *(f32*)&p[0x35] = *(f32*)&v.x;
    *(f32*)&p[0x36] = *(f32*)&v.y;
    *(f32*)&p[0x37] = *(f32*)&v.z;
    *(f32*)&p[0x38] = 0.0f;
    ((u8*)p)[0xCC] = 0;
    *(int*)&dead.x = 0;
    *(int*)&dead.y = 0;
    *(int*)&dead.z = 0;
}


}
