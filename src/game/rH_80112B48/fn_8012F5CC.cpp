/* Set the camera zoom mode, 8012F5CC. */
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
void fn_8012F5CC(Cam* c, int m) {
    c->mode = m = m & 3;
    c->a.z = c->v4(c->mode);
}
}
