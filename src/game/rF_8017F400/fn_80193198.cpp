#include "game/rF_8017F400/types.h"

extern "C" {

/* battle combatant (0x4A0 bytes), three of them at lbl_803C8E80 */
typedef struct BFaction {
    u8 pad[8];
    u8 id; /* 0x8 */
} BFaction;

typedef struct BPerson {
    u8 pad[0x18];
    struct BPerson* base; /* 0x18 */
    u8 pad1c[0x24 - 0x1C];
    u8 skills[0xEE - 0x24]; /* 0x24 */
    u16 flags; /* 0xee */
} BPerson;

typedef struct BRealUnit {
    u8 pad[0xF0];
    BPerson* person; /* 0xf0 */
    BFaction* faction; /* 0xf4 */
} BRealUnit;

typedef struct BUnit {
    u8 pad[0x3F0];
    BRealUnit* unit; /* 0x3f0 */
    u8 pad3f4[0x4A0 - 0x3F4];
} BUnit;

typedef struct BEvent {
    u8 type;
    u8 pad;
    s16 val;
} BEvent;

/* battle event queue at lbl_803C8E80 + 0xde0 */
typedef struct BEventQueue {
    s16 pos;
    u8 pad[2];
    BEvent e[1];
} BEventQueue;

typedef struct BattleState {
    BUnit u[3];
    BEventQueue q; /* 0xde0 */
    u8 pad[0x15EC - 0xDE8];
    u32 flags; /* 0x15ec */
} BattleState;

typedef struct BResultStats {
    u8 v[10];
} BResultStats;

typedef struct BResult {
    BRealUnit* unit;  /* 0x0 */
    s16 x4;
    s16 x6;
    s8 x8;
    s8 x9;
    u8 xa;
    u8 pad;
    BResultStats stats; /* 0xc */
} BResult;

/* battle result / exp gauge process */
typedef struct ExpProc {
    u8 pad[0x30];
    u8 alpha;  /* 0x30 */
    u8 x31;
    s8 x32;
    u8 count;  /* 0x33 */
    u16 timer; /* 0x34 */
    u16 max;   /* 0x36 */
    s16 x38;
    s16 x3a;
    s16 x3c;
    s16 x3e;
    f32 x40;
    s16 x44;
    s16 x46;
    s16 x48;
    u8 pad4a[2];
    BRealUnit* unit; /* 0x4c */
    void* tex;       /* 0x50 */
} ExpProc;

typedef struct SysInfo {
    u8 pad[0x1BC8];
    s8 lang; /* 0x1bc8 */
} SysInfo;

extern char* lbl_80388610[7];
extern void* lbl_804CA4E8;
extern void* lbl_804CA4EC;
extern int fn_8011B77C(void* skills, void* sid);
extern int fn_8028DB44(int x); /* abs */
extern void fn_80083DC4(void* proc, int result);
extern int fn_800AE654(void);
extern SysInfo* fn_8024BC94(void);
extern void fn_8023F1A0(char* path, int x);
extern void* fn_8001D3B4(char* path);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32 x, f32 y, f32 z, f32 w);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void* tex, p32arg, int b);
#else
extern void fn_8007E374(void* tex, int a, int b);
#endif
extern void* fn_800CD204(int x);
extern void fn_80176B54(int a, int b, int c, void* d, int e, int f, int g, int h, int i, int j);
extern void fn_800800D4(int x);
extern void fn_80080430(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
extern void fn_80080578(int x);
extern void fn_80080308(void);
extern void fn_8007E7DC(int a);
extern void fn_8007E7F4(void);
extern void fn_80193774(void* tex, f32 a, f32 b, int x, int y, int c);
extern f32 fn_8001EF30(f32 a, f32 b, f32 c, f32 t);
extern void fn_80083B78(void* proc);
class Pad {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual u32 getTrigger(); /* vtable +0x34 */
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual u32 getHeld(); /* vtable +0x48 */
};

class SoundChan {
public:
    virtual void v08();
    virtual void v0C();
    virtual BOOL isPlaying(); /* vtable +0x10 */
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void setVolume(f32 vol, f32 ms); /* vtable +0x38 */
};

extern Pad* lbl_804CB5B8;
extern u8 lbl_8038862C[0x74];
extern u8 lbl_803886A0[0x38];
extern SoundChan* fn_8024F3FC(s8 ch);
extern void fn_80253EE4(f32 vol, const char* name); /* play SFX */
extern void fn_8001D424(void* p);
extern void fn_800811E4(void* cls, void* parent);
extern void fn_801AA070(BRealUnit* u, void* parent);
extern int fn_80068D74(void);
extern void fn_800FAFF0(BRealUnit* u, int x);
extern void fn_80026000(BEventQueue* q);
extern int fn_800262A8(BEventQueue* q, int type);
extern int fn_800262F4(BEventQueue* q, int type);

extern BattleState lbl_803C8E80;

static inline BUnit* BS_GetUnit(int i)
{
    switch (i) {
    case 0:
        return &lbl_803C8E80.u[0];
    case 1:
        return &lbl_803C8E80.u[1];
    case 2:
        return &lbl_803C8E80.u[2];
    }
    return NULL;
}

static inline BOOL IsPlayerSide(BRealUnit* u)
{
    switch (u->faction->id) {
    case 0:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
        return TRUE;
    }
    return FALSE;
}

static inline BRealUnit* BS_GetPlayerUnit(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        BRealUnit* u = BS_GetUnit(i)->unit;
        if (u != NULL) {
            switch (u->faction->id) {
            case 0:
            case 5:
            case 7:
            case 8:
            case 9:
            case 10:
                return u;
            }
        }
    }
    return NULL;
}

static inline BOOL BS_ShowExp(void)
{
    return (lbl_803C8E80.flags & 0x10) ? FALSE : ((lbl_803C8E80.flags & 0x800) != 0);
}

BRealUnit* fn_80193198(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        BRealUnit* u = BS_GetUnit(i)->unit;
        if (u != NULL) {
            switch (u->faction->id) {
            case 0:
            case 5:
            case 7:
            case 8:
            case 9:
            case 10:
                return u;
            }
        }
    }
    return NULL;
}

void fn_80193294(BResultStats* out)
{
    s16 saved;
    BEventQueue* q;
    q = &lbl_803C8E80.q;
    saved = lbl_803C8E80.q.pos;
    fn_80026000(q);
    out->v[0] = 0;
    out->v[1] = 0;
    out->v[2] = 0;
    out->v[3] = 0;
    out->v[4] = 0;
    out->v[5] = 0;
    out->v[6] = 0;
    out->v[7] = 0;
    out->v[8] = 0;
    out->v[9] = 0;
    for (;;) {
        BEvent* e = &q->e[q->pos];
        switch (e->type) {
        case 0:
            goto end;
        case 0x32:
            out->v[0] = e->val;
            break;
        case 0x33:
            out->v[1] = e->val;
            break;
        case 0x34:
            out->v[2] = e->val;
            break;
        case 0x35:
            out->v[3] = e->val;
            break;
        case 0x36:
            out->v[4] = e->val;
            break;
        case 0x37:
            out->v[5] = e->val;
            break;
        case 0x38:
            out->v[6] = e->val;
            break;
        case 0x39:
            out->v[7] = e->val;
            break;
        case 0x3A:
            out->v[9] = e->val;
            break;
        case 0x3B:
            out->v[8] = e->val;
            break;
        }
        q->pos++;
    }
end:
    q->pos = saved;
}

void fn_80193404(BResult* r)
{
    r->unit = BS_GetPlayerUnit();
    r->xa = fn_800262A8(&lbl_803C8E80.q, 0x31);
    r->x4 = fn_800262F4(&lbl_803C8E80.q, 0x2D);
    r->x6 = fn_800262F4(&lbl_803C8E80.q, 0x2E);
    r->x8 = fn_800262F4(&lbl_803C8E80.q, 0x2F);
    r->x9 = fn_800262F4(&lbl_803C8E80.q, 0x30);
    fn_80193294(&r->stats);
}

void fn_80193590(void* tex, int x, int y, int max, int cur)
{
    int w;
    fn_8007E154();
    fn_8007E4E4(x, y, 100.0f, 1.0f);
    fn_8007E374(tex, 2, 0x11);
    fn_8007E164();
    fn_80176B54(0xF9, 0x1C, 2, fn_800CD204(1), 0, 0, 0x11, 0x18, 0x10, cur);
    w = (cur << 7) / max;
    if (w > 0) {
        if (w < 2) {
            w = 2;
        }
        fn_8007E154();
        fn_8007E4E4(x, y, 100.0f, 1.0f);
        fn_8007E374(tex, 1, 0x11);
        fn_8007E164();
        fn_800800D4(2);
        fn_80080430(81.0f, 35.0f, 0.0f, 0.0f, w, 16.0f);
        fn_80080578(0);
        fn_80080308();
    }
    fn_8007E154();
    fn_8007E4E4(x, y, 100.0f, 1.0f);
    fn_8007E374(tex, 0, 0x11);
    fn_8007E164();
    fn_800800D4(2);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 288.0f, 80.0f);
    fn_80080578(0);
    fn_80080308();
}

void fn_80193A2C(ExpProc* p)
{
    BResult r;
    BPerson* pd;
    fn_80193404(&r);
    p->unit = r.unit;
    p->x38 = r.x4;
    p->x3c = r.x4;
    p->x3e = r.x4 + r.x6;
    p->x3a = fn_8028DB44(r.x6);
    p->x40 = r.x8;
    p->x46 = r.x8;
    p->x48 = r.x8 + r.x9;
    p->x44 = fn_8028DB44(r.x9) * 3;
    if (!(lbl_803C8E80.flags & 0x400)) {
        p->x3a = 0;
    }
    if (!(lbl_803C8E80.flags & 0x10000)) {
        p->x44 = 0;
    }
    p->timer = 0;
    p->max = 0;
    p->alpha = 0;
    p->tex = NULL;
    p->x32 = -1;
    p->count = 0;
    if (p->x3a != 0) {
        p->count = 1;
    }
    if (p->x44 != 0) {
        p->count++;
    }
    if (p->count == 0) {
        fn_80083DC4(p, 99);
        return;
    }
    if (p->max < p->x3a) {
        p->max = p->x3a;
    }
    if (p->max < p->x44) {
        p->max = p->x44;
    }
    if (p->x44 != 0) {
        pd = p->unit->person;
        if (fn_8011B77C(pd->skills, lbl_804CA4E8) && !fn_8011B77C(pd->skills, lbl_804CA4EC)) {
            pd = pd->base;
        }
        if (pd != NULL) {
            if (pd->flags & 0x40) {
                p->x32 = 6;
            }
            if (pd->flags & 0x100) {
                p->x32 = 7;
            }
            if (pd->flags & 0x80) {
                p->x32 = 8;
            }
        }
    }
    if (fn_800AE654()) {
        p->x31 = 3;
    } else {
        p->x31 = 0;
    }
    fn_8023F1A0(lbl_80388610[fn_8024BC94()->lang], 0);
}

void fn_80193DD8(ExpProc* p)
{
    p->tex = fn_8001D3B4(lbl_80388610[fn_8024BC94()->lang]);
}

void fn_80193E24(ExpProc* p)
{
    fn_8007E154();
    fn_8007E7DC(p->alpha);
    fn_8007E164();
    if (p->x3a != 0) {
        fn_80193590(p->tex, 0xA0, 0xE0, 100, p->x38 % 100);
    }
    if (p->x44 != 0) {
        fn_80193774(p->tex, 30.0f, p->x40, 0xAC, 0x130, p->x32);
    }
    fn_8007E7F4();
}

void fn_80193ED0(ExpProc* p)
{
    p->timer++;
    p->alpha = fn_8001EF30(0.0f, 255.0f, 8.0f, p->timer);
    if (p->timer == 8) {
        fn_80083B78(p);
    }
}

void fn_80193F54(ExpProc* p)
{
    p->timer = 0;
}

void fn_80193F60(ExpProc* p)
{
    p->timer++;
    if (p->timer <= p->x3a) {
        p->x38 = fn_8001EF30(p->x3c, p->x3e, p->x3a, p->timer);
    }
    if (p->timer <= p->x44) {
        p->x40 = fn_8001EF30(p->x46, p->x48, p->x44, p->timer);
    }
    if (lbl_804CB5B8->getHeld() & 0xFFF0) {
        if (p->x3e != 100) {
            p->x38 = p->x3e;
            p->x40 = p->x48;
            p->timer = p->max;
        }
        fn_80083DC4(p, 10);
        return;
    }
    if (p->timer & 1) {
        fn_80253EE4(0.0f, "SFX_SYS_EX_POINT1");
    }
    if (p->timer >= p->max) {
        fn_80083B78(p);
    }
}

void fn_80194108(ExpProc* p)
{
    p->timer = 0;
}

void fn_80194114(ExpProc* p)
{
    p->timer++;
    p->alpha = fn_8001EF30(192.0f, 0.0f, 8.0f, p->timer);
    if (p->timer == 8) {
        fn_80083B78(p);
    }
}

void fn_80194198(ExpProc* p)
{
    if (p->tex != NULL) {
        fn_8001D424(p->tex);
    }
    if (lbl_803C8E80.flags & 0x10) {
        SoundChan* c = fn_8024F3FC((s8)p->x31);
        if (c != NULL && c->isPlaying()) {
            c->setVolume(1.0f, 1000.0f);
        }
    }
}

int fn_80194234(void* parent)
{
    if (!(lbl_803C8E80.flags & 0x400) && !(lbl_803C8E80.flags & 0x10000)) {
        return 0;
    }
    fn_800811E4(lbl_8038862C, parent);
    return 1;
}

int fn_80194288(void* parent)
{
    if (!BS_ShowExp()) {
        return 0;
    }
    fn_801AA070(BS_GetPlayerUnit(), parent);
    return 1;
}

void fn_801943D8(ExpProc* p)
{
    if (fn_80068D74()) {
        BRealUnit* u = BS_GetPlayerUnit();
        if (u != NULL) {
            fn_800FAFF0(u, 0);
        }
    } else {
        fn_80083DC4(p, 0);
    }
}

static inline BOOL BS_NeedResult(void)
{
    if (BS_ShowExp()) {
        return TRUE;
    }
    if (lbl_803C8E80.flags & 0x400) {
        return TRUE;
    }
    if (lbl_803C8E80.flags & 0x10000) {
        return TRUE;
    }
    return (lbl_803C8E80.flags & 0x10) != 0;
}

int fn_80194524(void* parent)
{
    if (!BS_NeedResult()) {
        return 0;
    }
    fn_800811E4(lbl_803886A0, parent);
    return 1;
}

}
