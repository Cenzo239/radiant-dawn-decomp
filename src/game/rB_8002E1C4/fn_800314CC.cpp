#include "game/rE_800E5DE4/types.h"
#pragma use_lmw_stmw on
#pragma inline_max_size(4000)
extern const char lbl_80361390[0x200];
extern void* lbl_804CA4DC;
typedef struct SysInfo { u8 pad[0x1bc8]; s8 lang; } SysInfo;
struct ItemD { u8 pad[0x16]; u16 x16; };
struct Item { ItemD* data; };
struct BU { u8 pad[0x12c]; u8 x12c[4]; };
extern "C" {
SysInfo* fn_8024BC94(void);
const char* fn_80110F08(Item* it);
const char* fn_801110C4(Item* it, int a);
int fn_80290D04(char* buf, int n, const char* fmt, ...);
void fn_800D0B38(int idx, const char* s);
int fn_8011B77C(void* skills, void* sid);
const char* fn_800D08B4(const char* key, int a);
#if TARGET_PC
FE10_PROTO void fn_801ABBA8(const char* msg, ptr32<const void>, void* a, int b);
#else
void fn_801ABBA8(const char* msg, const char* sfx, void* a, int b);
#endif
static inline u16 item_index(Item* it) {
    return it->data ? it->data->x16 : 0;
}
#define FAM(body, name, SFXDECL, SFXINIT, KEY, SFXARG, LAST) \
static inline void body(Item* it, void* a, BU* u, u16& ix) { \
    SFXDECL \
    const char* key; \
    const char* nm; \
    char buf[0x80]; \
    SFXINIT \
    key = KEY; \
    switch (fn_8024BC94()->lang) { \
    case 1: \
        ix = item_index(it); \
        nm = fn_80110F08(it); \
        fn_80290D04(buf, 0x80, lbl_80361390 + 0x1c, fn_801110C4(it, 0), nm, (u8)ix + 0x80); \
        break; \
    default: \
        ix = item_index(it); \
        fn_80290D04(buf, 0x80, lbl_80361390 + 0x27, (u8)ix + 0x80, fn_80110F08(it)); \
        break; \
    } \
    fn_800D0B38(0, buf); \
    fn_801ABBA8(fn_800D08B4(key, fn_8011B77C(u->x12c, lbl_804CA4DC)), SFXARG, a, LAST); \
} \
void name(Item* it, void* a, BU* u) { u16 ix; body(it, a, u, ix); }
#define SD const char* sfx;
FAM(b1, fn_800314CC, SD, sfx = lbl_80361390;, sfx + 0x11, sfx, 0)
FAM(b2, fn_800315F8, SD, sfx = lbl_80361390 + 0x30;, lbl_80361390 + 0x42, sfx, 1)
FAM(b3, fn_80031728, SD, sfx = lbl_80361390;, sfx + 0x4d, sfx, 0)
FAM(b4, fn_80031854, SD, sfx = lbl_80361390 + 0x30;, lbl_80361390 + 0x58, sfx, 1)
FAM(b5, fn_800319F8, , , lbl_80361390 + 0x83, 0, 0)
}
