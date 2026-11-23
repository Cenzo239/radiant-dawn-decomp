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
void fn_801E40B0(void*, int);
void fn_80111C24(void*, int);
void fn_8022E9A0(void*);
void fn_800D3BCC(void*, int);
class RO { public: virtual void destroy(int); int rc; };
#define REL(o, f) { RO* p = o->f; if (p != NULL) { if (--p->rc == 0 && p != NULL) p->destroy(1); o->f = NULL; } }
struct R7 { u8 p[0x44]; RO* a44; RO* a48; RO* a4c; RO* a50; RO* a54; RO* a58; RO* a5c; };
void fn_80225470(R7* o) {
    if (o != NULL) {
        REL(o, a5c)
        REL(o, a44)
        REL(o, a48)
        REL(o, a4c)
        REL(o, a50)
        REL(o, a58)
        REL(o, a54)
        fn_801E40B0(o, 0);
    }
}
extern u32 lbl_804CB878;
struct R6 { u8 p[0x40]; u8 a40[0x28]; RO* a68; RO* a6c; RO* a70; RO* a74; RO* a78; RO* a7c; };
void fn_802346C8(R6* o) {
    lbl_804CB878 &= ~0x10;
    if (o != NULL) {
        REL(o, a68)
        REL(o, a6c)
        REL(o, a70)
        REL(o, a74)
        REL(o, a78)
        REL(o, a7c)
        fn_80111C24(o->a40, -1);
        fn_801E40B0(o, 0);
    }
}
struct R3 { u8 p[0x6c]; RO* a6c; RO* a70; u8 p74[8]; RO* a7c; u8 p80[8]; u8* a88; void* a8c; };
void fn_80233BB8(R3* s) {
    WY* a = (WY*)fn_801E5640(s, 6, 0);
    WY* c;
    WY* d;
    WY* e;
    fn_801E5640(s, 0xa, 0);
    c = (WY*)fn_801E5640(s, 7, 0);
    d = (WY*)fn_801E5640(s, 9, 0);
    e = (WY*)fn_801E5640(s, 8, 0);
    mvx(s, a, a->x, -0x24, 0);
    mvx(s, c, -0x34, c->y, 0);
    if (d != NULL) mvx(s, d, 0x1a4, d->y, 0);
    mvx(s, e, 0x17e, e->y, 0);
    REL(s, a6c)
    REL(s, a70)
    REL(s, a7c)
    fn_8022E9A0(s);
    fn_8014C2AC(*(void**)(s->a88 + 8));
    fn_800D3BCC(s->a8c, 0xc);
    fn_80083DC4(s, 3);
}
}
