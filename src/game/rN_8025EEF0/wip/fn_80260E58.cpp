/* NEAR MISS: 22 lines, registers only: the last two page moves want q r30 and the zero in r31. */
/* Dictionary: input on the chapter list */
#pragma inline_max_size(4000)
#include "game/rN_8025EEF0/calls.h"

struct DS {
    u8 pad[4];
    int mode;
    u8 pad8[8];
    void*** list;
    int count;
    s16 page;
    s16 x, y, sx, sy, ex, ey, t;
    s16 sel;
    u8 pad2A[0x46];
    u8 m70;
    u8 pad71[3];
    void* m74;
    u8 pad78[4];
    u8* m7C;
};

extern "C" {

extern DS* lbl_804CC004;
extern void* lbl_804CC000;
extern char lbl_80372C90[];
void fn_800C4240(void* p);
void* fn_80076F54(void* s);
int fn_800C3FD0(void* p);
void* fn_800C6118(void* a, int b, int c, int d, void* e);
void* fn_800D4188(const char* s, void* p);
void fn_80253EE4(const char* s, f32 v);
void fn_80263E5C(void);
int fn_800C7F90(void);

static inline void sync(void) {
    char buf[0x40];
    u8* q = (u8*)lbl_804CC004 + lbl_804CC004->page * 0x24;
    if (lbl_804CC004->m74 != 0) {
        fn_800C4240(lbl_804CC004->m74);
        lbl_804CC004->m74 = 0;
    }
    if (lbl_804CC004->page == 0 && lbl_804CC004->mode == 1) {
        u8* u = (u8*)fn_80076F54(*lbl_804CC004->list[*(s16*)(q + 0x28)]);
        if (u != 0) {
            fn_800C3FD0(*(void**)(u + 0x10));
            lbl_804CC004->m74 = fn_800C6118(*(void**)(u + 0x10), 0, 0, 0x640E, lbl_804CC000);
        }
    }
    q = (u8*)lbl_804CC004 + lbl_804CC004->page * 0x24;
    {
        u8* v = lbl_804CC004->m7C;
        if (v != 0) {
            fn_80081A90(v);
            lbl_804CC004->m7C = 0;
        }
    }
    if (lbl_804CC004->page == 1 && lbl_804CC004->mode == 1 && lbl_804CC004->list[*(s16*)(q + 0x28)][3] != 0) {
        fn_80290DDC(buf, lbl_80372C90 + 0x11C, lbl_804CC004->list[*(s16*)(q + 0x28)][3]);
        lbl_804CC004->m7C = (u8*)fn_800D4188(buf, lbl_804CC000);
        {
            u8* m = lbl_804CC004->m7C;
            *(f32*)(m + 0x40) = 230.0f;
            *(f32*)(m + 0x44) = 256.0f;
        }
        lbl_804CC004->m7C[100] = 0;
    }
    lbl_804CC004->m70 = 0xC;
}
static inline void moveTo(DS* d, int ey, int page) {
    d->sx = d->x;
    d->sy = d->y;
    d->ex = 0x46;
    d->ey = ey;
    d->t = 4;
    d->page = page;
    fn_80263E5C();
    sync();
}

static inline void moves(u32 pr, u32 held, DS* d) {
    s16 old;
    old = lbl_804CC004->page;
    if (old == 0) {
        if (pr & 0x800008) moveTo(d, 0x5A, 1);
    } else if (held & 0x800008) {
        moveTo(d, (old - 1) * 0x18 + 0x42, old - 1);
    }
    if (d->page == 1) {
        if (pr & 0x400004) moveTo(lbl_804CC004, 0x42, 0);
    } else if (held & 0x400004) {
        int k = d->page + 1;
        moveTo(lbl_804CC004, k * 0x18 + 0x42, k);
    }
    if (old != d->page) fn_80253EE4(lbl_80372C90 + 0x143, 0.0f);
}

void fn_80260E58(void) {
/*P*/
    u32 pr;
    u32 held;
    DS* d;
/*E*/
    pr = lbl_804CB5B8->v48();
    held = lbl_804CB5B8->v3C();
    d = lbl_804CC004;
    if ((pr & 0x400) && lbl_804CC004->count > 0) {
        lbl_804CC004->mode = 1;
        sync();
        fn_80253EE4(lbl_80372C90 + 0x123, 0.0f);
        return;
    }
    if (pr & 0x800) {
        if (fn_800C7F90() == 0) {
            fn_80083DC4(lbl_804CC000, 3);
            fn_80253EE4(lbl_80372C90 + 0x133, 0.0f);
        }
        return;
    }
    moves(pr, held, d);
}

}
