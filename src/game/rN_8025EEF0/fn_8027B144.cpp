/* r20. fn_8027B144: room cursor tween. The easing function takes its mode first:
   fn_8017F68C(int mode, f32 from, f32 to, f32 t, f32 dur); `k = 4` is both the mode and the duration, which gives the
   original `li r3,4; xoris r0,r3,0x8000` (the old (f32,f32,f32,f32,int) prototype never did). */
#include "game/rN_8025EEF0/room.h"
extern "C" {
f32 fn_8017F68C(int mode, f32 a, f32 b, f32 c, f32 d);

void fn_8027B144(void) {
    int n;
    int k;
    if (roomData()->m36 > 0) {
        roomData()->m36--;
        n = 4 - roomData()->m36;
        k = 4;
        roomData()->m32 = fn_8017F68C(k, roomData()->m38, roomData()->m3C, n, k);
        roomData()->m34 = fn_8017F68C(k, roomData()->m3A, roomData()->m3E, n, k);
    }
}

}
