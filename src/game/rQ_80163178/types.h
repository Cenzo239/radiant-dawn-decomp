#ifndef RQ_TYPES_H
#define RQ_TYPES_H
/* Shared layouts for the AI action search region; Unit and Map are copied from rM_8014C9F8/ai.h and rH_80112B48. */
#include "game/rQ_80163178/base.h"

struct Person;
struct Job;
struct Inv {
    u8* item;     /* 0x00 */
    u8 uses;      /* 0x04 */
    u8 pad5[0x28 - 5];
};

struct Unit {
    u8 pad0[0xE4];
    Unit* prev;     /* 0xE4 */
    Unit* next;     /* 0xE8 */
    Person* person; /* 0xEC */
    Job* job;       /* 0xF0 */
    u8* team;       /* 0xF4 */
    u8* actor;      /* 0xF8 */
    u8 tid;         /* 0xFC */
    u8 padFD[5];
    s8 x;           /* 0x102 */
    s8 y;           /* 0x103 */
    u8 pad104[4];
    union {
        u64 flags;      /* 0x108 */
        struct {
            u32 flags108;
            u32 flags10C;
        };
    };
    u8 pad110[4];
    s8 hp;          /* 0x114 */
    u8 pad115[2];
    u8 b117;        /* 0x117 */
    u8 pad118[0x12C - 0x118];
    u8 skills[0x90]; /* 0x12C */
    Inv inv[7];     /* 0x1BC */
    u8 pad2D4[0x390 - 0x2D4];
    u8 ai[0x10];    /* 0x390 */
    u32 w3A0;       /* 0x3A0 */
    u8 pad3A4[0x10];
    u32 w3B4;       /* 0x3B4 */
    u8 pad3B8[4];
    u8 b3BC;        /* 0x3BC */
    u8 pad3BD;
    s16 h3BE;       /* 0x3BE */
    int w3C0;       /* 0x3C0 */
    u8 pad3C4[0xC];
    u8 m3D0[0x20];  /* 0x3D0 */
};

/* lbl_803CA870: the action the AI will take. */
struct AiAct {
    Unit* unit;  /* 0x00 */
    Unit* unit2; /* 0x04 */
    u8 pad8[4];
    u8 action;   /* 0x0C */
    u8 padD[2];
    s8 x0;       /* 0x0F */
    s8 y0;       /* 0x10 */
    s8 x;        /* 0x11 */
    s8 y;        /* 0x12 */
    s8 x2;       /* 0x13 */
    s8 y2;       /* 0x14 */
    u8 pad15;
    u8 b16;      /* 0x16 */
    u8 pad17[0x130 - 0x17];
};

/* lbl_804183F0: AI state. */
struct AiCfg {
    u8 b0;       /* 0x00 */
    u8 b1;       /* 0x01 */
    u8 flags;    /* 0x02 */
    u8 pad3[5];
    int op;      /* 0x08 */
    int padC;
    int res[5];  /* 0x10 */
    Unit* order[0x80]; /* 0x24 */
    Unit** cursor; /* 0x224 */
    u8 pad228[4];
    u8 done;     /* 0x22C */
    u8 pad22D[0x250 - 0x22D];
};

/* The battle map, lbl_803EC898; layout from rH_80112B48/map.h. */
struct Map {
    s32 w;
    s32 h;
    s8 x0, y0, x1, y1;     /* 0x00008 */
    u8 padC;
    union {
        u8 ter[5][0x1000]; /* 0x0000D */
    };
    u8 pad500D;
    u16 border[0x40];      /* 0x0500E */
    u16 flags[0x1000];     /* 0x0508E */
    u16 border2[0x40];     /* 0x0708E */
    union {
        u16 cost[0x1000];  /* 0x0710E */
        s16 costS[0x1000];
    };
    u16 border3[0x40];     /* 0x0910E */
    union {
        u16 cost2[0x1000]; /* 0x0918E */
        s16 cost2S[0x1000];
    };
    union {
        u16 g3[0x1000];    /* 0x0B18E */
        s16 g3S[0x1000];
    };
    union {
        u16 g4[0x1000];    /* 0x0D18E */
        s16 g4S[0x1000];
    };
    union {
        u16 g5[0x1000];    /* 0x0F18E */
        u8 b5[0x2000];
        s8 b5S[0x2000];
    };
    u16 g6[0x1000];        /* 0x1118E */
    u16 g7[0x1000];        /* 0x1318E */
    u8 pad1518E[2];
    union {
        u16* cur;          /* 0x15190 */
        s16* curS;
    };
};

extern "C" {
extern Map lbl_803EC898;
extern AiAct lbl_803CA870;
extern AiCfg lbl_804183F0;
}
#endif
