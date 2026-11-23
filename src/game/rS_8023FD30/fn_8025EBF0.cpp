/* fn_8025EBF0: static initialiser of the sound manager unit (the statics at
   lbl_8042E798; full layout in equiv/fn_8024CF54.cpp). Round 21, exact (needs
   fn_8025EBF0.symbols.json: "...bss.0" = lbl_8042E798). Hand-written; the
   original is the compiler's __sinit for the static objects named in the
   comments below: a lockable (vtable lbl_80380888 + OSMutex), the heap, three
   library objects with their destructors, the effect object (vtables
   lbl_80391840 / +0x14, three floats 1, 0, 0), two effect blocks, the faders
   (the default one at 1.0, the rest 0.0), four arrays of eight channel faders
   (constructor fn_8025F398) and the command mutex.
   The statics are defined once for the unit in sndmgr.h (included here).
   Port caveats: the sChain... arrays are the compiler's destructor-chain
   records; the byte arrays stand for library objects whose classes are not
   declared here. Use real static objects with constructors. */
#include "game/rS_8023FD30/sndmgr.h"
#pragma use_lmw_stmw off

/* The statics are sndmgr.h's block (one definition for the unit); the effect object is
   sEffect seen through its fields. */
struct Effect { u8 pad0[8]; void* vt8; void* vtC; u8 pad10[0xd0]; f32 xe0, xe4, xe8; };
#define sEffectObj (*(Effect*)sEffect)

extern "C" {
void fn_8031DD0C(void*);        /* OSInitMutex */
void __register_global_object(void* o, void* dtor, void* chain);
void fn_8028BFD8(void*, void*, void*, u32, u32);   /* __construct_array */
void fn_802B1628(void*);
void fn_802B1670(void*, int);
void fn_802ACE64(void*);
void fn_8025EEF0(void*, int);
void fn_802ACC2C(void*);
void fn_8025EF50(void*, int);
void fn_802A47F4(void*);
void fn_802A4840(void*, int);
void fn_802AEFEC(void*);
void fn_8025F1D4(void*, int);
void fn_802A6310(void*);
void fn_8025F2A0(void*, int);
void fn_802A5F28(void*);
void fn_8025F31C(void*, int);
void fn_8025F398(void*);
extern u8 lbl_80380888[];
extern u8 lbl_80391840[];
extern u8 lbl_80391150[];
extern void* lbl_804CBFE8;

static inline void finit(SndFader& f, f32 v) {
    f.t = 0;
    f.frames = 0;
    f.cur = v;
    f.from = v;
    f.to = v;
}
static inline void lockInit(SndLockRaw& l) {
    l.vt = lbl_80380888;
    fn_8031DD0C(l.mutex);
}

void fn_8025EBF0(void) {
    lockInit(sMutexRaw);
    fn_802B1628(sHeap);
    __register_global_object(sHeap, fn_802B1670, sChain01C);
    fn_802ACE64(sMember60);
    __register_global_object(sMember60, fn_8025EEF0, sChain054);
    fn_802ACC2C(sPad098);
    __register_global_object(sPad098, fn_8025EF50, sChain088);
    fn_802A47F4(sGroups);
    __register_global_object(sGroups, fn_802A4840, sChain0F0);
    fn_802AEFEC(&sEffectObj);
    sEffectObj.vt8 = lbl_80391840;
    sEffectObj.vtC = lbl_80391840 + 0x14;
    sEffectObj.xe0 = 1.0f;
    sEffectObj.xe4 = 0.0f;
    sEffectObj.xe8 = 0.0f;
    __register_global_object(&sEffectObj, fn_8025F1D4, sChain288);
    fn_802A6310(sEffA);
    __register_global_object(sEffA, fn_8025F2A0, sChain380);
    fn_802A5F28(sEffB);
    __register_global_object(sEffB, fn_8025F31C, sChain518);
    lbl_804CBFE8 = lbl_80391150;
    finit(sFaderDefault, 1.0f);
    finit(sFader6A4, 0.0f);
    finit(sFader6B8, 0.0f);
    finit(sFader6CC, 0.0f);
    finit(sFader6E0, 0.0f);
    finit(sFader6F4, 0.0f);
    finit(sFader708, 0.0f);
    finit(sFader71C, 0.0f);
    finit(sFader730, 0.0f);
    finit(sFader744, 0.0f);
    fn_8028BFD8(sChanA, fn_8025F398, 0, 0x14, 8);
    fn_8028BFD8(sChanB, fn_8025F398, 0, 0x14, 8);
    fn_8028BFD8(sChanC, fn_8025F398, 0, 0x14, 8);
    fn_8028BFD8(sChanD, fn_8025F398, 0, 0x14, 8);
    finit(sFader9D8, 0.0f);
    finit(sFader9EC, 0.0f);
    finit(sFaderA00, 0.0f);
    lockInit(sCmdMutexRaw);
}
}
