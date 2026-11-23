#include "game/rS_8023FD30/sndmgr.h"
/* Pause and unpause: sets a flag, starts a fader, then walks all four player pools.
   RawGuard reproduces the original scoped lock with an explicit on/off, because the guards'
   stack slots come out in reverse order of use. The declaration order of the locals came
   from a hill climb. */
extern "C" {
extern u32 lbl_804CBFE8[2];
struct RawGuard {
    void* vt;
    SndLockable* m;
    RawGuard() {}
    ~RawGuard() {}
    void on(SndLockable& x) { vt = lbl_80391888; m = &x; x.lock(); }
    void off() { vt = lbl_80391888; m->unlock(); }
};
#define GUARD_ON(g, mm) (g).on(*(mm));
#define GUARD_OFF(g) (g).off();
void fn_8024DEF0(f32 t) {
    RawGuard g;
    RawGuard g4;
    RawGuard g3;
    RawGuard g2;
    RawGuard g1;
    RawGuard g0;
    s32 i4;
    SndPlayer* s4;
    SndPlayer* s2;
    s32 i3;
    SndPlayer** p4;
    SndLockable* m0;
    s32 i1;
    SndPlayer* s1;
    SndPlayer* s3;
    SndPlayer** p1;
    SndPlayer** p2;
    SndLockable* m1;
    SndLockable* m3;
    SndLockable* m2;
    s32 i2;
    SndPlayer** p3;
    SndLockable* m4;
    m0 = &sMutex;
    GUARD_ON(g, m0)
    m0->lock();
    lbl_804CBFE8[1] |= 1;
    m0->unlock();
    m0->lock();
    sFader6B8.t = 0;
    sFader6B8.frames = t / 16.666666f;
    sFader6B8.from = sFader6B8.cur;
    sFader6B8.to = 0.0f;
    m0->unlock();
    GUARD_ON(g0, m0)
        m1 = &sMutex;
        GUARD_ON(g1, m1)
        p1 = sPoolA;
        for (i1 = 0; i1 < 4; i1++, p1++) {
            m1->lock();
            s1 = 0;
            if ((s8)i1 >= 0 && (s8)i1 < 4) {
                s1 = *p1;
            }
            m1->unlock();
            if (s1 != 0 && s1->isActive()) {
                s1->setA(t);
            }
        }
        GUARD_OFF(g1)
        m2 = &sMutex;
        GUARD_ON(g2, m2)
        p2 = sPoolB;
        for (i2 = 0; i2 < 16; i2++, p2++) {
            m2->lock();
            s2 = 0;
            if ((s8)i2 >= 0 && (s8)i2 < 16) {
                s2 = *p2;
            }
            m2->unlock();
            if (s2 != 0 && s2->isActive()) {
                s2->setA(t);
            }
        }
        GUARD_OFF(g2)
        m3 = &sMutex;
        GUARD_ON(g3, m3)
        p3 = sPoolC;
        for (i3 = 0; i3 < 16; i3++, p3++) {
            m3->lock();
            s3 = 0;
            if ((s8)i3 >= 0 && (s8)i3 < 16) {
                s3 = *p3;
            }
            m3->unlock();
            if (s3 != 0 && s3->isActive()) {
                s3->setA(t);
            }
        }
        GUARD_OFF(g3)
        m4 = &sMutex;
        GUARD_ON(g4, m4)
        p4 = sPoolD;
        for (i4 = 0; i4 < 4; i4++, p4++) {
            m4->lock();
            s4 = 0;
            if ((s8)i4 >= 0 && (s8)i4 < 4) {
                s4 = *p4;
            }
            m4->unlock();
            if (s4 != 0 && s4->isActive()) {
                s4->setA(t);
            }
        }
        GUARD_OFF(g4)
    GUARD_OFF(g0)
    GUARD_OFF(g)
}

void fn_8024E3AC(f32 t) {
    RawGuard g;
    RawGuard g4;
    RawGuard g3;
    RawGuard g2;
    RawGuard g1;
    RawGuard g0;
    s32 i4;
    SndPlayer* s4;
    SndPlayer* s2;
    s32 i3;
    SndPlayer** p4;
    SndLockable* m0;
    s32 i1;
    SndPlayer* s1;
    SndPlayer* s3;
    SndPlayer** p1;
    SndPlayer** p2;
    SndLockable* m1;
    SndLockable* m3;
    SndLockable* m2;
    s32 i2;
    SndPlayer** p3;
    SndLockable* m4;
    m0 = &sMutex;
    GUARD_ON(g, m0)
    m0->lock();
    lbl_804CBFE8[1] &= ~1;
    m0->unlock();
    m0->lock();
    sFader6B8.t = 0;
    sFader6B8.frames = t / 16.666666f;
    sFader6B8.from = sFader6B8.cur;
    sFader6B8.to = 1.0f;
    m0->unlock();
    GUARD_ON(g0, m0)
        m1 = &sMutex;
        GUARD_ON(g1, m1)
        p1 = sPoolA;
        for (i1 = 0; i1 < 4; i1++, p1++) {
            m1->lock();
            s1 = 0;
            if ((s8)i1 >= 0 && (s8)i1 < 4) {
                s1 = *p1;
            }
            m1->unlock();
            if (s1 != 0 && s1->isActive() && s1->canSetB()) {
                s1->setB(t);
            }
        }
        GUARD_OFF(g1)
        m2 = &sMutex;
        GUARD_ON(g2, m2)
        p2 = sPoolB;
        for (i2 = 0; i2 < 16; i2++, p2++) {
            m2->lock();
            s2 = 0;
            if ((s8)i2 >= 0 && (s8)i2 < 16) {
                s2 = *p2;
            }
            m2->unlock();
            if (s2 != 0 && s2->isActive() && s2->canSetB()) {
                s2->setB(t);
            }
        }
        GUARD_OFF(g2)
        m3 = &sMutex;
        GUARD_ON(g3, m3)
        p3 = sPoolC;
        for (i3 = 0; i3 < 16; i3++, p3++) {
            m3->lock();
            s3 = 0;
            if ((s8)i3 >= 0 && (s8)i3 < 16) {
                s3 = *p3;
            }
            m3->unlock();
            if (s3 != 0 && s3->isActive() && s3->canSetB()) {
                s3->setB(t);
            }
        }
        GUARD_OFF(g3)
        m4 = &sMutex;
        GUARD_ON(g4, m4)
        p4 = sPoolD;
        for (i4 = 0; i4 < 4; i4++, p4++) {
            m4->lock();
            s4 = 0;
            if ((s8)i4 >= 0 && (s8)i4 < 4) {
                s4 = *p4;
            }
            m4->unlock();
            if (s4 != 0 && s4->isActive() && s4->canSetB()) {
                s4->setB(t);
            }
        }
        GUARD_OFF(g4)
    GUARD_OFF(g0)
    GUARD_OFF(g)
}

void fn_8024E8D8(f32 t) {
    RawGuard g;
    RawGuard g4;
    RawGuard g3;
    RawGuard g2;
    RawGuard g1;
    RawGuard g0;
    s32 i4;
    SndPlayer* s4;
    SndPlayer* s2;
    s32 i3;
    SndPlayer** p4;
    SndLockable* m0;
    s32 i1;
    SndPlayer* s1;
    SndPlayer* s3;
    SndPlayer** p1;
    SndPlayer** p2;
    SndLockable* m1;
    SndLockable* m3;
    SndLockable* m2;
    s32 i2;
    SndPlayer** p3;
    SndLockable* m4;
    m0 = &sMutex;
    GUARD_ON(g, m0)
    m0->lock();
    lbl_804CBFE8[1] |= 2;
    m0->unlock();
    m0->lock();
    sFader6CC.t = 0;
    sFader6CC.frames = t / 16.666666f;
    sFader6CC.from = sFader6CC.cur;
    sFader6CC.to = 0.0f;
    m0->unlock();
    GUARD_ON(g0, m0)
        m1 = &sMutex;
        GUARD_ON(g1, m1)
        p1 = sPoolA;
        for (i1 = 0; i1 < 4; i1++, p1++) {
            m1->lock();
            s1 = 0;
            if ((s8)i1 >= 0 && (s8)i1 < 4) {
                s1 = *p1;
            }
            m1->unlock();
            if (s1 != 0 && s1->isActive()) {
                s1->setA(t);
            }
        }
        GUARD_OFF(g1)
        m2 = &sMutex;
        GUARD_ON(g2, m2)
        p2 = sPoolB;
        for (i2 = 0; i2 < 16; i2++, p2++) {
            m2->lock();
            s2 = 0;
            if ((s8)i2 >= 0 && (s8)i2 < 16) {
                s2 = *p2;
            }
            m2->unlock();
            if (s2 != 0 && s2->isActive()) {
                s2->setA(t);
            }
        }
        GUARD_OFF(g2)
        m3 = &sMutex;
        GUARD_ON(g3, m3)
        p3 = sPoolC;
        for (i3 = 0; i3 < 16; i3++, p3++) {
            m3->lock();
            s3 = 0;
            if ((s8)i3 >= 0 && (s8)i3 < 16) {
                s3 = *p3;
            }
            m3->unlock();
            if (s3 != 0 && s3->isActive()) {
                s3->setA(t);
            }
        }
        GUARD_OFF(g3)
        m4 = &sMutex;
        GUARD_ON(g4, m4)
        p4 = sPoolD;
        for (i4 = 0; i4 < 4; i4++, p4++) {
            m4->lock();
            s4 = 0;
            if ((s8)i4 >= 0 && (s8)i4 < 4) {
                s4 = *p4;
            }
            m4->unlock();
            if (s4 != 0 && s4->isActive()) {
                s4->setA(t);
            }
        }
        GUARD_OFF(g4)
    GUARD_OFF(g0)
    GUARD_OFF(g)
}

void fn_8024ED94(f32 t) {
    RawGuard g;
    RawGuard g4;
    RawGuard g3;
    RawGuard g2;
    RawGuard g1;
    RawGuard g0;
    s32 i4;
    SndPlayer* s4;
    s32 i2;
    s32 i3;
    SndPlayer** p4;
    SndLockable* m0;
    s32 i1;
    SndPlayer* s1;
    SndPlayer* s3;
    SndPlayer** p1;
    SndPlayer** p2;
    SndLockable* m1;
    SndLockable* m3;
    SndLockable* m2;
    SndPlayer* s2;
    SndPlayer** p3;
    SndLockable* m4;
    m0 = &sMutex;
    GUARD_ON(g, m0)
    m0->lock();
    lbl_804CBFE8[1] &= ~2;
    m0->unlock();
    m0->lock();
    lbl_804CBFE8[1] &= ~4;
    m0->unlock();
    m0->lock();
    sFader6CC.t = 0;
    sFader6CC.frames = t / 16.666666f;
    sFader6CC.from = sFader6CC.cur;
    sFader6CC.to = 1.0f;
    m0->unlock();
    GUARD_ON(g0, m0)
        m1 = &sMutex;
        GUARD_ON(g1, m1)
        p1 = sPoolA;
        for (i1 = 0; i1 < 4; i1++, p1++) {
            m1->lock();
            s1 = 0;
            if ((s8)i1 >= 0 && (s8)i1 < 4) {
                s1 = *p1;
            }
            m1->unlock();
            if (s1 != 0 && s1->isActive() && s1->canSetB()) {
                s1->setB(t);
            }
        }
        GUARD_OFF(g1)
        m2 = &sMutex;
        GUARD_ON(g2, m2)
        p2 = sPoolB;
        for (i2 = 0; i2 < 16; i2++, p2++) {
            m2->lock();
            s2 = 0;
            if ((s8)i2 >= 0 && (s8)i2 < 16) {
                s2 = *p2;
            }
            m2->unlock();
            if (s2 != 0 && s2->isActive() && s2->canSetB()) {
                s2->setB(t);
            }
        }
        GUARD_OFF(g2)
        m3 = &sMutex;
        GUARD_ON(g3, m3)
        p3 = sPoolC;
        for (i3 = 0; i3 < 16; i3++, p3++) {
            m3->lock();
            s3 = 0;
            if ((s8)i3 >= 0 && (s8)i3 < 16) {
                s3 = *p3;
            }
            m3->unlock();
            if (s3 != 0 && s3->isActive() && s3->canSetB()) {
                s3->setB(t);
            }
        }
        GUARD_OFF(g3)
        m4 = &sMutex;
        GUARD_ON(g4, m4)
        p4 = sPoolD;
        for (i4 = 0; i4 < 4; i4++, p4++) {
            m4->lock();
            s4 = 0;
            if ((s8)i4 >= 0 && (s8)i4 < 4) {
                s4 = *p4;
            }
            m4->unlock();
            if (s4 != 0 && s4->isActive() && s4->canSetB()) {
                s4->setB(t);
            }
        }
        GUARD_OFF(g4)
    GUARD_OFF(g0)
    GUARD_OFF(g)
}

}
