// Round 8 near miss: 16 of 326 words. See NOTES_round8_a.md.
#pragma auto_inline off
extern "C" {
#include "game/rI_801DD7D4/fn_shop.h"
void* memcpy(void*, const void*, u32);
void* fn_80081194(void*, void*);
void fn_80204A08(void*, void*);
void fn_802044F4(void*, void*);
void fn_80205594(void*, int);
int fn_80111094(void*);
void* fn_801116B8(void*);
void fn_80110D38(void*);
void fn_8012A850(void*);
void fn_80102C6C(void*, void*, int, int, int);
extern u8 lbl_8038E4C0[];
extern u8 lbl_804CA9B8[8];
class VQ { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(void*, void*); };
struct Sl { int size; LS* prev; LS* next; };
struct PF { u8 p[0x68]; s16 cur[8]; u8 p78[0x10]; Sl l[8]; };
struct EC { u8 c; EC() { c = 0; } };
struct Msgs2 { int x0; int x4; int x8; int xc; u8 p[0x18]; const char* x28; };
#define HELPS(o, fld) {     const char* s = o->x48->fld;     W* p = fn_801E5640(o, -0x1000, 0);     if (p != NULL) {         p->x64 = s;     } }
struct Sf { u8 p[0x40]; PF* x40; u8 p44[4]; Msgs2* x48; };
struct It2 { u8 p[5]; u8 f7 : 1; u8 rest : 7; };
ATS(atC, 0x88, 0x68)
#pragma use_lmw_stmw on
static inline void clamp(int j, Sl* l, s16* c) {
    for (j = 0; j < 8; l++, c++, j++) {
        if (*c >= (u32)l->size) *c = l->size - 1;
    }
}
void fn_802038BC(Sf* o) {
    /*P*/
    PF* w;
    int j;
    u8* u;
    int a;
    int i;
    int* p;
    Sl* l;
    It2* it;
    int i2;
    const char* h;
/*E*/
    u8 buf[0x10];
    switch (lbl_803CA870[0xc]) {
    case 0x81: {
        void** s;
        w = o->x40;
        s = atC((VL*)w, ((VL*)w)->v34());
        it = (It2*)s[0];
        u = (u8*)s[1];
        a = fn_80111094(it);
        { int m = fn_800626E0(lbl_803CAB38); fn_800615DC(lbl_803CAB38, m + a); }
        if (it->f7 && (*(int*)fn_801116B8(it) & 0x100) && (*(u32*)(u + 0x10c) & 0x800000)) {
            it->f7 = 0;
            ((u8**)lbl_803CA870)[1] = u;
            fn_80081194(lbl_8038E4C0, o);
        }
        fn_80110D38(it);
        if (u != NULL) {
            fn_8012A850(u);
            memcpy(buf, w->cur, 0x10);
            fn_80204A08(w, u);
            p = (int*)(u + 0x1bc);
            for (i = 0; i < 7; i++, p += 10) {
                if (p == NULL || *p == 0) break;
                ((VQ*)w)->v4C(p, u);
            }
            memcpy(w->cur, buf, 0x10);
            clamp(0, w->l, w->cur);
            fn_80102C6C(u, lbl_804CA9B8, 2, 0, 0);
        } else {
            l = w->l;
            for (j = 0; j < 8; l++, j++) {
                LS* f = findIf(l->next, (LS*)&l->prev, B2((Item*)it));
                if (f != (LS*)&l->prev) {
                    f->prev->next = f->next;
                    f->next->prev = f->prev;
                    fn_80079210(f);
                    {
                        u32 sz = --l->size;
                        s16& c = w->cur[j];
                        if (c >= sz) c = sz - 1;
                    }
                    break;
                }
            }
        }
        i2 = 0;
        while (1) { EC e; fn_802044F4((u8*)w + i2 * 0xc + 0x88, &e); if (++i2 == 8) break; }
        {
            int q = ((VL*)w)->v34();
            fn_80205594(w, w->cur[q]);
        }
        fn_8014C2AC(o->x48->x8);
        HELPS(o, x28);
        fn_80083DC4(o, 5);
        break;
    }
    case 0x80:
        fn_8014C2AC(o->x48->xc);
        HELPS(o, x28);
        fn_80083DC4(o, 5);
        break;
    }
}
#pragma use_lmw_stmw off
}
