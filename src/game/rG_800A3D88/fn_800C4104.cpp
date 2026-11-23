/* fn_800C4104: exact (round m2, agent m2-a). From wip/fn_800C4104_r20.cpp: the mode test is a switch with an empty `case -1` (mode -1 = keep flags); the extra case moves CW's switch pivot to 0, giving the original beq/bge/b/cmpwi 2 tree. */
#include "game/rG_800A3D88/chr.h"
extern "C" {
struct FG { s16 x, y, fl; };
extern FG lbl_803E50F0[];
extern const f64 lbl_804CD550;
struct F43 { u8 p[0x38]; f32 m38, m3c; u8 p40[3]; s8 m43; u8 p44[4]; u32 m48; };
int fn_8007E9BC(int);

f32 fn_800081B4(Mdl*);
int fn_800B5AB8(Chr*);
static inline f32 Frame(Chr* c) { if (c->mdl == NULL) return 0.0f; return fn_800081B4(c->mdl); }
int fn_800B5D14(Chr* c);

struct WB { u8 p[0x18]; struct { u8 p[0x40]; f32 x, y; }* m18; u8 p1c[0x14]; f32 m30, m34, m38; int m38i; };
struct WC { u8 p[0x18]; struct { u8 p[0x40]; f32 x, y; }* m18; u8 p1c[0x14]; f32 m30, m34; int m38; f32 m3c, m40, m44; };
f64 fn_80295CF0(f64);
int fn_8017F990(int, int);
f64 fn_80295940(f64);
extern const f32 lbl_804CD270, lbl_804CD280;
struct T18 { u8 p[0x40]; f32 x, y; };

struct Ef { u8 p[0x38]; void* m38; int m3c; u8 p40[4]; s16 m44; u16 m46; f32 m48, m4c, m50; };
extern u8 lbl_803825A8[];
extern char lbl_80365B64[];
extern const f32 lbl_804CD470;
void fn_800829CC(Ef*, void*);
f32 fn_800A84A4(const char*);
Ef* fn_80081050(void*, Ef*);
void fn_800BF148(Ef*);
void fn_800C0F44(Ef*, int);
#pragma use_lmw_stmw on

void fn_800BF444(Ef* e, int n, int k);

void fn_800BF608(Ef* e, int n, int k);

#pragma use_lmw_stmw off
extern FG lbl_dummy;
struct FadeG { u8 pad[0x32]; u16 m32; u8 m34, m35, m36, m37; s16 m38, m3a, m3c, m3e; };
extern FadeG* lbl_804CB6D8;
extern const f32 lbl_804CD5C8;
void fn_800C86D4(u8 r, u8 g, u8 b, int t0, int t1);

class VO {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* v9();
    virtual void* v10();
    virtual int v11();
    virtual int v12();
    void* m4;
};
#if TARGET_PC
FE10_PROTO void fn_80006B84(void*, void*, void*, ptr32<const void>, ptr32<const void>);
#else
void fn_80006B84(void*, void*, void*, void*, void*);
#endif
void fn_80305DB4(void*, int, int);
void fn_80022254(void*, int);
#if TARGET_PC
FE10_PROTO void fn_80306054(void*, ptr32<const void>);
#else
void fn_80306054(void*, void*);
#endif
void fn_8031292C(void*, f32, f32, f32);
void fn_80307F10(void*, int, int);
extern const f32 lbl_804CD610;
void fn_800C986C(VO* o);


}

#pragma use_lmw_stmw off
/* ---- from rG_800A3D88/wip/fn_800B5D14.cpp ---- */
extern "C" {
// Near misses, see NOTES.md. Needs declarations from ../fn_800B5D14.cpp.
void fn_800C4104(F43* f, s8 k, s8 m, int w) {
    if (k >= 0 && k <= 9) {
        f->m43 = k;
        int x = lbl_803E50F0[k].x;
        if (w != 0) {
            if (x >= 1000) x = fn_8007E9BC(x - 1000) + 1000;
            else x = fn_8007E9BC(x);
        }
        f->m38 = x;
        f->m3c = lbl_803E50F0[k].y;
        f->m48 &= ~1;
        switch (m) {
        case -1:
            break;
        case 0:
            f->m48 |= lbl_803E50F0[k].fl;
            break;
        case 1:
            f->m48 |= 1;
            break;
        }
    }
}
}
