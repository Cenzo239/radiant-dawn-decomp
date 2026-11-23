#ifndef RK_MENU_H
#define RK_MENU_H
#include "game/rK_800CF8BC/types.h"

struct MenuProc;
struct ItemProc;

/* One entry of a menu. vptr at +0. Slots named by vtable offset. */
class MenuItem {
public:
    virtual int v08();
    virtual int v0C();
    virtual int v10();
    virtual int v14();
    virtual int v18();
    virtual const char* v1C(ItemProc*);
    virtual int v20();
    virtual int v24();
    virtual int v28(MenuItem*, u8);
    virtual void v2C(MenuProc*, ItemProc*);
    virtual u8 v30(MenuProc*, ItemProc*);
    virtual u8 v34(MenuProc*, ItemProc*);
    virtual u8 v38(MenuProc*, ItemProc*);
    virtual void v3C(MenuProc*, ItemProc*);
    virtual u8 v40(MenuProc*, ItemProc*);
    virtual void v44(MenuProc*, ItemProc*);
    virtual void v48(MenuProc*, ItemProc*);
    virtual const char* v4C(ItemProc*);
};

struct MenuDefB {
    int x0;
};

/* A menu definition. vptr at +4. */
class MenuDef : public MenuDefB {
public:
    virtual void v08();
    virtual int v0C();
    virtual void v10();
    virtual void v14(MenuProc*);
    virtual void v18(MenuProc*);
    virtual void v1C(MenuProc*);
    virtual u8 v20(MenuProc*, ItemProc*);
    virtual u8 v24(MenuProc*, ItemProc*);
    virtual u8 v28(MenuProc*, ItemProc*);
    virtual u8 v2C(MenuProc*, ItemProc*);
    virtual void v30(MenuProc*);
    virtual void v34(MenuProc*);
    virtual void v38(MenuProc*);
    virtual void v3C(MenuProc*);
    virtual u8 v40(MenuProc*);
    virtual MenuItem* v44(int);
    virtual int v48();
    virtual int v4C();
    virtual int v50();
    virtual int v54();
    virtual int v58();
    virtual int v5C();
    virtual int v60();
    virtual int v64();
    virtual int v68();
    virtual int v6C();
    virtual f32 v70();
    virtual const char* v74();
    virtual const char* v78();
    virtual const char* v7C();
    virtual const char* v80();
    virtual const char* v84();
    virtual const char* v88();
    virtual int v8C(MenuProc*);
};

struct ItemProc {
    u8 proc[0x30];
    s16 x;       /* 0x30 */
    s16 y;       /* 0x32 */
    MenuItem* item; /* 0x34 */
    s8 sel;      /* 0x38 */
    u8 state;    /* 0x39 */
    u8 idx;      /* 0x3A */
    u8 vis;      /* 0x3B */
    int o3C;     /* 0x3C */
};

struct MenuProc {
    u8 proc0[0x18];
    MenuProc* parent; /* 0x18 */
    u8 pad1C[0xC];
    s16 sleep;   /* 0x28 */
    u8 mark;     /* 0x2A */
    u8 layer;    /* 0x2B */
    u8 flags;    /* 0x2C */
    u8 lockCnt;  /* 0x2D */
    u8 pause;    /* 0x2E */
    u8 pad2F;
    s16 x;       /* 0x30 */
    s16 y;       /* 0x32 */
    s16 w;       /* 0x34 */
    s16 h;       /* 0x36 */
    s16 a38;     /* 0x38 */
    s16 curY;    /* 0x3A */
    MenuDef* def; /* 0x3C */
    u8 items[0x64]; /* 0x40 */
    s8 n;        /* 0xA4 */
    u8 state;    /* 0xA5 */
    s8 cur;      /* 0xA6 */
    s8 prev;     /* 0xA7 */
    u8 vis;      /* 0xA8 */
};

#endif
