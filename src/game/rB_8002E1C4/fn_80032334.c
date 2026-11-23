#include "game/rB_8002E1C4/types.h"

/* Compiled as C: in C++ mode the compiler CSEs the address of lbl_804CCD2C
 * instead of using four @sda21 byte loads. */

extern const char lbl_80361390[0x200];
extern const f32 lbl_804CCD24; /* -1.0f */
extern const f32 lbl_804CCD28; /* 1.0f */
void fn_80031ED4(int x, int y, int w, int h);
void fn_8006E030(f32 a);
void fn_8006E068(void);

typedef struct GXColor { u8 r, g, b, a; } GXColor;
struct PersonData { u8 pad[0x107]; s8 x107; s8 x108; };
extern GXColor lbl_804CCD2C;
extern const f32 lbl_804CCD30; /* 0.8f */
extern const f32 lbl_804CCD34; /* 2.0f */
extern void* lbl_804CA4EC;
void fn_800800D4(int a);
void fn_80080330(f32 x, f32 y);
void fn_80080508(GXColor* c);
void fn_80080A94(f32 a);
void fn_80080ABC(f32 a, int b);
#if TARGET_PC
FE10_PROTO void fn_80080C24(char *);
#else
void fn_80080C24(int a);
#endif
void fn_80080308(void);
int fn_8011B77C(void* skills, void* sid);
s8 fn_80123AC4(BUnit* p);
s8 fn_80122990(BUnit* p);
s8 fn_8012255C(BUnit* p);
s8 fn_80123BF0(BUnit* p);
s8 fn_80122AA0(BUnit* p);
s8 fn_801225AC(BUnit* p);
void fn_801C6E64(f32 x, f32 y, const char* key, int a, int b, int c, int d, int e);

/* skill/speed panel */
void fn_80032334(
#if TARGET_PC
BUnit* p, int x, int y, char* icon
#else
BUnit* p, int x, int y, int icon
#endif
)
{
    int base;
    GXColor c;
    fn_80031ED4(x + 0x16, y, 0xde, 0x55);
    fn_8006E030(lbl_804CCD24);
    fn_8006E068();
    fn_800800D4(5);
    fn_80080330(x + 0x22, y + 4);
    c = lbl_804CCD2C;
    fn_80080508(&c);
    fn_80080A94(lbl_804CCD30);
    fn_80080ABC(lbl_804CCD34, 1);
    fn_80080C24(icon);
    fn_80080308();
    *(unsigned long long*)&p->x108 |= 2ULL;
    base = p->xf0->x107;
    fn_801C6E64(x + 0x1e, y + 0x1a, lbl_80361390 + 0x135, fn_8012255C(p), fn_80122990(p), fn_80123AC4(p),
                base, fn_8011B77C(p->x12c, lbl_804CA4EC));
    base = p->xf0->x108;
    fn_801C6E64(x + 0x1e, y + 0x36, lbl_80361390 + 0x13d, fn_801225AC(p), fn_80122AA0(p), fn_80123BF0(p),
                base, fn_8011B77C(p->x12c, lbl_804CA4EC));
    *(unsigned long long*)&p->x108 &= ~2ULL;
    fn_8006E030(lbl_804CCD28);
}
