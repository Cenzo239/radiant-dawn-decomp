#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

/* C++ object whose vptr sits at +0x28 (after its data members) */
class Obj28 {
public:
    u8 data[0x28];
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void release(int flag); /* vtable +0x14 */
};

typedef struct Struct80191134 {
    u8 pad[0x30];
    void* res;     /* 0x30 */
    u8 flags34;    /* 0x34 */
    u8 pad35[0x60 - 0x35];
    Obj28* obj;    /* 0x60 */
    u8 pad64[0x76 - 0x64];
    u8 closed;     /* 0x76 */
    u8 pad77;
    void* proc;    /* 0x78 */
} Struct80191134;

typedef struct CursorProc {
    u8 pad[0x58];
    int x;        /* 0x58 */
    int y;        /* 0x5C */
    u8 pad60[0xA];
    s8 dir;       /* 0x6A */
} CursorProc;

extern u8 lbl_803884A0[]; /* process class */
extern void fn_8018ED90(Struct80191134* p);
extern void fn_80081A90(void* proc);
extern void fn_80006A2C(void* handle);
extern void* fn_80081194(void* cls, void* parent);
extern void* fn_80083B84(void* cls);

void fn_80191134(Struct80191134* p)
{
    if (!p->closed) {
        if (p->obj != NULL) {
            p->obj->release(1);
        }
        fn_8018ED90(p);
        fn_80081A90(p->proc);
        if (p->res != NULL) {
            fn_80006A2C(&p->res);
        }
        p->closed = 1;
    }
}

void fn_801911B4(Struct80191134* p)
{
    p->flags34 |= 1;
}

void fn_801911C4(Struct80191134* p)
{
    p->flags34 &= ~1;
}

void fn_801911D4(void* parent)
{
    CursorProc* c = (CursorProc*)fn_80081194(lbl_803884A0, parent);
    c->y = -1;
    c->x = -1;
}

static inline BOOL Cursor_Exists(void)
{
    return fn_80083B84(lbl_803884A0) != NULL;
}

BOOL fn_8019120C(void)
{
    return Cursor_Exists();
}

BOOL fn_80191240(s16* x, s16* y, int* dir)
{
    *x = -1;
    *y = -1;
    if (!Cursor_Exists()) {
        return FALSE;
    }
    CursorProc* c = (CursorProc*)fn_80083B84(lbl_803884A0);
    *x = c->x;
    *y = c->y;
    *dir = c->dir;
    return TRUE;
}

}
