#include "game/rI_801DD7D4/types.h"
extern "C" {
extern char lbl_8036F03C[];
extern u8 lbl_8038D668[];
typedef struct Pt { s16 x, y; } Pt;
static inline Pt mk(u32 r) { Pt p; p.x = r >> 16; p.y = r; return p; }
struct Win { u32 flags; u8 pad[0x100]; };
extern Win lbl_8041EB20;
struct LBL { u8* x0; u8 pad[0x12c]; };
extern LBL lbl_803CA870;
void* fn_801E9B28(void*);
void fn_801E5954(void*);
int fn_801A2224(Win*);
void fn_801A1F64(Win*, void*, f32, f32);
void fn_801A1CFC(Win*);
void fn_801A1BE0(Win*, void*, void*, f32, f32);
void fn_80253EE4(const char*, f32);
void* fn_8012A088(void*, int);
struct UB { u32 x0, x4; };
UB* fn_801116B8(void*);
void* fn_80081194(void*, void*);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
#if TARGET_PC
FE10_PROTO struct Inv * fn_8012759C(void*);
#else
int fn_8012759C(void*);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_80127648(...);
#else
int fn_80127648(void*);
#endif
void fn_801E6B64(const char*, void*, f32, f32);
struct IN { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern IN* lbl_804CB5B8;
struct LV { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual u32 v30(); virtual void v34(void*); virtual int v38(void*); };
struct LM { u8 p[0x4c]; u8 x4c; u8 p2[3]; s16 x50; };
struct PR { u8 p[0x4c]; LM* x4c; };
#define HEAD \
    prev = fn_801E9B28(m); \
    fn_801E5954(o); \
    if (prev != fn_801E9B28(m)) { \
        prev = fn_801E9B28(m); \
        if (fn_801A2224(&lbl_8041EB20)) { \
            if (prev) { \
                Pt q = mk(((LV*)m)->v30()); \
                fn_801A1F64(&lbl_8041EB20, prev, q.x, q.y); \
            } else { \
                fn_801A1CFC(&lbl_8041EB20); \
            } \
        } \
    }
void fn_801F7388(PR* o) {
        LM* m;
    void* prev;
    u32 sh;
    s16 sv;
    u32 rep;
    void* u;
    m = o->x4c;
    HEAD;
    if (inputBlocked()) return;
    rep = lbl_804CB5B8->v48();
    if ((rep & 0x400) && prev && !fn_801A2224(&lbl_8041EB20)) {
        sh = (u32)lbl_803CA870.x0;
        if (!((LV*)m)->v38(prev)) {
            fn_80253EE4(lbl_8036F03C + 0xf3, 0.0f);
            return;
        }
        fn_80253EE4(lbl_8036F03C + 0x11b, 0.0f);
        u = fn_8012A088((void*)sh, m->x50);
        if (fn_801116B8(u)->x4 & 0x11) {
            ((LV*)m)->v34((void*)sh);
        } else {
            sv = m->x50;
            ((LV*)m)->v34((void*)sh);
            m->x50 = sv;
        }
        if ((fn_801116B8(u)->x0 & 0x100) || (*(u32*)(sh + 0x10c) & 0x800000)) {
            fn_80081194(lbl_8038D668, o);
        }
        return;
    }
    if ((rep & 0x2000) && !fn_801A2224(&lbl_8041EB20) && prev) {
        Pt q = mk(((LV*)m)->v30());
        fn_801A1BE0(&lbl_8041EB20, o, prev, q.x, q.y);
        lbl_8041EB20.flags |= 2;
        return;
    }
    if ((rep & 0x2800) && fn_801A2224(&lbl_8041EB20)) {
        fn_801A1CFC(&lbl_8041EB20);
        return;
    }
    if ((rep & 0x800) && !fn_801A2224(&lbl_8041EB20)) {
        fn_80083DC4(o, 0x15);
        fn_80253EE4(lbl_8036F03C + 0x3b, 0.0f);
    }
}

struct SB { u8 p[0x1c1]; u8 f : 1; u8 r : 7; };
void fn_801F7890(PR* o) {
        LM* m;
    u32 sh;
    int k;
    s16 sv;
    u32 rep;
    void* prev;
    m = o->x4c;
    HEAD;
    if (inputBlocked()) return;
    rep = lbl_804CB5B8->v48();
    if ((rep & 0x400) && prev && !fn_801A2224(&lbl_8041EB20)) {
        sh = (u32)lbl_803CA870.x0;
        if (!((LV*)m)->v38(prev)) {
            fn_80253EE4(lbl_8036F03C + 0xf3, 0.0f);
            return;
        }
        fn_80253EE4(lbl_8036F03C + 0x148, 0.0f);
        {
            SB* b = (SB*)(lbl_803CA870.x0 + m->x50 * 0x28);
            b->f = 0;
        }
        sv = m->x50;
        ((LV*)m)->v34((void*)sh);
        m->x50 = sv;
        k = 1;
        if (!fn_8012759C((void*)sh) && !fn_80127648((void*)sh)) k = 0;
        if (fn_801116B8(prev)->x0 & 0x100) {
            fn_80081194(lbl_8038D668, o);
        }
        if (k == 0) goto X;
        return;
    }
    if ((rep & 0x2000) && !fn_801A2224(&lbl_8041EB20) && prev) {
        Pt q = mk(((LV*)m)->v30());
        fn_801A1BE0(&lbl_8041EB20, o, prev, q.x, q.y);
        lbl_8041EB20.flags |= 2;
        return;
    }
    if ((rep & 0x2800) && fn_801A2224(&lbl_8041EB20)) {
        fn_801A1CFC(&lbl_8041EB20);
        return;
    }
    if ((rep & 0x800) && !fn_801A2224(&lbl_8041EB20)) {
X:
        fn_80083DC4(o, 0x18);
        fn_80253EE4(lbl_8036F03C + 0x3b, 0.0f);
    }
}
void fn_801F8088(PR* o) {
        LM* m;
    void* prev;
    u32 rep;
    m = o->x4c;
    m->x4c = 1;
    HEAD;
    if (inputBlocked()) return;
    rep = lbl_804CB5B8->v48();
    if ((rep & 0x400) && prev && !fn_801A2224(&lbl_8041EB20)) {
        if (!((LV*)m)->v38(prev)) {
            Pt q = mk(((LV*)m)->v30());
            fn_801E6B64(lbl_8036F03C + 0x173, o, q.x, q.y);
            return;
        }
        fn_80253EE4(lbl_8036F03C + 0x2b, 0.0f);
        fn_80083B78(o);
        return;
    }
    if ((rep & 0x2000) && !fn_801A2224(&lbl_8041EB20) && prev) {
        Pt q = mk(((LV*)m)->v30());
        fn_801A1BE0(&lbl_8041EB20, o, prev, q.x, q.y);
        lbl_8041EB20.flags |= 2;
        return;
    }
    if ((rep & 0x2800) && fn_801A2224(&lbl_8041EB20)) {
        fn_801A1CFC(&lbl_8041EB20);
        return;
    }
    if ((rep & 0x800) && !fn_801A2224(&lbl_8041EB20)) {
        fn_80083DC4(o, 0x1c);
        fn_80253EE4(lbl_8036F03C + 0x3b, 0.0f);
    }
}
}
