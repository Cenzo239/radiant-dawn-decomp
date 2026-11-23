/* NEAR MISS (size 0x90 vs 0x94): the original materialises the pool string
 * base+0x46 into r31 before calling fn_8002DD1C (string-literal + inline
 * artefact). With extern lbl_8036707C + offset the add is sunk into the else
 * branch. Probably needs the real string literals of the pool. */
#include "game/rE_800E5DE4/types.h"
extern EvProc* fn_80081194(void* type, void* parent);
extern void fn_800E5DE4(EvProc* p, void (*cb)(EvProc*), const char* name);
extern int fn_8002DD1C(void*);
extern s8 fn_800F0994(const char*);
extern u8 lbl_803C8E80[];
extern u8 lbl_8036707C[];

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
static inline void EvProc_SetSkill(EvProc* p, const char* name) {
    if (fn_8002DD1C(lbl_803C8E80) == 2) {
        p->unk6E = -1;
    } else {
        p->unk6E = fn_800F0994(name);
    }
}

extern u8 lbl_80384618[];

void fn_800E7DDC(void* parent, void (*cb)(EvProc*)) {
    EvProc* p = fn_80081194(lbl_80384618, parent);
    fn_800E5DE4(p, cb, "EID_HEALINGHAND_HEAL");
    EvProc_SetSkill(p, "\x89""\x9c""\x8b""`\x82""T");
}
