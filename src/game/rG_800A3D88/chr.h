#ifndef RG_CHR_H
#define RG_CHR_H
#include "game/rG_800A3D88/types.h"

struct Vec {
    f32 x, y, z;
};

struct Mdl {
    u32 flags;
    u8 pad4[0x58 - 4];
    f32 frame;
};

struct AnimSlot {
    void* a;
    const char* name;
};

struct ChrData {
    u8 pad[4];
    const char* name;
    u8 pad8[0x150 - 8];
    AnimSlot* anims;
};

struct AnimState {
    u8 pad[8];
    u16 flags;
};

/* Battle character object: model at +0x30, data at +0x78. */
struct Chr {
    u8 pad[0x30];
    Mdl* mdl;
    void* m34;
    void* m38;
    void* m3c[2];
    Vec m44;
    u32 flags;
    u16 m54;
    u8 pad56;
    u8 m57;
    s16 m58, m5a;
    u8 pad5c[2];
    s8 m5e;
    u8 pad5f[0x78 - 0x5F];
    ChrData* data;
    AnimState* m7c;
    u8 pad80[0x98 - 0x80];
    void* m98;
};

#endif
