#include "game/rA_800068A0/types.h"
/* DVD error loop: polls the drive status, shows the error text and halts on a fatal error. */
extern "C" {
typedef long long s64;
typedef f32 Mtx[3][4];
typedef f32 Mtx44[4][4];
struct C4 { u8 r, g, b, a; };
struct DBlock { u8 x0[0x2C]; void* user; };
extern u8 lbl_804CB0F0;
extern void* lbl_804CB0F4;
extern u32 lbl_804CB700;
extern int fn_802FAA84(void);
extern void fn_802FB1C4(DBlock*, void (*)(int, DBlock*));
extern void fn_80022CB8(int, DBlock*);
extern void fn_80320978(s64);
extern int fn_802577F8(int);
extern void fn_8024E8D8(f32);
extern void fn_8024ED94(f32);
extern int fn_8031F6A8(void*);
extern void fn_803202B0(void*);
extern int fn_801D09F0(void);
extern void fn_80320548(void*);
extern void fn_8033111C(int);
#if TARGET_PC
extern FE10_PROTO struct PadV * fn_8028BACC(void);
#else
extern int fn_8028BACC(void);
#endif
extern void fn_8028BC24(void);
#if TARGET_PC
extern FE10_PROTO p32ret fn_8008AECC(int);
#else
extern int fn_8008AECC(int);
#endif
#if TARGET_PC
extern FE10_PROTO int fn_8008AEE4(p32arg);
extern FE10_PROTO int fn_8008B08C(p32arg);
#else
extern int fn_8008AEE4(int);
extern int fn_8008B08C(int);
#endif
extern void fn_8023550C(void);
extern void fn_8002230C(void);
extern void fn_80307298(int, f32, f32, f32, f32, C4);
extern void fn_80021FEC(int);
extern void fn_80021FE8(int);
extern void fn_80021860(int, int, u8);
extern void fn_800217CC(int);
extern void fn_80021808(int, u8, int, int, u8);
extern void fn_80312F48(Mtx44, f32, f32, f32, f32, f32, f32);
extern void fn_80307D98(Mtx44, int);
extern void fn_80021B68(int);
extern void fn_80312318(Mtx);
extern void fn_80307E48(Mtx, int);
extern void fn_80307E98(Mtx, int);
extern void fn_80021784(int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80022B54(s16, s16, s16);
extern const C4* fn_800CD204(int);
extern void fn_8008B19C(C4, int, f32, f32, f32, f32);
extern void fn_80083B58(int);
extern void fn_802355D4(void);
extern void fn_8007B458(void);
extern void fn_8032F774(int);
extern void fn_80330018(void);
extern void fn_8017FA40(void);
extern void fn_8008A15C(void);
class Snd { public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9C(); virtual void vA0(); virtual void vA4(); virtual void vA8(); virtual void vAC();
};
extern Snd* lbl_804CB5B8;
void fn_80022CCC(void) {
    Mtx44 pr;
    Mtx m;
    DBlock b0;
    DBlock b1;
    volatile u8 d0;
    volatile u8 d1;
    int cnt;
    int th;
    int code;
    int st;
    int tw;
    int txt;
    cnt = 0;
    while (1) {
        code = -1;
        st = fn_802FAA84();
        switch (st) {
        case 4: code = 1; break;
        case 6: code = 2; break;
        case 11: code = 3; break;
        case -1: code = 4; break;
        case 7: code = 5; break;
        }
        if (code < 0) {
            if (--cnt < 0) cnt = 0;
        } else {
            if (++cnt > 3) cnt = 3;
        }
        if (code >= 0) {
            d0 = 0;
            b0.user = (void*)&d0;
            fn_802FB1C4(&b0, fn_80022CB8);
            while (d0 == 0) {
                fn_80320978(5LL * (*(u32*)0x800000F8 / 4 / 1000));
            }
            if (b0.user == 0) {
                lbl_804CB0F0 = 1;
                goto chk;
            }
        }
        if (code < 0) {
            d1 = 0;
            b1.user = (void*)&d1;
            fn_802FB1C4(&b1, fn_80022CB8);
            while (d1 == 0) {
                fn_80320978(5LL * (*(u32*)0x800000F8 / 4 / 1000));
            }
            if (b1.user != 0 && cnt == 0) {
                lbl_804CB0F0 = 0;
            }
        }
    chk:
        if (lbl_804CB700 & 0x100) {
            lbl_804CB0F0 = 0;
        }
        if (lbl_804CB0F0 != 0 && fn_802577F8(1) == 0) {
            lbl_804CB5B8->vAC();
            fn_8024E8D8(0.0f);
        } else if (lbl_804CB0F0 == 0 && fn_802577F8(1) != 0) {
            if (fn_8031F6A8(lbl_804CB0F4) != 0) {
                fn_803202B0(lbl_804CB0F4);
            }
            fn_8024ED94(0.0f);
        }
        f32 w = fn_801D09F0() ? 0x31C : 0x260;
        f32 h = fn_801D09F0() ? 0x1C0 : 0x1C0;
        if (lbl_804CB0F0 != 0 && code >= 0 && cnt > 2) {
            if (st == -1) {
                fn_80320548(lbl_804CB0F4);
            }
            fn_8033111C(0);
            if (st != -1 && fn_8028BACC() != 0) {
                fn_8028BC24();
            }
            txt = fn_8008AECC(code);
            tw = fn_8008AEE4(txt);
            th = fn_8008B08C(txt);
            fn_8023550C();
            fn_8002230C();
            C4 fog;
            *(u32*)&fog = 0;
            fn_80307298(0, 0.0f, 0.0f, 0.0f, 0.0f, fog);
            fn_80021FEC(1);
            fn_80021FE8(1);
            fn_80021860(0, 3, 0);
            fn_800217CC(1);
            fn_80021808(7, 0, 1, 7, 0);
            fn_80312F48(pr, -(h / 2.0f), h / 2.0f, -(w / 2.0f), w / 2.0f, 0.0f, -100.0f);
            fn_80307D98(pr, 1);
            fn_80021B68(0);
            fn_80312318(m);
            fn_80307E48(m, 0);
            fn_80307E98(m, 0);
            fn_80021784(0);
            fn_80021BA4(1, 4, 5, 0);
            fn_80022B54(0, w, h);
            const C4* c = fn_800CD204(1);
            fn_8008B19C(*c, txt, -((f32)tw / 2.0f), -((f32)th / 2.0f), 10.0f, 1.0f);
            if (st != -1) {
                fn_80083B58(7);
            }
            fn_802355D4();
            if (st != -1) {
                fn_8007B458();
            }
            if (st == -1) {
                fn_8032F774(0);
                while (1) {
                    fn_80330018();
                }
            }
            fn_8017FA40();
            fn_8008A15C();
        } else {
            fn_80330018();
        }
    }
}
}
