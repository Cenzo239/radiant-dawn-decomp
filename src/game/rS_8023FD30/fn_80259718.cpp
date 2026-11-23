#include "game/rS_8023FD30/audio.h"
struct UCfg {
    const char* name;
    u8 pad04[4];
    u8 type;   /* +0x08 */
    u8 v09;
    s16 v0A;
    s8 v0C;
    s8 v0D;
    s8 v0E;
    s8 v0F;
    u8 pad10;
    s8 v11;
    s8 v12;
    s8 v13;
    u8 v14;
};
class UMgr {
public:
    u8 pad[8];
    virtual void u08();
    virtual void u0C();
    virtual void u10();
    virtual void u14();
    virtual void u18();
    virtual void u1C();
    virtual void u20();
    virtual void u24();
    virtual void u28();
    virtual void u2C();
    virtual void u30();
    virtual void u34();
    virtual void u38();
    virtual f32 v3C();
    virtual f32 v40();
    virtual f32 v44();
};
class UP {
public:
    virtual void destroy(int);
    virtual void v0C();
    virtual int isActive();    /* +0x10 */
    virtual void v14();
    virtual int isReady();     /* +0x18 */
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void setA(s32);    /* +0x28 */
    virtual void v2C();
    virtual void v30();
    virtual int canSetB();     /* +0x34 */
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual f32 v64();
    virtual void v68();
    virtual f32 v6C();
    virtual f32 v70();
    virtual f32 v74();
    virtual f32 v78();
    virtual void v7C();
    virtual f32 v80();
    virtual f32 v84();
    virtual f32 v88();
    virtual f32 v8C();
    virtual f32 v90();
    virtual void v94();
    virtual int v98();
    void* groups;
    UMgr* mgr;
    UCfg* cfg;
    u8 pad10[0x48];
    s32 v58f;
    void* handle;
};
typedef void (*UCb)(UP*);
extern "C" {
extern UCb lbl_804CBFF4;
extern f32 lbl_804CAACC;
extern f32 lbl_804CAAC8;
extern f32 lbl_804CAAC4;
extern f32 lbl_804CAAC0;
double fn_80295AA4(double, f32);
void fn_802A1E30(void*);
void fn_802A2F5C(void*, f32, int);
void fn_802A3000(void*, f32);
void fn_802A3008(void*, f32);
void fn_802A3010(void*, f32);
void fn_802A3018(void*, f32);
void fn_802A3020(void*, f32);
void fn_802A305C(void*, f32, int);
void fn_802BAC48(void*, void*);
void fn_802BAB0C(void*, int);
void fn_802BAD54(void*);
void fn_802AA628(void*, void*);
void fn_802AA2CC(void*, int);
void fn_802AA734(void*);
}

struct FlagSet { u32 pad; u32 w[1]; };
extern "C" FlagSet lbl_804CBFE8;
static inline u32 test(SndMutex& m, u32 n) {
    m.lock();
    const u32* p = lbl_804CBFE8.w;
    while (n >= 32) {
        p++;
        n -= 32;
    }
    u32 r = (*p & (1 << n)) != 0;
    m.unlock();
    return r;
}
static inline UCb getCb(SndMutex& m) {
    m.lock();
    UCb cb = lbl_804CBFF4;
    m.unlock();
    return cb;
}
static inline f32 const& fMax(f32 const& a, f32 const& b) {
    return a < b ? b : a;
}

#define SET1(fn) { if (p->handle) fn(p->handle, v); }

static inline f32 pv(UCfg* c) {
    f32 st = c->v0C / 12.0f;
    if (c->v0A >= 0) {
        return fn_80295AA4(2.0, st * (c->v0A / 8191.0f));
    } else {
        return fn_80295AA4(2.0, st * (c->v0A / 8192.0f));
    }
}
static inline f32 g0(UP* p, f32 x) {
    return x * p->v6C();
}
static inline f32 g11(UP* p, f32 x) {
    f32 m = p->mgr->v40();
    return m + x;
}
static inline f32 g12(UP* p, f32 x) {
    f32 m = p->mgr->v44();
    return m + x;
}
/* Raw on/off guards: a real scoped lock in the expanded body puts the slots in the wrong order. */
struct RawGuard {
    void* vt;
    SndMutex* m;
    RawGuard() {}
    ~RawGuard() {}
    void on(SndMutex& x) { vt = lbl_80391888; m = &x; x.lock(); }
    void off() { vt = lbl_80391888; m->unlock(); }
};
struct HRef { void* h; };
static inline void hsetB(HRef& s, int v) { if (s.h) fn_802BAB0C(s.h, v); }
static inline void hsetA(HRef& s, int v) { if (s.h) fn_802AA2CC(s.h, v); }
/* Mix parameters of a player pushed to the low-level handle. The four copies differ only in the
   minimum volume constant, so the real source is probably one template or four small overrides. */
#define UPDATE_FN(NAME, MIN) \
void NAME(UP* p) { \
    SndMutex* m; \
    UCb cb; \
    f32 const* rr; \
    SndMutex* mm; \
    UCb cb2; \
    m = &lbl_8042E798; \
    SndLock g(*m); \
    if (!p->isReady() || !p->isActive()) { \
        return; \
    } \
    if (!p->canSetB()) { \
        if (test(*m, 0) || test(*m, 2)) { \
            p->setA(0); \
        } \
    } \
    if (p->v98() > 0) { \
        p->v58f = p->v58f - 16.666666f; \
        if (p->v58f <= 0) { \
            { \
                SndLock g2(lbl_8042E798); \
                mm = &lbl_8042E798; \
                mm->lock(); \
                cb = lbl_804CBFF4; \
                mm->unlock(); \
                if (cb) { \
                    mm->lock(); \
                    cb2 = lbl_804CBFF4; \
                    mm->unlock(); \
                    cb2(p); \
                } \
            } \
            if (p->handle) { \
                fn_802A1E30(p->handle); \
            } \
        } \
    } \
    f32 a = p->cfg->v09 / 127.0f; \
    { \
        f32 t = p->v64() + p->v8C(); \
        if (MIN < t) rr = &t; else rr = &MIN; \
        f32 m = p->mgr->v3C(); \
        f32 v = *rr * (m * a); \
        if (p->handle) fn_802A2F5C(p->handle, v, 0); \
    } \
    { \
        f32 st = p->cfg->v0C / 12.0f; \
        f32 x; \
        if (p->cfg->v0A >= 0) { \
            f32 d = st * (p->cfg->v0A / 8191.0f); \
            x = fn_80295AA4(2.0, d); \
        } else { \
            f32 d = st * (p->cfg->v0A / 8192.0f); \
            x = fn_80295AA4(2.0, d); \
        } \
        f32 v = p->v88() * g0(p, x); \
        SET1(fn_802A3000) \
    } \
    { \
        f32 x = 2.0f * (p->cfg->v0D / 127.0f) - 1.0f; \
        f32 v = x + p->v70(); \
        SET1(fn_802A3008) \
    } \
    { \
        s8 e = p->cfg->v0E; \
        f32 x = 2.0f * (e >= 0 ? e / 127.0f : e / 128.0f); \
        f32 v = x + p->v74(); \
        SET1(fn_802A3010) \
    } \
    { \
        f32 x = -(p->cfg->v0F / 127.0f); \
        f32 v = x + p->v78(); \
        SET1(fn_802A3018) \
    } \
    if (p->cfg->v14 != 1) { \
        { \
            f32 x = (p->cfg->v11 - 0x7F) / 127.0f; \
            f32 v = p->v80() + g11(p, x); \
            SET1(fn_802A3020) \
        } \
        { \
            f32 x = p->cfg->v12 / 127.0f; \
            f32 v = p->v84() + g12(p, x); \
            if (p->handle) fn_802A305C(p->handle, v, 0); \
        } \
        { \
            f32 x = p->cfg->v12 / 127.0f; \
            f32 v = p->v84() + g12(p, x); \
            if (p->handle) fn_802A305C(p->handle, v, 1); \
        } \
    } else { \
        if (p->handle) fn_802A3020(p->handle, 0.0f); \
        if (p->handle) fn_802A305C(p->handle, 0.0f, 0); \
        if (p->handle) fn_802A305C(p->handle, 0.0f, 1); \
    } \
}

/* The same body with a second check and guard around it: the base update inlined into a derived one. */
#define UPDATE2_FN(NAME, MIN, HDECL, TAIL) \
void NAME(UP* p) { \
    RawGuard g; \
    RawGuard g2; \
    RawGuard g1; \
    HDECL \
    f32 t; \
    SndMutex* m; \
    UCb cb; \
    f32 const* rr; \
    SndMutex* mm; \
    UCb cb2; \
    m = &lbl_8042E798; \
    g.on(*m); \
    if (!p->isReady() || !p->isActive()) { \
        g.off(); \
        return; \
    } \
    g1.on(*m); \
    if (!p->isReady() || !p->isActive()) { \
        g1.off(); \
        goto out; \
    } \
    if (!p->canSetB()) { \
        if (test(*m, 0) || test(*m, 2)) { \
            p->setA(0); \
        } \
    } \
    if (p->v98() > 0) { \
        p->v58f = p->v58f - 16.666666f; \
        if (p->v58f <= 0) { \
            { \
                g2.on(lbl_8042E798); \
                mm = &lbl_8042E798; \
                mm->lock(); \
                cb = lbl_804CBFF4; \
                mm->unlock(); \
                if (cb) { \
                    mm->lock(); \
                    cb2 = lbl_804CBFF4; \
                    mm->unlock(); \
                    cb2(p); \
                } \
                g2.off(); \
            } \
            if (p->handle) { \
                fn_802A1E30(p->handle); \
            } \
        } \
    } \
    f32 a = p->cfg->v09 / 127.0f; \
    { \
        t = p->v64() + p->v8C(); \
        if (MIN < t) rr = &t; else rr = &MIN; \
        f32 m = p->mgr->v3C(); \
        f32 v = *rr * (m * a); \
        if (p->handle) fn_802A2F5C(p->handle, v, 0); \
    } \
    { \
        f32 st = p->cfg->v0C / 12.0f; \
        f32 x; \
        if (p->cfg->v0A >= 0) { \
            f32 d = st * (p->cfg->v0A / 8191.0f); \
            x = fn_80295AA4(2.0, d); \
        } else { \
            f32 d = st * (p->cfg->v0A / 8192.0f); \
            x = fn_80295AA4(2.0, d); \
        } \
        f32 v = p->v88() * g0(p, x); \
        SET1(fn_802A3000) \
    } \
    { \
        f32 x = 2.0f * (p->cfg->v0D / 127.0f) - 1.0f; \
        f32 v = x + p->v70(); \
        SET1(fn_802A3008) \
    } \
    { \
        s8 e = p->cfg->v0E; \
        f32 x = 2.0f * (e >= 0 ? e / 127.0f : e / 128.0f); \
        f32 v = x + p->v74(); \
        SET1(fn_802A3010) \
    } \
    { \
        f32 x = -(p->cfg->v0F / 127.0f); \
        f32 v = x + p->v78(); \
        SET1(fn_802A3018) \
    } \
    if (p->cfg->v14 != 1) { \
        { \
            f32 x = (p->cfg->v11 - 0x7F) / 127.0f; \
            f32 v = p->v80() + g11(p, x); \
            SET1(fn_802A3020) \
        } \
        { \
            f32 x = p->cfg->v12 / 127.0f; \
            f32 v = p->v84() + g12(p, x); \
            if (p->handle) fn_802A305C(p->handle, v, 0); \
        } \
        { \
            f32 x = p->cfg->v12 / 127.0f; \
            f32 v = p->v84() + g12(p, x); \
            if (p->handle) fn_802A305C(p->handle, v, 1); \
        } \
    } else { \
        if (p->handle) fn_802A3020(p->handle, 0.0f); \
        if (p->handle) fn_802A305C(p->handle, 0.0f, 0); \
        if (p->handle) fn_802A305C(p->handle, 0.0f, 1); \
    } \
    g1.off(); \
out: \
    TAIL \
    g.off(); \
}

#define HANDLE_TAIL(CTOR, SET, DTOR) \
    if (0.0f <= p->v90()) { \
        CTOR(&s1, (u8*)p + 0x5C); \
        int x = (int)p->v90(); \
        SET(s1, x); \
        DTOR(&s1); \
    } else if (p->cfg->v13 >= 0) { \
        CTOR(&s2, (u8*)p + 0x5C); \
        SET(s2, p->cfg->v13); \
        DTOR(&s2); \
    }

#define NOTHING
#define HANDLES HRef s1; HRef s2;
extern "C" {
UPDATE_FN(fn_80259718, lbl_804CAACC)
UPDATE2_FN(fn_8025A0C0, lbl_804CAAC8, HANDLES, HANDLE_TAIL(fn_802BAC48, hsetB, fn_802BAD54))
UPDATE_FN(fn_8025A90C, lbl_804CAAC8)
UPDATE2_FN(fn_8025B218, lbl_804CAAC4, NOTHING, NOTHING)
UPDATE_FN(fn_8025B9B8, lbl_804CAAC4)
UPDATE2_FN(fn_8025C2C4, lbl_804CAAC0, HANDLES, HANDLE_TAIL(fn_802AA628, hsetA, fn_802AA734))
UPDATE_FN(fn_8025CB10, lbl_804CAAC0)
}
