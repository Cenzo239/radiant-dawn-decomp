#include "game/rG_800A3D88/types.h"

extern "C" {

extern const f32 lbl_804CD298;
extern u8 lbl_80382138[];

void* fn_80081050(void*, void*);
void* fn_80083B84(void*);
void fn_80081A90(void*);
void fn_80006EE0(void*);
u32 fn_80089ED0();
void fn_8027E4B8(void*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A8208(void*);
#else
void* fn_800A8208(void*);
#endif
#if TARGET_PC
FE10_PROTO void fn_800A5F08(void*, void*, i32arg);
#else
void fn_800A5F08(void*, void*, void*);
#endif
void fn_800A5B84(void*, void*, void*);
void fn_802573EC(void*);

struct Vec3 {
    f32 x, y, z;
};

struct Sub44 {
    u8 pad[0x18];
    s32 v18;
};

struct Sub78 {
    u32 flags;
    u8 pad4[0x44 - 4];
    Sub44* m44;
    u8 pad48[0x58 - 0x48];
    f32 m58;
};

struct Sub80 {
    u8 pad[0x30];
    u8 m30;
};

struct Next {
    u8 pad[0x80];
    void* next;
};

struct Body {
    u8 pad[0x3C];
    Vec3 pos;
    u8 pad48[0x72 - 0x48];
    u16 m72;
    u8 pad74[0x78 - 0x74];
    Sub78* m78;
    void* m7c;
    Sub80* m80;
    u8 pad84[0x88 - 0x84];
    s16 m88, m8a, m8c, m8e;
    f32 m90;
    void* m94;
    Next* m98;
    u8 pad9c[0xA0 - 0x9C];
    void* mA0[1];
};

void* fn_800A471C(Body* b) {
    Next* n = b->m98;
    if (n == NULL) {
        return NULL;
    }
    switch (b->m72 & 0xE000) {
    case 0x0000:
    case 0x4000:
    case 0x8000:
    case 0xA000:
        return n;
    case 0x2000:
        return n->next;
    case 0x6000:
        return b->m94;
    }
    return NULL;
}

void fn_800A4AE4(Body* b, const Vec3* v) {
    b->pos = *v;
}

void fn_800A4B00(Body* b, Next* n) {
    void* o = b->m94;
    b->m98 = n;
    if (o == NULL) {
        b->m94 = n;
    }
}

void fn_800A4B18(Body* b) {
    Next* n = b->m98;
    if (n != NULL) {
        b->m98 = (Next*)n->next;
    }
}

void fn_800A4B30(Body* b, s32 i, void* v) {
    b->mA0[i] = v;
}

void fn_800A4B40(Body* b, s16 a, s16 c, f32 f) {
    if (b->m88 >= 0 || c <= 0) {
        b->m88 = c;
        b->m8a = a;
        b->m8c = 0;
        b->m90 = f;
        b->m8e = fn_80089ED0() % 360;
    }
}

void fn_800A4BBC(Body* b) {
    b->m88 = 0;
    b->m8a = 0;
    b->m8c = 0;
    b->m90 = lbl_804CD298;
    b->m8e = 0;
}

void fn_800A5D34(Body* b, s32 on) {
    Sub78* m = b->m78;
    if (m != NULL) {
        if (on) {
            m->flags |= 8;
        } else {
            m->flags &= ~8;
        }
    }
}

void fn_800A5D68(Body* b, u32 v, s32 c) {
    Sub80* m = b->m80;
    if (m != NULL && v != m->m30) {
        if (c) {
            fn_8027E4B8(m);
        }
        if (v) {
            b->m80->m30 = 1;
        } else {
            b->m80->m30 = 0;
        }
    }
}

void fn_800A6100(void* a, void* b, void* c) {
    fn_800A5F08(a, b, fn_800A8208(c));
}

void fn_800A633C(void* a, void* b, void* c) {
    fn_800A5B84(a, b, c);
}

void fn_800A6440(Body* b) {
    fn_80081A90(b->m80);
    b->m80 = NULL;
    fn_80006EE0(b->m78);
    b->m78 = NULL;
    b->m7c = NULL;
}

void* fn_800A6490(void* parent) {
    return fn_80081050(lbl_80382138, parent);
}

void* fn_800A64A0() {
    return fn_80083B84(lbl_80382138);
}

struct Arr4 {
    void* m0;
    void* m4[1];
};

void* fn_800A6578(Arr4* a, s32 i) {
    return a->m4[i];
}

void fn_800A66B0(Arr4* a) {
    if (a->m4[0] != NULL) {
        fn_802573EC(a);
    }
}

} // extern "C"
