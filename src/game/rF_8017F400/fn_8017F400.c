#include "game/rF_8017F400/types.h"

int fn_8017F400(void) { return 1; }
int fn_8017F408(void) { return 0; }
int fn_8017F410(void) { return 0; }

#if TARGET_PC
/* C equivalents of the hand-written asm below (ctr loops over n/4 or n/8 words) */
int fn_8017F418(u32* a, u32* b, u32 n)
{
    for (n >>= 2; n != 0; n--) {
        if (*a++ != *b++) {
            return 1;
        }
    }
    return 0;
}

void fn_8017F44C(u32* dst, u32 val, u32 n)
{
    for (n >>= 2; n != 0; n--) {
        *dst++ = val;
    }
}

void fn_8017F464(u32* dst, u32 val, u32 n)
{
    for (n >>= 3; n != 0; n--) {
        *dst++ = val;
        *dst++ = val;
    }
}

void fn_8017F480(u32* dst, u32* src, u32 n)
{
    for (n >>= 2; n != 0; n--) {
        *dst++ = *src++;
    }
}

void fn_8017F4A0(u32* dst, u32* src, u32 n)
{
    for (n >>= 3; n != 0; n--) {
        *dst++ = *src++;
        *dst++ = *src++;
    }
}
#else
/* hand-written asm: word compare, returns 0 if equal */
asm int fn_8017F418(register u32* a, register u32* b, register u32 n)
{
    nofralloc
    subi r3, r3, 0x4
    srwi r5, r5, 2
    subi r4, r4, 0x4
    mtctr r5
loop:
    lwzu r11, 0x4(r3)
    lwzu r12, 0x4(r4)
    cmplw r11, r12
    bne diff
    bdnz loop
    li r3, 0x0
    blr
diff:
    li r3, 0x1
    blr
}

/* hand-written asm: word fill */
asm void fn_8017F44C(register u32* dst, register u32 val, register u32 n)
{
    nofralloc
    srwi r5, r5, 2
    subi r3, r3, 0x4
    mtctr r5
loop:
    stwu r4, 0x4(r3)
    bdnz loop
    blr
}

/* hand-written asm: word fill, 2x unrolled */
asm void fn_8017F464(register u32* dst, register u32 val, register u32 n)
{
    nofralloc
    srwi r5, r5, 3
    subi r3, r3, 0x4
    mtctr r5
loop:
    stwu r4, 0x4(r3)
    stwu r4, 0x4(r3)
    bdnz loop
    blr
}

/* hand-written asm: word copy */
asm void fn_8017F480(register u32* dst, register u32* src, register u32 n)
{
    nofralloc
    subi r3, r3, 0x4
    srwi r5, r5, 2
    subi r4, r4, 0x4
    mtctr r5
loop:
    lwzu r11, 0x4(r4)
    stwu r11, 0x4(r3)
    bdnz loop
    blr
}

/* hand-written asm: word copy, 2x unrolled */
asm void fn_8017F4A0(register u32* dst, register u32* src, register u32 n)
{
    nofralloc
    subi r3, r3, 0x4
    srwi r5, r5, 3
    subi r4, r4, 0x4
    mtctr r5
loop:
    lwzu r11, 0x4(r4)
    stwu r11, 0x4(r3)
    lwzu r12, 0x4(r4)
    stwu r12, 0x4(r3)
    bdnz loop
    blr
}

#endif

/* LZ77 header: decompressed size */
int fn_8017F658(u8* src)
{
    int size;
    if (src[0] != 0x10) {
        return 0;
    }
    size = src[1] + (src[2] << 8);
    size += src[3] << 16;
    return size;
}
