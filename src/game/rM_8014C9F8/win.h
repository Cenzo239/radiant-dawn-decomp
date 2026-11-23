#ifndef RM_WIN_H
#define RM_WIN_H
#include "game/rM_8014C9F8/types.h"

struct Color {
    u8 r, g, b, a;
};

/* One text line of the talk window. */
struct TLine {
    char text[0x40];
    char* end;      /* 0x40 */
    void clear() {
        text[0] = 0;
        end = text;
    }
};

/* Talk window proc. */
struct Win : Proc {
    TLine* lines[8]; /* 0x30 */
    s8 lineH;        /* 0x50 */
    s8 rows;         /* 0x51 */
    s8 head;         /* 0x52 */
    s8 tail;         /* 0x53 */
    u8 reveal;       /* 0x54 */
    u8 speed;        /* 0x55 */
    u8 style;        /* 0x56 */
    u8 b57;          /* 0x57 */
    s16 x;           /* 0x58 */
    s16 y;           /* 0x5A */
    s16 w;           /* 0x5C */
    s16 h;           /* 0x5E */
    s16 scissor[4];  /* 0x60 */
    s16 bx;          /* 0x68 */
    s16 by;          /* 0x6A */
    s16 bw;          /* 0x6C */
    s16 bz;          /* 0x6E */
    void* obj;       /* 0x70 */
    s16 objx;        /* 0x74 */
    s16 objy;        /* 0x76 */
    Color col;       /* 0x78 */
    u8 pad7C[4];
    u8 alpha;        /* 0x80 */
    u8 bright;       /* 0x81 */
    s8 parentNo;     /* 0x82 */
    u8 b83;          /* 0x83 */
};

/* Helper procs driving a window. */
struct WinFade : Proc {
    Win* win;  /* 0x30 */
    int a;     /* 0x34 */
    int b;     /* 0x38 */
    int c;     /* 0x3C */
    int d;     /* 0x40 */
};

struct Saved {
    u32 w;
    u16 h;
    u32 has(u32 m) { return w & m; }
};
struct Flags {
    u32 w;
    u32 has(u32 m) { return w & m; }
};

extern "C" {
extern Flags lbl_804CB700;
extern Saved lbl_804CB878;
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
extern void fn_8014D220(Saved*);
extern int fn_80148634(void);
}

#endif
