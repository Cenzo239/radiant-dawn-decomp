#include "game/rG_800A3D88/types.h"

extern "C" {

extern u8 lbl_804CB834;
extern const f32 lbl_804CD330;
extern const f32 lbl_804CD348;
extern const f32 lbl_804CD350;
extern u8 lbl_803821F8[];
extern u8 lbl_803C8E80[];

void fn_80312344(void*, void*);
void fn_8001E6D0(void*, void*);
void fn_80312494(void*, void*);
void fn_8013AF10(void*);
void fn_801364AC(void*);
void fn_8013B8D0(void*);
int fn_8013B74C(void*, int);
void fn_8013B2B8(void*);
void fn_80146FBC(void*, f32);
void* fn_800A7948(int);
void fn_800AA444(void*);
void fn_80135554(void*);
void fn_8013B974();
void fn_80011CBC(void (*)(), void*);
void fn_800A66B0(void*);
void* fn_80081050(void*, void*);
void* fn_80083B84(void*);
void fn_80083B78(void*);
void fn_80006D00(void*, f32);

struct Vec {
    f32 x, y, z;
};

void fn_80312DB4(f32*, Vec*, Vec*);

struct Sub18 {
    u8 pad[0x30];
    u8 m30;
};

struct Mdl {
    u8 pad[0x18];
    Sub18* m18;
    u8 pad1c[0x78 - 0x1C];
    f32 m78;
    u8 pad7c[0xCC - 0x7C];
    u8 cc;
    u8 padcd[3];
    f32 d0;
    Vec d4;
    f32 e0;
    u8 e4[1];
};

struct Res54 {
    u8 pad[8];
    u8 m8;
    u8 pad9[3];
    u8 mc, md;
};

struct Ev {
    u8 pad[0x30];
    u8 m30, m31, m32, m33, m34;
    u8 pad35[3];
    Vec m38;
    f32 m44, m48;
    u8 m4c, m4d, m4e;
    u8 pad4f;
    Mdl* m50;
    Res54* m54;
    void* m58;
};

static inline void Ev_Sync(Ev* e) {
    if (e->m50 == NULL) {
        return;
    }
    if (e->m4c) {
        e->m50->cc = 1;
    } else {
        e->m50->cc = 0;
    }
    e->m50->e0 = e->m44;
    Vec t = e->m38;
    e->m50->d4 = t;
    e->m50->d0 = e->m48;
    fn_8013AF10(e->m50);
    fn_801364AC(e->m50);
}

struct Arg4 {
    u8 pad[0x44];
    Vec v;
};

void fn_800AA848(Ev* e, Arg4* a) {
    f32 m[12];
    if (e->m50 != NULL && a != NULL) {
        fn_80312344(e->m50->e4, m);
        fn_8001E6D0(m, m);
        fn_80312494(m, m);
        Vec v = a->v;
        fn_80312DB4(m, &v, &v);
        e->m38 = v;
        Ev_Sync(e);
    }
}

static inline void Ev_SyncF(Ev* e, u8 f) {
    if (e->m50 == NULL) {
        return;
    }
    if (f) {
        e->m50->cc = 1;
    } else {
        e->m50->cc = 0;
    }
    e->m50->e0 = e->m44;
    Vec t = e->m38;
    e->m50->d4 = t;
    e->m50->d0 = e->m48;
    fn_8013AF10(e->m50);
    fn_801364AC(e->m50);
}

void fn_800AA97C(Ev* e) {
    int f = !e->m4c;
    e->m4c = f;
    Ev_SyncF(e, f);
}

void fn_800AAA38(Ev* e) {
    e->m44 += lbl_804CD348;
    Ev_Sync(e);
}

f32 fn_800AAAF8(Ev* e) {
    if (e->m50 == NULL) {
        return lbl_804CD330;
    }
    return e->m50->m78;
}

void fn_800AAB14(Ev* e, u8 v) {
    e->m31 = v;
}

void fn_800AAB1C(Ev* e, u8 v) {
    if (e->m50 != NULL) {
        lbl_804CB834 = v;
        fn_8013B8D0(e->m50);
    }
}

void fn_800AAB38(Ev* e, int pct) {
    if (e->m50 != NULL && fn_8013B74C(e->m50, pct) != 0) {
        fn_8013B2B8(e->m50);
        fn_8013B8D0(e->m50);
    }
}

void fn_800AAB8C(Ev* e, u8 v) {
    e->m4e = v;
}

void fn_800AAB94(Ev* e, f32 v) {
    Mdl* m = e->m50;
    if (m != NULL) {
        Sub18* s = m->m18;
        if (s != NULL) {
            fn_80146FBC(s, v);
        }
    }
}

void* fn_800AABB4(Ev* e) {
    Res54* r = e->m54;
    if (r != NULL) {
        return fn_800A7948(r->mc);
    }
    return NULL;
}

u8 fn_800AABD0(Ev* e) {
    Res54* r = e->m54;
    if (r != NULL) {
        return r->md;
    }
    return 0;
}

void fn_800AABEC(Ev* e) {
    Mdl* m = e->m50;
    e->m30 = 1;
    if (m != NULL) {
        Sub18* s = m->m18;
        if (s != NULL) {
            s->m30 = 1;
        }
    }
}

void fn_800AAC14(Ev* e) {
    Mdl* m = e->m50;
    e->m30 = 0;
    if (m != NULL) {
        Sub18* s = m->m18;
        if (s != NULL) {
            s->m30 = 0;
        }
    }
}

BOOL fn_800AAC3C(Ev* e) {
    Res54* r = e->m54;
    if (r != NULL && (r->m8 & 4)) {
        return 1;
    }
    return 0;
}

void fn_800AAC64(Ev* e) {
    fn_800AA444(e);
}

void fn_800AAC68(Ev* e) {
    Mdl* m = e->m50;
    if (m != NULL && e->m54 != NULL && e->m30 != 0) {
        fn_80135554(m);
    }
}

void fn_800AAC98(Ev* e) {
    e->m30 = 0;
    if (e->m50 != NULL) {
        fn_80011CBC(fn_8013B974, NULL);
        e->m50 = NULL;
    }
    if (e->m54 != NULL) {
        if (e->m4d != 0) {
            fn_800A66B0(e->m54);
        }
        e->m54 = NULL;
    }
    e->m58 = NULL;
}

void* fn_800AAD1C(void* parent) {
    return fn_80081050(lbl_803821F8, parent);
}

void* fn_800AAD2C() {
    return fn_80083B84(lbl_803821F8);
}

struct FadeP {
    u8 pad[0x30];
    s32 i;
    s32 n;
    s32 wait;
    f32 step;
};

void fn_800AAD38(FadeP* p) {
    p->i = 0;
}

void fn_800AAD44(FadeP* p) {
    p->i = 0;
    fn_80006D00(p, lbl_804CD350);
}

void fn_800AAD54(FadeP* p) {
    if (p->wait > 0) {
        p->wait--;
    } else {
        fn_80006D00(p, p->step);
        p->i++;
        if (p->i >= p->n) {
            fn_80083B78(p);
        }
    }
}

} // extern "C"
