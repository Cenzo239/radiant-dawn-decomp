/* Archive/file entry manager: DVD read callback. Reads the rest of the file in chunks of at most
   lbl_804CAA98 bytes and posts a "loaded" message to the loader thread when done. */
#include "game/rI_801DD7D4/fn_fe.h"
extern "C" {
extern u32 lbl_804CAA98;
extern int lbl_804CAAA0;
extern int lbl_804CAAA4;
struct FI { u8 p[0x2c]; FE* user; };
struct Msg { s8 type; u8 p1[3]; FE* e; int a8; };
int fn_802F6BA8(FI*, u32, u32, u32, void*, int);
u32 fn_802F6DC0(FI*);
void fn_802F69C4(FI*);
int fn_8031D34C(void*, void*, int);
int fn_8031D284(void*, void*, int);
}
static inline u32 maxRead() { return lbl_804CAA98; }
static inline u32 rem(FE* e) { return e->size - e->pos; }
static inline u32 rem2(FE* e) { u32 s = e->size; s -= e->pos; return s; }
static inline u32 rem3(const u32& a, const u32& b) { return a - b; }
static inline u32 const& mn2(u32 const& a, u32 const& b) { return a < b ? a : b; }
static inline u32 const& mn(u32 const& a, u32 const& b) { return b < a ? b : a; }
static inline int const& mx(int const& a, int const& b) { return a < b ? b : a; }
extern "C" void fn_8023BB70(int res, FI* fi);
static inline void rd(FI* fi, u32 a, u32 n, u32 o, int p) { fn_802F6BA8(fi, a, n, o, fn_8023BB70, p); }
static inline void rd2(FI* fi, FE* e, u32 n, const int& l) { fn_802F6BA8(fi, e->data + e->pos, n, e->pos, fn_8023BB70, mx(l, e->a56 - 1)); }
static inline void rd3(FI* fi, FE* e, u32 n, int l) { fn_802F6BA8(fi, e->data + e->pos, n, e->pos, fn_8023BB70, mx(l, e->a56 - 1)); }
static inline void rd4(FI* fi, u32 a, u32 n, FE* e, const int& l) { fn_802F6BA8(fi, a, n, e->pos, fn_8023BB70, mx(l, e->a56 - 1)); }
static inline void post(FE* e, int res) {
    Msg* m;
    fn_8031D34C(sQ2, &m, 1);
    m->type = 0;
    m->e = e;
    m->a8 = res;
    fn_8031D284(sQ1, m, 1);
}
static inline int const& mxW(int const& a, int const& b) { return mx(a, b); }
static inline void rd4w(FI* fi, u32 a, u32 n, FE* e, const int& l) { fn_802F6BA8(fi, a, n, e->pos, fn_8023BB70, mxW(l, e->a56 - 1)); }
static inline void rd4x(FI* fi, u32 a, u32 n, FE* e, const int& l) { rd4(fi, a, n, e, l); }
static inline u32 const& mnW(u32 const& a, u32 const& b) { return mn(a, b); }
static inline void c2(FI* fi, FE* e) { rd4(fi, e->data + e->pos, (mn(e->size - e->pos, maxRead()) + 0x1f) & ~0x1f, e, lbl_804CAAA4); }
static inline void c2w(FI* fi, FE* e) { rd4w(fi, e->data + e->pos, (mn(e->size - e->pos, maxRead()) + 0x1f) & ~0x1f, e, lbl_804CAAA4); }
static inline void c2m(FI* fi, FE* e) { rd4(fi, e->data + e->pos, (mnW(rem2(e), maxRead()) + 0x1f) & ~0x1f, e, lbl_804CAAA4); }
static inline void c2x(FI* fi, FE* e) { rd4x(fi, e->data + e->pos, (mn(e->size - e->pos, maxRead()) + 0x1f) & ~0x1f, e, lbl_804CAAA4); }
static inline void c2c(FI* fi, FE* e) { c2(fi, e); }
static inline void postW(FE* e, int res) { post(e, res); }
static inline void c1(FI* fi, FE* e, u32 const& n) { rd4(fi, e->data + e->pos, n, e, lbl_804CAAA0); }
extern "C" {
void fn_8023BB70(int res, FI* fi) {
    FE* e = fi->user;
    if (res == -3) {
        e->flags |= 0x10000;
    } else if (res < 0) {
        e->flags |= 0x20000;
        if (res == -1) return;
        u32 n = (rem2(e) + 0x1f) & ~0x1f;
        if (e->flags & 0x800) n = (mn(n, maxRead()) + 0x1f) & ~0x1f;
        rd4(fi, e->data + e->pos, n, e, lbl_804CAAA0);
        return;
    } else {
        e->pos += fn_802F6DC0(fi);
        if (e->pos < e->size) {
            c2m(fi, e);
            return;
        }
        postW(e, res);
    }
    fn_802F69C4(fi);
}
}
