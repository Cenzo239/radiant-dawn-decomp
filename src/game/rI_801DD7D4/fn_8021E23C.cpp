#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
extern VO0N* lbl_804CB5B8;
extern char lbl_80371B80[];
extern u8 lbl_803CAB38[];
int fn_80120378(void*);
f32 fn_80120524(void*, int);
f32 fn_80062850(void*);
void fn_80253EE4(const char*, f32);
u8 fn_80126B0C(void*);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
void fn_8007E720(f32);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
void fn_800CB3A8(f32, f32, int, int, int, int, int, const char*, ...);
int fn_80290D04(char*, int, const char*, ...);
char* strcpy(char*, const char*);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080330(f32, f32);
void fn_80080508(C4);
void fn_80080A94(f32);
void fn_80080C24(const char*);
int fn_801D09F0(void);
int fn_8011FF28(void*, int, int);
struct Un { u8 p[0xf0]; struct { u8 p[0xfb]; u8 afb; }* af0; u8 pf4[0xa]; s8 afe; };
struct E28 { void* vt; u8 p4[8]; u8 ac, ad; u8 pe[6]; s16 a14; u8 p16[0x12]; };
class EV { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(u32); };
struct Ctx { u8 p[0x2d]; u8 a2d; u8 a2e; u8 p2f[5]; int a34; struct { u8 p[8]; void* a8; }* a38; };
class BO { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; u8 p3c[4]; Un* a40; f32 a44; int a48; E28 e[4]; u8 pec[0]; E28 f; };
static inline f32 cost(Un* u, int k) {
    f32 r;
    if (k == 0) {
        r = 0.0f;
    } else {
        f32 v = fn_80120524(u, k);
        if (v < 1.0f) v = 1.0f;
        r = v;
    }
    return r;
}
static inline BOOL canUp(BO* o) {
    int v = ((const BO*)o)->a48;
    BOOL b = fn_80120378(o->a40) - v > 0;
    if (b) b = fn_80062850(lbl_803CAB38) >= cost(o->a40, o->a48 + 1);
    return b;
}
static inline void sfx(void) { fn_80253EE4(lbl_80371B80 + 0x95, 0.0f); }
static inline int lvSum(BO* o, Un* u) { int n = o->a48; int k = fn_80126B0C(u); return k + n; }
static inline void upLoop(BO* o) {
    while (canUp(o)) {
        o->a44 = fn_80062850(lbl_803CAB38) - cost(o->a40, ++o->a48);
        if (lvSum(o, o->a40) % 100 == 0) break;
    }
}
static inline void dnLoop(BO* o) {
    while (o->a48 > 0) {
        o->a44 = fn_80062850(lbl_803CAB38) - cost(o->a40, --o->a48);
        if (lvSum(o, o->a40) % 100 == 0) break;
    }
}
void fn_8021E23C(BO* o) {
    if (!inputBlocked()) {
        int k = lbl_804CB5B8->v3C();
        int q = lbl_804CB5B8->v44();
        if (canUp(o) && (q & 0x800008)) {
            o->a44 = fn_80062850(lbl_803CAB38) - cost(o->a40, ++o->a48);
            sfx();
            o->e[0].ad = 1;
            o->e[0].a14 = 0x1e;
        } else if (((const BO*)o)->a48 > 0 && (q & 0x400004)) {
            o->a44 = fn_80062850(lbl_803CAB38) - cost(o->a40, --o->a48);
            sfx();
            o->e[1].ad = 1;
            o->e[1].a14 = 0x1e;
        } else if (canUp(o) && (k & 0x200002)) {
            upLoop(o);
            sfx();
            o->e[3].ad = 1;
            o->e[3].a14 = 0x1e;
        } else if (o->a48 > 0 && (k & 0x100001)) {
            dnLoop(o);
            sfx();
            o->e[2].ad = 1;
            o->e[2].a14 = 0x1e;
        }
    }
}
}
