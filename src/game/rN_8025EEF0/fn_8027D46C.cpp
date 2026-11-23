/* Conversation room, and assorted small procs in the back half of the region. */
#include "game/rN_8025EEF0/calls.h"

#pragma use_lmw_stmw on

extern "C" {

extern char lbl_8037359C[];
extern u8* lbl_804CC06C;
extern u8* lbl_804CC074;
extern u8* lbl_804CC068;
extern u8 lbl_80392840[];

class V14 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void v14(int del);
};
struct Rooms { u8 pad[0x28]; V14* obj; };

static inline BOOL isProc(const char* s) { return fn_80085708(s) != 0; }

static inline u8* roomData(void) {
    if (isProc(lbl_8037359C)) {
        return lbl_804CC06C + 0x108;
    }
    if (isProc(lbl_8037359C + 0x13)) {
        return lbl_804CC074 + 0xC;
    }
    return 0;
}

struct Pad28 { u8 pad[0x28]; };
class DtorObj : public Pad28 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void dtor(int del);
};

void fn_8027D46C(void) {
    DtorObj* o = *(DtorObj**)(roomData() + 0x58);
    if (o != 0) {
        o->dtor(1);
    }
    if (*(void**)(lbl_804CC06C + 4) != 0) {
        fn_800761F0(*(void**)(lbl_804CC06C + 4));
        *(void**)(lbl_804CC06C + 4) = 0;
    }
    fn_80006A2C(lbl_804CC06C + 0x164);
    fn_80078E24(*(void**)(lbl_804CC068 + 0x30));
    *(void**)(lbl_804CC068 + 0x30) = 0;
}

void fn_8027D60C(void* parent) {
    lbl_804CC068 = (u8*)fn_80081194(lbl_80392840, parent);
    *(void**)(lbl_804CC068 + 0x30) = fn_80078CCC(0x1F0, lbl_8037359C + 0x16B, 0);
    lbl_804CC06C = *(u8**)(lbl_804CC068 + 0x30);
}

BOOL fn_8027D6C4(void) { return fn_80085708(lbl_8037359C) != 0; }

int fn_8027D6F8(u8* p) { return *(int*)(p + 0xC); }
int fn_8027D700(u8* p) { return *(int*)(p + 0x20); }
int fn_8027D708(u8* p) { return *(int*)(p + 0x28); }
int fn_8027D710(u8* p) { return *(int*)(p + 0xC); }
int fn_8027D718(u8* p) { return *(int*)(p + 8); }
int fn_8027D720(u8* p) { return *(int*)(p + 0x14); }
int fn_8027D728(u8* p) { return *(int*)(p + 0x24); }
int fn_8027D730(u8* p) { return *(int*)(p + 0x10); }
int fn_8027D738(u8* p) { return *(int*)(p + 0x1C); }
int fn_8027D740(u8* p) { return *(int*)(p + 0x18); }

f64 fn_80295CF0(f64 v);
f64 fn_8027D748(int v) { return fn_80295CF0(v); }

extern char lbl_804CAB10[8];
void* fn_8027D784(int size) { return fn_80078CCC(size, lbl_804CAB10, 0); }

void fn_80179660(void* p);
extern u8 lbl_80392578[];
void* fn_8027D790(u8* p) {
    fn_80179660(p);
    *(void**)(p + 0x28) = lbl_80392578;
    return p;
}

void fn_800BED98(void* p);
void fn_800A8B70(void);
void fn_8027DDD8(void* p) {
    fn_800BED98(p);
    fn_800A8B70();
}

extern u8 lbl_80392958[];
struct FadeBar {
    u8 pad[0x78];
    int m78;
    u8 pad7C[0x9C - 0x7C];
    int m9C;
    int mA0;
    s16 mA4, mA6, mA8, mAA, mAC;
    u8 mAE, mAF;
};

void fn_8027DE00(int a, void* parent) {
    FadeBar* f = (FadeBar*)fn_80081050(lbl_80392958, parent);
    f->m9C = a;
    f->m78 = 0;
    f->mA4 = 0x140;
    f->mA6 = 0x50;
    f->mA8 = 0xC3;
    f->mAA = 0x10B;
    f->mAC = 0x1F4;
    f->mAE = 0xFF;
    f->mAF = 0;
    f->mA0 = 0;
}

void fn_8027DEE8(int v) {
    FadeBar* f = (FadeBar*)fn_80083B84(lbl_80392958);
    if (f != 0) {
        f->mAC = v;
    }
}

void fn_8027DF28(int v) {
    FadeBar* f = (FadeBar*)fn_80083B84(lbl_80392958);
    if (f != 0) {
        f->mAE = v;
    }
}

void fn_8027DF68(void) { fn_800846BC(lbl_80392958); }

void fn_8027DF74(u8* p, f32 a, f32 b, f32 c) {
    *(f32*)(p + 0x4C) = a;
    *(f32*)(p + 0x50) = b;
    *(f32*)(p + 0x54) = c;
}

void fn_8027E80C(void) {}

void fn_8027E834(void) { fn_803080DC(0, 0x18, 0x260, 0x190); }
void fn_8027E848(void) { fn_803080DC(0, 0x18, 0x260, 0x190); }
void fn_8027E85C(void) { fn_803080DC(0, 0, 0x260, 0x68); }
void fn_8027E870(void) { fn_803080DC(0, 0x190, 0x260, 0x30); }

extern const char* lbl_803929B0[][2];
void fn_8027F2A8(void) {
    int lang = (s8)fn_8024BC94()[0x1BC8];
    fn_8023F1A0(lbl_803929B0[lang][fn_801D09F0()], 0);
}
void fn_8027F2FC(void* p) {
    int lang = (s8)fn_8024BC94()[0x1BC8];
    if (fn_8023F880(lbl_803929B0[lang][fn_801D09F0()]) != 0) {
        fn_80083B78(p);
    }
}

extern u8* lbl_804CC0A8;
extern u8* lbl_804CC0AC;
extern u8 lbl_80392A68[];
extern u8 lbl_803CAB38[];
extern char lbl_803738BC[];

void fn_80280C48(void) {
    *(s16*)(lbl_804CC0A8 + 4) = 0x22C;
    *(s16*)(lbl_804CC0A8 + 6) = 0x3F;
    *(s16*)(lbl_804CC0A8 + 0x18) = 0xFF;
    *(s16*)(lbl_804CC0A8 + 0x12) = 8;
    fn_80083B78(lbl_804CC0AC);
}

void fn_80280C80(void) {
    *(s16*)(lbl_804CC0A8 + 4) = 0x22C;
    *(s16*)(lbl_804CC0A8 + 6) = 0x3F;
    *(s16*)(lbl_804CC0A8 + 0x18) = 0;
    *(s16*)(lbl_804CC0A8 + 0x12) = 0;
    fn_80083B78(lbl_804CC0AC);
}

void fn_80280DA8(void) {
    u8* p = lbl_804CC0A8 + 0x20;
    if (*(int*)p != 0) {
        fn_80006A2C(p);
    }
    fn_80078E24(*(void**)(lbl_804CC0AC + 0x30));
    *(void**)(lbl_804CC0AC + 0x30) = 0;
    lbl_804CC0AC = 0;
    lbl_804CC0A8 = 0;
}

void fn_80280E5C(void) { fn_800846BC(lbl_80392A68); }


void fn_80280E68(void) {
    if (fn_80083B84(lbl_80392A68) != 0) {
        fn_80083DC4(lbl_804CC0AC, 2);
    }
}
void fn_80280EA4(void) {
    if (fn_80083B84(lbl_80392A68) != 0) {
        fn_80083DC4(lbl_804CC0AC, 3);
    }
}
void fn_80280EE0(void) {
    if (fn_80083B84(lbl_80392A68) != 0) {
        fn_80083DC4(lbl_804CC0AC, 5);
    }
}

void fn_8028270C(void) { fn_803080DC(0x38, 0x6A, 0x1F0, 0x11B); }

extern u8 lbl_80392B18[];
struct Fx282 {
    u8 pad[0x3C];
    f32 a, b, c;
    s16 m48, m4A;
    u8 m4C, m4D, m4E;
    u8 pad4F[0x54 - 0x4F];
    int m54, m58, m5C;
};
void fn_80282848(void* parent) {
    Fx282* f = (Fx282*)fn_80081194(lbl_80392B18, parent);
    if (f != 0) {
        f->a = 0.0f;
        f->b = 0.0f;
        f->c = 0.0f;
        f->m48 = 0;
        f->m4A = 4;
        f->m4C = 0;
        f->m4D = 0;
        f->m4E = 0;
        f->m54 = 0;
        f->m58 = 0;
        f->m5C = 0;
    }
}

extern u8 lbl_80430920[];
void fn_8028366C(void) {
    *(s16*)(lbl_80430920 + 0x14) = 0x12C;
    *(s16*)lbl_80430920 = 0;
}

void fn_80282D00(void* p);
void fn_80282FF4(void* p);
void fn_80283688(void) {
    fn_80282D00(lbl_80430920);
    fn_80282FF4(lbl_80430920);
}

extern u8 lbl_80392C18[];
static inline BOOL procAlive(void) { return fn_80083B84(lbl_80392C18) != 0; }
void fn_80283AC0(void) {
    if (procAlive()) {
        fn_800846BC(lbl_80392C18);
    }
}

extern const char* lbl_80392C58[][2];
void fn_80283B08(void) {
    int lang = (s8)fn_8024BC94()[0x1BC8];
    fn_8023F1A0(lbl_80392C58[lang][fn_801D09F0()], 0);
}

void fn_802852E0(void) { fn_803080DC(0, 0x50, 0x260, 0x154); }
#if TARGET_PC
FE10_PROTO void fn_80020764(int a, int b, int c, int d, p32arg);
#else
void fn_80020764(int a, int b, int c, int d, int e);
#endif
void fn_802852F4(void) { fn_80020764(0, 0, 0x260, 0x1C0, 0); }

void fn_802869E0(void) {
    int x = fn_801D09F0() != 0 ? 0x84 : 0x74;
    fn_803080DC(x, 0x52, fn_801D09F0() != 0 ? 0x78 : 0x9E, 0x96);
}

void fn_80312318(void* p);
void fn_80307E48(void* p, int a);
void fn_80021784(int a);
void fn_80020AE0(int a, int b, int c, int d, f32 v);
void fn_80287138(void) {
    u8 m[0x38];
    fn_80312318(m);
    fn_80307E48(m, 0);
    fn_80021784(0);
    fn_80020AE0(0, 0, 0x260, 0x1C0, 950.0f);
}

extern u8 lbl_80392D50[];
extern const char* lbl_80392DC8[][2];
void fn_802889D8(void) {
    int lang = (s8)fn_8024BC94()[0x1BC8];
    fn_8023F1A0(lbl_80392DC8[lang][fn_801D09F0()], 0);
}

extern u8 lbl_80392F10[];
#if TARGET_PC
FE10_PROTO extern p32ret lbl_804CC0F0;
#else
extern int lbl_804CC0F0;
#endif
void fn_8028B120(void) {
    u8* p = (u8*)fn_80081050(lbl_80392F10, (void*)7);
    *(int*)(p + 0x54) = lbl_804CC0F0;
}

void fn_803047B0(int a, int b, int c, int d);
void fn_80304814(int a, int b, int c, int d);
void fn_80305020(void* a, int b);
void fn_80303D74(void);
void fn_803061BC(void);
void fn_8028B27C(u8* p) {
    fn_803047B0(0, 0, 0x260, 0x1C0);
    fn_80304814(0x260, 0x1C0, 4, 0);
    fn_80305020(*(void**)(p + 0x54), 0);
    fn_80303D74();
    fn_803061BC();
}

extern int lbl_804CAB78;
extern int lbl_804CC100;
extern u8 lbl_804CC104;
void fn_8028B6F4(void) {
    lbl_804CAB78 = 0;
    lbl_804CC100 = 0;
    lbl_804CC104 = 0;
}
void fn_8028B708(void) {
    lbl_804CAB78 = -1;
    lbl_804CC100 = 0;
    lbl_804CC104 = 0;
}

extern u8 lbl_80392F30[];
void fn_8028BC24(void) { fn_80081050(lbl_80392F30, (void*)7); }
void fn_8028BC34(void) { lbl_804CB700 |= 0x800000; }
void fn_8028BC44(void) { lbl_804CB700 &= ~0x800000; }


extern u8* lbl_804CC070;
void fn_800763E0(const char* s);
static inline u8* roomData2(void) {
    const char* s = lbl_8037359C;
    fn_800763E0(s + 0x13E);
    if (isProc(s)) {
        return lbl_804CC06C + 0x108;
    }
    if (isProc(s + 0x13)) {
        return lbl_804CC074 + 0xC;
    }
    return 0;
}

void fn_8027D548(void) {
    DtorObj* o = *(DtorObj**)(roomData2() + 0x58);
    if (o != 0) {
        o->dtor(1);
    }
    fn_80006A2C(lbl_804CC074 + 0x68);
    fn_80078E24(*(void**)(lbl_804CC070 + 0x30));
    *(void**)(lbl_804CC070 + 0x30) = 0;
}

extern u8 lbl_803928F8[];
void fn_8027D668(void* parent) {
    lbl_804CC070 = (u8*)fn_80081194(lbl_803928F8, parent);
    *(void**)(lbl_804CC070 + 0x30) = fn_80078CCC(0xF4, lbl_8037359C + 0x16B, 0);
    lbl_804CC074 = *(u8**)(lbl_804CC070 + 0x30);
}


void fn_80272ED0(void* p);
void fn_80068C58(void);
void fn_80044850(void);
void fn_800F3874(void);

/* conversation list: current slot's entry */
void fn_8027CC3C(void) {
    *(s16*)lbl_804CC06C |= 1;
    s16* t = (s16*)(roomData() + 0x24);
    int i = t[*(s16*)(roomData() + 0x30)];
    fn_80272ED0(*(void**)(lbl_804CC06C + i * 4 + 0x24));
}

void fn_8027CD44(void) {
    *(s16*)lbl_804CC06C &= ~1;
    s16* t = (s16*)(roomData() + 0x24);
    int i = t[*(s16*)(roomData() + 0x30)];
    if (*(int*)(*(u8**)(lbl_804CC06C + i * 4 + 0x24) + 8) == 0) {
        fn_80068C58();
    }
    fn_80044850();
    fn_800F3874();
}

void fn_8027DE78(int x, int y, int w, int h) {
    FadeBar* f = (FadeBar*)fn_80083B84(lbl_80392958);
    if (f != 0) {
        f->mA4 = x;
        f->mA6 = y;
        f->mA8 = w;
        f->mAA = h;
    }
}

void fn_8027E7AC(u8* p) {
    f32* f = (f32*)p;
    f[0x34 / 4] = 0.0f;
    f[0x38 / 4] = 10.0f;
    f[0x3C / 4] = 60.0f;
    f[0x40 / 4] = -3.0f;
    f[0x44 / 4] = 0.0f;
    f[0x48 / 4] = 0.0f;
    f[0x58 / 4] = 36.0f;
    f[0x5C / 4] = 1.3571428f;
    f[0x60 / 4] = 2.0f;
    f[0x64 / 4] = 2000.0f;
    p[0x30] = 1;
    f[0x4C / 4] = 0.0f;
    f[0x50 / 4] = 0.0f;
    f[0x54 / 4] = 0.0f;
}

}
