/* fn_801C77DC: use the current unit's equipped item (the command-state unit), flag 0x2000 in the battle state. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct UB { u8 pad[0xb4]; void* xb4; } UB;
typedef struct Un { u8 pad[0xf0]; UB* xf0; } Un;
typedef struct CS { Un* u; u8 pad[0xe - 4]; s8 xe; } CS;
typedef struct SG { u8 pad[0x15ec]; u32 x15ec; } SG;
extern CS lbl_803CA870;
extern SG lbl_803C8E80;
extern void fn_8012A7B8(void*, int);
extern u8* fn_8010B23C(void*);
struct Ref {
    void* p;
    u8 kind;
    u8 flag;
    Ref() { p = 0; kind = 2; flag = 0; if (p) flag = 1; }
};
extern void fn_8004B03C(void* u, Ref r, void* proc);
int fn_801C77DC(void* proc) {
    Un* u = lbl_803CA870.u;
    fn_8012A7B8(u, lbl_803CA870.xe);
    lbl_803C8E80.x15ec |= 0x2000;
    {
        u8* it = fn_8010B23C(u->xf0->xb4);
        Ref r;
        r.p = it;
        r.flag = it[0x20] == 0;
        fn_8004B03C(u, r, proc);
    }
    return 1;
}
}
