/* symcheck: r21 review, flag was an artefact. fn_80150F0C: (a) `slots`: colour temporary and its two copies in
   permuted slots, same bytes. See docs/SCHED_REVIEW.md. */
/* Round 20, functionally equal (check_regs.py: slots): fn_80150F0C. Self-contained. fn_80150AC0.cpp with exported bodies removed plus the fragment from wip/near.cpp, completed: W1 (colour from four bytes) written out, the window colours lbl_804CA7A0..A6 declared as six separate u8 globals (the original loads each through its own sda21 symbol), fn_802291A8 taking its two colours by value. Differs only in the stack slots of the first colour pair (temporaries at 0x8/0xc and argument copies at 0x14/0x10 here; 0x14/0xc and 0x10/0x8 in the original). kC0/kC1 are the constants at lbl_804CE2BC (.sdata2, not reference-checked). */
/* Talk window: text lines, fades, page advance. 80150AC0..801520C0. */
#include "game/rM_8014C9F8/win.h"
#pragma auto_inline off

extern "C" {

extern void* fn_80079150(int);
extern void fn_80079210(void*);
extern void fn_80079474(void*);
extern void fn_80081194b(void*);
extern u8 lbl_80386DF0[];
extern u8 lbl_80386E00[];
extern u8 lbl_80386E1C[];
extern u8 lbl_80386E38[];
extern u8 lbl_80386E50[];
extern u8 lbl_80386E68[];
extern u8 lbl_80386E80[];
extern u8 lbl_803CAB38[];
extern char lbl_8036A080[];
extern void* lbl_804CB8A8;
extern Proc* fn_800811E4(void*, void*);
extern u32* fn_80060728(void*);
extern void* fn_800D4188(void*, void*);
extern void fn_800D3BCC(void*, int);
extern void fn_800D3C90(void*, int);
extern void fn_80253EE4(char*, f32);
extern void fn_803080DC(int, int, int, int);
extern void fn_801D0940(int, int, int, int);
extern void fn_80150790(void*);
extern void DCFlushRange(void*, u32);

class Pad5B8 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual u32 v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
    virtual u32 v48();
};
extern Pad5B8* lbl_804CB5B8;
void fn_80150AC0(Win* w, s16 x, s16 y);

void fn_80150ACC(Win* w, s8 v);

void fn_80150AD4(Win* w, s8 v);

void fn_80150ADC(Win* w, s16 v);

void fn_80150AE4(Win* w, u8 v);

void fn_80150AEC(Win* w, void* o, s16 x, s16 y);

void fn_80150AFC(Win* w, int x, int y);

void fn_80150B18(Win* w, u8 v);

void fn_80150B4C(Win* w);

Win* fn_80150BE8(Win* w);

void fn_80150C68(Win* w);

void fn_80151328(void* unused, s16* r);

void fn_80151360(Win* w, u8 c);

void fn_801513B0(Win* w);

BOOL fn_801513E4(Win* w);

void fn_80151414(void* p);

void fn_80151424(WinFade* f);


static inline void WinClear(Win* w) {
    int i;
    for (i = 0; i < w->rows; i++) {
        if (w->lines[i] != NULL) {
            w->lines[i]->clear();
        }
    }
    w->head = 0;
    w->tail = 0;
    w->reveal = 0;
}
void fn_801514E8(WinFade* f);

void fn_80151548(Win* w, void* parent);


static inline void WinNext(Win* w) {
    TLine* l = w->lines[w->head % w->rows];
    l->clear();
    w->head++;
    w->reveal = 0;
}
void fn_80151600(WinFade* f);

void fn_80151818(Win* w, void* parent);

void fn_801518C4(Win* w, void* parent);

void fn_801519B8(WinFade* f);

void fn_80151AA0(Win* w, void* parent, int arg);

void fn_80151B94(WinFade* f);

void fn_80151CC4(Win* w, void* parent);

void fn_80151D28(Win* w, void* parent);

void fn_80151D94(Proc* p);

void fn_80151EC4(Proc* p);

void fn_80151F08(void* a, void* parent, s16 t);





struct Dissolve : Proc {
    u8* tex;    /* 0x30 */
    s16* order; /* 0x34 */
    int left;   /* 0x38 */
    int pos;    /* 0x3C */
};

#pragma push
#pragma use_lmw_stmw on

void fn_80151F4C(Dissolve* d);


#pragma pop

void fn_80152080(Dissolve* d);


extern u8 lbl_80386E8C[];
extern void* fn_800791B0(int);
extern int fn_80089C88(int);




extern void fn_80021BF4(int);
extern void fn_80022158(int, int, int);
extern void fn_80021C34(int);
extern void fn_80312D2C(f32, f32, f32, f32, f32, f32, f32, f32, void*);
extern void fn_80307F10(void*, int, int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021E20(int, int, int, int, int);
extern void fn_80021D18(int, int, int, int, int, int);
extern void fn_80021E8C(int, int, int, int, int);
extern void fn_80021D9C(int, int, int, int, int, int);
extern void fn_80306FD8(int, int, int, int, int);
extern void fn_80305A40(void*, void*, int, int, int, int, int, int);
extern void fn_80305C94(void*, f32, f32, f32, int, int, int, int, int);
extern void fn_80022254(void*, int);
void fn_80150CC4(u32 flag);


extern void* fn_800C409C(int);
extern u8 fn_8014C83C(void);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E84C(int);
extern void fn_8007E7DC(u8);
extern void fn_8007E7E8(u8);
extern void fn_8007E174(void*, int);
extern void fn_8007E74C(void*, void*);
extern void fn_8007E780(void*, void*);
extern void fn_802291A8(int, int, int, Color, Color);
extern void fn_800800D4(int);
extern void fn_80080ABC(int, f32);
extern void fn_80080B70(int, f32);
extern void fn_80080B00(int, void*, f32);
extern void* fn_800CD204(int);
extern int fn_8007E9BC(int);
extern void fn_80080330(f32, f32);
extern void fn_800804D4(u8, u8, u8, u8);
extern void fn_80080C24(const char*);
extern void fn_80080308(void);
extern void fn_8007E7F4(void);
extern u8 lbl_804CA7A0, lbl_804CA7A1, lbl_804CA7A2, lbl_804CA7A4, lbl_804CA7A5, lbl_804CA7A6;

static inline Color WA(u8 r, u8 g, u8 b, u8 a) {
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return c;
}

static inline void Rect4(s16* r, s16 x, s16 y, s16 x2, s16 y2) {
    r[0] = x;
    r[1] = y;
    r[2] = x2;
    r[3] = y2;
}



}

#pragma use_lmw_stmw off
static inline Color W1(u8 r, u8 g, u8 b, u8 a) { Color c; c.r = r; c.g = g; c.b = b; c.a = a; return c; }
/* ---- from build/tmp/r20small/rM/frag_fn_80150F0C.cpp ---- */
extern "C" {
/* from fn_80150AC0.cpp: 9 words differ, only the stack slots of the first colour pair.
   Needs extern u8 lbl_804CA7A0..A6, a by-value fn_802291A8 and W1 from the attempt. */
static const Color kC0={0xe,0x12,0xe,0xff};static const Color kC1={0x1c,0x27,0x1c,0xff};
static inline void Back(Win* w){
if (w->b83 != 0) {
                u8 a = 0xB2;
                if (lbl_804CB878.has(0x1000)) {
                    a = 0xFF;
                }
                fn_802291A8(w->bx, w->by, w->bw, W1(lbl_804CA7A0, lbl_804CA7A1, lbl_804CA7A2, a), W1(lbl_804CA7A4, lbl_804CA7A5, lbl_804CA7A6, a));
            } else {
                fn_802291A8(w->bx, w->by, w->bw, kC0, kC1);
            }
}
void fn_80150F0C(Win* w) {
    int i;
    if (w->parentNo >= 0) {
        u8* o = (u8*)fn_800C409C(w->parentNo);
        if (o != NULL) {
            w->bright = o[0x41] + fn_8014C83C();
        }
        if (w->alpha != 0) {
            fn_8007E154();
            fn_8007E4E4(0.0f, 0.0f, w->bz, 1.0f);
            if (lbl_804CB878.has(0x200000)) {
                fn_8007E84C(1);
            }
            fn_8007E7DC(w->alpha);
            fn_8007E7E8(w->bright / 2);
            fn_8007E164();
            Back(w);
        }
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 61.0f, 1.0f);
    if (lbl_804CB8A8 != NULL) {
        fn_8007E780(fn_80150CC4, NULL);
        fn_8007E7DC(w->alpha);
    } else {
        fn_8007E174(NULL, 0x13);
        fn_8007E7DC(w->alpha);
        if (w->reveal != 0) {
            fn_8007E74C(fn_80151328, w->scissor);
            Rect4(w->scissor, w->x, w->y, w->x + w->w, w->y + w->h);
        }
    }
    fn_8007E164();
    for (i = 0; i < w->rows; i++) {
        int x;
        fn_800800D4(6);
        switch (w->style) {
        case 3:
            break;
        case 1:
            fn_80080ABC(1, 2.0f);
            fn_80080B70(0, 1.0f);
            break;
        case 2:
            fn_80080ABC(0, 2.0f);
            fn_80080B70(1, 1.0f);
            break;
        case 4:
            fn_80080B00(1, fn_800CD204(0x2A), 1.0f);
            fn_80080B70(0, 1.0f);
            break;
        }
        x = w->x;
        if (lbl_804CB878.has(0x200000)) {
            x = fn_8007E9BC(x);
        }
        fn_80080330(x, w->y + i * w->lineH - w->reveal);
        fn_800804D4(w->bright * w->col.r / 0xFF, w->bright * w->col.g / 0xFF, w->bright * w->col.b / 0xFF, w->col.a);
        fn_80080C24(w->lines[(w->head + i) % w->rows]->text);
        fn_80080308();
    }
    fn_8007E7F4();
}
}
