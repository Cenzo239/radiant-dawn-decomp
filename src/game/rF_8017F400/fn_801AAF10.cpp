#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

class Pad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38();
    virtual u32 rep();  /* +0x3C */
    virtual void v40(); virtual void v44();
    virtual u32 held(); /* +0x48 */
};

class VWin {
public:
    u8 pad[0x28];
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void destroy(int del); /* vtable +0x14 */
};

typedef struct CPos {
    s16 x, y;
    s16 pad;
} CPos;

/* movie / sound-test style list menu, 0xD4 bytes */
typedef struct MData {
    u32 flags;  /* 0x00 */
    int sel;    /* 0x04 */
    s16 x8;
    s16 xA;
    s16 curX;   /* 0x0C */
    s16 curY;   /* 0x0E */
    s16 x10;
    s16 x12;
    s16 x14;
    s16 x16;
    s16 x18;
    u8 pad1A[2];
    f32 scroll; /* 0x1C */
    s16 x20;
    s16 x22;
    s16 x24;
    s16 x26;
    u8 pad28[2];
    CPos pos[11]; /* 0x2A */
    u8 pad6C_[0x6C - 0x6C];
    void* res;  /* 0x6C */
    u8 pad70[0xD0 - 0x70];
    VWin* win;  /* 0xD0 */
} MData;

typedef struct MProc {
    u8 pad[0x30];
    MData* d;
} MProc;

extern MData* lbl_804CB98C;
extern MProc* lbl_804CB988;
extern Pad* lbl_804CB5B8;
extern char lbl_8036D4B8[];
extern char lbl_804CA798[8];
extern u8 lbl_80389010[];
extern u8 lbl_80389098[];
extern void fn_801C6EAC(const char* a, const char* b, char* out);
extern void fn_800068A0(void* res, const char* path);
extern void* fn_80078CCC(u32 size, const char* tag, int arg);
extern VWin* fn_80179660(void* p);
extern void fn_801798A8(VWin* w, int a);
extern void fn_8017980C(VWin* w, int x, int y, int z);
extern void fn_80253EE4(const char* s, f32 v);
extern void fn_80083DC4(void* p, int r);
extern void fn_80083B78(void* p);
extern double fn_80295CF0(double x);
extern void fn_80006A2C(void* p);
extern void fn_80078E24(void* p);
#if TARGET_PC
extern FE10_PROTO void fn_800D1D14(p32arg, int b, int c);
#else
extern void fn_800D1D14(u32 a, int b, int c);
#endif
extern int fn_800D2150(void);
extern MProc* fn_80081194(void* cls, void* parent);
extern void fn_803080DC(int a, int b, int c, int d);

void fn_801AAF10(void) {
    char path[0x60];
    int z = 0;
    int i;
    lbl_804CB98C->flags = z;
    lbl_804CB98C->sel = z;
    lbl_804CB98C->curX = -100;
    lbl_804CB98C->curY = -100;
    lbl_804CB98C->x8 = 0x68;
    lbl_804CB98C->xA = 0x70;
    lbl_804CB98C->x22 = z;
    lbl_804CB98C->x20 = z;
    lbl_804CB98C->scroll = z;
    lbl_804CB98C->x24 = z;
    for (i = 0; i < 11; i++) {
        CPos* p = &lbl_804CB98C->pos[i];
        p->x = lbl_804CB98C->x8 + 0x16;
        p->y = lbl_804CB98C->xA + 10 + i * 30;
    }
    lbl_804CB98C->x10 = 4;
    lbl_804CB98C->x12 = lbl_804CB98C->curX;
    lbl_804CB98C->x14 = lbl_804CB98C->curY;
    lbl_804CB98C->x16 = lbl_804CB98C->pos[lbl_804CB98C->sel].x;
    lbl_804CB98C->x18 = lbl_804CB98C->pos[lbl_804CB98C->sel].y - lbl_804CB98C->x22 * 30;
    lbl_804CB98C->x10 = 0;
    lbl_804CB98C->curX = lbl_804CB98C->x16;
    lbl_804CB98C->curY = lbl_804CB98C->x18;
    fn_801C6EAC(lbl_8036D4B8 + 0x3B, lbl_8036D4B8 + 0x56, path);
    fn_800068A0(&lbl_804CB98C->res, path);
    {
        void* p = fn_80078CCC(0x2C, lbl_804CA798, 0);
        if (p != NULL) {
            p = fn_80179660(p);
        }
        lbl_804CB98C->win = (VWin*)p;
    }
    fn_801798A8(lbl_804CB98C->win, 1);
    fn_8017980C(lbl_804CB98C->win, lbl_804CB98C->x8 + 0xEE, lbl_804CB98C->xA + 0xA, 0xEC);
}

static inline void ScrollToI(int from, int to, int n) {
    lbl_804CB98C->x20 = from;
    lbl_804CB98C->x22 = to;
    lbl_804CB98C->x26 = n;
    lbl_804CB98C->x24 = n;
}

static inline void ScrollTo(f32 from, f32 to, int n) {
    lbl_804CB98C->x20 = from;
    lbl_804CB98C->x22 = to;
    lbl_804CB98C->x26 = n;
    lbl_804CB98C->x24 = n;
}

void fn_801AB1C4(void) {
    u32 held = lbl_804CB5B8->held();
    u32 rep = lbl_804CB5B8->rep();
    int sel = lbl_804CB98C->sel;
    if (held & 0x400) {
        fn_80253EE4(lbl_8036D4B8 + 0x5B, 0.0f);
        fn_80083DC4(lbl_804CB988, 1);
        return;
    }
    if (held & 0x800) {
        fn_80253EE4(lbl_8036D4B8 + 0x6B, 0.0f);
        fn_80083B78(lbl_804CB988);
        return;
    }
    if (sel == 0) {
        if (held & 0x800008) {
            lbl_804CB98C->sel = 10;
            ScrollToI(lbl_804CB98C->scroll, 3, fn_80295CF0(44.0));
        }
    } else if (rep & 0x800008) {
        lbl_804CB98C->sel = sel - 1;
        if (lbl_804CB98C->sel - lbl_804CB98C->scroll <= 1.0f && lbl_804CB98C->scroll > 0.0f) {
            ScrollTo(lbl_804CB98C->scroll, lbl_804CB98C->scroll - 1.0f, 4);
        }
    }
    if (lbl_804CB98C->sel == 10) {
        if (held & 0x400004) {
            lbl_804CB98C->sel = 0;
            ScrollToI(lbl_804CB98C->scroll, 0, fn_80295CF0(44.0));
        }
    } else if (rep & 0x400004) {
        lbl_804CB98C->sel = lbl_804CB98C->sel + 1;
        if (lbl_804CB98C->sel - lbl_804CB98C->scroll >= 6.0f && lbl_804CB98C->scroll < 3.0f) {
            ScrollTo(lbl_804CB98C->scroll, 1.0f + lbl_804CB98C->scroll, 4);
        }
    }
    if (sel != lbl_804CB98C->sel) {
        lbl_804CB98C->x10 = 4;
        lbl_804CB98C->x12 = lbl_804CB98C->curX;
        lbl_804CB98C->x14 = lbl_804CB98C->curY;
        lbl_804CB98C->x16 = lbl_804CB98C->pos[lbl_804CB98C->sel].x;
        lbl_804CB98C->x18 = lbl_804CB98C->pos[lbl_804CB98C->sel].y - lbl_804CB98C->x22 * 30;
        fn_80253EE4(lbl_8036D4B8 + 0x7B, 0.0f);
    }
}

void fn_801AB50C(void) {
    fn_80006A2C(&lbl_804CB98C->res);
    if (lbl_804CB98C->win != NULL) {
        lbl_804CB98C->win->destroy(1);
    }
    fn_80078E24(lbl_804CB988->d);
    lbl_804CB988->d = NULL;
    lbl_804CB98C = NULL;
}

void fn_801AB574(void) {
    lbl_804CB98C->flags |= 1;
}

void fn_801AB588(void) {
    fn_800D1D14(*(u32*)(lbl_80389010 + lbl_804CB98C->sel * 12), 0, 1);
}

void fn_801AB5AC(void) {
    u32 held = lbl_804CB5B8->held();
    if (fn_800D2150() == 0 || (held & 0x4000)) {
        fn_80083B78(lbl_804CB988);
    }
}

void fn_801AB604(void) {
    lbl_804CB98C->flags &= ~1;
}

void fn_801AB618(void* parent) {
    lbl_804CB988 = fn_80081194(lbl_80389098, parent);
    lbl_804CB988->d = (MData*)fn_80078CCC(0xD4, lbl_8036D4B8 + 0x97, 0);
    lbl_804CB98C = lbl_804CB988->d;
}

void fn_801AB674(void* unused, s16* r) {
    fn_803080DC(r[0], r[1], r[2], r[3]);
}


/* telop / caption card, 0x19C bytes */
typedef struct TData {
    u32 x0;
    int timer;  /* 0x04 */
    int w;      /* 0x08 */
    char text[0x80]; /* 0x0C */
    u32 snd;    /* 0x8C */
    char line1[0x80]; /* 0x90 */
    char line2[0x80]; /* 0x110 */
    int lines;  /* 0x190 */
    u8 mode;    /* 0x194 */
    u8 pad195[3];
    f32 vol;    /* 0x198 */
} TData;

typedef struct TProc {
    u8 pad[0x30];
    TData* d;
} TProc;

class Snd {
public:
    virtual void v08();
    virtual void kill(); /* +0x0C */
    virtual int isOk(); /* +0x10 */
    virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void stop(int ms); /* +0x24 */
};

extern s8 lbl_804CB9A0;
extern s16 lbl_804CB9A8[4];
extern char lbl_8036D55C[];
extern u8 lbl_80389158[];
extern u32 lbl_804CB700;
extern f32 fn_802510B4(int a);
extern void fn_80250D64(int a, f32 x, f32 y);
extern char* strcpy(char* d, const char* s);
extern void* memcpy(void* d, const void* s, u32 n);
extern int fn_800CA3DC(const char* s, int n, f32 scale);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32 x, f32 y, f32 z, f32 w);
extern void fn_8007E7DC(int a);
extern f32 fn_8017F68C(int a, f32 x, f32 y, f32 t, f32 d);
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void* cb, s16* r);
#endif
extern void fn_80074A64(int a, int b, int c, int d);
extern void fn_801BCA5C(f32 v);
extern void fn_800CB3A8(f32 a, f32 b, int x, int y, int c, int d, int e, const char* fmt, ...);
extern void fn_8007E7B4(void);
#if TARGET_PC
extern FE10_PROTO Snd* fn_8024F704(p32arg);
#else
extern Snd* fn_8024F704(u32 id);
#endif

void fn_801AB68C(TProc* p) {
    if (p != NULL) {
        TData* d = p->d;
        d->x0 = 0;
        d->timer = 0;
        if (d->snd != 0) {
            fn_80253EE4((const char*)d->snd, 0.0f);
            d->vol = fn_802510B4(0);
            fn_80250D64(0, 0.5f * d->vol, 0.0f);
        }
        d->lines = 1;
        strcpy(d->line1, d->text);
        {
            char* q = d->text;
            int i = 0;
            for (; *q != 0; q++, i++) {
                if (*q == '\n') {
                    memcpy(d->line1, d->text, i);
                    d->line1[i] = 0;
                    strcpy(d->line2, q + 1);
                    d->lines = 2;
                }
            }
        }
        {
            int w1 = fn_800CA3DC(d->line1, -1, 1.0f);
            int w2;
            if (d->lines == 2) {
                w2 = fn_800CA3DC(d->line2, -1, 1.0f);
            } else {
                w2 = 0;
            }
            if (w1 > w2) {
                d->w = w1;
            } else {
                d->w = w2;
            }
        }
    }
}

void fn_801AB7C4(TData* d) {
    u16 tw;
    int x;
    int w;
    if (!lbl_804CB9A0) {
        lbl_804CB9A0 = 1;
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 8.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    if (d->timer <= 12) {
        w = fn_8017F68C(0, 0.0f, 608.0f, d->timer, 12.0f);
        x = (0x260 - w) / 2;
    } else {
        w = 0x260;
        x = 0;
    }
    tw = fn_800CA3DC(d->line1, -1, 1.0f);
    switch ((s8)d->mode) {
    case 0:
        lbl_804CB9A8[0] = x;
        lbl_804CB9A8[1] = 0xC0;
        lbl_804CB9A8[2] = w;
        lbl_804CB9A8[3] = 0x32;
        fn_8007E154();
        fn_8007E74C((void*)fn_801AB674, lbl_804CB9A8);
        fn_8007E164();
        fn_80074A64(0, 0xC0, 0xFF, 0);
        fn_801BCA5C(-1.0f);
        fn_800CB3A8(1.0f, 0.0f, (s16)(0x130 - ((u32)tw >> 1)), 0xCC, 1, 0, 0, d->line1);
        fn_801BCA5C(1.0f);
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E164();
        break;
    case 1:
        lbl_804CB9A8[0] = x;
        lbl_804CB9A8[1] = 0xC0;
        lbl_804CB9A8[2] = w;
        lbl_804CB9A8[3] = 0x32;
        fn_8007E154();
        fn_8007E74C((void*)fn_801AB674, lbl_804CB9A8);
        fn_8007E164();
        fn_80074A64(0, 0xC0, 0xFF, 1);
        fn_801BCA5C(-1.0f);
        fn_800CB3A8(1.0f, 0.0f, (s16)(0x130 - ((u32)tw >> 1)), 0xCC, 1, 0, 0, d->line1);
        fn_801BCA5C(1.0f);
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E164();
        break;
    case 2:
        fn_80074A64(0xA0, 0xBE, 0xFF, 2);
        fn_801BCA5C(-1.0f);
        fn_800CB3A8(1.0f, 0.0f, (s16)(0x130 - ((u32)tw >> 1)), 0xD8, 2, 0, 0, d->line1);
        fn_801BCA5C(1.0f);
        break;
    }
}

void fn_801ABA64(TProc* p) {
    TData* d = p->d;
    u32 held = lbl_804CB5B8->held();
    d->timer++;
    if (d->timer >= 120 || (d->timer >= 60 && ((held & 0x400) || (held & 0x800) || (lbl_804CB700 & 1)))) {
        if (d->snd != 0) {
            Snd* s = fn_8024F704(d->snd);
            if (s != NULL && s->isOk() != 0) {
                s->stop(500);
                s->kill();
            }
        }
        fn_80083B78(p);
    }
    fn_801AB7C4(d);
}

void fn_801ABB5C(TProc* p) {
    TData* d = p->d;
    if (d->snd != 0) {
        fn_80250D64(0, d->vol, 0.0f);
    }
    fn_80078E24(d);
}

void fn_801ABBA8(const char* text, u32 snd, void* parent, u8 mode) {
    TProc* p = (TProc*)fn_80081194(lbl_80389158, parent);
    TData* d;
    p->d = (TData*)fn_80078CCC(0x19C, lbl_8036D55C, 0);
    d = p->d;
    strcpy(d->text, text);
    d->snd = snd;
    d->mode = mode;
}

}
