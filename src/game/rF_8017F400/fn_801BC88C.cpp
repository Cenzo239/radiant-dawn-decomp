/* fn_801BC88C (0x1D0): exact (round m7). Textured quad with flip flags.
 * Lever: the tile parameter declared `u16` (s16 works too) makes the prologue copy r4 before r3. Callers in
 * matched files declare it `int` and pass it unextended, so keep `int` in shared prototypes. */
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



extern void fn_801C6114(BData*);
extern void fn_801BD170(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 sc);
extern void fn_801BD2EC(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h);









extern u8* fn_800CD204(int);
extern void* lbl_804CB588;
typedef struct TexH { u16 x0, x2; } TexH;
void fn_801BC88C(void* a, u16 b, GXColor2 c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8) {
    void** t = (void**)fn_80006A0C(a, b);
    if (fl & 1) { f32 s = f5; f5 = f7; f7 = s; }
    if (fl & 2) { f32 s = f6; f6 = f8; f8 = s; }
    fn_8007E154();
    if (t[1] != 0) {
        fn_8007E41C(a, (void*)b, 0, (u16)d);
    } else {
        fn_8007E374(a, (void*)b, (u16)d);
    }
    fn_8007E164();
    fn_800800D4(2);
    fn_8008031C(0.0f);
    fn_80080348(f1, f2, f5, f6);
    fn_80080368(f3, f4, f7, f8);
    fn_80080508(c);
    fn_80080578(0);
    if (fl & 4) fn_80080690();
    if (fl & 8) fn_800806E0();
    fn_80080308();
}




}
