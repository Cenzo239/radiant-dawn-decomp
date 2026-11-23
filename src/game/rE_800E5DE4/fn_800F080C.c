#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct Pair { char* name; int v; } Pair;
typedef struct IdEnt { u32 id; u32 v; } IdEnt;
typedef struct IdTbl { s32 n; IdEnt e[1]; } IdTbl;
typedef struct Grp { u8 pad[3]; u8 n; u16 ids[1]; } Grp;

extern u8 lbl_803674B4[];
extern void* lbl_804CB7C4;
extern u32 fn_80109A2C(void**);
extern int fn_80291188(char*, char*);
extern IdTbl* fn_80076F54(char*);
extern IdTbl* fn_80077064(char*);
extern void* fn_80007F10(void*);
extern int fn_80009E20(void*, Grp**);
extern u32 fn_800F173C(u32);
#if TARGET_PC
extern FE10_PROTO void fn_800E24F8(char *);
#else
extern void fn_800E24F8(u32);
#endif
extern int fn_80008C98(void*, int);
extern int fn_80008CF0(void*, int);
extern void fn_8017EA78(int, int, int, int, int, void*);

static inline int Spec(char* s) {
    char* base = (char*)lbl_803674B4;
    int r;
    if (fn_80291188(base + 0x4A0, s) == 0) return -1;
    r = fn_80291188(base + 0x4A5, s) == 0;
    return -r;
}
int fn_800F080C(char* s) {
    void* b = lbl_804CB7C4;
    int n = (u16)fn_80109A2C(&b);
    Pair* t;
    int i;
    fn_80109A2C(&b);
    t = b;
    for (i = 0; i < n; i++, t++) {
        if (fn_80291188(t->name, s) == 0) return i;
    }
    return Spec(s);
}

u32 fn_800F14B4(u32 id) {
    IdTbl* t;
    u32 r;
    if (id == 0xFFFF) return 0;
    if (id < 1000) return 0;
    r = 0;
    t = fn_80076F54((char*)lbl_803674B4 + 0x580);
    if (t == 0) return 0;
    {
        int n = t->n;
        IdEnt* e = t->e;
        int lo = 0;
        int hi = n - 1;
        while (lo <= hi) {
            int mid = lo + ((hi - lo) >> 1);
            IdEnt* m = &e[mid];
            if (m->id < id) {
                lo = mid + 1;
            } else if (m->id > id) {
                hi = mid - 1;
            } else {
                return m->v;
            }
        }
        {
            int i;
            for (i = 0; i < n; i++, e++) {
                if (e->id == id) {
                    r = e->v;
                    break;
                }
            }
        }
    }
    return r;
}

u32 fn_800F173C(u32 id) {
    IdTbl* t;
    if (id == 0xFFFF) return 0;
    if (id < 300 || id >= 1000) return 0;
    t = fn_80077064((char*)lbl_803674B4 + 0x595);
    {
        int lo = 0;
        int n = t->n;
        IdEnt* e = t->e;
        int hi = n - 1;
        while (lo <= hi) {
            int mid = lo + ((hi - lo) >> 1);
            s32 k = e[mid].id;
            if (k < (s32)id) {
                lo = mid + 1;
            } else if (k > (s32)id) {
                hi = mid - 1;
            } else {
                return e[mid].v;
            }
        }
        {
            int i;
            u32 r = 0;
            for (i = 0; i < n; i++, e++) {
                if (e->id == id) {
                    r = e->v;
                    break;
                }
            }
            return r;
        }
    }
}

#pragma use_lmw_stmw on
int fn_800F18BC(void* m) {
    u32 out[64];
    Grp* grp[64];
    u32* r;
    int ng;
    Grp** gp;
    u16* ip;
    u32* q;
    int cnt;
    int i;
    Grp* g;
    int j;
    int j2;
    if (m == 0) return 0;
    {
        void* o = fn_80007F10(m);
        if (o == 0) return 0;
        q = out;
        cnt = 0;
        ng = fn_80009E20(o, grp);
    }
    gp = grp;
    for (i = 0; i < ng; gp++, i++) {
        g = *gp;
        ip = (u16*)g;
        for (j = 0; j < g->n; ip += 2, j++) {
            u32 v = fn_800F173C(ip[2]);
            if (v) {
                *q++ = v;
                cnt++;
            }
        }
    }
    r = out;
    for (j2 = 0; j2 < cnt; r++, j2++) {
        fn_800E24F8(*r);
    }
    return cnt;
}
#pragma use_lmw_stmw off

static inline void Set4(int i, int a, int b, void* p) { fn_8017EA78(i, a, a, b, 0, p); }
