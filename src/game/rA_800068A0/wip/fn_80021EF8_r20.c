/* Round 20 draft, NOT at a counted level (check_regs.py: other): fn_80021EF8. Self-contained, complete source. Instruction count ours 27 orig 33. What differs: 27 vs 33 instructions: the original keeps base+0x10000-0x7fc0 in r31 and indexes with lwzx, and invalidates four dependent tables through four separate base registers (pooled file statics); the draft uses one struct. */
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


#pragma use_lmw_stmw off
/* ---- from rA_800068A0/wip/fn_80021EF8.c ---- */
/* fn_80021EF8: near miss, 26 of 27 words differ. Depends on types and helpers from ../fn_80021754.c; goes there in address order. */
void fn_80021EF8(int i, u32 key) {
    GXCache* g = &lbl_803B7878;
    u32* k = g->a8040;
    if (key != k[i]) {
        u32* b = g->a8080;
        u32* c = g->a80C0;
        u32* d = g->a8100;
        u32* e = g->a8140;
        b[i] = -1;
        c[i] = -1;
        d[i] = -1;
        e[i] = -1;
        fn_80306C18(i, key);
        k[i] = key;
    }
}