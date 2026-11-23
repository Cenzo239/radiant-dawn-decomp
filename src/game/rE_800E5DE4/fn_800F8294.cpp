#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
typedef f32 Mtx34[3][4];
struct V : Vec { V(const Vec& o) { x = o.x; y = o.y; z = o.z; } };
union Fifo { volatile f32 f; volatile u8 b; };
#define FIFO (*(Fifo*)0xCC008000)
extern "C" {
extern void fn_8001E9E4(void*, Vec*);
extern Vec fn_800076E8(void*, int);
extern void fn_80313460(const Vec*, const Vec*, Vec*);
extern void fn_803128AC(f32*, f32, f32, f32);
extern f32* fn_8000FB88(void);
extern void fn_80312444(f32*, f32*);
extern void fn_80312378(f32*, f32*, f32*);
extern void fn_80307E48(f32*, int);
extern void fn_80021784(int);
extern void fn_80304314(int, int, int);
extern u8 lbl_803CAB38[];
extern u8 lbl_803EC898[];
extern f32 fn_801142F0(void*, f32, f32);
static inline void Pos3(f32 x, f32 y, f32 z) { FIFO.f = x; FIFO.f = y; FIFO.f = z; }
static inline void Col4(u8 r, u8 g, u8 b, u8 a) { FIFO.b = r; FIFO.b = g; FIFO.b = b; FIFO.b = a; }
static inline void Tex2(f32 u, f32 v) { FIFO.f = u; FIFO.f = v; }
void fn_800F8294(f32 r) {
    f32 t[3][4];
    f32 u[3][4];
    Vec p = {0.0f, 0.0f, 0.0f};
    p.x = *(f32*)(lbl_803CAB38 + 0x944);
    p.y = *(f32*)(lbl_803CAB38 + 0x948);
    p.z = fn_801142F0(lbl_803EC898, p.x, p.y);
    fn_803128AC(&t[0][0], p.x, p.y, p.z);
    fn_80312444(fn_8000FB88(), &u[0][0]);
    fn_80312378(&t[0][0], &u[0][0], &u[0][0]);
    fn_80312378(fn_8000FB88(), &u[0][0], &u[0][0]);
    fn_80307E48(&u[0][0], 0);
    fn_80021784(0);
    fn_80304314(0x98, 0, 4);
    f32 n = -r;
    Pos3(n, n, 0.0f); Col4(0xFF, 0xFF, 0xFF, 0xFF); Tex2(0.0f, 0.0f);
    Pos3(r, n, 0.0f); Col4(0xFF, 0xFF, 0xFF, 0xFF); Tex2(1.0f, 0.0f);
    Pos3(n, r, 0.0f); Col4(0xFF, 0xFF, 0xFF, 0xFF); Tex2(0.0f, 1.0f);
    Pos3(r, r, 0.0f); Col4(0xFF, 0xFF, 0xFF, 0xFF); Tex2(1.0f, 1.0f);
}
}
