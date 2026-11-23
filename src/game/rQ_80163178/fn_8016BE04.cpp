/* AI: move toward the nearest ally of the leading unit of v's army (names guessed). Round 18: the separate lis register (lis r7; addi r21,r7) comes from the local m plus &lbl_803EC898 passed straight to the MapOutU inline. */
#include "game/rQ_80163178/common.h"
extern "C" {
void fn_80167704(u8*);
void fn_8010E41C(u8*, int);
u16 fn_801676D8(int, int);
void fn_80166720(Unit*);
void fn_80165F94(Unit*, int, int);
void fn_80165CB0(int, int, Unit*, int, int);
int fn_801658E4(Unit*, s8, s8);
int fn_801108F8(Unit*);
}
static inline BOOL SameT(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}
#define ABS(a) ((a) < 0 ? -(a) : (a))
static inline int Ab(int a) { return __abs(a); }
static inline Map* GetM() { return &lbl_803EC898; }
extern "C" u32 fn_8016BE04(Unit* u, Unit* v, s16* ox, s16* oy) {
/*P*/
    Map* m;
    Unit* w;
    int id;
    Unit* lead;
    int bs;
    Unit* b;
    int y;
    int x;
    int r;
    u16 k;
    int y3;
    int x3;
/*E*/
    u8 tbl[0xB];
    m = &lbl_803EC898;
    fn_80167704(v->team);
    lead = 0;
    fn_8010E41C(tbl, 0);
    for (id = 1; id <= 0xFE; id++) {
        w = UnitGet(id);
        if (w->person && tbl[w->team[8]] && !MapOutU(&lbl_803EC898, w) && !(w->flags10C & 0x10000DC) && fn_801676D8(w->x, w->y)) {
            lead = w;
        }
    }
    if (!lead) {
        fn_80166720(u);
        return 0;
    }
    fn_80165F94(lead, 7, lbl_803EC898.w * lbl_803EC898.h);
    bs = 0xFF;
    b = 0;
    for (y = ((Map*)&lbl_803EC898)->y0; y <= ((Map*)&lbl_803EC898)->y1 - 1; y++) {
        for (x = ((Map*)&lbl_803EC898)->x0; x <= ((Map*)&lbl_803EC898)->x1 - 1; x++) {
            if (((Map*)&lbl_803EC898)->cost2S[(s8)x + (s8)y * 0x40] >= 0 && ((Map*)&lbl_803EC898)->b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && ((Map*)&lbl_803EC898)->ter[0][(s8)x + (s8)y * 0x40]) {
                w = UnitGet(((Map*)&lbl_803EC898)->ter[0][(s8)x + (s8)y * 0x40]);
                if (SameT(lead, w, 1) && m->cost2S[(s8)x + (s8)y * 0x40] < bs) {
                    bs = (u8)m->cost2S[(s8)x + (s8)y * 0x40];
                    b = w;
                }
            }
        }
    }
    if (!b) {
        fn_80166720(u);
        return 0;
    }
    fn_80165CB0(b->x, b->y, v, 7, -1);
    {
        int K = 0x10000;
        k = K - 1;
        r = fn_801108F8(u);
        for (y3 = ((Map*)&lbl_803EC898)->y0; y3 <= lbl_803EC898.y1 - 1; y3++) {
            for (x3 = lbl_803EC898.x0; x3 <= lbl_803EC898.x1 - 1; x3++) {
                if (lbl_803EC898.cost2S[(s8)x3 + (s8)y3 * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x3 + (s8)y3 * 0x40] == 0 && !fn_801658E4(v, (s8)x3, (s8)y3) && lbl_803EC898.ter[0][(s8)x3 + (s8)y3 * 0x40] == 0) {
                    u16 d = fn_801676D8((s8)x3, (s8)y3);
                    if ((u8)r >= (s16)(ABS(v->x - x3) + ABS(v->y - y3)) && d < k) {
                        *ox = x3;
                        k = d;
                        *oy = y3;
                    }
                }
            }
        }
        fn_80166720(u);
        return k != (u16)(K - 1);
    }
}
