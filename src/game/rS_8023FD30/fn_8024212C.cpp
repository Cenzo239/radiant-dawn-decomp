#include "game/rS_8023FD30/types.h"
/* Talk list proc update: tracks the current row, handles confirm, help and cancel input. */
struct Pt16 { s16 x, y; };
class Item {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual int v20();
};
class ListW {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual u32 v30();
};
class Pad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual u32 v3C(); virtual void v40(); virtual void v44(); virtual u32 v48();
};
extern "C" {
extern u32 lbl_804CB700;
extern Pad* lbl_804CB5B8;
extern u32 lbl_8041EB20[];
extern char lbl_803728A8[];
ListW* fn_801E5640(void*, s32, s32);
Item* fn_80240868(ListW*);
void fn_801E5954(void*);
BOOL fn_801A2224(u32*);
void* fn_80240804(ListW*);
void fn_801A1DCC(u32*, void*, f32, f32);
void fn_801E6B64(const char*, void*, f32, f32);
void fn_80083B78(void*);
void fn_80253EE4(const char*, f32);
void fn_801A1AC4(u32*, void*, void*, f32, f32);
void fn_801A1CFC(u32*);
void fn_80083DC4(void*, s32);
}
static inline BOOL inputBlocked() {
    u32 a = *(volatile u32*)&lbl_804CB700;
    u32 b = *(volatile u32*)&lbl_804CB700;
    BOOL r = 0;
    if ((a & 0x10) && !(b & 0x20)) r = 1;
    return r;
}
static inline Pt16 mk(u32 r) { Pt16 t; t.x = r >> 16; t.y = r; return t; }
extern "C" {
void fn_8024212C(void* proc) {
    ListW* a = fn_801E5640(proc, 0x81, 0);
    Item* cur = fn_80240868(a);
    fn_801E5954(proc);
    if (cur != fn_80240868(a)) {
        cur = fn_80240868(a);
        if (fn_801A2224(lbl_8041EB20)) {
            Pt16 p = mk(a->v30()); fn_801A1DCC(lbl_8041EB20, fn_80240804(a), p.x, p.y);
        }
    }
    if (!inputBlocked()) {
        u32 k = lbl_804CB5B8->v48();
        if ((k & 0x400) && !fn_801A2224(lbl_8041EB20)) {
            if (cur->v20()) {
                Pt16 p = mk(a->v30()); fn_801E6B64(lbl_803728A8 + 0x25, proc, p.x, p.y);
            } else {
                fn_80083B78(proc);
                fn_80253EE4(lbl_803728A8 + 0x37, 0.0f);
            }
        } else if ((k & 0x2000) && !fn_801A2224(lbl_8041EB20)) {
            Pt16 p = mk(a->v30()); fn_801A1AC4(lbl_8041EB20, proc, fn_80240804(a), p.x, p.y);
            lbl_8041EB20[0] |= 2;
        } else if ((k & 0x2800) && fn_801A2224(lbl_8041EB20)) {
            fn_801A1CFC(lbl_8041EB20);
        } else if ((k & 0x800) && !fn_801A2224(lbl_8041EB20)) {
            fn_80083DC4(proc, 7);
            fn_80253EE4(lbl_803728A8 + 0x47, 0.0f);
        }
    }
}
}
