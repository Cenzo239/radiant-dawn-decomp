#include "game/rG_800A3D88/types.h"

// Battle camera: start a camera effect on the body.
extern "C" {
struct Cam { u8 p[8]; u16 m8; };
struct Mod { u8 p[0x44]; void* m44; };
struct Sub { u8 p[0x30]; u8 m30; };
struct Body {
    u8 p[0x70];
    u8 m70;
    u8 p71;
    u16 m72;
    u8 p74;
    u8 m75;
    s8 m76;
    u8 p77;
    Mod* m78;
    Cam* m7c;
    Sub* m80;
    s16 m84;
    s16 m86;
    u8 p88[0xA0 - 0x88];
    void* mA0[2];
};
extern char lbl_80365064[];
#if TARGET_PC
FE10_PROTO char * fn_800A6BD4(Cam*, char*);
#else
int fn_800A6BD4(Cam*, char*);
#endif
f32 fn_800A84A4(const char*);
void fn_8000BE20(void*);
void* fn_8017C288(Body*);
void fn_8017C1AC(void*, int);
void fn_80008F6C(Mod*, char*);
int fn_800BD280(void*);
void fn_800B2810(void*, int, f32);
void fn_800A47AC(Body*, int);
void* fn_8000BD3C(char*);
void fn_800088B0(Mod*, void*);
int fn_800A4420(Body* b, Cam* c, int t) {
    char buf[0x40];
/*P*/
void* u;
Body* q;
int k;
int i;
/*E*/
    b->m7c = c;
    if (c == NULL) return 0;
    b->m72 &= ~0x3E;
    b->m72 &= ~0x700;
    switch (b->m75) {
    case 1:
        if (!(c->m8 & 0x40)) return 0;
        break;
    case 0:
        break;
    case 2:
        return 0;
    }
    if (!fn_800A6BD4(c, buf)) return 0;
    if (t < 0) t = (int)fn_800A84A4(lbl_80365064);
    if (b->m78->m44 != NULL && t > 0) {
        b->m84 = t;
        b->m86 = 0;
        fn_800088B0(b->m78, fn_8000BD3C(buf));
        b->m80->m30 = 0;
        return 1;
    }
    if (b->m78 != NULL && b->m78->m44 != NULL) {
        fn_8000BE20(b->m78->m44);
        b->m78->m44 = NULL;
        b->m84 = 0;
        b->m86 = 0;
        void* q = fn_8017C288(b);
        if (q != NULL) fn_8017C1AC(q, -1);
    }
    fn_80008F6C(b->m78, buf);
    b->m80->m30 = 0;
    if ((c->m8 & 8) && b->m76 == 4) b->m72 |= 8;
    if (c->m8 & 2) b->m72 |= 2;
    if (c->m8 & 4) b->m72 |= 4;
    if (c->m8 & 0x10) b->m72 |= 0x10;
    if (c->m8 & 0x20) b->m72 |= 0x20;
    if (c->m8 & 0x100) b->m72 |= 0x100;
    if (c->m8 & 0x200) b->m72 |= 0x200;
    if (c->m8 & 0x400) b->m72 |= 0x400;
    int f = 0;
    if (b->m72 & 2) f = 1;
    if (b->m72 & 8) f++;
    if (f & 1) b->m70 = 1;
    else b->m70 = 0;
    if (c->m8 & 0x800) {
        k = b->m76;
        if (c->m8 & 0x100) k = 0;
        for (q = b, i = 0; i < 2; i++, q = (Body*)((u8*)q + 4)) {
            u = q->mA0[0];
            if (fn_800BD280(u)) fn_800B2810(u, k, 0.0f);
        }
    }
    b->m72 = (c->m8 & 0xE000) | (b->m72 & 0x1FFF);
    fn_800A47AC(b, 0);
    return 1;
}
}
