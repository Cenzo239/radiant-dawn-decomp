#include "game/rG_800A3D88/chr.h"

// Battle character: turn the head bone towards the opponent's head.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct Quat { f32 x, y, z, w; };
struct BoneH { u8 p[4]; BoneH* m4; BoneH* m8; u8 pc[0xEC - 0xC]; u32 ec; };
struct AnimH { u8 p[8]; u16 m8; };
struct ChH { u8 p[0x30]; Mdl* mdl; u8 p34[0x50 - 0x34]; u32 m50; u8 p54[0x68 - 0x54]; Quat m68; void* data; AnimH* m7c; ChH* m80; };
struct W3 { u32 a, b, c; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_80007630(Mdl*, const char*);
int fn_800B4000(ChH*, int, Vec*, int, int);
void* fn_80007EE4(Mdl*);
Mtx34* fn_800080B8(Mdl*);
void* fn_800080E4(Mdl*);
BoneH* fn_8000F3D4(void*, int);
void fn_80312344(void*, void*);
void fn_80312494(Mtx34*, Mtx34*);
void fn_80312318(void*);
void fn_80312DB4(Mtx34*, Vec*, Vec*);
void fn_800076E8(Vec*, Mdl*, int);
void fn_80313484(Vec*, Vec*, Vec*);
f32 fn_80313508(Vec*);
void fn_803134C4(Vec*, Vec*);
void fn_8031356C(Vec*, Vec*, Vec*);
void fn_8000F328(BoneH*, Mtx34*);
f32 fn_8031354C(Vec*, Vec*);
double fn_80295A90(double);
f32 fn_800A7370(void*, const char*);
void fn_80312830(Mtx34*, Vec*, f32);
void fn_803135A8(Quat*, Mtx34*);
f32 fn_800A84A4(const char*);
f32 fn_80006CF8();
void fn_80313774(Quat*, Quat*, Quat*, f32);
void fn_803129AC(Mtx34*, Quat*);
void fn_8000EDEC(BoneH*, Mtx34*);
void fn_80312378(Mtx34*, Mtx34*, Mtx34*);
void fn_8000EC30(BoneH*, Mtx34*, void*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A7460(void*, const char*);
#else
void* fn_800A7460(void*, const char*);
#endif
static inline int Node(ChH* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
int fn_800B0CD4(ChH* c) {
    Mtx34 save, inv, rot, bm;
    Vec tgt, v60, v54, v48, v3c, v30;
    Quat q;
    Vec t0, t1;
/*P*/
int k2;
Mtx34* mats;
void* nodes;
int k;
BoneH* i;
ChH* o;
BoneH* b;
void* w;
/*E*/
    if (c->mdl == NULL) return 0;
    if (c->m7c == NULL) return 0;
    o = c->m80;
    if (o == NULL) return 0;
    if (o->m50 & 1) return 0;
    if (!(c->m50 & 0x40)) return 0;
    if (!fn_800B4000(o, Node(o, STR(0x2B)), &tgt, -1, 0)) return 0;
    k = Node(c, STR(0x2B));
    k2 = Node(c, STR(0x30));
    if (k < 0 || k2 < 0) return 0;
    nodes = fn_80007EE4(c->mdl);
    mats = fn_800080B8(c->mdl);
    w = fn_800080E4(c->mdl);
    b = fn_8000F3D4(nodes, k);
    fn_80312344((u8*)c->mdl + 0x10, &save);
    fn_80312494(&save, &inv);
    fn_80312318((u8*)c->mdl + 0x10);
    fn_80312DB4(&inv, &tgt, &tgt);
    fn_80312318(&rot);
    if (c->m7c->m8 & 0x80) {
        fn_800076E8(&t0, c->mdl, k);
        v60 = t0;
        fn_800076E8(&t1, c->mdl, k2);
        v54 = t1;
        fn_80313484(&v54, &v60, &v48);
        fn_80313484(&tgt, &v60, &v3c);
        v48.x = 0.0f;
        v3c.x = 0.0f;
        if (fn_80313508(&v48) > 0.0f && fn_80313508(&v3c)) {
            fn_803134C4(&v48, &v48);
            fn_803134C4(&v3c, &v3c);
            fn_8031356C(&v48, &v3c, &v30);
            if (fn_80313508(&v30) >= 0.001f) {
                fn_8000F328(b, &bm);
                fn_80312DB4(&bm, &v30, &v30);
                f32 dot = fn_8031354C(&v48, &v3c);
                if (dot >= 0.0f) {
                    f32 a = fn_80295A90(dot);
                    f32 lim = 0.017453292f * fn_800A7370(c->data, STR(0x34));
                    if (a > lim) a = lim;
                    if (a < -lim) a = -lim;
                    fn_80312830(&rot, &v30, a);
                }
            }
        }
    }
    fn_803135A8(&q, &rot);
    f32 rate = fn_800A84A4(STR(0x3D));
    f32 rt = rate * fn_80006CF8();
    fn_80313774(&c->m68, &q, &c->m68, rt);
    fn_803129AC(&rot, &c->m68);
    fn_8000EDEC(b, mats);
    fn_80312378(&mats[k], &rot, &mats[k]);
    fn_8000EC30(b, mats, w);
    if (fn_800A7460(c->data, STR(0x46)) == NULL) {
        fn_80312494(&rot, &rot);
        for (i = b->m8; i != NULL; i = i->m4) {
            if ((i->ec >> 20) != (u32)k2) {
                fn_8000EDEC(i, mats);
                fn_80312378(&mats[i->ec >> 20], &rot, &mats[i->ec >> 20]);
                fn_8000EC30(i, mats, w);
            }
        }
    }
    fn_80312344(&save, (u8*)c->mdl + 0x10);
    return 1;
}
}
