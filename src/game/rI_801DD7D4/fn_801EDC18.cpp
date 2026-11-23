#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {
extern char lbl_8036F03C[];
extern char lbl_8036EFBC[];
extern VO0N* lbl_804CB5B8;
void fn_80253EE4(const char*, f32);
void fn_801E1CC0(void*, int);

class LW {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
};
#define F16(p, off) (*(s16*)((u8*)(p) + (off)))
#define INP(fn, sz, rows, cu, sm, snd) \
void fn(LW* o) { \
    u8* c; \
    int i = o->v34(); \
    s16 n; \
    c = (u8*)o + i * 2; \
    n = *(u32*)((u8*)o + i * 12 + sz); \
    if (n == 0) { \
        F16(c, 0x58) = 0; \
        F16(c, cu) = 0; \
    } else { \
        s16 rw = F16(o, rows); \
        if (!inputBlocked()) { \
            int k = lbl_804CB5B8->v3C(); \
            int k2 = lbl_804CB5B8->v48(); \
            s16 old = F16(c, cu); \
            if ((s16)(int)*(f32*)((u8*)o + sm) == 0) { \
                if (k & 0x800008) { \
                    if (old == 0) { \
                        if (k == k2) { \
                            F16(c, cu) = n - 1; \
                            F16(c, 0x58) = n > rw ? n - rw : 0; \
                        } \
                    } else { \
                        F16(c, cu) = old - 1; \
                        if (F16(c, cu) > 0 && F16(c, cu) - F16(c, 0x58) == 0) { \
                            F16(c, 0x58)--; \
                            *(f32*)((u8*)o + sm) = -28.0f; \
                        } \
                    } \
                    if (old != F16(c, cu)) { \
                        fn_80253EE4(snd, 0.0f); \
                    } \
                } else if (k & 0x400004) { \
                    int last = n - 1; \
                    if (old == last) { \
                        if (k == k2) { \
                            F16(c, cu) = 0; \
                            F16(c, 0x58) = 0; \
                        } \
                    } else { \
                        F16(c, cu) = old + 1; \
                        if (F16(c, cu) < last && rw - 1 == F16(c, cu) - F16(c, 0x58)) { \
                            F16(c, 0x58)++; \
                            *(f32*)((u8*)o + sm) = 28.0f; \
                        } \
                    } \
                    if (old != F16(c, cu)) { \
                        fn_80253EE4(snd, 0.0f); \
                    } \
                } \
            } \
        } \
        fn_801E1CC0(*(void**)((u8*)o + 0x4c), (s16)(F16(c, 0x58) * 0x1c - (int)*(f32*)((u8*)o + sm))); \
    } \
}
INP(fn_801FF9F0, 0x98, 0x8e, 0x70, 0x90, lbl_8036F03C + 0x2af)
INP(fn_801EDC18, 0x88, 0x7e, 0x68, 0x80, lbl_8036EFBC + 0xd)
INP(fn_801EEC20, 0x74, 0x6a, 0x5e, 0x6c, lbl_8036EFBC + 0xd)
INP(fn_801EFC28, 0x80, 0x76, 0x64, 0x78, lbl_8036EFBC + 0xd)

typedef void (RObj::*MF)(int);
typedef struct FnT { MF f; int arg; } FnT;
struct RL2 { int size; LNode* prev; LNode* next; };
static inline FnT forEach(LNode* n, LNode* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
    return f;
}
extern MF lbl_8038DDB0;
extern MF lbl_8038D070;
extern MF lbl_8038D094;
extern MF lbl_8038D0F0;
extern MF lbl_8038DDA4;
extern MF lbl_8038D064;
extern MF lbl_8038D088;
extern MF lbl_8038D0E4;
class MW {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C();
    virtual int v50(); virtual int v54(); virtual int v58(int, int, int, int, int);
    u8 pad[0x3c];
    RL2 l;
};
#define FOREACH(fn, tbl) \
void fn(MW* o, int arg) { \
    FnT g; \
    ((VO0N*)o)->v24(); \
    g.f = tbl; \
    g.arg = arg; \
    forEach(o->l.next, (LNode*)&o->l.prev, g); \
}
FOREACH(fn_801EDE3C, lbl_8038D070)
FOREACH(fn_801EEE44, lbl_8038D094)
FOREACH(fn_801EFE4C, lbl_8038D0F0)
FOREACH(fn_801FFC14, lbl_8038DDB0)

typedef struct KB { u8 pad[0x2d]; u8 x2d; u8 x2e; u8 pad2f[5]; RList l; } KB;
static inline BOOL kbTest(KB* a) { return a->x2d != 0 || a->x2e != 0; }
int fn_8028DB44(int);
int fn_800CB0FC(int, f32);
void fn_800712E8(int, int, int);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7E8(int);
}
