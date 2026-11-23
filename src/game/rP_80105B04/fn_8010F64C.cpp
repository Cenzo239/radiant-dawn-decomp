#include "game/rP_80105B04/rp.h"
/* Item names and articles ("a" or "an" from the first letter of the name, English only). */
struct Sys { u8 pad[0x1BC8]; u8 lang; };
#if TARGET_PC
/* host: Wii layout (32-bit pointer slots). The flags at 0x38 are one u64 elsewhere
   (ItemF.fl in fn_8010F988.cpp): its low word is at 0x3C on the big-endian Wii but at
   0x38 on a little-endian host, so fh/fl swap places. */
struct ItemN {
    FE10_P32(char) name;  /* 0 */
    FE10_P32(char) id;    /* 4 */
    u8 pad8[0xA];
    u8 x12;      /* 0x12 */
    u8 pad13[2];
    u8 article;  /* 0x15 */
    u8 pad16[0x21 - 0x16];
    u8 x21;      /* 0x21 */
    u8 pad22[0x38 - 0x22];
    u32 fl;      /* 0x38: low word of the u64 */
    u32 fh;      /* 0x3C */
};
static_assert(sizeof(ItemN) == 0x40, "ItemN");
#else
struct ItemN {
    char* name;  /* 0 */
    char* id;    /* 4 */
    u8 pad8[0xA];
    u8 x12;      /* 0x12 */
    u8 pad13[2];
    u8 article;  /* 0x15 */
    u8 pad16[0x21 - 0x16];
    u8 x21;      /* 0x21 */
    u8 pad22[0x38 - 0x22];
    u32 fh;      /* 0x38 */
    u32 fl;      /* 0x3C */
};
#endif
extern "C" {
extern char lbl_803680E8[];
extern void* lbl_804CA528;
Sys* fn_8024BC94();
void* fn_80076F54(const char* s);
char* fn_800D0864(const char* s);
char* fn_8010B384(int a, int b);
int fn_80123998(void* u);
int fn_8011B77C(void* s, void* id);

static inline int Article(ItemN* it) {
    int a = (s8)it->article;
    char* n;
    switch (a) {
    case -1:
        if (it->fh & 0x20000) return 3;
        if (fn_80076F54(it->id)) n = fn_800D0864(it->id);
        else n = it->name;
        if (n == 0) return 0;
        switch (*n) {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
            return 2;
        default:
            return 1;
        }
    default:
        return a;
    }
}
char* fn_8010F64C(ItemN* it, int b) {
    switch (fn_8024BC94()->lang) {
    case 1:
        return fn_8010B384(Article(it), b);
    default:
        return lbl_803680E8 + 0x3E;
    }
}
struct NSlot { ItemN* item; u8 uses; u8 f80 : 1; u8 f40 : 1; u8 f20 : 1; u8 lo : 5; };
char* fn_801110C4(NSlot* s, int b) {
    if (s->item == 0) return lbl_803680E8 + 0x3E;
    {
        int l = fn_8024BC94()->lang;
        if (l != 1) return lbl_803680E8 + 0x3E;
    }
    if (s->f20) return fn_8010B384(3, b);
    {
        ItemN* it = s->item;
        switch (fn_8024BC94()->lang) {
        case 1:
            return fn_8010B384(Article(it), b);
        default:
            return lbl_803680E8 + 0x3E;
        }
    }
}
void fn_8010FE38(ItemN* it) {
    switch (it->x12) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 13:
        it->fl |= 1;
        break;
    case 5:
        it->fl |= 5;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        it->fl |= 3;
        break;
    case 11:
        it->fl |= 0x10;
        break;
    case 15:
        it->fl |= 0x40;
        break;
    case 16:
        it->fl |= 0xA0;
        break;
    case 14:
        it->fl |= 0x20;
        break;
    }
}
char* fn_8010FECC(u32 k) {
    switch (k) {
    case 0:
        return fn_800D0864(lbl_803680E8 + 0x29e);
    case 1:
        return fn_800D0864(lbl_803680E8 + 0x2a5);
    case 2:
        return fn_800D0864(lbl_803680E8 + 0x2ac);
    case 3:
        return fn_800D0864(lbl_803680E8 + 0x2b3);
    case 4:
        return fn_800D0864(lbl_803680E8 + 0x2ba);
    case 5:
        return fn_800D0864(lbl_803680E8 + 0x2c1);
    case 6:
        return fn_800D0864(lbl_803680E8 + 0x2ca);
    case 7:
        return fn_800D0864(lbl_803680E8 + 0x2d1);
    case 8:
        return fn_800D0864(lbl_803680E8 + 0x2d8);
    case 9:
        return fn_800D0864(lbl_803680E8 + 0x2df);
    case 10:
        return fn_800D0864(lbl_803680E8 + 0x2e6);
    case 11:
        return fn_800D0864(lbl_803680E8 + 0x2ed);
    case 13:
        return fn_800D0864(lbl_803680E8 + 0x2f4);
    case 14:
        return lbl_803680E8 + 0x2FB;
    case 15:
        return lbl_803680E8 + 0x2FE;
    case 16:
        return fn_800D0864(lbl_803680E8 + 0x301);
    }
    return lbl_803680E8 + 0x30A;
}
u8 fn_801107C0(ItemN* it, void* u) {
    u8 r = it->x21;
    switch (it->x12) {
    case 11:
        r = 1;
        break;
    default:
        break;
    }
    if (r == 0xFF) {
        r = (s16)fn_80123998(u) / 2;
        if (r > 15) r = 15;
        if (r < 5) r = 5;
    }
    if (u && fn_8011B77C((u8*)u + 0x12C, lbl_804CA528) && (it->fh & 0x800000)) r = r + 1;
    return r;
}
u8 fn_80110940(void* u) {
    u8 r = fn_80123998(u);
    if (r < 3) r = 3;
    if (r > 30) r = 30;
    return r;
}
}
