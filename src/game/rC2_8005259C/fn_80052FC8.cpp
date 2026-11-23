#include "game/rC2_8005259C/base.h"
class Pad { public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual u32 v48();
};
struct MU { u8 pad[0x102]; s8 x; s8 y; };
struct Ctx { MU* p0; u8 pad4[0x12]; s8 b16; };
struct GD { u8 pad[0x934]; f32 x; f32 y; };
extern "C" {
extern u32 lbl_804CB700;
extern Pad* lbl_804CB5B8;
extern Ctx lbl_803CA870;
extern GD lbl_803CAB38;
extern u8 lbl_803EC898[];
extern char lbl_80361B8C[];
void* fn_800677E4(void);
void fn_80083DC4(void*, int);
#if TARGET_PC
FE10_PROTO void fn_801C6D2C(ptr32<const void>, void*, int, int, int);
#else
void fn_801C6D2C(void*, void*, int, int, int);
#endif
void fn_80185720(void);
int fn_80067D74(s8, s8);
void fn_80253EE4(const char*, f32);
void fn_8013F204(void);
void fn_800312BC(void);
void fn_80114D00(void*);
int fn_8012408C(MU*);
void fn_8014083C(int, int, int);
void fn_800620A8(GD*, f32, f32);
}

static inline int tryAt(s8 x, s8 y) {
    return fn_80067D74(x, y);
}

static inline void tl() {
    MU* u = lbl_803CA870.p0;
    s8 x;
    s8 y;
    y = u->y;
    x = u->x;
    int k = fn_8012408C(u);
    fn_8014083C(x, y, (s8)k);
    fn_800620A8(&lbl_803CAB38, u->x, u->y);
    fn_80253EE4(lbl_80361B8C + 0x85, 0.0f);
}
extern "C" void fn_80052FC8(void* p) {
    u32 m;
    void* v;
    if (lbl_804CB700 & 0x80) {
        return;
    }
    m = lbl_804CB5B8->v48();
    v = fn_800677E4();
    if (v && (m & 0x2000)) {
        fn_80083DC4(p, 3);
        fn_801C6D2C(v, p, 0, 0, 0);
        fn_80185720();
        return;
    }
    if (m & 0x400) {
        {s8 fy=lbl_803CAB38.y; s8 fx=lbl_803CAB38.x; if (!fn_80067D74(fx,fy)) {
            fn_80253EE4(lbl_80361B8C + 0x67, 0.0f);
            return;
        }}
        fn_80083DC4(p, 6);
        fn_8013F204();
        fn_800312BC();
        fn_80253EE4(lbl_80361B8C + 0x75, 0.0f);
        return;
    }
    if (m & 0x800) {
        if (lbl_803CA870.b16 == 0) {
            fn_80114D00(lbl_803EC898);
            fn_80083DC4(p, 0xa);
            fn_8013F204();
            fn_800312BC();
            fn_80253EE4(lbl_80361B8C + 0x85, 0.0f);
            return;
        }
    } else if (!(m & 0x1000)) {
        return;
    }
    tl();
}
