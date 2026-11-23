#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

/* base / preparation menu pages */
typedef struct BLink {
    f32 x, y;         /* 0x00 */
    s8 next[4];       /* 0x08 */
    s8 x0C;           /* 0x0C */
    u8 type;          /* 0x0D */
    u8 pad0E[2];
    const char* help; /* 0x10 */
} BLink;

typedef struct BPage {
    BLink e[27];
} BPage;

typedef struct BData {
    u8 pad[8];
    s16 t;      /* 0x08 */
    s8 page;    /* 0x0A */
    u8 pad0B;
    int sel;    /* 0x0C */
    int dir;    /* 0x10 */
    u8 pad14[0x20 - 0x14];
    u8 alpha;   /* 0x20 */
    u8 pad21[3];
    f32 x;      /* 0x24 */
    f32 y;      /* 0x28 */
    void* items[6]; /* 0x2C */
    u8* unit;   /* 0x44 */
    void* x48;
    void* x4C;
    void* x50;
    void* x54;
    u8 pad58[0x68 - 0x58];
    void* x68;
} BData;

typedef struct BProc {
    u8 pad[0x30];
    BData* d;
} BProc;

extern BPage lbl_8038A038[];
extern u8 lbl_803CAB38[];
extern char lbl_8036E118[];
extern void fn_800FAFF0(u8* u, int a);
extern u8* fn_80060728(void* p);
extern void fn_800C429C(void* p);
extern void fn_80081A90(void* p);
extern void fn_80078E24(void* p);
extern void fn_80253EE4(const char* s, f32 v);
extern f32 fn_8017F68C(int a, f32 x, f32 y, f32 t, f32 d);
extern void fn_80083B78(void* p);

void fn_801C6034(BProc* p) {
    u8 pg;
    u8* u;
    BData* d = p->d;
    fn_800FAFF0(d->unit, 1);
    pg = d->page;
    fn_80060728(lbl_803CAB38)[0x20] = pg;
    u = d->unit;
    *(u8**)(fn_80060728(lbl_803CAB38) + 0x24) = u;
    if (d->x48 != NULL) {
        fn_800C429C(d->x48);
    }
    if (d->x4C != NULL) {
        fn_80081A90(d->x4C);
        d->x4C = NULL;
    }
    if (d->x50 != NULL) {
        fn_80081A90(d->x50);
        d->x50 = NULL;
    }
    if (d->x54 != NULL) {
        fn_80081A90(d->x54);
        d->x54 = NULL;
    }
    if (d->x68 != NULL) {
        fn_80081A90(d->x68);
        d->x68 = NULL;
    }
    fn_80078E24(d);
}

BOOL fn_801C61F4(BData* d, int i) {
    BLink* e = &lbl_8038A038[d->page].e[i];
    u8 t = e->type;
    if (t >= 2 && t <= 8) {
        int want = t - 2;
        int n = 0;
        int k;
        for (k = 0; k < 7; k++) {
            if (*(u32*)(d->unit + k * 0x28 + 0x1BC) != 0) {
                n++;
            }
            if (n - 1 == want) {
                return TRUE;
            }
        }
        return FALSE;
    }
    if (t >= 10 && t <= 15) {
        return d->items[t - 10] != NULL;
    }
    if (t == 16) {
        return (u16)(*(u16*)(*(u8**)(d->unit + 0xF0) + 0xEE) & 0x10) != 0;
    }
    return TRUE;
}

void fn_801C6554(BProc* p) {
    p->d->t = 7;
}

void fn_801C6564(BProc* p) {
    BData* d = p->d;
    d->t--;
    if (d->dir == 1) {
        d->x = fn_8017F68C(4, 16.0f, -184.0f, 7 - d->t, 7.0f);
    } else {
        d->x = fn_8017F68C(4, 16.0f, 216.0f, 7 - d->t, 7.0f);
    }
    d->y = 170.0f;
    d->alpha = fn_8017F68C(4, 255.0f, 0.0f, 7 - d->t, 7.0f);
    if (d->t <= 0) {
        fn_80083B78(p);
    }
}

void fn_801C6690(BProc* p) {
    BData* d = p->d;
    if (d->dir == 1) {
        d->page++;
        if (d->page > 3) {
            d->page = 0;
        }
    } else {
        d->page--;
        if (d->page < 0) {
            d->page = 3;
        }
    }
    d->t = 7;
}

void fn_801C66F4(BProc* p) {
    BData* d = p->d;
    d->t--;
    if (d->dir == 1) {
        d->x = fn_8017F68C(4, 216.0f, 16.0f, 7 - d->t, 7.0f);
    } else {
        d->x = fn_8017F68C(4, -184.0f, 16.0f, 7 - d->t, 7.0f);
    }
    d->y = 170.0f;
    d->alpha = fn_8017F68C(4, 0.0f, 255.0f, 7 - d->t, 7.0f);
    if (d->t <= 0) {
        fn_80083B78(p);
    }
}

void fn_801C6820(BProc* p) {
    p->d->t = 7;
}

}
