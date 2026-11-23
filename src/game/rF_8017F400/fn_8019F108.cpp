/* fn_8019F108 (file menu window init): exact (round m6).
   Lever: a dead first `w->mode = 0;` before `w->flags = 1;` creates the zero constant before the one,
   which puts 0 in r5 and 1 in r4 like the original (the dead store itself is removed).
   Check with: check_func.py --symbol-map fn_8019F108.symbols.json --strict-references (maps the 13
   string literals of the table to their labels). */
#include "game/rF_8017F400/types.h"

extern "C" {

/* file menu window (0x28 bytes, see fn_801958C0.cpp WinAnim) */
typedef struct FMWin {
    s16 flags; /* 0x0 */
    s16 id;    /* 0x2 */
    s16 x4;    /* 0x4 */
    s16 x;     /* 0x6 */
    s16 y;     /* 0x8 */
    s16 fromX; /* 0xa */
    s16 toX;   /* 0xc */
    s16 fromY; /* 0xe */
    s16 toY;   /* 0x10 */
    s16 mode;  /* 0x12 */
    s16 t;     /* 0x14 */
    s16 dur;   /* 0x16 */
    s16 a0;    /* 0x18 */
    s16 a1;    /* 0x1a */
    s16 a2;    /* 0x1c */
    s16 at;    /* 0x1e */
    s16 adur;  /* 0x20 */
    u8 pad22[2];
    char* msg; /* 0x24 */
} FMWin;

typedef struct Mover {
    s16 flags; /* 0x0 */
    u8 pad2[4];
    s16 x;     /* 0x6 */
    s16 y;     /* 0x8 */
    s16 fromX; /* 0xa */
    s16 fromY; /* 0xc */
    s16 toX;   /* 0xe */
    s16 toY;   /* 0x10 */
    s16 t;     /* 0x12 */
    s16 dur;   /* 0x14 */
} Mover;

typedef struct Fade2 {
    s16 a;     /* 0x0 */
    s16 b;     /* 0x2 */
    s16 fromA; /* 0x4 */
    s16 toA;   /* 0x6 */
    s16 fromB; /* 0x8 */
    s16 toB;   /* 0xa */
    s16 t;     /* 0xc */
    s16 dur;   /* 0xe */
} Fade2;

typedef struct MsgTable {
    const char* ids[13];
} MsgTable;

extern s16 lbl_804CB93A;
extern s16 lbl_804CB93E;
extern const MsgTable lbl_8036C52C;
extern void* memset(void* p, int c, u32 n);
extern char* fn_800D0864(const char* id);
extern void fn_80253EE4(f32 vol, const char* name); /* play SFX */

static inline void setMode(FMWin* w, int m) { w->mode = m; }
#pragma use_lmw_stmw on
void fn_8019F108(FMWin* w, int x4, int id)
{
    const char* tbl[] = {
        "FM_START", "FM_LOAD", "FM_CONTINUE", "FM_COPY", "FM_DELETE", "FM_EXTRA", "FM_ILLUST",
        "FM_SOUNDROOM", "FM_MOVIEROOM", "FM_CONVERSATIONROOM", "FM_CONVERSATIONROOM_FE8",
        "FM_RECORDROOM", "FM_EXTRAMAP",
    };
    memset(w, 0, 0x28);
    w->mode = 0;
    w->flags = 1;
    w->x4 = x4;
    w->id = id;
    w->mode = 0;
    w->msg = fn_800D0864(tbl[w->id]);
    w->a0 = 0xFF;
}
#pragma use_lmw_stmw off

}
