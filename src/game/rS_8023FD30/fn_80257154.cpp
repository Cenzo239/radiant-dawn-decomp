#include "game/rS_8023FD30/sndmgr.h"

/* Command queue of the sound thread. lbl_804CBFF8 counts pending commands. */
extern "C" {

extern s32 lbl_804CBFF8;
int fn_8031D284(void*, void*, s32);
u32* fn_80077064(const char*);
u32 fn_802AD3C0(void*, u32);

static inline u8 cmdType(BOOL found, int a, int b) {
    u8 t = a;
    if (found) {
        t = b;
    }
    return t;
}

static inline u32 groupId(const char* name) {
    u32* p = fn_80077064(name);
    return fn_802AD3C0(sGroups, p[1]);
}

static inline u32 groupId2(const char* name) {
    u32* p = fn_80077064(name);
    return fn_802AD3C0((u8*)&sMutex + 0xFC, p[1]);
}

#pragma use_lmw_stmw on
BOOL fn_80257154(u32 id, u32 arg) {
    SndCmdLock& m = sCmdMutex;
    SndCmdGuard l(m);
    BOOL found;
    BOOL ok;
    m.lock();
    {
        SndCmd* c = sCmds;
        SndCmd* end = &sCmds[lbl_804CBFF8];
        found = FALSE;
        while (c != end) {
            if (id == c->id) {
                found = TRUE;
                break;
            }
            c++;
        }
    }
    m.unlock();
    {
        SndCmd* c = &sCmds[lbl_804CBFF8++];
        BOOL send = TRUE;
        if (c->busy || c->cancel) {
            c->type = cmdType(found, 2, 3);
            c->busy = 0;
            c->cancel = 0;
            c->result = -1;
            c->id = id;
            c->arg = arg;
        } else {
            switch (c->type) {
            case 4:
                c->type = cmdType(found, 5, 6);
                c->busy = 0;
                c->cancel = 0;
                send = FALSE;
                c->id = id;
                c->arg = arg;
                break;
            default:
                c->type = cmdType(found, 2, 3);
                c->busy = 0;
                c->cancel = 0;
                c->result = -1;
                c->id = id;
                c->arg = arg;
                break;
            }
        }
        if (send) {
            ok = fn_8031D284(sCmdQueue, c, 1) != 0;
        }
        if (ok == 0) {
            lbl_804CBFF8--;
        }
    }
    return ok;
}
#pragma use_lmw_stmw off

void fn_802573EC(void) {
    SndCmdLock& m = sCmdMutex;
    SndCmdGuard l(m);
    BOOL ok = TRUE;
    {
        s32 n = --lbl_804CBFF8;
        SndCmd* c = &sCmds[n];
        BOOL send = TRUE;
        if (c->busy || c->cancel) {
            c->type = 4;
            c->busy = 0;
            c->cancel = 0;
        } else {
            switch ((s8)c->type) {
            case 5:
            case 6:
                c->type = 4;
                c->busy = 0;
                c->cancel = 0;
                break;
            default:
                c->type = 1;
                send = FALSE;
                break;
            }
        }
        if (send) {
            ok = fn_8031D284(sCmdQueue, c, 1) != 0;
        }
        if (ok == 0) {
            lbl_804CBFF8++;
        }
    }
}

BOOL fn_80257520(const char* name) {
    SndCmdLock& m = sCmdMutex;
    SndCmdGuard l(m);
    u32 id;
    BOOL found;
    id = fn_802AD3C0(sGroups, fn_80077064(name)[1]);
    m.lock();
    {
        SndCmd* c = sCmds;
        SndCmd* end = &sCmds[lbl_804CBFF8];
        found = FALSE;
        while (c != end) {
            if (id == c->id) {
                found = TRUE;
                break;
            }
            c++;
        }
    }
    m.unlock();
    return found;
}

BOOL fn_80257628(const char* name) {
    SndCmdLock& m = sCmdMutex;
    SndCmdGuard l(m);
    u32 id;
    BOOL found;
    id = fn_802AD3C0(sGroups, fn_80077064(name)[1]);
    m.lock();
    {
        SndCmd* c = sCmds;
        SndCmd* end = &sCmds[lbl_804CBFF8];
        found = FALSE;
        while (c != end) {
            if (id == c->id) {
                found = c->busy != 0;
                break;
            }
            c++;
        }
    }
    m.unlock();
    return found;
}

static inline SndCmd* cmdLast(SndCmd* b, s32 n) {
    return &b[n - 1];
}

BOOL fn_80257740(void) {
    SndCmdLock& m = sCmdMutex;
    BOOL r;
    m.lock();
    r = TRUE;
    if (lbl_804CBFF8 > 0) {
        SndCmd* c = cmdLast(sCmds, lbl_804CBFF8);
        while (c != sCmds) {
            if ((s32)c->type == 2) {
                r = c->busy != 0;
                break;
            }
            c--;
        }
    }
    m.unlock();
    return r;
}

BOOL fn_80257340(const char* name, u32 arg) {
    SndCmdGuard l(sCmdMutex);
    u32* p = fn_80077064(name);
    return fn_80257154(fn_802AD3C0(sGroups, p[1]), arg);
}

s32 fn_802578F0(void) {
    s32 r;
    sCmdMutex.lock();
    r = lbl_804CBFF8;
    sCmdMutex.unlock();
    return r;
}

}
