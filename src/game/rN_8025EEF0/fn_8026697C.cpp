/* Dictionary relation chart: floating info window */
#pragma inline_max_size(4000)
#include "game/rN_8025EEF0/calls.h"

struct WPos { int x, y, d; };
struct RelSt {
    struct RelNode* cur;
    struct RelNode* node;
    int x, y;
    u8 pad10[4];
    int pos;
    int t;
    int hold;
    u8 pad20[4];
    void* m24;
    s16 m28; s16 m2A; s16 m2C;
    u8 pad2E[0x16];
    s16 m44; s16 m46;
    u8 pad48[0x14];
    f32 m5C, m60, m64, m68;
};
struct RelNode { const char* name; const char* desc; int m8; int mC; int m10; };

extern "C" {

extern RelSt* lbl_804CC008;
extern char lbl_80372C90[];
extern WPos lbl_80391940[];
void* fn_80076F54(const char* s);
void* fn_8012CE54(const char* s);
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
void fn_800705E4(f32 x, f32 y, f32 w, f32 h, int a);
#if TARGET_PC
FE10_PROTO void * fn_800C3FD0(void* p);
#else
int fn_800C3FD0(void* p);
#endif
void fn_800C4AAC(void* a, void* b, int x, int y, int al, int f);
const char* fn_80118C44(void* u);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);

static inline void body(RelSt* s) {
    char buf[0x60];
/*P*/
    BOOL in;
    u8* u;
    RelNode* c;
    int x;
    int b;
    int a;
    int y;
    RelNode* n;
/*E*/
    in = 0;
    c = s->cur;
    a = (int)((f32)s->m2A * lbl_804CC008->m5C - (f32)s->m44 * lbl_804CC008->m64);
    b = (int)((f32)s->m2C * lbl_804CC008->m60 - (f32)s->m46 * lbl_804CC008->m68);
    if (a >= lbl_80391940[s->pos].x - 0x36 && b >= lbl_80391940[s->pos].y - 0x36 && a <= lbl_80391940[s->pos].x + 0xA6 && b <= lbl_80391940[s->pos].y + 0xA6) {
        in = 1;
    }
    if (in || 0.34862384f != lbl_804CC008->m5C) {
        s->hold = 0;
    }
    if (c == 0 || in || 0.34862384f != lbl_804CC008->m5C) {
        if (s->hold > 0) {
            s->hold--;
            if (s->t < 0x10) s->t++;
        } else if (s->t > 0) {
            s->t--;
        } else if (in) {
            s->pos = (s->pos + 1) % 4;
        }
    } else {
        s->hold = 0x18;
        if (s->t < 0x10) s->t++;
    }
    s->x = (int)fn_8017F68C(lbl_80391940[s->pos].x + lbl_80391940[s->pos].d * 200, lbl_80391940[s->pos].x, s->t, 16.0f, 4);
    s->y = lbl_80391940[s->pos].y;
    if (c != 0) s->node = c;
    n = s->node;
    if (n != 0) {
        u = (u8*)fn_80076F54(n->name);
        x = s->x;
        y = s->y;
        fn_801BCA5C(-5.0f);
        { int k = 0x70; fn_800705E4(x, y, k, k, 0x41); }
        fn_801BCA5C(-1.0f);
        if (fn_800C3FD0(*(void**)(u + 0x10)) != 0) {
            int m = 0;
            if (n->m10 != 0) {
                m = 2;
            } else {
                u8* v = (u8*)fn_8012CE54(n->name);
                if (v != 0) {
                    u32 f = *(u32*)(v + 0x10C);
                    if (!(f & 0x20) && !(f & 0x10) && (f & 8)) m = 1;
                }
            }
            fn_800C4AAC(lbl_804CC008->m24, *(void**)(u + 0x10), x + 0x17, y + 5, 0xFF, m);
        }
        fn_801BCA94();
        fn_80290DDC(buf, lbl_80372C90 + 0x22B, fn_80118C44(u));
        fn_800CB3A8((s16)(x + 0x37 - fn_800CA3DC(buf, -1, 0.75f) / 2), (s16)(y + 0x46), 1, 0, 0, 0.75f, 0.0f, buf);
        if (n->desc != 0) {
            if ((*(u32*)(fn_8024BC94() + 0x18C0) & 0x80000000) && fn_80291188(*(const char**)u, lbl_80372C90 + 0x263) == 0) {
                fn_80290DDC(buf, lbl_80372C90 + 0x22B, fn_800D0864(lbl_80372C90 + 0x271));
            } else {
                fn_80290DDC(buf, lbl_80372C90 + 0x22B, fn_800D0864(n->desc));
            }
            fn_800CB3A8((s16)(x + 0x37 - fn_800CA3DC(buf, -1, 0.75f) / 2), (s16)(y + 0x59), 1, 0, 0, 0.75f, 0.0f, buf);
        }
        fn_801BCA5C(6.0f);
    }
}

void fn_8026697C(void) { body(lbl_804CC008); }

}
