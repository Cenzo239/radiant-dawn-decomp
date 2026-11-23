/* fn_801080CC: skill list row. Level: regs (the recomputed highlight flag sits
   in r28 here, r26 in the original; 2 words). From wip/fn_801080CC.cpp with the
   capacity test written as the original has it: `a = lv <= have;` inside the
   `if (a)` and `hl = a != 0;` after it (the draft set hl inside the if, which
   needed a narrowing at the call). Also holds the matched fn_80107AE0. */
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
void fn_8007E174(int a, int b);
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

char* fn_8011A054(ItemD*);
int fn_80127A90(void*);
int fn_8011B8A4(void*);
struct FD { u8 pad[0x1E]; u8 x1e; u8 x1f; };
struct UU { u8 pad[0x12C]; u8 skills[1]; };
#pragma use_lmw_stmw on
static inline u8 Lv(Slot* s) { return s->f02 ? 0 : ((FD*)s->item)->x1e; }
static inline u8 Lv2(Slot* s) { return (*((u8*)s + 5) & 2) ? 0 : ((FD*)s->item)->x1e; }
void fn_801080CC(Slot* s, int a, int x, int y, UU* u) {
    u32 hl;
    u8 k;
    if (s->item == 0) return;
    if (s->f01) ICONS->v4(x - 0x18, y + 2, 0x59);
    hl = a != 0;
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_800CB278(x + 0x23, y + 2, hl, lbl_80367F40, fn_8011A054(s->item));
    if (Lv(s) && u == 0) {
        fn_800CB278(x + 0xB6, y + 2, hl, lbl_80367F40 + 0xC, Lv(s));
    }
    k = ((FD*)s->item)->x1f;
    if (k) ICONS2->v4(x, y, k);
    if (u && Lv(s)) {
        if (a) {
            int have;
            int lv = Lv(s);
            have = fn_80127A90(u) - fn_8011B8A4(u->skills);
            if (have < 0) have = 0;
            a = lv <= have;
        }
        hl = a != 0;
        fn_8007E154();
        fn_8007E174(0, 0x13);
        fn_8007E164();
        fn_800CB278(x + 0xB6, y + 2, hl, lbl_80367F40 + 0xC, Lv2(s));
    }
}
}
