#ifndef RT_TYPES_H
#define RT_TYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
typedef double f64;
typedef unsigned long long u64;
typedef signed long long s64;

/* One affected map cell in the scratch result block lbl_803E7320 (0x24 bytes). */
typedef struct Cell {
    s8 a;  /* 0x00 x */
    s8 b;  /* 0x01 y */
    u8 c;  /* 0x02 */
    u32 d; /* 0x04 */
    u8 pad8[0x24 - 8];
    Cell() {}
    Cell& operator=(const Cell& o) {
        u32 od = o.d;
        u8 oc = o.c;
        s8 ob = o.b;
        s8 oa = o.a;
        b = ob;
        a = oa;
        c = oc;
        d = od;
        return *this;
    }
} Cell;

/* Battle-action proc data. */
typedef struct Act {
    struct Unit* u1; /* 0x00 */
    struct Unit* u2; /* 0x04 */
    u8 pad8[0xc - 8];
    u8 action; /* 0x0C */
    u8 padD[0x11 - 0xD];
    s8 cx; /* 0x11 */
    s8 cy; /* 0x12 */
    s8 x;  /* 0x13 */
    s8 y;  /* 0x14 */
    u8 pad15[0x18 - 0x15];
    int f18; /* 0x18 */
} Act;

/* lbl_803CA870: the unit command state (see rC_8004BE18/NOTES.md). */
typedef struct CmdState {
    union {
        struct {
            struct Unit* unit;  /* 0x00 */
            struct Unit* unit2; /* 0x04 */
        };
        struct {
            struct Unit* unit;
            struct Unit* unit2;
        } pair;
    };
    u8 pad8[4];
    u8 action; /* 0x0C */
    u8 fd;     /* 0x0D */
    u8 item; /* 0x0E */
    u8 x0;   /* 0x0F */
    u8 y0;   /* 0x10 */
    u8 cx; /* 0x11 */
    u8 cy; /* 0x12 */
    u8 x;  /* 0x13 */
    u8 y;  /* 0x14 */
    u8 f15;  /* 0x15 */
    u8 f16;  /* 0x16 */
    u8 pad17;
    int f18; /* 0x18 */
    u8 pad1c[0x28 - 0x1c];
    u8 f28;  /* 0x28 */
    u8 pad29[0x30 - 0x29];
    char buf30[0x80]; /* 0x30 */
    char bufB0[0x80]; /* 0xB0 */
} CmdState;

/* Item instance in an inventory (0x28 bytes). */
/* lbl_803CAB38: chapter / game state (flag table part as in rC_8004BE18). */
typedef struct GameState {
    u8 pad0[0x11];
    u8 side;  /* 0x11: phase */
    u16 f12;  /* 0x12 */
    u8 sideOn[4]; /* 0x14 */
    u8 pad18[0x9a - 0x18];
    s8 s9a;
    s8 s9b;
    u8 f9c;
    u8 pad9d[0xb0 - 0x9d];
    u32 fb0;
    u32 fb4;
    u16 fb8;
    u16 fba;
    u32 fbc;
    u8 padc0[0x144 - 0xc0];
    char* names[0x80];  /* 0x144 */
    u32 hashes[0x80];   /* 0x344 */
    u8 bits[0x10];      /* 0x544 */
    u8 x554[0x988 - 0x554]; /* 0x554 */
} GameState;

typedef struct Slot {
    u8* data; /* 0x00: d+0x12 type, d+0x16 might */
    u8 uses;  /* 0x04 */
    u8 f80 : 1; /* 0x05 flag bits, MSB first */
    u8 f40 : 1;
    u8 f20 : 1;
    u8 f10 : 1;
    u8 f08 : 1;
    u8 f04 : 1;
    u8 f02 : 1;
    u8 f01 : 1;
    u8 pad6[0x28 - 6];
} Slot;

/* Skill list entry (8 bytes). */
typedef struct SkillEnt {
    u8* d;  /* d+0x1F: cost */
    u8 b4;
    u8 b5;
    u8 pad[2];
} SkillEnt;

typedef struct Hp {
    u16 hi : 6;
    u16 n : 3;
    u16 lo : 7;
} Hp;

typedef struct Unit {
    u8 pad0[0xe8];
    struct Unit* next; /* 0xE8 */
    void* ec; /* 0xEC */
    u8 padf0[0xf4 - 0xf0];
    union { u8* f4; int f4x; }; /* 0xF4 */
    struct Unit* f8; /* 0xF8 */
    u8 fc; /* 0xFC */
    u8 padfd[0x102 - 0xfd];
    s8 x102; /* 0x102 map x */
    s8 y103; /* 0x103 map y */
    u8 pad104[0x108 - 0x104];
    u32 f108; /* 0x108 */
    u32 f10c; /* 0x10C */
    union {
        u8 x110[4]; /* 0x110 */
        Hp h;
    };
    s8 s114;    /* 0x114 */
    u8 pad115[0x12c - 0x115];
    union {
        u8 x12c[0x1bc - 0x12c]; /* 0x12C */
        SkillEnt skills[18];
    };
    Slot items[7]; /* 0x1BC */
    u8 pad2d4[0x37c - 0x2d4];
    s16 f37c; /* 0x37C */
    u8 pad37e[0x386 - 0x37e];
    s16 f386; /* 0x386 */
    u16 f388; /* 0x388 */
    u8 pad38a[0x38f - 0x38a];
    u8 f38f; /* 0x38F */
    u8 pad390[0x3f0 - 0x390];
    struct Unit* u3f0; /* 0x3F0 */
} Unit;

#define SB(f) (*(s8*)&(f))
#define FLAGS(u) (*(u64*)&(u)->f108)

/* An item instance held on the stack (ctor fn_80111B34, dtor fn_80111C24), 0x28 bytes. */
typedef struct Item {
    void* data;
    u8 pad[0x24];
} Item;

extern "C" {
extern CmdState lbl_803CA870;
extern u8 lbl_803C8E80[];
extern u8 lbl_803E7320[];
extern char lbl_803619D0[];
}

#endif
