/* Map objects ("traps"): list at lbl_803CB770, 80065D64..800677E0. */
#include "game/rO_80065D64/trap.h"
#pragma auto_inline off

extern "C" {
extern void fn_80111B34(void*);
extern void fn_80111C24(void*, int);
extern void fn_80079210(void*);
extern void fn_8028C0D0(void*, void*, int, int);
extern void* fn_800791B0(int);
#if TARGET_PC
extern FE10_PROTO Trap* fn_8028BE18(void*, p32arg, p32arg, int, int);
#else
extern Trap* fn_8028BE18(void*, int, int, int, int);
#endif
extern void* fn_800E45B0(int);
extern void fn_80081A90(void*);
extern void fn_800E4B20(void*, int);
#if TARGET_PC
extern FE10_PROTO struct DoorProc * fn_8013C80C(int, int, int, p32arg);
#else
extern int fn_8013C80C(int, int, int, int);
#endif
extern void fn_80114D00(void*);
extern char* strcpy(char*, const char*);
extern unsigned long strlen(const char*);
extern u8 lbl_803CAB38[];
extern u8 lbl_803CB4D0[];
extern u16 fn_80175E5C(void);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_8013B9B0(void);
#else
extern void* fn_8013B9B0(void);
#endif
struct Actor { u8 pad[0x30]; struct Actor2* a30; };
struct Actor2 { u8 pad[4]; u16 h4; u8 pad6[0x18 - 6]; u32 flags; };
extern Actor* fn_800E4060(const char*, void*);
extern f32 fn_80113F00(Map*, f32, f32);
extern void fn_800E48AC(Actor*, f32, f32, f32);
extern void fn_800E4AF0(Actor*, int);

extern void fn_8008A5AC(void*, u8);
extern void fn_8008A5E4(void*, int);
extern void fn_8008A780(void*, int, void*);
extern u8 fn_8008A1A0(void*);
extern int fn_8008A1DC(void*);
extern void fn_8008A43C(void*, int, void*);
extern void fn_80116CFC(Map*, int, int, int);
extern void* fn_8010B204(u8);
extern void fn_80110BB4(void*, void*);
extern void fn_80110D00(void*, u8);
extern void __register_global_object(void*, void*, void*);
extern u8 lbl_803CB790[];
extern u8 lbl_803CB780[];
extern char lbl_804CB560[1];

void* fn_80065D64(void* p) {
    fn_80111B34((u8*)p + 4);
    return p;
}

void* fn_80065D98(void* p, int del) {
    if (p != 0) {
        fn_80111C24((u8*)p + 4, -1);
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

void fn_80065DF4(void) {
    fn_8028C0D0(lbl_803CB4D0, (void*)fn_80065D98, 0x30, 0xE);
}

char* fn_80065E10(Trap* t) {
    u32 v = t->d[0] + (t->d[1] << 8);
    v += t->d[2] << 16;
    v += t->d[3] << 24;
    return lbl_803CB770.strs + v;
}

static inline const char* TrapModel(Trap* t) {
    switch (t->type) {
    case 0xC:
        return lbl_803621A8;
    case 0x15:
        return lbl_803621A8 + 0x11;
    default:
        return 0;
    }
}

void fn_80065E4C(Trap* t, int arg) {
    const char* m = TrapModel(t);
    if (m != 0) {
        int x = t->x;
        int y = t->y;
        u16 h = fn_80175E5C();
        if (fn_8013B9B0() != 0) {
            Actor* a = fn_800E4060(m, fn_8013B9B0());
            if (a != 0) {
                a->a30->flags |= 0x1064;
                fn_800E48AC(a, 0.5f + (f32)x, 0.5f + (f32)y, fn_80113F00(&lbl_803EC898, x, y) - 0.1f);
                fn_800E4AF0(a, arg);
                a->a30->h4 = h;
                t->d[2] = h;
                t->d[3] = h >> 8;
            }
        }
    }
}

static inline void ClearActor(Trap* t, int arg) {
    if (TrapModel(t) != 0) {
        u16 h = t->d[2] + (t->d[3] << 8);
        if (h != 0) {
            void* a = fn_800E45B0(h);
            if (a != 0) {
                if (arg == 0) {
                    fn_80081A90(a);
                } else {
                    fn_800E4B20(a, arg);
                }
            }
            t->d[2] = 0;
            t->d[3] = 0;
        }
    }
}

void fn_80065FB0(Trap* t, int arg) {
    ClearActor(t, arg);
}

void fn_80066070(TrapList* l) {
    l->traps = fn_8028BE18(fn_800791B0(0x410), 0, 0, 8, 0x80);
    l->strs = (char*)fn_800791B0(0x200);
}

void fn_800660C4(TrapList* l) {
    Trap* t = l->traps;
    t->x = 0;
    t->y = 0;
    t->type = 0;
    t->ext = 0;
    l->n = 0;
    l->strn = 0;
}

int fn_800660E8(TrapList* l) {
    return l->n;
}

int fn_800660F0(TrapList* l, u32 type) {
    int c = 0;
    int i;
    for (i = 0; i < l->n; i++) {
        Trap* t = &l->traps[i];
        if (type == t->type) {
            c++;
        }
    }
    return c;
}

static inline Trap* Find(TrapList* l, s8 x, s8 y, u32 type) {
    int i;
    for (i = 0; i < l->n; i++) {
        Trap* t = &l->traps[i];
        if (x == t->x && y == t->y && (type == 0 || type == t->type)) {
            return t;
        }
    }
    return 0;
}

static inline void Remove(TrapList* l, int i) {
    ClearActor(At(l, i), 0);
    for (; i < l->n - 1; i++) {
        *At(l, i) = *At(l, i + 1);
    }
    l->n--;
}

Trap* fn_80066130(TrapList* l, s8 x, s8 y, u32 type) {
    int i;
    for (i = 0; i < l->n; i++) {
        Trap* t = At(l, i);
        if (x == t->x && y == t->y && (type == 0 || type == t->type)) {
            return t;
        }
    }
    return 0;
}

Trap* fn_800661A0(TrapList* l, s8 x, s8 y, u32 type, s8 ext) {
    Trap* t = Find(l, x, y, type);
    if (t != 0) {
        return t;
    }
    t = &l->traps[l->n];
    t->x = x;
    t->y = y;
    t->type = type;
    t->ext = ext;
    t->d[0] = 0;
    t->d[1] = 0;
    t->d[2] = 0;
    t->d[3] = 0;
    t->d[6] = 0;
    l->n++;
    return t;
}

static inline Trap* Add(TrapList* l, s8 x, s8 y, u32 type, s8 ext) {
    Trap* t = Find(l, x, y, type);
    if (t != 0) {
        return t;
    }
    t = &l->traps[l->n];
    t->x = x;
    t->y = y;
    t->type = type;
    t->ext = ext;
    t->d[0] = 0;
    t->d[1] = 0;
    t->d[2] = 0;
    t->d[3] = 0;
    t->d[6] = 0;
    l->n++;
    return t;
}

#pragma push
#pragma use_lmw_stmw on
void fn_8006625C(TrapList* l, s8 x, s8 y, u32 type) {
    int i;
    for (i = 0; i < l->n; i++) {
        Trap* t = At(l, i);
        if (x == t->x && y == t->y && (type == 0 || type == t->type)) {
            Remove(l, i);
            i--;
        }
    }
}
#pragma pop

void fn_800663D8(TrapList* l, s8 x, s8 y, s8 ext, u8* item) {
    Trap* t = Add(l, x, y, 7, ext);
    u8 b = item[0x1B];
    t->d[0] = *(u16*)(item + 0xE);
    t->d[1] = b;
    t->d[2] = 0;
    t->d[3] = 0;
}

void fn_800664A4(TrapList* l, s8 x, s8 y, s8 ext, const char* s) {
    Trap* t = Add(l, x, y, 0xA, ext);
    TrapList* g = &lbl_803CB770;
    u32 off = g->strn;
    strcpy(g->strs + off, s);
    g->strn += strlen(s) + 1;
    t->d[0] = off;
    t->d[1] = off >> 8;
    t->d[2] = off >> 16;
    t->d[3] = off >> 24;
}

#pragma push
#pragma use_lmw_stmw on
struct Pt { s16 x, y; };
void fn_800665E4(TrapList* l, int arg);

void fn_80066968(TrapList* l) {
    int i;
    for (i = 0; i < l->n; i++) {
        Trap* t = At(l, i);
        switch (t->type) {
        case 2:
        case 3:
        case 4:
        case 6:
        case 0xC:
        case 0xD:
        case 0xF:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x15:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
            Remove(l, i);
            i--;
        }
    }
}

static inline void TrapSave(Trap* t, void* f) {
    int j;
    fn_8008A5AC(f, t->x);
    fn_8008A5AC(f, t->y);
    fn_8008A5AC(f, t->type);
    fn_8008A5AC(f, t->ext);
    for (j = 0; j < 4; j++) {
        fn_8008A5AC(f, t->d[j]);
    }
}

static inline void TrapLoad(Trap* t, void* f) {
    int j;
    t->x = fn_8008A1A0(f);
    t->y = fn_8008A1A0(f);
    t->type = fn_8008A1A0(f);
    t->ext = fn_8008A1A0(f);
    for (j = 0; j < 4; j++) {
        t->d[j] = fn_8008A1A0(f);
    }
}

void fn_80066AC0(TrapList* l, void* f);

void fn_80066B84(TrapList* l, void* f);

void fn_80066C48(void);

void* fn_80066D18(u8* p) {
    if (!lbl_804CB560[0]) {
        fn_80111B34(lbl_803CB790);
        __register_global_object(lbl_803CB790, (void*)fn_80111C24, lbl_803CB780);
        lbl_804CB560[0] = 1;
    }
    fn_80110BB4(lbl_803CB790, fn_8010B204(p[4]));
    fn_80110D00(lbl_803CB790, p[5]);
    return lbl_803CB790;
}
#pragma pop

Trap* fn_80066DA8(TrapList* l, s8 x, s8 y, u32 type) {
    int i;
    for (i = 0; i < l->n; i++) {
        Trap* t = At(l, i);
        int dx = x - t->x;
        int dy = y - t->y;
        if (dx * dx + dy * dy <= 1 && (type == 0 || type == t->type)) {
            return t;
        }
    }
    return 0;
}

static inline int DirX(u8 d) {
    switch (d) {
    case 1:
        return -1;
    case 2:
        return 1;
    default:
        return 0;
    }
}

static inline int DirY(u8 d) {
    switch (d) {
    case 4:
        return 1;
    case 8:
        return -1;
    default:
        return 0;
    }
}

static inline Trap* FindType(TrapList* l, s8 x, s8 y, u32 type) {
    Trap* t = l->traps;
    int i;
    for (i = 0; i < l->n; i++) {
        if (x == t->x && y == t->y && type == t->type) {
            return t;
        }
        t++;
    }
    return 0;
}

Trap* fn_80066E24(TrapList* l, int x, int y, int mode);

int fn_800670BC(TrapList* l, int type) {
    int i;
    for (i = 0; i < l->n; i++) {
        Trap* t = At(l, i);
        if (type == t->type) {
            return 1;
        }
    }
    return 0;
}

u8 fn_800670FC(Trap* t) {
    return lbl_803EC898.ter[0][t->x + (t->y << 6)];
}

int fn_80067128(Trap* t, int v) {
    int m = t->d[0];
    if (m == 0) {
        return 0;
    }
    if (v < m) {
        return 0;
    }
    return (v - m) % m == 0;
}
}
