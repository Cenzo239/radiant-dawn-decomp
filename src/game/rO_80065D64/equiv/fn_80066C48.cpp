/* Round 20, functionally equal (check_regs.py: sched): fn_80066C48. Self-contained. Parent file with exported bodies removed plus the fragment from wip/near.cpp, use_lmw_stmw set from the original. Moved (harmless): two adjacent byte loads (lbz 0/1 of the same pointer) and their extsb are in the other order. */
/* Map objects ("traps"): list at lbl_803CB770, 80065D64..800677E0. */
#include "game/rO_80065D64/trap.h"
#pragma auto_inline off

extern "C" {
extern void fn_80111B34(void*);
extern void fn_80111C24(void*, int);
extern void fn_80079210(void*);
extern void fn_8028C0D0(void*, void*, int, int);
extern void* fn_800791B0(int);
extern Trap* fn_8028BE18(void*, int, int, int, int);
extern void* fn_800E45B0(int);
extern void fn_80081A90(void*);
extern void fn_800E4B20(void*, int);
extern int fn_8013C80C(int, int, int, int);
extern void fn_80114D00(void*);
extern char* strcpy(char*, const char*);
extern unsigned long strlen(const char*);
extern u8 lbl_803CAB38[];
extern u8 lbl_803CB4D0[];
extern u16 fn_80175E5C(void);
extern void* fn_8013B9B0(void);
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
void* fn_80065D64(void* p);

void* fn_80065D98(void* p, int del);

void fn_80065DF4(void);

char* fn_80065E10(Trap* t);


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
void fn_80065E4C(Trap* t, int arg);


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
void fn_80065FB0(Trap* t, int arg);

void fn_80066070(TrapList* l);

void fn_800660C4(TrapList* l);

int fn_800660E8(TrapList* l);

int fn_800660F0(TrapList* l, u32 type);


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
Trap* fn_80066130(TrapList* l, s8 x, s8 y, u32 type);

Trap* fn_800661A0(TrapList* l, s8 x, s8 y, u32 type, s8 ext);


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

void fn_8006625C(TrapList* l, s8 x, s8 y, u32 type);

#pragma pop

void fn_800663D8(TrapList* l, s8 x, s8 y, s8 ext, u8* item);

void fn_800664A4(TrapList* l, s8 x, s8 y, s8 ext, const char* s);


#pragma push
#pragma use_lmw_stmw on
struct Pt { s16 x, y; };
void fn_800665E4(TrapList* l, int arg);
void fn_80066968(TrapList* l);


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
void* fn_80066D18(u8* p);

#pragma pop

Trap* fn_80066DA8(TrapList* l, s8 x, s8 y, u32 type);


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
int fn_800670BC(TrapList* l, int type);

u8 fn_800670FC(Trap* t);

int fn_80067128(Trap* t, int v);

}

#pragma use_lmw_stmw on
/* ---- from build/tmp/r20small/rO/frag_fn_80066C48.cpp ---- */
extern "C" {
/* from fn_80065D64.cpp: 20 of 52 words differ */
void fn_80066C48(void) {
    int i;
    for (i = 0; i < lbl_803CB770.n; i++) {
        Trap* t = At(&lbl_803CB770, i);
        switch (t->type) {
        case 6:
            fn_80116CFC(&lbl_803EC898, t->x, t->y, t->ext);
            break;
        case 9: {
            u8* c = lbl_803EC898.ter[0] + t->x + (t->y << 6);
            if (*c == 0) {
                c[0x3000] |= 2;
            }
            break;
        }
        }
    }
}
}
