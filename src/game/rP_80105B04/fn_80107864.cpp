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

void fn_80107864(Out7* o, void* u, f32 x) {
    BioParam* p;
    f32 t[5];
    o->v[4] = 0;
    o->v[3] = 0;
    o->v[2] = 0;
    o->v[1] = 0;
    o->v[0] = 0;
    o->v[6] = 0;
    o->v[5] = 0;
    p = (BioParam*)fn_80077064(lbl_80367F28);
    Tab(t, 1.0f);
    if (x < t[0]) p++;
    if (x < t[1]) p++;
    if (x <= t[3]) p++;
    if (x <= t[4]) p++;
    o->v[2] = p->b[0];
    o->v[3] = p->b[1];
    o->v[4] = p->b[2];
    o->v[5] = p->b[3];
    o->v[6] = p->b[4];
    if (fn_8011B77C(u, lbl_804CA6CC)) {
        o->v[0] = o->v[0] * 2;
        o->v[1] = o->v[1] * 2;
        o->v[2] = o->v[2] * 2;
        o->v[3] = o->v[3] * 2;
        o->v[4] = o->v[4] * 2;
        o->v[5] = o->v[5] * 2;
        o->v[6] = o->v[6] * 2;
    }
    if (fn_8011B77C(u, lbl_804CA6D0)) {
        o->v[0] = o->v[0] / 2;
        o->v[1] = o->v[1] / 2;
        o->v[2] = o->v[2] / 2;
        o->v[3] = o->v[3] / 2;
        o->v[4] = o->v[4] / 2;
        o->v[5] = o->v[5] / 2;
        o->v[6] = o->v[6] / 2;
    }
}

#pragma use_lmw_stmw on
void fn_80107AE0(Slot* s, int a, int x, int y, int icon, char* nums);
static inline BOOL Flag(Slot* s) {
    BOOL r = 1;
    if ((*fn_801116B8(s) & 0x0100000000000000ULL) == 0 && s->f04 == 0) r = 0;
    return r;
}

void fn_80107C80(Slot* s, int a, int x, int y) {
    if (s->item == 0) return;
    if (s->f80 && Flag(s)) {
        ICONS->v4(x - 0x12, y, 0x79);
    } else if (s->f80) {
        ICONS->v4(x - 0x12, y, 0x57);
    } else if (Flag(s)) {
        ICONS->v4(x - 0x12, y, 0x7B);
    }
    fn_80107AE0(s, a, x, y, 1, (char*)1);
}

#pragma use_lmw_stmw on
void fn_80108048(Slot* s, int a, int x, int y) {
    if (s->item) fn_80107AE0(s, a, x, y, 1, 0);
}
void fn_80108064(Slot* s, int a, int x, int y) {
    if (s->item) fn_80107AE0(s, a, x, y, 0, 0);
}
void fn_80108080(Slot* s, int x, int y, int d) {
    if (s->item == 0) return;
    ICONS->v5(x, y, (u8)(s->item ? s->item->icon : 0) + 0x81, d, 0xFF, 0x258);
}
}
