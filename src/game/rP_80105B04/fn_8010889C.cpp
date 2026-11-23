#include "game/rP_80105B04/rp.h"

/* Packed record, likely a set of per-stat shift registers, cleared by chained
   bitfield assignment (each field reads back the previous one). */
struct Hist {
    u16 f4 : 3;
    u16 f3 : 3;
    u16 f2 : 3;
    u16 f1 : 3;
    u16 f0 : 3;
    u16 lock : 1;
    u16 g3 : 2;
    u16 g2 : 2;
    u16 g1 : 2;
    u16 g0 : 2;
    u16 h1 : 3;
    u16 h0 : 3;
    u16 lo : 2;
};
struct Side { u8 pad[8]; u8 idx; };
struct UnitA { u8 pad[0xF4]; Side* side; };
struct Game { u8 pad[0x11]; u8 side; };
static inline int Count(Hist* h) {
    int n = 0;
    if (h->f4) n++;
    if (h->f2) n++;
    if (h->f1) n++;
    if (h->f3) n++;
    if (h->f0) n++;
    if (h->lock) n++;
    return n;
}
extern "C" {
void fn_80108E20(Hist* h, int mode);
extern Game lbl_803CAB38;

static inline void Reset(Hist* h) {
    h->f0 = 0;
    h->f1 = h->f0;
    h->f2 = h->f1;
    h->f3 = h->f2;
    h->f4 = h->f3;
    h->g0 = 0;
    h->g1 = h->g0;
    h->g2 = h->g1;
    h->g3 = h->g2;
}
static inline u8 Adj(UnitA* u, u8 v) {
    Game* g = &lbl_803CAB38;
    if (g->side != u->side->idx) v++;
    return v;
}
void fn_80108830(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    v = Adj(u, v);
    Reset(h);
    h->f4 = v;
}
void fn_801088DC(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    v = Adj(u, v);
    Reset(h);
    h->f2 = v;
}
void fn_80108948(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    v = Adj(u, v);
    Reset(h);
    h->f1 = v;
}
void fn_801089B4(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    v = Adj(u, v);
    Reset(h);
    h->f3 = v;
}
void fn_80108A20(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    v = Adj(u, v);
    Reset(h);
    h->f0 = v;
}
void fn_80108AD0(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    v = Adj(u, v);
    Reset(h);
    h->g3 = v;
}
void fn_80108B3C(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    v = Adj(u, v);
    Reset(h);
    h->g2 = v;
}
void fn_80108BA8(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    v = Adj(u, v);
    Reset(h);
    h->g1 = v;
}
void fn_80108C14(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    v = Adj(u, v);
    Reset(h);
    h->g0 = v;
}
void fn_8010889C(Hist* h) {
    if (h->lock) return;
    Reset(h);
}
void fn_80108A8C(Hist* h, UnitA* u, int v) {
    if (h->lock) return;
    Reset(h);
    h->lock = v;
}
void fn_80108C80(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    h->h1 = Adj(u, v);
}
void fn_80108CC0(Hist* h, UnitA* u, u8 v) {
    if (h->lock) return;
    h->h0 = Adj(u, v);
}

int fn_80108D00(Hist* h, int mode) {
    Hist t;
    if (Count(h) == 0) return 0;
    t = *h;
    fn_80108E20(&t, mode);
    if (Count(&t) == 0) return 1;
    return 0;
}
void fn_80108E20(Hist* h, int mode) {
    switch (mode) {
    case 0:
        break;
    case 1:
        if (h->f4) h->f4--;
        if (h->f2) h->f2--;
        if (h->f1) h->f1--;
        if (h->f3) h->f3--;
        if (h->f0) h->f0--;
        if (h->g3) h->g3--;
        if (h->g2) h->g2--;
        if (h->g1) h->g1--;
        if (h->g0) h->g0--;
        if (h->h1) h->h1--;
        if (h->h0) h->h0--;
        break;
    }
}
int fn_80108F68(Hist* h);
void fn_80109078(Hist* h) {
    h->f4 = 0;
    h->f2 = 0;
    h->f1 = 0;
    h->f3 = 0;
    h->f0 = 0;
    h->lock = 0;
    h->g3 = 0;
    h->g2 = 0;
    h->g1 = 0;
    h->g0 = 0;
    h->h1 = 0;
    h->h0 = 0;
}
void fn_80109094(Hist* h, u32 i, int v) {
    switch (i) {
    case 0: h->f4 = v; break;
    case 2: h->f2 = v; break;
    case 3: h->f1 = v; break;
    case 4: h->f3 = v; break;
    case 5: h->f0 = v; break;
    case 6: h->lock = v; break;
    case 15: h->g3 = v; break;
    case 16: h->g2 = v; break;
    case 17: h->g1 = v; break;
    case 18: h->g0 = v; break;
    case 19: h->h1 = v; break;
    case 20: h->h0 = v; break;
    }
}
int fn_80109174(Hist* h) {
    return Count(h);
}
int fn_801091E0(Hist* h, int i) {
    int n = 0;
    if (h->f4) n++;
    if (i + 1 == n) return 0x1A;
    if (h->f2) n++;
    if (i + 1 == n) return 0x1B;
    if (h->f1) n++;
    if (i + 1 == n) return 0x1C;
    if (h->f3) n++;
    if (i + 1 == n) return 0x1D;
    if (h->f0) n++;
    if (i + 1 == n) return 0x1E;
    if (h->lock) n++;
    if (i + 1 == n) return 0x1F;
    return 0;
}
int fn_801092C4(Hist* h);
int fn_8010931C(Hist* h) {
    if (h->f2) return 1;
    if (h->f0) return 1;
    return h->lock;
}
int fn_80109348(Hist* h) {
    if (h->f2) return 1;
    if (h->f3) return 1;
    if (h->f0) return 1;
    return h->lock;
}
int fn_80109384(Hist* h) {
    if (h->f2) return 1;
    if (h->f0) return 1;
    return h->lock;
}
int fn_801093B0(Hist* h) {
    if (h->f2) return 1;
    if (h->f1) return 1;
    if (h->f0) return 1;
    return h->lock;
}
int fn_80109014(Hist* h);
}
