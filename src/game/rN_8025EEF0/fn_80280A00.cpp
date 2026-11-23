/* Screen bars (lbl_804CC0A8 state), save-confirm dialog, game reset screen. */
#define RN_FLAGS_PLAIN
#include "game/rN_8025EEF0/calls.h"

#pragma use_lmw_stmw on

extern "C" {

f32 fn_8017F68C(f32 a, f32 b, f32 t, f32 d, int mode);
void* memset(void* p, int v, unsigned n);
extern u8* lbl_804CC0AC;

struct Bars {
    s16 m0, m2, m4, m6, m8, mA, mC, mE, m10, m12, m14, m16, m18, m1A, m1C;
};
extern Bars* lbl_804CC0A8;
extern char lbl_803738BC[];

extern u8 lbl_80392C18[];
extern const char* lbl_80392C58[][2];
extern const char* lbl_80392DC8[][2];
extern void* lbl_804CC0B0[2];
extern int lbl_804CC0C4;
extern int lbl_804CC0B8;
extern const char* lbl_804CC0BC;
extern const char* lbl_804CC0C0;
extern u8 lbl_804CC0C8;
extern s16 lbl_804CC0CA;
extern char lbl_80373AD0[];

extern char lbl_80373AA0[];
void fn_8028392C(void* a, int c, int d, u8 g, void* parent, int mode) {
    const char* s = lbl_80373AA0 + 0x4D;
    if (mode == 1) {
        fn_80081050(lbl_80392C18, parent);
    } else {
        fn_80081194(lbl_80392C18, parent);
    }
    lbl_804CC0B0[0] = a;
    lbl_804CC0B0[1] = 0;
    lbl_804CC0C4 = c;
    lbl_804CC0B8 = d;
    lbl_804CC0BC = s;
    lbl_804CC0C0 = s;
    lbl_804CC0C8 = g;
    lbl_804CC0CA = mode;
}

void fn_802839C4(void* a, int b, int c, int d, const char* e, const char* f, u8 g, void* parent, int mode) {
    if (mode == 1) {
        fn_80081050(lbl_80392C18, parent);
    } else {
        fn_80081194(lbl_80392C18, parent);
    }
    lbl_804CC0B0[0] = a;
    lbl_804CC0B0[1] = (void*)b;
    lbl_804CC0C4 = c;
    lbl_804CC0B8 = d;
    lbl_804CC0BC = e;
    lbl_804CC0C0 = f;
    lbl_804CC0C8 = g;
    lbl_804CC0CA = mode;
}

void fn_80283B5C(void* p) {
    int lang = (s8)fn_8024BC94()[0x1BC8];
    if (fn_8023F880(lbl_80392C58[lang][fn_801D09F0()]) != 0) {
        fn_80083B78(p);
    }
}

void fn_80288A2C(void* p) {
    int lang = (s8)fn_8024BC94()[0x1BC8];
    if (fn_8023F880(lbl_80392DC8[lang][fn_801D09F0()]) != 0) {
        fn_80083B78(p);
    }
}

class SndObj {
public:
    virtual void v08(); virtual void v0C();
    virtual int isPlaying();
    virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void stop(int a);
};
SndObj* fn_8024F3FC(int a);

void fn_80288DE8(u8* p) {
    if (*(void**)(p + 0x84) != 0) {
        fn_800761F0(*(void**)(p + 0x84));
        *(void**)(p + 0x84) = 0;
    }
    if (*(void**)(p + 0x88) != 0) {
        fn_800761F0(*(void**)(p + 0x88));
        *(void**)(p + 0x88) = 0;
    }
    fn_8001D424(*(void**)(p + 0x54));
    SndObj* o = fn_8024F3FC(0);
    if (o != 0 && o->isPlaying() != 0) {
        o->stop(1000);
    }
}

void fn_8028A3F8(u8* p) {
    if (*(s16*)(p + 0x68) > 0) {
        *(s16*)(p + 0x68) = (f32)*(s16*)(p + 0x68) - 16.666666f;
    } else {
        fn_80083B78(p);
    }
}

void fn_8028A45C(u8* p) {
    if (*(s16*)(p + 0x60) > 0) {
        *(s16*)(p + 0x60) = (f32)*(s16*)(p + 0x60) - 16.666666f;
    } else {
        fn_80083B78(p);
    }
}

void fn_800A8660(void);
void fn_800BEC84(void* p);
#if TARGET_PC
FE10_PROTO void* fn_800A75E8(p32arg, int b);
#else
void* fn_800A75E8(int a, int b);
#endif
void fn_800B1120(void* p);
#if TARGET_PC
FE10_PROTO void fn_800B1628(void* p, p32arg);
#else
void fn_800B1628(void* p, int a);
#endif
#if TARGET_PC
FE10_PROTO void fn_800B5344(void* p, p32arg);
FE10_PROTO void fn_800B4574(void* p, p32arg, int b);
#else
void fn_800B5344(void* p, int a);
void fn_800B4574(void* p, int a, int b);
#endif
void fn_800B54DC(void* p, int a);
void fn_800B26B0(void* p, const char* s, int a, u16 b);
extern char lbl_80373720[];

void fn_8027D948(u8* p) {
    void* u = *(void**)(p + 0x78);
    fn_800A8660();
    fn_800BEC84(p);
    if (u == 0) {
        u = fn_800A75E8(*(int*)(p + 0x9C), 0);
    }
    if (u == 0) {
        fn_80081A90(p);
        return;
    }
    *(void**)(p + 0x78) = u;
    p[0x57] = 0;
    fn_800B1120(p);
    fn_800B1628(p, *(int*)(p + 0x9C));
    fn_800B5344(p, *(int*)(p + 0x9C));
    fn_800B4574(p, *(int*)(p + 0xA0), 0);
    fn_800B54DC(p, -1);
    int v = 0xFFFF;
    fn_800B26B0(p, lbl_80373720, -1, v);
}

void fn_8027F728(u8* p) {
    p[0x47]++;
    if ((lbl_804CB5B8->v34() & 0x4000) && p[0x31] != 0) {
        fn_80083DC4(p, 0);
    }
    if (p[0x30] == 1) {
        s16 v = *(s16*)(p + 0x44);
        *(s16*)(p + 0x44) = v - 1;
        if (v <= 0) {
            fn_80083B78(p);
        }
    } else if (*(s16*)(p + 0x3E) < 0x18 - *(u16*)(p + 0x48) * 0x4C) {
        p[0x30] = 1;
    }
}


extern u8 lbl_80392E00[];
struct Fade8A {
    u8 pad[0x32];
    s16 m32;
    f32 m34;
    u8 pad38;
    u8 m39;
    u8 pad3A[0x54 - 0x3A];
    int m54;
    s16 m58;
    u8 m5A;
    f32 m5C;
    u8 pad60[0x6A - 0x60];
    u8 m6A;
    u8 pad6B[0x78 - 0x6B];
    f32 m78;
    s16 m7C, m7E, m80, m82;
    int m84, m88;
};
void fn_8028A4C0(void* parent) {
    Fade8A* f = (Fade8A*)fn_80081194(lbl_80392E00, parent);
    if (f != 0) {
        f->m32 = 0;
        f->m34 = 0.0f;
        f->m39 = 0;
        f->m54 = 0;
        f->m58 = 0;
        f->m5A = 0;
        f->m5C = 448.0f;
        f->m6A = 0;
        f->m78 = 0.0f;
        f->m7C = 0;
        f->m7E = 0;
        f->m80 = 0xFF;
        f->m82 = 0;
        f->m84 = 0;
        f->m88 = 0;
    }
}

extern u8 lbl_80430920[];
extern u8 lbl_80430D00[];
extern u8 lbl_80430D2C[];
extern u8 lbl_80430CE0[];
extern char lbl_803932EC[], lbl_803932FC[];
extern void* lbl_804CC0F0;
int fn_80348D78(void);
void fn_8008A068(int a);
void fn_8024E3AC(f32 v);
#if TARGET_PC
FE10_PROTO void fn_80256BF8(ptr32<const void>);
FE10_PROTO void fn_80256D70(ptr32<const void>);
#else
void fn_80256BF8(void* p);
void fn_80256D70(void* p);
#endif
void* fn_8029C7D8(void);
void fn_8029D3E8(void* a, int b, int c);
void fn_8030D66C(int i);
void fn_8030D688(int i);
void fn_800893AC(void* proc);
void fn_8008939C(void* proc);

void fn_8028A7C8(void) {
    switch (fn_80348D78()) {
    case 1:
        fn_8008A068(0xFE);
        break;
    case 2:
        fn_8008A068(0);
        break;
    default: {
        int i;
        fn_8024E3AC(250.0f);
        fn_80256BF8(lbl_80430D00);
        fn_80256D70(lbl_80430D2C);
        fn_8029D3E8(fn_8029C7D8(), 2, 0);
        for (i = 0; i < 4; i++) {
            fn_8030D66C(i);
        }
        break;
    }
    }
    {
        int proc = fn_80085708(lbl_803932FC);
        if (proc != 0) {
            fn_800893AC((void*)proc);
        }
    }
    lbl_804CB700 &= ~0x100000;
}

void fn_8024DEF0(f32 v);
void fn_80256EE8(void* p);
void fn_8025704C(f32 v);
void fn_80256FA4(void* p);
void fn_802570D0(f32 v);
u32 fn_8030585C(int w, int h, int a, int b, int c);
void* fn_80079958(u32 size, int align);
void DCInvalidateRange(void* p, u32 n);
void fn_80305A40(void* o, void* p, int w, int h, int a, int b, int c, int d);
void fn_80305C94(void* o, int a, int b, int c, int d, int e, f32 x, f32 y, f32 z);

extern u8 lbl_80392ED8[];
extern u8 lbl_80392F30[];
class PadV {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20();
    virtual u32 v24();
    virtual void v28();
    virtual u32 v2C();
};
PadV* fn_8007B594(int i);

static inline BOOL procFound(void* c) { return fn_80083B84(c) != 0; }

PadV* fn_8028BACC(void) {
    PadV* found;
    int i;
    PadV* p;
    if (fn_80083B84(lbl_80392F30) != 0) {
        return 0;
    }
    found = 0;
    if (!procFound(lbl_80392ED8)) {
        for (i = 0; i < 4; i++) {
            p = fn_8007B594(i);
            if ((p->v2C() & 0x10000) && (p->v24() & 0x10000)
                && (p->v2C() & ~0x30000) == 0 && (p->v24() & ~0x30000) == 0) {
                found = p;
                break;
            }
        }
    }
    return found;
}

void fn_80283A58(void) {
    if (procFound(lbl_80392C18)) {
        *(s16*)(lbl_80430920 + 0x14) = 0x12C;
        *(s16*)lbl_80430920 = 0;
        fn_80083DC4(fn_80083B84(lbl_80392C18), 0xE7);
    }
}

void fn_80280A00(void) {
    lbl_804CC0A8->m4 = fn_8017F68C(556.0f, 556.0f, lbl_804CC0A8->m12, 8.0f, 4);
    lbl_804CC0A8->m6 = fn_8017F68C(63.0f, 63.0f, lbl_804CC0A8->m12, 8.0f, 4);
    lbl_804CC0A8->m18 = fn_8017F68C(0.0f, 255.0f, lbl_804CC0A8->m12, 8.0f, 0);
    if (lbl_804CC0A8->m12 < 8) {
        lbl_804CC0A8->m12++;
    } else {
        fn_80083B78(lbl_804CC0AC);
    }
}

void fn_80280B24(void) {
    lbl_804CC0A8->m4 = fn_8017F68C(556.0f, 556.0f, lbl_804CC0A8->m12, 8.0f, 4);
    lbl_804CC0A8->m6 = fn_8017F68C(63.0f, 63.0f, lbl_804CC0A8->m12, 8.0f, 4);
    lbl_804CC0A8->m18 = fn_8017F68C(0.0f, 255.0f, lbl_804CC0A8->m12, 8.0f, 0);
    if (lbl_804CC0A8->m12 > 0) {
        lbl_804CC0A8->m12--;
    } else {
        fn_80083B78(lbl_804CC0AC);
    }
}

}
