/* End a camera script and snap the main camera, 80130468. */
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
struct Evs {
    u8 pad[0x3c];
    u8 done;
    u8 pad3d[3];
    void* ev;
};
extern u8 lbl_804133B8[];
extern void fn_800620A8(void*, f32, f32);
extern void fn_80078E24(void*);
extern f32 lbl_804CDDBC;
static inline void Rst(Cam* c) {
    c->mn.x = -1000.0f;
    c->mx.x = -1000.0f;
    c->col.x = 0.0f;
    c->col.y = 0.0f;
    c->col.z = 0.0f;
    c->v68 = 1.0f;
}
static inline void Set0(Cam* k, Cam* o) {
    Vec t = o->cur;
    k->tgt = t;
    k->cur = t;
}
extern u32 lbl_804CB700;
extern u8 fn_800C7FF4(void);
#define k ((Cam*)lbl_804133B8)
void fn_80130468(Evs* s) {
    Cam* c = lbl_804CB81C;
    lbl_804CB820 = 0;
    lbl_804CB81C = k;
    Rst(k);
    {
    Vec v = c->cur;
    fn_800620A8(lbl_803CAB38, (f32)(int)v.x, (f32)(int)v.y);
    }
    {
    Vec v = c->cur;
    k->tgt = v;
    k->cur = v;
    }
    {
    f32 q;
    q = c->b.z; k->a.z = q; k->b.z = q;
    q = c->b.x; k->a.x = q; k->b.x = q;
    q = c->b.y; k->a.y = q; k->b.y = q;
    }
    Rst(c);
    if ((lbl_804CB700 & 0x8001) || fn_800C7FF4()) {
        if (!(lbl_804CB838 & 8)) {
            Cam* w = (Cam*)lbl_804133B8;
            Fl* f = (Fl*)lbl_803CAB38;
            f32 x, y, z;
            x = f->x; y = f->y; z = f->z;
            w->tgt.x = x;
            w->tgt.y = y;
            w->tgt.z = z;
        }
        {
        Cam* w = (Cam*)lbl_804133B8;
        w->cur = w->tgt;
        w->b = w->a;
        }
    } else {
        k->v68 = 3.0f;
    }
    s->done = 1;
    fn_80078E24(s->ev);
    s->ev = 0;
}
}
