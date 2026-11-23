#include "game/rD_8008E3B4/types.h"

/* The original uses stmw/lmw for multi-register saves, not _savegpr calls. */
#pragma use_lmw_stmw on

extern u8* lbl_804CB810;
extern u8* lbl_804CB814;

void fn_80126B80(void* u, int v);
void fn_80128558(void* u, s8 v);
void fn_80126D9C(void* u, int v);
void fn_8011FF10(void* u, u8 v);
u8 fn_8010E2F4(void* p);
void* fn_8012CE54(void* pid);
s8 fn_8012E9B4(void* a, void* b);
void fn_8012E8A0(void* a, int i);
int fn_8012E8BC(void* a, s8 i);
void* fn_8024BC94(void);
int fn_802457BC(void* p);
void* fn_8024BCA0(void);
int fn_80118098(void* map, s8 x, s8 y);
void fn_801151BC(void* map, void* u);
void* fn_8010B23C(void* x);
int fn_8011B680(void* list, void* skill);
int fn_8011AB30(void* list);
int fn_80127A90(void* u);
int fn_8011B8A4(void* list);
void fn_8011B32C(void* list, void* skill);
void fn_8011A36C(void* list);
#if TARGET_PC
FE10_PROTO void fn_8011AEA0(void* p, void *, int a, int b);
#else
void fn_8011AEA0(void* p, int v, int a, int b);
#endif
void fn_8011FF20(void* u, u8 v);
void fn_80111B34(void* item);
void fn_80111C24(void* item, int flag);
void* fn_8010599C(u8 army);
int fn_80060754(void* p);
void* fn_801059B0(void);
void fn_801053EC(void* p, void* item);
void fn_80110D00(void* item, u8 v);
int fn_801116F4(void* item);
void* fn_801116B8(void* item);
s8 fn_80127520(void* u);
s8 fn_80127640(void* u);
int fn_8012B35C(void* u, void* data);
void fn_8012A088(void* u, int v);
void fn_80103D50(void* u, int v);
#if TARGET_PC
FE10_PROTO void fn_80110BFC(void* item, char *);
#else
void fn_80110BFC(void* item, int v);
#endif
int fn_8012BE78(void* u);
int fn_8012BEF4(void* u);
#if TARGET_PC
FE10_PROTO void fn_8012A440(void* u, void *);
#else
void fn_8012A440(void* u, int v);
#endif
void fn_8012A80C(void* u, s8 v);
void fn_80110D38(void* item);
void fn_8012A850(void* u);
void* fn_8010B228(void* x);
int fn_8012BD30(void* u, void* item);
void fn_8010E41C(u8* mask, int v);
int fn_8011F5B4(void* u);
int fn_8011F6F8(void* u);
#if TARGET_PC
FE10_PROTO void fn_801293F0(void* u, void *);
FE10_PROTO void fn_80129438(void* u, void *);
FE10_PROTO void fn_80129480(void* u, void *);
FE10_PROTO void fn_801294C8(void* u, void *);
FE10_PROTO void fn_80129510(void* u, void *);
FE10_PROTO void fn_8011FE74(void* u, unsigned int);
#else
void fn_801293F0(void* u, int v);
void fn_80129438(void* u, int v);
void fn_80129480(void* u, int v);
void fn_801294C8(void* u, int v);
void fn_80129510(void* u, int v);
void fn_8011FE74(void* u, void* x);
#endif
#if TARGET_PC
FE10_PROTO int * fn_8010B180(int v);
#else
int fn_8010B180(int v);
#endif
#if TARGET_PC
FE10_PROTO void fn_8006234C(void* p, int a, char *);
#else
void fn_8006234C(void* p, int a, int b);
#endif
void fn_80061584(void* p, u8 v);
void fn_80061A78(void* p, u8 a, u8 b, u8 c, u8 d);
void fn_800615DC(void* p, int v);
void fn_800626E0(void* p);
void fn_80061808(void* p, f32 v);
void fn_80062780(void* p);
#if TARGET_PC
FE10_PROTO void fn_80062318(void* p, int a, char *);
#else
void fn_80062318(void* p, int a, int b);
#endif
void fn_800453B4(void* p, u8 id);
extern void* lbl_804CA4E8;
int fn_8011F428(void* u);
void* fn_8012CECC(void* pid);
void* fn_8010B200(void* x);
extern u32 lbl_804CB700;
void* fn_8009E898(void);
void fn_80186F3C(void* u, void* x);
void* fn_800C3558(void);
void fn_80126EB0(void* u, s8 x, s8 y);
void fn_8011E294(void* a, void* b);
void fn_80114D00(void* p);
extern u8 lbl_803EC898[];
extern void* lbl_804CA594;
void fn_8011FFD0(void* u);
void fn_800F74D0(void* u, int x);
void fn_800F39DC(void* u);
void fn_8011E300(void* u, s8 x, s8 y, int z);
void* fn_8002C590(void* x);
extern u8 lbl_803C8E80[];
void* fn_8010B1D8(void* x);
void* fn_8012CF28(int x, int y);
void* fn_8012D2B0(int x);
#if TARGET_PC
FE10_PROTO void* fn_8012D290(int);
#else
void* fn_8012D290(void* x);
#endif

static inline u8* GetUnit(u8 id)
{
    if (id != 0) {
        return lbl_804CB810 + (id - 1) * 0x3f0;
    }
    return NULL;
}

extern f32 lbl_804CD1B8;
extern void* lbl_804CA4EC;
u8 fn_80126B0C(void* u);
int fn_8011B77C(void* p, void* q);
s8 fn_801284C4(void* u);
f32 fn_8012786C(void* u);
u8 fn_801278F8(void* u);
s16 fn_801237EC(void* u);
s16 fn_8012386C(void* u);
s16 fn_80123998(void* u);
s16 fn_80123AC4(void* u);
s16 fn_80123BF0(void* u);
s16 fn_80123D1C(void* u);
s16 fn_80123DC4(void* u);
s16 fn_80123EF0(void* u);
s8 fn_8012401C(void* u);
s8 fn_8012408C(void* u);
s8 fn_801241F4(void* u);
u8 fn_80106E30(void* p);
s16 fn_8012C250(void* u, int stat);

int fn_8008E3B4(int id, u32 field)
{
    u8* unit = GetUnit(id);
    u8* pid;
    s8 c;
    int b;
    if (unit == NULL || (pid = *(u8**)(unit + 0xec)) == NULL) {
        return 0;
    }
    switch (field) {
    case 0:
        return 0;
    case 1:
        if (*(u8**)(unit + 0xe8) != NULL) {
            return (*(u8**)(unit + 0xe8))[0xfc];
        }
        return 0;
    case 2:
        if (*(u8**)(unit + 0xe4) != NULL) {
            return (*(u8**)(unit + 0xe4))[0xfc];
        }
        return 0;
    case 3:
        return (*(u8**)(unit + 0xf4))[8];
    case 4:
        if (*(u8**)(unit + 0xf8) != NULL) {
            return (*(u8**)(unit + 0xf8))[0xfc];
        }
        return 0;
    case 5:
        return unit[0xfc];
    case 6:
        return *(s8*)(unit + 0xfe);
    case 7:
        return fn_80126B0C(unit);
    case 8:
        b = fn_8011B77C(unit + 0x12c, lbl_804CA4EC) ? 100 : 0;
        c = fn_801284C4(unit);
        return c + b;
    case 9:
        return *(s8*)(unit + 0x102);
    case 10:
        return *(s8*)(unit + 0x103);
    case 0xb:
        return lbl_804CD1B8 * fn_8012786C(unit);
    case 0xc:
        return fn_801278F8(unit);
    case 0xd:
        return fn_801237EC(unit);
    case 0xe:
        return *(s8*)(unit + 0x114);
    case 0xf:
        return fn_8012386C(unit);
    case 0x10:
        return fn_80123998(unit);
    case 0x11:
        return fn_80123AC4(unit);
    case 0x12:
        return fn_80123BF0(unit);
    case 0x13:
        return fn_80123D1C(unit);
    case 0x14:
        return fn_80123DC4(unit);
    case 0x15:
        return fn_80123EF0(unit);
    case 0x16:
        return fn_8012401C(unit);
    case 0x17:
        return fn_8012408C(unit);
    case 0x18:
        return fn_801241F4(unit);
    case 0x19:
        return *(u16*)(unit + 0x382);
    case 0x1a:
        return *(u16*)(unit + 0x384);
    case 0x1c:
        return *(u16*)(unit + 0x388);
    case 0x1d:
        return *(u16*)(unit + 0x38a);
    case 0x21:
        return *(u16*)(unit + 0x38c);
    case 0x22:
        return unit[0x38e];
    case 0x23:
        return unit[0x38f];
    case 0x24:
        return fn_80106E30(unit + 0x390);
    case 0x25:
        return *(u16*)(pid + 0x1c);
    case 0x26:
        return *(u16*)(*(u8**)(unit + 0xf0) + 0xec);
    case 0x27:
        return unit[0xfd];
    case 0x28:
        return fn_8012C250(unit, 0);
    case 0x29:
        return fn_8012C250(unit, 1);
    case 0x2a:
        return fn_8012C250(unit, 2);
    case 0x2b:
        return fn_8012C250(unit, 3);
    case 0x2c:
        return fn_8012C250(unit, 6);
    case 0x2d:
        return fn_8012C250(unit, 7);
    case 0x2e:
        return fn_8012C250(unit, 8);
    case 0x2f:
        return fn_8012C250(unit, 0xb);
    case 0x30:
        return fn_8012C250(unit, 9);
    case 0x31:
        return fn_8012C250(unit, 10);
    case 0x32:
        return fn_8012C250(unit, 5);
    case 0x33:
        return fn_8012C250(unit, 4);
    case 0x34:
        c = *(s8*)(unit + 0x118);
        if (c == -1) {
            c = *(s8*)(pid + 0xe1);
        }
        return c;
    }
    return 0;
}

int fn_8008E768(int id, u32 field, int value)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    switch (field) {
    case 0:
        return 0;
    case 6:
        *(s8*)(unit + 0xfe) = value;
        break;
    case 7:
        fn_80126B80(unit, value);
        break;
    case 8:
        fn_80128558(unit, (s8)value);
        break;
    case 0xb:
        *(s16*)(unit + 0x37c) = value;
        break;
    case 0xe:
        fn_80126D9C(unit, value);
        break;
    case 0x19:
        *(s16*)(unit + 0x382) = value;
        break;
    case 0x27:
        fn_8011FF10(unit, (u8)value);
        break;
    case 0x34:
        *(s8*)(unit + 0x118) = value;
        break;
    }
    return value;
}

u8 fn_8008E844(int i)
{
    u8* p;
    if (i < 0 || i >= 11) {
        return 0;
    }
    p = *(u8**)(lbl_804CB814 + i * 0xc);
    if (p == NULL) {
        return 0;
    }
    return p[0xfc];
}

u8 fn_8008E880(int i)
{
    if (i < 0 || i >= 11) {
        return 0;
    }
    return fn_8010E2F4(lbl_804CB814 + i * 0xc);
}

u8 fn_8008E8AC(void* pid)
{
    u8* p = fn_8012CE54(pid);
    if (p == NULL) {
        return 0;
    }
    return p[0xfc];
}

u8 fn_8008E8E0(int id)
{
    u8* unit = GetUnit(id);
    if (unit != NULL) {
        u8* p = *(u8**)(unit + 0xf8);
        if (p != NULL && (*(u32*)(p + 0x10c) & 2)) {
            return p[0xfc];
        }
    }
    return 0;
}

u8 fn_8008E930(int id)
{
    u8* unit = GetUnit(id);
    if (unit != NULL) {
        u8* p = *(u8**)(unit + 0xf8);
        if (p != NULL && (*(u32*)(p + 0x10c) & 4)) {
            return p[0xfc];
        }
    }
    return 0;
}

u8 fn_8008E980(int i, void* x)
{
    void* key = fn_8010B1D8(x);
    u8* next;
    u8* p = *(u8**)(lbl_804CB814 + i * 0xc);
    while (p != NULL) {
        next = *(u8**)(p + 0xe8);
        if (key == *(void**)(p + 0xec)) {
            return p[0xfc];
        }
        p = next;
    }
    return 0;
}

u8 fn_8008E9E8(int x, int y)
{
    u8* p = fn_8012CF28(x, y);
    if (p != NULL) {
        return p[0xfc];
    }
    return 0;
}

u8 fn_8008EA1C(void)
{
    u8* p = fn_8012D2B0(0);
    if (p == NULL) {
        p = fn_8012D290(NULL);
    }
    if (p != NULL) {
        return p[0xfc];
    }
    return 0;
}

u8 fn_8008EA64(void)
{
    u8* p = fn_8002C590(lbl_803C8E80);
    if (p != NULL && *(u8**)(p + 0x3f0) != NULL) {
        return (*(u8**)(p + 0x3f0))[0xfc];
    }
    return 0;
}

u8 fn_8008EAAC(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL) {
        return 0;
    }
    if (*(u8**)(unit + 0xe8) != NULL) {
        return (*(u8**)(unit + 0xe8))[0xfc];
    }
    return 0;
}

u8 fn_8008EAF8(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return (*(u8**)(unit + 0xf4))[8];
}

u32 fn_8008EB40(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return *(u32*)(unit + 0x10c);
}

int fn_8008EB84(int id, int mask)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return *(unsigned long long*)(unit + 0x108) &= ~(long long)mask;
}

int fn_8008EBE8(int id, int mask)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return *(unsigned long long*)(unit + 0x108) |= (long long)mask;
}

u32 fn_8008EC44(int id, u32 mask)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return *(u32*)(unit + 0x10c) & mask;
}

int fn_8008EC8C(int id)
{
    u8* other;
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (*(u8**)(unit + 0xf8) == NULL) {
        return 0;
    }
    if (*(u32*)(unit + 0x10c) & 4) {
        unit = *(u8**)(unit + 0xf8);
    }
    other = *(u8**)(unit + 0xf8);
    fn_8011E300(unit, *(s8*)(unit + 0x102), *(s8*)(unit + 0x103), 1);
    *(unsigned long long*)(unit + 0x108) &= ~1ULL;
    *(unsigned long long*)(other + 0x108) &= ~1ULL;
    return 1;
}

int fn_8008ED74(int id1, int id2)
{
    u8* a = GetUnit(id1);
    u8* b;
    if (a == NULL || *(int*)(a + 0xec) == 0) {
        return 0;
    }
    b = GetUnit(id2);
    if (b == NULL || *(int*)(b + 0xec) == 0) {
        return 0;
    }
    fn_80126EB0(b, *(s8*)(a + 0x102) + 1, *(s8*)(a + 0x103));
    fn_8011E294(a, b);
    fn_80114D00(lbl_803EC898);
    return 1;
}

static inline u8* GetUnitEE50(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return NULL;
    }
    if (!fn_8011B77C(unit + 0x12c, lbl_804CA594)) {
        return NULL;
    }
    if (*(int*)(*(u8**)(unit + 0xf0) + 0x14) == 0) {
        return NULL;
    }
    return unit;
}

int fn_8008EE50(int id)
{
    u8* unit = GetUnitEE50(id);
    if (unit != NULL) {
        fn_8011FFD0(unit);
        fn_800F74D0(unit, 0);
        fn_800F39DC(unit);
        return 1;
    }
    return 0;
}

int fn_8008EF10(int id)
{
    u8* unit;
    if (lbl_804CB700 & 0x8001) {
        return fn_8008EE50(id);
    }
    unit = GetUnitEE50(id);
    if (unit != NULL) {
        fn_80186F3C(unit, fn_8009E898());
        unit = fn_800C3558();
        unit[0x1c] = 1;
        return 1;
    }
    return 0;
}

int fn_8008F07C(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return *(s8*)(unit + 0x102);
}

int fn_8008F0C4(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return *(s8*)(unit + 0x103);
}

int fn_8008F10C(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return *(f32*)(unit + 0x4);
}

int fn_8008F164(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return *(f32*)(unit + 0x8);
}

int fn_8008F1BC(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return fn_801237EC(unit);
}

int fn_8008F21C(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return *(s8*)(unit + 0x114);
}

int fn_8008F264(int id, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_80126D9C(unit, v);
    return 0;
}

int fn_8008F2C4(int id, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_80126B80(unit, v);
    return 0;
}

BOOL fn_8008F324(int id, void* x)
{
    u8* unit = GetUnit(id);
    void* pid;
    if (unit == NULL || (pid = *(void**)(unit + 0xec)) == NULL) {
        return 0;
    }
    return pid == fn_8010B1D8(x);
}

BOOL fn_8008F398(int id, void* x)
{
    u8* unit = GetUnit(id);
    void* job;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    job = *(void**)(unit + 0xf0);
    return job == fn_8010B200(x);
}

#define UNIT_SET_FLAG_BY_STATE(name, bit)                       \
int name(int id)                                                \
{                                                               \
    u8* unit = GetUnit(id);                                     \
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {            \
        return 0;                                               \
    }                                                           \
    switch ((*(u8**)(unit + 0xf4))[8]) {                        \
    case 0:                                                     \
    case 5:                                                     \
    case 7:                                                     \
    case 8:                                                     \
    case 9:                                                     \
    case 10:                                                    \
        *(u32*)(unit + 0x10c) |= bit;                           \
        break;                                                  \
    }                                                           \
    return 1;                                                   \
}

UNIT_SET_FLAG_BY_STATE(fn_8008F410, 0x10000)
UNIT_SET_FLAG_BY_STATE(fn_8008F494, 0x20000)
UNIT_SET_FLAG_BY_STATE(fn_8008F518, 0x200000)

typedef struct UnitPair803CA870 {
    u8* unit0;
    u8* unit1;
    u8 pad8[5];
    u8 unkD;
} UnitPair803CA870;

extern UnitPair803CA870 lbl_803CA870;

u8 fn_8008F59C(void)
{
    if (lbl_803CA870.unit0 != NULL) {
        return lbl_803CA870.unit0[0xfc];
    }
    return 0;
}

u8 fn_8008F5BC(void)
{
    if (lbl_803CA870.unit1 != NULL) {
        return lbl_803CA870.unit1[0xfc];
    }
    return 0;
}

int fn_8008F5E0(int id)
{
    fn_800453B4(&lbl_803CA870, id);
    return id;
}

u8 fn_8008F61C(void)
{
    return lbl_803CA870.unkD;
}

int fn_8008F62C(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (fn_8011B77C(unit + 0x12c, lbl_804CA4EC)) {
        return 2;
    }
    return fn_8011B77C(unit + 0x12c, lbl_804CA4E8);
}

int fn_8008F6B4(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return fn_8011F428(unit);
}

BOOL fn_8008F6F8(void* x)
{
    u8* unit = fn_8012CECC(fn_8010B1D8(x));
    if (unit == NULL) {
        return 0;
    }
    return !(*(u32*)(unit + 0x10c) & 8);
}

typedef struct Struct803CAB38 {
    s16 unk0[8];
    u8 unk10;
    u8 unk11;
    s16 unk12;
    u8 unk14[1];
} Struct803CAB38;

extern Struct803CAB38 lbl_803CAB38;

void fn_8008F73C(s16 v)
{
    lbl_803CAB38.unk12 = v;
}

int fn_8008F74C(void)
{
    return lbl_803CAB38.unk12;
}

void fn_8008F75C(u8 v)
{
    lbl_803CAB38.unk11 = v;
}

u8 fn_8008F76C(void)
{
    return lbl_803CAB38.unk11;
}

int fn_8008F77C(int a, int b, int c, int d)
{
    fn_80061A78(&lbl_803CAB38, a, b, c, d);
    return 1;
}

u8 fn_8008F7C4(int i)
{
    return lbl_803CAB38.unk14[i];
}

int fn_8008F7D8(int v)
{
    fn_800615DC(&lbl_803CAB38, v);
    return v;
}

void fn_8008F814(void)
{
    fn_800626E0(&lbl_803CAB38);
}

int fn_8008F820(int v)
{
    fn_80061808(&lbl_803CAB38, v);
    return v;
}

void fn_8008F874(void)
{
    fn_80062780(&lbl_803CAB38);
}

int fn_8008F880(int a, int b)
{
    fn_80062318(&lbl_803CAB38, a, b);
    return 1;
}

int fn_8008F8B8(int a, int b)
{
    fn_8006234C(&lbl_803CAB38, a, b);
    return 1;
}

int fn_8008F8F0(int i)
{
    return lbl_803CAB38.unk0[i];
}

int fn_8008F904(int i, int v)
{
    lbl_803CAB38.unk0[i] = v;
    return v;
}

int fn_8008F91C(int v)
{
    fn_80061584(&lbl_803CAB38, v);
    return v;
}

u8 fn_8008F958(void)
{
    return lbl_803CAB38.unk10;
}

extern s16 lbl_803E9288[];

static inline void AddClamp803E9288(u8 i, s16 amt)
{
    lbl_803E9288[i] += amt;
    if (lbl_803E9288[i] > 4950) {
        lbl_803E9288[i] = 4950;
    }
    if (lbl_803E9288[i] < 0) {
        lbl_803E9288[i] = 0;
    }
}

int fn_8008F968(int i)
{
    if (i >= 0 && i < 6) {
        AddClamp803E9288(i, 50);
    }
    return 1;
}

extern s16 lbl_803E50B0[];

int fn_8008F9C0(void)
{
    return lbl_803E50B0[0];
}

int fn_8008F9CC(void)
{
    return lbl_803E50B0[1];
}

#define UNIT_FLAGS(u) (*(unsigned long long*)((u) + 0x108))

int fn_8008F9DC(int id, void* x)
{
    u8* unit = GetUnit(id);
    u8* other;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    other = fn_8012D290(x);
    if (other != NULL) {
        UNIT_FLAGS(unit) &= ~0x100ULL;
        fn_8011FF10(unit, other[0xfd]);
    }
    fn_8011FE74(unit, x);
    fn_800F74D0(unit, 0);
    fn_800F39DC(unit);
    return 1;
}

int fn_8008FAAC(int id, int set)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (set) {
        UNIT_FLAGS(unit) |= 0x100ULL;
    } else {
        UNIT_FLAGS(unit) &= ~0x100ULL;
    }
    return 1;
}

int fn_8008FB28(int id, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (!fn_8010B180(v)) {
        return 0;
    }
    fn_8011FF10(unit, v);
    return 1;
}

int fn_8008FBBC(int v)
{
    u8 mask[16];
    int count = 0;
    int i;
    u8* unit;
    fn_8010E41C(mask, 3);
    for (i = 1; i <= 0xfe; i++) {
        unit = GetUnit(i);
        if (*(int*)(unit + 0xec) != 0 && mask[(*(u8**)(unit + 0xf4))[8]] && fn_8011F5B4(unit) &&
            !fn_8011F6F8(unit) && v == unit[0xfd]) {
            count++;
        }
    }
    return count;
}

int fn_8008FC7C(int id, u8 v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    unit[0x380] = v;
    return 1;
}

#define UNIT_CALL_IF_STATE(name, func)                          \
int name(int id, int v)                                         \
{                                                               \
    u8* unit = GetUnit(id);                                     \
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {            \
        return 0;                                               \
    }                                                           \
    if ((*(u8**)(unit + 0xf4))[8] == 0) {                       \
        return 0;                                               \
    }                                                           \
    func(unit, v);                                              \
    return 1;                                                   \
}

UNIT_CALL_IF_STATE(fn_8008FCC4, fn_801293F0)
UNIT_CALL_IF_STATE(fn_8008FD3C, fn_80129438)
UNIT_CALL_IF_STATE(fn_8008FDB4, fn_80129480)
UNIT_CALL_IF_STATE(fn_8008FE2C, fn_801294C8)
UNIT_CALL_IF_STATE(fn_8008FEA4, fn_80129510)

int fn_8008FF1C(int id, int set)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if ((*(u8**)(unit + 0xf4))[8] == 0) {
        return 0;
    }
    if (set) {
        *(u32*)(unit + 0x3b4) |= 0x2000000;
    } else {
        *(u32*)(unit + 0x3b4) &= ~0x2000000;
    }
    return 1;
}


#define UNIT_STATE_CHECK(unit)                                  \
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {            \
        return 0;                                               \
    }                                                           \
    if ((*(u8**)(unit + 0xf4))[8] == 0) {                       \
        return 0;                                               \
    }

u32 fn_8008FF9C(int id, u32 mask)
{
    u8* unit = GetUnit(id);
    UNIT_STATE_CHECK(unit)
    return *(u32*)(unit + 0x3b4) |= mask;
}

u32 fn_80090000(int id, u32 mask)
{
    u8* unit = GetUnit(id);
    UNIT_STATE_CHECK(unit)
    return *(u32*)(unit + 0x3b4) & mask;
}

u32 fn_80090060(int id, u32 mask)
{
    u8* unit = GetUnit(id);
    UNIT_STATE_CHECK(unit)
    return *(u32*)(unit + 0x3b4) &= ~mask;
}

int fn_800900C4(int id, void* x)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return fn_8012BD30(unit, fn_8010B228(x));
}

int fn_80090138(int id, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_8012A440(unit, v);
    return 1;
}

int fn_80090198(int id, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (v < 0) {
        return 0;
    }
    fn_8012A80C(unit, v);
    return 1;
}

typedef struct UnitItem {
    void* data;     /* 0x00: item data pointer */
    u8 unk4;
    u8 flag80 : 1;  /* 0x05 */
    u8 flag40 : 1;
    u8 flag20 : 1;
    u8 flag10 : 1;
    u8 flag08 : 1;
    u8 flag04 : 1;
    u8 flag02 : 1;
    u8 flag01 : 1;
    u8 pad6[0x28 - 6];
} UnitItem;

int fn_8009020C(int id)
{
    u8* unit = GetUnit(id);
    int i;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    for (i = 0; i < 7; i++) {
        fn_80110D38(&((UnitItem*)(unit + 0x1bc))[i]);
    }
    fn_8012A850(unit);
    return 1;
}

int fn_800902A8(int id, int slot, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_80110BFC(&((UnitItem*)(unit + 0x1bc))[slot], v);
    return 1;
}

u8 fn_80090318(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return fn_8012BE78(unit);
}

int fn_80090378(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return (u8)fn_8012BE78(unit) + (u8)fn_8012BEF4(unit);
}

BOOL fn_800903FC(int id, int slot)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return ((UnitItem*)(unit + 0x1bc))[slot].flag80 != 0;
}

int fn_80090458(int id, int slot)
{
    u8* unit = GetUnit(id);
    void* data;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    data = ((UnitItem*)(unit + 0x1bc))[slot].data;
    if (data != NULL) {
        return fn_8012B35C(unit, data);
    }
    return 0;
}

int fn_800904B4(int id, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_8012A088(unit, v);
    if (v >= 0 && v <= 3) {
        fn_80103D50(unit, -1);
    }
    return 1;
}

int fn_8009054C(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return fn_80127520(unit);
}

int fn_800905AC(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return fn_80127640(unit);
}

int fn_8009060C(int id)
{
    u8* unit = GetUnit(id);
    int slot;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (fn_8011B77C(unit + 0x12c, lbl_804CA4E8)) {
        return -1;
    }
    slot = fn_80127520(unit);
    if (slot < 0) {
        return -1;
    }
    ((UnitItem*)(unit + 0x1bc))[slot].flag80 = 0;
    if (slot >= 0 && slot <= 7) {
        fn_80103D50(unit, -1);
    }
    return slot;
}

int fn_800906D8(int id)
{
    u8* unit = GetUnit(id);
    int slot;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    slot = fn_80127640(unit);
    if (slot < 0) {
        return -1;
    }
    ((UnitItem*)(unit + 0x1bc))[slot].flag80 = 0;
    return slot;
}

int fn_80090764(int id, int slot)
{
    u8* unit = GetUnit(id);
    UnitItem* item;
    int i;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    item = (UnitItem*)(unit + 0x1bc);
    for (i = 0; i < 7; item++, i++) {
        if (item->data != NULL && item->flag40 && i != slot) {
            return 0;
        }
    }
    item = &((UnitItem*)(unit + 0x1bc))[slot];
    if (item != NULL && item->data == NULL) {
        return 0;
    }
    item->flag40 = 1;
    return 1;
}

int fn_8009081C(int id, int slot)
{
    u8* unit = GetUnit(id);
    UnitItem* item;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    item = &((UnitItem*)(unit + 0x1bc))[slot];
    if (item != NULL && item->data == NULL) {
        return 0;
    }
    item->flag04 = 1;
    return 1;
}

int fn_80090890(int id, int slot)
{
    u8* unit = GetUnit(id);
    UnitItem* item;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    item = &((UnitItem*)(unit + 0x1bc))[slot];
    if (item != NULL && item->data == NULL) {
        return 0;
    }
    return fn_801116F4(item);
}

int fn_800908F8(int id, int slot)
{
    u8* unit = GetUnit(id);
    UnitItem* item;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (slot < 0 || slot >= 7) {
        return 0;
    }
    item = &((UnitItem*)(unit + 0x1bc))[slot];
    if (item != NULL && item->data == NULL) {
        return 0;
    }
    if (!(*(u32*)((u8*)fn_801116B8(item) + 4) & 1)) {
        return 0;
    }
    item->flag10 = 1;
    return 1;
}

int fn_800909C0(int id)
{
    u8* unit = GetUnit(id);
    UnitItem* item;
    int i;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    item = (UnitItem*)(unit + 0x1bc);
    for (i = 0; i < 7; i++, item++) {
        if (item != NULL && item->data == NULL) {
            return 0;
        }
        item->flag08 = 0;
    }
    return 1;
}

int fn_80090B1C(int id, int slot, int v)
{
    u8* unit = GetUnit(id);
    UnitItem* item;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (slot < 0 || slot >= 7) {
        return 0;
    }
    item = &((UnitItem*)(unit + 0x1bc))[slot];
    if (item != NULL && item->data == NULL) {
        return 0;
    }
    fn_80110D00(item, v);
    return 1;
}

static inline BOOL ItemIsKept(UnitItem* item)
{
    BOOL kept = 1;
    if (!(*(u32*)fn_801116B8(item) & 0x1000000) && item->flag04 == 0) {
        kept = 0;
    }
    return kept;
}

int fn_80090BBC(int id)
{
    u8* unit = GetUnit(id);
    UnitItem* item;
    int i;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    item = (UnitItem*)(unit + 0x1bc);
    for (i = 0; i < 7; i++, item++) {
        if (item != NULL && item->data != NULL && !(*(u32*)((u8*)fn_801116B8(item) + 4) & 4)) {
            if (!ItemIsKept(item)) {
                if (fn_80060754(&lbl_803CAB38)) {
                    fn_801053EC(fn_801059B0(), item);
                }
                fn_80110D38(item);
            }
        }
    }
    fn_8012A850(unit);
    return 1;
}

int fn_80090CC0(int id, int slot)
{
    u8* unit = GetUnit(id);
    UnitItem* item;
    BOOL kept;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (!fn_80060754(&lbl_803CAB38)) {
        return 0;
    }
    item = &((UnitItem*)(unit + 0x1bc))[slot];
    if (item->data == NULL) {
        return 0;
    }
    if (*(u32*)((u8*)fn_801116B8(item) + 4) & 4) {
        return 0;
    }
    kept = 1;
    if (!(*(u32*)fn_801116B8(item) & 0x1000000) && item->flag04 == 0) {
        kept = 0;
    }
    if (kept) {
        return 0;
    }
    if (fn_80060754(&lbl_803CAB38)) {
        fn_801053EC(fn_801059B0(), item);
    }
    fn_8012A80C(unit, slot);
    return 1;
}

/* Uses a stack UnitItem with C++ ctor (fn_80111B34) / dtor (fn_80111C24(this, -1)). */
int fn_80090DFC(int v)
{
    UnitItem item;
    BOOL kept;
    if (!fn_80060754(&lbl_803CAB38)) {
        return 0;
    }
    fn_80111B34(&item);
    fn_80110BFC(&item, v);
    if (*(u32*)((u8*)fn_801116B8(&item) + 4) & 4) {
        fn_80111C24(&item, -1);
        return 0;
    }
    kept = 1;
    if (!(*(u32*)fn_801116B8(&item) & 0x1000000) && item.flag04 == 0) {
        kept = 0;
    }
    if (kept) {
        fn_80111C24(&item, -1);
        return 0;
    }
    fn_801053EC(fn_801059B0(), &item);
    fn_80111C24(&item, -1);
    return 1;
}

int fn_80090EDC(int army, int id)
{
    u8* unit = GetUnit(id);
    UnitItem* item;
    int i;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (army <= 0 || army >= 6) {
        return 0;
    }
    item = (UnitItem*)(unit + 0x1bc);
    for (i = 0; i < 7; i++, item++) {
        if (item != NULL && item->data != NULL && !(*(u32*)((u8*)fn_801116B8(item) + 4) & 4)) {
            if (!ItemIsKept(item)) {
                fn_801053EC(fn_8010599C(army), item);
                fn_80110D38(item);
            }
        }
    }
    fn_8012A850(unit);
    return 1;
}

int fn_80090FEC(int army, int id, int slot)
{
    u8* unit = GetUnit(id);
    UnitItem* item;
    BOOL kept;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (!fn_80060754(&lbl_803CAB38)) {
        return 0;
    }
    if (army <= 0 || army >= 6) {
        return 0;
    }
    item = &((UnitItem*)(unit + 0x1bc))[slot];
    if (item->data == NULL) {
        return 0;
    }
    if (*(u32*)((u8*)fn_801116B8(item) + 4) & 4) {
        return 0;
    }
    kept = 1;
    if (!(*(u32*)fn_801116B8(item) & 0x1000000) && item->flag04 == 0) {
        kept = 0;
    }
    if (kept) {
        return 0;
    }
    fn_801053EC(fn_8010599C(army), item);
    fn_8012A80C(unit, slot);
    return 1;
}

int fn_8009111C(int army, int v)
{
    UnitItem item;
    BOOL kept;
    if (army <= 0 || army >= 6) {
        return 0;
    }
    fn_80111B34(&item);
    fn_80110BFC(&item, v);
    if (*(u32*)((u8*)fn_801116B8(&item) + 4) & 4) {
        fn_80111C24(&item, -1);
        return 0;
    }
    kept = 1;
    if (!(*(u32*)fn_801116B8(&item) & 0x1000000) && item.flag04 == 0) {
        kept = 0;
    }
    if (kept) {
        fn_80111C24(&item, -1);
        return 0;
    }
    fn_801053EC(fn_8010599C(army), &item);
    fn_80111C24(&item, -1);
    return 1;
}

int fn_80091208(int army, void* x)
{
    void* key = fn_8010B228(x);
    u8* next;
    UnitItem* item;
    int found;
    u8* unit;
    BOOL changed;
    int i;
    if (key == NULL) {
        return 0;
    }
    found = 0;
    unit = *(u8**)(lbl_804CB814 + army * 0xc);
    while (unit != NULL) {
        next = *(u8**)(unit + 0xe8);
        item = (UnitItem*)(unit + 0x1bc);
        changed = 0;
        for (i = 0; i < 7; i++, item++) {
            if (item == NULL || item->data == NULL) {
                break;
            }
            if (key == item->data) {
                fn_80110D38(item);
                found = 1;
                changed = 1;
            }
        }
        if (changed) {
            fn_8012A850(unit);
        }
        unit = next;
    }
    return found;
}

typedef struct ItemList {
    int count;
    UnitItem* items;
} ItemList;

int fn_800912CC(void* x)
{
    void* key = fn_8010B228(x);
    ItemList* list;
    UnitItem* item;
    int found;
    int i;
    if (key == NULL) {
        return 0;
    }
    if (!fn_80060754(&lbl_803CAB38)) {
        return 0;
    }
    list = fn_801059B0();
    if (list == NULL) {
        return 0;
    }
    found = 0;
    for (i = 0; i < list->count; i++) {
        item = &list->items[i];
        if (item != NULL && item->data != NULL && key == item->data) {
            fn_80110D38(item);
            found = 1;
        }
    }
    return found;
}

u8 fn_800913A4(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return unit[0x117];
}

int fn_800913E8(int id, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_8011FF20(unit, v);
    return 1;
}

int fn_8009144C(int v)
{
    u8 mask[16];
    int i;
    u8* unit;
    if (v == 0) {
        return -1;
    }
    fn_8010E41C(mask, 3);
    for (i = 1; i <= 0xfe; i++) {
        unit = GetUnit(i);
        if (*(int*)(unit + 0xec) != 0 && mask[(*(u8**)(unit + 0xf4))[8]] && fn_8011F5B4(unit) &&
            (*(u32*)(unit + 0x10c) & 0x4000000) && !(*(u32*)(unit + 0x10c) & 8) && v == unit[0x117]) {
            return unit[0xfc];
        }
    }
    return -1;
}

int fn_80091538(int v)
{
    u8 mask[16];
    int count = 0;
    int i;
    u8* unit;
    if (v <= 0) {
        return -1;
    }
    fn_8010E41C(mask, 3);
    for (i = 1; i <= 0xfe; i++) {
        unit = GetUnit(i);
        if (*(int*)(unit + 0xec) != 0 && mask[(*(u8**)(unit + 0xf4))[8]] && fn_8011F5B4(unit) &&
            v == unit[0x117] && !(UNIT_FLAGS(unit) & 8)) {
            count++;
        }
    }
    return count;
}

int fn_80091610(int id, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_8011AEA0(unit + 0x12c, v, 2, 0);
    return 1;
}


/* Unit skill list at unit+0x12c: 18 entries of 8 bytes. */
typedef struct SkillEntry {
    u8* skill;      /* 0x00: skill data (0x1e: cost, 0x1f: removable?) */
    u8 kind;        /* 0x04: 2 = removable/learned? */
    u8 f80 : 1;     /* 0x05 */
    u8 f40 : 1;
    u8 f20 : 1;
    u8 f10 : 1;
    u8 f08 : 1;
    u8 f04 : 1;
    u8 free : 1;    /* 0x02: skill costs nothing */
    u8 f01 : 1;
    u8 pad6[2];
} SkillEntry;

int fn_80091854(int id, void* x)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return fn_8011B680(unit + 0x12c, fn_8010B23C(x));
}

int fn_800918C8(int id, s8* name)
{
    u8* unit = GetUnit(id);
    SkillEntry* e;
    int i;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    if (name == NULL || *name == 0) {
        e = (SkillEntry*)(unit + 0x12c);
        for (i = 0; i < 18; i++, e++) {
            if (e != NULL && e->skill != NULL && e->kind == 2) {
                fn_8011B32C(unit + 0x12c, e->skill);
            }
        }
    } else {
        fn_8011B32C(unit + 0x12c, fn_8010B23C(name));
    }
    fn_8011A36C(unit + 0x12c);
    return 1;
}

int fn_800919B0(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_8011A36C(unit + 0x12c);
    return 1;
}

u16 fn_80091A14(void* x)
{
    u8* item = fn_8010B228(x);
    if (item == NULL) {
        return 0;
    }
    return *(u16*)(item + 0xe);
}

u8 fn_80091A48(s8 x, s8 y)
{
    return fn_80118098(lbl_803EC898, x, y);
}

u8 fn_80091A84(s8 x, s8 y)
{
    return (lbl_803EC898 + 0x200d)[x + y * 64];
}

int fn_80091AA8(int id, int i)
{
    u8* unit = GetUnit(id);
    int d;
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_801151BC(lbl_803EC898, unit);
    d = ((s16*)(lbl_803EC898 + 0x15294))[i];
    if (d > 30000) {
        d = -1;
    }
    return d;
}

u32 fn_80091B40(void)
{
    return lbl_804CB700;
}

u32 fn_80091B48(void)
{
    return *(u32*)(lbl_803C8E80 + 0x15ec);
}

int fn_80091B58(void)
{
    return fn_802457BC(fn_8024BC94()) + 1;
}

int fn_80091B80(void)
{
    return 1;
}

u8 fn_80091B88(void)
{
    return ((u8*)fn_8024BCA0())[0x34];
}


u32 fn_80091DC4(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    return *(u32*)(unit + 0x3b4) &= ~0x7000000;
}

int fn_80091E10(void)
{
    return *(s8*)((u8*)fn_8024BC94() + 0x1bc8);
}
