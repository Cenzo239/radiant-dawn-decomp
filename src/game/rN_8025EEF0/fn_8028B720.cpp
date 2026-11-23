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
void fn_80348D9C(int wide);
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

}
