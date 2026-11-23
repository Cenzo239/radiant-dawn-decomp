/* Scroll arrows of the text panel. */
#include "game/rR_80175E5C/types.h"
#include "game/rR_80175E5C/strpool.h"
#define F(p, t, o) (*(t*)((u8*)(p) + (o)))

struct C4 { u8 r, g, b, a; };
struct Arrow {
    u8 pad0[0x30];
    u8* obj;
    u8 pad34[0x38 - 0x34];
    u8 x38;
    u8 x39;
    u8 pad3A[0x5C - 0x3A];
    u8 x5C;
    u8 x5D;
    C4 col;
};

extern "C" {
extern char lbl_804CA440[8];
extern u8 lbl_80387C60[];
extern u8 lbl_804CA7C0, lbl_804CA7C1, lbl_804CA7C2, lbl_804CA7C3;
f32 fn_8001EBC8(f32, f32, f32, f32, int);
void fn_800E4AD4(f32, void*);
void fn_800E48AC(f32, f32, f32, void*);
void fn_800E4A40(f32, void*);
void fn_800E515C(void*);
void fn_800E56B8(void*);
#if TARGET_PC
FE10_PROTO void* fn_800E4060(const char*, p32arg);
#else
void* fn_800E4060(const char*, int);
#endif
void* fn_80078CCC(int, const char*, int);
void fn_8001D424(void*);
void fn_80081A90(void*);
void fn_80078E24(void*);
void* fn_8001D3EC(const char*, int);

static inline void SetC(u8* q, const C4& c) {
    q[0] = c.r;
    q[1] = c.g;
    q[2] = c.b;
    q[3] = c.a;
}


void fn_80179214(u8* p) {
    /*P*/
    int dx;
    int dy;
    u8* o;
/*E*/
    int t = F(p, int, 0x50);
    F(p, int, 0x50) = ++t;
    if (F(p, int, 0x54) > 0) {
        F(p, int, 0x50) = ++t;
        F(p, int, 0x54) = F(p, int, 0x54) - 1;
    }
    if (F(p, int, 0x50) >= F(p, int, 0x58)) {
        F(p, int, 0x50) = F(p, int, 0x50) - F(p, int, 0x58);
    }
    if (p[0x5D] != 0) {
        dx = 0;
        dy = 0;
        if (p[0x5C] != 0) {
            int d = fn_8001EBC8(0.0f, 10.0f, 30.0f, F(p, int, 0x54), 2);
            switch (F(p, int, 0x4C)) {
            case 8:
                dy = -d;
                break;
            case 4:
                dy = d;
                break;
            case 1:
                dx = -d;
                break;
            case 2:
                dx = d;
                break;
            }
        }
        o = F(p, u8*, 0x30);
        if (o != 0) {
            fn_800E4AD4(0.05f, o);
            fn_800E48AC(F(p, f32, 0x3C) + dx, F(p, f32, 0x40) + dy, 0.0f, o);
            F(F(o, u8*, 0x30), s16, 8) = F(p, f32, 0x44);
            fn_800E4AD4(F(p, f32, 0x48), o);
            C4 c = *(C4*)(p + 0x5E);
            SetC(F(o, u8*, 0x30) + 0x64, c);
            F(o, u8*, 0x30)[0x10] = p[0x39];
            switch (F(p, int, 0x4C)) {
            case 4:
                fn_800E4A40(0.0f, o);
                break;
            case 1:
                fn_800E4A40(90.0f, o);
                break;
            case 8:
                fn_800E4A40(180.0f, o);
                break;
            case 2:
                fn_800E4A40(270.0f, o);
                break;
            }
            fn_800E515C(o);
            fn_800E56B8(o);
        }
    }
}

Arrow* fn_8017948C(Arrow* p, int kind) {
    F(p, int, 0x4C) = 0;
    F(p, int, 0x50) = 0;
    F(p, int, 0x34) = 0;
    F(p, int, 0x54) = 0;
    p->x5D = 1;
    p->x5C = 1;
    F(p, int, 0x58) = 0x30;
    F(p, f32, 0x3C) = 0.0f;
    F(p, f32, 0x40) = 0.0f;
    F(p, f32, 0x44) = 0.0f;
    F(p, f32, 0x48) = 1.0f;
    C4 c = {0x80, 0x80, 0x80, 0xFF};
    p->col.r = c.r;
    p->col.g = c.g;
    p->col.b = c.b;
    p->col.a = c.a;
    p->x39 = 0xFF;
    p->x38 = kind;
    switch (kind) {
    case 0:
        p->obj = (u8*)fn_800E4060("EID_ARROW1", 4);
        F(p, f32, 0x48) = 0.05f;
        break;
    case 1:
        p->obj = (u8*)fn_800E4060("EID_ARROW1", 4);
        F(p, f32, 0x48) = 0.025f;
        break;
    case 2:
        p->obj = (u8*)fn_800E4060("EID_ARROW3", 4);
        F(p, f32, 0x48) = 0.05f;
        break;
    default:
        p->obj = NULL;
        break;
    }
    u8* o = p->obj;
    if (o != NULL) {
        u8* q = F(o, u8*, 0x30);
        F(q, int, 0x18) |= 0x101C;
    }
    return p;
}

u8* fn_80179660(u8* p) {
    F(p, void*, 0x28) = lbl_80387C60;
    F(p, void*, 0) = fn_8001D3EC("window/scrollbar.cms", 0x80);
    F(p, s16, 0x12) = 0;
    F(p, s16, 0x14) = 0;
    F(p, s16, 0x16) = 0;
    F(p, s16, 0x18) = 0;
    F(p, f32, 4) = 0.0f;
    F(p, f32, 8) = 0.0f;
    F(p, f32, 0xC) = 0.0f;
    F(p, int, 0x20) = 0;
    F(p, int, 0x24) = 0;
    p[0x1A] = 0xFF;
    C4 c = *(C4*)&lbl_804CA7C0;
    SetC(p + 0x1B, c);
    return p;
}

static inline void Free(u8* e) {
    if (F(e, void*, 0x34) != 0) {
        fn_8001D424(F(e, void*, 0x34));
    }
    if (F(e, void*, 0x30) != 0) {
        fn_80081A90(F(e, void*, 0x30));
        F(e, void*, 0x30) = 0;
    }
    fn_80078E24(e);
}

void fn_801798A8(u8* o, int on) {
    u8* e = F(o, u8*, 0x20);
    if (e != 0) {
        if (e != 0) Free(e);
        F(o, u8*, 0x20) = 0;
    }
    e = F(o, u8*, 0x24);
    if (e != 0) {
        if (e != 0) Free(e);
        F(o, u8*, 0x24) = 0;
    }
    if (on != 0) {
        u8* a = (u8*)fn_80078CCC(100, lbl_804CA440, 0);
        if (a != 0) a = (u8*)fn_8017948C((Arrow*)a, 1);
        F(o, u8*, 0x20) = a;
        u8* b = (u8*)fn_80078CCC(100, lbl_804CA440, 0);
        if (b != 0) b = (u8*)fn_8017948C((Arrow*)b, 1);
        F(o, u8*, 0x24) = b;
        F(F(o, u8*, 0x20), int, 0x4C) = 8;
        F(F(o, u8*, 0x24), int, 0x4C) = 4;
        F(o, u8*, 0x20)[0x5C] = 0;
        F(o, u8*, 0x24)[0x5C] = 0;
        C4 c = {0x40, 0x40, 0x80, 0xFF};
        u8* q = F(o, u8*, 0x20);
        q[0x5E] = c.r;
        q[0x5F] = c.g;
        q[0x60] = c.b;
        q[0x61] = c.a;
        C4 c2 = {0x40, 0x40, 0x80, 0xFF};
        q = F(o, u8*, 0x24);
        q[0x5E] = c2.r;
        q[0x5F] = c2.g;
        q[0x60] = c2.b;
        q[0x61] = c2.a;
    }
}
}
