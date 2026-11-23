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
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u16);
#else
void fn_8007E174(s32, u16);
#endif
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
extern "C" {
void fn_802402B0(DrawW* w, void* a) {
    /*P*/
    const char* s;
    int x;
    int y;
    int yy;
/*E*/
    Col4 t1; Col4 t2;
    w->v30();
    w->v18(a);
    fn_8007E154();
    fn_8007E174(0, (u16)(w->flags | 3));
    fn_8007E164();
    Col4 c = {0xA2, 0x7A, 0x5C, 0xFF};
    x = w->x; y = w->y;
    fn_800800D4(5); yy = y + 1;
    pos(x, yy); *(u32*)&t1 = *(u32*)&c; fn_80080508(&t1);
    fn_80080ABC(2.0f, 1); fn_80080A94(0.75f); s = lbl_80372780; fn_80080C24(fn_800D0864(s)); fn_80080308();
    fn_800800D4(5);
    pos(x + 0x108, yy);
    *(u32*)&t2 = *(u32*)&c; fn_80080508(&t2);
    fn_80080ABC(2.0f, 1); fn_80080A94(0.75f); fn_80080C24(fn_800D0864(lbl_80372780 + 0x15)); fn_80080308();
}
}
