#ifndef RK_800CF8BC_TYPES_H
#define RK_800CF8BC_TYPES_H

#include "game/rH_80112B48/types.h"

/* Controller object at lbl_804CB5B8. Virtuals are named after their vtable
 * offset; layout copied from rJ_800799AC/pad.h. */
class Pad {
public:
    virtual int v08(int);
    virtual int v0C(int);
    virtual int v10();
    virtual int v14();
    virtual int v18();
    virtual int v1C();
    virtual int v20();
    virtual int v24();
    virtual int v28();
    virtual int v2C();
    virtual int v30();
    virtual int v34();
    virtual int v38();
    virtual int v3C();
    virtual int v40();
    virtual int v44();
    virtual int v48();
    virtual int v4C();
    virtual int v50();
    virtual int v54();
    virtual int v58();
    virtual int v5C();
};
extern Pad* lbl_804CB5B8;

/* One tile entry of a target list (0x24 bytes), see fn_800CF8BC.cpp. */
struct TileEntry {
    s8 x;       /* 0x00, -1 terminates */
    s8 y;       /* 0x01 */
    u8 unit;    /* 0x02, 1-based unit id */
    u8 pad3;
    void* p4;   /* 0x04 */
    void* p8;   /* 0x08 */
    void* pC;   /* 0x0C */
    void* p10;  /* 0x10 */
    TileEntry* left;  /* 0x14 */
    TileEntry* right; /* 0x18 */
    u8 pad1C[8];
};

struct TileList {
    int n;      /* 0x00 */
    int cur;    /* 0x04 */
    TileEntry e[128]; /* 0x08 */
};

struct MapSelProc;

/* Target-select menu object at MapSelProc +0x30. The vptr sits at +4 because the
 * counter comes from a plain base. */
struct MenuB {
    int count; /* 0x00 frames with a target under the cursor */
};
class Menu : public MenuB {
public:
    virtual int v08(MapSelProc*);
    virtual int v0C(MapSelProc*);
    virtual int v10(MapSelProc*);
    virtual int v14(MapSelProc*);
    virtual int v18(MapSelProc*);
    virtual void v1C(MapSelProc*);
    virtual void v20(MapSelProc*);
    virtual void v24(MapSelProc*);
    virtual void v28(MapSelProc*);
    virtual int v2C(MapSelProc*);
    virtual const char* v30();
};

/* Process running a target-select map cursor. */
struct MapSelProc {
    u8 proc[0x30];
    Menu* menu;      /* 0x30 */
    f32 fx;          /* 0x34 */
    f32 fy;          /* 0x38 */
    s8 px;           /* 0x3C */
    s8 py;           /* 0x3D */
    s8 x;            /* 0x3E */
    s8 y;            /* 0x3F */
    TileEntry* e40;  /* 0x40 under the cursor */
    TileEntry* e44;  /* 0x44 last one under the cursor */
};

#endif
