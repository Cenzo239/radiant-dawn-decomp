#include "game/rC2_8005259C/base.h"
class ME;
struct MO;
class Ops { public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2C();
    virtual int v30(MO*, ME*); virtual int v34(MO*, ME*); virtual int v38(MO*, ME*); virtual void v3C(); virtual int v40(MO*, ME*);
};
struct ME { u8 pad[0x34]; Ops* ops; };
struct Own { int a0; };
class OwnV { public:
    int a0;
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual int v20(MO*, ME*); virtual int v24(MO*, ME*);
};
struct Pr { u8 pad[0x50]; u8 b50; };
struct MO { u8 pad[0x18]; Pr* p18; u8 p1c[0x20]; OwnV* o3c; u8 at40[0x66]; s8 cur; };
class Pad { public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual u32 v48();
};
extern "C" {
extern u32 lbl_804CB700;
extern Pad* lbl_804CB5B8;
extern u8 lbl_8041EB20[];
extern u8 lbl_803CA870[];
ME* fn_80085EF8(u8);
int fn_801A2224(void*);
void fn_800453B4(void*, int);
}
static inline int inputBlocked(void) {
    u32 f1 = *(volatile u32*)&lbl_804CB700;
    u32 f2 = *(volatile u32*)&lbl_804CB700;
    int b = 0;
    if ((f1 & 0x10) && !(f2 & 0x20)) {
        b = 1;
    }
    return b;
}

extern "C" int fn_8005F7F4(void* a, MO* m) {
    ME* e = fn_80085EF8(m->at40[m->cur]);
    u32 k;
    if (inputBlocked()) {
        return e->ops->v40(m, e);
    }
    k = lbl_804CB5B8->v48();
    if ((k & 0x400) && !fn_801A2224(lbl_8041EB20)) {
        return e->ops->v30(m, e);
    }
    if (k & 0x800) {
        return m->o3c->v20(m, e);
    }
    if (k & 0x1000) {
        return e->ops->v34(m, e);
    }
    if (k & 0x2000) {
        return m->o3c->v24(m, e);
    }
    if (k & 0x10) {
        return e->ops->v38(m, e);
    }
    if ((k & 0x4000) && !fn_801A2224(lbl_8041EB20)) {
        m->p18->b50 = 1;
        fn_800453B4(lbl_803CA870, 0x9a);
        return 5;
    }
    return e->ops->v40(m, e);
}
