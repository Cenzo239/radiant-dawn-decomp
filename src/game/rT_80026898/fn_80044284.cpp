#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
typedef struct FlagTable {
    u8 pad0[0x11];
    u8 b11;             /* 0x11 */
    u8 pad12[0x9a - 0x12];
    s8 s9a;
    s8 s9b;
    u8 pad9c[0x144 - 0x9c];
    char* names[0x80];  /* 0x144 */
    u32 hashes[0x80];   /* 0x344 */
    u8 bits[0x10];      /* 0x544 */
    u8 pad554[0x988 - 0x554];
} FlagTable;
extern "C" {
extern FlagTable lbl_803CAB38;
extern char lbl_80361684[0xbc];
extern char lbl_80379FA8[];
extern char lbl_80379F58[];
extern char lbl_8037A1B0[];
extern char lbl_8037A1E8[];
extern u8 lbl_803CB770[];
extern u8 lbl_803EC898[];
extern void* lbl_804CA5B8;
u32 fn_80076D18(const char*);
int fn_80291188(const char*, const char*);
void fn_802512C4(f32);
void fn_80250D64(int, f32, f32);
void fn_80250E38(int, f32, f32);
void fn_8025095C(f32, f32);
void fn_80250A08(f32, f32);
void fn_80114D00(void*);
#if TARGET_PC
FE10_PROTO void fn_801484B4(p32arg);
#else
void fn_801484B4(int);
#endif
void* fn_80083B84(void*);
void fn_80083DC4(void*, u8);
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void fn_800CD4A4(int);
void fn_80062380(void*, void*);
void fn_8024BCAC(void);
void fn_800620A8(void*, f32, f32);
void fn_8012FF30(void);
void fn_80062454(void*);
void fn_8012D620(void);
void fn_8012D908(void);
u8* fn_8006074C(void*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800680D0(void*);
#else
void* fn_800680D0(void*);
#endif
void fn_80257340(void*, int);
void fn_800785FC(const char*, int);
void fn_80092A00(u8);
int fn_8023F9F4(const char*);
void fn_80075FB4(const char*, int);
void fn_8023F1A4(const char*, int);
void fn_800F35AC(void);
int fn_8007857C(void);
void fn_80078C2C(const char*);
void fn_8012D58C(void);
void fn_8012FA44(void);
int fn_80257628(void*);
void fn_80320978(s64);
void fn_80062598(void*, void*);
char* strcpy(char*, const char*);
void fn_80291110(char*, const char*);
int fn_80060960(void*);
int fn_80060988(void*);
int fn_800609B0(void*);
void fn_8009E554(char*, void*);
void fn_8012D78C(void);
void* fn_800811E4(void*, void*);
void fn_80103D50(Unit*, int);
Slot* fn_8012759C(Unit*);
#if TARGET_PC
FE10_PROTO char * fn_80110F08(Slot*);
FE10_PROTO void fn_800310E4(p32arg, int, int, int);
#else
int fn_80110F08(Slot*);
void fn_800310E4(int, int, int, int);
#endif
void* fn_80066130(void*, int, int, int);
Slot* fn_80066D18(void*);
Slot* fn_80044FD0(CmdState*);
void fn_8011196C(Unit*, void*, void*);
u8 fn_8012408C(Unit*);
void fn_8017F44C(void*, int, int);
int fn_8011B77C(void*, void*);
Slot* fn_80127648(Unit*);
u32* fn_801116B8(Slot*);
int fn_80109348(void*);
void fn_80126EB0(Unit*, int, int);
void fn_800F39DC(Unit*);

static inline int flagFind(FlagTable* t, const char* name) {
    u32 h = fn_80076D18(name);
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == t->hashes[i] && fn_80291188(t->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}
static inline bool flagTestBit(FlagTable* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return t->bits[i >> 3] & (1 << (i & 7));
}
static inline bool flagGetBit(FlagTable* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return flagTestBit(t, i);
}
static inline bool flagGet(FlagTable* t, const char* name) {
    if (name[0] == 0) {
        return false;
    }
    return flagGetBit(t, flagFind(t, name));
}


void fn_800443F0(int a) {
    fn_80114D00(lbl_803EC898);
    fn_801484B4(a);
}

void fn_800444F4(int a) {
    fn_80083DC4(fn_80083B84(lbl_80379FA8), a);
}

struct Scripts { char a[0x34]; char b[0x1c]; char c[4]; };


static inline void scale(FlagTable* t) {
    fn_800620A8(t, t->s9a, t->s9b);
}


void fn_80044654(void) {
    u8* d = fn_8006074C(&lbl_803CAB38);
    void* h = fn_800680D0(d);
    fn_80257340(h, 0x10000);
    fn_800785FC(lbl_80361684 + 0x59, 0x180000);
    fn_80092A00(d[0x84]);
    if (fn_8023F9F4(lbl_80361684 + 0x62) != 0x40000) {
        fn_80075FB4(lbl_80361684 + 0x62, 0x40);
    }
    fn_8023F1A4(lbl_80361684 + 0x7b, 0);
    fn_800F35AC();
    fn_800785FC(lbl_80361684 + 0x8b, fn_8007857C());
    fn_80078C2C(lbl_80361684 + 0x59);
    fn_8012D58C();
    fn_8012FA44();
    while (fn_80257628(h) == 0) {
        fn_80320978(5LL * (*(u32*)0x800000F8 / 4 / 1000));
    }
}

void fn_80044758(u8* d) {
    void* h = fn_800680D0(d);
    fn_80257340(h, 0x10000);
    fn_800785FC(lbl_80361684 + 0x59, 0x180000);
    fn_80092A00(d[0x84]);
    if (fn_8023F9F4(lbl_80361684 + 0x62) != 0x40000) {
        fn_80075FB4(lbl_80361684 + 0x62, 0x40);
    }
    fn_8023F1A4(lbl_80361684 + 0x7b, 0);
    fn_800F35AC();
    fn_800785FC(lbl_80361684 + 0x8b, fn_8007857C());
    fn_80078C2C(lbl_80361684 + 0x59);
    fn_8012D58C();
    fn_8012FA44();
    while (fn_80257628(h) == 0) {
        fn_80320978(5LL * (*(u32*)0x800000F8 / 4 / 1000));
    }
}

void fn_80044914(void* a) {
    fn_80062598(&lbl_803CAB38, a);
}

void fn_80044924(void* a) {
    char buf[0x48];
    int* d = (int*)fn_8006074C(&lbl_803CAB38);
    int n = *d;
    strcpy(buf, lbl_80361684 + 0x95);
    fn_80291110(buf, (char*)n + 1);
    if (fn_80060960(&lbl_803CAB38)) {
        fn_80291110(buf, lbl_80361684 + 0x9d);
    } else if (fn_80060988(&lbl_803CAB38)) {
        fn_80291110(buf, lbl_80361684 + 0xa0);
    } else if (fn_800609B0(&lbl_803CAB38)) {
        fn_80291110(buf, lbl_80361684 + 0xa3);
    }
    fn_8009E554(buf, a);
}

void fn_80044A04(void* a) {
    fn_80062598(&lbl_803CAB38, a);
    fn_8012D78C();
}

void fn_80044AF0(void* a, void* b) {
    *(void**)((u8*)fn_800811E4(lbl_8037A1B0, b) + 0x54) = a;
}

void fn_80044B28(u8* p, f32 a, f32 b) {
    b /= 16.666666f;
    *(int*)(p + 0x10) = 0;
    *(f32*)(p + 0x1c) = *(f32*)(p + 0x18);
    *(f32*)(p + 0x20) = a;
    *(int*)(p + 0x14) = b;
}

void fn_80044B60(void) {
    fn_80103D50(lbl_803CA870.unit, -1);
}

void fn_80044B70(void) {
    if (lbl_803CA870.unit2) fn_80103D50(lbl_803CA870.unit2, -1);
}

void fn_80044B90(void) {
    fn_800310E4(fn_80110F08(fn_8012759C(lbl_803CA870.unit)), 0, 0x28, 0);
}

void fn_80044BCC(void) {
    fn_800310E4(fn_80110F08(fn_80066D18(fn_80066130(lbl_803CB770, lbl_803CA870.unit->x102, (s8)*(u8*)&lbl_803CA870.unit->y103, 7))), 0, 0x28, 0);
}

void fn_80044CE8(void* a) {
    Slot* s = fn_80044FD0(&lbl_803CA870);
    fn_8011196C(lbl_803CA870.unit, s->data, a);
}

void fn_80044E3C(void* a) {
    fn_80081194(lbl_8037A1E8, a);
}

void fn_80045120(CmdState* s, Unit* u) {
    s->unit = u;
    s->x0 = u->x102;
    s->y0 = u->y103;
    s->f15 = fn_8012408C(u);
    s->unit2 = 0;
    s->action = 0;
    SB(s->item) = -1;
    SB(s->cx) = -1;
    SB(s->cy) = -1;
    SB(s->x) = -1;
    SB(s->y) = -1;
    s->f16 = 0;
    fn_8017F44C(&s->f18, 0, 0x10);
    s->f28 = 0;
    (lbl_803EC898 + ((s8)s->x0 + ((s8)s->y0 << 6)))[0xd] = 0;
}

void fn_800451D4(CmdState* s, Unit* u) {
    s->unit = u;
    s->x0 = u->x102;
    s->y0 = u->y103;
    s->f15 = fn_8012408C(u);
    s->unit2 = 0;
    s->action = 0;
    SB(s->item) = -1;
    s->cx = u->x102;
    s->cy = u->y103;
    SB(s->x) = -1;
    SB(s->y) = -1;
    s->f16 = 0;
    fn_8017F44C(&s->f18, 0, 0x10);
    s->f28 = 0;
}

int fn_80045274(CmdState* s) {
    Unit* u = s->unit;
    if (fn_8011B77C(u->x12c, lbl_804CA5B8) == 0) {
        Slot* it = fn_80127648(u);
        if (it == 0 || it->data == 0 || !(*fn_801116B8(it) & 0x400)) return 0;
    }
    if ((s8)s->f16 != 0) return 0;
    if (s->f15 == 0) return 0;
    switch (s->action) {
    case 1:
    case 0xd:
    case 0xe:
    case 0x25:
    case 0x2a:
    case 0x2d:
    case 0x2e:
        return 0;
    }
    if (u->s114 == 0) return 0;
    if (u->f4[8] != lbl_803CAB38.b11) return 0;
    return fn_80109348(u->x110) == 0;
}

void fn_800453CC(CmdState* s) {
    Unit* u = s->unit;
    s->f16 = 1;
    FLAGS(u) &= ~1ULL;
}

void fn_800453FC(CmdState* s) {
    s->x0 = s->unit->x102;
    s->y0 = s->unit->y103;
    s->unit2 = 0;
    s->action = 0;
    SB(s->item) = -1;
    SB(s->cx) = -1;
    SB(s->cy) = -1;
    SB(s->x) = -1;
    SB(s->y) = -1;
    s->f16 = 1;
    fn_8017F44C(&s->f18, 0, 0x10);
    s->f28 = 0;
    (lbl_803EC898 + ((s8)s->x0 + ((s8)s->y0 << 6)))[0xd] = 0;
}

void fn_800454A8(CmdState* s, s8 x, s8 y) {
    fn_80126EB0(s->unit, x, y);
    fn_800F39DC(s->unit);
    s->cx = x;
    s->cy = y;
    if ((s8)s->f16 == 0) {
        s->f15 -= (*(s16**)(lbl_803EC898 + 0x15190))[x + (y << 6)];
    }
}

void fn_8004559C(CmdState* s, int a) {
    if ((s8)s->f16 == 0) s->fd = s->action;
    s->f16 = 0;
    fn_80114D00(lbl_803EC898);
    fn_801484B4(0);
    if (s->unit->s114) {
        s->unit->f388 += (u16)((s8)fn_8012408C(s->unit) - s->f15);
        if (a == 0) FLAGS(s->unit) |= 1ULL;
    }
}
}
