/* fn_80186768: class change event teardown; the three unit destructors are inlined. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct Ev { u8 pad[0x58]; u8* x58; } Ev;
extern u8 lbl_803C8E80[];
extern void fn_800A99C4(Ev*);
extern void fn_80026898(void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_8002E3D4(void*);
#else
extern void* fn_8002E3D4(void*);
#endif
extern void fn_80111C24(void*, int);
extern void fn_8028C0D0(void*, void*, u32, u32);
extern void fn_80079210(void*);
extern void fn_800E4548(void);
static inline void Dtor(u8* u) {
    if (u) {
        fn_8002E3D4(u);
        fn_80111C24(u + 0x41c, -1);
        fn_80111C24(u + 0x3f4, -1);
        if (u) if (u) if (u) if (u) if (u) if (u) if (u) {
            fn_8028C0D0(u + 0x1bc, (void*)fn_80111C24, 0x28, 7);
        }
    }
}
void fn_80186768(Ev* p) {
    u8* m;
    fn_800A99C4(p);
    fn_80026898(lbl_803C8E80, p->x58);
    m = p->x58;
    if (m) {
        if (m) {
            Dtor(m + 0x940);
            Dtor(m + 0x4a0);
            Dtor(m);
            fn_80079210(m);
        }
        p->x58 = 0;
    }
    fn_800E4548();
}
}
