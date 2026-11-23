/* Unit record list page */
#pragma inline_max_size(4000)
#pragma inline_max_total_size(30000)
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

extern char lbl_80373C40[];
extern char lbl_80392D1C[];
extern char lbl_80392D28[];
extern char lbl_80392D34[];
extern char lbl_80392D40[];
extern char lbl_804CAB58[8];
extern char lbl_804CAB60[8];
extern char lbl_804CAB68[4];
extern char lbl_804CAB6C[4];
extern char lbl_804CAB70[8];
void fn_802852E0(void*);
void fn_802852F4(void*);
void fn_800804D4(int r, int g, int b, int a);
void fn_80080330(f32 x, f32 y);
void fn_80080388(f32 a, f32 b, f32 c, f32 d);
void fn_80080508(C4* c);
void fn_80080940(C4* a, C4* b, C4* c, C4* d);
#if TARGET_PC
FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
void fn_80080910(void* f, void* a);
#endif
void fn_80080A94(f32 s);
void fn_80080B00(f32 s, int a, C4* c);
void fn_80080C24(const char* s);
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void* f, void* a);
#endif
void fn_8007E720(f32 v);
void fn_800F7E40(int a);
const char* fn_80118C44(void* p);
const char* fn_80118F00(void* p);
C4* fn_800CD204(int i);
int fn_800CA3DC(const char* s, int a, f32 v);
void* fn_8010B094(int a);
const char* fn_80092904(void* p);
const char* fn_8009285C(void* p);

struct Pair { void* first; void* second; };
void fn_80286FC0(Pair* p, f32 a, f32 b);

struct It { Pair* p; It& operator--() { --p; return *this; } Pair& operator*() const { return *p; } };
struct RI {
    It tmp;
    It cur;
    RI() {}
    RI(It x) { cur = x; }
    Pair& operator*() { tmp = cur; tmp.p--; return *tmp.p; }
    Pair* operator->() { return &**this; }
    RI& operator++() { cur.p--; return *this; }
};
struct CRI {
    It tmp;
    It cur;
    CRI(const RI& o) { cur = o.cur; }
    ~CRI() {}
    Pair& operator*() { tmp = cur; --tmp; return *tmp; }
    Pair* operator->() { return &**this; }
    CRI& operator++() { --cur; return *this; }
};
static inline bool operator!=(const CRI& a, const RI& b) { return a.cur.p != b.cur.p; }
struct Vect {
    Pair* begin;
    int size;
    RI rbegin() { It x; x.p = begin + size; return RI(x); }
    RI rend() { It x; x.p = begin; return RI(x); }
};

struct Rec {
    u8 pad[0x38];
    void* tex;
    u8 pad3C[8];
    u32 m44;
    u8 pad48[8];
    u16 m50, m52;
    u8 pad54[0x18];
    Vect list;
    u8 pad74[4];
    u8 m78;
};

static C4 kc = {0x3C, 0x3C, 0x3C, 0x7F};

static inline void img(void* tex, int i, u8 b, u8 a, f32 x, f32 y, f32 w, f32 h) {
    fn_8007E154();
    fn_8007E374(tex, i, 0x11);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800800D4(1);
    fn_800804D4(b, b, b, a);
    fn_80080430(x, y, 0.0f, 0.0f, w, h);
    fn_80080578(0);
    fn_80080308();
}
static inline void pdraw(Pair p, f32 a, f32 b) { fn_80286FC0(&p, a, b); }
static inline C4 mk5() { C4 r = kc; return r; }
static inline void hdr(f32 x, f32 y) {
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800800D4(5);
    fn_80080330(x, y);
}
static inline void txt(f32 x, f32 y, int cn, int n, const char* s) {
    hdr(x, y);
    { C4 c = *fn_800CD204(cn); fn_80080508(&c); }
    fn_80080A94(1.0f);
    fn_80080B00(1.0f, 1, fn_800CD204(n));
    fn_80080C24(s);
    fn_80080308();
}
static inline void grad(C4 d, C4 c, C4 b, C4 a) { fn_80080940(&d, &c, &b, &a); }
static inline BOOL vis(u16 y) {
    if (y + 0x50 < 0x50 || y > 0x1EF) return 0;
    return 1;
}
static inline u16 rowY(Rec* o, int i) { return o->m44 + (u16)i * 0x50 + 0x50; }

void fn_802845C8(Rec* o) {
    char buf[0x50];
/*P*/
    Pair* end;
    u16 y;
    Pair* e;
    int j;
    int i;
    const char* n;
    void* t0;
    u8 b;
    void* t;
    u8 b2;
    u8 a;
    u8 a2;
    const char* m;
    s8 lang;
    void* v;
    void* v2;
    u8* u;
    u16 w2;
    u16 w3;
    u16 w;
    u16 yy;
/*E*/
    lang = fn_8024BC94()[0x1BC8];
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E164();
    a = o->m52; b = o->m50; t0 = o->tex;
    img(t0, 1, b, a, 0.0f, 24.0f, 608.0f, 80.0f);
    a2 = o->m52; b2 = o->m50; t = o->tex;
    img(t, 2, b2, a2, 0.0f, 400.0f, 608.0f, 24.0f);
    fn_8007E154();
    fn_8007E74C(fn_802852E0, 0);
    fn_8007E164();
    e = o->list.begin;
    end = e + o->list.size;
    for (i = 0; e != end; e++, i++) {
        if (i >= o->m78 - 5) break;
        C4 c = mk5();
        y = o->m44 + 0x50 + (u16)i * 0x50;
        if (vis(y)) {
            fn_8007E154();
            fn_8007E4E4(0.0f, y, 800.0f, 1.0f);
            fn_8007E164();
            t = o->tex;
            img(t, 3, 0xFF, 0xFF, 96.0f, 8.0f, 160.0f, 22.0f);
            t = o->tex;
            img(t, 4, 0xFF, 0xFF, 456.0f, 8.0f, 120.0f, 22.0f);
            fn_8007E154();
            fn_8007E174(0, 0x12);
            fn_8007E164();
            fn_800800D4(3);
            fn_80080388(256.0f, 18.0f, 200.0f, 2.0f);
            grad(c, c, c, c);
            fn_80080578(0);
            fn_80080308();
            fn_8007E154();
            fn_8007E4E4(0.0f, y, 300.0f, 1.0f);
            fn_8007E164();
            fn_80290DDC(buf, lbl_80373C40 + 0x19, fn_80118C44(*(void**)((u8*)e->first + 0xEC)));
            txt(115.0f, 7.0f, 1, 2, buf);
            if (lang == 0) {
                fn_80290DDC(buf, lbl_80373C40 + 0x1C, *(u16*)((u8*)e->first + 900));
                w = fn_800CA3DC(buf, -1, 1.0f);
                txt((s16)(0x208 - w), 7.0f, 1, 2, buf);
                fn_80290DDC(buf, lbl_80373C40 + 0x19, fn_800D0864(lbl_80373C40 + 0x1F));
                txt(528.0f, 7.0f, 1, 2, buf);
            } else {
                fn_80290DDC(buf, lbl_80373C40 + 0x27, fn_800D0864(lbl_80373C40 + 0x1F), *(u16*)((u8*)e->first + 900));
                w2 = fn_800CA3DC(buf, -1, 1.0f);
                txt((s16)(0x21C - w2), 7.0f, 1, 2, buf);
            }
            {
                u = (u8*)e->first;
                if ((*(u8**)(u + 0xF4))[8] != 6) {
                        fn_80290DDC(buf, lbl_80373C40 + 0x19, fn_80118F00(*(void**)(u + 0xF0)));
                    txt(260.0f, 22.0f, 8, 0x2A, buf);
                    fn_80290DDC(buf, lbl_80373C40 + 0x2D);
                    txt(400.0f, 22.0f, 8, 0x2A, buf);
                    fn_80290DDC(buf, lbl_80373C40 + 0x1C, *(s8*)((u8*)e->first + 0xFE));
                    w3 = fn_800CA3DC(buf, -1, 1.0f);
                    txt((s16)(0x1BC - ((u32)w3 >> 1)), 22.0f, 8, 0x2A, buf);
                } else if (lang == 0) {
                    v = fn_8010B094(u[0x38E]);
                    if (*(u32*)(u + 0x10C) & 0x20) {
                        m = fn_800D0864(lbl_80392D28);
                        n = fn_80092904(v);
                        fn_80290DDC(buf, lbl_804CAB60, fn_8009285C(v), n, m);
                    } else {
                        m = fn_800D0864(lbl_80392D1C);
                        n = fn_80092904(v);
                        fn_80290DDC(buf, lbl_804CAB58, fn_8009285C(v), n, m);
                    }
                    txt(260.0f, 22.0f, 2, 0x2A, buf);
                } else {
                    if (*(u32*)(u + 0x10C) & 0x20) {
                        fn_80290DDC(buf, lbl_804CAB6C, fn_800D0864(lbl_80392D40));
                    } else {
                        fn_80290DDC(buf, lbl_804CAB68, fn_800D0864(lbl_80392D34));
                    }
                    txt(260.0f, 22.0f, 2, 0x2A, buf);
                    {
                        v2 = fn_8010B094(((u8*)e->first)[0x38E]);
                        fn_80290DDC(buf, lbl_804CAB70, fn_8009285C(v2), fn_80092904(v2));
                    }
                    txt(260.0f, 43.0f, 2, 0x2A, buf);
                }
            }
        }
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 200.0f, 1.0f);
    fn_8007E174(0, 0x410);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800800D4(0xB);
    fn_80080910(fn_802852F4, 0);
    fn_80080308();
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E164();
    {
        j = o->m78 - 1;
        CRI it = o->list.rbegin();
        for (; it != o->list.rend(); ++it, j--) {
            yy = o->m44 + 0x50 + (u16)j * 0x50;
            if (j < o->m78 - 5 && vis(yy) && it->second != 0) {
                pdraw(*it, 64.0f, yy + 0x32);
            }
        }
    }
    fn_800F7E40(0xC7);
}

}
