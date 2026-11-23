/* Map camera view update, 8012F800. */
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
extern void fn_8012F1F4(Vec*, const Vec*, f32);
struct W3 { u32 a, b, c; };
#define WC(d,s) *(W3*)&(d) = *(W3*)&(s)
extern void fn_80312654(void*, int, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_80312DB4(void*, void*, void*);
extern void fn_80313460(void*, void*, void*);
extern void fn_8000FA98(View*);
extern void fn_800106AC(int, void*, void*);
extern int fn_801D09F0(void);
extern void fn_8012F070(Cam*);
static inline void Rot(Cam* c, Vec* o) { Vec in = c->cur; fn_8012F1F4(o, &in, c->b.z); }
static inline void Tail(Cam* c) { Vec t = c->view->d4; c->v50 = t; }
void fn_8012F800(Cam* c) {
    u8 m1[0x30];
    u8 m2[0x30];
    u8 m3[0x30];
    Vec r;
    Vec o;
    {
    Rot(c, &o);
    {
    WC(r, o);
    c->view->e0.x = c->cur.x + r.x;
    c->view->e0.y = c->cur.y + r.y;
    c->view->e0.z = c->cur.z + r.z;
    }
    }
    c->view->v104 = c->b.z;
    c->view->v108 = c->b.x;
    c->view->v10c = c->b.y;
    c->view->ec.x = 0.0f;
    c->view->ec.y = -1.0f;
    c->view->ec.z = 0.0f;
    c->view->d4.x = 0.0f;
    c->view->d4.y = 0.0f;
    c->view->d4.z = -c->view->v104;
    c->view->f8 = c->col;
    fn_80312654(m1, 0x58, 0.017453292f * c->view->v10c);
    fn_80312654(m2, 0x5a, 0.017453292f * c->view->v108);
    fn_80312378(m2, m1, m3);
    fn_80312DB4(m3, &c->view->d4, &c->view->d4);
    fn_80312DB4(m3, &c->view->ec, &c->view->ec);
    fn_80313460(&c->view->d4, &c->view->e0, &c->view->d4);
    fn_8000FA98(c->view);
    fn_800106AC(1, (void*)fn_8012F070, c);
    c->v1();
    if (fn_801D09F0()) {
        c->view->flags |= 4;
    } else {
        c->view->flags &= ~4;
    }
    {
    Tail(c);
    }
}
}
