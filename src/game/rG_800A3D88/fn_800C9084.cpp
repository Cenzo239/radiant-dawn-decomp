/* Screen fade / flash / wipe processes: creation of the four effect
   processes (fn_800C9084) and the "kill unless it is one of ours" walk
   callback (fn_800C91C8).

   lbl_80382930 is the pooled .data of this unit: the proc scripts are file
   statics and the jump table of fn_800C8000 lies between the first and the
   second, so the real fn_800C8000 (matched in fn_800C8000.cpp) is repeated
   here to put the tables at their real offsets:
       +0x00 sFade   +0x18 jump table   +0x40 sFlash   +0x58 sWipe
       +0x70 sGrab (lbl_803829A0)       +0x80 sForce
   The tables are reconstructed from the DOL. Needs
   fn_800C9084.symbols.json ("...data.0" = lbl_80382930).
   Port caveats: use fn_800C8000 from its own file; sGrab is lbl_803829A0. */
#include "game/rG_800A3D88/types.h"
#pragma auto_inline off

// Screen fade: start one of the fade modes.
extern "C" {
struct Fd { u8 p[0x30]; u8 mode; u8 p31; u16 st; u16 t; u16 n; f32 from; f32 to; int col; u8 p44[4]; void* buf; u8 tex[1]; };
struct Ph { u8 p[0x54]; Fd* m54; };
extern u8 lbl_803829A0[];
u32 fn_8030585C(int, int, int, int, int);
void* fn_80079958(u32, int);
void DCInvalidateRange(void*, u32);
void fn_80305A40(void*, void*, int, int, int, int, int, int);
void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
#if TARGET_PC
FE10_PROTO Ph* fn_80081050(void*, p32arg);
#else
Ph* fn_80081050(void*, int);
#endif
static inline void Grab(Fd* f) {
    u32 sz = fn_8030585C(0x260, 0x1C0, 4, 0, 0);
    if (f->buf == NULL) f->buf = fn_80079958(sz, 0x40);
    DCInvalidateRange(f->buf, sz);
    fn_80305A40(f->tex, f->buf, 0x260, 0x1C0, 4, 0, 0, 0);
    fn_80305C94(f->tex, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    Ph* q = fn_80081050(lbl_803829A0, 6);
    q->m54 = f;
}

void fn_800C7B74(void*);
void fn_800C83DC(void*);
void fn_800C87A0(void*);
void fn_800C8D1C(void*);
void fn_800C8D80(void*);
extern char lbl_804CD5C0[];   /* "E_Fade" */
extern char lbl_804CD5E0[];   /* "E_Flash" */
extern char lbl_804CD5F4[];   /* "E_Wipe" */
extern char lbl_80365E90[];   /* "E_ForceFade" */
extern u8 lbl_803829D8[];

static void* sFade[] = {
    (void*)0x2003, lbl_804CD5C0, (void*)0x54911001, (void*)0x201A, (void*)fn_800C7B74, (void*)0
};
void fn_800C8000(Fd* f, u32 mode, int time) {
    if (time == 0 || !(f->st & 0xD) || f->mode != mode) {
        f->mode = mode;
        f->st = 1;
        f->t = 0;
        f->n = (f32)time / 16.666666f;
        switch (mode) {
        case 0:
            f->st = 2;
            f->to = 0.0f;
            f->col = 0;
            break;
        case 1:
            f->st = 6;
            f->to = 1.0f;
            f->col = 0xFF;
            break;
        case 2:
            f->from = 1.0f;
            f->to = 0.0f;
            f->col = 0xFF;
            break;
        case 3:
            f->st |= 4;
            f->from = 0.0f;
            f->to = 1.0f;
            f->col = 0xFF;
            break;
        case 4:
            f->st = 10;
            f->to = 1.0f;
            f->col = -1;
            break;
        case 5:
            f->from = 1.0f;
            f->to = 0.0f;
            f->col = -1;
            break;
        case 6:
            f->st |= 8;
            f->from = 0.0f;
            f->to = 1.0f;
            f->col = -1;
            break;
        case 7:
            f->from = 1.0f;
            f->to = 0.0f;
            f->col = -1;
            Grab(f);
            break;
        case 8:
            f->mode = 7;
            f->st = 2;
            f->from = 1.0f;
            f->to = 1.0f;
            f->n = 0xFFFF;
            f->col = -1;
            Grab(f);
            break;
        case 9:
            if (f->buf == NULL) {
                f->st = 2;
                f->to = 0.0f;
                f->col = 0;
            } else {
                f->mode = 7;
                f->from = 1.0f;
                f->to = 0.0f;
                f->col = -1;
            }
            break;
        }
    }
}

static void* sFlash[] = {
    (void*)0x2003, lbl_804CD5E0, (void*)0x54911001, (void*)0x201A, (void*)fn_800C83DC, (void*)0
};
static void* sWipe[] = {
    (void*)0x2003, lbl_804CD5F4, (void*)0x54911001, (void*)0x201A, (void*)fn_800C87A0, (void*)0
};
static void* sGrab[] = {
    (void*)0x100A, (void*)0x200F, (void*)fn_800C8D1C, (void*)0
};
static void* sForce[] = {
    (void*)0x2003, lbl_80365E90, (void*)0x54911001, (void*)0x201A, (void*)fn_800C8D80, (void*)0
};

struct FadeG { u8 pad[0x32]; u16 m32; u8 pad34[0x14]; void* m48; };
extern FadeG* lbl_804CB6D0;
extern FadeG* lbl_804CB6D4;
extern FadeG* lbl_804CB6D8;
extern FadeG* lbl_804CB6DC;

void fn_800C9084(void) {
    lbl_804CB6D4 = (FadeG*)fn_80081050(sFade, 8);
    lbl_804CB6D4->m48 = NULL;
    lbl_804CB6D0 = (FadeG*)fn_80081050(sForce, 8);
    lbl_804CB6D8 = (FadeG*)fn_80081050(sFlash, 8);
    lbl_804CB6D8->m32 = 0;
    lbl_804CB6DC = (FadeG*)fn_80081050(sWipe, 8);
    lbl_804CB6DC->m32 = 0;
}

struct P { void* script; u8 pad[0x14]; u32 m18; u8 pad1c[0xF]; u8 m2b; };
void fn_800893C4(P*);

void fn_800C91C8(P* p) {
    if (p->m2b == 0x7B) return;
    if (p->script == lbl_803829D8) return;
    if (p->script == sFade) return;
    if (p->script == sForce) return;
    if (p->script == sGrab) return;
    if (p->m18 == 1) return;
    if (p->m18 == 7) return;
    fn_800893C4(p);
}
}
