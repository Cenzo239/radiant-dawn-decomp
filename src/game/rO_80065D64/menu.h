#ifndef RO_MENU_H
#define RO_MENU_H
#include "game/rO_80065D64/trap.h"

/* Menu classes. Offsets of virtual slots are the names. MenuBase has its vptr at +4. */
struct MB0 { s16 h0; s16 h2; };
class ItemObj;
struct WinItem;
struct Widget;
class MenuBase : public MB0 {
public:
    virtual char* v08();
    virtual int v0C();
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
    virtual int v60();
    virtual int v64();
    virtual int v68();
    virtual int v6C();
    virtual f32 v70();
    virtual int v74();
    virtual int v78();
    virtual int v7C();
    virtual int v80();
    virtual int v84();
    virtual void* v88();
    virtual int v8C();
    virtual int v90();
    virtual char* v94();
    virtual int v98();
    s16 cols; /* 8 */
    s16 rows; /* A */
    s16 sC;   /* C */
    s16 sE;   /* E */
    s16 lines[8]; /* 10 */
};

class ItemObj {
public:
    virtual void v08();
    virtual char* v0C();
    virtual void* v10();
    virtual void v14();
    virtual char* v18(Widget*);
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44(Widget*, Widget*);
    virtual void v48(Widget*, Widget*);
    virtual void* v4C(Widget*);
};

struct Widget {
    u8 pad0[0x18];
    Widget* parent;   /* 18 */
    u8 pad1C[0x2D - 0x1C];
    u8 b2D;           /* 2D */
    u8 b2E;           /* 2E */
    u8 pad2F;
    s16 x;            /* 30 */
    s16 y;            /* 32 */
    union { struct { s16 w; s16 h; }; ItemObj* obj; }; /* 34 */
    union { s16 s38; struct { u8 b38; u8 b39; }; }; /* 38 */
    union { s16 s3A; struct { u8 b3A; u8 b3B; }; }; /* 3A */
    MenuBase* menu;   /* 3C */
    u8 ids[0x64];     /* 40 */
    s8 n;             /* A4 */
    u8 padA5;
    u8 cur;           /* A6 */
    u8 prev;          /* A7 */
};
#endif
