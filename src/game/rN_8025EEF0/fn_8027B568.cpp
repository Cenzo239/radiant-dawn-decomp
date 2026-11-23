/* Conversation room: top-level draw, value animation */
#include "game/rN_8025EEF0/room.h"
#include "game/rN_8025EEF0/prim2d.h"

extern "C" {

#if TARGET_PC
FE10_PROTO void fn_802758B0(int a, const char* s, ptr32<const void>);
#else
void fn_802758B0(int a, const char* s, void* tex);
#endif
void fn_80275FD4(void);
void fn_80277E10(void);
void fn_8027970C(void);
void fn_801BCA5C(f32 v);
const char* fn_800CF53C(void);
const char* fn_800CEB4C(void);
const char* fn_800CEC24(void);
void fn_801C6D9C(const char* s, int a, int b, int c);
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);

void fn_8027B568(void) {
    if (roomData()->m20 > 0) {
        roomData()->m20--;
        if (isProc(lbl_8037359C)) {
            f32 v = fn_8017F68C(roomData()->m1C, roomData()->m1E, roomData()->m22 - roomData()->m20, roomData()->m22, 0);
            setCurF(v);
        }
        if (isProc(lbl_8037359C + 0x13)) {
            roomData()->m14 = roomData()->m18 = fn_8017F68C(roomData()->m1C, roomData()->m1E, roomData()->m22 - roomData()->m20, roomData()->m22, 0);
        }
    }
}

}
