/* Text box proc: step the message script, one character or the whole page */
#include "game/rN_8025EEF0/calls.h"

extern "C" {

struct TB {
    u8 pad0[0x10];
    char* cur;
    u8 pad14[0xC];
    u8 m20;
    int m24;
    int m28;
    char buf[3][0x40];
    char* w;
    char* last;
    s16 line;
};
struct TBProc { u8 pad0[0x40]; int idx; u8 pad44[0x1C]; TB* d[1]; };
u8* fn_8024BCA0(void);
#if TARGET_PC
FE10_PROTO unsigned char * fn_80148728(char** p);
#else
int fn_80148728(char** p);
#endif
int fn_800CAB40(char* s);
}

static inline BOOL isSjis(u8 c, const char* p) {
    if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        c = p[1];
        if ((c >= 0x40 && c <= 0x7E) || (c >= 0x80 && c <= 0xFC)) return 1;
    }
    return 0;
}
static inline void emit(TB* d) {
    if (isSjis(*(const u8*)d->cur, d->cur)) {
        d->last = d->w;
        *d->w++ = *d->cur++;
        *d->w++ = *d->cur++;
        *d->w = 0;
        d->m28 = 8;
    } else {
        d->last = d->w;
        *d->w++ = *d->cur++;
        *d->w = 0;
        d->m28 = 8;
    }
}
static inline void skip(TB* d, char* s) {
    switch (*s) {
    case 1: d->cur = s + 2; break;
    case 2: d->cur = s + 3; break;
    case 3: d->cur = s + 4; break;
    case 4: d->cur = s + 1; fn_80148728(&d->cur); break;
    case 5:
        d->cur = s + 1;
        while (fn_80148728(&d->cur)) {}
        break;
    case 7: case 12: d->cur = s + 3; break;
    case 8: d->cur = s + 3; break;
    case 9: d->cur = s + 1; break;
    case 11: d->cur = s + 3; break;
    case 13: d->cur = s + 3; break;
    case 10: case 16: case 17: case 18: d->cur = s + 1; break;
    default: break;
    }
}
static inline int parse(TB* d) {
    char* s = d->cur;
    switch (*s) {
    case 0:
        d->m20 = 1;
        return 0;
    case 2: {
        char* t = s + 3;
        d->cur = t;
        switch (s[1]) {
        case 'w':
            d->m24 = 1 << (t[-1] - '0');
            return 2;
        case 'm':
            switch (t[-1]) {
            default:
                return 4;
            case 'c': case 'd': case 'o':
                return 1;
            }
        default:
            return 4;
        }
    }
    case 10:
        if (++d->line > 2) d->line = 2;
        d->w = d->buf[d->line];
        d->cur++;
        return 1;
    case 1: case 3: case 4: case 5: case 7: case 8: case 9: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
        skip(d, s);
        return 1;
    default:
        return 3;
    }
}
static inline int step(TB* d) {
    switch (parse(d)) {
    case 0: return 0;
    case 2: return 2;
    case 1: break;
    case 4:
    default:
        if ((s32)*(u8*)d->cur == 0x23) {
            int n = fn_800CAB40(d->cur);
            for (int i = 0; i < n; i++) emit(d);
        } else {
            emit(d);
        }
        break;
    }
    return 3;
}

extern "C" {
#pragma use_lmw_stmw on
void fn_8026FE48(TBProc* p) {
/*P*/
    int lim;
    int i;
    u32 pr;
    TB* d;
    BOOL sk;
/*E*/
    d = p->d[p->idx];
    pr = lbl_804CB5B8->v48();
    sk = 0;
    if (fn_8024BCA0()[0x34] > 1) {
        if (pr & 0xC00) {
            sk = 1;
            fn_80083DC4(p, 3);
        } else if (pr & 0x4000) {
            fn_80083DC4(p, 4);
            return;
        }
    }
    lim = 0x7FFF;
    if (sk == 0) lim = 1;
    if (sk == 0 && d->m24 > 0) {
        if (--d->m24 > 0) goto tail;
    }
    d->m24 = 8;
    for (i = 0; i < lim; i++) {
        if (step(d) == 0) break;
    }
    if (sk) {
        d->m28 = 0;
        d->m24 = 0;
    }
tail:
    if (sk == 0 && d->m20) fn_80083B78(p);
}
}
