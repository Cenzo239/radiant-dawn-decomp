#include "game/rI_801DD7D4/types.h"
extern "C" {
void* fn_80083B84(void*);
void* fn_801E5640(void*, int, int);
extern u8 lbl_8038FF24[];
struct E5 { u8 p[0x5c]; u8* x5c; };
struct It { u8 p[0x1f]; u8 x1f; };
struct Sl { It* x0; u8 x4; u8 x5; };
int fn_80228E5C(void) {
        u8* b;
    Sl* s;
    int off;
    It* q;
    int f;
    int i;
    b = ((E5*)fn_801E5640(fn_80083B84(lbl_8038FF24), 0x82, 0))->x5c;
    f = 0;
    i = 0;
    off = 0;
    for (; i < 18; i++) {
        s = (Sl*)(b + 0x12c + off);
        if (s && (q = s->x0) != 0 && q->x1f && !(s->x5 & 1)) {
            f = 1;
            break;
        }
        off += 8;
    }
    int r = 2;
    if (f) r = 0;
    return r;
}
int fn_8011AB30(void*);
int fn_80127A90(void*);
int fn_8011B8A4(void*);
It* fn_8010B22C(int);
int fn_80119F24(It*, void*);
extern int lbl_804CB7A8;
struct X4 { u8 p[4]; s8 x4; };
int fn_8022906C(X4* o) {
    int found;
    u8* u;
    int i;
    o->x4 = 0;
    u = ((E5*)fn_801E5640(fn_80083B84(lbl_8038FF24), 0x82, 0))->x5c;
    if ((u8)fn_8011AB30(u + 0x12c) >= 6) {
        o->x4 = -1;
        return 2;
    }
    {
        found = fn_80127A90(u);
        int d = found - fn_8011B8A4(u + 0x12c);
        if (d < 0) d = 0;
        if (d <= 0) {
            o->x4 = -2;
            return 2;
        }
    }
    found = 0;
    for (i = 0; i < lbl_804CB7A8; i++) {
        It* t = fn_8010B22C(i);
        if (t->x1f && fn_80119F24(t, u)) {
            found = 1;
            break;
        }
    }
    if (!found) {
        o->x4 = -3;
        return 2;
    }
    return 0;
}
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void fn_801E4094(void*);
u8 fn_801E7164(void);
static u8 s_t0[0x13c];
static u8 s_t1[0x44];
static u8 s_t2[0x44];
static u8 s_t3[0x44];
static u8 s_t4[0x44];
static u8 s_t5[0x44];
static u8 s_t6[0x44];
struct O4 { u8 p[0x40]; int x40; u8 x44; int x48; int x4c; };
O4* fn_80204348(void* p) {
    O4* o;
    if (p) o = (O4*)fn_80081194(s_t0, p); else o = (O4*)fn_80081050(s_t0, p);
    if (o) {
        fn_801E4094(o);
        o->x40 = 0;
        o->x44 = 0;
        o->x48 = 0;
        o->x4c = 0;
    }
    o->x44 = fn_801E7164();
    switch (o->x44) {
    case 1: o->x48 = (int)s_t1; break;
    case 2: o->x48 = (int)s_t2; break;
    case 3: o->x48 = (int)s_t3; break;
    case 4: o->x48 = (int)s_t4; break;
    case 5: o->x48 = (int)s_t5; break;
    case 6: o->x48 = (int)s_t6; break;
    }
    return o;
}
struct WV { virtual void v08(); virtual const char* v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); };
int fn_800CA3DC(const char*, int, f32);
int fn_800CA7A4(const char*, int, f32);
void fn_801E6DA0(s16, s16, int, const char*, ...);
struct TF { u8 p[0x30]; s16 x30, x32; u8 p2[5]; u8 x39; };
void fn_801FD28C(WV* o, void* a, TF* t) {
    f32 x, y;
    int c;
    o->v50();
    x = t->x30;
    y = t->x32;
    x -= (f32)(fn_800CA3DC(o->v0c(), -1, 1.0f) >> 1);
    y += (f32)((0x20 - fn_800CA7A4(o->v0c(), -1, 1.0f)) >> 1);
    c = 0x1f;
    if (t->x39 == 2) c = 0;
    fn_801E6DA0(x, y, c, o->v0c());
}
}
