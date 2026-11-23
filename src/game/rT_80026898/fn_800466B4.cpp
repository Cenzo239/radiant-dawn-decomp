/* Command action finish: post-action effects per command kind (names guessed). */
#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
struct Act2 {
    void* a;
    void* b;
    void* c;
    u8 kind;
    u8 padD;
    u8 bE;
    u8 padF[0x1C - 0xF];
    int x1C;
};
extern "C" {
extern u8 lbl_8037AF38[], lbl_8037B098[], lbl_8037B1A8[], lbl_8037B210[];
extern u8 lbl_803E7320[];
extern u8* lbl_804CB814;
void fn_80047164(Act2*, void*);
void fn_8011E864(void*);
void fn_8011E294(void*, void*);
void fn_8011E414(void*);
s8 fn_80127520(void*);
void fn_80129B20(void*, int);
void fn_8002BCC4(void*);
int fn_80030D84(void*);
void fn_80103D50(void*, int);
void fn_80119A88(void*, void*, int);
void* fn_800CFD18(void*, int);
void* fn_800CFB0C(void*);
void* fn_80081194(void*, void*);

static inline u8* section(int i) {
    switch (i) {
    case 0: return lbl_803C8E80;
    case 1: return lbl_803C8E80 + 0x4a0;
    case 2: return lbl_803C8E80 + 0x940;
    }
    return 0;
}
extern u8 lbl_803CAB38[];
static inline u8 lbl_803CAB38_11() { return lbl_803CAB38[0x11]; }
#define F(p, t, o) (*(t*)((u8*)(p) + (o)))
#define RESET_ALL() do { \
        int i; \
        fn_8002BCC4(lbl_803C8E80); \
        for (i = 0; i < 2; i++) { \
            u8* s = section(i); \
            if (fn_80030D84(s) == 0 && F(s, void*, 0x3F0)) fn_80103D50(F(s, void*, 0x3F0), 0x10); \
        } \
    } while (0)
#define RESET_ALL2(i, s) do { \
        fn_8002BCC4(lbl_803C8E80); \
        for (i = 0; i < 2; i++) { \
            s = section(i); \
            if (fn_80030D84(s) == 0 && F(s, void*, 0x3F0)) fn_80103D50(F(s, void*, 0x3F0), 0x10); \
        } \
    } while (0)
#define TOUCH_ALL() do { \
        int i; \
        for (i = 0; i < 2; i++) { \
            void* v = F(section(i), void*, 0x3F0); \
            if (v) fn_8011E414(v); \
        } \
    } while (0)
#define MARK_SIDE() do { \
        Unit* u = *(Unit**)(lbl_804CB814 + lbl_803CAB38_11() * 0xC); \
        while (u) { \
            Unit* nx = u->next; \
            if (!(F(u, u32, 0x10C) & 0x9D)) F(u, u32, 0x3B4) |= 0x10000; \
            u = nx; \
        } \
    } while (0)



static inline void Rst1(int i) {
    u8* s = section(i);
    if (fn_80030D84(s) == 0 && F(s, void*, 0x3F0)) fn_80103D50(F(s, void*, 0x3F0), 0x10);
}
static inline void RstAll() {
    int i;
    fn_8002BCC4(lbl_803C8E80);
    for (i = 0; i < 2; i++) Rst1(i);
}
static inline void RstAll2() {
    fn_8002BCC4(lbl_803C8E80);
    for (int i = 0; i < 2; i++) { u8* s = section(i); if (fn_80030D84(s) == 0 && F(s, void*, 0x3F0)) fn_80103D50(F(s, void*, 0x3F0), 0x10); }
}
static inline void Tch1(int i) { void* v = F(section(i), void*, 0x3F0); if (v) fn_8011E414(v); }
static inline void TchA() { int i; for (i = 0; i < 2; i++) Tch1(i); }
static inline void TchB() { for (int i = 0; i < 2; i++) { void* v = F(section(i), void*, 0x3F0); if (v) fn_8011E414(v); } }
static inline void TchC() { for (int i = 0; i < 2; i++) { u8* s = section(i); if (F(s, void*, 0x3F0)) fn_8011E414(F(s, void*, 0x3F0)); } }
static inline void TchD() { int i = 0; do { void* v = F(section(i), void*, 0x3F0); if (v) fn_8011E414(v); i++; } while (i < 2); }
void fn_800466B4(Act2* o, void* p) {
    switch (o->kind) {
    case 19:
    case 20:
        fn_80047164(o, p);
        break;
    case 25:
        if (o->x1C) fn_8011E864(o->b);
        break;
    case 26:
        fn_8011E294(o->a, o->b);
        break;
    case 15:
    case 21:
    case 22:
    case 30:
    case 43:
    case 65:
        TchA();
        break;
    case 16:
        if (fn_80127520(o->a) < 0 && lbl_803C8E80[0x47B] == 0) {
            fn_80129B20(o->a, (s8)o->bE);
        }
        break;
    case 4:
    case 53:
        if (!(F(lbl_803C8E80, u32, 0x15EC) & 0x2000)) RstAll();
        break;
    case 28:
        fn_8011E294(o->b, o->c);
        o->c = 0;
        break;
    case 29:
        fn_8011E294(o->a, o->c);
        o->c = 0;
        break;
    case 60:
        fn_80119A88(lbl_803CA870.unit, lbl_803CA870.unit2, 3);
        break;
    case 18:
    case 44:
    case 64: {
        int k;
        for (k = 0; k < *(int*)lbl_803E7320; k++) {
            Unit* u = (Unit*)fn_800CFB0C(fn_800CFD18(lbl_803E7320, k));
            *(u64*)&F(u, u32, 0x108) &= ~1ULL;
        }
        RstAll();
        fn_80081194(lbl_8037AF38, p);
        break;
    }
    case 66:
    case 67:
    case 68:
        RESET_ALL();
        fn_80081194(lbl_8037AF38, p);
        break;
    case 69:
    case 70:
    case 71:
        RESET_ALL();
        fn_80081194(lbl_8037AF38, p);
        break;
    case 72:
    case 73:
    case 74:
        RESET_ALL();
        fn_80081194(lbl_8037AF38, p);
        break;
    case 75:
    case 76:
    case 77: {
        int k;
        RESET_ALL();
        for (k = 0; k < *(int*)lbl_803E7320; k++) {
            fn_80119A88(lbl_803CA870.unit, fn_800CFB0C(fn_800CFD18(lbl_803E7320, k)), 3);
        }
        fn_80081194(lbl_8037AF38, p);
        break;
    }
    case 79:
        TOUCH_ALL();
        break;
    case 47:
        if (*(int*)lbl_803E7320 > 0) fn_80081194(lbl_8037B098, p);
        break;
    case 83:
    case 84:
    case 85:
    case 96:
        fn_8011E414(o->a);
        fn_8011E414(o->b);
        break;
    case 86:
        MARK_SIDE();
        break;
    case 87:
        RESET_ALL();
        fn_80081194(lbl_8037B1A8, p);
        break;
    case 88:
        RESET_ALL();
        fn_80081194(lbl_8037B210, p);
        break;
    case 90:
        MARK_SIDE();
        break;
    default:
        break;
    }
}
}
