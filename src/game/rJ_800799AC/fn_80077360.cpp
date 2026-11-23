/* Font: glyph lookup by Shift-JIS code. */
#include "game/rJ_800799AC/types.h"

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
#if TARGET_PC
FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
void fn_8023F1A8(void* p);
#endif
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

#define SEEKD(f, code) \
    if (f->cur->code != (u16)code) { \
        d = f->hdr; b = (Glyph*)((u8*)d + d->glyphs); \
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

void* fn_80077360(Font* f, int del) {
    if (f != 0) {
        if (f->v0 != 0 && f->hdr != 0) {
            fn_80078E24(f->hdr);
            f->hdr = 0;
        } else if (f->hdr != 0) {
            fn_8023F1A8(f->hdr);
        }
        f->hdr = 0;
        f->v0 = 0;
        f->count = 0;
        f->cur = 0;
        if (del > 0) {
            fn_80079210(f);
        }
    }
    return f;
}

void fn_80077400(Font* f) {
    if (f->v0 != 0 && f->hdr != 0) {
        fn_80078E24(f->hdr);
        f->hdr = 0;
    } else if (f->hdr != 0) {
        fn_8023F1A8(f->hdr);
    }
    f->hdr = 0;
    f->v0 = 0;
    f->count = 0;
    f->cur = 0;
}

static inline void fontLoad(Font* f, FontHdr* h) {
    Glyph* g;
    f->hdr = h;
    h->v10 = h->v12 = h->v08 + h->v0A;
    f->count = (h->pixels - h->glyphs) >> 4;
    g = (Glyph*)((u32)f->hdr + h->glyphs) + (f->count - 1);
    while (g->code == 0) {
        g--;
        f->count--;
    }
    f->cur = (Glyph*)((u32)f->hdr + h->glyphs);
}

FontHdr* fn_80077478(Font* f, const char* name, int flags) {
    FontHdr* h = (FontHdr*)fn_8023F1A4(name, flags | 0x20);
    fontLoad(f, h);
    return f->hdr;
}

/* Find a character's glyph; returns the next character */
u8* fn_80077524(Font* f, const u8* s, void** pix, u32* w, u32* h, int* adv) {
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
    if (isSjis(s)) {
        code = (((u8*)s)[0] << 8) | ((u8*)s)[1];
        n = (u8*)s + 2;
    } else {
        code = ((u8*)s)[0];
        n = (u8*)s + 1;
    }
    SEEK(f, code)
    {
        Glyph* g = f->cur;
        FontHdr* d = f->hdr;
        *adv = g->adv;
        *pix = (void*)(g->cell * d->cellSize + ((u32)d + d->pixels));
        *w = g->w;
        *h = g->h;
    }
    return n;
}

int fn_800778A8(const u8** ps) {
    const u8* s;
    int key2;
    int code;
    u16 key;
    int len;
    Glyph* mid;
    Glyph* first;
    int half2;
    int half;
    Glyph* mid2;
    Glyph* first2;
    Glyph* e;
    Glyph* b;
    u8* n;
    Font* f;
    int len0;
    f = lbl_804CB598;
    s = *ps;
    if (isSjis(s)) {
        code = (((u8*)s)[0] << 8) | ((u8*)s)[1];
        n = (u8*)s + 2;
    } else {
        code = ((u8*)s)[0];
        n = (u8*)s + 1;
    }
    SEEK(f, code)
    {
        s8 a = f->cur->adv;
        *ps = n;
        return a;
    }
}

int fn_80077C08(void) {
    int wide = fn_801D09F0();
    const char* a = lbl_80362350;
    const char* n = a + 0x13;
    if (wide) {
        n = a;
    }
    fn_8023F1A0(n, 0x8A0);
    return 1;
}

int fn_80077C4C(void) {
    FontHdr* h;
    int wide = fn_801D09F0();
    const char* a = lbl_80362350;
    const char* n = a + 0x13;
    if (wide) {
        n = a;
    }
    h = (FontHdr*)fn_8023F1A4(n, 0x8A0);
    fontLoad(&lbl_803CD858, h);
    lbl_804CB598 = &lbl_803CD858;
    return 1;
}

Font* fn_80077DB0(Font* f) {
    Font* old = lbl_804CB598;
    lbl_804CB598 = f ? f : &lbl_803CD858;
    return old;
}

Glyph* fn_80077DDC(const u8* s) {
    Font* f;
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
    int key2;
    FontHdr* d;
    if (isSjis(s)) {
        code = (((u8*)s)[0] << 8) | ((u8*)s)[1];
    } else {
        code = ((u8*)s)[0];
    }
    f = lbl_804CB598;
    SEEKD(f, code)
    return f->cur;
}

void* fn_80077360(Font* f, int del);
void fn_80077F68(void) {
    lbl_803CD858.v0 = 0;
    lbl_803CD858.hdr = 0;
    lbl_803CD858.count = 0;
    lbl_803CD858.cur = 0;
    __register_global_object(&lbl_803CD858, fn_80077360, lbl_803CD848);
}

}
