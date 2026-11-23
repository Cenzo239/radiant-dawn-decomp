/* fn_80204EB4: draw of the weapon-type tab strip (8 icons, the selected one lit) followed by the
   selected type's name centred in the remaining width. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
void fn_8007E720(f32);
void fn_801D820C(s16, s16, int, int, int, int);
void fn_801D855C(s16, s16, s16, int);
int fn_800CB0FC(f32, int);
int fn_800CA3DC(f32, const char*, int);
const char* fn_800D0864(const char*);
void fn_800CB3A8(f32, f32, s16, s16, int, int, int, const char*, ...);
extern char lbl_804CAA00[8], lbl_804CA9F8[8], lbl_804CA9F0[8], lbl_804CA9E8[8], lbl_804CA9E0[8], lbl_804CA9D8[8], lbl_804CA9D0[8], lbl_804CA9C8[8], lbl_804CA9C0[8];
}
struct Nd { u8 p[8]; void* x8; };
struct Ctx { u8 p[0x2d]; u8 x2d, x2e; u8 p2f[5]; int x34; Nd* x38; };
class Tab { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(Ctx*);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; void* parent; int sel;
};
static inline void* front(Ctx* c) { if (c->x34 != 0) return c->x38->x8; return 0; }
static inline BOOL lit(Tab* o, Ctx* c) {
    BOOL r = FALSE;
    BOOL b = FALSE;
    if (c->x2d == 0 && c->x2e == 0 && o->parent != 0) b = TRUE;
    if (b) {
        void* p = o->parent;
        if (front(c) == p) r = TRUE;
    }
    return r;
}
extern "C" void fn_80204EB4(Tab* o, Ctx* c) {
    f32 x, y;
    int i;
    int icon;
    s16 w, h;
    s16 rem;
    int ty;
    const char* s;
    o->v18(c);
    x = 0.0f;
    y = x;
    for (i = 0; i < 8; i++) {
        fn_8007E154();
        fn_8007E720(0.01f);
        fn_8007E164();
        switch (i) {
        case 0: icon = 0xb; break;
        case 1: icon = 0xc; break;
        case 2: icon = 0xd; break;
        case 3: icon = 0xe; break;
        case 4: icon = 0xf; break;
        case 5: icon = 0x10; break;
        case 6: icon = 0x16; break;
        case 7: icon = 0x17; break;
        default: icon = 0xb; break;
        }
        fn_801D820C((int)x, (int)y, icon, i == o->sel, lit(o, c), 0x10);
        x += 20.0f;
    }
    w = o->x1 - o->x0;
    h = o->iy1 - o->iy0;
    rem = w - x;
    ty = (h - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    switch (o->sel) {
    case 0: s = fn_800D0864(lbl_804CAA00); break;
    case 1: s = fn_800D0864(lbl_804CA9F8); break;
    case 2: s = fn_800D0864(lbl_804CA9F0); break;
    case 3: s = fn_800D0864(lbl_804CA9E8); break;
    case 4: s = fn_800D0864(lbl_804CA9E0); break;
    case 5: s = fn_800D0864(lbl_804CA9D8); break;
    case 6: s = fn_800D0864(lbl_804CA9D0); break;
    case 7: s = fn_800D0864(lbl_804CA9C8); break;
    default: s = lbl_804CA9C0; break;
    }
    fn_800CB3A8(0.8f, 0.0f, (int)(x + ((rem - fn_800CA3DC(0.8f, s, -1)) >> 1)), (int)(y + ty - 1.0f), 1, 1, 0, s);
    fn_801D855C((int)x, (int)y, rem, 0x10);
}
