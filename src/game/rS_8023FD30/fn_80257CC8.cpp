#include "game/rS_8023FD30/sndmgr.h"
/* The sound manager's per-frame update: advances every volume fader, pushes the products
   to the effect channels, ticks the players of all four pools and the effect mix faders. */
class SndPlayerU {
public:
    virtual void v08();
    virtual void v0C();
    virtual int isActive(); /* +0x10 */
    virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30();
    virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5C(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70();
    virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80();
    virtual void v84(); virtual void v88(); virtual void v8C(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9C(); virtual void vA0();
    virtual void vA4(); virtual void vA8(); virtual void vAC(); virtual void vB0();
    virtual void vB4(); virtual void vB8();
    virtual void update(int); /* +0xBC */
};
struct FlagSet {
    u32 pad;
    u32 w[1];
};
extern "C" {
extern FlagSet lbl_804CBFE8;
void* fn_802AFE04(void*, int);
void fn_802B1A68(void*, f32);
void fn_802ACE4C(void*, f32);
void fn_802ACE54(void*, f32);
void fn_802ACE5C(void*, f32);
void fn_802AFA64(void*);

static inline u32 flagGet(u32 n) {
    SndLockable* m = &sMutex;
    m->lock();
    const u32* p = lbl_804CBFE8.w;
    u32 q = n;
    while (q >= 32) {
        q -= 32;
        p++;
    }
    n = q;
    u32 r = (*p & (1 << n)) != 0;
    m->unlock();
    return r;
}

static inline void flagSet(u32 n) {
    SndLockable* m = &sMutex;
    m->lock();
    u32* p = lbl_804CBFE8.w;
    u32 q = n;
    while (q >= 32) {
        q -= 32;
        p++;
    }
    n = q;
    *p |= 1 << n;
    m->unlock();
}

static inline f32 upd(SndFader& f) {
    if (f.t < f.frames) {
        f.cur = (f.to - f.from) * ((f32)f.t / (f32)f.frames) + f.from;
        f.t++;
    } else {
        f.cur = f.to;
    }
    return f.cur;
}

#define POOL(arr, n) \
    { \
        SndPlayerU* s; \
        SndPlayerU** p = (SndPlayerU**)arr; \
        SndLockable* m = &sMutex; \
        int i; \
        for (i = 0; i < n; i++, p++) { \
            m->lock(); \
            s = 0; \
            if ((s8)i >= 0 && (s8)i < n) { \
                s = *p; \
            } \
            m->unlock(); \
            if (s != 0 && s->isActive()) { \
                s->update(0); \
            } \
        } \
    }

void fn_80257CC8(void) {
    SndGuard g(sMutex);
    if (flagGet(2)) {
        return;
    }
    if (flagGet(1)) {
        flagSet(2);
    }
    f32 base = upd(sFader6A4);
    base *= upd(sFader6B8);
    base *= upd(sFader6CC);
    f32 v;
    s16 i;
    v = upd(sFader708);
    for (i = 0; i < 8; i++) {
        v *= upd(sChanA[i]);
    }
    fn_802B1A68(fn_802AFE04(sEffect, 0), base * v);
    v = upd(sFader71C);
    for (i = 0; i < 8; i++) {
        v *= upd(sChanB[i]);
    }
    fn_802B1A68(fn_802AFE04(sEffect, 1), base * v);
    v = upd(sFader730);
    for (i = 0; i < 8; i++) {
        v *= upd(sChanC[i]);
    }
    fn_802B1A68(fn_802AFE04(sEffect, 2), base * v);
    v = upd(sFader744);
    for (i = 0; i < 8; i++) {
        v *= upd(sChanD[i]);
    }
    fn_802B1A68(fn_802AFE04(sEffect, 3), base * v);
    fn_802ACE4C(sPad098, upd(sFader9D8));
    fn_802ACE54(sPad098, upd(sFader9EC));
    fn_802ACE5C(sPad098, upd(sFaderA00));
    POOL(sPoolA, 4)
    POOL(sPoolB, 16)
    POOL(sPoolC, 16)
    POOL(sPoolD, 4)
    *(f32*)(sEffect + 0xE0) = upd(sFader6A4);
    *(f32*)(sEffect + 0xE4) = upd(sFader6E0);
    *(f32*)(sEffect + 0xE8) = upd(sFader6F4);
    fn_802AFA64(sEffect);
}
}
