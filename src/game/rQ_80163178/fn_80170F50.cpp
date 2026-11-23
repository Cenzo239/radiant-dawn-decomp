/* AI: unit flag setup, range marks. */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
extern "C" {
extern u8 lbl_80387438[];
extern u8 lbl_803CAB38[];
extern u8 lbl_804CB830;
extern SkillAct lbl_80387690[];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA5C4;
#else
extern u32 lbl_804CA5C4;
#endif
void fn_80163178(Unit*);
int fn_8012BB48(Unit*, u8*);
int fn_8012BA20(Unit*, u8*);
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, u32);
#endif
u8* fn_801116B8(Inv*);
void fn_80170D64(Unit*);
void fn_80170E60(Unit*);
int fn_80109348(void*);
void fn_8010E41C(u8*, int);
int fn_80165818(void);
#if TARGET_PC
FE10_PROTO void fn_801148CC(Map*, p32arg);
#else
void fn_801148CC(Map*, int);
#endif
void fn_80114B44(Map*, int, int);
void fn_80114888(Map*, int);
void fn_80115DEC(Map*, int, int, u8, u8);
#if TARGET_PC
FE10_PROTO void fn_80116098(Map*, int, int, p32arg, p32arg);
#else
void fn_80116098(Map*, int, int, u8, u8);
#endif
s8 fn_8012408C(Unit*);
int fn_801658E4(Unit*, s8, s8);
void fn_800620A8(u8*, f32, f32);
void fn_800454A8(AiAct*, int, int);
u8* fn_80081194_(void);
void fn_80129CB8(Unit*, int);
u8 fn_801107A0(u8*, Unit*);
u8 fn_801107C0(u8*, Unit*);
u8 fn_80110DA8(Inv*);
#if TARGET_PC
FE10_PROTO void fn_801030B8(Unit*, int, int, int, int, p32arg);
#else
void fn_801030B8(Unit*, int, int, int, int, void*);
#endif

void fn_801689C8(f32* p);

void fn_80168BF0(u8* p);

void fn_80170F50(void) {
    u8 tbl[0xB];
    Inv* base;
    int id;
    fn_8010E41C(tbl, 3);
    for (id = 1; id <= 0xFE; id++) {
        Unit* u = UnitGet(id);
        if (u->person && tbl[u->team[8]]) {
            int i;
            Inv* p;
            u->w3B4 &= 0xFAFFC02B;
            fn_80163178(u);
            base = u->inv;
            p = base;
            for (i = 0; i < 7; i++, p++) {
                if (!p || !p->item) break;
                if (fn_8012BB48(u, p->item)) {
                    u8* it = p->item;
                    if ((u8)(it ? it[0x14] : 0x13) == 0x81 || (u8)(it ? it[0x14] : 0x13) == 0x82) {
                        u->w3B4 |= 4;
                    }
                }
            }
            {
                Inv* q = base;
                int j;
                for (j = 0; j < 7; j++, q++) {
                    if (!q || !q->item) break;
                    if (fn_8012BB48(u, q->item) && (u8)(q->item ? q->item[0x14] : 0x13) == 0x86) {
                        u->w3B4 |= 0x10;
                    }
                }
            }
            if (fn_8011B77C(u->skills, lbl_804CA5C4)) {
                u->w3B4 |= 0x2000;
            }
            for (i = 0; i < 7; i++, base++) {
                if (!base || !base->item) break;
                if (fn_8012BA20(u, base->item) && (*(u32*)(fn_801116B8(base) + 4) & 2)) {
                    u->w3B4 |= 0x40;
                    break;
                }
            }
            fn_80170D64(u);
            fn_80170E60(u);
            if (fn_80109348((u8*)u + 0x110)) {
                u->w3B4 |= 0x1000000;
            }
        }
    }
}

void fn_80171188(Unit* u);

void fn_80170738(Unit* u, u8 a, u8 b) {
    Map* m = &lbl_803EC898;
    int ux, uy, r, x0, y0, x1, y1, yy;
    fn_801148CC(m, fn_80165818());
    fn_80114B44(m, 9, 0);
    ux = u->x;
    uy = u->y;
    r = fn_8012408C(u);
    x0 = ux - r;
    if (x0 < m->x0) {
        x0 = m->x0;
    }
    y0 = uy - r;
    if (y0 < lbl_803EC898.y0) {
        y0 = lbl_803EC898.y0;
    }
    x1 = ux + r;
    if (x1 > lbl_803EC898.x1 - 1) {
        x1 = lbl_803EC898.x1 - 1;
    }
    y1 = uy + r;
    if (y1 > lbl_803EC898.y1 - 1) {
        y1 = lbl_803EC898.y1 - 1;
    }
    for (yy = y0; yy <= y1; yy++) {
        int xx;
        for (xx = x0; xx <= x1; xx++) {
            if (r >= ABS(ux - xx) + ABS(uy - yy)) {
                if (lbl_803EC898.costS[(s8)xx + (s8)yy * 0x40] >= 0 && lbl_803EC898.b5S[(s8)xx + (s8)yy * 0x40] == 0 && !fn_801658E4(u, (s8)xx, (s8)yy) && lbl_803EC898.ter[0][(s8)xx + (s8)yy * 0x40] == 0) {
                    fn_80115DEC(m, (s8)xx, (s8)yy, a, b);
                }
            }
        }
    }
    fn_80114888(m, 6);
}
void fn_80170998(Unit* u, u8 a, u8 b) {
    Map* m = &lbl_803EC898;
    int ux, uy, r, x0, y0, x1, y1, yy;
    fn_801148CC(m, fn_80165818());
    fn_80114B44(m, 9, 0);
    ux = u->x;
    uy = u->y;
    r = fn_8012408C(u);
    x0 = ux - r;
    if (x0 < m->x0) {
        x0 = m->x0;
    }
    y0 = uy - r;
    if (y0 < lbl_803EC898.y0) {
        y0 = lbl_803EC898.y0;
    }
    x1 = ux + r;
    if (x1 > lbl_803EC898.x1 - 1) {
        x1 = lbl_803EC898.x1 - 1;
    }
    y1 = uy + r;
    if (y1 > lbl_803EC898.y1 - 1) {
        y1 = lbl_803EC898.y1 - 1;
    }
    for (yy = y0; yy <= y1; yy++) {
        int xx;
        for (xx = x0; xx <= x1; xx++) {
            if (r >= ABS(ux - xx) + ABS(uy - yy)) {
                if (lbl_803EC898.costS[(s8)xx + (s8)yy * 0x40] >= 0 && lbl_803EC898.b5S[(s8)xx + (s8)yy * 0x40] == 0 && !fn_801658E4(u, (s8)xx, (s8)yy) && lbl_803EC898.ter[0][(s8)xx + (s8)yy * 0x40] == 0) {
                    fn_80115DEC(m, (s8)xx, (s8)yy, a, b);
                }
            }
        }
    }
    fn_80114888(m, 6);
}
void fn_8016935C(void) {
    Inv* p;
    Unit* u = lbl_803CA870.unit;
    BOOL ok;
    if ((s8)lbl_803CA870.b16 != 0) {
        ok = 0;
    } else if (lbl_804183F0.flags & 4) {
        ok = 0;
    } else if (u->flags10C & 0x18) {
        ok = 0;
    } else {
        switch (lbl_803CA870.action) {
        case 0xF:
        case 0x10:
        case 0x15:
        case 0x16:
        case 0x28:
        case 0x3A:
        case 0x41:
            ok = 0;
            break;
        default:
            ok = 1;
            break;
        }
    }
    if (ok) {
        int best = -1;
        int m = -0x80;
        BOOL any = 0;
        int i;
        p = u->inv;
        for (i = 0; i < 7; i++, p++) {
            if (!p->item) break;
            if (fn_8012BA20(u, p->item)) {
                any = 1;
                if ((u8)(p->item ? fn_801107A0(p->item, u) : 0) <= 1 && (u8)(p->item ? fn_801107C0(p->item, u) : 0) > 1 && m < (int)fn_80110DA8(p)) {
                    m = (s8)fn_80110DA8(p);
                    best = i;
                }
            }
        }
        if (any) {
            fn_80129CB8(u, (s8)best);
        }
    }
}
}
