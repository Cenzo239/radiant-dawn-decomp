#include "game/rS_8023FD30/audio.h"
/* Sound thread main loop, and setting one value on every player of pool A. */
class SndObj {
public:
    virtual void destroy(int);
    virtual void v0C();
    virtual int isActive();
    virtual void v14();
    virtual int isReady();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void setA(s32);
};
extern "C" {
extern SndObj* lbl_8042ED88[];
void fn_80252B04(f32 v) {
    /*P*/
    SndObj* s;
    SndObj** q;
    SndMutex* m;
    s32 i;
/*E*/
    SndLock l(lbl_8042E798);
    q = lbl_8042ED88;
    i = 0;
loop:
    m = &lbl_8042E798;
    {
        m->lock();
        s = 0;
        if ((s8)i >= 0 && (s8)i < 4) s = *q;
        m->unlock();
        if (s != 0 && s->isActive()) {
            s->setA((s32)v);
        }
        i++;
        q++;
    if (i < 4) goto loop;
    }
}
}
