/* fn_8017F4C8 LZ77 decompress: near miss, 70/100 words differ (header reg order; unrolled copy loop emits an extra len<=0 guard on cr1). */
#include "game/rF_8017F400/types.h"
int fn_8017F4C8(u8* src, u8* dst)
{
    u8* start = dst;
    s8 flags;
    s8 bits = 0;
    int size;
    u8* p;
    int len;
    int i;
    u32 b0, b1;

    if (src[0] != 0x10) {
        return 0;
    }
    size = src[1] + (src[2] << 8);
    size += src[3] << 16;
    src += 4;
    for (;;) {
        if (size == dst - start) {
            break;
        }
        if (bits == 0) {
            flags = *src++;
            bits = 8;
        }
        if (flags >= 0) {
            *dst++ = *src++;
        } else {
            b0 = src[0];
            b1 = src[1];
            src += 2;
            len = ((b0 >> 4) & 0xF) + 3;
            p = dst - (((b0 & 0xF) << 8) + b1) - 1;
            for (i = 0; i < len; i++) {
                *dst++ = *p++;
            }
        }
        flags <<= 1;
        bits--;
    }
    return dst - start;
}
