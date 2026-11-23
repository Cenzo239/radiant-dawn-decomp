/* fn_8027ACDC (0x278) and fn_8027AF54 (0x1F0): exact (round m12). From wip/fn_8027ACDC.cpp.
   Lever: the three name lookups of each sprintf are nested call arguments (no x/y/s locals), which puts the
   string base in r26 and the lookup results in r27/r28; a, b, c are declared c, b, a (r29, r30, r31). */
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
    const char* c;
    const char* b;
    const char* a;
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
        fn_80290DDC((char*)lbl_804CC06C + 0x168, lbl_8037359C + 0x72, a, fn_800D0864(lbl_8037359C + 0x81), c, fn_800D0864(lbl_8037359C + 0x8C), b,
                    fn_800D0864(lbl_8037359C + 0x97));
    }
    if (isProc(lbl_8037359C + 0x13)) {
        fn_80290DDC((char*)lbl_804CC074 + 0x6C, lbl_8037359C + 0x72, a, fn_800D0864(lbl_8037359C + 0x81), c, fn_800D0864(lbl_8037359C + 0x8C), b,
                    fn_800D0864(lbl_8037359C + 0x97));
    }
    fn_801C6D9C((char*)lbl_804CC06C + 0x168, 0xFF, 0xFF, 0);
    fn_801BCA5C(1.0f);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

void fn_8027AF54(void) {
    const char* c;
    const char* b;
    const char* a;
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
        fn_80290DDC((char*)lbl_804CC06C + 0x168, lbl_8037359C + 0x72, a, fn_800D0864(lbl_8037359C + 0x81), c, fn_800D0864(lbl_8037359C + 0x8C), b,
                    fn_800D0864(lbl_8037359C + 0x97));
    }
    if (isProc(lbl_8037359C + 0x13)) {
        fn_80290DDC((char*)lbl_804CC074 + 0x6C, lbl_8037359C + 0x72, a, fn_800D0864(lbl_8037359C + 0x81), c, fn_800D0864(lbl_8037359C + 0x8C), b,
                    fn_800D0864(lbl_8037359C + 0x97));
    }
    fn_801C6D9C((char*)lbl_804CC074 + 0x6C, 0xFF, 0xFF, 0);
    fn_801BCA5C(1.0f);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

}
