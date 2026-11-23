/* Unit support levels (Unit +0x300), 8012E830..8012EDA0. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern Unit* fn_8012CECC(void*);
extern void* fn_8010B250(int);
extern s8 fn_801197F4(void*, int);

struct SupItem {
    void* pid;
    u8 flag;
    u8 val;
};

struct SupData {
    void* pid;
    int count;
    SupItem e[1];
};

struct SupCfg {
    u8 lv[4];
    u8 pad4[7];
    s8 add[4];
};

extern SupCfg* lbl_804CB808;

static inline SupData* SupOf(Person* p) {
    return *(SupData**)((u8*)p + 0xdc);
}

u8 fn_8012E830(Unit* u) {
    SupData* d = SupOf(u->person);
    if (d == 0) {
        return 0;
    }
    return d->count;
}

static inline void* SupPid(Unit* u, int i) {
    if (i < 0) {
        return 0;
    }
    return SupOf(u->person)->e[i].pid;
}

void fn_8012E88C(Unit* u, int i, u8 v) {
    if (i >= 0) {
        u->sup[i] = v;
    }
}

u8 fn_8012E8A0(Unit* u, int i) {
    if (i < 0) {
        return 0;
    }
    return u->sup[i];
}

static inline u32 SupVal(Unit* u, int i) {
    if (i < 0) {
        return 0;
    }
    return u->sup[i];
}

int fn_8012E8BC(Unit* u, int i) {
    SupCfg* c;
    SupItem* e;
    u32 v;
    if (i < 0) {
        return 0;
    }
    c = lbl_804CB808;
    e = &SupOf(u->person)->e[i];
    if (e == 0) {
        return 0;
    }
    v = SupVal(u, i);
    if (v <= c->lv[0]) {
        return 0;
    }
    if (v <= c->lv[1]) {
        return 1;
    }
    return v <= c->lv[2] ? 2 : 3;
}

static inline u8 SupCount(Person* p) {
    SupData* d = SupOf(p);
    if (d == 0) {
        return 0;
    }
    return d->count;
}

static inline void* SupAt(Person* p, int i) {
    if (i < 0) {
        return 0;
    }
    return SupOf(p)->e[i].pid;
}

static inline int SupIdx(Person* p, void* pid) {
    int r = -1;
    int i;
    for (i = 0; i < SupCount(p); i++) {
        if (SupAt(p, i) == pid) {
            r = (s8)i;
            break;
        }
    }
    return r;
}

void fn_8012EC10(Unit* u, int i) {
    if (i >= 0) {
        u->sup[i]++;
    }
}

void fn_8012ECF8(Unit* u) {
    int i;
    for (i = 0; i < 0x48; i++) {
        u->sup[i] = 0;
    }
}

void fn_8012ED88(Unit* u, int i) {
    if (i >= 0) {
        u->sup[i] = 0;
    }
}

}
