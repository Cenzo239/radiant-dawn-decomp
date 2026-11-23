/* Title intro: unit profile screen */
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

class Info { public: virtual void v8(); };

extern "C" {

extern char lbl_8037307C[];
extern u8 lbl_803E7290[];
struct InfoB { u8 pad[0x44]; };
class InfoT : public InfoB {
public:
    virtual void v8(); virtual void vC(); virtual void v10(); virtual void v14();
    virtual void v18(int x, int y, int s);
};
void fn_8007E7E8(int a);
void fn_80080388(f32 a, f32 b, f32 c, f32 d);
void fn_80080940(C4* a, C4* b, C4* c, C4* d);
void fn_800804D4(int r, int g, int b, int a);
void fn_8026A5A0(void* tex, const char* s, int x, int y, int a, int n, int v);
u16 fn_800CEABC(int k);
u8 fn_80244D88(void);
int fn_800B5D14(void* a);
int fn_800B7260(void* a, int b);
void fn_800B26B0(void* a, void* b, int c, u16 d);

struct Prof {
    u8 pad[0x40];
    void* m40;
    u8 pad44[0x1C];
    s16 m60;
    u8 pad62[4];
    s16 m66;
    u8* unit;
    void* tex;
    void* tex2;
    u8* m74;
};

static inline C4 rgba(u8 r, u8 g, u8 b, u8 a) { C4 c = {r, g, b, a}; return c; }
static inline void grad(C4 a, C4 b, C4 c, C4 d) { fn_80080940(&a, &b, &c, &d); }
static inline void pos(f32 z) {
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, z, 1.0f);
    fn_8007E164();
}
static inline void* at(u8* t, int i) {
    if (i < 0 || i >= 5) return 0;
    return *(void**)(t + i * 4 + 0x2C);
}

void fn_8026B200(Prof* o) {
/*P*/
    void* a;
    int x;
    s16 n;
    int i;
    int k;
    int i2;
    int off;
    u8* t;
    int i3;
    int o3;
    int i4;
    int o4;
    void* m;
/*E*/
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 109.0f, 1.0f);
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(3);
    fn_80080388(0.0f, 0.0f, 608.0f, 448.0f);
    fn_80080578(0);
    {
        C4 a3, t3, a2, t2, a1, t1, a0, t0;
        *(u32*)&t0 = 0;
        t0.r = 0x18; t0.g = 0x10; t0.b = 0;
        *(u32*)&a0 = *(u32*)&t0;
        t1.r = 0x18; t1.g = 0x10; t1.b = 0; t1.a = 0xC0;
        *(u32*)&a1 = *(u32*)&t1;
        *(u32*)&t2 = 0;
        t2.r = 0x18; t2.g = 0x10; t2.b = 0;
        *(u32*)&a2 = *(u32*)&t2;
        t3.r = 0x18; t3.g = 0x10; t3.b = 0; t3.a = 0xC0;
        *(u32*)&a3 = *(u32*)&t3;
        fn_80080940(&a3, &a2, &a1, &a0);
    }
    fn_80080308();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 103.0f, 1.0f);
    fn_8007E374(o->tex, 0, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 21.0f, 0.0f, 0.0f, 608.0f, 80.0f);
    fn_80080578(0);
    fn_80080308();
    n = o->m60;
    if (n > 100) n = 100;
    fn_8026A5A0(o->tex, lbl_8037307C + 0x7C, 0x29, 0x6B, n, 0x14, *(s8*)(o->unit + 0xFD));
    fn_8026A5A0(o->tex, lbl_8037307C + 0x83, 0x29, 0x87, n, 0x14, *(s8*)(o->unit + 0xFE));
    fn_8026A5A0(o->tex, lbl_8037307C + 0x8B, 0x29, 0xA3, n, 0x14, *(s8*)(o->unit + 0xFF));
    fn_8026A5A0(o->tex, lbl_8037307C + 0x93, 0x29, 0xBF, n, 0x14, *(s8*)(o->unit + 0x100));
    fn_8026A5A0(o->tex, lbl_8037307C + 0x9C, 0x29, 0xDB, n, 0x14, *(s8*)(o->unit + 0x102));
    fn_8026A5A0(o->tex, lbl_8037307C + 0xA3, 0x29, 0xF7, n, 0x14, *(s8*)(o->unit + 0x103));
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 106.0f, 1.0f);
    fn_8007E374(o->tex, 4, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(36.0f, 270.0f, 0.0f, 0.0f, 236.0f, 37.0f);
    fn_80080578(0);
    fn_80080308();
    pos(102.0f);
    i = 0;
    x = 0x80;
    for (; i < 0xC; i++) {
        if (*(s16*)(o->unit + (u8)i * 2 + 0xB8) > 0) {
            { int c = fn_800CEABC((u8)i); ((InfoT*)lbl_803E7290)->v18(x, 0x114, c); }
            x += 0x20;
        }
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 108.0f, 1.0f);
    fn_8007E374(o->tex, 1, 0x11);
    fn_8007E164();
    for (i2 = 0, off = 0x13F; i2 < 3; i2++, off += 0x20) {
        fn_800800D4(1);
        fn_80080430(0.0f, off, 0.0f, 0.0f, 280.0f, 32.0f);
        fn_80080578(0);
        fn_80080308();
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 108.0f, 1.0f);
    fn_8007E374(o->tex, 2, 0x11);
    fn_8007E164();
    for (i3 = 0, o3 = 0x13F; i3 < 3; i3++, o3 += 0x20) {
        fn_800800D4(1);
        fn_80080430(280.0f, o3, 0.0f, 0.0f, 88.0f, 32.0f);
        fn_80080578(0);
        fn_80080308();
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 107.0f, 1.0f);
    fn_8007E174(0, 0x12);
    fn_8007E164();
    for (i4 = 0, o4 = 0x13F; i4 < 4; i4++, o4 += 0x20) {
        fn_800800D4(1);
        fn_80080388(0.0f, o4, 368.0f, 1.0f);
        fn_80080578(0);
        fn_800804D4(0xA0, 0xA0, 0xA0, 0x60);
        fn_80080308();
    }
    {
        k = (u8)fn_80244D88();
        switch (k) {
        case 0:
            fn_8007E154();
            fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
            fn_8007E374(o->tex2, 0, 0x11);
            fn_8007E164();
            fn_800800D4(1);
            fn_80080430(60.0f, 26.0f, 0.0f, 0.0f, 176.0f, 56.0f);
            fn_80080578(0);
            fn_80080308();
            fn_8007E154();
            fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
            fn_8007E374(o->tex2, 1, 0x11);
            fn_8007E164();
            fn_800800D4(1);
            fn_80080430(341.0f, 35.0f, 0.0f, 0.0f, 200.0f, 40.0f);
            fn_80080578(0);
            fn_80080308();
            break;
        case 1: case 2: case 3: case 4: case 5: case 6:
            fn_8007E154();
            fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
            {
                int f;
                switch (k) {
                case 0: f = 0; break;
                case 1: f = 2; break;
                case 2: f = 3; break;
                case 3: f = 4; break;
                case 4: f = 5; break;
                case 5: f = 6; break;
                case 6: f = 7; break;
                default: f = 2; break;
                }
                fn_8007E374(o->tex2, f, 0x11);
            }
            fn_8007E164();
            fn_800800D4(1);
            fn_80080430(248.0f, 24.0f, 0.0f, 0.0f, 288.0f, 56.0f);
            fn_80080578(3);
            fn_80080308();
            break;
        }
    }
    m = o->m40;
    t = o->m74;
    a = at(t, o->m66);
    if (a != 0) {
        if (fn_800B5D14(m) != 0 || (at(t, o->m66 + 1) != 0 && fn_800B7260(m, 5) != 0)) {
            { int z = 0x10000; fn_800B26B0(m, a, -1, z - 1); }
            o->m66++;
        }
    }
}

}
