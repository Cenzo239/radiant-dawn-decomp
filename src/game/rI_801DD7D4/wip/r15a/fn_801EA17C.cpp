#include "game/rI_801DD7D4/types.h"
extern "C" {
void fn_80253EE4(void*, f32);
extern u8 lbl_8036EF08[];
}
class Pad { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual int v3C(); virtual void v40(); virtual void v44(); virtual int v48(); };
extern "C" Pad* lbl_804CB5B8;
struct Row { int x0; u8 p[0x24]; };
struct D { u8 p[0x1bc]; Row rows[7]; };
struct O { u8 p[0x50]; s16 cur; u8 p2[0xa]; D* d; int mode; };
static inline int flg(int e, u32 m) { return e & m; }
static inline int gc(O* o) { return o->cur; }
static inline BOOL en(O* o, s16 i) {
    BOOL t = 0;
    u8* r = (u8*)o->d->rows;
    if (*(int*)(r + i * 0x28) == 0) {
        if (o->mode == 1 && (i == 0 || *(int*)((u8*)o->d->rows + (i - 1) * 0x28) != 0)) t = 1;
    } else {
        t = 1;
    }
    return t;
}
static inline s16 prv(O* o, s16 s) {
    s16 i = s; s16 res = -1;
    for (; i >= 0; i--) {
        if (en(o, i)) { res = i; break; }
    }
    return res;
}
static inline s16 nxt(O* o, s16 s) {
    s16 i = s; s16 res = -1;
    if (i < 0) i = 0;
    for (; i < 7; i++) {
        if (en(o, i)) { res = i; break; }
    }
    return res;
}
extern "C" void fn_801EA17C(O* o) {
    if (inputBlocked()) return;
    int e = lbl_804CB5B8->v3C();
    int r = lbl_804CB5B8->v48();
    s16 cur = o->cur;
    s16 n = cur;
    if (flg(e, 0x800008)) {
        n = prv(o, cur - 1);
        if (n < 0) {
            if (flg(r, 0x800008)) {
                n = prv(o, 6);
            } else {
                n = cur;
            }
        }
    } else if (flg(e, 0x400004)) {
        n = nxt(o, cur + 1);
        if (n < 0) {
            if (flg(r, 0x400004)) {
                n = nxt(o, 0);
            } else {
                n = cur;
            }
        }
    }
    if ((s16)cur != (s16)n) {
        o->cur = n;
        fn_80253EE4(lbl_8036EF08, 0.0f);
    }
}
