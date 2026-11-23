/* wip: fn_80194D58 (file menu 3-way cursor), 165/231 words match. Remaining diff is register
 * coloring in the cursor-move inline (4 constant in r6 vs r7, mul/x6 swapped). Other functions
 * in this copy are matched in ../fn_801945C0.cpp. */
#include "game/rF_8017F400/types.h"

extern "C" {

/* simple frame-count wait process (class lbl_803886D8) */
typedef struct WaitProc {
    u8 pad[0x30];
    f32 cur; /* 0x30 */
    f32 end; /* 0x34 */
} WaitProc;

/* menu/help-bar global, pointed to by lbl_804CB934 */
typedef struct HelpBar {
    u32 flags;      /* 0x0 */
    u8 pad4[0x1C - 0x4];
    int mode;       /* 0x1c */
    char text[0x6C]; /* 0x20 */
    u8 x8c;
    u8 x8d;
    u8 x8e;
    u8 pad8f;
    s16 x90;
    u8 pad92[2];
    int x94;
    int x98;
    u8 pad9c[0x488 - 0x9C];
    struct FMCursor {
        s16 x0;
        s16 x2;   /* 0x48a */
        s16 x4;   /* 0x48c */
        s16 x6;   /* 0x48e */
        s16 x8;   /* 0x490 */
        s16 xa;   /* 0x492 */
        s16 xc;   /* 0x494 */
        s16 xe;   /* 0x496 */
        s16 x10;  /* 0x498 */
        s16 x12;  /* 0x49a */
        s16 x14;  /* 0x49c */
        s16 x16;  /* 0x49e */
        s16 x18;  /* 0x4a0 */
        s16 sel;  /* 0x4a2 */
        u8 pad1c[4];
        void* win[2]; /* 0x4a8 */
    } cur; /* 0x488 */
} HelpBar;

typedef struct SysInfo {
    u8 pad[0x20];
    u32 flags; /* 0x20 */
} SysInfo;

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

/* static save-file buffers built on first use */
typedef struct DtorChain {
    void* next;
    void* dtor;
    void* obj;
} DtorChain;

extern HelpBar* lbl_804CB934;
extern const char lbl_8036C5E8[0x3D0];
extern u8 lbl_803886D8[0x14];
extern s8 lbl_804CB938;
extern s8 lbl_804CB939;
extern u8 lbl_8041CA08[0x1070];
extern u8 lbl_8041DA88[0x1098];
extern DtorChain lbl_8041C9F8;
extern DtorChain lbl_8041DA78;
extern int lbl_804CBFCC;
extern void fn_8019FAC8(void* p, int del);
extern void fn_80245C88(void* p);
extern void* __register_global_object(void* obj, void* dtor, void* chain);
extern void fn_8024B978(int slot, void* buf, int x);
extern void fn_8024BB8C(int slot, void* buf, int x);
extern void fn_80246494(void);
extern void* fn_80081194(void* cls, void* parent);
extern void fn_80083B78(void* proc);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32 x, f32 y, f32 z, f32 w);
extern char* fn_800CEB4C(void);
extern char* fn_800CEC24(void);
extern char* fn_800CF3A4(void);
extern char* fn_800CF470(void);
extern char* fn_800D0864(const char* id);
extern int fn_80290DDC(char* buf, const char* fmt, ...);
extern SysInfo* fn_8024BC94(void);
extern Pad* lbl_804CB5B8;
extern s16 lbl_804CB93A;
extern void fn_80253EE4(f32 vol, const char* name); /* play SFX */
extern void fn_801795E8(void* w, int x);
extern void* memset(void* p, int c, u32 n);
extern int fn_802450BC(SysInfo* s);

void fn_801945C0(WaitProc* p)
{
    p->cur += 1.0f;
    if (p->cur >= p->end) {
        fn_80083B78(p);
    }
}

void fn_801945E8(int frames, void* parent)
{
    WaitProc* p = (WaitProc*)fn_80081194(lbl_803886D8, parent);
    p->cur = 0.0f;
    p->end = frames;
}

void fn_80194644(void)
{
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 120.0f, 1.0f);
    fn_8007E164();
}

void* fn_801947D4(void)
{
    return &lbl_804CB934->x8c;
}

void* fn_801947E0(void)
{
    return (u8*)lbl_804CB934 + 0x9C;
}

void* fn_801947EC(int i)
{
    return (u8*)lbl_804CB934 + i * 0x28 + 0xB0;
}

void* fn_80194800(int i)
{
    return (u8*)lbl_804CB934 + i * 0x7C + 0x1A0;
}

void* fn_80194814(void)
{
    return (u8*)lbl_804CB934 + 0x488;
}

void* fn_80194820(int i)
{
    return (u8*)lbl_804CB934 + i * 0x1C + 0x4B0;
}

void fn_80194834(int mode)
{
    lbl_804CB934->mode = mode;
}

#pragma use_lmw_stmw on
void fn_80194840(void)
{
    char* a = fn_800CEB4C();
    char* b = fn_800CEC24();
    char* c = fn_800CF3A4();
    char* d = fn_800CF470();
    char* select = fn_800D0864(lbl_8036C5E8 + 0x0 /* "FM_SELECT" */);
    char* decide = fn_800D0864(lbl_8036C5E8 + 0xA /* "FM_DECIDE" */);
    char* cancel = fn_800D0864(lbl_8036C5E8 + 0x14 /* "FM_CANCEL" */);
    char* check = fn_800D0864(lbl_8036C5E8 + 0x1E /* "FM_CHECK" */);
    char* remain = fn_800D0864(lbl_8036C5E8 + 0x27 /* "FM_REMAIN" */);
    char* suspend = fn_800D0864(lbl_8036C5E8 + 0x31 /* "FM_SUSPEND" */);
    char* wiimenu = fn_800D0864(lbl_8036C5E8 + 0x3C /* "FM_WIIMENU" */);
    switch (lbl_804CB934->mode) {
    case 0:
        lbl_804CB934->text[0] = 0;
        break;
    case 1:
        fn_80290DDC(lbl_804CB934->text, lbl_8036C5E8 + 0x47 /* "%s%s  %s%s  %s%s" */, c, select, b, cancel, a, decide);
        break;
    case 2:
        fn_80290DDC(lbl_804CB934->text, lbl_8036C5E8 + 0x47 /* "%s%s  %s%s  %s%s" */, d, select, b, cancel, a, decide);
        break;
    case 3:
        fn_80290DDC(lbl_804CB934->text, lbl_8036C5E8 + 0x58 /* "%s%s  %s%s" */, b, remain, a, check);
        break;
    case 4:
        fn_80290DDC(lbl_804CB934->text, lbl_8036C5E8 + 0x58 /* "%s%s  %s%s" */, b, suspend, a, check);
        break;
    case 5:
        fn_80290DDC(lbl_804CB934->text, lbl_8036C5E8 + 0x58 /* "%s%s  %s%s" */, b, wiimenu, a, remain);
        break;
    }
}
#pragma use_lmw_stmw off

void* fn_801949E4(void)
{
    SysInfo* s = fn_8024BC94();
    if (fn_802450BC(s)) {
        return s;
    }
    return NULL;
}

void* fn_80194A28(int slot)
{
    if (!lbl_804CB938) {
        fn_80245C88(lbl_8041CA08);
        __register_global_object(lbl_8041CA08, fn_8019FAC8, &lbl_8041C9F8);
        lbl_804CB938 = 1;
    }
    fn_8024B978(slot, lbl_8041CA08, 0);
    fn_80246494();
    if (lbl_804CBFCC == 0) {
        return lbl_8041CA08;
    }
    return NULL;
}

void* fn_80194AC0(int slot)
{
    if (!lbl_804CB939) {
        fn_80245C88(lbl_8041DA88);
        __register_global_object(lbl_8041DA88, fn_8019FAC8, &lbl_8041DA78);
        lbl_804CB939 = 1;
    }
    fn_8024BB8C(slot, lbl_8041DA88, 0);
    fn_80246494();
    if (lbl_804CBFCC == 0) {
        return lbl_8041DA88;
    }
    return NULL;
}

int fn_80194B58(void)
{
    return -1;
}

#pragma use_lmw_stmw on
int fn_80194B60(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        if (fn_80194AC0(i) != NULL) {
            return i;
        }
    }
    return -1;
}

int fn_80194C08(void)
{
    int i;
    int n = 0;
    for (i = 0; i < 6; i++) {
        if (fn_80194AC0(i) != NULL) {
            n++;
        }
    }
    return n;
}

int fn_80194CB0(void)
{
    int i;
    int n = 0;
    for (i = 0; i < 6; i++) {
        if (fn_80194A28(i) != NULL) {
            n++;
        }
    }
    return n;
}
#pragma use_lmw_stmw off

static inline void FM_SetBarColor(u8 c)
{
    HelpBar* g = lbl_804CB934;
    g->x8d = g->x8c;
    g->x8e = c;
    g->x98 = 15;
    g->x94 = 15;
}

static inline void FM_MoveRect(HelpBar::FMCursor* c, s16 x, s16 y, s16 w, s16 h)
{
    c->xe = c->xa;
    c->x10 = c->xc;
    c->x12 = x;
    c->x14 = y;
    c->x18 = h;
    c->x16 = w;
}

static inline void FM_SetCursor(s16 i)
{
    HelpBar::FMCursor* c = &lbl_804CB934->cur;
    c->sel = i;
    FM_MoveRect(c, c->x6 + i * 0x73 + 0x55, c->x8 + 0x5C, 4, 4);
}

static inline void FM_MoveCursor(int d)
{
    HelpBar::FMCursor* c = &lbl_804CB934->cur;
    c->sel += d;
    FM_MoveRect(c, c->x6 + c->sel * 0x73 + 0x55, c->x8 + 0x5C, 4, 4);
}

static inline void FM_HideCursor(void)
{
    HelpBar* g = lbl_804CB934;
    g->cur.x2 = 4;
    g->cur.x4 = 5;
    g->cur.xa = -1000;
    g->cur.xc = -1000;
}

void fn_80194D58(void* p)
{
    u32 held = lbl_804CB5B8->getHeld();
    u32 rep = lbl_804CB5B8->getRepeat();
    SysInfo* s = fn_8024BC94();
    HelpBar* g;
    s16 old;
    if (held & 0x400) {
        if (lbl_804CB934->cur.sel == 2 && !(s->flags & 4)) {
            fn_80253EE4(0.0f, lbl_8036C5E8 + 0x63 /* "SFX_SYS_MISS1" */);
            return;
        }
        fn_80253EE4(0.0f, lbl_8036C5E8 + 0x71 /* "SFX_SYS_SELECT1" */);
        FM_SetBarColor(0);
        FM_HideCursor();
        lbl_804CB93A = lbl_804CB934->cur.sel;
        fn_80083B78(p);
        return;
    }
    if (held & 0x800) {
        fn_80253EE4(0.0f, lbl_8036C5E8 + 0x81 /* "SFX_SYS_CANCEL1" */);
        FM_SetBarColor(0);
        FM_HideCursor();
        lbl_804CB93A = 3;
        fn_80083B78(p);
        return;
    }
    g = lbl_804CB934;
    old = g->cur.sel;
    if ((rep & 0x200002) || (held & 0x200002)) {
        FM_MoveCursor(1);
        if (lbl_804CB934->cur.sel > 2) {
            if (held & 0x200002) {
                FM_SetCursor(0);
            } else {
                FM_SetCursor(2);
            }
        }
    }
    if ((rep & 0x100001) || (held & 0x100001)) {
        FM_MoveCursor(-1);
        if (lbl_804CB934->cur.sel < 0) {
            if (held & 0x100001) {
                FM_SetCursor(2);
            } else {
                FM_SetCursor(0);
            }
        }
    }
    if (old != lbl_804CB934->cur.sel) {
        fn_80253EE4(0.0f, lbl_8036C5E8 + 0x91 /* "SFX_SYS_CURSOR_WINDOW_MOVE1" */);
    }
}

void fn_801950F4(void)
{
    int i;
    HelpBar::FMCursor* cur = &lbl_804CB934->cur;
    for (i = 0; i < 2; i++) {
        if (cur->win[i] != NULL) {
            fn_801795E8(cur->win[i], 1);
            cur->win[i] = NULL;
        }
    }
    memset(cur, 0, 0x28);
    cur->x2 = 1;
    FM_SetBarColor(0xA2);
    lbl_804CB934->x90 = -8;
    lbl_804CB934->mode = 2;
}

}
