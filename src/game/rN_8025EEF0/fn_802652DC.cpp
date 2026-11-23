/* Dictionary relation chart: unit node */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

struct GXC { u8 r, g, b, a; };

extern "C" {

void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
void* fn_80076F54(const char* s);
void* fn_8012CECC(void* u);
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC c, int d, int e);
#if TARGET_PC
FE10_PROTO void * fn_800C3FD0(void* p);
#else
int fn_800C3FD0(void* p);
#endif
void fn_800C4AAC(void* a, void* b, int x, int y, int al, int f);
const char* fn_80118C44(void* u);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);

struct RelNode { const char* name; u8 pad4[8]; s16 x; s16 y; int m10; };

static inline GXC mk(const u8* p) { GXC c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF; return c; }

static inline void Icon(RelNode* e, u8* v, u8* unit, const int& y, const int& x) {
    int m = 0;
    if (e->m10 != 0) {
        m = 2;
    } else if (v != 0) {
        u32 f = *(u32*)(v + 0x10C);
        if (!(f & 0x20) && !(f & 0x10) && (f & 8)) {
            m = 1;
        }
    }
    fn_800C4AAC(*(void**)lbl_804CC008->m24, *(void**)(unit + 0x10), x, y, 0xFF, m);
}

void fn_802652DC(RelNode* e, int flag) {
    u8* v;
    void* tex;
    u16 h;
    u16 w;
    s16 x;
    s16 y;
    u8* unit;
    char buf[0x40];
    x = e->x;
    y = e->y;
    unit = (u8*)fn_80076F54(e->name);
    v = (u8*)fn_8012CECC(unit);
    if (x < 0) return;
    fn_801BCA5C(-2.0f);
    tex = *(void**)lbl_804CC008->m20;
    {
        u16* d = *fn_80006A0C(tex, 6);
        w = d[1];
        h = d[0];
    }
    {
        fn_801BC88C(x, y, x + w, y + h, 0.0f, 0.0f, w, h, tex, 6, mk(fn_800CD204(1)), 0x11, 0);
    }
    if (unit == 0) {
        fn_801BCA5C(2.0f);
        return;
    }
    fn_801BCA5C(-1.0f);
    if (flag != 0) {
        if (fn_800C3FD0(*(void**)(unit + 0x10)) != 0) {
            Icon(e, v, unit, y + 5, x + 3);
        }
        fn_801BCA94();
        if (fn_800CA3DC(fn_80118C44(unit), -1, 0.75f) >= 0x44) {
            fn_80290DDC(buf, lbl_80372C90 + 0x222, fn_80118C44(unit));
        } else {
            fn_80290DDC(buf, lbl_80372C90 + 0x22B, fn_80118C44(unit));
        }
        fn_800CB3A8((s16)(x + 0x22 - fn_800CA3DC(buf, -1, 0.75f) / 2), (s16)(y + 0x43), 8, 0, 0, 0.75f, 0.0f, buf);
    }
    fn_801BCA5C(3.0f);
}

}
