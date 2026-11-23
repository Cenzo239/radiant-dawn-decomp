#include "game/rS_8023FD30/audio.h"

extern "C" {

void* fn_8029C7D8(void);
void fn_8029D3E8(void*, s32, s32);
int fn_8029D1E4(void*, s32, void*);
u32 fn_802A63E0(void*);
#if TARGET_PC
FE10_PROTO void fn_802A6534(void*, p32arg);
#else
void fn_802A6534(void*, u32);
#endif
void fn_802A6414(void*);
void fn_802A640C(void*, void*, u32);
u32 fn_802A5FB8(void*);
#if TARGET_PC
FE10_PROTO void fn_8030E3F4(ptr32<const void>, void*);
FE10_PROTO void* fn_8030E344(ptr32<const void>, u32, s32);
#else
void fn_8030E3F4(void*, void*);
void* fn_8030E344(void*, u32, s32);
#endif
extern void* lbl_804CBFDC;
extern void* lbl_804CBFE0;
extern u8 lbl_8042EB24[];
extern u8 lbl_8042ECBC[];
extern void* lbl_804CBFE4;
#if TARGET_PC
FE10_PROTO void fn_802A610C(void*, p32arg);
#else
void fn_802A610C(void*, u32);
#endif
void fn_802A5FEC(void*);
void fn_802A5FE4(void*, void*, u32);

static inline void* heapAlloc(u32 size) {
    SndLock l(lbl_8042E798);
    return fn_8030E344(lbl_804CBFDC, size, 0x20);
}

static inline void heapFree(void* old) {
    SndLock l(lbl_8042E798);
    fn_8030E3F4(lbl_804CBFDC, old);
}

#pragma use_lmw_stmw on
int fn_80256BF8(u32 a) {
    SndLock l(lbl_8042E798);
    fn_8029D3E8(fn_8029C7D8(), 0, 0);
    u32 before = fn_802A63E0(lbl_8042EB24);
    fn_802A6534(lbl_8042EB24, a);
    a = fn_802A63E0(lbl_8042EB24);
    if (a > before) {
        fn_802A6414(lbl_8042EB24);
        heapFree(lbl_804CBFE0);
        lbl_804CBFE0 = heapAlloc(a);
        fn_802A640C(lbl_8042EB24, lbl_804CBFE0, a);
    }
    return fn_8029D1E4(fn_8029C7D8(), 0, lbl_8042EB24);
}

int fn_80256D70(u32 a) {
    SndLock l(lbl_8042E798);
    fn_8029D3E8(fn_8029C7D8(), 1, 0);
    u32 before = fn_802A5FB8(lbl_8042ECBC);
    fn_802A610C(lbl_8042ECBC, a);
    a = fn_802A5FB8(lbl_8042ECBC);
    if (a > before) {
        fn_802A5FEC(lbl_8042ECBC);
        heapFree(lbl_804CBFE4);
        lbl_804CBFE4 = heapAlloc(a);
        fn_802A5FE4(lbl_8042ECBC, lbl_804CBFE4, a);
    }
    return fn_8029D1E4(fn_8029C7D8(), 1, lbl_8042ECBC);
}
#pragma use_lmw_stmw off

struct SndParams {
    f32 a, b, c, d, e, f;
    s32 g;
    f32 h;
    s32 i;
    f32 j, k;
};

void fn_80256EE8(SndParams* out) {
    SndMutex& m = lbl_8042E798;
    m.lock();
    SndParams* p = (SndParams*)(lbl_8042EB24 + 0x18);
    out->a = p->a;
    out->b = p->b;
    out->c = p->c;
    out->d = p->d;
    out->e = p->e;
    out->f = p->f;
    out->g = p->g;
    out->h = p->h;
    out->i = p->i;
    out->j = p->j;
    out->k = p->k;
    m.unlock();
}

struct SndVec5 {
    f32 a, b, c, d, e;
};
SndVec5* fn_802A62B0(void*);

void fn_80256FA4(SndVec5* out) {
    SndLock l(lbl_8042E798);
    SndVec5* p = fn_802A62B0(lbl_8042ECBC);
    out->a = p->a;
    out->b = p->b;
    out->c = p->c;
    out->d = p->d;
    out->e = p->e;
}

#if TARGET_PC
FE10_PROTO void fn_80312AC0(void*, void*, void*, void*);
#else
void fn_80312AC0(void*, s32, s32, s32);
#endif
void fn_802ACC94(void*, void*);
extern u8 lbl_8042E830[];

#pragma use_lmw_stmw on
void fn_80257948(
#if TARGET_PC
void* a, void* b, void* c
#else
s32 a, s32 b, s32 c
#endif
) {
    u8 buf[0x30];
    SndMutex& m = lbl_8042E798;
    SndLock l(m);
    fn_80312AC0(buf, a, c, b);
    {
        SndLock l2(m);
        fn_802ACC94(lbl_8042E830, buf);
    }
}
#pragma use_lmw_stmw off

void fn_8025704C(f32 ms) {
    SndLock l(lbl_8042E798);
    fn_8029D3E8(fn_8029C7D8(), 0, ms);
}

void fn_802570D0(f32 ms) {
    SndLock l(lbl_8042E798);
    fn_8029D3E8(fn_8029C7D8(), 1, ms);
}

}
