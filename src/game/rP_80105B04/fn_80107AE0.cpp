#include "game/rP_80105B04/slot.h"

struct BioParam { f32 v; u8 b[8]; };
struct Out7 { s8 v[7]; };
extern "C" {
extern char lbl_80367F28[];
extern char lbl_80367F40[];
extern void* lbl_804CA6CC;
extern void* lbl_804CA6D0;
extern u8 lbl_803CAB38[];
void* fn_80077064(const char* name);
int fn_8011B77C(void* skills, void* id);
void fn_8007E154();
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int b);
#else
void fn_8007E174(int a, int b);
#endif
void fn_8007E164();
void fn_800CB278(s16 x, s16 y, u8 c, const char* fmt, ...);
int fn_80290DDC(char* buf, const char* fmt, ...);
int fn_800CA3DC(const char* s, int n, f32 k);
int fn_800626E0(void* game);
int fn_80111094(Slot* s);
char* strcpy(char* a, const char* b);

static inline void Tab(f32* out, f32 k) {
    BioParam* p = (BioParam*)fn_80077064(lbl_80367F28);
    out[0] = p[0].v * k;
    out[1] = p[1].v * k;
    out[2] = p[2].v * k;
    out[3] = p[3].v * k;
    out[4] = p[4].v * k;
}

#pragma use_lmw_stmw on
void fn_80107AE0(Slot* s, int a, int x, int y, int icon, char* nums);
static inline BOOL Flag(Slot* s) {
    BOOL r = 1;
    if ((*fn_801116B8(s) & 0x0100000000000000ULL) == 0 && s->f04 == 0) r = 0;
    return r;
}

#pragma use_lmw_stmw on

static inline BOOL Flag14(Slot* s) {
    BOOL r = 1;
    if ((*fn_801116B8(s) & 0x0002000000000000ULL) == 0 && s->f10 == 0) r = 0;
    return r;
}
void fn_80107AE0(Slot* s, int a, int x, int y, int icon, char* nums) {
    int c2;
    u32 hl = a != 0;
    u32 c;
    c2 = 0;
    if (a) c2 = 0xC;
    c = hl;
    if (hl == 1) {
        if (s->f20) c = 4;
        if (s->f10) c = 0x40;
    }
    if (s->f40) c = 3;
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_800CB278(x + 0x18, y, c, lbl_80367F40, fn_80110F08(s));
    if ((*fn_801116B8(s) & 0x0001000000000040ULL) == 0 && !s->f10 && nums) {
        fn_800CB278(x + 0xA8, y, hl, (nums = lbl_80367F40) + 5, s->uses);
        fn_800CB278(x + 0xCB, y, c2, nums + 0xC, s->item ? s->item->maxUses : 0);
    }
    if (icon) {
        ICONS->v4(x, y, (u8)(s->item ? s->item->icon : 0) + 0x81);
    }
}



static inline int PriceCol(Slot* s, int a, f32 k) {
    int c = 0;
    int price;
    if (a) c = 0x20;
    price = (int)(k * (f32)fn_80111074(s));
    if (fn_800626E0(lbl_803CAB38) < price) c = 0;
    return c;
}
static inline u8 HlCol(int a) { u8 c = 0; if (a) c = 0x20; return c; }
}
