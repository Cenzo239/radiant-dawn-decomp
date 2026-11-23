/* Process system: queries, the per-frame runner and the script interpreter.
 * Functions that inline Proc_End are in fn_80081A90.cpp. */
#include "game/rJ_800799AC/proc.h"

extern "C" {

extern u8 lbl_803E4E88[0x20];
extern Proc* lbl_803E4E60[10];
extern Proc* lbl_803E4A58[];
extern Proc** lbl_804CB5C8;
extern Proc lbl_803D9A58[0x100];
extern void* lbl_803E4EA8[8];
extern const f32 lbl_804CD140;
extern const f64 lbl_804CD148;
void fn_80085F0C(Proc* p);
Proc* fn_80081050(void* script, Proc* parent);

/* Proc_SetBlocking */
void fn_80083174(Proc* p) {
    Proc* parent = p->parent;
    if (parent == 0) {
        return;
    }
    p->flags |= PROC_BLOCKING;
    parent->lockCnt++;
}

/* Proc_ClearBlocking */
void fn_8008319C(Proc* p) {
    if (!(p->flags & PROC_BLOCKING)) {
        return;
    }
    p->flags &= ~PROC_BLOCKING;
    p->parent->lockCnt--;
}

/* Proc_CountFree */
int fn_800839DC(void) {
    int n;
    ((ProcLock*)lbl_803E4E88)->lock();
    n = lbl_804CB5C8 - lbl_803E4A58;
    ((ProcLock*)lbl_803E4E88)->unlock();
    return n;
}

/* Proc_RunTree */
void fn_80083A48(Proc* p) {
    if (p->prev != 0) {
        fn_80083A48(p->prev);
    }
    if (p->script == 0) {
        return;
    }
    if (p->pause != 0) {
        return;
    }
    if (p->lockCnt == 0 && (!(p->flags & PROC_SYNC) || p->parent->lockCnt == 0)) {
        for (;;) {
            if (p->loop == 0) {
                fn_80085F0C(p);
            }
            if (p->loop != 0) {
                if (p->sleep >= 0) {
                    if (--p->sleep < 0) {
                        p->loop = 0;
                        continue;
                    }
                }
                p->loop(p);
            }
            break;
        }
        if (p->flags & PROC_ENDED) {
            return;
        }
    }
    if (p->onIdle != 0) {
        p->onIdle(p);
    }
    if (p->child != 0) {
        fn_80083A48(p->child);
    }
}

/* Proc_RunRoot */
void fn_80083B58(int tree) {
    if (lbl_803E4E60[tree] != 0) {
        fn_80083A48(lbl_803E4E60[tree]);
    }
}

/* Proc_Break: leave the current repeat function */
void fn_80083B78(Proc* p) {
    p->loop = 0;
}

/* Proc_Find */
Proc* fn_80083B84(void* script) {
    Proc* result = 0;
    ProcLock* lock = (ProcLock*)lbl_803E4E88;
    Proc* p;
    int i;
    lock->lock();
    p = lbl_803D9A58;
    for (i = 0; i < 0x100; i++, p++) {
        if (p->script == script) {
            result = p;
            break;
        }
    }
    lock->unlock();
    return result;
}

/* Proc_Count */
int fn_80083CB4(void* script) {
    int n = 0;
    ProcLock* lock = (ProcLock*)lbl_803E4E88;
    Proc* p;
    int i;
    lock->lock();
    p = lbl_803D9A58;
    for (i = 0; i < 0x100; i++, p++) {
        if (p->script == script) {
            n++;
        }
    }
    lock->unlock();
    return n;
}

/* Proc_Goto: jump to label */
void fn_80083DC4(Proc* p, int label) {
    u32 w;
    u32* c = p->script;
    while ((w = *c) != 0) {
        if ((w & 0xFFF) == 1 && (s16)(w >> 16) == label) {
            p->cur = c;
            p->loop = 0;
            return;
        }
        c = (u32*)((u8*)c + ((w >> 10) & 0x3C));
    }
}

void fn_80083E10(Proc* p, ProcFunc f) {
    p->onEnd = f;
}

void fn_80083E18(Proc* p, ProcFunc f) {
    p->onIdle = f;
}

/* Proc_ForEach */
void fn_80083E20(ProcFunc f) {
    Proc* p = lbl_803D9A58;
    int i = 0;
    do {
        if (p->script != 0) {
            f(p);
        }
        i++;
        p++;
    } while (i < 0x100);
}

/* Proc_ForEachOfClass */
void fn_80083E90(void* script, ProcFunc f) {
    Proc* p = lbl_803D9A58;
    int i = 0;
    do {
        if (p->script == script) {
            f(p);
        }
        i++;
        p++;
    } while (i < 0x100);
}

/* Proc_BreakAllOfClass */
void fn_80084E64(void* script) {
    Proc* p = lbl_803D9A58;
    int i;
    for (i = 0; i < 0x100; i++, p++) {
        if (p->script == script) {
            p->loop = 0;
        }
    }
}


static inline int nameCmp(const char* s1, const char* s2) {
    while (*s1 | *s2) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return 0;
}

/* Proc_FindByName */
Proc* fn_80085708(const char* name) {
    Proc* p = lbl_803D9A58;
    int i;
    for (i = 0; i < 0x100; i++, p++) {
        if (p->script != 0 && nameCmp(p->name, name) == 0) {
            return p;
        }
    }
    return 0;
}

Proc* fn_800857F8(Proc* p, Proc* parent) {
    if (p->parent == parent) {
        return p;
    }
    return 0;
}

}
