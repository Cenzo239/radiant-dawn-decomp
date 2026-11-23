#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
typedef struct UData { u8 pad[0x10C]; u32 v10C; u16 h110; } UData;
typedef struct Mdl { u32 flags; u8 pad4[4]; GXColor c; u8 padC[0x7C]; UData* u; } Mdl;
typedef struct Sub { u8 pad[4]; u16 tex; } Sub;
typedef struct Arg { u8 pad[0x14]; Sub* s; } Arg;
extern "C" {
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_80011E28(void);
extern FE10_PROTO ptr32<void> fn_80011EB4(void);
extern FE10_PROTO ptr32<void> fn_80011F38(void);
extern FE10_PROTO void fn_80021CB4(ptr32<const void>, int, int, int);
#else
extern void* fn_80011E28(void);
extern void* fn_80011EB4(void);
extern void* fn_80011F38(void);
extern void fn_80021CB4(void*, int, int, int);
#endif
extern void fn_80021EF8(void*, int);
extern void fn_80006A64(void*, void*, u16);
#if TARGET_PC
extern FE10_PROTO void fn_80022254(void*, ptr32<const void>);
extern FE10_PROTO void fn_80021F7C(ptr32<const void>, int, int, int);
extern FE10_PROTO void fn_80021E20(ptr32<const void>, int, int, int, int);
extern FE10_PROTO void fn_80021D18(ptr32<const void>, int, int, int, int, int);
extern FE10_PROTO void fn_80021E8C(ptr32<const void>, int, int, int, int);
extern FE10_PROTO void fn_80021D9C(ptr32<const void>, int, int, int, int, int);
#else
extern void fn_80022254(void*, void*);
extern void fn_80021F7C(void*, int, int, int);
extern void fn_80021E20(void*, int, int, int, int);
extern void fn_80021D18(void*, int, int, int, int, int);
extern void fn_80021E8C(void*, int, int, int, int);
extern void fn_80021D9C(void*, int, int, int, int, int);
#endif
extern void fn_80306FD8(int, int, int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_80022158(ptr32<const void>, int, int);
#else
extern void fn_80022158(void*, int, int);
#endif
extern int fn_801092C4(void*);
extern int fn_8017FA1C(void);
extern u8 fn_8001F060(int, int, int, int);
extern void fn_800140A0(Mdl*, void*);
extern void fn_80013CF0(Mdl*, void*, Arg*);
#if TARGET_PC
extern FE10_PROTO void fn_800125A8(Mdl*, p32arg, void*, Arg*);
#else
extern void fn_800125A8(Mdl*, int, void*, Arg*);
#endif
void fn_800FB9D0(Mdl* m, void* b, Arg* a, void* t) {
    u8 tex[0x20];
    GXColor sv = m->c;
    UData* u = m->u;
    void* g = fn_80011E28();
    if ((m->flags & 0x800) || a->s == 0) {
        fn_80021CB4(g, 0xFF, 0xFF, 4);
        fn_80021EF8(g, 4);
    } else {
        void* x = fn_80011EB4();
        void* y = fn_80011F38();
        fn_80006A64(t, tex, a->s->tex);
        fn_80022254(tex, x);
        fn_80021F7C(y, 1, 4, 0x3C);
        fn_80021CB4(g, (int)y, (int)x, 4);
        fn_80021EF8(g, 0);
    }
    if (u->h110 & 1) {
        fn_80021E20(g, 0xF, 0xA, 0xA, 0xF);
        fn_80021D18(g, 0, 0, 3, 1, 0);
        fn_80021E8C(g, 7, 4, 5, 7);
        fn_80021D9C(g, 0, 0, 0, 1, 0);
    } else {
        if (u->v10C & 1) {
            fn_80306FD8(1, 1, 1, 1, 3);
            fn_80022158(g, 0, 1);
            fn_80021E20(g, 0xF, 8, 0xA, 0xA);
            fn_80021D18(g, 0, 2, 3, 1, 0);
            fn_80021E8C(g, 7, 4, 5, 7);
            fn_80021D9C(g, 0, 0, 0, 1, 0);
        }
        if (fn_801092C4(&u->h110)) {
            u8 v = fn_8001F060(0x40, 0x80, 0x80, fn_8017FA1C());
            m->c.r = m->c.r * v >> 7;
            m->c.g = m->c.g * v >> 7;
            m->c.b = m->c.b * v >> 7;
        }
    }
    fn_800140A0(m, b);
    fn_80013CF0(m, b, a);
    fn_800125A8(m, 0, b, a);
    m->c = sv;
}
}
