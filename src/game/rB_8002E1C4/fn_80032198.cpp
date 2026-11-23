#include "game/rB_8002E1C4/types.h"

/* battle preview window drawing (no lmw/stmw in this part: uses _savegpr) */

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

/* HP panel */
void fn_80032198(BUnit* p, int x, int y, int dhp, int showItems)
{
    int hp;
    int i;
    hp = dhp + p->x114;
    if (hp > fn_801237EC(p)) hp = fn_801237EC(p);
    if (hp < 0) hp = 0;
    fn_80031ED4(x + 0x16, y - 4, 0xde, 0x20);
    fn_8006E030(lbl_804CCD24);
    fn_80074EB4(x + 0x1e, y + 0x12, 0xcc, 0xa0);
    fn_8006E068();
    fn_8006E030(lbl_804CCD24);
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, x + 0x28, y, 9, 1, 0, lbl_80361390 + 0x11c, fn_800D0864(lbl_80361390 + 0x11f));
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, x + 0x78, y, 1, 1, 0, lbl_80361390 + 0x125, hp, fn_801237EC(p));
    fn_8006E030(lbl_804CCD28);
    if (showItems) {
        fn_8006E030(lbl_804CCD24);
        for (i = 0; i < fn_80109174(&p->x110); i++) {
            ((VObj*)&lbl_803E7290)->draw(x + 0xd8, y, fn_801091E0(&p->x110, i));
        }
        fn_8006E030(lbl_804CCD28);
    }
    fn_8006E030(lbl_804CCD28);
}

}
