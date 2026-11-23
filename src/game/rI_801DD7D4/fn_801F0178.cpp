#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
extern char lbl_8041EB20[];
int fn_801A2224(void*);
void fn_801A1CFC(void*);
void fn_801A1F64(void*, void*, f32, f32);
typedef struct LN { struct LN* prev; struct LN* next; void* val; } LN;
class VF { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(int); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual u32 v48();
};
struct Slot { int size; LN* prev; LN* next; };
struct Tw { u8 pad[0x34]; RList list; s16 x40; u8 p42[2]; int x44; };
struct Pt { s16 x, y; };
static inline VF* back(Tw* o) { return o->list.size != 0 ? (VF*)o->list.prev->val : NULL; }
static inline LN* adv(LN* it, s16 n) {
    if (n >= 0) {
        for (; n > 0; n--) it = it->next;
    } else {
        for (; n < 0; n++) it = it->prev;
    }
    return it;
}
struct WS { u8 pad[0x68]; s16 cur[0x10]; Slot sl[4]; };
static inline Pt mk(u32 r) { Pt p; p.x = r >> 16; p.y = r; return p; }
#define ATS(name, SZ, CU) \
static inline void** name(VF* w, int i) { \
    u8* c; u8* s; \
    c = (u8*)w + i * 2; \
    s = (u8*)w + i * 12; \
    if (*(int*)(s + SZ) == 0) return NULL; \
    { \
        s16 n = *(s16*)(c + CU); \
        LN* it = adv(*(LN**)(s + SZ + 8), n); \
        return &it->val; \
    } \
}
#define PICK(fn, base) \
void fn(Tw* o) { \
    void** v; \
    o->x40 = 0; \
    back(o)->v30(o->x44); \
    if (fn_801A2224(lbl_8041EB20) != 0) { \
        VF* w; \
        if (o->list.size != 0) w = (VF*)o->list.prev->val; else w = NULL; \
        { \
        v = base(w, w->v34()); \
        } \
        if (v != NULL) { \
            Pt q = mk(back(o)->v48()); \
            fn_801A1F64(lbl_8041EB20, *v, q.x, q.y); \
        } else { \
            fn_801A1CFC(lbl_8041EB20); \
        } \
    } \
}
ATS(at0, 0x88, 0x68)
ATS(at1, 0x74, 0x5e)
ATS(at2, 0x80, 0x64)
ATS(at3, 0x98, 0x70)
PICK(fn_801F0178, at0)
PICK(fn_801F0908, at1)
PICK(fn_801F1098, at2)
PICK(fn_8020029C, at3)
}
