/* fn_800C9918: exact since the round 21 regs review (was regs, 5 words). Helpers from fn_800B5D14.cpp (exported bodies removed), body from wip/fn_800B5D14.cpp.
   symcheck: (c) fixed. fn_8031292C is PSMTXScale(m, x, y, z); the draft passed no z (f3 held the int-to-float bias 2^52+2^31),
   the original passes 1.0f. Only rows 0-1 are loaded afterwards (fn_80307F10(m, 0x21, 1)), so nothing was visible. */
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

/* ---- from rG_800A3D88/wip/fn_800B5D14.cpp ---- */
extern "C" {

void fn_800C9918(VO* o) {
    u8 m[0x30];
    f32 y = lbl_804CD610 / (f32)o->v12();
    fn_8031292C(m, lbl_804CD610 / (f32)o->v11(), y, lbl_804CD610);
    fn_80307F10(m, 0x21, 1);
}
}
