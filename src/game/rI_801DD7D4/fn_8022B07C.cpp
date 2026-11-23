#include "game/rI_801DD7D4/types.h"
extern "C" {
#pragma pool_strings on
#if TARGET_PC
FE10_PROTO const char* fn_8022B6DC(ptr32<const void>, int, int);
#else
const char* fn_8022B6DC(void*, int, int);
#endif
void fn_80253EE4(const char*, f32);
struct VI { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual u32 v3c(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern VI* lbl_804CB5B8;
struct VT { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3c(); virtual int v40(); virtual int v44(); };
struct VT2 { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual int v2c(); virtual int v30(); virtual int v34(); };
#if TARGET_PC
FE10_PROTO int fn_8022B620(ptr32<const void>);
#else
int fn_8022B620(void*);
#endif
#if TARGET_PC
FE10_PROTO int fn_8022B6A0(ptr32<const void>);
#else
int fn_8022B6A0(void*);
#endif
extern s16 lbl_804CAA78[4];
struct TW { u8 p[0xa]; s16 x0a, x0c, x0e, x10, x12, x14, x16, x18, x1a, x1c, x1e, x20; u8 p2[0x1e]; void* x40; s16 x44, x46, x48; };
static inline const s16& mn(const s16& a, const s16& b) { return b < a ? b : a; }
static inline void teSet(TW* o, s16 w, s16 h) {
    o->x0e = o->x0a + w;
    o->x10 = o->x0c + h;
    o->x12 = 0;
    o->x14 = 0;
    o->x16 = w;
    o->x18 = h;
}
void fn_8022A6E4(TW* o) {
    s16 w;
    s16 n = fn_8022B620(o->x40);
    int m = fn_8022B6A0(o->x40);
    o->x44 = n;
    o->x46 = mn(lbl_804CAA78[0], n);
    o->x48 = m;
    w = o->x48 * ((VT2*)o)->v30();
    teSet(o, w, o->x46 * ((VT2*)o)->v34());
}

struct TB { u8 p[0x40]; void* x40; s16 x44, x46, x48, x4a, x4c, x4e, x50, x52; u8 p2[8]; f32 x5c; };
static inline int flg(u32 v, u32 m) { return v & m; }
const char* dummy1() { return "MH_BCHAR"; }
void fn_8022B07C(TB* o) {
    if (inputBlocked()) return;
    u32 press;
    u32 rep;
    int ox;
    int oy;
    int oz;
    press = lbl_804CB5B8->v3c();
    rep = lbl_804CB5B8->v48();
    ox = o->x4c;
    oy = o->x4e;
    oz = o->x4a;
    if (flg(press, 0x100001)) {
        o->x4c = ox - 1;
        if ((s16)(ox - 1) < 0) {
            o->x4c = rep == press ? (s16)((VT*)o)->v40() - 1 : (s16)(o->x4c += 1);
        }
        int done = 0;
        s8 dir = -1;
        while (done == 0) {
            const char* c = fn_8022B6DC(o->x40, o->x4c, o->x4e);
            switch (*c) {
            case 10:
                if (rep == press) {
                    o->x4c = ((VT*)o)->v40() - dir - 1;
                } else {
                    dir = dir - dir * 2;
                }
                break;
            case 9:
                break;
            default:
                done = 1;
                break;
            }
            o->x4c += done == 0 ? dir : 0;
        }
    } else if (flg(press, 0x200002)) {
        s16 n = ((VT*)o)->v40();
        o->x4c = o->x4c + 1;
        if ((s16)o->x4c >= n) {
            o->x4c = rep == press ? 0 : (s16)(o->x4c -= 1);
        }
        int done = 0;
        s8 dir = 1;
        while (done == 0) {
            const char* c = fn_8022B6DC(o->x40, o->x4c, o->x4e);
            switch (*c) {
            case 10:
                if (rep == press) {
                    o->x4c = -dir;
                } else {
                    dir = dir - dir * 2;
                }
                break;
            case 9:
                break;
            default:
                done = 1;
                break;
            }
            o->x4c += done == 0 ? dir : 0;
        }
    }
    if (flg(press, 0x800008)) {
        if (o->x4e == 0) {
            if (press == rep) {
                o->x4e = ((VT*)o)->v44() - 1;
                o->x4a = (s16)((VT*)o)->v3c() < (s16)((VT*)o)->v44() ? (s16)((VT*)o)->v44() - (s16)((VT*)o)->v3c() : 0;
            }
        } else {
            s16 y = o->x4e - 1;
            o->x4e = y;
            if (y > 0 && y - o->x4a == 0) {
                o->x4a = o->x4a - 1;
                o->x5c = (f32)-(s16)((VT*)o)->v34();
            }
        }
    } else if (flg(press, 0x400004)) {
        s16 n = ((VT*)o)->v44();
        if (o->x4e == n - 1) {
            if (press == rep) {
                o->x4a = 0;
                o->x4e = 0;
            }
        } else {
            o->x4e = o->x4e + 1;
            if (o->x4e < (s16)((VT*)o)->v44() - 1) {
                int k = (s16)((VT*)o)->v3c() - 1;
                int z = o->x4a;
                int d = o->x4e - z;
                if (d == k) {
                    o->x4a = z + 1;
                    o->x5c = (f32)(s16)((VT*)o)->v34();
                }
            }
        }
    }
    {
        int done = 0;
        s8 dir = -1;
        while (done == 0) {
            const char* c = fn_8022B6DC(o->x40, o->x4c, o->x4e);
            switch (*c) {
            case 10:
                dir = dir - dir * 2;
                break;
            case 9:
                break;
            default:
                done = 1;
                break;
            }
            o->x4c += done == 0 ? dir : 0;
        }
    }
    if (ox != o->x4c || oy != o->x4e || oz != o->x4a) {
        fn_80253EE4("SFX_SYS_NAME_WINDOW_MOVE2", 0.0f);
    }
}
}
