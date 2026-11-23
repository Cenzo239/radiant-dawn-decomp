/* Conversation room: header bar */
#include "game/rN_8025EEF0/room.h"
#include "game/rN_8025EEF0/prim2d.h"

struct GXC { u8 r, g, b, a; };

extern "C" {

u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC* c, int d, int e);
void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080940(GXC* a, GXC* b, GXC* c, GXC* d);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);

/* lbl_804D05DC and +4 */
static const GXC sc0 = {0,0,0,0xFF};
static const GXC sc1 = {0,0,0,0xFF};

static inline void grad(GXC a, GXC b, GXC c, GXC d) { fn_80080940(&a, &b, &c, &d); }
static inline GXC Zero() { GXC z; *(u32*)&z = 0; return z; }

static inline void part0(int i, f32 x, f32 y) {
    GXC t;
    GXC c;

    
    u16* d;
    f32 w;
    f32 h;
    f32 h2;
    f32 w2;
    u8* p;

    d = *fn_80006A0C(roomTex(), (u16)i);
    w = d[1];
    h = d[0];
    p = fn_800CD204(1);
    c.r = p[0];
    c.g = p[1];
    c.b = p[2];
    c.a = 0xFF;
    d = *fn_80006A0C(roomTex(), (u16)i);
    w2 = d[1];
    h2 = d[0];
    {
        void* tx = roomTex();
        *(u32*)&t = *(u32*)&c;
        fn_801BC88C(x, y, x + w, y + h, 0.0f, 0.0f, w2, h2, tx, (u16)i, &t, 0x11, 0);
    }
}

static inline void part(int i, f32 x, f32 y) { part0(i, x, y); }

void fn_802758B0(int frame, const char* msg, int val) {
    
    const char* s;
    char buf[0x18];

    part(0, 0.0f, 0.0f);
    fn_801BCA5C(-1.0f);
    part(frame, 17.0f, 14.0f);
    part(3, 0.0f, 62.0f);
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(3);
    fn_80080388(480.0f, 32.0f, 128.0f, 24.0f);
    grad(Zero(), sc0, Zero(), sc1);
    fn_80080578(0);
    fn_80080308();
    fn_801BCA5C(-1.0f);
    s = fn_800D0864(msg);
    fn_801BCA94();
    fn_800CB3A8((s16)(0x130 - fn_800CA3DC(s, -1, 0.8f) / 2), 0x43, 0x3E, 0, 0, 0.8f, 0.0f, s);
    fn_80290DDC(buf, lbl_8037359C + 0x3F, val);
    fn_800CB3A8(0x208, 0x21, 0x3E, 0, 0, 1.0f, 0.0f, buf);
    fn_801BCA5C(2.0f);
}

}
