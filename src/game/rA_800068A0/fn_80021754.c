#include "game/rA_800068A0/types.h"

/* GX state cache: each wrapper builds a key from its arguments and calls the
 * GX setter only when the key differs from the cached one. */

typedef struct GXColor8 { u8 r, g, b, a; } GXColor8;

extern GXColor8 lbl_804CB0B4;

void fn_80021754(GXColor8 c) {
    lbl_804CB0B4.r = c.r;
    lbl_804CB0B4.g = c.g;
    lbl_804CB0B4.b = c.b;
    lbl_804CB0B4.a = c.a;
}

extern void fn_80307054();
extern u32 lbl_804CB0C0;

void fn_80021808(int a0, u8 a1, int a2, int a3, u8 a4) {
    u32 key = a0 + (a1 << 4) + (a2 << 8) + (a3 << 12) + (a4 << 16);
    if (lbl_804CB0C0 != key) {
        fn_80307054(a0, a1, a2, a3, a4);
        lbl_804CB0C0 = key;
    }
}

extern void fn_803077F0();
extern u32 lbl_804CB0C4;

void fn_80021860(int a0, int a1, u8 a2) {
    u32 key = a0 + (a1 << 8) + (a2 << 16);
    if (key != lbl_804CB0C4) {
        fn_803077F0(a0, a1, a2);
        lbl_804CB0C4 = key;
    }
}

extern void fn_803055E4();
extern void fn_803056BC();
extern u32 lbl_804CB0C8;
extern u32 lbl_804CB0CC;

void fn_800218A8(int ch, GXColor8 c) {
    u32 key = *(u32*)&c;
    switch (ch) {
    case 0:
    case 2:
    case 4:
        if (lbl_804CB0C8 != key) {
            fn_803055E4(ch, c);
            lbl_804CB0C8 = key;
        }
        break;
    default:
        fn_803055E4(ch, c);
        break;
    }
}

void fn_80021958(int ch, GXColor8 c) {
    u32 key = *(u32*)&c;
    switch (ch) {
    case 0:
    case 2:
    case 4:
        if (lbl_804CB0CC != key) {
            fn_803056BC(ch, c);
            lbl_804CB0CC = key;
        }
        break;
    default:
        fn_803055E4(ch, c);
        break;
    }
}

extern void fn_803057B8();
extern u32 lbl_804CB0D0;
extern u32 lbl_804CB0D4;

#define CHANKEY (a1 + (a2 << 1) + (a3 << 2) + (a5 << 3) + (a6 << 5) + (a4 << 7))

void fn_80021A08(int ch, int a1, int a2, int a3, int a4, int a5, int a6) {
    u32 key;
    switch (ch) {
    case 4:
        key = CHANKEY;
        if (lbl_804CB0D0 + (lbl_804CB0D4 << 16) != key + (key << 16)) {
            fn_803057B8(ch, a1, a2, a3, a4, a5, a6);
            lbl_804CB0D0 = key;
            lbl_804CB0D4 = key;
        }
        break;
    case 0:
        key = CHANKEY;
        if (lbl_804CB0D0 != key) {
            fn_803057B8(ch, a1, a2, a3, a4, a5, a6);
            lbl_804CB0D0 = key;
        }
        break;
    case 2:
        key = CHANKEY;
        if (lbl_804CB0D4 != key) {
            fn_803057B8(ch, a1, a2, a3, a4, a5, a6);
            lbl_804CB0D4 = key;
        }
        break;
    default:
        fn_803057B8(ch, a1, a2, a3, a4, a5, a6);
        break;
    }
}

extern void fn_80307748();
extern u32 lbl_804CB0E0;

void fn_80021BA4(int a0, int a1, int a2, int a3) {
    u32 key = a0 | (a1 << 8) | (a2 << 16) | (a3 << 24);
    if (key != lbl_804CB0E0) {
        fn_80307748(a0, a1, a2, a3);
        lbl_804CB0E0 = key;
    }
}

extern void fn_80307118();
extern u32 lbl_803BF878[16];

void fn_80021CB4(int i, int a1, int a2, int a3) {
    u32 key = a1 | (a2 << 8) | (a3 << 16);
    if (key != lbl_803BF878[i]) {
        fn_80307118(i, a1, a2, a3);
        lbl_803BF878[i] = key;
    }
}

extern void fn_80306D2C();
extern void fn_80306D84();
extern void fn_80306CAC();
extern void fn_80306CEC();
extern void fn_80306C18();
extern void fn_80303634();
extern u32 lbl_803BF8B8[16];
extern u32 lbl_803BF8F8[16];
extern u32 lbl_803BF938[16];
extern u32 lbl_803BF978[16];
extern u32 lbl_803BF9B8[16];
extern u32 lbl_803BF9F8[16];

void fn_80021D18(int i, int a1, int a2, int a3, u8 a4, int a5) {
    u32 key = a1 | (a2 << 4) | (a3 << 8) | (a4 << 12) | (a5 << 16);
    if (key != lbl_803BF8F8[i]) {
        fn_80306D2C(i, a1, a2, a3, a4, a5);
        lbl_803BF8F8[i] = key;
        lbl_803BF8B8[i] = -1;
    }
}

void fn_80021D9C(int i, int a1, int a2, int a3, u8 a4, int a5) {
    u32 key = a1 | (a2 << 4) | (a3 << 8) | (a4 << 12) | (a5 << 16);
    if (key != lbl_803BF938[i]) {
        fn_80306D84(i, a1, a2, a3, a4, a5);
        lbl_803BF938[i] = key;
        lbl_803BF8B8[i] = -1;
    }
}

void fn_80021E20(int i, int a1, int a2, int a3, int a4) {
    u32 key = a1 | (a2 << 8) | (a3 << 16) | (a4 << 24);
    if (key != lbl_803BF978[i]) {
        fn_80306CAC(i, a1, a2, a3, a4);
        lbl_803BF978[i] = key;
    }
}

void fn_80021E8C(int i, int a1, int a2, int a3, int a4) {
    u32 key = a1 | (a2 << 8) | (a3 << 16) | (a4 << 24);
    if (key != lbl_803BF9B8[i]) {
        fn_80306CEC(i, a1, a2, a3, a4);
        lbl_803BF9B8[i] = key;
    }
}

/* The sine table (0x8000 bytes) and the state caches share one object. */
typedef struct GXCache {
    s16 sinTbl[0x4000];
    u32 a8000[16];
    u32 a8040[16];
    u32 a8080[16];
    u32 a80C0[16];
    u32 a8100[16];
    u32 a8140[16];
    u32 a8180[8];
    u32 a81A0[16];
    u32 a81E0[16];
    u32 a8220[16];
    u32 a8260[64];
} GXCache;
extern GXCache lbl_803B7878;

void fn_80021EF8(int i, u32 key);

void fn_80021F7C(int i, int a1, int a2, int a3) {
    u32 lo = a1 | (a2 << 8);
    u32 hi = a3 << 16;
    u32 key = hi | lo;
    if (key != lbl_803BF9F8[i]) {
        fn_80303634(i, a1, a2, a3, 0, 0x7D);
        lbl_803BF9F8[i] = key;
    }
}

extern void fn_80306EFC();
extern void fn_80306F4C();
extern void fn_80306F9C();
extern u8 lbl_804CB0E9;
extern u8 lbl_804CB0EA;
extern u32 lbl_803BFA18[16];
extern u32 lbl_803BFA58[16];
extern u32 lbl_803BFA98[16];

#pragma use_lmw_stmw on
void fn_800220B0(void) {
    int i;
    if (lbl_804CB0E9 == 0) return;
    for (i = 0; i < 16; i++) {
        if (lbl_803BFA18[i] != 0) {
            fn_80306EFC(i, 0);
            lbl_803BFA18[i] = 0;
            lbl_804CB0E9 = 1;
        }
        if (lbl_803BFA58[i] != 0) {
            fn_80306F4C(i, 0);
            lbl_803BFA58[i] = 0;
            lbl_804CB0E9 = 1;
        }
    }
    lbl_804CB0E9 = 0;
}
#pragma use_lmw_stmw off

void fn_800221BC(void) {
    int i;
    if (lbl_804CB0EA == 0) return;
    for (i = 0; i < 16; i++) {
        if (lbl_803BFA98[i] != 0) {
            fn_80306F9C(i, 0, 0);
            lbl_803BFA98[i] = 0;
            lbl_804CB0EA = 1;
        }
    }
    lbl_804CB0EA = 0;
}

typedef struct GXBlock { u32 w[8]; } GXBlock;
extern GXBlock lbl_803BFAD8[];
extern void fn_80305FC4(const GXBlock*, int);

void fn_80022254(const GXBlock* p, int n) {
    GXBlock* c = &lbl_803BFAD8[n];
    int i;
    for (i = 0; i < 8; i++) {
        if (p->w[i] != c->w[i]) {
            fn_80305FC4(p, n);
            *c = *p;
            return;
        }
    }
}

extern void fn_803055E4(int ch, GXColor8 c);
extern void fn_803056BC(int ch, GXColor8 c);
extern void fn_803077C4(int);
extern void fn_80307798(int);
extern u32 lbl_804CB0B8;
extern u32 lbl_804CB0BC;
extern u32 lbl_804CB0DC;
extern u8 lbl_804CB0D8;
extern u8 lbl_804CB0E4;
extern u8 lbl_804CB0E5;
extern u8 lbl_804CB0E6;
extern u8 lbl_804CB0E7;
extern u8 lbl_804CB0E8;

#pragma use_lmw_stmw on
void fn_8002230C(void);
#pragma use_lmw_stmw off
