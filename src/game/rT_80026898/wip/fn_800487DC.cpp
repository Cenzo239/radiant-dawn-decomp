#include "game/rT_80026898/types.h"
/* Staff action starters: one body, five action codes. */
#pragma use_lmw_stmw on
extern "C" {
void fn_800CFB34(void*);
void fn_800CFC50(void*, int, int, int, u32);
Cell* fn_800CFCB4(void*, int, int);
void fn_8003B0F4(Unit*);
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
void fn_800487DC(Act* q, void* proc) {
    Cell buf[3];
    s8 cx;
    s8 cy;
    s8 x;
    s8 y;
    Cell* c;
    Cell* e;
    Cell* e2;
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
{ u32 od; u8 oc; s8 ob; s8 oa; od = c->d; oc = c->c; ob = c->b; oa = c->a; buf[0].b = ob; buf[0].a = oa; buf[0].c = oc; buf[0].d = od; }
        e = &buf[1];
        c = fn_800CFCB4(lbl_803E7320, (s8)(cx * 2 - x), (s8)(cy * 2 - y));
        if (c) {
{ u32 od; u8 oc; s8 ob; s8 oa; od = c->d; oc = c->c; ob = c->b; oa = c->a; (*e).b = ob; (*e).a = oa; (*e).c = oc; (*e).d = od; }
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
    fn_8002C170(lbl_803C8E80);
    fn_800E8048(proc, fn_80048770);
}
}
