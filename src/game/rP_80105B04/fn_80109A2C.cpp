#include "game/rP_80105B04/rp.h"
/* Big-endian stream readers: the argument points at the read cursor. */
static inline u32 Rd32(u8*& s) {
    u8* p = s;
    u32 v = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
    s = p + 4;
    return v;
}
extern "C" {
u16 fn_80109A2C(u8** s) {
    u8* p = *s;
    u16 v = (p[0] << 8) + p[1];
    *s = p + 2;
    return v;
}
u32 fn_80109A50(u8** s) {
    return Rd32(*s);
}
u32 fn_80109A88(u8** s) {
    if (*s == 0) return 0;
    return Rd32(*s);
}
f32 fn_80109AD0(u8** s) {
    u32 v = Rd32(*s);
    return *(f32*)&v;
}
}
