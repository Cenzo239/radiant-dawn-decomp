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
#pragma push
#pragma use_lmw_stmw on
static u8 sFree[0x20];
static u8 sRead[0x20];
static u8 sRead2[0x20];
static u32 mFree[10];
static u32 mRead[10];
static u32 mRead2[10];
static u8 sThread[0x318];
static inline int* popFree(void) { int* m; fn_8031D34C(sFree, &m, 1); return m; }
void fn_80237B78(void) {
    int off; int n; int i; i = 0;
    off = T.b8;
    n = T.bc;
    for (;;) {
        int* msg = popFree();
        int r;
        r = fn_802F6C90(&T, (void*)msg[0], n, off, 2);
        if (r != n) {
            if (r == -1) T.a8 = -1;
            if (i == 0) fn_80236A48(0);
            fn_80320548(sThread);
        }
        msg[1] = i;
        fn_8031D284(sRead, msg, 1);
        off += n;
        n = *(int*)msg[0];
        u32 k = (i + T.c0) % T.a50;
        if (k == T.a50 - 1) {
            if (T.a6 & 1) off = T.a64;
            else fn_80320548(sThread);
        }
        i++;
    }
}
#pragma pop
}
