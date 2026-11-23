#include "game/rG_800A3D88/types.h"

// Battle camera: start a camera effect if it differs from the running one.
extern "C" {
struct Cam { u8 p[8]; u16 m8; u8 pA; u8 mB; };
struct CamR { u8 p[0x18]; int m18; };
struct Mod { u8 p[0x44]; CamR* m44; u8 p48[0x58 - 0x48]; f32 m58; };
struct Tgt { u8 p[0x80]; void* m80; };
struct Body {
    u8 p[0x72];
    u16 m72;
    u8 p74;
    u8 m75;
    s8 m76;
    u8 p77;
    Mod* m78;
    Cam* m7c;
    u8 p80[0x94 - 0x80];
    void* m94;
    Tgt* m98;
    void* m9c;
};
Cam* fn_800A6C38(void*);
Cam* fn_800A5DE8(Body*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800B175C(void*, int);
#else
void* fn_800B175C(void*, int);
#endif
int fn_800A4420(Body*, Cam*, int);
#if TARGET_PC
FE10_PROTO void* fn_800A83E4(p32arg);
#else
void* fn_800A83E4(int);
#endif
void* fn_800A6D08(void*, int);
static inline void* Target(Body* b) {
    Tgt* t = b->m98;
    if (t == NULL) return NULL;
    switch (b->m72 & 0xE000) {
    case 0:
    case 0x4000:
    case 0x8000:
    case 0xA000:
        return t;
    case 0x2000:
        return t->m80;
    case 0x6000:
        return b->m94;
    }
    return NULL;
}
static inline BOOL Differs(Body* b, Cam* c) {
    if (b->m7c != NULL && b->m9c == Target(b)) {
        Cam* r = b->m7c;
        if (c->m8 & 0x80) return 1;
        if (c == r) return 0;
        if (c->mB != 0 && c->mB == r->mB) return 0;
    }
    return 1;
}
static inline int Start(Body* b, Cam* c, BOOL adj) {
    if (!Differs(b, c)) return 0;
    int r = fn_800A4420(b, c, -1);
    if (adj && b->m78 != NULL && b->m78->m44 != NULL) {
        b->m78->m58 = b->m78->m44->m18;
    }
    return r;
}
int fn_800A5F08(Body* b, void* e, int k) {
    BOOL adj = 0;
    if (e == NULL) return 0;
    if (k < 0) return 0;
    void* q = fn_800B175C(e, k);
    if (q == NULL) return 0;
    Cam* c = fn_800A6C38(q);
    if (c == NULL) return 0;
    if (b->m75 == 1 && !(c->m8 & 0x40)) {
        c = fn_800A5DE8(b);
        adj = 1;
    }
    return Start(b, c, adj);
}
int fn_800A614C(Body* b, int k) {
    BOOL adj = 0;
    void* q = fn_800A83E4(k);
    if (q == NULL) return 0;
    q = fn_800A6D08(q, b->m76);
    if (q == NULL) return 0;
    Cam* c = fn_800A6C38(q);
    if (c == NULL) return 0;
    if (b->m75 == 1 && !(c->m8 & 0x40)) {
        c = fn_800A5DE8(b);
        adj = 1;
    }
    return Start(b, c, adj);
}
}
