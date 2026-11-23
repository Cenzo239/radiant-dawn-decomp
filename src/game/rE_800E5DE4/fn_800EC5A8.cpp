#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
typedef struct BSeq { u8 b0; u8 b1; s16 kind; u8 pad4[5]; u8 b9; u8 padA; u8 bB; } BSeq;
typedef struct Actor2 { u8 pad[0x10]; } Actor2;
typedef struct UObj { u8 pad[0x3F0]; void* actor; u8 pad3F4[0x8A]; s8 b47E; } UObj;
typedef struct H2 { UObj* obj; } H2;
typedef struct BtlProc { u8 pad[0x30]; BSeq* seq; H2* h1; H2* h2; u8 pad3C[7]; u8 b43; u8 pad44[2]; u8 b46; s8 b47; s8 b48; s8 b49; } BtlProc;
typedef struct CF2 { u8 pad[0x10]; u8 b10; } CF2;
typedef struct CD { u8 pad[0x10]; CF2* v10; } CD;
extern "C" {
extern int fn_801CFA90(BSeq*);
extern int fn_801CFCE0(BSeq*);
extern int fn_800F4700(void*, const char*);
extern int fn_800F0994(const char*);
extern int fn_800F0A2C(int);
extern int fn_800F4628(void*, int);
extern void fn_800F651C(void*, int);
extern void fn_80083DC4(BtlProc*, int);
extern CD* fn_800F43F0(void*);
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

static inline int Find(void* a, const char* const& s) {
    if (a && fn_800F4700(a, s)) return fn_800F0994(s);
    return -1;
}
static inline void* Act(UObj* o) { return o ? o->actor : 0; }
static inline int Mag(void* a, int k) {
    if (!a) return -1;
    switch (k) {
    case 4: return Find(a, "\x92""e\x82""\xa9""\x82""\xea""\x82""P");
    case 5: return Find(a, "\x92""e\x82""\xa9""\x82""\xea""\x82""Q");
    }
    return -1;
}
void fn_800EC5A8(BtlProc* p) {
    UObj* o = p->h1->obj;
    void* a = Act(o);
    void* b = Act(p->h2->obj);
    int k;
    p->b47 = -1;
    p->b48 = -1;
    p->b49 = -1;
    p->b43 = 0;
    if (fn_801CFA90(p->seq)) {
        switch (p->seq->bB) {
        case 1: p->b47 = Find(a, "\x89""\x9c""\x8b""`\x82""P"); break;
        case 2: p->b47 = Find(a, "\x89""\x9c""\x8b""`\x82""Q"); break;
        case 3: p->b47 = Find(a, "\x89""\x9c""\x8b""`\x82""R"); break;
        case 4: p->b47 = Find(a, "\x89""\x9c""\x8b""`\x82""S"); break;
        case 5: p->b47 = Find(a, "\x89""\x9c""\x8b""`\x82""T"); break;
        }
    } else {
        switch (p->seq->b1) {
        case 1:
            if (o->b47E < 0) p->b47 = Find(a, "\x8f""\xe3""\x8d""U\x8c""\x82""\x82""P");
            if (o->b47E > 0) p->b47 = Find(a, "\x89""\xba""\x8d""U\x8c""\x82""\x82""P");
            if (p->b47 < 0) p->b47 = Find(a, "\x8d""U\x8c""\x82""\x82""P");
            break;
        case 2: case 3: case 4: case 5:
            if (o->b47E < 0) p->b47 = Find(a, "\x8f""\xe3""\x96""\x82""\x96""@\x82""P");
            if (o->b47E > 0) p->b47 = Find(a, "\x89""\xba""\x96""\x82""\x96""@\x82""P");
            if (p->b47 < 0) p->b47 = Find(a, "\x96""\x82""\x96""@\x82""P");
            break;
        }
        if ((int)p->seq->b1 != 6) {
            if (p->b46 & 1) {
                k = fn_800F0A2C(p->b47);
                if (k >= 0 && fn_800F4628(a, k)) p->b47 = k;
            }
            if (p->b47 < 0) {
                fn_80083DC4(p, 8);
                return;
            }
        }
    }
    switch (p->seq->kind) {
    case 0x6E:
    case 0x6F:
        if (fn_801CFCE0(p->seq)) {
            p->b48 = Find(b, "\x83""K\x81""[\x83""h");
            p->b49 = Mag(a, p->b47);
            p->b43 = 1;
        } else {
            p->b48 = Find(b, "\x83""_\x83""\x81""\x81""[\x83""W");
        }
        break;
    case 0x70:
        p->b48 = Find(b, "\x89""\xf1""\x94""\xf0""");
        if (b && (fn_800F43F0(b)->v10->b10 & 2)) {
            p->b49 = Mag(a, p->b47);
            p->b43 = 1;
        }
        break;
    }
    if (p->b47 >= 0) fn_800F651C(a, p->b47);
    if (p->b48 >= 0) fn_800F651C(b, p->b48);
    if (p->b49 >= 0) fn_800F651C(a, p->b49);
    if (p->seq->b9) {
        k = fn_800F0A2C(p->b47);
        if (k >= 0 && fn_800F4628(a, k)) fn_800F651C(a, k);
    }
}
}
