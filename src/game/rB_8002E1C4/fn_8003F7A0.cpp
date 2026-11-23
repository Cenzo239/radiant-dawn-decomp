extern "C" {
#include "game/rB_8002E1C4/statefn.h"
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
    u32 x0;
    u8 pad4[0x11 - 4];
    u8 x11;
    u8 pad12[0x934 - 0x12];
    f32 x934; /* cursor x */
    f32 x938; /* cursor y */
};
struct MapState {
    u8 pad[0xd];
    u8 grid[64 * 64];
    u8 pad100d[0xd18e - 0x100d];
    u16 xd18e[64 * 64];
};

struct ChapterFlags {
    u32 x0_0 : 8;
    u32 x0_8 : 2;
    u32 x0_rest : 22;
};


struct BState {
    u8 pad[0x448];
    s16 x448;
    u8 pad44a[0x8ea - 0x44a];
    s16 x8ea;
};

extern "C" {
extern Pad* lbl_804CB5B8;
extern GameState lbl_803CAB38;
extern MapState lbl_803EC898;
extern u8 lbl_804CB728;
extern u8* lbl_804CB810;
void fn_80253EE4(const char* name, f32 v);  /* play sound */
void fn_80083DC4(void* proc, int n);

static inline u16 tileD18E(s8 x, s8 y)
{
    return lbl_803EC898.xd18e[x + (y << 6)];
}

void fn_8003F7A0(void* a)
{
    u32 k = lbl_804CB5B8->buttons();
    if ((k & 0x400) && tileD18E(lbl_803CAB38.x934, lbl_803CAB38.x938) != 0) {
        fn_80253EE4(lbl_803615A8 + 0xb, 0.0f);
        lbl_804CB728 = 5;
        fn_80083DC4(a, 0x63);
    } else if (k & 0x800) {
        fn_80253EE4(lbl_803615A8 + 0x58, 0.0f);
        lbl_804CB728 = 9;
        fn_80083DC4(a, 0x63);
    }
}

#if TARGET_PC
FE10_PROTO void fn_80039D6C(MapUnit* u, p32arg);
#else
void fn_80039D6C(MapUnit* u, int n);
#endif
void* fn_800CFD18(void* layer, int n);
void* fn_800CFB0C(void* cell);
void fn_8006214C(GameState* g, void* u);
void fn_801C6EAC(const char* a, const char* b, void* out);
void fn_8023F1A0(void* p, int n);
extern int lbl_803E7320[];

void fn_8003F898(void)
{
    u8 buf[0x68];
    fn_80039D6C(lbl_803CA870.unit, 0);
    if (lbl_803E7320[0] == 0) return;
    void* c = fn_800CFD18(lbl_803E7320, 0);
    fn_8006214C(&lbl_803CAB38, fn_800CFB0C(c));
    fn_801C6EAC(lbl_803615A8 + 0x2f, lbl_803615A8 + 0x46, buf);
    fn_8023F1A0(buf, 0);
}

static inline u8* GetUnit(u8 id)
{
    if (id != 0) {
        return lbl_804CB810 + (id - 1) * 0x3f0;
    }
    return 0;
}

typedef struct ItemTmp { u8 pad[0x28]; } ItemTmp;
void fn_80111B34(ItemTmp* p);
void fn_80111C24(ItemTmp* p, int n);
void fn_80110BFC(ItemTmp* p, const char* name);
int fn_8010E314(u8 a, u8 b);
extern BState lbl_803C8E80;
void fn_80026C44(BState* b, MapUnit* a, u8* d);
void fn_80026E64(BState* b, ItemTmp* it);
void fn_8002742C(BState* b, int n);
ChapterFlags* fn_80060728(GameState* g);
void fn_8003DD6C(void* p, u8* u, int a, int b, int c);
extern u8 lbl_803CA7C0[];

void fn_8003F918(void)
{
    u8* u;
    s8 x = lbl_803CAB38.x934;
    s8 y = lbl_803CAB38.x938;
    int idx = x + (y << 6);
    if (lbl_803EC898.xd18e[idx] == 0) return;
    u = GetUnit(lbl_803EC898.grid[idx]);
    if (u == 0) return;
    if ((u8)fn_8010E314(((u8*)*(void**)(u + 0xf4))[8], lbl_803CAB38.x11) != 1) return;
    {
        ItemTmp it;
        fn_80111B34(&it);
        fn_80110BFC(&it, lbl_803615A8 + 0x68);
        fn_80026C44(&lbl_803C8E80, lbl_803CA870.unit, u);
        fn_80026E64(&lbl_803C8E80, &it);
        fn_8002742C(&lbl_803C8E80, 0xf);
        if (fn_80060728(&lbl_803CAB38)->x0_8 == 0) {
            if (lbl_803C8E80.x448 <= lbl_803C8E80.x8ea)
                lbl_803C8E80.x8ea = lbl_803C8E80.x448 - 1;
        }
        fn_8003DD6C(lbl_803CA7C0, u, 0, 0, 0xff);
        fn_80111C24(&it, -1);
    }
}

void fn_8013F1C4(void);
void fn_80081194(void* a, void* b);
extern u8 lbl_80379760[];
extern s8 lbl_804CB2A0;
typedef struct StateObj18 { u32 x0; void* desc; u8 pad[0x10]; } StateObj18;
extern StateObj18 lbl_803CA828;
extern u8 lbl_80379850[];

void fn_8003FA9C(void* a)
{
    if (((u8*)&lbl_803CA870)[0xc] == 0x32) {
        fn_8013F1C4();
        fn_80081194(lbl_80379760, a);
    } else {
        fn_80039D6C(lbl_803CA870.unit, 0);
        if (!lbl_804CB2A0) INIT_GC(lbl_804CB2A0, lbl_803CA828, lbl_80379850);
        fn_800D042C(&lbl_803CA828, a);
    }
}

void* fn_8010B228(const char* name);
void fn_80039AE4(MapUnit* u, void* t);
extern s8 lbl_804CB2A1;
extern StateObj18 lbl_803CA840;
extern u8 lbl_80379818[];

void fn_8003FB34(void* a)
{
    MapUnit* u = lbl_803CA870.unit;
    fn_80039AE4(u, fn_8010B228(lbl_803615A8 + 0x73));
    if (!lbl_804CB2A1) INIT_GC(lbl_804CB2A1, lbl_803CA840, lbl_80379818);
    fn_800D042C(&lbl_803CA840, a);
}

void fn_8003B3DC(MapUnit* u, int n);
extern u8 lbl_80383AF0[];

#define SIMPLE_FN(name, guard, obj, n) \
    extern s8 guard; \
    extern StateObj obj; \
    void name(void* a) \
    { \
        fn_8003B3DC(lbl_803CA870.unit, n); \
        if (!guard) { \
            obj.desc = lbl_80383AF0; \
            guard = 1; \
        } \
        fn_800D042C(&obj, a); \
    }

SIMPLE_FN(fn_8003FBC0, lbl_804CB2A2, lbl_804CB2A8, 0xc)
SIMPLE_FN(fn_8003FC28, lbl_804CB2B0, lbl_804CB2B8, 0xd)
}
