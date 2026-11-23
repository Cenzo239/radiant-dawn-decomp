#include "game/rL_80133EB4/types.h"
struct Mtx { f32 m[12]; };
struct MM {
    u8 pad0[0x14];
    u8* x14;
    u8 pad18[0x58 - 0x18];
    f32 x58;
    u8 pad5c[0xD4 - 0x5C];
    u8 padd4[0xE4 - 0xD4];
    u8 xe4[0x30];
};
struct Lit { u8 pad[0xD4]; Vec a; Vec b; };
struct Fx { u8 pad[0x30]; u8* x30; };
struct PosT { u8 pad[4]; u8 x4; u8 pad5; s8 x6, x7; };
extern "C" {
extern MM* fn_8013B9A8(void);
extern void fn_8001E6D0(void*, void*);
extern void fn_80312494(void*, void*);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_80312A50(void*, Vec*, Vec*);
extern u8 lbl_803CAB38[];
extern u8 lbl_803EC898[];
extern u8* lbl_804CB814;
extern Fx* lbl_804CB868;
extern Fx* lbl_804CB86C;
extern int fn_80060780(void*);
extern PosT* fn_80062A9C(void*, int);
extern int fn_8010E2F4(void*);
extern f32 fn_80113F00(void*, f32, f32);
extern void fn_800E48AC(void*, f32, f32, f32);

static inline void Place(Fx* fx, void* q, PosT* p) {
    *(u32*)(fx->x30 + 0x18) |= 0x10;
    if (p->x4 == 3 && fn_8010E2F4(q)) {
        *(u32*)(fx->x30 + 0x18) &= ~0x10;
        f32 x = 0.5f + (f32)p->x6;
        f32 y = 0.5f + (f32)p->x7;
        fn_800E48AC(fx, x, y, fn_80113F00(lbl_803EC898, x, y) - 0.1f);
    }
}
void fn_80140954(void) {
    if (fn_80060780(lbl_803CAB38)) {
        Fx* fx = lbl_804CB868;
        if (fx) {
            PosT* p = fn_80062A9C(lbl_803CAB38, 0);
            Place(fx, lbl_804CB814, p);
        }
        fx = lbl_804CB86C;
        if (fx) {
            PosT* p = fn_80062A9C(lbl_803CAB38, 3);
            Place(fx, lbl_804CB814 + 0x24, p);
        }
    }
}

int fn_80140C8C(Lit* l, Mtx* out, f32 h) {
    MM* mm = fn_8013B9A8();
    if (mm == 0) return 0;
    Mtx mv;
    Mtx mi;
    Mtx ms;
    Mtx ml;
    Mtx mt;
    Vec up = {0.0f, 1.0f, 0.0f};
    Vec c = {0.0f, 0.0f, 0.0f};
    Vec a = l->b;
    Vec b = l->a;
    f32 s = mm->x58;
    fn_8001E6D0(mm->xe4, &mv);
    fn_80312494(&mv, &mi);
    fn_80312DB4(&mi, &a, &a);
    fn_80312DB4(&mi, &b, &b);
c.x = a.x;
    c.y = h;
    c.z = a.z;
    fn_803128AC(&mt, -a.x, -(f32)(f64)h, -a.z);
    fn_8031292C(&ms, 1.0f, s, 1.0f);
    fn_80312378(&ms, &mt, &ms);
    fn_803128AC(&mt, c.x, c.y, c.z);
    fn_80312378(&mt, &ms, &ms);
    fn_80312378(&ms, &mi, &ms);
    fn_80312378(&mv, &ms, &ms);
    fn_80312DB4(&mv, &c, &c);
    fn_80312DB4(&mv, &up, &up);
    fn_80312A50(&ml, &c, &up);
    fn_80312378(&ms, &ml, out);
    return 1;
}
}
