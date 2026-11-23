/* fn_801A2268: help text line splitter. Exact (round m2, m2-b): the three line clears are a loop k < 3 (unrolled by the compiler). */
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

void fn_801A2268(HelpWin* h, const char* s)
{
    int col;
    int n;
    int maxw;
    {int k; for (k = 0; k < 3; k++) h->line[k][0] = 0;}
    maxw = 0;
    col = 0;
    n = 0;
    for (;;) {
        if ((s[0] == 2 && s[1] == 'm' && s[2] == 'c') || (s[0] == 2 && s[1] == 'm' && s[2] == 'd')) {
            s += 3;
            continue;
        }
        if (*s == 0 || *s == '\n') {
            int w;
            h->line[n][col] = 0;
            w = fn_800CA3DC(h->line[n], -1, 1.0f);
            n++;
            if (w > maxw) {
                maxw = w;
            }
            if (*s == 0) {
                break;
            }
            col = 0;
            s++;
            continue;
        }
        h->line[n][col++] = *s;
        s++;
    }
    h->nlines = n;
    h->maxw = maxw;
}

}
