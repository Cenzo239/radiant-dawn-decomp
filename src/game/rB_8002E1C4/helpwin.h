#ifndef HELPWIN_H
#define HELPWIN_H
/* Declarations and macros shared by the help-window files (from fn_80032B88.cpp). */
#include "game/rB_8002E1C4/types.h"

/* Help windows drawn over a unit. Each starts from the same inlined head:
 * background frame, HP line, then the item icons of the unit's skills. */

extern const char lbl_80361390[0x200];
extern const f32 lbl_804CCCF4; /* 0.0f */
extern const f32 lbl_804CCD24; /* -1.0f */
extern const f32 lbl_804CCD28; /* 1.0f */

struct VBase { u8 pad[0x44]; };
struct VObj : VBase {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void draw(int x, int y, void* item);
};
struct WSub { u8 pad[8]; u8 b8; };
extern void* lbl_804CA4EC;
extern "C" {
extern VObj lbl_803E7290;
s16 fn_801237EC(BUnit* p);                 /* max HP */
void fn_80031ED4(int x, int y, int w, int h); /* draw frame */
void fn_8006E030(f32 a);
void fn_80074EB4(int x, int y, int w, int h);
void fn_8006E068(void);
const char* fn_800D0864(const char* key);
void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, int c, int d, int e, const char* fmt, ...);
int fn_80109174(void* list);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_801091E0(void* list, int i);
#else
void* fn_801091E0(void* list, int i);
#endif
void fn_800718F0(BUnit* p, int a, int b, int c);
void fn_800718D0(int a, int x, int w, int h, u8 k, int d);
void fn_80032198(BUnit* p, int x, int y, int dhp, int showItems);
void fn_80032334(BUnit* p, int x, int y, const char* s);
void fn_80032A34(int kind, int x, int y);
void fn_80032B88(BUnit* p, int kind, int x, int y, int dhp);
s8 fn_8012401C(BUnit* p);
s8 fn_80124144(BUnit* p);
s16 fn_80123BF0(BUnit* p);
u8 fn_801076D0(BUnit* p);
u8 fn_8010779C(BUnit* p, f32 bio);
f32 fn_801072E4(BUnit* p);
f32 fn_80107444(BUnit* p);
f32 fn_801071C4(BUnit* p, s16 n);
void fn_800327D8(u8 a, int b, int c, int d);
void fn_80032CD0(BUnit* p, int a, int b, int c);
int fn_8012B120(BUnit* p, void* it);
int fn_8011F0E0(BUnit* p, void* it);
int fn_80111F5C(void* it);
void fn_80107C80(void* it, u8 c, int a, int b);
s8 fn_80123EF0(BUnit* p);
s8 fn_80122D30(BUnit* p);
s8 fn_8012269C(BUnit* p);
int fn_8011B77C(void* list, void* key);
void fn_801C6E64(f32 x, f32 y, const char* s, int a, int b, int c, int d, int e);
void fn_80032560(int x, int y, u8 k);
const char* fn_80118C44(void* job);
int fn_800CA3DC(const char* s, int n, f32 a);
void fn_800CB278(s16 x, s16 y, int c, const char* s, ...);
int fn_8007265C(int x, int y);
void fn_8007E154(void);
void fn_8007E174(void* tex, int a);
void fn_8007E164(void);
}
#define WIN_FRAME(p, h) \
    fn_800718F0(p, 0, 0, 1); \
    fn_800718D0(0, 0x24, 0x108, h, ((WSub*)p->xf4)->b8, 0x9a); \
    fn_8006E030(lbl_804CCD24); \
    fn_8006E068();
#define WIN_HP(p, x, y) \
    fn_80074EB4(x + 0x1e, y + 0x12, 0xcc, 0xa0); \
    fn_8006E068(); \
    fn_8006E030(lbl_804CCD24); \
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, x + 0x28, y, 9, 1, 0, lbl_80361390 + 0x11c, fn_800D0864(lbl_80361390 + 0x11f)); \
    { int v = p->x114; fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, x + 0x78, y, 1, 1, 0, lbl_80361390 + 0x125, v, fn_801237EC(p)); } \
    fn_8006E030(lbl_804CCD28);
#define WIN_ITEMS(p, y) \
    fn_8006E030(lbl_804CCD24); \
    for (i = 0; i < fn_80109174(&p->x110); i++) { \
        ((VObj*)&lbl_803E7290)->draw(0xd8, y, fn_801091E0(&p->x110, i)); \
    } \
    fn_8006E030(lbl_804CCD28);
#define WIN_HEAD(p, h) \
    WIN_FRAME(p, h) \
    WIN_HP(p, 0, 0x34) \
    WIN_ITEMS(p, 0x34)

#endif
