/* fn_801F6C54, zero-idiom family, round 20 copy: complete self-contained draft, class `other`.
 * Source: wip/r19zero/fn_801F6C54.cpp (unchanged; same instructions as fn_801F3D28). 264 of 264.
 * Is the mr/li instruction the only difference? YES (apart from register numbers): `mr r26,r29` in the
 * original, `li r23,0` here. Functionally equal.
 */
/* WIP (round 19, zero-idiom family): complete draft for the port, class `other` like its sibling.
   fn_801F6C54 is instruction-for-instruction identical to fn_801F3D28 (same references); this is
   wip/fn_801F3D28.cpp renamed. The `mr rZ,rI` zero idiom is not reproduced. */
#pragma auto_inline off
extern "C" {
void* fn_80081194(void*, void*);
#include "game/rI_801DD7D4/fn_shop.h"
void* memcpy(void*, const void*, u32);
void fn_801FEA10(void*, void*);
void fn_801FDC38(void*, void*);
void fn_801FE76C(void*, int);
void fn_801E5890(void*);
extern u8 lbl_8038D690[];
class VT { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(void*); };
class VQ { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(void*, void*); };
struct Sl { int size; LS* prev; LS* next; };
struct PS { u8 p[0x70]; s16 cur[12]; u8 p88[0x10]; Sl l[12]; };
struct Ent { u8 p[0x1bc]; int e[7][10]; };
struct EC { u8 c; EC() { c = 0; } };
#define G0 (((void**)lbl_803CA870)[0])
#define G1 (((void**)lbl_803CA870)[1])
#pragma use_lmw_stmw on
static inline void clamp(int j, Sl* l, s16* c) {
    for (j = 0; j < 12; l++, c++, j++) {
        if (*c >= (u32)l->size) *c = l->size - 1;
    }
}
static inline void fill(PS* s, u8*& a, int*& p, int& i, u8* b) {
    memcpy(b, s->cur, 0x18);
    fn_801FEA10(s, a);
    p = (int*)(a + 0x1bc);
    for (i = 0; i < 7; i++, p += 10) {
        if (p == NULL || *p == 0) break;
        ((VQ*)s)->v4C(p, a);
    }
    memcpy(s->cur, b, 0x18);
}
static inline void erase(PS* s, Sl* ll, Sl*& l2, int& j, Item* it) {
                l2 = ll;
                for (j = 0; j < 12; l2++, j++) {
                    LS* f = findIf(l2->next, (LS*)&l2->prev, B2(it));
                    if (f != (LS*)&l2->prev) {
                        f->prev->next = f->next;
                        f->next->prev = f->prev;
                        fn_80079210(f);
                        {
                            u32 sz = --l2->size;
                            s16& c = s->cur[j];
                            if (c >= sz) c = sz - 1;
                        }
                        break;
                    }
                }
}
struct Gs { u8* a; u8* b; };
static inline Gs* gp() { return (Gs*)lbl_803CA870; }
static inline Gs& gr() { return *(Gs*)lbl_803CA870; }
void fn_801F6C54(Sc* o) {
    /*P*/
    int* p1;
    u8* a1;
    int* p0;
    int i0;
    u8* a0;
    Sl* l2;
    s16* cc;
    int j;
    PS* s;
    int k;
    Sl* ll;
    int i;
    void* w;
/*E*/
    u8 b0[0x18];
    u8 b1[0x18];
    {
        w = o->x50;
        ((VT*)o->x4c)->v34(((Gs*)lbl_803CA870)->a);
        ((VT*)w)->v34(((Gs*)lbl_803CA870)->b);
    }
    s = (PS*)o->x54;
    a0 = ((Gs*)lbl_803CA870)->a;
    fill(s, a0, p0, i0, b0);
    ll = s->l;
    cc = s->cur;
    clamp(0, ll, cc);
    a1 = ((u8**)lbl_803CA870)[1];
    fill(s, a1, p1, i0, b1);
    clamp(0, ll, cc);
    i = 0;
    while (1) { EC e; fn_801FDC38((u8*)s + i * 0xc + 0x98, &e); if (++i == 12) break; }
    {
        for (k = 0; k < 7; k++) {
            u8* q = (u8*)G0 + k * 0x28;
            Item* it = (Item*)(q + 0x1bc);
            if (*(int*)(q + 0x1bc) != 0) {
                erase(s, ll, l2, j, it);
            }
        }
    }
    {
        int q = ((VL*)s)->v34();
        fn_801FE76C(s, s->cur[q]);
    }
    fn_801E5890(o);
    fn_80081194(lbl_8038D690, o);
    fn_80083B78(o);
}
#pragma use_lmw_stmw off
}
