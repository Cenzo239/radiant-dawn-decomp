/* NOT MATCHING, not compiled. fn_8011F70C (10 words: gauge/base load registers), fn_8011F9C4 (about 125 words: needs fewer saved registers), fn_8011FFD0 (not refined). */
/* Level-up by table or by growths, class change, 8011F70C, 8011F9C4, 8011FFD0. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern u8 lbl_803CAB38[];
extern char lbl_80369010[];
extern void* lbl_804CA5BC;
extern void* lbl_804CA6F8;
extern void* fn_8006074C(void*);
extern int fn_80092C84(void*);
extern int fn_80089C88(int);
extern u8* fn_80077064(void*);
extern u16 fn_80109A2C(void*);
extern int fn_80291188(const char*, const char*);
extern u8 fn_80126BA4(Unit*);
extern int fn_8011B77C(void*, void*);
extern void fn_8011B32C(void*, void*);
extern void fn_8011B958(void*, void*);
extern void fn_8011A36C(void*);
extern void fn_8011B430(void*, void*);
extern void fn_80126B80(Unit*, int);
extern s16 fn_801237EC(Unit*);
extern void fn_80126D9C(Unit*, int);

#define B(p, o) (*((u8*)(p) + (o)))
static inline int Cl(int a, int b) { return a > b ? b : a; }
static inline int Share(int a) {
    int r = 10 - fn_80089C88(20);
    return a * (100 - r) / 10000;
}
#define SHARE(a) Share(a)

#pragma push
#pragma use_lmw_stmw on
BOOL fn_8011F70C(Unit* u) {
    int n = fn_80092C84(fn_8006074C(lbl_803CAB38));
    if (u->team[8] != 1) {
        n = 0;
    }
    {
s8 base = *(s8*)((u8*)u->person + 0x1e); int d = u->gauge - base; n += d; { int cap = u->job->fb - base; if (n > cap) n = cap; }
        u->gauge = n + base;
    }
    {
        u8* g;
        s16 a7, a6, a5, a4, a3, a2, a1, a0;
        if (u->team[8] == 1) {
            g = (u8*)u->job + 0x10c;
        } else {
            g = (u8*)u->person + 0x2a;
        }
        a0 = n * g[0];
        a1 = n * g[1];
        a2 = n * g[2];
        a3 = n * g[3];
        a4 = n * g[4];
        a5 = n * g[5];
        a6 = n * g[6];
        a7 = n * g[7];
        u->stat[0] += SHARE(a0);
        u->stat[1] += SHARE(a1);
        u->stat[2] += SHARE(a2);
        u->stat[3] += SHARE(a3);
        u->stat[4] += SHARE(a4);
        u->stat[5] += SHARE(a5);
        u->stat[6] += SHARE(a6);
        u->stat[7] += SHARE(a7);
    }
    return 1;
}

struct LvEnt {
    const char* name;
    u8 lo;
    u8 hi;
    u8 (*tbl)[8];
};

static inline LvEnt* LvFind(const char* name) {
    u8* p = fn_80077064(lbl_80369010 + 0x1d);
    if (p) {
        u16 n;
        LvEnt* e;
        int i;
        n = fn_80109A2C(&p);
        fn_80109A2C(&p);
        e = (LvEnt*)p;
        for (i = 0; i < n; i++) {
            if (fn_80291188(name, e->name) == 0) {
                return e;
            }
            e++;
        }
    }
    return 0;
}

#define LV_MIN(a, b) ((a) > (b) ? (b) : (a))

BOOL fn_8011F9C4(Unit* u) {
    LvEnt* e = 0;
    if (u->team[8] != 1) {
        e = LvFind(u->person->name);
    }
    if (e) {
        int lv = (u8)fn_80126BA4(u) - e->lo;
        int span = e->hi - e->lo;
        u8 (*t)[8] = e->tbl;
        Job* j = u->job;
        Person* p = u->person;
        int v0 = t[(u8)LV_MIN(lv, (u8)span)][0] - (p->base[0] + j->base[0]);
        int v1 = t[(u8)LV_MIN(lv, (u8)span)][1] - (p->base[1] + j->base[1]);
        int v2 = t[(u8)LV_MIN(lv, (u8)span)][2] - (p->base[2] + j->base[2]);
        int v3 = t[(u8)LV_MIN(lv, (u8)span)][3] - (p->base[3] + j->base[3]);
        int v4 = t[(u8)LV_MIN(lv, (u8)span)][4] - (p->base[4] + j->base[4]);
        int v5 = t[(u8)LV_MIN(lv, (u8)span)][5] - (p->base[5] + j->base[5]);
        int v6 = t[(u8)LV_MIN(lv, (u8)span)][6] - (p->base[6] + j->base[6]);
        int v7 = t[(u8)LV_MIN(lv, (u8)span)][7] - (p->base[7] + j->base[7]);
        u->stat[0] = v0;
        u->stat[1] = v1;
        u->stat[2] = v2;
        u->stat[3] = v3;
        u->stat[4] = v4;
        u->stat[5] = v5;
        u->stat[6] = v6;
        u->stat[7] = v7;
        return 1;
    }
    return 0;
}

struct S8S {
    s8 v[8];
};

void fn_8011FFD0(Unit* u) {
    struct Sl {
        void* item;
        u8 b4;
    };
    Sl* q = (Sl*)u->skills;
    int i;
    Job* old = u->job;
    Job* j;
    for (i = 0; i < 18; i++) {
        if (q && q->item && q->b4 == 1) {
            fn_8011B32C(u->skills, q->item);
        }
        q++;
    }
    j = (Job*)u->job->p14;
    u->job = j;
    fn_8011B958(u->skills, (u8*)j + 0x24);
    fn_8011A36C(u->skills);
    j = u->job;
    {
        u8 s0 = u->stat[0] += B(j, 0x114);
        u8 s1 = u->stat[1] += B(j, 0x115);
        u8 s2 = u->stat[2] += B(j, 0x116);
        u8 s3 = u->stat[3] += B(j, 0x117);
        u8 s4 = u->stat[4] += B(j, 0x118);
        u8 s5 = u->stat[5] += B(j, 0x119);
        u8 s6 = u->stat[6] += B(j, 0x11a);
        u8 s7 = u->stat[7] += B(j, 0x11b);
        S8S d;
        S8S c;
        d.v[0] = old->base[0];
        d.v[1] = old->base[1];
        d.v[2] = old->base[2];
        d.v[3] = old->base[3];
        d.v[0] = old->base[0] - j->base[0];
        d.v[1] = old->base[1] - j->base[1];
        d.v[2] = old->base[2] - j->base[2];
        d.v[3] = old->base[3] - j->base[3];
        d.v[4] = old->base[4] - j->base[4];
        d.v[5] = old->base[5] - j->base[5];
        d.v[6] = old->base[6] - j->base[6];
        d.v[7] = old->base[7] - j->base[7];
        c = d;
        u->stat[0] = s0 + c.v[0];
        u->stat[1] = s1 + c.v[1];
        u->stat[2] = s2 + c.v[2];
        u->stat[3] = s3 + c.v[3];
        u->stat[4] = s4 + c.v[4];
        u->stat[5] = s5 + c.v[5];
        u->stat[6] = s6 + c.v[6];
        u->stat[7] = s7 + c.v[7];
    }
    if (!fn_8011B77C(u->skills, lbl_804CA5BC)) {
        fn_8011B430(u->skills, lbl_804CA6F8);
        fn_8011A36C(u->skills);
    }
    {
        u32 k;
        for (k = 0; k < 12; k++) {
            s16 m = *(s16*)((u8*)u->job + 0xb8 + (u8)k * 2);
            if (u->s2D4[(u8)k] < m) {
                u->s2D4[(u8)k] = m;
            }
        }
    }
    u->gauge = 1;
    fn_80126B80(u, 0);
    u->flags &= ~(u64)0x40000;
    fn_80126D9C(u, fn_801237EC(u));
}
#pragma pop

}
