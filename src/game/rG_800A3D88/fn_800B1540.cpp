#include "game/rG_800A3D88/chr.h"

#pragma auto_inline off

extern "C" {

extern char lbl_803657E8[];
extern u8 lbl_80382550[];
extern const f32 lbl_804CD3B8;
extern const f32 lbl_804CD400;

void fn_80290DDC(char*, const char*, ...);
int fn_8023F9F4(char*);
void fn_800092D4(Mdl*, char*, int);
#if TARGET_PC
FE10_PROTO int fn_800A6F98(ChrData*, p32arg);
#else
int fn_800A6F98(ChrData*, int);
#endif
void* fn_800A6F34(ChrData*, int);
int fn_800A8208(const char*);
int fn_800B1B48(Chr*, int, int, int, int);
void fn_80006EE0(void*);
#if TARGET_PC
FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
void fn_8023F1A8(void*);
#endif
void fn_80011CBC(void (*)(void*), void*);
void fn_80081A90(void*);
void fn_800829CC(Chr*, void*);
void fn_800B33F4(Chr*, int);
s16 fn_8001E094(f32);
f32 fn_8001E064(s16);
int fn_80007630(Mdl*, const char*);
int fn_800B4000(Chr*, int, Vec*, int, int);
f32 fn_800A7370(ChrData*, const char*);
void fn_80312654(void*, int, f32);
void fn_80312DB4(void*, Vec*, Vec*);
void fn_80313460(Vec*, Vec*, Vec*);
f32 fn_800A84A4(const char*);
int fn_80008C98(Mdl*, int);
u16 fn_80008CF0(Mdl*, int);
void fn_800E48C8(void*, Vec*);
#if TARGET_PC
FE10_PROTO p32ret fn_800E45B0(int);
#else
int fn_800E45B0(int);
#endif
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A7460(ChrData*, const char*);
#else
void* fn_800A7460(ChrData*, const char*);
#endif

static inline int HasAnimFile(ChrData* d, int i, char* buf) {
    if (d == NULL) {
        return 0;
    }
    fn_80290DDC(buf, lbl_803657E8 + 0x62, d->name, d->anims[i].name);
    return fn_8023F9F4(buf) != 0x40000;
}

static inline int LoadAnim(Chr* c, int i) {
    char buf[0x40];
    if (c->mdl == NULL) {
        return 0;
    }
    if (c->data == NULL) {
        return 0;
    }
    if (!HasAnimFile(c->data, i, buf)) {
        return 0;
    }
    fn_800092D4(c->mdl, buf, (c->flags & 0x04000000) ? 0x20 : 0x40);
    c->mdl->flags &= ~0x800;
    return 1;
}

int fn_800B1540(Chr* c, int i) {
    return LoadAnim(c, i);
}

int fn_800B1628(
#if TARGET_PC
Chr* c, void* k
#else
Chr* c, int k
#endif
) {
    int i = 0;
    if (k != 0) {
        i = fn_800A6F98(c->data, k);
    }
    return LoadAnim(c, i);
}

void* fn_800B1728(Chr* c) {
    ChrData* d = c->data;
    if (d == NULL) {
        return NULL;
    }
    int i = (s8)c->m57;
    if (i < 0) {
        return NULL;
    }
    return fn_800A6F34(d, i);
}

int fn_800B26B0(Chr* c, const char* name, int a, u16 b) {
    return fn_800B1B48(c, fn_800A8208(name), a, b, -1);
}


void fn_800B2944(Chr* c, f32 x, f32 y, f32 z) {
    c->m44.x = x;
    c->m44.y = y;
    c->m44.z = z;
    fn_800B33F4(c, 1);
}

void fn_800B2958(Chr* c, f32 a) {
    c->m58 = fn_8001E094(a);
    fn_800B33F4(c, 1);
}

void fn_800B2994(Chr* c, f32 a) {
    c->m5a = fn_8001E094(a);
    fn_800B33F4(c, 1);
}

#define ZERO_VEC(v) (*(u32*)&(v).x = 0, *(u32*)&(v).y = 0, *(u32*)&(v).z = 0)

Vec fn_800B5C3C(Chr* c) {
    f32 m[12];
    Vec d;
    f32 z = fn_800A84A4(lbl_803657E8 + 0x1D7);
    ZERO_VEC(d);
    d.z = -z;
    fn_80312654(m, 'y', lbl_804CD400 * fn_8001E064(c->m58));
    fn_80312DB4(m, &d, &d);
    return d;
}

BOOL fn_800B5CDC(Chr* c) {
    Vec v = c->m44;
    return v.y > lbl_804CD3B8;
}

static inline int HasTag(Chr* c, int t) {
    if (c->mdl == NULL) {
        return 0;
    }
    return fn_80008C98(c->mdl, t);
}

BOOL fn_800B6570(Chr* c, u16* out) {
    *out = 0;
    if (c->mdl == NULL) {
        return 0;
    }
    if (HasTag(c, 2)) {
        *out = fn_80008CF0(c->mdl, 2);
        return 1;
    }
    return 0;
}


int fn_800B7260(Chr* c, int t) {
    if (c->mdl == NULL) {
        return 0;
    }
    return fn_80008C98(c->mdl, t);
}

struct View {
    u8 pad[0x30];
    struct Ctx* ctx;
};

struct Ctx {
    u8 pad[4];
    u16 m4;
    u8 pad6[0xA4 - 6];
    Chr* a;
    int b;
};

void fn_800B9CA8(View* w) {
    Vec v;
    if (fn_800B4000(w->ctx->a, w->ctx->b, &v, -1, 0) != 0) {
        Vec t = v;
        fn_800E48C8(w, &t);
    }
}

void fn_800BBAE0(View* w) {
    Ctx* x = w->ctx;
    Chr* c = x->a;
    if (c->data != NULL && x->m4 != 2) {
        Mdl* m = c->mdl;
        if (m != NULL) {
            m->flags &= ~8;
        }
    }
}

int fn_800BCC54() {
    return fn_800E45B0(1);
}

BOOL fn_800BD218(Chr* c) {
    return c->m5e >= 0;
}

BOOL fn_800BD22C(Chr* c) {
    if ((c->m7c->flags & 0x40) && fn_800A7460(c->data, lbl_803657E8 + 0x325) != NULL) {
        return 1;
    }
    return 0;
}

BOOL fn_800BD280(Chr* c) {
    return c->data != NULL;
}

} // extern "C"
