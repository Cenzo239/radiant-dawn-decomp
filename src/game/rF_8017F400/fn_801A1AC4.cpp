#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct TIp { u8 p0[0xC4]; void* xC4; u8 pC8[0x14]; f32 xDC, xE0; u8 pE4[0x10]; f32 xF4, xF8; u8 pFC[0x10]; f32 x10C, x110; };
struct Proc { u8 pad[0x2E]; u8 x2E; };
extern u8 lbl_80388A70[0x20];
extern u8 lbl_8041EB20[0x124];
extern char lbl_8036CA00[];
extern Proc* fn_80083B84(u8*);
extern void fn_80081050(u8*, void*);
extern void* memset(void*, int, u32);
extern void fn_801C6EAC(const char*, const char*, char*);
extern void fn_800068A0(void**, const char*);
extern void fn_80253EE4(const char*, f32);
extern void fn_801A1DCC(TIp*, const char*, f32, f32);
extern void fn_801A1F64(TIp*, void*, f32, f32);
static inline BOOL Alive(void) { Proc* h = fn_80083B84(lbl_80388A70); if (h == 0) return 0; return h->x2E == 0; }
static inline void Open(TIp* p, f32 x, f32 y) {
    char buf[0x60];
    char* b = lbl_8036CA00;
    p->xDC = x;
    p->xE0 = y;
    p->xF4 = x;
    p->xF8 = y;
    p->x10C = 0.0f;
    p->x110 = 0.0f;
    fn_801C6EAC(b + 0x6F, b + 0x80, buf);
    fn_800068A0(&p->xC4, buf);
    fn_80253EE4(b + 0x85, 0.0f);
}
void fn_801A1AC4(TIp* p, void* parent, const char* s, f32 x, f32 y) {
    if (Alive()) return;
    fn_80081050(lbl_80388A70, parent);
    memset(lbl_8041EB20, 0, 0x124);
    Open(p, x, y);
    fn_801A1DCC(p, s, x, y);
}
void fn_801A1BE0(TIp* p, void* parent, void* s, f32 x, f32 y) {
    if (Alive()) return;
    fn_80081050(lbl_80388A70, parent);
    memset(lbl_8041EB20, 0, 0x124);
    Open(p, x, y);
    fn_801A1F64(p, s, x, y);
}
}
