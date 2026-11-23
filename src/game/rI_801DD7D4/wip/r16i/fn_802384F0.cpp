#include "game/rI_801DD7D4/fn_fe.h"
extern "C" {
extern s8 lbl_804CAA9C;
extern void* lbl_804CBF90;
extern void* lbl_804CBF94;
FE* fn_8023D9B8(void);
int fn_8023A0BC(FE*, const char*, FE*, int, void*);
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
    if ((src & 0xF0000000) != 0x90000000) {
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
static inline void freeData(FE* e, u32 p) {
    if ((p & 0xF0000000) != 0x90000000) {
        u32 q = p;
        if (p != 0) q = p;
        fn_80078E24(q);
    } else {
        u32 q = p;
        if (p != 0) q = p;
        fn_8030E3F4(lbl_804CBF90, q);
    }
}
extern "C" {
#pragma push
#pragma use_lmw_stmw on
void fn_802384F0(FE* e) {
/*P*/
    int mD2;
    int n1;
    const char* hint1;
    int mA1;
    int hA1;
    int pA1;
    int mC1;
    int hC2;
    int pB1;
    int mB1;
    int hC1;
    int pC1;
    u32 sz21;
    int mA2;
    int hA2;
    int mD1;
    int n2;
    const char* hint2;
    u32 sz22;
    int pD1;
    int pA2;
    u32 sz12;
    int hD1;
    int hB2;
    int pB2;
    int mB2;
    int hB1;
    int pC2;
    int mC2;
    int hD2;
    int pD2;
    u32 sz11;
    u32 src1;
    u32 src2;
/*E*/
    if (e->flags & 0x40) {
        FE* c;
        e->flags |= 4;
        c = fn_8023D9B8();
        if (c != NULL && fn_8023A0BC(c, e->name, e, 0x80484, fn_8023BE80) != 0) {
            c->a4b = -1;
            if ((e->flags & 0x04000000) && !(e->flags & 0x00100000)) {
                startLoad(e, src1, sz11, n1, hint1, sz21, hA1, pA1, mA1, hB1, pB1, mB1, hC1, pC1, mC1, hD1, pD1, mD1);
            }
            return;
        }
        e->flags &= ~4;
        if (c != NULL && !(c->flags & 0x10000000)) {
            fn_802FAED4(c->task);
            while (!(c->flags & 0x00230000)) {
                fn_80320978((s64)5 * ((*(u32*)0x800000F8 >> 2) / 1000));
                if (c->name[0] == 0) break;
            }
            if (c->name[0] != 0) {
                VO0N* k;
                if (c->flags & 0x00200000) {
                    fn_8023B894(c);
                    fn_8023B9D8(c);
                }
                freeData(c, c->data);
                k = (VO0N*)sLock;
                k->v08();
                if ((c->data & 0xF0000000) != 0x90000000) {
                    fn_802BC238(sA, c);
                } else {
                    fn_802BC238(sB, c);
                }
                k->v10();
                ((VD*)c)->d(-1);
                fn_8030EC2C(lbl_804CBF94, c);
            }
        }
    }
    if ((e->flags & 0x04000000) && !(e->flags & 0x00100000)) {
        startLoad(e, src2, sz12, n2, hint2, sz22, hA2, pA2, mA2, hB2, pB2, mB2, hC2, pC2, mC2, hD2, pD2, mD2);
    } else {
        if (e->flags & 0x08000000) fn_8023B6C4(e);
        DCFlushRange(e->data, e->size);
        e->flags |= 0x200000;
    }
}
#pragma pop
}
