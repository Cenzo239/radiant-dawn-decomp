#include "game/rP_80105B04/rp.h"
/* Item table: lbl_804CB7D4, count lbl_804CB7D0, 0xB4 bytes each. */
struct ItemRec {
    char* name;  /* 0 */
    u8 pad4[0x10];
    char* a[3];  /* 0x14 */
    u8 pad20[0x10];
    char* b[3];  /* 0x30 */
    u8 pad3C[0x84 - 0x3C];
    u8 id;       /* 0x84 */
    u8 pad85[0xB4 - 0x85];
};
extern "C" {
extern int lbl_804CB7D0;
extern ItemRec* lbl_804CB7D4;
extern char lbl_80367F68[];
extern char lbl_803EC2D8[];
extern char lbl_803EC2F8[];
int fn_80291188(const char* a, const char* b);
int fn_802912A4(const char* a, const char* b, int n);
char* strcpy(char* a, const char* b);

ItemRec* fn_8010B094(int id) {
    int n = lbl_804CB7D0;
    ItemRec* p = lbl_804CB7D4;
    int i;
    for (i = 0; i < n; i++) {
        if (p->id == id) return p;
        p++;
    }
    return 0;
}
ItemRec* fn_8010B100(const char* name) {
    int n;
    ItemRec* p;
    int i;
    i = 0;
    p = lbl_804CB7D4;
    n = lbl_804CB7D0;
    for (; i < n; i++, p++) {
        if (fn_80291188(p->name, name) == 0) return p;
    }
    return 0;
}
int fn_8010B260(u8* s) {
    if (s == 0) return 0;
    if (s[1] == 'I' && s[2] == 'D' && s[3] == '_') {
        switch ((s8)s[0]) {
        case 'P': return 1;
        case 'J': return 2;
        case 'I': return 3;
        case 'F': return 4;
        case 'E': return 6;
        case 'A': return 7;
        case 'S': return 9;
        case 'R': return 8;
        }
    }
    if (s[0] == 'M') {
        if (s[2] == '_' || s[4] == '_') return 5;
        if ((s8)s[1] == 'Y') return 5;
    }
    if (fn_802912A4((char*)s, lbl_80367F68 + 0xBB, 5) == 0) return 0xA;
    return 0;
}
char* fn_8010B384(int a, int b) {
    if (b) {
        switch (a) {
        case 0: return lbl_80367F68 + 0xC1;
        case 1: return lbl_80367F68 + 0xC2;
        case 2: return lbl_80367F68 + 0xC5;
        case 3: return lbl_80367F68 + 0xC9;
        }
    } else {
        switch (a) {
        case 0: return lbl_80367F68 + 0xC1;
        case 1: return lbl_80367F68 + 0xCE;
        case 2: return lbl_80367F68 + 0xD1;
        case 3: return lbl_80367F68 + 0xD5;
        }
    }
    return lbl_80367F68 + 0xC1;
}
char* fn_8010B528(ItemRec* r, int i) {
    char* p;
    if (r->a[i]) {
        strcpy(lbl_803EC2D8, r->a[i]);
        p = lbl_803EC2D8;
        while (*p) {
            if (*p == '/') {
                *p = 0;
                break;
            }
            p++;
        }
        return lbl_803EC2D8;
    }
    return 0;
}
u8 fn_8010B5AC(ItemRec* r, int i) {
    u8 f = 0;
    char buf[0x20];
    char* p;
    if (r->a[i]) {
    strcpy(buf, r->a[i]);
    p = buf;
    while (*p) {
        if (*p == '/') {
            switch (p[1]) {
            case 'D': f |= 1; break;
            case '2': f |= 2; break;
            case 'L': f |= 4; break;
            case 'S': f |= 8; break;
            }
        }
        p++;
    }
    }
    return f;
}
char* fn_8010B6D8(ItemRec* r, int i) {
    char* p;
    if (r->b[i]) {
        strcpy(lbl_803EC2F8, r->b[i]);
        p = lbl_803EC2F8;
        while (*p) {
            if (*p == '/') {
                *p = 0;
                break;
            }
            p++;
        }
        return lbl_803EC2F8;
    }
    return 0;
}
u8 fn_8010B75C(ItemRec* r, int i) {
    u8 f = 0;
    char buf[0x20];
    char* p;
    if (r->b[i]) {
    strcpy(buf, r->b[i]);
    p = buf;
    while (*p) {
        if (*p == '/') {
            switch (p[1]) {
            case 'F': f |= 1; break;
            case 'N': f |= 2; break;
            }
        }
        p++;
    }
    }
    return f;
}

struct MapHdr { int w, h; u8 pad[0x30000]; };
struct UnitP {
    u8 pad[0x108];
    u64 flags;
};
struct Tile { u8 pad[8]; u8* obj; };
struct Tgt { u8 pad[0xA]; s8 x, y; };
extern MapHdr lbl_803EC898;
extern u8 lbl_803CB770[];
int fn_80117A0C(void* u, s8 x, s8 y);
Tile* fn_801181E8(void* m, s8 x, s8 y);
#if TARGET_PC
FE10_PROTO struct Trap * fn_80066130(void* m, s8 x, s8 y, int k);
#else
int fn_80066130(void* m, s8 x, s8 y, int k);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_8012CF28(int x, int y);
#else
int fn_8012CF28(int x, int y);
#endif

#pragma use_lmw_stmw on
int fn_8010B7F8(UnitP* u, int x, int y, u32 t, int n, Tgt** list) {
    int i;
    int r;
    if (x < 0 || y < 0 || x >= lbl_803EC898.w || y >= lbl_803EC898.h) return 0;
    if (t != fn_80117A0C(&lbl_803EC898, x, y)) return 0;
    if (list) {
        for (i = 0; i < n; i++) {
            if (x == (*list)->x && y == (*list)->y) return 0;
            list++;
        }
    }
    if (fn_801181E8(&lbl_803EC898, x, y)->obj[7] & 1) return 0;
    if (fn_80066130(lbl_803CB770, x, y, 0xC)) return 0;
    u->flags |= 0x800000000ULL;
    r = fn_8012CF28(x, y);
    u->flags &= ~0x800000000ULL;
    return r == 0;
}

#define R8() fn_80109A18(s)
#define R32() fn_80109A88(s)
struct ItemFull {
    u16 a0, a2;
    void* p4, *p8;
    u8 xc, xd, xe, xf, x10, x11;
    u8 pad12[2];
    void* w14[7];
    void* w30[5];
    void* p44, *p48, *p4c, *p50, *p54;
    u8 x58[8];
    u8 x60, x61, x62, x63, x64, x65, x66, x67;
};
extern char lbl_80368054[];
u16 fn_80109A2C(u8** s);
u8 fn_80109A18(u8** s);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_80109A88(u8** s);
#else
void* fn_80109A88(u8** s);
#endif
u8 fn_801194FC(void* s);

void fn_8010BCBC(u8** s, ItemFull* r, u8 id, int kind) {
    int i;
    switch (kind) {
    case 7:
        r->a0 = fn_80109A2C(s);
        r->a2 = fn_80109A2C(s);
        r->p4 = R32();
        r->p8 = R32();
        r->xe = R8();
        r->xf = R8();
        r->x10 = R8();
        r->x11 = R8();
        r->xd = R8();
        r->xc = R8();
        r->x60 = R8();
        r->x63 = R8();
        r->x58[0] = R8();
        r->x58[1] = R8();
        r->x58[2] = R8();
        r->x58[3] = R8();
        r->x58[4] = R8();
        r->x58[5] = R8();
        r->x58[6] = R8();
        r->x58[7] = R8();
        r->x62 = R8();
        r->x65 = R8();
        r->x66 = R8();
        R8();
        r->x64 = fn_801194FC(R32());
        for (i = 0; i < 7; i++) r->w14[i] = R32();
        for (i = 0; i < 5; i++) r->w30[i] = R32();
        r->p44 = R32();
        r->p48 = R32();
        r->p4c = R32();
        r->p50 = R32();
        r->x61 = 0;
        r->p54 = R32();
        if (r->p54 == 0) r->p54 = lbl_80368054 + 0x19;
        break;
    default:
        break;
    }
    *s = (u8*)(((u32)*s + 3) & ~3);
    r->x67 = id;
}
}
