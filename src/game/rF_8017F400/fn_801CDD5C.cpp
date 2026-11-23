#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
struct Lab { u8 p0[0x40]; char x40[0x20]; void* x60; };
extern char lbl_8036EA00[];
extern int fn_800CA3DC(const char*, int, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8000FF74(p32arg);
#else
extern void fn_8000FF74(int);
#endif
extern void fn_803080DC(int, int, int, int);
extern void fn_80020354(int, int, int, int, C4*, f32);
#if TARGET_PC
extern FE10_PROTO void fn_80020764(int, int, int, int, p32arg);
#else
extern void fn_80020764(int, int, int, int, int);
#endif
extern void fn_80021BA4(int, int, int, int);
extern void fn_800217CC(int);
extern void fn_80021808(int, int, int, int, int);
extern void fn_80021860(int, int, int);
extern void fn_80021FE8(int);
extern void fn_8007EA48(void);
extern void fn_80021C34(int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_80021958(int, C4);
extern void fn_800218A8(int, C4);
extern void fn_800CC8AC(int, int, int, f32, f32, f32, f32, f32, const C4&, const C4&, C4, C4, const char*);
extern void fn_8001F4D8(int, int, int, int, int, int, void*, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_800104DC(p32arg);
#else
extern void fn_800104DC(int);
#endif
extern void fn_80011838(int);
extern char* strcpy(char*, const char*);
static const C4 k0 = {255, 255, 255, 255};
static const C4 k1 = {0, 0, 0, 128};
static const C4 k2 = {0, 0, 0, 255};
static const C4 k3 = {255, 255, 255, 255};
static const C4 k4 = {255, 255, 255, 255};
static inline void TevA(void) { fn_80021958(4, k3); }
static inline void TevB(void) { fn_800218A8(4, k4); }
void fn_801CDD5C(Lab* p) {
    void* tex;
    char* s;
    s = p->x40;
    tex = p->x60;
    int x = (0x80 - fn_800CA3DC(s, -1, 1.0f)) / 2;
    C4 t[4];
    C4 c = k0;
    u32 cw = *(u32*)&c;
    *(u32*)&t[0] = cw; *(u32*)&t[1] = cw; *(u32*)&t[2] = cw; *(u32*)&t[3] = cw;
    fn_8000FF74(0);
    fn_803080DC(0, 0, 0x80, 0x20);
    fn_80020354(0, 0, 0x80, 0x20, t, 0.0f);
    fn_80020764(0, 0, 0x80, 0x20, 0);
    fn_80021BA4(1, 4, 5, 7);
    fn_800217CC(0);
    fn_80021808(4, 0, 1, 0, 0);
    fn_80021860(0, 3, 0);
    fn_80021FE8(1);
    fn_8007EA48();
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x1E);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021EF8(0, 0);
    TevA();
    TevB();
    {
    int y = 2;
    fn_800CC8AC(0, 0, 0x80, x, y, 0.0f, 1.01f, 0.0f, c, c, k1, k2, s);
    }
    fn_8001F4D8(0, 0, 0x80, 0x20, 0x80, 0x20, tex, 6, 1);
    fn_800104DC(0);
    fn_80011838(-1);
    strcpy(p->x40, lbl_8036EA00 + 0x24);
}
}
