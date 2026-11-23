/* fn_80164330: functionally equal (regs level per tools/check_regs.py; registers differ from the original). AI: move toward a unit carrying a healing staff. Declarations copied from fn_80174C2C.cpp (bodies stripped). */
/* symcheck: (b) block 42: the two bytes of an equality test are compared the other way round (cmplw a,b / cmplw b,a), tested by beq only (clean with --eqsym). */
/* AI: target searches on the map, whole-army AI runners. */
#include "game/rQ_80163178/common.h"
struct Fk { void* vt; Unit* u; u8 k; };
static inline BOOL SameT(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}
extern "C" {
extern ListHdr lbl_803E7320[];
extern u8 lbl_803CAB38[];
extern u8 lbl_80387248[];
extern u8 lbl_80387308[];
extern u8 lbl_80387338[];
extern u8 lbl_80387790[];
extern u8 lbl_80387800[];
extern u32 lbl_804CA5C0;
void* memset(void*, int, u32);
void fn_80163010(AiCfg*, Unit*);
void fn_80045120(AiAct*, Unit*);
void fn_80045548(AiAct*);
void fn_80166720(Unit*);
int fn_80169718(Unit*, void*, void*);
int fn_80169558(Unit*, void*, void*);
int fn_80169870(Unit*, void*, void*);
int fn_80152C20(void*, void*, int);
int fn_801699C8(Unit*, void*, void*);
void fn_8010E41C(u8*, int);
Unit* fn_8012CE54(int);
int fn_801658E4(Unit*, s8, s8);
void fn_80165E18(Unit*, int, int);
void fn_801659F4(int, int, int, int, int);
int fn_8011EFC8(Unit*, Unit*);
int fn_8016CB60(Unit*, Inv*);
int fn_80162B54(void*, Unit*);
int fn_8011B77C(void*, u32);
void fn_800CFB34(ListHdr*);
void fn_800398E0(void*, int);
void* fn_800CFD18(ListHdr*, int);
Unit* fn_800CFB0C(void* e);
s8 fn_8016CC18(Unit*, Unit*, int*);
void fn_800392FC(void*, int, int);
int fn_8016D11C(Unit*);
void fn_80169B20(Unit*, u16, int, int, void*, s16*, s16*);
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
u32 fn_80045274(AiAct*);
int fn_8010E2F4(Side*);
extern Side* lbl_804CB814;
extern u8 lbl_803872F8[];
u8* fn_801116B8(Inv*);
void fn_80165F94(Unit*, int, int);
int fn_80171378(int, int, Filt*);
void fn_8016F94C(Unit*, int, int, int, u16, int, int, int);

u32 fn_80174C2C(void);

int fn_8016E2AC(Unit* u, s16* ox, s16* oy, u32* res);

int fn_8016E3BC(int id, s16* ox, s16* oy, u32* res);

BOOL fn_8016E50C(Filter* f, Unit* u, s16* ox, s16* oy);

BOOL fn_8016E67C(Filter* f, Unit* u, s16* ox, s16* oy);

static inline void AiPrep(Unit* v) {
    v->m3D0[0] = 0x40;
    v->b3BC = 0;
    fn_80163010(&lbl_804183F0, v);
    lbl_804183F0.done = 0;
    memset(&lbl_804183F0.res, 0, 0x14);
    fn_80045120(&lbl_803CA870, v);
    fn_80166720(v);
}

u8 fn_80173188(void);

u8 fn_80173628(void);

u8 fn_801737FC(void);

Unit* fn_80173C04(ListHdr* l);

Unit* fn_80173F08(ListHdr* l);

u8 fn_8016CDEC(Unit* u, void* f);
void fn_8016CF78(FF* f, s8 x, s8 y);
void fn_8017293C(FF* f, s8 x, s8 y);

u8 fn_80164330(Unit* u, u16 item);

static inline BOOL SideOn(int i, int k) {
    BOOL r = 0;
    if (fn_8010E2F4(&lbl_804CB814[i]) > 0 && lbl_803CAB38[k] == 1) {
        r = 1;
    }
    return r;
}
static inline BOOL IsNz(int v) {
    return v != 0;
}
Unit* fn_801739D0(ListHdr* l);

u8 fn_80172E70(void);

static inline BOOL HasW(Unit* u, Unit* v) {
    int i;
    BOOL any = 0;
    Inv* p = v->inv;
    for (i = 0; i < 7; i++, p++) {
        if (!p || !p->item) break;
        if (fn_8016CB60(u, p)) {
            any = 1;
            break;
        }
    }
    return any;
}
BOOL fn_8016E7FC(Filter* f, Unit* u, s16* ox, s16* oy);
BOOL fn_8016EDE8(Filter* f, Unit* u, s16* ox, s16* oy);
}


/* ---- fn_80164330 ---- */
extern "C" {
u8 fn_80164330(Unit* u, u16 item) {
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        return 0;
    } else {
/*P*/
        Map* m = &lbl_803EC898;
        int cb = 0x7FFFFFFF;
        int best = 0xFF;
        int bx;
        int by;
        int y;
        int x;
        Unit* v;
        int k;
        int j;
        Inv* p;
/*E*/
        Filt g;
        fn_80165F94(u, 6, lbl_803EC898.w * m->h);
        for (y = m->y0; y <= m->y1 - 1; y++) {
            for (x = m->x0; x <= m->x1 - 1; x++) {
                if (m->costS[(s8)x + (s8)y * 0x40] >= 0 && m->b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && m->ter[0][(s8)x + (s8)y * 0x40]) {
                    v = UnitGet(m->ter[0][(s8)x + (s8)y * 0x40]);
                    if (u != v && !SameT(u, v, 1)) {
                        p = v->inv;
                        k = -1;
                        for (j = 0; j < 7; j++, p++) {
                            if (!p || !p->item) break;
                            if (!(*(u32*)(fn_801116B8(p) + 4) & 0x20) && (u8)(p->item ? p->item[0x12] : 0x13) == 0xE && (u8)(p->item ? p->item[0x14] : 0x13) == 0x81) {
                                k = j;
                                break;
                            }
                        }
                        if ((s8)k >= 0) {
                            int c;
                            g.u = u;
                            g.vt = lbl_80387308;
                            c = fn_80171378((s16)x, (s16)y, &g);
                            if (c <= cb && m->curS[(s8)x + (s8)y * 0x40] < best) {
                                cb = c;
                                best = (u8)m->curS[(s8)x + (s8)y * 0x40];
                                bx = (s16)x;
                                by = (s16)y;
                            }
                        }
                    }
                }
            }
        }
        if (cb != 0x7FFFFFFF && m->ter[0][(s8)bx + (s8)by * 0x40] != u->tid) {
            fn_8016F94C(u, bx, by, 1, item, 0, 0, -1);
        }
        return lbl_804183F0.done;
    }
}
}
