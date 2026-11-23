/* NOT MATCHING, not compiled. fn_8011F9C4: 151 by position; lookup and registers r30/r31 right, the per-stat sums get hoisted above the min branch. */
/* Unit stats from the FE10PersonGrowth table, 8011F9C4. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
struct GrowE {
    const char* name;
    u8 lo;
    u8 hi;
    u8 (*tbl)[8];
};
extern u8 fn_80126BA4(Unit*);
extern GrowE* fn_80077064(const char*);
extern u16 fn_80109A2C(GrowE**);
extern int fn_80291188(const char*, const char*);
#pragma pool_strings on
const char* dumS() { const char* s; s = "PID_SOTHE"; s = "gf_gameover"; s = "NOBTL_"; return s; }
static inline GrowE* Find(const char* name) {
    GrowE* d = fn_80077064("FE10PersonGrowth");
    if (d) {
        u16 n = fn_80109A2C(&d);
        GrowE* e;
        int i;
        fn_80109A2C(&d);
        e = d;
        for (i = 0; i < n; i++) {
            if (fn_80291188(name, e->name) == 0) return e;
            e++;
        }
    }
    return 0;
}
#define MINN(a, b) ((a) > (b) ? (b) : (a))
#define ST(j) (e->tbl[(u8)MINN(k, (u8)d)][j] - (u->person->base[j] + u->job->base[j]))
#define SS(v, n) x = MINN(k, (u8)d); v = e->tbl[(u8)x][n] - (u->person->base[n] + u->job->base[n]);
#pragma push
#pragma use_lmw_stmw on
BOOL fn_8011F9C4(Unit* u) {
    /*P*/
    GrowE* e;
    int i;
    u16 n;
    const char* name;
    GrowE* dt;
    /*E*/
    e = 0;
    name = u->person->name;
    if ((s32)u->team[8] != 1) {
        dt = fn_80077064("FE10PersonGrowth");
        if (dt) {
            n = fn_80109A2C(&dt);
            fn_80109A2C(&dt);
            e = dt;
            for (i = 0; i < n; i++) {
                switch (fn_80291188(name, e->name)) { case 0: goto found; default: break; }
                e++;
            }
        }
        e = 0;
    }
found:
    if (e) {
        u8 kv = fn_80126BA4(u); int k = kv - e->lo;
        int d = e->hi - e->lo;
        {
        int x;
        int a, b, c, f, g, h, i2, j;
        SS(a, 0) SS(b, 1) SS(c, 2) SS(f, 3) SS(g, 4) SS(h, 5) SS(i2, 6) SS(j, 7)
        u->stat[0] = a; u->stat[1] = b; u->stat[2] = c; u->stat[3] = f; u->stat[4] = g; u->stat[5] = h; u->stat[6] = i2; u->stat[7] = j;
        }
        return 1;
    }
    return 0;
}
#pragma pop
}
