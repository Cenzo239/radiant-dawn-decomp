#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

/* help window (lbl_8041EB20, 0x124 bytes used) */
typedef struct HelpWin {
    u32 flags;          /* 0x0 */
    char line[3][0x40]; /* 0x4 */
    void* res;          /* 0xc4 */
    u8 padc8[4];
    int xcc;            /* 0xcc */
    int nlines;         /* 0xd0 */
    int maxw;           /* 0xd4 */
    s16 xd8;            /* 0xd8 */
    u8 padda[2];
    f32 xdc;
    f32 xe0;
    u8 pade4[0xF4 - 0xE4];
    f32 xf4;
    f32 xf8;
    f32 xfc;
    f32 x100;
    f32 x104;
    f32 x108;
    f32 x10c;
    f32 x110;
    f32 x114;
    f32 x118;
    f32 x11c;
    f32 x120;
    u8 pad124[4];
} HelpWin;

/* help window process (class lbl_80388A70) */
typedef struct HelpProc {
    u8 pad[0x2E];
    u8 busy; /* 0x2e */
} HelpProc;

class Pad {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual u32 getTrigger(); /* vtable +0x34 */
    virtual void v38();
    virtual u32 getRepeat();  /* vtable +0x3c */
    virtual void v40();
    virtual void v44();
    virtual u32 getHeld();    /* vtable +0x48 */
};

extern Pad* lbl_804CB5B8;
extern HelpWin lbl_8041EB20;
extern u8 lbl_80388A70[0x20];
extern u8 lbl_80388A90[0x10];
extern const char lbl_8036CA00[0xC0];
extern void fn_80006A2C(void* handle); /* release resource handle */
extern void fn_800068A0(void* handle, const char* path);
extern void* memset(void* p, int c, u32 n);
extern void* fn_80083B84(void* cls);
extern void* fn_80081050(void* cls, void* parent);
extern void* fn_80081194(void* cls, void* parent);
extern void fn_80083B78(void* proc);
extern void fn_80253EE4(f32 vol, const char* name); /* play SFX */
extern int fn_800CA3DC(const char* s, int n, f32 scale);
extern char* fn_800D0864(const char* id);
extern void fn_801C6EAC(const char* a, const char* b, char* out);
extern void fn_801A1DCC(HelpWin* h, char* msg, f32 x, f32 y);
extern void fn_803080DC(int x0, int y0, int x1, int y1);

void fn_801A1A80(void)
{
    fn_80006A2C(&lbl_8041EB20.res);
    memset(&lbl_8041EB20, 0, 0x124);
}

static inline BOOL Help_IsIdle(void)
{
    HelpProc* p = (HelpProc*)fn_80083B84(lbl_80388A70);
    if (p == NULL) {
        return FALSE;
    }
    return p->busy == 0;
}

void fn_801A1CFC(HelpWin* h)
{
    if (Help_IsIdle() && !(h->flags & 1)) {
        h->flags |= 1;
        h->xfc = h->xf4;
        h->x100 = h->xf8;
        h->x104 = 24.0f + h->xdc;
        h->x108 = 25.0f + h->xe0;
        h->x114 = h->x10c;
        h->x118 = h->x110;
        h->x11c = 0.0f;
        h->x120 = 0.0f;
        h->xcc = 8;
        fn_80253EE4(0.0f, lbl_8036CA00 + 0x9F /* "SFX_SYS_HELP_WINDOW_CLOSE1" */);
    }
}

BOOL fn_801A2224(void)
{
    return Help_IsIdle();
}

void fn_801A2384(void* p)
{
    if (lbl_804CB5B8->getHeld() & 0xF0FFFF) {
        fn_801A1CFC(&lbl_8041EB20);
        fn_80083B78(p);
    }
}

void fn_801A23E0(int x, int y, const char* id, void* parent)
{
    char path[0x60];
    char* msg;
    fn_80081194(lbl_80388A90, parent);
    msg = fn_800D0864(id);
    if (!Help_IsIdle()) {
        fn_80081050(lbl_80388A70, parent);
        memset(&lbl_8041EB20, 0, 0x124);
        lbl_8041EB20.xdc = x;
        lbl_8041EB20.xe0 = y;
        lbl_8041EB20.xf4 = x;
        lbl_8041EB20.xf8 = y;
        lbl_8041EB20.x10c = 0.0f;
        lbl_8041EB20.x110 = 0.0f;
        fn_801C6EAC(lbl_8036CA00 + 0x6F /* "window/help/help" */, lbl_8036CA00 + 0x80 /* ".cms" */, path);
        fn_800068A0(&lbl_8041EB20.res, path);
        fn_80253EE4(0.0f, lbl_8036CA00 + 0x85 /* "SFX_SYS_HELP_WINDOW_OPEN1" */);
        fn_801A1DCC(&lbl_8041EB20, msg, x, y);
    }
    lbl_8041EB20.xd8 = 1;
    lbl_8041EB20.flags |= 2;
}

void fn_801A2570(void* unused, s16* r)
{
    fn_803080DC(r[0], r[1], r[2], r[3]);
}

}
