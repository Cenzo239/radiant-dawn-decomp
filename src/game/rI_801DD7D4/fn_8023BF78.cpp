/* fn_8023BF78: open (or re-reference) an archive/file entry by name and wait until it is loaded.
   Sibling of fn_8023C9C8; takes one more reference and returns the entry's data pointer. */
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
int fn_8031D34C(void*, void*, int);
int fn_8031D284(void*, void*, int);
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
struct FB { u32 a : 8; u32 b8 : 1; u32 c : 3; u32 b12 : 1; u32 d : 19; };
struct Msg { s8 type; u8 p1[3]; FE* e; u32 a8; };
static inline void slp() { fn_80320978((s64)5 * ((*(u32*)0x800000F8 >> 2) / 1000)); }
static inline void waitLoaded(FE* e) {
    inc0(e);
    while (!(e->flags & 0x200000)) slp();
    dec0(e);
}
static inline void waitIdle(FE* e) {
    inc0(e);
    while (e->flags & 4) slp();
    dec0(e);
}
static inline void post(FE* e, u32 fl) {
    Msg* m;
    e->flags = (e->flags & ~0x200000) | fl;
    fn_8031D34C(sQ2, &m, 1);
    m->type = 0;
    m->e = e;
    m->a8 = 0;
    fn_8031D284(sQ1, m, 1);
}
u32 fn_8023BF78(const char* name, u32 fl) {
    FE* e;
    if ((fl & 0x80) && (fl & 0x40)) fl &= ~0x40;
    e = fn_8023DCC0(name);
    if (e != NULL) {
        e->flags |= fl;
        if ((e->data & 0xF0000000) == 0x90000000) {
            if (!(fl & 0x80)) {
                if (flg(e, 0x800004)) {
                    FE* n;
                    waitLoaded(e);
                    n = fn_8023D9B8();
                    fn_8023A0BC(n, name, e, fl, fn_8023BE08);
                    e = n;
                }
            } else {
                if (e->a4b == -1) e->a4b = lbl_804CAA9C;
                if (flg(e, 0x04000000) && !flg(e, 0x100000)) {
                    waitLoaded(e);
                    if (!flg(e, 0x100000)) {
                        if (flg(e, 0x200000) || flg(e, 4)) {
                            waitIdle(e);
                            post(e, fl);
                        }
                    }
                } else if (flg(e, 0x800004) && flg(e, 0x08000000)) {
                    waitIdle(e);
                    post(e, fl);
                }
            }
        }
    } else {
        FE* a;
        e = fn_8023D9B8();
        fn_8023B5B0(e, name);
        a = findArc(e->name);
        if (a == NULL) fn_802396CC(e, name, fl);
        else fn_8023AC14(e, name, a, fl);
    }
    waitLoaded(e);
    inc0(e);
    touch(e);
    { FB* b = (FB*)&e->flags; b->b12 = 0; b->b8 = 0; }
    return e->data;
}
#pragma pop
}
