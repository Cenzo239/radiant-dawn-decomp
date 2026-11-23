#include "game/rS_8023FD30/audio.h"
struct FlagSet {
    u32 pad;
    u32 w[1];
};
extern "C" {
extern FlagSet lbl_804CBFE8;
u32 fn_802577F8(u32 n) {
    SndMutex* m = &lbl_8042E798;
    m->lock();
    const u32* p = lbl_804CBFE8.w;
    u32 q = n;
    while (q >= 32) {
        q -= 32;
        p++;
    }
    n = q;
    u32 r = (*p & (1 << n)) != 0;
    m->unlock();
    return r;
}
}
