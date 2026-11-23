/* EXACT (round 23a): fn_8026806C, from equiv/fn_8026806C.cpp; a const SlotMenu* parameter moves the first lha above the stwu */
/* (older header, kept for history)  r19: self-contained (helpers of fn_80266E3C.cpp + wip fragment); `sched` level. */
/* Menus around the dictionary: creation, slot tables at lbl_80430740. */
#include "game/rN_8025EEF0/dict.h"

#pragma use_lmw_stmw on

extern "C" {

void* fn_80081194(void* script, void* parent);
void* fn_80078CCC(int size, const char* name, int a);
void* memset(void* p, int v, unsigned n);
f32 fn_8017F68C(int mode, f32 from, f32 to, f32 t, f32 d);
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
void fn_80266E3C(void* parent);

void fn_80266F24(void* parent);


struct FadeProc {
    u8 pad[0x30];
    s8 t;      /* 0x30 */
    u8 pad31[0x48 - 0x31];
    f32 a;     /* 0x48 */
    f32 b;     /* 0x4C */
};
void fn_8026700C(FadeProc* p);

void fn_802670D0(FadeProc* p);


struct SndProc { u8 pad[0x34]; u8 a[4]; u8 b[4]; };
void fn_80267194(SndProc* p);

void fn_802671FC(SndProc* p);

void fn_8026724C(void);

void fn_8026725C(u8* p);


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
void fn_80267268(SlotMenu* m);

void fn_80267470(SlotMenu* m);

void fn_80267360(SlotMenu* m);

void fn_80267568(SlotMenu* m);

void fn_80267678(u8* p);

void fn_802678AC(void* v);


}

/* ---- from rN_8025EEF0/wip/fn_8026806C.cpp ---- */
extern "C" {
/* fn_8026806C: lha scheduled above stwu in the original */
u32 fn_8026806C(const SlotMenu* m) {
    int x;
    int y;
    s16 pos[2];
    switch (m->grp) {
    case 0: x = 0x23; y = 0x4C; break;
    case 1: x = 0xE3; y = 0x4C; break;
    case 2: x = 0x1A3; y = 0x4C; break;
    }
    pos[0] = x + (m->idx % 4) * 0x28;
    pos[1] = y + (m->idx / 4) * 0x30;
    return *(u32*)pos;
}
}
