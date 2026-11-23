#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct BSeq { u8 b0; u8 b1; s16 kind; } BSeq;
typedef struct EP { u8 pad[0x30]; BSeq* seq; Handle* h1; Handle* h2; void* a1; void* a2; u8 doneCb; u8 pad45[0x2F]; void (*cb)(struct EP*); u8 b78; } EP;
typedef struct Cmd { u8 pad[0x18]; EP* proc; } Cmd;
class Snd { public:
    virtual void v8(); virtual void vC(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C(); virtual void vA0(); virtual void vA4(); virtual void shake(int);
};
extern "C" {
extern Snd* lbl_804CB5B8;
extern int fn_800E46C4(Cmd*, int);
extern Vec fn_800D5B4C(Handle*);
extern Vec fn_800D5C44(Handle*);
extern void fn_8013C14C(int, int, EP*, f32);
extern void fn_800EE1BC(Vec, EP*);
extern void fn_800EDE14(Vec, EP*);
extern void fn_800EE270(Vec, EP*);
extern void fn_800EDEC8(Vec, EP*);
extern void fn_800EE61C(Vec, int, EP*);
extern void fn_800EE6CC(Vec, int, EP*);
extern void fn_802549C4(const char*, const Vec&, f32);
extern int fn_801CE5B8(Handle*);
extern void fn_800EFEB8(Handle*, int, EP*);
extern void fn_80103234(void*, int, int, EP*);
extern void fn_80102C6C(void*, const char*, int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_80102CD8(void*, p32arg, p32arg, p32arg);
extern FE10_PROTO void fn_80102D70(void*, const char*, p32arg, p32arg);
#else
extern void fn_80102CD8(void*, int, int, int);
extern void fn_80102D70(void*, const char*, int, int);
#endif
extern void fn_8008319C(Cmd*);
extern void fn_800E28E4(Cmd*);
extern Handle* fn_800D6840(BSeq*);
extern void fn_800EFC38(Handle*);
extern void fn_800EFCD4(Handle*);
extern void* fn_800D621C(BSeq*);
extern void* fn_800E3810(void*, EP*);
extern void fn_800E48AC(void*, f32, f32, f32);
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

struct V : Vec { V(const Vec& o) { x = o.x; y = o.y; z = o.z; } };
#define Snd(s, e) fn_802549C4(s, V(e), 0.0f);
static inline void* Act(Handle* h) { return h->obj ? h->obj->actor : 0; }
static inline int Neg(EP* p) {
    if (p->h2->unkE < 0) {
        switch (p->b78) {
        case 0: case 1: case 2:
            return 1;
        }
    }
    return 0;
}
void fn_800EA408(EP* p) {
/*P*/
    Handle* h;
    EP* q;
    s16 kind;
    s16 dmg;
/*E*/
    q = p;
    h = fn_800D6840(q->seq);
    kind = q->seq->kind;
    if (kind == 0x70) {
        fn_80102C6C(Act(h), "\x89""\xf1""\x94""\xf0", 2, 0, 0);
        fn_80102D70(Act(h), "\x8d""\\\x82""\xa6", 0x18, 0);
        fn_800EE270(fn_800D5C44(h), p);
        Snd("SFX_BMP_MISS1", fn_800D5B4C(h))
    } else {
        dmg = h->unkE;
        if (dmg == 0) {
            fn_800EDEC8(fn_800D5C44(h), p);
            Snd("SFX_BMP_NO_DAMAGE1", fn_800D5B4C(h))
            lbl_804CB5B8->shake(4);
        } else {
            if (fn_801CE5B8(h)) {
                Snd("SFX_BMP_DAMAGE_FINISH1", fn_800D5B4C(h))
            } else {
                Snd("SFX_BMP_DAMAGE_THRUST1", fn_800D5B4C(h))
            }
            fn_80102C6C(Act(h), "\x83""_\x83""\x81""\x81""[\x83""W", 2, 0, 0);
            fn_80102D70(Act(h), "\x8d""\\\x82""\xa6", 0x18, 0);
            if (kind == 0x6F) {
                fn_8013C14C(6, 2, p, 60.0f);
                lbl_804CB5B8->shake(0x10);
                fn_800EFC38(h);
                Snd("SFX_BMP_DAMAGE_SPECIAL1", fn_800D5B4C(h))
            } else {
                fn_8013C14C(6, 2, p, 15.0f);
                lbl_804CB5B8->shake(8);
                fn_800EFCD4(h);
            }
            fn_800EFEB8(h, dmg, p);
            fn_800EE6CC(fn_800D5C44(h), dmg, p);
        }
        fn_80103234(Act(h), 1, 4, p);
        void* n = fn_800D621C(p->seq);
        if (n) {
            Vec v = fn_800D5B4C(h);
            void* e = fn_800E3810(n, p);
            if (e) fn_800E48AC(e, v.x, v.y, v.z);
        }
    }
}
}
