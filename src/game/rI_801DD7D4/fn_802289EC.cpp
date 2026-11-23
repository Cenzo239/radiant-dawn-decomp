#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/fn_wf.h"
extern "C" {
void* memset(void*, int, u32);
void* fn_801E5640(void*, int, int);
class RObj { public: virtual void destroy(int); int rc; };
struct LB { u8* x0; u8 p[8]; u8 xc; u8 p2[0xb]; int x18; u8 p3[0x100]; };
extern LB lbl_803CA870;
extern u8 lbl_8038FB98[];
struct It { u8 p[0x1f]; u8 x1f; };
It* fn_8010B22C(int);
int fn_8011B8A4(void*);
void fn_801E495C(void*, void*, void*, int);
void fn_801E459C(void*, void*, void*, int);
void fn_80083B78(void*);
void fn_80083DC4(void*, int);
int fn_8021E9A4(void*);
int fn_8011AB30(void*);
int fn_80127A90(void*);
int fn_80119F24(It*, void*);
extern int lbl_804CB7A8;
#if TARGET_PC
FE10_PROTO void fn_80222A58(void*, ptr32<const void>, ptr32<const void>);
#else
void fn_80222A58(void*, void*, void*);
#endif
void* fn_8011A158(void*);
int fn_8012C9BC(void*, void*);
int fn_8012BD30(void*, void*);
void fn_8012A80C(void*, int);
extern u8 lbl_803CAB38[];
int fn_80060754(void*);
void* fn_801059B0(void);
int fn_80105328(void*, void*);
void fn_801053DC(void*, int);
extern int lbl_804CAA70;
extern u8* lbl_804CB810;
struct WM { u8 p[0xa]; s16 xa, xc; u8 p2[0x3e]; u8 x4c; };
struct W4C { WF w; f32 x40; int x44; It* x48; };
struct Sl { It* x0; u8 x4; u8 x5; };
#define REL(fld) { RObj* r = (RObj*)o->fld; if (r) { if (--r->rc == 0 && r) r->destroy(1); o->fld = 0; } }
struct PQ { u8 p[0x54]; WM* x54; WM* x58; };
void fn_802289EC(PQ* o) {
    WM* w = (WM*)fn_801E5640(o, 0x86, 0);
    if (fn_8021E9A4(w) == 0) {
        {
            s16 q[2];
            s16 y = w->xc;
            q[0] = 0x191;
            q[1] = y;
            fn_801E495C(o, w, q, 0);
        }
        u8* b = lbl_803CA870.x0;
        Sl* s;
        int off;
        It* it;
        int f;
        int i;
        f = 1;
        i = 0;
        off = 0;
        for (; i < 18; i++) {
            s = (Sl*)(b + 0x12c + off);
            if (s && (it = s->x0) != 0 && it->x1f && !(s->x5 & 1)) {
                f = 0;
                break;
            }
            off += 8;
        }
        if (f) {
            {
                s16 q[2];
                s16 y = o->x58->xc;
                q[0] = 0x198;
                q[1] = y;
                fn_801E495C(o, o->x58, q, 0);
            }
            REL(x58);
            fn_80083DC4(o, 6);
        } else {
            fn_80083B78(o);
        }
    }
}
void fn_80227950(PQ* o) {
        u8* w;
    int f;
    int i;
        w = (u8*)fn_801E5640(o, 0x86, 0);
    if (fn_8021E9A4(w) == 0) {
        {
            s16 q[2];
            s16 y = ((WM*)w)->xc;
            q[0] = 0x191;
            q[1] = y;
            fn_801E495C(o, w, q, 0);
        }
        w = lbl_803CA870.x0;
        if ((u8)fn_8011AB30(w + 0x12c) >= 6) {
            f = 1;
        } else {
            f = fn_80127A90(w);
            int d = f - fn_8011B8A4(w + 0x12c);
            if (d < 0) d = 0;
            if (d == 0) {
                f = 1;
            } else {
                f = 1;
                for (i = 0; i < lbl_804CB7A8; i++) {
                    It* t = fn_8010B22C(i);
                    if (t->x1f && fn_80119F24(t, w)) {
                        f = 0;
                        break;
                    }
                }
            }
        }
        if (f) {
            REL(x54);
            {
                s16 q[2];
                s16 y = o->x58->xc;
                q[0] = 0x198;
                q[1] = y;
                fn_801E495C(o, o->x58, q, 0);
            }
            REL(x58);
            fn_80083DC4(o, 6);
        } else {
            fn_80083B78(o);
        }
    }
}
}
