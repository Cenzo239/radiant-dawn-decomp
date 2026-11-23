/* Event trigger conditions: 0x8009F768..0x800A0330. */
#include "game/rD_8008E3B4/evflags.h"

extern "C" {

typedef struct BattleCur {
    u8* a;      /* 0x00 */
    u8* b;      /* 0x04 */
    u8 pad8[9];
    s8 x;       /* 0x11 */
    s8 y;       /* 0x12 */
} BattleCur;
extern BattleCur lbl_803CA870;

typedef struct MapSize {
    int w;
    int h;
    u8 pad[0x20000];
} MapSize;
extern MapSize lbl_803EC898;

typedef struct EvFilter {
    s16 a;
    s16 b;
    s16 c;
    u8 d[4];
    u8 e;    /* 0xA */
} EvFilter;
extern EvFilter lbl_803E50B0;

extern char lbl_80364B30[];
extern u8 lbl_80381BD4[];

u8* fn_800C3558(void);
u8* fn_800C3BC8(void* p);
int fn_801D0C88(void* ctx, void* v);
void* fn_80081194(void* cls, void* parent);
char* fn_8009D948(void* p, int ofs);
void* fn_8010B1D8(void* x);
int fn_8009FBEC(u8* p);
int fn_8004A3EC(void* p);

typedef int (*EvCond)(u8*);
typedef struct EvProc {
    u8 pad0[0x30];
    u8* cur;     /* 0x30 */
    int kind;    /* 0x34 */
    EvCond cond; /* 0x38 */
} EvProc;

#pragma push
#pragma use_lmw_stmw on
int fn_8009F768(u8* p)
{
    /*P*/
    BOOL r;
    u8* u;
    s8 x1, y1, x2, y2;
    u32 h;
    int i;
    FlagTable* q;
    const char* name;
/*E*/
    u = lbl_803CA870.a;
    if ((s8)u[0x114] == 0) {
        return 0;
    }
    if (*(s16*)(p + 0x1c) >= 0 && *(s16*)(p + 0x1c) != (*(u8**)(u + 0xf4))[8]) {
        return 0;
    }
    name = fn_8009D948(p, *(u16*)(p + 0x1e));
    FLAG_GET_R(r, q, name, h, i);
    if (r) {
        return 0;
    }
    x1 = *(s16*)(p + 0x14);
    y1 = *(s16*)(p + 0x16);
    x2 = *(s16*)(p + 0x18);
    y2 = *(s16*)(p + 0x1a);
    if (x2 <= 0) {
        x2 = lbl_803EC898.w - 1 - x2;
    }
    if (y2 <= 0) {
        y2 = lbl_803EC898.h - 1 - y2;
    }
    if (x1 > lbl_803CA870.x) {
        return 0;
    }
    if (lbl_803CA870.x > x2) {
        return 0;
    }
    if (y1 > lbl_803CA870.y) {
        return 0;
    }
    return y2 >= lbl_803CA870.y;
}
#pragma pop

int fn_8009FA1C(void)
{
    return !flagGet(&lbl_803CAB38, lbl_80364B30 + 0x23);
}

int fn_8009FBF4(void* parent)
{
    u8* p = fn_800C3BC8(NULL);
    BOOL found;
    EvProc* q;
    while (p != NULL) {
        if ((int)p[0xc] == 0xf) {
            found = 1;
            goto done;
        }
        p = fn_800C3BC8(p);
    }
    found = 0;
done:
    if (!found) {
        return 0;
    }
    lbl_803E50B0.e = 0;
    q = (EvProc*)fn_80081194(lbl_80381BD4, parent);
    q->kind = 0xf;
    q->cond = fn_8009FBEC;
    return 1;
}

#pragma push
#pragma use_lmw_stmw on
int fn_8009FC94(u8* p)
{
    char* name = fn_8009D948(p, *(u16*)(p + 0x1a));
    void* a;
    void* b;
    void* ua;
    void* ub;
    if (name != NULL && *name != 0) {
        if (flagHas(&lbl_803CAB38, (const char*)name)) {
            if (flagGet(&lbl_803CAB38, (const char*)name)) {
                return 0;
            }
        } else if (!fn_801D0C88(fn_800C3558(), (void*)name)) {
            return 0;
        }
    }
    a = fn_8010B1D8(fn_8009D948(p, *(u16*)(p + 0x14)));
    b = fn_8010B1D8(fn_8009D948(p, *(u16*)(p + 0x16)));
    ua = *(void**)(lbl_803CA870.a + 0xec);
    ub = *(void**)(lbl_803CA870.b + 0xec);
    if (ua == a && ub == b) {
        return 1;
    }
    if (*(s16*)(p + 0x18) != 0 && ua == b && ub == a) {
        return 1;
    }
    return 0;
}

int fn_8009FFE4(u8* p)
{
    /*P*/
    void* ua;
    void* ub;
    char* name;
    void* a;
    void* b;
    /*E*/
    if (fn_8004A3EC(&lbl_803CA870)) {
        ub = NULL;
        ua = *(void**)(lbl_803CA870.a + 0xec);
    } else {
        u8* v = lbl_803CA870.b;
        if (v == NULL) {
            return 0;
        }
        ub = *(void**)(v + 0xec);
        ua = *(void**)(lbl_803CA870.a + 0xec);
    }
    name = fn_8009D948(p, *(u16*)(p + 0x1a));
    if (name != NULL && *name != 0) {
        if (flagHas(&lbl_803CAB38, (const char*)name)) {
            if (flagGet(&lbl_803CAB38, (const char*)name)) {
                return 0;
            }
        } else if (!fn_801D0C88(fn_800C3558(), (void*)name)) {
            return 0;
        }
    }
    a = fn_8010B1D8(fn_8009D948(p, *(u16*)(p + 0x14)));
    b = fn_8010B1D8(fn_8009D948(p, *(u16*)(p + 0x16)));
    if (*(s16*)(p + 0x18) == 0) {
        if (a != ua) {
            return 0;
        }
        if (b != NULL && b != ub) {
            return 0;
        }
    } else {
        if (a != NULL && a != ua && a != ub) {
            return 0;
        }
        if (b != NULL && b != ua && b != ub) {
            return 0;
        }
    }
    return 1;
}

int fn_800A0330(u8* p)
{
    /*P*/
    BOOL r;
    u32 h;
    int i;
    FlagTable* q;
    const char* name;
/*E*/
    if (lbl_803E50B0.a >= 0 && lbl_803E50B0.a != *(s16*)(p + 0x14)) {
        return 0;
    }
    if (lbl_803E50B0.b >= 0 && lbl_803E50B0.b != *(s16*)(p + 0x16)) {
        return 0;
    }
    if (lbl_803E50B0.c != 0 && lbl_803E50B0.c != *(s16*)(p + 0x18)) {
        return 0;
    }
    name = fn_8009D948(p, *(u16*)(p + 0x1a));
    FLAG_GET_R(r, q, name, h, i);
    if (r) {
        return 0;
    }
    lbl_803E50B0.a = *(s16*)(p + 0x14);
    lbl_803E50B0.b = *(s16*)(p + 0x16);
    lbl_803E50B0.c = *(s16*)(p + 0x18);
    return 1;
}
#pragma pop

}
