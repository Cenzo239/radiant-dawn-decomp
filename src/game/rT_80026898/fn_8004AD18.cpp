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
FE10_PROTO char * fn_8011A054(void*);
#else
int fn_8011A054(void*);
#endif
int fn_80290D04(char*, int, const char*, ...);
void fn_800D0B38(int, const char*);
void fn_800D0864(const char*);
#if TARGET_PC
FE10_PROTO char * fn_80110F08(Slot*);
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

static inline Slot* getSlot(int i) {
    if (i == 7) {
        return &lbl_803CAAE0;
    }
    return &lbl_804CB3D8->items[i];
}

#define LOCKED(p) ((p)->data && (p)->f40)


struct ItemRef {
    void* a;
    u8 b;
    u8 c;
};


void fn_8004AD18(Unit* u, Slot* s, void* proc) {
    Slot* p;
    s->f80 = 0;
    s->f40 = 0;
    s->f08 = 0;
    s->f04 = 0;
    if (u->f4[8] == 1) {
        int i; p = u->items;
        for (i = 0; i < 7; i++, p++) if (LOCKED(p)) goto skip;
        s->f40 = 1;
    }

skip:
    if (fn_8012A0F4(u, s)) {
        if (u->f4[8] != 1) {
            fn_800314CC(s, proc, u);
        } else {
            fn_800315F8(s, proc, u);
        }
    } else {
        switch (u->f4[8]) {
        case 0:
        case 5:
        case 7:
        case 8:
        case 9:
        case 10:
            lbl_804CB3D8 = u;
            fn_80111C78(&lbl_803CAAE0, s);
            fn_80081194(lbl_8037B428, proc);
            break;
        }
    }
}



static inline SkillEnt* At(Unit* u, int i) { return &u->skills[i]; }
static inline SkillEnt* At2(Unit* u, int i) { return (SkillEnt*)(u->x12c + i * 8); }
void fn_8004B120(Unit* u, void* proc) {
    SkillEnt* e;
    u8* d;
    int f;
    int i;
    if (u == 0) return;
    if (fn_8011AB30(u->x12c) <= 6 && fn_80127A90(u) - fn_8011B8A4(u->x12c) >= 0) {
        fn_8011A36C(u->x12c);
        return;
    }
    f = 0;
for (i = 0; i < 18; i++) { e = At2(u, i); if (e && (d = e->d) && d[0x1f] && !(e->b5 & 1)) { f = 1; break; } }

    if (f) {
        lbl_804CB3E0 = u;
        lbl_804CB3E8 = 0;
        fn_80083DC4(fn_80081194(lbl_8037B490, proc), 10);
    } else {
        fn_8011A36C(u->x12c);
    }
}
}
