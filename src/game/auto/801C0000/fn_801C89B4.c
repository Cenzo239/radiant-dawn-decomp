#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800E6F7C(void *, void (*)(void *));
FE10_PROTO void fn_800E700C(void *, void (*)(void *));
FE10_PROTO void fn_800E709C(void *, void (*)(void *));
FE10_PROTO void fn_800E712C(void *, void (*)(void *));
FE10_PROTO void fn_800E73B0(void *, void (*)(void *));
FE10_PROTO void fn_800E73F8(void *, void (*)(void *));
FE10_PROTO void fn_800E7670(void *, void (*)(void *));
FE10_PROTO void fn_800E76B8(void *, void (*)(void *));
FE10_PROTO void fn_800E7700(void *, void (*)(void *));
FE10_PROTO void fn_800E7748(void *, void (*)(void *));
FE10_PROTO void fn_800E7898(void *, void (*)(void *));
FE10_PROTO void fn_800E78E0(void *, void (*)(void *));
FE10_PROTO void fn_800E7928(void *, void (*)(void *));
FE10_PROTO void fn_800E7970(void *, void (*)(void *));
FE10_PROTO void fn_800E79B8(void *, void (*)(void *));
FE10_PROTO void fn_800E7A00(void *, void (*)(void *));
FE10_PROTO void fn_800E7A48(void *, void (*)(void *));
FE10_PROTO void fn_800E7A90(void *, void (*)(void *));
FE10_PROTO void * fn_8010B228(char *);
#else
M2C_UNK fn_800E6F7C();
M2C_UNK fn_800E700C();
M2C_UNK fn_800E709C();
M2C_UNK fn_800E712C();
M2C_UNK fn_800E73B0();
M2C_UNK fn_800E73F8();
M2C_UNK fn_800E7670();
M2C_UNK fn_800E76B8();
M2C_UNK fn_800E7700();
M2C_UNK fn_800E7748();
M2C_UNK fn_800E7898();
M2C_UNK fn_800E78E0();
M2C_UNK fn_800E7928();
M2C_UNK fn_800E7970();
M2C_UNK fn_800E79B8();
M2C_UNK fn_800E7A00();
M2C_UNK fn_800E7A48();
M2C_UNK fn_800E7A90();
u32 fn_8010B228();
#endif
extern u8 lbl_8036E6D8[0x258];

void fn_801C89B4(
#if TARGET_PC
void *arg0, void *arg1, s32 arg2
#else
u32 arg0, s32 arg1, s32 arg2
#endif
) {
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x66)) {
        fn_800E709C(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x98)) {
        fn_800E6F7C(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0xA6)) {
        fn_800E700C(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x83)) {
        fn_800E712C(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0xB4)) {
        fn_800E73B0(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8)) {
        fn_800E7670(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 9)) {
        fn_800E76B8(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x14)) {
        fn_800E7700(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x20)) {
        fn_800E7748(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x2B)) {
        fn_800E7898(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0xC2)) {
        fn_800E78E0(arg1, arg2);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0xCB)) {
        fn_800E7928(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0xD7)) {
        fn_800E7970(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0xE5)) {
        fn_800E79B8(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0xEF)) {
        fn_800E7A00(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0xFB)) {
        fn_800E7A48(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x108)) {
        fn_800E7A90(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x114)) {
        fn_800E73F8(arg1, 0);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x37)) {
        fn_800E7898(arg1, arg2);
        return;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x51)) {
        fn_800E7748(arg1, 0);
    }
}
