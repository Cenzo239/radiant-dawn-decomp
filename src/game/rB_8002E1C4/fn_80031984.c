#include "game/rB_8002E1C4/types.h"

#pragma use_lmw_stmw on

/* string pool: "SFX_FF_ITEM_GET1", "MNT_GETI_P", "%s%s#P%03X", "#P%03X%s",
 * "SFX_FF_ITEM_LOST1", "MNT_GETI_E", "MNT_STLI_P", "MNT_STLI_E", "MNT_SENDI", ... */
extern const char lbl_80361390[0x200];
extern void* lbl_804CA4DC;

typedef struct SysInfo { u8 pad[0x1bc8]; s8 lang; } SysInfo;
SysInfo* fn_8024BC94(void);
const char* fn_80110F08(Item* it);          /* item name */
const char* fn_801110C4(Item* it, int a);   /* item article/prefix */
int fn_80290D04(char* buf, int n, const char* fmt, ...); /* snprintf */
void fn_800D0B38(int idx, const char* s);    /* set message argument */
int fn_8011B77C(void* skills, void* sid);
const char* fn_800D08B4(const char* key, int a);
const char* fn_800D0864(const char* key);
#if TARGET_PC
FE10_PROTO void fn_801ABBA8(const char* msg, unsigned int, void* a, int b);
#else
void fn_801ABBA8(const char* msg, const char* sfx, void* a, int b);
#endif

static inline u16 item_index(Item* it)
{
    return it->data ? it->data->x16 : 0;
}

void fn_80031984(int n, void* a)
{
    char buf[0x80];
    fn_80290D04(buf, 0x80, lbl_80361390 + 0x77, n);
    fn_800D0B38(0, buf);
    fn_801ABBA8(fn_800D0864(lbl_80361390 + 0x7a), lbl_80361390, a, 0);
}


typedef struct LevelUp {
    u8 pad[0x22];
    s8 hp, str, mag, skl, spd, lck, def, res, x2a, con;
} LevelUp;

/* single stat-up message */
void fn_80031C38(LevelUp* l, void* a)
{
    const char* key;
    if (l->hp) key = lbl_80361390 + 0xb4;
    else if (l->str) key = lbl_80361390 + 0xbb;
    else if (l->mag) key = lbl_80361390 + 0xc3;
    else if (l->skl) key = lbl_80361390 + 0xcc;
    else if (l->spd) key = lbl_80361390 + 0xd5;
    else if (l->lck) key = lbl_80361390 + 0xdf;
    else if (l->def) key = lbl_80361390 + 0xe8;
    else if (l->res) key = lbl_80361390 + 0xf0;
    else if (l->con) key = lbl_80361390 + 0xf9;
    else if (l->x2a) key = lbl_80361390 + 0x103;
    fn_801ABBA8(fn_800D0864(key), lbl_80361390, a, 2);
}

u16 fn_800CEABC(u8 type);
int fn_80290DDC(char* buf, const char* fmt, ...); /* sprintf */
char* fn_80291110(char* d, const char* s);         /* strcat */

static inline void add_wtype_icon(char* out, u8 type)
{
    char tmp[16];
    fn_80290DDC(tmp, lbl_80361390 + 0x10b, fn_800CEABC(type) - 1);
    fn_80291110(out, tmp);
}

/* weapon level up message */
void fn_80031D8C(s8 t1, void* a, s8 t2, s8 t3, s8 t4)
{
    char out[0x40];
    out[0] = 0;
    add_wtype_icon(out, t1);
    if (t2 >= 0) add_wtype_icon(out, t2);
    if (t3 >= 0) add_wtype_icon(out, t3);
    if (t4 >= 0) add_wtype_icon(out, t4);
    fn_800D0B38(0, out);
    fn_801ABBA8(fn_800D0864(lbl_80361390 + 0x112), lbl_80361390, a, 2);
}
