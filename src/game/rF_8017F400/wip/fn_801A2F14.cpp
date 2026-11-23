/* near misses: fn_801A2F14 (2 words: xoris r4 wanted, plus lfd placement), fn_801A3104 (35), fn_801A3898 (17: register ranks; the string base wants r27, zero r26, global r25). Self-contained. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
/* illustration room (MIR_*) mode setup; global at lbl_804CB94C, same object as fn_801A3068.cpp */
typedef struct C4 { u8 r, g, b, a; } C4;
typedef struct IEnt { const char* a; const char* b; } IEnt;
typedef struct IG {
    void* res0; void* res4; void* res8; int xC;
    s16 x10, x12, x14, x16, x18, x1A, x1C, x1E;
    u8 x20; u8 pad21; u16 x22; f32 x24; s16 x28, x2A, x2C; u8 pad2E[2];
    IEnt* x30; char x34[0x60]; void* x94;
} IG;
extern IG* lbl_804CB94C;
extern char lbl_8036D10C[];
extern IEnt lbl_80388AA0[];
extern char lbl_804CA798[8];
extern void* fn_80078CCC(u32, void*, int);
extern void* fn_80179660(void*);
extern void fn_801798A8(void*, int);
extern const u8* fn_800CD204(int);
extern void fn_80179A58(void*, C4);
extern void fn_801C6EAC(const char*, const char*, char*);
extern void fn_800068A0(void*, const char*);
extern void fn_802639D0(void);
extern const char* fn_800D0864(const char*);
extern const char* fn_800CEC24(void);
extern const char* fn_800CEB4C(void);
extern const char* fn_800CF3A4(void);
extern const char* fn_800CF53C(void);
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_80006A2C(void*);
extern char* strcpy(char*, const char*);
extern char* fn_80291110(char*, const char*);
#define STR(a) (lbl_8036D10C + (a) - 0x8036D10C)

void fn_801A2F14(void) {
    char path[0x60];
    IG* g = lbl_804CB94C;
    int z = 0;
    lbl_804CB94C->res8 = (void*)z;
    lbl_804CB94C->res4 = (void*)z;
    lbl_804CB94C->xC = z;
    lbl_804CB94C->x10 = z;
    lbl_804CB94C->x12 = -100;
    lbl_804CB94C->x14 = -100;
    lbl_804CB94C->x34[0] = z;
    g->x2A = z;
    g->x28 = z;
    g->x24 = z;
    g->x2C = z;
    {
    void* m = fn_80078CCC(0x2C, lbl_804CA798, 0);
    if (m) m = fn_80179660(m);
    lbl_804CB94C->x94 = m;
    }
    fn_801798A8(lbl_804CB94C->x94, 1);
    fn_80179A58(lbl_804CB94C->x94, *(C4*)fn_800CD204(4));
    lbl_804CB94C->x16 = 4;
    lbl_804CB94C->x18 = lbl_804CB94C->x12;
    lbl_804CB94C->x1A = lbl_804CB94C->x14;
    lbl_804CB94C->x1C = -100;
    lbl_804CB94C->x1E = -100;
    fn_801C6EAC(STR(0x8036D129), STR(0x8036D146), path);
    fn_800068A0(lbl_804CB94C, path);
    fn_802639D0();
}

void fn_801A3104(void) {
    IG* g = lbl_804CB94C;
    IEnt* e = lbl_80388AA0;
    lbl_804CB94C->xC = 3;
    lbl_804CB94C->x34[0] = 0;
    g->x30 = lbl_80388AA0;
    g->x20 = 0;
    while (e->a != 0) {
        e++;
        g->x20++;
    }
    {
    int r = g->x20 / 3;
    if (g->x20 % 3 > 0) r++;
    r = r * 0x1C + 0x30;
    g->x22 = r;
    if ((s16)r > 0xF0) g->x22 = 0xF0;
    }
    lbl_804CB94C->x16 = 0;
    {
    int k = lbl_804CB94C->x10 + lbl_804CB94C->x2A * -3;
    lbl_804CB94C->x12 = (k % 3) * 0x92 + 0x4D;
    lbl_804CB94C->x14 = (k / 3) * 0x1C + 0x98;
    }
    {
    const char* a = fn_800D0864(STR(0x8036D16D));
    const char* b = fn_800CEB4C();
    const char* c = fn_800D0864(STR(0x8036D165));
    const char* d = fn_800CEC24();
    const char* e2 = fn_800D0864(STR(0x8036D15A));
    fn_80290DDC(lbl_804CB94C->x34, STR(0x8036D14B), fn_800CF53C(), e2, d, c, b, a);
    }
    if (lbl_804CB94C->res4 != 0) {
        fn_80006A2C(&lbl_804CB94C->res4);
        lbl_804CB94C->res4 = 0;
    }
    if (lbl_804CB94C->res8 != 0) {
        fn_80006A2C(&lbl_804CB94C->res8);
        lbl_804CB94C->res8 = 0;
    }
}

void fn_801A3898(void) {
    char path[0x40];
/*P*/
    const char* d;
    const char* c;
    const char* b;
    const char* a;
    const char* s;
    int z;
    IG* g;
/*E*/
    g = lbl_804CB94C;
    s = lbl_8036D10C;
    z = 0;
    g->xC = 4;
    lbl_804CB94C->x34[0] = z;
    a = fn_800D0864(s + 0xB6);
    b = fn_800CEC24();
    c = fn_800CEB4C();
    d = fn_800D0864(s + 0x4E);
    fn_80290DDC(lbl_804CB94C->x34, s + 0xA8, fn_800CF3A4(), d, c, b, a);
    if (lbl_804CB94C->res8 != 0) {
        fn_80006A2C(&lbl_804CB94C->res8);
        lbl_804CB94C->res8 = (void*)z;
    }
    lbl_804CB94C->res8 = lbl_804CB94C->res4;
    strcpy(path, STR(0x8036D1CD));
    fn_80291110(path, g->x30[lbl_804CB94C->x10].b);
    fn_801C6EAC(path, STR(0x8036D146), path);
    fn_800068A0(&lbl_804CB94C->res4, path);
}
}
