/* Unit checks and reset, stat limits, 80121E3C..80122F14. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off

extern "C" {

extern Map lbl_803EC898;
extern u8 lbl_803CAB38[];
extern u8 lbl_804CB830[1];
extern void* lbl_804CA4EC;
extern int fn_8011B77C(void*, void*);
extern u8 fn_80126BA4(Unit*);
extern Unit* fn_8012CECC(Person*);
extern u32* fn_80060728(void*);
extern void fn_80109078(void*);
extern void fn_80110D38(Inv*);
extern void* memset(void*, int, u32);

struct Sk {
    u32 a, b;
};
#define SKS(u) ((Sk*)(u)->skills)

BOOL fn_80121E3C(Unit* u) {
    u64 f = u->flags;
    if (f & 0x20000000) {
                Person* p = u->person;
        u32 c;
        Unit* o;
        u->person = 0;
        o = fn_8012CECC(p);
        u->person = p;
        if (o == 0) {
            return 1;
        }
        if (o->job != u->job) {
            return 0;
        }
        {
            c = (u8)fn_80126BA4(u);
            u32 d = (u8)fn_80126BA4(o);
            if (d != c) {
                return 0;
            }
        }
        {
            int i;
            for (i = 0; i < 18; i++) {
                Unit* a = (Unit*)((u8*)o + i * 8);
                Unit* b = (Unit*)((u8*)u + i * 8);
                if (SKS(a)->a != SKS(b)->a) {
                    return 0;
                }
            }
        }
        {
            int i;
            for (i = 0; i < 7; i++) {
                if (o->inv[i].item != u->inv[i].item) {
                    return 0;
                }
            }
        }
    } else if (f & 0x1000000000ULL) {
        return 0;
    }
    return 1;
}

static inline BOOL ModeOk(void) {
    BOOL t = 1;
    if (*lbl_804CB830 != 1 && *lbl_804CB830 != 2) {
        t = 0;
    }
    return t;
}

static inline BOOL AtHome(Unit* u) {
    if (ModeOk() == 0) {
        return 0;
    }
    if (u->team[8] != 1) {
        return 0;
    }
    return lbl_803EC898.ter[2][u->x + u->y * 0x40] == 0;
}

int fn_801220A0(Unit* u) {
    int r = *fn_80060728(lbl_803CAB38) >> 30;
    if (AtHome(u)) {
        r = 2;
    }
    if (r == 3) {
        switch (u->flags & 0xC0000000ULL) {
        case 0:
            r = 0;
            break;
        case 0x40000000:
            r = 1;
            break;
        case 0x80000000:
            r = 2;
            break;
        }
    }
    if (r == 0 && (int)u->team[8] != 0) {
        r = 1;
    }
    return r;
}

typedef void (Sk::*SkMF)();
struct SkFn {
    SkMF f;
    SkFn() {}
    SkFn(SkMF x) : f(x) {}
};
extern SkMF lbl_80385D70;
static inline SkFn Mk(SkMF f) { return SkFn(f); }

static inline SkFn SkEach(Sk* a, Sk* e, SkFn f) {
    while (a != e) {
        (a->*f.f)();
        a++;
    }
    return f;
}

#pragma push
#pragma use_lmw_stmw on
static inline void SkEach2(Sk* a, Sk* e, SkFn f) { SkFn h = SkEach(a,e,f); }
void fn_801221E8(Unit* u, int k) {
    u->prev = 0;
    u->next = 0;
    u->person = 0;
    u->job = 0;
    u->team = 0;
    u->actor = 0;
    u->gauge = 0;
    u->ff = 0;
    u->u100 = 0;
    u->pad101 = 0;
    u->x = 0;
    u->y = 0;
    u->flags = 0;
    fn_80109078(u->skills110);
    u->hp = 0;
    u->stat[7] = 0;
    u->stat[6] = 0;
    u->stat[5] = 0;
    u->stat[4] = 0;
    u->stat[3] = 0;
    u->stat[2] = 0;
    u->stat[1] = 0;
    u->stat[0] = 0;
    u->pad121[7] = 0;
    u->pad121[6] = 0;
    u->pad121[5] = 0;
    u->pad121[4] = 0;
    u->pad121[3] = 0;
    u->pad121[2] = 0;
    u->pad121[1] = 0;
    u->pad121[0] = 0;
    {
        SkFn g(lbl_80385D70); SkEach(SKS(u), SKS(u) + 18, g);
    }
    {
        int i;
        Inv* e = u->inv;
        for (i = 0; i < 7; i++) {
            fn_80110D38(e);
            e++;
        }
    }
    {
        int i;
        for (i = 0; i < 12; i++) {
            u->s2D4[i] = 0;
        }
        for (i = 0; i < 4; i++) {
            *(u32*)((u8*)u + 0x2f0 + i * 4) = 0;
        }
    }
    memset(u->sup, 0, 0x48);
    {
        int i;
        for (i = 0; i < 3; i++) {
            *(u32*)((u8*)u + 0x34c + i * 4) = 0;
        }
        for (i = 0; i < 3; i++) {
            *(u32*)((u8*)u + 0x35c + i * 4) = 0;
        }
        for (i = 0; i < 3; i++) {
            *(u32*)((u8*)u + 0x36c + i * 4) = 0;
        }
        for (i = 0; i < 6; i++) {
            *(u16*)((u8*)u + 0x382 + i * 2) = 0;
        }
    }
    *((u8*)u + 0x38e) = 0;
    *((u8*)u + 0x38f) = 0;
    if (k >= 0) {
        u->padFC = k;
    }
    u->fd = 0;
    u->u117 = 0;
    *(s8*)&u->u118 = -1;
    *((s8*)u + 0x378) = -1;
    *((s8*)u + 0x379) = -1;
    *(s16*)((u8*)u + 0x37a) = -1;
    *(u16*)((u8*)u + 0x37c) = 0;
    u->h37E = 0;
    u->b380 = -1;
}
#pragma pop

static inline s16 StatLim(Unit* u, int i) {
    int m = u->job->max[i];
    if (u->job->promoted && fn_8011B77C(u->skills, lbl_804CA4EC)) {
        m = ((Job*)u->job->promoted)->max[i];
    }
    return m - (u->person->base[i] + u->job->base[i]);
}

s16 fn_80122F14(Unit* u, u32 k) {
    switch (k) {
    case 0:
        return StatLim(u, 0);
    case 1:
        return StatLim(u, 1);
    case 2:
        return StatLim(u, 2);
    case 3:
        return StatLim(u, 3);
    case 4:
        return StatLim(u, 4);
    case 5:
        return StatLim(u, 5);
    case 6:
        return StatLim(u, 6);
    case 7:
        return StatLim(u, 7);
    }
    return -1;
}

}
