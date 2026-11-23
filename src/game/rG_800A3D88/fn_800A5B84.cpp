#include "game/rG_800A3D88/types.h"

// Battle body: load the camera model and reset the view state.
extern "C" {
struct Vec { f32 x, y, z; };
struct Cm { u8 p[0x30]; u8 m30; };
struct Body {
    u8 p[0x30];
    Vec m30, m3c, m48, m54;
    f32 m60, m64, m68;
    u8 m6c, m6d, m6e, m6f, m70;
    u8 p71;
    u16 m72;
    u8 p74;
    u8 m75;
    s8 m76;
    u8 p77;
    void* m78;
    void* m7c;
    Cm* m80;
    s16 m84, m86, m88, m8a, m8c, m8e;
    f32 m90;
    void* m94, *m98, *m9c, *mA0, *mA4;
};
extern char lbl_80365064[];
int fn_80290DDC(char*, const char*, ...);
void* fn_80006E1C();
#if TARGET_PC
FE10_PROTO void* fn_8017F37C(const char*, const char*, p32arg);
#else
void* fn_8017F37C(const char*, const char*, int);
#endif
void fn_80009030(void*, void*);
void fn_80009090(void*, void*);
void fn_80006F20(void*);
void fn_80007A00(void*, int);
#if TARGET_PC
FE10_PROTO Cm* fn_8027E824(p32arg);
#else
Cm* fn_8027E824(int);
#endif
#define Z(v) *(u32*)&v.x = 0; *(u32*)&v.y = 0; *(u32*)&v.z = 0
void fn_800A5B84(Body* b) {
    char buf[0x40];
    Vec v0, v1, v2, v3;
    const char* s = lbl_80365064;
    fn_80290DDC(buf, s + 0xDE);
    b->m78 = fn_80006E1C();
    fn_80009030(b->m78, fn_8017F37C(buf, s + 0xE7, 0));
    fn_80009090(b->m78, fn_8017F37C(buf, s + 0xEB, 0));
    fn_80006F20(b->m78);
    fn_80007A00(b->m78, 0x8000000);
    b->m80 = fn_8027E824(4);
    b->m80->m30 = 0;
    b->m6c = 1;
    b->m6d = 0;
    b->m6e = 0;
    b->m6f = 0;
    b->m70 = 0;
    b->m7c = NULL;
    b->m84 = 0;
    b->m86 = 0;
    b->m88 = 0;
    b->m8a = 0;
    b->m8c = 0;
    b->m90 = 0.0f;
    b->m8e = 0;
    b->m94 = NULL;
    b->m98 = NULL;
    b->m9c = NULL;
    b->mA0 = NULL;
    b->mA4 = NULL;
    b->m75 = 0;
    b->m72 = 0;
    Z(v0);
    b->m30 = v0;
    Z(v1);
    b->m3c = v1;
    Z(v2);
    b->m48 = v2;
    Z(v3);
    b->m60 = 1.0f;
    b->m64 = 1.0f;
    b->m68 = 1.0f;
    b->m54 = v3;
    b->m76 = -1;
}
}
