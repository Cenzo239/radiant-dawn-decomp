#include "game/rS_8023FD30/sndmgr.h"
typedef SndLockable SndMutex;
#define lbl_8042E798 sMutex
#define SndLock SndGuard
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
    u8 pad15[0x1E - 0x15];
    s8 v1E;
    u8 pad1F;
    s8 v20;
    s8 v21;
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
struct Vec3 { f32 x, y, z; };
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
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual Vec3* vB4();
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
void fn_80312DB4(void*, Vec3*, Vec3*);
f32 fn_80313508(Vec3*);
void fn_802BAC48(void*, void*);
void fn_802BAB0C(void*, int);
void fn_802BAD54(void*);
double fn_80295AA4(double, f32);
void fn_802A1E30(void*);
void fn_802A2F5C(void*, f32, int);
void fn_802A3000(void*, f32);
void fn_802A3008(void*, f32);
void fn_802A3010(void*, f32);
void fn_802A3018(void*, f32);
void fn_802A3020(void*, f32);
void fn_802A305C(void*, f32, int);
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
static inline void vol(UP* p, f32 a) {
    f32 const* rr;
        f32 t = p->v64() + p->v8C();
        if (lbl_804CAACC < t) rr = &t; else rr = &lbl_804CAACC;
        f32 m = p->mgr->v3C();
        f32 v = *rr * (m * a);
        if (p->handle) fn_802A2F5C(p->handle, v, 0);
}
static inline void upd(UP* p) {
/*P*/
    f32 tt;
    f32 x;
    f32 a;
    SndMutex* m;
    UCb cb;
    f32 const* rr;
    SndMutex* mm;
    UCb cb2;
/*E*/
    m = &lbl_8042E798;
    SndLock g(*m);
    if (!p->isReady() || !p->isActive()) {
        return;
    }
    if (!p->canSetB()) {
        if (test(*m, 0) || test(*m, 2)) {
            p->setA(0);
        }
    }
    if (p->v98() > 0) {
        p->v58f = p->v58f - 16.666666f;
        if (p->v58f <= 0) {
            {
                SndLock g2(lbl_8042E798);
                mm = &lbl_8042E798;
                mm->lock();
                cb = lbl_804CBFF4;
                mm->unlock();
                if (cb) {
                    mm->lock();
                    cb2 = lbl_804CBFF4;
                    mm->unlock();
                    cb2(p);
                }
            }
            if (p->handle) {
                fn_802A1E30(p->handle);
            }
        }
    }
    vol(p, p->cfg->v09 / 127.0f);
    {
        f32 st = p->cfg->v0C / 12.0f;
        if (p->cfg->v0A >= 0) {
            f32 d = st * (p->cfg->v0A / 8191.0f);
            x = fn_80295AA4(2.0, d);
        } else {
            f32 d = st * (p->cfg->v0A / 8192.0f);
            x = fn_80295AA4(2.0, d);
        }
        f32 v = p->v88() * g0(p, x);
        SET1(fn_802A3000)
    }
    {
        x = 2.0f * (p->cfg->v0D / 127.0f) - 1.0f;
        f32 v = x + p->v70();
        SET1(fn_802A3008)
    }
    {
        s8 e = p->cfg->v0E;
        x = 2.0f * (e >= 0 ? e / 127.0f : e / 128.0f);
        f32 v = x + p->v74();
        SET1(fn_802A3010)
    }
    {
        x = -(p->cfg->v0F / 127.0f);
        f32 v = x + p->v78();
        SET1(fn_802A3018)
    }
    if (p->cfg->v14 != 1) {
        {
            x = (p->cfg->v11 - 0x7F) / 127.0f;
            f32 v = p->v80() + g11(p, x);
            SET1(fn_802A3020)
        }
        {
            x = p->cfg->v12 / 127.0f;
            f32 v = p->v84() + g12(p, x);
            if (p->handle) fn_802A305C(p->handle, v, 0);
        }
        {
            x = p->cfg->v12 / 127.0f;
            f32 v = p->v84() + g12(p, x);
            if (p->handle) fn_802A305C(p->handle, v, 1);
        }
    } else {
        if (p->handle) fn_802A3020(p->handle, 0.0f);
        if (p->handle) fn_802A305C(p->handle, 0.0f, 0);
        if (p->handle) fn_802A305C(p->handle, 0.0f, 1);
    }
}


static inline f32 fval(SndLockable& m, SndFader& f) {
    m.lock();
    f32 v = f.cur;
    m.unlock();
    return v;
}
static inline void nop2(SndLockable& m) {
    m.lock();
    m.unlock();
}
static inline f32 calc(f32 d) {
    f32 k = d - fval(sMutex, sFader9EC);
    if (k < 0.0f) k = 0.0f;
    return k / fval(sMutex, sFaderA00);
}
extern "C" {
void fn_80258C70(UP* p) {
/*P*/
    f32 x;
    f32 fa;
    f32 fb;
    f32 k;
    f32 b;
    f32 d;
    f32 k0;
    SndMutex* m;
/*E*/
    m = &lbl_8042E798;
    SndLock g(*m);
    if (!p->isReady() || !p->isActive()) {
        return;
    }
    upd(p);
    nop2(sMutex);
    Vec3 pos;
    fn_80312DB4(sPad098, p->vB4(), &pos);
    d = fn_80313508(&pos);
    k = calc(d);
    {
        b = k * -(p->cfg->v1E / 127.0f);
        x = -(p->cfg->v0F / 127.0f);
        f32 v = p->v78(); v = v + (x + b);
        if (p->handle) fn_802A3018(p->handle, v);
    }
    if (p->cfg->v14 != 1) {
        {
            x = (p->cfg->v11 - 0x7F) / 127.0f;
            b = k * (p->cfg->v20 / 127.0f);
            b = b + g11(p, x);
            f32 v = p->v80(); v = v + b;
            if (p->handle) fn_802A3020(p->handle, v);
        }
        {
            x = p->cfg->v12 / 127.0f;
            b = k * (p->cfg->v21 / 127.0f);
            b = b + g12(p, x);
            f32 v = p->v84(); v = v + b;
            if (p->handle) fn_802A305C(p->handle, v, 0);
        }
        {
            x = p->cfg->v12 / 127.0f;
            b = k * (p->cfg->v21 / 127.0f);
            f32 c = b + g12(p, x);
            f32 v = p->v84(); v = v + c;
            if (p->handle) fn_802A305C(p->handle, v, 1);
        }
    }
}
}
/* WIP: fn_80258C70, base update plus distance attenuation. About 12 words differ, all float registers:
   wants a=f31 and the v8C temp f30 (mine reversed), and the first fader value f31 and d f30 (mine
   reversed), plus the last fadds into f31. Integer registers and stack are all right. */
