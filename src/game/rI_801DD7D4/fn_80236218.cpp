#include "game/rI_801DD7D4/fn_thp.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_804203A8[], lbl_804203C8[];
extern u8 lbl_804209C0[], lbl_804209E0[], lbl_80420A98[];
extern u8 lbl_80420680[], lbl_804206A0[], lbl_804206C0[];
int fn_8032D5A8(void);
void* fn_802BCD60(void*);
void fn_80237428(void);
void DCFlushRange(void*, u32);
void DCInvalidateRange(void*, u32);
void fn_802BCDA4(void*, u32);
void fn_802BCE20(void);
extern int lbl_804CBF50, lbl_804CBF5C, lbl_804CBF64, lbl_804CBF68, lbl_804CBF6C;
extern void* lbl_804CBF60;
extern void (*lbl_804CBF58)(void);
int fn_802F6C90(void*, void*, int, int, int);
#if TARGET_PC
FE10_PROTO void fn_80236A48(p32arg);
#else
void fn_80236A48(int);
#endif
u32 fn_8032D644(void*, u32, int);
int fn_802370F4(void);
int fn_80238184(int);
int fn_8033119C(void);
void fn_80235B18(void);
void fn_80235A00(void);
struct C4 { u8 r,g,b,a; };
void fn_80235FF4x(void*, void*, void*, int, int, int, C4, int, int, int, int);
void fn_80235FF4(void*, void*, void*, s16, s16, s16, C4, s16, s16, s16, s16);
void fn_80021860(int, int, int);
void fn_80021FEC(int);
void fn_80304EE4(void*, int);
void fn_80303CB4(void);
u32 fn_80331194(void);
void fn_803310B0(void*);
void fn_8033111C(int);
void fn_80330F9C(void);
void fn_80330018(void);
extern u32 lbl_804CB5F0;
extern volatile u32 lbl_804CB5F4;
extern u8 lbl_804CAA90;
extern void* lbl_804CBF30, *lbl_804CBF34, *lbl_804CBF38;
}
#define T lbl_80420420
struct RB { void* ptr; int frame; };
struct AB { void* a0; void* a4; u32 a8; };
extern "C" {
#define Q (*(THPPlayer*)sT)
static u8 sT[0x260];
static u8 sQ[0x20];
static u32 sM[8];
static u8 sAud[0x300];
int fn_80236218(int a) {
    int irq;
    memset(sT, 0, 0x1f8);
    fn_8031D224(sQ, sM, 3);
    if (fn_8032D5A8() == 0) return 0;
    irq = OSDisableInterrupts();
    lbl_804CBF5C = 0;
    lbl_804CBF64 = 0;
    lbl_804CBF68 = 0;
    lbl_804CBF6C = a;
    lbl_804CBF60 = fn_802BCD60(fn_80237428);
    if (lbl_804CBF60 == 0 && lbl_804CBF6C != 0) {
        fn_802BCD60(0);
        OSRestoreInterrupts(irq);
        return 0;
    }
    OSRestoreInterrupts(irq);
    if (lbl_804CBF6C == 0) {
        memset(sAud, 0, 0x300);
        DCFlushRange(sAud, 0x300);
        fn_802BCDA4(sAud + lbl_804CBF5C * 0x180, 0x180);
        fn_802BCE20();
    }
    lbl_804CBF50 = 1;
    return 1;
}
}
