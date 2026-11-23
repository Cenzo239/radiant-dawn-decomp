#include "game/rQ_80163178/types.h"
#pragma use_lmw_stmw on
#pragma auto_inline off

class Filter {
public:
    virtual int check(Unit*);
    virtual int at(int, int, int);
};
struct ListHdr { int n; };
struct Side { Unit* head; Unit* tail; int n; };
struct SkillAct { char* name; u8* item; int (*func)(Unit*, int, int, int); };
struct Filt {
    void* vt;
    Unit* u;
};
struct F3 {
    void* vt;
    void* a;
    void* b;
    F3(void* v, void* x, void* y) {
        b = y;
        a = x;
        vt = v;
    }
};
struct FF {
    void* vt;
    Unit* u;
    Filter* f;
    s8 x;
    s8 y;
};

extern "C" Unit* lbl_804CB810;
extern "C" int fn_8010E398(void*, void*);
static inline Unit* UnitGet(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}
static inline BOOL MapOutU(Map* m, Unit* v) {
    s8 x = v->x;
    s8 y = v->y;
    BOOL r = 0;
    if (x < m->x0 || m->x1 - 1 < x || y < m->y0 || m->y1 - 1 < y) {
        r = 1;
    }
    return r;
}
