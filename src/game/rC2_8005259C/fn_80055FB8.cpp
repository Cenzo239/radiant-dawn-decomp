/* Battle-preview style commands: both build two descriptors on the stack and call fn_800269E4 inside a guard. */
#include "game/rC2_8005259C/base.h"
struct AUnit { u8 pad[0x102]; s8 x; s8 y; };
struct Ctx { AUnit* p0; u8 pad4[8]; u8 bc; u8 pad[4]; s8 b11; s8 b12; u8 p13[3]; s8 b16; u8 p17; int x18; int x1c; int x20; };
struct SubU { u8 pad[0x44a]; s16 h44a; };
struct Big { u8 pad[0x448]; s16 h448; u8 p[0x4a0 - 0x44a]; SubU sub; };
struct Desc1 { AUnit* u; s8 x; s8 y; u8 z; u8 k; int w; u8 m; };
struct Desc2 { AUnit* u; s8 x; s8 y; s8 z; u8 k; void* g; u8 m; };
struct Gd { u8 pad[0x28]; };
struct Lv { u8 pad[4]; int x4; };
extern "C" {
extern Ctx lbl_803CA870;
extern Big lbl_803C8E80;
extern u8 lbl_803E7320[];
extern const int lbl_804CA348;
Lv* fn_800CFD3C(void*);
AUnit* fn_800CFB0C(Lv* c);
void* fn_80030CBC(Big*);
void fn_80111B64(Gd*, void*);
void fn_80111C24(Gd*, int);
u8 fn_80127520(AUnit*);
void fn_800269E4(Big*, Desc2*, Desc1*);
void fn_8002742C(Big*, int);
s16 fn_801237EC(SubU*);
void fn_8002BDA0(Big*, s16);
#if TARGET_PC
FE10_PROTO void fn_800E9530(void*, p32arg);
#else
void fn_800E9530(void*, int);
#endif
void fn_8002C170(Big*);
u8 fn_80120928(AUnit*, AUnit*);
int fn_80089D68(int);
int fn_80121DEC(AUnit*);
void fn_80108948(void*, SubU*, int);
void fn_80108A20(void*, SubU*, int);
void fn_8002C06C(Big*, int);
}
static inline const int& minR(const int& a, const int& b) { return a < b ? a : b; }
static inline const int& maxR(const int& a, const int& b) { return a < b ? b : a; }

static inline void fire(AUnit* u, AUnit* a0, Gd* g) {
    Desc1 d1 = {u, u->x, u->y, fn_80127520(u), 1, 0, 1};
    Desc2 d2 = {a0, lbl_803CA870.b11, lbl_803CA870.b12, -1, 0, g, 1};
    fn_800269E4(&lbl_803C8E80, &d2, &d1);
}


extern "C" void fn_80055FB8(void) {
    Gd g;
    AUnit* a0;
    AUnit* u;
    int k;
    Lv* c = fn_800CFD3C(lbl_803E7320);
    a0 = lbl_803CA870.p0;
    u = fn_800CFB0C(c);
    fn_80111B64(&g, fn_80030CBC(&lbl_803C8E80));
    fire(u, a0, &g);
    fn_8002C170(&lbl_803C8E80);
    {
        int b = lbl_803CA870.x18;
        SubU* s = &lbl_803C8E80.sub;
        int c = fn_80120928(a0, u);
        int t = c + b;
        if (t > 0x64) t = 0x64;
        if (t < 0) t = 0;
        k = 0;
        if (fn_80089D68(t) && !fn_80121DEC(u)) {
            k = 1;
        }
        if (k) {
            switch (lbl_803CA870.bc) {
            case 0x5b:
            case 0x5d:
                fn_80108948((u8*)s + 0x110, s, 5);
                break;
            case 0x5c:
                fn_80108A20((u8*)s + 0x110, s, 5);
                break;
            default:
                fn_80111C24(&g, -1);
                return;
            }
        }
    }
    fn_8002C06C(&lbl_803C8E80, k);
    fn_80111C24(&g, -1);
}
