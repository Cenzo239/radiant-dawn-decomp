#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct Ctl { u8 pad[0x18]; u32 flags; u8 pad1C[0x48]; GXColor col; u8 pad68[0x3C]; struct Sh* a4; int a8; } Ctl;
typedef struct Cmd { u8 pad[0x18]; struct Sh* proc; u8 pad1C[0x14]; Ctl* ctl; } Cmd;
typedef struct Sh { u8 pad[0x7C]; s8 x0; s8 y0; s8 x1; s8 y1; s16 h80; s16 h82; f32 f84; s16 h88; s16 h8A; f32 f8C; } Sh;
typedef struct Sh2 { u8 pad[0x7C]; s8 x0; s8 y0; s8 x1; s8 y1; f32 f80; f32 f84; s16 h88; s16 h8A; f32 f8C; } Sh2;
class Snd { public:
    virtual void v8(); virtual void vC(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C(); virtual void vA0(); virtual void vA4(); virtual void shake(int);
};
static inline Vec Mk(f32 x, f32 y, f32 z) { Vec v; v.x = x; v.y = y; v.z = z; return v; }
struct V : Vec { V(const Vec& o) { x = o.x; y = o.y; z = o.z; } };
extern "C" {
extern Snd* lbl_804CB5B8;
extern u8 lbl_803EC898[];
extern f32 fn_801142F0(void*, f32, f32);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f32 fn_8001EBC8(int, f32, f32, f32, f32);
extern f32 fn_8001ECE4(int, f32, f32, f32, f32);
extern void fn_80312654(f32 (*)[4], int, f32);
extern void fn_80312DB4(f32 (*)[4], const Vec*, Vec*);
extern void fn_800E48AC(Cmd*, f32, f32, f32);
extern void fn_800E4918(Cmd*, f32);
extern void fn_8013C14C(int, int, void*, f32);
extern void fn_802549C4(const char*, const Vec&, f32);
#pragma pool_strings on
void pool_707c() {
    const char* volatile s;
    s = "\x8f""\xf1"""; /* 0x0 */
    s = "SFX_BMP_MISS1"; /* 0x3 */
    s = "\x83""_\x83""\x81""\x81""[\x83""W"; /* 0x11 */
    s = "EID_HEALINGHAND"; /* 0x1a */
    s = "r_hand"; /* 0x2a */
    s = "EID_HEALINGHAND_HEAL"; /* 0x31 */
    s = "\x89""\x9c""\x8b""`\x82""T"; /* 0x46 */
    s = "EID_CHANT"; /* 0x4d */
    s = "EID_BLISS"; /* 0x57 */
    s = "EID_SORROW"; /* 0x61 */
    s = "EID_BRAVE"; /* 0x6c */
    s = "EID_HEAL"; /* 0x76 */
    s = "EID_BOON"; /* 0x7f */
    s = "EID_BLESSING"; /* 0x88 */
    s = "EID_CHANT_H"; /* 0x95 */
    s = "EID_BLISS_H"; /* 0xa1 */
    s = "EID_SORROW_H"; /* 0xad */
    s = "EID_BRAVE_H"; /* 0xba */
    s = "EID_HEAL_H"; /* 0xc6 */
    s = "EID_BLESSING_HEAL"; /* 0xd1 */
    s = "EID_BOON_CURE"; /* 0xe3 */
    s = "EID_EVILEYE_STONE"; /* 0xf1 */
    s = "EID_EVILEYE"; /* 0x103 */
    s = "SFX_BMP_NO_DAMAGE1"; /* 0x10f */
    s = "SFX_BMP_DAMAGE_FINISH1"; /* 0x122 */
    s = "SFX_BMP_DAMAGE_DOWN1"; /* 0x139 */
    s = "EID_CURE"; /* 0x14e */
    s = "EID_POISON_H"; /* 0x157 */
    s = "EID_ATTK1"; /* 0x164 */
    s = "EID_LAVA01"; /* 0x16e */
    s = "EID_LAVA02"; /* 0x179 */
    s = "EID_STATE_RECOVER"; /* 0x184 */
    s = "EID_SHOOTER"; /* 0x196 */
    s = "\x8d""\\\x82""\xa6"""; /* 0x1a2 */
    s = "\x89""\xf1""\x94""\xf0"""; /* 0x1a7 */
    s = "SFX_BMP_DAMAGE_THRUST1"; /* 0x1ac */
    s = "SFX_BMP_DAMAGE_SPECIAL1"; /* 0x1c3 */
    s = "SFX_BMP_ROCK_BREAK2"; /* 0x1db */
    s = "EID_ONAGER"; /* 0x1ef */
    s = "EID_ONAGERSTONES"; /* 0x1fa */
    s = ""; /* 0x20b */
}

static inline void SetCol(Cmd* c, int a) { GXColor col = {0x80, 0x80, 0x80, a}; GXColor t = col; c->ctl->col = t; }
int fn_800E9DF0(Cmd* c) {
    Sh* p = c->proc;
    if (p->h80 >= p->h82) return 0;
    p->h80++;
    {
/*P*/
    f32 s;
    f32 d;
    f32 x;
    f32 ax;
    f32 ay;
    f32 az;
    f32 bx;
    f32 by;
    f32 y;
    f32 bz;
    f32 r;
    f32 h;
    f32 z;
/*E*/
    ax = (f32)p->x0 + 0.5f;
    ay = (f32)p->y0 + 0.5f;
    az = fn_801142F0(lbl_803EC898, ax, ay);
    bx = (f32)p->x1 + 0.5f;
    by = (f32)p->y1 + 0.5f;
    bz = fn_801142F0(lbl_803EC898, bx, by);
    x = fn_8001EF30(ax, bx, p->h82, p->h80);
    y = fn_8001EF30(ay, by, p->h82, p->h80);
    z = fn_8001EF30(az, bz, p->h82, p->h80);
    int a = 0xFF;
    f32 m[3][4];
    Vec v = {0.0f, 0.0f, 0.0f};
    v.y = p->f84;
    fn_80312654(m, 0x58, 0.08726646f);
    fn_80312DB4(m, &v, &v);
    d = 0.75f * v.z;
    h = 0.5f * p->h82;
    if (p->h80 < h) {
        r = z + fn_8001EBC8(2, -0.25f, -d, h, p->h80);
        s = fn_8001EBC8(2, -5.0f, 0.0f, h, p->h80);
        a = fn_8001EBC8(2, 0.0f, 255.0f, h, p->h80);
    } else {
        r = z + fn_8001ECE4(2, -d, 0.0f, h, p->h80 - h);
        s = fn_8001ECE4(2, 0.0f, 5.0f, h, p->h80 - h);
    }
    fn_800E48AC(c, x, y, r);
    SetCol(c, a);
    fn_800E4918(c, s);
    if (p->h80 >= p->h82) c->ctl->flags &= ~0x800;
    }
    return 0;
}
}
