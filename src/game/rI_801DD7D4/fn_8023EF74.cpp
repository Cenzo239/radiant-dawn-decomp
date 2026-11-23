#include "game/rI_801DD7D4/fn_fe.h"
extern "C" {
extern void* lbl_804CBF90;
extern void* lbl_804CBF94;
FE* fn_802BC2A4(void*, FE*);
FE* fn_8023DCC0(const char*);
u64 OSGetTime(void);
u64 fn_8028C418(u64, u64);
void fn_80320978(s64);
int fn_80238EE8(FE*);
void fn_802FAED4(void*);
void fn_8023B894(FE*);
void fn_8023B9D8(FE*);
#if TARGET_PC
FE10_PROTO void fn_80078E24(p32arg);
#else
void fn_80078E24(u32);
#endif
#if TARGET_PC
FE10_PROTO void fn_8030E3F4(ptr32<const void>, p32arg);
#else
void fn_8030E3F4(void*, u32);
#endif
void fn_802BC238(void*, FE*);
void fn_8030EC2C(void*, FE*);
}
class VD { public: virtual void d(int); };
static inline int flg(FE* e, int m) { return e->flags & m; }
static inline FE* par(FE* e) { return e->parent; }
static inline void dec4(FE* e) { if (flg(e, 0x10000000) != 0) fn_80238EE8(par(e)); --e->rc; }
static inline void dec3(FE* e) { if (flg(e, 0x10000000) != 0) dec4(par(e)); --e->rc; }
static inline void dec2(FE* e) { if (flg(e, 0x10000000) != 0) dec3(par(e)); --e->rc; }
static inline void dec1(FE* e) { if (flg(e, 0x10000000) != 0) dec2(par(e)); --e->rc; }
static inline void waitDone(FE* c) {
    fn_802FAED4(c->task);
    while (!(c->flags & 0x00230000)) {
        fn_80320978((s64)5 * ((*(u32*)0x800000F8 >> 2) / 1000));
        if (c->name[0] == 0) break;
    }
}
static inline void freeData(u32 p) {
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
static inline void freeE(FE* c) {
    if (c->name[0] != 0) {
        VO0N* k;
        if (flg(c, 0x00200000)) {
            fn_8023B894(c);
            fn_8023B9D8(c);
        }
        freeData(c->data);
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
static inline void relE(FE* e) {
    fn_802FAED4(e->task);
    while (!(e->flags & 0x00230000)) {
        fn_80320978((s64)5 * ((*(u32*)0x800000F8 >> 2) / 1000));
        if (e->name[0] == 0) break;
    }
    if (e->name[0] != 0) {
        e->a58 = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2);
        if (flg(e, 0x10000000) != 0) dec1(par(e));
        u16 n = e->rc - 1;
        e->rc = n;
        if (n == 0) {
            if (flg(e, 0x200000)) fn_8023B894(e);
            if ((!flg(e, 0x200000) || flg(e, 0x120)) && !flg(e, 0x10000000)) {
                waitDone(e);
                freeE(e);
            }
        }
    }
}
extern "C" {
#pragma push
#pragma use_lmw_stmw on
int fn_8023EF74(void) {
    int r = 1;
    VO0N* k = (VO0N*)sLock;
    u32 now;
    FE* e;
    k->v08();
    now = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2);
    for (e = fn_802BC2A4(sA, NULL); e != NULL; e = fn_802BC2A4(sA, e)) {
        if (e->name[0] != 0 && !flg(e, 0x200000) && flg(e, 0x80000) && now <= e->a58 + 10) { r = 0; goto done; }
    }
    for (e = fn_802BC2A4(sB, NULL); e != NULL; e = fn_802BC2A4(sB, e)) {
        if (e->name[0] != 0 && !flg(e, 0x200000) && flg(e, 0x80000) && now <= e->a58 + 10) { r = 0; goto done; }
    }
done:
    k->v10();
    return r;
}
void fn_8023F1A8(u32 data) {
    FE* f = 0;
    VO0N* k = (VO0N*)sLock;
    u8* l;
    FE* a;
    k->v08();
    l = sB;
    if ((data & 0xF0000000) != 0x90000000) l = sA;
    for (a = fn_802BC2A4(l, NULL); a != NULL; a = fn_802BC2A4(l, a)) {
        if (a->data == data) { f = a; break; }
    }
    k->v10();
    if (f != NULL) relE(f);
}
void fn_8023F4EC(const char* name) {
    FE* e = fn_8023DCC0(name);
    if (e != NULL) relE(e);
}
#pragma pop
}
