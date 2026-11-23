/* functionally equal (check_regs). Dictionary: input on the entry list (page up/down, wrap, select, back). Round 18, written from the asm;
   DS and sync() as in wip/fn_80260E58.cpp. */
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

/* per-page cursor block at lbl_804CC004 + 0x28 + page * 0x24 */
struct PG {
    s16 cur;
    u8 pad2[0xE];
    f32 f10;    /* scroll now */
    f32 f14;    /* scroll start */
    f32 f18;    /* scroll target */
    int m1C;    /* frames left */
    int m20;    /* frames total */
};
struct D2 { void* item; u8 pad4[0x26]; s16 m2A; s16 m2C; u8 pad2E[0x16]; s16 m44; s16 m46; };
extern D2* lbl_804CC008;
void fn_80264204(int page, int idx, int c);
#define PAGES ((PG*)((u8*)lbl_804CC004 + 0x28))

#define MAXSC ((f32)(lbl_804CC004->count - 9))
static inline void scrollTo(f32 from, f32 to, int t) {
    PG* d = &PAGES[lbl_804CC004->page];
    if (to > MAXSC) to = MAXSC;
    if (to < 0.0f) to = 0.0f;
    d->f14 = from;
    d->f18 = to;
    d->m20 = t;
    d->m1C = t;
}

void fn_80261728(void) {
    u32 pr;
    u32 held;
    int page;
    PG* q;
    int old;
    pr = lbl_804CB5B8->v48();
    held = lbl_804CB5B8->v3C();
    page = lbl_804CC004->page;
    q = &PAGES[page];
    if ((pr & 0x400) && page == 0) {
        if (fn_800C7F90() == 0) {
            if (*(s16*)((u8*)lbl_804CC004->list[lbl_804CC004->sel] + 0xC) >= 0) {
                D2* d2 = lbl_804CC008;
                s16* e = (s16*)lbl_804CC004->list[q->cur];
                d2->m2A = e[6] + 2;
                d2->m2C = e[7] + 0x14;
                lbl_804CC008->m44 = e[6] - 0x112;
                lbl_804CC008->m46 = e[7] - 0xB8;
                if (lbl_804CC008->m44 < 0) lbl_804CC008->m44 = 0;
                if (lbl_804CC008->m44 > 0x470) lbl_804CC008->m44 = 0x470;
                if (lbl_804CC008->m46 < 0) lbl_804CC008->m46 = 0;
                if (lbl_804CC008->m46 > 0x348) lbl_804CC008->m46 = 0x348;
                fn_80083DC4(lbl_804CC000, 2);
                lbl_804CC008->item = lbl_804CC004->list[q->cur];
                fn_80253EE4(lbl_80372C90 + 0x123, 0.0f);
            }
        }
        return;
    }
    if (pr & 0x800) {
        lbl_804CC004->mode = 0;
        sync();
        fn_80253EE4(lbl_80372C90 + 0x133, 0.0f);
        return;
    }
    if (q->m1C == 0) {
        old = q->cur;
        if (held & 0x100001) {
            f32 v = q->f10 - 9.0f;
            if (v < 0.0f) v = 0.0f;
            scrollTo(q->f10, v, 4);
            if (q->cur - 9 < 0) q->cur = 0; else q->cur = q->cur - 9;
            fn_80264204(page, q->cur, 0);
            if (old != q->cur) {
                sync();
                fn_80253EE4(lbl_80372C90 + 0x143, 0.0f);
            }
            return;
        }
        if (held & 0x200002) {
            f32 v = 9.0f + q->f10;
            int k;
            if (v > MAXSC) v = MAXSC;
            if (v < 0.0f) v = 0.0f;
            scrollTo(q->f10, v, 4);
            k = lbl_804CC004->count - 1;
            if (q->cur + 9 > k) q->cur = k; else q->cur = q->cur + 9;
            fn_80264204(page, q->cur, 0);
            if (old != q->cur) {
                sync();
                fn_80253EE4(lbl_80372C90 + 0x143, 0.0f);
            }
            return;
        }
        if (old == 0) {
            if (pr & 0x800008) {
                fn_80264204(page, lbl_804CC004->count - 1, 0);
                scrollTo(q->f10, lbl_804CC004->count - 9, 0xC);
                sync();
            }
        } else if (held & 0x800008) {
            if (old < (int)q->f18 + 2) {
                scrollTo(q->f10, q->f18 - 1.0f, 4);
            }
            fn_80264204(page, q->cur - 1, 0);
            sync();
        }
        if (q->cur == lbl_804CC004->count - 1) {
            if (pr & 0x400004) {
                fn_80264204(page, 0, 0);
                scrollTo(q->f10, 0.0f, 0xC);
                sync();
            }
        } else if (held & 0x400004) {
            if (q->cur > (int)q->f18 + 6) {
                scrollTo(q->f10, 1.0f + q->f18, 4);
            }
            fn_80264204(page, q->cur + 1, 0);
            sync();
        }
        if (old != q->cur) fn_80253EE4(lbl_80372C90 + 0x143, 0.0f);
    }
    {
        if (q->f18 > MAXSC) q->f18 = MAXSC;
        if (q->f18 < 0.0f) q->f18 = 0.0f;
    }
}

}
