/* Unit: exp, transform timers and growth bonuses, 801282F0..80129A8C. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern void fn_80127DEC(Unit*);
extern void fn_8012CAD8(Unit*);
extern int fn_8012CA88(Unit*);
extern void fn_801288D4(Unit*);
extern s8 fn_80127520(Unit*);
extern void* fn_80076F54(void*);
extern void* lbl_804CA4E8;
extern void* lbl_804CA4EC;
extern void* lbl_804CA4F0;
extern void* lbl_804CA4F4;
extern void* lbl_804CA5E0;

#define HAS(u, s) fn_8011B77C((u)->skills, s)

void fn_801282F0(Unit* u, s8* b) {
    u->stat[0] += b[0];
    u->stat[1] += b[1];
    u->stat[2] += b[2];
    u->stat[3] += b[3];
    u->stat[4] += b[4];
    u->stat[5] += b[5];
    u->stat[6] += b[6];
    u->stat[7] += b[7];
    fn_80127DEC(u);
}

void fn_80128374(Unit* u, int a, int b) {
    u->exp115 += a;
    u->u116 += b;
    if ((s8)u->exp115 > 0x63) {
        u->exp115 = 0x63;
    }
    if (u->u116 > 0x14) {
        u->u116 = 0x14;
    }
}

char* fn_801283C0(Unit* u) {
    if (u->person == 0) {
        return 0;
    }
    return u->person->name;
}

char* fn_801283DC(Unit* u) {
    if (u->job == 0) {
        return 0;
    }
    return u->job->name;
}

void fn_801283F8(Unit* u) {
    if (HAS(u, lbl_804CA4E8)) {
        if (HAS(u, lbl_804CA4EC)) {
            u->u100 = 0x1e;
        } else {
            u->u100 = u->person->e2;
        }
    }
}

void fn_80128460(Unit* u) {
    if (HAS(u, lbl_804CA4EC)) {
        u->u100 = 0x1e;
    } else if (u->flags10C & 0x8000000) {
        u->u100 = 0;
    }
    fn_8012CAD8(u);
}

u8 fn_801284C4(Unit* u) {
    if (HAS(u, lbl_804CA4F0)) {
        return 0x1e;
    }
    if (HAS(u, lbl_804CA4F4)) {
        return 0x1e;
    }
    if (HAS(u, lbl_804CA5E0)) {
        return 0x1e;
    }
    if (u->flags108 & 1) {
        return 0x1e;
    }
    return u->u100;
}

void fn_80128558(Unit* u, int v) {
    if ((s8)v > 0x1e) {
        v = 0x1e;
    }
    if ((s8)v < 0) {
        v = 0;
    }
    u->u100 = v;
}

extern void fn_80129CB8(Unit*, int);
extern void fn_80129F40(Unit*, int);
extern u8* fn_801116B8(Inv*);

static inline BOOL Ready(Unit* u) {
    if (!HAS(u, lbl_804CA4E8)) {
        return 0;
    }
    if ((s8)u->u100 == 0 && HAS(u, lbl_804CA4EC)) {
        return 1;
    }
    if ((int)u->u100 == 0x1e && !HAS(u, lbl_804CA4EC)) {
        return 1;
    }
    return 0;
}

BOOL fn_8012857C(Unit* u, int k) {
    int d = 0;
    if (HAS(u, lbl_804CA4EC)) {
        if (!HAS(u, lbl_804CA5E0)) {
            d = u->person->eb;
        }
    } else if (u->flags10C & 0x2000000) {
        d = u->person->e9;
    } else if (k) {
        d = 0;
    } else {
        d = u->person->e9;
    }
    if (!HAS(u, lbl_804CA4E8)) {
        return 0;
    }
    if (HAS(u, lbl_804CA4F0)) {
        return 0;
    }
    if (HAS(u, lbl_804CA4F4)) {
        return 0;
    }
    if (u->flags108 & 1) {
        return 0;
    }
    if (fn_8012CA88(u)) {
        return 0;
    }
    {
        int v = (s8)(u->u100 + d);
        if (v > 0x1e) {
            v = 0x1e;
        }
        if (v < 0) {
            v = 0;
        }
        u->u100 = v;
    }
    return Ready(u);
}

BOOL fn_80128744(Unit* u) {
    int d = 0;
    if (HAS(u, lbl_804CA4EC)) {
        if (!HAS(u, lbl_804CA5E0)) {
            d = u->person->ea;
        }
    } else {
        d = u->person->e8;
    }
    if (!HAS(u, lbl_804CA4E8)) {
        return 0;
    }
    if (HAS(u, lbl_804CA4F0)) {
        return 0;
    }
    if (HAS(u, lbl_804CA4F4)) {
        return 0;
    }
    if (u->flags108 & 1) {
        return 0;
    }
    if (fn_8012CA88(u)) {
        return 0;
    }
    {
        int v = (s8)(u->u100 + d);
        if (v > 0x1e) {
            v = 0x1e;
        }
        if (v < 0) {
            v = 0;
        }
        u->u100 = v;
    }
    return Ready(u);
}

extern void fn_80111B34(Inv*);
extern void fn_80111C24(Inv*, int);
extern void fn_80110BB4(Inv*, void*);
extern void* fn_80128AA0(Unit*);
extern void fn_8012BC54(Unit*, int, Inv*);

void fn_80128D70(Unit* u) {
    if (fn_80128AA0(u)) {
        Inv o;
        fn_80111B34(&o);
        fn_80110BB4(&o, fn_80128AA0(u));
        if (&u->inv[0] && u->inv[0].item && u->inv[0].bit10) {
            ((u8*)&o)[5] |= 0x10;
        }
        fn_8012BC54(u, 0, &o);
        ((u8*)&u->inv[0])[5] |= 0x80;
        fn_80111C24(&o, -1);
    }
}

void fn_80128E14(Unit* u, int k) {
    if (HAS(u, lbl_804CA4E8) && !HAS(u, lbl_804CA4F0) && !HAS(u, lbl_804CA4F4) && !(u->flags108 & 1) && !fn_8012CA88(u)) {
        if (k) {
            if (HAS(u, lbl_804CA4EC)) {
                return;
            }
        } else {
            if (!HAS(u, lbl_804CA4EC)) {
                return;
            }
        }
        fn_801288D4(u);
    }
}

BOOL fn_80128EDC(Unit* u) {
    if (!HAS(u, lbl_804CA4E8)) {
        return 0;
    }
    if (HAS(u, lbl_804CA4EC)) {
        return 0;
    }
    if (fn_80127520(u) < 0) {
        return 0;
    }
    return !(u->flags10C & 0x2000000);
}

BOOL fn_80128F64(Unit* u) {
    return Ready(u);
}

struct Stat2 {
    void* a;
    u8 b;
};

void fn_80129150(Stat2* p) {
    p->a = 0;
    p->b = 0;
}

void fn_80129160(Stat2* p) {
    p->a = 0;
    p->b = 0;
}

struct Stat3 {
    u8 pad0[4];
    void* v4;
    u8 pad8[4];
    u8 vC;
    u8 padD;
    u8 vE;
    u8 vF;
    u8 pad10;
    u8 v11;
    u8 v12;
    u8 v13;
    u8 v14;
};

struct Stat4 {
    void* v0;
    u8 v4, v5, v6, v7, v8, v9, vA, vB;
};

void fn_80129170(Stat4* d, Stat3* s) {
    d->v0 = s->v4;
    d->v4 = s->vC;
    d->v5 = s->vE;
    d->v6 = s->vF;
    d->v7 = s->vF;
    d->v8 = s->v11;
    d->v9 = s->v12;
    d->vA = s->v13;
    d->vB = s->v14;
}

void fn_801291BC(Unit* u) {
    u->ptr[0] = 0;
    u->ptr[1] = 0;
    u->ptr[2] = 0;
    u->ptr[3] = 0;
    u->p3A4 = 0;
    u->b3A8 = 0;
    u->p3AC = 0;
    u->cnt[0] = 0;
    u->cnt[1] = 0;
    u->cnt[2] = 0;
    u->cnt[3] = 0;
    u->b3BA = 0;
    u->b3BB = 0;
    u->w3B4 = 0;
    u->h3B8 = 0;
    u->b3BC = 0;
    u->b3D0 = 0x40;
    u->w3C4 = 0;
    u->b3C8 = 0;
}

void fn_801293F0(Unit* u, void* id) {
    u8* d = (u8*)fn_80076F54(id);
    if (d) {
        u->ptr[0] = *(void**)(d + 0x18);
        u->cnt[0] = 0;
    }
}

void fn_80129438(Unit* u, void* id) {
    u8* d = (u8*)fn_80076F54(id);
    if (d) {
        u->ptr[1] = *(void**)(d + 0x18);
        u->cnt[1] = 0;
    }
}

void fn_80129480(Unit* u, void* id) {
    u8* d = (u8*)fn_80076F54(id);
    if (d) {
        u->ptr[2] = *(void**)(d + 0x18);
        u->cnt[2] = 0;
    }
}

void fn_801294C8(Unit* u, void* id) {
    u8* d = (u8*)fn_80076F54(id);
    if (d) {
        u->ptr[3] = *(void**)d;
        u->cnt[3] = 0;
    }
}

void fn_80129510(Unit* u, void* id) {
    u8* d = (u8*)fn_80076F54(id);
    if (d) {
        u->p3A4 = *(void**)d;
    }
}

void fn_80129550(Unit* u, int i) {
    switch (i) {
    case 0:
        u->cnt[0]++;
        break;
    case 1:
        u->cnt[1]++;
        break;
    case 2:
        u->cnt[2]++;
        break;
    case 3:
        u->cnt[3]++;
        break;
    }
}

void fn_801295B8(Unit* u, int i, u8 v) {
    switch (i) {
    case 0:
        u->cnt[0] = v;
        break;
    case 1:
        u->cnt[1] = v;
        break;
    case 2:
        u->cnt[2] = v;
        break;
    case 3:
        u->cnt[3] = v;
        break;
    }
}

u8 fn_80129600(Unit* u, int i) {
    u8 r = 0;
    switch (i) {
    case 0:
        r = u->cnt[0];
        break;
    case 1:
        r = u->cnt[1];
        break;
    case 2:
        r = u->cnt[2];
        break;
    case 3:
        r = u->cnt[3];
        break;
    }
    return r;
}

int fn_80129A8C(Unit* u) {
    int i;
    for (i = 0; i < 7; i++) {
        if (u->inv[i].item == 0) {
            return i;
        }
    }
    return -1;
}

void fn_8012A088(Unit* u, int i) {
    if (*(u32*)(fn_801116B8(&u->inv[i]) + 4) & 0x11) {
        fn_80129CB8(u, i);
    } else {
        fn_80129F40(u, i);
    }
}

}
