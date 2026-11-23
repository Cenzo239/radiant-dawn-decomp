#ifndef RN_8025EEF0_DICT_H
#define RN_8025EEF0_DICT_H
#include "game/rN_8025EEF0/types.h"

/* Dictionary menu: dictionary.bin (lbl_804306E8) and dictionaryF.bin (lbl_80430710) */

struct DictF8 { u32 bit; const char* name; };
struct Dict14 { const char* name; u8 pad4[0x10]; };
struct Dict18 { const char* name; const char* a; u8 pad[0x10]; };
struct Dict10 { const char* name; int a; const char* b; int c; };

struct DictMain {
    int* raw;       /* 0x00 */
    DictF8* t0;     /* 0x04 */
    int* cnt1;      /* 0x08 */
    Dict14* t1;     /* 0x0C */
    int* cnt2;      /* 0x10 */
    Dict18* t2;     /* 0x14 */
    int* cnt3;      /* 0x18 */
    Dict10* t3;     /* 0x1C */
    int* cnt4;      /* 0x20 */
    Dict10* t4;     /* 0x24 */
};
struct DictFlags {
    int* cnt1; DictF8* tbl1;
    int* cnt2; DictF8* tbl2;
    int* cnt3; DictF8* tbl3;
    int* cnt4; DictF8* tbl4;
};
extern DictMain lbl_804306E8;
extern DictFlags lbl_80430710;
extern char lbl_80372C90[];

extern "C" u8* fn_8024BC94(void);

/* menu state, lbl_804CC004. Fields from +0x28 up repeat per page, 0x24 bytes apart. */
struct DictState {
    u8 pad0[4];
    int mode;       /* 0x04 */
    int nlines;     /* 0x08 */
    char** lines;   /* 0x0C */
    void** list;    /* 0x10 */
    int listCount;  /* 0x14 */
    s16 page;       /* 0x18 */
    s16 m1A;        /* 0x1A */
    s16 m1C;        /* 0x1C */
    s16 x1E;        /* 0x1E */
    s16 y20;        /* 0x20 */
    s16 x22;        /* 0x22 */
    s16 y24;        /* 0x24 */
    s16 t26;        /* 0x26 */
    s16 cur;        /* 0x28 */
    s16 m2A;        /* 0x2A */
    s16 m2C;        /* 0x2C */
    s16 m2E;        /* 0x2E */
    s16 m30;        /* 0x30 */
    s16 m32;        /* 0x32 */
    s16 m34;        /* 0x34 */
    s16 m36;        /* 0x36 */
    f32 f38;        /* 0x38 */
    f32 f3C;        /* 0x3C */
    f32 f40;        /* 0x40 */
    int m44;        /* 0x44 */
    int m48;        /* 0x48 */
    u8 pad4C[0x74 - 0x4C];
    void* m74;      /* 0x74 */
    void* m78;      /* 0x78 */
    void* m7C;      /* 0x7C */
};
struct DictState2 {
    u8 pad0[0x20];
    u8 m20[4];      /* 0x20 */
    u8 m24[4];      /* 0x24 */
    u8 pad28[2];
    s16 m2A, m2C;   /* 0x2A */
    u8 pad2E[0x3C - 0x2E];
    int nlines;     /* 0x3C */
    char** lines;   /* 0x40 */
    s16 m44, m46;   /* 0x44 */
    s16 m48, m4A;
    s16 m4C, m4E, m50, m52;  /* 0x4C */
    f32 f54, f58, f5C, f60, f64, f68;  /* 0x54 */
    u8* m6C;        /* 0x6C */
    u8* m70;        /* 0x70 */
    u8* m74;        /* 0x74 */
    u8 pad78[0x8A - 0x78];
    s16 m8A;        /* 0x8A */
};
struct DictMenu { u8 pad[0x30]; int state; u8* m34; u8* m38; };
extern DictMenu* lbl_804CC000;
extern DictState* lbl_804CC004;
extern DictState2* lbl_804CC008;
/* free and clear, reloading the global each time */
#define FREE_FIELD(g, f) do { if ((g)->f != 0) { fn_80078E24((g)->f); (g)->f = 0; (g)->f = 0; } } while (0)
#define DICT_PAGE(st, i) ((DictState*)((u8*)(st) + (i) * 0x24))
#endif
