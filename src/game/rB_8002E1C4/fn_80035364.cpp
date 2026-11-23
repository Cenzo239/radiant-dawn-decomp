#include "game/rB_8002E1C4/types.h"

/* Gradient palette process (lbl_80379470) and the on-screen notice (lbl_803794D0). */
extern const char lbl_80361390[0x200];
struct Col {
    u8 r, g, b, a;
    Col& operator=(const Col& o) { r = o.r; g = o.g; b = o.b; a = o.a; return *this; }
};
struct PalProc {
    u8 pad[0x30];
    s16 mode;
    Col* tbl;
    int x38, x3c, x40, x44;
};
extern u8 lbl_80379470[];
extern "C" {
Col* fn_80078D9C(int n, const char* s, int k);
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

void fn_80035364(PalProc* p) {
    p->tbl = fn_80078D9C(-0x80, lbl_80361390 + 0x1bb, 0);
    build(p);
}

static inline void setup(PalProc* p, int a, int b, int c, int d, int m) {
    p->x38 = a;
    p->x3c = b;
    p->x40 = c;
    p->x44 = d;
    p->mode = m;
}
#pragma use_lmw_stmw on
int fn_80036398(int a, int b, int c, int d) {
    if (fn_80083B84(lbl_80379470)) {
        PalProc* p = fn_80083B84(lbl_80379470);
        setup(p, a, b, c, d, 0);
        if (p->tbl) build(p);
    } else {
        PalProc* p = fn_80081050(lbl_80379470, 3);
        setup(p, a, b, c, d, 0);
        p->tbl = 0;
    }
    return 0;
}
int fn_80036654(int a, int b, int c, int d) {
    if (fn_80083B84(lbl_80379470)) {
        PalProc* p = fn_80083B84(lbl_80379470);
        setup(p, a, b, c, d, 1);
        if (p->tbl) build(p);
    } else {
        PalProc* p = fn_80081050(lbl_80379470, 3);
        setup(p, a, b, c, d, 1);
        p->tbl = 0;
    }
    return 0;
}
#pragma use_lmw_stmw reset
}
