/* Width in pixels of the widest line of s, from the glyph cache (see fn_8008A868, fn_8008B19C). Names guessed. */
#include "game/rJ_800799AC/types.h"

struct Glyph {
    u8 pix[0x120];
    u16 code;  /* 0x120 */
    u16 w;     /* 0x122 */
    u8 pad[0x140 - 0x124];
};
struct GlyphCache {
    Glyph* buf;
    int count;
};

extern "C" {
extern GlyphCache lbl_804CB5E8;
u16 fn_8031C044(void);
}

static inline BOOL isSjis(const u8* s) {
    if (((s[0] >= 0x81 && s[0] <= 0x9F) || (s[0] >= 0xE0 && s[0] <= 0xFC))
        && ((s[1] >= 0x40 && s[1] <= 0x7E) || (s[1] >= 0x80 && s[1] <= 0xFC))) {
        return 1;
    }
    return 0;
}
static inline Glyph* find(GlyphCache* gc, u16 code) {
    Glyph* b;
    Glyph* e;
    Glyph* first;
    int half;
    Glyph* mid;
    int len;
    b = gc->buf;
    e = b + gc->count;
    first = b;
    len = e - b;
    while (len > 0) {
        half = len / 2;
        mid = first + half;
        if (mid->code < code) {
            first = mid + 1;
            len -= half + 1;
        } else {
            len = half;
        }
    }
    if (e == first || first->code != code) {
        first = gc->buf;
    }
    return first;
}

extern "C" {
#pragma use_lmw_stmw on
int fn_8008AEE4(const u8* s) {
    int max = 0;
    int cur = 0;
    while ((s8)*s != 0) {
        u16 c;
        if ((s8)*s == '\n') {
            if (max < cur) max = cur;
            cur = 0;
            s++;
            continue;
        }
        if (fn_8031C044() != 1) {
            c = *s++;
        } else {
            BOOL sj = 0;
            if (fn_8031C044() == 1) sj = isSjis(s);
            if (!sj) {
                c = *s++;
            } else {
                c = *(const u16*)s;
                s += 2;
            }
        }
        cur += find(&lbl_804CB5E8, c)->w;
    }
    if (max < cur) max = cur;
    return max;
}
#pragma use_lmw_stmw off
}
