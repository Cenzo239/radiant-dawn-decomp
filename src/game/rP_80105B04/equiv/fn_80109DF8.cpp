/* EQUIVALENT (sched, round 19b): fn_80109DF8. Moved instruction (checked with dd.py): the dead pair-loop counter addi r8 is before the pointer step addi r7 instead of after it. From wip/fn_80109DF8.cpp. */
#pragma push
#pragma ppc_unroll_factor_limit 1
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
extern int lbl_804CB790;
extern u8* lbl_804CB794;
extern void* lbl_804CA4DC;
void fn_80118D24(void*);
#if TARGET_PC
u8 fn_801194FC(p32arg);
#else
u8 fn_801194FC(u32);
#endif
void fn_80119258(void*, u8*);
void fn_8010A2FC() ;
struct DJ2 { u32 x, y; }; struct DJ { u8 p[0xEC]; DJ2 a[2]; };
static inline void Rd4w(DJ2* o, u8*& q) { o->x = Rd(q); o->y = Rd(q); }
void fn_80109DF8() {
    u8 buf[4];
    u8* pp;
    s16 tt;
    u8 nS;
    u8 fl;
    u8* q;
    u8* j;
    int i;
    int n;
    u8 k;
    int t;
    u32 v;
    {
        u8* d = fn_80077064(lbl_80367F68 + 0x93);
        n = (d[0] << 24) + (d[1] << 16) + (d[2] << 8) + d[3];
        q = d + 4;
        lbl_804CB790 = n;
        lbl_804CB794 = fn_8028BE18(fn_800791B0(n * 0xFC + 0x10), (void*)fn_80118D24, 0, 0xFC, n);
        fn_8017F44C(lbl_804CB794, 0, lbl_804CB790 * 0xFC);
    }
    j = lbl_804CB794;
    for (i = 0; i < lbl_804CB790; i++) {
        H(j, 0x1C) = i + 1;
        nS = q[0];
        B(j, 0x1E) = q[2];
        fl = q[3];
        q += 4;
        W(j, 0x00) = Rd(q);
        W(j, 0x04) = Rd(q);
        W(j, 0x08) = Rd(q);
        W(j, 0x10) = Rd(q);
        W(j, 0x14) = Rd(q);
        B(j, 0xE1) = fn_801194FC(Rd(q));
        fn_801115A8(j + 0x32, Rd(q));
#if TARGET_PC
        /* lbl_804CA4DC points into the DOL data (outside the window): pass the pointer */
        if (fl) fn_8011AEA0(j + 0x4C, lbl_804CA4DC, 0, 2);
#else
        if (fl) fn_8011AEA0(j + 0x4C, (u32)lbl_804CA4DC, 0, 2);
#endif
        for (fl = 0; fl < nS; fl++) {
            fn_8011AEA0(j + 0x4C, Rd(q), 0, 2);
        }
        v = Rd(q);
        if (v) fn_8011AEA0(j + 0x4C, v, 0, 2);
pp = j; for (tt = 0; tt < 2; ) { W(pp, 0xEC) = Rd(q); W(pp, 0xF0) = Rd(q); pp += 8; tt++; }
        B(j, 0xE4) = q[0];
        B(j, 0xE5) = q[1];
        B(j, 0xE3) = q[2];
        B(j, 0xE0) = q[3];
        B(j, 0x21) = q[4];
        buf[0] = q[5];
        buf[1] = q[6];
        buf[2] = q[7];
        buf[3] = q[8];
        fn_80119258(j, buf);
        B(j, 0x22) = q[9];
        B(j, 0x23) = q[0xA];
        B(j, 0x24) = q[0xB];
        B(j, 0x25) = q[0xC];
        B(j, 0x26) = q[0xD];
        B(j, 0x27) = q[0xE];
        B(j, 0x28) = q[0xF];
        B(j, 0x29) = q[0x10];
        B(j, 0x1F) = q[0x11];
        B(j, 0x20) = q[0x12];
        B(j, 0x2A) = q[0x13];
        B(j, 0x2B) = q[0x14];
        B(j, 0x2C) = q[0x15];
        B(j, 0x2D) = q[0x16];
        B(j, 0x2E) = q[0x17];
        B(j, 0x2F) = q[0x18];
        B(j, 0x30) = q[0x19];
        B(j, 0x31) = q[0x1A];
        fn_80076D48(W(j, 0), j);
        {
            u8* nq = q + 0x1E;
            j += 0xFC;
#if TARGET_PC
            q = (u8*)(FE10_PTRINT(nq) & ~3);
#else
            q = (u8*)((u32)nq & ~3);
#endif
        }
    }
}
}