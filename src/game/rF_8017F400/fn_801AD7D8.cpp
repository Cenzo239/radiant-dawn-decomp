#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
struct TexH { u16 x0, x2; };
struct Bar { u8 pad[0x32]; u8 x32; u8 p33[9]; s16 x3C, x3E; u8 p40[4]; const char* x44; };
extern void* lbl_804CB58C;
extern u8 lbl_804CF0D8[8];
extern void* fn_80006A0C(void*, int);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080308(void);
extern void fn_80080578(int);
struct W { u32 v; };
extern void fn_80080940(C4, W, C4, W);
extern void fn_801BCA5C(f32);
extern const char* fn_800D0864(const char*);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);

static const C4 kA = {0, 0, 0, 160};
static const C4 kB = {0, 0, 0, 160};
void fn_801AD7D8(Bar* p) {
    void* arch = lbl_804CB58C;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 9.0f, 1.0f);
    fn_8007E7DC(p->x32);
    fn_8007E164();
    {
    TexH* q = *(TexH**)fn_80006A0C(arch, 2);
    u16 w;
    u16 h;
    h = q->x0 - 4;
    w = q->x2;
    fn_8007E154();
    fn_8007E174(0, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(p->x3C, p->x3E, w, h);
    fn_800804D4(0, 0, 0, 0xA0);
    fn_80080308();
    fn_800800D4(3);
    fn_80080388(p->x3C + w, p->x3E, 32.0f, h);
    fn_80080578(0);
    }
    {
    W w;
    w.v = 0;
    fn_80080940(kA, w, kB, w);
    }
    fn_80080308();
    fn_801BCA5C(-0.1f);
    {
    int wd = fn_800CA3DC(fn_800D0864(p->x44), -1, 1.0f);
    f32 fw = wd;
    int x = (int)((f32)(p->x3C + 0x4E) - 0.5f * fw);
    s16 y = p->x3E;
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_800CB3A8(1.0f, 0.0f, x, y, 0xD, 0, 0, fn_800D0864(p->x44));
    }
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}
}
