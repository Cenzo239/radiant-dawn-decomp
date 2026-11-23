#include "game/rB_8002E1C4/types.h"

/* Second gradient palette process (lbl_803794A0). */
struct Col {
    u8 r, g, b, a;
    Col& operator=(const Col& o) { r = o.r; g = o.g; b = o.b; a = o.a; return *this; }
};
struct PalProc {
    u8 pad[0x30];
    s16 mode;
    Col* tbl;
    int x38, x3c, x40, x44, x48, x4c;
    bool x50;
};
extern u8 lbl_803794A0[];
extern "C" {
PalProc* fn_80083B84(void* cls);
#if TARGET_PC
FE10_PROTO PalProc* fn_80081050(void* cls, p32arg);
#else
PalProc* fn_80081050(void* cls, int k);
#endif

static inline void build(PalProc* p) {
    switch (p->mode) {
    case 0:
        for (int i = 0; i < 16; i++) {
            p->tbl[i].r = 0xff;
            p->tbl[i].g = i * 14;
            p->tbl[i].b = i * 8;
            p->tbl[i].a = 0xff;
            Col* d = &p->tbl[31 - i]; Col* s = &p->tbl[i]; *d = *s;
        }
        break;
    case 1:
        for (int i = 0; i < 16; i++) {
            p->tbl[i].r = 0x40;
            p->tbl[i].g = i * 4 + 0x80;
            p->tbl[i].b = 0x80;
            p->tbl[i].a = 0xff;
            Col* d = &p->tbl[31 - i]; Col* s = &p->tbl[i]; *d = *s;
        }
        break;
    }
}

static inline void setup(PalProc* p, int a, int b, int c, int d, int e, int f, void* g, int m) {
    p->x38 = a;
    p->x3c = b;
    p->x40 = c;
    p->x44 = d;
    p->x48 = e;
    p->x4c = f;
    p->x50 = g != 0;
    p->mode = m;
}
#pragma use_lmw_stmw on
int fn_80038D38(int a, int b, int c, int d, int e, int f, void* g) {
    if (fn_80083B84(lbl_803794A0)) {
        PalProc* p = fn_80083B84(lbl_803794A0);
        setup(p, a, b, c, d, e, f, g, 0);
        if (p->tbl) build(p);
    } else {
        PalProc* p = fn_80081050(lbl_803794A0, 3);
        setup(p, a, b, c, d, e, f, g, 0);
        p->tbl = 0;
    }
    return 0;
}
#pragma use_lmw_stmw reset
}
