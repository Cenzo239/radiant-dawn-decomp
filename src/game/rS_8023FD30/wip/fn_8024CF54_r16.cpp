#include "game/rS_8023FD30/types.h"
/* The manager statics as in sndmgr.h, split further where this function addresses a block
   directly from the pool base: the heap at +0x28, the two effect blocks at +0x38C and +0x524,
   the thread at +0xA18 and its stack at +0xD30, and the message buffer at +0x1D50. */
class SndLockable {
public:
    SndLockable();
    virtual void lock();   /* +0x08 */
    virtual void v0C();
    virtual void unlock(); /* +0x10 */
    u8 pad04[0x28 - 4];
};
struct SndFader {
    s32 t;
    s32 frames;
    f32 cur;
    f32 from;
    f32 to;
};
struct SndCmd {
    u8 type;
    s8 busy;
    s8 cancel;
    u8 pad03;
    s32 result;
    u32 id;
    u32 arg;
};
class SndPlayer;
static SndLockable sMutex;          /* +0x000 lbl_8042E798 */
static u8 sHeap[0x60 - 0x28];        /* +0x028 */
static u8 sMember60[0x98 - 0x60];    /* +0x060 */
static u8 sPad098[0xFC - 0x98];      /* +0x098 */
static u8 sGroups[0x288 - 0xFC];     /* +0x0FC */
static u8 sPad288[0xC];
static u8 sEffect[0xC];              /* +0x294 effect state */
static u8 sEffect2[0x38C - 0x2A0];
static u8 sEffA[0x14];               /* +0x38C lbl_8042EB24 */
static u8 sEffA2[0x524 - 0x3A0];
static u8 sEffB[0x5F0 - 0x524];      /* +0x524 lbl_8042ECBC */
static SndPlayer* sPoolA[4];        /* +0x5F0 */
static SndPlayer* sPoolB[16];       /* +0x600 */
static SndPlayer* sPoolC[16];       /* +0x640 */
static SndPlayer* sPoolD[4];        /* +0x680 */
static SndFader sFaderDefault;      /* +0x690 */
static SndFader sFader6A4;
static SndFader sFader6B8;
static SndFader sFader6CC;
static SndFader sFader6E0;
static SndFader sFader6F4;
static SndFader sFader708;
static SndFader sFader71C;
static SndFader sFader730;
static SndFader sFader744;
static SndFader sChanA[8];          /* +0x758 */
static SndFader sChanB[8];          /* +0x7F8 */
static SndFader sChanC[8];          /* +0x898 */
static SndFader sChanD[8];          /* +0x938 */
static SndFader sFader9D8;
static SndFader sFader9EC;
static SndFader sFaderA00;
static u8 sPadA14[4];
static u8 sThread[0xD30 - 0xA18];    /* +0xA18 OSThread */
static u8 sStack[0x1000];           /* +0xD30 */
static u8 sCmdQueue[0x20];          /* +0x1D30 OSMessageQueue */
static u8 sCmdMsgs[0x1DB0 - 0x1D50]; /* +0x1D50 its buffer */
static u8 sCmdMutex[0x20];          /* +0x1DB0 */
static SndCmd sCmds[24];            /* +0x1DD0 */
extern "C" {
extern char lbl_80391888[];
}
struct SndGuard {
    void* vt;
    SndLockable* m;
    SndGuard(SndLockable& x) {
        vt = lbl_80391888;
        m = &x;
        x.lock();
    }
    ~SndGuard() {
        vt = lbl_80391888;
        m->unlock();
    }
};
/* Sound manager start-up: resets every fader and pool, sets up the heap, the sound groups,
   the effect and reverb blocks, the command queue, and starts the sound thread. */
struct FlagSet {
    u32 pad;
    u32 w[1];
};
struct SndParams {
    f32 a, b, c, d, e, f;
    s32 g;
    f32 h;
    s32 i;
    f32 j, k;
};
struct SndParams2 {
    f32 a, b, c, d, e;
};
struct LinkNode {
    LinkNode* next;
    LinkNode* prev;
};
struct LinkIt {
    LinkNode* node;
};
extern "C" void fn_802BC3D4(void*, LinkIt, LinkNode*);
extern "C" void fn_8029C20C(const char*, int, const char*, ...);
extern "C" char lbl_803918B8[];
extern "C" char lbl_80391894[];
struct LinkList {
    u32 size;
    LinkNode node;
    LinkIt endIter() {
        LinkIt it;
        it.node = &node;
        return it;
    }
    static LinkNode* nodeOf(void* p) {
        if (p == 0) {
            fn_8029C20C(lbl_803918B8, 0x233, lbl_80391894);
        }
        return (LinkNode*)((u8*)p + 0x50);
    }
    void pushBack(void* p) {
        LinkIt it = endIter();
        fn_802BC3D4(this, it, nodeOf(p));
    }
};
struct Obj60 {
    u8 pad[0xC];
    LinkList list;
    u32 m18;
    u32 m1C;
};
extern "C" {
extern FlagSet lbl_804CBFE8;
extern void* lbl_804CBFD8;
extern void* lbl_804CBFDC;
extern void* lbl_804CBFE0;
extern void* lbl_804CBFE4;
extern u8 lbl_804CBFF0;
extern void* lbl_804CBFF4;
extern s32 lbl_804CBFF8;
extern u8 lbl_8041F080[];
void fn_8024CCF8(void*);
void fn_802BCE78(int);
void fn_802BDC48(void);
void* fn_80075FB4(void*, u32);
void fn_802B22CC(int, int);
void* fn_8030ECD8(void*, u32);
void* fn_8030E294(void*, u32, int);
void* fn_8030E344(void*, u32, s32);
void fn_802A48C0(void*, void*);
void fn_802A4B88(void*, void*, u32);
void fn_802A4C10(void*, void*, u32);
u32 fn_802AF4BC(void*, void*);
u32 fn_802AF5EC(void*, void*);
void fn_802AF3B8(void*, void*, void*, u32, void*, u32);
u32 fn_802ACEB8(void*, void*);
void fn_802ACF0C(void*, void*, void*, u32);
void fn_80312318(void*);
void fn_802ACC94(void*, void*);
void fn_802ACE4C(void*, f32);
void fn_802ACE54(void*, f32);
void fn_802ACE5C(void*, f32);
void fn_802A6534(void*, SndParams*);
u32 fn_802A63E0(void*);
void fn_802A640C(void*, void*, u32);
void* fn_8029C7D8(void);
int fn_8029D1E4(void*, s32, void*);
void fn_8029D3E8(void*, s32, s32);
void fn_802A610C(void*, SndParams2*);
u32 fn_802A5FB8(void*);
void fn_802A5FE4(void*, void*, u32);
void fn_802B16E0(void*, void*, u32);
void* memset(void*, int, u32);
void fn_8031D224(void*, void*, int);
int fn_8031FC48(void*, void (*)(void*), void*, void*, u32, int, int);
int fn_803202B0(void*);

static inline void finit(SndFader& f, f32 v) {
    f.t = f.frames = 0;
    f.cur = f.from = f.to = v;
}

static inline void* heapAlloc(u32 size) {
    SndGuard l(sMutex);
    return fn_8030E344(lbl_804CBFDC, size, 0x20);
}

#define CLEAR(arr, n, m, i) \
    m = &sMutex; \
    for (i = 0; i < n; i++) { \
        m->lock(); \
        if ((s8)i >= 0 && (s8)i < n) { \
            arr[(s8)i] = 0; \
        } \
        m->unlock(); \
    }

#define EFF_A sEffA
#define EFF_B sEffB
#define MEM28 sHeap
void fn_8024CF54(void* heap, void* arc) {
/*P*/
    u32 n1;
    u32 n2;
    Obj60* g;
    int i1;
    SndLockable* m1;
    SndLockable* m2;
    SndLockable* m3;
    SndLockable* m4;
    int i;
    int i2;
    int i3;
    int i4;
/*E*/
    lbl_804CBFD8 = 0;
    lbl_804CBFDC = 0;
    finit(sFader6A4, 1.0f);
    finit(sFader6B8, 1.0f);
    finit(sFader6CC, 1.0f);
    finit(sFader6E0, 0.0f);
    finit(sFader6F4, 0.0f);
    finit(sFader708, 1.0f);
    finit(sFader71C, 1.0f);
    finit(sFader730, 1.0f);
    finit(sFader744, 1.0f);
    {
        SndFader* a = sChanA; SndFader* b = sChanB; SndFader* d = sChanD; SndFader* c = sChanC;
        for (s16 k = 0; k < 8; k++, a++, b++, c++, d++) {
            finit(*a, 1.0f); finit(*b, 1.0f); finit(*c, 1.0f); finit(*d, 1.0f);
        }
    }
    finit(sFader9D8, 1.0f);
    finit(sFader9EC, 1.0f);
    finit(sFaderA00, 1.0f);
    lbl_804CBFF4 = 0;
    lbl_804CBFE8.w[0] = 0;
    lbl_804CBFF0 = 0;
    CLEAR(sPoolA, 4, m1, i1)
    CLEAR(sPoolB, 16, m2, i2)
    CLEAR(sPoolC, 16, m3, i3)
    CLEAR(sPoolD, 4, m4, i4)
    fn_802BCE78(0);
    fn_802BDC48();
    lbl_804CBFD8 = fn_80075FB4(heap, 0x880);
    fn_802B22CC(4, 3);
    lbl_804CBFDC = fn_8030E294(fn_8030ECD8(lbl_8041F080, 0x180000), 0x180000, 4);
    fn_802A48C0(sGroups, arc);
    {
        n1 = *(u32*)(sGroups + 0x124);
        void* mem = heapAlloc(n1);
        fn_802A4B88(sGroups, mem, n1);
    }
    {
        n2 = *(u32*)(sGroups + 0x11C);
        void* mem = heapAlloc(n2);
        fn_802A4C10(sGroups, mem, n2);
    }
    {
        u32 n1 = fn_802AF4BC(sEffect, sGroups);
        u32 n2 = fn_802AF5EC(sEffect, sGroups);
        void* m1 = heapAlloc(n1);
        void* m2 = heapAlloc(n2);
        fn_802AF3B8(sEffect, sGroups, m1, n1, m2, n2);
    }
    {
        u32 n = fn_802ACEB8(sMember60, sGroups);
        void* mem = heapAlloc(n);
        fn_802ACF0C(sMember60, sGroups, mem, n);
    }
    {
        g = (Obj60*)sMember60;
        g->m1C = 0x20;
        u8 lis[0x38];
        fn_80312318(lis);
        g->list.pushBack(sPad098);
        fn_802ACC94(sPad098, lis);
    }
    fn_802ACE4C(sPad098, sFader9D8.cur);
    fn_802ACE54(sPad098, sFader9EC.cur);
    fn_802ACE5C(sPad098, sFaderA00.cur);
    {
        SndParams p;
        p.a = 0.02f;
        p.b = 3.0f;
        p.c = 0.6f;
        p.d = 0.4f;
        p.e = 0.1f;
        p.f = 1.0f;
        p.g = 5;
        p.h = 0.02f;
        p.i = 0;
        p.j = 0.0f;
        p.k = 1.0f;
        fn_802A6534(EFF_A, &p);
        u32 n = fn_802A63E0(EFF_A);
        lbl_804CBFE0 = heapAlloc(n);
        fn_802A640C(EFF_A, lbl_804CBFE0, n);
        fn_8029D1E4(fn_8029C7D8(), 0, EFF_A);
    }
    {
        SndParams2 p;
        p.a = 10.0f;
        p.b = 0.5f;
        p.c = 1.0f;
        p.d = 0.0f;
        p.e = 1.0f;
        fn_802A610C(EFF_B, &p);
        u32 n = fn_802A5FB8(EFF_B);
        lbl_804CBFE4 = heapAlloc(n);
        fn_802A5FE4(EFF_B, lbl_804CBFE4, n);
        fn_8029D1E4(fn_8029C7D8(), 1, EFF_B);
    }
    fn_8029D3E8(fn_8029C7D8(), 2, 0);
    fn_802B16E0(MEM28, fn_8030ECD8(lbl_8041F080, 0x1800000), 0x1800000);
    lbl_804CBFF8 = 0;
    memset(sCmds, 0, 0x180);
    fn_8031D224(sCmdQueue, sCmdMsgs, 0x18);
    fn_8031FC48(sThread, fn_8024CCF8, 0, sStack + 0x1000, 0x1000, 0x12, 1);
    fn_803202B0(sThread);
}
}
