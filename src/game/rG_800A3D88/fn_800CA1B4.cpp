#include "game/rG_800A3D88/chr.h"

// Parses n hex digits at *s, advancing *s, and returns the value.
extern "C" {
int fn_800CA1B4(char** s, u32 n) {
    u8* buf = (u8*)__alloca(n);
    int i;
    for (i = 0; (u8)i < n; i++) {
        s8 c = *(*s)++;
        if (c >= '0' && c <= '9') buf[(u8)i] = c - '0';
        else if (c >= 'a' && c <= 'f') buf[(u8)i] = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') buf[(u8)i] = c - 'A' + 10;
    }
    int r = 0;
    u32 m = n - 1;
    s16 j = m;
    s16 sh = 0;
    for (; j >= 0; j--) {
        r += buf[j] << sh;
        sh += 4;
    }
    n = m; return r;
}
}
