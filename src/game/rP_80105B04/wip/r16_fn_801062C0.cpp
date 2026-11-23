/* NOT MATCHING, not compiled. fn_801062C0: 23 of 474 words, all in the first slot loop: h wants r28 (ours r26), the tm array base r26 (ours r28), the newest base r22 and 0x100000 r21 (swapped), lis 0x2005 r31 and the lbl_80367E9C base r30 (swapped). Everything else matches, including SysInit (shared with fn_80106B84). */
#include "game/rP_80105B04/rp.h"
#pragma use_lmw_stmw on
extern "C" {
struct SysF {
    u32 magic, ver;
    u64 seed;
    u16 x10;
    u8 s12[0x1E];
    void* p30;
    u32 w34, w38, w3c, w40;
    u8 x44, x45, x46, x47;
    u8 x48;
    u8 x49[2];
    u8 x4b;
};
extern SysF lbl_803EC180;
extern u8 lbl_8037F7E0[];
void fn_802F56CC(int, u64*);
s64 OSGetTime(void);
u32 fn_80331194(void);
u8 fn_80105E98(void);
void* memset(void* p, int v, u32 n);
static inline void SysInit(SysF* h) {
    u64 t;
    h->magic = 0x53595346;
    h->ver = 0x20050201;
    t = 0;
    fn_802F56CC(0, &t);
    t += OSGetTime();
    t += fn_80331194() * 0x7b;
    h->x10 = 0;
    h->seed = t;
    h->x44 = 0;
    h->x45 = 0;
    h->x46 = 0x40;
    h->x47 = 0;
    h->x48 = fn_80105E98();
    h->x4b = 0;
    memset(h->s12, 0, 0x1e);
    memset(h->x49, 0, 2);
    h->w34 = 0;
    h->w38 = 0;
    h->w3c = 0;
    h->w40 = 0;
}
struct FHdr {
    u8 pad[0x40];
    u32 magic;
    u32 ver;
    u32 time;
    u32 size;
    u32 crc;
    u8 pad54[0xc];
    u8 x60, x61, x62, x63;
    u8 pad64[0xc];
    SysF sys;
};
struct Bank { u8* base; };
extern char lbl_80367E9C[];
int fn_80079E84(u8*);
void fn_80079E70(int);
void* fn_80078CCC(int, const char*, int);
void fn_800799AC(u32* table);
u32 fn_80079A6C(void*, void*, u32);
void fn_80078E24(void*);
void fn_80105EB0(SysF*, SysF*);
static inline BOOL Valid(FHdr* h) {
    if (h->magic != 0x4645384A) return 0;
    return h->ver == 0x20050201;
}
static inline BOOL SysValid(FHdr* h) {
    if (h->sys.magic != 0x53595346) return 0;
    return h->sys.ver == 0x20050201;
}
static inline BOOL CrcOk(FHdr* h) {
    void* w;
    u32 c;
    if (h->crc == 0x12345678) return 1;
    if (h->x60 == 1) return 1;
    w = fn_80078CCC(0x400, lbl_80367E9C, 0);
    fn_800799AC((u32*)w);
    c = fn_80079A6C(w, &h->sys, h->size - 0x70);
    fn_80078E24(w);
    return h->crc == c;
}
static inline u32 Time(FHdr* h) {
    u32 n = h->time;
    return n > 0x100000 ? 0 : n;
}
void fn_801062C0(Bank* b, int mode) {
    s8 newest[5];
    u32 tm[5];
    u8 cnt[6];
    FHdr* p[2];
    /*P*/
    int o5;
    FHdr* h5;
    int o4;
    int o1;
    int i2;
    int i3;
    FHdr* h4;
    int i4;
    FHdr* h1;
    int i1;
    int i5;
    FHdr* h6;
    u8* base;
    int o6;
    FHdr* h7;
    int i7;
    int o7;
    FHdr* f;
    u32 best;
    int i6;
/*E*/
    if (!fn_80079E84(b->base)) {
        fn_80079E70(-4);
        return;
    }
    for (i1 = 0; i1 < 5; i1++) {
        newest[i1] = -1;
        tm[i1] = 0;
    }
    for (i1 = 0, o1 = 0x2000; i1 < 6; i1++, o1 += 0x4000) {
        h1 = (FHdr*)(b->base + o1);
        if (Valid(h1) && !CrcOk(h1)) {
            h1->magic = 0;
            fn_80079E70(-0x42);
        } else {
            u8 k = h1->x62;
            if (tm[k] < Time(h1)) {
                newest[k] = i1;
                tm[k] = Time(h1);
            }
        }
    }
    for (i2 = 0; i2 < 6; i2++) cnt[i2] = 0;
    for (i3 = 0; i3 < 5; i3++) {
        if (newest[i3] >= 0) cnt[newest[i3]]++;
    }
    for (i4 = 0; i4 < 6; i4++) {
        h4 = (FHdr*)(b->base + (i4 * 0x4000 + 0x2000));
        if (cnt[i4] == 0) {
            h4->magic = 0;
        } else if (h4->x60 == 1) {
            h4->magic = 0;
        }
    }
    for (i5 = 0, o5 = 0x1a000; i5 < 2; o5 += 0x6000, i5++) {
        h5 = (FHdr*)(b->base + o5);
        p[i5] = h5;
        if (Valid(h5) && !CrcOk(h5)) {
            p[i5]->magic = 0;
            fn_80079E70(-0x42);
            goto done;
        }
    }
    {
        FHdr* o;
        FHdr* a = p[0];
        FHdr* c = p[1];
        u32 ta = Time(a);
        u32 tc = Time(c);
        if (ta < tc) {
            o = a;
        } else {
            o = c;
            c = a;
        }
        o->magic = 0;
        if (c->x60 == 1) c->magic = 0;
    }
done:
    base = b->base;
    best = 0;
    f = 0;
    for (i6 = 0, o6 = 0x2000; i6 < 6; o6 += 0x4000, i6++) {
        h6 = (FHdr*)(base + o6);
        if (SysValid(h6) && best < Time(h6)) {
            best = Time(h6);
            f = h6;
        }
    }
    for (i7 = 0, o7 = 0x1a000; i7 < 2; i7++, o7 += 0x6000) {
        h7 = (FHdr*)(base + o7);
        if (SysValid(h7) && best < Time(h7)) {
            best = Time(h7);
            f = h7;
        }
    }
    if (mode) {
        if (f) {
            if (lbl_803EC180.seed == f->sys.seed) return;
            if (lbl_803EC180.seed == 0x0123456789ABCDEFULL) return;
        }
        fn_80079E70(-0x40);
    } else if (f) {
        fn_80105EB0(&lbl_803EC180, &f->sys);
    } else {
        SysInit(&lbl_803EC180);
        fn_80079E70(-0x42);
    }
}
void fn_80106B84(void) {
    lbl_803EC180.p30 = lbl_8037F7E0;
    SysInit(&lbl_803EC180);
    lbl_803EC180.magic = 0xFFFFFFFF;
    lbl_803EC180.ver = 0xFFFFFFFF;
    lbl_803EC180.x48 = 1;
}
}
