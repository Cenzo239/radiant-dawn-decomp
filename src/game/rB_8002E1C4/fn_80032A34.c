#include "game/rB_8002E1C4/types.h"

extern const f32 lbl_804CCD24; /* -1.0f */
extern const f32 lbl_804CCD28; /* 1.0f */
extern void* lbl_804CB58C;     /* UI texture archive */

typedef struct TexObj { u8 data[0x20]; } TexObj;
typedef struct Tex { TexObj tex; u16 w; u16 h; } Tex;
void fn_8006E030(f32 a);
void fn_80006A64(void* arc, TexObj* tex, u16 id);
u16 fn_80305DF8(TexObj* tex); /* GXGetTexObjWidth */
u16 fn_80305E0C(TexObj* tex); /* GXGetTexObjHeight */
void fn_8007E154(void);
void fn_8007E174(TexObj* tex, int a);
void fn_8007E164(void);
void fn_800800D4(int a);
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080308(void);

/* draw weapon-advantage arrow icon */
void fn_80032A34(int kind, int x, int y)
{
    int id;
    Tex t;
    switch (kind) {
    case 0: id = 0x30; break;
    case 1: id = 0x31; break;
    case 2: id = -1; break;
    case 3: id = 0x32; break;
    case 4: id = 0x33; break;
    }
    if (id < 0) return;
    fn_8006E030(lbl_804CCD24);
    fn_80006A64(lbl_804CB58C, &t.tex, id);
    t.w = fn_80305DF8(&t.tex);
    t.h = fn_80305E0C(&t.tex);
    fn_8007E154();
    fn_8007E174(&t.tex, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(x + 0xd8, y + ((0x1c - t.h) >> 1), t.w, t.h);
    fn_80080308();
    fn_8006E030(lbl_804CCD28);
}
