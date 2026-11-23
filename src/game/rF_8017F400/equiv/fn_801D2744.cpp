/* r19: copied from wip/fn_801D2744.cpp; `sched` level (same instructions per basic block, order differs). */
/* wip (round 19): `other` by 3 words. Everything matches except the scheduling of two `li` in the first widget
   constructor: the original loads 0x190 (y0) into r0 before the vtable store and -1 (id) into r5 after it; ours loads
   -1 into r0 first and 0x190 into r11, using one more temporary (r12 for zero). Tried: int/s16 parameters, id through
   an inline/local/u16, rect setter inlines, placement ctor. A non-volatile lbl_804CB700 is needed for the epilogue
   order (rI types.h declares it volatile). */
/* fn_801D2744: base (camp) screen setup. Copies the background name of the current chapter data into
   lbl_8041EEE0 (with the "-wide" suffix in widescreen), loads it, builds the help text box (0x68 bytes) and the
   0x40 widget kept at +0x54, and starts the BGM unless bit 4 of the global flags is set. */
#define lbl_804CB700 lbl_804CB700_vol
#include "game/rI_801DD7D4/fn_wf.h"
#undef lbl_804CB700
extern "C" { extern u32 lbl_804CB700; }
extern "C" { extern u8 lbl_8038C1C0[], lbl_8038BD90[], lbl_8038C10C[], lbl_8038C100[]; }
struct WB { WF w; int a40, a44, a48, a4c; u8 a50; f32 a54; s16 a58, a5a, a5c, a5e; int a60; const void* a64; };
static inline void wbInit(WB* b, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    wfInit(&b->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
    b->a40 = 0; b->a44 = 0; b->a48 = 0; b->a4c = 0;
    b->a50 = 1;
    b->a5a = 0; b->a5e = 0;
    b->w.vt = lbl_8038C1C0;
    b->a60 = 0; b->a64 = 0;
    b->a58 = iy1; b->a5c = iy1;
    b->a54 = 0.75f;
}
struct Scn { u8 pad0[0x40]; const char* bg; u8 pad44[0x10]; WF* x54; };
struct Chap { u8 pad0[0x94]; const char* bgName; };
extern "C" {
extern u8 lbl_803CAB38[];
extern char lbl_8041EEE0[0x80];
extern char lbl_804CA928[8]; /* "-wide" in Shift-JIS */
extern char lbl_804CA920[8]; /* "" */
extern char lbl_8036EA88[];
Chap* fn_8006074C(void*);
void* fn_80068528(Chap*);
char* fn_802910CC(char*, const char*, u32); /* strncpy */
char* fn_80291110(char*, const char*);      /* strcat */
int fn_801D09F0(void);
void fn_800D42A0(const char*);
void* fn_800D4188(const char*, void*);
void fn_800D3D00(f32, void*, int);
WB* fn_801E5640(void*, int, int);
void fn_80084F0C(void*);
void fn_80250E38(f32, f32, int);
s8 fn_8024F7EC(void* bgm);
void fn_80251838(f32, int, void*);
void fn_801D2744(Scn* s);
}
static inline void LoadBg(Scn* s, const char* name) {
    if (name != 0) {
        s->bg = name;
        void* r = fn_800D4188(name, s);
        fn_800D3D00(90.0f, r, 2);
        fn_800D3D00(89.9f, fn_800D4188(lbl_8036EA88, r), 2);
    }
}

void fn_801D2744(Scn* s) {
    fn_802910CC(lbl_8041EEE0, fn_8006074C(lbl_803CAB38)->bgName, 0x7f);
    lbl_8041EEE0[0x7f] = 0;
    if (fn_801D09F0()) {
        fn_80291110(lbl_8041EEE0, lbl_804CA928);
    }
    if (s->bg != 0) {
        fn_800D42A0(s->bg);
    }
    LoadBg(s, lbl_8041EEE0);
    WB* b = (WB*)fn_80079150(0x68);
    if (b != 0) {
        wbInit(b, 0, 0x190, 0x260, 0x1c0, 0x260, 0x30, 0x78, 0x10);
    }
    b->w.id = -0x1000;
    b->a4c = 1;
    b->a64 = lbl_804CA920;
    b->w.flags |= 0x10;
    b->a60 = 0;
    b->w.a28 = 8;
    fn_801E5448(s, b);
    WB* h = fn_801E5640(s, -0x1000, 0);
    if (h != 0) {
        h->a64 = lbl_8038C10C;
    }
    lbl_804CB700 &= ~1;
    fn_80084F0C(lbl_8038C100);
    WF* p = (WF*)fn_80079150(0x40);
    if (p != 0) {
        wfInit(p, 0x1ae, 0x24, 0x260, 0x38, 0xb2, 0x14, 0x320, 0x10);
        p->vt = lbl_8038BD90;
    }
    s->x54 = p;
    if (p != 0) {
        p->rc++;
    }
    s->x54->id = 0;
    s->x54->a28 = 0;
    fn_801E5448(s, s->x54);
    if (!(lbl_804CB700 & 0x10)) {
        fn_80250E38(0.0f, 0.0f, 6);
        void* m = fn_80068528(fn_8006074C(lbl_803CAB38));
        if (fn_8024F7EC(m)) {
            fn_80251838(0.0f, 0, m);
        }
    }
    lbl_804CB700 |= 0xF0000;
}
