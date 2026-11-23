/* Unit record screen: per-frame logic */
#pragma use_lmw_stmw on
#include "game/rN_8025EEF0/calls.h"

extern "C" {

extern char lbl_80373C40[];
u8* fn_80006E1C(void);
void fn_80006EE0(void* m);
void fn_80006F20(void* m);
void fn_80011CBC(void* f, void* m);
void* fn_800F4544(void* u, const char* s);
void* fn_8000BD3C(void* res);
void fn_8027DF68(void);

struct Pair { u8* unit; u8* model; };
struct Rec {
    u8 pad[0x30];
    u8 state;
    u8 pad31;
    u16 t;
    u8 m34;
    u8 pad35[0xF];
    int m44;
    s16 m48;
    s16 pad4A;
    s16 m4C;
    s16 pad4E;
    u16 m50;
    u16 m52;
    s16 a[8];
    u8 pad64[6];
    s16 m6A;
    Pair* list;
    int n;
    u8 pad74[4];
    u8 m78, m79;
};

static inline void fade(s16& a, u32 t, u32 k) {
    if (t > k && a != 0xFF) {
        a += 3;
        if (a > 0xFF) a = 0xFF;
    }
}

static inline void load(Pair* e) {
    u8* m = fn_80006E1C();
    e->model = m;
    *(u8**)(m + 4) = e->unit + 0x28;
    *(void**)(e->model + 0x44) = fn_8000BD3C(fn_800F4544(e->unit, lbl_80373C40 + 0x14));
    *(u32*)e->model |= 0xE021A000;
    fn_80006F20(e->model);
}

void fn_80286B44(Rec* o) {
/*P*/
    Pair* end;
    Pair* e;
    int off;
    int i;
    u32 pr;
/*E*/
    if (o->t < 10000) o->t++;
    pr = lbl_804CB5B8->v48();
    if ((pr & 0x4000) && o->m34 != 0) {
        fn_80083DC4(o, 0);
    }
    switch (o->state) {
    case 0:
        if (o->m48-- <= 0) o->state = 1;
        break;
    case 1:
        end = o->list + o->n;
        i = 0;
        e = o->list;
        for (; e != end; i++, e++) {
            off = (u16)i * 0x50;
            if ((u16)(off + o->m44 + 0x50) == 0x1FE) {
                load(e);
            }
            if ((u16)(off + o->m44 + 0x50) == 0) {
                if (e->model != 0) fn_80011CBC(fn_80006EE0, e->model);
                e->model = 0;
            }
        }
        { int k = 3 - o->m78; if (o->m44 < (k + 1) * 0x50) o->state = 2; }
        break;
    case 2:
        if (o->m52 != 0) o->m52 -= 2;
        if (o->m50 > 0x60) {
            o->m50--;
        } else {
            if (o->m6A == 10) {
                o->state = 3;
                o->t = 0;
                o->m79 = o->m78 - 5;
            }
            o->m6A++;
        }
        break;
    case 3:
        if (o->t > 0x226) {
            if (o->m79 == o->m78 - 1) {
                o->state = 4;
                o->m44 = 0;
                o->t = 0;
            }
            for (i = 1; i < 8; i++) {
                s16* q = &o->a[(u8)i];
                if (*q != 0) {
                    *q -= 2;
                    if (*q < 0) *q = 0;
                }
            }
            if (o->a[1] == 0 && o->t > 0x2CB) {
                fn_8027DF68();
                o->t = 0;
                o->m79++;
            }
        } else {
            if (o->t == 10) o->m44 = 0x28;
            fade(o->a[1], o->t, 10);
            fade(o->a[2], o->t, 10);
            fade(o->a[3], o->t, 10);
            fade(o->a[4], o->t, 10);
            fade(o->a[5], o->t, 10);
            fade(o->a[6], o->t, 10);
            fade(o->a[7], o->t, 0xAA);
        }
        break;
    case 4:
        if (pr & 0xFFF0) o->state = 5;
        break;
    case 5:
        if (o->m4C-- <= 0) fn_80083B78(o);
        break;
    }
}

}
