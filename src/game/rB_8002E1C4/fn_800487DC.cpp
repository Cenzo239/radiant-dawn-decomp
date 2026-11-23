/* The five staff/command action starters (fn_800487DC, fn_80048A98, fn_80048D54, fn_80048FF8,
   fn_800492B8): one body with different action codes, prepare call and callback. Each body is a
   static inline taking the action proc; the cell copy is the cp() inline. */
#include "game/rT_80026898/types.h"
/* Staff action starters: one body, five action codes. */
#pragma use_lmw_stmw on
extern "C" {
void fn_800CFB34(void*);
void fn_800CFC50(void*, int, int, int, u32);
Cell* fn_800CFCB4(void*, int, int);
void fn_8003B0F4(Unit*);
void fn_8003B148(Unit*);
void fn_8003B19C(Unit*);
void fn_8003B1F0(Unit*);
void fn_8003B244(Unit*);
void fn_80026C44(void*, Unit*, Unit*);
void fn_80026CD8(void*, Unit*, int);
void fn_8002C170(void*);
void fn_80048770(void*);
void fn_800E8048(void*, void (*)(void*));
void fn_80048A2C(void*);
void fn_800E8098(void*, void (*)(void*));
void fn_80048CE8(void*);
void fn_800E80E8(void*, void (*)(void*));
void fn_80048F8C(void*);
void fn_800E8138(void*, void (*)(void*));
void fn_8004924C(void*);
void fn_800E7260(void*, void (*)(void*));
/* Copy of a cell's position, flags and data (orig: reads a, d, c, b; stores a, b, c, d). */
static inline void cp(Cell* e, Cell* o) {
    s8 oa;
    s8 ob;
    u8 oc;
    u32 od;

    oa = o->a;
    od = o->d;
    oc = o->c;
    ob = o->b;

    e->a = oa;
    e->b = ob;
    e->c = oc;
    e->d = od;
}
static inline void run0(Act* q) {
    Cell* e;
    Cell* e2;
    s8 y;
    Cell buf[3];
    Cell* c;
    s8 x;
    s8 cy;
    s8 cx;

    cx = q->cx;
    cy = q->cy;
    x = q->x;
    y = q->y;
    switch (lbl_803CA870.action) {
    case 0x12:
        fn_800CFB34(lbl_803E7320);
        fn_800CFC50(lbl_803E7320, x, y, q->u2->fc, 0);
        fn_80026C44(lbl_803C8E80, q->u1, q->u2);
        break;
    case 0x40:
        fn_8003B0F4(q->u1);
        c = fn_800CFCB4(lbl_803E7320, x, y);
        cp(&buf[0], c);
e = buf; e++; c = fn_800CFCB4(lbl_803E7320, (s8)(cx * 2 - x), (s8)(cy * 2 - y));
        if (c) {
            cp(e, c);
            e++;
        }
        e->a = -1;
        fn_800CFB34(lbl_803E7320);
        for (e2 = buf; e2->a >= 0; e2++) {
            fn_800CFC50(lbl_803E7320, e2->a, (s8)*(u8*)&e2->b, e2->c, e2->d);
        }
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    case 0x2c:
        fn_8003B0F4(q->u1);
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    }
}
void fn_800487DC(Act* q, void* proc) {
    run0(q);
    fn_8002C170(lbl_803C8E80);
    fn_800E8048(proc, fn_80048770);
}
static inline void run1(Act* q) {
    Cell* e;
    Cell* e2;
    s8 y;
    Cell buf[3];
    Cell* c;
    s8 x;
    s8 cy;
    s8 cx;

    cx = q->cx;
    cy = q->cy;
    x = q->x;
    y = q->y;
    switch (lbl_803CA870.action) {
    case 0x42:
        fn_800CFB34(lbl_803E7320);
        fn_800CFC50(lbl_803E7320, x, y, q->u2->fc, 0);
        fn_80026C44(lbl_803C8E80, q->u1, q->u2);
        break;
    case 0x43:
        fn_8003B148(q->u1);
        c = fn_800CFCB4(lbl_803E7320, x, y);
        cp(&buf[0], c);
e = buf; e++; c = fn_800CFCB4(lbl_803E7320, (s8)(cx * 2 - x), (s8)(cy * 2 - y));
        if (c) {
            cp(e, c);
            e++;
        }
        e->a = -1;
        fn_800CFB34(lbl_803E7320);
        for (e2 = buf; e2->a >= 0; e2++) {
            fn_800CFC50(lbl_803E7320, e2->a, (s8)*(u8*)&e2->b, e2->c, e2->d);
        }
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    case 0x44:
        fn_8003B148(q->u1);
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    }
}
void fn_80048A98(Act* q, void* proc) {
    run1(q);
    fn_8002C170(lbl_803C8E80);
    fn_800E8098(proc, fn_80048A2C);
}
static inline void run2(Act* q) {
    Cell* e;
    Cell* e2;
    s8 y;
    Cell buf[3];
    Cell* c;
    s8 x;
    s8 cy;
    s8 cx;

    cx = q->cx;
    cy = q->cy;
    x = q->x;
    y = q->y;
    switch (lbl_803CA870.action) {
    case 0x45:
        fn_800CFB34(lbl_803E7320);
        fn_800CFC50(lbl_803E7320, x, y, q->u2->fc, 0);
        fn_80026C44(lbl_803C8E80, q->u1, q->u2);
        break;
    case 0x46:
        fn_8003B19C(q->u1);
        c = fn_800CFCB4(lbl_803E7320, x, y);
        cp(&buf[0], c);
e = buf; e++; c = fn_800CFCB4(lbl_803E7320, (s8)(cx * 2 - x), (s8)(cy * 2 - y));
        if (c) {
            cp(e, c);
            e++;
        }
        e->a = -1;
        fn_800CFB34(lbl_803E7320);
        for (e2 = buf; e2->a >= 0; e2++) {
            fn_800CFC50(lbl_803E7320, e2->a, (s8)*(u8*)&e2->b, e2->c, e2->d);
        }
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    case 0x47:
        fn_8003B19C(q->u1);
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    }
}
void fn_80048D54(Act* q, void* proc) {
    run2(q);
    fn_8002C170(lbl_803C8E80);
    fn_800E80E8(proc, fn_80048CE8);
}
static inline void run3(Act* q) {
    Cell* e;
    Cell* e2;
    s8 y;
    Cell buf[3];
    Cell* c;
    s8 x;
    s8 cy;
    s8 cx;

    cx = q->cx;
    cy = q->cy;
    x = q->x;
    y = q->y;
    switch (lbl_803CA870.action) {
    case 0x48:
        fn_800CFB34(lbl_803E7320);
        fn_800CFC50(lbl_803E7320, x, y, q->u2->fc, 0);
        fn_80026C44(lbl_803C8E80, q->u1, q->u2);
        break;
    case 0x49:
        fn_8003B1F0(q->u1);
        c = fn_800CFCB4(lbl_803E7320, x, y);
        cp(&buf[0], c);
e = buf; e++; c = fn_800CFCB4(lbl_803E7320, (s8)(cx * 2 - x), (s8)(cy * 2 - y));
        if (c) {
            cp(e, c);
            e++;
        }
        e->a = -1;
        fn_800CFB34(lbl_803E7320);
        for (e2 = buf; e2->a >= 0; e2++) {
            fn_800CFC50(lbl_803E7320, e2->a, (s8)*(u8*)&e2->b, e2->c, e2->d);
        }
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    case 0x4a:
        fn_8003B1F0(q->u1);
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    }
}
void fn_80048FF8(Act* q, void* proc) {
    run3(q);
    fn_8002C170(lbl_803C8E80);
    fn_800E8138(proc, fn_80048F8C);
}
static inline void run4(Act* q) {
    Cell* e;
    Cell* e2;
    s8 y;
    Cell buf[3];
    Cell* c;
    s8 x;
    s8 cy;
    s8 cx;

    cx = q->cx;
    cy = q->cy;
    x = q->x;
    y = q->y;
    switch (lbl_803CA870.action) {
    case 0x4b:
        fn_800CFB34(lbl_803E7320);
        fn_800CFC50(lbl_803E7320, x, y, q->u2->fc, 0);
        fn_80026C44(lbl_803C8E80, q->u1, q->u2);
        break;
    case 0x4c:
        fn_8003B244(q->u1);
        c = fn_800CFCB4(lbl_803E7320, x, y);
        cp(&buf[0], c);
e = buf; e++; c = fn_800CFCB4(lbl_803E7320, (s8)(cx * 2 - x), (s8)(cy * 2 - y));
        if (c) {
            cp(e, c);
            e++;
        }
        e->a = -1;
        fn_800CFB34(lbl_803E7320);
        for (e2 = buf; e2->a >= 0; e2++) {
            fn_800CFC50(lbl_803E7320, e2->a, (s8)*(u8*)&e2->b, e2->c, e2->d);
        }
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    case 0x4d:
        fn_8003B244(q->u1);
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    }
}
void fn_800492B8(Act* q, void* proc) {
    run4(q);
    fn_8002C170(lbl_803C8E80);
    fn_800E7260(proc, fn_8004924C);
}
}
