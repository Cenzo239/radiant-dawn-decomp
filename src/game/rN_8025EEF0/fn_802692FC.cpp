/* Unit slot menu: start of the menu proc, fills the three groups */
#include "game/rN_8025EEF0/calls.h"

extern "C" {

struct Slot { void* unit; s16 a; s16 b; };
extern Slot lbl_80430740[3][20];
extern u8* lbl_804CB814;
extern void* lbl_80391A10[][2];
extern u8 lbl_80391A48[];
extern u8 lbl_80391D78[];
extern char lbl_804CA380[8];
void fn_800068A0(void* p, void* q);
void fn_800C4A58(void* p);
void fn_8017F44C(void* p, int v, int n);
void* fn_8017AA08(void* p);
void fn_8017A968(void* p, void* q);

struct Bar {
    u8 pad[0x31];
    u8 m31;
    int m34; int m38; void* m3C;
    f32 m40, m44, m48, m4C, m50;
};
struct Own { u8 pad[0x34]; void* m34; void* m38; u8* m3C; Bar* m40; Bar* m44; u8 pad48[4]; s16 grp; s16 idx; };

struct UL { u8* head; };

static inline void fill(int g, int off) {
/*P*/
    u8* nx;
    int n;
    u8* nx2;
    u8* u2;
    Slot* row;
    u8* u;
/*E*/
    row = lbl_80430740[g];
    n = 0;
    u = *(u8**)(lbl_804CB814 + off);
    while (u != 0) {
        nx = *(u8**)(u + 0xE8);
        if (*(u32*)(u + 0x10C) & 0x10000) {
            ((u8**)row)[n++ * 2] = u;
        }
        u = nx;
    }
    u2 = *(u8**)(lbl_804CB814 + off);
    while (u2 != 0) {
        nx2 = *(u8**)(u2 + 0xE8);
        if (!(*(u32*)(u2 + 0x10C) & 0x10000)) {
            ((u8**)row)[n * 2] = u2;
            n++;
        }
        u2 = nx2;
    }
}

static inline Bar* newBar(Own* o) {
    Bar* b = (Bar*)fn_80081050(lbl_80391A48, o);
    if (b != 0) {
        b->m31 = 0;
        b->m34 = 0;
        b->m38 = 0;
        b->m3C = 0;
        b->m40 = 0.0f;
        b->m44 = 0.0f;
        b->m48 = 0.0f;
        b->m4C = 1.0f;
        b->m50 = 799.0f;
    }
    return b;
}

void fn_802692FC(Own* o) {
    int lang = (s8)fn_8024BC94()[0x1BC8];
    fn_800068A0(&o->m34, lbl_80391A10[lang][fn_801D09F0()]);
    fn_800C4A58(&o->m38);
    fn_8017F44C(lbl_80430740, 0, 0x1E0);
    fill(0, 0x60);
    fill(1, 0x6C);
    fill(2, 0x78);
    {
        void* unit = lbl_80430740[o->grp][o->idx].unit;
        Bar* b = newBar(o);
        b->m3C = unit;
        b->m40 = 16.0f;
        b->m44 = 324.0f;
        o->m40 = b;
    }
    {
        Bar* b = newBar(o);
        b->m3C = 0;
        b->m40 = 306.0f;
        b->m44 = 324.0f;
        o->m44 = b;
        b->m31 = 1;
        o->m44->m4C = 0.0f;
    }
    {
        void* p = fn_80078CCC(0x30, lbl_804CA380, 0);
        if (p != 0) {
            p = fn_8017AA08(p);
        }
        o->m3C = (u8*)p;
        fn_8017A968(p, lbl_80391D78);
        *(f32*)(o->m3C + 0x10) = 799.0f;
    }
}

}
