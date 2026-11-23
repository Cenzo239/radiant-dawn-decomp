#include "game/rC2_8005259C/base.h"
class Pad { public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual u32 v48();
};
struct CK { u8 pad[8]; u8 b8; };
struct UX { u8 pad[0xec]; void* ec; u8 pf0[4]; CK* f4; u8 pf8[4]; u8 fc; u8 pfd[5]; s8 x; s8 y; u8 p104[4]; u64 flags; u8 pe[0x3f0 - 0x110]; };
struct Opt { u8 pad[0x11]; u8 b11; };
struct Map { u8 pad[0xd]; u8 id[1]; };
extern "C" {
extern u32 lbl_804CB700;
extern Pad* lbl_804CB5B8;
extern UX* lbl_804CB810;
extern u8 lbl_803CAB38[];
extern u8 lbl_803CA870[];
extern Map lbl_803EC898;
extern char lbl_80361B8C[];
UX* fn_800677E4(void);
UX* fn_80067880(UX*);
void fn_80083DC4(void*, int);
#if TARGET_PC
FE10_PROTO void fn_801C6D2C(ptr32<const void>, void*, int, int, int);
#else
void fn_801C6D2C(UX*, void*, int, int, int);
#endif
void fn_80185720(void);
void fn_800620A8(void*, f32, f32);
void fn_80253EE4(const char*, f32);
u8 fn_80044FEC(UX*);
Opt* fn_80060728(void*);
void fn_80114D00(Map*);
void fn_80067168(UX*);
void fn_80045120(void*, UX*);
void fn_800451D4(void*, UX*);
int fn_8004A8EC(void);
void fn_801856F4(void);
void fn_8010E41C(void*, int);
void fn_801A7B20(void*);
#if TARGET_PC
FE10_PROTO int fn_80025A08(ptr32<const void>);
#else
int fn_80025A08(void*);
#endif
void fn_8013F204(void);
void fn_80193094(void);
}
static inline UX* unitAt(u8 id) {
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

extern "C" void fn_80052B64(void* p) {
    UX* c;
    u32 m;
    if (lbl_804CB700 & 0x80) {
        return;
    }
    m = lbl_804CB5B8->v48();
    c = fn_800677E4();
    if (c && (m & 0x2000)) {
        if (c->flags & 0x10000000) {
            return;
        }
        fn_80083DC4(p, 0);
        fn_801C6D2C(c, p, 0, 0, 0);
        fn_80185720();
        return;
    }
    if (m & 0x1000) {
        UX* u = fn_80067880(fn_800677E4());
        if (u) {
            fn_800620A8(lbl_803CAB38, u->x, u->y);
            fn_80083DC4(p, 0);
            fn_80253EE4(lbl_80361B8C, 0.0f);
            return;
        }
    }
    if (m & 0x400) {
        switch (fn_80044FEC(c)) {
        case 0:
            goto cancel;
        case 2:
            if (c->flags & 0x10000000) {
                return;
            }
            if (fn_80060728(lbl_803CAB38)->b11 == 2) {
                return;
            }
            if (c->flags & 0x800) {
                return;
            }
            c->flags |= 0x800;
            fn_80114D00(&lbl_803EC898);
            fn_80067168(c);
            fn_80253EE4(lbl_80361B8C + 0x1c, 0.0f);
            return;
        case 3:
        case 4:
            return;
        case 6:
            fn_80045120(lbl_803CA870, c);
            lbl_803EC898.id[c->x + c->y * 0x40] = c->fc;
            fn_80253EE4(lbl_80361B8C + 0x37, 0.0f);
            fn_80083DC4(p, 2);
            return;
        case 5:
            fn_800451D4(lbl_803CA870, c);
            if (fn_8004A8EC()) {
                fn_801856F4();
                fn_80083DC4(p, 8);
                return;
            }
            goto cancel;
        }
    }
    if (m & 0x800) {
        switch (fn_80044FEC(c)) {
        case 1:
            break;
        case 2:
            if (c->flags & 0x800) {
                c->flags &= ~0x800ULL;
                fn_80114D00(&lbl_803EC898);
                fn_80067168(c);
                fn_80253EE4(lbl_80361B8C + 0x4c, 0.0f);
                return;
            }
            break;
        case 0: {
            u8 buf[0x10];
            int any = 0;
            int i;
            fn_8010E41C(buf, 1);
            for (i = 1; i < 0xff; i++) {
                UX* u = unitAt(i);
                if (u->ec && buf[u->f4->b8] && (u->flags & 0x800)) {
                    u->flags &= ~0x800ULL;
                    any = 1;
                }
            }
            fn_80114D00(&lbl_803EC898);
            if (any) {
                fn_80253EE4(lbl_80361B8C + 0x4c, 0.0f);
            }
            return;
        }
        }
    }
    if (m & 0x4000) {
        fn_801A7B20(p);
        return;
    }
    if (!(m & 0x10)) {
        return;
    }
cancel:
    if (fn_80025A08(p)) {
        fn_8013F204();
        fn_801856F4();
        fn_80193094();
        fn_80083DC4(p, 9);
    }
}
