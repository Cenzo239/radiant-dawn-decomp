/* Map camera smoothing toward its target, 8012F640. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off

extern "C" {

extern f32 lbl_804CDD74;
extern f32 lbl_804CDD64;
extern f32 lbl_804CDD88;
extern f32 lbl_804CDD8C;
extern f32 lbl_804CDD90;
extern f32 lbl_804CDDB8;
extern u8 lbl_804CB820;
extern u8 lbl_804CB838;
extern u8 lbl_804CB818;
extern u8 lbl_804CA718;
extern u8 lbl_803CAB38[];

struct CamBase {
    u8 pad0[4];
    Vec a;       /* 0x04 */
    Vec b;       /* 0x10 */
    int mode;    /* 0x1C */
    f32 v20;     /* 0x20 */
    u8 pad24[8];
    f32 v2C;     /* 0x2C */
    u8 pad30[8];
    Vec cur;     /* 0x38 */
    Vec tgt;     /* 0x44 */
    u8 pad50[0xC];
    Vec col;     /* 0x5C */
    f32 v68;     /* 0x68 */
};

class Cam : public CamBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual f32 v4();
    virtual void v5();
};

extern Cam* lbl_804CB81C;
extern void fn_8012F800(Cam*);

extern u8 lbl_804CB819;
struct Fl { u8 pad[0x93c]; f32 x; f32 y; u8 pad2[8]; f32 z; };
void fn_8012F640(Cam* c) {
    f32 kxy, kz;
    c->v68 = (7.0f * c->v68 + 1.0f) / 8.0f;
    if ((lbl_804CB838 & 8) == 0) {
        Fl* f = (Fl*)lbl_803CAB38;
        c->tgt.x = f->x;
        c->tgt.y = f->y;
        c->tgt.z = f->z;
    }
    kxy = c->v68;
    kz = kxy;
    {
    Vec t = c->tgt;
    Vec p = c->cur;
    switch (lbl_804CB819) {
    case 0:
        kxy *= 13.0f;
        kz *= 23.0f;
        break;
    case 1:
        kxy *= 9.0f;
        kz *= 17.0f;
        break;
    case 2:
        kxy *= 6.0f;
        kz *= 11.0f;
        break;
    }
    c->cur.x = (p.x * kxy + t.x) / (1.0f + kxy);
    c->cur.y = (p.y * kxy + t.y) / (1.0f + kxy);
    c->cur.z = (p.z * kz + t.z) / (1.0f + kz);
    }
    if (lbl_804CB818 == 0) {
        c->v3();
    }
    {
    f32 q = 7.0f * c->v68;
    c->b.z = (c->b.z * q + c->a.z) / (1.0f + q);
    c->b.x = (c->b.x * q + c->a.x) / (1.0f + q);
    c->b.y = (c->b.y * q + c->a.y) / (1.0f + q);
    }
}
}
