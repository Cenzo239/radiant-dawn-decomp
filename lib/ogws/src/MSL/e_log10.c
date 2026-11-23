/* @(#)e_log10.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/* __ieee754_log10(x): base 10 logarithm (fdlibm; not part of the ogws tree,
 * FE10 address 0x80292AA0). */

#include <errno.h>
#include <internal/fdlibm.h>
#include <math.h>

static const double two54 = 1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
    ivln10 = 4.34294481903251816668e-01,                /* 0x3FDBCB7B, 0x1526E50E */
    log10_2hi = 3.01029995663611771306e-01,             /* 0x3FD34413, 0x509F6000 */
    log10_2lo = 3.69423907715893078616e-13;             /* 0x3D59FEF3, 0x11F12B36 */

static double zero = 0.0;

double __ieee754_log10(double x) {
    double y, z;
    int i, k, hx;
    unsigned int lx;

    hx = __HI(x);
    lx = __LO(x);
    k = 0;

    if (hx < 0x00100000) {
        if (((hx & 0x7FFFFFFF) | lx) == 0) {
            errno = EDOM;
            return -two54 / zero;
        }

        if (hx < 0) {
            errno = EDOM;
            return (x - x) / zero;
        }

        k -= 54;
        x *= two54;
        hx = __HI(x);
    }

    if (hx >= 0x7FF00000) {
        return x + x;
    }

    k += (hx >> 20) - 1023;
    i = ((unsigned int)k & 0x80000000) >> 31;
    hx = (hx & 0x000FFFFF) | ((0x3FF - i) << 20);
    y = (double)(k + i);
    __HI(x) = hx;
    z = y * log10_2lo + ivln10 * __ieee754_log(x);
    return z + y * log10_2hi;
}
