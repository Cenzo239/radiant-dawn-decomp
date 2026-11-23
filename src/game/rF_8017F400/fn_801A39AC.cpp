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

static inline int Rows(GD* d, int& q) {
    q = d->n / 3;
    if (d->n % 3 > 0) q++;
    return q;
}
#define ST(o, to, a, v) \
    o->x28 = o->scroll; \
    a = to; \
    o->x2A = a; \
    o->x2E = 0; \
    o->x2C = 0; \
    v = to; \
    o->x28 = v; \
    o->scroll = v;
static inline void Clamp(GD* d) {
/*P*/
    GD* o;
    s16 a;
    s16 a2;
    GD* p;
    s16 sl;
    int q;
    s16 v2;
    s16 v;
    int z;
/*E*/
    while ((o = lbl_804CB94C)->sel / 3 - d->scroll <= 0.0f && d->scroll > 0.0f) {
        { f32 t1 = d->scroll - 1.0f; ST(o, t1, a, v) }
    }
    while ((sl = (p = lbl_804CB94C)->sel) / 3 - d->scroll >= 6.0f && d->scroll < Rows(d, q) - 7) {
        { f32 t2 = 1.0f + d->scroll; ST(p, t2, a2, v2) }
    }
    {
    int k;
   int x2=lbl_804CB94C->x2A; lbl_804CB94C->x16=0;
    k = sl - x2*3;
    lbl_804CB94C->x12 = (k % 3) * 0x92 + 0x4D;
    lbl_804CB94C->x14 = (k / 3) * 0x1C + 0x98;
    fn_80253EE4(lbl_8036D10C + 0xD1, 0.0f);
    fn_80083DC4(lbl_804CB948, 2);
    }
}
void fn_801A39AC(void) {
    u32 held;
    GD* d;
    u32 trig;
    d = lbl_804CB94C;
    held = lbl_804CB5B8->held();
    trig = lbl_804CB5B8->trig();
    if (((held & 0x400) && fn_800C7F90() == 0) || ((held & 0x800) && fn_800C7F90() == 0)) {
        fn_80253EE4(lbl_8036D10C + 0x7C, 0.0f);
        fn_80083DC4(lbl_804CB948, 0);
        fn_800C835C(3, 0xB4);
        return;
    }
    if ((trig & 0x800008) && fn_800C7F90() == 0) {
        do {
            lbl_804CB94C->sel--;
            if (lbl_804CB94C->sel < 0) lbl_804CB94C->sel = d->n - 1;
        } while (fn_8025F6A0(lbl_80388AA0[lbl_804CB94C->sel][0]) == 0);
        Clamp(d);
    } else if ((trig & 0x400004) && fn_800C7F90() == 0) {
        do {
            lbl_804CB94C->sel++;
            if (lbl_804CB94C->sel >= d->n) lbl_804CB94C->sel = 0;
        } while (fn_8025F6A0(lbl_80388AA0[lbl_804CB94C->sel][0]) == 0);
        Clamp(d);
    }
}
}
