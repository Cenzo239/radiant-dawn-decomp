/* Round 20 draft, NOT at a counted level (check_regs.py: other): fn_800A4A98. Self-contained, complete source. Instruction count ours 18 orig 19. What differs: beq L here, bne L; b L in the original (one instruction short). */
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
void* fn_800A8208(void*);
void fn_800A5F08(void*, void*, void*);
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
void* fn_800A471C(Body* b);

void fn_800A4AE4(Body* b, const Vec3* v);

void fn_800A4B00(Body* b, Next* n);

void fn_800A4B18(Body* b);

void fn_800A4B30(Body* b, s32 i, void* v);

void fn_800A4B40(Body* b, s16 a, s16 c, f32 f);

void fn_800A4BBC(Body* b);

void fn_800A5D34(Body* b, s32 on);

void fn_800A5D68(Body* b, u32 v, s32 c);

void fn_800A6100(void* a, void* b, void* c);

void fn_800A633C(void* a, void* b, void* c);

void fn_800A6440(Body* b);

void* fn_800A6490(void* parent);

void* fn_800A64A0();


struct Arr4 {
    void* m0;
    void* m4[1];
};
void* fn_800A6578(Arr4* a, s32 i);

void fn_800A66B0(Arr4* a);


} // extern "C"


#pragma use_lmw_stmw off
/* ---- from rG_800A3D88/wip/fn_800A4A98.cpp ---- */
extern "C" {
// size 0x48 vs 0x4C: the original has beq-over-b for the inner null test.
static inline void Sub78_sync(Sub78* m) {
    Sub44* s = m->m44;
    if (s == NULL) {
        return;
    }
    m->m58 = s->v18;
}

void fn_800A4A98(Body* b) {
    Sub78* m = b->m78;
    if (m != NULL) {
        Sub78_sync(m);
    }
}
}
