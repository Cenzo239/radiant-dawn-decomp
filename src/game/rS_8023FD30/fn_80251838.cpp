#pragma inline_max_size(8192)
#pragma inline_max_total_size(30000)
#include "game/rS_8023FD30/sndmgr.h"
struct SndCfg {
    const char* name;
    u8 pad04[4];
    u8 type;
    u8 pad09;
    s16 v0A;
    s8 v0C;
    u8 pad0D[8];
    s8 limit;      /* +0x15 */
    s16 rndA;      /* +0x16 */
    s16 rndB;      /* +0x18 */
    s8 v1A;
    s8 v1B;
    u16 v1C;
};
class SndPlay {
public:
    virtual void destroy(int);
    virtual void v0C();
    virtual int isActive();    /* +0x10 */
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void start(s32);    /* +0x20 */
    virtual void stop(s32);    /* +0x24 */
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48f();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58f();
    virtual void v5C();
    virtual void v60f();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void setArg(void*);   /* +0xB0 */
    void* groups;
    void* mgr;
    SndCfg* cfg;
    u32 v10, v14f;
    f32 a0, a1, a2, a3;
    f32 b0, b1, b2, b3, b4, b5;
    f32 vol;
    f32 pan;
    s8 v48;
    s8 countdown;
    u8 pad4A[6];
    s64 time;
    u32 v58;
    u32 handle;
    u8 v60[0x10];
};
extern "C" {
extern void* lbl_804CBFDC;
extern char lbl_80391780[];
extern char lbl_80391180[];
extern char lbl_80391600[];
extern char lbl_80391480[];
extern char lbl_80391300[];
int fn_8025041C(void);
int fn_802505DC(void);
int fn_8025079C(void);
int fn_802501A4(const char*);
int fn_802502E0(const char*);
int fn_8024FD40(const char*);
int fn_8024FED4(const char*);
SndCfg* fn_80076F54(const char*);
int fn_80250068(const char*);
int fn_8024FBAC(const char*);
#if TARGET_PC
FE10_PROTO void* fn_8030E344(ptr32<const void>, u32, s32);
#else
void* fn_8030E344(void*, u32, s32);
#endif
s32 fn_80290EAC(void);
f32 fn_8017F68C(s32, f32, f32, f32, f32);
double fn_80295AA4(double, f32);
s64 OSGetTime(void);
void fn_802AB9E4(void*, void*, void*);
u32 fn_802AD3B0(void*, u32);
void fn_802B22B4(void*, void*, s32, s32);


#define POOL_FNS(X, POOL, N) \
static inline SndPlay* poolGet##X(SndLockable& m, s8 i) { \
    SndPlay* s; \
    m.lock(); \
    s = 0; \
    if (i >= 0 && i < N) { \
        s = (SndPlay*)POOL[i]; \
    } \
    m.unlock(); \
    return s; \
} \
static inline void poolSet##X(SndLockable& m, s8 i, SndPlay* v) { \
    m.lock(); \
    if (i >= 0 && i < N) { \
        POOL[i] = (SndPlayer*)v; \
    } \
    m.unlock(); \
}

POOL_FNS(A, sPoolA, 4)
POOL_FNS(B, sPoolB, 16)
POOL_FNS(C, sPoolC, 16)
POOL_FNS(D, sPoolD, 4)

static inline void* heapAlloc(u32 size) {
    SndGuard l(sMutex);
    return fn_8030E344(lbl_804CBFDC, size, 0x20);
}

static inline f32 randA(SndCfg* cfg) {
    return fn_8017F68C(0, cfg->rndB, cfg->rndA, fn_80290EAC(), 32767.0f);
}

static inline f32 randB(SndCfg* cfg) {
    return fn_8017F68C(0, cfg->v1B, cfg->v1A, fn_80290EAC(), 32767.0f);
}

static inline f32 pitchVar(SndCfg* cfg, f32 r) {
    f32 st = (f32)cfg->v0C / 12.0f;
    if (cfg->v0A >= 0) {
        return fn_80295AA4(2.0, st * (r / 8191.0f));
    } else {
        return fn_80295AA4(2.0, st * (r / 8192.0f));
    }
}

static inline f32 calcPitch(SndCfg* cfg) {
    if (cfg->rndA == 0 && cfg->rndB == 0) {
        return 1.0f;
    }
    return pitchVar(cfg, randA(cfg));
}

static inline f32 calcPan(SndCfg* cfg) {
    if (cfg->v1A == 0 && cfg->v1B == 0) {
        return 0.0f;
    }
    return randB(cfg) / 127.0f;
}


#define OBJ_BASE() \
    *(void**)p = lbl_80391780; \
    p->groups = sGroups; \
    p->mgr = sEffect; \
    p->cfg = cfg; \
    p->v10 = 0; \
    p->v14f = 0; \
    p->a0 = 1.0f; \
    p->a1 = 1.0f; \
    p->a2 = 1.0f; \
    p->a3 = 1.0f; \
    p->b0 = 0.0f; \
    p->b1 = 0.0f; \
    p->b2 = 0.0f; \
    p->b3 = 0.0f; \
    p->b4 = 0.0f; \
    p->b5 = 0.0f; \
    p->vol = calcPitch(cfg); \
    p->pan = calcPan(cfg); \
    p->v48 = -1; \
    p->countdown = 0; \
    p->time = OSGetTime(); \
    p->v58 = cfg->v1C; \
    p->handle = 0;

#define OBJ_60(vt) \
    { \
        SndGuard l(sMutex); \
        p = (SndPlay*)fn_8030E344(lbl_804CBFDC, 0x60, 0x20); \
    } \
    if (p != 0) { \
        OBJ_BASE() \
        *(void**)p = vt; \
        { \
            SndGuard g2(sMutex); \
            u32 id = fn_802AD3B0(sGroups, *(u32*)((u8*)p->cfg + 4)); \
            if (id != 0xFFFFFFFF) { \
                fn_802B22B4((u8*)p->mgr + 0xC, &p->handle, id, 0); \
            } \
        } \
    }

static inline SndPlay* create(SndCfg* cfg) {
    SndPlay* p = 0;
    if (cfg != 0) {
    switch (cfg->type) {
    case 0:
        OBJ_60(lbl_80391600)
        break;
    case 1:
        OBJ_60(lbl_80391480)
        break;
    case 2:
        OBJ_60(lbl_80391300)
        break;
    }
    }
    return p;
}

/* Evicts the oldest player when the sound's instance limit is reached. */
#define EVICT(X, COUNT, OLDEST) \
        if (cfg != 0) { \
            s8 lim = cfg->limit; \
            if (lim > 0 && lim <= COUNT(cfg->name)) { \
                s32 i = OLDEST(cfg->name); \
                m = (SndLockable*)&sMutex; \
                p = poolGet##X(*m, i); \
                p->stop(0); \
                m = (SndLockable*)&sMutex; \
                poolSet##X(*m, i, 0); \
                if (p) { \
                    if (p) { \
                        p->destroy(1); \
                    } \
                } \
            } \
        }

#define PUBLISH(X) \
        { \
            SndLockable* mm = (SndLockable*)&sMutex; \
            poolSet##X(*mm, r, p); \
        }

#define FAIL() \
            if (p) { \
                if (p) { \
                    p->destroy(1); \
                } \
            } \
            r = -1;

/* Plays a sound of any of the three kinds, into a free slot. */
#define PLAY_ANY(fn, X, FREE, COUNT, OLDEST) \
int fn(const char* name, f32 ms) { \
    SndCfg* cfg; \
    SndPlay* p; \
    s32 r; \
    SndLockable* m; \
    m = (SndLockable*)&sMutex; \
    SndGuard g(*m); \
    r = FREE(); \
    if ((s8)r >= 0) { \
        cfg = fn_80076F54(name); \
        EVICT(X, COUNT, OLDEST) \
        p = create(cfg); \
        if (p != 0 && p->isActive()) { \
            p->start(ms); \
            PUBLISH(X) \
        } else { \
            FAIL() \
        } \
    } \
    return r; \
}

/* Plays a sound of the 0xE0-byte kind and hands it an argument. */
#define PLAY_ARG(fn, X, FREE, COUNT, OLDEST) \
int fn(const char* name, void* arg, f32 ms) { \
    SndCfg* cfg; \
    SndPlay* p; \
    s32 r; \
    SndLockable* m; \
    m = (SndLockable*)&sMutex; \
    SndGuard g(*m); \
    r = FREE(); \
    if ((s8)r >= 0) { \
        cfg = fn_80076F54(name); \
        EVICT(X, COUNT, OLDEST) \
        p = 0; \
        if (cfg != 0) { \
            p = (SndPlay*)heapAlloc(0xE0); \
            if (p != 0) { \
                OBJ_BASE() \
                *(void**)p = lbl_80391180; \
                fn_802AB9E4(p->v60, sEffect, sMember60); \
                { \
                    SndGuard g2(sMutex); \
                    u32 id = fn_802AD3B0(sGroups, *(u32*)((u8*)p->cfg + 4)); \
                    if (id != 0xFFFFFFFF) { \
                        fn_802B22B4(p->v60, &p->handle, id, 0); \
                    } \
                } \
            } \
        } \
        if (p != 0 && p->isActive()) { \
            p->start(ms); \
            PUBLISH(X) \
            p->setArg(arg); \
        } else { \
            FAIL() \
        } \
    } \
    return r; \
}

/* Replaces whatever is playing in a fixed slot. */
#define PLAY_SLOT(fn, X) \
int fn(s32 r, const char* name, f32 ms) { \
    SndCfg* cfg; \
    SndPlay* p; \
    SndPlay* old; \
    SndLockable* m; \
    m = (SndLockable*)&sMutex; \
    SndGuard g(*m); \
    old = poolGet##X(*m, r); \
    if (old) { \
        old->stop(0); \
        m = (SndLockable*)&sMutex; \
        poolSet##X(*m, r, 0); \
        if (old) { \
            if (old) { \
                old->destroy(1); \
            } \
        } \
    } \
    cfg = fn_80076F54(name); \
    p = create(cfg); \
    if (p != 0 && p->isActive()) { \
        p->start(ms); \
        PUBLISH(X) \
    } else { \
        FAIL() \
    } \
    return r; \
}

PLAY_SLOT(fn_80251838, A)
PLAY_ANY(fn_80252C38, B, fn_8025041C, fn_80250068, fn_8024FBAC)
PLAY_ARG(fn_80253848, B, fn_8025041C, fn_80250068, fn_8024FBAC)
PLAY_ANY(fn_80253EE4, C, fn_802505DC, fn_802501A4, fn_8024FD40)
PLAY_ARG(fn_802549C4, C, fn_802505DC, fn_802501A4, fn_8024FD40)
PLAY_ANY(fn_80255368, D, fn_8025079C, fn_802502E0, fn_8024FED4)
PLAY_SLOT(fn_80255E48, D)

}
