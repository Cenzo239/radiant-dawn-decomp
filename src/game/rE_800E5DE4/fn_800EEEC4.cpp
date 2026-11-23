#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct GProc { u8 pad[0x3C]; void* font; u8 pad40[7]; u8 b47; } GProc;
extern "C" {
extern int lbl_804CA498;
extern int lbl_804CA49C;
extern int lbl_804CA4A0;
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_8007E7DC(u8);
extern void fn_8007E7F4(void);
extern void fn_8007E720(f32);
extern void* fn_800CD204(int);
extern void fn_80176B54(int, int, int, void*, int, int, int, int, int, int);
extern void fn_800800D4(int);
extern void fn_80080430(f32, f32, f32, f32, f32, f32);
extern void fn_80080578(int);
extern void fn_80080308(void);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800803C8(f32, f32, f32, f32);
extern void fn_800808F8(f32, f32);
void fn_800EEEC4(GProc* p, int alpha, int idx, int flag, f32 x, f32 y) {
/*P*/
    int d;
    int c;
    int b;
    int a;
    int f2;
    int fl;
    s16 ofs;
/*E*/
    f32 z = 405.0f;
    fl = 0x10;
    if (flag) {
        fl = 0x20;
        z -= 1.0f;
    }
    if (idx > 4) idx = 4;
    if (idx < 0) idx = 0;
    ofs = p->b47 == 0 ? 0 : -8;
    a = 6;
    if (p->b47 == 0) a = 0xB;
    b = 8;
    if (p->b47 == 0) b = 0x10;
    c = 0x48;
    if (p->b47 == 0) c = 0x40;
    d = 0x58;
    if (p->b47 == 0) d = 0x48;
    fn_8007E154();
    fn_8007E4E4(x + ofs, y, z, 1.0f);
    f2 = fl | 1;
    fn_8007E374(p->font, a + idx, f2);
    fn_8007E7DC(alpha);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, c, d);
    fn_80080578(0);
    fn_80080308();
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E374(p->font, b + idx, f2);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, c, d);
    fn_80080578(0);
    fn_80080308();
    fn_8007E7F4();
}
}
