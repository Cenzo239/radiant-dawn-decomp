#ifndef RC_8004BE18_TYPES_H
#define RC_8004BE18_TYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;

/* Item data (static item definition). Only fields seen so far. */
typedef struct ItemData {
    u32 flags0;     /* 0x00 */
    u32 flags4;     /* 0x04 */
    u8 pad8[0x12 - 0x8];
    u8 type;        /* 0x12 */
    u8 pad13[0x1c - 0x13];
    u8 id1c;        /* 0x1C */
} ItemData;

/* Item instance in a unit's inventory (size 0x28). */
typedef struct ItemSlot {
    ItemData* data; /* 0x00 */
    u8 uses;        /* 0x04 */
    u8 f7 : 1;      /* 0x05 bit 0x80 */
    u8 f6 : 1;
    u8 f5 : 1;
    u8 f4 : 1;      /* 0x10 */
    u8 f3 : 1;
    u8 f2 : 1;      /* 0x04 */
    u8 f1 : 1;
    u8 f0 : 1;      /* 0x01 */
    u8 pad6[0x28 - 0x6];
} ItemSlot;

typedef struct UnitSub {
    u8 pad0[8];
    u8 b8;          /* 0x08 */
} UnitSub;

/* Unit; inventory of 7 slots at 0x1BC. */
typedef struct Unit {
    u8 pad0[0xf4];
    struct UnitSub* f4; /* 0xF4 */
    void* f8;       /* 0xF8 */
    u8 padfc[0x102 - 0xfc];
    s8 x102;        /* 0x102 */
    s8 y103;        /* 0x103 */
    u8 pad104[0x10c - 0x104];
    u32 flags10c;   /* 0x10C */
    u8 pad110[0x12c - 0x110];
    u8 x12c[0x1bc - 0x12c]; /* 0x12C */
    ItemSlot items[7]; /* 0x1BC */
} Unit;

/* Menu entry passed as third argument to the menu callbacks. */
typedef struct MenuEntry {
    u8 pad0[0x30];
    s16 x;          /* 0x30 */
    s16 y;          /* 0x32 */
    u8 pad34[0x39 - 0x34];
    u8 active;      /* 0x39 */
    u8 index;       /* 0x3A */
} MenuEntry;

#define VPAD(n) virtual void _vpad##n();

typedef struct ItemRef {
    ItemData* data;
    u8 b4;
    u8 b5;
} ItemRef;

/* First argument of the menu-command callbacks (vptr at 0). */
class MenuCmd {
public:
    VPAD(0) VPAD(1) VPAD(2) VPAD(3) VPAD(4) VPAD(5) VPAD(6) VPAD(7)
    VPAD(8) VPAD(9) VPAD(10) VPAD(11) VPAD(12) VPAD(13) VPAD(14) VPAD(15)
    VPAD(16) VPAD(17)
    virtual void v50();                      /* 0x50 */
    VPAD(19)
    virtual ItemRef* v58(void* key);         /* 0x58 */
    virtual ItemRef* v5c(struct MenuEntry* e); /* 0x5C */
};

/* Object at Menu+0x3C (vptr at 4). */
class MenuOwner {
public:
    u32 f0;                                  /* 0x00 */
    VPAD(0) VPAD(1) VPAD(2) VPAD(3) VPAD(4) VPAD(5) VPAD(6) VPAD(7)
    VPAD(8) VPAD(9) VPAD(10) VPAD(11) VPAD(12) VPAD(13) VPAD(14) VPAD(15)
    VPAD(16) VPAD(17)
    virtual s16 v50();                       /* 0x50 */
    virtual s16 v54();                       /* 0x54 */
    VPAD(20) VPAD(21)
    virtual s16 v60();                       /* 0x60 */
    virtual s16 v64();                       /* 0x64 */
    Unit* unit;                              /* 0x08 */
};

/* Object at Menu+0x18 */
typedef struct CursorRef {
    void* w0;
    u8 b4;
    u8 b5;
    s8 x;
    s8 y;
} CursorRef;

typedef struct MenuProc {
    u8 pad0[0x18];
    struct MenuProc* f18; /* 0x18 */
    u8 pad1c[0x30 - 0x1c];
    CursorRef* cursor;    /* 0x30 */
    CursorRef saved;      /* 0x34 */
    u8 pad3c[0xa6 - 0x3c];
    u8 a6;          /* 0xA6 */
} MenuProc;

typedef struct Menu {
    u8 pad0[0x18];
    MenuProc* proc; /* 0x18 */
    u8 pad1c[0x3c - 0x1c];
    MenuOwner* owner; /* 0x3C */
} Menu;

typedef struct Pos8 {
    u8 x;
    u8 y;
} Pos8;

/* Main battle-map unit-command state (lbl_803CA870, size 0x130). */
typedef struct UnitCmdState {
    Unit* unit;     /* 0x00 active unit */
    Unit* unit2;    /* 0x04 */
    u8 pad8[0xc - 0x8];
    u8 b0c;         /* 0x0C */
    u8 padd;
    s8 itemIdx;     /* 0x0E */
    u8 padf[0x11 - 0xf];
    s8 x11;         /* 0x11 */
    s8 y12;         /* 0x12 */
    struct Pos8 pos13; /* 0x13 */
    u8 pad15;
    s8 b16;         /* 0x16 */
    u8 pad17;
    int i18;        /* 0x18 */
    u8 pad1c[0x28 - 0x1c];
    u8 b28;         /* 0x28 */
    u8 pad29[0x130 - 0x29];
} UnitCmdState;

extern UnitCmdState lbl_803CA870;

extern "C" ItemData* fn_801116B8(ItemSlot* slot);
extern "C" ItemSlot* fn_80044FD0(UnitCmdState* st);
extern "C" void fn_800453B4(UnitCmdState* st, int arg);
extern "C" void* fn_800D5448(void* proc, void* parent, int arg);
extern "C" const char* fn_800D0864(const char* key);
extern "C" void fn_801A23E0(int x, int y, const char* str, Menu* m);
extern "C" void fn_80253EE4(const char* name, f32 vol);

static inline u32 dataFlagA(ItemSlot* s) { return fn_801116B8(s)->flags0 & 0x01000000; }
static inline u32 dataFlagB(ItemSlot* s) { return fn_801116B8(s)->flags0 & 0x20000; }
static inline bool slotF2(ItemSlot* s) { return s->f2; }
static inline bool slotF4(ItemSlot* s) { return s->f4; }
static inline bool slotF7(ItemSlot* s) { return s->f7; }
static inline bool isUnusableA(ItemSlot* s) { return dataFlagA(s) || slotF2(s); }
static inline bool isUnusableB(ItemSlot* s) { return dataFlagB(s) || slotF4(s); }

#endif
