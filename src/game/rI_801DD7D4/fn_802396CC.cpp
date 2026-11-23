/* Archive/file entry manager: open an entry from the disc (DVDOpen-style task at +0x6C), allocate its
   buffer and start the first read. Same allocation inlines as fn_8023AC14.cpp. */
#include "game/rI_801DD7D4/fn_fe.h"
extern "C" {
extern s8 lbl_804CAA9C;
extern void* lbl_804CBF90;
extern void* lbl_804CBF94;
extern char lbl_80372758[];
void fn_8023B5B0(FE*, const char*);
char* fn_80291314(const char*, int);
int fn_80291188(const char*, const char*);
u64 OSGetTime(void);
u64 fn_8028C418(u64, u64);
u32 strlen(const char*);
u32 fn_80079088(int);
void fn_8023E264(int, int);
void fn_8023E8EC(int, int);
void* fn_80078D28(int, u32, const char*, u32);
void fn_8007914C(void);
void fn_8023DE84(void);
u32 fn_8030E4C0(void*, int);
#if TARGET_PC
FE10_PROTO void* fn_8030E344(ptr32<const void>, u32, int);
#else
void* fn_8030E344(void*, u32, int);
#endif
void fn_80320978(s64);
void fn_802BC1C8(void*, FE*);
#if TARGET_PC
FE10_PROTO int fn_8023835C(u32, u32, u32, int, ptr32<const void>, ptr32<const void>);
#else
int fn_8023835C(u32, u32, u32, int, void*, FE*);
#endif
int fn_8023AB4C(FE* e);
static inline int flg(FE* e, int m) { return e->flags & m; }
static inline FE* par(FE* e) { return e->parent; }
static inline void inc4(FE* e) { if (flg(e, 0x10000000) != 0) fn_8023AB4C(par(e)); ++e->rc; }
static inline void inc3(FE* e) { if (flg(e, 0x10000000) != 0) inc4(par(e)); ++e->rc; }
static inline void inc2(FE* e) { if (flg(e, 0x10000000) != 0) inc3(par(e)); ++e->rc; }
static inline void inc1(FE* e) { if (flg(e, 0x10000000) != 0) inc2(par(e)); ++e->rc; }
static inline void inc0(FE* e) { if (flg(e, 0x10000000) != 0) inc1(par(e)); ++e->rc; }
}
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
static inline BOOL hasExt(const char* name, const char* const& ext) {
    char* p = fn_80291314(name, '.');
    if (p != NULL) return fn_80291188(p, ext) == 0;
    return 0;
}
static inline u32 getFl(const char* name) {
    u32 x = 0;
    if (hasExt(name, lbl_80372758)) x |= 0x0C000000;
    if (hasExt(name, lbl_80372758 + 5)) x |= 0x08000000;
    if (hasExt(name, lbl_80372758 + 10)) x |= 0x04000000;
    return x;
}
extern "C" {
#pragma push
#pragma use_lmw_stmw on
struct DI { u8 p[0x34]; u32 a34; };
struct FI { u8 p[0x2c]; FE* user; };
int fn_802F6718(const char*, void*);
int fn_802F6BA8(void*, u32, u32, int, void*, int);
void fn_8023BB70(void* p, void* arg);
#if TARGET_PC
FE10_PROTO void fn_8023BD70(ptr32<const void>, void* arg);
#else
void fn_8023BD70(void* p, void* arg);
#endif
u32 fn_8025F520(void*, const char*);
#if TARGET_PC
FE10_PROTO void fn_8025F598(void*, const char*, p32arg, void*, void*);
#else
void fn_8025F598(void*, const char*, u32, void*, void*);
#endif
extern u32 lbl_804CAA98;
static inline u32 maxRead() { return lbl_804CAA98; }
static inline u32 const& mn(u32 const& a, u32 const& b) { return b < a ? b : a; }
int fn_802396CC(FE* e, const char* name, u32 fl) {
/*P*/
    u32 size;
    u32 len;
    u32 x;
    int hB;
    void* task;
    int n1;
    int mB;
    int n2;
    const char* hint2;
    int mE;
    int pA;
    int mA;
    u32 lim;
    int pB;
    const char* hint1;
    int hC;
    int pC;
    int mC;
    int hD;
    int pD;
    int mD;
    int hE;
    int pE;
    int hA;
    int hF;
    int pF;
    int mF;
    int hG;
    int pG;
    int mG;
    int hH;
    int pH;
    int mH;
/*E*/
    fn_8023B5B0(e, name);
    e->a4b = lbl_804CAA9C;
    x = getFl(name);
    e->flags |= fl | x;
    e->a58 = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2);
    task = e->task;
    ((FI*)task)->user = e; /* e->a98: userData of the DVD command block at +0x6C */
    if (fn_802F6718(e->name, task) == 0) fn_8023DE84();
    size = (((DI*)task)->a34 + 0x1f) & ~0x1f;
    len = size;
    if (flg(e, 0x04000100)) {
        if (!(e->flags & 0x80)) {
            n1 = strlen(e->name) - 0xf;
            hint1 = e->name + n1;
            if (e->flags & 0x10) {
                void* p = tail1(size + 1, hint1, hA, pA, mA);
                e->data = (u32)p;
                e->size = size;
                *(u8*)(size + ((u32)p + 0x40000000)) = 0;
            } else {
                void* p = tail1(size, hint1, hB, pB, mB);
                e->data = (u32)p;
                e->size = size;
            }
            ((VO0N*)sLock)->v08();
            fn_802BC1C8(sA, e);
            ((VO0N*)sLock)->v10();
        } else {
            strlen(e->name);
            if (e->flags & 0x10) {
                void* p = tail2(size + 1, hC, pC, mC);
                e->data = (u32)p;
                e->size = size;
                *(u8*)(size + ((u32)p + 0x40000000)) = 0;
            } else {
                void* p = tail2(size, hD, pD, mD);
                e->data = (u32)p;
                e->size = size;
            }
            ((VO0N*)sLock)->v08();
            fn_802BC1C8(sB, e);
            ((VO0N*)sLock)->v10();
        }
    } else {
        if (!(e->flags & 0x80)) {
            n2 = strlen(e->name) - 0xf;
            hint2 = e->name + n2;
            if (e->flags & 0x10) {
                void* p = head1(size + 4, hint2, hE, pE, mE);
                e->data = (u32)p;
                e->size = size;
                ((u32*)((u32)p + 0x40000000))[size] = 0;
            } else {
                void* p = head1(size, hint2, hF, pF, mF);
                e->data = (u32)p;
                e->size = size;
            }
            ((VO0N*)sLock)->v08();
            fn_802BC1C8(sA, e);
            ((VO0N*)sLock)->v10();
        } else {
            strlen(e->name);
            if (e->flags & 0x10) {
                void* p = head2(size + 4, hG, pG, mG);
                e->data = (u32)p;
                e->size = size;
                ((u32*)((u32)p + 0x40000000))[size] = 0;
            } else {
                void* p = head2(size, hH, pH, mH);
                e->data = (u32)p;
                e->size = size;
            }
            ((VO0N*)sLock)->v08();
            fn_802BC1C8(sB, e);
            ((VO0N*)sLock)->v10();
        }
    }
    if (e->flags & 0x200) e->a56 = 1;
    else if (e->flags & 0x400) e->a56 = 3;
    else e->a56 = 2;
    lim = mn(len, maxRead());
    if (e->flags & 0x800) lim = len;
    e->pos = 0;
    return fn_802F6BA8(task, e->data, lim, 0, fn_8023BB70, e->a56) != 0;
}
#pragma pop
}
