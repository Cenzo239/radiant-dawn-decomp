/* AI script: per-command handlers, table at lbl_804CB8B8. 80158C8C.. */
#include "game/rM_8014C9F8/ai.h"
#pragma auto_inline off

struct AiCmd {
    int op;      /* 0x00 */
    int a;       /* 0x04: often percent chance */
    int b;       /* 0x08 */
    int c;       /* 0x0C */
    int d;       /* 0x10 */
    u32 fl;      /* 0x14 */
    u32 x;       /* 0x18 */
    u32 y;       /* 0x1C */
    u32 z;       /* 0x20 */
    u32 w;       /* 0x24 */
};

struct Fn4 {
    void* vt;
    Unit* u;
    u32 x;
    u8 k;
};

static inline void Fn2Set(Fn2* f, void* vt, Unit* u) {
    f->u = u;
    f->vt = vt;
}
static inline void Fn4Set(Fn4* f, void* vt, Unit* u, u32 x, u8 k) {
    f->u = u;
    f->vt = vt;
    f->x = x;
    f->k = k;
}

extern "C" {

extern u8 lbl_803872B8[];
extern u8 lbl_803872C8[];
extern AiCmd* lbl_804CB8B8;
#if TARGET_PC
FE10_PROTO extern p32ret lbl_804CB8B4;
#else
extern int lbl_804CB8B4;
#endif
extern u8 lbl_804CB8B0;
extern int fn_80089C88(int);
extern void fn_80129550(Unit*, int);
extern int fn_80152C20(void*, void*, u8);

#pragma use_lmw_stmw off
void fn_80158C8C(void) { lbl_804CB8B8 = NULL; }
#pragma use_lmw_stmw off
u8* fn_80158C98(void) { return (u8*)lbl_804CB8B8; }

extern u8 lbl_8036A128[];
extern u8 lbl_8036A178[];
extern u8 lbl_8036A1C8[];
extern u8 lbl_8036A780[];
extern u8 fn_80129600(Unit*, int);
#if TARGET_PC
extern FE10_PROTO AiCmd* fn_80076F54(p32arg);
extern FE10_PROTO void* fn_80077064(p32arg);
extern FE10_PROTO void fn_801293F0(Unit*, p32arg);
extern FE10_PROTO void fn_80129438(Unit*, p32arg);
extern FE10_PROTO void fn_80129480(Unit*, p32arg);
extern FE10_PROTO void fn_801294C8(Unit*, p32arg);
#else
extern AiCmd* fn_80076F54(u32);
extern void* fn_80077064(u32);
extern void fn_801293F0(Unit*, u32);
extern void fn_80129438(Unit*, u32);
extern void fn_80129480(Unit*, u32);
extern void fn_801294C8(Unit*, u32);
#endif
extern void fn_801295B8(Unit*, int, u8);
extern int fn_8016D1DC(int, int, u32, u32);
extern char* fn_800CFD3C(void*);
extern u8 lbl_803E7320[];
extern void fn_80160508(u8, Unit*, int, int, int, int, int);
#if TARGET_PC
extern FE10_PROTO int fn_80169558(Unit*, ptr32<const void>, ptr32<const void>);
#else
extern int fn_80169558(Unit*, void*, void*);
#endif
extern int fn_80154678(void*, void*, u8);
#if TARGET_PC
extern FE10_PROTO int fn_80154C44(p32arg, u8);
#else
extern int fn_80154C44(u32, u8);
#endif
extern int fn_801557D0(void*, void*, u8);
#if TARGET_PC
extern FE10_PROTO int fn_8016C9C8(Unit*, void*, ptr32<const void>);
#else
extern int fn_8016C9C8(Unit*, void*, void*);
#endif
extern int fn_801540B0(void*, void*, u8);
extern int fn_80153A74(void*, void*, u8);
extern int fn_80153070(void*, void*, u8);
extern int fn_801534C0(void*, void*, u8);
extern u32 fn_80170BF8(u32);
#if TARGET_PC
extern FE10_PROTO u8* fn_8012CE54(p32arg);
#else
extern u8* fn_8012CE54(u32);
#endif
extern u8 lbl_803872D8[];
extern u8 lbl_803872E8[];
extern u8 lbl_80387298[];
extern u8 lbl_803872A8[];
extern char lbl_804CE320[4];
extern void fn_8015960C(Unit*);

struct Entry {
    int key;
    void (*fn)(Unit*);
    int pad;
};

static inline Entry* FindOp(AiCmd* c) {
    int n;
    int key;
    int h;
    Entry* m;
    Entry* e;
    e = (Entry*)lbl_8036A780;
    n = 0x52;
    key = c->op;
    while (n > 0) {
        h = n / 2;
        m = e + h;
        if (e[h].key < key) {
            e = m + 1;
            n -= h + 1;
        } else {
            n = h;
        }
    }
    return e;
}

static inline void RunCmd(Unit* u) {
    Entry* e;
    u32 old;
    e = FindOp(lbl_804CB8B8);
    old = *(volatile u32*)&u->w3B4;
    if (lbl_804CB8B8->fl & 0x20) {
        u->w3B4 |= 0x80000;
    }
    e->fn(u);
    if (old & 0x80000) {
        u->w3B4 |= 0x80000;
    } else {
        u->w3B4 &= ~0x80000;
    }
}

#pragma use_lmw_stmw off
void fn_80159364(Unit* u) { fn_80129550(u, lbl_804CB8B4); }
#pragma use_lmw_stmw off
void fn_8015936C(Unit* u) { fn_80129550(u, lbl_804CB8B4); }

#pragma use_lmw_stmw off
void fn_80159374(Unit* u) {
    int r;
    int k = lbl_804CB8B8->b;
    int* p = &lbl_804183F0.res[lbl_804CB8B8->a];
    int v = lbl_804CB8B8->c;
    switch (k) {
    case 0:
        r = v < *p;
        break;
    case 1:
        r = *p >= v;
        break;
    case 2:
        r = *p == v;
        break;
    case 4:
        r = *p < v;
        break;
    case 3:
        r = v >= *p;
        break;
    case 5:
        r = *p != v;
        break;
    default:
        r = 0;
        break;
    }
    if (r) {
        fn_8015960C(u);
    } else {
        fn_80129550(u, lbl_804CB8B4);
    }
}

#pragma use_lmw_stmw off
void fn_80159474(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        u8 (*fn)(Unit*, AiCmd*) = (u8 (*)(Unit*, AiCmd*))fn_80077064(c->x);
        if (fn != NULL) {
            lbl_804CB8B0 = fn(u, c);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_801594F0(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    BOOL hit = 0;
    if (c->x != 0) {
        if (lbl_804CB8B4 == 0) {
            hit = 1;
        }
        fn_801293F0(u, c->x);
    }
    if (c->y != 0) {
        if (lbl_804CB8B4 == 1) {
            hit = 1;
        }
        fn_80129438(u, c->y);
    }
    if (c->z != 0) {
        if (lbl_804CB8B4 == 2) {
            hit = 1;
        }
        fn_80129480(u, c->z);
    }
    if (c->w != 0) {
        if (lbl_804CB8B4 == 3) {
            hit = 1;
        }
        fn_801294C8(u, c->w);
    }
    if (!hit) {
        fn_80129550(u, lbl_804CB8B4);
    } else {
        lbl_804CB8B0 = 1;
        lbl_804183F0.b1--;
    }
    u32 f = u->w3B4;
    *(u16*)((u8*)u + 0x3B8) = 0;
    u->w3B4 = f & ~8;
}

#pragma use_lmw_stmw off
void fn_8015960C(Unit* u) {
    int d = lbl_804CB8B8->d;
    int i = 0;
    AiCmd* p;
    if (lbl_804CB8B4 == 0) {
        p = fn_80076F54(*(u32*)((u8*)u + 0x394));
    } else {
        p = fn_80076F54(*(u32*)((u8*)u + 0x398));
    }
    if (d != 0) {
        while (p->op != 0 || p->c != d) {
            p++;
            i++;
        }
        fn_801295B8(u, lbl_804CB8B4, i);
    } else {
        fn_801295B8(u, lbl_804CB8B4, 0);
    }
}

#pragma use_lmw_stmw off
void fn_801597B8(Unit* u) {
    if ((lbl_804CB8B8->a != 0) == (lbl_804183F0.done != 0)) {
        fn_8015960C(u);
    } else {
        fn_80129550(u, lbl_804CB8B4);
    }
}

#pragma use_lmw_stmw off
void fn_801597F8(Unit* u) {
    lbl_804183F0.done = 0;
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_80159810(Unit* u) {
    if ((lbl_804CB8B8->a != 0) == (lbl_804183F0.done != 0) && u->x != lbl_803CA870.x && u->y != lbl_803CA870.y) {
        fn_8015960C(u);
    } else {
        fn_80129550(u, lbl_804CB8B4);
    }
}

#pragma use_lmw_stmw off
void fn_80159888(Unit* u) {
    void* s;
    AiCmd* c = lbl_804CB8B8;
    lbl_804183F0.res[0] = 0;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 g1;
        Fn2 g2;
        Fn4Set(&f3, lbl_803872E8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872D8, u, c->x, 1);
        s = &f3;
        u32 fl = c->fl & 1;
        if (fl) {
            s = &f2;
        }
        if (fl) {
            Fn2Set(&g1, lbl_80387338, u);
            fn_80152C20(s, &g1, 0xF);
        } else if (fn_80170BF8(c->x) == 1) {
            if (*(u32*)(fn_8012CE54(c->x) + 0x10C) & 4) {
                lbl_804183F0.res[0] = 4;
            } else {
                g2.vt = lbl_80387338;
            g2.u = u;
                fn_80152C20(s, &g2, 0xF);
            }
        } else {
            lbl_804183F0.res[0] = 1;
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_801599E0(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_80387338, u);
        fn_80152C20(s, &g, 0xF);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_80159AC8(Unit* u) { fn_80129550(u, lbl_804CB8B4); }

#pragma use_lmw_stmw off
void fn_80159AD0(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_80387338, u);
        lbl_804183F0.flags |= 2;
        fn_80152C20(s, &g, 0xF);
        lbl_804183F0.flags &= ~2;
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_80159BD8(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (c->x != 0 && fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 g;
        void* s;
        Fn4Set(&f3, lbl_80387298, u, c->x, lbl_804CE320[c->c & 0xFF]);
        Fn4Set(&f2, lbl_803872A8, u, c->x, lbl_804CE320[c->c & 0xFF]);
        s = &f2;
        if (c->fl & 1) {
            s = &f3;
        }
        Fn2Set(&g, lbl_80387338, u);
        fn_80152C20(s, &g, 0xF);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_80159CBC(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_80387338, u);
        fn_80169558(u, s, &g);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_80159DA4(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_80387338, u);
        lbl_804183F0.flags |= 2;
        fn_80169558(u, s, &g);
        lbl_804183F0.flags &= ~2;
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_80159F80(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        lbl_804183F0.flags |= 2;
        fn_8016CD04(u, s);
        lbl_804183F0.flags &= ~2;
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015A074(Unit* u) { fn_80129550(u, lbl_804CB8B4); }

#pragma use_lmw_stmw off
void fn_8015A07C(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        fn_8016C9C8(u, fn_80077064(lbl_804CB8B8->y), s);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015A164(Unit* u) {
    void* s;
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        lbl_804183F0.flags |= 2;
        fn_8016C9C8(u, fn_80077064(lbl_804CB8B8->y), s);
        lbl_804183F0.flags &= ~2;
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015A274(Unit* u) {
    void* s;
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_80387338, u);
        if (fn_801540B0(s, &g, 0x32) == 0) {
            Fn2 g2;
            g2.vt = lbl_80387338;
            g2.u = u;
            fn_80153A74(s, &g2, 0x2B);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015A388(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_80387338, u);
        fn_80154678(s, &g, 0x2F);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015A470(Unit* u) {
    fn_80154C44(lbl_804CB8B8->x, 0x2F);
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015A4B4(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_80387338, u);
        fn_801557D0(s, &g, 0x13);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015A59C(Unit* u) {
    void* s;
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_80387338, u);
        if (fn_80153070(s, &g, 0xF) == 0) {
            Fn2 g2;
            g2.vt = lbl_80387338;
            g2.u = u;
            fn_801534C0(s, &g2, 0xF);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

extern u8 lbl_80387218[];
extern u8 lbl_80387208[];
extern u8 lbl_803871F8[];
extern u8 lbl_80387318[];
extern void fn_80129170(void*, void*);
extern void fn_80129160(void*);
#if TARGET_PC
extern FE10_PROTO void * fn_8010B228(p32arg);
#else
extern int fn_8010B228(u32);
#endif
#if TARGET_PC
extern FE10_PROTO int fn_80155090(void*, void*, p32arg, u8);
#else
extern int fn_80155090(void*, void*, u32, u8);
#endif
extern int fn_80234954(void*, void*, u8);
extern int fn_80234C48(void*, void*, u8);
extern int fn_8016E3BC(u32, s16*, s16*, int*);
extern int fn_80170C48(int, int, int, int);
extern int fn_8016D11C(Unit*);
extern u32 fn_8016E67C(void*, Unit*, s16*, s16*);
extern int fn_80164F90(Unit*);
extern char* lbl_804CA508;
extern int fn_8011B77C(void*, void*);
extern int fn_80171A20(Unit*, int, s16*, s16*);
extern int fn_8016D944(Unit*, int, u32, s16*, s16*);
extern int fn_8016D27C(Unit*, int, u32, s16*, s16*);
extern void fn_80164938(Unit*, u32);
extern int fn_80163AF0(Unit*, u16);
extern void fn_80164A78(Unit*);

struct Fn3x {
    void* vt;
    Unit* u;
    int v;
};

static inline void Fn3Set(Fn3x* f, void* vt, Unit* u, int v) {
    f->u = u;
    f->vt = vt;
    f->v = v;
}

#pragma use_lmw_stmw off
void fn_8015AACC(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn3x g;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn3Set(&g, lbl_80387218, u, c->c);
        fn_80152C20(s, &g, 0xF);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015ABBC(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn3x g;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn3Set(&g, lbl_80387208, u, c->c);
        fn_80152C20(s, &g, 0xF);
        if (lbl_804183F0.done != 0) {
            fn_80129170((u8*)u + 0x3C4, &lbl_803CA870);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015ACD0(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    lbl_804183F0.done = 0;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_803871F8, u);
        fn_80152C20(s, &g, 0xF);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015ADC8(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    lbl_804183F0.done = 0;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_803871F8, u);
        fn_80169558(u, s, &g);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015AEC0(Unit* u) {
    void* s;
    AiCmd* c = lbl_804CB8B8;
    lbl_804183F0.done = 0;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        u32 it = c->y;
        if (it != 0 && fn_8010B228(it) != 0) {
            Fn2 g;
            Fn2Set(&g, lbl_80387338, u);
            fn_80155090(s, &g, it, 0xF);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015AFE4(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a && !(u->flags10C & 6)) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        void* s;
        Fn2Set(&f1, lbl_80387318, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 3);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_80387338, u);
        fn_80234954(s, &g, 0x1A);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015B0D4(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a && !(u->flags10C & 6)) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2 g;
        void* s;
        f1.vt = lbl_80387338;
        f1.u = u;
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 3);
        if (c->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (c->fl & 1) {
                s = &f2;
            }
        }
        Fn2Set(&g, lbl_80387338, u);
        fn_80234C48(s, &g, 0x1A);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw on
void fn_8015B488(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    int r;
    lbl_804183F0.res[0] = 0;
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        r = 0;
        if (fn_8016E3BC(c->x, &x, &y, &r)) {
            lbl_804183F0.res[0] = r;
            u32 fl = c->fl;
            fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
            if (fn_80170C48(x, y, lbl_803CA870.x, lbl_803CA870.y) && lbl_804183F0.res[0] != 4) {
                *(u8**)((u8*)&lbl_803CA870 + 4) = fn_8012CE54(c->x);
                lbl_804183F0.res[0] = 2;
                lbl_804183F0.done = 0;
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015B598(Unit* u) {
    fn_80160610(1, u->x, u->y, u, u->x, u->y, -1, 0, 0);
    lbl_804183F0.done = 0;
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015B8B4(Unit* u) {
    s16 x;
    s16 y;
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        if (fn_8016DC30(u, fn_8016D11C(u), &x, &y) == 1) {
            fn_80160610(1, (s8)x, (s8)y, NULL, (s8)x, (s8)y, -1, 0, 0);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015B95C(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 1);
        if (lbl_804CB8B8->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (lbl_804CB8B8->fl & 1) {
                s = &f2;
            }
        }
        if (fn_8016E50C(s, u, &x, &y) == 1) {
            u32 fl = c->fl;
            fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015BA84(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 1);
        if (lbl_804CB8B8->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (lbl_804CB8B8->fl & 1) {
                s = &f2;
            }
        }
        if (fn_8016E67C(s, u, &x, &y) == 1) {
            u32 fl = c->fl;
            fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015BBAC(Unit* u) { fn_80129550(u, lbl_804CB8B4); }

#pragma use_lmw_stmw off
void fn_8015BBB4(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    lbl_804183F0.res[c->a] = 0;
    if (!(lbl_804183F0.flags & 2)) {
        if (!(u->w3B4 & 0x7000000)) {
            u32 fl;
            int r;
            int v = c->c;
            if (c->fl & 0x10) {
                r = fn_8016D27C(u, 0, v, &x, &y);
            } else {
                r = fn_8016D944(u, 0, v, &x, &y);
            }
            if (r != 0) {
                fl = c->fl;
                fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
                if (x == lbl_803CA870.x && y == lbl_803CA870.y) {
                    lbl_804183F0.res[c->a] = 8;
                } else if (lbl_803CA870.action == 1) {
                    fn_80164938(u, v);
                }
            } else {
                lbl_804183F0.res[c->a] = 9;
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015BF88(Unit* u) {
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        u->w3B4 |= 8;
        if (fn_80163AF0(u, fn_8016D11C(u)) != 0 && lbl_803CA870.action == 1) {
            fn_80164A78(u);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015CA88(Unit* u) { fn_80129550(u, lbl_804CB8B4); }
#pragma use_lmw_stmw off
void fn_8015CA90(Unit* u) { fn_80129550(u, lbl_804CB8B4); }

extern u32 fn_8016E7FC(void*, Unit*, s16*, s16*);
extern u32 fn_8016E9A8(void*, Unit*, s16*, s16*);
extern u32 fn_8016EBD8(void*, Unit*, s16*, s16*);
extern u32 fn_8016EDE8(void*, Unit*, s16*, s16*);
extern u8* fn_800CFCB4(void*, int, int);
extern int fn_8009FF74(void);
extern void fn_80172494(Unit*, int, int);
extern void fn_8016EFC8(Unit*, int, int, int, u16, int, int, int);
extern char* fn_800CFD18(void*, int);
extern u32 fn_8016D5D4(Unit*, int, int, s16*, s16*);
extern s8 fn_8012C9BC(Unit*, u8*);
extern int fn_8012C8BC(Unit*, u8*);
extern s16 fn_801237EC(Unit*);
extern s8 fn_801284C4(Unit*);
extern char* lbl_804CA4EC;
extern char* lbl_804CA4E8;
extern char* lbl_804CA5E0;
extern char* lbl_804CA650;
extern char* lbl_804CA4F0;
extern char* lbl_804CA4F4;
extern void fn_8017252C(Unit*, int, int, int);

#pragma use_lmw_stmw off
void fn_8015D474(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        void* s;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 1);
        if (lbl_804CB8B8->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (lbl_804CB8B8->fl & 1) {
                s = &f2;
            }
        }
        if (fn_8016E7FC(s, u, &x, &y) == 1) {
            u32 fl = c->fl;
            fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015DA04(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    if (!(lbl_804183F0.flags & 2)) {
        if (!(u->w3B4 & 0x7000000) && !(u->flags10C & 6)) {
            Fn4 f3;
            Fn4 f2;
            Fn2 f1;
            void* s;
            Fn2Set(&f1, lbl_80387318, u);
            Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
            Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 3);
            if (lbl_804CB8B8->x == 0) {
                s = &f1;
            } else {
                s = &f3;
                if (lbl_804CB8B8->fl & 1) {
                    s = &f2;
                }
            }
            if (fn_8016E9A8(s, u, &x, &y) == 1) {
                u32 fl = c->fl;
                fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015DB34(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    if (!(lbl_804183F0.flags & 2)) {
        if (!(u->w3B4 & 0x7000000) && !(u->flags10C & 6)) {
            Fn4 f3;
            Fn4 f2;
            Fn2 f1;
            void* s;
            f1.vt = lbl_80387338;
            f1.u = u;
            Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
            Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 3);
            if (lbl_804CB8B8->x == 0) {
                s = &f1;
            } else {
                s = &f3;
                if (lbl_804CB8B8->fl & 1) {
                    s = &f2;
                }
            }
            if (fn_8016EBD8(s, u, &x, &y) == 1) {
                u32 fl = c->fl;
                fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015E61C(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    if (!(lbl_804183F0.flags & 2)) {
        if (!(u->w3B4 & 0x7000000) && !(u->flags10C & 6)) {
            Fn4 f3;
            Fn4 f2;
            Fn2 f1;
            void* s;
            Fn2Set(&f1, lbl_80387308, u);
            Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
            Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 1);
            if (lbl_804CB8B8->x == 0) {
                s = &f1;
            } else {
                s = &f3;
                if (lbl_804CB8B8->fl & 1) {
                    s = &f2;
                }
            }
            if (fn_8016EDE8(s, u, &x, &y) == 1) {
                u32 fl = c->fl;
                fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015E8B4(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    char* k = lbl_804CA4EC;
    lbl_804183F0.res[c->a] = 0;
    if (fn_8011B77C(u->skills, k)) {
        lbl_804183F0.res[c->a] = 0xB;
    } else {
        lbl_804183F0.res[c->a] = 0;
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015ECEC(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    int r = 0;
    if (fn_8011B77C(u->skills, lbl_804CA4E8) && !fn_8011B77C(u->skills, lbl_804CA4EC)) {
        if (fn_8011B77C(u->skills, lbl_804CA5E0)) {
            r = 1;
        } else if (fn_801284C4(u) >= 0x1E) {
            r = 1;
        } else if (fn_8011B77C(u->skills, lbl_804CA650)) {
            r = 1;
        }
    }
    lbl_804183F0.res[c->c] = r;
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015EDC8(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    lbl_804183F0.res[c->c] = fn_801284C4(u);
    lbl_804183F0.res[c->d] = fn_801284C4(u) * 100 / 30;
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015EE6C(Unit* u) {
    s8 k;
    if (fn_8011B77C(u->skills, lbl_804CA4E8) && !fn_8011B77C(u->skills, lbl_804CA4F0) &&
        !fn_8011B77C(u->skills, lbl_804CA4F4) && fn_8011B77C(u->skills, lbl_804CA4EC)) {
        k = 2;
    } else {
        k = fn_80172748(u);
    }
    if (k < 0) {
        lbl_804183F0.done = 0;
    } else {
        s8 x = u->x;
        s8 y = u->y;
        if (lbl_804183F0.done != 0) {
            fn_800453B4(&lbl_803CA870, 0x3D);
        } else {
            fn_80160610(0x3D, x, y, u, x, y, 0, k, 0);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

extern int fn_801705A8(Unit*, int, int, void*, u8, int, u16, int, int, int);

#pragma use_lmw_stmw on
void fn_8015B738(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    lbl_804183F0.res[0] = 0;
    lbl_804183F0.res[1] = 0;
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        if (fn_80164F90(u) == 0 && fn_8011B77C(u->skills, lbl_804CA508) && fn_80171A20(u, 0, &x, &y)) {
            u32 fl = c->fl;
            fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
            if (lbl_804183F0.done != 0 && x == lbl_803CA870.x && y == lbl_803CA870.y) {
                fn_80160610(0x26, lbl_803CA870.x, lbl_803CA870.y, *(Unit**)((u8*)&lbl_803CA870 + 4), ((s8*)&lbl_803CA870)[0x13], (s8)((u8*)&lbl_803CA870)[0x14], -1, 0, 0);
                lbl_804183F0.res[1] = 0x10;
            }
        }
        if (c->c != 0) {
            u16* h = (u16*)((u8*)u + 0x3B8);
            (*h)++;
            if (*h > c->c) {
                lbl_804183F0.res[0] = 10;
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015D14C(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    int r = 0;
    lbl_804183F0.res[0] = 0;
    lbl_804183F0.res[1] = 0;
    if (fn_8016E3BC(c->x, &x, &y, &r)) {
        lbl_804183F0.res[0] = r;
        lbl_804183F0.res[1] = r;
        Unit* t = (Unit*)fn_8012CE54(c->x);
        *(Unit**)((u8*)&lbl_803CA870 + 4) = t;
        if (fn_8009FF74() == 0) {
            lbl_804183F0.res[0] = 9;
            lbl_804183F0.res[1] = 9;
        } else {
            fn_80172494(u, -1, -1);
            if (fn_800CFCB4(lbl_803E7320, t->x, (s8)*(u8*)&t->y) != NULL && lbl_804183F0.res[0] != 4) {
                fn_80160610(7, (s8)*(u8*)&u->x, u->y, t, (s8)x, (s8)y, -1, 0, 0);
                lbl_804183F0.res[0] = 3;
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015D868(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        Fn4 f3;
        Fn4 f2;
        Fn4 f5;
        Fn4 f4;
        Fn2 f1;
        void* s;
        void* t;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 1);
        Fn4Set(&f5, lbl_803872C8, u, lbl_804CB8B8->y, 3);
        Fn4Set(&f4, lbl_803872B8, u, lbl_804CB8B8->y, 1);
        if (lbl_804CB8B8->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (lbl_804CB8B8->fl & 1) {
                s = &f2;
            }
        }
        if (lbl_804CB8B8->y == 0) {
            t = &f1;
        } else {
            t = &f5;
            if (lbl_804CB8B8->fl & 1) {
                t = &f4;
            }
        }
        if (fn_8016E50C(s, u, &x, &y) == 1) {
            u32 fl = c->fl;
            fn_801705A8(u, x, y, t, c->c, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
static inline void ActAt(int v, Unit* u, s8 x, s8 y) {
    fn_80160508(v, u, x, y, -1, 0, 0);
}
#pragma use_lmw_stmw on

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off
void fn_80159EAC(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (fn_80089C88(100) < c->a) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, c->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, c->x, 1);
        fn_8016CD04(u, c->x == 0 ? (void*)&f1 : ((c->fl & 1) ? (void*)&f2 : (void*)&f3));
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw on

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off
void fn_8015E95C(Unit* u) {
    u8* it = (u8*)fn_8010B228(lbl_804CB8B8->x);
    if (it == NULL || (s8)fn_8012C9BC(u, it) < 0 || !fn_8012C8BC(u, it)) {
        lbl_804183F0.done = 0;
    } else {
        s8 k = fn_8012C9BC(u, it);
        s8 x = u->x;
        s8 y = u->y;
        if (lbl_804183F0.done != 0) {
            fn_800453B4(&lbl_803CA870, 4);
            ((s8*)&lbl_803CA870)[0xE] = k;
        } else {
            fn_80160610(4, x, y, u, x, y, k, 0, 0);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off
void fn_8015B614(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    if (lbl_804CB8B8->x != 0) {
        if (!(lbl_804183F0.flags & 2)) {
            if (!(u->w3B4 & 0x7000000)) {
                Fn4 f3;
                Fn4 f2;
                Fn4Set(&f3, lbl_80387298, u, lbl_804CB8B8->x, lbl_804CE320[lbl_804CB8B8->c & 0xFF]);
                Fn4Set(&f2, lbl_803872A8, u, lbl_804CB8B8->x, lbl_804CE320[lbl_804CB8B8->c & 0xFF]);
                if (fn_8016E50C((lbl_804CB8B8->fl & 1) ? (void*)&f3 : (void*)&f2, u, &x, &y) == 1) {
                    u32 fl = c->fl;
                    fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
                }
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */

static inline s8 ActFlag16(void) { return ((s8*)&lbl_803CA870)[0x16]; }

#pragma use_lmw_stmw on

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw on

extern int fn_801658E4(Unit*, s8, s8);
extern int fn_80171A30(Unit*, int, s16*, s16*);
extern int fn_8015C018(Unit*, int, int, s16*, s16*, s8*);
extern int fn_8015C468(Unit*, int, int, s16*, s16*, s8*);

#pragma use_lmw_stmw on
void fn_8015C8B8(Unit* u) {
    AiCfg* cfg = &lbl_804183F0;
    u32 fl;
    AiCmd* c = lbl_804CB8B8;
    int px;
    int py;
    char* p;
    s16 x;
    s16 y;
    s16 x2;
    s16 y2;
    u8 k;
    cfg->res[0] = 0;
    if (fn_80171A30(u, 0, &x, &y) != 0) {
        p = fn_800CFD3C(lbl_803E7320);
        if (p == NULL) {
            cfg->res[0] = 9;
        } else {
            px = p[0];
            py = p[1];
            if (fn_8015C018(u, px, py, &x2, &y2, (s8*)&k) != 0) {
                fn_80160610(0x28, (s8)x2, (s8)*(s16*)&y2, NULL, px, py, (s8)k, 0, 0);
                cfg->res[0] = 0x10;
            } else if (fn_8015C468(u, px, py, &x2, &y2, (s8*)&k) != 0) {
                fl = c->fl;
                fn_8016F94C(u, x2, y2, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
                if (x2 == lbl_803CA870.x && y2 == lbl_803CA870.y) {
                    cfg->res[0] = 2;
                }
            } else {
                fl = c->fl;
                fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
            }
        }
    } else {
        cfg->res[0] = 9;
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw on
void fn_8015CA98(Unit* u) {
    AiCfg* cfg = &lbl_804183F0;
    AiCmd* c = lbl_804CB8B8;
    Unit* t;
    u32 fl;
    s16 x;
    s16 y;
    int r;
    cfg->res[0] = 0;
    cfg->res[1] = 0;
    if (!(cfg->flags & 2)) {
        if (!(u->w3B4 & 0x7000000) && ((*(u16*)((u8*)u + 0x110) >> 4) & 7) == 0) {
            r = 0;
            if (fn_8016E3BC(lbl_804CB8B8->x, &x, &y, &r)) {
                cfg->res[0] = r;
                cfg->res[1] = r;
                t = (Unit*)fn_8012CE54(c->x);
                *(Unit**)((u8*)&lbl_803CA870 + 4) = t;
                if (fn_8009FF74() == 0) {
                    cfg->res[0] = 9;
                    cfg->res[1] = 9;
                } else {
                    fl = c->fl;
                    fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
                    fn_80172494(u, lbl_803CA870.x, lbl_803CA870.y);
                    if (fn_800CFCB4(lbl_803E7320, t->x, (s8)*(u8*)&t->y) != NULL && cfg->res[0] != 4) {
                        fn_80160508(7, t, (s8)x, (s8)y, -1, 0, 0);
                        if (lbl_803CA870.action == 7) {
                            cfg->res[0] = 3;
                        }
                    }
                }
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

extern void fn_800CFB34(void*);

#pragma use_lmw_stmw on
void fn_8015EA68(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    u8* it = (u8*)fn_8010B228(lbl_804CB8B8->x);
    if (it == NULL || fn_8012C9BC(u, it) < 0 || !fn_8012C8BC(u, it)) {
        lbl_804183F0.done = 0;
    } else {
        s8 k = fn_8012C9BC(u, it);
        s8 x;
        s8 y;
        s8 tx;
        s8 ty;
        if (lbl_804183F0.done != 0) {
            x = lbl_803CA870.x;
            y = lbl_803CA870.y;
        } else {
            x = u->x;
            y = u->y;
        }
        tx = x;
        ty = y;
        switch (c->c) {
        case 1:
            tx = x - 1;
            break;
        case 2:
            tx = x + 1;
            break;
        case 4:
            ty = y + 1;
            break;
        case 8:
            ty = y - 1;
            break;
        }
        fn_800CFB34(lbl_803E7320);
        fn_8017252C(u, 0xC, x, y);
        if (*(int*)lbl_803E7320 == 0 || fn_800CFCB4(lbl_803E7320, tx, ty) == NULL) {
            lbl_804183F0.done = 0;
        } else if (lbl_804183F0.done != 0) {
            fn_800453B4(&lbl_803CA870, 4);
            ((s8*)&lbl_803CA870)[0xE] = k;
            ((s8*)&lbl_803CA870)[0x13] = tx;
            ((s8*)&lbl_803CA870)[0x14] = ty;
        } else {
            fn_80160610(4, x, y, u, tx, ty, k, 0, 0);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}
#ifndef ABS
#define ABS(a) ((a) < 0 ? -(a) : (a))
#endif
extern u32 fn_801676D8(int,int);
extern void fn_80165E18(Unit*, int, int);
#pragma use_lmw_stmw on

#if TARGET_PC
extern FE10_PROTO int fn_8016E2AC(Unit*, s16*, s16*, p32arg);
#else
extern int fn_8016E2AC(Unit*, s16*, s16*, int);
#endif
extern int fn_801723A8(void*, Unit*, u32, u32, BOOL, f32);
extern int fn_80171E5C(void*, Unit*, int, u32, u32, BOOL);
class FilterV { public: virtual int check(void*); };
#pragma use_lmw_stmw off
void fn_8015D290(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    s16 x;
    s16 y;
    lbl_804183F0.res[0] = 0;
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        Unit* o = *(Unit**)((u8*)u + 0x3C0);
        if (u == o) {
            lbl_804183F0.res[0] = 9;
        } else if (o == NULL) {
            lbl_804183F0.res[0] = 1;
        } else if (!(o->flags10C & 1) && *(void**)((u8*)o + 0x3C4) != NULL) {
            u32 fl;
            x = ((s8*)o)[0x3CC];
            y = ((s8*)o)[0x3CD];
            fn_80165F94(u, 6, -1);
            lbl_803EC898.costS[(s8)x + (s8)y * 0x40] = -1;
            fl = c->fl;
            fn_8016EFC8(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
        } else if (fn_8016E2AC(o, &x, &y, 0) != 0) {
            u32 fl = c->fl;
            fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
            if (fn_80170C48(x, y, lbl_803CA870.x, lbl_803CA870.y) && lbl_804183F0.res[0] != 4) {
                lbl_804183F0.res[0] = 2;
                *(Unit**)((u8*)&lbl_803CA870 + 4) = o;
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015E750(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    Fn4 f3;
    Fn4 f2;
    Fn2 f1;
    void* s;
    u32 fl;
    Fn2Set(&f1, lbl_80387308, u);
    Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
    Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 1);
    if (lbl_804CB8B8->x == 0) {
        s = &f1;
    } else {
        s = &f3;
        if (lbl_804CB8B8->fl & 1) {
            s = &f2;
        }
    }
    fl = c->fl;
    f32 v = c->b;
    v /= 65536.0f;
    if (fl & 8) {
        lbl_804183F0.res[c->a] = fn_80171E5C(s, u, (int)v, (fl >> 6) & 1, (fl >> 9) & 1, !(fl & 4));
    } else {
        lbl_804183F0.res[c->a] = fn_801723A8(s, u, (fl >> 6) & 1, (fl >> 9) & 1, !(fl & 4), v);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw off
void fn_8015EF74(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    Fn4 f3;
    Fn4 f2;
    Fn2 f1;
    void* s;
    Fn2Set(&f1, lbl_80387318, u);
    Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
    Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 3);
    if (lbl_804CB8B8->x == 0) {
        s = &f1;
    } else {
        s = &f3;
        if (lbl_804CB8B8->fl & 1) {
            s = &f2;
        }
    }
    lbl_804183F0.res[lbl_804CB8B8->a] = 0;
    void* ac = u->actor;
    if (ac != NULL) {
        lbl_804183F0.res[c->a] = ((FilterV*)s)->check(ac);
    }
    fn_80129550(u, lbl_804CB8B4);
}

#pragma use_lmw_stmw on

extern void fn_8016FA34(int, int, Unit*, int, int, int, u16, int, int, int);
extern void fn_80116BD0(Map*, int, int, int, int);
extern u8* fn_80116294(Map*, void*, int, int, int);
extern int fn_801107A0(u8*, Unit*);
static inline int InvRange(Unit* u, Inv* v) {
    if (v->item != NULL) {
        return (u8)fn_801107A0(v->item, u);
    }
    return 0;
}
#pragma use_lmw_stmw on

static inline void ActS(u8 a, s8 x, s8 y) { fn_80160610(a, x, y, NULL, x, y, -1, 0, 0); }
#pragma use_lmw_stmw on

}
