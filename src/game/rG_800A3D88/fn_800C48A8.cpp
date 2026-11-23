#include "game/rG_800A3D88/types.h"
extern "C" {
struct Rec { int x, y, w, h; u32 color; u8 mtx[0x30]; void* res; int idx; int prio; u8 flag; u8 p51[3]; };
extern Rec lbl_803E5130[];
extern int lbl_804CB6C8;
extern const f32 lbl_804CD560, lbl_804CD568;
struct FD { void* res; u8 p4[0x1E]; s16 m22; };
struct FX { u8 p[0x30]; void* m30; FD* m34; u8 p38[0x10]; u32 m48; };
struct FR { u8 p[0x2C]; s16 m2c; };
void fn_8007E154();
void fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E41C(void*, p32arg, int, int);
#else
void fn_8007E41C(void*, int, int, int);
#endif
void fn_8007E7DC(int);
void* fn_800C79A0(void*);
void fn_800C7A98(void*);
void fn_800800D4(int);
void fn_80080430(f32, f32, f32, f32, f32, f32);
void fn_80080388(f32, f32, f32, f32);
void fn_800803C8(f32, f32, f32, f32);
void fn_80080578(int);
void fn_80080494();
void fn_80080308();
#if TARGET_PC
FE10_PROTO void* fn_8007E4C4(p32arg);
#else
void* fn_8007E4C4(int);
#endif
void fn_80312344(void*, void*);
#if TARGET_PC
FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
void fn_80080910(void (*)(void*), void*);
#endif
void fn_800C43C4(void*);
FR* fn_80076F54(const char*);
extern char lbl_80365E0C[];
static inline FR* FontGet(const char* name) {
    FR* r = fn_80076F54(name);
    if (r != NULL) return r;
    return fn_80076F54(lbl_80365E0C + 0x3A);
}
void fn_800C48A8(int x, int y, int col, FX* f, int prio) {
    fn_8007E154();
    int idx;
    FD* d = f->m34;
    idx = d->m22;
    if (idx == 0xFFFF) idx = 0;
    fn_8007E41C(fn_800C79A0(d->res), idx, 0, 0x11);
    fn_800C7A98(d->res);
    fn_8007E7DC((u8)col);
    fn_8007E164();
    if (prio == 0) {
        fn_800800D4(1);
        fn_80080430(x, y, lbl_804CD560, lbl_804CD560, lbl_804CD568, lbl_804CD568);
        fn_80080578(0);
        if ((f->m48 & 1) == 1) fn_80080494();
        fn_80080308();
    } else {
        Rec* r = &lbl_803E5130[lbl_804CB6C8];
        r->x = x; r->y = y; r->w = 0x40; r->h = 0x40; r->color = col;
        fn_80312344(fn_8007E4C4(0), r->mtx);
        r->res = f->m30;
        r->idx = f->m34->m22;
        r->prio = prio;
        if ((f->m48 & 1) == 1) r->flag = 1; else r->flag = 0;
        lbl_804CB6C8++;
        if (lbl_804CB6C8 >= 100) lbl_804CB6C8 = 0;
        fn_800800D4(0xB);
        fn_80080910(fn_800C43C4, r);
        fn_80080308();
    }
}
void fn_800C4AAC(void* tex, const char* name, int x, int y, int col, int prio) {
    FR* fr = FontGet(name);
    if (fr == NULL || fr->m2c < 0) return;
    fn_8007E154();
    fn_8007E41C(tex, fr->m2c, 0, 0x11);
    fn_8007E7DC((u8)col);
    fn_8007E164();
    if (prio == 0) {
        fn_800800D4(1);
        fn_80080430(x, y, lbl_804CD560, lbl_804CD560, lbl_804CD568, lbl_804CD568);
        fn_80080578(0);
        fn_80080308();
    } else {
        Rec* r = &lbl_803E5130[lbl_804CB6C8];
        r->x = x; r->y = y; r->w = 0x40; r->h = 0x40; r->color = col;
        fn_80312344(fn_8007E4C4(0), r->mtx);
        r->res = tex;
        r->idx = fr->m2c;
        r->prio = prio;
        lbl_804CB6C8++;
        if (lbl_804CB6C8 >= 100) lbl_804CB6C8 = 0;
        fn_800800D4(0xB);
        fn_80080910(fn_800C43C4, r);
        fn_80080308();
    }
}
void fn_800C4C3C(void* tex, const char* name, int x, int y, int w, int h, int col, int prio) {
    FR* fr = FontGet(name);
    fn_8007E154();
    fn_8007E41C(tex, fr->m2c, 0, 0x11);
    fn_8007E7DC((u8)col);
    fn_8007E164();
    if (prio == 0) {
        fn_800800D4(1);
        fn_80080388(x, y, w, h);
        fn_800803C8(lbl_804CD560, lbl_804CD560, lbl_804CD568, lbl_804CD568);
        fn_80080578(0);
        fn_80080308();
    } else {
        Rec* r = &lbl_803E5130[lbl_804CB6C8];
        r->x = x; r->y = y; r->w = w; r->h = h; r->color = col;
        fn_80312344(fn_8007E4C4(0), r->mtx);
        r->res = tex;
        r->idx = fr->m2c;
        r->prio = prio;
        lbl_804CB6C8++;
        if (lbl_804CB6C8 >= 100) lbl_804CB6C8 = 0;
        fn_800800D4(0xB);
        fn_80080910(fn_800C43C4, r);
        fn_80080308();
    }
}
}
