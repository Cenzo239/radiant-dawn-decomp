#include "game/rS_8023FD30/types.h"
/* The sound thread's main loop: takes a command from the queue and runs it. */
class CmdLock {
public:
    virtual void lock();
    virtual void v0C();
    virtual void unlock();
};
struct SndCmd { u8 type; s8 busy; s8 cancel; u8 pad03; s32 result; u32 id; u32 arg; };
struct Ldr { u8 p[4]; u8 mtx[0x18]; u8 list[0x4]; };
struct Mgr {
    u8 p[0x28];
    Ldr ldr;
    u8 p2[0x294 - 0x28 - sizeof(Ldr)];
    u8 eff[0x1D30 - 0x294];
    u8 q[0x80];
    CmdLock lock;
};
extern "C" {
extern u8 lbl_8042E798[];
void fn_8031D34C(void*, void*, int);
void fn_8031DD44(void*);
void fn_8031DE20(void*);
int fn_802A5ED8(void*);
int fn_802FAA84(void);
void fn_802B1810(void*, s32);
int fn_802B107C(void*, u32, void*, u32);
void fn_802B17BC(void*);
}
static inline int alloc2(Ldr* l) {
    int r;
    void* k = l->mtx;
    fn_8031DD44(k);
    r = fn_802A5ED8(l->list);
    fn_8031DE20(k);
    return r;
}
static inline void lockIt(CmdLock* k) { k->lock(); }
static inline void unlockIt(CmdLock* k) { k->unlock(); }
static inline int alloc(Ldr* l) {
    void* k = l->mtx;
    int r;
    fn_8031DD44(k);
    r = fn_802A5ED8(l->list);
    fn_8031DE20(k);
    return r;
}
#define LOAD_LOOP \
    c->result = alloc(l); \
    while (fn_802B107C(m->eff, c->id, &m->ldr, c->arg) == 0) { \
        if (fn_802FAA84() != -1) { \
            fn_802B1810(&m->ldr, c->result); \
        } else { \
            fail = 1; \
            break; \
        } \
    } \
    fn_802B17BC(&m->ldr);
#pragma use_lmw_stmw on
extern "C" void fn_8024CCF8(void) {
    /*P*/
    int one;
    Mgr* m;
    CmdLock* lk;
    Ldr* l;
    int fail;
    int zero;
    SndCmd* c;
/*E*/
    m = (Mgr*)lbl_8042E798;
    one = 1;
    zero = 0;
    l = &m->ldr;
    lk = &m->lock;
    while (1) {
        SndCmd* msg;
        fn_8031D34C(m->q, &msg, 1);
        {
            CmdLock* k = (CmdLock*)((u8*)m + 0x1DB0);
            k->lock();
            c = msg;
            c->cancel = one;
            ((CmdLock*)((u8*)m + 0x1DB0))->unlock();
        }
        fail = 0;
        switch ((s8)c->type) {
        case 2:
            LOAD_LOOP
            break;
        case 3:
            c->result = alloc(l);
            fn_802B17BC(l);
            break;
        case 4:
            fn_802B1810(&m->ldr, c->result);
            break;
        case 5:
            fn_802B1810(&m->ldr, c->result);
            LOAD_LOOP
            break;
        case 6:
            fn_802B1810(&m->ldr, c->result);
            c->result = alloc2(l);
            fn_802B17BC(l);
            break;
        }
        lk->lock();
        if (c->cancel != 0 && fail == 0) {
            c->cancel = zero;
            c->busy = one;
        }
        lk->unlock();
    }
}
