#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct Color { u8 r, g, b, a; };
struct Mat { u8 pad[0x25]; u8 x25; u8 pad26[2]; u16 x28; u8 pad2a; Color x2b; };
struct Obj { u8 pad[0x30]; Mat* x30; };
struct MM {
    u8 pad0[0x10];
    void* x10;
    u8 pad14[0x54 - 0x14];
    u8 x54, x55, x56, x57;
    f32 x58, x5c;
    u8 x60, x61, x62, x63, x64, x65;
    Color x66;
    u8 pad6a[0x8A - 0x6A];
    char name[1];
};
extern "C" {
extern const char lbl_803694D4[];
extern const u8 lbl_804CDE8F;
extern int fn_80290DDC(char*, const char*, ...);
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(const char*);
#else
extern int fn_80076F54(const char*);
#endif
extern u8* fn_80077064(const char*);
extern u8 fn_80109A18(u8**);
extern u16 fn_80109A2C(u8**);
extern Obj* fn_8017C218(int, void*);

static inline void SetC(MM* mm, Color c) { mm->x66 = c; }
static inline void SetM(Mat* m, Color c) { m->x2b = c; }
static inline Color Mk(u8 a, u8 b, u8 c, u8 d) { Color k; k.r = a; k.g = b; k.b = c; k.a = d; return k; }

static inline Color Mk2(u8 a, u8 b, u8 c, u8 d) { return Mk(a, b, c, d); }
static inline void SetM1(Obj* o, Color* c) { SetM(o->x30, *c); }
static inline void SetM2(Obj* o, Color* c) { SetM1(o, c); }
void fn_801369BC(MM* mm) {
    char path[0x40];
    u8* r;
    Color k;
    fn_80290DDC(path, lbl_803694D4 + 0xD0, mm->name);
    if (fn_80076F54(path)) {
        r = fn_80077064(path);
        u8 ver = fn_80109A18(&r);
        mm->x54 = fn_80109A18(&r);
        mm->x55 = fn_80109A18(&r);
        mm->x56 = fn_80109A18(&r);
        mm->x57 = fn_80109A18(&r);
        mm->x58 = fn_80109A18(&r) / 100.0f;
        mm->x5c = (s16)fn_80109A2C(&r) / 100.0f;
        mm->x64 = fn_80109A18(&r);
        mm->x65 = fn_80109A18(&r);
        {
            u8 a = fn_80109A18(&r);
            u8 b = fn_80109A18(&r);
            u8 c = fn_80109A18(&r);
            u8 d = fn_80109A18(&r);
            SetC(mm, Mk2(a, b, c, d));
        }
        if (ver >= 1) {
            mm->x60 = fn_80109A18(&r);
            mm->x61 = fn_80109A18(&r);
            mm->x62 = fn_80109A18(&r);
            mm->x63 = fn_80109A18(&r);
        }
        if (ver >= 2) {
            u8 id = fn_80109A18(&r);
            u8 v = fn_80109A18(&r);
            u8 w = fn_80109A18(&r);
            u8 a = fn_80109A18(&r);
            u8 b = fn_80109A18(&r);
            u8 c = fn_80109A18(&r);
            k.r = a;
            k.a = lbl_804CDE8F;
            k.g = b;
            k.b = c;
            if (id) {
                Obj* o = fn_8017C218((u8)(id - 1), mm->x10);
                o->x30->x25 = v;
                o->x30->x28 = w;
                SetM2(o, &k);
            }
        }
    }
}
}
