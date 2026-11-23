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
void fn_801115A8(void* p, u32 v);
void fn_80119358(void* p, int i, u8 a, int b);
void fn_8011AEA0(void* p, u32 id, int a, int b);
void fn_8011097C(void* p, u32 v);
int fn_8011B77C(void* p, void* id);
void fn_80076D48(u32 v, void* p);
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
extern int lbl_804CB7A0;
extern u8* lbl_804CB7A4;
void fn_8010AECC(void*);
u8 fn_8010F73C(u32);
u16 fn_801112A8(u32);
void fn_8010FFFC(void*, u32);
void fn_8010FE38(void*);
u8 fn_8010F988(u32);
void fn_8010A958() {
    u8* s;
    u8* q;
    int n;
    u8* j;
    int i;
    int k;
    u8 fl;
    int nB;
    int nA;
    int k2;
    {
        u8* d = fn_80077064(lbl_80367F68 + 0xA6);
        n = (d[0] << 24) + (d[1] << 16) + (d[2] << 8) + d[3];
        s = d + 4;
        lbl_804CB7A0 = n;
        lbl_804CB7A4 = fn_8028BE18(fn_800791B0(n * 0x50 + 0x10), (void*)fn_8010AECC, 0, 0x50, n);
        fn_8017F44C(lbl_804CB7A4, 0, lbl_804CB7A0 * 0x50);
    }
    j = lbl_804CB7A4;
    for (i = 0; i < lbl_804CB7A0; i++) {
        H(j, 0xE) = i + 1;
        W(j, 0) = Rd(s);
        W(j, 4) = Rd(s);
        W(j, 8) = Rd(s);
        B(j, 0x12) = fn_8010F73C(Rd(s));
        B(j, 0x13) = fn_8010F73C(Rd(s));
        H(j, 0x18) = fn_801112A8(Rd(s));
        W(j, 0x40) = Rd(s);
        W(j, 0x44) = Rd(s);
        W(j, 0x48) = Rd(s);
        q = (u8*)((u32)(s + 0x10) & ~3);
        H(j, 0x16) = (s[0] << 8) + s[1];
        H(j, 0x10) = (s[2] << 8) + s[3];
        B(j, 0x1C) = s[4];
        B(j, 0x1D) = s[5];
        B(j, 0x1F) = s[6];
        B(j, 0x1E) = s[7];
        B(j, 0x1B) = s[8];
        B(j, 0x1A) = s[9];
        B(j, 0x20) = s[0xA];
        B(j, 0x21) = s[0xB];
        B(j, 0x15) = s[0xC];
        B(j, 0x2C) = q[0];
        nA = q[1];
        nB = q[2];
        fl = q[3];
        q += 4;
        for (k = 0; k < nA; k++) fn_8010FFFC(j, Rd(q));
        for (k2 = 0; k2 < nB; k2++) fn_8011097C(j + 0xC, Rd(q));
        if (fl & 1) {
            B(j, 0x22) = q[0];
            B(j, 0x23) = q[1];
            B(j, 0x24) = q[2];
            B(j, 0x25) = q[3];
            B(j, 0x26) = q[4];
            B(j, 0x27) = q[5];
            B(j, 0x28) = q[6];
            B(j, 0x29) = q[7];
            B(j, 0x2A) = q[8];
            B(j, 0x2B) = q[9];
            q += 0xA;
        } else {
            B(j, 0x22) = 0;
            B(j, 0x23) = 0;
            B(j, 0x24) = 0;
            B(j, 0x25) = 0;
            B(j, 0x26) = 0;
            B(j, 0x27) = 0;
            B(j, 0x28) = 0;
            B(j, 0x29) = 0;
            B(j, 0x2A) = 0;
            B(j, 0x2B) = 0;
        }
        if (fl & 2) {
            B(j, 0x2D) = q[0];
            B(j, 0x2E) = q[1];
            B(j, 0x2F) = q[2];
            B(j, 0x30) = q[3];
            B(j, 0x31) = q[4];
            B(j, 0x32) = q[5];
            B(j, 0x33) = q[6];
            B(j, 0x34) = q[7];
            q += 8;
        } else {
            B(j, 0x2D) = 0;
            B(j, 0x2E) = 0;
            B(j, 0x2F) = 0;
            B(j, 0x30) = 0;
            B(j, 0x31) = 0;
            B(j, 0x32) = 0;
            B(j, 0x33) = 0;
            B(j, 0x34) = 0;
        }
        fn_8010FE38(j);
        B(j, 0x14) = fn_8010F988(W(j, 0));
        fn_80076D48(W(j, 0), j);
        s = (u8*)((u32)(q + 3) & ~3);
        j += 0x50;
    }
}
}
