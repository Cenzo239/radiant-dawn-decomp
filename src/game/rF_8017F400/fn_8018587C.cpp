/* fn_8018587C, fn_80185A10: sparkle sprite update/draw and placement. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct SpG { u8 pad[0x30]; void* arch; int x34; } SpG;
typedef struct Sp { u8 pad[0x30]; SpG* g; f32 x34, x38, x3c, x40; int x44; } Sp;
typedef struct Tex { u8 b[0x20]; s16 w, h; } Tex;
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(void*, int);
extern void fn_80006A64(void*, Tex*, u16);
extern s16 fn_80305DF8(Tex*);
extern s16 fn_80305E0C(Tex*);
extern void fn_800800D4(int);
extern void fn_80080308(void);
extern void fn_8008031C(f32);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(u8, u8, u8, u8);
extern double fn_80295534(double);
void fn_8018587C(Sp* p) {
    Tex tex;
    f32 a = 0.5f * (f32)fn_80295534(6.2831855f / p->x3c * p->x40) + 0.5f;
    p->x40 += 0.016666668f;
    if (p->x40 > p->x3c) p->x40 -= p->x3c;
    fn_80006A64(p->g->arch, &tex, (u16)p->x44);
    tex.w = fn_80305DF8(&tex);
    tex.h = fn_80305E0C(&tex);
    fn_8007E154();
    fn_8007E174(&tex, 0x20);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(p->x34, (((int)(512.0f + p->x38 - p->g->x34 / 2)) & 0x1ff) - 0x20, (u16)tex.w, (u16)tex.h);
    fn_800804D4(0xc0, 0xc0, 0xff, 160.0f * a);
    fn_8008031C(-1.0f);
    fn_80080308();
}
typedef struct Rect16 { s16 x0, y0, x1, y1; } Rect16;
typedef struct Bk { u8 pad[0x30]; void* arch; } Bk;
extern char lbl_80388070[], lbl_8038808C[];
extern void* fn_80081050(void*, void*);
extern void fn_800068A0(void*, const char*);
extern void* fn_800791B0(u32);
extern void* fn_8028BE18(void*, void*, void*, u32, u32);
extern void fn_80079474(void*);
extern int fn_80089C88(int);
extern BOOL fn_8017FB24(Rect16*, Rect16*);
extern void fn_8017FB88(Rect16*);
static inline void RInit(Rect16* r, s16 a, s16 b, s16 c, s16 d) { r->x0 = a; r->y0 = b; r->x1 = c; r->y1 = d; }
static inline void Mv(Rect16* r, s16 dx, s16 dy) { r->x0 += dx; r->y0 += dy; r->x1 += dx; r->y1 += dy; }
static inline s16 RnS(int n) { return fn_80089C88(n); }
void fn_80185A10(void* parent, int mode) {
    /*P*/
    Rect16* r;
    Rect16* q;
    Bk* m;
    void* arch;
    int left;
    Rect16* rects;
    int i;
    int tile;
    int j;
    /*Y*/
    Sp* sp;
/*E*/
    Tex tex;
    m = (Bk*)fn_80081050(lbl_80388070, parent);
    {
    const char* names[2] = { "window/back.cms", "window/back2.cms" };
    fn_800068A0(&m->arch, names[mode]);
    }
    arch = m->arch;
    left = 100;
    rects = (Rect16*)fn_8028BE18(fn_800791B0(0x110), 0, 0, 8, 0x20);
    r = rects;
    for (i = 0; i < 0x20; i++, r++) {
        tile = fn_80089C88(8) + 2;
        fn_80006A64(arch, &tex, (u16)tile);
        tex.w = fn_80305DF8(&tex);
        tex.h = fn_80305E0C(&tex);
        RInit(r, 0, 0, tex.w, tex.h);
    again:
        s16 y = RnS(0x200);
        s16 x2 = fn_80089C88((u16)tex.w + 0x260) - ((u32)(u16)tex.w >> 1);
        Mv(r, x2, y);
        q = rects;
        for (j = 0; j < i; q++, j++) {
            if (fn_8017FB24(r, q)) {
                fn_8017FB88(r);
                if (--left >= 0) goto again;
                goto next;
            }
        }
        sp = (Sp*)fn_80081050(lbl_8038808C, m);
        sp->x34 = r->x0;
        sp->x38 = r->y0;
        sp->x44 = tile;
        sp->g = (SpG*)m;
        sp->x3c = 5.0f;
        sp->x40 = sp->x3c / 32768.0f * fn_80089C88(0x8000);
    next:;
    }
    if (rects) fn_80079474((u8*)rects - 0x10);
}
}
