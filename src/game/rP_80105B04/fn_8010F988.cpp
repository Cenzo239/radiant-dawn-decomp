#include "game/rP_80105B04/rp.h"
/* String tables: item id to staff/use sound class, and item trait name to flag bit. */
extern "C" {
extern char lbl_803680E8[];
int fn_80291188(const char* a, const char* b);
struct ItemF { u8 pad[0x38]; u64 fl; };
int fn_8010F988(const char* s) {
    char* t = lbl_803680E8;
    if (fn_80291188(s, t + 0xae) == 0) return 0x81;
    if (fn_80291188(s, t + 0xb7) == 0) return 0x81;
    if (fn_80291188(s, t + 0xc2) == 0) return 0x81;
    if (fn_80291188(s, t + 0xce) == 0) return 0x81;
    if (fn_80291188(s, t + 0xd9) == 0) return 0x81;
    if (fn_80291188(s, t + 0xe5) == 0) return 0x83;
    if (fn_80291188(s, t + 0xee) == 0) return 0x84;
    if (fn_80291188(s, t + 0xfa) == 0) return 0x84;
    if (fn_80291188(s, t + 0x104) == 0) return 0x85;
    if (fn_80291188(s, t + 0x10f) == 0) return 0x85;
    if (fn_80291188(s, t + 0x11a) == 0) return 0x87;
    if (fn_80291188(s, t + 0x124) == 0) return 0x86;
    if (fn_80291188(s, t + 0x131) == 0) return 0x85;
    if (fn_80291188(s, t + 0x13c) == 0) return 0x87;
    if (fn_80291188(s, t + 0x148) == 0) return 0x81;
    if (fn_80291188(s, t + 0x157) == 0) return 0x87;
    if (fn_80291188(s, t + 0x165) == 0) return 0x87;
    if (fn_80291188(s, t + 0x174) == 0) return 0x87;
    if (fn_80291188(s, t + 0x185) == 0) return 0x87;
    if (fn_80291188(s, t + 0x194) == 0) return 0x87;
    if (fn_80291188(s, t + 0x1a2) == 0) return 0x87;
    if (fn_80291188(s, t + 0x1b2) == 0) return 0x87;
    if (fn_80291188(s, t + 0x1c3) == 0) return 0x87;
    if (fn_80291188(s, t + 0x1d0) == 0) return 0x87;
    if (fn_80291188(s, t + 0x1da) == 0) return 0x87;
    if (fn_80291188(s, t + 0x1ea) == 0) return 0x88;
    if (fn_80291188(s, t + 0x1fa) == 0) return 0x88;
    if (fn_80291188(s, t + 0x20a) == 0) return 0x87;
    if (fn_80291188(s, t + 0x0) == 0) return 0x85;
    if (fn_80291188(s, t + 0x10) == 0) return 0x85;
    if (fn_80291188(s, t + 0x1c) == 0) return 0x85;
    if (fn_80291188(s, t + 0x219) == 0) return 0x81;
    if (fn_80291188(s, t + 0x222) == 0) return 0x81;
    if (fn_80291188(s, t + 0x230) == 0) return 0x81;
    if (fn_80291188(s, t + 0x23f) == 0) return 0x81;
    if (fn_80291188(s, t + 0x24a) == 0) return 0x87;
    if (fn_80291188(s, t + 0x258) == 0) return 0x83;
    if (fn_80291188(s, t + 0x266) == 0) return 0x83;
    if (fn_80291188(s, t + 0x270) == 0) return 0x87;
    if (fn_80291188(s, t + 0x27e) == 0) return 0x87;
    return fn_80291188(s, t + 0x28d) ? 0x13 : 0x85;
}
void fn_8010FFFC(ItemF* d, const char* s) {
    char* t;
    if (s == 0) return;
    t = lbl_803680E8;
    if (fn_80291188(s, t + 0x38f) == 0) { d->fl |= 0x1000000000000ULL; return; }
    if (fn_80291188(s, t + 0x398) == 0) { d->fl |= 0x2000000000000ULL; return; }
    if (fn_80291188(s, t + 0x3a1) == 0) { d->fl |= 0x4000000000000ULL; return; }
    if (fn_80291188(s, t + 0x3a9) == 0) { d->fl |= 0x8000000000000ULL; return; }
    if (fn_80291188(s, t + 0x3ae) == 0) { d->fl |= 0x10000000000000ULL; return; }
    if (fn_80291188(s, t + 0x3ba) == 0) { d->fl |= 0x20000000000000ULL; return; }
    if (fn_80291188(s, t + 0x3c4) == 0) { d->fl |= 0x100ULL; return; }
    if (fn_80291188(s, t + 0x3ca) == 0) { d->fl |= 0x400ULL; return; }
    if (fn_80291188(s, t + 0x3d1) == 0) { d->fl |= 0x1000ULL; return; }
    if (fn_80291188(s, t + 0x59) == 0) { d->fl |= 0x3000000000004ULL; return; }
    if (fn_80291188(s, t + 0xa9) == 0) return;
    if (fn_80291188(s, t + 0x3d9) == 0) { d->fl |= 0x8ULL; return; }
    if (fn_80291188(s, t + 0x3e1) == 0) { d->fl |= 0x200ULL; return; }
    if (fn_80291188(s, t + 0x3e7) == 0) { d->fl |= 0x2000ULL; return; }
    if (fn_80291188(s, t + 0x3ee) == 0) { d->fl |= 0x100000000000ULL; return; }
    if (fn_80291188(s, t + 0x3f5) == 0) { d->fl |= 0x4000ULL; return; }
    if (fn_80291188(s, t + 0x3f8) == 0) { d->fl |= 0x20000004000ULL; return; }
    if (fn_80291188(s, t + 0x3fe) == 0) { d->fl |= 0x8000ULL; return; }
    if (fn_80291188(s, t + 0x404) == 0) { d->fl |= 0x10000ULL; return; }
    if (fn_80291188(s, t + 0x40d) == 0) { d->fl |= 0x20000ULL; return; }
    if (fn_80291188(s, t + 0x418) == 0) { d->fl |= 0x40000ULL; return; }
    if (fn_80291188(s, t + 0x423) == 0) { d->fl |= 0x80000ULL; return; }
    if (fn_80291188(s, t + 0x42e) == 0) { d->fl |= 0x800000ULL; return; }
    if (fn_80291188(s, t + 0x437) == 0) { d->fl |= 0x1000000ULL; return; }
    if (fn_80291188(s, t + 0x441) == 0) { d->fl |= 0x2000000ULL; return; }
    if (fn_80291188(s, t + 0x44b) == 0) { d->fl |= 0x100000ULL; return; }
    if (fn_80291188(s, t + 0x453) == 0) { d->fl |= 0x80000000000ULL; return; }
    if (fn_80291188(s, t + 0x45a) == 0) { d->fl |= 0x4000000ULL; return; }
    if (fn_80291188(s, t + 0x464) == 0) { d->fl |= 0x8000000ULL; return; }
    if (fn_80291188(s, t + 0x468) == 0) { d->fl |= 0x10000000ULL; return; }
    if (fn_80291188(s, t + 0x46c) == 0) { d->fl |= 0x20000000ULL; return; }
    if (fn_80291188(s, t + 0x470) == 0) { d->fl |= 0x40000000ULL; return; }
    if (fn_80291188(s, t + 0x474) == 0) { d->fl |= 0x80000000ULL; return; }
    if (fn_80291188(s, t + 0x478) == 0) { d->fl |= 0x100000000ULL; return; }
    if (fn_80291188(s, t + 0x47c) == 0) { d->fl |= 0x200000000ULL; return; }
    if (fn_80291188(s, t + 0x480) == 0) { d->fl |= 0x400000000ULL; return; }
    if (fn_80291188(s, t + 0x484) == 0) { d->fl |= 0x800000000ULL; return; }
    if (fn_80291188(s, t + 0x488) == 0) { d->fl |= 0x1000000000ULL; return; }
    if (fn_80291188(s, t + 0x48f) == 0) { d->fl |= 0x40000000000ULL; return; }
    if (fn_80291188(s, t + 0x495) == 0) { d->fl |= 0x200000000000ULL; return; }
    if (fn_80291188(s, t + 0x49b) == 0) { d->fl |= 0x400000000000ULL; return; }
    if (fn_80291188(s, t + 0x4a3) == 0) { d->fl |= 0x800000000000ULL; return; }
    if (fn_80291188(s, t + 0x4ab) == 0) { d->fl |= 0x200000ULL; return; }
    if (fn_80291188(s, t + 0x4b5) == 0) { d->fl |= 0x400000ULL; return; }
    if (fn_80291188(s, t + 0x4bf) == 0) { d->fl |= 0x40000000000000ULL; return; }
    if (fn_80291188(s, t + 0x4c7) == 0) { d->fl |= 0x80000000000000ULL; return; }
    if (fn_80291188(s, t + 0x4d3) == 0) { d->fl |= 0x100000000000000ULL; return; }
    if (fn_80291188(s, t + 0x4dd) == 0) { d->fl |= 0x200000000000000ULL; return; }
    if (fn_80291188(s, t + 0x4ec) == 0) { d->fl |= 0x400000000000000ULL; return; }
}
}
