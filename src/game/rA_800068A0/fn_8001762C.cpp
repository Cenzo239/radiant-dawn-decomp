#include "game/rA_800068A0/types.h"
extern "C" {
typedef f32 Mtx[3][4];
typedef struct Vec { f32 x, y, z; } Vec;
typedef struct GPart { Vec pos; Vec vel; f32 x18; f32 x1C; f32 x20; f32 x24; f32 x28; u8 r, g, b, a; u8 x30[0x48 - 0x30]; u8 x48, x49; s16 x4A; } GPart;
typedef struct GSeg { u8 x0[0xA]; s16 id; u8 xC[0x1C - 0xC]; u16 node; u16 count; } GSeg;
typedef struct SV { s16 x, y, z; } SV;
typedef struct GEnt { u8 x0[0xC]; GPart* parts; SV* buf; } GEnt;
typedef struct GLay { u8 x0[8]; f32 x8, xC, x10, x14, x18; } GLay;
typedef struct GMatL { u8 x0[0x14]; GLay* layers; } GMatL;
typedef struct GAnm { u32 x0; u8 x4[0x10]; int t0; int t1; } GAnm;
extern const Vec lbl_80360DE0;
extern GAnm* fn_80007F10(void* a);
extern void* fn_80007EE4(void* a);
extern void* fn_8000F3D4(void* m, u16 i);
extern int fn_80016568(GSeg* s, GMatL* m, void* e, GAnm* an);
extern void* fn_8000FB88(void);
extern void fn_80307E48(const void* m, int id);
extern void fn_80021784(int);
extern void fn_8001D44C(const void* a, void* b);
extern void fn_8001E638(const void* a, void* b);
extern void fn_80016368(GSeg* s, void* n, void* a, void* b);
extern void fn_803134C4(const Vec* a, Vec* b);
extern void fn_80312DB4(const void* m, const Vec* a, Vec* b);
extern f32 fn_80313508(const Vec* v);
extern void fn_8001E0B4(Vec* o, const SV* s);
extern int fn_8000AE38(GAnm* b, int id, f32* out, f32 frame);
extern int fn_8000B100(GAnm* b, int id, f32* out, f32 frame);
extern int fn_8000B3C8(GAnm* b, int id, f32* out, f32 frame);
extern int fn_8000B690(GAnm* b, int id, f32* out, f32 frame);
extern int fn_8000B958(GAnm* b, int id, f32* out, f32 frame);
extern void fn_80312318(void* m);
extern void fn_803128AC(void* m, f32 x, f32 y, f32 z);
extern void fn_8031292C(void* m, f32 x, f32 y, f32 z);
extern void fn_80312654(void* m, int axis, f32 a);
extern void fn_80312378(const void* a, const void* b, void* c);
extern void fn_80307F10(const void* m, u32 id, u32 type);
extern void fn_8001BD34(f32 w, void* n, void* m, Vec* pos, f32* sz, u8* al, int cnt, int mode);
static inline SV* at(SV* b, int o, int v) { return b + (v % 32 + o); }
void fn_8001762C(u8* a, GEnt* st, GSeg* s, GMatL* m, void* e) {

    Vec* pv;
    f32* ps;
    GLay* l;
    u8* pa;
    int i;
    int j;
    GAnm* an;
    void* nd;
    int tm;
    GPart* p;
    int cnt;
    int base2;
    int base;
    f32 sc;
    f32 t;

    Vec vpos[32];
    f32 size[32];
    Mtx view;
    Mtx rot;
    Mtx tex;
    Mtx mt;
    Mtx mr;
    Mtx ms;
    u8 alpha[32];
    Vec v2;
    f32 ksy, ksx, kty, ktx, kr;
    an = fn_80007F10(a);
    nd = fn_8000F3D4(fn_80007EE4(a), s->node);
    tm = fn_80016568(s, m, e, an);
    p = st->parts;
    fn_80307E48(fn_8000FB88(), 0);
    fn_80021784(0);
    fn_8001D44C(a + 0xC, view);
    fn_8001E638(view, rot);
    fn_80016368(s, nd, view, view);
    Vec n = {1.0f, 1.0f, 1.0f};
    fn_803134C4(&n, &n);
    fn_80312DB4(rot, &n, &n);
    sc = fn_80313508(&n);
    for (i = 0; i < s->count; i++, p++) {
        if (!(p->x18 < 0.0f)) {
            cnt = p->x24;
            if (cnt > p->x48) {
                cnt = p->x48;
            }
            if (cnt <= 1) {
                break;
            }
            fn_80312DB4(view, &p->pos, &vpos[0]);
            pv = &vpos[1];
            ps = &size[1];
            pa = &alpha[1];
            size[0] = p->x20 * sc;
            alpha[0] = p->a;
            base = p->x49;
            base += p->x48;
            base2 = base + 0x20;
            for (j = 1; j < cnt;) {
                Vec v3;
                fn_8001E0B4(&v3, at(st->buf, p->x4A, base2 - j));
                v2 = v3;
                fn_80312DB4(view, &v2, pv);
                pv++;
                j++;
                *ps = p->x20 * sc;
                ps++;
                *pa = p->a;
                pa++;
            }
            if (tm != 0x3C) {
                l = m->layers;
                kr = l->x18;
                ktx = l->x8;
                kty = l->xC;
                ksx = l->x10;
                ksy = l->x14;
                if (an->x0 != 0) {
                    t = p->x1C * (f32)(an->t1 - an->t0) + (f32)an->t0;
                    fn_8000B3C8(an, s->id, &kr, t);
                    fn_8000AE38(an, s->id, &ktx, t);
                    fn_8000B100(an, s->id, &kty, t);
                    fn_8000B690(an, s->id, &ksx, t);
                    fn_8000B958(an, s->id, &ksy, t);
                }
                fn_80312318(tex);
                if (0.0f != kr) {
                    fn_803128AC(mt, -0.5f, -0.5f, 0.0f);
                    fn_80312654(mr, 0x7A, 0.017453292f * -kr);
                    fn_80312378(mr, mt, mr);
                    fn_803128AC(mt, 0.5f, 0.5f, 0.0f);
                    fn_80312378(mt, mr, tex);
                }
                if (1.0f != ksx || 1.0f != ksy) {
                    fn_803128AC(mt, 0.0f, -1.0f, 0.0f);
                    fn_8031292C(ms, ksx, ksy, 1.0f);
                    fn_80312378(ms, mt, ms);
                    fn_803128AC(mt, 0.0f, 1.0f, 0.0f);
                    fn_80312378(mt, ms, ms);
                    fn_80312378(ms, tex, tex);
                }
                if (0.0f != ktx || 0.0f != kty) {
                    fn_803128AC(mt, ktx, -kty, 0.0f);
                    fn_80312378(mt, tex, tex);
                }
                fn_80307F10(tex, tm, 1);
            }
            fn_8001BD34(p->x28, nd, view, vpos, size, alpha, cnt, 2);
        }
    }
}
}
