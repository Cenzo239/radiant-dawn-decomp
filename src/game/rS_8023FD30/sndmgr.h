#ifndef RS_8023FD30_SNDMGR_H
#define RS_8023FD30_SNDMGR_H
#include "game/rS_8023FD30/types.h"

/* The sound manager's state, written as the file statics the original seems to have used.
   CodeWarrior pools statics of one file behind a shared base register, which is what the
   `addi rN, rBase, 0x0` in the original comes from. sMutex is at lbl_8042E798. */
/* The two locks: classes with virtual functions (vtable pointer at +0, OSMutex at +4). The
   original constructs them in the unit's __sinit (fn_8025EBF0, hand-written). So that the block
   needs no compiler-made constructor, the storage is a POD (SndLockRaw) and sMutex/sCmdMutex
   name it through the class type, which keeps the virtual calls as the original makes them. */
struct SndLockRaw {
    void* vt;
    u8 mutex[0x18];        /* OSMutex */
};

class SndLockable {
public:
    virtual void lock();   /* +0x08 */
    virtual void v0C();
    virtual void unlock(); /* +0x10 */
    u8 mutex[0x18];
};

class SndPlayer {
public:
    virtual void destroy(int); /* +0x08 */
    virtual void v0C();
    virtual int isActive();    /* +0x10 */
    virtual void v14();
    virtual int isReady();     /* +0x18 */
    virtual void v1C();
    virtual void v20();
    virtual void stop(s32);    /* +0x24 */
    virtual void setA(s32);    /* +0x28 */
    virtual void setB(s32);    /* +0x2C */
    virtual void v30();
    virtual int canSetB();     /* +0x34 */
    u8 pad04[8];
    const char** name;         /* +0x0C */
};

struct SndFader {
    s32 t;
    s32 frames;
    f32 cur;
    f32 from;
    f32 to;
};

/* A queued command for the sound thread. */
struct SndCmd {
    u8 type;
    s8 busy;
    s8 cancel;
    u8 pad03;
    s32 result;
    u32 id;
    u32 arg;
};

class SndCmdLock {
public:
    virtual void lock();
    virtual void v0C();
    virtual void unlock();
    u8 mutex[0x18];
};

/* The block at lbl_8042E798 ("...bss.0" of every file including this header), in the
   original's order. The sChain... arrays are the compiler's destructor-chain records that
   fn_8025EBF0 (__sinit) registers; the byte arrays stand for library objects whose classes are
   not declared here. */
static SndLockRaw sMutexRaw;        /* +0x000 lbl_8042E798 */
static u32 sChain01C[3];            /* +0x01C */
static u8 sHeap[0x54 - 0x28];       /* +0x028 */
static u32 sChain054[3];            /* +0x054 */
static u8 sMember60[0x88 - 0x60];   /* +0x060 passed to fn_802AB9E4 */
static u32 sChain088[4];            /* +0x088 */
static u8 sPad098[0xF0 - 0x98];     /* +0x098 */
static u32 sChain0F0[3];            /* +0x0F0 */
static u8 sGroups[0x288 - 0xFC];    /* +0x0FC lbl_8042E894; size not 8-divisible or it aligns to 8 */
static u32 sChain288[3];            /* +0x288 */
static u8 sEffect[0x380 - 0x294];   /* +0x294 effect object (fields at +0x8, +0xC, +0xE0..) */
static u32 sChain380[3];            /* +0x380 */
static u8 sEffA[0x518 - 0x38C];     /* +0x38C */
static u32 sChain518[3];            /* +0x518 */
static u8 sEffB[0x5F0 - 0x524];     /* +0x524 */
static SndPlayer* sPoolA[4];        /* +0x5F0 lbl_8042ED88 */
static SndPlayer* sPoolB[16];       /* +0x600 lbl_8042ED98 */
static SndPlayer* sPoolC[16];       /* +0x640 lbl_8042EDD8 */
static SndPlayer* sPoolD[4];        /* +0x680 lbl_8042EE18 */
static SndFader sFaderDefault;      /* +0x690 */
static SndFader sFader6A4;          /* +0x6A4 */
static SndFader sFader6B8;          /* +0x6B8 */
static SndFader sFader6CC;          /* +0x6CC */
static SndFader sFader6E0;          /* +0x6E0 */
static SndFader sFader6F4;          /* +0x6F4 */
static SndFader sFader708;          /* +0x708 */
static SndFader sFader71C;          /* +0x71C */
static SndFader sFader730;          /* +0x730 */
static SndFader sFader744;          /* +0x744 */
static SndFader sChanA[8];          /* +0x758 lbl_8042EEF0 */
static SndFader sChanB[8];          /* +0x7F8 lbl_8042EF90 */
static SndFader sChanC[8];          /* +0x898 lbl_8042F030 */
static SndFader sChanD[8];          /* +0x938 lbl_8042F0D0 */
static SndFader sFader9D8;          /* +0x9D8 */
static SndFader sFader9EC;          /* +0x9EC */
static SndFader sFaderA00;          /* +0xA00 */
static u8 sPadA14[0x1D30 - 0xA14];  /* +0xA14 thread and its stack */
static u8 sCmdQueue[0x1DB0 - 0x1D30]; /* +0x1D30 OSMessageQueue and its buffer */
static SndLockRaw sCmdMutexRaw;     /* +0x1DB0 lbl_80430548 */
static u32 sPad1DCC;                /* +0x1DCC */
static SndCmd sCmds[24];            /* +0x1DD0 lbl_80430568 */
static u8 sPad1F50[0x1000];
#define sMutex (*(SndLockable*)&sMutexRaw)
#define sCmdMutex (*(SndCmdLock*)&sCmdMutexRaw)

extern "C" {
extern char lbl_80391888[];
}

struct SndCmdGuard {
    void* vt;
    SndCmdLock* m;
    SndCmdGuard(SndCmdLock& x) {
        vt = lbl_80391888;
        m = &x;
        x.lock();
    }
    ~SndCmdGuard() {
        vt = lbl_80391888;
        m->unlock();
    }
};

struct SndGuard {
    void* vt;
    SndLockable* m;
    SndGuard(SndLockable& x) {
        vt = lbl_80391888;
        m = &x;
        x.lock();
    }
    ~SndGuard() {
        vt = lbl_80391888;
        m->unlock();
    }
};

#endif
