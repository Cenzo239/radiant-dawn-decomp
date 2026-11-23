#include "game/rG_800A3D88/chr.h"

// Battle character reset.
extern "C" {
struct Blend { u32 mode; f32 a, b, c, d, e; };
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
void* fn_80079150(u32);
void fn_800B29D0(Chr*);
static inline Blend* NewBlend(u32 mode) {
    Blend* b = (Blend*)fn_80079150(0x18);
    if (b != NULL) {
        b->a = 0.0f;
        b->b = 0.0f;
        b->c = 0.0f;
        b->d = 0.0f;
        b->e = 0.0f;
        b->mode = mode;
    }
    return b;
}
void fn_800BEC84(ChrB* c) {
    c->m54 = -1;
    c->m57 = -1;
    c->m55 = -1;
    c->m30 = NULL;
    c->m78 = NULL;
    c->m7c = NULL;
    c->m34 = NULL;
    c->m38 = NULL;
    c->m80 = NULL;
    c->m8c = NewBlend(0);
    c->m90 = NewBlend(0);
    c->m94 = NewBlend(3);
    c->m3c = NULL;
    c->m40 = NULL;
    c->m98 = NULL;
    c->flags = 0;
    c->flags |= 0x204C;
    fn_800B29D0((Chr*)c);
}
}
