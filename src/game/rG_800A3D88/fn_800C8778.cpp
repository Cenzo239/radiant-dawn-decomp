#include "game/rG_800A3D88/types.h"

// Screen fade / colour fade / filter processes and their globals (lbl_804CB6D0..DC).

#pragma auto_inline off

extern "C" {

extern const f32 lbl_804CD59C;
extern const f32 lbl_804CD5A0;
extern const f32 lbl_804CD5A4;
extern const f32 lbl_804CD5A8;
extern const f32 lbl_804CD5C8;
extern const f32 lbl_804CD600;
extern u8 lbl_80382930[];
extern u8 lbl_803829C8[];
extern u8 lbl_803829D8[];
extern u32 lbl_804CB700;

struct FadeG {
    u8 pad[0x30];
    u8 m30;
    u8 m31;
    u16 m32;
    u8 m34, m35, m36, m37;
    s16 m38, m3a, m3c, m3e;
    u8 pad40[8];
    void* m48;
};

struct FadeS {
    u8 pad[0x32];
    u16 m32;
    s16 m34;
    s16 m36;
};

extern FadeG* lbl_804CB6D0;
extern FadeG* lbl_804CB6D4;
extern FadeG* lbl_804CB6D8;
extern FadeS* lbl_804CB6DC;

void fn_800C8000(FadeG*, int, int);
void fn_803047B0(int, int, int, int);
void fn_80304814(int, int, int, int);
void fn_80305020(void*, int);
void fn_80303D74();
void fn_803061BC();
#if TARGET_PC
FE10_PROTO void* fn_80081050(void*, p32arg);
#else
void* fn_80081050(void*, int);
#endif
void fn_800846BC(void*);
void* fn_80083B84(void*);
void fn_8007E154();
void fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_8007E4E4(f32, f32, f32, f32);
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_80080308();
void fn_80083E20(void (*)(void*));
int fn_800893BC(void*);
void fn_800893C4(void*);
void fn_800893D4(void*);
void fn_80079978(void*);
f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_80021F7C(int, int, int, int);
void fn_80021EF8(int, int);
void fn_80021CB4(int, int, int, int);
void fn_80021E20(int, int, int, int, int);
void fn_80021D18(int, int, int, int, int, int);
void fn_80021E8C(int, int, int, int, int);
void fn_80021D9C(int, int, int, int, int, int);
void fn_80077C08(int);

void fn_800C835C(int a, int b) {
    if (lbl_804CB700 & 0x8001) {
        switch (a) {
        case 2:
            a = 0;
            break;
        case 3:
            a = 1;
            break;
        case 5:
            a = 0;
            break;
        case 6:
            a = 4;
            break;
        case 7:
        case 8:
        case 9:
            a = 0;
            break;
        }
        b = 0;
    }
    fn_800C8000(lbl_804CB6D4, a, b);
}

BOOL fn_800C8778() {
    FadeG* f = lbl_804CB6D8;
    if (f->m32 == 1 || f->m32 == 2) {
        return 1;
    }
    return 0;
}

void fn_800C8C3C(int t) {
    FadeS* s = lbl_804CB6DC;
    s->m32 = 1;
    s->m34 = 0;
    s->m36 = t / lbl_804CD5C8;
}

void fn_800C8C90(int t) {
    FadeS* s = lbl_804CB6DC;
    s->m32 = 3;
    s->m34 = 0;
    s->m36 = t / lbl_804CD5C8;
}

void fn_800C8CE4() {
    lbl_804CB6DC->m32 = 0;
}

BOOL fn_800C8CF4() {
    FadeS* f = lbl_804CB6DC;
    if (f->m32 == 1 || f->m32 == 3) {
        return 1;
    }
    return 0;
}

struct Holder54 {
    u8 pad[0x54];
    FadeG* m54;
};

void fn_800C8D1C(Holder54* h) {
    FadeG* g = h->m54;
    fn_803047B0(0, 0, 0x260, 0x1C0);
    fn_80304814(0x260, 0x1C0, 4, 0);
    fn_80305020(g->m48, 0);
    fn_80303D74();
    fn_803061BC();
}

void fn_800C900C(int a, int b) {
    fn_800C8000(lbl_804CB6D0, a, b);
}

u32 fn_800C9020() {
    return lbl_804CB6D0->m32 & 1;
}

BOOL fn_800C9030() {
    BOOL r = 0;
    u16 v = lbl_804CB6D0->m32;
    if ((v & 2) && (v & 4)) {
        r = 1;
    }
    return r;
}

BOOL fn_800C9054() {
    BOOL r = 0;
    u16 v = lbl_804CB6D0->m32;
    if ((v & 2) && (v & 8)) {
        r = 1;
    }
    return r;
}

u16 fn_800C9078() {
    return lbl_804CB6D0->m32;
}

void fn_800C9108() {
    fn_8007E154();
    fn_8007E4E4(lbl_804CD5A0, lbl_804CD5A0, lbl_804CD5A0, lbl_804CD59C);
    fn_8007E174(0, 0x800);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(lbl_804CD5A0, lbl_804CD5A0, lbl_804CD5A8, lbl_804CD5A4);
    fn_80080308();
}

BOOL fn_800C916C() {
    fn_80081050(lbl_803829C8, 4);
    return 1;
}

BOOL fn_800C919C() {
    fn_800846BC(lbl_803829C8);
    return 1;
}

struct BlurP {
    u8 pad[0x28];
    s16 m28;
    u8 pad2a[6];
    u8 m30;
    u8 pad31[3];
    s16 m34;
    u8 pad36[2];
    f32 m38, m3c;
    u8 pad40[8];
    void* m48;
};

void fn_800C9244(void* p) {
    if (fn_800893BC(p) != 0) {
        fn_800893D4(p);
    }
}

void fn_800C9280(BlurP* p) {
    fn_80083E20(fn_800C9244);
    if (p->m48 != NULL) {
        fn_80079978(p->m48);
        p->m48 = NULL;
    }
}

void fn_800C96A8(BlurP* p) {
    p->m34 = fn_8017F68C(0, p->m38, p->m3c, 6 - p->m28, lbl_804CD600);
}

void fn_800C9718() {
    if (fn_80083B84(lbl_803829D8) != NULL) {
        BlurP* p = (BlurP*)fn_80083B84(lbl_803829D8);
        p->m30 = 0x7B;
    } else {
        fn_80081050(lbl_803829D8, 5);
    }
}

void fn_800C9770() {
    fn_80021F7C(0, 1, 4, 0x21);
    fn_80021EF8(0, 0);
    fn_80021CB4(0, 0, 1, 4);
}

void fn_800C97C0() {
    fn_80021F7C(0, 1, 4, 0x1E);
    fn_80021E20(0, 0xF, 0xF, 0xF, 0xA);
    fn_80021D18(0, 0, 0, 0, 1, 0);
    fn_80021E8C(0, 7, 4, 5, 7);
    fn_80021D9C(0, 0, 0, 0, 1, 0);
    fn_80021CB4(0, 0, 0, 4);
}

int fn_800C9D58() {
    return 0;
}

int fn_800C9D60() {
    return 0;
}

void fn_800C9EB8() {
    fn_80077C08(0);
}

} // extern "C"
