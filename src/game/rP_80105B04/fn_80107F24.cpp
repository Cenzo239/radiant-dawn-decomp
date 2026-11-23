/* Shop list row with a price column: the price, or the "--" text when the
   item cannot be sold (names guessed). Round 21, exact: the x and y arguments
   go through two s16 locals before the colour is chosen. */
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



static inline int HlCol2(int a) { int c = 0; if (a) c = 0x20; return c; }
static inline u8 HlCol(int a) { u8 c = 0; if (a) c = 0x20; return c; }
void fn_80107F24(Slot* s, int a, int x, int y) {
    char buf[0x10];
    BOOL r;
    s16 w;
    int c;
    if (s->item == 0) return;
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    r = 1;
    if ((*fn_801116B8(s) & 0x0002000000000000ULL) == 0 && s->f10 == 0) r = 0;
    if (r) {
        strcpy(buf, lbl_80367F40 + 0x17);
    } else {
        fn_80290DDC(buf, lbl_80367F40 + 0x12, fn_80111094(s));
    }
    {
    s16 px = x + (0x12C - (s16)fn_800CA3DC(buf, -1, 1.0f));
    s16 py = y;
    c = 0;
    if (a) c = 0x20;
    fn_800CB278(px, py, c, buf);
    }
    fn_80107AE0(s, a, x, y, 1, (char*)1);
}
}
