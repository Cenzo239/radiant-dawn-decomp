/* const int& with a literal gives the right shape and one load, but through lwz from sdata2 instead of li r3,4. A plain local gets folded and emits li twice. About 28 words off. */
#include "game/rN_8025EEF0/room.h"
extern "C" {
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
static inline f32 anim0(int a, int b, int n, const int& t) { return fn_8017F68C(a, b, n, t, t); }
static inline f32 anim(int a, int b, int n) { return anim0(a, b, n, 4); }

void fn_8027B144(void) {
    int n;
    if (roomData()->m36 > 0) {
        roomData()->m36--;
        n = 4 - roomData()->m36;
        roomData()->m32 = anim(roomData()->m38, roomData()->m3C, n);
        roomData()->m34 = anim(roomData()->m3A, roomData()->m3E, n);
    }
}

}
