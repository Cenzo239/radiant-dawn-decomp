#include "game/rI_801DD7D4/types.h"
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_80083DC4(void*, int);
void* fn_80081194(void*, void*);
void fn_80253EE4(const char*, f32);
extern u8 lbl_8038FDC8[];
extern char lbl_80371DCC[];
struct It { u8 p[0x1c]; u8 x1c; u8 p2[2]; u8 x1f; u8 x20; };
struct Sl { It* x0; u8 x4; u8 x5; };
struct T2 { u8 p[0x5c]; u8* x5c; u8 p2[8]; s16 x68; };
struct C3 { u8 p[0x30]; T2* x30; u8 p2[4]; It* x38; };
void fn_80222AD0(T2* o, It* t, void* p2) {
    C3* c = (C3*)fn_80081194(lbl_8038FDC8, p2);
        int off;
    It* q;
    Sl* s;
    int j;
    int i;
    j = 0;
    i = 0;
    off = 0;
    for (; i < 18; i++) {
        s = (Sl*)(o->x5c + 0x12c + off);
        if (s && (q = s->x0) != 0 && q->x1f) {
            if (t->x1c == q->x1c) {
                o->x68 = j;
                break;
            }
            j++;
        }
        off += 8;
    }
    c->x30 = o;
    c->x38 = t;
    fn_80083DC4(c, 3);
}
struct D8 { void* p; u8 k; bool f; };
#if TARGET_PC
FE10_PROTO void fn_801080CC(D8*, ptr32<const void>, int, int, void*);
#else
void fn_801080CC(D8*, void*, int, int, void*);
#endif
void fn_801D8ADC(int, s16, s16, int);
struct T4 { u8 p[0x12]; s16 x12, x14, x16, x18; u8 p1[4]; s16 x1e; u8 p2[0x2e]; void* x50; u8 p3[0xc]; u8 x60_[2]; s16 x62; };
void fn_80223B80(T4* o, int a, int b, int c, It* t, void* e) {
    D8 d;
    d.p = t;
    d.k = 2;
    d.f = false;
    if (t) d.f = t->x20 == 0;
    fn_801080CC(&d, e, a, b, o->x50);
    fn_8007E154();
    fn_8007E720(0.5f);
    fn_8007E164();
    fn_801D8ADC(a, b + o->x62 - 0xc, (s16)(o->x16 - o->x12) - o->x1e * 2, 0x10);
    fn_8007E154();
    fn_8007E720(-0.5f);
    fn_8007E164();
}
}
