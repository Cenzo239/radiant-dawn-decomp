#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
struct Cmd;
class CmdObj {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual u8 test(int);
};
extern "C" {
extern GameState lbl_803CAB38;
extern u8 lbl_803E9000[];
extern u8 lbl_8041EB20[];
extern Unit* lbl_804CB3D8;
extern Unit* lbl_804CB3E0;
extern void* lbl_804CB3E8;
extern u8 lbl_804CB3EC;
extern u8 lbl_804CB3ED;
extern Slot lbl_803CAAE0;
extern char lbl_803CAA20[];
extern char lbl_803CAA2C[];
extern CmdObj* lbl_8037B2FC[];
extern char lbl_8037B428[];
extern char lbl_8037B490[];
extern char lbl_8037D268[];
extern char lbl_8037D274[];
extern char lbl_8037D294[];
extern char lbl_8037D2A0[];
extern void* lbl_804CA4D8;
extern void* lbl_804CA4EC;
u32 fn_80076D18(const char*);
int fn_80291188(const char*, const char*);
void fn_800453B4(CmdState*, int);
void fn_800D5448(void*, void*, int);
int fn_8011B77C(void*, void*);
void fn_800451D4(CmdState*, Unit*);
int fn_8012CA88(Unit*);
void fn_80128460(Unit*);
void fn_80081A90(void*);
void fn_801038D0(Unit*, void*);
void fn_801288D4(Unit*);
s8 fn_8012408C(Unit*);
void fn_801408AC(int);
void fn_800314CC(Slot*, void*, Unit*);
void fn_800315F8(Slot*, void*, Unit*);
int fn_80060754(void*);
void* fn_801059B0(void);
void fn_801053EC(void*, Slot*);
void fn_80110D38(Slot*);
void fn_8012A850(Unit*);
s8 fn_80127520(Unit*);
void fn_80129CB8(Unit*, int);
int fn_8012A0F4(Unit*, Slot*);
void fn_80111C78(Slot*, Slot*);
void* fn_80081194(void*, void*);
void fn_8011B32C(void*, void*);
void* fn_8011A158(void*);
void fn_80111B34(Item*);
void fn_80110BB4(Item*, void*);
void fn_80111B64(Item*, Item*);
struct Slot;
void fn_80111C24(Item*, int);
void fn_8011ABCC(void*, void*);
u8 fn_8011AB30(void*);
int fn_80127A90(Unit*);
int fn_8011B8A4(void*);
void fn_80031B24(void*, void*, Unit*);
void fn_8011A36C(void*);
void fn_80083DC4(void*, int);
int fn_801A2224(void*);
#if TARGET_PC
FE10_PROTO p32ret fn_8011A054(void*);
#else
int fn_8011A054(void*);
#endif
int fn_80290D04(char*, int, const char*, ...);
void fn_800D0B38(int, const char*);
void fn_800D0864(const char*);
#if TARGET_PC
FE10_PROTO p32ret fn_80110F08(Slot*);
#else
int fn_80110F08(Slot*);
#endif

static inline int flagFind(GameState* t, const char* name) {
    u32 h = fn_80076D18(name);
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == t->hashes[i] && fn_80291188(t->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}
static inline bool flagTestBit(GameState* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return t->bits[i >> 3] & (1 << (i & 7));
}
static inline bool flagGetBit(GameState* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return flagTestBit(t, i);
}
static inline bool flagGet(GameState* t, const char* name) {
    if (name[0] == 0) {
        return false;
    }
    return flagGetBit(t, flagFind(t, name));
}
static inline bool flagExists(GameState* t, const char* name) {
    if (flagFind(t, name) >= 0 && flagGet(t, name)) {
        return true;
    }
    return false;
}

int fn_8004A70C(const char* name) {
    return flagExists(&lbl_803CAB38, name);
}

void fn_8004A870(void* proc) {
    fn_800453B4(&lbl_803CA870, 0);
    if (lbl_803CA870.unit->f10c & 1) {
        fn_800D5448(lbl_803CAA2C, proc, 0);
    } else {
        fn_800D5448(lbl_803CAA20, proc, 0);
    }
}

int fn_8004A8EC(void) {
    Unit* u = lbl_803CA870.unit;
    int r;
    CmdObj** c;
    if (u == 0) return 0;
    if (!(u->f10c & 1)) return 0;
    if (fn_8011B77C(u->x12c, lbl_804CA4D8) == 0) return 0;
    fn_800451D4(&lbl_803CA870, u);
    r = 0;
    for (c = lbl_8037B2FC; *c; c++) {
        if ((*c)->test(0) == 0) {
            r = 1;
            break;
        }
    }
    return r;
}

void fn_8004A9F0(void* proc) {
    u8 m = 0;
    if (fn_8011B77C(lbl_803CA870.unit->x12c, lbl_804CA4EC)) m |= 1;
    if (fn_8012CA88(lbl_803CA870.unit)) m |= 2;
    switch (m) {
    case 3:
        fn_80128460(lbl_803CA870.unit);
        fn_80081A90(proc);
        break;
    case 0:
    case 1:
    case 2:
    default:
        fn_801038D0(lbl_803CA870.unit, proc);
        break;
    }
}

void fn_8004AA9C(void) {
    fn_801288D4(lbl_803CA870.unit);
    fn_801408AC(fn_8012408C(lbl_803CA870.unit));
}

void fn_8004AB40(void* proc) {
    fn_800314CC(&lbl_803CAAE0, proc, lbl_804CB3D8);
}

static inline Slot* getSlot(int i) {
    if (i == 7) {
        return &lbl_803CAAE0;
    }
    return &lbl_804CB3D8->items[i];
}

void fn_8004AB98(void) {
    if ((s8)lbl_803CA870.item == 7) {
        if (fn_80060754(&lbl_803CAB38)) {
            fn_801053EC(fn_801059B0(), &lbl_803CAAE0);
        }
    } else {
        Slot* s = getSlot((s8)lbl_803CA870.item);
        if (fn_80060754(&lbl_803CAB38)) {
            fn_801053EC(fn_801059B0(), s);
        }
        fn_80110D38(s);
        fn_8012A850(lbl_804CB3D8);
        if (fn_80127520(lbl_804CB3D8) < 0) {
            fn_80129CB8(lbl_804CB3D8, -1);
        }
        fn_8012A0F4(lbl_804CB3D8, &lbl_803CAAE0);
    }
}

#define LOCKED(p) ((p)->data && (p)->f40)


void fn_8004AED0(Slot* s) {
    s->f80 = 0;
    s->f40 = 0;
    s->f08 = 0;
    s->f04 = 0;
    fn_801053EC(lbl_803E9000, s);
}


struct ItemRef {
    void* a;
    u8 b;
    u8 c;
};

void fn_8004B03C(
#if TARGET_PC
Unit* u, ItemRef sv, void* proc
#else
Unit* u, ItemRef* s, void* proc
#endif
) {
#if TARGET_PC
    ItemRef* s = &sv;
#endif
    if (u == 0 || s->a == 0) return;
    fn_8011ABCC(u->x12c, s);
    if (fn_8011AB30(u->x12c) <= 6 && fn_80127A90(u) - fn_8011B8A4(u->x12c) >= 0) {
        fn_80031B24(s, proc, u);
        fn_8011A36C(u->x12c);
    } else {
        lbl_804CB3E0 = u;
        ((ItemRef*)&lbl_804CB3E8)->a = s->a;
        ((ItemRef*)&lbl_804CB3E8)->b = s->b;
        ((ItemRef*)&lbl_804CB3E8)->c = s->c;
        fn_80081194(lbl_8037B490, proc);
    }
}


int fn_8004B2E0(void) {
    return fn_801A2224(lbl_8041EB20) ? 0x40 : 0x10;
}

void fn_8004B338(void) {
    char buf[0x40];
    int n = fn_8011A054(lbl_804CB3E8);
    fn_80290D04(buf, 0x40, lbl_8037D274, ((u8*)lbl_804CB3E8)[0x1f] - 1, n);
    buf[0x3f] = 0;
    fn_800D0B38(0, buf);
    fn_800D0864(lbl_8037D268);
}

int fn_8004B418(void) {
    return fn_801A2224(lbl_8041EB20) ? 0x40 : 0x10;
}

void fn_8004B4B0(void) {
    char buf[0x40];
    Slot* s = getSlot((s8)lbl_803CA870.item);
    u16 m = s->data ? *(u16*)(s->data + 0x16) : 0;
    int n = fn_80110F08(s);
    fn_80290D04(buf, 0x40, lbl_8037D2A0, (u8)m + 0x80, n);
    buf[0x3f] = 0;
    fn_800D0B38(0, buf);
    fn_800D0864(lbl_8037D294);
}
}
