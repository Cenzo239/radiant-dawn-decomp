#include "game/rS_8023FD30/types.h"
/* List window update: smoothed cursor box and input. */
struct Input { u8 pad[0x2D]; u8 a; u8 b; u8 pad2[5]; int has; struct { u8 pad[8]; void* obj; }* cur; };
class Pad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual u32 v3C(); virtual void v40(); virtual void v44(); virtual u32 v48();
};
struct LW;
class LWV {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18(void*);
};
struct LW {
    void* vt;
    u8 pad04[0x12 - 4];
    s16 v12, v14, v16, v18;
    u8 pad1A[4];
    s16 x, y;
    u8 pad22[0x50 - 0x22];
    void* scr;
    u8 v54;
    u8 pad55;
    s16 cursor;
    s16 bx, by;
    s16 top;
    u8 pad5E[2];
    f32 scroll;
    u8 pad64[8];
    int count;
};
extern "C" {
extern u32 lbl_804CB700;
extern Pad* lbl_804CB5B8;
extern char lbl_80372780[];
int fn_8028DB44(int);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7B4(void);
void fn_8007E7E8(int);
int fn_800CB0FC(int, f32);
void fn_800712E8(int, int, int);
void fn_80072ACC(int, int, int, int, int, int, int);
void fn_80253EE4(const char*, f32);
void fn_801E1CC0(void*, s16);
}
static inline s16 gx(LW* w) { return w->bx; }
static inline int gi(LW* w) { return w->bx; }
extern "C" {
void fn_802410C0(LW* w, Input* in) {
    /*P*/
    int tx;
    int cw;
    int bx;
    int on;
    s16 ty;
/*E*/
    ((LWV*)w)->v18(in);
    s16 r = w->cursor - w->top; s16 wd = w->v16 - w->v12; bx = gi(w); tx = w->x; wd = wd - 0x40; int m = r * 0x1E; cw = (s16)(wd + tx); ty = (s16)(m + w->y);
    if (bx == -0x8000 && w->by == -0x8000 || fn_8028DB44(bx - tx) <= 1 && fn_8028DB44(w->by - ty) <= 1) {
        w->bx = tx;
        w->by = ty;
    } else {
        w->bx = (bx + tx + 1) >> 1;
        w->by = (ty + w->by + 1) >> 1;
    }
    if (w->v54 != 0 && w->count != 0) {
        on = 0;
        int t = 0;
        if (in->a != 0 || in->b != 0) {
            t = 1;
        }
        if (t == 0) {
            void* o = in->has ? in->cur->obj : 0;
            if (o == w) {
                on = 1;
            }
        }
        fn_8007E154();
        fn_8007E720(-2.0f);
        fn_8007E164();
        int h = (0x1E - fn_800CB0FC(-1, 1.0f)) >> 1; fn_800712E8(w->bx, w->by + h, on);
        fn_8007E154();
        fn_8007E720(3.0f);
        fn_8007E164();
        fn_80072ACC((cw >> 1) + (tx - w->x), ty + 0xF, cw, 0x17, 0x19, 0x33, on);
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E7E8(0x80);
    fn_8007E164();
}
static inline s16 smin(s16 a, s16 b) { s16 r = b; if (a < b) r = a; return r; }
static inline int imin(int a, int b) { int r = b; if (a < b) r = a; return r; }
static inline int imin2(const s16& a, const s16& b) { if (a < b) return a; return b; }
static inline const s16& rmin(const s16& a, const s16& b) { return a < b ? a : b; }
static inline BOOL inputBlocked() {
    BOOL r = 0;
    u32 a = *(volatile u32*)&lbl_804CB700;
    u32 b = *(volatile u32*)&lbl_804CB700;
    if ((a & 0x10) && !(b & 0x20)) r = 1;
    return r;
}
void fn_802412A8(LW* w) {
    /*P*/
    u32 hold;
    s16 cur;
    s16 v;
    s16 n;
/*E*/
    n = w->count;
    v = 7; if (n < 7) v = n;
    cur = w->cursor;
    if (!inputBlocked()) {
        hold = lbl_804CB5B8->v3C();
        u32 rep = lbl_804CB5B8->v48();
        s16 old = w->cursor;
        if ((s16)(int)w->scroll == 0) {
            if ((hold & 0x00800008)) {
                if (cur == 0) {
                    if ((int)hold == (int)rep) {
                        int d;
                        int k = n - v;
                        int last = n - 1;
                        d = old + last;
                        w->cursor = d;
                        w->top = k > 0 ? k : 0;
                        if ((s16)d > last) {
                            w->cursor = last;
                        }
                    }
                } else {
                    int t; s16 c = old - 1; w->cursor = old - 1; if (c > 0) { t = w->top; if (c - t == 0) {w->scroll = -30.0f; w->top = t - 1;} }
                }
            } else if (hold & 0x00400004) {
                int last = n - 1;
                if (cur == last) {
                    if ((int)hold == (int)rep) {
                        w->cursor = old - last;
                        w->top = 0;
                    }
                } else {
                    w->cursor = old + 1;
                    if (w->cursor > last) {
                        w->cursor = last;
                    }
                    if (w->cursor < last) {
                        if (v - 1 == w->cursor - w->top) {w->scroll = 30.0f; w->top++;}
                    }
                }
            }
        }
        if (old != w->cursor) {
            fn_80253EE4(lbl_80372780 + 0x9A, 0.0f);
        }
    }
    fn_801E1CC0(w->scr, w->top * 0x1E - (int)w->scroll);
}
}
