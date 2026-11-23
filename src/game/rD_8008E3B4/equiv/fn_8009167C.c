/* EQUIVALENT (register-only, round 19): fn_8009167C at regs level (30 words in the unrolled inner loop); wip fragment made self-contained. */
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
void fn_8011AEA0(void* p, int v, int a, int b);
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
void fn_80110BFC(void* item, int v);
int fn_8012BE78(void* u);
int fn_8012BEF4(void* u);
void fn_8012A440(void* u, int v);
void fn_8012A80C(void* u, s8 v);
void fn_80110D38(void* item);
void fn_8012A850(void* u);
void* fn_8010B228(void* x);
int fn_8012BD30(void* u, void* item);
void fn_8010E41C(u8* mask, int v);
int fn_8011F5B4(void* u);
int fn_8011F6F8(void* u);
void fn_801293F0(void* u, int v);
void fn_80129438(void* u, int v);
void fn_80129480(void* u, int v);
void fn_801294C8(void* u, int v);
void fn_80129510(void* u, int v);
void fn_8011FE74(void* u, void* x);
int fn_8010B180(int v);
void fn_8006234C(void* p, int a, int b);
void fn_80061584(void* p, u8 v);
void fn_80061A78(void* p, u8 a, u8 b, u8 c, u8 d);
void fn_800615DC(void* p, int v);
void fn_800626E0(void* p);
void fn_80061808(void* p, f32 v);
void fn_80062780(void* p);
void fn_80062318(void* p, int a, int b);
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
void* fn_8012D290(void* x);

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
int fn_8008E3B4(int id, u32 field);

int fn_8008E768(int id, u32 field, int value);

u8 fn_8008E844(int i);

u8 fn_8008E880(int i);

u8 fn_8008E8AC(void* pid);

u8 fn_8008E8E0(int id);

u8 fn_8008E930(int id);

u8 fn_8008E980(int i, void* x);

u8 fn_8008E9E8(int x, int y);

u8 fn_8008EA1C(void);

u8 fn_8008EA64(void);

u8 fn_8008EAAC(int id);

u8 fn_8008EAF8(int id);

u32 fn_8008EB40(int id);

int fn_8008EB84(int id, int mask);

int fn_8008EBE8(int id, int mask);

u32 fn_8008EC44(int id, u32 mask);

int fn_8008EC8C(int id);

int fn_8008ED74(int id1, int id2);


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
int fn_8008EE50(int id);

int fn_8008EF10(int id);

int fn_8008F07C(int id);

int fn_8008F0C4(int id);

int fn_8008F10C(int id);

int fn_8008F164(int id);

int fn_8008F1BC(int id);

int fn_8008F21C(int id);

int fn_8008F264(int id, int v);

int fn_8008F2C4(int id, int v);

BOOL fn_8008F324(int id, void* x);

BOOL fn_8008F398(int id, void* x);


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





typedef struct UnitPair803CA870 {
    u8* unit0;
    u8* unit1;
    u8 pad8[5];
    u8 unkD;
} UnitPair803CA870;

extern UnitPair803CA870 lbl_803CA870;
u8 fn_8008F59C(void);

u8 fn_8008F5BC(void);

int fn_8008F5E0(int id);

u8 fn_8008F61C(void);

int fn_8008F62C(int id);

int fn_8008F6B4(int id);

BOOL fn_8008F6F8(void* x);


typedef struct Struct803CAB38 {
    s16 unk0[8];
    u8 unk10;
    u8 unk11;
    s16 unk12;
    u8 unk14[1];
} Struct803CAB38;

extern Struct803CAB38 lbl_803CAB38;
void fn_8008F73C(s16 v);

int fn_8008F74C(void);

void fn_8008F75C(u8 v);

u8 fn_8008F76C(void);

int fn_8008F77C(int a, int b, int c, int d);

u8 fn_8008F7C4(int i);

int fn_8008F7D8(int v);

void fn_8008F814(void);

int fn_8008F820(int v);

void fn_8008F874(void);

int fn_8008F880(int a, int b);

int fn_8008F8B8(int a, int b);

int fn_8008F8F0(int i);

int fn_8008F904(int i, int v);

int fn_8008F91C(int v);

u8 fn_8008F958(void);


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
int fn_8008F968(int i);


extern s16 lbl_803E50B0[];
int fn_8008F9C0(void);

int fn_8008F9CC(void);


#define UNIT_FLAGS(u) (*(unsigned long long*)((u) + 0x108))

int fn_8008F9DC(int id, void* x);

int fn_8008FAAC(int id, int set);

int fn_8008FB28(int id, int v);

int fn_8008FBBC(int v);

int fn_8008FC7C(int id, u8 v);


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

int fn_8008FF1C(int id, int set);



#define UNIT_STATE_CHECK(unit)                                  \
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {            \
        return 0;                                               \
    }                                                           \
    if ((*(u8**)(unit + 0xf4))[8] == 0) {                       \
        return 0;                                               \
    }

u32 fn_8008FF9C(int id, u32 mask);

u32 fn_80090000(int id, u32 mask);

u32 fn_80090060(int id, u32 mask);

int fn_800900C4(int id, void* x);

int fn_80090138(int id, int v);

int fn_80090198(int id, int v);


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
int fn_8009020C(int id);

int fn_800902A8(int id, int slot, int v);

u8 fn_80090318(int id);

int fn_80090378(int id);

BOOL fn_800903FC(int id, int slot);

int fn_80090458(int id, int slot);

int fn_800904B4(int id, int v);

int fn_8009054C(int id);

int fn_800905AC(int id);

int fn_8009060C(int id);

int fn_800906D8(int id);

int fn_80090764(int id, int slot);

int fn_8009081C(int id, int slot);

int fn_80090890(int id, int slot);

int fn_800908F8(int id, int slot);

int fn_800909C0(int id);

int fn_80090B1C(int id, int slot, int v);


static inline BOOL ItemIsKept(UnitItem* item)
{
    BOOL kept = 1;
    if (!(*(u32*)fn_801116B8(item) & 0x1000000) && item->flag04 == 0) {
        kept = 0;
    }
    return kept;
}
int fn_80090BBC(int id);

int fn_80090CC0(int id, int slot);

int fn_80090DFC(int v);

int fn_80090EDC(int army, int id);

int fn_80090FEC(int army, int id, int slot);

int fn_8009111C(int army, int v);

int fn_80091208(int army, void* x);


typedef struct ItemList {
    int count;
    UnitItem* items;
} ItemList;
int fn_800912CC(void* x);

u8 fn_800913A4(int id);

int fn_800913E8(int id, int v);

int fn_8009144C(int v);

int fn_80091538(int v);

int fn_80091610(int id, int v);



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
int fn_80091854(int id, void* x);

int fn_800918C8(int id, s8* name);

int fn_800919B0(int id);

u16 fn_80091A14(void* x);

u8 fn_80091A48(s8 x, s8 y);

u8 fn_80091A84(s8 x, s8 y);

int fn_80091AA8(int id, int i);

u32 fn_80091B40(void);

u32 fn_80091B48(void);

int fn_80091B58(void);

int fn_80091B80(void);

u8 fn_80091B88(void);

u32 fn_80091DC4(int id);

int fn_80091E10(void);


/* ---- from build/tmp/r19hpbs/frag_167c.c ---- */
static inline u8 SkillEntryCost(SkillEntry* e)
{
    return e->free ? 0 : e->skill[0x1e];
}

static inline SkillEntry* FindCheapestSkill(SkillEntry* e)
{
    u8 bestCost = 0xff;
    SkillEntry* best = NULL;
    int i;
    for (i = 0; i < 18; e++, i++) {
        if (e != NULL && e->skill != NULL && e->skill[0x1f] != 0 && SkillEntryCost(e) != 0 &&
            SkillEntryCost(e) < bestCost) {
            bestCost = SkillEntryCost(e);
            best = e;
        }
    }
    return best;
}

int fn_8009167C(int id, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_8011AEA0(unit + 0x12c, v, 2, 0);
    while ((u8)fn_8011AB30(unit + 0x12c) > 6 || fn_80127A90(unit) - fn_8011B8A4(unit + 0x12c) < 0) {
        fn_8011B32C(unit + 0x12c, FindCheapestSkill((SkillEntry*)(unit + 0x12c))->skill);
        fn_8011A36C(unit + 0x12c);
    }
    return 1;
}