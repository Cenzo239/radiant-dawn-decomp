#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* fullscreen overlay input: picks a cursor entry per page and moves the highlight */
struct Cur { int page; int idx; int x8; int xC; int x10; u8* x14; int x18; Cur* prev; Cur* next; };
struct Page { int x0; f32 x; f32 y; int n; Cur c[5]; };
typedef struct SD {
    u8 done; u8 pad1[3]; u32 flags; s8 state; u8 pad9; s16 timer; void* res;
    Page pages[4];
    Cur* cur; int x324; s16 x328, x32A, x32C, x32E, x330, x332; u32* x334;
    u8 pad338[0x348 - 0x338];
    int order[2][2];
} SD;
class Pad { public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38();
    virtual u32 trig();
    virtual void v40(); virtual void v44();
    virtual u32 held();
};
extern SD* lbl_804CB964;
extern void* lbl_804CB960;
extern Pad* lbl_804CB5B8;
extern char lbl_8036D22C[];
extern void fn_80253EE4(const char*, f32);
extern void fn_80006EE0(void*);
extern u32* fn_80006E1C(void);
extern void fn_80006F20(void*);
extern void fn_80083DC4(void*, int);

static inline void First(Page*& p) {
    SD* d = lbl_804CB964;
    int i;
    for (i = 0; i < 4; i++) {
        p = (Page*)((u8*)d + 0x10 + d->order[0][i] * 0xC4);
        if (p->n > 0) { d->cur = p->c; return; }
    }
}
static inline void Move(int t) {
    lbl_804CB964->x324 = t;
    lbl_804CB964->x32C = lbl_804CB964->x328;
    lbl_804CB964->x32E = lbl_804CB964->x32A;
    lbl_804CB964->x330 = 10.0f + lbl_804CB964->pages[lbl_804CB964->cur->page].x;
    lbl_804CB964->x332 = 16.0f + lbl_804CB964->pages[lbl_804CB964->cur->page].y + lbl_804CB964->cur->idx * 0x18;
    fn_80253EE4(lbl_8036D22C + 0xC1, 0.0f);
    if (lbl_804CB964->cur->x14 != 0) {
        if (lbl_804CB964->x334 != 0) fn_80006EE0(lbl_804CB964->x334);
        lbl_804CB964->x334 = fn_80006E1C();
        lbl_804CB964->x334[1] = (u32)(lbl_804CB964->cur->x14 + 0x28);
        lbl_804CB964->x334[0] |= 0xE001A000;
        fn_80006F20(lbl_804CB964->x334);
    }
}

static inline void Up(u32 held) {
            Cur* o = lbl_804CB964->cur;
            if (o->prev != 0) {
                lbl_804CB964->cur = o->prev;
            } else if (held & 0x800008) {
                while (lbl_804CB964->cur->next != 0) lbl_804CB964->cur = lbl_804CB964->cur->next;
            }
            if (o != lbl_804CB964->cur) Move(6);
}
static inline void Dn(u32 held) {
            Cur* o = lbl_804CB964->cur;
            if (o->next != 0) {
                lbl_804CB964->cur = o->next;
            } else if (held & 0x400004) {
                while (lbl_804CB964->cur->prev != 0) lbl_804CB964->cur = lbl_804CB964->cur->prev;
            }
            if (o != lbl_804CB964->cur) Move(6);
}
void fn_801A7150(void) {
    u32 held = lbl_804CB5B8->held();
    u32 trig = lbl_804CB5B8->trig();
    switch (lbl_804CB964->state) {
    case 0:
        if (held & 0x400) {
            lbl_804CB964->state = 1;
            lbl_804CB964->timer = 0;
            {Page* p; First(p);}
            Move(1);
            fn_80253EE4(lbl_8036D22C + 0xDC, 0.0f);
        } else if (held & 0x800) {
            fn_80083DC4(lbl_804CB960, 1);
            fn_80253EE4(lbl_8036D22C + 0xF9, 0.0f);
        }
        break;
    case 2:
        if (held & 0x800) {
            lbl_804CB964->state = 3;
            lbl_804CB964->timer = 6;
            fn_80253EE4(lbl_8036D22C + 0xF9, 0.0f);
        } else if ((trig & 0x800008) || (held & 0x800008)) {
            Up(held);
        } else if ((trig & 0x400004) || (held & 0x400004)) {
            Dn(held);
        }
        break;
    case 1:
        lbl_804CB964->timer++;
        if (lbl_804CB964->timer >= 6) lbl_804CB964->state = 2;
        break;
    case 3:
        lbl_804CB964->timer--;
        if (lbl_804CB964->timer <= 0) lbl_804CB964->state = 0;
        break;
    }
}
}
