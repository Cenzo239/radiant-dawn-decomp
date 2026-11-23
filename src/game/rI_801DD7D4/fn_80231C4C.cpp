#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
void fn_80079210(void*);
void* fn_801E5640(void*, int, int);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_801E5734(void*, void*);
void fn_8014C2AC(void*);
void fn_80253EE4(const char*, f32);
void fn_801E495C(void*, void*, void*, int);
void fn_801E518C(void*, void*, int, f32);
void fn_801E4F50(void*, void*, int);
extern VO0N* lbl_804CB5B8;
extern u8 lbl_803CA870[0x130];
extern u8 lbl_803CAB38[0x988];
extern char lbl_80372600[];
struct XY { s16 x, y; };
struct Wi { u8 p[0x40]; const char* a40; u8 p44[0x20]; const char* a64; };
struct WY { u8 p[0xa]; s16 x, y; };
struct Sm { u8 p[0x88]; u8* a88; };
static inline void mvx(void* s, WY* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }
static inline void setHelpV(void* s, const char* str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
#define SL12 virtual int s08(); virtual int s0C(); virtual int s10(); virtual int s14(); virtual int s18(); virtual int s1C(); virtual int s20(); virtual int s24(); virtual int s28(); virtual int s2C(); virtual int s30(); virtual int s34();
class V38 { public: SL12 virtual void v38(int); };
class V382 { public: SL12 virtual void v38(int, int); };
void fn_801E5448(void*, void*);
void fn_801E459C(void*, void*, void*, int);
void* fn_80079150(int);
struct WF { void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26; s16 a28; u8 p2a[2]; f32 sx, sy, sz; int flags; int a3c; };
extern u8 lbl_8038CB1C[];
static inline void wfInit(WF* w, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    w->rc = 0;
    w->vt = lbl_8038CB1C;
    w->id = -1;
    w->x0 = x0; w->y0 = y0; w->x1 = x1; w->y1 = y1;
    w->ix0 = 0; w->iy0 = 0; w->ix1 = ix1; w->iy1 = iy1;
    w->a1a = 0; w->a1c = 0; w->tx = 0; w->ty = 0;
    w->c[0] = 0xff; w->c[1] = 0xff; w->c[2] = 0xff; w->c[3] = 0xff;
    w->a26 = a26; w->a28 = 0;
    w->sx = 1.0f; w->sy = 1.0f; w->sz = 1.0f;
    w->flags = fl; w->a3c = 0;
}

static inline void mv(void* s, WY* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
void* fn_802167C8(void*, int, int, int, int, int, int);
struct S2 { u8 p[0x68]; void* a68; void* a6c; void* a70; WF* a74; WF* a78; u8 p7c[4]; u8 a80; u8 p81[3]; f32 a84; u8* a88; void* a8c; };
extern u8 lbl_8038FA38[];
extern u8 lbl_8038E160[];
extern char lbl_80372600_[];
void fn_8014BED4(void*, void*);
void* fn_800D4188(const char*, void*);
void fn_800D3BCC(void*, int);
struct G3 { WF w; int a40; int a44; };
extern u8 lbl_8038C1C0[];
extern u8 lbl_8038E070[];
extern char lbl_80390B3C[];
void* fn_800D0864(const char*);
int fn_801E7204(int);
int fn_801E7218(int);
#if TARGET_PC
FE10_PROTO void * fn_8010B228(const char*);
#else
int fn_8010B228(const char*);
#endif
struct WB { WF w; int a40, a44, a48, a4c; u8 a50; f32 a54; s16 a58, a5a, a5c, a5e; int a60; void* a64; };
struct G4 { WF w; void* a40; int a44; };
class RO { public: virtual void destroy(int); int rc; };
void fn_8021C638(void*, int);
void* fn_80081050(void*, void*);
extern u8 lbl_80390A38[];
void* fn_801E2204(void*, void*, void*);
struct LC { u8 p[0x4c]; WF* s[7]; s16 a6a_; };
struct RL { u8 p[0x30]; u8 a30; u8 a31; s8 a32; u8 p33; void* a34; void* a38; };
void fn_80231C4C(void* s) {
    WF* w;
    u8* l = (u8*)fn_801E5640(s, 0xc, 0);
    XY p;
    w = *(WF**)(l + *(s16*)(l + 0x6a) * 4 + 0x4c);
    fn_801E2204(l, &p, &w->x0);
    w->id = 0xd;
    w->a28 = 0x10;
    w->a26 = 0x1c2;
    w->sy = 1.0f;
    w->sz = 1.0f;
    w->sx = 1.0f;
    {
        s16 x = p.x;
        w->x1 = x + (s16)(w->x1 - w->x0);
        w->x0 = x;
    }
    {
        s16 y = p.y;
        w->y1 = y + (s16)(w->y1 - w->y0);
        w->y0 = y;
    }
    if (w != NULL) w->rc++;
    fn_8021C638(l, *(s16*)(l + 0x6a));
    fn_801E5448(s, w);
    if (w != NULL) {
        if (--w->rc == 0 && w != NULL) ((RO*)w)->destroy(1);
    }
    {
        s8 k = *(s16*)(l + 0x6a);
        RL* r = (RL*)fn_80081050(lbl_80390A38, s);
        r->a30 = 1;
        r->a31 = 0;
        r->a32 = k;
        r->a34 = s;
        r->a38 = l;
        if (r->a31 == k) r->a31++;
    }
}
}
