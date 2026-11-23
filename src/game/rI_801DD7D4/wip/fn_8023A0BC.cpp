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
void* fn_8030E344(void*, u32, int);
void fn_80320978(s64);
void fn_802BC1C8(void*, FE*);
int fn_8023835C(u32, u32, u32, int, void*, FE*);
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
static inline void evict1(int h, u32 size) {
    if (fn_80079088(h) < size) {
        int m = 0x2000;
        while (m != -1 && fn_80079088(h) < size) {
            fn_8023E264(h, m);
            m = nextMode(m);
        }
    }
}
static inline void evict2(int h, u32 size) {
    if (fn_8030E4C0(lbl_804CBF90, 0x20) < size) {
        int m = 0x2000;
        while (m != -1 && fn_8030E4C0(lbl_804CBF90, 0x20) < size) {
            fn_8023E8EC(h, m);
            if (fn_8030E4C0(lbl_804CBF90, 0x20) < size) {
                fn_8023E8EC(-1, m);
            }
            m = nextMode(m);
        }
    }
}
static inline void* tail1(u32 size, const char* hint) {
    int h = lbl_804CAA9C;
    int p = h;
    evict1(h, size);
    p = (int)fn_80078D28(h, -size, hint, size);
    if (p == 0) fn_8007914C();
    return (void*)p;
}
static inline void* tail2(u32 size) {
    int h = lbl_804CAA9C;
    int p = h;
    evict2(h, size);
    p = (int)fn_8030E344(lbl_804CBF90, size, -0x20);
    if (p == 0) fn_8007914C();
    return (void*)p;
}
static inline void* head1(u32 size, const char* hint) {
    int h = lbl_804CAA9C;
    int p = h;
    evict1(h, size);
    p = (int)fn_80078D28(h, size, hint, size);
    if (p == 0) { fn_8007914C(); fn_8023DE84(); }
    return (void*)p;
}
static inline void* head2(u32 size) {
    int h = lbl_804CAA9C;
    int p = h;
    evict2(h, size);
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
int fn_8023A0BC(FE* e, const char* name, FE* src, u32 fl, int (*cb)(u32, u32, u32, int, void*, FE*)) {
/*P*/
    u32 x;
    u32 size;
    u32 f;
/*E*/
    fn_8023B5B0(e, name);
    {
        f = src->flags;
        e->flags = 0;
        e->flags |= f & 0xFF58C00F;
    }
    e->a4b = lbl_804CAA9C;
    {
        x = getFl(name);
        e->flags |= fl | x;
    }
    e->a58 = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2);
    e->a98 = src;
    inc0(src);
    size = src->size;
    if ((e->flags & 0x04000000) && !(e->flags & 0x00100000) || (e->flags & 0x100)) {
        if (!(e->flags & 0x80)) {
            int n = strlen(e->name) - 0xf;
            const char* hint = e->name + n;
            if (e->flags & 0x10) {
                void* p = tail1(size + 1, hint);
                e->data = (u32)p;
                e->size = size;
                *(u8*)(size + ((u32)p + 0x40000000)) = 0;
            } else {
                void* p = tail1(size, hint);
                e->data = (u32)p;
                e->size = size;
            }
            ((VO0N*)sLock)->v08();
            fn_802BC1C8(sA, e);
            ((VO0N*)sLock)->v10();
        } else {
            strlen(e->name);
            if (e->flags & 0x10) {
                void* p = tail2(size + 1);
                e->data = (u32)p;
                e->size = size;
                *(u8*)(size + ((u32)p + 0x40000000)) = 0;
            } else {
                void* p = tail2(size);
                e->data = (u32)p;
                e->size = size;
            }
            ((VO0N*)sLock)->v08();
            fn_802BC1C8(sB, e);
            ((VO0N*)sLock)->v10();
        }
    } else {
        if (!(e->flags & 0x80)) {
            int n = strlen(e->name) - 0xf;
            const char* hint = e->name + n;
            if (e->flags & 0x10) {
                void* p = head1(size + 4, hint);
                e->data = (u32)p;
                e->size = size;
                ((u32*)((u32)p + 0x40000000))[size] = 0;
            } else {
                void* p = head1(size, hint);
                e->data = (u32)p;
                e->size = size;
            }
            ((VO0N*)sLock)->v08();
            fn_802BC1C8(sA, e);
            ((VO0N*)sLock)->v10();
        } else {
            strlen(e->name);
            if (e->flags & 0x10) {
                void* p = head2(size + 4);
                e->data = (u32)p;
                e->size = size;
                ((u32*)((u32)p + 0x40000000))[size] = 0;
            } else {
                void* p = head2(size);
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
    while (fn_8023835C(e->data, src->data, src->size, e->a56, (void*)cb, e) == 0) {
        fn_80320978((s64)5 * ((*(u32*)0x800000F8 >> 2) / 1000));
    }
    return 1;
}
#pragma pop
}
