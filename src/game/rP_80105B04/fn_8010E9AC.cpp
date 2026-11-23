#include "game/rP_80105B04/rp.h"

/* Difficulty-scaled constants: lbl_803680D8 is the name of a game-data block
   and fn_80060728(lbl_803CAB38)->diff (+0x11) is the difficulty. */
struct Game {
    u8 pad0[0x11];
    u8 diff; /* 0x11 */
};
struct Bal {
    s16 w[4][12];
    s16 t60[4];
    u8 b68[4][8];
};
extern "C" {
extern char lbl_803680D8[];
extern u8 lbl_803CAB38[];
Bal* fn_80076F54(const char* name);
Game* fn_80060728(void* p);
}

static inline int DiffIdx() {
    switch (fn_80060728(lbl_803CAB38)->diff) {
    case 3: return 0;
    case 0: return 1;
    case 1: return 2;
    case 2: return 3;
    default: return 0;
    }
}

extern "C" {
s16 fn_8010E9AC() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x0))[DiffIdx()];
}
s16 fn_8010EA40() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x8))[DiffIdx()];
}
s16 fn_8010EAD8() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x10))[DiffIdx()];
}
s16 fn_8010EB70() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x18))[DiffIdx()];
}
s16 fn_8010EC08() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x20))[DiffIdx()];
}
s16 fn_8010ECA0() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x28))[DiffIdx()];
}
s16 fn_8010ED38() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x30))[DiffIdx()];
}
s16 fn_8010EDD0() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x38))[DiffIdx()];
}
s16 fn_8010EE68() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x40))[DiffIdx()];
}
s16 fn_8010EF00() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x48))[DiffIdx()];
}
s16 fn_8010EF98() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return ((s16*)((u8*)p + 0x60))[DiffIdx()];
}
u8 fn_8010F030() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return p->b68[DiffIdx()][0x68 - 0x68];
}
u8 fn_8010F0C8() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return p->b68[DiffIdx()][0x69 - 0x68];
}
u8 fn_8010F160() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return p->b68[DiffIdx()][0x6a - 0x68];
}
u8 fn_8010F1F8() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return p->b68[DiffIdx()][0x6b - 0x68];
}
u8 fn_8010F290() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return p->b68[DiffIdx()][0x6c - 0x68];
}
u8 fn_8010F328() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return p->b68[DiffIdx()][0x6d - 0x68];
}
u8 fn_8010F3C0() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return p->b68[DiffIdx()][0x6e - 0x68];
}
u8 fn_8010F458() {
    Bal* p = fn_80076F54(lbl_803680D8);
    return p->b68[DiffIdx()][0x6f - 0x68];
}
}
