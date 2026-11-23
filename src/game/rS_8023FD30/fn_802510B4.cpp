#include "game/rS_8023FD30/sndmgr.h"

static inline BOOL chanValid(s8 i) {
    BOOL r = FALSE;
    if (i >= 0 && i < 8) {
        r = TRUE;
    }
    return r;
}

static inline SndFader& chanFader(SndFader* arr, s8 i) {
    return chanValid(i) ? arr[i] : sFaderDefault;
}

#pragma use_lmw_stmw on
extern "C" {

f32 fn_802510B4(s8 i) {
    SndLockable& m = sMutex;
    f32 v;
    m.lock();
    if (chanValid(i)) {
        v = sChanA[i].cur;
    } else {
        v = sFaderDefault.cur;
    }
    m.unlock();
    return v;
}

SndFader* fn_80251174(s8 i) {
    SndLockable& m = sMutex;
    SndFader* v;
    m.lock();
    v = &chanFader(sChanA, i);
    m.unlock();
    return v;
}

SndFader* fn_8025121C(s8 i) {
    SndLockable& m = sMutex;
    SndFader* v;
    m.lock();
    v = &chanFader(sChanB, i);
    m.unlock();
    return v;
}

/* Register allocation note: the declaration order below came from a hill climb. */
void fn_802512C4(f32 t) {
    s32 i4;
    s32 i2;
    SndPlayer* s1;
    SndPlayer* s4;
    s32 i1;
    SndPlayer** p1;
    SndPlayer** p2;
    SndLockable* m1;
    SndLockable* m2;
    SndLockable* m3;
    SndPlayer** p3;
    SndLockable* m4;
    SndPlayer* s3;
    SndPlayer* s2;
    s32 i3;



    SndGuard l(sMutex);
    m1 = &sMutex;
    {
    SndGuard l1(*m1);
    p1 = sPoolA;
    for (i1 = 0; i1 < 4; i1++, p1++) {
        m1->lock();
        s1 = 0;
        if ((s8)i1 >= 0 && (s8)i1 < 4) {
            s1 = *p1;
        }
        m1->unlock();
        if (s1 != 0 && s1->isActive()) {
            s1->stop(t);
            m1->lock();
            if ((s8)i1 >= 0 && (s8)i1 < 4) {
                *p1 = 0;
            }
            m1->unlock();
            if (s1) {
                if (s1) {
                    s1->destroy(1);
                }
            }
        }
    }
    }
    m2 = &sMutex;
    {
    SndGuard l2(*m2);
    p2 = sPoolB;
    for (i2 = 0; i2 < 16; i2++, p2++) {
        m2->lock();
        s2 = 0;
        if ((s8)i2 >= 0 && (s8)i2 < 16) {
            s2 = *p2;
        }
        m2->unlock();
        if (s2 != 0 && s2->isActive()) {
            s2->stop(t);
            m2->lock();
            if ((s8)i2 >= 0 && (s8)i2 < 16) {
                *p2 = 0;
            }
            m2->unlock();
            if (s2) {
                if (s2) {
                    s2->destroy(1);
                }
            }
        }
    }
    }
    m3 = &sMutex;
    {
    SndGuard l3(*m3);
    p3 = sPoolC;
    for (i3 = 0; i3 < 16; i3++, p3++) {
        m3->lock();
        s3 = 0;
        if ((s8)i3 >= 0 && (s8)i3 < 16) {
            s3 = *p3;
        }
        m3->unlock();
        if (s3 != 0 && s3->isActive()) {
            s3->stop(t);
            m3->lock();
            if ((s8)i3 >= 0 && (s8)i3 < 16) {
                *p3 = 0;
            }
            m3->unlock();
            if (s3) {
                if (s3) {
                    s3->destroy(1);
                }
            }
        }
    }
    }
    m4 = &sMutex;
    {
    SndGuard l4(*m4);
    for (i4 = 0; i4 < 4; i4++) {
        m4->lock();
        s4 = 0;
        if ((s8)i4 >= 0 && (s8)i4 < 4) {
            s4 = sPoolD[i4];
        }
        m4->unlock();
        if (s4 != 0 && s4->isActive()) {
            s4->stop(t);
            m4->lock();
            if ((s8)i4 >= 0 && (s8)i4 < 4) {
                sPoolD[i4] = 0;
            }
            m4->unlock();
            if (s4) {
                if (s4) {
                    s4->destroy(1);
                }
            }
        }
    }
    }
}
}
