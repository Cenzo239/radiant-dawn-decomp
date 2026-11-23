#include <MSL/arith.h>

int abs(int n) {
    if (n < 0) {
        return -n;
    } else {
        return n;
    }
}

// FE10: labs is linked too (0x8028DB54)
long labs(long n) {
    if (n < 0) {
        return -n;
    } else {
        return n;
    }
}
