/* fn_80288094: round m1, exact (from wip/fn_80288094.cpp, 11 words). The fix: the sprintf arguments
   are nested calls, evaluated last to first, instead of named locals. */
/* Result report window draw */
#include "game/rN_8025EEF0/prim2d.h"

struct GXC { u8 r, g, b, a; };

extern "C" {

struct Rep {
    void* tex;
    void* win;
    s16 m8;
    u8 padA[0x21C - 0xA];
    char text[1];
};
extern Rep* lbl_804CC0D4;
extern char lbl_80373CF0[];
void fn_801C6EAC(const char* a, const char* b, char* out);
void fn_800068A0(void* p, void* q);
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC* c, int d, int e);
void fn_801BCA5C(f32 v);
void fn_80287B54(f32 a, f32 b);
const char* fn_800CEC24(void);
const char* fn_800CF53C(void);
void fn_801C6D9C(char* s, int a, int b, int c);
void fn_80179A84(void* w);

static inline void bg(f32 x, f32 y) {
    GXC c;
    GXC t;
    u16* d = *fn_80006A0C(lbl_804CC0D4->tex, 0);
    f32 h;
    f32 w;
    u8* p;
    w = d[1];
    h = d[0];
    p = fn_800CD204(1);
    c.r = p[0];
    c.g = p[1];
    c.b = p[2];
    c.a = 0xFF;
    d = *fn_80006A0C(lbl_804CC0D4->tex, 0);
    {
        f32 w2 = d[1];
        f32 h2 = d[0];
        *(u32*)&t = *(u32*)&c;
        fn_801BC88C(x, y, x + w, y + h, x, y, w2, h2, lbl_804CC0D4->tex, 0, &t, 0x11, 0);
    }
}

void fn_80288094(void) {
    char name[0x60];
    fn_801C6EAC(lbl_80373CF0 + 0x16, lbl_80373CF0 + 0x37, name);
    if (fn_8023F880(name) == 0) {
        return;
    }
    if (lbl_804CC0D4->tex == 0) {
        fn_800068A0(lbl_804CC0D4, name);
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    bg(0.0f, 0.0f);
    fn_80287B54(20.0f, 16.0f);
    fn_801BCA5C(-0.5f);
    {
    if (lbl_804CC0D4->m8 < 9) {
        fn_80290DDC(lbl_804CC0D4->text, lbl_80373CF0 + 0x3C, fn_800CEC24(), fn_800D0864(lbl_80373CF0 + 0x41));
    } else {
        fn_80290DDC(lbl_804CC0D4->text, lbl_80373CF0 + 0x55, fn_800CF53C(), fn_800D0864(lbl_80373CF0 + 0x5F), fn_800CEC24(), fn_800D0864(lbl_80373CF0 + 0x41));
    }
    }
    fn_801C6D9C(lbl_804CC0D4->text, 0xFF, 0xFF, 0);
    fn_801BCA5C(0.5f);
    fn_80179A84(lbl_804CC0D4->win);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

}
