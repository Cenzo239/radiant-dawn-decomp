#include "game/rI_801DD7D4/fn_fe.h"
extern "C" {
extern s8 lbl_804CAA9C;
extern void* lbl_804CBF90;
extern void* lbl_804CBF94;
FE* fn_8023D9B8(void);
int fn_8023A0BC(FE*, const char*, FE*, int, void*);
void fn_802384F0(FE*, u32);
int fn_80238EE8(FE*);
int fn_8031D34C(void*, void*, int);
int fn_8031D284(void*, void*, int);
void fn_8023BE80(int, int, int, int);
void fn_8023BEF8(void* p, void* arg);
u32 fn_8017F658(u32);
u32 strlen(const char*);
u32 fn_80079088(int);
void fn_8023E264(int, int);
void fn_8023E8EC(int, int);
void* fn_80078D28(int, u32, const char*, u32);
void fn_8007914C(void);
void fn_8023DE84(void);
u32 fn_8030E4C0(void*, int);
void* fn_8030E344(void*, u32, int);
void fn_8017FBCC(u32, u32, void*, FE*);
void fn_802FAED4(void*);
void fn_80320978(s64);
void fn_8023B894(FE*);
void fn_8023B9D8(FE*);
void fn_8023B6C4(FE*);
void fn_80078E24(u32);
void fn_8030E3F4(void*, u32);
void fn_802BC238(void*, FE*);
void fn_8030EC2C(void*, FE*);
void DCFlushRange(u32, u32);
}
class VD { public: virtual void d(int); };
static inline int nextMode(int m) {
    int r = -1;
    switch (m) {
    case 0x2000: r = 0; break;
    case 0: r = 0x1000; break;
    case 0x1000: r = -1; break;
    }
    return r;
}
static inline void evict1(int& h, u32 size, int& m) {
    if (fn_80079088(h) < size) {
        m = 0x2000;
        while (m != -1 && fn_80079088(h) < size) {
            fn_8023E264(h, m);
            m = nextMode(m);
        }
    }
}
static inline void evict2(int& h, u32 size, int& m) {
    if (fn_8030E4C0(lbl_804CBF90, 0x20) < size) {
        m = 0x2000;
        while (m != -1 && fn_8030E4C0(lbl_804CBF90, 0x20) < size) {
            fn_8023E8EC(h, m);
            if (fn_8030E4C0(lbl_804CBF90, 0x20) < size) {
                fn_8023E8EC(-1, m);
            }
            m = nextMode(m);
        }
    }
}
static inline void* tail1(u32 size, const char* hint, int& h, int& p, int& m) {
    h = lbl_804CAA9C;
    p = h;
    evict1(h, size, m);
    p = (int)fn_80078D28(h, -size, hint, size);
    if (p == 0) fn_8007914C();
    return (void*)p;
}
static inline void* tail2(u32 size, int& h, int& p, int& m) {
    h = lbl_804CAA9C;
    p = h;
    evict2(h, size, m);
    p = (int)fn_8030E344(lbl_804CBF90, size, -0x20);
    if (p == 0) fn_8007914C();
    return (void*)p;
}
static inline void* head1(u32 size, const char* hint, int& h, int& p, int& m) {
    h = lbl_804CAA9C;
    p = h;
    evict1(h, size, m);
    p = (int)fn_80078D28(h, size, hint, size);
    if (p == 0) { fn_8007914C(); fn_8023DE84(); }
    return (void*)p;
}
static inline void* head2(u32 size, int& h, int& p, int& m) {
    h = lbl_804CAA9C;
    p = h;
    evict2(h, size, m);
    p = (int)fn_8030E344(lbl_804CBF90, size, 0x20);
    if (p == 0) { fn_8007914C(); fn_8023DE84(); }
    return (void*)p;
}
#define SLP u32& src, u32& sz1, int& n, const char*& hint, u32& sz2, int& hA, int& pA, int& mA, int& hB, int& pB, int& mB, int& hC, int& pC, int& mC, int& hD, int& pD, int& mD
static inline void startLoad(FE* e, SLP) {
    src = e->data;
    e->pos = 0;
    e->flags |= 2;
    if ((e->data & 0xF0000000) != 0x90000000) {
        sz1 = fn_8017F658(src);
        n = strlen(e->name) - 0xf;
        hint = e->name + n;
        if (e->flags & 0x10) {
            void* p = head1(sz1 + 4, hint, hA, pA, mA);
            e->data = (u32)p;
            e->size = sz1;
            ((u32*)((u32)p + 0x40000000))[sz1] = 0;
        } else {
            void* p = head1(sz1, hint, hB, pB, mB);
            e->data = (u32)p;
            e->size = sz1;
        }
    } else {
        sz2 = fn_8017F658(src);
        strlen(e->name);
        if (e->flags & 0x10) {
            void* p = head2(sz2 + 4, hC, pC, mC);
            e->data = (u32)p;
            e->size = sz2;
            ((u32*)((u32)p + 0x40000000))[sz2] = 0;
        } else {
            void* p = head2(sz2, hD, pD, mD);
            e->data = (u32)p;
            e->size = sz2;
        }
    }
    fn_8017FBCC(src, e->data, fn_8023BEF8, e);
}
static inline int flg(FE* e, int m) { return e->flags & m; }
static inline FE* par(FE* e) { return e->parent; }
static inline void dec4(FE* e) { if (flg(e, 0x10000000) != 0) fn_80238EE8(par(e)); --e->rc; }
static inline void dec3(FE* e) { if (flg(e, 0x10000000) != 0) dec4(par(e)); --e->rc; }
static inline void dec2(FE* e) { if (flg(e, 0x10000000) != 0) dec3(par(e)); --e->rc; }
static inline void dec1(FE* e) { if (flg(e, 0x10000000) != 0) dec2(par(e)); --e->rc; }
static inline void dec0(FE* e) { if (flg(e, 0x10000000) != 0) dec1(par(e)); --e->rc; }
static inline void freeData(FE* e, u32 p) {
    if (!p) p = e->data;
    if ((p & 0xF0000000) != 0x90000000) {
        if (!p) p = e->data;
        fn_80078E24(p);
    } else {
        if (!p) p = e->data;
        fn_8030E3F4(lbl_804CBF90, p);
    }
}
struct Msg { s8 type; u8 p1[3]; FE* e; u32 a8; };
extern "C" {
#pragma push
#pragma use_lmw_stmw on
void fn_80238FB8(void) {
/*P*/
    u32 src1;
    FE* s;
    u32 p2;
    u32 f3;
    u32 p3;
    FE* e;
    u32 sz11;
    int mA1;
    const char* hint1;
    int mB1;
    int hA1;
    int pA1;
    int n1;
    int hB1;
    int pB1;
    u32 sz21;
    int hC1;
    int pC1;
    int mC1;
    int hD1;
    int pD1;
    int mD1;
/*E*/
    for (;;) {
        Msg* m = NULL;
        fn_8031D34C(sQ1, &m, 1);
        e = m->e;
        if (e->name[0] != 0) {
            switch (m->type) {
            case 0:
                fn_802384F0(e, m->a8);
                break;
            case 1: {
                dec0(e->a98);
                if ((e->flags & 0x04000000) && !(e->flags & 0x00100000)) {
                    startLoad(e, src1, sz11, n1, hint1, sz21, hA1, pA1, mA1, hB1, pB1, mB1, hC1, pC1, mC1, hD1, pD1, mD1);
                } else {
                    if (e->flags & 0x08000000) fn_8023B6C4(e);
                    DCFlushRange(e->data, e->size);
                    e->flags |= 0x200020;
                }
                break;
            }
            case 2: {
                s = e->a98;
                p2 = m->a8;
                dec0(s);
                if (s->flags & 0x04000000) {
                    if (s->flags & 0x00200000) freeData(s, p2);
                } else {
                    DCFlushRange(s->data, s->size);
                    s->flags |= 0x200000;
                }
                s->flags &= ~4;
                e->flags = (e->flags & ~4) | 0xA80000;
                break;
            }
            case 3: {
                f3 = (e->flags & ~2) | 0x100000;
                p3 = m->a8;
                e->flags = f3;
                if (!(f3 & 4)) freeData(e, p3);
                if (e->flags & 0x08000000) fn_8023B6C4(e);
                DCFlushRange(e->data, e->size);
                e->flags |= 0x200000;
                break;
            }
            }
        }
        fn_8031D284(sQ2, m, 1);
    }
}
#pragma pop
}
