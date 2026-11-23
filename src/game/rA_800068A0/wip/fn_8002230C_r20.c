/* Round 20 draft, NOT at a counted level (check_regs.py: other): fn_8002230C. Self-contained, complete source. Instruction count ours 227 orig 227. What differs: rewritten with the GX state caches as separate definitions pooled behind the sine table (the real fn_8001E44C is repeated in the file to put the table at the head of the pool). That reproduces the per-array base registers and the 8-entry fill, but this compiler lays pooled objects out in order of first use, so the offsets of 0x8040..0x8260 differ from the original (address order). wip/fn_8002230C_r18.c is the other near miss (one struct, 2 words). */
/* Round 18 wip (other level, close): fn_8002230C. Same size and instructions except (1) the li -1 for the first loop is scheduled before the base address is finished (the original reuses r3 for both), and (2) the 8-entry a8180 fill: the original stores entry 0 through the base register and entries 1..7 through a pointer with a second li -1. hi/ARR (base + 0x10000 with negative offsets) reproduces the single base register; the original source probably just uses the struct members. Self-contained. */
#include "game/rA_800068A0/types.h"

/* GX state cache: each wrapper builds a key from its arguments and calls the
 * GX setter only when the key differs from the cached one. */

typedef struct GXColor8 { u8 r, g, b, a; } GXColor8;

extern GXColor8 lbl_804CB0B4;

void fn_80021754(GXColor8 c);

extern void fn_80307054();
extern u32 lbl_804CB0C0;

void fn_80021808(int a0, u8 a1, int a2, int a3, u8 a4);

extern void fn_803077F0();
extern u32 lbl_804CB0C4;

void fn_80021860(int a0, int a1, u8 a2);

extern void fn_803055E4();
extern void fn_803056BC();
extern u32 lbl_804CB0C8;
extern u32 lbl_804CB0CC;

void fn_800218A8(int ch, GXColor8 c);

void fn_80021958(int ch, GXColor8 c);

extern void fn_803057B8();
extern u32 lbl_804CB0D0;
extern u32 lbl_804CB0D4;

#define CHANKEY (a1 + (a2 << 1) + (a3 << 2) + (a5 << 3) + (a6 << 5) + (a4 << 7))

void fn_80021A08(int ch, int a1, int a2, int a3, int a4, int a5, int a6);

extern void fn_80307748();
extern u32 lbl_804CB0E0;

void fn_80021BA4(int a0, int a1, int a2, int a3);

extern void fn_80307118();
extern u32 lbl_803BF878[16];

void fn_80021CB4(int i, int a1, int a2, int a3);

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

void fn_80021D18(int i, int a1, int a2, int a3, u8 a4, int a5);

void fn_80021D9C(int i, int a1, int a2, int a3, u8 a4, int a5);

void fn_80021E20(int i, int a1, int a2, int a3, int a4);

void fn_80021E8C(int i, int a1, int a2, int a3, int a4);

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

void fn_80021F7C(int i, int a1, int a2, int a3);

extern void fn_80306EFC();
extern void fn_80306F4C();
extern void fn_80306F9C();
extern u8 lbl_804CB0E9;
extern u8 lbl_804CB0EA;
extern u32 lbl_803BFA18[16];
extern u32 lbl_803BFA58[16];
extern u32 lbl_803BFA98[16];

#pragma use_lmw_stmw on
void fn_800220B0(void);
#pragma use_lmw_stmw off

void fn_800221BC(void);

typedef struct GXBlock { u32 w[8]; } GXBlock;
extern GXBlock lbl_803BFAD8[];
extern void fn_80305FC4(const GXBlock*, int);

void fn_80022254(const GXBlock* p, int n);

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

#pragma use_lmw_stmw on
/* fn_8002230C (GX state cache reset): every cached key is set to -1, the colours are re-sent and the
 * two "dirty" flush routines (fn_800221BC, then fn_800220B0) run inline. The inline copies below read the
 * cache arrays as members of lbl_803B7878 (lbl_803BFA18/58/98 are a81A0/a81E0/a8220 of that object), which
 * is what makes the original keep one base register for the whole function. */
typedef struct ColPair { GXColor8 a; GXColor8 b; } ColPair;
extern const GXColor8 lbl_804CCC5C;
extern const GXColor8 lbl_804CCC60;
typedef struct GXBlock8 { u32 w[8]; } GXBlock8;
/* lbl_803B7878 is the pooled .bss of this translation unit: the sine table and the GX state caches are separate
   file statics (the original fills the 8-entry table through its own base register). Same memory as GXCache above. */
s16 sSinTbl[0x4000];
u32 s8000[16];
u32 s8040[16];
u32 s8080[16];
u32 s80C0[16];
u32 s8100[16];
u32 s8140[16];
u32 s8180[8];
u32 s81A0[16];
u32 s81E0[16];
u32 s8220[16];
u32 s8260[64];
/* The sine table initialiser (matched in fn_8001E1A4.cpp) is repeated here because it is the function of this
   translation unit that puts sSinTbl at the head of the pool. */
extern f64 fn_80295940(f64);
extern void fn_80006D00(f32);
void fn_8001E44C(void) {
    int i;
    for (i = 0; i < 0x4000; i++) {
        f32 v = fn_80295940(6.2831855f * i / 16384.0f);
        v *= 16384.0f;
        sSinTbl[i] = v;
    }
    fn_80006D00(1.0f);
}

static inline void FlushTexMtx(void) {
    int i;
    if (lbl_804CB0EA == 0) return;
    for (i = 0; i < 16; i++) {
        if (s8220[i] != 0) {
            fn_80306F9C(i, 0, 0);
            s8220[i] = 0;
            lbl_804CB0EA = 1;
        }
    }
    lbl_804CB0EA = 0;
}
static inline void FlushTex(void) {
    int i;
    if (lbl_804CB0E9 == 0) return;
    for (i = 0; i < 16; i++) {
        if (s81A0[i] != 0) {
            fn_80306EFC(i, 0);
            s81A0[i] = 0;
            lbl_804CB0E9 = 1;
        }
        if (s81E0[i] != 0) {
            fn_80306F4C(i, 0);
            s81E0[i] = 0;
            lbl_804CB0E9 = 1;
        }
    }
    lbl_804CB0E9 = 0;
}

void fn_8002230C(void) {
    int i;
    for (i = 0; i < 16; i++) {
        s8000[i] = -1;
        s8080[i] = -1;
        s80C0[i] = -1;
        s8100[i] = -1;
        s8140[i] = -1;
        s8040[i] = -1;
        s8220[i] = -1;
    }
    for (i = 0; i < 8; i++) {
        s8180[i] = -1;
    }
    for (i = 0; i < 64; i++) {
        s8260[i] = -1;
    }
    lbl_804CB0B8 = -1;
    lbl_804CB0BC = -1;
    lbl_804CB0C0 = -1;
    lbl_804CB0C4 = -1;
    lbl_804CB0C8 = -1;
    lbl_804CB0CC = -1;
    lbl_804CB0DC = -1;
    lbl_804CB0E0 = -1;
    lbl_804CB0D0 = -1;
    lbl_804CB0D4 = -1;
    lbl_804CB0D8 = 0;
    lbl_804CB0E4 = 0;
    lbl_804CB0E5 = 0;
    lbl_804CB0E6 = 0;
    lbl_804CB0E7 = 0;
    lbl_804CB0E8 = 1;
    fn_803055E4(4, lbl_804CCC5C);
    fn_803056BC(4, lbl_804CCC60);
    fn_803077C4(0);
    fn_80307798(1);
    lbl_804CB0EA = 1;
    lbl_804CB0E9 = 1;
    FlushTexMtx();
    FlushTex();
}
