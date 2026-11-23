#include "game/rB_8002E1C4/types.h"

typedef struct JobData {
    u8 pad[0xe1];
    u8 xe1;
} JobData;

/* stat bonus block filled by fn_8002FC64 / fn_80119424 */
typedef struct StatBonus {
    u8 pad[4];
    s8 atk;
    s8 hit;
    s8 avo;
    s8 crit;
    s8 x8;
    s8 x9;
} StatBonus;

void fn_8002FA8C(BUnit* p, BUnit* q)
{
    p->x448[5] = p->x448[3] - q->x448[4];
    p->x448[8] = p->x448[6] - q->x448[7];
}

void fn_8002FC64(BUnit* p, StatBonus* b, int c);

void fn_8002FAB0(BUnit* p)
{
    StatBonus b;
    b.x9 = 0;
    b.x8 = 0;
    b.crit = 0;
    b.avo = 0;
    b.hit = 0;
    b.atk = 0;
    fn_8002FC64(p, &b, 0);
    p->x448[0] += b.atk;
    p->x448[1] += b.hit;
    p->x448[3] += b.avo;
    p->x448[4] += b.crit;
    p->x448[6] += b.x8;
    p->x448[7] += b.x9;
}


typedef struct GameState {
    u8 pad[0x92];
    u8 x92;
} GameState;
extern GameState lbl_803CAB38;
void fn_80119424(StatBonus* b, u8 a, u8 c);

void fn_8002FB78(BUnit* p)
{
    StatBonus b;
    u8 m = lbl_803CAB38.x92;
    u8 c;
    b.x9 = 0;
    b.x8 = 0;
    b.crit = 0;
    b.avo = 0;
    b.hit = 0;
    b.atk = 0;
    c = p->x118;
    fn_80119424(&b, (s8)c == -1 ? p->xec->xe1 : c, m);

    p->x448[0] += b.atk;
    p->x448[1] += b.hit;
    p->x448[3] += b.avo;
    p->x448[4] += b.crit;
    p->x448[6] += b.x8;
    p->x448[7] += b.x9;
}

extern u32 lbl_804CB700;
BUnit* fn_8012E3A4(BUnit* p);
u8 fn_80126F34(BUnit* a, BUnit* b);
int fn_8012E944(BUnit* a, JobData* j);
u8 fn_8012E8BC(BUnit* a, int b);
void fn_8012EC2C(BUnit* a, u8 b, StatBonus* s);
void fn_80119760(StatBonus* s);

/* support bonus calculation */
void fn_8002FC64(BUnit* p, StatBonus* b, int force)
{
    BUnit* q;
    s8 c;
    u8 r;
    b->x9 = 0;
    b->x8 = 0;
    b->crit = 0;
    b->avo = 0;
    b->hit = 0;
    b->atk = 0;
    if (lbl_804CB700 & 0x10000) return;
    q = fn_8012E3A4(p);
    if (q != 0) {
        if (force != 0 ||
            (p->xf4 == q->xf4 && !(p->x10c & 0x18) && !(q->x10c & 0x18) && fn_80126F34(p, q) <= 3)) {
            c = fn_8012E944(p, q->xec);
            fn_8012E944(q, p->xec);
            r = fn_8012E8BC(p, c);
            fn_8012EC2C(p, r, b);
            fn_8012EC2C(q, r, b);
            p->x49c = (u32)q;
        }
    }
    fn_80119760(b);
}

extern void* lbl_804CA6AC;
extern void* lbl_804CA63C;
Item* fn_80127648(BUnit* p);
ItemData* fn_801116B8(Item* it);
int fn_8011B77C(void* a, void* b);

void fn_8002FD84(BUnit* p, BUnit* q)
{
    Item* it;
    if (p->x108 & 0x200) {
        p->x448[5] /= 2;
        p->x448[8] *= 2;
    }
    if (p->x108 & 0x400) {
        p->x448[0] /= 2;
    }
    if ((q->x110 >> 1) & 7) p->x448[5] = 100;
    if (q->x110 & 1) p->x448[5] = 100;
    if (fn_8011B77C(q->x12c, lbl_804CA6AC)) p->x448[8] = 0;
    if (q->item2.data != 0 && (fn_801116B8(&q->item2)->flags & 0x10000)) p->x448[8] = 0;
    it = fn_80127648(p);
    if (it != 0 && it->data != 0 && (fn_801116B8(it)->flags & 0x10000)) p->x448[8] = 0;
    if (fn_8011B77C(q->x12c, lbl_804CA63C)) p->x448[8] = 0;
}

/* clamp hit/crit to 0..100 */
void fn_8002FEC0(BUnit* p)
{
    if (p->x448[5] > 100) p->x448[5] = 100;
    if (p->x448[5] < 0) p->x448[5] = 0;
    if (p->x448[8] > 100) p->x448[8] = 100;
    if (p->x448[8] < 0) p->x448[8] = 0;
}

typedef struct DebugFlags {
    u8 flags[0xa0];
    u8 idx;
} DebugFlags;
extern DebugFlags lbl_803C8DA0;
extern BattleState lbl_803C8E80;
int fn_80089DE8(int hit);
int fn_80089D68(int crit);

/* roll attack result: 0x6e normal hit, 0x6f crit, 0x70 miss */
int fn_8002FF14(BUnit* p)
{
    u8 f = lbl_803C8DA0.flags[lbl_803C8DA0.idx];
    if (f & 4) return 0x70;
    if (f & 2) return 0x6f;
    if (f & 1) return 0x6e;
    if (p->x480 != 0) {
        p->x480 = 0;
        lbl_803C8E80.flags |= 0x1000;
        return 0x6f;
    }
    if (fn_80089DE8(p->x448[5]) == 0) return 0x70;
    return fn_80089D68(p->x448[8]) ? 0x6f : 0x6e;
}

