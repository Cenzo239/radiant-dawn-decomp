/* near miss: fn_801A32BC, about 45 lines of volatile-register differences (ScrollTo o/t; c block; last block). Saved registers and shape right. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* 3-column grid menu input */
typedef struct GD {
    u8 pad[0x10];
    s16 sel; s16 x12; s16 x14; s16 x16; s16 x18; s16 x1A; s16 x1C; s16 x1E;
    u8 n; u8 pad21[3];
    f32 scroll;
    s16 x28; s16 x2A; s16 x2C; s16 x2E;
} GD;
class Pad { public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38();
    virtual u32 trig();
    virtual void v40(); virtual void v44();
    virtual u32 held();
};
extern GD* lbl_804CB94C;
extern void* lbl_804CB948;
extern Pad* lbl_804CB5B8;
extern char lbl_8036D10C[];
extern const char* lbl_80388AA0[][2];
extern int fn_800C7F90(void);
extern int fn_8025F6A0(const char*);
extern void fn_80253EE4(const char*, f32);
extern void fn_80083DC4(void*, int);
extern void fn_800C835C(int, int);
extern double fn_80295CF0(double);

static inline void ScrollTo(f32 to, s16 t) {
    GD* o = lbl_804CB94C;
    o->x28 = o->scroll;
    o->x2A = to;
    o->x2E = t;
    o->x2C = t;
    if (t == 0) {
        s16 v = to;
        o->x28 = v;
        o->scroll = v;
    }
}
void fn_801A32BC(void) {

    u32 held;
    GD* d;
    s16 old;
    u32 trig;
    s16 rows;

    d = lbl_804CB94C;
    held = lbl_804CB5B8->held();
    trig = lbl_804CB5B8->trig();
    old = lbl_804CB94C->sel;
    if ((held & 0x400) && fn_800C7F90() == 0) {
        if (fn_8025F6A0(lbl_80388AA0[lbl_804CB94C->sel][0]) != 0) {
            fn_80253EE4(lbl_8036D10C + 0x6C, 0.0f);
            fn_80083DC4(lbl_804CB948, 1);
            fn_800C835C(3, 0xB4);
        }
        return;
    }
    if ((held & 0x800) && fn_800C7F90() == 0) {
        fn_80253EE4(lbl_8036D10C + 0x7C, 0.0f);
        fn_80083DC4(lbl_804CB948, 3);
        return;
    }
    {
    int q = d->n / 3;
    if (d->n % 3 > 0) q++;
    rows = q;
    if (lbl_804CB94C->sel < 3) {
        if (held & 0x800008) {
            int m = (rows - 1) * 3;
            lbl_804CB94C->sel = m + lbl_804CB94C->sel;
            if (lbl_804CB94C->sel > d->n - 1) lbl_804CB94C->sel -= 3;
            { s16 tt = fn_80295CF0(rows * 4); ScrollTo(rows - 7, tt); }
        }
    } else if (trig & 0x800008) {
        lbl_804CB94C->sel -= 3;
        {
            f32 s = d->scroll;
            if (lbl_804CB94C->sel / 3 - s <= 1.0f && s > 0.0f) {
                s = s - 1.0f; ScrollTo(s, 4);
            }
        }
    }
    if (lbl_804CB94C->sel >= d->n - 3) {
        if (held & 0x400004) {
            int m = (1 - rows) * 3;
            lbl_804CB94C->sel = m + lbl_804CB94C->sel;
            if (lbl_804CB94C->sel < 0) lbl_804CB94C->sel += 3;
            { s16 tt = fn_80295CF0(rows * 4); ScrollTo(0, tt); }
        }
    } else if (trig & 0x400004) {
        lbl_804CB94C->sel += 3;
        {
            f32 s = d->scroll;
            if (lbl_804CB94C->sel / 3 - s >= 5.0f && s < rows - 7) {
                s = 1.0f + s; ScrollTo(s, 4);
            }
        }
    }
    }
    if (lbl_804CB94C->sel % 3 == 0) {
        if (held & 0x100001) lbl_804CB94C->sel += 2;
        if (lbl_804CB94C->sel >= d->n) lbl_804CB94C->sel = d->n - 1;
    } else if (trig & 0x100001) {
        lbl_804CB94C->sel--;
    }
    int c = lbl_804CB94C->sel % 3;
    if (c == 2 || lbl_804CB94C->sel == d->n - 1) {
        if (held & 0x200002) lbl_804CB94C->sel -= c;
    } else if (trig & 0x200002) {
        lbl_804CB94C->sel++;
        if (lbl_804CB94C->sel >= d->n) lbl_804CB94C->sel = d->n - 1;
    }
    if (old != lbl_804CB94C->sel) {
        int k = lbl_804CB94C->sel - lbl_804CB94C->x2A * 3;
        lbl_804CB94C->x16 = 4;
        lbl_804CB94C->x18 = lbl_804CB94C->x12;
        lbl_804CB94C->x1A = lbl_804CB94C->x14;
        lbl_804CB94C->x1C = (k % 3) * 0x92 + 0x4D;
        lbl_804CB94C->x1E = (k / 3) * 0x1C + 0x98;
        fn_80253EE4(lbl_8036D10C + 0x8C, 0.0f);
    }
}
}
