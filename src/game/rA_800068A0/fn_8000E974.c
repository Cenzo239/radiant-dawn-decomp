#include "game/rA_800068A0/types.h"

/* Hand-written Gekko paired-single routines (no compiler frame or register
 * conventions): GQR setup and matrix-palette skinning. */

#if TARGET_PC
/* Host: OSInitFastCast (GQR2-5 = u8/u16/s8/s16), see fe10/gekko.h */
void fn_8000E974(void) {
    fe10_fastcast_init();
}
#else
asm void fn_8000E974(void) {
    nofralloc
    li r3, 0x4
    oris r3, r3, 0x4
    mtspr 914, r3
    li r3, 0x5
    oris r3, r3, 0x5
    mtspr 915, r3
    li r3, 0x6
    oris r3, r3, 0x6
    mtspr 916, r3
    li r3, 0x7
    oris r3, r3, 0x7
    mtspr 917, r3
    blr
}
#endif

#if TARGET_PC
/* Host: GQR5 = (r4 << 8 | r3) for loads and stores (type r3, scale r4) */
void fn_8000E9C4(u32 type, u32 scale) {
    u32 v = (scale << 8) | type;
    fe10_gqr[5] = (v << 16) | v;
}
#else
asm void fn_8000E9C4(void) {
    nofralloc
    slwi r0, r4, 8
    or r3, r0, r3
    slwi r0, r3, 16
    or r0, r3, r0
    mtspr 917, r0
    blr
}
#endif

#if TARGET_PC
/* Host: no C version of the paired-single skinning routine fn_8001D024 yet (register
   arguments, no C prototype); left undefined, the port's generated stub aborts if called. */
#else
asm void fn_8001D024(void) {
    nofralloc
    stwu r1, -0x40(r1)
    stfd f14, 0x8(r1)
    and. r5, r5, r5
    stfd f15, 0x10(r1)
    beq L_8001D118
    subi r3, r3, 0x4
    stfd f16, 0x18(r1)
    subi r7, r5, 0x1
    psq_lu f12, 0x4(r3), 0, 6
    subi r4, r4, 0x2
    stfd f17, 0x20(r1)
    mtctr r7
    psq_lu f13, 0x4(r3), 0, 6
    stfd f18, 0x28(r1)
    ps_madds0 f15, f0, f12, f6
    ps_madds0 f16, f1, f12, f7
    ps_muls1 f17, f0, f13
    psq_lu f14, 0x4(r3), 0, 6
    ps_muls1 f18, f1, f13
    and. r7, r7, r7
    beq L_8001D120
    ps_madds1 f15, f2, f12, f15
    ps_madds1 f16, f3, f12, f16
    ps_madds0 f17, f2, f14, f17
    psq_lu f12, 0x4(r3), 0, 6
    ps_madds0 f18, f3, f14, f18
    ps_madds0 f8, f4, f13, f15
    ps_madds0 f9, f5, f13, f16
    psq_lu f13, 0x4(r3), 0, 6
    ps_madds1 f10, f4, f14, f17
    ps_madds1 f11, f5, f14, f18
    psq_lu f14, 0x4(r3), 0, 6
L_8001D0A4:
    ps_madds0 f15, f0, f12, f6
    psq_stu f8, 0x2(r4), 0, 6
    ps_madds0 f16, f1, f12, f7
    psq_stu f9, 0x8(r4), 1, 6
    ps_muls1 f17, f0, f13
    psq_stu f10, 0x4(r4), 0, 7
    ps_muls1 f18, f1, f13
    psq_stu f11, 0x2(r4), 1, 7
    ps_madds1 f15, f2, f12, f15
    ps_madds1 f16, f3, f12, f16
    psq_lu f12, 0x4(r3), 0, 6
    ps_madds0 f17, f2, f14, f17
    ps_madds0 f18, f3, f14, f18
    ps_madds0 f8, f4, f13, f15
    ps_madds0 f9, f5, f13, f16
    psq_lu f13, 0x4(r3), 0, 6
    ps_madds1 f10, f4, f14, f17
    ps_madds1 f11, f5, f14, f18
    psq_lu f14, 0x4(r3), 0, 6
    bdnz L_8001D0A4
L_8001D0F4:
    lfd f14, 0x8(r1)
    psq_stu f8, 0x2(r4), 0, 6
    lfd f15, 0x10(r1)
    psq_stu f9, 0x8(r4), 1, 6
    lfd f16, 0x18(r1)
    psq_stu f10, 0x4(r4), 0, 7
    lfd f17, 0x20(r1)
    psq_stu f11, 0x2(r4), 1, 7
    lfd f18, 0x28(r1)
L_8001D118:
    addi r1, r1, 0x40
    blr
L_8001D120:
    ps_madds1 f15, f2, f12, f15
    ps_madds1 f16, f3, f12, f16
    ps_madds0 f17, f2, f14, f17
    ps_madds0 f18, f3, f14, f18
    ps_madds0 f8, f4, f13, f15
    ps_madds0 f9, f5, f13, f16
    ps_madds1 f10, f4, f14, f17
    ps_madds1 f11, f5, f14, f18
    b L_8001D0F4
}
#endif

#if TARGET_PC
/* Host: no C version of the paired-single skinning routine fn_8001D144 yet (register
   arguments, no C prototype); left undefined, the port's generated stub aborts if called. */
#else
asm void fn_8001D144(void) {
    nofralloc
    stwu r1, -0x40(r1)
    stfd f14, 0x8(r1)
    and. r5, r5, r5
    stfd f15, 0x10(r1)
    beq L_8001D2D0
    subi r3, r3, 0x4
    stfd f16, 0x18(r1)
    subi r7, r5, 0x1
    psq_lu f12, 0x4(r3), 0, 6
    subi r4, r4, 0xc
    stfd f17, 0x20(r1)
    mtctr r7
    psq_lu f13, 0x4(r3), 0, 6
    stfd f18, 0x28(r1)
    ps_madds0 f15, f0, f12, f6
    ps_madds0 f16, f1, f12, f7
    ps_muls1 f17, f0, f13
    psq_lu f14, 0x4(r3), 0, 6
    ps_muls1 f18, f1, f13
    ps_madds1 f15, f2, f12, f15
    ps_madds1 f16, f3, f12, f16
    ps_madds0 f17, f2, f14, f17
    psq_lu f12, 0x4(r3), 0, 6
    ps_madds0 f18, f3, f14, f18
    ps_madds0 f8, f4, f13, f15
    ps_madds0 f9, f5, f13, f16
    psq_lu f13, 0x4(r3), 0, 6
    ps_madds1 f10, f4, f14, f17
    ps_madds1 f11, f5, f14, f18
    psq_lu f14, 0x4(r3), 0, 6
    ps_muls0 f15, f0, f12
    psq_stu f8, 0xc(r4), 0, 6
    ps_muls0 f16, f1, f12
    psq_stu f9, 0x8(r4), 1, 6
    ps_muls1 f17, f0, f13
    psq_stu f10, 0x4(r4), 0, 7
    ps_muls1 f18, f1, f13
    psq_stu f11, 0x2(r4), 1, 7
    and. r7, r7, r7
    beq L_8001D2D8
    ps_madds1 f15, f2, f12, f15
    ps_madds1 f16, f3, f12, f16
    psq_lu f12, 0x4(r3), 0, 6
    ps_madds0 f17, f2, f14, f17
    ps_madds0 f18, f3, f14, f18
    ps_madds0 f8, f4, f13, f15
    ps_madds0 f9, f5, f13, f16
    psq_lu f13, 0x4(r3), 0, 6
    ps_madds1 f10, f4, f14, f17
    ps_madds1 f11, f5, f14, f18
    psq_lu f14, 0x4(r3), 0, 6
L_8001D210:
    ps_madds0 f15, f0, f12, f6
    psq_stu f8, 0x1(r4), 0, 7
    ps_madds0 f16, f1, f12, f7
    psq_stu f9, 0x2(r4), 1, 7
    ps_muls1 f17, f0, f13
    psq_stu f10, 0x1(r4), 0, 7
    ps_muls1 f18, f1, f13
    psq_stu f11, 0x2(r4), 1, 7
    ps_madds1 f15, f2, f12, f15
    ps_madds1 f16, f3, f12, f16
    psq_lu f12, 0x4(r3), 0, 6
    ps_madds0 f17, f2, f14, f17
    ps_madds0 f18, f3, f14, f18
    ps_madds0 f8, f4, f13, f15
    ps_madds0 f9, f5, f13, f16
    psq_lu f13, 0x4(r3), 0, 6
    ps_madds1 f10, f4, f14, f17
    ps_madds1 f11, f5, f14, f18
    psq_lu f14, 0x4(r3), 0, 6
    ps_muls0 f15, f0, f12
    psq_stu f8, 0xc(r4), 0, 6
    ps_muls0 f16, f1, f12
    psq_stu f9, 0x8(r4), 1, 6
    ps_muls1 f17, f0, f13
    psq_stu f10, 0x4(r4), 0, 7
    ps_muls1 f18, f1, f13
    psq_stu f11, 0x2(r4), 1, 7
    ps_madds1 f15, f2, f12, f15
    ps_madds1 f16, f3, f12, f16
    psq_lu f12, 0x4(r3), 0, 6
    ps_madds0 f17, f2, f14, f17
    ps_madds0 f18, f3, f14, f18
    ps_madds0 f8, f4, f13, f15
    ps_madds0 f9, f5, f13, f16
    psq_lu f13, 0x4(r3), 0, 6
    ps_madds1 f10, f4, f14, f17
    ps_madds1 f11, f5, f14, f18
    psq_lu f14, 0x4(r3), 0, 6
    bdnz L_8001D210
L_8001D2AC:
    lfd f14, 0x8(r1)
    psq_stu f8, 0x1(r4), 0, 7
    lfd f15, 0x10(r1)
    psq_stu f9, 0x2(r4), 1, 7
    lfd f16, 0x18(r1)
    psq_stu f10, 0x1(r4), 0, 7
    lfd f17, 0x20(r1)
    psq_stu f11, 0x2(r4), 1, 7
    lfd f18, 0x28(r1)
L_8001D2D0:
    addi r1, r1, 0x40
    blr
L_8001D2D8:
    ps_madds1 f15, f2, f12, f15
    ps_madds1 f16, f3, f12, f16
    ps_madds0 f17, f2, f14, f17
    ps_madds0 f18, f3, f14, f18
    ps_madds0 f8, f4, f13, f15
    ps_madds0 f9, f5, f13, f16
    ps_madds1 f10, f4, f14, f17
    ps_madds1 f11, f5, f14, f18
    b L_8001D2AC
}
#endif

#if TARGET_PC
/* Host: no C version of the paired-single skinning routine fn_8001D2FC yet (register
   arguments, no C prototype); left undefined, the port's generated stub aborts if called. */
#else
asm void fn_8001D2FC(void) {
    nofralloc
    lhzu r12, 0x0(r4)
    psq_lu f6, 0x0(r5), 1, 7
    mulli r12, r12, 0x30
    subi r6, r6, 0x1
    add r12, r12, r3
    and. r6, r6, r6
    psq_l f8, 0x0(r12), 0, 0
    psq_lu f9, 0x8(r12), 0, 0
    psq_lu f10, 0x8(r12), 0, 0
    psq_lu f11, 0x8(r12), 0, 0
    psq_lu f12, 0x8(r12), 0, 0
    psq_lu f13, 0x8(r12), 0, 0
    beq L_8001D390
    ps_muls0 f8, f8, f6
    mtctr r6
    ps_muls0 f9, f9, f6
    ps_muls0 f10, f10, f6
    ps_muls0 f11, f11, f6
    ps_muls0 f12, f12, f6
    ps_muls0 f13, f13, f6
L_8001D34C:
    lhzu r12, 0x2(r4)
    psq_lu f6, 0x1(r5), 1, 7
    mulli r12, r12, 0x30
    add r12, r12, r3
    psq_l f0, 0x0(r12), 0, 0
    psq_lu f1, 0x8(r12), 0, 0
    psq_lu f2, 0x8(r12), 0, 0
    psq_lu f3, 0x8(r12), 0, 0
    psq_lu f4, 0x8(r12), 0, 0
    psq_lu f5, 0x8(r12), 0, 0
    ps_madds0 f8, f0, f6, f8
    ps_madds0 f9, f1, f6, f9
    ps_madds0 f10, f2, f6, f10
    ps_madds0 f11, f3, f6, f11
    ps_madds0 f12, f4, f6, f12
    ps_madds0 f13, f5, f6, f13
    bdnz L_8001D34C
L_8001D390:
    ps_merge00 f0, f8, f10
    ps_merge01 f1, f12, f7
    ps_merge11 f2, f8, f10
    ps_merge11 f3, f12, f7
    ps_merge00 f4, f9, f11
    ps_merge01 f5, f13, f7
    ps_merge11 f6, f9, f11
    ps_merge11 f7, f13, f7
    blr
}
#endif

#if TARGET_PC
/* Host: psq_st f32 -> GQR5 type, read back as s16 */
void fn_8000E9A8(const f32* src, s16* dst) {
    union { u8 b[4]; s16 h; } t;
    fe10_psq_st(t.b, src[0], 5);
    *dst = t.h;
}
#else
asm void fn_8000E9A8(void) {
    nofralloc
    stwu r1, -0x10(r1)
    lfs f0, 0x0(r3)
    psq_st f0, 0x8(r1), 1, 5
    lha r0, 0x8(r1)
    sth r0, 0x0(r4)
    addi r1, r1, 0x10
    blr
}
#endif

