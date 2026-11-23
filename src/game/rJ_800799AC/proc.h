#ifndef RJ_800799AC_PROC_H
#define RJ_800799AC_PROC_H

#include "game/rJ_800799AC/types.h"

/* Process object. Closely follows the "6C proc" system of the GBA Fire Emblem
 * games: a script of commands drives a tree of objects. */
struct Proc;
typedef void (*ProcFunc)(Proc*);

enum ProcFlags {
    PROC_FREED = 1,    /* back in the free stack */
    PROC_ENDED = 2,    /* being destroyed */
    PROC_BLOCKING = 4, /* parent's lockCnt counts this one */
    PROC_SYNC = 8,
    PROC_INIT = 0x10,  /* set during creation */
    PROC_KILLABLE = 0x20 /* may be killed when the pool is exhausted */
};

struct Proc {
    u32* script;   /* 0x00 start of script, NULL when dead */
    u32* cur;      /* 0x04 next command */
    ProcFunc onEnd;  /* 0x08 */
    ProcFunc onIdle; /* 0x0C runs every frame after the script */
    ProcFunc loop;   /* 0x10 current repeat function */
    const char* name; /* 0x14 */
    Proc* parent;  /* 0x18 tree slot (< 11) or parent proc */
    Proc* child;   /* 0x1C most recently added child */
    Proc* next;    /* 0x20 */
    Proc* prev;    /* 0x24 */
    s16 sleep;     /* 0x28 */
    u8 mark;       /* 0x2A */
    u8 layer;      /* 0x2B */
    u8 flags;      /* 0x2C */
    u8 lockCnt;    /* 0x2D */
    u8 pause;      /* 0x2E */
    u8 pad2F[0xB0 - 0x2F];
};

/* Lock with virtual lock/unlock at vtable +8 and +0x10. */
class ProcLock {
public:
    virtual void lock();
    virtual void v0C();
    virtual void unlock();
};

extern "C" {
int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);
}

#endif
