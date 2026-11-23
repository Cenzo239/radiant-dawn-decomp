#include "game/rS_8023FD30/audio.h"

/* Sound player pools of the sound manager at lbl_8042E798. Each pool is a table of
   pointers, indexed by a signed byte and guarded by the manager's mutex. */
class SndObj {
public:
    virtual void destroy(int);    /* +0x08 */
    virtual void v0C();
    virtual int isActive();       /* +0x10 */
    virtual void v14();
    virtual int isReady();        /* +0x18 */
    virtual void v1C();
    virtual void v20();
    virtual void stop(s32);     /* +0x24 */
    virtual void setA(s32);     /* +0x28 */
    virtual void setB(s32);     /* +0x2C */
    virtual void v30();
    virtual int canSetB();      /* +0x34 */
    virtual void fadeTo(f32, f32); /* +0x38 */
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual s64 startTime();      /* +0x94 */
    u8 pad04[8];
    const char** name;            /* +0x0C */
};

extern "C" {

extern SndObj* lbl_8042ED88[4];
extern SndObj* lbl_8042ED98[16];
extern SndObj* lbl_8042EDD8[16];
extern SndObj* lbl_8042EE18[4];
int fn_80291188(const char*, const char*);
s64 OSGetTime(void);

}

static inline SndObj* slotGet(SndMutex& m, SndObj** tbl, int n, int i) {
    SndObj* s;
    m.lock();
    s = 0;
    if ((s8)i >= 0 && (s8)i < n) {
        s = tbl[i];
    }
    m.unlock();
    return s;
}

#pragma use_lmw_stmw on
static inline SndObj* slotGetS(SndMutex& m, SndObj** tbl, int n, int i) {
    SndObj* s;
    m.lock();
    s = 0;
    if ((s8)i >= 0 && (s8)i < n) {
        s = tbl[(s8)i];
    }
    m.unlock();
    return s;
}

static inline SndObj* slotGetG(SndObj** tbl, int n, int i) {
    SndObj* s;
    SndMutex& m = lbl_8042E798;
    m.lock();
    s = 0;
    if ((s8)i >= 0 && (s8)i < n) {
        s = tbl[(s8)i];
    }
    m.unlock();
    return s;
}

extern "C" {

SndObj* fn_8024F3FC(s8 i) {
    return slotGetG(lbl_8042ED88, 4, i);
}

SndObj* fn_8024F484(s8 i) {
    return slotGetG(lbl_8042ED98, 16, i);
}

SndObj* fn_8024F50C(s8 i) {
    return slotGetG(lbl_8042EDD8, 16, i);
}

SndObj* fn_8024F594(s8 i) {
    return slotGetG(lbl_8042EE18, 4, i);
}

int fn_8024F7EC(const char*);
SndObj* fn_8024F61C(const char* name) {
    SndLock l(lbl_8042E798);
    SndObj* s;
    s32 i = fn_8024F7EC(name);
    if ((s8)i >= 0) {
        s = slotGetG(lbl_8042ED88, 4, i);
    } else {
        s = 0;
    }
    return s;
}

int fn_8024F92C(const char*);
SndObj* fn_8024F704(const char* name) {
    SndLock l(lbl_8042E798);
    SndObj* s;
    s32 i = fn_8024F92C(name);
    if ((s8)i >= 0) {
        s = slotGetG(lbl_8042EDD8, 16, i);
    } else {
        s = 0;
    }
    return s;
}

int fn_8024F7EC(const char* name) {
    SndMutex* m;
    SndLock l(lbl_8042E798);
    s32 found = -1;
    for (s32 i = 0; i < 4; i++) {
        m = &lbl_8042E798;
        SndObj* s = slotGet(*m, lbl_8042ED88, 4, i);
        if (s != 0 && s->isReady() && s->isActive()) {
            if (name == 0 || fn_80291188(name, *s->name) == 0) {
                found = i;
                break;
            }
        }
    }
    return found;
}

int fn_8024F92C(const char* name) {
    SndMutex* m;
    SndLock l(lbl_8042E798);
    s32 found = -1;
    for (s32 i = 0; i < 16; i++) {
        m = &lbl_8042E798;
        SndObj* s = slotGet(*m, lbl_8042EDD8, 16, i);
        if (s != 0 && s->isReady() && s->isActive()) {
            if (name == 0 || fn_80291188(name, *s->name) == 0) {
                found = i;
                break;
            }
        }
    }
    return found;
}

int fn_8024FA6C(const char* name) {
    SndMutex* m;
    SndLock l(lbl_8042E798);
    s32 found = -1;
    for (s32 i = 0; i < 4; i++) {
        m = &lbl_8042E798;
        SndObj* s = slotGet(*m, lbl_8042EE18, 4, i);
        if (s != 0 && s->isReady() && s->isActive()) {
            if (name == 0 || fn_80291188(name, *s->name) == 0) {
                found = i;
                break;
            }
        }
    }
    return found;
}

int fn_8024FBAC(const char* name) {
    SndMutex* m;
    SndLock l(lbl_8042E798);
    s32 found = -1;
    s64 best = OSGetTime();
    s32 i = 0;
loop:
    m = &lbl_8042E798;
    SndObj* s = slotGet(*m, lbl_8042ED98, 16, i);
    if (s != 0 && s->isReady() && s->isActive() && s->startTime() < best) {
        if (name == 0 || fn_80291188(name, *s->name) == 0) {
            found = i;
            best = s->startTime();
        }
    }
    i++;
    if (i < 16) goto loop;
    return found;
}

int fn_8024FD40(const char* name) {
    SndMutex* m;
    SndLock l(lbl_8042E798);
    s32 found = -1;
    s64 best = OSGetTime();
    s32 i = 0;
loop:
    m = &lbl_8042E798;
    SndObj* s = slotGet(*m, lbl_8042EDD8, 16, i);
    if (s != 0 && s->isReady() && s->isActive() && s->startTime() < best) {
        if (name == 0 || fn_80291188(name, *s->name) == 0) {
            found = i;
            best = s->startTime();
        }
    }
    i++;
    if (i < 16) goto loop;
    return found;
}

int fn_8024FED4(const char* name) {
    SndMutex* m;
    SndLock l(lbl_8042E798);
    s32 found = -1;
    s64 best = OSGetTime();
    s32 i = 0;
loop:
    m = &lbl_8042E798;
    SndObj* s = slotGet(*m, lbl_8042EE18, 4, i);
    if (s != 0 && s->isReady() && s->isActive() && s->startTime() < best) {
        if (name == 0 || fn_80291188(name, *s->name) == 0) {
            found = i;
            best = s->startTime();
        }
    }
    i++;
    if (i < 4) goto loop;
    return found;
}

s8 fn_80250068(const char* name) {
    SndMutex* m;
    s32 count;
    {
        SndLock l(lbl_8042E798);
        count = 0;
        s32 i = 0;
    loop:
        m = &lbl_8042E798;
        SndObj* s = slotGet(*m, lbl_8042ED98, 16, i);
        if (s != 0 && s->isReady() && s->isActive()) {
            if (name == 0 || fn_80291188(name, *s->name) == 0) {
                count++;
            }
        }
        i++;
        if (i < 16) goto loop;
    }
    return count;
}

s8 fn_802501A4(const char* name) {
    SndMutex* m;
    s32 count;
    {
        SndLock l(lbl_8042E798);
        count = 0;
        s32 i = 0;
    loop:
        m = &lbl_8042E798;
        SndObj* s = slotGet(*m, lbl_8042EDD8, 16, i);
        if (s != 0 && s->isReady() && s->isActive()) {
            if (name == 0 || fn_80291188(name, *s->name) == 0) {
                count++;
            }
        }
        i++;
        if (i < 16) goto loop;
    }
    return count;
}

s8 fn_802502E0(const char* name) {
    SndMutex* m;
    s32 count;
    {
        SndLock l(lbl_8042E798);
        count = 0;
        s32 i = 0;
    loop:
        m = &lbl_8042E798;
        SndObj* s = slotGet(*m, lbl_8042EE18, 4, i);
        if (s != 0 && s->isReady() && s->isActive()) {
            if (name == 0 || fn_80291188(name, *s->name) == 0) {
                count++;
            }
        }
        i++;
        if (i < 4) goto loop;
    }
    return count;
}

int fn_8025041C(void) {
    SndMutex* m;
    SndMutex* m2;
    SndLock l(lbl_8042E798);
    s32 found = -1;
    for (s32 i = 0; i < 16; i++) {
        m = &lbl_8042E798;
        SndObj* s = slotGet(*m, lbl_8042ED98, 16, i);
        if (slotGet(*m, lbl_8042ED98, 16, i) == 0) {
            found = i;
            break;
        }
        if (s->isActive() == 0) {
            m2 = &lbl_8042E798;
            m2->lock();
            if ((s8)i >= 0 && (s8)i < 16) {
                lbl_8042ED98[(s8)i] = 0;
            }
            m2->unlock();
            if (s) {
                if (s) {
                    s->destroy(1);
                }
            }
            found = i;
            break;
        }
    }
    return found;
}

int fn_802505DC(void) {
    SndMutex* m;
    SndMutex* m2;
    SndLock l(lbl_8042E798);
    s32 found = -1;
    for (s32 i = 0; i < 16; i++) {
        m = &lbl_8042E798;
        SndObj* s = slotGet(*m, lbl_8042EDD8, 16, i);
        if (slotGet(*m, lbl_8042EDD8, 16, i) == 0) {
            found = i;
            break;
        }
        if (s->isActive() == 0) {
            m2 = &lbl_8042E798;
            m2->lock();
            if ((s8)i >= 0 && (s8)i < 16) {
                lbl_8042EDD8[(s8)i] = 0;
            }
            m2->unlock();
            if (s) {
                if (s) {
                    s->destroy(1);
                }
            }
            found = i;
            break;
        }
    }
    return found;
}

int fn_8025079C(void) {
    SndMutex* m;
    SndMutex* m2;
    SndLock l(lbl_8042E798);
    s32 found = -1;
    for (s32 i = 0; i < 4; i++) {
        m = &lbl_8042E798;
        SndObj* s = slotGet(*m, lbl_8042EE18, 4, i);
        if (slotGet(*m, lbl_8042EE18, 4, i) == 0) {
            found = i;
            break;
        }
        if (s->isActive() == 0) {
            m2 = &lbl_8042E798;
            m2->lock();
            if ((s8)i >= 0 && (s8)i < 4) {
                lbl_8042EE18[(s8)i] = 0;
            }
            m2->unlock();
            if (s) {
                if (s) {
                    s->destroy(1);
                }
            }
            found = i;
            break;
        }
    }
    return found;
}

void fn_80252418(const char* name, f32 ms) {
    s32 i;
    SndObj* s;
    SndMutex* m = &lbl_8042E798;
    SndMutex* m2;
    SndLock l(*m);
    i = fn_8024F7EC(name);
    if ((s8)i >= 0) {
        s = slotGetS(*m, lbl_8042ED88, 4, i);
        s->stop(ms);
        m2 = &lbl_8042E798;
        m2->lock();
        if ((s8)i >= 0 && (s8)i < 4) {
            lbl_8042ED88[(s8)i] = 0;
        }
        m2->unlock();
        if (s) {
            if (s) {
                s->destroy(1);
            }
        }
    }
}

void fn_80255060(const char* name, f32 ms) {
    s32 i;
    SndObj* s;
    SndMutex* m = &lbl_8042E798;
    SndMutex* m2;
    SndLock l(*m);
    i = fn_8024F92C(name);
    if ((s8)i >= 0) {
        s = slotGetS(*m, lbl_8042EDD8, 16, i);
        s->stop(ms);
        m2 = &lbl_8042E798;
        m2->lock();
        if ((s8)i >= 0 && (s8)i < 16) {
            lbl_8042EDD8[(s8)i] = 0;
        }
        m2->unlock();
        if (s) {
            if (s) {
                s->destroy(1);
            }
        }
    }
}

void fn_802568F0(const char* name, f32 ms) {
    s32 i;
    SndObj* s;
    SndMutex* m = &lbl_8042E798;
    SndMutex* m2;
    SndLock l(*m);
    i = fn_8024FA6C(name);
    if ((s8)i >= 0) {
        s = slotGetS(*m, lbl_8042EE18, 4, i);
        s->stop(ms);
        m2 = &lbl_8042E798;
        m2->lock();
        if ((s8)i >= 0 && (s8)i < 4) {
            lbl_8042EE18[(s8)i] = 0;
        }
        m2->unlock();
        if (s) {
            if (s) {
                s->destroy(1);
            }
        }
    }
}

void fn_802525A0(s32 i, f32 ms) {
    SndObj* s;
    SndMutex* m = &lbl_8042E798;
    SndMutex* m2;
    SndLock l(*m);
    s = slotGetS(*m, lbl_8042ED88, 4, i);
    if (s != 0 && s->isActive()) {
        s->stop(ms);
        m2 = &lbl_8042E798;
        m2->lock();
        if ((s8)i >= 0 && (s8)i < 4) {
            lbl_8042ED88[(s8)i] = 0;
        }
        m2->unlock();
        if (s) {
            if (s) {
                s->destroy(1);
            }
        }
    }
}

void fn_80252738(s32 i, f32 ms) {
    SndObj* s;
    SndMutex* m = &lbl_8042E798;
    SndLock l(*m);
    s = slotGetS(*m, lbl_8042ED88, 4, i);
    if (s != 0 && s->isActive()) {
        s->setA(ms);
    }
}

void fn_80252850(s32 i, f32 ms) {
    SndObj* s;
    SndMutex* m = &lbl_8042E798;
    SndLock l(*m);
    s = slotGetS(*m, lbl_8042ED88, 4, i);
    if (s != 0 && s->isActive() && s->canSetB()) {
        s->setB(ms);
    }
}

void fn_80252984(f32 ms) {
    SndMutex* m;
    SndLock l(lbl_8042E798);
    s32 i = 0;
loop:
    m = &lbl_8042E798;
    SndObj* s = slotGet(*m, lbl_8042ED88, 4, i);
    if (s != 0 && s->isActive()) {
        s->stop(ms);
        m->lock();
        if ((s8)i >= 0 && (s8)i < 4) {
            lbl_8042ED88[i] = 0;
        }
        m->unlock();
        if (s) {
            if (s) {
                s->destroy(1);
            }
        }
    }
    i++;
    if (i < 4) goto loop;
}

void fn_802551E8(f32 ms) {
    SndMutex* m;
    SndLock l(lbl_8042E798);
    s32 i = 0;
loop:
    m = &lbl_8042E798;
    SndObj* s = slotGet(*m, lbl_8042EDD8, 16, i);
    if (s != 0 && s->isActive()) {
        s->stop(ms);
        m->lock();
        if ((s8)i >= 0 && (s8)i < 16) {
            lbl_8042EDD8[i] = 0;
        }
        m->unlock();
        if (s) {
            if (s) {
                s->destroy(1);
            }
        }
    }
    i++;
    if (i < 16) goto loop;
}

void fn_80256A78(f32 ms) {
    SndMutex* m;
    SndLock l(lbl_8042E798);
    s32 i = 0;
loop:
    m = &lbl_8042E798;
    SndObj* s = slotGet(*m, lbl_8042EE18, 4, i);
    if (s != 0 && s->isActive()) {
        s->stop(ms);
        m->lock();
        if ((s8)i >= 0 && (s8)i < 4) {
            lbl_8042EE18[i] = 0;
        }
        m->unlock();
        if (s) {
            if (s) {
                s->destroy(1);
            }
        }
    }
    i++;
    if (i < 4) goto loop;
}

int fn_80251838(s32, void*, f32);
int fn_80252C38(void*, f32);
int fn_80253848(void*, void*, f32);
int fn_802549C4(void*, void*, f32);

int fn_802522E0(s32 i, void* b, f32 vol, f32 ms) {
    SndObj* s;
    SndMutex* m = &lbl_8042E798;
    SndLock l(*m);
    i = fn_80251838((s8)i, b, ms);
    if ((s8)i >= 0) {
        s = slotGetS(*m, lbl_8042ED88, 4, i);
        s->fadeTo(vol, 0.0f);
    }
    return i;
}

int fn_80253718(void* a, f32 vol, f32 ms) {
    SndObj* s;
    SndMutex* m = &lbl_8042E798;
    SndLock l(*m);
    s32 i = fn_80252C38(a, ms);
    if ((s8)i >= 0) {
        s = slotGetS(*m, lbl_8042ED98, 16, i);
        s->fadeTo(vol, 0.0f);
    }
    return i;
}

int fn_80253DAC(void* a, void* b, f32 vol, f32 ms) {
    SndObj* s;
    SndMutex* m = &lbl_8042E798;
    SndLock l(*m);
    s32 i = fn_80253848(a, b, ms);
    if ((s8)i >= 0) {
        s = slotGetS(*m, lbl_8042ED98, 16, i);
        s->fadeTo(vol, 0.0f);
    }
    return i;
}

int fn_80254F28(void* a, void* b, f32 vol, f32 ms) {
    SndObj* s;
    SndMutex* m = &lbl_8042E798;
    SndLock l(*m);
    s32 i = fn_802549C4(a, b, ms);
    if ((s8)i >= 0) {
        s = slotGetS(*m, lbl_8042EDD8, 16, i);
        s->fadeTo(vol, 0.0f);
    }
    return i;
}

}
