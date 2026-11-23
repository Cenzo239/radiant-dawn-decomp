#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
struct TexH { u16 x0, x2; };
typedef struct LData { void* arch; u8 p4[0x10]; void* x14; u8 p18[0x10]; int x28; } LData;
extern LData* lbl_804CB9BC;
extern char lbl_8036DCE0[];
extern void fn_801B2150(void);
extern void fn_801B3688(void);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void* fn_80006A0C(void*, int);
extern const u8* fn_800CD204(int);
extern void fn_801BC88C(void* a, int b, C4* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern const char* fn_800D0864(const char*);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_801C6D9C(const char*, int, int, int);
extern void fn_80179A84(void*);

void fn_801B378C(void) {
    C4 c;
    C4 t;
/*P*/
    u16 h;
    u16 w;
    const char* s;
/*E*/
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E4E4(0.0f, 0.0f, 150.0f, 1.0f);
    fn_8007E164();
    {
    TexH** q = (TexH**)fn_80006A0C(lbl_804CB9BC->arch, 0);
    w = (*q)->x2;
    h = (*q)->x0;
    const u8* cp = fn_800CD204(1);
    c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = 0xFF;
    q = (TexH**)fn_80006A0C(lbl_804CB9BC->arch, 0);
    {
    f32 x = 0.0f;
    u16 tw = (*q)->x2, th = (*q)->x0;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(lbl_804CB9BC->arch, 0, &t, 0x11, 0, x, x, x + w, x + h, x, x, tw, th);
    }
    }
    {
    char* b = lbl_8036DCE0;
    s = fn_800D0864(b + 0x11F);
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    fn_800CB3A8(0.8f, 0.0f, 0x1D8 - fn_800CA3DC(s, -1, 1.0f) / 2, 0x1E, 0x37, 1, 0, s);
    fn_801BCA5C(1.0f);
    fn_801B2150();
    fn_801B3688();
    switch (lbl_804CB9BC->x28) {
    case 2: s = fn_800D0864(b + 0x125); break;
    case 1: s = fn_800D0864(b + 0x131); break;
    case 0: s = fn_800D0864(b + 0x13C); break;
    }
    }
    fn_801BCA5C(-7.0f);
    fn_801C6D9C(s, 0xFF, 0xFF, 0);
    fn_801BCA5C(7.0f);
    fn_80179A84(lbl_804CB9BC->x14);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}
}
