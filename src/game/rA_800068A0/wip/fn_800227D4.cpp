/* main: 29 of 224 words differ, registers only: a pure rotation of the four saved registers (statics r28, string base r29, language table r30, zero and 0x1000000 r31; this draft gives r30, r31, r28, r29). Declaration order, explicit pointer locals, real pooled string literals, a mainInit inline and sharing the zero/k variable all had no effect. */
#include "game/rA_800068A0/types.h"
/* Program entry. */
extern "C" {
struct C4 { u8 r, g, b, a; };
struct OSThr { u8 x0[0x318]; };
static OSThr sThread0;
static OSThr sThread1;
static OSThr sThread2;
static u8 sStack0[0x1800];
static u8 sStack1[0x4000];
static u8 sStack2[0x2000];
extern u8 lbl_803C7DA0[];
extern char lbl_80361098[];
extern u8 lbl_803C7D40[0x40];
extern char lbl_803C7D80[];
extern const char* lbl_80378918[];
extern void* lbl_804CB0F4;
extern u8 lbl_804CB0F0;
extern u8 lbl_804CB0F8;
extern volatile u32 lbl_804CB5F4;
extern u32 lbl_804CCC90;
struct Lang { u8 x0[0x1BC8]; s8 lang; };
class Vm {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual u32 v48();
};
extern void* fn_8031F69C(void);
extern u32 SCCheckStatus(void);
extern void fn_80318A80(void);
extern void fn_8008BDDC(void);
extern void fn_800CDF54(const char*);
extern u8 fn_803257F0(void);
extern void fn_801D09E8(int);
extern void fn_8033161C(int);
extern void fn_80331670(int);
extern void fn_8007A528(void);
extern void fn_8008A120(void);
extern void fn_8031FC48(OSThr*, void*, int, void*, int, int, int);
extern void fn_803202B0(OSThr*);
extern void fn_800226A8(void);
extern void fn_80022700(void);
extern void fn_80022CCC(void);
extern void fn_800227BC(void);
extern void fn_8008AEA8(void);
extern void DVDSetAutoFatalMessaging(int);
extern void fn_8001E44C(void);
extern void fn_80011E0C(void);
extern void fn_80076C28(void);
extern void fn_8023F0C8(u32);
extern void fn_8017FCE0(void);
extern void fn_800C9EB8(void);
extern Lang* fn_8024BC94(void);
extern void fn_8024CF4C(const char*);
extern void fn_8028B720(void);
extern void fn_800CDB98(void);
extern char* strcpy(char*, const char*);
extern u32 OSGetTick(void);
extern void fn_80089AA8(u32);
extern void fn_80089EC8(u32);
extern void fn_80246100(void);
extern void fn_80080F18(void);
extern void fn_80089A98(void);
extern void fn_80053DAC(void);
extern void fn_803208BC(void*, int, void*, int);
extern void fn_800C9084(void);
extern void fn_800C9EC0(void);
extern void fn_8007DF58(int);
extern void fn_8007E00C(f32, f32, f32, f32);
extern void fn_801D0868(void);
extern void fn_8024CF54(const char*, const char*);
extern void fn_80257340(const char*, int);
extern void fn_8028B84C(void);
extern void fn_800CDF7C(const char*);
extern void fn_800CDF44(void);
extern void fn_8007F7E0(void);
extern void fn_80320548(void*);
extern Vm* fn_8028BACC(void);
extern void fn_8028BBD0(int, int);
extern void fn_80011B58(int);
extern void fn_80083B58(int);
extern void fn_8023550C(void);
extern void fn_8002230C(void);
extern C4 fn_8002177C(void);
extern void fn_80304C74(C4, u32);
extern void fn_80021FE8(int);
extern void fn_8001084C(int);
extern void fn_8000FF74(int);
extern void fn_8007F874(void);
extern void fn_8001093C(int);
extern void fn_800100C8(int);
extern void fn_8007B2F4(void);
extern void fn_802355D4(void);
extern void fn_80011D50(void);
extern void fn_8017FA40(void);
extern void fn_8008A15C(void);
int main(void) {
    lbl_804CB0F4 = fn_8031F69C();
    while (SCCheckStatus() == 1) {
    }
    fn_80318A80();
    fn_8008BDDC();
    fn_800CDF54(lbl_80361098 + 0x11);
    fn_801D09E8(fn_803257F0() == 1);
    fn_8033161C(1);
    fn_80331670(2);
    fn_8007A528();
    fn_8008A120();
    fn_8031FC48(&sThread0, (void*)fn_800226A8, 0, sStack0 + sizeof(sStack0), 0x1800, 3, 1);
    fn_803202B0(&sThread0);
    fn_8008AEA8();
    DVDSetAutoFatalMessaging(0);
    fn_8031FC48(&sThread2, (void*)fn_80022CCC, 0, lbl_803C7DA0 + 0x1000, 0x1000, 0x10, 1);
    fn_803202B0(&sThread2);
    fn_8001E44C();
    fn_80011E0C();
    fn_80076C28();
    fn_8023F0C8(lbl_804CCC90);
    fn_8017FCE0();
    fn_800C9EB8();
    fn_8024CF4C(lbl_80378918[fn_8024BC94()->lang]);
    fn_8028B720();
    fn_800CDB98();
    lbl_803C7D40[0] = 0;
    strcpy(lbl_803C7D80, lbl_80361098 + 0x22);
    fn_80089AA8(OSGetTick());
    fn_80089EC8(OSGetTick());
    fn_80246100();
    fn_80080F18();
    fn_80089A98();
    fn_80053DAC();
    fn_803208BC((void*)fn_800227BC, 0, sStack2 + sizeof(sStack2), 0x2000);
    fn_800C9084();
    fn_800C9EC0();
    fn_8007DF58(0);
    fn_8007E00C(1.0f, 0.99f, 0.01f, 0.0f);
    fn_801D0868();
    lbl_804CB0F8 = 0;
    fn_8024CF54(lbl_80378918[fn_8024BC94()->lang], lbl_80361098 + 0x29);
    fn_80257340(lbl_80361098, 0x10000);
    fn_8031FC48(&sThread1, (void*)fn_80022700, 0, sStack1 + sizeof(sStack1), 0x4000, 0x10, 1);
    fn_803202B0(&sThread1);
    fn_8028B84C();
    fn_800CDF7C(lbl_80361098 + 0x3E);
    fn_800CDF44();
    fn_8007F7E0();
    while (1) {
        while (lbl_804CB0F0 != 0) {
            fn_80320548(fn_8031F69C());
        }
        {
            Vm* v = fn_8028BACC();
            if (v != 0) {
                fn_8028BBD0((v->v48() >> 17) & 1, 1);
            }
        }
        if (lbl_804CB5F4 & 2) {
            lbl_804CB5F4 &= ~2;
            fn_80011B58(0);
        } else {
            int k = 0x1000000;
            fn_80083B58(1);
            fn_8023550C();
            fn_80083B58(5);
            fn_8002230C();
            fn_80304C74(fn_8002177C(), k - 1);
            fn_80021FE8(0);
            fn_8001084C(0);
            fn_8000FF74(0);
            fn_8007F874();
            fn_8001093C(0);
            fn_800100C8(0);
            fn_80083B58(6);
            fn_80083B58(8);
            fn_80083B58(7);
            if (lbl_804CB5F4 & 4) {
                lbl_804CB5F4 &= ~4;
                lbl_804CB5F4 |= 2;
            }
        }
        fn_8007B2F4();
        fn_8007F7E0();
        fn_80083B58(2);
        fn_80083B58(3);
        fn_80083B58(4);
        fn_80021FE8(1);
        if (!(lbl_804CB5F4 & 2)) {
            fn_802355D4();
            fn_80011D50();
        }
        fn_8017FA40();
        fn_8008A15C();
    }
}
}
