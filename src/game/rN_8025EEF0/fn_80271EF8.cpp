/* Slide proc setup: allocates two sets of three drawers */
#include "game/rN_8025EEF0/calls.h"

extern "C" {

void* fn_80079150(int size);
extern char lbl_8039275C[];
extern char lbl_80392768[];
extern char lbl_80392750[];

struct ObjA { void* vt; int i; int p; s16 x; s16 y; };
struct ObjB { void* vt; int i; int p; int mC; int m10; s16 x; s16 y; s16 m18; s16 m1A; f32 m1C; u8 pad[8]; };
struct ObjC {
    void* vt; int i; int p; int mC; int m10; int m14; int m18; int m1C;
    u8 m20; u8 pad21[3]; int m24; int m28; u8 pad2C[0xF4 - 0x2C];
    s16 mF4; u8 padF6[2]; int mF8; int mFC; s16 x; s16 y; f32 m104;
};
struct Own {
    u8 pad[0x38]; int m38; u8 pad3C[0x48 - 0x3C];
    ObjA* a[2]; ObjB* b[2]; u8 pad58[8]; ObjC* c[2];
};

static inline ObjA* newA(int i, Own* o) {
    ObjA* p = (ObjA*)fn_80079150(0x10);
    if (p != 0) {
        int v = o->m38;
        p->vt = lbl_8039275C;
        p->i = i;
        p->p = v;
        switch (i) {
        case 0: p->x = 0x1C; p->y = 0x1C; break;
        case 1: p->x = 0xBB; p->y = 0xED; break;
        }
    }
    return p;
}
static inline ObjB* newB(int i, Own* o) {
    ObjB* p = (ObjB*)fn_80079150(0x28);
    if (p != 0) {
        int v = o->m38;
        p->vt = lbl_80392768;
        p->i = i;
        p->p = v;
        p->mC = 0;
        p->m10 = 0;
        p->m18 = 0;
        p->m1A = 0;
        p->m1C = 0.0f;
        switch (i) {
        case 0: p->x = 0x174; p->y = 0x23; break;
        case 1: p->x = 0; p->y = 0xF4; break;
        }
    }
    return p;
}
static inline ObjC* newC(int i, Own* o) {
    ObjC* p = (ObjC*)fn_80079150(0x108);
    if (p != 0) {
        int v = o->m38;
        p->vt = lbl_80392750;
        p->i = i;
        p->p = v;
        p->mC = 0;
        p->m10 = 0;
        p->m14 = 0;
        p->m18 = 0;
        p->m1C = 0;
        p->m20 = 0;
        p->m24 = 0;
        p->m28 = 0;
        p->mF4 = 0;
        p->mF8 = 0;
        p->mFC = 0;
        p->m104 = 0.0f;
        switch (i) {
        case 0: p->x = 0x1C; p->y = 0x1C; break;
        case 1: p->x = 0xBB; p->y = 0xED; break;
        }
    }
    return p;
}

void fn_80271EF8(Own* o) {
    Own* q = o;
    int i;
    for (i = 0; i < 2; i++, q = (Own*)((u8*)q + 4)) {
        q->a[0] = newA(i, o);
        q->b[0] = newB(i, o);
        q->c[0] = newC(i, o);
    }
}

}
