/* NEAR MISS: fn_8028B84C 2 words. The value kept across fn_8023FB24 should be r29, ours r31. */
/* Health and safety screen: language select, preload and setup */
#include "game/rN_8025EEF0/calls.h"

extern "C" {

struct TvS {
    void* m0; void* m4; void* m8; void* mC; void* m10;
    int m14; int m18; u32 m1C; int m20; int m24; int m28; int m2C;
    f32 m30; f32 m34; f32 m38; int m3C;
    u8 pad40[0x40];
};
extern TvS lbl_80432E90;
extern void* lbl_804CC0E8;
extern void* lbl_804CC0EC;
extern void* lbl_804CC0F4;
extern void* lbl_804CC0F8;
extern void* lbl_804CC0FC;
int fn_80325918(void);
void* fn_80079940(int size, int align);
void* fn_8030E294(void* p, int size, int a);
void fn_8030E4C0(void* h, int a);
#if TARGET_PC
FE10_PROTO void* fn_8030E344(ptr32<const void>, int size, int align);
#else
void* fn_8030E344(void* h, int size, int align);
#endif
void* fn_8023F1A4(const char* s, int a);
#if TARGET_PC
FE10_PROTO int fn_8023FB24(ptr32<const void>);
#else
int fn_8023FB24(void* res);
#endif
void fn_8032DAD8(void* res);
void fn_80348A48(TvS* s);
void fn_80348D9C(void);
void fn_80348DAC(void* a, void* b, int c);
extern char lbl_8039310C[], lbl_803930E8[], lbl_803930C4[], lbl_803930A0[], lbl_8039307C[], lbl_80393058[], lbl_80393034[], lbl_80393014[];
extern char lbl_80392FF8[], lbl_80392FD8[], lbl_80392FB8[], lbl_80392F90[];
extern char lbl_803932CC[], lbl_803932A8[], lbl_80393284[], lbl_80393260[], lbl_8039323C[], lbl_80393218[], lbl_803931F4[], lbl_803931D4[];
extern char lbl_803931B8[], lbl_80393198[], lbl_80393178[], lbl_80393150[], lbl_8039312C[];

void fn_8028B720(void) {
    lbl_80432E90.m1C = (u8)fn_80325918();
    switch (lbl_80432E90.m1C) {
    case 0: fn_8023F1A0(lbl_8039310C, 0x880); break;
    case 1: fn_8023F1A0(lbl_803930E8, 0x880); break;
    case 2: fn_8023F1A0(lbl_803930C4, 0x880); break;
    case 3: fn_8023F1A0(lbl_803930A0, 0x880); break;
    case 4: fn_8023F1A0(lbl_8039307C, 0x880); break;
    case 5: fn_8023F1A0(lbl_80393058, 0x880); break;
    case 6: fn_8023F1A0(lbl_80393034, 0x880); break;
    default: fn_8023F1A0(lbl_80393014, 0x880); break;
    }
    fn_8023F1A0(lbl_80392FF8, 0x880);
    fn_8023F1A0(lbl_80392FD8, 0x880);
    fn_8023F1A0(lbl_80392FB8, 0x880);
    fn_8023F1A0(lbl_80392F90, 0x880);
}

void fn_8028B84C(void) {
/*P*/
    int z;
    TvS* st;
    void* a;
    int k;
/*E*/
    lbl_80432E90.m1C = (u8)fn_80325918();
    k = 0x9D1A8;
    lbl_804CC0E8 = fn_80079940(k, 0x40);
    lbl_804CC0EC = fn_8030E294(lbl_804CC0E8, k, 0);
    switch (lbl_80432E90.m1C) {
    case 0: lbl_80432E90.m0 = fn_8023F1A4(lbl_803932CC, 0x880); break;
    case 1: lbl_80432E90.m0 = fn_8023F1A4(lbl_803932A8, 0x880); break;
    case 2: lbl_80432E90.m0 = fn_8023F1A4(lbl_80393284, 0x880); break;
    case 3: lbl_80432E90.m0 = fn_8023F1A4(lbl_80393260, 0x880); break;
    case 4: lbl_80432E90.m0 = fn_8023F1A4(lbl_8039323C, 0x880); break;
    case 5: lbl_80432E90.m0 = fn_8023F1A4(lbl_80393218, 0x880); break;
    case 6: lbl_80432E90.m0 = fn_8023F1A4(lbl_803931F4, 0x880); break;
    default:
        lbl_80432E90.m1C = 0;
        lbl_80432E90.m0 = fn_8023F1A4(lbl_803931D4, 0x880);
        break;
    }
    lbl_80432E90.m8 = fn_8023F1A4(lbl_803931B8, 0x880);
    {
        st = &lbl_80432E90;
        a = fn_8023F1A4(lbl_80393198, 0x880);
        if (&st->m28 != 0) {
            st->m28 = fn_8023FB24(a);
        }
        lbl_80432E90.mC = a;
    }
    lbl_80432E90.m4 = fn_8023F1A4(lbl_80393178, 0x880);
    z = 0;
    lbl_80432E90.m14 = z;
    lbl_80432E90.m18 = z;
    lbl_80432E90.m20 = z;
    lbl_80432E90.m34 = 1.3092105f;
    lbl_80432E90.m38 = 1.0f;
    lbl_80432E90.m30 = 1.0f;
    lbl_80432E90.m24 = z;
    lbl_804CC0FC = fn_8023F1A4(lbl_80393150, 0x880);
    fn_8032DAD8(lbl_804CC0FC);
    fn_8030E4C0(lbl_804CC0EC, 0x20);
    lbl_80432E90.m10 = fn_8030E344(lbl_804CC0EC, 0x80000, 0x20);
    lbl_80432E90.m2C = 0x80000;
    lbl_80432E90.m3C = z;
    fn_80348A48(&lbl_80432E90);
    fn_801D09F0();
    fn_80348D9C();
    lbl_804CC0F4 = fn_8023F1A4(lbl_8039312C, 0x880);
    fn_8030E4C0(lbl_804CC0EC, 0x20);
    lbl_804CC0F8 = fn_8030E344(lbl_804CC0EC, 0x1D128, 0x20);
    fn_80348DAC(lbl_804CC0F4, lbl_804CC0F8, 0x1D128);
}

}
