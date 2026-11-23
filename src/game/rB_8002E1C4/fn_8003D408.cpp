extern "C" {
#include "game/rB_8002E1C4/statefn.h"

void fn_8003B04C(MapUnit* u, void* t);

STATE_FN(fn_8003D408, INIT_CG, lbl_804CB268, lbl_804CB270, lbl_80379AC8, fn_8003B04C(lbl_803CA870.unit, TARGET))
}

class Pad {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual u32 buttons(); /* +0x48 */
};

struct GameState {
    u8 pad[0x934];
    f32 x934; /* cursor x */
    f32 x938; /* cursor y */
};
struct MapState {
    u8 pad[0x710e];
    s16 x710e[64 * 64];
};

extern "C" {
extern Pad* lbl_804CB5B8;
extern GameState lbl_803CAB38;
extern MapState lbl_803EC898;
extern u8 lbl_804CB728;
void fn_80253EE4(const char* name, f32 v);  /* play sound */
void fn_80083DC4(void* proc, int n);

static inline s16 tileAt(s8 x, s8 y)
{
    return lbl_803EC898.x710e[x + (y << 6)];
}

void fn_8003D484(void* a)
{
    u32 k = lbl_804CB5B8->buttons();
    if ((k & 0x400) && tileAt(lbl_803CAB38.x934, lbl_803CAB38.x938) >= 0) {
        fn_80253EE4(lbl_803615A8 + 0xb, 0.0f);
        lbl_804CB728 = 5;
        fn_80083DC4(a, 0x63);
    } else if (k & 0x800) {
        lbl_804CB728 = 9;
        fn_80083DC4(a, 0x63);
    }
}

void fn_8013F204(RangeState* s);
void fn_8006214C(GameState* g, MapUnit* u);

void fn_8003D564(void)
{
    s8 y = lbl_803CAB38.x938;
    s8 x = lbl_803CAB38.x934;
    lbl_803CA870.x14 = y;
    lbl_803CA870.x13 = x;
    fn_8013F204(&lbl_803CA870);
    fn_8006214C(&lbl_803CAB38, lbl_803CA870.unit);
}
}
