/* round 17: 5 words. The rect is a local aggregate initialiser {0x28, y, 0x1B8, 0x16} (the sdata2 pieces at lbl_804CF360/4/6 are its template), no kRect stand-in needed. Left: the original loads w, h, then x. */
/* near miss: fn_801B78F0, 6 words. Only the rect copy: the original loads kRect.w, .h, then .x (after the lha of x6A) and stores w, x, h, y; ours loads x, w, h. Everything else matches. Self-contained. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {

/* unit list window init. Entry: unit, model handle, weapon, cached stats for sorting */
struct R4 { u16 x, y, w, h; };
struct P2 { u16 a, b; };
struct RR { P2 pos; P2 size; };
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
};
typedef struct LView {
    u8 pad[0x30];
    void* x30;
    LPage** pages;
    LEnt* ents;
    void* tex;
    void* x40; void* x44; void* x48; void* x4C; void* x50; void* x54;
    R4 x58;
    u8 x60; u8 n; s8 x62; u8 x63; u8 x64; u8 x65; u8 x66; s8 x67;
    s16 x68, x6A;
    u8 x6C, x6D, x6E, x6F;
    u32 x70;
} LView;

extern u32 lbl_804CB700;
typedef struct LHead { u8* head; u32 a, b; } LHead;
extern LHead* lbl_804CB814;
extern char lbl_8036DEB0[];
extern u8 lbl_803C8E80[];
extern u8 lbl_803CAB38[];
extern u8 lbl_803CA870[];
extern u8 lbl_80389848[], lbl_80389B0C[], lbl_80389AE8[], lbl_80389A44[], lbl_80389A20[], lbl_803899A8[], lbl_80389984[], lbl_80389960[], lbl_8038986C[];
extern char lbl_804CA440[8], lbl_804CA798[8], lbl_804CA380[8];
static const R4 kRect = {0x28, 0, 0x1B8, 0x16};
extern char lbl_8041EC48[];
extern const char* lbl_80389528[];
extern char lbl_804CA8F0[8];
extern void* fn_800791B0(u32);
extern void* fn_80079150(u32);
extern void* fn_8028BE18(void*, void*, void*, int, int);
extern void fn_801B8B00(u32*);
extern void fn_801B7290(LView*);
extern u32* fn_80006E1C(void);
extern void* fn_800F4544(u8*, const char*);
extern u32 fn_8000BD3C(void*);
extern void fn_80006F20(u32*);
extern void fn_80083DC4(void*, int);
extern void fn_80027088(void*, u8*, int);
extern void fn_8009DBE4(u8*, LStat*, int, int);
extern void** fn_80030CF4(void*);
extern u32 fn_801107A0(void*, void*);
extern u32 fn_801107C0(void*, void*);
extern u8* fn_80060728(void*);
extern void* fn_80078CCC(u32, void*, int);
extern void* fn_8017948C(void*, int);
extern void fn_801791D8(void*, int);
extern void fn_8017918C(void*, int, int);
extern void fn_801791D0(void*, f32);
extern void* fn_80179660(void*);
extern void fn_8017980C(void*, int, int, int);
extern void fn_8017985C(void*, int);
extern void fn_80179864(void*, int);
extern void fn_80179888(void*, int);
extern void fn_80179854(void*, f32);
extern void fn_801798A8(void*, int);
extern void* fn_8017AA08(void*);
extern void fn_8017A968(void*, const char*);
extern s8 fn_80244D88(void);
extern void fn_80290DDC(char*, const char*, ...);
extern void* fn_8001D3EC(const char*, int);
extern void* fn_80177284(void*, void*);
extern void fn_800453B4(void*, int);

#define ADD(fl) do { \
    e->u = u; \
    { u32* h = fn_80006E1C(); e->h = h; h[1] = (u32)(u + 0x28); \
    h[0x11] = fn_8000BD3C(fn_800F4544(u, lbl_8036DEB0 + 0x9E)); \
    h[0] |= fl; \
    fn_80006F20(h); } \
    e++; p->n++; } while (0)

static inline LPage* PInit(LPage* g, void* vt) {
    *(void**)((u8*)g + 0x58) = vt;
    return g;
}
static inline void PCopy(LPage* g) {
    s16* q = (s16*)g;
    int i;
    for (i = 0; i < g->n21; i++) { *(s16*)((u8*)q + 0x3E) = *(s16*)((u8*)q + 0x24); q++; }
}
static inline const char* LangName(void) {
    s8 m = fn_80244D88();
    if (m >= 0) return lbl_80389528[m];
    return lbl_804CA8F0;
}
static inline void SetTitle(LView* p) {
    if (p->x62 < 0) {
        switch (p->x6C) {
        case 1: case 2: fn_8017A968(p->x50, lbl_8036DEB0 + 0xA3); break;
        case 5: fn_8017A968(p->x50, lbl_8036DEB0 + 0xB4); break;
        default: fn_8017A968(p->x50, lbl_8036DEB0 + 0xC4); break;
        }
    } else {
        switch (p->x6C) {
        case 1: case 2: fn_8017A968(p->x50, lbl_8036DEB0 + 0xD3); break;
        case 5: fn_8017A968(p->x50, lbl_8036DEB0 + 0xE4); break;
        default: fn_8017A968(p->x50, lbl_8036DEB0 + 0xF4); break;
        }
    }
}
static inline void Swp(LEnt* e, int j) { LEnt t(e[j]); e[j] = e[j+1]; e[j+1] = t; }
static inline int LCmp(LView* p, int j) {
    return p->x67 * p->pages[p->x66 / 13]->cmp(&p->ents[j], p->x66 % 13);
}
static inline int LFind(LView* p, u8* m) {
    u8* t = *(u8**)(m + 0x28);
    int i;
    int n;
    if (t == 0) return -1;
    n = p->n;
    for (i = 0; i < n; i++) {
        if (p->ents[i].u == t) return i;
    }
    return -1;
}
static inline void* NewWin(int t) {
    void* m = fn_80078CCC(100, lbl_804CA440, 0);
    if (m) m = fn_8017948C(m, t);
    return m;
}

static inline void SetR(LView* p, R4 r) {
    R4 q = { 0x28, (u16)(p->x62 * 32 + 0x68 - p->x6A), 0x1B8, 0x16 };
    p->x58 = q;
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
void fn_801B78F0(LView* p) {
    int all;
    LEnt* e;
    p->x64 = 0;
    p->x62 = 0;
    p->x63 = 0;
    p->x68 = 0;
    p->x6A = 0;
    p->x6E = 0;
    p->x6F = 8;
    p->x70 = 0;
    p->x66 = 0;
    p->x65 = 0;
    p->x67 = 1;
    p->pages = 0;
    p->ents = 0;
    p->x50 = 0;
    p->x4C = 0;
    p->x40 = 0;
    p->x44 = 0;
    p->x48 = 0;
    p->x30 = 0;
    p->tex = 0;
    switch (p->x6C) {
    case 1: case 2: case 3:
        p->x70 = lbl_804CB700 & 0xF0000;
        lbl_804CB700 &= ~0xF0000;
        break;
    }
    p->n = 0;
    e = (LEnt*)fn_8028BE18(fn_800791B0(0x1BD8), (void*)fn_801B8B00, 0, 0x1C, 0xFE);
    p->ents = e;
    switch (p->x6C) {
    case 1: {
        u32 m = 0x10000DC;
        {
        u8* nx; u8* u;
        for (u = lbl_804CB814[0].head; u != 0; u = nx) {
            nx = *(u8**)(u + 0xE8);
            if (*(u32*)(u + 0x10C) & m) continue;
            ADD(0xE021A000);
        }
        }
        {
        u8* nx; u8* u;
        for (u = lbl_804CB814[0].head; u != 0; u = nx) {
            nx = *(u8**)(u + 0xE8);
            if ((*(u32*)(u + 0x10C) & m) == 0) continue;
            ADD(0xE021A000);
        }
        }
        all = 0;
        break;
    }
    case 2: {
        {
        u8* nx; u8* u;
        for (u = lbl_804CB814[5].head; u != 0; u = nx) {
            nx = *(u8**)(u + 0xE8);
            if ((*(u32*)(u + 0x10C) & 0x400000) == 0) continue;
            ADD(0xE021A000);
        }
        }
        {
        u8* nx; u8* u;
        for (u = lbl_804CB814[5].head; u != 0; u = nx) {
            nx = *(u8**)(u + 0xE8);
            if (*(u32*)(u + 0x10C) & 0x400000) continue;
            ADD(0xE021A000);
        }
        }
        all = 0;
        break;
    }
    case 3: {
        {
        u8* nx; u8* u;
        for (u = lbl_804CB814[0].head; u != 0; u = nx) {
            nx = *(u8**)(u + 0xE8);
            ADD(0xE001A000);
        }
        }
        {
        u8* nx; u8* u;
        for (u = lbl_804CB814[5].head; u != 0; u = nx) {
            nx = *(u8**)(u + 0xE8);
            ADD(0xE001A000);
        }
        }
        all = 0;
        break;
    }
    case 4: {
        {
        u8* nx; u8* u;
        for (u = lbl_804CB814[p->x60].head; u != 0; u = nx) {
            nx = *(u8**)(u + 0xE8);
            ADD(0xE001A000);
        }
        }
        all = 0;
        break;
    }
    default: {
        {
        u8* nx; u8* u;
        for (u = lbl_804CB814[p->x60].head; u != 0; u = nx) {
            u32 f = *(u32*)(u + 0x10C);
            nx = *(u8**)(u + 0xE8);
            if ((f & 8) || (f & 0x10)) continue;
            ADD(0xE001A000);
        }
        }
        all = 1;
        break;
    }
    }
    if (p->n == 0) {
        fn_80083DC4(p, 0);
        return;
    }
    {
    e = p->ents;
    int i;
    for (i = 0; i < p->n; i++, e++) {
        void** ls;
        fn_80027088(lbl_803C8E80, e->u, -1);
        fn_8009DBE4(e->u, &e->s, 2, all);
        ls = fn_80030CF4(lbl_803C8E80);
        { u8* bs = lbl_803C8E80;
        if (ls != 0 && *ls != 0) {
            e->w = *ls;
            e->s.rmax = *ls ? (u8)fn_801107A0(*ls, bs) : 0;
            e->s.rmin = *ls ? (u8)fn_801107C0(*ls, bs) : 0;
            e->s.atk = *(s16*)(bs + 0x448);
            e->s.hit = *(u16*)(bs + 0x44E);
            e->s.avo = *(s16*)(bs + 0x450);
            e->s.crit = *(s16*)(bs + 0x454);
            e->s.cavo = *(s16*)(bs + 0x456);
        } else {
            e->w = 0;
            e->s.rmax = 0;
            e->s.rmin = 0;
            e->s.atk = 0;
            e->s.hit = 0;
            e->s.avo = *(s16*)(bs + 0x450);
            e->s.crit = 0;
            e->s.cavo = *(s16*)(bs + 0x456);
        }
        }
    }
    }
    if (p->x6C == 5) {
        LPage* g;
        p->x6D = 1;
        p->pages = (LPage**)fn_800791B0(4);
        g = (LPage*)fn_80079150(0x5C);
        if (g != 0) {
            PInit(g, lbl_80389848);
            g->a22 = 8; g->b23 = 7; g->n20 = 3;
            g->x24[0] = 0x70; g->x24[1] = 0xEA; g->x24[2] = 0x18F;
            g->n21 = 3;
            PCopy(g);
        }
        p->pages[0] = g;
        p->x66 = 0;
        p->x63 = 0;
    } else {
        LPage* g;
        p->x6D = 8;
        p->pages = (LPage**)fn_800791B0(0x20);
        g = (LPage*)fn_80079150(0x5C);
        if (g != 0) {
            PInit(g, lbl_80389B0C);
            g->a22 = 0; g->b23 = 0; g->n20 = 6;
            g->x24[0] = 0x70; g->x24[1] = 0xEA; g->x24[2] = 0x18F; g->x24[3] = 0x1B7; g->x24[4] = 0x1E4; g->x24[5] = 0x202;
            g->n21 = 6;
            PCopy(g);
        }
        p->pages[0] = g;
        g = (LPage*)fn_80079150(0x5C);
        if (g != 0) {
            PInit(g, lbl_80389AE8);
            g->a22 = 1; g->b23 = 1; g->n20 = 8;
            g->x24[0] = 0x70; g->x24[1] = 0xEA; g->x24[2] = 0x119; g->x24[3] = 0x148; g->x24[4] = 0x177; g->x24[5] = 0x1A6; g->x24[6] = 0x1D5; g->x24[7] = 0x204;
            g->n21 = 8;
            PCopy(g);
        }
        p->pages[1] = g;
        g = (LPage*)fn_80079150(0x5C);
        if (g != 0) {
            PInit(g, lbl_80389A44);
            g->a22 = 2; g->b23 = 2; g->n20 = 5;
            g->x24[0] = 0x70; g->x24[1] = 0xEA; g->x24[2] = 0x199; g->x24[3] = 0x1C9; g->x24[4] = 0x1F9;
            g->n21 = 5;
            PCopy(g);
        }
        p->pages[2] = g;
        g = (LPage*)fn_80079150(0x5C);
        if (g != 0) {
            PInit(g, lbl_80389A20);
            g->a22 = 3; g->b23 = 3; g->n20 = 7;
            g->x24[0] = 0x70; g->x24[1] = 0xEA; g->x24[2] = 0x123; g->x24[3] = 0x15C; g->x24[4] = 0x195; g->x24[5] = 0x1CE; g->x24[6] = 0x207;
            g->n21 = 7;
            PCopy(g);
        }
        p->pages[3] = g;
        g = (LPage*)fn_80079150(0x5C);
        if (g != 0) {
            PInit(g, lbl_803899A8);
            g->a22 = 4; g->b23 = 4; g->n20 = 3;
            g->x24[0] = 0x70; g->x24[1] = 0xEA; g->x24[2] = 0x18A;
            g->n21 = 3;
            PCopy(g);
        }
        p->pages[4] = g;
        g = (LPage*)fn_80079150(0x5C);
        if (g != 0) {
            PInit(g, lbl_80389984);
            g->a22 = 5; g->b23 = 5; g->n20 = 4;
            g->x24[0] = 0x70; g->x24[1] = 0xEA; g->x24[2] = 0x174; g->x24[3] = 0x1A6;
            g->n21 = 4;
            PCopy(g);
            g->x3E[3] += 0x1E;
        }
        p->pages[5] = g;
        g = (LPage*)fn_80079150(0x5C);
        if (g != 0) {
            PInit(g, lbl_80389960);
            g->a22 = 6; g->b23 = 0; g->n20 = 0xD;
            g->x24[0] = 0x70; g->x24[1] = 0xE4; g->x24[2] = 0xFF; g->x24[3] = 0x11A; g->x24[4] = 0x135; g->x24[5] = 0x150; g->x24[6] = 0x16B; g->x24[7] = 0x186; g->x24[8] = 0x1A1; g->x24[9] = 0x1BC; g->x24[10] = 0x1D7; g->x24[11] = 0x1F2; g->x24[12] = 0x20D;
            g->n21 = 0xD;
            PCopy(g);
        }
        p->pages[6] = g;
        g = (LPage*)fn_80079150(0x5C);
        if (g != 0) {
            PInit(g, lbl_8038986C);
            g->a22 = 7; g->b23 = 6; g->n20 = 3;
            g->x24[0] = 0x70; g->x24[1] = 0xEA; g->x24[2] = 0x180;
            g->n21 = 3;
            PCopy(g);
            g->n21 = 2;
        }
        p->pages[7] = g;
        {
        u8 b = fn_80060728(lbl_803CAB38)[0x22];
        p->x66 = b & 0x7F;
        if (b & 0x80) p->x67 = -1;
        }
        p->x63 = fn_80060728(lbl_803CAB38)[0x21];
    }
    p->x68 = p->x63 * 0x150;
    switch (p->x6C) {
    case 1: case 2: break;
    default: LSort(p);
    }
    {
    int k = LFind(p, fn_80060728(lbl_803CAB38));
    if (k >= 0) {
        p->x62 = k;
        if (k - p->x6A / 32 >= 8) {
            if (k == p->n - 1) p->x6A = (k - 8) * 32;
            else p->x6A = (k - 7) * 32;
        }
    }
    }
    {
    SetR(p, kRect);
    }
    p->x40 = NewWin(0);
    fn_801791D8(p->x40, 1);
    fn_8017918C(p->x40, 0x20, 0x4C);
    fn_801791D0(p->x40, 50.0f);
    p->x44 = NewWin(0);
    fn_801791D8(p->x44, 2);
    fn_8017918C(p->x44, 0x240, 0x4C);
    fn_801791D0(p->x44, 50.0f);
    {
    void* m = fn_80078CCC(0x2C, lbl_804CA798, 0);
    if (m) m = fn_80179660(m);
    p->x4C = m;
    }
    fn_8017980C(p->x4C, 0x242, 0x6C, 0x118);
    fn_8017985C(p->x4C, p->n << 5);
    fn_80179864(p->x4C, 0x120);
    fn_80179888(p->x4C, p->x6A);
    fn_80179854(p->x4C, 300.0f);
    fn_801798A8(p->x4C, 1);
    {
    void* m = fn_80078CCC(0x30, lbl_804CA380, 0);
    if (m) m = fn_8017AA08(m);
    p->x50 = m;
    }
    SetTitle(p);
    p->x48 = NewWin(2);
    fn_801791D8(p->x48, 8);
    fn_8017918C(p->x48, 0x1B8, 0x2C);
    fn_801791D0(p->x48, 50.0f);
    fn_80290DDC(lbl_8041EC48, lbl_8036DEB0 + 0x8B, LangName());
    p->tex = fn_8001D3EC(lbl_8041EC48, 0x2080);
    p->x30 = fn_80177284((void*)fn_801B7290, p);
    fn_800453B4(lbl_803CA870, 0x80);
}
}
