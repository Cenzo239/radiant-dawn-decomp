/* New game: clears the save data and applies the per-difficulty table in TUT_DATA. */
#include "game/rC2_8005259C/base.h"
struct Ver { u8 pad[0x44]; u32 a44; u8 p48[0xd]; u8 b55; };
struct Ent { s8 id; u8 p[4]; u8 fl[3]; u8 rest[0x10]; };
struct Tbl { u32 n; Ent e[1]; };
struct GD {
    u16 h0[8];
    u8 b10;
    u8 p11[7];
    u8 a18[0xc];
    u8 a24[0xc];
    u8 p30[0x61];
    u8 b91, b92;
    u8 p93;
    u16 h94, h96, h98;
    u8 p9a[2];
    u8 b9c, b9d;
    u8 p9e;
    u8 b9f;
    u64 ta0;
    u8 pa8[0x18];
    u16 hc0;
    u8 pc2[2];
    u16 hc4, hc6;
    u32 wc8, wcc;
    u8 pd0[0xc];
    u32 bits1[4];
    u32 pec;
    u32 bits2[4];
    u32 w100;
    u32 w104[12];
    u8 a134[0x10];
    u8 names[0x400];
    u8 bits[0x10];
    u8 a554[0x3c0];
};
extern "C" {
extern char lbl_803620E4[116];
extern u8 lbl_803C8E80[];
extern u8 lbl_803E9288[];
extern u8 lbl_803CB770[];
extern int lbl_804CB80C;
extern int lbl_804CB800;
void fn_8017F44C(void*, int, int);
u16 fn_80089ED0(void);
Ver* fn_8024BCA0(void);
void fn_801095FC(void*);
void fn_801097FC(void*);
void* fn_801B3ABC(void);
void* fn_80075D78(void*);
Tbl* fn_80077064(const char*);
void fn_8023F7EC(void*, int);
void fn_800761F0(void*);
void fn_80063C30(void*);
void fn_8002697C(void*);
void fn_8012CBF0(void);
void fn_800660C4(void*);
void fn_80105850(void);
void* memset(void*, int, u32);
}
static inline void setBit(u32* p, u32 q) {
    while (q >= 32) {
        q -= 32;
        p++;
    }
    *p |= 1 << q;
}

extern "C" void fn_800609D8(GD* g, u8 k0, u8 k, u32 lv) {
    int z = 0;
    g->b10 = k0;
    g->h0[0] = z;
    g->h0[1] = z;
    g->h0[2] = z;
    g->h0[3] = z;
    g->h0[4] = z;
    g->h0[5] = z;
    g->h0[6] = z;
    g->h0[7] = z;
    g->b9c = 3;
    fn_8017F44C(g->a18, 0, 0xc);
    fn_8017F44C(g->a24, 0, 0xc);
    g->b91 = z;
    g->b9d = z;
    g->b92 = z;
    g->h94 = fn_80089ED0();
    g->h96 = fn_80089ED0();
    g->h98 = fn_80089ED0();
    g->b9f = lv;
    if (lv > 0x63) {
        g->b9f = 0x63;
    }
    z = 0;
    *(u32*)((u8*)&g->ta0 + 4) = z;
    *(u32*)&g->ta0 = z;
    g->hc0 = z;
    g->wcc = z;
    g->hc4 = z;
    g->hc6 = z;
    fn_801095FC(&fn_8024BCA0()->a44);
    fn_8024BCA0()->b55 = k;
    fn_8024BCA0()->a44 |= 0x80;
    fn_801097FC(&fn_8024BCA0()->a44);
    g->bits1[0] = z;
    g->bits1[1] = z;
    g->bits1[2] = z;
    g->bits1[3] = z;
    g->bits2[0] = z;
    g->bits2[1] = z;
    g->bits2[2] = z;
    g->bits2[3] = z;
    {
        void* a = fn_80075D78(fn_801B3ABC());
        Tbl* t = fn_80077064(lbl_803620E4 + 0x17);
        Ent* e = t->e;
        u32 n = t->n;
        u32 i;
        for (i = 0; i < n; i++) {
            if (e[i].fl[k] & 2) {
                setBit(g->bits1, e[i].id);
            }
            if (e[i].fl[k] & 1) {
                setBit(g->bits2, e[i].id);
            }
        }
        fn_8023F7EC(fn_801B3ABC(), 0x20);
        fn_800761F0(a);
    }
    {
        int j;
        z = 0;
        for (j = 0; j < 0x10; j++) {
            g->bits[j] = z;
        }
        fn_80063C30(g->names);
        fn_8002697C(lbl_803C8E80);
        fn_8012CBF0();
        fn_800660C4(lbl_803CB770);
        fn_80105850();
        memset(lbl_803E9288, 0, 0xc);
        fn_8017F44C(g->a554, 0, 0x3c0);
        g->w104[0] = z;
        g->w104[1] = z;
        g->w104[2] = z;
        g->w104[3] = z;
        g->w104[4] = z;
        g->w104[5] = z;
        g->w104[6] = z;
        g->w104[7] = z;
        g->w104[8] = z;
        g->w104[9] = z;
        g->w104[10] = z;
        g->w104[11] = z;
        lbl_804CB80C = z;
        lbl_804CB800 = z;
    }
}
