
#include "game/rL_80133EB4/talk.h"
#pragma use_lmw_stmw on
extern "C" {
struct SB { u8 l : 1; u8 n : 7; };
static inline void F18(Talk* t){ if (t->x18) { fn_800D42A0(t->x18); t->x18 = 0; }}
static inline void F14(Talk* t){ if (t->x14) { fn_80081A90(t->x14); t->x14 = 0; }}
static inline void F1C4(Talk* t) {
    int i;
    for (i = 0; i < 8; i++, t = (Talk*)((u8*)t + 4)) {
        if (t->x1c4[0]) fn_800DF6C8(t->x1c4[0]);
    }
}
static inline void TalkEnd() {
    if (lbl_804181AC.proc) {
        {
            int i;
            Talk* t = &lbl_804181AC;
            for (i = 0; i < 9; i++, t = (Talk*)((u8*)t + 4)) {
                if (t->x21c[0]) fn_80150C68(t->x21c[0]);
                t->x21c[0] = 0;
            }
        }
        {
            Talk* t = &lbl_804181AC;
            int i;
            for (i = 0; i < 5; i++, t = (Talk*)((u8*)t + 4)) {
                if (t->actor[0]) fn_800C4240(t->actor[0]);
                t->actor[0] = 0;
            }
        }
        if (lbl_804CB880) fn_80006A2C(&lbl_804CB880);
        F18(&lbl_804181AC);
        F14(&lbl_804181AC);
        {
            Talk* t = &lbl_804181AC;
            if ((t->str0 >> 31) == 0) {
                ((u8*)&t->str0)[1] = 0;
                ((SB*)&t->str0)->n = 0;
            } else {
                *t->strp = 0;
                t->str1 = 0;
            }
        }
        lbl_804181AC.proc = 0;
        lbl_804181AC.cur = 0;
        fn_8014CFEC();
        if (lbl_804CB878 & 0x80) {
            fn_80068C08();
            lbl_804CB878 &= ~0x80;
        }
        lbl_804CB700 &= ~0x8002;
        fn_8014D364(&lbl_804CB878);
        {
            Talk* t = &lbl_804181AC;
            int i;
            for (i = 0; i < 8; i++, t = (Talk*)((u8*)t + 4)) {
                if (t->x1c4[0]) fn_800DF6C8(t->x1c4[0]);
            }
        }
    }
}
#pragma auto_inline off
void fn_80148B90(void) { TalkEnd(); }
} /* extern "C" */
extern "C" {
extern u8 lbl_80413F10[];
extern void fn_801D0A40(const char*);
extern void fn_8014EFBC(void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_8014CEBC(ptr32<const void>, s16, s16, void*);
#else
extern void fn_8014CEBC(void*, s16, s16, void*);
#endif
extern void fn_8014D1AC(void*, u8);
extern const char* fn_800D0864_1(void);

void fn_8014BED4(const char* a, void* parent) {
    const char* text = ((const char*(*)(const char*))fn_800D0864)(a);
    Empty e;
    u32 n;
    int i;
    if (text == a) return;
    fn_8014D310(&lbl_804CB878);
    lbl_804181AC.proc = fn_800811E4(lbl_80386A98, parent);
    {
        for (i = 0; i < 5; i++) lbl_804181AC.actor[i] = 0;
        for (i = 0; i < 9; i++) lbl_804181AC.x21c[i] = 0;
        for (i = 0; i < 16; i++) {
            lbl_804181AC.slots[i * 0x18] = 0;
            lbl_804181AC.x19c[i] = -1;
        }
        for (i = 0; i < 8; i++) lbl_804181AC.x1c4[i] = 0;
        lbl_804181AC.x1e4 = lbl_804181AC.x1c4;
        lbl_804181AC.x201 = -1;
        lbl_804181AC.cur200 = -1;
        lbl_804181AC.x203 = -1;
        lbl_804181AC.x202 = -1;
        lbl_804181AC.x1f4 = 1;
        n = (lbl_804181AC.str0 >> 31) == 0 ? (*(u8*)&lbl_804181AC.str0 & 0x7F) : lbl_804181AC.str1;
    }
    fn_800250B0(&lbl_804181AC.str0, 0, n, text, text + strlen(text), e);
    lbl_804181AC.cur = (lbl_804181AC.str0 >> 31) == 0 ? (char*)&lbl_804181AC.str0 + 1 : lbl_804181AC.strp;
    {
        Talk* t = &lbl_804181AC;
        t->x18 = 0;
        t->x14 = 0;
        t->x1ec = 8;
        t->x1ee = 8;
        t->x1f0 = 0;
        t->x1f8 = 0x808;
        t->x1fc = 0x808;
        t->x1f3 = 1;
        t->x204 = 800;
        t->x1ea = 0;
        t->x1eb = 0;
        t->x206 = 0;
        t->x1e9 = 0;
        ((u8*)t)[0x1AC] = 0;
    }
    fn_8014EEEC(lbl_80413F10);
    fn_8014D220(&lbl_804CB878);
    if (lbl_804CB700 & 1) {
        fn_8014B650(lbl_804181AC.proc);
    } else {
        fn_800C3558()[0x1C] = 1;
    }
    fn_801D0A40(a);
}

static inline u8 FadeA(Talk* t) {
    if (t->x14 && fn_800D3CF4(t->x14) && fn_800D3CF4(t->x14) != 0xFF) return fn_800D3CF4(t->x14);
    return 0xFF;
}
void fn_8014B244(Talk* t) {
    int k;
    if (t->x201 == t->cur200 && t->x203 == t->x202) return;
    t->x201 = t->cur200;
    t->x203 = t->x202;
    k = t->x19c[t->cur200];
    if (k >= 0) {
        fn_8014EFBC(lbl_80413F10, &t->slots[t->cur200 * 0x18]);
        {
            f32 y = *(f32*)(t->actor[k] + 0x3C);
            f32 x = *(f32*)(t->actor[k] + 0x38);
            fn_8014CEBC(&t->slots[t->cur200 * 0x18], x, y, t->proc);
        }
        {
            int i;
            for (i = 0; i < 5; i++) {
                if (t->actor[i]) {
                    if (i == k) {
                        u8 c = FadeA(t);
                        fn_8014D1AC(t->actor[i], c);
                    } else {
                        u8 c;
                        if (lbl_804CB878 & 1) {
                            c = FadeA(t);
                        } else {
                            c = FadeA(t) - 0x4D;
                        }
                        fn_8014D1AC(t->actor[i], c);
                    }
                }
            }
        }
    }
}

void fn_8014B45C(void) {
    int i;
    Talk* t = &lbl_804181AC;
    for (i = 0; i < 9; i++, t = (Talk*)((u8*)t + 4)) {
        if (t->x21c[0]) fn_80150F0C(t->x21c[0]);
    }
}


extern void* fn_80151414(void*);
extern void* fn_80150BE8(void*);
extern void fn_80150AEC(void*, void*, int, int);
struct TColor;
extern void fn_80150AC0(void*, int, int);
extern void fn_80150AFC(void*, int, int);
extern void fn_80150ADC(void*, int);
extern void fn_80150ACC(void*, u8);
extern void fn_80150AD4(void*, u8);
extern void fn_80150AE4(void*, u8);
extern void fn_80150B18(void*, u8);
extern int fn_801D09F0(void);
struct TColor { u8 r, g, b, a; };
struct TalkCfg {
    u8 pad0[8];
    void* x08;
    void* x0c;
    TColor x10;
    s16 x14, x16, x18, x1a, x1c, x1e, x20, x22, x24;
    u8 x26, x27, x28, x29, x2a, x2b, x2c;
};
extern void fn_80150B20(void*, TColor);
struct Port { u8 pad0[0x68]; s16 x68,x6a,x6c,x6e; u8 pad70[0x12]; u8 x82,x83; };
void fn_80148998(TalkCfg* c, int b) {
    Port* p = 0;
    {
        Talk* q = &lbl_804181AC;
        int i;
        for (i = 0; i < 9; q = (Talk*)((u8*)q + 4), i++) {
            if (q->x21c[0] == 0) {
                Talk* t = &lbl_804181AC;
                t->x240 = t->x21c[i] = fn_80151414(t->proc);
                p = (Port*)fn_80150BE8(t->x21c[i]);
                break;
            }
        }
    }
    fn_80150AEC(p, c->x0c, c->x18, c->x1a);
    fn_80150B20(p, c->x10);
    fn_80150AC0(p, c->x14, c->x16);
    fn_80150AFC(p, c->x18, c->x1a);
    fn_80150ADC(p, c->x1c);
    p->x68 = c->x1e;
    p->x6a = c->x20;
    p->x6c = (c->x22 - c->x1e + 0x2F) / 0x30;
    p->x6e = c->x24;
    fn_80150ACC(p, c->x26);
    fn_80150AD4(p, c->x27);
    fn_80150AE4(p, c->x28);
    p->x82 = c->x29;
    lbl_804181AC.x1e9 = c->x2a != 0;
    p->x83 = c->x2b;
    fn_80150B18(p, c->x2c);
    lbl_804181AC.x1e8 = 0;
    if (b && fn_801D09F0()) lbl_804CB878 |= 0x200000;
    {
        void* x = c->x08;
        if (x) {
            lbl_804181AC.x18 = x;
            lbl_804181AC.x1e8 = 1;
        }
    }
}
int fn_8014B1D8(Talk* t, u8* a) {
    int i;
    for (i = 0; i < 5; i++) {
        if (a == t->actor[i]) return i;
    }
    return -1;
}


void fn_8014C99C(void) {
    u32 f = lbl_804CB878;
    lbl_804CB878 = f & ~4;
    lbl_804CB700 |= 2;
    if (f & 0x8000) lbl_804CB700 |= 0x8000;
}


extern char lbl_804CA780[8],lbl_804CA778[8],lbl_804CA770[8],lbl_804CA768[8],lbl_804CA760[8],lbl_804CA758[8],lbl_804CA750[8],lbl_804CA748[8],lbl_804CA740[8];
extern char lbl_80386C24[],lbl_80386C18[],lbl_80386C0C[],lbl_80386C00[],lbl_80386BF4[],lbl_80386BE8[],lbl_80386BDC[],lbl_80386BCC[],lbl_80386BC0[],lbl_80386BB4[],lbl_80386BA8[],lbl_80386B98[],lbl_80386B8C[],lbl_80386B80[];
extern char* strcpy(char*, const char*);
extern char* fn_80291110(char*, const char*);
extern int fn_80291188(const char*, const char*);
extern void* fn_8012CE54(const char*);
extern char* fn_801246A4(void*);
extern char* fn_8012486C(void*);
extern char* fn_802910CC(void*, const char*, int);
extern u8 lbl_803CA870[0x200];
extern u8* fn_80148728(u8**);
#define T1(a,b) if (fn_80291188(d, a) == 0) { void* v = fn_8012CE54(b); if (v) d = fn_801246A4(v); }
#define T2(a,b) if (fn_80291188(d, a) == 0) { void* v = fn_8012CE54(b); if (v) d = fn_8012486C(v); }
void fn_8014AE04(Talk* t, u8** s) {
    char buf[0x40];
    u8* q;
    int i;
    u8* w;
    char* d;
    q = t->slots;
    for (i = 0; i < 16; i++, q += 0x18) {
        w = fn_80148728(s);
        if (w == 0) return;
        d = buf;
        strcpy(d, lbl_804CA780);
        fn_80291110(d, (char*)w);
        T1(lbl_804CA778,lbl_804CA770);
        T1(lbl_80386C24,lbl_80386C18);
        T1(lbl_80386C0C,lbl_80386C00);
        T1(lbl_80386BF4,lbl_80386BE8);
        T1(lbl_804CA768,lbl_804CA760);
        T2(lbl_80386BDC,lbl_804CA758);
        T2(lbl_80386BCC,lbl_80386BC0);
        T2(lbl_80386BB4,lbl_80386BA8);
        T2(lbl_80386B98,lbl_80386B8C);
        T2(lbl_80386B80,lbl_804CA750);
        if (fn_80291188(d, lbl_804CA748) == 0) { void* v = *(void**)lbl_803CA870; if (v) d = fn_801246A4(v); }
        if (fn_80291188(d, lbl_804CA740) == 0) { void* v = *(void**)lbl_803CA870; if (v) d = fn_8012486C(v); }
        fn_802910CC(q, d, 0x18);
    }
}
extern int fn_8014D070(void*);
void fn_8014B0C8(Talk* t, int* n) {
    int k;
    (*n)++;
    k = t->x19c[t->cur200];
    if (t->x1e8 == 0) fn_80151D28(t->x21c[(s8)t->actor[k][0x43]], t->proc);
    if (lbl_804CB700 & 3) {
        fn_800C4240(t->actor[k]);
    } else {
        fn_800C71CC(t->actor[k], t->proc);
    }
    t->actor[k] = 0;
    if (fn_8014D070(&t->slots[t->cur200 * 0x18])) fn_8014CF98();
    t->x19c[t->cur200] = -1;
    t->x201 = -1;
    t->cur200 = -1;
    t->x203 = -1;
    t->x202 = -1;
}
}
