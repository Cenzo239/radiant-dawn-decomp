
// Yes, versions other than 4.3U align by 8.
#if defined(VERSION_43U)
#pragma function_align 32
#else
#pragma function_align 8
#endif  // VERSION_43U

#include <TRK_Hollywood_Revolution.h>

#pragma force_active on

// The original is one asm function with four `entry` points. Entries are not function symbols,
// so for the lib check each one is its own 8-byte asm function here (same bytes, function_align 8).
#ifdef __MWERKS__
asm DSIOResult TRKAccessFile(MessageCommandID cmd, unsigned int handle, int* count, unsigned char* buffer) {
    nofralloc
    twi 31, r0, 0
    blr
}

asm DSIOResult TRKOpenFile() {
    nofralloc
    twi 31, r0, 0
    blr
}

asm DSIOResult TRKCloseFile() {
    nofralloc
    twi 31, r0, 0
    blr
}

asm DSIOResult TRKPositionFile() {
    nofralloc
    twi 31, r0, 0
    blr
}
#endif // __MWERKS__
