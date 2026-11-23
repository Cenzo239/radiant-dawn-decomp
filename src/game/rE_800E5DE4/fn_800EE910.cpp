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
void fn_800EE910(GProc* p, int alpha, int s1, int s2, int flag, f32 x, f32 y, f32 tx, f32 ty) {
/*P*/
    int b;
    int a;
    int w;
    s16 ofs;
    int fl;
/*E*/
    f32 z = 401.0f;
    fl = 0x10;
    if (flag) {
        fl = 0x20;
        z -= 1.0f;
    }
    ofs = p->b47 == 0 ? 0 : -8;
    w = 0x1F;
    if (p->b47 == 0) w = 0x1B;
    a = 0x34;
    if (p->b47 == 0) a = 0x2F;
    b = 0x34;
    if (p->b47 == 0) b = 0x2B;
    fn_8007E154();
    fn_8007E4E4(x + ofs, y, z, 1.0f);
    int f2 = fl | 1;
    fn_8007E374(p->font, 0x19, f2);
    fn_8007E7DC(alpha);
    fn_8007E164();
    {
        int h = 0x18;
        fn_80176B54(w + tx, h + ty, 2, fn_800CD204(1), 0, 0, 0x11, 0x17, 0xF, s1);
    }
    fn_8007E154();
    fn_8007E374(p->font, 0x1A, f2);
    fn_8007E164();
    fn_80176B54(a, b, 2, fn_800CD204(4), 0, 0, 0xB, 0xF, 9, s2);
    fn_8007E7F4();
}
}
