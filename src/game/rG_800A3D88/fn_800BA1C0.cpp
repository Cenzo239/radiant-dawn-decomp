#include "game/rG_800A3D88/chr.h"

#pragma auto_inline off

extern "C" {

extern char lbl_803657E8[];
extern char lbl_80365B64[];
extern u8 lbl_80382508[];
extern u8 lbl_80382580[];
extern u8 lbl_803825A8[];
extern void* lbl_80382650[];
extern u8 lbl_80382778[];
extern u8 lbl_80382790[];
extern u8 lbl_804CD45C[4];
extern const f32 lbl_804CD3B8;
extern const f32 lbl_804CD460;
extern const f32 lbl_804CD470;
extern const f32 lbl_804CD4B0;
extern const f32 lbl_804CD4B8;

void fn_800E4904(void*, int, void*);
int fn_80007630(void*, const char*);
int fn_800B4000(Chr*, int, Vec*, int, int);
void fn_800E48AC(void*, f32, f32, f32);
f32 fn_800A84A4(const char*);
void* fn_80081050(void*, void*);
void* fn_80081194(void*, void*);
void fn_8001A954(void*);
void fn_8001AA84(void*);
void fn_800829CC(void*, void*);
void fn_80006EE0(void*);
void fn_8023F1A8(void*);
void fn_80011CBC(void (*)(void*), void*);
int fn_800A6844(void*, int);
void fn_80008F20(void*, u8);
void fn_80008F10(void*, u8, u8, u8);
void* fn_800A7FAC(int);
void fn_80108618(void*, void*);
void fn_801780B0(void*);

/* Effect attached to a battle character */
struct EffData {
    u8 pad[0xC];
    void* mc;
    void* m10;
    void* m14;
    void* m18;
    u8 pad1c[0x21 - 0x1C];
    u8 m21;
};

struct EffMdl {
    u8 pad[0xB];
    u8 mb;
};

struct Eff {
    void* pad0[0x30 / 4];
    void* m30;
    EffMdl* m34;
    EffData* m38;
    Chr* m3c;
    void* m40;
    s16 m44;
    u16 m46;
    Vec m48;
    f32 m54;
    u8 pad58[0x5C - 0x58];
    s16 m5c;
    u8 pad5e[0x6C - 0x5E];
    f32 m6c;
    u8 pad70[0x9C - 0x70];
    f32 m9c;
    f32 ma0;
    u16 ma4;
    s16 ma6;
};


struct Ctx {
    u8 pad[0x18];
    u32 m18;
    Vec m1c;
    u8 pad28[0x9C - 0x28];
    int m9c;
    Chr* a4;
    u8 pada8[0xB0 - 0xA8];
    AnimState* b0;
};

struct View {
    u8 pad[0x30];
    Ctx* ctx;
};



struct ChrE {
    u8 pad[0x30];
    void* mdl;
    u8 pad34[0x3C - 0x34];
    Eff* e[2];
    u8 pad44[0x50 - 0x44];
    u32 flags;
};

void fn_800C0EFC(Eff*);
void fn_800C0F20(Eff*);

void fn_800BE340(ChrE* c) {
    if (c->mdl != NULL && !(c->flags & 1)) {
        fn_8001AA84(c->mdl);
        for (int i = 0; i < 2; i++) {
            if (c->e[i] != NULL) {
                fn_800C0F20(c->e[i]);
            }
        }
    }
}

void* fn_800BEEA0(void* parent) {
    return fn_80081050(lbl_80382580, parent);
}

u32 fn_800BEEB0(Chr* c, u32 m) {
    return c->flags & m;
}

struct S56 {
    u8 pad[0x56];
    u8 m56;
};

void fn_800BEEBC(S56* s) {
    s->m56 = 0;
}

struct Small {
    u8 pad[2];
    s16 m2;
    u8 pad4[4];
    u8 m8;
    u8 pad9[0x14 - 9];
    u32 m14;
};

s16 fn_800BEEC8(Small* s) {
    return s->m2;
}

u8 fn_800BEED0(Small* s) {
    return s->m8;
}

u32 fn_800BEED8(Small* s, int b) {
    return s->m14 & (1 << b);
}

struct S48 {
    u8 pad[0x48];
    u8 m48;
};

void fn_800BEEEC(S48* s, u8 v) {
    s->m48 = v;
}

void fn_800BF0B4(Eff* e) {
    e->m46 |= 1;
    if (e->m34 != NULL) {
        fn_800829CC(e, lbl_803825A8);
        fn_80011CBC(fn_80006EE0, e->m34);
        if (e->m30 != NULL) {
            fn_80011CBC(fn_8023F1A8, e->m30);
        }
        e->m34 = NULL;
        e->m30 = NULL;
        e->m46 = 0;
    }
}

void* fn_800BF138(void* parent) {
    return fn_80081050(lbl_803825A8, parent);
}

void fn_800C1064(Eff*, int);
void fn_800C0F44(Eff*, int);
void fn_800BF444(Eff*, int, int);

void fn_800BF568(Eff* e, int n) {
    if (e->m38 != NULL) {
        if (e->m38->m21 & 2) {
            e->m46 &= ~0x10;
            fn_800C1064(e, 0);
            fn_800829CC(e, lbl_803825A8);
        } else {
            e->m46 |= 0x10;
            fn_800C0F44(e, -1);
            if (n > 1) {
                fn_800BF444(e, n - 1, -1);
            }
        }
    }
}

void fn_800BF750(Eff* e, Chr* c, const char* name) {
    int i = fn_80007630(c->mdl, name);
    e->m3c = c;
    e->m44 = i;
}

void fn_800C0988(Eff* e) {
    e->m6c = lbl_804CD470;
    e->m46 |= 0x40;
    if (e->m40 != NULL) {
        fn_801780B0(e->m40);
        e->m40 = NULL;
    }
}

u8 fn_800C09E0(Eff* e, int i) {
    if (e->m38 == NULL) {
        return 0;
    }
    return fn_800A6844(e->m38, i);
}

void* fn_800C0A18(Eff* e) {
    EffData* d = e->m38;
    if (d == NULL) {
        return NULL;
    }
    return d->mc;
}

void* fn_800C0A34(Eff* e) {
    EffData* d = e->m38;
    if (d == NULL) {
        return NULL;
    }
    return d->m10;
}

void* fn_800C0A50(Eff* e) {
    EffData* d = e->m38;
    if (d == NULL) {
        return NULL;
    }
    return d->m14;
}

void* fn_800C0A6C(Eff* e) {
    EffData* d = e->m38;
    if (d == NULL) {
        return NULL;
    }
    return d->m18;
}

static inline u16 EffFlag(Eff* e, u16 m) {
    return e->m46 & m;
}

BOOL fn_800C0EE4(Eff* e) {
    return EffFlag(e, 2) != 0;
}

void fn_800C0EFC(Eff* e) {
    if (e->m34 != NULL && (e->m46 & 0x10)) {
        fn_8001A954(e->m34);
    }
}

void fn_800C0F20(Eff* e) {
    if (e->m34 != NULL && (e->m46 & 0x10)) {
        fn_8001AA84(e->m34);
    }
}

void fn_800C0F44(Eff* e, int t) {
    if (e->m34 != NULL) {
        if (t < 0) {
            t = fn_800A84A4(lbl_80365B64 + 0xC7);
        }
        if (e->m38->m21 & 8) {
            if (e->ma4 != 0 && lbl_804CD4B0 == e->ma0) {
                return;
            }
            e->m9c = e->m34->mb;
            e->ma0 = lbl_804CD4B0;
            if (t == 0) {
                fn_80008F20(e->m34, lbl_804CD4B0);
            }
        } else {
            if (e->ma4 != 0 && lbl_804CD460 == e->ma0) {
                return;
            }
            e->m9c = e->m54;
            e->ma0 = lbl_804CD460;
            if (t == 0) {
                e->m54 = lbl_804CD460;
            }
        }
        e->ma4 = t;
        e->ma6 = 0;
    }
}

void fn_800C1064(Eff* e, int t) {
    if (e->m34 != NULL) {
        if (t < 0) {
            t = fn_800A84A4(lbl_80365B64 + 0xC7);
        }
        if (e->m38->m21 & 8) {
            if (e->ma4 != 0 && lbl_804CD470 == e->ma0) {
                return;
            }
            e->m9c = e->m34->mb;
            e->ma0 = lbl_804CD470;
            if (t == 0) {
                fn_80008F20(e->m34, lbl_804CD470);
            }
        } else {
            if (e->ma4 != 0 && lbl_804CD470 == e->ma0) {
                return;
            }
            e->m9c = e->m54;
            e->ma0 = lbl_804CD470;
            if (t == 0) {
                e->m54 = lbl_804CD470;
            }
        }
        e->ma4 = t;
        e->ma6 = 0;
    }
}

void fn_800C1184(Eff* e, int i) {
    e->m38 = (EffData*)fn_800A7FAC(i);
}

void fn_800C11B8(Eff* e, u8* c) {
    if (e->m34 != NULL) {
        fn_80008F10(e->m34, c[0], c[1], c[2]);
        fn_80008F20(e->m34, c[3]);
    }
}

void fn_800C1218(Eff* e, void* p) {
    fn_80108618(e->m34, p);
}

void fn_80079210(void*);
void* fn_80079150(u32);
void fn_800B2710(Chr*);
void fn_800B29D0(Chr*);

struct Blend {
    u32 mode;
    f32 a, b, c, d, e;
};

struct ChrB {
    u8 pad[0x30];
    void* m30;
    void* m34;
    void* m38;
    void* m3c;
    void* m40;
    u8 pad44[0x50 - 0x44];
    u32 flags;
    s8 m54, m55;
    u8 pad56;
    s8 m57;
    u8 pad58[0x78 - 0x58];
    void* m78;
    void* m7c;
    void* m80;
    u8 pad84[0x8C - 0x84];
    Blend* m8c;
    Blend* m90;
    Blend* m94;
    void* m98;
};

static inline Blend* NewBlend(u32 mode) {
    Blend* b = (Blend*)fn_80079150(0x18);
    if (b != NULL) {
        b->a = lbl_804CD3B8;
        b->b = lbl_804CD3B8;
        b->c = lbl_804CD3B8;
        b->d = lbl_804CD3B8;
        b->e = lbl_804CD3B8;
        b->mode = mode;
    }
    return b;
}

void fn_800BED98(ChrB* c) {
    c->flags |= 1;
    fn_800B2710((Chr*)c);
    if (c->m8c != NULL) {
        fn_80079210(c->m8c);
        c->m8c = NULL;
    }
    if (c->m90 != NULL) {
        fn_80079210(c->m90);
        c->m90 = NULL;
    }
    if (c->m94 != NULL) {
        fn_80079210(c->m94);
        c->m94 = NULL;
    }
}

void fn_800BEC84(ChrB* c);

void fn_800BEE18(ChrB* c) {
    fn_800BEC84(c);
}

void fn_800BEE1C() {
}

void fn_800BEE20(ChrB* c) {
    c->flags |= 1;
    fn_800B2710((Chr*)c);
    if (c->m8c != NULL) {
        fn_80079210(c->m8c);
        c->m8c = NULL;
    }
    if (c->m90 != NULL) {
        fn_80079210(c->m90);
        c->m90 = NULL;
    }
    if (c->m94 != NULL) {
        fn_80079210(c->m94);
        c->m94 = NULL;
    }
}

void* fn_800E4060(void*, void*);
void fn_800BEA14(void*);

struct Spawned {
    u8 pad[0x30];
    struct SpawnedSub* s;
};

struct SpawnedSub {
    u8 pad[0x18];
    u32 flags;
    u8 pad1c[0x9C - 0x1C];
    void (*cb)(void*);
};

struct ChrSpawn {
    u8 pad[0x78];
    struct { u8 pad[0xC]; void* mc; }* m78;
    u8 pad7c[0x98 - 0x7C];
    Spawned* m98;
};

void fn_80081A90(void*);

void fn_800BEBD4(ChrSpawn* c) {
    if (c->m78 != NULL) {
        if (c->m98 != NULL) {
            fn_80081A90(c->m98);
            c->m98 = NULL;
        }
        if (c->m78->mc != NULL) {
            Spawned* s = (Spawned*)fn_800E4060(c->m78->mc, c);
            c->m98 = s;
            s->s->cb = fn_800BEA14;
            fn_800E4904(c->m98, 0, c);
            c->m98->s->flags |= 0x2004;
            c->m98->s->flags &= ~0x8000;
        }
    }
}

void fn_800BEEF4(Eff* e) {
    Vec v;
    *(u32*)&v.x = 0;
    *(u32*)&v.y = 0;
    *(u32*)&v.z = 0;
    e->m34 = NULL;
    e->m30 = NULL;
    e->m3c = NULL;
    e->m38 = NULL;
    e->m40 = NULL;
    e->m44 = -1;
    e->m46 = 0;
    e->m5c = 0;
    e->ma4 = 0;
    e->m54 = lbl_804CD460;
    e->m48 = v;
}

struct EffD2 {
    u8 pad[0x21];
    u8 m21;
};

} // extern "C"
