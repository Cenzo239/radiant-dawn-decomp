#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* movie/picture list window draw */
struct C4 { u8 r, g, b, a; };
struct TexH { u16 x0, x2; };
struct PInfo { s8 id; s8 x1; s8 x2; u8 x3; s8 x4; u8 pad[7]; const char* xC; };
struct LNode { LNode* prev; LNode* next; PInfo* val; };
struct PList { u32 x0; LNode s; };
typedef struct LData { void* arch; u8 p4[4]; const char** x8; const char** xC; const char** x10; u8 p14[4]; PList* list; int x1C; int x20; int x24; u8 p28[0x14]; int x3C; } LData;
struct N3 { const char* a[3]; };
struct I0 { LNode* n; }; struct It { I0 i; };
extern LData* lbl_804CB9BC;
extern const f32 lbl_804CF21C, lbl_804CF218;
extern u8 lbl_803CAB38[];
extern const N3 lbl_8036DCC0;
extern s8 lbl_804CB9CC;
extern u16 lbl_804CB9D0[4];
extern void fn_801B00A8(void* p, void* arg);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void* fn_80006A0C(void*, int);
extern const u8* fn_800CD204(int);
extern void fn_801BC88C(void* a, int b, C4* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern const char* fn_800D0864(const char*);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(int, int);
extern void fn_8007E7B4(void);
extern void fn_8007E74C(void (*)(void*, void*), u16*);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080308(void);
extern void fn_80075124(int, int, int, int);
extern void fn_80074EB4(int, int, int, int);

static inline TexH* TexOf(int tile) { return *(TexH**)fn_80006A0C(lbl_804CB9BC->arch, tile); }
#define Fix(tile, fl, xi, yi, W, H) do { \
    f32 fx_; f32 fy_; fy_ = yi; \
    fx_ = xi; \
    C4 t_; \
    C4 c_; \
    const u8* p_ = fn_800CD204(1); \
    c_.r = p_[0]; c_.g = p_[1]; c_.b = p_[2]; c_.a = 0xFF; \
    TexH** q_ = (TexH**)fn_80006A0C(lbl_804CB9BC->arch, tile); \
    { u16 tw = (*q_)->x2, th = (*q_)->x0; *(u32*)&t_ = *(u32*)&c_; fn_801BC88C(lbl_804CB9BC->arch, tile, &t_, 0x11, fl, fx_, fy_, fx_ + W, fy_ + H, 0.0f, 0.0f, tw, th); } \
} while (0)
#define Auto(tile, fl, xi, yi, W, H) do { \
    f32 fx_; f32 fy_; fy_ = yi; \
    fx_ = xi; \
    C4 c_; \
    C4 t_; \
    TexH** q_ = (TexH**)fn_80006A0C(lbl_804CB9BC->arch, tile); \
    W = (*q_)->x2; \
    H = (*q_)->x0; \
    const u8* p_ = fn_800CD204(1); \
    c_.r = p_[0]; c_.g = p_[1]; c_.b = p_[2]; c_.a = 0xFF; \
    q_ = (TexH**)fn_80006A0C(lbl_804CB9BC->arch, tile); \
    { u16 tw = (*q_)->x2, th = (*q_)->x0; *(u32*)&t_ = *(u32*)&c_; fn_801BC88C(lbl_804CB9BC->arch, tile, &t_, 0x11, fl, fx_, fy_, fx_ + W, fy_ + H, 0.0f, 0.0f, tw, th); } \
} while (0)
static inline u32 Lk(u32* w, u32 k) {
    while (k >= 32) { k -= 32; w++; }
    return *w & (1 << k);
}
static inline int Dist(LNode* a, LNode* b) { int n = 0; while (a != b) { a = a->next; n++; } return n; }
#define FIND_(N,P,F) static inline int P(PInfo* p, s8 v) { int ok = 0; if (p->id >= 0 && v == p->F) ok = 1; return ok; } \
 static inline It N(LNode* first, LNode* last, LNode* it) { s8 v = it->val->F; while (first != last && !P(first->val, v)) first = first->next; It r; r.i.n = first; return r; }
FIND_(F2,P2,x2) FIND_(F1,P1,x1) FIND_(F4,P4,x4)

static inline void Rows(int bx) {
    It found;
/*P*/
    LNode* it;
    int y;
    int x;
    int n;
    int row;
    LNode* e0;
    const char* s;
/*E*/
    PList* l;
    n = lbl_804CB9BC->x3C / 32;
    l = lbl_804CB9BC->list;
    it = l->s.next;
    e0 = &l->s;
    {
    int k2 = n;
    if (n >= 0) {
        for (; k2 > 0; k2--) it = it->next;
    } else {
        for (; k2 < 0; k2++) it = it->prev;
    }
    }
    for (row = 0; row < 9; row++) {
        if (it == e0) break;
        {
        LData* d = lbl_804CB9BC;
        int mode; LNode* end; LNode* beg;
        x = d->x1C + 0xF5;
        beg = d->list->s.next;
        end = &d->list->s;
        mode = d->x24;
        y = row * 0x20 + d->x20 + 0x22 - d->x3C % 32;
        switch (mode) {
        case 0: found = F2(beg,end,it); break;
        case 1: found = F1(beg,end,it); break;
        case 2: found = F4(beg,end,it); break;
        }
        if (n == Dist(beg, found.i.n)) {
            switch (mode) {
            case 0: s = fn_800D0864(d->x8[it->val->x2]); break;
            case 1: s = fn_800D0864(d->xC[it->val->x1]); break;
            case 2: s = fn_800D0864(d->x10[it->val->x4]); break;
            }
            fn_80075124(bx + 0x18, y - 2, 0x70, 0x1C);
            fn_801BCA94();
            fn_800CB3A8(1.0f, 0.0f, bx + 0x50 - fn_800CA3DC(s, -1, 1.0f) / 2, y, 0x34, 1, 0, s);
        }
        fn_80074EB4(x, y + 0x12, 0x123, 0x80);
        fn_801BCA5C(-1.0f);
        s = fn_800D0864(it->val->xC);
        {
        u8 c;
        if (Lk((u32*)(lbl_803CAB38 + 0xDC), it->val->id) == 0) c = 0;
        else c = Lk((u32*)(lbl_803CAB38 + 0xF0), it->val->id) ? 1 : 0x14;
        fn_800CB3A8(1.0f, 0.0f, x + 8, y, c, 1, 0, s);
        }
        fn_801BCA5C(1.0f);
        }
        it = it->next; n++;
    }
}
#pragma use_lmw_stmw off
void fn_801B2150(void) {
/*P*/
    int by;
    int xx;
    int yy;
    int h2;
    int w2;
    int x;
    int y;
    int col;
    int i;
    u16 w;
    int bx;
    u16 h;
    const char* s;
/*E*/
    fn_801BCA5C(-1.0f);
    {
    N3 names = lbl_8036DCC0;
    for (i = 0; i < 3; i++) {
        LData* d = lbl_804CB9BC;
        f32 f;
        x = d->x1C;
        y = i * 0x1C + d->x20 + 10;
        if (d->x24 == i) { f = 2.0f; col = 0x35; } else { f = 0.0f; col = 0; }
        fn_801BCA5C(-(1.4f - 0.2f * i) - f);
        Auto(1, 0, x, y, w, h);
        fn_801BCA5C(-0.1f);
        fn_801BCA94();
        {
        s = fn_800D0864(names.a[i]);
        fn_800CB3A8(1.0f, 0.0f, x + 0x34 - fn_800CA3DC(s, -1, 1.0f) / 2, y + 4, col, 1, 0, s);
        }
        fn_801BCA5C(0.1f + ((1.4f - 0.2f * i) + f));
    }
    }
    {
    bx = lbl_804CB9BC->x1C + 0x61;
    by = lbl_804CB9BC->x20;
    {
    w2 = 0x72;
    h2 = 0x104;
    fn_801BCA5C(-1.0f);
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(bx, by + 0xC, 458.0f, 291.0f);
    fn_800804D4(0x35, 0x2D, 0x23, 0xFF);
    fn_80080308();
    fn_801BCA5C(-1.0f);
    Auto(6, 0, bx, by, w, h);
    Auto(7, 0, bx, by + 0x12F, w, h);
    Fix(8, 0, bx, by + 0xC, lbl_804CF21C, lbl_804CF218);
    Fix(8, 0, bx + 0x1CA, by + 0xC, lbl_804CF21C, lbl_804CF218);
    {
    xx = bx + 0xF;
    yy = by + 0x14;
    Auto(2, 0, xx, yy, w, h);
    Fix(3, 0, xx + 8, yy, w2, lbl_804CF21C);
    Auto(2, 1, xx + 0x7A, yy, w, h);
    Fix(4, 0, xx, yy + 8, lbl_804CF21C, h2);
    Fix(5, 0, xx + 8, yy + 8, w2, h2);
    Fix(4, 1, xx + 0x7A, yy + 8, lbl_804CF21C, h2);
    Auto(2, 2, xx, yy + 0x10C, w, h);
    Fix(3, 2, xx + 8, yy + 0x10C, w2, lbl_804CF21C);
    Auto(2, 3, xx + 0x7A, yy + 0x10C, w, h);
    }
    fn_801BCA5C(-1.0f);
    fn_801BCA5C(-2.0f);
    if (!lbl_804CB9CC) lbl_804CB9CC = 1;
    lbl_804CB9D0[0] = bx; lbl_804CB9D0[1] = by + 0x20; lbl_804CB9D0[2] = 0x1C0; lbl_804CB9D0[3] = 0x100;
    fn_8007E154();
    fn_8007E74C(fn_801B00A8, lbl_804CB9D0);
    fn_8007E164();
    Rows(bx);
    }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_801BCA5C(6.0f);
}
}
