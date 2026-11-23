/* fn_80221050 (round 19): state step of the unit-detail screen: waits for the fade counter, then builds
   the help bar, refreshes the unit's derived stats, attaches the four panels and drops the temporary
   widget at 0x58 unless it is still busy, plays the open sound and moves to state 4. */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_8038C1C0[];
extern char lbl_80371CCC[];
extern int lbl_803CA870[];
int fn_80058718(void);
int fn_8002460C(void);
void* fn_801E5640(void*, int, int);
void fn_80083DC4(void*, int);
int fn_801237EC(int);
void fn_80126D9C(int, s16);
void fn_801E4D1C(void*, void*, int);
int fn_8021D964(void*);
void fn_80253EE4(const char*, f32);
}
class RO { public: virtual void destroy(int); int rc; };
struct WB { WF w; int a40, a44, a48, a4c; u8 a50; f32 a54; s16 a58, a5a, a5c, a5e; int a60; const char* a64; };
struct Tmp { u8 p[0x48]; int a48; };
struct Sc { u8 p[0x44]; int a44; void* a48; void* a4c; void* a50; void* a54; RO* a58; };
static inline WB* newB(void) {
    WB* b = (WB*)fn_80079150(0x68);
    if (b != NULL) {
        wfInit(&b->w, 0, 400, 0x260, 0x1c0, 0x260, 0x30, 0x78, 0x10);
        b->a40 = 0; b->a44 = 0; b->a48 = 0; b->a4c = 0;
        b->a50 = 1;
        b->a5a = 0; b->a5e = 0;
        b->w.vt = lbl_8038C1C0;
        b->a60 = 0; b->a64 = 0;
        b->a58 = 0x30; b->a5c = 0x30;
        b->a54 = 0.75f;
    }
    return b;
}
static inline void release(RO*& r) {
    RO* p = r;
    if (p != NULL) {
        if (--p->rc == 0) {
            if (p != NULL) p->destroy(1);
        }
        r = NULL;
    }
}
extern "C" void fn_80221050(Sc* s) {
    if (s->a44 > 0) {
        fn_80083DC4(s, 0xb);
    } else {
        int u = lbl_803CA870[0];
        WB* b = newB();
        int one = 1;
        b->w.id = -0x1000;
        b->a4c = one;
        b->a64 = lbl_80371CCC + 0x18;
        b->w.flags |= 0x10;
        b->a60 = 0;
        b->w.a28 = 8;
        fn_801E5448(s, b);
        if (fn_80058718() != 0 && fn_8002460C() != 0) {
            WB* h = (WB*)fn_801E5640(s, -0x1000, 0);
            if (h != NULL) h->a60 = one;
        }
        fn_80126D9C(u, fn_801237EC(u));
        ((Tmp*)s->a58)->a48 = 0;
        fn_801E5448(s, s->a54);
        fn_801E4D1C(s, s->a54, 0);
        fn_801E5448(s, s->a48);
        fn_801E4D1C(s, s->a48, 0);
        fn_801E5448(s, s->a4c);
        fn_801E4D1C(s, s->a4c, 0);
        fn_801E5448(s, s->a50);
        fn_801E4D1C(s, s->a50, 0);
        if (fn_8021D964(s->a58) == 0) {
            release(s->a58);
            fn_80253EE4(lbl_80371CCC + 0x65, 0.0f);
            fn_80083DC4(s, 4);
        }
    }
}
