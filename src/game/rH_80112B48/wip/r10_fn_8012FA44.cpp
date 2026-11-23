/* NOT MATCHING, not compiled. fn_8012FA44: 39 words: zero constant and first camera swapped (r28/r29). Needs file statics at lbl_804133B8. */
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
extern View* fn_8000F470(void);
struct C1 { u8 b[0x70]; };
struct C2 { u8 b[0x74]; };
static C1 s0;
static C2 s1;
static C2 s2;
static inline void CamI(Cam* c) {
    c->mode = 0;
    c->view = fn_8000F470();
    c->b.x = 0.0f; c->a.x = 0.0f;
    c->b.y = 40.0f; c->a.y = 40.0f;
    {
    f32 z = c->v4(c->mode);
    c->b.z = z; c->a.z = z;
    }
    lbl_804CB818 = 0;
    lbl_804CB819 = 0;
    {
    f32 k = 0.0f;
    c->v50.x = k; c->cur.x = k; c->tgt.x = k;
    c->v50.y = k; c->cur.y = k; c->tgt.y = k;
    c->v50.z = k; c->cur.z = k; c->tgt.z = k;
    c->mn.x = -1000.0f;
    c->mx.x = -1000.0f;
    c->col.x = k; c->col.y = k; c->col.z = k;
    c->v68 = 1.0f;
    }
}
static inline void CamJ(Cam* c, int z) {
    c->mode = z;
    c->view = fn_8000F470();
    c->b.x = 0.0f; c->a.x = 0.0f;
    c->b.y = 40.0f; c->a.y = 40.0f;
    {
    f32 z = c->v4(c->mode);
    c->b.z = z; c->a.z = z;
    }
    lbl_804CB818 = z;
    lbl_804CB819 = z;
    {
    f32 k = 0.0f;
    c->v50.x = k; c->cur.x = k; c->tgt.x = k;
    c->v50.y = k; c->cur.y = k; c->tgt.y = k;
    c->v50.z = k; c->cur.z = k; c->tgt.z = k;
    c->mn.x = -1000.0f;
    c->mx.x = -1000.0f;
    c->col.x = k; c->col.y = k; c->col.z = k;
    c->v68 = 1.0f;
    }
}
void fn_8012FA44(void) {
    CamI((Cam*)&s0);
    CamI((Cam*)&s1);
    CamI((Cam*)&s2);
    lbl_804CB820 = 0;
    lbl_804CB81C = (Cam*)&s0;
}
}
