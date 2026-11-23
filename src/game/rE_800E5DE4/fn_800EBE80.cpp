/* fn_800EB988: 3 of 123 words (n is r26, r28 in the original). fn_800EBE80: 8 of 146 words (return temp and copy of the fn_800D5B4C Vec are swapped on the stack).
 * fn_800EBB74 from this file is matched in ../fn_800EBB74.cpp. */
#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

class Pad {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void Rumble(int);
};

typedef struct BSeq { u8 pad[2]; s16 kind; u8 pad4[7]; u8 bB; u8 nC; u8 padD; u16 ids[1]; } BSeq;
typedef struct BtlProc {
    u8 pad[0x30];
    BSeq* seq;    /* 0x30 */
    Handle* h1;   /* 0x34 */
    Handle* h2;   /* 0x38 */
    void* v3C;    /* 0x3C */
    u8 b40;       /* 0x40 */
    u8 pad41[4];
    s8 b45;       /* 0x45 */
    s8 b46;       /* 0x46 */
    u8 pad47;
    s8 b48;       /* 0x48 */
    s8 b49;       /* 0x49 */
} BtlProc;
typedef struct HObj { u8 pad[0x48B]; u8 b48B; } HObj;

extern "C" {
extern Pad* lbl_804CB5B8;
extern void fn_800EFEB8(Handle*, int, BtlProc*);
extern Vec fn_800D5C44(Handle*);
extern Vec fn_800D5B4C(Handle*);
extern void fn_800EE61C(const Vec&, int, BtlProc*);
extern void fn_800EE1BC(Vec, BtlProc*);
extern void fn_800EDE14(const Vec&, BtlProc*);
extern void fn_800EB590(BtlProc*);
extern BOOL fn_801CFE78(BSeq*, u16);
extern int fn_801D0214(BSeq*, u16);
extern Handle* fn_801D0784(BSeq*, int);
extern BOOL fn_801CFDEC(BSeq*, u16);
extern BOOL fn_801D012C(BSeq*, u16);
extern void* fn_801D009C(BSeq*, u16);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_8013B9B0(void);
#else
extern void* fn_8013B9B0(void);
#endif
extern void fn_801CE2F4(void*, int, void*);
#if TARGET_PC
extern FE10_PROTO void fn_80102928(void*, int, int, int, p32arg);
extern FE10_PROTO void fn_80102D70(void*, const char*, p32arg, p32arg);
#else
extern void fn_80102928(void*, int, int, int, int);
extern void fn_80102D70(void*, const char*, int, int);
#endif
extern void* fn_80103234(void*, int, int, void*);
extern char* fn_800D621C(BSeq*);
extern void* fn_800E3810(char*, void*);
extern void fn_800E5BB0(void*, UnitObj*);
extern f32 fn_800D5F6C(Handle*);
extern void fn_800E49AC(void*, f32);
extern void fn_802549C4(const char*, const Vec&, f32);

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

#define OUCH "\x8d""\\\x82""\xa6"""
static inline void* Act(Handle* h) {
    return h->obj ? h->obj->actor : 0;
}
static inline void PopN(Vec v, int n, BtlProc* p) {
    fn_800EE61C(v, n, p);
}

static inline void Pop2(Vec v, BtlProc* p) {
    fn_800EDE14(v, p);
}
static inline void Snd(const char* s, const Vec& v) {
    Vec w;
    w = v;
    fn_802549C4(s, w, 0.0f);
}
static inline void Snd2(const char* s, Vec v) {
    Vec w;
    w = v;
    fn_802549C4(s, w, 0.0f);
}
static inline void Item(BtlProc* p, u16 id) {
    if (fn_801CFE78(p->seq, id)) {
        Handle* h = fn_801D0784(p->seq, fn_801D0214(p->seq, id));
        if ((!fn_801CFDEC(p->seq, id) || (int)p->seq->bB == 1) && h && fn_801D012C(p->seq, id)) {
            void* a = fn_801D009C(p->seq, id);
            HObj* o = (HObj*)h->obj;
            void* b = fn_8013B9B0();
            if (o->b48B) {
                fn_801CE2F4(a, 9, b);
            } else {
                fn_801CE2F4(a, 10, b);
            }
        }
    }
}
static inline void Snd3(Handle* h) {
    Vec w;
    w = fn_800D5B4C(h);
    fn_802549C4("SFX_BMP_MISS1", w, 0.0f);
}
static inline void Notify(BtlProc* p) {
    int i;
    for (i = 0; i < p->seq->nC; i++) {
        Item(p, p->seq->ids[i]);
    }
    p->b45++;
    p->b46++;
}
struct V : Vec { V(const Vec& o) { x = o.x; y = o.y; z = o.z; } };
void fn_800EBE80(BtlProc* p) {
    void* a = Act(p->h1);
    void* b = Act(p->h2);
    if (p->b40 != 2) {
        fn_800EE1BC(fn_800D5C44(p->h2), p);
    }
    Notify(p);
    fn_802549C4("SFX_BMP_MISS1", V(fn_800D5B4C(p->h2)), 0.0f);
    if (b) {
        if (p->b48 >= 0) {
            fn_80102928(b, p->b48, 2, 0, 0);
            fn_80102D70(b, OUCH, 8, 0);
        }
        if (p->b49 >= 0) {
            fn_80102928(a, p->b49, 2, 0, 0);
            fn_80102D70(a, OUCH, 8, 0);
        }
    }
}
}
