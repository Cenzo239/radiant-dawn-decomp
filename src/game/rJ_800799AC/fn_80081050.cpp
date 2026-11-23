#include "game/rJ_800799AC/proc.h"

extern "C" {

extern u8 lbl_803E4E88[0x20];
extern Proc* lbl_803E4E60[10];
extern Proc** lbl_804CB5C8;
extern const char lbl_803625A8[];
extern u8 lbl_80380F90[0x20];

extern Proc lbl_803D9A58[0x100];
extern Proc* lbl_803E4A58[0x101];
extern void* lbl_803E4EA8[8];
extern u8 lbl_80380FB0[];
Proc* fn_800831C4(void);
void fn_80085F0C(Proc* p);

/* Proc_InitSystem. The object at lbl_803E4EA8 holds the eight command table
 * pointers; its first word starts as the base table lbl_80380FB0. */
void fn_80080F18(void) {
    Proc* p = lbl_803D9A58;
    Proc** s = lbl_803E4A58;
    int i;
    for (i = 0; i < 0x100; i++, p++, s++) {
        p->script = 0;
        p->cur = 0;
        p->onEnd = 0;
        p->onIdle = 0;
        p->loop = 0;
        p->name = 0;
        p->parent = 0;
        p->child = 0;
        p->next = 0;
        p->prev = 0;
        p->sleep = -1;
        p->mark = 0xFF;
        p->layer = 0;
        p->flags = 3;
        p->lockCnt = 0;
        p->pause = 0;
        *s = p;
    }
    lbl_803E4A58[0x100] = 0;
    lbl_804CB5C8 = lbl_803E4A58;
    lbl_803E4EA8[0] = 0;
    lbl_803E4EA8[1] = 0;
    lbl_803E4EA8[2] = 0;
    lbl_803E4EA8[3] = 0;
    lbl_803E4EA8[4] = 0;
    lbl_803E4EA8[5] = 0;
    lbl_803E4EA8[6] = 0;
    lbl_803E4EA8[7] = 0;
    lbl_803E4EA8[0] = lbl_80380FB0;
    for (i = 0; i < 10; i++) {
        lbl_803E4E60[i] = 0;
    }
}

/* Proc_Create */
Proc* fn_80081050(void* script, Proc* parent) {
    ProcLock* lock;
    Proc* p = fn_800831C4();
    p->script = (u32*)script;
    p->cur = (u32*)script;
    p->onEnd = 0;
    p->onIdle = 0;
    p->loop = 0;
    p->name = lbl_803625A8;
    p->parent = 0;
    p->child = 0;
    p->next = 0;
    p->prev = 0;
    p->sleep = -1;
    p->mark = 0xFF;
    p->flags = 0x10;
    p->lockCnt = 0;
    p->pause = 0;
    if ((u32)parent < 10) {
        lock = (ProcLock*)lbl_803E4E88;
        p->layer = 0;
        lock->lock();
        if (lbl_803E4E60[(u32)parent] != 0) {
            lbl_803E4E60[(u32)parent]->next = p;
            p->prev = lbl_803E4E60[(u32)parent];
        }
        p->parent = parent;
        lbl_803E4E60[(u32)parent] = p;
        lock->unlock();
    } else {
        p->layer = parent->layer;
        if (parent->child != 0) {
            parent->child->next = p;
            p->prev = parent->child;
        }
        parent->child = p;
        p->parent = parent;
    }
    fn_80085F0C(p);
    p->flags &= ~0x10;
    return p;
}

/* Proc_CreateBlocking */
Proc* fn_80081194(void* script, Proc* parent) {
    Proc* p = fn_80081050(script, parent);
    if (p->script == 0) {
        return 0;
    }
    p->flags |= PROC_BLOCKING;
    p->parent->lockCnt++;
    return p;
}

Proc* fn_800811E4(void* script, Proc* parent) {
    if (parent == 0) {
        parent = (Proc*)3;
    }
    if ((int)parent < 0) {
        return fn_80081194(script, parent);
    }
    return fn_80081050(script, parent);
}

void fn_80081250(Proc* p) {
    *(int*)((u8*)p + 0x60) = 0;
}

void fn_8008125C(Proc* p) {
    int n = *(int*)((u8*)p + 0x60) + 1;
    *(int*)((u8*)p + 0x60) = n;
    if (n >= *(int*)((u8*)p + 0x64)) {
        p->loop = 0;
    }
}

void fn_80081280(int v, Proc* parent) {
    if (parent == 0) {
        parent = (Proc*)3;
    }
    Proc* p;
    if ((int)parent < 0) {
        p = fn_80081194(lbl_80380F90, parent);
    } else {
        p = fn_80081050(lbl_80380F90, parent);
    }
    *(int*)((u8*)p + 0x64) = v;
}

/* The three teardown walkers below recurse over prev and child. The compiler
 * auto-inlined each into itself to a fixed depth. */
#pragma push
#pragma inline_depth(3)
/* Proc_MarkEnded */
void fn_8008130C(Proc* p) {
    if (p->prev != 0) {
        fn_8008130C(p->prev);
    }
    if (p->child != 0) {
        fn_8008130C(p->child);
    }
    p->flags |= PROC_ENDED;
}
#pragma pop

#pragma use_lmw_stmw on
#pragma push
#pragma inline_depth(2)
/* Proc_Free */
void fn_800815A8(Proc* p) {
    int lvl = OSDisableInterrupts();
    if (p->prev != 0) {
        fn_800815A8(p->prev);
    }
    if (p->child != 0) {
        fn_800815A8(p->child);
    }
    if (!(p->flags & PROC_FREED)) {
        p->flags |= PROC_FREED;
        ((ProcLock*)lbl_803E4E88)->lock();
        *--lbl_804CB5C8 = p;
        ((ProcLock*)lbl_803E4E88)->unlock();
        OSRestoreInterrupts(lvl);
    }
}
#pragma pop
#pragma use_lmw_stmw off

#pragma push
#pragma inline_depth(1)
/* Proc_RunEndCallbacks */
void fn_80081948(Proc* p) {
    if (p->prev != 0) {
        fn_80081948(p->prev);
    }
    if (p->child != 0) {
        fn_80081948(p->child);
    }
    if (p->onEnd != 0) {
        p->onEnd(p);
    }
    p->script = 0;
    p->loop = 0;
    if (p->flags & PROC_BLOCKING) {
        p->parent->lockCnt--;
    }
}
#pragma pop

}
