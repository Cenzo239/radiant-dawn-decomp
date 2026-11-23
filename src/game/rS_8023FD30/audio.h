#ifndef RS_8023FD30_AUDIO_H
#define RS_8023FD30_AUDIO_H
#include "game/rS_8023FD30/types.h"

/* Mutex-like object with virtual lock/unlock; the first member of the sound manager. */
class SndMutex {
public:
    virtual void lock();   /* +0x08 */
    virtual void v0C();
    virtual void unlock(); /* +0x10 */
    u8 pad[0x1FF0];
};

extern "C" {
extern char lbl_80391888[];
extern SndMutex lbl_8042E798;
extern u8 lbl_8042F1B0[];
}

/* Scoped lock on the stack. The vtable is stored by hand so the checker can verify it. */
struct SndLock {
    void* vt;
    SndMutex* m;
    SndLock(SndMutex& x) {
        vt = lbl_80391888;
        m = &x;
        x.lock();
    }
    ~SndLock() {
        vt = lbl_80391888;
        m->unlock();
    }
};

#endif
