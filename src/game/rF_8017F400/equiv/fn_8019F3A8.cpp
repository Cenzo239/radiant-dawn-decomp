/* r19: copied from wip/fn_8019F3A8.cpp; `sched` level (same instructions per basic block, order differs). */
/* wip: fn_8019F3A8 (file menu entry init), 55/89 words. Code is identical except that
 * the entry pointer gets r31 instead of r30 (the original keeps the constant 0 in r31). */
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

/* 0x7c-byte file menu entry */
typedef struct FMEntry {
    s16 flags; /* 0x0 */
    s16 x2;
    s16 type;  /* 0x4 */
    u8 pad6[0x14 - 0x6];
    s16 x14;
    u8 pad16[0x1A - 0x16];
    s16 a0;    /* 0x1a */
    s16 a1;    /* 0x1c */
    s16 a2;    /* 0x1e */
    s16 at;    /* 0x20 */
    s16 adur;  /* 0x22 */
    u8 pad24[2];
    s16 x26;
    int x28;
    int x2c;
    int x30;
    s16 x34;
    s16 x36;
    char name[0x40]; /* 0x38 */
    f32 x78;
} FMEntry;

typedef struct FMGlobal {
    u8 pad[0xC];
    void* res;  /* 0xc */
    void* draw; /* 0x10 */
    u8 pad14[0x88 - 0x14];
    void* buf;  /* 0x88 */
} FMGlobal;

extern FMGlobal* lbl_804CB934;
extern void* lbl_804CB92C;
extern void* lbl_804CB930;
extern const char lbl_8036C5E8[0x3D0];
extern char lbl_803889E8[9]; /* "FM_CLEAR" */
extern char lbl_803889F4[9]; /* "FM_BASES" */
extern char lbl_80388A00[9]; /* "FM_CLEAR" */
extern char* strcpy(char* d, const char* s);
extern void fn_801C6EAC(const char* a, const char* b, char* out);
extern void fn_800068EC(void* handle, const char* path, int flags);
extern void fn_80250D64(f32 a, f32 b, int ch);
extern void* fn_80177284(void (*func)(void), void* arg); /* register draw callback */
extern void fn_80197BF0(void);
extern void fn_80197928(void);
extern void* fn_80078CCC(u32 size, const char* tag, int arg); /* alloc */
extern s16 lbl_804CB93A;
extern s16 lbl_804CB93E;
extern const MsgTable lbl_8036C52C;
extern void* memset(void* p, int c, u32 n);
extern char* fn_800D0864(const char* id);
extern void fn_80253EE4(f32 vol, const char* name); /* play SFX */

static inline void FMEntry_SetLabel(FMEntry* e, s16 kind, const char* name, int a, int b, int c)
{
    e->flags |= 4;
    e->x26 = kind;
    strcpy(e->name, name);
    e->x28 = a;
    e->x2c = b;
    e->x30 = c;
    e->x34 = 0;
    e->x36 = 0;
}

void fn_8019F3A8(FMEntry* e, int type)
{
    memset(e, 0, 0x7C);
    e->flags = 1;
    e->type = type;
    e->x2 = 0;
    e->x14 = 0;
    e->x78 = 0.0f;
    e->a0 = 0xFF;
    e->flags = 1;
    switch (e->type) {
    case 0:
        FMEntry_SetLabel(e, 2, lbl_80388A00, 0, 0x37, 0x21);
        break;
    case 3:
        FMEntry_SetLabel(e, 5, lbl_803889F4, 2, 0xD, 0x33);
        break;
    case 4:
        FMEntry_SetLabel(e, 4, lbl_803889E8, 1, 0x2D, 5);
        break;
    }
}

}
