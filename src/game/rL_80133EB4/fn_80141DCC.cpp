#include "game/rL_80133EB4/types.h"
struct Mtx { f32 m[12]; };
struct Tex { u8 p[0x20]; };
struct F { Mtx mo; Mtx mq; Mtx mv; Mtx ml; Mtx mp; };
struct Ent { u8 pad[4]; u16 x4; u8 pad6[0x1C - 6]; };
struct Tbl { u8 pad[6]; u8 x6; u8 pad7[0x14 - 7]; Ent* x14; };
struct MM {
    u8 pad0[0xAD];
    s8 xad, xae;
    u8 xaf;
    u8 padb0[0xCC - 0xB0];
    u8 xcc;
    u8 padcd[0xD0 - 0xCD];
    f32 scale;
    u8 padd4[0xE4 - 0xD4];
    u8 xe4[0x30];
};
extern "C" {
extern MM* fn_8013B9A8(void);
extern void fn_8001E6D0(void*, void*);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern void fn_80312378(void*, void*, void*);
extern void fn_80312AC0(void*, Vec*, Vec*, Vec*);
extern void fn_80312D2C(void*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80019D9C(void*);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_80011E28(void);
extern FE10_PROTO ptr32<void> fn_80011F38(void);
extern FE10_PROTO ptr32<void> fn_80011EB4(void);
#else
extern void* fn_80011E28(void);
extern void* fn_80011F38(void);
extern void* fn_80011EB4(void);
#endif
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_80011FC4(void);
#else
extern void* fn_80011FC4(void);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80307F10(void*, ptr32<const void>, int);
#else
extern void fn_80307F10(void*, void*, int);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80021F7C(ptr32<const void>, int, int, ptr32<const void>);
extern FE10_PROTO void fn_80022254(void*, ptr32<const void>);
#else
extern void fn_80021F7C(void*, int, int, void*);
extern void fn_80022254(void*, void*);
#endif
extern void fn_80006A64(void*, void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_80021CB4(ptr32<const void>, ptr32<const void>, ptr32<const void>, int);
extern FE10_PROTO void fn_80021D18(ptr32<const void>, int, int, int, int, int);
extern FE10_PROTO void fn_80021E20(ptr32<const void>, int, int, int, int);
extern FE10_PROTO void fn_80021D9C(ptr32<const void>, int, int, int, int, int);
extern FE10_PROTO void fn_80021E8C(ptr32<const void>, int, int, int, int);
#else
extern void fn_80021CB4(void*, void*, void*, int);
extern void fn_80021D18(void*, int, int, int, int, int);
extern void fn_80021E20(void*, int, int, int, int);
extern void fn_80021D9C(void*, int, int, int, int, int);
extern void fn_80021E8C(void*, int, int, int, int);
#endif

static inline void View(MM* mm, F* f, Vec u, Vec t, Vec e) {
    fn_8001E6D0(mm->xe4, &f->mv);
    fn_80312DB4(mm->xe4, &e, &e);
    fn_80312DB4(mm->xe4, &t, &t);
    fn_80312DB4(&f->mv, &u, &u);
    fn_80312AC0(&f->mo, &e, &u, &t);
}
static inline const Vec& T(Vec& t, f32 x, f32 z) { *(int*)&t.x = 0; *(int*)&t.y = 0; *(int*)&t.z = 0; t.x = x; t.z = z; return t; }
static inline Vec Up1() { Vec u = {0.0f, 0.0f, -1.0f}; return u; }

void fn_80141DCC(void* a, void* b, Tbl* c, void* d) {
    F f;
    Tex tex;
    fn_80019D9C(&f.ml);
    void* g;
    void* i;
    void* h;
    g = fn_80011E28();
    h = fn_80011EB4();
    i = fn_80011F38();
    int n = c->x14[c->x6 - 1].x4;
    MM* mm = fn_8013B9A8();
    f32 y;
    f32 s;
    s = mm->xaf / 2;
    f32 z = mm->xae;
    f32 x = mm->xad;
    y = s;
    Vec t;
    Vec e = {0.0f, 1.0f, 0.0f};
    e.x = x;
    e.z = z;
    View(mm, &f, Up1(), T(t, x, z), e);
    if (mm->xcc) { f32 k = -1.0f; y = s * k; }
    fn_80312D2C(&f.mq, -s, s, -y, y, 0.5f, 0.5f, 0.5f, 0.5f);
    fn_80312378(&f.mo, &f.ml, &f.mo);
    fn_80312378(&f.mq, &f.mo, &f.mp);
    void* q = fn_80011FC4();
    fn_80307F10(&f.mp, q, 0);
    fn_80021F7C(i, 0, 0, q);
    fn_80006A64(d, &tex, n);
    fn_80022254(&tex, h);
    fn_80021CB4(g, i, h, 4);
    fn_80021D18(g, 0, 0, 0, 1, 0);
    fn_80021E20(g, 0xF, 0, 8, 0xF);
    fn_80021D9C(g, 0, 0, 0, 1, 0);
    fn_80021E8C(g, 7, 7, 7, 0);
}

static inline Vec Up3() { Vec u = {0.0f, 0.0f, -1.0f}; return u; }
void fn_80142D90(void* a, void* b, Tbl* c, void* d) {
    F f;
    Tex tex;
    fn_80019D9C(&f.ml);
    void* g;
    void* i;
    void* h;
    g = fn_80011E28();
    h = fn_80011EB4();
    i = fn_80011F38();
    int n = c->x14[c->x6 - 1].x4;
    MM* mm = fn_8013B9A8();
    f32 y;
    f32 s;
    f32 k5 = 5.0f * mm->scale;
    s = mm->xaf / 2 * k5;
    y = s;
    Vec t;
    Vec e = {0.0f, 1.0f, 0.0f};
    e.x = 0.0f;
    e.z = 0.0f;
    View(mm, &f, Up3(), T(t, 0.0f, 0.0f), e);
    if (mm->xcc) { f32 k = -1.0f; y = s * k; }
    fn_80312D2C(&f.mq, -s, s, -y, y, 0.5f, 0.5f, 0.5f, 0.5f);
    fn_80312378(&f.mo, &f.ml, &f.mo);
    fn_80312378(&f.mq, &f.mo, &f.mp);
    void* q = fn_80011FC4();
    fn_80307F10(&f.mp, q, 0);
    fn_80021F7C(i, 0, 0, q);
    fn_80006A64(d, &tex, n);
    fn_80022254(&tex, h);
    fn_80021CB4(g, i, h, 4);
    fn_80021D18(g, 0, 0, 0, 1, 0);
    fn_80021E20(g, 0xF, 0, 8, 0xF);
    fn_80021D9C(g, 0, 0, 0, 1, 0);
    fn_80021E8C(g, 7, 7, 7, 0);
}

}
