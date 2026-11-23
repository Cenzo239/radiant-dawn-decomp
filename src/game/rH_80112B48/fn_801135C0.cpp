/* Map wall flags and terrain heights, 801135C0..80114A44. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off

extern "C" {

extern void fn_8017F464(void*, int, int);
extern void fn_8017F4A0(void*, void*, int);
extern int fn_8010E314(int, int);
extern void* fn_80078D9C(int, char*, int);
extern void fn_80078E24(void*);
extern char lbl_80368760[];
extern char lbl_803CB770[];
extern Map lbl_803EC898;
#if TARGET_PC
extern FE10_PROTO struct Trap * fn_80066130(void*, int, int, int);
#else
extern int fn_80066130(void*, int, int, int);
#endif
extern void fn_80113794(Map*, s8, s8, u32);
#if TARGET_PC
extern FE10_PROTO void fn_80115DEC(Map*, int, int, ptr32<const void>, ptr32<const void>);
#else
extern void fn_80115DEC(Map*, int, int, void*, void*);
#endif
#if TARGET_PC
extern FE10_PROTO u8* fn_80116294(Map*, u8*, int, int, int);
#else
extern void fn_80116294(Map*, u8*, int, int, int);
#endif
#if TARGET_PC
extern FE10_PROTO u8* fn_80116680(Map*, u8*, int, int);
#else
extern void fn_80116680(Map*, u8*, int, int);
#endif

void fn_801136C0(Map* m) {
    int i;
    for (i = 0; i < m->w; i++) {
        m->flags[(s8)i] = (m->flags[(s8)i] & ~0x808) | 0x80;
        m->flags[(s8)i + ((s8)(m->h - 1) << 6)] = (m->flags[(s8)i + ((s8)(m->h - 1) << 6)] & ~0x404) | 0x40;
    }
    for (i = 0; i < m->h; i++) {
        m->flags[(s8)i << 6] = (m->flags[(s8)i << 6] & ~0x101) | 0x10;
        m->flags[(s8)(m->w - 1) + ((s8)i << 6)] = (m->flags[(s8)(m->w - 1) + ((s8)i << 6)] & ~0x202) | 0x20;
    }
}

static inline u16* FlagAt(Map* m, s8 x, s8 y) {
    return &m->flags[x + (y << 6)];
}

static inline void FlagOr(Map* m, s8 x, s8 y, u32 f) {
    *FlagAt(m, x, y) |= f;
}

static inline void FlagClr(Map* m, s8 x, s8 y, u32 f) {
    *FlagAt(m, x, y) &= ~f;
}

f32 fn_801141D4(Map* m, s8 x, s8 y, int k) {
    return m->scale * (f32)m->hgt[k + (x + (y << 6)) * 4];
}

f32 fn_80114230(Map* m, s8 x, s8 y) {
    int i;
    if (x < 0 || x >= m->w || y < 0 || y >= m->h) {
        return -100.0f;
    }
    i = (x + (y << 6)) * 4;
    return m->scale * (f32)((m->hgt[i] + m->hgt[i + 1] + m->hgt[i + 2] + m->hgt[i + 3]) >> 2);
}

f32 fn_801146A8(Map* m, s8 x, s8 y, int k) {
    if (x < 0 || x >= m->w || y < 0 || y >= m->h) {
        return -100.0f;
    }
    return m->scale * (f32)m->hgt2[k + (x + (y << 6)) * 4];
}

f32 fn_80114728(Map* m, s8 x, s8 y) {
    int i;
    if (x < 0 || x >= m->w || y < 0 || y >= m->h) {
        return -100.0f;
    }
    i = (x + (y << 6)) * 4;
    return m->scale * (f32)((m->hgt2[i] + m->hgt2[i + 1] + m->hgt2[i + 2] + m->hgt2[i + 3]) >> 2);
}

int fn_801147E4(Map* m, s8 x, s8 y) {
    return m->bits[(x + (y << 6)) >> 3] & (1 << (x & 7));
}

void fn_80114818(Map* m, s8 x, s8 y) {
    m->bits[(x + (y << 6)) >> 3] |= (1 << (x & 7));
}

void fn_80114850(Map* m, s8 x, s8 y) {
    m->bits[(x + (y << 6)) >> 3] &= ~(1 << (x & 7));
}

void fn_80114888(Map* m, int k) {
    switch (k) {
    case 6:
        m->cur = m->cost;
        break;
    case 7:
        m->cur = m->cost2;
        break;
    case 12:
        break;
    }
}

void fn_801148CC(Map* m, u16* p) {
    m->cur = p;
}

int fn_801148D8(Map* m, u32 k) {
    int r = 0;
    switch (k) {
    case 0:
        r = 0x1000;
        break;
    case 1:
        r = 0x1000;
        break;
    case 2:
        r = 0x1000;
        break;
    case 3:
        r = 0x1000;
        break;
    case 5:
        r = 0x2000;
        break;
    case 6:
        r = 0x2000;
        break;
    case 7:
        r = 0x2000;
        break;
    case 8:
        r = 0x2000;
        break;
    case 9:
        r = 0x2000;
        break;
    case 4:
        break;
    }
    return r;
}

void fn_80114944(Map* m, u32 k, void* d) {
    int n = fn_801148D8(m, k);
    switch (k) {
    case 0:
        fn_8017F4A0(d, m->ter[0], n);
        break;
    case 1:
        fn_8017F4A0(d, m->ter[1], n);
        break;
    case 2:
        fn_8017F4A0(d, m->ter[2], n);
        break;
    case 3:
        fn_8017F4A0(d, m->ter[3], n);
        break;
    case 5:
        fn_8017F4A0(d, m->flags, n);
        break;
    case 6:
        fn_8017F4A0(d, m->cost, n);
        break;
    case 7:
        fn_8017F4A0(d, m->cost2, n);
        break;
    case 8:
        fn_8017F4A0(d, m->g3, n);
        break;
    case 9:
        fn_8017F4A0(d, m->g4, n);
        break;
    }
}

void fn_80114A44(Map* m, u32 k, void* d) {
    int n = fn_801148D8(m, k);
    switch (k) {
    case 0:
        fn_8017F4A0(m->ter[0], d, n);
        break;
    case 1:
        fn_8017F4A0(m->ter[1], d, n);
        break;
    case 2:
        fn_8017F4A0(m->ter[2], d, n);
        break;
    case 3:
        fn_8017F4A0(m->ter[3], d, n);
        break;
    case 5:
        fn_8017F4A0(m->flags, d, n);
        break;
    case 6:
        fn_8017F4A0(m->cost, d, n);
        break;
    case 7:
        fn_8017F4A0(m->cost2, d, n);
        break;
    case 8:
        fn_8017F4A0(m->g3, d, n);
        break;
    case 9:
        fn_8017F4A0(m->g4, d, n);
        break;
    }
}

static inline void Fill8(void* p, u8 v, int n) {
    fn_8017F464(p, (v + (v << 8)) + ((v << 24) + (v << 16)), n);
}

static inline void Fill16(void* p, u16 v, int n) {
    fn_8017F464(p, v + (v << 16), n);
}

void fn_80114B44(Map* m, u32 k, int v) {
    switch (k) {
    case 0:
        Fill8(m->ter[0], v, 0x1000);
        return;
    case 1:
        Fill8(m->ter[1], v, 0x1000);
        return;
    case 2:
        Fill8(m->ter[2], v, 0x1000);
        return;
    case 4:
        Fill8(m->ter[4], v, 0x1000);
        return;
    case 3:
        Fill8(m->ter[3], v, 0x1000);
        return;
    case 6:
        Fill16(m->border2, v, 0x2080);
        return;
    case 7:
        Fill16(m->border3, v, 0x2080);
        return;
    case 12:
        if (m->cur == m->cost) {
            fn_80114B44(m, 6, v);
            return;
        }
        if (m->cur == m->cost2) {
            fn_80114B44(m, 7, v);
            return;
        }
        Fill16(m->cur, v, 0x2000);
        return;
    case 8:
        Fill16(m->g3, v, 0x2000);
        return;
    case 9:
        Fill16(m->g4, v, 0x2000);
        return;
    case 10:
        Fill16(m->g7, v, 0x2000);
        return;
    case 5:
    case 11:
        return;
    }
}

void fn_80115658(Map* m, int i, s8 v) {
    m->costTbl[i] = v;
    if (v < 0) {
        m->costTbl[i] = 0x7fff;
    }
}

static inline u8 IsAlly(int a, int b) {
    return (u8)fn_8010E314(a, b) == 1;
}

void fn_8011567C(Map* m, u8* u) {
    if (u == 0) {
        m->team[0] = 0;
        m->team[1] = 0;
        m->team[2] = 0;
        m->team[3] = 0;
    } else {
        u8 a = u[8];
        m->team[0] = IsAlly(a, 0);
        m->team[1] = IsAlly(a, 1);
        m->team[2] = IsAlly(a, 2);
        m->team[3] = IsAlly(a, 3);
    }
}

#pragma push
#pragma use_lmw_stmw on
void fn_80116098(Map* m, s8 sx, s8 sy, void* a, void* b) {
    void* p = fn_80078D9C(-fn_801148D8(&lbl_803EC898, 5), lbl_80368760, 0);
    int y;
    int x;
    fn_80114944(&lbl_803EC898, 5, p);
    for (y = m->y0; y < m->y1; y++) {
        for (x = m->x0; x < m->x1; x++) {
            if (fn_80066130(lbl_803CB770, (s8)x, (s8)y, 4)) {
                fn_80113794(m, (s8)x, (s8)y, 0xf00);
            }
        }
    }
    fn_80115DEC(m, sx, sy, a, b);
    fn_80114A44(&lbl_803EC898, 5, p);
    fn_80078E24(p);
}
#pragma pop

void
#if TARGET_PC
*
#endif
fn_80116658(Map* m, s8 x, s8 y) {
    m->padC = 1;
#if TARGET_PC
    return fn_80116294(m, m->buf, x, y, 0x100);
#else
    fn_80116294(m, m->buf, x, y, 0x100);
#endif
}

void
#if TARGET_PC
*
#endif
fn_80116A30(Map* m, s8 x, s8 y) {
#if TARGET_PC
    return fn_80116680(m, m->buf, x, y);
#else
    fn_80116680(m, m->buf, x, y);
#endif
}

u8* fn_80116A4C(Map* m) {
    return m->buf;
}

u8* fn_80116A58(Map* m) {
    u8* b = m->buf;
    *b = 0x40;
    return b;
}

}
