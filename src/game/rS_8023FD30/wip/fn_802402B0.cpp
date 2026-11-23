#include "game/rS_8023FD30/types.h"
/* Column headers of the talk list. */
struct Col4 { u8 r, g, b, a; };
class DrawW {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18(void*);
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    u8 pad04[0x1E - 4];
    s16 x;
    s16 y;
    u8 pad22[0x38 - 0x22];
    u32 flags;
};
extern "C" {
void fn_8007E154(void);
void fn_8007E174(s32, u16);
void fn_8007E164(void);
void fn_800800D4(s32);
void fn_80080330(f32, f32);
void fn_80080508(Col4*);
void fn_80080ABC(f32, s32);
void fn_80080A94(f32);
const char* fn_800D0864(const char*);
void fn_80080C24(const char*);
void fn_80080308(void);
extern char lbl_80372780[];
}
static inline void setCol(Col4 c) { fn_80080508(&c); }
static inline void pos(int x, int y) { fn_80080330(x, y); }
static inline void txt(const char* s) {
    fn_80080ABC(2.0f, 1);
    fn_80080A94(0.75f);
    fn_80080C24(fn_800D0864(s));
    fn_80080308();
}
extern "C" {
void fn_802402B0(DrawW* w, void* a) {
    w->v30();
    w->v18(a);
    fn_8007E154();
    fn_8007E174(0, (u16)(w->flags | 3));
    fn_8007E164();
    Col4 c = {0xA2, 0x7A, 0x5C, 0xFF};
    int x = w->x;
    int y0 = w->y;
    fn_800800D4(5);
    pos(x, y0 + 1);
    setCol(c);
    txt(lbl_80372780);
    fn_800800D4(5);
    pos(x + 0x108, y0 + 1);
    setCol(c);
    txt(lbl_80372780 + 0x15);
}
}
/* WIP: column header draw. Calls and order fit. The colour local belongs at 0x8 and its two by-value
   copies at 0x10 and 0xC, and the y load should reuse r31 with y+1 in r29. */
