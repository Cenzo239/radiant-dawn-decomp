#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

/* object with its vptr at +0x28 */
class VWin {
public:
    u8 pad[0x28];
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void destroy(int del); /* vtable +0x14 */
};

typedef struct TGlobal {
    void* res0; /* 0x0 */
    void* res4; /* 0x4 */
    void* res8; /* 0x8 */
    u8 padc[0x94 - 0xC];
    VWin* win;  /* 0x94 */
} TGlobal;

typedef struct TProc {
    u8 pad[0x30];
    TGlobal* g; /* 0x30 */
} TProc;

typedef struct TDraw {
    u8 pad[0x338];
    u8 alpha;  /* 0x338 */
    u8 pad339[0x340 - 0x339];
    s16 x340;  /* 0x340 */
} TDraw;

extern TGlobal* lbl_804CB94C;
extern TProc* lbl_804CB948;
extern TDraw* lbl_804CB964;
extern u8 lbl_80388D50[];
extern const char lbl_8036D10C[];
extern void fn_80263A80(void);
extern void fn_80006A2C(void* handle);
extern void fn_80078E24(void* p);
extern void* fn_80078CCC(u32 size, const char* tag, int arg);
extern void* fn_80081194(void* cls, void* parent);
extern void fn_800217CC(int x);
extern void fn_80021808(int a, int b, int c, int d, int e);
extern void fn_8001A4DC(void* p);
extern int fn_8017F990(int a, int b);
extern double fn_80295940(double x); /* sin */
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E7DC(int a);
extern void fn_8007E4E4(f32 x, f32 y, f32 z, f32 w);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int b);
#else
extern void fn_8007E174(int a, int b);
#endif
extern void fn_800800D4(int x);
extern void fn_80080388(f32 x0, f32 y0, f32 x1, f32 y1);
extern void fn_800804D4(int r, int g, int b, int a);
extern void fn_80080308(void);
extern void fn_801A4744(int a, f32 x, f32 y);

void fn_801A3068(void)
{
    fn_80263A80();
    if (lbl_804CB94C->res4 != NULL) {
        fn_80006A2C(&lbl_804CB94C->res4);
        lbl_804CB94C->res4 = NULL;
    }
    if (lbl_804CB94C->res8 != NULL) {
        fn_80006A2C(&lbl_804CB94C->res8);
        lbl_804CB94C->res8 = NULL;
    }
    fn_80006A2C(lbl_804CB94C);
    if (lbl_804CB94C->win != NULL) {
        lbl_804CB94C->win->destroy(1);
    }
    fn_80078E24(lbl_804CB94C);
    lbl_804CB94C = NULL;
}

void fn_801A3F9C(void* parent)
{
    lbl_804CB948 = (TProc*)fn_80081194(lbl_80388D50, parent);
    lbl_804CB948->g = (TGlobal*)fn_80078CCC(0x98, lbl_8036D10C + 0xED, 0);
    lbl_804CB94C = lbl_804CB948->g;
}

void fn_801A3FF8(void* p)
{
    fn_800217CC(0);
    fn_80021808(6, 0x80, 1, 0, 0);
    fn_8001A4DC(p);
    fn_800217CC(1);
    fn_80021808(7, 0, 1, 7, 0);
}

void fn_801A4614(void)
{
    lbl_804CB964->x340 = 126.0f * (f32)fn_80295940(3.141592f * (2.0f * fn_8017F990(0, 1000)) / 1000.0f) + 128.0f;
    fn_8007E154();
    fn_8007E7DC(lbl_804CB964->alpha);
    fn_8007E4E4(0.0f, 0.0f, 300.0f, 1.0f);
    fn_8007E164();
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(0.0f, 0.0f, 608.0f, 480.0f);
    fn_800804D4(0, 0, 0, 0x80);
    fn_80080308();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 150.0f, 1.0f);
    fn_8007E164();
    fn_801A4744(0xFF, 124.0f, 149.0f);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

}
