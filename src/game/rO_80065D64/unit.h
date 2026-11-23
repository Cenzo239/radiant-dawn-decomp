#ifndef RO_UNIT_H
#define RO_UNIT_H
#include "game/rO_80065D64/types.h"

/* Person data (Unit +0xEC). */
struct Person {
    char* name;
    u8 pad4[0x1C - 4];
    u16 id;       /* 0x1C */
    u8 pad1E;
    u8 level1F;   /* 0x1F */
    u8 pad20[2];
    s8 base[8];   /* 0x22: hp str mag skl spd lck def res */
    u8 pad2A[0xE2 - 0x2A];
    u8 e2;        /* 0xE2 */
    u8 padE3[0xE8 - 0xE3];
    s8 e8;        /* 0xE8 */
    s8 e9;        /* 0xE9 */
    s8 ea;        /* 0xEA */
    s8 eb;        /* 0xEB */
};

/* Job data (Unit +0xF0). */
struct Job {
    char* name;
    u8 pad4[0x14 - 4];
    void* p14;      /* 0x14 */
    void* promoted; /* 0x18 */
    u8 pad1C[0xF0 - 0x1C];
    u8 levelF0;   /* 0xF0 */
    u8 padF1;
    u8 f2;        /* 0xF2 */
    u8 padF3;
    u8 f4;        /* 0xF4 */
    u8 f5;        /* 0xF5 */
    u8 padF6;
    u8 f7;        /* 0xF7 */
    u8 padF8[3];
    u8 fb;        /* 0xFB */
    s8 base[8];   /* 0xFC */
    s8 max[8];    /* 0x104 */
};

/* Inventory entry, 0x28 bytes (the seven at Unit +0x1BC). */
struct Inv {
    u8* item;     /* 0x00 */
    u8 uses;      /* 0x04 */
    u8 equipped : 1; /* 0x05 */
    u8 bit40 : 1;
    u8 bit20 : 1;
    u8 bit10 : 1;
    u8 bits2 : 1;
    u8 bit4 : 1;
    u8 bits0 : 2;
    u8 pad6[0x28 - 6];
};

/* A unit: 0x3F0 bytes, in the array at lbl_804CB810. */
struct Unit {
    u8 pad0[0xC7];
    s8 sC7;         /* 0xC7 */
    u8 padC8[0xE4 - 0xC8];
    Unit* prev;     /* 0xE4 */
    Unit* next;     /* 0xE8 */
    Person* person; /* 0xEC */
    Job* job;       /* 0xF0 */
    u8* team;       /* 0xF4 */
    u8* actor;      /* 0xF8: MapUnit */
    u8 padFC;
    u8 fd;          /* 0xFD */
    union { s8 gauge; u8 ugauge; }; /* 0xFE: laguz transform gauge */
    u8 ff;          /* 0xFF */
    u8 u100;        /* 0x100 */
    u8 pad101;
    s8 x;           /* 0x102 */
    s8 y;           /* 0x103 */
    u8 pad104[4];
    union {
        u64 flags;  /* 0x108 */
        struct {
            u32 flags108;
            u32 flags10C;
        };
    };
    union {
        u8 skills110[4];
        struct {
            u16 wtpad : 9;
            u16 wt : 3;
        };
    };
    s8 hp;          /* 0x114 */
    u8 exp115;      /* 0x115 */
    s8 u116;        /* 0x116 */
    u8 u117;        /* 0x117 */
    u8 u118;        /* 0x118 */
    s8 stat[8];     /* 0x119 */
    u8 pad121[0x12C - 0x121];
    u8 skills[0x1BC - 0x12C]; /* 0x12C */
    Inv inv[7];     /* 0x1BC */
    s16 s2D4[0x10]; /* 0x2D4 */
    u8 pad2F4[0x300 - 0x2F4];
    u8 sup[0x48];   /* 0x300 */
    u8 pad348[0x37E - 0x348];
    u16 h37E;       /* 0x37E */
    s8 b380;        /* 0x380 */
    u8 pad381[0x390 - 0x381];
    u8 u390[4];     /* 0x390 */
    void* ptr[4];   /* 0x394 */
    void* p3A4;     /* 0x3A4 */
    u8 b3A8;        /* 0x3A8 */
    void* p3AC;     /* 0x3AC */
    u8 cnt[4];      /* 0x3B0 */
    u32 w3B4;       /* 0x3B4 */
    u16 h3B8;       /* 0x3B8 */
    u8 b3BA;
    u8 b3BB;
    u8 b3BC;
    u8 pad3BD[7];
    u32 w3C4;       /* 0x3C4 */
    u8 b3C8;        /* 0x3C8 */
    u8 pad3C9[7];
    u8 b3D0;        /* 0x3D0 */
    u8 pad3D1[0x3F0 - 0x3D1];
};

extern Unit* lbl_804CB810;

static inline Unit* UnitGet(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

#endif
