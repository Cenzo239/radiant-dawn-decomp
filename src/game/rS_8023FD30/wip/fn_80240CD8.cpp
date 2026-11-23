#include "game/rS_8023FD30/types.h"
/* List window draw. */
class Obj { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(void*); };
struct LN { LN* prev; LN* next; Obj* val; };
typedef void (Obj::*MF)(void*);
struct Fn { MF f; void* arg; Fn(MF m, void* a) { f = m; arg = a; } };
struct RectS { s16 a, b, c, d; };
struct Scr { u8 pad[0x40]; s16 a40, a42, a44; };
struct LW;
class LWV {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(void*); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(int, s16, void*); virtual void v38();
};
struct LW {
    void* vt;
    u8 pad04[0x12 - 4];
    s16 v12, v14, v16, v18;
    u8 pad1A[4];
    s16 x, y;
    u8 pad22[0x44 - 0x22];
    LN* cprev;
    LN* cnext;
    u8 pad4C[4];
    Scr* scr;
    u8 v54;
    u8 pad55;
    s16 cursor;
    s16 bx, by;
    s16 top;
    u8 pad5E[2];
    f32 scroll;
    RectS rect;
    u32 count;
    LN* last;
    LN* first;
};
extern "C" {
void fn_801E2204(LW*, void*, void*);
void fn_801E2104(void* p, void* arg);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E74C(void (*)(void*, void*), void*);
void fn_8007E7B4(void);
}
static inline LN* adv(LN* it, const int& n) { s16 k = n; if ((s16)n >= 0) { for (; k > 0; k--) it = it->next; } else { for (; k < 0; k++) it = it->prev; } return it; }
static inline int gtop(LW* w) { return w->top; }
static inline void setR(Scr* s, s16 a, s16 b, s16 c) { s->a40 = a; s->a42 = b; s->a44 = c; }
static inline int sgn(s16 v) { return v < 0 ? -1 : v > 0; }
typedef struct FnT { MF f; void* arg; } FnT;
static inline FnT forEach(LN* n, LN* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
    return f;
}
extern MF lbl_80390EE8;
extern "C" {
void fn_80240CD8(LW* w, void* in) {
    /*P*/
    int off;
    LN* it;
    int i;
    int yy;
    int x;
    int top;
    int end;
/*E*/
    ((LWV*)w)->v38();
    ((LWV*)w)->v18(in);
    s16 hh = w->v18 - w->v14;
    s16 ww = w->v16 - w->v12;
    w->rect.a = 0;
    w->rect.b = 0;
    w->rect.c = ww;
    w->rect.d = hh;
    fn_801E2204(w, &w->rect, &w->rect);
    fn_801E2204(w, &w->rect.c, &w->rect.c);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E74C(fn_801E2104, &w->rect);
    fn_8007E164();
    off = (int)((const LW*)w)->scroll;
    top = gtop(w);
    if (w->scroll < 0.0f) {
        w->scroll += 7.5f;
        if (w->scroll >= -0.00000011920929f) w->scroll = 0.0f;
    } else if (w->scroll > 0.0f) {
        w->scroll -= 7.5f;
        if (w->scroll <= 0.00000011920929f) w->scroll = 0.0f;
    }
    s16 sg = sgn(off); if (sg > 0 && top >= 0) top = (s16)(top - 1);
    it = adv(w->first, (s16)top);
    i = (-sg & ~sg) >> 31; end = (s16)(7 + ((u32)sg >> 31));
    x = w->x;
    yy = (s16)off + i * 0x1E;
    for (; (s16)i < end; i++) {
        if ((s16)top >= w->count) break;
        ((LWV*)w)->v34(x, yy + w->y, it->val);
        it = it->next;
        yy += 0x1E;
        top++;
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    setR(w->scr, w->count * 0x1E, 0xD2, w->top * 0x1E - off);
    {
        FnT f;
        f.f = lbl_80390EE8;
        f.arg = in;
        forEach(w->cnext, (LN*)&w->cprev, f);
    }
}
}
