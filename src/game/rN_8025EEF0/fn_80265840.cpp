/* Dictionary relation chart: unit box */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

extern "C" {

void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);
u8* fn_800D4228(const char* s);
u8* fn_800D4188(const char* s, void* p);
#if TARGET_PC
FE10_PROTO char * fn_80291480(const char* a, const char* b);
#else
int fn_80291480(const char* a, const char* b);
#endif
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_800804D4(int r, int g, int b, int a);

struct RelBox { const char* name; s16 x; s16 y; const char* msg; s16 tx; s16 ty; };

static inline void SetPos(u8* p, f32 x, f32 y) { *(f32*)(p + 0x40) = x; *(f32*)(p + 0x44) = y; }
static inline void SetV(u8* p, f32 x, f32 y) { *(f32*)(p + 0x4C) = x; *(f32*)(p + 0x50) = y; }
static inline void SetS(u8* p, f32 x, f32 y) { *(f32*)(p + 0x54) = x; *(f32*)(p + 0x58) = y; }

void fn_80265840(u8* m, RelBox* e, int flag) {
        int tx;
    f32 sc;
    u8* q;
    u8* p2;
    const char* name;
    int ty;
    u8* p;
    const char* s;
    int x;
    char buf[0x40];
    int y;
    int w;
    int bw;
    const char* msg;

    x = e->x;
    y = e->y;
    tx = e->tx;
    ty = e->ty;
    sc = 0.7f;
    if (e->name != 0) {
        if (*(u32*)(fn_8024BC94() + 0x18C0) & 0x80000000) {
            s = lbl_80372C90;
            name = e->name;
            if (fn_80291188(name, s + 0x1F7) == 0 || fn_80291188(name, s + 0x200) == 0) {
                fn_80290DDC(buf, lbl_80372C90 + 0x20B, name);
            } else {
                fn_80290DDC(buf, lbl_80372C90 + 0x11C, name);
            }
        } else {
            fn_80290DDC(buf, lbl_80372C90 + 0x11C, e->name);
        }
        p = fn_800D4228(buf);
        if (p == 0) {
            p = fn_800D4188(buf, lbl_804CC000);
        }
        if (p != 0) {
            SetPos(p, (f32)x + lbl_804CC008->f54, (f32)y + lbl_804CC008->f58);
            SetV(p, 0.0f, 0.0f);
            SetS(p, lbl_804CC008->f5C, lbl_804CC008->f60);
        }
    }
    if (flag != 0 && (q = (u8*)e->msg) != 0) {
        if (fn_80291480(*(const char**)(m + 4), lbl_80372C90 + 0x10) != 0) {
            fn_80290DDC(buf, lbl_80372C90 + 0x11C, (const char*)q);
            p2 = fn_800D4228(buf);
            if (p2 == 0) {
                p2 = fn_800D4188(buf, lbl_804CC000);
            }
            if (p2 != 0) {
                f32 a;
                if (fn_801D09F0() != 0) {
                    a = 0.764f;
                } else {
                    a = 1.0f;
                }
                SetPos(p2, (f32)tx + lbl_804CC008->f54, (f32)ty + lbl_804CC008->f58);
                SetV(p2, tx, ty);
                SetS(p2, lbl_804CC008->f5C * a, lbl_804CC008->f60);
            }
        } else {
            fn_801BCA5C(-4.0f);
            msg = fn_800D0864(e->msg);
            w = fn_800CA3DC(msg, -1, sc);
            fn_8007E154();
            fn_8007E174(0, 0x12);
            fn_8007E164();
            fn_800800D4(1);
            bw = w + 10;
            fn_80080388(tx - bw / 2, ty, bw, 20.0f);
            fn_800804D4(0x5A, 0x4B, 0x40, 0xFF);
            fn_80080308();
            fn_801BCA5C(-1.0f);
            fn_801BCA94();
            fn_800CB3A8((s16)(tx - w / 2), (s16)(ty + 1), 1, 0, 0, sc, 0.0f, msg);
            fn_801BCA5C(5.0f);
        }
    }
}

}
