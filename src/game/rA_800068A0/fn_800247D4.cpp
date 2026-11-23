#include "game/rA_800068A0/types.h"

/* Help/sally screen widgets: virtual dispatch through the UI class hierarchy.
 * Slot names are the vtable offsets. */

struct VB { int x0; };

/* vptr at +4 (behind a plain data base). */
class VP4 : public VB {
public:
 virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(void*, void*); virtual int v24(void*, void*);
 virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual s32 v50();
 virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(); virtual int v64(); virtual int v68(); virtual int v6C(); virtual int v70(); virtual int v74(); virtual int v78(); virtual int v7C(); virtual int v80(); virtual int v84(); virtual int v88(); virtual int v8C(); virtual int v90();
};

/* vptr at +0. */
class VP0 {
public:
    virtual int v08();
    virtual int v0C();
    virtual int v10();
    virtual int v14();
    virtual int v18(void*);
    virtual int v1C();
    virtual int v20();
    virtual int v24();
    virtual int v28();
    virtual int v2C();
    virtual int v30(void*, void*);
    virtual int v34(void*, void*);
    virtual int v38(void*, void*);
    virtual int v3C();
    virtual int v40(void*, void*);
    virtual int v44();
    virtual int v48();
    virtual int v4C();
    virtual void v50(void*);
    virtual void v54(void*);
};

struct WinA {
    u8 pad[0x18];
    struct Sub { u8 pad[0x54]; u8 b54; }* p18;
    u8 pad1C[0x20];
    VP4* p3C;
    u8 b40[0x66];
    s8 sA6;
};

struct WinB {
    u8 pad[0x32];
    s16 s32;
    VP0* p34;
    u8 b38, b39, b3A;
};

extern "C" {

extern s32 fn_800CB0FC(int, f32);
#if TARGET_PC
extern FE10_PROTO s32 fn_800CA3DC(p32arg, int, f32);
#else
extern s32 fn_800CA3DC(int, int, f32);
#endif
extern void fn_8006F1B4(int, int, int);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080ABC(int, f32);
#if TARGET_PC
extern FE10_PROTO void fn_80080C24(p32arg);
#else
extern void fn_80080C24(int);
#endif
extern void fn_80080308(void);

void fn_8002468C(VP0* self, WinA* a, WinB* b);

struct C4 { u8 r, g, b, a; C4(const C4& o) : r(o.r), g(o.g), b(o.b), a(o.a) {} };
extern const C4& fn_800CD204(int);
extern void fn_80080508(C4);

void fn_800247D4(void* s, WinB* b) {
    if (b[0].b39 == 2) {
        fn_80080508(fn_800CD204(0));
    } else {
        fn_80080508(fn_800CD204(b->b38 != 0));
    }
}

extern VP0* lbl_804CB5B8;
extern volatile u32 lbl_804CB700;
extern u8 lbl_804CB140;
extern u8 lbl_8041EB20[];
extern u8 lbl_803CA870[];
extern int fn_801A2224(void*);
extern void fn_800453B4(void*, int);
struct Fac { u8 pad[0x34]; VP0* p34; u8 b38, b39, b3A; };
extern Fac* fn_80085EF8(u8);

static inline BOOL inputBlocked(void) {
    u32 a = lbl_804CB700;
    u32 b = lbl_804CB700;
    BOOL r = 0;
    if ((a & 0x10) && !(b & 0x20)) {
        r = 1;
    }
    return r;
}

int fn_80024AD8(void* s, WinA* w) {
    u32 in;
    Fac* f = fn_80085EF8(w->b40[w->sA6]);
    if (inputBlocked()) {
        return f->p34->v40(w, f);
    }
    in = lbl_804CB5B8->v48();
    lbl_804CB140 = f->b3A + 0x80;
    if ((in & 0x400) && fn_801A2224(lbl_8041EB20) == 0) {
        return f->p34->v30(w, f);
    }
    if (in & 0x800) {
        return w->p3C->v20(w, f);
    }
    if (in & 0x1000) {
        return f->p34->v34(w, f);
    }
    if (in & 0x2000) {
        return w->p3C->v24(w, f);
    }
    if (in & 0x10) {
        return f->p34->v38(w, f);
    }
    if ((in & 0x4000) && fn_801A2224(lbl_8041EB20) == 0) {
        w->p18->b54 = 1;
        fn_800453B4(lbl_803CA870, 0x87);
        return 5;
    }
    return f->p34->v40(w, f);
}

extern void fn_80083B78(void*);
class VI { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); };

void fn_800257E4(void* p) {
    if (((VI*)lbl_804CB5B8)->v34() & 0xC00) {
        fn_80083B78(p);
    }
}

int fn_80024D1C(VP4* o) { return o->v90(); }
int fn_80024D2C(VP4* o) { return o->v90(); }
int fn_80024DE0(VP0* o) { return o->v10(); }
int fn_80024DFC(VP0* o) { return o->v0C(); }
int fn_80024E20(VP0* o) { return o->v08(); }
int fn_80024EC4(VP4* o) { return o->v50(); }

} /* extern "C" */
