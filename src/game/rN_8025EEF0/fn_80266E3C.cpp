/* Menus around the dictionary: creation, slot tables at lbl_80430740. */
#include "game/rN_8025EEF0/dict.h"

#pragma use_lmw_stmw on

extern "C" {

void* fn_80081194(void* script, void* parent);
void* fn_80078CCC(int size, const char* name, int a);
void* memset(void* p, int v, unsigned n);
f32 fn_8017F68C(f32 a, f32 b, f32 t, f32 d, int mode);
void fn_80083B78(void* p);
void fn_80083DC4(void* p, int label);
int fn_801D09F0(void);
void fn_800068A0(void* p, void* q);
void fn_80006A2C(void* p);
void fn_800C4A58(void* p);
void fn_800C4AA8(void* p);
void fn_80253EE4(void* p, f32 v);
void* fn_80060728(void* p);
void fn_8011FE74(void* unit, int a);

extern u8 lbl_80391970[];
extern void* lbl_80391A10[][2];
extern u8 lbl_80391E28[];
extern u8 lbl_80391E38[];
extern u8 lbl_803CAB38[];
extern u8 lbl_803CA870[];
extern u8 lbl_80391AA8[];
extern u8 lbl_80391AD8[];

struct Slot { void* unit; s16 a; s16 b; };
extern Slot lbl_80430740[3][20];

static inline BOOL dictCreate(void* parent) {
    if (lbl_804CC000 != 0) {
        return 0;
    }
    if ((lbl_804CC000 = (DictMenu*)fn_80081194(lbl_80391970, parent)) == 0) {
        return 0;
    }
    lbl_804CC000->m34 = (u8*)fn_80078CCC(0x80, lbl_80372C90 + 0x26, 0);
    memset(lbl_804CC000->m34, 0, 0x80);
    lbl_804CC000->m38 = (u8*)fn_80078CCC(0x8C, lbl_80372C90 + 0x26, 0);
    memset(lbl_804CC000->m38, 0, 0x8C);
    lbl_804CC004 = (DictState*)lbl_804CC000->m34;
    lbl_804CC008 = (DictState2*)lbl_804CC000->m38;
    return 1;
}

void fn_80266E3C(void* parent) {
    if (dictCreate(parent)) {
        lbl_804CC000->state = 0;
    }
}

void fn_80266F24(void* parent) {
    if (dictCreate(parent)) {
        lbl_804CC000->state = 1;
    }
}

struct FadeProc {
    u8 pad[0x30];
    s8 t;      /* 0x30 */
    u8 pad31[0x48 - 0x31];
    f32 a;     /* 0x48 */
    f32 b;     /* 0x4C */
};

void fn_8026700C(FadeProc* p) {
    p->a = fn_8017F68C(0.0f, 64.0f, p->t, 4.0f, 5);
    p->b = fn_8017F68C(1.0f, 0.0f, p->t, 4.0f, 5);
    if (++p->t > 4) {
        fn_80083B78(p);
    }
}

void fn_802670D0(FadeProc* p) {
    p->a = fn_8017F68C(64.0f, 0.0f, p->t, 4.0f, 5);
    p->b = fn_8017F68C(0.0f, 1.0f, p->t, 4.0f, 5);
    if (++p->t > 4) {
        fn_80083B78(p);
    }
}

struct SndProc { u8 pad[0x34]; u8 a[4]; u8 b[4]; };

void fn_80267194(SndProc* p) {
    int lang = (s8)fn_8024BC94()[0x1BC8];
    fn_800068A0(p->a, lbl_80391A10[lang][fn_801D09F0()]);
    fn_800C4A58(p->b);
}

void fn_802671FC(SndProc* p) {
    if (*(int*)p->a != 0) {
        fn_80006A2C(p->a);
    }
    if (*(int*)p->b != 0) {
        fn_800C4AA8(p->b);
    }
}

void fn_8026724C(void) { fn_80253EE4(lbl_80391E28, 0.0f); }

void fn_8026725C(u8* p) { fn_80083DC4(p, (u8)*(int*)(p + 0x58)); }

struct SlotMenu {
    u8 pad[0x40];
    u8* m40;  /* 0x40 */
    u8* m44;  /* 0x44 */
    u8 pad48[0x4C - 0x48];
    s16 grp;  /* 0x4C */
    s16 idx;  /* 0x4E */
    s16 grp2; /* 0x50 */
    s16 idx2; /* 0x52 */
    s16 m54;  /* 0x54 */
    s16 m56;  /* 0x56 */
    int m58;  /* 0x58 */
};

void fn_80267268(SlotMenu* m) {
    void* want = *(void**)((u8*)fn_80060728(lbl_803CAB38) + 0x28);
    int i;
    int g;
    Slot* row = lbl_80430740[0];
    for (g = 0; g < 3; g++, row += 20) {
        Slot* e = row;
        for (i = 0; i < 20; e++, i++) {
            if (want == e->unit) {
                m->grp = g;
                m->idx = i;
                goto done;
            }
        }
    }
done:
    m->m54 = -0x8000;
    m->m56 = -0x8000;
    switch (m->m58) {
    case 1:
        *(void**)(m->m44 + 0x3C) = lbl_80430740[m->grp][m->idx].unit;
        break;
    default:
        *(void**)(m->m40 + 0x3C) = lbl_80430740[m->grp][m->idx].unit;
        break;
    }
}

void fn_80267470(SlotMenu* m) {
    void* want = *(void**)((u8*)fn_80060728(lbl_803CAB38) + 0x24);
    int i;
    int g;
    Slot* row = lbl_80430740[0];
    for (g = 0; g < 3; g++, row += 20) {
        Slot* e = row;
        for (i = 0; i < 20; e++, i++) {
            if (want == e->unit) {
                m->grp = g;
                m->idx = i;
                goto done;
            }
        }
    }
done:
    m->m54 = -0x8000;
    m->m56 = -0x8000;
    switch (m->m58) {
    case 1:
        *(void**)(m->m44 + 0x3C) = lbl_80430740[m->grp][m->idx].unit;
        break;
    default:
        *(void**)(m->m40 + 0x3C) = lbl_80430740[m->grp][m->idx].unit;
        break;
    }
}

void fn_80267360(SlotMenu* m) {
    int i2;
    void* u;
    int i;
    Slot* e2;
    Slot* e;
    Slot* e3;
    int i3;

    for (i = 0, e = lbl_80430740[0]; i < 20 && e->unit != 0; e++, i++) {
        fn_8011FE74(e->unit, 8);
    }
    for (i2 = 0, e2 = lbl_80430740[1]; i2 < 20 && e2->unit != 0; e2++, i2++) {
        fn_8011FE74(e2->unit, 9);
    }
    for (i3 = 0, e3 = lbl_80430740[2]; i3 < 20 && e3->unit != 0; e3++, i3++) {
        fn_8011FE74(e3->unit, 10);
    }
    u = lbl_80430740[m->grp][m->idx].unit;
    *(void**)((u8*)fn_80081194(lbl_80391AD8, m) + 0x30) = u;
}

void fn_80267568(SlotMenu* m) {
    int i2;
    void* u;
    int i;
    Slot* e2;
    Slot* e;
    Slot* e3;
    int i3;

    for (i = 0, e = lbl_80430740[0]; i < 20 && e->unit != 0; e++, i++) {
        fn_8011FE74(e->unit, 8);
    }
    for (i2 = 0, e2 = lbl_80430740[1]; i2 < 20 && e2->unit != 0; e2++, i2++) {
        fn_8011FE74(e2->unit, 9);
    }
    for (i3 = 0, e3 = lbl_80430740[2]; i3 < 20 && e3->unit != 0; e3++, i3++) {
        fn_8011FE74(e3->unit, 10);
    }
    u = lbl_80430740[m->grp][m->idx].unit;
    *(void**)((u8*)fn_80081194(lbl_80391AA8, m) + 0x30) = u;
}

void fn_80267678(u8* p) {
    if (*(int*)(lbl_803CA870 + 0x18) != 0) {
        fn_80083DC4(p, 4);
    } else {
        p[0x4A] = 1;
    }
}

void fn_802678AC(void* v) {
    Slot* s = (Slot*)v;
    s->unit = 0;
    s->b = 0;
    s->a = 0;
}

}
