/* Map camera object (global at lbl_804CB81C), 8012F558..8012FF30. */
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

void fn_8012F558(Cam* c) {
    c->v20 = -1000.0f;
    c->v2C = -1000.0f;
    c->col.x = 0.0f;
    c->col.y = 0.0f;
    c->col.z = 0.0f;
    c->v68 = 1.0f;
}

void fn_8012F580(Cam* c, f32 v) {
    c->a.z = v;
    c->b.z = v;
}

void fn_8012F58C(Cam* c) {
    if (c->a.z < lbl_804CDD8C) {
        c->mode = 0;
    } else if (c->a.z > lbl_804CDD90) {
        c->mode = 2;
    } else {
        c->mode = 1;
    }
}

void fn_8012F610(Cam* c, Vec* v) {
    f32 z; f32 y; f32 x; x = v->x; y = v->y; z = v->z; c->col.x = x; c->col.y = y; c->col.z = z;
}

void fn_8012F62C(Cam* c) {
    f32 k = lbl_804CDD74;
    c->col.x = k;
    c->col.y = k;
    c->col.z = k;
}

u8 fn_8012FA3C(void) {
    return lbl_804CB820;
}

void fn_8012FC4C(void) {
    if ((lbl_804CB838 & 4) == 0) {
        lbl_804CB81C->v5();
        fn_8012F800(lbl_804CB81C);
    }
}

void fn_8012FC90(void) {
    lbl_804CA718 = lbl_804CB818;
}

void fn_8012FC9C(void) {
    lbl_804CB818 = lbl_804CA718;
    lbl_804CA718 = 0xff;
}

void fn_8012FCB0(void) {
    lbl_804CB818++;
}

void fn_8012FCC0(void) {
    lbl_804CB818--;
}

Cam* fn_8012FCD0(void) {
    return lbl_804CB81C;
}

static inline void CamSync(Cam* c) {
    if ((lbl_804CB838 & 8) == 0) {
        c->tgt.x = *(f32*)(lbl_803CAB38 + 0x93c);
        c->tgt.y = *(f32*)(lbl_803CAB38 + 0x940);
        c->tgt.z = *(f32*)(lbl_803CAB38 + 0x94c);
    }
}

BOOL fn_8012FCD8(int k) {
    Cam* c = lbl_804CB81C;
    f32 t;
    if (c == 0) {
        return 0;
    }
    if (lbl_804CB820 == 0) {
        CamSync(c);
    }
    c = lbl_804CB81C;
    t = lbl_804CDD88;
    if (k) {
        t = lbl_804CDDB8;
    }
    if ((f32)__fabs((f64)(c->tgt.x - c->cur.x)) > t) {
        return 1;
    }
    return (f32)__fabs((f64)(c->tgt.y - c->cur.y)) > t;
}

void fn_8012FED4(void) {
    Cam* c = lbl_804CB81C;
    if (c) {
        CamSync(c);
        c->cur.x = c->tgt.x;
        c->cur.y = c->tgt.y;
        c->cur.z = c->tgt.z;
        fn_8012F800(lbl_804CB81C);
    }
}

void fn_8012FF30(void) {
    Cam* c = lbl_804CB81C;
    if (c) {
        CamSync(c);
        c->cur.x = c->tgt.x;
        c->cur.y = c->tgt.y;
        c->cur.z = c->tgt.z;
        fn_8012F800(lbl_804CB81C);
    }
    c = lbl_804CB81C;
    if (c) {
        c->b.x = c->a.x;
        c->b.y = c->a.y;
        c->b.z = c->a.z;
        fn_8012F800(lbl_804CB81C);
    }
}

}
