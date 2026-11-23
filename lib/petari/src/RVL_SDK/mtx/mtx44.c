#include "revolution/mtx.h"

void mtx44_FORCE_MATCH_SDATA2() {
    (void)1.0f;
    (void)2.0f;
    (void)0.0f;
    (void)-1.0f;
}

extern f64 tan(f64);

void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f) {
    f32 angle;
    f32 cot;
    f32 tmp;
    angle = fovY * 0.5f;
    angle = MTXDegToRad(angle);
    cot = tan(angle);
    cot = 1.0f / cot;

    m[0][0] = cot / aspect;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;

    m[1][0] = 0.0f;
    m[1][1] = cot;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;

    tmp = 1.0f / (f - n);
    m[2][2] = -(n)*tmp;
    m[2][3] = -(f * n) * tmp;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = -1.0f;
    m[3][3] = 0.0f;
}

void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 tmp;
    tmp = 1.0f / (r - l);
    m[0][0] = 2.0f * tmp;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = -(r + l) * tmp;

    tmp = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = 2.0f * tmp;
    m[1][2] = 0.0f;
    m[1][3] = -(t + b) * tmp;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;

    tmp = 1.0f / (f - n);
    m[2][2] = -(1.0f) * tmp;
    m[2][3] = -(f)*tmp;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

// clang-format off

void PSMTX44Identity( register Mtx44 m )
{
    register f32 c1 = 1.0F;
    register f32 c0 = 0.0F;
    
    asm
    {
        stfs        c1,  0(m);
        psq_st      c0,  4(m), 0, 0;
        psq_st      c0, 12(m), 0, 0;
        stfs        c1, 20(m);
        psq_st      c0, 24(m), 0, 0;
        psq_st      c0, 32(m), 0, 0;
        stfs        c1, 40(m);
        psq_st      c0, 44(m), 0, 0;
        psq_st      c0, 52(m), 0, 0;
        stfs        c1, 60(m);
    }
}

asm void PSMTX44Copy( const register Mtx44 src, register Mtx44 dst )
{
    nofralloc;
    psq_l       fp1,  0(src), 0, 0;
    psq_st      fp1,  0(dst), 0, 0;
    psq_l       fp1,  8(src), 0, 0;
    psq_st      fp1,  8(dst), 0, 0;
    psq_l       fp1, 16(src), 0, 0;
    psq_st      fp1, 16(dst), 0, 0;
    psq_l       fp1, 24(src), 0, 0;
    psq_st      fp1, 24(dst), 0, 0;
    psq_l       fp1, 32(src), 0, 0;
    psq_st      fp1, 32(dst), 0, 0;
    psq_l       fp1, 40(src), 0, 0;
    psq_st      fp1, 40(dst), 0, 0;
    psq_l       fp1, 48(src), 0, 0;
    psq_st      fp1, 48(dst), 0, 0;
    psq_l       fp1, 56(src), 0, 0;
    psq_st      fp1, 56(dst), 0, 0;
    blr;
}

//clang-format on

// FE10 links PSMTX44Concat and C_MTX44Inverse (source: doldecomp/dolsdk2004 src/mtx/mtx44.c)
// clang-format off
asm void PSMTX44Concat(const register Mtx44 a, const register Mtx44 b, register Mtx44 ab) {
    nofralloc
    psq_l f0, 0x0(a), 0, 0
    psq_l f2, 0x0(b), 0, 0
    ps_muls0 f6, f2, f0
    psq_l f3, 0x10(b), 0, 0
    psq_l f4, 0x20(b), 0, 0
    ps_madds1 f6, f3, f0, f6
    psq_l f1, 0x8(a), 0, 0
    psq_l f5, 0x30(b), 0, 0
    ps_madds0 f6, f4, f1, f6
    psq_l f0, 0x10(a), 0, 0
    ps_madds1 f6, f5, f1, f6
    psq_l f1, 0x18(a), 0, 0
    ps_muls0 f8, f2, f0
    ps_madds1 f8, f3, f0, f8
    psq_l f0, 0x20(a), 0, 0
    ps_madds0 f8, f4, f1, f8
    ps_madds1 f8, f5, f1, f8
    psq_l f1, 0x28(a), 0, 0
    ps_muls0 f10, f2, f0
    ps_madds1 f10, f3, f0, f10
    psq_l f0, 0x30(a), 0, 0
    ps_madds0 f10, f4, f1, f10
    ps_madds1 f10, f5, f1, f10
    psq_l f1, 0x38(a), 0, 0
    ps_muls0 f12, f2, f0
    psq_l f2, 0x8(b), 0, 0
    ps_madds1 f12, f3, f0, f12
    psq_l f0, 0x0(a), 0, 0
    ps_madds0 f12, f4, f1, f12
    psq_l f3, 0x18(b), 0, 0
    ps_madds1 f12, f5, f1, f12
    psq_l f1, 0x8(a), 0, 0
    ps_muls0 f7, f2, f0
    psq_l f4, 0x28(b), 0, 0
    ps_madds1 f7, f3, f0, f7
    psq_l f5, 0x38(b), 0, 0
    ps_madds0 f7, f4, f1, f7
    psq_l f0, 0x10(a), 0, 0
    ps_madds1 f7, f5, f1, f7
    psq_l f1, 0x18(a), 0, 0
    ps_muls0 f9, f2, f0
    psq_st f6, 0x0(ab), 0, 0
    ps_madds1 f9, f3, f0, f9
    psq_l f0, 0x20(a), 0, 0
    ps_madds0 f9, f4, f1, f9
    psq_st f8, 0x10(ab), 0, 0
    ps_madds1 f9, f5, f1, f9
    psq_l f1, 0x28(a), 0, 0
    ps_muls0 f11, f2, f0
    psq_st f10, 0x20(ab), 0, 0
    ps_madds1 f11, f3, f0, f11
    psq_l f0, 0x30(a), 0, 0
    ps_madds0 f11, f4, f1, f11
    psq_st f12, 0x30(ab), 0, 0
    ps_madds1 f11, f5, f1, f11
    psq_l f1, 0x38(a), 0, 0
    ps_muls0 f13, f2, f0
    psq_st f7, 0x8(ab), 0, 0
    ps_madds1 f13, f3, f0, f13
    psq_st f9, 0x18(ab), 0, 0
    ps_madds0 f13, f4, f1, f13
    psq_st f11, 0x28(ab), 0, 0
    ps_madds1 f13, f5, f1, f13
    psq_st f13, 0x38(ab), 0, 0
    blr
}

// clang-format on

#define SWAP(a, b) \
    {              \
        f32 tmp;   \
        tmp = a;   \
        a = b;     \
        b = tmp;   \
    }

#pragma fp_contract off
u32 C_MTX44Inverse(const Mtx44 src, Mtx44 inv) {
    Mtx44 gjm;
    s32 i;
    s32 j;
    s32 k;
    f32 w;
    f32 max;
    s32 swp;
    f32 ftmp;

    PSMTX44Copy(src, gjm);
    PSMTX44Identity(inv);

    for (i = 0; i < 4; i++) {
        max = 0.0f;
        swp = i;

        for (k = i; k < 4; k++) {
            ftmp = (f32)__fabs(gjm[k][i]);
            if (ftmp > max) {
                max = ftmp;
                swp = k;
            }
        }

        if (max == 0.0f) {
            return 0;
        }

        if (swp != i) {
            for (k = 0; k < 4; k++) {
                SWAP(gjm[i][k], gjm[swp][k]);
                SWAP(inv[i][k], inv[swp][k]);
            }
        }

        w = 1.0f / gjm[i][i];
        for (j = 0; j < 4; j++) {
            gjm[i][j] *= w;
            inv[i][j] *= w;
        }

        for (k = 0; k < 4; k++) {
            if (k != i) {
                w = gjm[k][i];
                for (j = 0; j < 4; j++) {
                    gjm[k][j] -= gjm[i][j] * w;
                    inv[k][j] -= inv[i][j] * w;
                }
            }
        }
    }

    return 1;
}

