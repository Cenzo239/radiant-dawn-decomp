#include "game/rS_8023FD30/types.h"
/* Scrolling list window helpers. */
struct ListWin {
    u8 pad00[0xA];
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 v12;
    s16 v14;
    s16 v16;
    s16 v18;
    u8 pad1A[4];
    s16 v1E;
    s16 v20;
    u8 pad22[0x56 - 0x22];
    s16 cursor;
    u8 pad58[4];
    s16 top;
    u8 pad5E[0x6C - 0x5E];
    u32 count;
};
struct Pt16 { s16 x, y; };
class UObj {
public:
    virtual void v08();
    virtual const char* v0C();
};
struct UProc {
    u8 pad00[0x40];
    const char* v40;
    u32 v44;
    u8 pad48[0x64 - 0x48];
    const char* v64;
};
struct UWin {
    u8 pad00[8];
    s16 x;
    s16 y;
    u8 pad0C[0x24 - 0xC];
    u8 v24;
};
extern "C" {
extern char lbl_803728A8[];
extern char lbl_80390F88[];
extern char lbl_803910B8[];
u32* fn_801E2204(ListWin*, void*, Pt16*);
UProc* fn_801E5640(void*, s32, s32);
UObj* fn_80240868(UProc*);
void* fn_800D0864(const char* s);
void fn_800D0B38(s32, void*);
#if TARGET_PC
FE10_PROTO UWin* fn_801E041C(p32arg, p32arg);
#else
UWin* fn_801E041C(s32, s32);
#endif
void fn_800D5448(UWin*, void*, s32);
UProc* fn_80081194(void*, void*);
void fn_801E4094(UProc* p);

void fn_8024076C(ListWin* w, u32 i) {
    u32 n = w->count;
    if (i > n - 1) {
        i = (s16)(n - 1);
    }
    if ((int)i < 0) {
        i = 0;
    }
    if (n <= 7) {
        w->cursor = i;
        w->top = 0;
        return;
    }
    int top = w->top;
    if (n - top < 7) {
        w->cursor = i;
        w->top = n - 7;
        return;
    }
    if (top < (int)i && (int)(i - top) < 6) {
        w->cursor = i;
        return;
    }
    if (i == 0) {
        w->top = i;
        w->cursor = i;
        return;
    }
    w->cursor = i;
    w->top = i - 1;
}
void fn_80242430(void* self) {
    UProc* a = fn_801E5640(self, 0x81, 0);
    UProc* b = fn_801E5640(self, 0x80, 0);
    fn_800D0B38(0, fn_800D0864(fn_80240868(a)->v0C()));
    const char* s = lbl_803728A8;
    b->v40 = s + 0x57;
    UWin* w = fn_801E041C(0, 0);
    w->x = 0x180;
    w->y = 0x1B;
    w->v24 = 1;
    fn_800D5448(w, self, 0);
    const char* h = s + 0x69;
    UProc* c = fn_801E5640(self, -0x1000, 0);
    if (c) {
        c->v64 = h;
    }
}
UProc* fn_80242850(void* parent) {
    UProc* p = fn_80081194(lbl_80390F88, parent);
    if (p) {
        fn_801E4094(p);
        p->v40 = lbl_803910B8;
        p->v44 = 0;
    }
    return p;
}
}
