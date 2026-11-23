/* Process system: tree walks and the script interpreter. */
#include "game/rJ_800799AC/proc.h"

extern "C" {

extern u8 lbl_803E4E88[0x20];
extern Proc lbl_803D9A58[0x100];
extern void** lbl_803E4EA8[8];
Proc* fn_800857F8(Proc* p, Proc* parent);
Proc* fn_80081050(void* script, Proc* parent);

#pragma use_lmw_stmw on
/* Proc_FindChildOfClass */
Proc* fn_8008580C(void* script, Proc* parent) {
    int i;
    Proc* p;
    ProcLock* lock = (ProcLock*)lbl_803E4E88;
    Proc* result = 0;
    lock->lock();
    p = lbl_803D9A58;
    for (i = 0; i < 0x100; i++, p++) {
        if (p->script == script && (result = fn_800857F8(p, parent)) != 0) {
            break;
        }
    }
    lock->unlock();
    return result;
}

#pragma push
#pragma inline_depth(3)
/* Proc_WalkSiblings */
void fn_800858B0(Proc* p, ProcFunc f) {
    if (p->prev != 0) {
        fn_800858B0(p->prev, f);
    }
    f(p);
    if (p->child != 0) {
        fn_800858B0(p->child, f);
    }
}
#pragma pop
#pragma use_lmw_stmw off

/* Proc_GetIndex */
u8 fn_80085ECC(Proc* p) {
    return p - lbl_803D9A58;
}

Proc* fn_80085EF8(int i) {
    return &lbl_803D9A58[i];
}

/* RunProcessScript */
void fn_80085F0C(Proc* p) {
    typedef int (*Cmd)(Proc*);
    void*** t;
    if (p->script == 0) {
        return;
    }
    if (p->lockCnt != 0) {
        return;
    }
    if (p->pause != 0) {
        return;
    }
    if (p->loop != 0) {
        return;
    }
    t = lbl_803E4EA8;
    do {
        u32 w = *p->cur;
        if (((Cmd)t[(w >> 8) & 7][w & 0xFF])(p) == 0) {
            return;
        }
    } while (p->script != 0 && p->lockCnt == 0 && p->pause == 0);
}

/* Script commands. Every command returns nonzero to keep interpreting. */
int fn_80086764(Proc* p) {
    p->mark = (u16)(*p->cur++ >> 16);
    return 1;
}

int fn_80086784(Proc* p) {
    p->layer = (u16)(*p->cur++ >> 16);
    return 1;
}

int fn_800867A4(Proc* p) {
    p->name = (const char*)p->cur[1];
    p->cur += 2;
    return 1;
}

int fn_800867C0(Proc* p) {
    p->onEnd = (ProcFunc)p->cur[1];
    p->cur += 2;
    return 1;
}

int fn_800867DC(Proc* p) {
    p->onIdle = (ProcFunc)p->cur[1];
    p->cur += 2;
    return 1;
}

int fn_800867F8(Proc* p) {
    p->flags |= PROC_SYNC;
    p->cur++;
    return 1;
}

int fn_80087858(Proc* p) {
    p->cur++;
    return 1;
}

void fn_8008786C(Proc* p) {
}

int fn_80087870(Proc* p) {
    int t = (s16)(*p->cur++ >> 16);
    if (t == 0) {
        return 0;
    }
    p->sleep = t;
    p->loop = fn_8008786C;
    return 0;
}

int fn_800878AC(Proc* p) {
    p->loop = fn_8008786C;
    p->cur++;
    return 0;
}


/* Goto: jumps to label, same search as fn_80083DC4 */
static inline void gotoLabel(Proc* p, int label) {
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

int fn_800878CC(Proc* p) {
    gotoLabel(p, (*p->cur >> 16) & 0xFF);
    return 1;
}

int fn_80087928(Proc* p) {
    int label = (*p->cur >> 16) & 0xFF;
    if (p->sleep >= 0) {
        if (--p->sleep == 0) {
            u32* c = p->script;
            u32 w;
            while ((w = *c) != 0) {
                if ((w & 0xFFF) == 1 && (s16)(w >> 16) == label) {
                    p->cur = c;
                    p->loop = 0;
                    goto end;
                }
                c = (u32*)((u8*)c + ((w >> 10) & 0x3C));
            }
        }
    }
end:
    return 1;
}

int fn_800879A0(Proc* p) {
    p->script = (u32*)p->cur[1];
    p->cur = p->script;
    p->loop = 0;
    return 1;
}

typedef int (*CmdFn)(Proc*);
typedef int (*CmdFn1)(Proc*, int);
typedef int (*CmdFn2)(Proc*, int, int);

int fn_800879C0(Proc* p) {
    CmdFn f = (CmdFn)p->cur[1];
    p->cur += 2;
    f(p);
    return 1;
}

int fn_800879F8(Proc* p) {
    if (((CmdFn)p->cur[1])(p) != 0) {
        gotoLabel(p, (*p->cur >> 16) & 0xFF);
    } else {
        p->cur += 2;
    }
    return 1;
}

int fn_80087AA0(Proc* p) {
    if (((CmdFn)p->cur[1])(p) == 0) {
        gotoLabel(p, (*p->cur >> 16) & 0xFF);
    } else {
        p->cur += 2;
    }
    return 1;
}

int fn_80087B48(Proc* p) {
    CmdFn f = (CmdFn)p->cur[1];
    p->cur += 2;
    return f(p);
}

int fn_80087B60(Proc* p) {
    CmdFn f = (CmdFn)p->cur[1];
    p->cur += 2;
    return f(p) == 0;
}

int fn_80087B9C(Proc* p) {
    if (((CmdFn)p->cur[1])(p) != 0) {
        return 0;
    }
    p->cur += 2;
    return 1;
}

int fn_80087BF4(Proc* p) {
    if (((CmdFn)p->cur[1])(p) == 0) {
        return 0;
    }
    p->cur += 2;
    return 1;
}

int fn_80087C4C(Proc* p) {
    u32* c = p->cur;
    int a = (s16)(c[0] >> 16);
    CmdFn1 f = (CmdFn1)c[1];
    p->cur += 2;
    return f(p, a);
}

int fn_80087C70(Proc* p) {
    u32 v = p->cur[2];
    p->cur += 3;
    return ((CmdFn2)v)(p, (s16)v, (s16)(v >> 16));
}

int fn_80087C94(Proc* p) {
    u32* c = p->cur;
    int a = c[2];
    CmdFn1 f = (CmdFn1)c[1];
    p->cur += 3;
    return f(p, a);
}

int fn_80087CB0(Proc* p) {
    u32* c = p->cur;
    int b = (s16)(c[0] >> 16);
    int a = c[2];
    CmdFn2 f = (CmdFn2)c[1];
    p->cur += 3;
    return f(p, a, b);
}

int fn_80087CD8(Proc* p) {
    p->loop = (ProcFunc)p->cur[1];
    p->cur += 2;
    return 0;
}

int fn_80087CF4(Proc* p) {
    p->sleep = (u16)(*p->cur++ >> 16);
    return 1;
}

int fn_80087D14(Proc* p) {
    fn_80081050((void*)p->cur[1], p);
    p->cur += 2;
    return 1;
}

int fn_80087D5C(Proc* p) {
    Proc* q = fn_80081050((void*)p->cur[1], p);
    if (q->script != 0) {
        q->flags |= PROC_BLOCKING;
        q->parent->lockCnt++;
    }
    p->cur += 2;
    return 0;
}

int fn_80087DCC(Proc* p) {
    fn_80081050((void*)p->cur[1], (Proc*)(s16)(*p->cur >> 16));
    p->cur += 2;
    return 1;
}

static inline Proc* findClass(void* script) {
    Proc* result = 0;
    ProcLock* lock = (ProcLock*)lbl_803E4E88;
    Proc* q;
    int i;
    lock->lock();
    q = lbl_803D9A58;
    for (i = 0; i < 0x100; i++, q++) {
        if (q->script == script) {
            result = q;
            break;
        }
    }
    lock->unlock();
    return result;
}

/* Wait while any instance exists */
int fn_80087E1C(Proc* p) {
    if (findClass((void*)p->cur[1]) != 0) {
        return 0;
    }
    p->cur += 2;
    return 1;
}

int fn_80088738(Proc* p) {
    void* script = (void*)p->cur[1];
    int i;
    Proc* q = lbl_803D9A58;
    for (i = 0; i < 0x100; i++, q++) {
        if (q->script == script) {
            q->loop = 0;
        }
    }
    p->cur += 2;
    return 1;
}

int fn_800887F8(Proc* p) {
    return 0;
}

int fn_80088800(Proc* p) {
    if (p->flags & PROC_BLOCKING) {
        p->flags &= ~PROC_BLOCKING;
        p->parent->lockCnt--;
    }
    p->cur++;
    return 1;
}

static inline Proc* findName(const char* name) {
    Proc* q = lbl_803D9A58;
    int i;
    for (i = 0; i < 0x100; i++, q++) {
        if (q->script != 0) {
            const char* s1 = q->name;
            const char* s2 = name;
            int r;
            while (*s1 | *s2) {
                if (*s1 != *s2) {
                    r = *s1 - *s2;
                    goto done;
                }
                s1++;
                s2++;
            }
            r = 0;
        done:
            if (r == 0) {
                return q;
            }
        }
    }
    return 0;
}

int fn_80088838(Proc* p) {
    if (findName((const char*)p->cur[1]) != 0) {
        return 0;
    }
    p->cur += 2;
    return 1;
}

int fn_800891E4(Proc* p) {
    Proc* q = findName((const char*)p->cur[1]);
    if (q != 0) {
        q->loop = 0;
    }
    p->cur += 2;
    return 1;
}

int fn_800892F4(Proc* p) {
    p->flags |= PROC_KILLABLE;
    p->cur++;
    return 1;
}

int fn_80089314(Proc* p) {
    int t = (s16)(*p->cur++ >> 16);
    if (t == 0) {
        return 0;
    }
    p->sleep = t / (1000.0f / 60.0f);
    p->loop = fn_8008786C;
    return 0;
}

void fn_80089388(int i, void** table) {
    lbl_803E4EA8[i] = table;
}

void fn_8008939C(Proc* p) {
    p->lockCnt++;
}

void fn_800893AC(Proc* p) {
    p->lockCnt--;
}

u8 fn_800893BC(Proc* p) {
    return p->pause;
}

void fn_800893C4(Proc* p) {
    p->pause++;
}

void fn_800893D4(Proc* p) {
    p->pause--;
}

#pragma use_lmw_stmw on
Proc* fn_800893E4(void* script, Proc* (*f)(Proc*, void*), void* arg) {
    Proc* result = 0;
    ProcLock* lock = (ProcLock*)lbl_803E4E88;
    Proc* q;
    int i;
    lock->lock();
    q = lbl_803D9A58;
    for (i = 0; i < 0x100; i++, q++) {
        if (q->script == script && (result = f(q, arg)) != 0) {
            break;
        }
    }
    lock->unlock();
    return result;
}
#pragma use_lmw_stmw off

}
