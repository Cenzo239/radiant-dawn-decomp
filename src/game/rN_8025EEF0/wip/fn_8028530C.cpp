/* NEAR MISS: 41 words, registers only, same size. n should be r27 with tex r26 in the first three draws (tex r28 later); later branches want x r21, alpha r24, v r21, m r24, a r23. No declaration order reaches it. */
/* Unit record page draw (WRR_* strings) */
#pragma inline_max_size(4000)
#pragma inline_max_total_size(30000)
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

extern u8 lbl_804CAB57;
extern char lbl_80373C40[];
extern char lbl_80392D1C[];
extern char lbl_80392D28[];
extern char lbl_80392D34[];
extern char lbl_80392D40[];
extern char lbl_804CAB58[8];
extern char lbl_804CAB60[8];
extern char lbl_804CAB68[4];
extern char lbl_804CAB6C[4];
extern char lbl_804CAB70[8];
void fn_800804D4(int r, int g, int b, int a);
void fn_80080330(f32 x, f32 y);
void fn_80080508(C4* c);
void fn_80080A94(f32 s);
void fn_80080B00(f32 s, int a, C4* c);
void fn_80080C24(const char* s);
void fn_8007E74C(void* f, void* a);
void fn_8007E7B4(void);
void fn_8027DE00(void* u, void* o);
void fn_8027DF28(int a);
void fn_8027DEE8(int a);
void fn_8027DE78(int x, int y, int w, int h);
void fn_802869E0(void*);
void fn_800C4DDC(int x, int y, int a, void* p);
void* fn_800E3C04(const char* s, void* p);
void fn_800E48AC(f32 x, f32 y, f32 z, void* p);
const char* fn_80118C44(void* p);
const char* fn_80118F48(void* p);
const char* fn_80118F00(void* p);
C4* fn_800CD204(int i);
int fn_800CA3DC(const char* s, int a, f32 v);
void* fn_8010B094(int a);
const char* fn_80092904(void* p);
const char* fn_8009285C(void* p);

struct Rec {
    u8 pad[0x30];
    u8 m30; u8 pad31; u16 m32;
    u8 pad34[4];
    void* tex;
    u8 pad3C[8];
    int m44;
    u8 pad48[0xE];
    s16 m56, m58, m5A, m5C, m5E, m60, m62;
    u8 pad64[8];
    u8** m6C;
    u8 pad70[8];
    u8 m78, m79;
    u8 pad7A[2];
    void* m7C[8];
};

static inline void img(void* tex, int i, u8 a, f32 x, f32 y, f32 w, f32 h, int f) {
    fn_8007E154();
    fn_8007E374(tex, i, 0x11);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800800D4(1);
    fn_800804D4(0xFF, 0xFF, 0xFF, a);
    fn_80080430(x, y, 0.0f, 0.0f, w, h);
    fn_80080578(f);
    fn_80080308();
}
static inline void hdr(u8 a, int m, f32 x, f32 y) {
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E7DC(a);
    fn_8007E164();
    fn_800800D4(m);
    fn_80080330(x, y);
}
static inline void tail(int n, const char* b) {
    fn_80080A94(1.0f);
    fn_80080B00(1.0f, 1, fn_800CD204(n));
    fn_80080C24(b);
    fn_80080308();
}
static inline void setc(C4 c) { fn_80080508(&c); }
static inline void txtm(int m, u8 a, f32 x, f32 y, u8 r, u8 g, u8 b, int n, const char* s) {
    hdr(a, m, x, y);
    { C4 d; C4 c; c.a = lbl_804CAB57; c.r = r; c.g = g; c.b = b; *(u32*)&d = *(u32*)&c; fn_80080508(&d); }
    tail(n, s);
}
static inline void txt(u8 a, f32 x, f32 y, u8 r, u8 g, u8 b, int n, const char* s) {
    txtm(5, a, x, y, r, g, b, n, s);
}
static inline void txt9(u8 a, f32 x, f32 y, u8 r, u8 g, u8 b, int n, const char* s) {
    txtm(9, a, x, y, r, g, b, n, s);
}
static inline void txt2m(u8 a, f32 x, f32 y, int cn, int n, const char* s) {
    hdr(a, 5, x, y);
    { C4 c = *fn_800CD204(cn); fn_80080508(&c); }
    tail(n, s);
}
static inline void txt2(u8 a, f32 x, f32 y, int cn, int n, const char* s) { txt2m(a, x, y, cn, n, s); }
static inline void pos(f32 y, f32 z) {
    fn_8007E154();
    fn_8007E4E4(0.0f, y, z, 1.0f);
    fn_8007E164();
}
static inline void clip(int y, Rec* o) {
    int r = fn_801D09F0();
    int x = 0x133;
    int w;
    if (r != 0) x = 0x148;
    r = fn_801D09F0();
    w = 0xC3;
    if (r != 0) w = 0x94;
    fn_8027DE78(x, y, w, 0x10B);
}

static inline u16 cnt(Rec* o) { return o->m78 - o->m79; }

void fn_8028530C(Rec* o) {
    char buf[0x50];
/*P*/
    u16 n;
    const char* S;
    s8 lang;
    s16 sy;
    u8* u;
    u16 w;
/*E*/
    sy = o->m44;
    u = *(u8**)((u8*)o->m6C + o->m79 * 8);
    n = cnt(o);
    lang = fn_8024BC94()[0x1BC8];
    pos(sy, 695.0f);
    img(o->tex, 5, o->m56, 47.0f, 31.0f, 514.0f, 386.0f, 0);
    pos(sy, 300.0f);
    img(o->tex, 0xC, o->m56, 315.0f, 112.0f, 180.0f, 8.0f, 1);
    img(o->tex, 0xD, o->m56, 315.0f, 371.0f, 180.0f, 8.0f, 1);
    {
        s16 a; s16 b;
        if (fn_801D09F0() != 0) { a = 0x15; b = 0x18; } else { a = 0; b = 0; }
        img(o->tex, 0xE, o->m56, (s16)(a + 0x133), 112.0f, 8.0f, 267.0f, 0);
        img(o->tex, 0xF, o->m56, (s16)(0x1EE - b), 112.0f, 8.0f, 267.0f, 0);
    }
    if (o->m32 == 0 && o->m30 == 3) {
        fn_8027DE00(u, o);
        fn_8027DF28(0);
        fn_8027DEE8(600);
        clip(0x70, o);
    } else if (o->m32 >= 0xAA) {
        fn_8027DF28((u8)o->m62);
        clip(sy + 0x70, o);
    }
    fn_8007E154();
    fn_8007E4E4(93.0f, sy + 0x74, 694.0f, 1.0f);
    fn_8007E74C(fn_802869E0, 0);
    fn_8007E164();
    fn_800C4DDC(0x5D, 0x74, o->m62, o->m7C[n - 1]);
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    {
        int i;
        switch (n) {
        case 1: i = 7; break;
        case 2: i = 8; break;
        case 3: i = 9; break;
        case 4: i = 10; break;
        case 5: i = 0xB; break;
        }
        pos(sy, 299.0f);
        img(o->tex, i, o->m62, 140.0f, 41.0f, 100.0f, 56.0f, 1);
    }
    if (o->m32 == 100 && o->m30 == 3) {
        void* e;
        S = lbl_80373C40;
        fn_80290DDC(buf, S + 0x30, n);
        e = fn_800E3C04(buf, o);
        {
            int r = fn_801D09F0();
            int x = 0x130;
            if (r != 0) x = 0x114;
            fn_800E48AC(x, 224.0f, 0.0f, e);
        }
        *(s16*)(*(u8**)((u8*)e + 0x30) + 8) = 0x121;
    }
    img(o->tex, 6, o->m56, 58.0f, 224.0f, 265.0f, 62.0f, 0);
    pos(sy, 298.0f);
    {
        const char* m = fn_80118C44(*(void**)(u + 0xEC));
        S = lbl_80373C40;
        fn_80290DDC(buf, S + 0x19, m);
    }
    {
        w = fn_800CA3DC(buf, -1, 1.0f);
        txt(o->m62, (s16)(0xC1 - ((u32)w >> 1)), 233.0f, 0x2B, 0x1B, 6, 0x2A, buf);
    }
    fn_80290DDC(buf, S + 0x19, fn_800D0864(S + 0x3D));
    txt(o->m58, 112.0f, 290.0f, 0x6F, 0xA7, 0x50, 2, buf);
    fn_80290DDC(buf, S + 0x19, fn_800D0864(S + 0x4C));
    txt(o->m5A, 112.0f, 318.0f, 0x6F, 0xA7, 0x50, 2, buf);
    fn_80290DDC(buf, S + 0x19, fn_800D0864(S + 0x5C));
    txt(o->m5C, 112.0f, 346.0f, 0x6F, 0xA7, 0x50, 2, buf);
    if (lang == 0) {
        fn_80290DDC(buf, S + 0x1C, u[0x38F]);
        w = fn_800CA3DC(buf, -1, 1.0f);
        txt(o->m58, (s16)(0xF8 - w), 290.0f, 0xFC, 0xED, 200, 2, buf);
        fn_80290DDC(buf, S + 0x19, fn_800D0864(S + 0x69));
        txt(o->m58, 256.0f, 290.0f, 0xC4, 0xA2, 0x58, 2, buf);
        fn_80290DDC(buf, S + 0x1C, *(u16*)(u + 0x382));
        w = fn_800CA3DC(buf, -1, 1.0f);
        txt(o->m5A, (s16)(0xF8 - w), 318.0f, 0xFC, 0xED, 200, 2, buf);
        fn_80290DDC(buf, S + 0x19, fn_800D0864(S + 0x73));
        txt(o->m5A, 256.0f, 318.0f, 0xC4, 0xA2, 0x58, 2, buf);
        fn_80290DDC(buf, S + 0x1C, *(u16*)(u + 900));
        w = fn_800CA3DC(buf, -1, 1.0f);
        txt(o->m5C, (s16)(0xF8 - w), 346.0f, 0xFC, 0xED, 200, 2, buf);
        fn_80290DDC(buf, S + 0x19, fn_800D0864(S + 0x1F));
        txt(o->m5C, 256.0f, 346.0f, 0xC4, 0xA2, 0x58, 2, buf);
    } else {
        fn_80290DDC(buf, S + 0x7E, fn_800D0864(S + 0x69), u[0x38F]);
        w = fn_800CA3DC(buf, -1, 1.0f);
        txt2(o->m58, (s16)(0x114 - w), 290.0f, 0, 2, buf);
        fn_80290DDC(buf, S + 0x7E, fn_800D0864(S + 0x73), *(u16*)(u + 0x382));
        w = fn_800CA3DC(buf, -1, 1.0f);
        txt2(o->m5A, (s16)(0x114 - w), 318.0f, 0, 2, buf);
        fn_80290DDC(buf, S + 0x7E, fn_800D0864(S + 0x1F), *(u16*)(u + 900));
        w = fn_800CA3DC(buf, -1, 1.0f);
        txt2(o->m5C, (s16)(0x114 - w), 346.0f, 0, 2, buf);
    }
    if ((*(u8**)(u + 0xF4))[8] != 6) {
        int x;
        if (lang == 0) {
            fn_80290DDC(buf, lbl_80373C40 + 0x19, fn_80118F48(*(void**)(u + 0xF0)));
            txt9(o->m5E, 318.0f, 52.0f, 0x2B, 0x1B, 6, 0x2A, buf);
        }
        fn_80290DDC(buf, lbl_80373C40 + 0x19, fn_80118F00(*(void**)(u + 0xF0)));
        if ((s8)fn_8024BC94()[0x1BC8] != 0 && fn_801D09F0() == 0) {
            x = 0x13C;
        } else {
            x = 0x13E;
        }
        txt(o->m5E, x, 76.0f, 0x2B, 0x1B, 6, 0x2A, buf);
        fn_80290DDC(buf, lbl_80373C40 + 0x9C);
        if ((s8)fn_8024BC94()[0x1BC8] != 0 && fn_801D09F0() == 0) {
            x = 0x1C5;
        } else {
            x = 0x1CA;
        }
        txt(o->m60, x, 76.0f, 0xF9, 0xD4, 0x79, 2, buf);
        fn_80290DDC(buf, lbl_80373C40 + 0x1C, *(s8*)(u + 0xFE));
        w = fn_800CA3DC(buf, -1, 1.0f);
        txt(o->m60, (s16)(0x1F0 - w), 76.0f, 0xFC, 0xED, 200, 2, buf);
    } else {
        if (lang == 0) {
            void* v = fn_8010B094(u[0x38E]);
            if (*(u32*)(u + 0x10C) & 0x20) {
                const char* m = fn_800D0864(lbl_80392D28);
                const char* a = fn_80092904(v);
                fn_80290DDC(buf, lbl_804CAB60, fn_8009285C(v), a, m);
            } else {
                const char* m = fn_800D0864(lbl_80392D1C);
                const char* a = fn_80092904(v);
                fn_80290DDC(buf, lbl_804CAB58, fn_8009285C(v), a, m);
            }
            txt2(o->m5E, 318.0f, 76.0f, 2, 0x2A, buf);
        } else {
            if (*(u32*)(u + 0x10C) & 0x20) {
                fn_80290DDC(buf, lbl_804CAB6C, fn_800D0864(lbl_80392D40));
            } else {
                fn_80290DDC(buf, lbl_804CAB68, fn_800D0864(lbl_80392D34));
            }
            txt2(o->m5E, 318.0f, 52.0f, 2, 0x2A, buf);
            {
                void* v = fn_8010B094(u[0x38E]);
                const char* a = fn_80092904(v);
                fn_80290DDC(buf, lbl_804CAB70, fn_8009285C(v), a);
            }
            txt2(o->m5E, 318.0f, 76.0f, 2, 0x2A, buf);
        }
    }
}

}
