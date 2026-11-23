/* symcheck: r21 review, flag was an artefact. fn_8014D9FC: (a) tool bug: `@sda21(r0)` took r0's value as the base;
   fixed in symcheck.py. See docs/SCHED_REVIEW.md. */
/* Round 20, functionally equal (check_regs.py: sched): fn_8014D9FC. Self-contained. Parent file with its exported fn_ bodies removed plus the fragment from wip/near.cpp, use_lmw_stmw set from the original. Moved (harmless): three independent constant loads (li 0x4000, subi 0x10000-0x4000, li 0x1000) before a call are emitted in another order. */
/* Snow particles: three flakes per process, 8014D370..8014DC50. */
#include "game/rM_8014C9F8/types.h"

struct Flake {
    s16 life;   /* 0x00 */
    s8 size;    /* 0x02 */
    u8 alpha;   /* 0x03 */
    int x;      /* 0x04 */
    int y;      /* 0x08 */
    int vx;     /* 0x0C */
    int vy;     /* 0x10 */
    u8* tint;   /* 0x14 */
};

struct FlakeProc : Proc {
    Flake f[3]; /* 0x30 */
};

struct Snow : Proc {
    f32 rate;   /* 0x30 */
    f32 acc;    /* 0x34 */
    u8* tint;   /* 0x38 */
};

extern "C" {

extern u8* lbl_804CB888;
extern char lbl_80369C30[];
extern int lbl_804CB88C;
extern int lbl_804CB890;
extern int lbl_804CB894;
extern int lbl_804CB898;
extern int lbl_804CB89C;
extern u8 lbl_804CB8A0;
extern u8 lbl_804CB8A1;
extern u8 lbl_80386CD0[];
extern u8 lbl_80386CE0[];

extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E374(u8*, int, int);
extern void fn_8007E7DC(u8);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804F4(u8);
extern void fn_80080308(void);
extern void fn_800068A0(void*, char*);
extern void fn_80006A2C(void*);
extern void fn_80079474(void*);
extern u32 fn_80089ED0(void);

static inline void FlakeDraw(Flake* f) {
    int w = 0x50;
    if (f->size < 8) {
        w = 0x6E;
    }
    f32 fw = w;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, fw, 1.0f);
    fn_8007E374(lbl_804CB888, 6, 0x10);
    if (f->tint != NULL) {
        fn_8007E7DC(*f->tint);
    }
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(f->x >> 16, f->y >> 16, f->size, f->size);
    fn_800804F4(f->alpha);
    fn_80080308();
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
    f->x += f->vx;
    f->y += f->vy;
    if (f->x < -0x80000) {
        f->x = 0x2600000;
    }
    if (f->x > 0x2610000) {
        f->x = -0x70000;
    }
    if (f->y > 0x1220000) {
        f->life = -1;
    }
}
void fn_8014D370(FlakeProc* p);

void fn_8014D7F0(void);

void fn_8014D800(void);


static inline void FlakeInitRest(FlakeProc* p, int i, Snow* s) {
    u8* t = s->tint;
    p->f[i].life = fn_80089ED0() % 300 + 300;
    p->f[i].tint = t;
    if (i == 0) {
        int w = lbl_804CB89C;
        lbl_804CB88C = lbl_804CB894 - w + fn_80089ED0() % (u32)(w * 2);
        if (lbl_804CB88C <= 0) {
            lbl_804CB88C = -lbl_804CB88C;
            if (lbl_804CB88C == 0) {
                lbl_804CB88C = 0x4000;
            }
        }
    }
    {
        int w = lbl_804CB898;
        int vx = lbl_804CB890 - w + fn_80089ED0() % (u32)(w * 2);
        int vy = lbl_804CB88C;
        p->f[i].vx = vx;
        p->f[i].vy = vy;
        int lo = lbl_804CB894 - lbl_804CB89C;
        int range = lbl_804CB894 + lbl_804CB89C - lo;
        int d = vy - lo;
        p->f[i].size = (u8)(d * 7 / range) + 2;
        p->f[i].alpha = lbl_804CB8A0 + d * (lbl_804CB8A1 - lbl_804CB8A0) / range;
    }
}
void fn_8014DC08(void);

void fn_8014DC18(Proc* p);


}

#pragma use_lmw_stmw off
/* ---- from build/tmp/r20small/rM/frag_fn_8014D9FC.cpp ---- */
extern "C" {
/* from fn_8014D370.cpp */
void fn_8014D9FC(void* parent, u8* tint) {
    Snow* s = (Snow*)fn_80081050(lbl_80386CE0, parent);
    if (s != NULL) {
        lbl_804CB898 = 0x2000;
        lbl_804CB890 = 0x4000;
        lbl_804CB894 = 0xC000;
        lbl_804CB89C = 0x1000;
        lbl_804CB8A0 = 0x28;
        lbl_804CB8A1 = 0x80;
        s->rate = 0.2f;
        s->acc = 0.0f;
        s->tint = tint;
        while (1) {
            if (0x80 - fn_800839DC() < 1) {
                return;
            }
            int i;
            FlakeProc* p = (FlakeProc*)fn_80081050(lbl_80386CD0, s);
            for (i = 0; i < 3; i++) {
                p->f[i].x = fn_80089ED0() % 0x25F0000;
                p->f[i].y = fn_80089ED0() % 0x1F40000 - 0xC80000;
                FlakeInitRest(p, i, s);
            }
        }
    }
}
}
