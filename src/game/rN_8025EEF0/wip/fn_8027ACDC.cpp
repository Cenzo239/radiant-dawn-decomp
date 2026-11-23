/* fn_8027ACDC 29, fn_8027AF54 26 words: the string base should be r26 all through (a,b,c r29..r31), it takes r31. */
/* Conversation room: top-level draw, value animation */
#include "game/rN_8025EEF0/room.h"
#include "game/rN_8025EEF0/prim2d.h"

extern "C" {

void fn_802758B0(int a, const char* s, void* tex);
void fn_80275FD4(void);
void fn_80277E10(void);
void fn_8027970C(void);
void fn_801BCA5C(f32 v);
const char* fn_800CF53C(void);
const char* fn_800CEB4C(void);
const char* fn_800CEC24(void);
void fn_801C6D9C(const char* s, int a, int b, int c);
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);

void fn_8027ACDC(void) {
        /*P*/
    const char* b;
    const char* a;
    const char* y;
    const char* x;
    const char* c;
    const char* x2;
    const char* y2;
    const char* s;
/*E*/
    if (*(s16*)lbl_804CC06C & 1) {
        return;
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E7DC((u8)*(s16*)(lbl_804CC06C + 0x1E8));
    fn_8007E164();
    if (isProc(lbl_8037359C)) {
        fn_802758B0(1, lbl_8037359C + 0x4E, *(void**)(lbl_804CC06C + 0x1EC));
    }
    if (isProc(lbl_8037359C + 0x13)) {
        fn_802758B0(2, lbl_8037359C + 0x5E, *(void**)(lbl_804CC074 + 0xF0));
    }
    switch (roomData()->m0) {
    case 0:
        fn_80275FD4();
        break;
    case 1:
        fn_80277E10();
        break;
    }
    fn_801BCA5C(-1.0f);
    a = fn_800CF53C();
    fn_800CF53C();
    b = fn_800CEB4C();
    c = fn_800CEC24();
    if (isProc(lbl_8037359C)) {
        s = lbl_8037359C;
        x = fn_800D0864(s + 0x97);
        y = fn_800D0864(s + 0x8C);
        fn_80290DDC((char*)lbl_804CC06C + 0x168, s + 0x72, a, fn_800D0864(s + 0x81), c, y, b, x);
    }
    if (isProc(lbl_8037359C + 0x13)) {
        x2 = fn_800D0864(lbl_8037359C + 0x97);
        y2 = fn_800D0864(lbl_8037359C + 0x8C);
        fn_80290DDC((char*)lbl_804CC074 + 0x6C, lbl_8037359C + 0x72, a, fn_800D0864(lbl_8037359C + 0x81), c, y2, b, x2);
    }
    fn_801C6D9C((char*)lbl_804CC06C + 0x168, 0xFF, 0xFF, 0);
    fn_801BCA5C(1.0f);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

void fn_8027AF54(void) {
        /*P*/
    const char* b;
    const char* a;
    const char* y;
    const char* x;
    const char* c;
    const char* x2;
    const char* y2;
    const char* s;
/*E*/
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E7DC((u8)*(s16*)(lbl_804CC074 + 0xEC));
    fn_8007E164();
    if (isProc(lbl_8037359C)) {
        fn_802758B0(1, lbl_8037359C + 0x4E, *(void**)(lbl_804CC06C + 0x1EC));
    }
    if (isProc(lbl_8037359C + 0x13)) {
        fn_802758B0(2, lbl_8037359C + 0x5E, *(void**)(lbl_804CC074 + 0xF0));
    }
    fn_8027970C();
    fn_801BCA5C(-1.0f);
    a = fn_800CF53C();
    fn_800CF53C();
    b = fn_800CEB4C();
    c = fn_800CEC24();
    if (isProc(lbl_8037359C)) {
        s = lbl_8037359C;
        x = fn_800D0864(s + 0x97);
        y = fn_800D0864(s + 0x8C);
        fn_80290DDC((char*)lbl_804CC06C + 0x168, s + 0x72, a, fn_800D0864(s + 0x81), c, y, b, x);
    }
    if (isProc(lbl_8037359C + 0x13)) {
        x2 = fn_800D0864(lbl_8037359C + 0x97);
        y2 = fn_800D0864(lbl_8037359C + 0x8C);
        fn_80290DDC((char*)lbl_804CC074 + 0x6C, lbl_8037359C + 0x72, a, fn_800D0864(lbl_8037359C + 0x81), c, y2, b, x2);
    }
    fn_801C6D9C((char*)lbl_804CC074 + 0x6C, 0xFF, 0xFF, 0);
    fn_801BCA5C(1.0f);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

}
