#ifndef RB_ACTWIN_H
#define RB_ACTWIN_H
#include "game/rB_8002E1C4/types.h"

/* Range-action windows (0x800409E8..0x80041AA0). The window object is a
 * C++ class with a member at +0 and its vtable at +4; vtable slot +8 gets
 * the window position and colour. */

struct Sprite {
    u8 pad[0x18];
    u32 flags;
};
struct Effect {
    u8 pad[0x30];
    Sprite* x30;
};
struct MapUnit;
struct Ctx {
    u8 pad[0x3e];
    s8 x3e;
    s8 x3f;
    void* x40;
};
struct RangeState {
    MapUnit* unit;
    u8 pad4[0x130 - 4];
};
struct Pos { s8 x; s8 y; };
struct MapState {
    u8 pad[0x710e];
    s16 x710e[64 * 64];
};

class Win8 {
public:
    u32 x0;
    virtual void getPos(int* x, int* y, int* col);
    Effect* x8;
};

extern "C" {
extern RangeState lbl_803CA870;
extern MapState lbl_803EC898;
extern int lbl_803E7320[];
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E4E4(f32 x, f32 y, f32 a, f32 b);
void fn_8007E7DC(u8 c);
MapUnit* fn_800CFB0C(void* p);
void fn_800E48AC(Effect* e, f32 x, f32 y, f32 z);
Pos* fn_800CFD18(void* layer, int i);
void fn_80114B44(MapState* m, int a, int b);
void fn_8013F1C4(void);
}

/* reset the move layer and mark every highlighted tile */
#define TILE_FN(name) \
    void name(void) \
    { \
        int i; \
        fn_80114B44(&lbl_803EC898, 6, -1); \
        fn_80114B44(&lbl_803EC898, 9, 0); \
        for (i = 0; i < lbl_803E7320[0]; i++) { \
            Pos* p = fn_800CFD18(lbl_803E7320, i); \
            lbl_803EC898.x710e[p->x + (p->y << 6)] = 1; \
        } \
        fn_8013F1C4(); \
    }

/* draw the window body and an arrow effect at +8 */
#define DRAW8_FN(name, body) \
    void name(Win8* self, Ctx* c) \
    { \
        int x, y, col; \
        self->x8->x30->flags |= 0x10; \
        if (c->x40 == 0) return; \
        self->getPos(&x, &y, &col); \
        fn_8007E154(); \
        fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f); \
        fn_8007E7DC(col); \
        fn_8007E164(); \
        body(fn_800CFB0C(c->x40)); \
        self->x8->x30->flags &= ~0x10; \
        fn_800E48AC(self->x8, x + 0xa4, y + 0x8a, 0.0f); \
        fn_8007E154(); \
        fn_8007E7DC(0xff); \
        fn_8007E164(); \
    }

/* draw the window body only */
#define DRAW_FN(name, body) \
    void name(Win8* self, Ctx* c) \
    { \
        int x, y, col; \
        if (c->x40 == 0) return; \
        self->getPos(&x, &y, &col); \
        fn_8007E154(); \
        fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f); \
        fn_8007E7DC(col); \
        fn_8007E164(); \
        body(fn_800CFB0C(c->x40)); \
        fn_8007E154(); \
        fn_8007E7DC(0xff); \
        fn_8007E164(); \
    }

#endif
