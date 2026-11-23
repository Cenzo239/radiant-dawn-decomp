#ifndef RG_BATTLE_H
#define RG_BATTLE_H
#include "game/rG_800A3D88/types.h"

/* lbl_803C8E80: game/scene global */
struct SceneGlobal {
    u8 pad[0x3F0];
    void* m3f0;
    u8 pad3f4[0x890 - 0x3F4];
    void* m890;
    u8 pad894[0x15EC - 0x894];
    u32 flags;
    u8 pad15f0[0x15FC - 0x15F0];
    s8 fc;
    u8 fd;
    u8 pad15fe[0x1600 - 0x15FE];
    const char* m1600;
    u8 pad1604[0x1624 - 0x1604];
    char x1624[1];
};
extern "C" SceneGlobal lbl_803C8E80;

struct Res54 {
    u8 pad[8];
    u8 m8;
};

struct Ev {
    u8 pad[0x54];
    Res54* m54;
};

struct Chan {
    u8 pad[0x30];
    void* m30;
    void* m34;
    void* m38;
    u8 pad3c[0x50 - 0x3C];
    u32 flags;
    s8 m54;
    s8 m55;
    u8 pad56[0x78 - 0x56];
    void* m78;
};

struct Body {
    u8 pad[0x6D];
    u8 m6d, m6e;
    u8 pad6f[0x75 - 0x6F];
    u8 m75, m76;
};

struct Scr {
    u8 m0;
    u8 m1;
    u8 pad[6];
    u8 m8, m9;
    u8 padA;
    u8 mB;
    u8 mC;
    u8 padD;
    u16 mE[1];
};

struct Queue {
    u8 pad[0x54];
    u32 head, tail;
};

/* Battle scene controller process (0x98 bytes or more). */
struct Battle {
    u8 pad[0x30];
    Ev* m30;
    void* m34;
    u8 pad38[4];
    Chan* ch[2];
    u8 pad40[0x44 - 0x44];
    Body* m44;
    u8 pad48[0x4C - 0x48];
    u8 m4c;
    u8 pad4d[0x5C - 0x4D];
    struct Queue* q[2];
    u8 pad64[0x68 - 0x64];
    s8 m68;
    u8 pad69;
    u8 m6a, m6b;
    u8 pad6c[0x70 - 0x6C];
    Chan* m70;
    Chan* m74;
    s8 m78;
    u8 m79;
    u8 m7a;
    u8 pad7b;
    u16 m7c;
    s16 m7e;
    u8 m80, m81, m82;
    u8 pad83[0x88 - 0x83];
    Scr* m88;
    u8 pad8c[0x94 - 0x8C];
    u32 m94;
};

#endif
