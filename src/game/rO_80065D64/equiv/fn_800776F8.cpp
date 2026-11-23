/* Font: advance width of the character at s in the current font; returns the
   next character. Same lookup as fn_80077524/fn_800778A8 (in
   rJ_800799AC/fn_80077360.cpp, the same source file).
   Level: sched. In the two-byte branch the original loads s[1] before s[0]
   (`lbz r30,1(r3); addi; lbz r3,0(r3); rlwimi`), ours s[0] first; the two
   loads are independent. Other differences are registers. symcheck --anon:
   clean. */
#include "game/rO_80065D64/types.h"

struct Glyph {
    u16 code;  /* 0x00 */
    u16 cell;  /* 0x02 */
    u16 w;     /* 0x04 */
    u16 h;     /* 0x06 */
    u8 p08[4];
    s8 adv;    /* 0x0C */
    u8 p0D[3];
};

struct FontHdr {
    u8 p00[0x8];
    u16 v08;
    u16 v0A;
    u8 p0C[0x10 - 0xC];
    u16 v10;
    u16 v12;
    u32 cellSize; /* 0x14 */
    u8 p18[0x22 - 0x18];
    u16 glyphs;   /* 0x22 */
    u32 pixels;   /* 0x24 */
};

struct Font {
    int v0;
    FontHdr* hdr; /* 0x04 */
    int count;    /* 0x08 */
    Glyph* cur;   /* 0x0C */
};

extern "C" {

extern const char lbl_80362350[];
extern u8 lbl_803CD848[];
void __register_global_object(void* o, void* dtor, void* chain);
#pragma use_lmw_stmw on
extern Font lbl_803CD858;
extern Font* lbl_804CB598;
extern int lbl_804CA3B0;
void fn_80078E24(void* p);
void fn_8023F1A8(void* p);
void* fn_8023F1A4(const char* name, int flags);
int fn_8023F1A0(const char* name, int flags);
void fn_80079210(void* p);
int fn_801D09F0(void);

static inline int dist(Glyph* const& a, Glyph* const& b) {
    return b - a;
}

static inline BOOL isSjis(const u8* s) {
    if (((s[0] >= 0x81 && s[0] <= 0x9F) || (s[0] >= 0xE0 && s[0] <= 0xFC))
        && ((s[1] >= 0x40 && s[1] <= 0x7E) || (s[1] >= 0x80 && s[1] <= 0xFC))) {
        return 1;
    }
    return 0;
}

#define SEEK(f, code) \
    if (f->cur->code != (u16)code) { \
        b = (Glyph*)((u8*)f->hdr + f->hdr->glyphs); \
        e = b + f->count; \
        len0 = dist(b, e); \
        key = (u16)code; \
        first = b; \
        len = len0; \
        while (len > 0) { \
            half = len / 2; \
            mid = first + half; \
            if (mid->code < key) { \
                first = mid + 1; \
                len -= half + 1; \
            } else { \
                len = half; \
            } \
        } \
        f->cur = first; \
        if (e == f->cur || f->cur->code != (u16)code) { \
            key2 = lbl_804CA3B0; \
            first2 = b; \
            while (len0 > 0) { \
                half2 = len0 / 2; \
                mid2 = first2 + half2; \
                if (mid2->code < (u16)key2) { \
                    first2 = mid2 + 1; \
                    len0 -= half2 + 1; \
                } else { \
                    len0 = half2; \
                } \
            } \
            f->cur = first2; \
            if (e == f->cur || f->cur->code != 0x8199) { \
                f->cur = b; \
            } \
        } \
    }


u8* fn_800776F8(const u8* s, int* adv) {
    Glyph* mid2;
    int half2;
    int len;
    Glyph* first2;
    Glyph* mid;
    u16 key;
    Glyph* first;
    Glyph* e;
    Glyph* b;
    int len0;
    int code;
    int half;
    u8* n;
    int key2;
    Font* f = lbl_804CB598;
    if (isSjis(s)) {
        code = (((u8*)s)[0] << 8) | ((u8*)s)[1];
        n = (u8*)s + 2;
    } else {
        code = ((u8*)s)[0];
        n = (u8*)s + 1;
    }
    SEEK(f, code)
    *adv = f->cur->adv;
    return n;
}

}
