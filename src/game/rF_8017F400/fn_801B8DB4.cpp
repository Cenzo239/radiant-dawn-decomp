#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {

/* unit list window: input handling. Same layout as fn_801B78F0. */
struct W2 { u32 a, b; };
struct LStat { W2 a; u16 hit; s8 atk; s8 avo; s8 crit; s8 cavo; u8 rmax; u8 rmin; };
struct LEnt { u8* u; u32* h; void* w; LStat s;
 LEnt() {}
 LEnt(const LEnt& o) { u = o.u; h = o.h; w = o.w; s = o.s; }
 LEnt& operator=(const LEnt& o) { u = o.u; h = o.h; w = o.w; s = o.s; return *this; }
};
class LPage {
public:
    u8 pad[0x20];
    u8 n20; u8 n21; u8 a22; u8 b23;
    s16 x24[13];
    s16 x3E[13];
    virtual void v08();
    virtual int cmp(LEnt* e, int col);
    virtual const char* help(int k);
    virtual void v14();
};
struct LView;
typedef int (*LCb)(LView*, u8*);
typedef struct LView {
    u8 pad[0x30];
    void* x30;
    LPage** pages;
    LEnt* ents;
    void* tex;
    void* x40; void* x44; void* x48; void* x4C; void* x50; LCb cb;
    s16 x58, x5A, x5C, x5E;
    u8 x60; u8 n; s8 x62; u8 x63; u8 x64; s8 x65; u8 x66; s8 x67;
    s16 x68, x6A;
    u8 x6C, x6D, x6E, x6F;
    u32 x70;
} LView;
class LWin { public: u8 pad[0x28]; virtual void v08(); virtual void v0C(); virtual void v10(); virtual void destroy(int); };
class Pad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30();
    virtual u32 trig(); /* +0x34 */
    virtual void v38();
    virtual u32 rep();  /* +0x3C */
    virtual void v40();
    virtual u32 rep2(); /* +0x44 */
    virtual u32 held(); /* +0x48 */
};
extern Pad* lbl_804CB5B8;
extern u32 lbl_804CB700;
extern char lbl_8036DEB0[];
extern u8 lbl_803CAB38[];
extern u32 lbl_8041EB20[];
extern void fn_80253EE4(const char* s, f32 v);
extern void fn_80083DC4(void* p, int r);
extern void fn_80083B78(void* p);
extern void fn_80081A90(void* p);
extern void fn_8017A968(void* p, const char* s);
extern void fn_80179888(void* p, int a);
extern f32 fn_8001EBC8(int m, f32 a, f32 b, f32 c, f32 d);
extern int fn_801B76F8(LView* p);
extern void fn_801791E0(void* p);
extern void fn_8005874C(LView* p);
extern void fn_80024640(LView* p);
extern void fn_800FAFF0(u8* u, int a);
extern int fn_801A2224(void* h);
extern void fn_801A1CFC(void* h);
extern void fn_801A1AC4(void* h, void* p, const char* s, f32 x, f32 y);
extern void fn_801A1DCC(void* h, const char* s, f32 x, f32 y);
extern u8* fn_80060728(void* p);
extern void fn_80079210(void* p);
extern void fn_80079474(void* p);
extern void fn_80006EE0(void* p);
extern void fn_8017AB5C(void* p, int a);
extern void fn_801795E8(void* p, int a);
extern void fn_8001D424(void* p);

#define SFX(off) fn_80253EE4(lbl_8036DEB0 + (off), 0.0f)
static inline void SlideUp(LView* p) {
    p->x64++;
    p->x68 = fn_8001EBC8(2, (p->x63 + 1) * 0x150, p->x63 * 0x150, 16.0f, p->x64);
    if (p->x64 == 16) {
        p->x64 = 0;
        if (p->x62 < 0) {
            fn_80083DC4(p, 6);
        } else {
            fn_80083DC4(p, 1);
        }
    }
}
static inline void SlideDn(LView* p) {
    p->x64++;
    p->x68 = fn_8001EBC8(2, (p->x63 - 1) * 0x150, p->x63 * 0x150, 16.0f, p->x64);
    if (p->x64 == 16) {
        p->x64 = 0;
        if (p->x62 < 0) {
            fn_80083DC4(p, 6);
        } else {
            fn_80083DC4(p, 1);
        }
    }
}
static inline BOOL NextPage(LView* p) {
    int cur = p->x63;
    if (cur == p->x6D - 1) {
        if (lbl_804CB5B8->held() & 0x200002) p->x63 = 0;
    } else {
        if (lbl_804CB5B8->rep() & 0x200002) p->x63 = p->x63 + 1;
    }
    if (p->x63 == cur) return 0;
    p->x65 = 0;
    p->x64 = 0;
    fn_801791E0(p->x44);
    fn_80083DC4(p, 5);
    SFX(0x6F);
    return 1;
}

void fn_801B8DB4(LView* p) {
    u32 held = lbl_804CB5B8->held();
    u32 rep = lbl_804CB5B8->rep();
    if (lbl_804CB5B8->trig() & 0x1000) {
        p->x6F = 0x10;
        rep = lbl_804CB5B8->rep2();
    } else {
        p->x6F = 8;
    }
    if (held & 0x4000) {
        switch (p->x6C) {
        case 1:
            fn_8005874C(p);
            fn_8017A968(p->x50, lbl_8036DEB0 + 0x103);
            fn_80083DC4(p, 8);
            break;
        case 2:
            fn_80024640(p);
            fn_8017A968(p->x50, lbl_8036DEB0 + 0x103);
            fn_80083DC4(p, 8);
            break;
        }
        return;
    }
    if (held & 0x2000) {
        fn_80083DC4(p, 7);
        return;
    }
    if (fn_801B76F8(p)) {
        SlideUp(p);
        return;
    }
    if (NextPage(p)) {
        SlideDn(p);
        return;
    }
    if (rep & 0x800008) {
        if (p->x62 == 0) {
            if (held & 0x800008) {
                fn_80083DC4(p, 6);
                SFX(0x114);
            }
        } else {
            p->x62--;
            SFX(0x114);
            if (p->x62 != 0 && p->x62 - p->x6A / 32 == 0) {
                p->x6A -= p->x6F;
                fn_80179888(p->x4C, p->x6A);
                fn_80083DC4(p, 2);
            }
        }
    } else if (rep & 0x400004) {
        if (p->x62 == p->n - 1) {
            if (held & 0x400004) {
                p->x62 = 0;
                p->x6A = 0;
                fn_80179888(p->x4C, 0);
                SFX(0x114);
            }
        } else {
            p->x62++;
            SFX(0x114);
            if (p->x62 != p->n - 1 && p->x62 - p->x6A / 32 == 8) {
                p->x6A += p->x6F;
                fn_80179888(p->x4C, p->x6A);
                fn_80083DC4(p, 3);
            }
        }
    } else if (held & 0x800) {
        SFX(0x135);
        fn_80083DC4(p, 0);
    } else if (held & 0x400) {
        u8* u = p->ents[p->x62].u;
        if (p->cb != 0) {
            if (p->cb(p, u)) SFX(0x145);
            else SFX(0x155);
        } else {
            SFX(0x145);
            fn_800FAFF0(u, 1);
            fn_80083DC4(p, 0);
        }
    }
}

static inline int LCmp(LView* p, int j) {
    return p->x67 * p->pages[p->x66 / 13]->cmp(&p->ents[j], p->x66 % 13);
}
static inline void LSort(LView* p) {
        int i;
        for (i = 0; i < p->n; i++) {
            int j;
            for (j = 0; j < p->n - 1 - i; j++) {
                int a = LCmp(p, j + 1);
                if (LCmp(p, j) < a) {
                    LEnt t(p->ents[j]);
                    p->ents[j] = p->ents[j + 1];
                    p->ents[j + 1] = t;
                }
            }
        }
}
static inline void HelpMove(LView* p) {
    if (fn_801A2224(lbl_8041EB20)) {
        LPage* g = p->pages[p->x63];
        s16 x = g->x3E[p->x65];
        const char* s = g->help(p->x65);
        fn_801A1DCC(lbl_8041EB20, s, x, 64.0f);
    }
}
void fn_801B9454(LView* p) {
    u32 held = lbl_804CB5B8->held();
    u32 rep = lbl_804CB5B8->rep();
    if (held & 0x2000) {
        if (fn_801A2224(lbl_8041EB20) == 0) {
            LPage* g = p->pages[p->x63];
            s16 x = g->x3E[p->x65];
            const char* s = g->help(p->x65);
            fn_801A1AC4(lbl_8041EB20, p, s, x, 64.0f);
            lbl_8041EB20[0] |= 2;
        } else {
            fn_801A1CFC(lbl_8041EB20);
        }
    }
    if (held & 0x400004) {
        p->x62 = 0;
        SFX(0x114);
        fn_801A1CFC(lbl_8041EB20);
        fn_80083B78(p);
    } else if (held & 0x800008) {
        u8 n = p->n;
        p->x62 = n - 1;
        if (n > 9) p->x6A = (n - 9) * 32;
        else p->x6A = 0;
        fn_80179888(p->x4C, p->x6A);
        SFX(0x114);
        fn_801A1CFC(lbl_8041EB20);
        fn_80083B78(p);
    } else if (rep & 0x100001) {
        if (p->x65 == 0) {
            if (fn_801B76F8(p)) SlideUp(p);
        } else {
            p->x65--;
            SFX(0x163);
        }
        HelpMove(p);
    } else if (rep & 0x200002) {
        if (p->x65 == p->pages[p->x63]->n21 - 1) {
            if (NextPage(p)) SlideDn(p);
        } else {
            p->x65++;
            SFX(0x163);
        }
        HelpMove(p);
    } else if (held & 0x400) {
        int k = p->x65 + p->x63 * 13;
        if (p->x66 == k) {
            u8 t = p->x67;
            p->x67 = t - t * 2;
        } else {
            p->x66 = k;
            p->x67 = 1;
        }
        LSort(p);
        SFX(0x17F);
    } else if (held & 0x800) {
        if (fn_801A2224(lbl_8041EB20)) fn_801A1CFC(lbl_8041EB20);
        else fn_80083DC4(p, 0);
    }
}

static inline void Set21(u8 v) { fn_80060728(lbl_803CAB38)[0x21] = v; }
static inline void Set28(u8* v) { *(u8**)(fn_80060728(lbl_803CAB38) + 0x28) = v; }
void fn_801B9CEC(LView* p) {
    switch (p->x6C) {
    case 1: case 2: case 3:
        lbl_804CB700 |= p->x70;
        break;
    }
    if (p->ents != 0 && p->x6C != 5) {
        if (p->x62 < 0) {
            u8* m = fn_80060728(lbl_803CAB38);
            *(u32*)(m + 0x28) = 0;
        } else {
            Set28(p->ents[p->x62].u);
        }
        Set21(p->x63);
        u8 b = p->x66;
        if (p->x67 < 0) b |= 0x80;
        fn_80060728(lbl_803CAB38)[0x22] = b;
    }
    if (p->pages != 0) {
        int i;
        for (i = 0; i < p->x6D; i++) {
            if (p->pages[i] != 0) {
                fn_80079210(p->pages[i]);
                p->pages[i] = 0;
            }
        }
        fn_80079474(p->pages);
    }
    if (p->ents != 0) {
        int i;
        for (i = 0; i < p->n; i++) {
            fn_80006EE0(p->ents[i].h);
        }
        if (p->ents != 0) fn_80079474((u8*)p->ents - 0x10);
    }
    if (p->x50 != 0) {
        fn_8017AB5C(p->x50, 1);
        p->x50 = 0;
    }
    if (p->x4C != 0) {
        if (p->x4C != 0) ((LWin*)p->x4C)->destroy(1);
        p->x4C = 0;
    }
    if (p->x40 != 0) { fn_801795E8(p->x40, 1); p->x40 = 0; }
    if (p->x44 != 0) { fn_801795E8(p->x44, 1); p->x44 = 0; }
    if (p->x48 != 0) { fn_801795E8(p->x48, 1); p->x48 = 0; }
    fn_80081A90(p->x30);
    fn_8001D424(p->tex);
}
}
