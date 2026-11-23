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
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(u8*, p32arg, int);
#else
extern void fn_8007E374(u8*, int, int);
#endif
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

void fn_8014D370(FlakeProc* p) {
    int n = 0;
    if (p->f[0].life >= 0) {
        n++;
        FlakeDraw(&p->f[0]);
    }
    if (p->f[1].life >= 0) {
        n++;
        FlakeDraw(&p->f[1]);
    }
    if (p->f[2].life >= 0) {
        n++;
        FlakeDraw(&p->f[2]);
    }
    if (n == 0) {
        fn_80081A90(p);
    }
}

void fn_8014D7F0(void) { fn_800068A0(&lbl_804CB888, lbl_80369C30); }
void fn_8014D800(void) { fn_80006A2C(&lbl_804CB888); }

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





void fn_8014DC08(void) { fn_800068A0(&lbl_804CB888, lbl_80369C30); }

void fn_8014DC18(Proc* p) {
    fn_80006A2C(&lbl_804CB888);
    fn_80079474(*(void**)(p + 1));
}

}
