/* Is the map camera still moving, 8012FD80. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_804CB820;
extern u8 lbl_804CB838;
extern u8 lbl_804CB818;
extern u8 lbl_804CB819;
extern u8 lbl_803CAB38[];
struct View {
    u16 flags;
    u8 pad[0xd2];
    Vec d4; Vec e0; Vec ec; Vec f8;
    f32 v104; f32 v108; f32 v10c;
};
struct CamBase {
    View* view;
    Vec a;       /* 0x04 */
    Vec b;       /* 0x10 */
    int mode;    /* 0x1C */
    Vec mn;      /* 0x20 */
    Vec mx;      /* 0x2C */
    Vec cur;     /* 0x38 */
    Vec tgt;     /* 0x44 */
    Vec v50;     /* 0x50 */
    Vec col;     /* 0x5C */
    f32 v68;     /* 0x68 */
};
class Cam : public CamBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual f32 v4(int);
    virtual void v5();
};
extern Cam* lbl_804CB81C;
struct Fl { u8 pad[0x93c]; f32 x; f32 y; u8 pad2[8]; f32 z; };
static inline bool M1(Cam*& c, int b) {
    c = lbl_804CB81C;
    if (c == 0) return false;
    if (lbl_804CB820 == 0 && (lbl_804CB838 & 8) == 0) {
        Fl* f = (Fl*)lbl_803CAB38;
        c->tgt.x = f->x;
        c->tgt.y = f->y;
        c->tgt.z = f->z;
    }
    c = lbl_804CB81C;
    {
    f32 e = 1.0f; if (b) e = 0.1f;
    if ((f32)__fabs(c->tgt.x - c->cur.x) > e) return true;
    return (f32)__fabs(c->tgt.y - c->cur.y) > e;
    }
}
static inline bool M2(Cam* c, int b) {
    if (c == 0) return false;
    {
    f32 e = 10.0f; if (b) e = 1.0f;
    if ((f32)__fabs(c->a.x - c->b.x) > e) return true;
    if ((f32)__fabs(c->a.y - c->b.y) > e) return true;
    return (f32)__fabs(c->a.z - c->b.z) > e;
    }
}
static inline int F2(Cam* c, int b) { if (M2(c, b) == true) return 1; return 0; }
static inline int F3(Cam* c, int b) { if ((u32)M2(c, b) == 1) { return 1; } return 0; }
int fn_8012FD80(int b) {
    Cam* c;
    if (M1(c, b) == 1) return 1; if (F3(c, b)) return 1; return 0;
}
}
