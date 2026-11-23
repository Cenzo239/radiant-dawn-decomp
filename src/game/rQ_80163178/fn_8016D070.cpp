/* AI: small predicates and map helpers. */
#include "game/rQ_80163178/types.h"
#pragma use_lmw_stmw on
#define ABS(a) ((a) < 0 ? -(a) : (a))

class Filter {
public:
    virtual int check(Unit*);
};

struct ListHdr { int n; };
struct Side { Unit* head; Unit* tail; int n; };
struct B0 { int x; };
class Cls : public B0 {
public:
    virtual void v8(); virtual void vc(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual s16 v48(); virtual void v4c(); virtual s16 v50();
};
struct FF {
    void* vt;
    Unit* u;
    Filter* f;
    u8 x;
    u8 y;
};
struct F3 {
    void* vt;
    void* a;
    void* b;
    F3(void* v, void* x, void* y) {
        b = y;
        a = x;
        vt = v;
    }
};

extern "C" Unit* lbl_804CB810;
static inline Unit* UnitGet(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}
extern "C" int fn_8010E398(void*, void*);
static inline BOOL Same0(Unit* a, Unit* b) {
    return (u8)fn_8010E398(a->team, b->team) == 0;
}
extern "C" {
extern ListHdr lbl_803E7320[];
extern Side* lbl_804CB814;
extern s16 lbl_8036B278[];
extern u8 lbl_80387790[];
extern u8 lbl_803CB770[];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA500;
FE10_PROTO extern void *lbl_804CA520;
#else
extern u32 lbl_804CA500;
extern u32 lbl_804CA520;
#endif
u8* fn_80066130(u8*, int, int, int);
u8** fn_80077064(u8*);
int fn_8011F0E0(Unit*, Inv*);
int fn_80291188(const char*, u8*);
void fn_80116658(Map*, int, int);
int fn_80116A68(Map*, s8*, s8*, int, u8*);
extern Unit* lbl_804CB810;
extern u8 lbl_803CAB38[];
extern u8 lbl_8036B268[];
extern u8 lbl_80387800[];
extern u8 lbl_803877C0[];
extern u8 lbl_803877B0[];
extern u8 lbl_803877A0[];
extern u8 lbl_80387878[];
extern u8 lbl_80387928[];
extern u8 lbl_803879D4[];
extern void* lbl_803878F0[][2];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA5C0;
#else
extern u32 lbl_804CA5C0;
#endif
int fn_800A05B0(int, int, int);
void fn_800CFB34(ListHdr*);
void fn_80039708(void*, int, int);
void fn_800398E0(void*, int);
void fn_800392FC(void*, int, int);
void fn_800394E0(void*, int, int);
#if TARGET_PC
FE10_PROTO void fn_800CFC50(ListHdr*, int, int, u8, p32arg);
#else
void fn_800CFC50(ListHdr*, int, int, u8, int);
#endif
#if TARGET_PC
FE10_PROTO struct TileEntry * fn_800CFCB4(ListHdr*, int, int);
#else
int fn_800CFCB4(ListHdr*, int, int);
#endif
int fn_8012BA20(Unit*, void*);
u8 fn_80110DA8(Inv*);
int fn_8010E398(void*, void*);
int fn_8028DB44(int);
u8 fn_801107C0(u8*, Unit*);
u8 fn_801107A0(u8*, Unit*);
u8 fn_801107B8(u8*, Unit*);
u8 fn_80110880(u8*, Unit*);
s8 fn_8012408C(Unit*);
void fn_80170738(Unit*, u8, u8);
void fn_80170998(Unit*, u8, u8);
int fn_8012BB48(Unit*, void*);
void fn_801151BC(Map*, Unit*);
int fn_801D09F0(void);
s8 fn_80244CDC(void);
void fn_8023F1A0(void*, int);
int fn_8023F880(void*);
#if TARGET_PC
FE10_PROTO void fn_80168BC0(void* p);
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_80168BC0(void* p);
int fn_8011B77C(void*, u32);
#endif
void fn_80114888(Map*, int);
void fn_80114B44(Map*, int, int);
void fn_80165F94(Unit*, int, int);
u32 fn_8016CDEC(Unit*, void*);

u32 fn_8016D070(void) {
    return (u16)(lbl_804183F0.flags & 1) != 0;
}
u32 fn_8016D090(void) {
    return (u16)(lbl_804183F0.flags & 0x10) != 0;
}
u32 fn_8016D0B0(Unit* u) {
    int side;
    if ((lbl_804183F0.flags & 8) == 0) {
        return 0;
    }
    side = u ? u->team[8] : lbl_803CAB38[0x11];
    switch (side) {
    case 1:
    case 2:
    case 4:
        return 0;
    }
    return 1;
}
int fn_8016D11C(Unit* u) {
    int v = lbl_804183F0.op;
    int r;
    switch (v) {
    case -1:
        r = u->hp;
        break;
    default:
        r = v;
        break;
    }
    return r;
}

int fn_8016D144(Unit* u) {
    Inv* p = u->inv;
    int r = -1;
    u8 m = 0;
    int i;
    for (i = 0; i < 7; i++, p++) {
        if (!p || !p->item) break;
        if (fn_8012BA20(u, p->item) && m < fn_80110DA8(p)) {
            m = fn_80110DA8(p);
            r = (s8)i;
        }
    }
    return r;
}

u32 fn_8016D1DC(s8 x, s8 y, int k, int a) {
    if (!a) {
        return fn_800A05B0((u8)k, x, y);
    } else {
        struct { void* vt; u32 k; } f;
        f.vt = lbl_80387800;
        fn_800CFB34(lbl_803E7320);
        f.k = k;
        fn_80039708(&f, x, y);
        return lbl_803E7320->n != 0;
    }
}

int fn_8017062C(int x, int y, int x2, int y2, int r) {
    return r >= ABS(x - x2) + ABS(y - y2);
}

void fn_80170910(Unit* u, Inv* p) {
    s8 a = p->item ? fn_801107A0(p->item, u) : 0;
    s8 b = p->item ? fn_801107C0(p->item, u) : 0;
    fn_80170738(u, a, b);
}
void fn_80170B70(Unit* u, Inv* p) {
    s8 a = p->item ? fn_801107B8(p->item, u) : 0;
    s8 b = p->item ? fn_80110880(p->item, u) : 0;
    fn_80170998(u, a, b);
}

int fn_80170D64(Unit* u) {
    Inv* p = u->inv;
    int r = 0;
    int i;
    for (i = 0; i < 7; i++, p++) {
        u8 k;
        if (!p || !p->item) break;
        if (fn_8012BB48(u, p->item)) {
            r = 1;
            u->w3B4 |= 0x80;
            k = p->item ? p->item[0x14] : 0x13;
            switch (k) {
            case 0x81: u->w3B4 |= 0x100; break;
            case 0x84: u->w3B4 |= 0x200; break;
            case 0x83: u->w3B4 |= 0x400; break;
            }
        }
    }
    return r;
}

int fn_80170E60(Unit* u) {
    Inv* p = u->inv;
    int r = 0;
    int i;
    for (i = 0; i < 7; i++, p++) {
        if (!p || !p->item) break;
        if (fn_8012BA20(u, p->item)) {
            if ((u8)(p->item ? fn_801107A0(p->item, u) : 0) == 1) {
                u->w3B4 |= 0x800;
            }
            if ((u8)(p->item ? fn_801107C0(p->item, u) : 0) > 1) {
                u->w3B4 |= 0x1000;
            }
            r = 1;
        }
    }
    return r;
}

void fn_8017244C(void* a, void* b) {
    F3 f(lbl_803877C0, a, b);
    ListHdr* l = lbl_803E7320;
    fn_800CFB34(l);
    fn_800398E0(&f, 0);
}

void fn_8016CD04_(void);

void fn_80174FAC(void) {
    lbl_803CA870.unit->flags |= 1;
}

void fn_8017504C(void* parent) {
    fn_80081194(lbl_80387878, parent);
}

void fn_80175294(void) {
    fn_8023F1A0(lbl_803878F0[fn_80244CDC()][fn_801D09F0()], 0x2a0);
}
void fn_801752E4(void* p) {
    if (fn_8023F880(lbl_803878F0[fn_80244CDC()][fn_801D09F0()])) {
        fn_80083B78(p);
    }
}
void fn_80175DC0(void* p) {
    if (!fn_80083B84(lbl_80387928)) {
        fn_80083B78(p);
    }
}
void fn_80175E04(void* p) {
    fn_80081194(lbl_803879D4, p);
    fn_80081050(lbl_80387928, (void*)6);
}
u32 fn_8016CD04(Unit* u, void* f) {
    Map* m = &lbl_803EC898;
    if (!fn_8011B77C(u->skills, lbl_804CA5C0)) {
        return 0;
    }
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    return fn_8016CDEC(u, f);
}

u32 fn_80172494_(void);
void fn_8016CB18(void* a, void* b) {
    F3 f(lbl_80387790, a, b);
    ListHdr* l = lbl_803E7320;
    fn_800CFB34(l);
    fn_800398E0(&f, 0);
}
static inline void fn_8017244C_(void* p, void* vt, Unit* u) {
    struct G { void* vt; Unit* u; };
    ((G*)p)->vt = vt;
    ((G*)p)->u = u;
}
void fn_80172494(Unit* u, int x, int y);
void fn_8017252C(Unit* u, u8 k, s8 x, s8 y) {
    struct { void* vt; Unit* u; u8 k; } f;
    f.u = u;
    f.vt = lbl_803877A0;
    f.k = k;
    fn_800CFB34(lbl_803E7320);
    fn_801151BC(&lbl_803EC898, f.u);
    fn_800394E0(&f, x, y);
}
#pragma use_lmw_stmw off
int fn_80170664(Unit* u, Unit* v, Inv* p);
#pragma use_lmw_stmw on
u16 fn_80170C48(int x, int y, int x2, int y2) {
    if (ABS(x - x2) + ABS(y - y2) > 1) {
        return 0;
    }
    if (y2 == y - 1) {
        return (lbl_803EC898.flags[(s8)x + (s8)y * 0x40] >> 3) & 1;
    }
    if (y2 == y + 1) {
        return (lbl_803EC898.flags[(s8)x + (s8)y * 0x40] >> 2) & 1;
    }
    if (x2 == x - 1) {
        return lbl_803EC898.flags[(s8)x + (s8)y * 0x40] & 1;
    }
    if (x2 == x + 1) {
        return (lbl_803EC898.flags[(s8)x + (s8)y * 0x40] >> 1) & 1;
    }
    return 0;
}
int fn_80171378(s16 x, s16 y, Filter* f) {
    int n = 0;
    s16* d;
    for (d = lbl_8036B278; *d != 0x7FFF; d += 2) {
        BOOL out;
        int px, py;
        px = x + d[0];
        out = 0;
        py = y + d[1];
        if (px < lbl_803EC898.x0 || lbl_803EC898.x1 - 1 < px || py < lbl_803EC898.y0 || lbl_803EC898.y1 - 1 < py) {
            out = 1;
        }
        if (!out) {
            if (lbl_803EC898.ter[0][(s8)px + (s8)py * 0x40] && f->check(UnitGet(lbl_803EC898.ter[0][(s8)px + (s8)py * 0x40]))) {
                n++;
            }
        }
    }
    return n;
}
int fn_801725A0(Unit* u) {
    if (!*(int*)((u8*)u + 0x3C0)) {
        return (u8)fn_8012408C(u);
    } else {
        Unit* nx;
        u8 r = 0xFF;
        Unit* v;
        for (v = lbl_804CB814[u->team[8]].head; v; v = nx) {
            nx = v->next;
            if (!(v->flags & 8) && ((u8*)v)[0x117] == ((u8*)u)[0x117] && r >= fn_8012408C(v)) {
                r = fn_8012408C(v);
            }
        }
        return r;
    }
}
s32 fn_80172664(Unit* u, s8* ox, s8* oy) {
    AiAct* act = &lbl_803CA870;
    int s = fn_8011B77C(u->skills, lbl_804CA500);
    *ox = u->x;
    *oy = u->y;
    if (u->m3D0[0] == 0x40) {
        if (fn_8011B77C(u->skills, lbl_804CA520)) {
            return 0;
        }
        fn_80165F94(u, 6, -1);
        fn_80116658(&lbl_803EC898, act->x, (s8)*(u8*)&act->y);
        return fn_80116A68(&lbl_803EC898, ox, oy, s, 0);
    }
    return fn_80116A68(&lbl_803EC898, ox, oy, s, u->m3D0);
}
void fn_80172D7C(void* a, s8 x, s8 y) {
    u8* p = fn_80066130(lbl_803CB770, x, y, 4);
    if (p && p[4]) {
        fn_800CFC50(lbl_803E7320, x, y, 0, p[4]);
    }
}
void fn_8016CFFC(FF* f, Unit* v) {
    if (f->f->check(v)) {
        fn_800CFC50(lbl_803E7320, (s8)f->x, (s8)f->y, ((u8*)v)[0xFC], 0);
    }
}
void fn_8017505C(FF* f, Unit* v) {
    if (Same0(f->u, v) && (v->flags & 1) && !fn_800CFCB4(lbl_803E7320, v->x, (s8)*(u8*)&v->y)) {
        fn_800CFC50(lbl_803E7320, v->x, (s8)*(u8*)&v->y, ((u8*)v)[0xFC], 0);
    }
}
static inline int TblFind(Unit* u, Inv* p) {
    u8** t = fn_80077064(lbl_8036B268);
    int i;
    if (!fn_8011F0E0(u, p)) {
        return -1;
    }
    for (i = 0; *t; t++, i++) {
        char* s = p->item ? *(char**)p->item : 0;
        if (!fn_80291188(s, *t)) {
            return i;
        }
    }
    return -1;
}
BOOL fn_8016CB60(Unit* u, Inv* p) {
    return TblFind(u, p) >= 0;
}
int fn_8016CC18(Unit* u, Unit* v, int* out) {
    Inv* p = v->inv;
    int res = -1;
    int i;
    *out = res;
    for (i = 0; i < 7; i++, p++) {
        if (p && p->item) {
            int r = TblFind(u, p);
            if (r >= 0) {
                *out = r;
                res = i;
                break;
            }
        }
    }
    return res;
}
s16 fn_801751D8(Cls* c) {
    s16 a = c->v50();
    s16 t = a - c->v48() * 2;
    return t / 3;
}
}
