/* Unit helpers: equipped item, skills, position, 80126AA4..80127B28. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern u8* fn_80060728(void*);
extern int fn_80060828(void*, Unit*);
extern u8 lbl_803CAB38[];
extern void* lbl_804CA6B4;
extern void* lbl_804CA668;
extern void* lbl_804CA6D4;
extern void* lbl_804CA4E0;
extern void* lbl_804CA4E4;
extern void* lbl_804CA4E8;
extern void* lbl_804CA4F8;
extern void* lbl_804CA5C0;
extern s16 fn_8010ECA0(void);
extern s16 fn_8010EC08(void);
extern int fn_8010EDD0(void);
extern u8 fn_8010EE68(void);
extern s8 fn_801243F4(Unit*);
extern void fn_800F3B50(u8*, f32, f32);
extern void fn_8010701C(Unit*, f32*, f32*, f32*, f32*);
extern f32 fn_801070A4(Unit*);
extern void* fn_8010B180(int);
extern char* fn_8010E9A4(void*);
extern char lbl_80369088[];

static inline int EquipIdx(Unit* u) {
    Inv* it = u->inv;
    int i;
    for (i = 0; i < 7; i++) {
        if (it->item == 0) {
            break;
        }
        if ((*(u32*)(fn_801116B8(it) + 4) & 0x11) && it->equipped) {
            return (s8)i;
        }
        it++;
    }
    return -1;
}

#pragma push
#pragma use_lmw_stmw on
s8 fn_801267F8(Unit* u) {
    Inv* base = u->inv;
    int r = 0;
    Inv* e;
    int i;
    {
        int idx = EquipIdx(u);
        if (idx < 0) {
            e = 0;
        } else {
            e = &u->inv[idx];
        }
    }
    if (e) {
        r = (s8)e->item[0x2b];
    }
    for (i = 0; i < 7; i++) {
        u32 t;
        if (base == 0 || base->item == 0) {
            break;
        }
        t = base->item ? base->item[0x12] : 0x13;
        if (t == 0xe) {
            if (base->equipped || (*(u32*)fn_801116B8(base) & 0x2000000)) {
                r += (s8)base->item[0x2b];
            }
        }
        base++;
    }
    if (r > 0x7f) {
        r = 0x7f;
    }
    if (r < -0x80) {
        r = -0x80;
    }
    return r;
}
#pragma pop

int fn_80126AA4(Unit* u) {
    int r = 0;
    if (fn_8011B77C(u->skills, lbl_804CA6B4)) {
        r = 0x32;
    }
    if (fn_8011B77C(u->skills, lbl_804CA668)) {
        r = -0x32;
    }
    return r;
}

static inline BOOL TeamIs(Unit* u, int t) {
    return u->team[8] == t;
}

void fn_80126B80(Unit* u, int v) {
    if (v != 0xff && (v < 0 || v > 100)) {
        return;
    }
    u->ff = v;
}

u8 fn_80126BA4(Unit* u) {
    int r = u->gauge;
    if (!fn_8011B77C(u->skills, lbl_804CA4E8)) {
        if (fn_8011B77C(u->skills, lbl_804CA4E4)) {
            r += 0x28;
        } else if (fn_8011B77C(u->skills, lbl_804CA4E0)) {
            r += 0x14;
        }
    }
    return r;
}

u8 fn_80126D28(Unit* u) {
    u8 r = 0;
    if (fn_8011B77C(u->skills, lbl_804CA4F8)) {
        r = (u8)fn_8010EDD0();
    }
    if (fn_8011B77C(u->skills, lbl_804CA5C0)) {
        r += fn_8010EE68();
    }
    return r;
}

static inline int StatJ(Unit* u, int i) {
    return u->stat[i] + u->job->base[i];
}

static inline s16 StatBaseF(Unit* u, int i) {
    int a = StatJ(u, i);
    int v = u->person->base[i] + a;
    if (v > u->job->max[i]) {
        v = u->job->max[i];
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

static inline s16 MaxHp(Unit* u) {
    s16 v = StatBaseF(u, 0);
    return v + fn_801243F4(u);
}

void fn_80126D9C(Unit* u, int hp) {
    if (hp > MaxHp(u)) {
        hp = MaxHp(u);
    }
    if (hp < 0) {
        hp = 0;
    }
    u->hp = hp;
}

void fn_80126EB0(Unit* u, s8 x, s8 y) {
    u8* m = u->actor;
    u->x = x;
    u->y = y;
    if (m) {
        f32 fx = 0.5f + (f32)x;
        f32 fy = 0.5f + (f32)y;
        m[0x102] = x;
        m[0x103] = y;
        fn_800F3B50(m, fx, fy);
    }
}

s8 fn_80127520(Unit* u) {
    Inv* it = u->inv;
    int i;
    for (i = 0; i < 7; i++) {
        if (it->item == 0) {
            break;
        }
        if ((*(u32*)(fn_801116B8(it) + 4) & 0x11) && it->equipped) {
            return i;
        }
        it++;
    }
    return -1;
}

Inv* fn_8012759C(Unit* u) {
    int idx = EquipIdx(u);
    if (idx < 0) {
        return 0;
    }
    return &u->inv[idx];
}

int fn_80127640(void) {
    return -1;
}

int
#if TARGET_PC
*
#endif
fn_80127648(void) {
    return 0;
}

extern int fn_8010B260(void*);
extern void* fn_8010B1D8(void*);
extern void* fn_8010B200(void*);
extern void* fn_8010B228(void*);
extern void* fn_801059B0(void);
extern int fn_8010536C(void*, void*);
extern void fn_8010E41C(void*, int);
extern int fn_8012C9BC(Unit*, void*);
extern int fn_801109B8(void*, void*);

f32 fn_8012786C(Unit* u) {
    f32 a, b, c, d;
    fn_8010701C(u, &a, &b, &c, &d);
    return fn_801070A4(u) / a;
}

struct Weap {
    u32 a;
    u16 b;
    s8 c;
    Weap() {}
    Weap(const Weap& o) : a(o.a), b(o.b), c(o.c) {}
};

extern void fn_80107864(Weap*, u8*, f32);
extern s8 fn_801252F8(Unit*);
extern void* lbl_804CA4EC;
extern void* lbl_804CA4F4;
extern void* lbl_804CA51C;

static inline Weap WeapGet(Unit* u) {
    Weap t;
    fn_80107864(&t, u->skills, fn_801070A4(u));
    return t;
}

u32 fn_80127A90(Unit* u) {
    u32 r;
    if (u->job == 0) {
        return 0;
    }
    r = u->job->f7;
    if (fn_8011B77C(u->skills, lbl_804CA4E8)) {
        s8 v = u->gauge;
        if (v >= 30) {
            r += 0x32;
        } else {
            BOOL m = 0;
            if (v >= 15 && v < 30) {
                m = 1;
            }
            if (m) {
                r += 0xf;
            }
        }
    }
    return r;
}

char* fn_80127B28(Unit* u) {
    void* x = fn_8010B180(u->fd);
    if (x == 0) {
        return lbl_80369088 + 0xd0;
    }
    return fn_8010E9A4(x);
}

}
