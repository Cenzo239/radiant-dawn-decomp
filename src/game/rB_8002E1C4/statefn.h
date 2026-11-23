#ifndef RB_STATEFN_H
#define RB_STATEFN_H
#include "game/rB_8002E1C4/types.h"

/* Map-action range setup (0x8003CA20..0x8003DCAC): highlight the range,
 * then start a menu/state object with fn_800D042C. Each object is a C++
 * local static of a class derived from a base with a vtable at +4: the
 * inlined constructors store the base vtable (a dead store) and then the
 * real one. Writing both stores is what gives the original register
 * choice. lbl_StateBaseVt never appears in the output. */

typedef struct MapUnit MapUnit;
typedef struct RangeState {
    MapUnit* unit;
    u32 x4;
    u8 pad8[6];
    s8 xe;
    u8 padf[0x13 - 0xf];
    u8 x13;
    u8 x14;
    u8 pad15[2];
    u8 x17;
    u8 pad[0x130 - 0x18];
} RangeState;
extern RangeState lbl_803CA870;
void* fn_800D042C(void* a, void* b);
void** fn_80044FD0(RangeState* s);

typedef struct Sprite {
    u8 pad[8];
    s16 x8;
    u8 pada[0x18 - 0xa];
    u32 flags;
} Sprite;
typedef struct Effect {
    u8 pad[0x30];
    Sprite* x30;
} Effect;
Effect* fn_800E3C04(const char* name, void* p);
void fn_800E4AD4(Effect* e, f32 v);
extern char lbl_803615A8[];

typedef struct StateObj {
    u32 x0;
    void* desc;
} StateObj;
typedef struct MidStateObj {
    u32 x0;
    void* desc;
    Effect* x8;
} MidStateObj;
typedef struct BigStateObj {
    u32 x0;
    void* desc;
    int x8;
    Effect* xc;
} BigStateObj;

extern u8 lbl_StateBaseVt[];
#define CTOR(o, d) ((o)->desc = lbl_StateBaseVt, (o)->desc = (d))

#define INIT_CG(guard, obj, dsc) do { CTOR(&obj, dsc); guard = 1; } while (0)
#define INIT_GC(guard, obj, dsc) do { guard = 1; CTOR(&obj, dsc); } while (0)

#define TARGET (*fn_80044FD0(&lbl_803CA870))

/* plain: obj = {x0, desc}. MID_FN/BIG_FN take one of statefn_bss.h's objects. */
#define STATE_FN(name, INIT, guard, obj, dsc, call) \
    extern s8 guard; \
    extern StateObj obj; \
    extern u8 dsc[]; \
    void name(void* a) \
    { \
        call; \
        if (!guard) INIT(guard, obj, dsc); \
        fn_800D042C(&obj, a); \
    }

/* with an arrow effect at +8 */
#define MID_FN(name, INIT, guard, obj, dsc, call) \
    extern s8 guard; \
    extern u8 dsc[]; \
    void name(void* a) \
    { \
        call; \
        if (!guard) INIT(guard, obj, dsc); \
        obj.x8 = fn_800E3C04(lbl_803615A8, fn_800D042C(&obj, a)); \
        obj.x8->x30->flags |= 4; \
        fn_800E4AD4(obj.x8, 0.03f); \
        obj.x8->x30->x8 = 0x14; \
    }

/* with a value at +8 and an arrow effect at +0xC */
#define BIG_FN(name, INIT, guard, obj, dsc, call, setval) \
    extern s8 guard; \
    extern u8 dsc[]; \
    void name(void* a) \
    { \
        call; \
        if (!guard) INIT(guard, obj, dsc); \
        setval; \
        obj.xc = fn_800E3C04(lbl_803615A8, fn_800D042C(&obj, a)); \
        obj.xc->x30->flags |= 4; \
        fn_800E4AD4(obj.xc, 0.03f); \
        obj.xc->x30->x8 = 0x14; \
    }

#endif
