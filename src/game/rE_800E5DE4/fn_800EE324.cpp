#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct Popup {
    u8 pad[0x30];
    void* font;   /* 0x30 */
    Vec pos;      /* 0x34 */
    u8 pad40[8];
    f32 f48;      /* 0x48 */
    u8 pad4C[4];
    s32 alpha;    /* 0x50 */
    s32 y;        /* 0x54 */
    s32 n;        /* 0x58 */
} Popup;

extern "C" {
extern const f32 lbl_804CD9B8;
#if TARGET_PC
extern FE10_PROTO void fn_80011B90(p32arg, Vec*, Vec*);
#else
extern void fn_80011B90(int, Vec*, Vec*);
#endif
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_8007E7DC(u8);
extern void fn_8007E7F4(void);
extern void fn_80176B54(int, int, int, GXColor*, int, int, int, int, int, int);

static const GXColor kc0 = {0xFF, 0xA0, 0xA0, 0xFF};
static const GXColor kc1 = {0xA0, 0xFF, 0xA0, 0xFF};
static const GXColor kc2 = {0xFF, 0xFF, 0xFF, 0xFF};

static inline void Set(GXColor& o, GXColor v) { o = v; }
static inline void Set2(GXColor& o, GXColor v) { Set(o, v); }
static inline void Body(Popup* p, int n, const Vec& v, GXColor c) {
    if (n < 0) {
        n -= n * 2;
        Set(c, kc0);
    } else {
        Set2(c, kc1);
    }
    fn_8007E154();
    fn_8007E4E4(v.x, v.y + p->f48, (f32)p->y, lbl_804CD9B8);
    fn_8007E374(p->font, 0x1B, 0x11);
    fn_8007E7DC(p->alpha);
    fn_8007E164();
    fn_80176B54(0, 0, 2, &c, 0, 0, 0x18, 0x20, 0x10, n);
    fn_8007E7F4();
}
void fn_800EE324(Popup* p) {
    int n = p->n;
    Vec v;
    fn_80011B90(0, &p->pos, &v);
    Body(p, n, v, kc2);
}
}
