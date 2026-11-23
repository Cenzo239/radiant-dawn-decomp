#include "game/rC2_8005259C/base.h"
/* Picks spawn points for the event table: fills two lists, then writes map marks. */
struct Ev { s8 x, y; u8 kind; u8 p3; u8 p4; u8 id; u8 flag; u8 p7; };
struct EvList { Ev* e[0x20]; int n; };
struct Mk { s8 x, y; u8 k; u8 p3; int a; int b; int c; };
extern "C" {
extern u8 lbl_803CAB38[];
extern u8 lbl_803CB770[];
extern u8 lbl_803E7320[];
void* fn_80079150(int);
void fn_80079210(void*);
int fn_800660E8(void*);
int fn_80067128(Ev*, s16);
int fn_80089D68(u8);
int fn_800670FC(Ev*);
int fn_80089CF4(int, int);
Mk* fn_800CFBFC(void*);
f32 fn_80176A4C(f32, f32, f32, f32);
}
static inline EvList* newList() {
    EvList* l = (EvList*)fn_80079150(0x84);
    if (l) l->n = 0;
    return l;
}
extern "C" {
#pragma use_lmw_stmw off
void fn_8005474C(void) {
    /*P*/
    int v;
    Ev* best;
    EvList* a;
    EvList* b;
    int fl;
    Ev** q;
    int k;
    int n;
    Ev* e;
    int x;
    int y;
    int z;
    /*E*/
    if (lbl_803CAB38[0x11] != 0) return;
    a = newList();
    b = newList();
    for (n = 0; n < fn_800660E8(lbl_803CB770); n++) {
        e = &(*(Ev**)lbl_803CB770)[n];
        if (e->kind == 0xE) {
            if (e->flag == 0) {
                if (b->n < 0x20) {
                    b->e[b->n++] = e;
                }
            } else if (fn_80067128(e, *(s16*)(lbl_803CAB38 + 0x12)) != 0 && fn_80089D68(e->id) != 0 && fn_800670FC(e) != 0) {
                if (a->n < 0x20) {
                    a->e[a->n++] = e;
                }
            }
        }
    }
    if (a->n > 0) {
        if (b->n == 0) {
            best = 0;
        } else {
            best = b->e[fn_80089CF4(0, b->n)];
        }
        if (best) {
            Mk* m = fn_800CFBFC(lbl_803E7320);
            u8 yy = *(u8*)&best->y;
            u8 xx = *(u8*)&best->x;
            m->x = xx;
            m->y = yy;
            m->k = 0;
            m->a = 4;
        }
        q = a->e;
        for (k = 0; k < a->n; q++, k++) {
            z = 0;
            Ev* c = *q;
            x = c->x;
            y = c->y;
            fl = c->flag;
            v = fn_800670FC(c);
            if (best) {
                z = fn_80176A4C(best->x, best->y, x, y);
            }
            Mk* m = fn_800CFBFC(lbl_803E7320);
            m->x = x;
            m->y = y;
            m->k = v;
            m->a = 4;
            m->b = -fl;
            m->c = z;
        }
    }
    fn_80079210(a);
    fn_80079210(b);
}
}
