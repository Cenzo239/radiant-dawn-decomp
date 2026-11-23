/* video.cpp: screen adjust menu, creation. Names guessed. */
#include "game/rJ_800799AC/types.h"

extern "C" {
void* fn_80081194(void* script, void* parent);
void* fn_80079150(int size);
extern u8 lbl_80381330[];
extern void* lbl_8038C294[];
}

struct SprV { virtual void v08(); virtual void v0C(); };
struct Spr {
    void* vt;
    int x4;
    int kind;
    u8 xc;
    u8 xd;
    s16 x;
    s16 y;
    s16 z;
    s16 x14;
    f32 sx;
    f32 sy;
    u8 r, g, b, a;
    f32 x24;
    Spr(int k) {
        vt = lbl_8038C294;
        x4 = 0;
        kind = k;
        xc = 1;
        xd = 1;
        x14 = 0;
        sx = 1.0f;
        sy = 1.0f;
        r = 0x80;
        g = 0x80;
        b = 0x80;
        a = 0xff;
        x24 = 0.0f;
        ((SprV*)this)->v0C();
    }
    void setPos(s16 px, s16 py, s16 pz) { x = px; y = py; z = pz; }
#if TARGET_PC
    /* Host: size_t is 64-bit */
    void* operator new(__SIZE_TYPE__ n) { return fn_80079150(n); }
#else
    void* operator new(u32 n) { return fn_80079150(n); }
#endif
};

struct AdjProc {
    u8 pad[0x30];
    void* img;      /* 0x30 */
    u8 dirty;       /* 0x34 */
    void* arrow[3]; /* 0x38 */
    Spr* o44;
    Spr* o48;
    Spr* o4c;
    Spr* o50;
    Spr* o54;
    Spr* o58;
};

extern "C" void fn_8008D058(void* parent) {
    AdjProc* p = (AdjProc*)fn_80081194(lbl_80381330, parent);
    if (p != NULL) {
        p->img = NULL;
        p->dirty = 0;
        p->o44 = new Spr(2);
        p->o48 = new Spr(3);
        p->o4c = new Spr(0);
        p->o50 = new Spr(1);
        p->o54 = new Spr(2);
        p->o58 = new Spr(3);
        p->o44->setPos(0xe8, 0x38, 0);
        p->o48->setPos(0xe8, 0x78, 0);
        p->o4c->setPos(0xb8, 0xa8, 0);
        p->o50->setPos(0x118, 0xa8, 0);
        p->o54->setPos(0xe8, 0xf8, 0);
        p->o58->setPos(0xe8, 0x138, 0);
    }
}
