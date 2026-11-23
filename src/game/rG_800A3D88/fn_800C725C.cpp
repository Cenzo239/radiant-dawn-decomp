#include "game/rG_800A3D88/types.h"

// Face fade processes and the shared face resource cache (lbl_803E7200).

#pragma auto_inline off

extern "C" {

extern u8 lbl_803828B0[];
extern u8 lbl_803828D0[];
extern u8 lbl_803828F8[];
extern u8 lbl_80382918[];
extern void* lbl_803E50D0[8];
extern u32 lbl_804CB700;
extern const f32 lbl_804CD560;
extern const f32 lbl_804CD588;

f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_80083B78(void*);
void* fn_80081050(void*, void*);
void* fn_80081194(void*, void*);
void fn_80081A90(void*);
void fn_800C3E70(void*, char*);
void fn_80006A2C(void*);
void* fn_800C3FD0(void*);
void fn_800068EC(void*, char*, int);
void fn_800C3EE0(void*, u16);
void fn_800C3F64(void*);

struct FaceX {
    u8 pad[0x40];
    u8 id;
    u8 m41;
    u8 m42;
};

struct FadeP {
    u8 pad[0x60];
    int idx;
    int n;
    int t;
    int from;
};

void fn_800C725C(FadeP* p) {
    FaceX* f = (FaceX*)lbl_803E50D0[p->idx];
    if (f != NULL) {
        f->m42 = fn_8017F68C(0, lbl_804CD560, lbl_804CD588, p->t, p->n);
        if (p->n == p->t) {
            fn_80083B78(p);
        } else {
            p->t = p->t + 1;
        }
    }
}

FadeP* fn_800C7324(int idx, int n, void* parent) {
    FaceX* f = (FaceX*)lbl_803E50D0[idx];
    if (f == NULL) {
        return NULL;
    }
    if (n == 0 || (lbl_804CB700 & 1)) {
        f->m42 = 0xFF;
        return NULL;
    }
    FadeP* p;
    if (parent != NULL) {
        p = (FadeP*)fn_80081050(lbl_803828B0, parent);
    } else {
        p = (FadeP*)fn_80081050(lbl_803828B0, (void*)3);
    }
    p->idx = idx;
    p->n = n;
    return p;
}

void fn_800C73D0(FadeP* p) {
    FaceX* f = (FaceX*)lbl_803E50D0[p->idx];
    if (f != NULL) {
        p->t = 0;
        p->from = f->m42;
    }
}

void fn_800C7400(FadeP* p) {
    FaceX* f = (FaceX*)lbl_803E50D0[p->idx];
    if (f != NULL) {
        if (lbl_804CB700 & 1) {
            p->t = p->n;
        }
        f->m42 = fn_8017F68C(0, p->from, lbl_804CD560, p->t, p->n);
        if (p->n == p->t) {
            fn_80083B78(p);
        } else {
            p->t = p->t + 1;
        }
    }
}

static inline void FaceFree(FaceX* f) {
    if (f != NULL) {
        void** s = &lbl_803E50D0[f->id];
        if (*s != NULL) {
            fn_80081A90(*s);
        }
        *s = NULL;
    }
}

void fn_800C74F0(FadeP* p) {
    FaceX* f = (FaceX*)lbl_803E50D0[p->idx];
    if (f != NULL) {
        FaceFree(f);
    }
}

FadeP* fn_800C755C(int idx, int n, void* parent) {
    FaceX* f = (FaceX*)lbl_803E50D0[idx];
    if (f == NULL) {
        return NULL;
    }
    if (lbl_804CB700 & 1) {
        n = 0;
    }
    if (n == 0) {
        f->m42 = 0;
        FaceFree(f);
        return NULL;
    }
    FadeP* p;
    if (parent != NULL) {
        p = (FadeP*)fn_80081194(lbl_803828D0, parent);
    } else {
        p = (FadeP*)fn_80081050(lbl_803828D0, (void*)3);
    }
    p->idx = idx;
    p->n = n;
    return p;
}

struct DimP {
    u8 pad[0x30];
    int idx;
    int t;
    int n;
    int from;
    int to;
    int mode;
};


void fn_800C7680(DimP* p) {
    FaceX* f = (FaceX*)lbl_803E50D0[p->idx];
    int v = (u8)(int)fn_8017F68C(p->mode, p->from, p->to, p->t, p->n);
    if (v > 0xFF) {
        v = 0xFF;
    }
    if (v < 0) {
        v = 0;
    }
    f->m41 = v;
    if (p->t == p->n) {
        fn_80083B78(p);
    } else {
        p->t = p->t + 1;
    }
}

DimP* fn_800C777C(int idx, int to, int n, void* parent) {
    FaceX* f = (FaceX*)lbl_803E50D0[idx];
    if (f == NULL) {
        return NULL;
    }
    if (lbl_804CB700 & 1) {
        n = 0;
    }
    if (n == 0) {
        if (to > 0xFF) {
            to = 0xFF;
        }
        if (to < 0) {
            to = 0;
        }
        f->m41 = to;
        return NULL;
    }
    DimP* p;
    if (parent != NULL) {
        p = (DimP*)fn_80081050(lbl_803828F8, parent);
    } else {
        p = (DimP*)fn_80081050(lbl_803828F8, (void*)3);
    }
    p->idx = idx;
    p->n = n;
    p->to = to;
    return p;
}

/* Face resource cache: up to 8 loaded faces */
struct FaceCache {
    void* res[8];
    void* key[8];
    s16 del[8];
    s16 ref[8];
};

extern FaceCache lbl_803E7200;


#pragma push
#pragma use_lmw_stmw on

#pragma pop


void fn_800C7B14() {
}

void fn_800C7B18(void* name, int f) {
    fn_800C3EE0(fn_800C3FD0(name), (u16)(f | 0x2000));
}

void fn_800C7B50(void* name) {
    fn_800C3F64(fn_800C3FD0(name));
}

/* lbl_804CB6D4: pad/input state object */
struct PadS {
    u8 pad[0x30];
    u8 m30;
    u8 pad31;
    u16 m32;
};

extern PadS* lbl_804CB6D4;

u32 fn_800C7F90() {
    return lbl_804CB6D4->m32 & 1;
}

BOOL fn_800C7FA0() {
    BOOL r = 0;
    u16 v = lbl_804CB6D4->m32;
    if ((v & 2) && (v & 4)) {
        r = 1;
    }
    return r;
}

BOOL fn_800C7FC4() {
    BOOL r = 0;
    u16 v = lbl_804CB6D4->m32;
    if ((v & 2) && (v & 8)) {
        r = 1;
    }
    return r;
}

u16 fn_800C7FE8() {
    return lbl_804CB6D4->m32;
}

u8 fn_800C7FF4() {
    return lbl_804CB6D4->m30;
}

} // extern "C"
