/* Script command helper: resets selected per-unit visual state (name guessed). */
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
#pragma use_lmw_stmw on

struct C4 { u8 r, g, b, a; };
struct KD { u8 pad[8]; u8 kind; };
struct U {
    u16 h0;
    u8 pad2[0x10 - 2];
    f32 sx, sy, sz;
    u8 pad1C[0xC6 - 0x1C];
    u8 bC6;
    u8 padC7[0xD8 - 0xC7];
    s8 bD8;
    u8 padD9;
    s16 hDA;
    u8 padDC[0xEC - 0xDC];
    void* ec;
    u8 padF0[4];
    KD* f4;
    u8 padF8[0x3F0 - 0xF8];
};
struct MM { u8 pad[0xC]; u8* c; u8 pad10[0x52 - 0x10]; s16 n52; };
struct O {
    u8 pad[0x3A];
    u8 b3A;
    u8 pad3B[2];
    u8 b3D, b3E, b3F, b40, b41, b42, b43, b44;
    u8 pad45[0x4C - 0x45];
    u8 b4C, b4D;
};

extern "C" {
extern U* lbl_804CB810;
extern u32 lbl_804CB700;
extern u8 lbl_804CA4AC;
extern u8 lbl_804CB838;
extern u8 lbl_804CB73C, lbl_804CB73D, lbl_804CB73E, lbl_804CB73F, lbl_804CB740;
extern C4 lbl_804CD880;
int fn_8013B9CC();
MM* fn_8013B9A8();
void fn_80137988(MM*, int);
void fn_8010E41C(u8*, int);
void fn_800F3EB0(U*, C4);
void fn_800F3F30(U*, int);
void fn_800F3F28(U*, int);
void fn_800F4B94(U*, int);
void fn_80006D00(f32);
void fn_801CA40C(u8*, int);
void fn_8013AC48(MM*);
void fn_8013AE18(MM*);

static inline U* unitAt(u8 id) {
    if (id) return &lbl_804CB810[id - 1];
    return 0;
}
static inline void body(O* o) {
    C4 co;
    u8 m1[0xC], m2[0xC], m3[0xC], m4[0xC], m5[0xC], m6[0xC], m7[0xC];
    /*P*/
    int i1;
    U* u1;
    int i2;
    U* u2;
    int i3;
    U* u3;
    int i4;
    U* u4;
    int i5;
    U* u5;
    int i6;
    U* u6;
    int i7;
    U* u7;
/*E*/
    if (o->b3A == 0) {
        lbl_804CB700 &= ~0x1000;
        if (fn_8013B9CC()) {
            fn_80137988(fn_8013B9A8(), 1);
        }
    }
    if (o->b3D) {
        fn_8010E41C(m1, 5);
        for (i1 = 1; i1 <= 0xFE; i1++) {
            u1 = unitAt(i1);
            if (u1->ec && m1[u1->f4->kind]) u1->bC6 = 100;
        }
        lbl_804CA4AC = 100;
    }
    if (o->b3E) {
        fn_8010E41C(m2, 5);
        for (i2 = 1; i2 <= 0xFE; i2++) {
            u2 = unitAt(i2);
            if (u2->ec && m2[u2->f4->kind]) {
                fn_800F3EB0(u2, lbl_804CD880);
            }
        }
    }
    if (o->b3F) {
        fn_8010E41C(m3, 5);
        for (i3 = 1; i3 <= 0xFE; i3++) {
            u3 = unitAt(i3);
            if (u3->ec && m3[u3->f4->kind] && u3->bD8 >= 0) {
                fn_800F3F30(u3, -1);
                fn_800F4B94(u3, -1);
            }
        }
    }
    if (o->b40) {
        fn_8010E41C(m4, 5);
        for (i4 = 1; i4 <= 0xFE; i4++) {
            u4 = unitAt(i4);
            if (u4->ec && m4[u4->f4->kind] && u4->hDA >= 0) {
                fn_800F3F28(u4, -1);
                fn_800F4B94(u4, -1);
            }
        }
    }
    if (o->b42) {
        fn_8010E41C(m5, 5);
        for (i5 = 1; i5 <= 0xFE; i5++) {
            u5 = unitAt(i5);
            if (u5->ec && m5[u5->f4->kind]) u5->h0 &= ~0x20;
        }
    }
    if (o->b43) {
        fn_8010E41C(m6, 5);
        for (i6 = 1; i6 <= 0xFE; i6++) {
            u6 = unitAt(i6);
            if (u6->ec && m6[u6->f4->kind]) u6->h0 &= ~0x800;
        }
    }
    if (o->b41) {
        fn_8010E41C(m7, 5);
        for (i7 = 1; i7 <= 0xFE; i7++) {
            u7 = unitAt(i7);
            if (u7->ec && m7[u7->f4->kind]) {
                u7->sx = 0.0f;
                u7->sy = 0.0f;
                u7->sz = 0.0f;
            }
        }
    }
    if (o->b44) {
        fn_80006D00(1.0f);
    }
    if (fn_8013B9CC()) {
        MM* mm = fn_8013B9A8();
        if (o->b4C) {
            int j;
            for (j = 0; j < mm->n52; j++) {
                fn_801CA40C(mm->c + j * 0xD0, 0);
            }
        }
        if (o->b4D) {
            fn_8013AC48(mm);
            fn_8013AE18(mm);
        }
    }
    lbl_804CB838 &= ~0x10;
    lbl_804CB73C = 1;
    lbl_804CB73E = 1;
    lbl_804CB73D = 1;
    lbl_804CB73F = 1;
    lbl_804CB740 = 0;
}
#pragma inline_max_size(4000)
void fn_800D7778(O* o) { body(o); }
}
