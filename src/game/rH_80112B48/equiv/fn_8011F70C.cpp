/* EQUIVALENT (sched, round 19b): fn_8011F70C. Moved instructions (checked with dd.py): an independent lbz 0xfb load and a subf swap places. From wip/r7_fn_8011F70C.cpp. */
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

BOOL fn_8011F9C4(Unit* u);


struct S8S {
    s8 v[8];
};
void fn_8011FFD0(Unit* u);

#pragma pop

}