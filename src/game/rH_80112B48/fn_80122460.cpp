/* Unit stats (base + job + personal, clamped to the job cap), 80122460..80124144. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern void fn_80106DD0(void*, Unit*);
extern int fn_8011B77C(void*, void*);
extern void* lbl_804CA4EC;
extern void* lbl_804CA4F4;
extern s8 fn_801243F4(Unit*);
extern s8 fn_80124CF0(Unit*);
extern s8 fn_80124FF4(Unit*);
extern s8 fn_801252F8(Unit*);
extern s8 fn_801258D8(Unit*);
extern s8 fn_80125EB8(Unit*);
extern s8 fn_801261E4(Unit*);
extern s8 fn_801264E8(Unit*);
extern s8 fn_801267F8(Unit*);
extern int fn_80126934(Unit*);
extern int fn_80109348(void*);

void fn_80122460(Unit* u) {
    fn_80106DD0(u->u390, u);
}

static inline s16 StatClamp(int v, int max) {
    if (v > max) {
        v = max;
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

static inline int StatJ(Unit* u, int i) {
    return u->stat[i] + u->job->base[i];
}

static inline s16 StatBaseF(Unit* u, int i) {
    int a = StatJ(u, i); int v = u->person->base[i] + a;
    if (v > u->job->max[i]) {
        v = u->job->max[i];
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

#define STAT_BASE(u, i) StatBaseF(u, i)

static inline s16 StatDoubled(Unit* u, int i) {
    int v = STAT_BASE(u, i);
    if (fn_8011B77C(u->skills, lbl_804CA4EC)) {
        if (fn_8011B77C(u->skills, lbl_804CA4F4) || (u->flags10C & 0x8000000)) {
            v *= 1.5f;
        } else {
            v *= 2;
        }
    }
    if (v > u->job->max[i]) {
        v = u->job->max[i];
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

static inline s8 Move(Unit* u) {
    int v = u->u116 + u->job->f5;
    if (v > 20) {
        v = 20;
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

s16 fn_8012246C(Unit* u) {
    return STAT_BASE(u, 0);
}

s16 fn_801224BC(Unit* u) {
    return STAT_BASE(u, 1);
}

s16 fn_8012250C(Unit* u) {
    return STAT_BASE(u, 2);
}

s16 fn_8012255C(Unit* u) {
    return STAT_BASE(u, 3);
}

s16 fn_801225AC(Unit* u) {
    return STAT_BASE(u, 4);
}

s16 fn_801225FC(Unit* u) {
    return STAT_BASE(u, 5);
}

s16 fn_8012264C(Unit* u) {
    return STAT_BASE(u, 6);
}

s16 fn_8012269C(Unit* u) {
    return STAT_BASE(u, 7);
}

s8 fn_801226EC(Unit* u) {
    return Move(u);
}

s16 fn_80122720(Unit* u) {
    return STAT_BASE(u, 0);
}

s16 fn_80122770(Unit* u) {
    return StatDoubled(u, 1);
}

s16 fn_80122880(Unit* u) {
    return StatDoubled(u, 2);
}

s16 fn_80122990(Unit* u) {
    return StatDoubled(u, 3);
}

s16 fn_80122AA0(Unit* u) {
    return StatDoubled(u, 4);
}

s16 fn_80122BB0(Unit* u) {
    int v = STAT_BASE(u, 5);
    if (v > u->job->max[5]) {
        v = u->job->max[5];
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

s16 fn_80122C20(Unit* u) {
    return StatDoubled(u, 6);
}

s16 fn_80122D30(Unit* u) {
    return StatDoubled(u, 7);
}

s8 fn_80122E40(Unit* u) {
    int v = Move(u);
    if (v > 20) {
        v = 20;
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

int fn_80122E8C(Unit* u, u32 i) {
    switch (i) {
    case 0:
        return u->stat[0];
    case 1:
        return u->stat[1];
    case 2:
        return u->stat[2];
    case 3:
        return u->stat[3];
    case 4:
        return u->stat[4];
    case 5:
        return u->stat[5];
    case 6:
        return u->stat[6];
    case 7:
        return u->stat[7];
    }
    return -1;
}

static inline s16 StatRoom(Unit* u, int i) {
    int v = u->job->max[i];
    if (u->job->promoted && fn_8011B77C(u->skills, lbl_804CA4EC)) {
        v = ((Job*)u->job->promoted)->max[i];
    }
    return v - (u->person->base[i] + u->job->base[i]);
}

s16 fn_80123288(Unit* u) {
    return StatRoom(u, 0);
}

s16 fn_80123318(Unit* u) {
    return StatRoom(u, 1);
}

s16 fn_801233A8(Unit* u) {
    return StatRoom(u, 2);
}

s16 fn_80123438(Unit* u) {
    return StatRoom(u, 3);
}

s16 fn_801234C8(Unit* u) {
    return StatRoom(u, 4);
}

s16 fn_80123558(Unit* u) {
    return StatRoom(u, 5);
}

s16 fn_801235E8(Unit* u) {
    return StatRoom(u, 6);
}

s16 fn_80123678(Unit* u) {
    return StatRoom(u, 7);
}

s8 fn_80123708(Unit* u) {
    int v = 0x63;
    if (u->job->promoted && fn_8011B77C(u->skills, lbl_804CA4EC)) {
        v = 0x63;
    }
    return v - (u->person->level1F + u->job->levelF0);
}

s8 fn_80123780(Unit* u) {
    int v = 0x14;
    if (u->job->promoted && fn_8011B77C(u->skills, lbl_804CA4EC)) {
        v = 0x14;
    }
    return v - u->job->f5;
}

s16 fn_801237EC(Unit* u) {
    s16 v = STAT_BASE(u, 0);
    return v + fn_801243F4(u);
}

s16 fn_8012386C(Unit* u) {
    s16 v = StatDoubled(u, 1);
    s16 r = v + fn_80124CF0(u);
    if (r < 0) {
        r = 0;
    }
    return r;
}

s16 fn_80123998(Unit* u) {
    s16 v = StatDoubled(u, 2);
    s16 r = v + fn_80124FF4(u);
    if (r < 0) {
        r = 0;
    }
    return r;
}

s16 fn_80123AC4(Unit* u) {
    s16 v = StatDoubled(u, 3);
    s16 r = v + fn_801252F8(u);
    if (r < 0) {
        r = 0;
    }
    return r;
}

s16 fn_80123BF0(Unit* u) {
    s16 v = StatDoubled(u, 4);
    s16 r = v + fn_801258D8(u);
    if (r < 0) {
        r = 0;
    }
    return r;
}

s16 fn_80123D1C(Unit* u) {
    int v = STAT_BASE(u, 5);
    s16 r;
    if (v > u->job->max[5]) {
        v = u->job->max[5];
    }
    if (v < 0) {
        v = 0;
    }
    r = (s16)v + fn_80125EB8(u);
    if (r < 0) {
        r = 0;
    }
    return r;
}

s16 fn_80123DC4(Unit* u) {
    s16 v = StatDoubled(u, 6);
    s16 r = v + fn_801261E4(u);
    if (r < 0) {
        r = 0;
    }
    return r;
}

s16 fn_80123EF0(Unit* u) {
    s16 v = StatDoubled(u, 7);
    s16 r = v + fn_801264E8(u);
    if (r < 0) {
        r = 0;
    }
    return r;
}

s8 fn_8012401C(Unit* u) {
    int v = *(s8*)&u->person->level1F;
    v += u->job->levelF0;
    v += (s8)u->exp115;
    v += fn_801267F8(u);
    if (v > 0x63) {
        v = 0x63;
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

s8 fn_8012408C(Unit* u) {
    if (fn_80109348(u->skills110)) {
        return 0;
    }
    {
        int v = Move(u);
        s8 r;
        if (v > 20) {
            v = 20;
        }
        if (v < 0) {
            v = 0;
        }
        r = v + fn_80126934(u);
        if (r > 20) {
            r = 20;
        }
        if (r < 0) {
            r = 0;
        }
        return r;
    }
}

s8 fn_80124144(Unit* u) {
    int v = *(s8*)&u->person->level1F;
    v += u->job->levelF0;
    v += (s8)u->exp115;
    v += fn_801267F8(u);
    if (v > 0x63) {
        v = 0x63;
    }
    if (v < 0) {
        v = 0;
    }
    v = (s8)v + (s8)(u->job->f2 + u->job->f4);
    if (v > 0x63) {
        v = 0x63;
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

}
