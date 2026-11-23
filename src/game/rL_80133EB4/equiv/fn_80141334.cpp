/* fn_80141334: functionally equal (regs level per tools/check_regs.py; registers differ from the original). From wip/near3.cpp. */
/* ===== fn_80141334: 4 words: only the template base register (r5, want r4). The camera form works in fn_80141DCC.cpp ===== */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct Mtx { f32 m[12]; };
struct Tex { u8 p[0x20]; };
struct MM {
    u8 pad0[0x14];
    u8* x14;
    u8 pad18[0x58 - 0x18];
    f32 x58;
    u8 pad5c[0x61 - 0x5C];
    s8 x61;
    u8 x62;
    u8 pad63[0xAD - 0x63];
    s8 xad, xae;
    u8 xaf;
    u8 padb0[0xCC - 0xB0];
    u8 xcc;
    u8 padcd[0xD0 - 0xCD];
    f32 scale;
    Vec xd4;
    u8 pade0[4];
    u8 xe4[0x30];
};
struct Cam { Vec e, t, u; Cam(const Vec& a, const Vec& b, const Vec& c) : e(a), t(b), u(c) {} };
struct Cam2 { Vec e, t, u; };
struct W3 { u32 a, b, c; };
inline Vec Z() { Vec z = {0.0f, 0.0f, 0.0f}; return z; }
inline W3 Z3() { W3 z = {0, 0, 0}; return z; }
struct F { Mtx mo; Mtx mq; Mtx mv; Mtx ml; Mtx mp; };
struct Lit { Vec a; Vec b; };
extern "C" {
extern MM* fn_8013B9A8(void);
extern void fn_8001E6D0(void*, void*);
extern void fn_80312494(void*, void*);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_80312A50(void*, Vec*, Vec*);
extern void fn_80312AC0(void*, Vec*, Vec*, Vec*);
extern void fn_80312D2C(void*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80019D9C(void*);
extern int fn_800120A0(void);
extern void* fn_80012048(void);
extern void* fn_80011F38(void);
extern void* fn_80011EB4(void);
extern void* fn_80011FC4(void);
extern void fn_8001E51C(void*);
extern void fn_803067E0(int, void*, int);
extern void fn_80305A40(void*, void*, int, int, int, int, int, int);
extern void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
extern void fn_80307F10(void*, void*, int);
extern void fn_80021F7C(void*, int, int, void*);
extern void fn_80022254(void*, void*);
extern void fn_80306A38(void*, void*, void*);
extern void fn_80306934(void*, int, int);
extern void fn_80306B6C(void*, void*, int, int, int);

static inline Vec Eye(f32 x, f32 z) { Vec e = {0.0f, 1.0f, 0.0f}; e.x = x; e.z = z; return e; }
static inline Vec Tgt(f32 x, f32 z) { Vec t = {0.0f, 0.0f, 0.0f}; t.x = x; t.z = z; return t; }
static inline Vec Up() { Vec u = {0.0f, 0.0f, -1.0f}; return u; }
static inline void View(MM* mm, F* f, Vec u, Vec t, Vec e) {
    fn_8001E6D0(mm->xe4, &f->mv);
    fn_80312DB4(mm->xe4, &e, &e);
    fn_80312DB4(mm->xe4, &t, &t);
    fn_80312DB4(&f->mv, &u, &u);
    fn_80312AC0(&f->mo, &e, &u, &t);
}
static inline const Vec& T(Vec& t, f32 x, f32 z) { *(int*)&t.x = 0; *(int*)&t.y = 0; *(int*)&t.z = 0; t.x = x; t.z = z; return t; }
int fn_80141334(void* out) {
    MM* mm = fn_8013B9A8();
    if (mm == 0) return 0;
    u8* w = mm->x14;
    if (w == 0) return 0;
    if (*(void**)(w + 0x48) == 0) return 0;
    int idx = mm->x61;
    f32 y;
    f32 s = mm->x62 / 2.0f;
    s *= 5.0f * mm->scale;
    if (0.0f == s) return 0;
    void* a = (void*)fn_800120A0();
    if ((int)a == 4) {
        F f;
        u8 m3[0x18];
        Tex tex;
        fn_80019D9C(&f.ml);
        fn_80305A40(&tex, *(void**)(w + 0x48), 0x20, 0x20, 3, 1, 1, 0);
        fn_80305C94(&tex, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
        a = fn_80012048();
        void* b = fn_80011F38();
        void* c = fn_80011EB4();
        void* d = fn_80011FC4();
        fn_8001E51C(m3);
        fn_803067E0(2, m3, idx);
        y = s;
        Vec t;
        Vec e = {0.0f, 1.0f, 0.0f};
        e.x = 0.0f;
        e.z = 0.0f;
        View(mm, &f, Up(), T(t, 0.0f, 0.0f), e);
        if (mm->xcc) { f32 k = -1.0f; y = s * k; }
        fn_80312D2C(&f.mq, -s, s, -y, y, 0.5f, 0.5f, 0.5f, 0.5f);
        fn_80312378(&f.mo, &f.ml, &f.mo);
        fn_80312378(&f.mq, &f.mo, &f.mp);
        fn_80307F10(&f.mp, d, 0);
        fn_80021F7C(b, 0, 0, d);
        fn_80022254(&tex, c);
        fn_80306A38(a, b, c);
        fn_80306934(a, 0, 0);
    }
    fn_80306B6C(out, a, 1, 0, 2);
    return 1;
}
}

