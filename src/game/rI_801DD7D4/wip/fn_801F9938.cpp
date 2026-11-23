/* wip near misses for fn_801F9938.cpp (whole file kept so declarations stay together):
   fn_801FC0D8: size 0x44, want 0x3C; 9 of 15 words differ
   fn_801FE504: size 0x30, want 0x1C; 7 of 7 words differ
   fn_80201CE0: 4 of 14 words differ
   fn_80201D58: 4 of 14 words differ
   fn_80201F38: 13 of 17 words differ
*/
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {

typedef struct RangeState { void* x0; u8 pad[0x12c]; } RangeState;
extern RangeState lbl_803CA870;
extern char lbl_803CAB38[];
extern char lbl_8036F03C[];
extern char lbl_8038D254[];
extern char lbl_8038DF6C[];
extern char lbl_8038DF60[];
extern char lbl_8038DF48[];
extern char lbl_8038DF2C[];
extern char lbl_8038DF10[];
extern char lbl_8038DEC4[];
extern char lbl_8038DEB4[];
extern char lbl_8038DE94[];
extern char lbl_8038DE78[];
extern char lbl_8038DE6C[];
extern char lbl_8038DE50[];
extern char lbl_8038DE44[];
extern char lbl_804CA980[8];
extern char lbl_804CA978[8];
extern char lbl_804CA970[8];
extern char lbl_804CA968[8];
void fn_801E5734(void*, void*);
void* fn_801E5640(void*, int, int);
int fn_801E999C(void*, int);
void fn_8008939C(void*);
void fn_80083DC4(void*, int);
void fn_801288D4(void*);
void* fn_80083B84(void*);
void fn_801EA538(void*, void*);
int fn_801F1688(void*);
int fn_800D0864(const char*);
int fn_80060754(void*);
void fn_801DDDF8(void*, void*);
void fn_801DDDE8(void);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7E8(int);

typedef struct LM {
    u8 pad[0x4c];
    u8 x4c;
    u8 pad4d[3];
    s16 x50;
    u8 pad52[0x64 - 0x52];
    const char* x64;
} LM;
typedef struct Sub { u8 pad[0x40]; void* x40; } Sub;
typedef struct Proc {
    u8 pad[0x44];
    Sub* x44;
    u8 pad48[4];
    LM* x4c;
    u8 pad50[4];
    u8* x54;
    u8 pad58[4];
    void* x5c;
    u8 pad60[0x68 - 0x60];
    void* x68;
    u8 x6c;
} Proc;

void fn_801F9938(Proc* o) { o->x54[0x51] = 1; }

void fn_801F9948(Proc* o) {
    fn_801E5734(o, o->x54);
    {
        const char* s = lbl_8036F03C + 0x1d3;
        LM* p = (LM*)fn_801E5640(o, -0x1000, 0);
        if (p != NULL) {
            p->x64 = s;
        }
    }
}

void fn_801FA5D8(Proc* o) {
    LM* m = o->x4c;
    m->x4c = 1;
    m->x50 = fn_801E999C(m, 0);
}

void fn_801FA618(Proc* o) {
    fn_801E5734(o, o->x4c);
    {
        const char* s = lbl_8036F03C + 0x216;
        LM* p = (LM*)fn_801E5640(o, -0x1000, 0);
        if (p != NULL) {
            p->x64 = s;
        }
    }
}

void fn_801FAE6C(Proc* o) { fn_8008939C(o->x5c); }
void fn_801FB048(Proc* o) { fn_8008939C(o->x5c); }
void fn_801FB7E8(Proc* o) { fn_80083DC4(o, o->x6c); }
void fn_801FBA18(void) { fn_801288D4(lbl_803CA870.x0); }
void fn_801FBC30(void) {}

void fn_801FBEB0(void) {
    Proc* p = (Proc*)fn_80083B84(lbl_8038D254);
    if (p != NULL) {
        p->x68 = NULL;
        if (p->x44 != NULL) {
            p->x68 = p->x44->x40;
            fn_801EA538(p->x44, NULL);
        }
    }
}

int fn_801FC0D8(void) {
    int t = !fn_801F1688(lbl_803CA870.x0);
    return t ? 0 : 2;
}

void* fn_801FC114(void) { return lbl_8038DF6C; }
int fn_801FC120(void) { return fn_800D0864(lbl_8038DF60); }
void* fn_801FC260(void) { return lbl_804CA980; }
int fn_801FC268(void) { return fn_800D0864(lbl_8038DF48); }
void* fn_801FC3D0(void) { return lbl_804CA978; }
int fn_801FC3D8(void) { return fn_800D0864(lbl_8038DF2C); }
void* fn_801FC55C(void) { return lbl_804CA970; }
int fn_801FC564(void) { return fn_800D0864(lbl_8038DF10); }
void* fn_801FC724(void) { return lbl_8038DEC4; }
int fn_801FC730(void) { return fn_800D0864(lbl_8038DEB4); }

int fn_801FC7D4(void) {
    return fn_80060754(lbl_803CAB38) != 0 ? 0 : 2;
}

void* fn_801FC810(void) { return lbl_804CA968; }
int fn_801FC818(void) { return fn_800D0864(lbl_8038DE94); }
void* fn_801FC934(void) { return lbl_8038DE78; }
int fn_801FC940(void) { return fn_800D0864(lbl_8038DE6C); }
int fn_801FC9E4(void) { return 0; }
void* fn_801FC9EC(void) { return lbl_8038DE50; }
int fn_801FC9F8(void) { return fn_800D0864(lbl_8038DE44); }

typedef struct Lst { u8 pad[0xa6]; s8 sel; } Lst;
typedef struct ProcS { u8 pad[0x64]; s8 x64; } ProcS;

void fn_801FCA04(void* o, Lst* l) {
    ProcS* p = (ProcS*)fn_80083B84(lbl_8038D254);
    p->x64 = l->sel;
    fn_801DDDF8(o, l);
}

void fn_801FCA58(void* o, Lst* l) {
    s8 v;
    fn_801DDDE8();
    v = ((ProcS*)fn_80083B84(lbl_8038D254))->x64;
    if (v >= 0) {
        l->sel = v;
    }
}

void fn_801FCF7C(VO4* o) {
    o->v94();
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E7E8(0x80);
    fn_8007E164();
}

int fn_801FD234(void) { return 0x20; }
int fn_801FD23C(void) { return 0; }
int fn_801FD244(void) { return 0; }

void* fn_801FD24C(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void fn_801D772C(int, int, int);
void fn_801D7AF8(int, int, int);
void fn_8007E174(int, int);
void fn_801D870C(int, int, int, int);
void fn_80072ACC(int, int, int, int, int, int, int);
extern char lbl_8038DFD4[];
extern char lbl_8038DFC8[];
extern char lbl_8038DF94[];
extern char lbl_8038DF88[];
extern void* lbl_804CBEF8;

void fn_801FD3FC(void) {
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E7E8(0x80);
    fn_8007E164();
}

void* fn_801FD594(void) { return lbl_8038DFD4; }
int fn_801FD5A0(void) { return fn_800D0864(lbl_8038DFC8); }
void* fn_801FD700(void) { return lbl_8038DF94; }
int fn_801FD70C(void) { return fn_800D0864(lbl_8038DF88); }

void fn_801FD858(VO0* o) {
    o->v14();
    fn_801D772C(0, 0, 0x10);
}

void fn_801FDAA4(VO0* o) {
    o->v14();
    fn_801D7AF8(0, 0, 0x10);
}

void fn_801FDAE0(RList* l) {
    LNode* e = (LNode*)&l->prev;
    l->size = 0;
    l->next = e;
    l->prev = e;
}

void* fn_801FE048(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void* fn_801FE088(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void* fn_801FE0C8(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void* fn_801FE4C4(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

typedef struct Tri { int a, b, c; } Tri;

void fn_801FE504(u8* o, Tri* t) {
    Tri c = *t;
    *(Tri*)(o + 0x44) = c;
}

class Win2 {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30(void*);
    u8 pad4[6];
    s16 xa, xc, xe, x10;
    s16 x12, x14, x16, x18;
};

void* fn_801FE5C8(u8* o) { return *(void**)(*(u8**)(o + 0x138) + 0x40); }
void fn_801FE5D4(Win2* o) { o->v30(lbl_804CBEF8); }
void fn_801FE5E8(u8* o, void* v) {
    *(void**)(*(u8**)(o + 0x138) + 0x40) = v;
    lbl_804CBEF8 = v;
}

s16 fn_801FE710(Win2* o) { return o->x16 - o->x12; }
int fn_801FE724(void) { return 0x1c; }

void* fn_801FE72C(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

BOOL fn_801FEEBC(u8* o, void* x) {
    u8 (*fp)(void*, void*) = *(u8 (**)(void*, void*))(o + 0x130);
    if (fp != NULL) {
        return fp(x, *(void**)(o + 0x134)) != 0;
    }
    return 1;
}

void fn_801FEFE0(void* o, int x, int y, int w, int h, int k) {
    fn_80072ACC(x + (w >> 1), y + (h >> 1), w, 0x17, 0x19, 0x4c, k);
}

void fn_801FF00C(Win2* o) {
    o->v14();
    fn_801D870C(0, 0, (s16)(o->xe - o->xa), 0x10);
}

void fn_801FFE80(Win2* o) { o->v18(); }
void fn_80200008(Win2* o) { o->v24(); }

typedef struct Tgt { u8 pad[0x50]; u8 x50; u8 pad51[0x94 - 0x51]; s16 x94, x96; } Tgt;
typedef struct Seq { u8 pad[0x34]; RList list; } Seq;
void* fn_801E40B0(void*, int);
void fn_801D817C(int, int, int);
void fn_801D7B88(int, int, int);
void fn_801D80EC(int, int, int);
u32* fn_801E2204(void*, s16*, s16*);

void fn_80200018(Seq* o) {
    Tgt* t = o->list.size != 0 ? (Tgt*)o->list.prev->val : NULL;
    t->x50 = 0;
    t->x94 = 0;
    t->x96 = 0;
    if (o != NULL) {
        fn_801E40B0(o, 0);
    }
}

void fn_80200058(u8* o) { *(s16*)(o + 0x40) = 0; }

void fn_802007A8(Win2* o) {
    o->v14();
    fn_801D817C(0, 0, 0x10);
}

void fn_80200ADC(Win2* o) {
    o->v14();
    fn_801D817C(0, 0, 0x10);
}

u32 fn_80200E08(Win2* o) {
    s16 q[2];
    s16 p[2];
    p[0] = 0;
    p[1] = 0;
    return *fn_801E2204(o, q, p);
}

void fn_80200E40(Win2* o) { o->v14(); }

u32 fn_8020109C(Win2* o) {
    s16 q[2];
    s16 p[2];
    p[0] = 0;
    p[1] = 0;
    return *fn_801E2204(o, q, p);
}

void fn_802010D4(void* o, int x, int y, int w, int h, int k) {
    fn_80072ACC(x + (w >> 1), y + (h >> 1), w, 0x17, 0x19, 0x4c, k);
}

void fn_80201100(Win2* o) { o->v14(); }

void fn_80201650(Win2* o) {
    if (*(int*)((u8*)o + 0x40) == 1) {
        o->v24();
    }
}

void fn_80201670(Win2* o) {
    o->v14();
    fn_801D7B88(0, 0, 0x10);
}

void fn_80201B28(Win2* o) {
    o->v14();
    fn_801D80EC(0, 0, 0x10);
}

typedef struct LS {
    u8 pad[0xa];
    s16 xa, xc, xe, x10;
    s16 x12, x14, x16, x18;
    u8 pad1a[4];
    s16 x1e, x20;
} LS;

static inline void lsSet(LS* o, s16 a, s16 b, s16 c, s16 d, s16 e, s16 f) {
    o->x12 = a;
    o->x14 = b;
    o->x16 = c;
    o->x18 = d;
    o->x1e = e;
    o->x20 = f;
}

void fn_80201CE0(LS* o) {
    lsSet(o, 0, 0, o->xe - o->xa, o->x10 - o->xc, 0, 0);
}

void* fn_80201D18(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void fn_80201D58(LS* o) {
    lsSet(o, 0, 0, o->xe - o->xa, o->x10 - o->xc, 0, 0);
}

void* fn_80201D90(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void fn_80201F38(LS* o) {
    s16 h = o->x10 - o->xc;
    lsSet(o, 0, 4, o->xe - o->xa, h - 4, 0, 0);
}

void* fn_80201F7C(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

}
