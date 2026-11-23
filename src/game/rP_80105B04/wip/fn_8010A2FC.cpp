/* 8 of 407 words differ: only registers. The hoisted 0 for +0x101 should be r26 and nB r31, ours swap them, and the record count should be r26, ours r25.
   fn_80109DF8 and fn_8010A958 are the same kind of loader and should follow once this is solved. */
#include "game/rP_80105B04/rp.h"
/* Job table loader: "BinData" block with one big-endian record per job, 0x11C bytes in memory. */
struct JobRec {
    u32 w[9];       /* 0x00 */
    u16 x24[0x48];  /* 0x24: skill list */
    u8 padB4[0];
};
extern "C" {
extern char lbl_80367F68[];
extern int lbl_804CB798;
extern u8* lbl_804CB79C;
extern void* lbl_804CA4E8;
u8* fn_80077064(const char* s);
void* fn_800791B0(int n);
u8* fn_8028BE18(void* p, void* ctor, int a, int sz, int n);
void fn_8017F44C(void* p, int v, int n);
void fn_80118DF4(void* p);
#if TARGET_PC
/* Host: pointer arguments the callers pass as 32-bit window offsets */
void fn_801115A8(void* p, p32arg v);
#else
void fn_801115A8(void* p, u32 v);
#endif
void fn_80119358(void* p, int i, u8 a, int b);
#if TARGET_PC
void fn_8011AEA0(void* p, p32arg id, int a, int b);
#else
void fn_8011AEA0(void* p, u32 id, int a, int b);
#endif
#if TARGET_PC
void fn_8011097C(void* p, p32arg v);
#else
void fn_8011097C(void* p, u32 v);
#endif
int fn_8011B77C(void* p, void* id);
#if TARGET_PC
void fn_80076D48(p32arg v, void* p);
#else
void fn_80076D48(u32 v, void* p);
#endif
void fn_801192F0(void* p);

static inline u32 Rd(u8*& s) {
    u8* p;
    u32 v;
    if (s == 0) return 0;
    p = s;
    v = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
    s = p + 4;
    return v;
}
#define B(p, o) (((u8*)(p))[o])
#define W(p, o) (*(u32*)((u8*)(p) + (o)))
#define H(p, o) (*(u16*)((u8*)(p) + (o)))
#pragma use_lmw_stmw on
void fn_8010A2FC() {
    u8* q;
    u8* j;
    int i;
    int n;
    int k;
    int nB;
    int nA;
    {
        u8* p = fn_80077064(lbl_80367F68 + 0x9E);
        n = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
        q = p + 4;
        lbl_804CB798 = n;
        lbl_804CB79C = fn_8028BE18(fn_800791B0(n * 0x11C + 0x10), (void*)fn_80118DF4, 0, 0x11C, n);
        fn_8017F44C(lbl_804CB79C, 0, lbl_804CB798 * 0x11C);
    }
    j = lbl_804CB79C;
    for (i = 0; i < lbl_804CB798; i++) {
        H(j, 0xEC) = i + 1;
        W(j, 0x00) = Rd(q);
        W(j, 0x04) = Rd(q);
        W(j, 0x08) = Rd(q);
        W(j, 0x0C) = Rd(q);
        W(j, 0x10) = Rd(q);
        W(j, 0x14) = Rd(q);
        W(j, 0x18) = Rd(q);
        W(j, 0x1C) = Rd(q);
        W(j, 0x20) = Rd(q);
        W(j, 0xE8) = Rd(q);
        fn_801115A8(j + 0xB8, W(j, 0xE8));
        fn_801115A8(j + 0xD0, Rd(q));
        B(j, 0xF0) = q[0];
        fn_80119358(j, 0, q[1], (s8)q[2]);
        fn_80119358(j, 1, q[3], (s8)q[4]);
        nA = q[5];
        nB = q[6];
        B(j, 0xFA) = q[7];
        B(j, 0xF9) = q[8];
        B(j, 0xF5) = q[9];
        B(j, 0xF7) = q[0xA];
        B(j, 0xF8) = q[0xB];
        B(j, 0xF6) = q[0xC];
        q += 0x10;
        for (k = 0; k < nA; k++) {
            fn_8011AEA0(j + 0x24, Rd(q), 1, 0);
        }
        W(j, 0xB4) = Rd(q);
        for (k = 0; k < nB; k++) {
            fn_8011097C(j + 0xEE, Rd(q));
        }
        B(j, 0xFB) = fn_8011B77C(j + 0x24, lbl_804CA4E8) ? 0x28 : 0x14;
        B(j, 0x104) = q[0x0];
        B(j, 0x105) = q[0x1];
        B(j, 0x106) = q[0x2];
        B(j, 0x107) = q[0x3];
        B(j, 0x108) = q[0x4];
        B(j, 0x109) = q[0x5];
        B(j, 0x10a) = q[0x6];
        B(j, 0x10b) = q[0x7];
        B(j, 0xfc) = q[0x8];
        B(j, 0xfd) = q[0x9];
        B(j, 0xfe) = q[0xa];
        B(j, 0xff) = q[0xb];
        B(j, 0x100) = q[0xc];
        B(j, 0x101) = 0;
        B(j, 0x102) = q[0xe];
        B(j, 0x103) = q[0xf];
        B(j, 0x10c) = q[0x10];
        B(j, 0x10d) = q[0x11];
        B(j, 0x10e) = q[0x12];
        B(j, 0x10f) = q[0x13];
        B(j, 0x110) = q[0x14];
        B(j, 0x111) = q[0x15];
        B(j, 0x112) = q[0x16];
        B(j, 0x113) = q[0x17];
        B(j, 0x114) = q[0x18];
        B(j, 0x115) = q[0x19];
        B(j, 0x116) = q[0x1a];
        B(j, 0x117) = q[0x1b];
        B(j, 0x118) = q[0x1c];
        B(j, 0x119) = q[0x1d];
        B(j, 0x11a) = q[0x1e];
        B(j, 0x11b) = q[0x1f];
        fn_80076D48(W(j, 0), j);
        {
            u8* nq = q + 0x23;
            j += 0x11C;
#if TARGET_PC
            q = (u8*)(FE10_PTRINT(nq) & ~3);
#else
            q = (u8*)((u32)nq & ~3);
#endif
        }
    }
    for (i = 0; i < lbl_804CB798; i++) {
        fn_801192F0(lbl_804CB79C + i * 0x11C);
    }
}
}
