/* NEAR MISS: 5 words. off should be r29 and the hoisted lis of fn_8027E848 r28; only those two swapped. */
/* Scrolling list: row backgrounds and whole screen */
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

void fn_8007E74C(void* f, void* a);
void fn_80080494(void);
void fn_80080508(C4* c);
void fn_8027E834(void*);
void fn_8027E848(void*);
void fn_8027E85C(void*);
void fn_8027E870(void*);
void fn_8027E884(void* e);

struct Rows {
    u8 pad[0x34];
    void* tex;
    u8 pad38[4];
    u16 x;
    s16 y;
    u8 pad40[0xC];
    u8* list;
    int count;
};

static inline void cb(void* f) { if (f != 0) { fn_8007E74C(f, 0); } }

#define TEX1(tt, i, fl) do { tt = p->tex; fn_8007E154(); fn_8007E374(tt, i, fl); fn_8007E7DC(0xFF); fn_8007E164(); } while (0)

void fn_8027ECA4(Rows* p) {
/*P*/
    int off;
    u16 x;
    u8* end;
    void* t1;
    void* t2;
    int ix;
    void* t3;
    u16 y;
    u8* e;
    void* t5;
    void* t4;
/*E*/
    e = p->list;
    end = e + p->count * 8;
    off = 0;
    for (; e != end; e += 8, off += 0x4C) {
        x = p->x;
        y = p->y + off;
        if (y + 0x4C >= 0x18 && y <= 0x1A8) {
            fn_8007E154();
            fn_8007E4E4(x, y, 400.0f, 1.0f);
            fn_8007E164();
            TEX1(t1, 3, 0x11);
            fn_800800D4(1);
            fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 440.0f, 56.0f);
            fn_80080578(0);
            fn_80080308();
            TEX1(t2, 3, 0x11);
            fn_800800D4(1);
            fn_80080430(168.0f, 6.0f, 0.0f, 0.0f, 440.0f, 56.0f);
            fn_80080494();
            fn_80080578(0);
            fn_80080308();
            {
                if (fn_801D09F0() != 0 || (s8)fn_8024BC94()[0x1BC8] == 0) {
                    ix = 0x74;
                } else {
                    ix = 0x7A;
                }
                TEX1(t3, 4, 0x11);
                fn_800800D4(1);
                fn_80080430(ix, 10.0f, 0.0f, 0.0f, 10.0f, 19.0f);
            }
            fn_80080578(0);
            fn_80080308();
            TEX1(t4, 5, 1);
            fn_800800D4(1);
            fn_80080430(283.0f, 37.0f, 0.0f, 0.0f, 48.0f, 13.0f);
            fn_80080578(2);
            fn_80080308();
            TEX1(t5, 6, 1);
            fn_800800D4(1);
            fn_80080430(407.0f, 37.0f, 0.0f, 0.0f, 40.0f, 13.0f);
            fn_80080578(2);
            fn_80080308();
            fn_8007E154();
            fn_8007E4E4(x, y, 350.0f, 1.0f);
            fn_8007E174(0, 0x13);
            fn_8007E74C((void*)fn_8027E848, 0);
            fn_8007E164();
            fn_8027E884(e);
        }
    }
}

}
