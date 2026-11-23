/* fn_80223CF4: draw of a scrolling multi-column list (std::list of entries, `cols` per row): eases the
   scroll offset to 0, advances the iterator to the first visible entry, draws every visible cell through
   v50/v54, updates the scroll bar child and then forwards the draw to every child widget
   (std::for_each with a bound member function). Same body as fn_801E7E1C with the fields 4 bytes later.
   `__ptmf_scall` is fn_8028C178 (helper name, not in symbols.txt). Round m15. */
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E74C(void*, void*);
void fn_8007E7B4(void);
u32* fn_801E2204(void*, s16*, s16*);
void fn_801E2104(void* p, void* arg);
}
typedef struct LN { struct LN* prev; struct LN* next; int val; } LN;
typedef void (RObj::*MF)(void*);
typedef struct FnT { MF f; void* arg; } FnT;
extern "C" MF lbl_8038FEA8;
struct Child { u8 pad[0x40]; s16 x40, x42, x44; };
class GL { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C();
    virtual int v50(int); virtual int v54(int, int, int, int, int); virtual int v58(); virtual int v5C();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; void* parent; int a40; LNode* a44; LNode* a48; Child* a4c; u8 p50[0xe]; s16 top; s16 cols; s16 rowH;
    f32 scroll; s16 sc; s16 r0, r1, r2, r3; u8 p72[2]; u32 count; LN* lprev; LN* lnext;
};
static inline void setR(GL* o, s16 a, s16 b, s16 c, s16 d) { o->r0 = a; o->r1 = b; o->r2 = c; o->r3 = d; }
static inline void setC(Child* k, s16 a, s16 b, s16 c) { k->x40 = a; k->x42 = b; k->x44 = c; }
static inline LN* adv(LN* it, s16 n) {
    if (n >= 0) {
        for (; n > 0; n--) it = it->next;
    } else {
        for (; n < 0; n++) it = it->prev;
    }
    return it;
}
static inline int sgn(s16 v) { if (v < 0) return -1; return v > 0; }
static inline FnT forEach(LNode*& n, LNode* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
    return f;
}
extern "C" void fn_80223CF4(GL* o, void* c) {
    FnT ft;
    s16 cols;
    s16 rowH;
    LNode* sent;
    int cwi;
    int e;
    int t;
    int yo;
    LNode* n;
    int x;
    LN* it;
    s16 idx;
    s16 xx;
    int rows;
    s16 row;
    s16 end;
    s16 y;
    s16 s;
    s16 col;
    o->v5C();
    o->v18(c);
    setR(o, 0, 0, o->ix1 - o->ix0, o->iy1 - o->iy0);
    fn_801E2204(o, &o->r0, &o->r0);
    fn_801E2204(o, &o->r2, &o->r2);
    fn_8007E154();
    fn_8007E74C(fn_801E2104, &o->r0);
    fn_8007E164();
    cols = o->cols;
    rows = o->v4C();
    idx = o->top * o->cols;
    cwi = o->v44();
    rowH = o->rowH;
    t = (int)o->scroll;
    o->sc = t;
    if (o->scroll < 0.0f) {
        o->scroll += rowH / 4.0f;
        if (o->scroll >= -1.1920929e-07f) o->scroll = 0.0f;
    } else if (o->scroll > 0.0f) {
        o->scroll -= rowH / 4.0f;
        if (o->scroll <= 1.1920929e-07f) o->scroll = 0.0f;
    }
    s = sgn((s16)t);
    if (s > 0 && idx - cols >= 0) idx = idx - cols;
    it = adv(o->lnext, idx);
    e = (s16)rows;
    if (s > 0) row = -1; else row = 0;
    if (s < 0) e++;
    yo = row * rowH;
    end = e;
    for (; row < end; row++, yo += rowH) {
        y = o->ty + (t + yo);
        for (col = 0, x = 0; col < cols; col++, idx++) {
            if ((u32)idx >= o->count) goto done;
            xx = x + o->tx;
            o->v54(xx, y, -1, it->val, o->v50(it->val));
            it = it->next;
            x += (s16)cwi;
        }
    }
done:
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_8007E154();
    fn_8007E720(-2.0f);
    fn_8007E164();
    setC(o->a4c, rowH * ((cols + o->count - 1) / cols), rows * rowH, rowH * o->top - t);
    {
        ft.f = lbl_8038FEA8;
        ft.arg = c;
        sent = (LNode*)&o->a44;
        forEach((n = o->a48), sent, ft);
    }
}
