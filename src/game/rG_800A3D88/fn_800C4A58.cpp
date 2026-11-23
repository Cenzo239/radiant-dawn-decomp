#include "game/rG_800A3D88/types.h"

// Talk/portrait windows: lbl_803E50D0 holds up to 8 face objects.

#pragma auto_inline off

extern "C" {

extern char lbl_80365E0C[];
extern u8 lbl_80382898[];
extern void* lbl_803E50D0[8];
extern const f32 lbl_804CD564;
extern const f32 lbl_804CD588;

int fn_801D09F0();
void fn_800068EC(void*, const char*, int);
void fn_80006A2C(void*);
void fn_800C7B18(void*, int);
void fn_800C7B50(void*);
void* fn_800C79A0(void*, void*);
void fn_800C7A98(void*);
void fn_800C4EDC(void*, int, int, int, int, f32);
#if TARGET_PC
FE10_PROTO void* fn_800C5EA4(int, void*, ptr32<const void>, ptr32<const void>, ptr32<const void>, int, int);
#else
void* fn_800C5EA4(int, void*, void*, void*, void*, int, int);
#endif
void fn_800C6634(void*, int, int);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
u32 fn_80089ED0();
f32 fn_8017F68C(int, f32, f32, f32, f32);
void* fn_800811E4(void*, void*);
void fn_80081A90(void*);
void fn_80083E10(void*, void (*)(void*));

void fn_800C4A58(void* p) {
    int w = fn_801D09F0();
    const char* b = lbl_80365E0C;
    const char* s = b + 0x62;
    if (w != 0) {
        s = b + 0x4B;
    }
    fn_800068EC(p, s, 0x80);
}

void fn_800C4AA8(void* p) {
    fn_80006A2C(p);
}

struct FaceRes {
    void* m0;
    u8 pad4[0x25 - 4];
    u8 m25;
};

struct Face {
    u8 pad[0x30];
    void* m30;
    FaceRes* m34;
    f32 x;
    f32 y;
    u8 m40;
    u8 pad41;
    u8 m42;
    u8 m43;
    u8 pad44[4];
    u32 flags;
    struct FaceAnim* m4c;
    struct FaceAnim* m50;
    u8 pad54[0x60 - 0x54];
    int m60;
    u8 pad64[4];
    void* m68;
};

void fn_800C5D3C(Face* f) {
    fn_800C7B18(f->m34->m0, 0);
}

void fn_800C5D4C(Face* f) {
    fn_800C7B50(f->m34->m0);
}

void fn_800C5D58(Face* f) {
    f->m30 = fn_800C79A0(f->m34->m0, f->m34);
}

void fn_800C5D90(Face* f) {
    f32 s = f->m34->m25 / lbl_804CD588;
    u32 fl = f->flags;
    if (fl & 0x80) {
        s += f->m40;
    }
    if (fl & 0x20000) {
        s -= lbl_804CD564;
    }
    if (fl & 0x40000) {
        s += lbl_804CD564;
    }
    fn_800C4EDC(f, (int)f->x, (int)f->y, f->m42, 1, s);
}

void fn_800C5E44(Face* f) {
    void* r = f->m34->m0;
    if (f->m30 != NULL) {
        fn_800C7A98(r);
        f->m30 = NULL;
    }
    lbl_803E50D0[f->m40] = NULL;
}

struct FaceAnim {
    u8 pad[0x18];
    void* m18;
    u8 pad1c[0x30 - 0x1C];
    void* m30;
    s16 m34, m36;
    int m38;
    s16 m3c;
    u8 pad3e[2];
    s16 m40;
};

void fn_800C63F0(Face* f, u32 m) {
    FaceAnim* a = f->m4c;
    if (a != NULL) {
        f->flags &= ~0x38;
        if (a->m36 != -1) {
            a->m36 = 1;
        }
        f->flags |= m;
    }
}

void fn_800C642C(Face* f) {
    FaceAnim* a = f->m4c;
    if (a != NULL) {
        f->flags &= ~0x38;
        a->m36 = 1;
    }
}

void fn_800C6450(FaceAnim* a) {
    void* x = a->m18;
    a->m36 = 1;
    a->m30 = x;
    a->m34 = 1;
}

void fn_800C660C(Face* f, s16 x, s16 y) {
    FaceAnim* a = f->m50;
    if (a != NULL) {
        if (x > 0) {
            a->m34 = x;
        }
        if (y > 0) {
            a->m36 = y;
        }
    }
}

void fn_800C6ADC(FaceAnim* a) {
    fn_800C6634(a, 0, 0);
    fn_800C6634(a, 1, 0);
    if (a->m36 != 1) {
        fn_80083DC4(a, (u8)a->m36);
        return;
    }
    if (--a->m38 < 0) {
        int r = fn_80089ED0() >> 16;
        switch (a->m34) {
        case 3:
            r = (r >> 7) + 0x12C;
            break;
        case 1:
            r = (r >> 7) + 0x3C;
            break;
        case 2:
            r = (r >> 10) + 1;
            break;
        case 4:
            r = 1;
            break;
        case 5:
            r = 0x7FFFFFFF;
            break;
        default:
            r = 1;
            break;
        }
        a->m38 = r;
        a->m36 = 2;
        fn_80083DC4(a, 2);
    }
}

#define STEP_HEAD(a, m0, m1, want, onMismatch)  \
    fn_800C6634(a, 0, m0);                      \
    fn_800C6634(a, 1, m1);                      \
    if (a->m36 != want) {                       \
        fn_80083DC4(a, (u8)a->m36);             \
    }

void fn_800C6BD8(FaceAnim* a) {
    fn_800C6634(a, 0, 2);
    fn_800C6634(a, 1, 2);
    if (a->m36 != 2) {
        fn_80083DC4(a, (u8)a->m36);
    } else if (a->m3c == 2 && a->m40 == 2) {
        fn_80083B78(a);
    }
}

void fn_800C6C58(FaceAnim* a) {
    fn_800C6634(a, 0, 0);
    fn_800C6634(a, 1, 0);
    if (a->m36 != 2) {
        fn_80083DC4(a, (u8)a->m36);
    } else if (a->m3c == 0 && a->m40 == 0) {
        a->m36 = 1;
        fn_80083DC4(a, 1);
    }
}

void fn_800C6CE4(FaceAnim* a) {
    fn_800C6634(a, 0, 2);
    fn_800C6634(a, 1, 2);
    if (a->m36 != 3) {
        fn_80083DC4(a, (u8)a->m36);
    }
}

void fn_800C6D40(FaceAnim* a) {
    fn_800C6634(a, 0, 1);
    fn_800C6634(a, 1, 1);
    if (a->m36 != 4) {
        fn_80083DC4(a, (u8)a->m36);
    }
}

void fn_800C6D9C(FaceAnim* a) {
    fn_800C6634(a, 0, 0);
    fn_800C6634(a, 1, 0);
    if (a->m36 != 5) {
        fn_80083DC4(a, (u8)a->m36);
    }
}

void fn_800C6DF8(FaceAnim* a) {
    fn_800C6634(a, 0, 2);
    fn_800C6634(a, 1, 0);
    if (a->m36 != 6) {
        fn_80083DC4(a, (u8)a->m36);
    } else if (a->m3c == 2 && a->m40 == 0) {
        fn_80083B78(a);
    }
}

void fn_800C6E78(FaceAnim* a) {
    fn_800C6634(a, 0, 0);
    fn_800C6634(a, 1, 0);
    if (a->m36 != 6) {
        fn_80083DC4(a, (u8)a->m36);
    } else if (a->m3c == 0 && a->m40 == 0) {
        a->m36 = 1;
        fn_80083DC4(a, 1);
    }
}

void fn_800C6F04(FaceAnim* a) {
    fn_800C6634(a, 0, 0);
    fn_800C6634(a, 1, 2);
    if (a->m36 != 7) {
        fn_80083DC4(a, (u8)a->m36);
    } else if (a->m3c == 0 && a->m40 == 2) {
        fn_80083B78(a);
    }
}

void fn_800C6F84(FaceAnim* a) {
    fn_800C6634(a, 0, 0);
    fn_800C6634(a, 1, 0);
    if (a->m36 != 7) {
        fn_80083DC4(a, (u8)a->m36);
    } else if (a->m3c == 0 && a->m40 == 0) {
        a->m36 = 1;
        fn_80083DC4(a, 1);
    }
}

struct AlphaP {
    u8 pad[0x28];
    s16 m28;
    u8 pad2a[6];
    Face* face;
    int t, n, from, to;
};

void fn_800C7010(AlphaP* p) {
    Face* f;
    p->t = p->t + 1;
    int v = fn_8017F68C(0, p->from, p->to, p->t, p->n);
    f = p->face;
    f->m42 = v;
}

void fn_800C70BC(Face* f, void* parent) {
    AlphaP* p = (AlphaP*)fn_800811E4(lbl_80382898, parent);
    p->face = f;
    p->t = 0;
    p->n = 8;
    p->m28 = 8;
    p->from = 0;
    p->to = 0xFF;
}

void fn_800C7114(Face* f, void* parent) {
    AlphaP* p = (AlphaP*)fn_800811E4(lbl_80382898, parent);
    p->face = f;
    p->t = 0;
    p->n = 8;
    p->m28 = 8;
    p->from = f->m42;
    p->to = 0;
}

struct Holder30 {
    u8 pad[0x30];
    struct { u8 pad[0x40]; u8 id; }* s;
};

void fn_800C716C(Holder30* h) {
    if (h->s != NULL) {
        void** p = &lbl_803E50D0[h->s->id];
        if (*p != NULL) {
            fn_80081A90(*p);
        }
        *p = NULL;
    }
}

void fn_800C71CC(Face* f, void* parent) {
    AlphaP* p = (AlphaP*)fn_800811E4(lbl_80382898, parent);
    p->face = f;
    p->t = 0;
    p->n = 8;
    p->m28 = 8;
    p->from = f->m42;
    p->to = 0;
    fn_80083E10(p, (void (*)(void*))fn_800C716C);
}

void fn_800C7230(Face* f) {
    Face* o = (Face*)lbl_803E50D0[f->m60];
    if (o != NULL) {
        f->m68 = NULL;
        o->m42 = 0;
    }
}

} // extern "C"
