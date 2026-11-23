#include "game/rG_800A3D88/types.h"

extern "C" {

extern u8 lbl_80382188[];
extern char lbl_803653B8[];
extern const f32 lbl_804CD318;
extern const f32 lbl_804CD328;
extern const f32 lbl_804CD32C;
extern const f32 lbl_804CD330;
extern const f32 lbl_804CD334;

void fn_800A8CC0(void*);
void fn_80079474(void*);
void* fn_80081050(void*, void*);
int fn_800BD280(void*);
void fn_8013B270(void*);
void fn_8013B1F4(void*);
void fn_8013B21C(void*, void*);
void* fn_800B5784(void*, int);
f32 fn_800A84A4(const char*);
void fn_800A9E64(void*, int, int);
void fn_80250D64(int, f32, f32);
void fn_80020EEC();
void fn_80083F0C(int);
void fn_800E4548();
void fn_800A8B70();
void fn_80011CBC(void (*)(), void*);
#if TARGET_PC
FE10_PROTO void fn_8000FF74(p32arg);
FE10_PROTO void fn_800104DC(p32arg);
FE10_PROTO void fn_80020764(int, int, int, int, p32arg);
#else
void fn_8000FF74(int);
void fn_800104DC(int);
void fn_80020764(int, int, int, int, int);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_80020E74(void);
#else
int fn_80020E74();
#endif
#if TARGET_PC
FE10_PROTO void fn_801764F8(int, int, int, int, p32arg);
#else
void fn_801764F8(int, int, int, int, int);
#endif
void fn_8017659C(int, int, int, int, int, u8*, int, f32);
unsigned long long fn_8017DA30(int, int);
void* fn_800A7B38(const char*);
struct AnimRes { void* res; };
AnimRes* fn_800A66C4(void*, int);
#if TARGET_PC
FE10_PROTO int fn_80139964(void*, int, p32arg);
#else
int fn_80139964(void*, int, int);
#endif

struct IVec {
    u32 x, y, z;
};

struct FVec {
    f32 x, y, z;
};

struct BgmProc {
    u8 pad[0x30];
    u8 m30;
    u8 pad31[3];
    FVec m34;
    void* m40;
    void* m44;
    void* m48;
    u8 m4c;
};

void fn_800A9110(BgmProc* p) {
    FVec v;
    *(u32*)&v.x = 0;
    *(u32*)&v.y = 0;
    *(u32*)&v.z = 0;
    p->m44 = NULL;
    p->m30 = 1;
    p->m40 = NULL;
    p->m48 = NULL;
    p->m34 = v;
    p->m4c = 0;
}

void fn_800A915C(void* p) {
    fn_800A8CC0(p);
}

void fn_800A9160(BgmProc* p) {
    p->m30 = 0;
    if (p->m48 != NULL) {
        fn_80079474(p->m48);
        p->m48 = NULL;
    }
}

void* fn_800A91B0(void* parent) {
    return fn_80081050(lbl_80382188, parent);
}

void fn_800A91C0() {
}

struct Chan {
    u8 pad[0x30];
    void* m30;
    void* m34;
    u8 pad38[0x50 - 0x38];
    u32 flags;
    u8 m54;
    s8 m55;
};

struct Duo {
    u8 pad[0x30];
    Chan* a;
    Chan* b;
    u8 pad38[4];
    Chan* ch[2];
};

static inline Chan* DuoGet(Duo* d, int i) {
    if (i < 0) {
        return NULL;
    }
    return d->ch[i];
}

Chan* fn_800A93B8(Duo* d, int v) {
    for (int i = 0; i < 2; i++) {
        if (fn_800BD280(DuoGet(d, i)) != 0 && v == DuoGet(d, i)->m55) {
            return DuoGet(d, i);
        }
    }
    return NULL;
}

struct Owner50 {
    u8 pad[0x50];
    void* m50;
};

struct Duo2 {
    u8 pad[0x30];
    Owner50* o;
    Chan* c;
    u8 pad38[4];
    Chan* ch[2];
};

void fn_800A98C0(Duo2* d) {
    void* g = d->o->m50;
    if (g != NULL) {
        fn_8013B270(g);
        fn_8013B1F4(g);
        fn_8013B21C(g, *(void**)((u8*)d->c + 0x3C));
        for (int i = 0; i < 2; i++) {
            fn_8013B21C(g, DuoGet((Duo*)d, i)->m30);
            for (int j = 0; j < 2; j++) {
                if (fn_800B5784(DuoGet((Duo*)d, i), j) != NULL) {
                    fn_8013B21C(g, ((Chan*)fn_800B5784(DuoGet((Duo*)d, i), j))->m34);
                }
            }
        }
    }
}

static inline void SetFade(void* p, int a, int b) {
    if (a < 0) {
        a = fn_800A84A4(lbl_803653B8 + 0x6D);
    }
    if (b < 0) {
        b = fn_800A84A4(lbl_803653B8 + 0x1D);
        if (a != 100) {
            b *= 2;
        }
    }
    fn_80250D64(3, lbl_804CD328 * a, b * lbl_804CD32C);
}

void fn_800A99C4(void* p) {
    fn_800A9E64(p, 100, -1);
    SetFade(p, 100, -1);
    fn_80020EEC();
    fn_80083F0C(100);
    fn_800E4548();
    fn_80011CBC(fn_800A8B70, NULL);
}

void fn_800A9FC8(void* p, int a, int b) {
    if (a < 0) {
        a = fn_800A84A4(lbl_803653B8 + 0x6D);
    }
    if (b < 0) {
        b = fn_800A84A4(lbl_803653B8 + 0x1D);
        if (a != 100) {
            b *= 2;
        }
    }
    fn_80250D64(3, lbl_804CD328 * a, b * lbl_804CD32C);
}

void fn_800AA2BC(Duo* d, Chan* c) {
    for (int i = 0; i < 2; i++) {
        if (fn_800BD280(DuoGet(d, i)) != 0) {
            DuoGet(d, i)->flags &= ~0x800000;
        }
    }
    if (c != NULL) {
        c->flags |= 0x800000;
    }
}

void fn_800AA360(u8 a) {
    u8 col[4];
    if (fn_8017DA30(0, 0x80) == 0) {
        col[0] = a;
        col[1] = a;
        col[2] = a;
        col[3] = a;
        int t = fn_80020E74();
        fn_8000FF74(0);
        fn_801764F8(0, 0, 0x260, 0x1C0, t);
        fn_8017659C(0, 0, 0x260, 0x1C0, 1, col, t, lbl_804CD318);
        fn_800104DC(0);
    }
}

void fn_800AA400() {
    fn_8000FF74(0);
    fn_80020764(0, 0, 0x260, 0x1C0, 0);
    fn_800104DC(0);
}

struct Ev {
    u8 pad[0x30];
    u8 m30, m31, m32, m33, m34;
    u8 pad35[3];
    FVec m38;
    f32 m44, m48;
    u8 m4c, m4d, m4e;
    u8 pad4f;
    void* m50;
    void* m54;
    void* m58;
};

void fn_800AA444(Ev* e) {
    e->m30 = 1;
    FVec v;
    *(u32*)&v.x = 0;
    *(u32*)&v.y = 0;
    *(u32*)&v.z = 0;
    e->m50 = NULL;
    e->m58 = NULL;
    e->m54 = NULL;
    e->m33 = 0x32;
    e->m34 = 0x32;
    e->m32 = 0;
    e->m38 = v;
    e->m4d = 0;
    e->m4e = 0;
    e->m4c = 0;
    e->m44 = lbl_804CD330;
    e->m48 = lbl_804CD334;
    e->m31 = 1;
    e->m50 = NULL;
}


BOOL fn_800AA4C0(Ev* e, const char* name, int i) {
    void* a = fn_800A7B38(name);
    if (a == NULL) {
        return 0;
    }
    AnimRes* r = fn_800A66C4(a, i);
    if (fn_80139964(r->res, e->m31, e->m4e != 0 ? 0x20 : 0x2240) == 0) {
        return 0;
    }
    return 1;
}

} // extern "C"
