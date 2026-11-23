/* Unit slot menu: swap two slots, close the gap in the source group */
#include "game/rN_8025EEF0/calls.h"

extern "C" {

struct Slot {
    void* unit; s16 a; s16 b;
    void clear();
    Slot& operator=(const Slot& o) { unit = o.unit; a = o.a; b = o.b; return *this; }
};
typedef void (Slot::*SlotMF)();
struct SlotFn { SlotMF f; SlotFn() {} SlotFn(SlotMF x) : f(x) {} };
extern SlotMF lbl_80391B24;
extern Slot lbl_80430740[3][20];

struct SlotAnim { u8 pad[0x30]; u8 m30; u8 m31; u8 pad32[0x16]; f32 m48; f32 m4C; f32 m50; };
struct SlotCur { u8 pad[0x3C]; void* unit; };
struct SlotMenu {
    u8 pad[0x40];
    SlotCur* cur;
    SlotAnim* anim;
    u8 pad48;
    u8 m49;
    u8 pad4A[2];
    s16 grp;
    s16 idx;
    s16 grp2;
    s16 idx2;
};

static inline SlotFn each(Slot* a, Slot* e, SlotFn f) {
    while (a != e) {
        (a->*f.f)();
        a++;
    }
    return f;
}

static inline Slot* rem(Slot* a, Slot* e) {
    while (a != e && a->unit != 0) {
        a++;
    }
    if (a != e) {
        Slot* q = a + 1;
        while (q != e) {
            if (*(int*)q != 0) {
                *a = *q;
                a++;
            }
            q++;
        }
    }
    return a;
}

static inline void swap(Slot& a, Slot& b) {
    Slot t = a;
    a = b;
    b = t;
}

void fn_802676A0(SlotMenu* m) {
    Slot* s;
    swap(lbl_80430740[m->grp][m->idx], lbl_80430740[m->grp2][m->idx2]);
    if (lbl_80430740[m->grp2][m->idx2].unit == 0) {
        s = rem(lbl_80430740[m->grp2], lbl_80430740[m->grp2] + 20);
        each(s, lbl_80430740[m->grp2] + 20, SlotFn(lbl_80391B24));
    }
    m->grp = m->grp2;
    m->idx = m->idx2;
    m->m49 = 0;
    {
        SlotAnim* an = m->anim;
        if ((int)an->m31 != 1) {
            an->m48 = 64.0f;
            an->m4C = 0.0f;
            an->m30 = 0;
            an->m50 = 800.0f;
            an->m31 = 1;
            fn_80083DC4(an, 2);
        }
    }
    m->cur->unit = lbl_80430740[m->grp][m->idx].unit;
}

}
