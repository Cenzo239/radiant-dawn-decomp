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
void fn_802355D4(void) {
    void* n;
    fn_80021860(1, 3, 1);
    fn_80021FEC(1);
    fn_80304EE4(lbl_804CBF38, 1);
    fn_80303CB4();
    if (lbl_804CB5F0 != fn_80331194() && !(lbl_804CB5F4 & 8)) {
        lbl_804CB5F4 |= 4;
    }
    fn_803310B0(lbl_804CBF38);
    if (lbl_804CAA90 != 0) {
        fn_8033111C(0);
        lbl_804CAA90 = 0;
    }
    fn_80330F9C();
    if (lbl_804CB5F4 & 1) {
        if (!(lbl_804CB5F4 & 4)) {
            fn_80330018();
        }
        lbl_804CB5F4 &= ~4;
    }
    fn_80330018();
    n = lbl_804CBF30;
    if (lbl_804CBF38 == lbl_804CBF30) {
        n = lbl_804CBF34;
    }
    lbl_804CBF38 = n;
}
static inline AB* popAB(void) { AB* m; fn_8031D34C(lbl_804203A8, &m, 1); return m; }
void fn_802358B8(RB* rb) {
    AB* m; u32 i;
    u32* sizes = (u32*)((u8*)rb->ptr + 8);
    u8* ptr = (u8*)rb->ptr + T.a6c * 4 + 8;
    m = popAB();
    for (i = 0; i < T.a6c; i++) {
        switch (T.a70[i]) {
        case 1: {
            AB* msg = m;
            msg->a8 = fn_8032D644(msg->a0, (u32)ptr + *sizes * T.ec, 0);
            msg->a4 = msg->a0;
            fn_8031D284(lbl_804203C8, msg, 1);
            return; }
        }
        ptr += *sizes;
        sizes++;
    }
}
#pragma push
#pragma use_lmw_stmw on
int fn_8023721C(
#if TARGET_PC
void* a, int x, int y, int w, fe10_rgba colv, int u, int v
#else
void* a, int x, int y, int w, const C4* col, int u, int v
#endif
) {
#if TARGET_PC
    const C4* col = (const C4*)&colv;
#endif
    if (T.a0 != 0 && T.a4 != 0 && T.fc != 0) {
        fn_80235B18();
        fn_80235FF4((void*)T.fc[0], (void*)T.fc[1], (void*)T.fc[2], x, y, w, *col, T.a80, T.a84, u, v);
        fn_80235A00();
        return (u32)(T.fc[3] + T.c0) % T.a50;
    }
    return -1;
}
#pragma pop
}
