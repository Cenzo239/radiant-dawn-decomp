#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void *, void *);
#else
s32 fn_8011B77C();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA52C;
FE10_PROTO extern void *lbl_804CA530;
FE10_PROTO extern void *lbl_804CA534;
FE10_PROTO extern void *lbl_804CA538;
FE10_PROTO extern void *lbl_804CA540;
FE10_PROTO extern void *lbl_804CA544;
FE10_PROTO extern void *lbl_804CA548;
FE10_PROTO extern void *lbl_804CA54C;
FE10_PROTO extern void *lbl_804CA550;
#else
extern s32 lbl_804CA52C;
extern s32 lbl_804CA530;
extern s32 lbl_804CA534;
extern s32 lbl_804CA538;
extern s32 lbl_804CA540;
extern s32 lbl_804CA544;
extern s32 lbl_804CA548;
extern s32 lbl_804CA54C;
extern s32 lbl_804CA550;
#endif

void fn_8012C448(s8 *arg0) {
    if (((s16) M2C_FIELD(arg0, s16 *, 0x2D4) == 0) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA52C) != 0)) {
        M2C_FIELD(arg0, s16 *, 0x2D4) = 1;
    }
    if (((s16) M2C_FIELD(arg0, s16 *, 0x2D6) == 0) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA530) != 0)) {
        M2C_FIELD(arg0, s16 *, 0x2D6) = 1;
    }
    if (((s16) M2C_FIELD(arg0, s16 *, 0x2D8) == 0) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA534) != 0)) {
        M2C_FIELD(arg0, s16 *, 0x2D8) = 1;
    }
    if (((s16) M2C_FIELD(arg0, s16 *, 0x2DA) == 0) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA538) != 0)) {
        M2C_FIELD(arg0, s16 *, 0x2DA) = 1;
    }
    if (((s16) M2C_FIELD(arg0, s16 *, 0x2E6) == 0) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA548) != 0)) {
        M2C_FIELD(arg0, s16 *, 0x2E6) = 1;
    }
    if (((s16) M2C_FIELD(arg0, s16 *, 0x2E8) == 0) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA54C) != 0)) {
        M2C_FIELD(arg0, s16 *, 0x2E8) = 1;
    }
    if (((s16) M2C_FIELD(arg0, s16 *, 0x2DE) == 0) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA544) != 0)) {
        M2C_FIELD(arg0, s16 *, 0x2DE) = 1;
    }
    if (((s16) M2C_FIELD(arg0, s16 *, 0x2DC) == 0) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA540) != 0)) {
        M2C_FIELD(arg0, s16 *, 0x2DC) = 1;
    }
    if (((s16) M2C_FIELD(arg0, s16 *, 0x2EA) == 0) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA550) != 0)) {
        M2C_FIELD(arg0, s16 *, 0x2EA) = 1;
    }
}
