/* File menu: choice cursor input (three choices). */
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
        f32 alpha; /* 0x4a4 */
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
#if TARGET_PC
extern FE10_PROTO void fn_8024B978(int slot, ptr32<const void>, p32arg);
extern FE10_PROTO void fn_8024BB8C(int slot, ptr32<const void>, p32arg);
#else
extern void fn_8024B978(int slot, void* buf, int x);
extern void fn_8024BB8C(int slot, void* buf, int x);
#endif
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
extern char lbl_804CA440[8];
extern void* fn_80078CCC(u32 size, const char* tag, int arg); /* alloc */
extern void* fn_8017948C(void* w, int type);
extern void fn_8017918C(void* w, int x, int y);
extern void fn_801791D0(void* w, f32 v);
extern void fn_8017920C(void* w, int a);
extern void fn_801791D8(void* w, int n);
extern f32 fn_8017F68C(int mode, f32 from, f32 to, f32 t, f32 d); /* interpolate */
extern int fn_802450BC(SysInfo* s);


static inline void FM_MoveRect(HelpBar::FMCursor* c, s16 x, s16 y, s16 w, s16 h)
{
    c->xe = c->xa;
    c->x10 = c->xc;
    c->x12 = x;
    c->x14 = y;
    c->x18 = h;
    c->x16 = w;
}
static inline void FM_SetBarColor(u8 c, int t)
{
    HelpBar* g = lbl_804CB934;
    g->x8d = g->x8c;
    g->x8e = c;
    g->x98 = t;
    g->x94 = t;
}
static inline void FM_Hide(void)
{
    HelpBar::FMCursor* c = &lbl_804CB934->cur;
    c->x2 = 4;
    c->x4 = 5;
    c->xa = -1000;
    c->xc = -1000;
}
#define CUR (&lbl_804CB934->cur)
void fn_80194D58(void* proc) {
    u32 trig = lbl_804CB5B8->getHeld();
    u32 rep = lbl_804CB5B8->getRepeat();
    SysInfo* sys = fn_8024BC94();
    if (trig & 0x400) {
        if (lbl_804CB934->cur.sel == 2 && !(sys->flags & 4)) {
            fn_80253EE4(0.0f, lbl_8036C5E8 + 0x63);
        } else {
            fn_80253EE4(0.0f, lbl_8036C5E8 + 0x71);
            FM_SetBarColor(0, 15);
            FM_Hide();
            lbl_804CB93A = lbl_804CB934->cur.sel;
            fn_80083B78(proc);
        }
    } else if (trig & 0x800) {
        fn_80253EE4(0.0f, lbl_8036C5E8 + 0x81);
        FM_SetBarColor(0, 15);
        FM_Hide();
        lbl_804CB93A = 3;
        fn_80083B78(proc);
    } else {
        HelpBar* g = lbl_804CB934;
        s16 old = g->cur.sel;
        if ((rep & 0x200002) || (trig & 0x200002)) {
            g->cur.sel++;
            FM_MoveRect(&g->cur, (g->cur.x6 + 0x55) + g->cur.sel * 0x73, g->cur.x8 + 0x5C, 4, 4);
            {
                HelpBar::FMCursor* hc = &lbl_804CB934->cur;
                if (hc->sel > 2) {
                    if (trig & 0x200002) { hc->sel = 0; FM_MoveRect(hc, hc->x6 + 0x55, hc->x8 + 0x5C, 4, 4); }
                    else { hc->sel = 2; FM_MoveRect(hc, hc->x6 + 0x13b, hc->x8 + 0x5C, 4, 4); }
                }
            }
        }
        if ((rep & 0x100001) || (trig & 0x100001)) {
            HelpBar* g = lbl_804CB934;
            g->cur.sel--;
            FM_MoveRect(&g->cur, (g->cur.x6 + 0x55) + g->cur.sel * 0x73, g->cur.x8 + 0x5C, 4, 4);
            {
                HelpBar::FMCursor* hc = &lbl_804CB934->cur;
                if (hc->sel < 0) {
                    if (trig & 0x100001) { hc->sel = 2; FM_MoveRect(hc, hc->x6 + 0x13b, hc->x8 + 0x5C, 4, 4); }
                    else { hc->sel = 0; FM_MoveRect(hc, hc->x6 + 0x55, hc->x8 + 0x5C, 4, 4); }
                }
            }
        }
        if (old != lbl_804CB934->cur.sel) fn_80253EE4(0.0f, lbl_8036C5E8 + 0x91);
    }
}
}
