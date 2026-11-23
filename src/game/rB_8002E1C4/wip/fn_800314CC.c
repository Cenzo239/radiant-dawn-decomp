/* NEAR MISS: 8 of 75 words, the item index wants r28 and the key r30 (shape shared with 800315F8,
 * 80031728, 80031854 and 800319F8). Local copies, inline layouts and declaration hill-climbing did not help. */
#include "game/rB_8002E1C4/types.h"
#pragma use_lmw_stmw on
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
void fn_801ABBA8(const char* msg, const char* sfx, void* a, int b);
static inline u16 item_index(Item* it)
{
    return it->data ? it->data->x16 : 0;
}
void fn_800314CC(Item* it, void* a, BUnit* u)
{
    char buf[0x80];
    const char* sfx;
    const char* key;

    sfx = lbl_80361390;
    key = lbl_80361390 + 0x11;
    switch (fn_8024BC94()->lang) {
    case 1:
        fn_80290D04(buf, 0x80, lbl_80361390 + 0x1c, fn_801110C4(it, 0), fn_80110F08(it), (u8)item_index(it) + 0x80);
        break;
    default:
        fn_80290D04(buf, 0x80, lbl_80361390 + 0x27, (u8)item_index(it) + 0x80, fn_80110F08(it));
        break;
    }
    fn_800D0B38(0, buf);
    fn_801ABBA8(fn_800D08B4(key, fn_8011B77C(u->x12c, lbl_804CA4DC)), sfx, a, 0);
}
