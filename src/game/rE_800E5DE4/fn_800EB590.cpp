#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct BSeq { u8 b0; u8 b1; s16 kind; } BSeq;
typedef struct EP { u8 pad[0x30]; BSeq* seq; Handle* h1; Handle* h2; void* v3C; u8 b40; u8 pad41[5]; u8 b46; } EP;
typedef struct UI { u8 pad[0x12]; u8 b12; } UI;
typedef struct UR { UI* o; } UR;
typedef struct CC { u8 pad[0xE]; u8 bE; } CC;
typedef struct Cmd { u8 pad[0x30]; CC* ctl; } Cmd;
class Snd { public:
    virtual void v8(); virtual void vC(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C(); virtual void vA0(); virtual void vA4(); virtual void shake(int);
};
struct V : Vec { V(const Vec& o) { x = o.x; y = o.y; z = o.z; } };
extern "C" {
extern Snd* lbl_804CB5B8;
extern Vec fn_800D5B4C(Handle*);
extern int fn_801CE5B8(Handle*);
extern UR* fn_801CE474(Handle*);
extern int fn_801CFA90(BSeq*);
extern void fn_802549C4(const char*, const Vec&, f32);
extern void fn_801CB920(void*, EP*, GXColor, int);
extern void fn_8013C14C(int, int, void*, f32);
extern void fn_800EFC38(Handle*);
extern void fn_800EFCD4(Handle*);
extern char* fn_800D621C(BSeq*);
extern Cmd* fn_800E3810(char*, EP*);
extern void fn_800E48AC(Cmd*, f32, f32, f32);
extern void fn_800E5BB0(Cmd*, UnitObj*);
extern f32 fn_800D5F6C(Handle*);
extern void fn_800E49AC(Cmd*, f32);
#pragma pool_strings on
void pool_72a0() {
    const char* volatile s;
    s = "SFX_BMP_DAMAGE_DOOR_FINISH1"; /* 0x0 */
    s = "SFX_BMP_DAMAGE_DOOR1"; /* 0x1c */
    s = "SFX_BMP_DAMAGE_FINISH1"; /* 0x31 */
    s = "SFX_BMP_DAMAGE_THRUST1"; /* 0x48 */
    s = "SFX_BMP_DAMAGE_UP1"; /* 0x5f */
    s = "SFX_BMP_DAMAGE_DOWN1"; /* 0x72 */
    s = "SFX_BMP_DAMAGE_SPECIAL2"; /* 0x87 */
    s = "SFX_BMP_DAMAGE_SPECIAL1"; /* 0x9f */
    s = "SFX_BMP_NO_DAMAGE1"; /* 0xb7 */
    s = "\x8d""\\\x82""\xa6"""; /* 0xca */
    s = "SFX_BMP_MISS1"; /* 0xcf */
    s = "\x89""\x9c""\x8b""`\x82""P"; /* 0xdd */
    s = "\x89""\x9c""\x8b""`\x82""Q"; /* 0xe4 */
    s = "\x89""\x9c""\x8b""`\x82""R"; /* 0xeb */
    s = "\x89""\x9c""\x8b""`\x82""S"; /* 0xf2 */
    s = "\x89""\x9c""\x8b""`\x82""T"; /* 0xf9 */
    s = "\x8f""\xe3""\x8d""U\x8c""\x82""\x82""P"; /* 0x100 */
    s = "\x89""\xba""\x8d""U\x8c""\x82""\x82""P"; /* 0x109 */
    s = "\x8d""U\x8c""\x82""\x82""P"; /* 0x112 */
    s = "\x8f""\xe3""\x96""\x82""\x96""@\x82""P"; /* 0x119 */
    s = "\x89""\xba""\x96""\x82""\x96""@\x82""P"; /* 0x122 */
    s = "\x96""\x82""\x96""@\x82""P"; /* 0x12b */
    s = "\x83""K\x81""[\x83""h"; /* 0x132 */
    s = "\x92""e\x82""\xa9""\x82""\xea""\x82""P"; /* 0x139 */
    s = "\x92""e\x82""\xa9""\x82""\xea""\x82""Q"; /* 0x142 */
    s = "\x83""_\x83""\x81""\x81""[\x83""W"; /* 0x14b */
    s = "\x89""\xf1""\x94""\xf0"""; /* 0x154 */
    s = "magic"; /* 0x159 */
    s = ""; /* 0x15f */
}

#define S(s) fn_802549C4(s, V(pos), 0.0f);
void fn_800EB590(EP* p) {
    s16 kind = p->seq->kind;
    Vec pos = fn_800D5B4C(p->h2);
    switch (p->b40) {
    case 1:
        if (fn_801CE5B8(p->h2)) {
            S("SFX_BMP_DAMAGE_DOOR_FINISH1")
        } else {
            S("SFX_BMP_DAMAGE_DOOR1")
        }
        if (p->v3C) {
            GXColor c = {0xFF, 0xFF, 0xFF, 0xFF};
            fn_801CB920(p->v3C, p, c, 2);
        }
        break;
    default:
        if (fn_801CE5B8(p->h2)) {
            S("SFX_BMP_DAMAGE_FINISH1")
        } else {
            u8 w = 5;
            UR* u = fn_801CE474(p->h1);
            if (u) {
                if (u->o) w = u->o->b12;
                else w = 0x13;
            }
            switch (w) {
            case 1: case 3: case 13:
                S("SFX_BMP_DAMAGE_THRUST1")
                break;
            case 0: case 2: case 4:
                if (p->b46 & 1) {
                    S("SFX_BMP_DAMAGE_UP1")
                } else {
                    S("SFX_BMP_DAMAGE_DOWN1")
                }
                break;
            default:
                S("SFX_BMP_DAMAGE_DOWN1")
                break;
            }
        }
        break;
    }
    if (fn_801CFA90(p->seq)) {
        S("SFX_BMP_DAMAGE_SPECIAL2")
    } else if (kind == 0x6F) {
        S("SFX_BMP_DAMAGE_SPECIAL1")
    }
    if (kind == 0x6F) {
        fn_8013C14C(6, 2, p, 60.0f);
        lbl_804CB5B8->shake(0x10);
        fn_800EFC38(p->h2);
    } else {
        fn_8013C14C(6, 2, p, 15.0f);
        lbl_804CB5B8->shake(8);
        fn_800EFCD4(p->h2);
    }
    {
        char* n = fn_800D621C(p->seq);
        if (n) {
            Cmd* c = fn_800E3810(n, p);
            if (c) {
                switch (p->b40) {
                case 1:
                    fn_800E48AC(c, pos.x, pos.y, pos.z);
                    break;
                default:
                    fn_800E5BB0(c, p->h2->obj);
                    break;
                }
                fn_800E49AC(c, 180.0f + fn_800D5F6C(p->h1));
                c->ctl->bE = 3;
            }
        }
    }
}
}
