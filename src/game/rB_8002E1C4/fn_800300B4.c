#include "game/rB_8002E1C4/types.h"

/* skill ids (pointers in .sdata) */
extern void* lbl_804CA5E4;
extern void* lbl_804CA5E8;
extern void* lbl_804CA5EC;
extern void* lbl_804CA5F0;
extern void* lbl_804CA5F4;
extern void* lbl_804CA5F8;
extern void* lbl_804CA5FC;
extern void* lbl_804CA600;
extern void* lbl_804CA604;
extern void* lbl_804CA608;
extern void* lbl_804CA60C;
extern void* lbl_804CA610;
extern void* lbl_804CA614;
extern void* lbl_804CA618;
extern void* lbl_804CA61C;
extern void* lbl_804CA620;
extern void* lbl_804CA624;
extern void* lbl_804CA628;
extern void* lbl_804CA634;
extern void* lbl_804CA638;
extern void* lbl_804CA640;
extern void* lbl_804CA644;
extern void* lbl_804CA648;
extern void* lbl_804CA64C;
extern void* lbl_804CA5DC;
extern void* lbl_804CA670;
extern void* lbl_804CA674;
extern void* lbl_804CA680;
extern void* lbl_804CA684;
extern void* lbl_804CA688;
extern void* lbl_804CA68C;
extern void* lbl_804CA690;
extern void* lbl_804CA694;
extern void* lbl_804CA698;
extern void* lbl_804CA6E0;
extern void* lbl_804CA6E4;
extern void* lbl_804CA6E8;
extern void* lbl_804CA6EC;

int fn_8011B77C(void* skills, void* sid);  /* SkillList::has */
void fn_8011B430(void* skills, void* sid); /* SkillList::remove */
void fn_8011A36C(void* skills);
void fn_8002EBF0(BUnit* p);

#define REMOVE_SKILL(sid) \
    if (fn_8011B77C(p->x12c, sid)) { \
        fn_8011B430(p->x12c, sid); \
        removed = 1; \
    }

/* strip battle-only skills; returns whether any were removed */
int fn_800300B4(BUnit* p)
{
    int removed = 0;
    REMOVE_SKILL(lbl_804CA5E4)
    REMOVE_SKILL(lbl_804CA5E8)
    REMOVE_SKILL(lbl_804CA5EC)
    REMOVE_SKILL(lbl_804CA5F0)
    REMOVE_SKILL(lbl_804CA5F4)
    REMOVE_SKILL(lbl_804CA5F8)
    REMOVE_SKILL(lbl_804CA5FC)
    REMOVE_SKILL(lbl_804CA600)
    REMOVE_SKILL(lbl_804CA604)
    REMOVE_SKILL(lbl_804CA608)
    REMOVE_SKILL(lbl_804CA60C)
    REMOVE_SKILL(lbl_804CA610)
    REMOVE_SKILL(lbl_804CA614)
    REMOVE_SKILL(lbl_804CA618)
    REMOVE_SKILL(lbl_804CA61C)
    REMOVE_SKILL(lbl_804CA620)
    REMOVE_SKILL(lbl_804CA624)
    REMOVE_SKILL(lbl_804CA628)
    REMOVE_SKILL(lbl_804CA634)
    REMOVE_SKILL(lbl_804CA638)
    REMOVE_SKILL(lbl_804CA640)
    REMOVE_SKILL(lbl_804CA644)
    REMOVE_SKILL(lbl_804CA648)
    REMOVE_SKILL(lbl_804CA64C)
    REMOVE_SKILL(lbl_804CA5DC)
    REMOVE_SKILL(lbl_804CA670)
    REMOVE_SKILL(lbl_804CA674)
    REMOVE_SKILL(lbl_804CA680)
    REMOVE_SKILL(lbl_804CA684)
    REMOVE_SKILL(lbl_804CA688)
    REMOVE_SKILL(lbl_804CA68C)
    REMOVE_SKILL(lbl_804CA690)
    REMOVE_SKILL(lbl_804CA694)
    REMOVE_SKILL(lbl_804CA698)
    REMOVE_SKILL(lbl_804CA6E0)
    REMOVE_SKILL(lbl_804CA6E4)
    REMOVE_SKILL(lbl_804CA6E8)
    REMOVE_SKILL(lbl_804CA6EC)
    if (removed) fn_8011A36C(p->x12c);
    fn_8002EBF0(p);
    return removed;
}

/* strip temporary status skills */
int fn_8003065C(BUnit* p)
{
    int removed = 0;
    REMOVE_SKILL(lbl_804CA5E4)
    REMOVE_SKILL(lbl_804CA5E8)
    REMOVE_SKILL(lbl_804CA5EC)
    REMOVE_SKILL(lbl_804CA5F0)
    REMOVE_SKILL(lbl_804CA5F4)
    REMOVE_SKILL(lbl_804CA5F8)
    REMOVE_SKILL(lbl_804CA5FC)
    REMOVE_SKILL(lbl_804CA600)
    REMOVE_SKILL(lbl_804CA604)
    REMOVE_SKILL(lbl_804CA608)
    REMOVE_SKILL(lbl_804CA60C)
    REMOVE_SKILL(lbl_804CA610)
    REMOVE_SKILL(lbl_804CA614)
    REMOVE_SKILL(lbl_804CA618)
    REMOVE_SKILL(lbl_804CA61C)
    REMOVE_SKILL(lbl_804CA620)
    REMOVE_SKILL(lbl_804CA624)
    REMOVE_SKILL(lbl_804CA628)
    if (removed) fn_8011A36C(p->x12c);
    return removed;
}

s16 fn_801237EC(BUnit* p);

/* snapshot of battle stats before combat */
void fn_8003092C(BUnit* p)
{
    p->x468[0] = fn_801237EC(p);
    p->x468[1] = p->x114;
    p->x468[2] = p->x448[0];
    p->x468[3] = p->x448[1];
    p->x468[4] = p->x448[5];
    p->x468[5] = p->x448[8];
}

void fn_80030988(void) {}

extern BattleState lbl_803C8E80;
extern Item lbl_803EC368;
ItemData* fn_801116B8(Item* it);
int fn_800D7D74(void);
int fn_80110744(ItemData* d);
void fn_8002600C(void* obj, int id, int arg);

static inline Item* bunit_weapon(BUnit* u)
{
    if (u->x47c <= 0) return &lbl_803EC368;
    if (u->x47d != 0) return &lbl_803EC368;
    return &u->item;
}

/* use up one weapon durability point */
void fn_8003098C(BUnit* p, void* anim, int flag)
{
    if (p->x47c <= 0) return;
    if (fn_801116B8(bunit_weapon(p))->x0 & 0x10000) return;
    if (bunit_weapon(p)->b5_4) return;
    if (fn_800D7D74() != 0) return;
    if (p->x445 == 0x70 && fn_80110744(bunit_weapon(p)->data) == 0) return;
    if (!(lbl_803C8E80.flags & 4) && (fn_801116B8(bunit_weapon(p))->flags & 0x10)) return;
    p->x47c--;
    if (p->x47b == 0 && p->x47c == 0) {
        p->x47b = 1;
        if (anim != 0) fn_8002600C(anim, flag ? 0x97 : 0x99, 0);
    }
}

/* use up n durability points */
#pragma use_lmw_stmw on
void fn_80030B58(BUnit* p, void* anim, int n, int flag)
{
    int i;
    for (i = 0; i < n; i++) {
        if (p->x47c <= 0) return;
        if (fn_801116B8(bunit_weapon(p))->x0 & 0x10000) return;
        if (bunit_weapon(p)->b5_4) return;
        if (fn_800D7D74() != 0) return;
        p->x47c--;
        if (p->x47b == 0 && p->x47c == 0) {
            p->x47b = 1;
            if (anim != 0) fn_8002600C(anim, flag ? 0x97 : 0x99, 0);
        }
    }
}

#pragma use_lmw_stmw reset

/* disable the weapon */
void fn_80030C78(BUnit* p, void* anim, int flag)
{
    if (p->x47d != 0) return;
    p->x47d = 1;
    if (anim != 0) fn_8002600C(anim, flag ? 0x98 : 0x9a, 0);
}

Item* fn_80030CB4(BUnit* p) { return &p->item; }

/* BUnit::getWeapon */
Item* fn_80030CBC(BUnit* p)
{
    if (p->x47c <= 0) return &lbl_803EC368;
    if (p->x47d != 0) return &lbl_803EC368;
    return &p->item;
}

Item* fn_80030CF4(BUnit* p) { return &p->item2; }

extern void* lbl_804CA5A0;
extern void* lbl_804CA4E8;
extern void* lbl_804CA4EC;

int fn_80030CFC(BUnit* p)
{
    if (p->item2.data != 0) return 0;
    if (fn_8011B77C(p->x12c, lbl_804CA5A0)) return 0;
    if (fn_8011B77C(p->x12c, lbl_804CA4E8)) return 0;
    return !fn_8011B77C(p->x12c, lbl_804CA4EC);
}

int fn_80030D84(BUnit* p)
{
    return p->x114 == 0;
}

typedef struct Faction { u8 pad[8]; u8 x8; } Faction;
int fn_801284C4(BUnit* p);
void fn_8012857C(BUnit* p, u8 v);
void fn_80128558(BUnit* p, int v);
int fn_80067858(int a, int b, int c);

/* level / exp change notification */
void fn_80030D98(BUnit* p)
{
    BattleState* bs;
    s8 before;
    s8 after;
    before = fn_801284C4(p);
    fn_8012857C(p, p->x490[2]);
    after = fn_801284C4(p);
    if (before != after) {
        p->x484 = 1;
        bs = &lbl_803C8E80;
        fn_8002600C(bs->xde0, 0x2f, before);
        fn_8002600C(bs->xde0, 0x30, (s16)(after - before));
        if (((Faction*)p->unit->xf4)->x8 == 0) {
            bs->flags |= 0x10000;
        }
    }
}

void fn_80030E54(BUnit* p, s8 d)
{
    BattleState* bs;
    s8 before;
    int after;
    d = fn_80067858((s8)fn_801284C4(p), 0x1e, d);
    before = fn_801284C4(p);
    after = before + d;
    fn_80128558(p, (s8)after);
    if (before != after) {
        p->x484 = 1;
        bs = &lbl_803C8E80;
        fn_8002600C(bs->xde0, 0x2f, before);
        fn_8002600C(bs->xde0, 0x30, (s16)(after - before));
        if (((Faction*)p->unit->xf4)->x8 == 0) {
            bs->flags |= 0x10000;
        }
    }
}

/* colour/fog tween helper (screen effect) */
typedef struct Tween {
    u8 pad0[0x28];
    s16 x28;
    u8 pad2a[0x30 - 0x2a];
    f32 cur[3];      /* 0x30 */
    u8 x3c;
    u8 pad3d[3];
    f32 from[3];     /* 0x40 */
    f32 to[3];       /* 0x4c */
    u8 t;            /* 0x58 */
    u8 dur;          /* 0x59 */
    u8 mode;         /* 0x5a */
    u8 x5b;
    u8 x5c[0x8b - 0x5c];
    u8 x8b;
} Tween;

f32 fn_8017F68C(f32 from, f32 to, f32 t, f32 dur, u8 mode); /* interpolate */
int fn_80068D74(void);
void fn_80072488(int a, int b, u8 c, u8 d, u8 e, u8* f);
void fn_8007E7F4(void);

void fn_80031078(Tween* w)
{
    f32 y, z, x;
    z = w->cur[2];
    y = w->cur[1];
    x = w->cur[0];
    w->from[1] = y;
    w->from[0] = x;
    w->from[2] = z;
    if (w->x3c != 0) {
        w->to[0] = -100.0f;
        w->to[1] = w->cur[1];
        w->to[2] = 0.0f;
    } else {
        w->to[0] = 500.0f;
        w->to[1] = w->cur[1];
        w->to[2] = 0.0f;
    }
    w->t = 0;
    w->dur = 8;
    w->mode = 3;
}

/* stack of on-screen popup messages (Tween objects with a text at 0x5c) */
extern Tween* lbl_803CA6E0[16];
extern int lbl_804CB180;
extern u8 lbl_80379448[];
int fn_80291188(const char* a, const char* b); /* strcmp */
char* strcpy(char* d, const char* s);
#if TARGET_PC
FE10_PROTO Tween* fn_80081050(void* pool, void *);
#else
Tween* fn_80081050(void* pool, int a);
#endif
void fn_80083B78(Tween* w);

void fn_800310E4(const char* s, u8 flag, int y, u32 side)
{
    Tween* w;
    int n;
    int i;
    if (flag == 0 && lbl_804CB180 > 0 && fn_80291188((char*)lbl_803CA6E0[lbl_804CB180 - 1]->x5c, s) == 0) return;
    n = 0;
    for (i = 0; i < lbl_804CB180; i++) {
        if (side == lbl_803CA6E0[i]->x3c) n++;
    }
    if (y > 240) {
        y -= n * 36;
    } else {
        y += n * 36;
    }
    lbl_803CA6E0[lbl_804CB180++] = w = fn_80081050(lbl_80379448, 4);
    strcpy((char*)w->x5c, s);
    w->t = 0;
    w->dur = 8;
    w->mode = 6;
    w->x5b = flag;
    w->x8b = n;
    if (side != 0) {
        w->from[0] = -100.0f;
        w->from[1] = y;
        w->from[2] = 0.0f;
        w->to[0] = 0.0f;
        w->to[1] = y;
        w->to[2] = 255.0f;
        w->x3c = 1;
    } else {
        w->from[0] = 500.0f;
        w->from[1] = y;
        w->from[2] = 0.0f;
        w->to[0] = 376.0f;
        w->to[1] = y;
        w->to[2] = 255.0f;
        w->x3c = 0;
    }
}

void fn_800312BC(void)
{
    if (lbl_804CB180 == 0) return;
    fn_80083B78(lbl_803CA6E0[--lbl_804CB180]);
}

void fn_800312E8(void)
{
    while (lbl_804CB180 != 0) {
        if (lbl_804CB180 != 0) {
            fn_80083B78(lbl_803CA6E0[--lbl_804CB180]);
        }
    }
}

void fn_80031344(void)
{
    int v;
    int i;
    if (lbl_804CB180 == 0) return;
    v = 20;
    for (i = lbl_804CB180 - 1; i >= 0; i--) {
        lbl_803CA6E0[i]->x28 = v;
        v += 4;
    }
    lbl_804CB180 = 0;
}

void fn_800846BC(void* pool);

void fn_80031490(void)
{
    lbl_804CB180 = 0;
    lbl_803CA6E0[0] = 0;
    lbl_803CA6E0[1] = 0;
    lbl_803CA6E0[2] = 0;
    lbl_803CA6E0[3] = 0;
    lbl_803CA6E0[4] = 0;
    lbl_803CA6E0[5] = 0;
    lbl_803CA6E0[6] = 0;
    lbl_803CA6E0[7] = 0;
    fn_800846BC(lbl_80379448);
}
