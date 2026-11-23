/* Font: length in bytes of the character at s (2 for a Shift-JIS pair). */
#include "game/rJ_800799AC/types.h"

extern "C" {

static inline BOOL isSjis(const u8* s) {
    if (((s[0] >= 0x81 && s[0] <= 0x9F) || (s[0] >= 0xE0 && s[0] <= 0xFC))
        && ((s[1] >= 0x40 && s[1] <= 0x7E) || (s[1] >= 0x80 && s[1] <= 0xFC))) {
        return 1;
    }
    return 0;
}

/* Font_NextChar: pointer to the character after s */
const u8* fn_80077D44(const u8* s) {
    int n = 1;
    n += isSjis(s) != 0;
    return s + n;
}

}
