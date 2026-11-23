/* Map camera view bounds from the four screen corners, 8012F070. */
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
#if TARGET_PC
extern FE10_PROTO void fn_80011C60(p32arg, void*, Vec*);
#else
extern void fn_80011C60(int, void*, Vec*);
#endif
extern const f32 lbl_80369260[12];
struct V2 { f32 x,y,z; };
void fn_8012F070(Cam* c) {
    f32* q;
    int i;
    f32 t[12] = {-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f};
    Vec o;
    Vec a;
    Vec b;
    a.x = 1000.0f;
    a.y = 1000.0f;
    b.x = -1000.0f;
    b.y = -1000.0f;
    q = t;
    for (i = 0; i < 4; i++) {
        fn_80011C60(0, q, &o);
        if (a.x > o.x) a.x = o.x;
        if (a.y > o.y) a.y = o.y;
        if (b.x < o.x) b.x = o.x;
        if (b.y < o.y) b.y = o.y;
        q += 3;
    }
    {
    Vec p = a;
    Vec r = b;
    c->mn = p;
    c->mx = r;
    }
}
}
