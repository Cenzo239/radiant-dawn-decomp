#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
class Pad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38();
    virtual u32 rep();  /* +0x3C */
    virtual void v40(); virtual void v44();
    virtual u32 held(); /* +0x48 */
};
extern Pad* lbl_804CB5B8;
typedef struct BLink {
    f32 x, y;         /* 0x00 */
    u8 next[4];       /* 0x08 */
    s8 x0C;           /* 0x0C */
    u8 type;          /* 0x0D */
    u8 pad0E[2];
    const char* help; /* 0x10 */
} BLink;
typedef struct BPage { BLink e[27]; } BPage;
typedef struct Slot { struct { u8 pad[0x1F]; u8 x1F; }* p; u8 pad[4]; } Slot;
typedef struct UMdlNode { u8 pad[8]; u16 x8; u8 padA[0xE]; u32 x18; } UMdlNode;
typedef struct UMdl { u8 pad[0x30]; UMdlNode* n; } UMdl;
typedef struct BData {
    u8 pad[4];
    int x4;
    s16 t;      /* 0x08 */
    s8 page;    /* 0x0A */
    u8 pad0B;
    int sel;    /* 0x0C */
    int dir;    /* 0x10 */
    u8 x14; u8 pad15[3];
    f32 x18, x1C;
    u8 alpha;   /* 0x20 */
    u8 pad21[3];
    f32 x;      /* 0x24 */
    f32 y;      /* 0x28 */
    Slot* items[6]; /* 0x2C */
    u8* unit;   /* 0x44 */
    void* x48;
    UMdl* x4C;
    UMdl* x50;
    UMdl* x54;
    u8 pad58[8];
    f32 x60, x64;
    UMdl* x68;
    f32 x6C, x70;
} BData;
typedef struct BProc {
    u8 pad[0x30];
    BData* d;
    int x34; u8* x38; void (*x3C)(void*); void* x40;
} BProc;
typedef struct GXColor2 { u8 r,g,b,a; } GXColor2;
extern BPage lbl_8038A038[];
extern u8 lbl_803CAB38[];
extern u8 lbl_803C8E80[];
extern u8 lbl_8041EB20[];
extern char lbl_8036E118[];
extern const int lbl_8036E0C0[4];
extern void* fn_80006A0C(void*, int);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E41C(void*, void*, int, u16);
extern void fn_8007E374(void*, void*, u16);
extern void fn_800800D4(int);
extern void fn_8008031C(f32);
extern void fn_80080348(f32, f32, f32, f32);
extern void fn_80080368(f32, f32, f32, f32);
extern void fn_80080508(GXColor2);
extern void fn_80080578(int);
extern void fn_80080690(void);
extern void fn_800806E0(void);
extern void fn_80080308(void);
extern void fn_80253EE4(const char* s, f32 v);
extern void* fn_80078CCC(u32 size, const char* tag, int arg);
extern void* memset(void* p, int c, u32 n);
extern void* fn_801246A4(void*);
extern void* fn_800C6210(void*, int);
extern void fn_80027088(void*, void*, int);
extern u8* fn_80060728(void* p);
extern UMdl* fn_800E3C04(const char*, void*);
extern void fn_800E4AD4(UMdl*, f32);
extern void fn_800E48AC(UMdl*, f32, f32, f32);
extern void fn_800E4A40(UMdl*, f32);
extern void fn_800E57B4(UMdl*, int, int);
extern BOOL fn_801A2224(void*);
extern BOOL fn_800C7F90(void);
extern void fn_80083DC4(void*, int);
extern BOOL fn_801C61F4(BData*, int);
extern void fn_801A1AC4(void*, void*, const char*, f32, f32);
extern void fn_801C63F0(BData*, BLink*);
extern void fn_801A1CFC(void*);
extern void fn_801C62D8(BData*, int);
extern void fn_801A1F64(void*, void*, f32, f32);
extern void fn_801A1DCC(void*, const char*, f32, f32);
extern const char* fn_8011A0A8(void*);
extern const char* fn_80118D1C(void*);
extern const char* fn_80118F68(void*);

extern void fn_801BC88C(void* a, int b, GXColor2 c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);

extern void fn_801C6114(BData*);
extern void fn_801BD170(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 sc);
extern void fn_801BD2EC(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h);
void fn_801BCB08(BProc* p) {
    f32 z = 0.0f;
    const char* s = lbl_8036E118;
    BData* d;
    u8 w;
    fn_80253EE4(s + 0x25, z);
    d = (BData*)fn_80078CCC(0x74, s + 0x3F, 0);
    p->d = d;
    memset(d, 0, 0x74);
    d->unit = p->x38;
    d->x4 = p->x34;
    d->t = 0;
    d->x48 = fn_800C6210(fn_801246A4(d->unit), 0);
    fn_80027088(lbl_803C8E80, d->unit, -1);
    fn_801C6114(d);
    w = 0xFF;
    d->x14 = w;
    d->x18 = 0.0f;
    d->x1C = 0.0f;
    d->page = fn_80060728(lbl_803CAB38)[0x20];
    d->alpha = w;
    d->x = 16.0f;
    d->y = 170.0f;
    d->x4C = fn_800E3C04(s, p);
    fn_800E4AD4(d->x4C, 1.0f);
    fn_800E48AC(d->x4C, 122.0f + z, 40.0f + z, 0.0f);
    d->x4C->n->x8 = 0xA9;
    d->x4C->n->x18 |= 4;
    d->x50 = fn_800E3C04(s + 10, p);
    fn_800E4AD4(d->x50, 0.05f);
    fn_800E4A40(d->x50, 90.0f);
    fn_800E48AC(d->x50, 18.0f, 287.0f, 0.0f);
    {
    u16 k = 0x96;
    d->x50->n->x8 = k;
    d->x50->n->x18 |= 0x1004;
    d->x54 = fn_800E3C04(s + 10, p);
    fn_800E4AD4(d->x54, 0.05f);
    fn_800E4A40(d->x54, -90.0f);
    fn_800E48AC(d->x54, 590.0f, 287.0f, 0.0f);
    d->x54->n->x8 = k;
    d->x54->n->x18 |= 0x1004;
    d->x68 = fn_800E3C04(s + 0x15, p);
    fn_800E57B4(d->x68, -100, 100);
    fn_800E4AD4(d->x68, 1.0f);
    d->x68->n->x8 = k;
    d->x68->n->x18 |= 4;
    }
    d->x6C = 0.0f;
    d->x70 = 128.0f;
    if (p->x3C) p->x3C(p->x40);
}

void fn_801BD070(BProc* p) {
    BData* d = p->d;
    u32 r = lbl_804CB5B8->rep();
    u32 h = lbl_804CB5B8->held();
    if (h & 0x800 || h & 0x2000) {
        fn_80083DC4(p, 0);
        fn_801A1CFC(lbl_8041EB20);
    } else if (r & 0x800008) {
        fn_801C62D8(d, 0);
    } else if (r & 0x400004) {
        fn_801C62D8(d, 1);
    } else if (r & 0x100001) {
        fn_801C62D8(d, 2);
    } else if (r & 0x200002) {
        fn_801C62D8(d, 3);
    }
}

void fn_801BCD90(BProc* p) {
    BData* d = p->d;
    u32 r = lbl_804CB5B8->rep();
    u32 h = lbl_804CB5B8->held();
    if (fn_801A2224(lbl_8041EB20) == 0) {
        if ((h & 0x800) && fn_800C7F90() == 0) {
            fn_80083DC4(p, 4);
            fn_80253EE4(lbl_8036E118 + 0x40, 0.0f);
        } else if (r & 0x200002) {
            d->x64 = 2.0f;
            fn_80083DC4(p, 2);
            d->dir = 1;
            fn_80253EE4(lbl_8036E118 + 0x50, 0.0f);
        } else if (r & 0x100001) {
            d->x60 = 2.0f;
            fn_80083DC4(p, 2);
            d->dir = -1;
            fn_80253EE4(lbl_8036E118 + 0x50, 0.0f);
        } else if (r & 0x800008) {
            fn_80083DC4(p, 3);
            d->dir = -1;
            fn_80253EE4(lbl_8036E118 + 0x6C, 0.0f);
        } else if (r & 0x400004) {
            fn_80083DC4(p, 3);
            d->dir = 1;
            fn_80253EE4(lbl_8036E118 + 0x6C, 0.0f);
        } else if ((r & 0x400) && *(int*)(d->unit + 0xF8) != 0) {
            fn_80083DC4(p, 3);
            d->dir = 0;
            fn_80253EE4(lbl_8036E118 + 0x6C, 0.0f);
        } else if (h & 0x2000) {
            int tbl[4] = {0x13, 0xC, 0xD, 0xC};
            BLink* e;
            fn_80083DC4(p, 1);
            d->sel = tbl[d->page];
            while (fn_801C61F4(d, d->sel) == 0) {
                d->sel = lbl_8038A038[d->page].e[d->sel].x0C;
            }
            e = &lbl_8038A038[d->page].e[d->sel];
            fn_801A1AC4(lbl_8041EB20, p, lbl_8036E118 + 0x8D, e->x, e->y);
            fn_801C63F0(d, e);
        }
    }
}




extern u8* fn_800CD204(int);
extern void* lbl_804CB588;
typedef struct TexH { u16 x0, x2; } TexH;
static inline void Sprite(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    u8* p = fn_800CD204(col);
    GXColor2 c;
    void* arch;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = alpha;
    arch = lbl_804CB588;
    {
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(arch, tile, c, 0x11, fl, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
    }
}
void fn_801BD170(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 sc) {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB588, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    Sprite(col, alpha, tile, fl, x, y, w * sc, h * sc);
}
void fn_801BD2EC(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    u8* p = fn_800CD204(col);
    GXColor2 c;
    void* arch;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = alpha;
    arch = lbl_804CB588;
    {
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(arch, tile, c, 0x11, fl, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
    }
}
}
