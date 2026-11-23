/* fn_8005A428: deployment-phase swap-units cursor handler; same helpers as fn_80059B18.cpp. Round 16. */
#include "game/rC2_8005259C/base.h"
class Pad { public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual u32 v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual u32 v48(); virtual void v4C();
    virtual int v50(); virtual int v54();
};
struct CK { u8 pad[8]; u8 b8; };
struct Sel { s8 x; s8 y; };
struct FU { u8 pad[0x10c]; u32 f10c; u8 p[0x3f0 - 0x110]; };
struct GCur { u8 pad[0x934]; f32 x; f32 y; };
struct Cc { u8 pad[0x11]; s8 b11; s8 b12; };
struct PU { u8 pad[0x30]; FU* u; u8 p34[0x24]; s8 x; s8 y; };
struct UX { u8 pad[0xe8]; UX* next; u8 pec[8]; CK* f4; u8 pf8[0x10]; u64 flags; };
struct UL { u8 pad[0xc]; UX* h0c; };
struct Spr { u8 pad[0x64]; const char* s; };
struct Opt { u32 p : 25; u32 f : 1; u32 r : 6; u8 p4[0xd]; u8 b11; };
struct Pr { u8 pad[0x50]; u8 b50; };
struct Map { u8 pad[0xd]; u8 id[1]; };
extern "C" {
extern u32 lbl_804CB700;
extern Pad* lbl_804CB5B8;
extern UL* lbl_804CB814;
extern UX* lbl_804CB418;
extern const char** lbl_804CB554;
extern GCur lbl_803CAB38;
extern FU* lbl_804CB810;
extern int lbl_803E7320[];
Sel* fn_800CFD18(void*, int);
extern Cc lbl_803CA870;
extern Map lbl_803EC898;
extern char lbl_80361F9C[316];
UX* fn_800677E4(void);
u8 fn_8010E314(int, u8);
Spr* fn_801E5640(void*, int, int);
Opt* fn_80060728(GCur*);
void fn_8013F204(void);
void fn_8013F1C4(void);
void fn_80067168(UX*);
void fn_80185720(void);
void fn_800451D4(Cc*, UX*);
void fn_80253EE4(const char*, f32);
void fn_80083DC4(void*, int);
void fn_80114D00(Map*);
void fn_801B5D68(void);
void fn_80083B78(void*);
PU* fn_80081194(void*, void*);
#if TARGET_PC
FE10_PROTO PU* fn_80081050(void*, p32arg);
#else
PU* fn_80081050(void*, int);
#endif
extern u8 lbl_8037E148[];
void fn_800620A8(GCur*, f32, f32);
}
static inline int inputBlocked(void) {
    u32 f1 = *(volatile u32*)&lbl_804CB700;
    u32 f2 = *(volatile u32*)&lbl_804CB700;
    int b = 0;
    if ((f1 & 0x10) && !(f2 & 0x20)) {
        b = 1;
    }
    return b;
}
#define HELP(p, n) \
    { const char* s = lbl_804CB554[n]; \
    Spr* q = fn_801E5640(p, -0x1000, 0); \
    if (q) { q->s = s; } }
#define PANEL_OFF() if (lbl_804CB700 & 0x400) { fn_8013F204(); }

static inline FU* idUnit(int id) {
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}
static inline void deployTile(int x, int y, int& ok) {
    int id;
    ok = 0;
    id = lbl_803EC898.id[(s8)x + (s8)y * 0x40];
    if (id != 0 && (idUnit(id)->f10c & 0x20000)) {
        ok = 0;
        return;
    }
    {
        int i;
        for (i = 0; i < lbl_803E7320[0]; i++) {
            Sel* s = fn_800CFD18(lbl_803E7320, i);
            if ((s8)x == s->x && (s8)y == s->y) {
                ok = 1;
                return;
            }
        }
    }
}

static inline void panel(UX* v) {
    if (!v) {
        PANEL_OFF()
    }
    if (inputBlocked() || (!(lbl_804CB5B8->v34() & 0xf) && !lbl_804CB5B8->v50() && !lbl_804CB5B8->v54())) {
        if (lbl_804CB418 != v || !(lbl_804CB700 & 0x400)) {
            lbl_804CB418 = v;
            if (!v || v->f4->b8 == 0) {
                PANEL_OFF()
            } else {
                fn_80067168(v);
                fn_8013F1C4();
            }
        }
    }
}

static inline PU* newProc(Pr* p) {
    if (p) {
        return fn_80081194(lbl_8037E148, p);
    }
    return fn_80081050(lbl_8037E148, 4);
}

extern "C" void fn_8005A428(Pr* p) {
/*P*/
    int ok;
    int x;
    int y;
    u8* tile;
    UX* c;
    int sx;
    int sy;
    FU* u0;
    u32 m;
/*E*/
    c = fn_800677E4();
    x = (int)lbl_803CAB38.x;
    sx = lbl_803CA870.b11;
    sy = lbl_803CA870.b12;
    y = (int)lbl_803CAB38.y;
    tile = &lbl_803EC898.id[sx + sy * 0x40];
    {
        int id = *tile;
        u0 = id ? &lbl_804CB810[id - 1] : 0;
    }
    if (c) {
        if (fn_8010E314(0, c->f4->b8) == 1) {
            if (!(c->flags & 0x800)) {
                HELP(p, 2)
            } else {
                HELP(p, 3)
            }
        } else if ((UX*)u0 != c) {
            deployTile(x, y, ok);
            if (ok) {
                HELP(p, 7)
            } else {
                HELP(p, 8)
            }
        } else {
            HELP(p, 9)
        }
    } else {
        int any = 0;
        UX* u = lbl_804CB814->h0c;
        while (u) {
            u32 f = u->flags;
            u = u->next;
            if (f & 0x800) {
                any = 1;
                break;
            }
        }
        if (!any) {
            HELP(p, 10)
        } else {
            HELP(p, 6)
        }
    }
    if (fn_80060728(&lbl_803CAB38)->b11 != 2 && fn_80060728(&lbl_803CAB38)->f != 1) {
        panel(fn_800677E4());
    }
    if (inputBlocked()) {
        return;
    }
    m = lbl_804CB5B8->v48();
    if (c && (m & 0x2000)) {
        fn_80185720();
        PANEL_OFF()
        fn_800451D4(&lbl_803CA870, c);
        lbl_803CA870.b11 = sx;
        lbl_803CA870.b12 = sy;
        fn_80253EE4(lbl_80361F9C + 0xe5, 0.0f);
        p->b50 = 0xb;
        fn_80083DC4(p, 0x24);
        return;
    }
    if (m & 0x400) {
        if (c) {
            deployTile(x, y, ok);
            if (!ok) {
                if (fn_8010E314(0, c->f4->b8) == 1) {
                    if (fn_80060728(&lbl_803CAB38)->b11 == 2) {
                        return;
                    }
                    if (c->flags & 0x800) {
                        return;
                    }
                    c->flags |= 0x800;
                    fn_80114D00(&lbl_803EC898);
                    fn_80067168(c);
                    fn_80253EE4(lbl_80361F9C + 0x7c, 0.0f);
                    return;
                }
                fn_80253EE4(lbl_80361F9C + 0x97, 0.0f);
                return;
            }
        }
        if ((s8)x == sx && (s8)y == sy) {
            goto cancel;
        }
        deployTile(x, y, ok);
        if (!ok) {
            goto cancel;
        }
        fn_801B5D68();
        PANEL_OFF()
        {
            FU* u1 = idUnit(*tile);
            if (u1) {
                PU* q = newProc(p);
                q->u = u1;
                q->x = x;
                q->y = y;
            }
        }
        if (c) {
            PU* q = newProc(p);
            q->u = (FU*)c;
            q->x = sx;
            q->y = sy;
        }
        fn_80253EE4(lbl_80361F9C + 0xf5, 0.0f);
        fn_80083B78(p);
        return;
    } else if (m & 0x800) {
        if (c) {
            deployTile(x, y, ok);
            if (!ok && fn_8010E314(0, c->f4->b8) == 1) {
                if (!(c->flags & 0x800)) {
                    return;
                }
                c->flags &= ~0x800ULL;
                fn_80114D00(&lbl_803EC898);
                fn_80067168(c);
                fn_80253EE4(lbl_80361F9C + 0xba, 0.0f);
                return;
            }
        }
        if (!c) {
            UX* n;
            int any;
            UX* u;
            any = 0;
            u = lbl_804CB814->h0c;
            while (u) {
                n = u->next;
                if (u->flags & 0x800) {
                    u->flags &= ~0x800ULL;
                    any = 1;
                }
                u = n;
            }
            if (any) {
                fn_80253EE4(lbl_80361F9C + 0xba, 0.0f);
                fn_80114D00(&lbl_803EC898);
                return;
            }
        }
        PANEL_OFF()
        fn_80253EE4(lbl_80361F9C + 0xd5, 0.0f);
        fn_800620A8(&lbl_803CAB38, lbl_803CA870.b11, lbl_803CA870.b12);
        fn_80083DC4(p, 7);
        return;
    } else if (m & 0x10) {
    cancel:
        PANEL_OFF()
        fn_80253EE4(lbl_80361F9C + 0xd5, 0.0f);
        fn_800620A8(&lbl_803CAB38, lbl_803CA870.b11, lbl_803CA870.b12);
        fn_80083DC4(p, 1);
    } else if (m & 0x4000) {
        PANEL_OFF()
        p->b50 = 0xb;
        fn_80083DC4(p, 0x1c);
    }
}
