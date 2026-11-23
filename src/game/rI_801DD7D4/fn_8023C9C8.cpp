#include "game/rI_801DD7D4/fn_fe.h"
extern "C" {
extern s8 lbl_804CAA9C;
extern void* lbl_804CBF94;
extern u8 lbl_80390C58[];
void* fn_8030EB98(void*);
void fn_8023E264(int, int);
void fn_8023E8EC(int, int);
void fn_8023DE84(void);
FE* fn_8023DCC0(const char*);
FE* fn_802BC2A4(void*, FE*);
void fn_8023B5B0(FE*, const char*);
int fn_80291188(const char*, const char*);
int fn_8025F4E0(FE*, const char*);
int fn_802396CC(FE*, const char*, u32);
void fn_8023AC14(FE*, const char*, FE*, u32);
int fn_8023A0BC(FE*, const char*, FE*, u32, void*);
#if TARGET_PC
FE10_PROTO void fn_8023BE08(ptr32<const void>, ptr32<const void>, ptr32<const void>, ptr32<const void>);
#else
void fn_8023BE08(void* p, void* a, void* b, void* c);
#endif
FE* fn_8023D9B8(void);
u64 OSGetTime(void);
u64 fn_8028C418(u64, u64);
void fn_80320978(s64);
int fn_8023AB4C(FE*);
int fn_80238EE8(FE*);
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
static inline int flg(FE* e, int m) { return e->flags & m; }
static inline FE* par(FE* e) { return e->parent; }
static inline void inc4(FE* e) { if (flg(e, 0x10000000) != 0) fn_8023AB4C(par(e)); ++e->rc; }
static inline void inc3(FE* e) { if (flg(e, 0x10000000) != 0) inc4(par(e)); ++e->rc; }
static inline void inc2(FE* e) { if (flg(e, 0x10000000) != 0) inc3(par(e)); ++e->rc; }
static inline void inc1(FE* e) { if (flg(e, 0x10000000) != 0) inc2(par(e)); ++e->rc; }
static inline void inc0(FE* e) { if (flg(e, 0x10000000) != 0) inc1(par(e)); ++e->rc; }
static inline void dec4(FE* e) { if (flg(e, 0x10000000) != 0) fn_80238EE8(par(e)); --e->rc; }
static inline void dec3(FE* e) { if (flg(e, 0x10000000) != 0) dec4(par(e)); --e->rc; }
static inline void dec2(FE* e) { if (flg(e, 0x10000000) != 0) dec3(par(e)); --e->rc; }
static inline void dec1(FE* e) { if (flg(e, 0x10000000) != 0) dec2(par(e)); --e->rc; }
static inline void dec0(FE* e) { if (flg(e, 0x10000000) != 0) dec1(par(e)); --e->rc; }
static inline void feInit(FE* e) {
    e->vt = lbl_80390C58;
    e->name[0] = 0;
    e->a4b = -1;
    e->hash = 0;
    e->flags = 0;
    e->rc = 0;
    e->a56 = 2;
    e->parent = 0;
    e->data = 0;
    e->size = 0;
    e->pos = 0;
    e->a4 = 0;
    e->a8 = 0;
}
#define H ((s8)*(u8*)&lbl_804CAA9C)
#define TRY(fn, h) { int m = 0x2000; while (m != -1 && (p = (FE*)fn_8030EB98(lbl_804CBF94)) == NULL) { fn(h, m); m = nextMode(m); } }
extern "C" {
#pragma push
#pragma use_lmw_stmw on
static inline void touch(FE* e) { e->a58 = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2); }
static inline FE* findArc(const char* const& nm) {
    FE* f = 0;
    VO0N* k = (VO0N*)sLock;
    FE* a;
    k->v08();
    for (a = fn_802BC2A4(sPad, NULL); a != NULL; a = fn_802BC2A4(sPad, a)) {
        if (fn_8025F4E0(a, nm)) { f = a; break; }
    }
    k->v10();
    return f;
}
void fn_8023C9C8(const char* name, u32 fl) {
    FE* e;
    if ((fl & 0x80) && (fl & 0x40)) fl &= ~0x40;
    e = fn_8023DCC0(name);
    if (e != NULL) {
        if ((e->data & 0xF0000000) != 0x90000000) {
            if (fl & 0x80) { e->a58 = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2); return; }
 {
                e->a58 = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2);
            }
        } else if (!(fl & 0x80)) {
            if (flg(e, 0x800004)) {
                inc0(e);
                while (!(e->flags & 0x200000)) {
                    fn_80320978((s64)5 * ((*(u32*)0x800000F8 >> 2) / 1000));
                }
                dec0(e);
                fn_8023A0BC(fn_8023D9B8(), name, e, fl | 0x80000, fn_8023BE08);
            } else {
                e->a58 = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2);
            }
        } else {
            e->a4b = lbl_804CAA9C;
            e->a58 = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2);
        }
    } else {
        FE* n = fn_8023D9B8();
        FE* a;
        fn_8023B5B0(n, name);
        a = findArc(n->name);
        if (a == NULL) fn_802396CC(n, name, fl | 0x80000);
        else fn_8023AC14(n, name, a, fl | 0x80000);
    }
}
FE* fn_8023D9B8(void) {
    FE* p = (FE*)fn_8030EB98(lbl_804CBF94);
    if (p == NULL) {
        TRY(fn_8023E264, H)
        if (p == NULL) {
            TRY(fn_8023E8EC, H)
            if (p == NULL) {
                TRY(fn_8023E264, -1)
                if (p == NULL) {
                    TRY(fn_8023E8EC, -1)
                }
            }
        }
    }
    if (p == NULL) fn_8023DE84();
    if (p != NULL) feInit(p);
    return p;
}
void fn_8023DE84(void) {
    char b1[0x20];
    char b2[0x20];
    FE* e;
    u32 mask = 0;
    mask |= 0x1cd831f1;
    ((VO0N*)sLock)->v08();
    for (e = fn_802BC2A4(sA, NULL); e != NULL; e = fn_802BC2A4(sA, e)) {
        if (e->name[0] != 0) {
        if (e->flags & mask) {
            char* p;
            e->flags;
            p = b1;
            *p = 0x5b; p++;
            
            if (e->flags & 1) { *p = 0x49; p++; }
            if (e->flags & 0x10) { *p = 0x5a; p++; }
            if (e->flags & 0x20) { *p = 0x56; p++; }
            if (e->flags & 0x4000000) {
                if (e->flags & 0x100000) { *p = 100; p++; } else { *p = 99; p++; }
            }
            if (e->flags & 0x40) { *p = 0x65; p++; }
            if (e->flags & 0x80) { *p = 0x45; p++; }
            if (e->flags & 0x100) { *p = 0x54; p++; }
            if (e->flags & 0x8000000) { *p = 0x50; p++; }
            if (e->flags & 0x10000000) { *p = 0x43; p++; }
            if (e->flags & 0x400000) { *p = 0x55; p++; }
            if (e->flags & 0x80000) { *p = 0x52; p++; }
            if (e->flags & 0x1000) { *p = 0x48; p++; }
            if (e->flags & 0x2000) { *p = 0x4c; p++; }
            *p = 0x5d;
            *(volatile char*)(p + 1) = 0;
        }
            if (flg(e, 0x10000000) == 0) *(volatile u32*)&e->size;

        }
    }
    for (e = fn_802BC2A4(sB, NULL); e != NULL; e = fn_802BC2A4(sB, e)) {
        if (e->name[0] != 0) {
        if (e->flags & mask) {
            char* p;
            e->flags;
            p = b2;
            *p = 0x5b; p++;
            
            if (e->flags & 1) { *p = 0x49; p++; }
            if (e->flags & 0x10) { *p = 0x5a; p++; }
            if (e->flags & 0x20) { *p = 0x56; p++; }
            if (e->flags & 0x4000000) {
                if (e->flags & 0x100000) { *p = 100; p++; } else { *p = 99; p++; }
            }
            if (e->flags & 0x800000) { *p = 0x65; p++; }
            if (e->flags & 0x80) { *p = 0x45; p++; }
            if (e->flags & 0x100) { *p = 0x54; p++; }
            if (e->flags & 0x8000000) { *p = 0x50; p++; }
            if (e->flags & 0x10000000) { *p = 0x43; p++; }
            if (e->flags & 0x400000) { *p = 0x55; p++; }
            if (e->flags & 0x80000) { *p = 0x52; p++; }
            if (e->flags & 0x1000) { *p = 0x48; p++; }
            if (e->flags & 0x2000) { *p = 0x4c; p++; }
            *p = 0x5d;
            *(volatile char*)(p + 1) = 0;
        }
            if (flg(e, 0x10000000) == 0) *(volatile u32*)&e->size;

        }
    }
    ((VO0N*)sLock)->v10();
}
#pragma pop
}
